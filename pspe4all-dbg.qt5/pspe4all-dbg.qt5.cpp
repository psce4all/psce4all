/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "dbghelp.lib")
#pragma comment(linker, "/ENTRY:mainCRTStartup")

#include "pspe4all-dbg.qt5.Debugger.h"

//int wmain(int argc, wchar_t * argv[])
int main(int argc, char *argv[])
{
    dbg::qt5::Debugger Debugger(argc, argv);

    int result = -1;

    if (argc == 2)
    {
        DWORD pid = atol(argv[1]);

        if (lle::mmu::Attach(pid))
        {
            result = Debugger.exec(pid);

            lle::mmu::Detach();
        }
    }

    return result;
}
