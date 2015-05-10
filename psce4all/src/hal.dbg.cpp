/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hal.dbg.h"

namespace emu
{
    namespace log
    {
        SubCategory dbg(hal, "dbg", "DBG - Debugging Facility");
    }
}

#include <psapi.h>
#include <comdef.h>
#include <dbghelp.h>

#pragma comment(lib, "psapi")
#pragma comment(lib, "dbghelp")

////////////////////////////////////////////// DIA //////////////////////////////////////////////////

#include "cvconst.h"
#include "dia2.h"

class __declspec(uuid("E60AFBEE-502D-46AE-858F-8272A09BD707")) DiaSource71_;
class __declspec(uuid("BCE36434-2C24-499E-BF49-8BD99B0EEB68")) DiaSource80_;
class __declspec(uuid("4C41678E-887B-4365-A09E-925D28DB33C2")) DiaSource90_;
class __declspec(uuid("B86AE24D-BF2F-4ac9-B5A2-34B14E4CE11D")) DiaSource100;
class __declspec(uuid("761D3BCD-1304-41D5-94E8-EAC54E4AC172")) DiaSource110;
class __declspec(uuid("3BFCEA48-620F-4B6B-81F7-B9AF75454C7D")) DiaSource120;

class __declspec(uuid("83AB22C8-993A-4D14-A0E0-37BC0AAEA793")) DiaSource120_Alternative;

static HRESULT __stdcall CoCreateInstance(wchar_t const * dllName, REFCLSID rclsid, REFIID riid, void ** ppv)
{
    HRESULT hr = S_FALSE;
    HMODULE hDIADll = ::LoadLibraryW(dllName);
    if (hDIADll)
    {
        typedef HRESULT __stdcall PDllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppvObj);
        auto DllGetClassObject = (PDllGetClassObject *)::GetProcAddress(hDIADll, "DllGetClassObject");
        if (DllGetClassObject)
        {
            IClassFactory * classFactory;
            hr = DllGetClassObject(rclsid, IID_IClassFactory, (void**)&classFactory);
            if (SUCCEEDED(hr))
            {
                hr = classFactory->CreateInstance(0, riid, ppv);
                classFactory->Release();
            }
        }

        if (FAILED(hr))
        {
            ::FreeLibrary(hDIADll);
        }
    }
    return hr;
}

struct DiaModule
{
    HMODULE                     Handle;
    IDiaDataSource*             DataSource;
    IDiaSession*                Session;
    MODULEINFO                  Info;
    _bstr_t                     Name;
    _bstr_t                     FileName;

    DiaModule(HMODULE Handle) : Handle(Handle), DataSource(0), Session(0)
    {
        WCHAR   TmpFileName[FILENAME_MAX];
        WCHAR   ModFileName[FILENAME_MAX];
        WCHAR   PdbFileName[FILENAME_MAX];
        WCHAR * Name = 0;
        if (::GetModuleFileNameW(Handle, TmpFileName, FILENAME_MAX))
        {
            bool Result;

            ::GetModuleInformation((HANDLE)-1, Handle, &Info, sizeof(Info));

            ::GetFullPathNameW(TmpFileName, FILENAME_MAX, ModFileName, &Name);

            wsprintfW(PdbFileName, L"%s", ModFileName);
            wcscpy(wcsrchr((wchar_t *)PdbFileName, L'.'), L".pdb");

            this->Name = Name;
            this->FileName = ModFileName;

            Result = /*******/ (S_OK == CoCreateInstance(/**************/ __uuidof(DiaSource120), 0, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&DataSource));
            Result = Result || (S_OK == CoCreateInstance(L"msdia120.dll", __uuidof(DiaSource120_Alternative), /**********/ __uuidof(IDiaDataSource), (void**)&DataSource));
            Result = Result || (S_OK == CoCreateInstance(/**************/ __uuidof(DiaSource110), 0, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&DataSource));
            Result = Result || (S_OK == CoCreateInstance(/**************/ __uuidof(DiaSource100), 0, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&DataSource));
            Result = Result || (S_OK == CoCreateInstance(/**************/ __uuidof(DiaSource90_), 0, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&DataSource));
            Result = Result || (S_OK == CoCreateInstance(/**************/ __uuidof(DiaSource80_), 0, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&DataSource));
            Result = Result || (S_OK == CoCreateInstance(/**************/ __uuidof(DiaSource71_), 0, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void**)&DataSource));
            if (Result)
            {
                Result = Result && (S_OK == DataSource->loadDataForExe(ModFileName, L".;SRV*C:\\Temp\\symbols*http://msdl.microsoft.com/download/symbols", 0));
                Result = Result && (S_OK == DataSource->openSession(&Session));
                if (Result)
                {
                    Result = (S_OK == Session->put_loadAddress((ULONGLONG)Info.lpBaseOfDll));
                    if (!Result)
                    {
                        Session->Release();
                        Session = 0;
                    }
                }
                else
                {
                    DataSource->Release();
                    DataSource = 0;
                }
            }
        }
    }

    ~DiaModule()
    {
        if (Session) Session->Release();
        if (DataSource) DataSource->Release();
    }
};

