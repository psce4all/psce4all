/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifndef hle_kd_ThreadMan_h__
#error you must include "hle.kd.ThreadMan.h" instead
#endif

#include "lle.sys.Clock.h"

namespace hle
{
    namespace kd
    {
        struct Timer;

        /// KernelTimerList /////////////////////////////////////////////////////////

        struct TimerList : hal::LinkedList< Timer >
        {
            void        AddTimerToList(Timer * timer);
            void        RemoveTimerFromList(Timer * timer);

            bool        DispatchTimers();
            void        RescheduleTimers();

            static void Initialize();
            static void Terminate()
            {
            }
        };


        /// KernelTimer /////////////////////////////////////////////////////////////

        struct Timer : Object, TimerList::Node
        {
            declare_kernel_type(Timer, Object);

            /**/              Timer(char const * name);
            /**/             ~Timer();

            static Timer *    Create(u64 timeout);
            int               Delete(int intr);

            u64               m_time;
            int               m_unk_10;
        };

        /// KernelDelay /////////////////////////////////////////////////////////////

        struct Delay : Timer
        {
            declare_kernel_type(Delay, Timer);

            /**/              Delay();
            /**/             ~Delay();

            static Delay *    Create(u64 timeout, int * result, Thread * delayed_thread);
            int               Delete(int intr);

            void              Cancel();

            Thread          * m_thread;
        };

        /// KernelDelayList /////////////////////////////////////////////////////////

        struct DelayList : protected TimerList
        {
            /**/              DelayList();
            /**/             ~DelayList();

            void              Release(Delay * delay);
            Delay           * Acquire();
        };

        /// KernelSysClock //////////////////////////////////////////////////////////

        class SysClock : public lle::sys::Clock
        {
        public:
            /**/              SysClock();
            /**/             ~SysClock();

            bool              Handle();
        };
    }

    typedef kd::Timer     KernelTimer;
    typedef kd::TimerList KernelTimerList;
    typedef kd::Delay     KernelDelay;
    typedef kd::DelayList KernelDelayList;
    typedef kd::SysClock  KernelSysClock;
}

extern hle::kd::SysClock * theSysClock;
