/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "hal.os.win32.h"

namespace hal
{
    namespace os
    {
        class Clock
        {
        public:
            /**/            Clock();
            /**/           ~Clock();

            f64             Get() const;
            static f64      GetMaximalResolution();

            static u64      GetTimeStamp();
            static s64      GetElpasedTimeStamp(u64 & tsc);
            static s64      GetElpasedTimeStampPerMicrosecond();

        private:
            /**/            Clock(int);

            void            ReadCounters(s64 & tsc, s64 & pc);

            s64             m_old_count;

            static ULONG    m_max_resolution;
            static ULONG    m_old_resolution;
            static f64      m_qpc_resolution;
            static f64      m_qpc_frequency;
            static f64      m_qpc_factor;
            static s64      m_tsc_frequency;
            static Clock    m_instance;
        };
    }
}