namespace hal
{
    namespace dbg
    {
        struct Implementation : Interface
        {
            Implementation() : ModuleCount(0) { ::InitializeCriticalSection(&CriticalSection); }

            ~Implementation() { ::DeleteCriticalSection(&CriticalSection); }

            __forceinline void EnterCriticalSection() { ::EnterCriticalSection(&CriticalSection); }
            __forceinline void LeaveCriticalSection() { ::LeaveCriticalSection(&CriticalSection); }

            /* interface v 1.0 */

            virtual bool                         DllProcessAttach();
            virtual void                         DllProcessDetach();

            virtual bool                         Refresh();

            virtual void                         Walk(size_t * callstack, int skip);

            virtual void                         EnumCallstack(size_t * callstack, std::function< void(uintptr_t address, wchar_t * modulename, wchar_t * filename, int linenumber, wchar_t * symbolname, wchar_t * undecoratedname) > callback);
            virtual void                         EnumCallstack(size_t * callstack);

            virtual void                         DumpLastError(char const message[], DWORD error);

            virtual int                          DumpFilter(DumpType type, EXCEPTION_POINTERS * pep = nullptr);

            virtual LPTOP_LEVEL_EXCEPTION_FILTER EnforceFilter(bool enforce, LPTOP_LEVEL_EXCEPTION_FILTER filter = nullptr);

            DiaModule     * Module[256];
            size_t          ModuleCount;

            // Calls to functions belonging to DIA Interfaces are single threaded.
            // Therefore, calls from more than one thread will likely result in unexpected behavior or memory corruption.
            // To avoid this, we synchronize all concurrent calls.
            CRITICAL_SECTION CriticalSection;
        };
    }
}

static hal::dbg::Implementation * implementation = 0;

extern "C" __declspec(dllexport) hal::dbg::Interface * hal_dbg$GetInterface(long version)
{
    long version_major = (version >> 8) & 255;
    long version_minor = (version >> 0) & 255;

    if (version_major == hal::dbg::Implementation::version_major && version_minor <= hal::dbg::Implementation::version_minor)
    {
        return implementation;
    }

    return 0;
}

extern void ForceLinkWithStartupCleanup();

void hal::dbg::Startup()
{
    ForceLinkWithStartupCleanup();

    implementation = new Implementation;
}

void hal::dbg::Cleanup()
{
    delete implementation;
}

__noinline bool hal::dbg::Implementation::DllProcessAttach()
{
    if (FAILED(::CoInitialize(NULL)))
    {
        DWORD error = ::GetLastError();
        errorf(dbg, "CoInitialize returned error code : %d", error);

        return false;
    }

    ModuleCount = 0;

    for (size_t i = 0; i < 256; ++i)
    {
        Module[i] = 0;
    }

    return true;
}


__noinline void hal::dbg::Implementation::DllProcessDetach()
{
    for (size_t i = 0; i < ModuleCount; ++i)
    {
        if (Module[i])
        {
            delete Module[i];
            Module[i] = 0;
        }
    }

    ::CoUninitialize();
}

static int SortModuleByBaseAddress(void const * lhs, void const * rhs)
{
    intptr_t value = *((uintptr_t *)lhs) - *((uintptr_t *)rhs);
    return value ? (value < 0 ? -1 : 1) : 0;
}

