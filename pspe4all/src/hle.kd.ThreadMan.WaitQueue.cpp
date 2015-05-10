/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

#define MAX_THREAD_PRIORITY     127
#define MIN_THREAD_STACKSIZE    0x200
#define THREAD_KSTACKSIZE       0x800

char const * hle::kd::WaitQueue::m_object_type = "KernelWaitQueue";

void hle::kd::WaitQueue::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

hle::kd::WaitQueue::WaitQueue(char const * name, SceUInt attr)
:   Object(name)
,   m_attributes(attr)
,   m_waiters_count(0)
{
}

hle::kd::WaitQueue::~WaitQueue()
{
}

int hle::kd::WaitQueue::Delete(int /*intr*/)
{
    int count = ReleaseAllWaitingThreads(SCE_KERNEL_ERROR_WAIT_DELETE);

    __delete this;

    if (count)
    {
        ReleaseWait(false, 0);
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::WaitQueue::Cancel()
{
    int count = ReleaseAllWaitingThreads(SCE_KERNEL_ERROR_WAIT_CANCEL);

    if (count)
    {
        ReleaseWait(false, 0);
    }

    return count;
}


int hle::kd::WaitQueue::AddWaitingThread(Thread * current_thread, int wait_type, u64 time, SceUInt * timeout)
{
    current_thread->m_timeout_object = 0;
    current_thread->m_timeout        = 0;

    if (timeout)
    {
        int result = current_thread->RequestTimeout(time, (int *)timeout);
        if (!result)
        {
            return result;
        }
    }

    current_thread->m_status          = Thread::STATUS_WAIT;
    current_thread->m_wait_type       = wait_type;
    current_thread->m_wait_queue      = this;
    current_thread->m_callback_status = SCE_KERNEL_ERROR_OK;

    this->m_waiters_count++;

    if (!(this->m_attributes & WAITQUEUE_PRIORITY))
    {
        this->m_waiters_queue.Append(current_thread);
    }
    else
    {
        Thread * previous_thread;

        for (previous_thread = this->m_waiters_queue.First(); previous_thread; previous_thread = this->m_waiters_queue.Next(previous_thread))
        {
            if (previous_thread->m_current_priority > current_thread->m_current_priority)
            {
                current_thread->InsertInListBefore(previous_thread);

                break;
            }
        }

        if (!previous_thread)
        {
            this->m_waiters_queue.Append(current_thread);
        }
    }

    ReleaseWait(true, 1);

    return current_thread->m_callback_status;
}

int hle::kd::WaitQueue::Acquire() // TODO: not the appropriate name indeed
{
    return 0;
}

int hle::kd::WaitQueue::Release()
{
    this->m_waiters_count--;

    return 0;
}

bool hle::kd::WaitQueue::RemoveWaitingThread(Thread * this_thread)
{
    return this_thread->ReleaseWaitingThread();
}

void hle::kd::WaitQueue::RemoveWaitingThread(Thread * this_thread, int intr_context, int state)
{
    this_thread->ReleaseWaitingThread(intr_context, state);
}

void hle::kd::WaitQueue::InsertWaitingThread(Thread * this_thread)
{
    m_waiters_queue.InsertWaitingThread(this_thread);
}

void hle::kd::WaitQueue::ReleaseWait(bool released, int intr)
{
    Thread * current_thread;

    if (g_scheduler && (current_thread = g_scheduler->GetCurrentThread()))
    {
        g_scheduler->m_elected_thread = 0;
        current_thread->ReleaseWait(released, intr);
    }
}

u32 hle::kd::WaitQueue::ReleaseAllWaitingThreads(int reason)
{
    u32 count;

    Thread * waiting_thread;

    // for each thread in the wait queue, we wake them up
    for (count = 0; waiting_thread = this->m_waiters_queue.First(); ++count)
    {
        if (waiting_thread->ReleaseWaitingThread())
        {
            g_scheduler->AddThreadToReadyQueue(waiting_thread);
        }

        waiting_thread->m_callback_status = reason;
    }

    return count;
}