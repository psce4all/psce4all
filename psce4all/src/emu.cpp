/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "advapi32.lib")

#define SECURITY_WIN32
#include <Userenv.h>
#include <Security.h>

#include "emu.h"
#include "emu.log.h"
#include "hal.dbg.h"
#include "hal.npa.h"
#include "hal.hmm.h"
#include "lle.mmu.h"
#include "hal.video.h"

namespace emu
{
    namespace sysinfo
    {
        OSVERSIONINFOEXW vi;
        SYSTEM_INFO      si[2];
        bool             windows_wow64 = false;
        wchar_t        * windows_name;
        wchar_t        * windows_arch;
        long             windows_bits;
        wchar_t        * username = 0;
        wchar_t        * homepath = 0;
        wchar_t        * workpath = 0;
        wchar_t        * temppath = 0;

        bool Dump();
    };

    struct Implementation : Interface
    {
        using Interface::GetVersion;

        static long GetVersion(Interface *)
        {
            return Interface::version;
        }

        Implementation()
        {
            using namespace sysinfo;

            this->Interface::GetVersion_ = &Implementation::GetVersion;

            HANDLE hprocess = ::GetCurrentProcess();

            vi.dwOSVersionInfoSize = sizeof(vi);
            ::GetVersionExW((OSVERSIONINFOW *)&vi);

            switch (vi.dwMajorVersion)
            {
            case 6:
                switch (vi.dwMinorVersion)
                {
                case 0: if (vi.wProductType == VER_NT_WORKSTATION) windows_name = L"Windows Vista"; else windows_name = L"Windows Server 2008";    break;
                case 1: if (vi.wProductType == VER_NT_WORKSTATION) windows_name = L"Windows 7";     else windows_name = L"Windows Server 2008 R2"; break;
                case 2: if (vi.wProductType == VER_NT_WORKSTATION) windows_name = L"Windows 8";     else windows_name = L"Windows Server 2012";    break;
                case 3: if (vi.wProductType == VER_NT_WORKSTATION) windows_name = L"Windows 8.1";   else windows_name = L"Windows Server 2012 R2"; break;
                default:                                           windows_name = L"Windows ???";                                                  break;
                }
                break;
            default:                                               windows_name = L"Windows ???";                                                  break;
            }

            ::GetNativeSystemInfo(si + 0);

            switch (si[0].wProcessorArchitecture)
            {
            case PROCESSOR_ARCHITECTURE_AMD64:  windows_arch = L"x64"; windows_bits = 64; break;                                                                                              break;
            case PROCESSOR_ARCHITECTURE_INTEL:  windows_arch = L"x86"; windows_bits = 32; break;                                                                                              break;
            default:                            windows_arch = L"???"; windows_bits = 0;  break;                                                                                              break;
            }

            ::GetSystemInfo(si + 1);

            BOOL bIsWow64 = FALSE;

            ::IsWow64Process(hprocess, &bIsWow64);

            windows_wow64 = TRUE == bIsWow64;

            HANDLE token = 0;
            BOOL ok = ::OpenProcessToken(hprocess, TOKEN_QUERY, &token);
            if (ok)
            {
                DWORD dwBufferSize = 0;
                wchar_t * path;

                // Retrieve User Name
                ::GetUserNameExW(NameSamCompatible, NULL, &dwBufferSize);
                if (dwBufferSize != 0)
                {
                    path = new wchar_t[dwBufferSize];
                    if (::GetUserNameExW(NameSamCompatible, path, &dwBufferSize))
                    {
                        username = path;
                    }
                    else
                    {
                        delete [] path;
                    }
                }

                dwBufferSize = 0;

                // Retrieve Home Directory
                ok = ::GetUserProfileDirectoryW(token, NULL, &dwBufferSize);
                if (!ok && dwBufferSize != 0)
                {
                    path = new wchar_t[dwBufferSize];
                    ok = ::GetUserProfileDirectoryW(token, path, &dwBufferSize);
                    if (ok)
                    {
                        homepath = path;
                    }
                    else
                    {
                        delete [] path;
                    }
                }

                // Retrieve Working Directory
                dwBufferSize = ::GetCurrentDirectoryW(0, NULL);
                if (dwBufferSize != 0)
                {
                    path = new wchar_t[dwBufferSize];
                    if (0 != ::GetCurrentDirectoryW(dwBufferSize, path))
                    {
                        workpath = path;
                    }
                    else
                    {
                        delete [] path;
                    }
                }

                // Retrieve Temp Directory
                dwBufferSize = ::GetTempPathW(0, NULL);
                if (dwBufferSize != 0)
                {
                    path = new wchar_t[dwBufferSize];
                    if (0 != ::GetTempPathW(dwBufferSize, path))
                    {
                        temppath = path;
                    }
                    else
                    {
                        delete [] path;
                    }
                }

                ::CloseHandle(token);
            }
        }

