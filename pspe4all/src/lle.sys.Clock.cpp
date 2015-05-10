/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "lle.sys.Clock.h"

lle::sys::Clock::Clock()
{
}

lle::sys::Clock::~Clock()
{
}

void lle::sys::Clock::Set(u64 target_time)
{
    m_compare_time = target_time;
}

u64 lle::sys::Clock::Get() const
{
    return u64(hal::os::Clock::Get()*1000000.);
}

void lle::sys::Clock::Step()
{
    m_current_time = lle::sys::Clock::Get();
    if (m_current_time <= m_compare_time)
    {
        //theEmulator->EnqueueEvent(theSysClock);
    }
}