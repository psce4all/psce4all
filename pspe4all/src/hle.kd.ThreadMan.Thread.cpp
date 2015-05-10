/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

//#include "hle.syscalls.Modules.h"

#define MAX_THREAD_PRIORITY     127
#define MIN_THREAD_STACKSIZE    0x200
#define THREAD_KSTACKSIZE       0x800

////

char const * hle::kd::Thread::m_object_type = "KernelThread";

void hle::kd::Thread::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

hle::kd::Thread::Thread(char const * name)
:   WaitQueue(name, WAITQUEUE_PRIORITY)
,   UmsThread(0, 0)
,   m_npa_event(name)
{
    ThreadQueue::Node::Clear();
}

hle::kd::Thread::Thread(char const * name, SceKernelThreadEntry entry, int priority, SceSize stacksize, SceUInt attr)
:   WaitQueue(name, WAITQUEUE_PRIORITY)
,   UmsThread(0, 0)
,   m_current_attributes(attr & SCE_KERNEL_AT_LEGAL_TH)
,   m_initial_attributes(attr & SCE_KERNEL_AT_LEGAL_TH)
,   m_status(STATUS_INEXISTENT)
,   m_entry(entry)
,   m_exit_status(SCE_KERNEL_ERROR_DORMANT)
,   m_argc(0)
,   m_argp(0)
,   m_initial_priority(priority)
,   m_current_priority(priority)
,   m_wakeup_count(0)
,   m_wait_type(WaitQueue::WAITTYPE_NONE)
,   m_wait_queue(0)
,   m_cb_arg1(0)
,   m_cb_arg2(0)
,   m_cb_arg3(0)
,   m_cb_arg4(0)
,   m_cb_arg5(0)
,   m_timeout_object(0)
,   m_timeout(0)
,   m_event_mask(0)
,   m_event_handler(0)
,   m_stack(0)
,   m_stack_id(0)
,   m_stack_size(stacksize)
,   m_stack_top(0)
,   m_gp(0/*theKernelModuleManager.GetModuleGPByAddress(entry)*/)
,   m_api_module_id(0/*theKernelModuleManager.GetModuleIdByAddress(entry)*/)
,   m_callback_status(0)
,   m_check_callbacks(0)
,   m_callback_notify(0)
,   m_callback(0)
,   m_run_clocks(0LL)
,   m_npa_event(name)
{
    if (g_scheduler && g_scheduler->GetCurrentThread())
    {
        if (!m_gp)
        {
            m_gp = g_scheduler->GetCurrentThread()->m_thread_context.gpr[ALLEGREX_GP];
        }

        if (m_api_module_id == SCE_KERNEL_ERROR_ILLEGAL_ADDR)
        {
            this->m_api_module_id = g_scheduler->GetCurrentThread()->GetApiModuleId();
        }
    }

#ifdef USE_NVPA
    m_event_id = gPerfUtils->registerEvent(name);
#endif
}

hle::kd::Thread::~Thread()
{
    if (m_stack_id)
    {
        PartitionBlock * object;

        int result = Objects.Get< PartitionBlock >(m_stack_id, object);

        if (!result)
        {
            object->Delete(0);
        }
    }
}

int hle::kd::Thread::ChangeAttributes(u32 clear_bits, u32 set_bits, int intr)
{
    (void)clear_bits;
    (void)set_bits;
    (void)intr;
    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Thread::Create(char const * name, SceKernelThreadEntry entry, int priority, SceSize stacksize, SceUInt attr, int intr)
{
    if (!name)
    {
        return SCE_KERNEL_ERROR_ERROR;
    }

    auto * created_thread = new Thread(name, entry, priority, stacksize, attr);

    created_thread->GrabThreadStack(stacksize, g_scheduler->m_thread_opt_param.stack_id);

    g_scheduler->AddThreadToDormantQueue(created_thread);

    created_thread->DispatchEventHandlers(SCE_KERNEL_THREAD_EVENT_CREATE, intr);

    return created_thread->GetUid();
}

int hle::kd::Thread::Delete(int intr)
{
    if (this->m_status & STATUS_DELETABLE)
    {
        return SCE_KERNEL_ERROR_NOT_DORMANT;
    }

    if (this->m_event_mask)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
    }

    this->DispatchEventHandlers(SCE_KERNEL_THREAD_EVENT_DELETE, intr);

    this->m_status = STATUS_INEXISTENT;

    this->RemoveFromList();

    if (this->m_current_attributes & SCE_KERNEL_THREAD_ATTR_CLEAR_STACK)
    {
        ::memset(&((u8 &)*p32< u8 >(this->m_stack)), 0, this->m_stack_size);
    }

    return WaitQueue::Delete(intr);
}

