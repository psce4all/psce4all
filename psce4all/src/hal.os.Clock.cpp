/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hal.os.Clock.h"
#include "hal.os.Thread.h"

ULONG          hal::os::Clock::m_old_resolution;
ULONG          hal::os::Clock::m_max_resolution;
f64            hal::os::Clock::m_qpc_resolution;
f64            hal::os::Clock::m_qpc_factor;
f64            hal::os::Clock::m_qpc_frequency;
s64            hal::os::Clock::m_tsc_frequency;
hal::os::Clock hal::os::Clock::m_instance(0);

hal::os::Clock::Clock()
{
}

hal::os::Clock::Clock(int)
{
    ULONG     dummy;
    s64       pca, pcb, pcf, tsca, tscb;
    f64       interval;
    int const times = 16;
    int const retries = 5;

    ::NtQueryTimerResolution(&dummy, &m_max_resolution, &m_old_resolution);
    ::NtSetTimerResolution(m_max_resolution, TRUE, &dummy);
    ::NtQueryPerformanceCounter((PLARGE_INTEGER)&pca, (PLARGE_INTEGER)&pcf);

    m_qpc_frequency  = f64(pcf);
    m_qpc_factor     = 1000000.0 / m_qpc_frequency;
    m_qpc_resolution = f64(m_max_resolution) / 10.0;

    m_tsc_frequency = 0;
    f64 frequency = 0.0;

    __ThreadPriority(THREAD_PRIORITY_TIME_CRITICAL)
    {
        for (int j = 0; j < times; ++j)
        {
            for (int i = 0; i < retries; ++i)
            {
                ReadCounters(tsca, pca);

                do
                {
                    ReadCounters(tscb, pcb);
                    interval = f64(pcb - pca) * m_qpc_factor;
                }
                while (interval < 1000.0);

                if (interval < 1001.0)
                {
                    frequency += f64(tscb - tsca) / interval;
                    break;
                }
            }
        }
    }

    m_tsc_frequency = s64(frequency / f64(times));
}

hal::os::Clock::~Clock()
{
    if (this == &m_instance)
    {
        ULONG dummy;

        ::NtSetTimerResolution(m_old_resolution, FALSE, &dummy);
    }
}

f64 hal::os::Clock::Get() const
{
    s64 c;

    ::NtQueryPerformanceCounter((PLARGE_INTEGER)&c, 0);

    return f64(c) * m_qpc_factor;
}

f64 hal::os::Clock::GetMaximalResolution()
{
    return m_qpc_resolution;
}

u64 hal::os::Clock::GetTimeStamp()
{
    return __rdtsc();
}

s64 hal::os::Clock::GetElpasedTimeStamp(u64 & tsc)
{
    s64 old = tsc;
    tsc     = __rdtsc();
    return tsc - old;
}

s64 hal::os::Clock::GetElpasedTimeStampPerMicrosecond()
{
    return m_tsc_frequency;
}

void hal::os::Clock::ReadCounters(s64 & tsc, s64 & pc)
{
    u64           rdtsc_a, rdtsc_b;
    LARGE_INTEGER pca;
    int           count = 0;
again:
    rdtsc_a = __rdtsc();
    ::NtQueryPerformanceCounter(&pca, 0);
    rdtsc_b = __rdtsc();
    if (rdtsc_b - rdtsc_a > 100000 && count++ < 5 ) goto again;
    tsc = s64((rdtsc_a + rdtsc_b)/2ULL);
    pc  = s64(pca.QuadPart);
}