__noinline bool hal::dbg::Implementation::Refresh()
{
    EnterCriticalSection();

    for (size_t i = 0; i < ModuleCount; ++i)
    {
        if (Module[i])
        {
            delete Module[i];
            Module[i] = 0;
        }
    }
    ModuleCount = 0;

    bool    Result = false;
    HANDLE  ProcessHandle = ::GetCurrentProcess();
    DWORD   Bytes = 0;
    HMODULE ModuleHandle[256];

    // get a snapshot of loaded first 256 modules
    ::EnumProcessModules(ProcessHandle, ModuleHandle, sizeof(ModuleHandle), &Bytes);

    ModuleCount = Bytes / sizeof(HMODULE);

    // sort them by increasing base address
    ::qsort(ModuleHandle, ModuleCount, sizeof(HMODULE), SortModuleByBaseAddress);

    for (size_t i = 0; i < ModuleCount; ++i)
    {
        Module[i] = new DiaModule(ModuleHandle[i]);

        tracef(dbg, "Module 0x%016I64X-0x%016I64X : %s",
               (uintptr_t)Module[i]->Info.lpBaseOfDll,
               (uintptr_t)Module[i]->Info.lpBaseOfDll + (uintptr_t)Module[i]->Info.SizeOfImage,
               (char const *)Module[i]->Name);

    }

    LeaveCriticalSection();

    return Result;
}

__noinline void hal::dbg::Implementation::Walk(size_t * callstack, int skip)
{
    int i = ::RtlCaptureStackBackTrace(skip, 63 - skip, (PVOID*)callstack, 0);
    callstack[i] = 0;
}

static int SearchModuleByAddress(void const * lhs, void const * rhs)
{
    DiaModule * m = *((DiaModule **)rhs);
    uintptr_t   x = *((uintptr_t *)lhs);
    uintptr_t   y = (uintptr_t)m->Info.lpBaseOfDll;
    intptr_t    s = (uintptr_t)m->Info.SizeOfImage;
    intptr_t cmp = x - y;
    if (cmp < 0)
    {
        return -1;
    }
    else if (cmp >= s)
    {
        return +1;
    }
    return 0;
}

__noinline void hal::dbg::Implementation::EnumCallstack(size_t * callstack, std::function< void(uintptr_t, wchar_t *, wchar_t *, int, wchar_t *, wchar_t *) > callback)
{
    if (callstack)
    {
        EnterCriticalSection();

        for (DWORD64 address; address = *callstack; ++callstack)
        {
            // a binary search in the sorted module list to check which module this return address belongs to
            DiaModule ** found = (DiaModule **)::bsearch(callstack, Module, ModuleCount, sizeof(DiaModule *), SearchModuleByAddress);
            if (found)
            {
                DiaModule   * Module = *found;
                IDiaSession * Session = Module->Session;

                if (0 != Session)
                {
                    IDiaSymbol*          Symbol = 0;
                    IDiaEnumLineNumbers* Lines = 0;
                    IDiaLineNumber*      Line = 0;
                    IDiaSourceFile*      SourceFile = 0;
                    _bstr_t              FileName = L"???";
                    _bstr_t              SymbolName = L"???";
                    _bstr_t              UndecoratedName = L"???";
                    DWORD                LineNumber = (DWORD)-1;

                    bool valid = (S_OK == Session->findSymbolByVA(address, SymTagFunction, &Symbol));

                    if (!valid) valid = (S_OK == Session->findSymbolByVA(address, SymTagPublicSymbol, &Symbol));

                    if (valid)
                    {
                        BSTR Name;
                        if (S_OK == Symbol->get_name(&Name))
                        {
                            SymbolName = Name;
                        }
                        if (S_OK == Symbol->get_undecoratedNameEx(0x98, &Name))
                        {
                            UndecoratedName = Name;
                        }
                        else
                        {
                            UndecoratedName = SymbolName;
                        }

                        if (S_OK == Session->findLinesByVA(address, 1, &Lines))
                        {
                            if (S_OK == Lines->Item(0, &Line))
                            {
                                Line->get_lineNumber(&LineNumber);

                                if (S_OK == Line->get_sourceFile(&SourceFile))
                                {
                                    if (S_OK == SourceFile->get_fileName(&Name))
                                    {
                                        FileName = _bstr_t(wcsrchr((wchar_t *)Name, L'\\') + 1);
                                    }

                                    SourceFile->Release();
                                }
                                Line->Release();
                            }
                            Lines->Release();
                        }
                    }

                    callback((uintptr_t)address, Module->Name, FileName, (int)LineNumber, SymbolName, UndecoratedName);

                    Symbol->Release();

                    continue;
                }
            }

            callback((uintptr_t)address, L"???", L"???", (int)-1, L"???", L"");
        }

        LeaveCriticalSection();
    }
}