int hle::kd::Thread::_Start(SceSize argc, void const *argp, int intr)
{
    if (this->m_status == STATUS_STOPPED)
    {
        if (this->m_event_mask)
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        this->m_stack_top  = this->m_stack + this->m_stack_size - 256;
        ::memset(&((u8 &)*p32< u8 >(this->m_stack_top)), 0, 64);
        p32< SceThreadStack >(this->m_stack)->thread_id = this->GetUid();

        this->m_wait_type          = WaitQueue::WAITTYPE_NONE;
        this->m_current_attributes = this->m_initial_attributes;
        this->m_current_priority   = this->m_initial_priority;
        this->m_wait_queue         = 0;
        this->m_wakeup_count       = 0;

        this->m_stack_top -= (u32(argc) + 15) & ~15;
        if (argc > 0 && argp)
        {
            this->m_argc = argc;
            this->m_argp = this->m_stack_top;
            ::memcpy(&((u8 &)*p32< u8 >(this->m_stack_top)), argp, argc);
        }
        else
        {
            this->m_argc = 0;
            this->m_argp = 0;
        }

        this->m_stack_top -= 64;

        // RA: <--- $RA points here
        //   JR $RA;
        //   SYSCALL _sceKernelExitThread;
        // PC: <--- entry of starting thread
        //   SYSCALL _sceKernelStartThread;

#if 0
        theKernelModuleManager.WriteSyscall("ThreadManForUser", 0x07F3A4BC, this->m_stack_top + 4); // _sceKernelStartThread syscall
        theKernelModuleManager.WriteSyscall("ThreadManForUser", 0x532A522E, this->m_stack_top + 0); // _sceKernelExitThread syscall
#else
        //hle::syscalls::WriteSyscall("ThreadManForUser", 0x07F3A4BC, this->m_stack_top + 4); // _sceKernelStartThread syscall
        //hle::syscalls::WriteSyscall("ThreadManForUser", 0x532A522E, this->m_stack_top + 0); // _sceKernelExitThread syscall
#endif
        this->m_thread_context.pc = u32(this->m_stack_top + 8);
        this->m_thread_context.ie = 1;


        this->m_exit_status = SCE_KERNEL_ERROR_NOT_DORMANT;

        this->RemoveFromList();
        this->SwitchTo(intr);

        return SCE_KERNEL_ERROR_OK;
    }

    return SCE_KERNEL_ERROR_NOT_DORMANT;
}

int hle::kd::Thread::Start(SceSize argc, u32 argp, int intr)
{
    if (argc > 0 && argp)
    {
        return _Start(argc, p32< void const >(argp), intr);
    }
    else
    {
        return _Start(0, 0, intr);
    }
}

void hle::kd::Thread::SwitchToIdle()
{
    GrabThreadStack(this->m_stack_size, false);

    this->m_stack_top  = this->m_stack + this->m_stack_size - 8;
    p32< SceThreadStack >(this->m_stack)->thread_id = this->GetUid();

    this->m_wait_type                       = WaitQueue::WAITTYPE_NONE;
    this->m_current_attributes              = this->m_initial_attributes;
    this->m_current_priority                = this->m_initial_priority;
    this->m_wait_queue                      = 0;
    this->m_wakeup_count                    = 0;
    this->m_argc                            = 0;
    this->m_argp                            = 0;
    this->m_thread_context.gpr[ALLEGREX_SP] = u32(this->m_stack_top);
    this->m_thread_context.gpr[ALLEGREX_FP] = u32(this->m_stack_top);
    this->m_thread_context.gpr[ALLEGREX_RA] = u32(this->m_stack_top);
    this->m_thread_context.pc               = u32(this->m_stack_top);
    this->m_thread_context.ie               = 1;
    this->m_exit_status                     = SCE_KERNEL_ERROR_NOT_DORMANT;
    this->m_status                          = STATUS_RUN;
    this->RemoveFromList();

#if 0
    theKernelModuleManager.WriteSyscall("ThreadManForUser", 0xE0A68B8C, this->m_stack_top); // _sceKernelIdleThread syscall
#else
    //hle::syscalls::WriteSyscall("ThreadManForUser", 0xE0A68B8C, this->m_stack_top); // _sceKernelIdleThread syscall
#endif

    g_scheduler->m_current_thread = this;
    g_scheduler->m_elected_thread = 0;

    //theEmulator->reschedule = true;

#ifdef USE_NVPA
    if (gPerfUtils)
    {
        gPerfUtils->startEvent(this->m_event_id);
    }
#endif
    //Fiber::SwitchTo();
}

