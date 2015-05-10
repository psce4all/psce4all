/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

//#include "emu.settings.h"
#include "hal.display.h"
#include "hal.dbg.h"

namespace hal
{
    namespace display
    {
        struct Implementation : hal::display::Interface
        {
            Implementation()
            {
            }

            virtual bool DllProcessAttach() { return false; }
            virtual void DllProcessDetach() {}

            virtual void StartUp() {}
            virtual void CleanUp() {}

            virtual bool CreateDisplay(HDC hDC)               { return false; }
            virtual bool ReleaseDisplay()                     { return false; }
            virtual bool PrepareDisplay()                     { return false; }
            virtual void ResizeDisplay(int width, int height) {}
            virtual bool UpdateDisplay()                      { return false; }
            virtual bool RenderDisplay()                      { return false; }
            virtual bool PresentDisplay()                     { return false; }
            virtual void ToggleVsync()                        {}
        };
    }
}

typedef hal::display::Interface * (Function)(long version);

static Function * hal_display_GetInterface = 0;

static hal::display::Implementation * implementation = 0;

extern "C" __noinline hal::display::Interface * hal_display$GetInterface(long version)
{
    if (hal_display_GetInterface == 0)
    {
        char const * dllfilename = __ConfigurationDllStringA("psce4all-display.OGL4");
        HINSTANCE    hDLL        = ::LoadLibraryA(dllfilename);
        if (hDLL)
        {
            hal_display_GetInterface = (Function *)::GetProcAddress(hDLL, "hal_display$GetInterface");
        }
        else
        {
            return 0;
        }
    }

    return hal_display_GetInterface(version);
}

extern void ForceLinkWithStartupCleanup();

void hal::display::Startup()
{
    ForceLinkWithStartupCleanup();

    implementation = new Implementation;
}

void hal::display::Cleanup()
{
    delete implementation;
}

