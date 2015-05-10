/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma comment(lib, "userenv.lib")
#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "shlwapi.lib")

#define SECURITY_WIN32
#include <Userenv.h>
#include <Security.h>
#include <Shlwapi.h>
#include <fcntl.h>
#include <io.h>

#include "emu.Module.h"
#include "emu.log.h"
#include "hal.os.h"

namespace emu
{
    namespace log
    {
        Category emu("emu", "Emulation");
        Category hal("hal", "Hardware Abstract Layout");
        Category lle("lle", "Low Level Emulation");
        Category hle("hle", "High Level Emulation");

        SubCategory log(emu, "log", "Logging Facility");

        struct Overlapped : OVERLAPPED
        {
            char Buffer[1024];
        };

        static const long log_overlapped_bit = 8; // up to 256 synchronous log calls without blocking the caller execution
        static const long log_overlapped_max = 1<<log_overlapped_bit;
        long              log_overlapped_key = 0;
        wchar_t         * log_filename       = 0;
        HANDLE            log_file           = INVALID_HANDLE_VALUE;
        long              log_offset;
        Overlapped        log_overlapped[log_overlapped_max];

        static char const * const level_name[] =
        {
            "E_OFF", "E_FATAL", "E_ERROR", "E_WARN", "E_INFO", "E_DEBUG", "E_TRACE", "E_FORCE"
        };

        struct Implementation : Interface
        {
            using Interface::GetVersion;
            using Interface::Log;
            using Interface::Register;
            using Interface::Unregister;

            static long GetVersion(emu::Interface *) { return version; }

            static void Log(Category const * that, Level level, char const src[]);

            static void Register(Category *& that, Category * parent);

            static void Unregister(Category *& that, Category * parent);

            static void UseConsole()
            {
                static const WORD MAX_CONSOLE_LINES = 1024;

                int hConHandle;
                long lStdHandle;

                CONSOLE_SCREEN_BUFFER_INFO coninfo;

                FILE * fp;

                ::AllocConsole();
                ::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);

                coninfo.dwSize.Y = MAX_CONSOLE_LINES;

                ::SetConsoleScreenBufferSize(::GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

                // redirect unbuffered STDOUT to the console
                lStdHandle = (long)::GetStdHandle(STD_OUTPUT_HANDLE);
                hConHandle = ::_open_osfhandle(lStdHandle, _O_TEXT);
                fp = ::_fdopen(hConHandle, "w");
                *stdout = *fp;
                ::setvbuf(stdout, NULL, _IONBF, 0);

                // redirect unbuffered STDIN to the console
                lStdHandle = (long)::GetStdHandle(STD_INPUT_HANDLE);
                hConHandle = ::_open_osfhandle(lStdHandle, _O_TEXT);
                fp = ::_fdopen(hConHandle, "r");
                *stdin = *fp;
                ::setvbuf(stdin, NULL, _IONBF, 0);

                // redirect unbuffered STDERR to the console
                lStdHandle = (long)::GetStdHandle(STD_ERROR_HANDLE);
                hConHandle = ::_open_osfhandle(lStdHandle, _O_TEXT);
                fp = ::_fdopen( hConHandle, "w" );
                *stderr = *fp;
                ::setvbuf(stderr, NULL, _IONBF, 0);

                use_stderr = true;

                // point to console as well
                //ios::sync_with_stdio();
            }

            static void FreeConsole()
            {
                if (use_stderr)
                {
                    ::FreeConsole();
                }
            }

