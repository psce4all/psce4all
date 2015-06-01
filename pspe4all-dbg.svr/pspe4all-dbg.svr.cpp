/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

//extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }

#include "pspe4all-dbg.svr.h"

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "dbghelp.lib")
#pragma comment(linker, "/ENTRY:wmainCRTStartup")

using DebugServer = dbg::svr::Debugger;

int wmain(int argc, wchar_t * argv[])
{
    DebugServer Debugger;

    if (argc == 2)
    {
        DWORD ProcessId = _wtol(argv[1]);

        if (lle::mmu::Attach(ProcessId))
        {
            if (Debugger.AttachToProcess(ProcessId))
            {
                Debugger.DebugLoop(INFINITE);
            }

            lle::mmu::Detach();
        }
    }

    return 0;
}
