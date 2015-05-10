/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "emu.settings.h"
#include "hal.video.h"
#include "hal.dbg.h"

namespace hal
{
    namespace video
    {
        struct Implementation : hal::video::Interface
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

typedef hal::video::Interface * (Function)(long version);

static Function * hal_video_GetInterface = 0;

static hal::video::Implementation * implementation = 0;

extern "C" __noinline hal::video::Interface * hal_video$GetInterface(long version)
{
    if (hal_video_GetInterface == 0)
    {
        char const * dllfilename = __ConfigurationDllStringA("pspe4all-hal.video.OGL4")/*(theSettings->gerenderer + string(".dll")).c_str()*/;
        HINSTANCE    hDLL        = ::LoadLibraryA(dllfilename);
        if (hDLL)
        {
            hal_video_GetInterface = (Function *)::GetProcAddress(hDLL, "hal_video$GetInterface");
        }
        else
        {
            return 0;
        }
    }

    return hal_video_GetInterface(version);
}

extern void ForceLinkWithStartupCleanup();

void hal::video::Startup()
{
    ForceLinkWithStartupCleanup();

    implementation = new Implementation;
}

void hal::video::Cleanup()
{
    delete implementation;
}