            Implementation()
            {
                critical_section.Create();

                this->Interface::GetVersion_ = &Implementation::GetVersion;
                this->Interface::Log_        = &Implementation::Log;
                this->Interface::Register_   = &Implementation::Register;
                this->Interface::Unregister_ = &Implementation::Unregister;

                HANDLE hprocess = ::GetCurrentProcess();
                HANDLE token = 0;
                BOOL ok = ::OpenProcessToken(hprocess, TOKEN_QUERY, &token);
                if (ok)
                {
                    DWORD dwBufferSize = 0;
                    wchar_t * path;

                    // Retrieve Home Directory
                    ok = ::GetUserProfileDirectoryW(token, NULL, &dwBufferSize);
                    if (!ok && dwBufferSize != 0)
                    {
                        path = new wchar_t[dwBufferSize];
                        ok = ::GetUserProfileDirectoryW(token, path, &dwBufferSize);
                        if (ok)
                        {
                            log_filename = new wchar_t[dwBufferSize + sizeof(L"\\" W_EMULATOR_NAME L"\\" W_EMULATOR_NAME L"-YYYYMMDDhhmmss.sss.log")];

                            ::wsprintfW(log_filename, L"%s\\" W_EMULATOR_NAME, path);
                            _wmkdir(log_filename);

                            SYSTEMTIME st;

                            ::GetSystemTime(&st);

                            ::wsprintfW(log_filename, L"%s\\" W_EMULATOR_NAME L"\\" W_EMULATOR_NAME L"-%04u%02u%02u%02u%02u%02u%03u.log", path, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

                            ::CloseHandle(token);

                            log_file = ::CreateFileW(log_filename, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED|FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH, NULL);
                            if (INVALID_HANDLE_VALUE != log_file)
                            {
                                log_offset = 0;

                                for (long i = 0; i < log_overlapped_max; ++i)
                                {
                                    memset(log_overlapped + i, 0, sizeof(Overlapped));
                                    log_overlapped[i].hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
                                }

                                use_stderr = false;

                                delete [] path;

                                return;
                            }
                        }

                        delete [] path;
                    }
                }

                UseConsole();
            }

            ~Implementation()
            {
                if (INVALID_HANDLE_VALUE != log_file)
                {
                    for (long i = 0; i < log_overlapped_max; ++i)
                    {
                        DWORD  dummy;
                        auto & overlapped = log_overlapped[i];

                        // wait for previous asynchronous I/O completion if any
                        ::GetOverlappedResult(log_file, &overlapped, &dummy, TRUE);

                        ::CloseHandle(overlapped.hEvent);
                    }

                    // it is safe to close the file here because the file will be closed internally by the kernel
                    // only after all I/O asynchronous operations on this file complete
                    ::CloseHandle(log_file);
                }

                delete [] log_filename;

                FreeConsole();

                critical_section.Delete();
            }

            bool DllProcessAttach()
            {
                infof(log, L"Logging into '%s'.", log_filename);

                return true;
            }

            void DllProcessDetach()
            {
            }

            static Categories & GetCategories() { static Categories root; return root; }

        protected:
            static hal::os::Benaphore critical_section;
            static bool use_stderr;
        };

        hal::os::Benaphore Implementation::critical_section(false);
        bool               Implementation::use_stderr;

        void Implementation::Log(Category const * that, Level level, char const src[])
        {
            long              thuid;
            SYSTEMTIME        st;
            ::GetLocalTime(&st);
            thuid = 0; //GetKernelThreadUid();

            if (use_stderr)
            {
                fprintf(stderr, "%-95s|%-7s|%08X|%04d-%02d-%02d %02d:%02d:%02d.%03d| %s\r\n", that->GetName().c_str(), level_name[level], thuid, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, src);
            }
            else
            {
                static long const maxlength  = sizeof(log_overlapped[0].Buffer);
                DWORD             dummy;
                long              index      = _InterlockedExchangeAdd(&log_overlapped_key, 1)&(log_overlapped_max-1);
                auto            & overlapped = log_overlapped[index];

                // wait for previous asynchronous I/O completion if any
                ::GetOverlappedResult(log_file, &overlapped, &dummy, TRUE);
                //::ResetEvent(overlapped.hEvent);

                long length = ::snprintf(overlapped.Buffer, maxlength, "%-95s|%-7s|%08X|%04d-%02d-%02d %02d:%02d:%02d.%03d| %s\r\n", that->GetName().c_str(), level_name[level], thuid, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, src);
                overlapped.Offset = (DWORD)_InterlockedExchangeAdd(&log_offset, length);

                // starts a new asynchronous I/O
                ::WriteFile(log_file, overlapped.Buffer, length, &dummy, &overlapped);
            }
        }

        void Implementation::Register(Category *& that, Category * parent)
        {
            critical_section.Enter();
            if (!parent)
            {
                auto & categories = GetCategories();
                for (auto category : categories)
                {
                    // checks whether there is already a registered category of the same name
                    if (category->GetName() == that->GetName())
                    {
                        // if so, just create an alias to the already registered category
                        that = category;

                        critical_section.Leave();

                        return;
                    }
                }
                // if not, register the new category
                categories.insert(that);
            }
            else
            {
                auto & subcategories = parent->GetSubCategories();
                for (auto subcategory : subcategories)
                {
                    // checks whether there is already a registered subcategory of the same name
                    if (subcategory->GetName() == that->GetName())
                    {
                        // if so, just create an alias to the already registered subcategory
                        that = subcategory;

                        critical_section.Leave();

                        return;
                    }
                }
                // if not, register the new category
                subcategories.insert((SubCategory *)that);
            }
            critical_section.Leave();
        }

        void Implementation::Unregister(Category *& that, Category * parent)
        {
            critical_section.Enter();
            if (parent)
            {
                parent->GetSubCategories().erase((SubCategory *)that);
                that = 0;
            }
            else
            {
                GetCategories().erase(that);
            }
            critical_section.Leave();
        }

