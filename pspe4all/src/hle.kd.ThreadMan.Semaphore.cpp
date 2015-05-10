/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

char const * hle::kd::Semaphore::m_object_type = "KernelSemaphore";

void hle::kd::Semaphore::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

hle::kd::Semaphore::Semaphore(char const * name, SceUInt attributes, int initial_count, int maximum_count, SceKernelSemaOptParam * opt_param)
:   WaitQueue(name, attributes)
,   m_initial_count(initial_count)
,   m_maximum_count(maximum_count)
,   m_current_count(initial_count)
,   m_opt_param(opt_param)
{
}

hle::kd::Semaphore::~Semaphore()
{

}


int hle::kd::Semaphore::Create(char const * name, SceUInt attributes, int initial_count, int maximum_count, SceKernelSemaOptParam * opt_param)
{
    auto * sem = new Semaphore(name, attributes, initial_count, maximum_count, opt_param);

    return sem->GetUid();
}


int hle::kd::Semaphore::Delete(int intr)
{
    return WaitQueue::Delete(intr);
}

int hle::kd::Semaphore::Signal(int count, int intr, int is_intr_context)
{
    return SCE_KERNEL_ERROR_OK;

#if 0
    int new_count = m_current_count + count;

    Thread * waiting_thread;

    for (waiting_thread = m_waiters_queue.First(); waiting_thread; waiting_thread = m_waiters_queue.Next(waiting_thread))
    {
        new_count -= waiting_thread->m_cb_arg1;
    }

    if (new_count > m_maximum_count)
    {
        return SCE_KERNEL_ERROR_SEMA_OVF;
    }

    m_current_count += count;

    Thread * this_thread, * last_thread;

    int ready_threads = 0;

    for (this_thread = this->m_waiters_queue.First(); this_thread;)
    {
        if (this_thread->m_cb_arg1 > m_current_count)
        {
            break;
        }

        m_current_count -= this_thread->m_cb_arg1;

        auto * next_thread = this->m_waiters_queue.Next(this_thread);

        if (this_thread->ReleaseWaitingThread())
        {
            g_scheduler->AddThreadToReadyQueue(this_thread);

            last_thread = this_thread;

            ++ready_threads;
        }

        this_thread = next_thread;
    }

    if (ready_threads == 1)
    {
        g_scheduler->RemoveThreadFromReadyQueue(last_thread);
        last_thread->SwitchTo(intr);
    }
    else if (ready_threads > 0)
    {
        g_scheduler->m_elected_thread = 0;

        if (is_intr_context)
        {
            g_scheduler->GetCurrentThread()->ReleaseWait(0, intr);
        }
    }

    return SCE_KERNEL_ERROR_OK;
#endif
}

int hle::kd::Semaphore::Wait(int count, SceUInt * timeout, bool check_callbacks, int intr)
{
    return SCE_KERNEL_ERROR_OK;

#if 0
    unsigned int result;

    if (intr == 0 || g_scheduler->m_dispatch_thread_suspended != 0)
    {
        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    if (count > this->m_maximum_count)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_COUNT;
    }

    SceKernelSysClock sysclock(theSysClock->Get());

    if (timeout)
    {
        sysclock += u64(*timeout);
    }

    bool is_waiting = false;

    do
    {
        auto * current_thread = g_scheduler->GetCurrentThread();

        if (check_callbacks && current_thread->m_callback_notify)
        {
            current_thread->DispatchCallbacks(intr);
        }

        bool is_fifo = !(this->m_attributes & WAITQUEUE_PRIORITY);

        if ((this->m_waiters_count <= 0) || is_fifo || (current_thread->m_current_priority < this->m_waiters_queue.First()->m_current_priority))
        {
            if (is_fifo)
            {
                is_waiting = true;
            }

            if (is_waiting || (this->m_current_count < count))
            {
                current_thread->m_cb_arg1 = count;
            }
            else
            {
                result = 0;

                this->m_current_count -= count;

                break;
            }
        }
        else
        {
            is_waiting = true;

            current_thread->m_cb_arg1 = count;
        }

        current_thread->m_check_callbacks = check_callbacks;

        result = WaitQueue::AddWaitingThread(current_thread, WAITTYPE_SEMA, sysclock, timeout);
    }
    while (check_callbacks && (result == SCE_KERNEL_ERROR_NOTIFY_CALLBACK));

    return result;
#endif
}

int hle::kd::Semaphore::Poll(int count)
{
    return SCE_KERNEL_ERROR_OK;

#if 0
    SceKernelCpuSuspendIntrScope intr;

    if (count > this->m_maximum_count)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_COUNT;
    }

    auto * current_thread = g_scheduler->GetCurrentThread();

    if ((this->m_waiters_count > 0 && (!(this->m_attributes & WAITQUEUE_PRIORITY) || current_thread->m_current_priority >= this->m_waiters_queue.First()->m_current_priority)) || this->m_current_count < count)
    {
        return SCE_KERNEL_ERROR_SEMA_ZERO;
    }

    this->m_current_count -= count;

    return 0;
#endif
}

int hle::kd::Semaphore::Cancel(int count, int * waiters)
{
    SceKernelCpuSuspendIntrScope intr;

    if (count > this->m_maximum_count)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_COUNT;
    }

    int result = WaitQueue::Cancel();

    if (count < 0)
    {
        count = this->m_initial_count;
    }

    this->m_current_count = count;

    if (waiters)
    {
        *waiters = result;
    }

    return 0;
}

int hle::kd::Semaphore::ReferStatus(SceKernelSemaInfo * info)
{
    SceKernelCpuSuspendIntrScope intr;

    size_t size = info->size < sizeof(SceKernelSemaInfo) ? info->size : sizeof(SceKernelSemaInfo);

    if (size >= sizeof(SceKernelStructureSize))
    {
        ::memset(info, 0, size);

        info->size = sizeof(SceKernelSemaInfo);

        if (size >= sizeof(SceKernelStructureName))
        {
            if (this->m_name)
            {
                ::strncpy(info->name, this->m_name, sizeof(this->m_name) - 1);
            }

            if (size >= sizeof(SceKernelStructureAttr))
            {
                info->attributes = this->m_attributes;

                if (size >= sizeof(SceKernelSemaInfo))
                {
                    info->initial_count   = this->m_initial_count;
                    info->current_count   = this->m_current_count;
                    info->maximum_count   = this->m_maximum_count;
                    info->waiting_threads = this->m_waiters_count;
                }
            }
        }
    }

    return 0;
}