// for sceKernelExitThread/sceKernelExitDeleteThread
void hle::kd::Thread::Exit(int status, int intr, bool is_deletable)
{
    this->m_exit_status = status;

    if (g_scheduler->m_dispatch_thread_suspended)
    {
        g_scheduler->m_dispatch_thread_suspended = 0;
    }

    if (is_deletable)
    {
        this->m_event_mask |= SCE_KERNEL_THREAD_EVENT_DELETE;
    }

    this->DispatchEventHandlers(SCE_KERNEL_THREAD_EVENT_EXIT, intr);

    this->ReleaseAllWaitingThreads(status);

    this->ReleaseAllCallbacks(intr);

    if (is_deletable)
    {
        this->m_status = STATUS_DELETABLE;

        g_scheduler->m_deletable_threads.Append(this);
        g_scheduler->m_do_cleanup = true;
    }
    else
    {
        this->m_status = STATUS_STOPPED;

        g_scheduler->m_stopped_threads.Append(this);
    }

    g_scheduler->m_elected_thread = 0;

    this->ReleaseWait(true, 1);

    assert(("panic ! Thread DORMANT !", 0));
}

// for sceKernelTerminateThread/sceKernelTerminateDeleteThread
int hle::kd::Thread::Terminate(int /*intr*/, bool /*is_deletable*/)
{
#if 0
    int result;

    if (m_status == STATUS_DELETABLE)
    {
        return SCE_KERNEL_ERROR_UNKNOWN_THID;
    }

    if (m_status & STATUS_DELETABLE)
    {
        if (this == theKernelScheduler->GetCurrentThread() && theKernelScheduler->m_dispatch_thread_suspended)
        {
            theKernelScheduler->m_dispatch_thread_suspended = 3;

            return SCE_KERNEL_ERROR_OK;
        }

        if (m_event_mask  & (SCE_KERNEL_THREAD_EVENT_EXIT|SCE_KERNEL_THREAD_EVENT_DELETE))
        {
            if (is_deletable)
            {
                return SCE_KERNEL_ERROR_DORMANT;
            }

            m_event_mask |= SCE_KERNEL_THREAD_EVENT_DELETE;

            return SCE_KERNEL_ERROR_OK;
        }

        m_exit_status = SCE_KERNEL_ERROR_THREAD_TERMINATED;

        if (theKernelScheduler->m_dispatch_thread_suspended)
        {
            theKernelScheduler->m_dispatch_thread_suspended = 0;
        }

        this->ReleaseEventHandler();

        this->ReleaseCallback();

        //ret = sub_0000E7A8(thread);
        if (!result /*&& sub_000022B4(0x4, thread) == 0*/)
        {
            this->ReleaseAllWaitingThreads(SCE_KERNEL_ERROR_THREAD_TERMINATED);

            //sub_0000237C(thread);
            if (!isIntr || thread != gInfo.currentThread)
            {
                if (m_status == STATUS_READY)
                {
                    if (m_next == m_prev && m_next != this)
                    {
                        //CLEAR_THREAD_PRIORITY_FLAG(thread->currentPriority);
                    }

                    //REMOVE_FROM_LIST(thread);
                }
                else
                {
                    //REMOVE_FROM_LIST(thread);

                    if (m_status == STATUS_WAIT || m_status == STATUS_WAITSUSPEND)
                    {
                        //sub_00000544(thread);

                        if (m_wait_type != 0)
                        {
                            //sub_000005F4(thread->waitType);
                        }
                    }
                }
            }

            //ADD_TO_LIST(thread, gInfo.stoppedThreads);

            m_status = PSP_THREAD_STOPPED;
        }
        else
        {
            if (m_status == STATUS_READY)
            {
                //REMOVE_FROM_LIST(thread);

                if (m_status == STATUS_WAIT || m_status == STATUS_WAITSUSPEND)
                {
                    //sub_00000544(thread);

                    if (m_wait_type != 0)
                    {
                        //sub_000005F4(thread->waitType);
                    }
                }
            }

            //sub_0000FFA4(thread->threadContext);

            //thread->threadContext->type = 0x4;
            //thread->threadContext->gpr[GPREG_A1 - 1] = SCE_KERNEL_ERROR_THREAD_TERMINATED;
            //thread->threadContext->gpr[GPREG_A0 - 1] = 0;
            //thread->threadContext->gpr[GPREG_SP - 1] = THREAD_IS_USER_MODE(thread) ? thread->kStackPointer : thread->stackPointer;
            //thread->threadContext->gpr[GPREG_RA - 1] = sub_000136F4;
            //thread->threadContext->gpr[GPREG_FP - 1] = thread->threadContext->gpr[GPREG_SP - 1];
            //thread->threadContext->EPC = doExitDeleteThread;
            //thread->threadContext->gpr[GPREG_GP - 1] = thread->gpreg;
            //thread->threadContext->status = 0x20000003;
            if (m_status != STATUS_READY)
            {
                m_status = STATUS_READY;

                //_AddThreadToReadyQueue(thread);

                theKernelScheduler->m_elected_thread = 0;
            }

            if (!isIntr)
            {
                //result = AddThreadToWaitQueue(cb, 0x9, 0, 0, 0);
                if (result != SCE_KERNEL_ERROR_THREAD_TERMINATED)
                {
                    result = SCE_KERNEL_ERROR_OK;
                }
            }
        }

        if (!is_deletable)
        {
            return result;
        }

        DispatchEventHandlers(SCE_KERNEL_THREAD_EVENT_DELETE, intr);

        m_status = STATUS_STOPPED;

        //REMOVE_FROM_LIST(thread);

        //_ClearAllThreadStacks(thread, intr);

        return result;
    }
    else
    {
        if (!is_deletable)
        {
            return SCE_KERNEL_ERROR_DORMANT;
        }

        DispatchEventHandlers(SCE_KERNEL_THREAD_EVENT_DELETE, intr);

        m_status = SCE_KERNEL_ERROR_OK;

        //REMOVE_FROM_LIST(thread);

        //_ClearAllThreadStacks(thread, intr);
    }
#endif

    return SCE_KERNEL_ERROR_OK;
}

