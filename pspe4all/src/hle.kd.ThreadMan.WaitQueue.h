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
        /// KernelWaitQueue /////////////////////////////////////////////////////////

        struct WaitQueue : Object
        {
            declare_kernel_type(WaitQueue, Object);

            enum Attributes
            {
                WAITQUEUE_FIFO     = 0x000U,
                WAITQUEUE_PRIORITY = 0x100U,
            };

            enum WaitType
            {
                WAITTYPE_NONE            =  0,
                WAITTYPE_SLEEP           =  1,
                WAITTYPE_DELAY           =  2,
                WAITTYPE_SEMA            =  3,
                WAITTYPE_EVENTFLAG       =  4,
                WAITTYPE_MBX             =  5,
                WAITTYPE_VPL             =  6,
                WAITTYPE_FPL             =  7,
                WAITTYPE_MPIPE           =  8,
                WAITTYPE_THREAD          =  9,
                WAITTYPE_EVENTHANDLER    = 10,
                WAITTYPE_CALLBACK        = 11,
                WAITTYPE_ALARM           = 12,
                WAITTYPE_VTIMER          = 13,
                WAITTYPE_MUTEX           = 14,
                WAITTYPE_LWMUTEX         = 15,

                WAITTYPE_SOFT2           = 0x100,
                WAITTYPE_DISPLAY_VSYNC   = 0x101,
                WAITTYPE_IOMGR_ASYNC     = 0x102,
                WAITTYPE_AUDIO           = 0x103,
                WAITTYPE_GE              = 0x104,
                WAITTYPE_GE_LISTSYNC     = 0x105,
                WAITTYPE_GE_DRAWSYNC     = 0x106,
            };

            SceUInt           m_attributes;
            u32               m_waiters_count;
            ThreadQueue       m_waiters_queue;

            WaitQueue(char const * name, SceUInt attr);
            ~WaitQueue();

            int               Delete(int intr);

            int               AddWaitingThread(Thread *, int wait_type, u64 time, SceUInt * timeout);
            bool              RemoveWaitingThread(Thread *);
            void              RemoveWaitingThread(Thread *, int intr_context, int intr);
            void              InsertWaitingThread(Thread *);

            u32               ReleaseAllWaitingThreads(int reason);

            virtual int       Cancel();
            virtual int       Acquire(); // TODO: not the appropriate name indeed
            virtual int       Release();

            void              ReleaseWait(bool released, int intr);
        };
    }

    typedef kd::WaitQueue KernelWaitQueue;
}
