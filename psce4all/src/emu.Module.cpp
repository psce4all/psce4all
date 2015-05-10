/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include <Psapi.h>
#pragma comment(lib, "psapi")

#include "emu.Module.h"

hal::os::Module & emu::Module::GetCurrentModule()
{
    static hal::os::Module module(&emu::Module::GetCurrentModule);
    return module;
}

hal::os::Module & emu::Module::GetEmulatorModule()
{
    static hal::os::Module module("emu$GetInterface", false);
    return module;
}

bool emu::Module::IsEmulatorModule()
{
    return GetCurrentModule() == GetEmulatorModule();
}
