/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_mainwindow.h"

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "dbghelp.lib")
#pragma comment(linker, "/ENTRY:mainCRTStartup")

using DebugServer = dbg::svr::Debugger;

//int wmain(int argc, wchar_t * argv[])
int main(int argc, char *argv[])
{
    QApplication::setStyle("fusion");

    QApplication a(argc, argv);

    //DebugServer Debugger;

    int result = -1;

    if (argc == 2)
    {
        DWORD ProcessId = atol(argv[1]);
        //if (!Debugger.AttachToProcess(ProcessId))
        //{
        //    return 0;
        //}

        if (lle::mmu::Attach(ProcessId))
        {
            {
                qt_MainWindow w;

                w.show();

                result = a.exec();

                //Debugger.DebugLoop();
            }

            lle::mmu::Detach();
        }
    }

    return result;
}
