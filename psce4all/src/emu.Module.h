/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "hal.os.Module.h"

namespace emu
{
    struct Module
    {
        static hal::os::Module & GetCurrentModule();
        static hal::os::Module & GetEmulatorModule();
        static bool              IsEmulatorModule();

        template< typename F > static F * GetFunction(char const * name)
        {
            return GetEmulatorModule().GetFunction< F >(name);
        }
    };
}