        ~Implementation()
        {
            using namespace sysinfo;

            delete [] username;
            delete [] homepath;
            delete [] workpath;
            delete [] temppath;
        }

        bool DllProcessAttach()
        {
            long version = Implementation::version;

            forcef(emu, A_EMULATOR_NAME "-emu(version=%d.%02d)", (version>>8)&255, version&255);

            emu::sysinfo::Dump();

            bool result =
                emu_log$GetInterface(version)->DllProcessAttach() &&
                hal_dbg$GetInterface(version)->DllProcessAttach() &&
                hal_npa$GetInterface(version)->DllProcessAttach() &&
                hal_hmm$GetInterface(version)->DllProcessAttach() &&
                lle_mmu$GetInterface(version)->DllProcessAttach();

            return result ? TRUE : FALSE;
        }

        void DllProcessDetach()
        {
            infof(emu, "Perform any necessary cleanup...");

            lle_mmu$GetInterface(version)->DllProcessDetach();
            hal_hmm$GetInterface(version)->DllProcessDetach();
            hal_dbg$GetInterface(version)->DllProcessDetach();
            hal_npa$GetInterface(version)->DllProcessDetach();
            emu_log$GetInterface(version)->DllProcessDetach();

            infof(emu, "Cleanup done");
        }
    };

    Implementation implementation;

    namespace sysinfo
    {
        wchar_t const * WindowsName()
        {
            return windows_name;
        }

        wchar_t const * WindowsArch()
        {
            return windows_arch;
        }

        long WindowsBits()
        {
            return windows_bits;
        }

        bool IsWow64()
        {
            return windows_wow64;
        }

        wchar_t const * UserName()
        {
            return username;
        }

        wchar_t const * HomePath()
        {
            return homepath;
        }

        wchar_t const * WorkPath()
        {
            return workpath;
        }

        wchar_t const * TempPath()
        {
            return temppath;
        }

        bool Dump()
        {
            if (vi.dwMajorVersion < 6)
            {
                errorf(emu, L"Windows ver. %u.%u.%u not supported", vi.dwMajorVersion, vi.dwMinorVersion, vi.dwBuildNumber);
                return false;
            }

            infof(emu, L"%s %d-bit (%s) ver. %u.%u.%u", WindowsName(), WindowsBits(), WindowsArch(), vi.dwMajorVersion, vi.dwMinorVersion, vi.dwBuildNumber);
            infof(emu, L"Service Pack: %u.%u", vi.wServicePackMajor, vi.wServicePackMinor);
            infof(emu, L"The process %s running under WOW64", IsWow64() ? L"is" : L"is not");
            infof(emu, L"User Name: %s", UserName());
            infof(emu, L"Home Path: %s", HomePath());
            infof(emu, L"Work Path: %s", WorkPath());
            infof(emu, L"Temp Path: %s", TempPath());

            return true;
        }
    }
}

void emu::Interface::Reschedule()
{
    //theKernelScheduler->SwitchToNextThread();
}


void emu::Interface::ExecutePendingEvents()
{
    bool reschedule = false;

#if 0
    EmulatorEvent * event;

    while (m_event_queue.Dequeue(event))
    {
        reschedule |= event->Handle();
    }
#endif

    if (reschedule)
    {
        //theKernelScheduler->m_elected_thread = 0;

        Reschedule();
    }
}

extern "C" __declspec(dllexport) emu::Interface * emu$GetInterface(long version)
{
    if (version <= emu::implementation.GetVersion())
    {
        return &emu::implementation;
    }
    return 0;
}

extern "C" __declspec(dllexport) long GetImplementationVersion()
{
    return emu::Implementation::version;
}