// for sceKernelSleepThread/sceKernelSleepThreadCB
int hle::kd::Thread::Sleep(bool cb, int intr)
{
    if (intr == 0 || g_scheduler->m_dispatch_thread_suspended != 0)
    {
        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    for (;;)
    {
        if (cb && this->m_callback_notify)
        {
            DispatchCallbacks(intr);
        }

        this->m_callback_status = 0;

        if (this->m_wakeup_count == 0)
        {
            g_scheduler->m_sleeping_threads.AddWaitingThread(this, WaitQueue::WAITTYPE_SLEEP);

            if (cb) this->m_check_callbacks = true;

            g_scheduler->m_elected_thread = 0;

            ReleaseWait(true, 1);
        }
        else
        {
            this->m_wakeup_count--;
        }

        if (!cb || this->m_callback_status != SCE_KERNEL_ERROR_NOTIFY_CALLBACK)
        {
            break;
        }
    }

    return this->m_callback_status;
}

// for sceKernelWakeupThread
int hle::kd::Thread::WakeUp(int intr, int is_intr_context)
{
    if (!is_intr_context && this == g_scheduler->GetCurrentThread())
    {
        return SCE_KERNEL_ERROR_ILLEGAL_THID;
    }

    if (this->m_status & STATUS_DELETABLE)
    {
        return SCE_KERNEL_ERROR_DORMANT;
    }

    if ((this->m_status & STATUS_WAIT) && this->m_wait_type == WaitQueue::WAITTYPE_SLEEP)
    {
        this->ReleaseWaitingThread(is_intr_context, intr);
    }
    else
    {
        this->m_wakeup_count++;
    }

    return 0;
}


// for sceKernelCancelWakeupThread
int hle::kd::Thread::CancelWakeUp(int /*intr*/)
{
    int result = this->m_wakeup_count;
    this->m_wakeup_count = 0;

    return result;
}

// for sceKernelSuspendThread
int hle::kd::Thread::Suspend(int is_intr_context)
{
    int result;

    switch (this->m_status)
    {
        case STATUS_RUN:
        {
            if (g_scheduler->m_dispatch_thread_suspended)
            {
                if (g_scheduler->m_dispatch_thread_suspended != 3)
                {
                    g_scheduler->m_dispatch_thread_suspended = 2;
                }
                result = SCE_KERNEL_ERROR_OK;
                break;
            }
        }

        case STATUS_READY:
        {
            if (is_intr_context)
            {
                g_scheduler->RemoveThreadFromReadyQueue(this);
            }
            g_scheduler->m_suspended_threads.Append(this);

            this->m_status = STATUS_SUSPEND;
            result = SCE_KERNEL_ERROR_OK;
            break;
        }

        case STATUS_WAIT:
        {
            this->m_status |= STATUS_SUSPEND;
            result = SCE_KERNEL_ERROR_OK;
            break;
        }

        case STATUS_SUSPEND:
        case STATUS_WAITSUSPEND:
        {
            result = SCE_KERNEL_ERROR_SUSPEND;
            break;
        }

        default:
        {
            result = SCE_KERNEL_ERROR_DORMANT;
            break;
        }
    }

    return result;
}

// for sceKernelResumeThread
int hle::kd::Thread::Resume(int intr, int is_intr_context)
{
    int result;

    switch (this->m_status)
    {
        case STATUS_RUN:
        {
            if (g_scheduler->m_dispatch_thread_suspended == 2)
            {
                g_scheduler->m_dispatch_thread_suspended = 1;
                result = SCE_KERNEL_ERROR_OK;
            }
            else
            {
                result = SCE_KERNEL_ERROR_NOT_SUSPEND;
            }
            break;
        }

        case STATUS_SUSPEND:
        {
            this->RemoveFromList();

            if (!is_intr_context)
            {
                this->m_status = STATUS_READY;
                this->SwitchTo(intr);
            }
            else
            {
                g_scheduler->AddThreadToReadyQueue(this);
                g_scheduler->m_elected_thread = 0;
            }

            result = SCE_KERNEL_ERROR_OK;
            break;
        }

        case STATUS_WAITSUSPEND:
        {
            this->m_status = STATUS_WAIT;
            result = SCE_KERNEL_ERROR_OK;
            break;
        }

        default:
        {
            result = SCE_KERNEL_ERROR_NOT_SUSPEND;
            break;
        }
    }

    return result;
}

// for sceKernelWaitThreadEnd/sceKernelWaitThreadEndCB
int hle::kd::Thread::WaitThreadEnd(SceUInt * timeout, bool cb, int intr)
{
    if (!intr || g_scheduler->m_dispatch_thread_suspended)
    {
        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    auto * that = g_scheduler->GetCurrentThread();
    if (this == that)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_THID;
    }

    if (this->m_status >= STATUS_STOPPED)
    {
        return this->m_exit_status;
    }

    SceKernelSysClock clk;

    if (timeout)
    {
        clk += u64(*timeout);
    }

    int result;
    do
    {
        if (cb && that->m_callback_notify)
        {
            DispatchCallbacks(intr);
        }

        that->m_check_callbacks = cb;

        result = this->AddWaitingThread(that, WaitQueue::WAITTYPE_THREAD, clk, timeout);
    }
    while (cb && result == SCE_KERNEL_ERROR_NOTIFY_CALLBACK);

    return result;
}

// for sceKernelDelayThread/sceKernelDelayThreadCB
int hle::kd::Thread::Delay(SceUInt delay, bool cb, int intr)
{
    if (intr == 0 || g_scheduler->m_dispatch_thread_suspended != 0)
    {
        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    u64 time = delay + theSysClock->Get();

    do
    {
        if (cb && this->m_callback_notify)
        {
            DispatchCallbacks(intr);
        }

        this->m_timeout = 0;

        int result = RequestTimeout(time, 0);
        if (result < 0)
        {
            return (result == SCE_KERNEL_ERROR_WAIT_TIMEOUT) ? 0 : result;
        }

        g_scheduler->m_delayed_threads.AddWaitingThread(this, WaitQueue::WAITTYPE_DELAY);

        ReleaseWait(true, 1);
    }
    while (cb && this->m_callback_status == SCE_KERNEL_ERROR_NOTIFY_CALLBACK);

    return this->m_callback_status;
}


// for sceKernelDelaySysClockThread/sceKernelDelaySysClockThreadCB
int hle::kd::Thread::DelaySysClock(SceKernelSysClock * delay, bool cb, int intr)
{
    if (intr == 0 || g_scheduler->m_dispatch_thread_suspended != 0)
    {
        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    u64 time = *delay + theSysClock->Get();

    do
    {
        if (cb && this->m_callback_notify)
        {
            DispatchCallbacks(intr);
        }

        this->m_timeout = 0;

        int result = RequestTimeout(time, 0);
        if (result < 0)
        {
            return (result == SCE_KERNEL_ERROR_WAIT_TIMEOUT) ? 0 : result;
        }

        g_scheduler->m_delayed_threads.AddWaitingThread(this, WaitQueue::WAITTYPE_DELAY);

        ReleaseWait(true, 1);
    }
    while (cb && this->m_callback_status == SCE_KERNEL_ERROR_NOTIFY_CALLBACK);

    return this->m_callback_status;
}

void hle::kd::Thread::_Start()
{
    ::memset(&this->m_thread_context.gpr[ALLEGREX_ZR], 0, sizeof(u32)*32);
    ::memset(&this->m_thread_context.fpr[ALLEGREX_F0], 0, sizeof(f32)*32);
    ::memset(&this->m_thread_context.vpr[0          ], 0, sizeof(f32)*4*4*8);

    this->m_thread_context.fcr31 = 0;
    this->m_thread_context.hilo  = 0;
    this->m_thread_context.vcr.Reset();
    this->m_thread_context.rnd.SetSeed(0x3f800001);

    this->m_thread_context.gpr[ALLEGREX_A0] = u32(this->m_argc);
    this->m_thread_context.gpr[ALLEGREX_A1] = u32(this->m_argp);
    this->m_thread_context.gpr[ALLEGREX_K0] = u32(this->m_stack_top);
    this->m_thread_context.gpr[ALLEGREX_GP] = u32(this->m_gp);
    this->m_thread_context.gpr[ALLEGREX_SP] = u32(this->m_stack_top);
    this->m_thread_context.gpr[ALLEGREX_FP] = u32(this->m_stack_top);
    this->m_thread_context.gpr[ALLEGREX_RA] = u32(this->m_stack_top);
    this->m_thread_context.pc               = u32(this->m_entry);

    this->DispatchEventHandlers(SCE_KERNEL_THREAD_EVENT_START, 1);
}


void hle::kd::Thread::_Exit()
{
    Exit(this->m_thread_context.gpr[ALLEGREX_V0], 1, false);
}


int hle::kd::Thread::ChangePriority(int priority, int intr, int is_intr_context)
{
    if (this->m_status & STATUS_DELETABLE)
    {
        return SCE_KERNEL_ERROR_DORMANT;
    }

    if (!priority)
    {
        priority = this->m_current_priority;
    }

    if (this == g_scheduler->GetCurrentThread())
    {
        if (g_scheduler->m_dispatch_thread_suspended)
        {
            this->m_current_priority = priority;
        }
        else
        {
            if (is_intr_context) // does it mean we should delay rescheduling ?
            {
                this->m_current_priority = priority;
                g_scheduler->AddThreadToReadyQueue(this);
                g_scheduler->m_elected_thread = 0;
            }
            else
            {
                int highest_priority = 0, i, bit;
                for (i = 0; i < (MAX_THREAD_PRIORITY + 1) / 32; i++)
                {
                    int mask = g_scheduler->m_priority_mask[i];
                    if (mask != 0)
                    {
                        for (bit = 0; bit < 31; bit++)
                        {
                            if (mask & (1 << bit))
                            {
                                break;
                            }
                        }
                        highest_priority = i * 32 + bit;
                        break;
                    }
                }

                if (i == (MAX_THREAD_PRIORITY + 1) / 32)
                {
                    highest_priority = MAX_THREAD_PRIORITY + 1;
                }

                if (highest_priority <= priority)
                {
                    this->m_current_priority = priority;

                    if (intr)
                    {
                        g_scheduler->AddThreadToReadyQueue(this);
                        g_scheduler->m_elected_thread = 0;
                        ReleaseWait(0, intr);
                    }
                }
            }
        }
    }
    else
    {
        switch (this->m_status)
        {
            case STATUS_READY:
            {
                if (is_intr_context || g_scheduler->m_dispatch_thread_suspended || priority >= g_scheduler->GetCurrentThread()->m_current_priority)
                {
                    g_scheduler->RemoveThreadFromReadyQueue(this);

                    this->m_current_priority = priority;

                    g_scheduler->AddThreadToReadyQueue(this);
                    g_scheduler->m_elected_thread = 0;
                }
                else
                {
                    if (intr) // interrupts enabled : immediate thread switching allowed
                    {
                        g_scheduler->AddThreadToReadyQueue(g_scheduler->m_current_thread);

                        this->m_status = STATUS_RUN;
                        g_scheduler->m_elected_thread = this;

                        ReleaseWait(false, intr);
                    }
                    else // interrupts disabled : no thread switching
                    {
                        g_scheduler->AddThreadToReadyQueue(this);
                        g_scheduler->m_elected_thread = 0;
                    }
                }
                break;
            }

            case STATUS_WAIT:
            case STATUS_WAITSUSPEND:
            {
                if (this->m_wait_queue->m_attributes & WaitQueue::WAITQUEUE_PRIORITY)
                {
                    this->RemoveFromList();
                    this->m_wait_queue->InsertWaitingThread(this);
                    // i think it tries to determine if waiting threads in the queue should be wake up
                    if (true/*sub_000005F4(thinfo->waitType)*/ && !g_scheduler->m_dispatch_thread_suspended)
                    {
                        g_scheduler->m_elected_thread = 0;
                        if (!is_intr_context)
                        {
                            ReleaseWait(false, intr);
                        }
                    }
                }
                break;
            }

            default: // is there any reason not to change priority for any status else ?
            {
                this->m_current_priority = priority;
                break;
            }
        }
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Thread::GrabThreadStack(u32 stack_size, SceUID stack_id)
{
    char stack_name[32];

    ::strcpy(stack_name + 0, "stack:");
    ::strncpy(stack_name + 6, m_name, sizeof(stack_name) - 6);
    stack_name[31] = '\0';

    stack_size = ((stack_size + 255) & ~255);

    PartitionBlock *stack;

    if (!stack_id)
    {
        stack_id = 2;
    }

    if (Partition::Get(stack_id)->AllocatePartitionBlock(stack_name, 1, 0, stack_size, stack))
    {
        m_stack_id   = stack->GetUid();
        m_stack      = stack->m_address;
        m_stack_size = stack_size;

        if (!(this->m_current_attributes & SCE_KERNEL_THREAD_ATTR_NO_FILLSTACK))
        {
            u8 * p = &((u8 &)(*p32< u8 >(m_stack)));
            ::memset(p, 255, m_stack_size);
        }

        return SCE_KERNEL_ERROR_OK;
    }

    return SCE_KERNEL_ERROR_NO_MEMORY;
}

u32 hle::kd::Thread::CheckStack()
{
    return this->m_thread_context.gpr[ALLEGREX_SP] - this->m_stack;
}

SceUID hle::kd::Thread::GetApiModuleId()
{
    return (m_api_module_id > 0) ? m_api_module_id : 0x80020001;
}

bool hle::kd::Thread::SwitchToNext()
{
    if (g_scheduler->m_dispatch_thread_suspended)
    {
        return true;
    }

    if (g_scheduler->m_elected_thread == 0)
    {
        g_scheduler->ElectNextRunningThread();
    }

    if (g_scheduler->m_elected_thread == g_scheduler->m_current_thread)
    {
        g_scheduler->m_thread_switch_count[1]++;
    }
    else
    {
        SceKernelSysClock sysclock(theSysClock->Get());

        this->m_run_clocks     = sysclock - g_scheduler->m_unk_428;
        g_scheduler->m_unk_428 = sysclock;

        g_scheduler->m_thread_switch_count[0]++;
    }

#ifdef USE_NVPA
    if (gPerfUtils && theKernelScheduler->m_current_thread)
    {
        gPerfUtils->stopEvent(theKernelScheduler->m_current_thread->m_event_id);
    }
#endif
    auto * next_thread            = g_scheduler->m_elected_thread;
    g_scheduler->m_current_thread = next_thread;
#ifdef USE_NVPA
    if (gPerfUtils)
    {
        gPerfUtils->startEvent(next_thread->m_event_id);
    }
#endif
    this->m_thread_context.ie = KernelIntr::m_ie;
    //next_thread->Fiber::SwitchTo();
    g_scheduler->m_elected_thread = 0;
    KernelIntr::Resume(this->m_thread_context.ie);
    return true;
}

bool hle::kd::Thread::ReleaseWaitingThread()
{
    if (this->m_status == STATUS_KILLED)
    {
        return false;
    }

    this->m_check_callbacks = false;

    if (this->m_timeout_object)
    {
        this->m_timeout_object->Cancel();
        this->m_timeout_object = 0;
        this->m_timeout        = 0;
    }

    if (this->m_wait_queue)
    {
        this->m_wait_queue->Release();
    }

    this->RemoveFromList();

    if (this->m_status == STATUS_WAITSUSPEND)
    {
        g_scheduler->m_suspended_threads.Append(this);
        this->m_status = STATUS_SUSPEND;

        return false;
    }

    return true;
}

void hle::kd::Thread::ReleaseWaitingThread(int intr_context, int intr)
{
    if (ReleaseWaitingThread())
    {
        if (intr_context)
        {
            g_scheduler->AddThreadToReadyQueue(this);
            g_scheduler->m_elected_thread = 0;
        }
        else
        {
            SwitchTo(intr);
        }
    }
}

void hle::kd::Thread::SwitchTo(int intr)
{
    if (!g_scheduler->m_current_thread || this->m_current_priority >= g_scheduler->m_current_thread->m_current_priority || g_scheduler->m_dispatch_thread_suspended)
    {
        g_scheduler->AddThreadToReadyQueue(this);

        return;
    }

    if (intr)
    {
        g_scheduler->AddThreadToReadyQueue(g_scheduler->m_current_thread);

        this->m_status = STATUS_RUN;
        g_scheduler->m_elected_thread = this;
    }
    else
    {
        g_scheduler->AddThreadToReadyQueue(this);
        g_scheduler->m_elected_thread = 0;
    }

    ReleaseWait(false, intr);
}

void hle::kd::Thread::ReleaseWait(bool released, int intr)
{
    this->m_thread_switches = released ? &this->m_released_thread_switches : &this->m_preempted_thread_switches;
    if (!intr)
    {
        g_scheduler->TriggerIntrSoft2();
    }
    else
    {
        this->SwitchToNext();
        this->m_check_callbacks = 0;
    }
}

int hle::kd::Thread::ReferStatus(SceKernelThreadInfo * info, int intr)
{
    (void)intr;

    SceKernelThreadInfo * buffer = &g_scheduler->m_thread_info;

    ::memset(buffer, 0, sizeof(SceKernelThreadInfo));

    buffer->size = min(info->size, SceSize(sizeof(SceKernelThreadInfo)));

    if (GetName())
    {
        strncpy(buffer->name, GetName(), 31);
    }

    buffer->attributes       = this->m_current_attributes;
    buffer->entry            = this->m_entry;
    buffer->status           = this->m_status;
    buffer->stack_size       = this->m_stack_size;
    buffer->stack_base       = this->m_stack;
    buffer->initial_priority = this->m_initial_priority;
    buffer->current_priority = this->m_current_priority;
    buffer->gp_reg           = this->m_gp;

    if (this->m_status == STATUS_WAIT || this->m_status == STATUS_WAITSUSPEND)
    {
        buffer->wait_type = this->m_wait_type;
        buffer->wait_id   = this->m_wait_queue->GetUid();
    }

    buffer->wakeup_count = this->m_wakeup_count;
    buffer->exit_status  = this->m_exit_status;

    //t6 = gInfo.currentThread;
    //v0 = 0;
    //fp = &buf->runClocks;
    //s2 = thread->runClocks.hi;
    //a3 = thread->runClocks.low;
    //t9 = s2 << 0;
    //s2 = v0 + a3;
    //t8 = s2 < a3;
    //t7 = t9 + s3;
    //s3 = t7 + t8;
    //if(thread == gInfo.currentThread)
    //{
    //    v0v1 = sub_0000B490();

    //    t0 = gInfo.unk_428.hi;
    //    a3 = gInfo.unk_428.low;

    //    a1 = 0;
    //    t8 = t0 << 0;
    //    t5 = a1 + a3;
    //    t9 = 0;
    //    t7 = t5 < a3;
    //    t6 = t8 + t9;
    //    t1 = t6 + t7;
    //    a0 = v0 - t5;
    //    t4 = v0 < t5;
    //    t3 = v1 - t1;
    //    t2 = t3 - t4;
    //    s2 = s2 + a0;
    //    t0 = s2 < a0;
    //    a2 = s3 + t2;
    //    s3 = a2 + t0;
    //}

    //v1 = s3 >> 0;
    //buf->runClocks.hi = v1;
    //buf->runClocks.low = s2;

    buffer->run_clocks           = this->m_run_clocks;
    buffer->intr_preempt_count   = 0; //this->m_intr_preempt_count;
    buffer->thread_preempt_count = 0; //this->m_thread_preempt_count;
    buffer->release_count        = 0; //this->m_release_count;

    ::memcpy(info, buffer, buffer->size);

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Thread::RequestTimeout(u64 timeout, int * result)
{
    Delay::Create(timeout, result, this);

    return SCE_KERNEL_ERROR_OK;
}

void hle::kd::Thread::ReleaseEventHandler()
{
    EventHandler * eh = m_event_handler;

    if (!eh)
    {
        return;
    }

    eh->m_uses--;

    if (eh->m_invalid != 0)
    {
        if (eh->m_uses == 0)
        {
            eh->RemoveFromList();
            eh->ReleaseAllWaitingThreads(SCE_KERNEL_ERROR_OK);
        }
    }

    m_event_handler = 0;
    m_event_mask    = 0;
}

void hle::kd::Thread::ReleaseAllCallbacks(int intr)
{
    Callback * callback;

    while (callback = m_callbacks.First())
    {
        callback->m_uses = 0;
        callback->Delete(intr);
    }

    m_callback_notify = 0;
}

void hle::kd::Thread::ReleaseCallback()
{
    Callback * callback = m_callback;

    if (!callback)
    {
        return;
    }

    callback->m_uses--;

    if (callback->m_invalid != 0)
    {
        if (callback->m_uses == 0)
        {
            callback->RemoveFromList();
            callback->ReleaseAllWaitingThreads(SCE_KERNEL_ERROR_OK);
        }
    }

    m_callback = 0;
}

#if 0
char const * Emulator::ThreadName()
{
    if (theKernelScheduler && theKernelScheduler->GetCurrentThread())
    {
        return theKernelScheduler->GetCurrentThread()->GetName();
    }
    return "<none>";
}
#endif

DWORD hle::kd::Thread::Run()
{
    static long state;

    Intr::Resume(this->m_thread_context.ie);
loop:
    state = emulator->RawState();
loop1:
    switch (state & emu::EmulatorState::EmuStateMask)
    {
        case emu::EmulatorState::EmuRunning:
        {
            emulator->ExecutePendingEvents();
            {
                do
                {
                    this->m_thread_context.Interpret();
                }
                while (emulator->IsStateUnchanged(state));
            }
            goto loop1;
        }

        case emu::EmulatorState::EmuPausing:
        {
            if (!emulator->Start())
            {
                hal::os::Thread::Yield();
            }
            goto loop;
        }

        case emu::EmulatorState::EmuLeaving:
        {
            break;
        }

        default:
        {
            goto loop;
        }
    }

    return 0;
}
