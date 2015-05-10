/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "emu.log.h"

namespace emu
{
    namespace log
    {
        extern SubCategory sys;
    }
}

#include "hal.Atomic.h"
#include "hal.os.Clock.h"

//#include "emu_EmulatorEvent.h"

namespace lle
{
    namespace sys
    {
        class Clock : public hal::os::Clock/*, public EmulatorEvent*/
        {
        public:
            /**/                Clock();
            /**/               ~Clock();

            void                Set(u64 target_time);
            u64                 Get() const;
            virtual bool        Handle() = 0;

            void                Step();

        protected:
            u64                 m_current_time; // 0xBC60000 - current clock value (µs)
            u64                 m_compare_time; // 0xBC60004 - compare clock value (µs)
        };
    }
}