__noinline void hal::dbg::Implementation::EnumCallstack(size_t * callstack)
{
    auto errorf_hal = [] (uintptr_t /*address*/, wchar_t * modulename, wchar_t * filename, int linenumber, wchar_t * symbolname, wchar_t * undecoratedname)
    {
        wchar_t fullname[1024];
        wsprintfW(fullname, L"%32s!%-40s", modulename, filename);
        errorf(dbg, " |%-72ws(%5d) %ws", fullname, linenumber, (*undecoratedname) ? undecoratedname : symbolname);
    };
    errorf(dbg, " /--- Call Stack");
    EnumCallstack(callstack, errorf_hal);
    errorf(dbg, " \\---");
}

__noinline void hal::dbg::Implementation::DumpLastError(char const message[], DWORD error)
{
    if (error)
    {
        PVOID MessageBuffer = 0;
        if (error) ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPSTR)&MessageBuffer, 0, NULL);
        errorf(dbg, "%s returned error code: %d", message, error);
        if (MessageBuffer)
        {
            for (char * p = (char *)MessageBuffer, *q = p; *p; p = q)
            {
                while (*q && (*q != '\n' && *q != '\r')) ++q;
                while (*q && (*q == '\n' || *q == '\r')) *q++ = '\0';
                errorf(dbg, "    %s", p);
            }
        }
        hal::dbg::Callstack callstack;
        Walk(callstack, 2);
        EnumCallstack(callstack);
        if (MessageBuffer)
        {
            ::LocalFree(MessageBuffer);
        }
    }
    else
    {
        errorf(dbg, " %s", message);
        hal::dbg::Callstack callstack;
        Walk(callstack, 2);
        EnumCallstack(callstack);
    }
}

static BOOL CALLBACK DumpCallback(PVOID pParam, PMINIDUMP_CALLBACK_INPUT const pInput, PMINIDUMP_CALLBACK_OUTPUT pOutput)
{
    auto type = hal::dbg::Interface::DumpType(intptr_t(pParam));
    BOOL bRet = FALSE;

    if (pInput == 0 || pOutput == 0)
    {
        return FALSE;
    }

    switch (pInput->CallbackType)
    {
        case IncludeModuleCallback:
        {
            bRet = type != hal::dbg::Interface::TinyDump;
            break;
        }

        case IncludeThreadCallback:
        {
            bRet = type != hal::dbg::Interface::TinyDump;
            break;
        }

        case ModuleCallback:
        {
            if (hal::dbg::Interface::MiniDump == type)
            {
                if (!(pOutput->ModuleWriteFlags & ModuleReferencedByMemory))
                {
                    pOutput->ModuleWriteFlags &= (~ModuleWriteModule);
                }
            }

            bRet = TRUE;
            break;
        }

        case ThreadCallback:
        {
            bRet = TRUE;
            break;
        }

        case ThreadExCallback:
        {
            bRet = TRUE;
            break;
        }

        case MemoryCallback:
        {
            // We do not include any information here -> return FALSE
            bRet = FALSE;
            break;
        }

        case CancelCallback:
        {
            break;
        }
    }

    return bRet;
}

