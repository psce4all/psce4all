/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include <Psapi.h>
#pragma comment(lib, "psapi")

#include "hal.os.Module.h"

HMODULE hal::os::Module::GetCurrentModule(void * FunctionAddress)
{
    HMODULE module = 0;
    ::GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT|GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)FunctionAddress, &module);
    return module;
}

HMODULE hal::os::Module::GetFirstModule(char const FunctionName[])
{
    HMODULE ModuleArray[256];
    DWORD   n;

    if (::EnumProcessModules(::GetCurrentProcess(), ModuleArray, sizeof(ModuleArray), &n))
    {
        for (DWORD i = 0; i < n; ++i)
        {
            FARPROC pFunction = ::GetProcAddress(ModuleArray[i], FunctionName);

            if (pFunction)
            {
                return ModuleArray[i];
            }
        }
    }

    return 0;
}
