/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"
//#include "hle_Syscalls.h"

namespace emu
{
    namespace log
    {
        SubCategory kd(hle, "kd", "Kernel modules");
    }
}

#if 0
char const * KernelModule::m_object_type          = "KernelModule";
char const * KernelIoAsync::m_object_type         = "KernelIoAsync";
#endif

namespace hle
{

    namespace kd
    {
        static bool ready = false;

        bool Reboot()
        {
            ShutDown();

            //syscalls::Reboot();

            ready = true;
            return true;
        }

        bool ShutDown()
        {
            if (ready)
            {
                //syscalls::ShutDown();
                //al_Context::CountInstructions();
                int count = Objects.CountAll();
                if (count)
                {
                    Objects.Dump();
                    tracef(kd, "Shutting down kernel - %i kernel objects alive", count);
                    //theKernelObjects.ClearAll();
                }

                ready = false;
            }
            return true;
        }
    }
}
