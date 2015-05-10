/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "emu.h"

namespace hal
{
    namespace video
    {
#if defined(EMU_EXPORTS)
        void   Startup();
        void   Cleanup();
#endif

        struct Interface : emu::Interface
        {
            /**/     Interface() { }
            virtual ~Interface() { }

            /* interface v 1.0 */

            u32 address;
            u32 stride;
            u32 width;
            u32 height;
            u32 format;

            virtual bool CreateDisplay(HDC hDC)               = 0;
            virtual bool ReleaseDisplay()                     = 0;
            virtual bool PrepareDisplay()                     = 0;
            virtual void ResizeDisplay(int width, int height) = 0;
            virtual bool UpdateDisplay()                      = 0;
            virtual bool RenderDisplay()                      = 0;
            virtual bool PresentDisplay()                     = 0;
            virtual void ToggleVsync()                        = 0;
        };
    }
}

#if defined(PSPE4ALLHALVIDEOOGL4_EXPORTS)
extern "C" __declspec(dllexport) hal::video::Interface * hal_video$GetInterface(long version);
#else
extern "C"                       hal::video::Interface * hal_video$GetInterface(long version);
#endif
