/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

hle::kd::Scheduler * hle::kd::g_scheduler = 0;

hle::kd::Scheduler::Scheduler()
:   m_current_thread(0)
,   m_elected_thread(0)
,   m_idle_thread(0)
,   m_dispatch_thread_suspended(0)
,   m_do_cleanup(false)
{
    ::memset(m_priority_mask, 0, sizeof(m_priority_mask));

    m_idle_thread = new hle::kd::Thread("SceThreadmanIdle", 0, 127, 256, 0);
}

hle::kd::Scheduler::~Scheduler()
{
    m_idle_thread->Delete(0);
}

void hle::kd::Scheduler::ElectNextRunningThread()
{
    int i, bit, priority = 0;

    this->m_elected_thread = this->m_current_thread;

    if (this->m_do_cleanup)
    {
        this->m_do_cleanup = 0;

        for (auto * deletable_thread = g_scheduler->m_deletable_threads.First(); deletable_thread; )
        {
            auto * next_thread = g_scheduler->m_deletable_threads.Next(deletable_thread);

            deletable_thread->Delete(0);

            deletable_thread = next_thread;
        }
    }

    for (i = 0; i < (MAX_THREAD_PRIORITY + 1) / 32; i++)
    {
        int mask = this->m_priority_mask[i];
        if (mask != 0)
        {
            for (bit = 0; bit < 31; bit++)
            {
                if (mask & (1 << bit))
                {
                    break;
                }
            }
            priority = i * 32 + bit;
            break;
        }
    }

    if (i == (MAX_THREAD_PRIORITY + 1) / 32)
    {
        priority = MAX_THREAD_PRIORITY + 1;
    }

    if (priority > MAX_THREAD_PRIORITY)
    {
        return;
    }

    auto * current_thread = this->m_current_thread;

    if (KernelThread::STATUS_RUN == current_thread->m_status)
    {
        int current_priority = current_thread->m_current_priority;

        if (priority >= current_priority)
        {
            return;
        }

        // make current thread ready
        g_scheduler->AddThreadToReadyQueue(current_thread);
    }

    // set next thread to run
    g_scheduler->ElectNextReadyThread(priority);
}

void hle::kd::Scheduler::AddThreadToReadyQueue(Thread * runnable_thread)
{
    int current_priority = runnable_thread->m_current_priority;
    this->m_priority_mask[current_priority / 32] |= 1 << (current_priority % 32);
    this->m_ready_threads[current_priority].Append(runnable_thread);
    runnable_thread->m_status = Thread::STATUS_READY;
}

void hle::kd::Scheduler::RemoveThreadFromReadyQueue(Thread * runnable_thread)
{
    int current_priority = runnable_thread->m_current_priority;
    runnable_thread->RemoveFromList();
    if (this->m_ready_threads[current_priority].Empty())
    {
        this->m_priority_mask[current_priority / 32] &= ~(1 << (current_priority % 32));
    }
}

void hle::kd::Scheduler::AddThreadToDormantQueue(Thread * dormant_thread)
{
    this->m_stopped_threads.Append(dormant_thread);
    dormant_thread->m_status = Thread::STATUS_STOPPED;
}

void hle::kd::Scheduler::AddThreadToCleanupQueue(Thread * deletable_thread)
{
    this->m_stopped_threads.Append(deletable_thread);
    deletable_thread->m_status = Thread::STATUS_DELETABLE;
}

void hle::kd::Scheduler::ElectNextReadyThread(int priority)
{
    Thread *next_thread = this->m_ready_threads[priority].First();
    if (!(this->m_ready_threads[priority].Empty()) && next_thread == this->m_ready_threads[priority].Last())
    {
        this->m_priority_mask[priority / 32] &= ~(1 << (priority % 32));
    }
    next_thread->RemoveFromList();
    this->m_elected_thread = next_thread;
    next_thread->m_status = Thread::STATUS_RUN;
}

int hle::kd::Scheduler::SuspendDispatchThread(int intr)
{
    if (!intr)
    {
        return SCE_KERNEL_ERROR_CPUDI;
    }

    if (!this->m_dispatch_thread_suspended)
    {
        this->m_dispatch_thread_suspended = 1;
        return 1;
    }
    return 0;
}

int hle::kd::Scheduler::ResumeDispatchThread(int old, int intr)
{
    if (!intr)
    {
        return SCE_KERNEL_ERROR_CPUDI;
    }

    if (old)
    {
        if (this->m_dispatch_thread_suspended)
        {
            switch (this->m_dispatch_thread_suspended)
            {
                case 1: // running thread
                    this->m_dispatch_thread_suspended = 0;
                    break;
                case 2: // running thread must be now suspended (deferred operation)
                    this->m_dispatch_thread_suspended = 0;
                    g_scheduler->m_suspended_threads.Append(this->m_current_thread);
                    this->m_current_thread->m_status = Thread::STATUS_SUSPEND;
                    break;
                case 3: // running thread must be now killed (deferred operation)
                    this->m_dispatch_thread_suspended = 0;
                    this->m_current_thread->Exit(SCE_KERNEL_ERROR_THREAD_TERMINATED, intr, true);
                    break;
                default:
                    return SCE_KERNEL_ERROR_OK;
            }

            g_scheduler->m_elected_thread = 0;

            this->m_current_thread->ReleaseWait(0, intr);
        }
    }
    else if (this->m_dispatch_thread_suspended)
    {
        this->m_dispatch_thread_suspended = 0;
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Scheduler::RotateThreadReadyQueue(int priority, int intr, int is_intr_context)
{
    if (is_intr_context)
    {
        if (priority == 0)
        {
            int i, bit;
            for (i = 0; i < (MAX_THREAD_PRIORITY + 1) / 32; i++)
            {
                int mask = this->m_priority_mask[i];
                if (mask != 0)
                {
                    for (bit = 0; bit < 31; bit++)
                    {
                        if (mask & (1 << bit))
                        {
                            break;
                        }
                    }
                    priority = i * 32 + bit;
                    break;
                }
            }

            if (i == (MAX_THREAD_PRIORITY + 1) / 32)
            {
                priority = MAX_THREAD_PRIORITY + 1;
            }
        }
    }
    else if (priority == 0)
    {
        priority = GetCurrentThread()->m_current_priority;
    }

    if (!this->m_ready_threads[priority].Empty())
    {
        if (priority == GetCurrentThread()->m_current_priority && !g_scheduler->m_dispatch_thread_suspended)
        {
            if (is_intr_context)
            {
                AddThreadToReadyQueue(this->m_current_thread);
                this->m_elected_thread = 0;
            }
            else if (intr)
            {
                AddThreadToReadyQueue(this->m_current_thread);
                this->m_elected_thread = 0;

                this->m_current_thread->ReleaseWait(0, intr);
            }
            else
            {
                this->m_elected_thread = 0;
            }
        }
    }

    return SCE_KERNEL_ERROR_OK;
}

void hle::kd::Scheduler::TriggerIntrSoft2()
{
    //theEmulator->EnqueueEvent(&m_intr_soft2);
}

#ifdef QT_CORE_LIB
u32 qt4_LogCategory::GetKernelThreadUid()
{
    Thread * logged_thread = 0;
    if (theKernelScheduler)
    {
        logged_thread = theKernelScheduler->GetCurrentThread();
    }
    return logged_thread ? logged_thread->GetUid() : 0;
}
#endif

