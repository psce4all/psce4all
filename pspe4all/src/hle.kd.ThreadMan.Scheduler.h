/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifndef hle_kd_ThreadMan_h__
#error you must include "hle.kd.ThreadMan.h" instead
#endif

namespace hle
{
    namespace kd
    {
        /// KernelScheduler /////////////////////////////////////////////////////////

        struct Scheduler : hal::os::UmsScheduler, hal::hmm::Allocator< Scheduler >
        {
            using Thread      = hle::kd::Thread;
            using ThreadQueue = hle::kd::ThreadQueue;
            using TimerList   = hle::kd::TimerList;
            using DelayList   = hle::kd::DelayList;
            using IntrSoft2   = hle::kd::IntrSoft2;

            /**/                        Scheduler();
            /**/                       ~Scheduler();

            /////////////////////////////////////////////////////////////////////////////////
            Thread                    * m_current_thread;
            Thread                    * m_elected_thread;
            Thread                    * m_idle_thread;
            int                         m_priority_mask[128 / 32];
            ThreadQueue                 m_ready_threads[128];
            ThreadQueue                 m_sleeping_threads;
            ThreadQueue                 m_delayed_threads;
            ThreadQueue                 m_stopped_threads;
            ThreadQueue                 m_suspended_threads;
            ThreadQueue                 m_deletable_threads;


            Thread                    * GetCurrentThread()
            {
                return m_current_thread;
            }
            Thread                    * GetElectedThread()
            {
                return m_elected_thread;
            }
            Thread                    * GetIdleThread()
            {
                return m_idle_thread;
            }

            void                        SwitchToIdleThread()
            {
                if (m_idle_thread) m_idle_thread->SwitchToIdle();
            }
            void                        SwitchToNextThread()
            {
                if (m_current_thread) m_current_thread->SwitchToNext();
            }

            void                        ElectNextRunningThread();

            void                        AddThreadToReadyQueue(Thread *);
            void                        RemoveThreadFromReadyQueue(Thread *);
            int                         RotateThreadReadyQueue(int priority, int intr, int is_intr_context);

            void                        AddThreadToDormantQueue(Thread *);
            void                        AddThreadToCleanupQueue(Thread *);

            void                        AddThreadToDelayList(Thread *);
            void                        RemoveThreadFromDelayList(Thread *);

            /////////////////////////////////////////////////////////////////////////////////
            int                         m_dispatch_thread_suspended; //418

            int                         SuspendDispatchThread(int intr);
            int                         ResumeDispatchThread(int old, int intr);

            /////////////////////////////////////////////////////////////////////////////////
            SceKernelSysClock           m_unk_428;
            SceKernelSysClock           m_unk_430; //system time
            SceKernelSysClock           m_unk_438;

            /////////////////////////////////////////////////////////////////////////////////
            int                         m_timer_id; //440

            /////////////////////////////////////////////////////////////////////////////////
            int                         m_do_cleanup; //5cc


            /////////////////////////////////////////////////////////////////////////////////
            int                         m_delay_count; //5f8

            TimerList                   m_timers; //5FC
            DelayList                   m_delays; //604

            /////////////////////////////////////////////////////////////////////////////////
            /////////////////////////////////////////////////////////////////////////////////
            SceUID                      m_heapuid;

            /////////////////////////////////////////////////////////////////////////////////
            int                         m_thread_switch_count[2]; //67c, 680

            /////////////////////////////////////////////////////////////////////////////////

            void                        ElectNextReadyThread(int priority);

            SceUID                      m_threadret_syscall;
            u32                         m_threadret_syscall_id;

            SceKernelThreadInfo         m_thread_info;
            SceKernelThreadOptParam     m_thread_opt_param;

            IntrSoft2                   m_intr_soft2;

            void                        TriggerIntrSoft2();

            using hal::hmm::Allocator< Scheduler >::operator new;
            using hal::hmm::Allocator< Scheduler >::operator delete;
        };

        typedef kd::Scheduler KernelScheduler;

        extern Scheduler * g_scheduler;
    }
}
