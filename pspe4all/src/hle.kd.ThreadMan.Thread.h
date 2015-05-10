/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifndef hle_kd_ThreadMan_h__
#error you must include "hle.kd.ThreadMan.h" instead
#endif

#include "hal.npa.h"
#include "hal.os.UmsThread.h"
#include "lle.cpu(Allegrex).h"

namespace hle
{
    namespace kd
    {
        /// KernelThread ////////////////////////////////////////////////////////////

        struct Thread : WaitQueue, ThreadQueue::Node, hal::os::UmsThread, hal::hmm::Allocator< Thread >
        {
            declare_kernel_type(Thread, WaitQueue);

            using hal::hmm::Allocator< Thread >::operator new;
            using hal::hmm::Allocator< Thread >::operator delete;

            /**/                           Thread(char const * name, SceKernelThreadEntry entry, int priority, SceSize stacksize, SceUInt attr);
            /**/                           Thread(char const * name);
            /**/                          ~Thread();

            /////////////////////////////////////////////////////////////////////////////////
            SceUInt                         m_current_attributes;
            SceUInt                         m_initial_attributes;

            int                             ChangeAttributes(u32 clear_bits, u32 set_bits, int intr);

            /////////////////////////////////////////////////////////////////////////////////
            enum TheadStatus
            {
                STATUS_INEXISTENT       = 0x00,
                STATUS_RUN              = SCE_KERNEL_THS_RUN,
                STATUS_READY            = SCE_KERNEL_THS_READY,
                STATUS_WAIT             = SCE_KERNEL_THS_WAIT,
                STATUS_SUSPEND          = SCE_KERNEL_THS_SUSPEND,
                STATUS_WAITSUSPEND      = STATUS_WAIT|STATUS_SUSPEND,
                STATUS_STOPPED          = SCE_KERNEL_THS_DORMANT,
                STATUS_KILLED           = SCE_KERNEL_THS_DEAD,
                STATUS_DELETABLE        = STATUS_STOPPED|STATUS_KILLED,
                STATUS_MASK             = STATUS_RUN|STATUS_READY|STATUS_WAITSUSPEND|STATUS_STOPPED|STATUS_KILLED
            };

            int                             m_status;
            SceKernelThreadEntry            m_entry;       //6c
            int                             m_exit_status; //18
            int                             m_argc;
            u32                             m_argp;

            static int                      Create(char const * name, SceKernelThreadEntry entry, int priority, SceSize stacksize, SceUInt attr, int intr);
            int                             Delete(int intr);

            int                             Start(SceSize argc, u32 argp, int intr);
            void                            Exit(int status, int intr, bool is_deletable = false);
            void                            ExitDelete(int status, int intr);
            int                             Terminate(int intr, bool is_deletable = false);
            int                             TerminateDelete(int intr);
            int                             Suspend(int is_intr_context);
            int                             Resume(int intr, int is_intr_context);
            int                             WaitThreadEnd(SceUInt * timeout, bool cb, int intr);
            int                             Delay(SceUInt delay, bool cb, int intr);
            int                             DelaySysClock(SceKernelSysClock * delay, bool cb, int intr);

            int                             _Start(SceSize argc, void const * argp, int intr);
            void                            _Start();
            void                            _Exit();

            /////////////////////////////////////////////////////////////////////////////////
            int                             m_initial_priority; //60
            int                             m_current_priority; //10

            int                             ChangePriority(int priority, int intr, int is_intr_context);

            /////////////////////////////////////////////////////////////////////////////////
            int                             m_wakeup_count; //14

            int                             Sleep(bool cb, int intr);
            int                             WakeUp(int intr, int is_intr_context);
            int                             CancelWakeUp(int intr);

            /////////////////////////////////////////////////////////////////////////////////
            int                             m_wait_type;  //1c
            hle::kd::WaitQueue            * m_wait_queue; //20
            int                             m_cb_arg1;    //24
            int                             m_cb_arg2;    //28
            int                             m_cb_arg3;    //2c
            int                             m_cb_arg4;    //30
            int                             m_cb_arg5;    //34

            bool                            ReleaseWaitingThread();
            void                            ReleaseWaitingThread(int /*intr_context*/, int /*intr*/);

            /////////////////////////////////////////////////////////////////////////////////
            s64                           * m_iores;

            s64                             GetIoResult() const;

            /////////////////////////////////////////////////////////////////////////////////
            hle::kd::Delay                * m_timeout_object;
            int                           * m_timeout; //3c

            int                             RequestTimeout(u64 timeout, int * result);

            /////////////////////////////////////////////////////////////////////////////////
            int                             m_event_mask;    //44 - events being fired
            hle::kd::EventHandler         * m_event_handler; //48 - event handler being fired

            void                            DispatchEventHandlers(int mask, int intr);
            void                            ReleaseEventHandler();

            /////////////////////////////////////////////////////////////////////////////////
            u32                             m_stack;
            SceUID                          m_stack_id;
            u32                             m_stack_size;
            u32                             m_stack_top;

            int                             GrabThreadStack(u32 stack_size, SceUID stack_id = 2);
            u32                             CheckStack();

            /////////////////////////////////////////////////////////////////////////////////
            u32                             m_gp; //88 ($gp or the module address)
            SceUID                          m_api_module_id;

            SceUID                          GetApiModuleId();

            /////////////////////////////////////////////////////////////////////////////////
            int                             m_callback_status; //40 - callback status
            hle::kd::CallbackQueue          m_callbacks;       //4c - callbacks for thread
            int                             m_check_callbacks; //54 - is callback
            int                             m_callback_notify; //58 - callback notify
            hle::kd::Callback             * m_callback;        //5c - callback

            int                             DispatchCallbacks(int intr);
            void                            ReleaseAllCallbacks(int intr);
            void                            ReleaseCallback();

            /////////////////////////////////////////////////////////////////////////////////
            SceKernelSysClock               m_run_clocks; //64

            /////////////////////////////////////////////////////////////////////////////////
            ThreadContext                   m_thread_context;
            ThreadContext                   m_callback_context;
            u32                             m_preempted_thread_switches;
            u32                             m_released_thread_switches;
            u32                           * m_thread_switches;

            bool                            SwitchToNext();
            void                            SwitchTo(int intr);
            void                            SwitchToIdle();
            void                            ReleaseWait(bool released, int intr);

            int                             ReferStatus(SceKernelThreadInfo * status, int intr);

            hal::npa::Event                 m_npa_event;

            DWORD                           Run();
            void                            Syscall(u32 opcode);
        };
    }

    typedef kd::Thread KernelThread;
}

__forceinline void hle::kd::Thread::ExitDelete(int status, int /*intr*/)
{
    Exit(status, true);
}


__forceinline int hle::kd::Thread::TerminateDelete(int /*intr*/)
{
    return Terminate(true);
}


__forceinline s64 hle::kd::Thread::GetIoResult() const
{
    return *m_iores;
}


__forceinline void hle::kd::Thread::DispatchEventHandlers(int /*mask*/, int /*intr*/)
{
}