int hal::dbg::Implementation::DumpFilter(DumpType type, EXCEPTION_POINTERS * pep)
{
    if (pep)
    {
        forcef(dbg, "Dumping from an exception...");
    }
    else
    {
        forcef(dbg, "Dumping all...");
    }

    HANDLE hFile = ::CreateFileW(L"pspe4all.dmp", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
    {
        MINIDUMP_EXCEPTION_INFORMATION mdei;
        MINIDUMP_CALLBACK_INFORMATION  mci;
        MINIDUMP_TYPE                  mdt = MiniDumpNormal;

        mdei.ThreadId          = ::GetCurrentThreadId();
        mdei.ExceptionPointers = pep;
        mdei.ClientPointers    = FALSE;

        mci.CallbackRoutine    = (MINIDUMP_CALLBACK_ROUTINE)DumpCallback;
        mci.CallbackParam      = (PVOID)type;

        switch (type)
        {
            case TinyDump:
            {
                break;
            }
            case MiniDump:
            {
                mdt = (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory |
                                      MiniDumpScanMemory);
                break;
            }
            case MidiDump:
            {
                mdt = (MINIDUMP_TYPE)(MiniDumpWithPrivateReadWriteMemory |
                                      MiniDumpWithDataSegs |
                                      MiniDumpWithHandleData |
                                      MiniDumpWithFullMemoryInfo |
                                      MiniDumpWithThreadInfo |
                                      MiniDumpWithUnloadedModules);

                break;
            }
            default:
            case MaxiDump:
            {
                mdt = (MINIDUMP_TYPE)(MiniDumpWithFullMemory |
                                      MiniDumpWithFullMemoryInfo |
                                      MiniDumpWithHandleData |
                                      MiniDumpWithThreadInfo |
                                      MiniDumpWithUnloadedModules);
                break;
            }
        }

        BOOL rv = ::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, mdt, (pep != 0) ? &mdei : nullptr, nullptr, MaxiDump == type ? nullptr : &mci);

        if (!rv)
        {
            DumpLastError("Dumping failed", ::GetLastError());
        }
        else
        {
            forcef(dbg, "Dumping is successful");
        }

        ::CloseHandle(hFile);
    }
    else
    {
        DumpLastError("Creating dump file failed", ::GetLastError());
    }

    return pep ? EXCEPTION_CONTINUE_SEARCH : EXCEPTION_EXECUTE_HANDLER;
}

static const BYTE                   PatchBytes   [3] = { 0x33, 0xC0, 0xC3 }; // xor eax, eax; retn
static       BYTE                   OriginalBytes[3] = { 0 };

LPTOP_LEVEL_EXCEPTION_FILTER hal::dbg::Implementation::EnforceFilter(bool enforce, LPTOP_LEVEL_EXCEPTION_FILTER filter)
{
    LPTOP_LEVEL_EXCEPTION_FILTER OldFilter = nullptr;

    if (enforce && filter)
    {
        OldFilter = ::SetUnhandledExceptionFilter(filter);
    }

    HMODULE hLib = ::GetModuleHandleW(L"kernel32.dll");

    if (nullptr == hLib)
    {
        ::SetUnhandledExceptionFilter(OldFilter);
        return 0;
    }

    BYTE * pTarget = (BYTE *)::GetProcAddress(hLib, "SetUnhandledExceptionFilter");

    if (nullptr == pTarget)
    {
        ::SetUnhandledExceptionFilter(OldFilter);
        return 0;
    }

    if (enforce)
    {
        memcpy(OriginalBytes, pTarget, sizeof(OriginalBytes));
    }

    DWORD        OldProtect = 0;
    SIZE_T       Size = enforce ? sizeof(PatchBytes) : sizeof(OriginalBytes);
    BYTE const * pSource = enforce ? PatchBytes : OriginalBytes;

    if (!::VirtualProtect(pTarget, Size, PAGE_EXECUTE_READWRITE, &OldProtect))
    {
        ::SetUnhandledExceptionFilter(OldFilter);
        return 0;
    }

    memcpy(pTarget, pSource, Size);

    DWORD Temp = 0;

    if (!::VirtualProtect(pTarget, Size, OldProtect, &Temp))
    {
        ::SetUnhandledExceptionFilter(OldFilter);
        return 0;
    }

    if (!enforce && filter)
    {
        ::SetUnhandledExceptionFilter(filter);
    }

    return OldFilter;
}
