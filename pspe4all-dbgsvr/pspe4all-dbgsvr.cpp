/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

//extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }

#include "pspe4all-dbgsvr.h"

#pragma comment(linker, "/ENTRY:wmainCRTStartup")
int wmain(int argc, wchar_t * argv[])
{
    Debugger Debugger;

    if (argc == 2)
    {
        DWORD ProcessId = _wtol(argv[1]);
        if (!Debugger.AttachToProcess(ProcessId))
        {
            return 0;
        }
    }

    Debugger.DebugLoop();

    return 0;
}