        Interface * instance = 0;

        struct NullImplementation : Interface
        {
            using Interface::GetVersion;
            using Interface::Log;
            using Interface::Register;
            using Interface::Unregister;

            static long GetVersion(emu::Interface *) { return 0; }

            static void Log(Category const * that, Level level, char const src[]) {}

            static void Register(Category *& that, Category * parent) {}

            static void Unregister(Category *& that, Category * parent) {}

            NullImplementation()
            {
                this->Interface::GetVersion_ = &NullImplementation::GetVersion;
                this->Interface::Log_        = &NullImplementation::Log;
                this->Interface::Register_   = &NullImplementation::Register;
                this->Interface::Unregister_ = &NullImplementation::Unregister;
            }

            virtual bool DllProcessAttach() { return true; };
            virtual void DllProcessDetach() {};
        };

        static NullImplementation null_instance;

        Category::Category( char const * name, char const * labelname /*= 0*/ ) : m_name(name), m_labelname(labelname ? labelname : name)
        {
            m_level     = E_DEFAULT;
            GetLevel$   = GetLevel$Category;
            CheckLevel$ = CheckLevel$Category;
            LogfA$      = LogfA$Category;
            LogfW$      = LogfW$Category;
            that        = this;
            if (!instance)
            {
                instance = GetInstance();
                if (!instance)
                {
                    instance = &null_instance;
                }
            }
            instance->Register(that, 0);
        }

        Category::Category(std::string const & name, char const * labelname) : m_name(name), m_labelname(labelname ? labelname : name)
        {
            m_level     = E_DEFAULT;
            GetLevel$   = GetLevel$Category;
            CheckLevel$ = CheckLevel$Category;
            LogfA$      = LogfA$Category;
            LogfW$      = LogfW$Category;
            that        = this;
            if (!instance)
            {
                instance = GetInstance();
                if (!instance)
                {
                    instance = &null_instance;
                }
            }
            instance->Register(that, 0);
        }

        Category::~Category()
        {
            if (that == this)
            {
                instance->Unregister(that, 0);
            }
        }

        Level Category::GetLevel$Category(Category const * that)
        {
            return that->m_level;
        }

        bool Category::CheckLevel$Category(Category const * that, Level level)
        {
            return that->m_level >= level;
        }

        void Category::LogfA$Category(Category const * that, Level level, char const fmt[], va_list args)
        {
            char src[1024];
            ::vsnprintf(src, 1024, fmt, args);
            instance->Log(that, level, src);
        }

        void Category::LogfW$Category(Category const * that, Level level, wchar_t const fmt[], va_list args)
        {
            wchar_t tmp[1024];
            char    src[2048];
            ::wvnsprintf(tmp, 1024, fmt, args);
            ::wcstombs(src, tmp, sizeof(src));
            instance->Log(that, level, src);
        }

        SubCategory::SubCategory(Category & category, char const * subname, char const * labelname /*= 0*/) : Category((category.GetName() + ".") + subname, labelname ? labelname : subname), m_category(category), m_subname(subname), m_off(false)
        {
            GetLevel$   = GetLevel$SubCategory;
            CheckLevel$ = CheckLevel$SubCategory;
            LogfA$      = LogfA$Category;
            LogfW$      = LogfW$Category;
            that        = this;

            instance->Register(that, &m_category);
        }

        SubCategory::~SubCategory()
        {
            if (that == this)
            {
                instance->Unregister(that, &m_category);
            }
            else
            {
                that = 0; // always 0 for Category destructor when called after SubCategory destructor
            }
        }

        Level SubCategory::GetLevel$SubCategory(Category const * category)
        {
            SubCategory * that = (SubCategory *)category;

            return ((SubCategory *)that)->m_category.GetLevel();
        }

        bool SubCategory::CheckLevel$SubCategory(Category const * category, Level level)
        {
            SubCategory * that = (SubCategory *)category;

            return !that->m_off  && that->m_category.GetLevel() >= level;
        }
    }
}

static emu::log::Implementation * implementation = 0;

#if defined(EMU_EXPORTS)
extern "C" __declspec(dllexport) emu::log::Interface * emu_log$GetInterface(long version)
{
    return implementation;
}

extern void ForceLinkWithStartupCleanup();

void emu::log::Startup()
{
    ForceLinkWithStartupCleanup();

    implementation = new Implementation;
}

void emu::log::Cleanup()
{
    delete implementation;
}

#else
extern "C" emu::log::Interface * emu_log$GetInterface(long version)
{
    typedef emu::log::Interface * (Function)(long version);
    static Function * function = emu::Module::GetFunction< Function >("emu_log$GetInterface");
    if (function)
    {
        return function(version);
    }
    return 0;
}
#endif
