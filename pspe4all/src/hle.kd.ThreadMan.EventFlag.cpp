/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

char const * hle::kd::EventFlag::m_object_type = "KernelEventFlag";

void hle::kd::EventFlag::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

hle::kd::EventFlag::EventFlag(char const * name, SceUInt attributes, SceUInt initial_pattern, SceKernelEventFlagOptParam * /*opt_param*/)
:   WaitQueue(name, attributes)
,   m_initial_pattern(initial_pattern)
,   m_current_pattern(initial_pattern)
{
}

hle::kd::EventFlag::~EventFlag()
{
}


int hle::kd::EventFlag::Create(char const * name, SceUInt attr, SceUInt initial_pattern, SceKernelEventFlagOptParam * opt_param)
{
    EventFlag * evf = new EventFlag(name, attr, initial_pattern, opt_param);

    return evf->GetUid();
}

int hle::kd::EventFlag::Delete(int /*intr*/)
{
    int count = m_waiters_count;

    delete this;

    if (count)
    {
        g_scheduler->m_elected_thread = 0;
        g_scheduler->GetCurrentThread()->ReleaseWait(false, 0);
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::EventFlag::Set(SceUInt pattern, int is_intr_context, int intr)
{
    if (pattern != 0)
    {
        this->m_current_pattern |= pattern;

        Thread * this_thread, * last_thread = nullptr;

        int ready_threads = 0;

        for (this_thread = this->m_waiters_queue.First(); this_thread;)
        {
            if (this->m_current_pattern == 0)
            {
                break;
            }

            int matched;
            int pattern  = this_thread->m_cb_arg1;
            int waitmode = this_thread->m_cb_arg2;

            if (waitmode & WAITMODE_OR)
            {
                matched = this->m_current_pattern & pattern;
            }
            else
            {
                matched = (this->m_current_pattern & pattern) == pattern;
            }

            if (matched)
            {
                if (this_thread->m_cb_arg3 != 0)
                {
                    *((p32< int >)this_thread->m_cb_arg3) = this->m_current_pattern;
                }

                if (waitmode & WAITMODE_CLEAR_ALL)
                {
                    this->m_current_pattern = 0;
                }
                else if (waitmode & WAITMODE_CLEAR_MATCHED)
                {
                    this->m_current_pattern &= ~pattern;
                }

                Thread * next_thread = this->m_waiters_queue.Next(this_thread);

                if (this_thread->ReleaseWaitingThread())
                {
                    g_scheduler->AddThreadToReadyQueue(this_thread);

                    last_thread = this_thread;

                    ++ready_threads;
                }

                this_thread = next_thread;
            }
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
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::EventFlag::Clear(SceUInt pattern)
{
    SceKernelCpuSuspendIntrScope intr;

    this->m_current_pattern &= pattern;

    return 0;
}

int hle::kd::EventFlag::Wait(SceUInt pattern, SceUInt waitmode, u32 result_pattern, SceUInt *timeout, bool is_cb, int intr)
{
    int result = 0;

    if (!(this->m_attributes & WAITATTR_MULTIPLE) && this->m_waiters_count > 0)
    {
        return SCE_KERNEL_ERROR_EVF_MULTI;
    }

    auto * this_thread = g_scheduler->GetCurrentThread();

    SceKernelSysClock sysclock(theSysClock->Get());

    if (timeout)
    {
        sysclock += u64(*timeout);
    }

    do
    {
        if (is_cb && this_thread->m_callback_notify != 0)
        {
            this_thread->DispatchCallbacks(intr);
        }

        u32 matched;

        if (waitmode & WAITMODE_OR)
        {
            matched = this->m_current_pattern & pattern;
        }
        else
        {
            matched = ((this->m_current_pattern & pattern) == pattern);
        }

        if (matched)
        {
            if (result_pattern)
            {
                *((p32< SceUInt >)result_pattern) = SceUInt(this->m_current_pattern);
            }

            if (waitmode & WAITMODE_CLEAR_ALL)
            {
                this->m_current_pattern = 0;
            }
            else if (waitmode & WAITMODE_CLEAR_MATCHED)
            {
                this->m_current_pattern &= ~pattern;
            }

            return 0;
        }

        this_thread->m_cb_arg1         = int(pattern);
        this_thread->m_cb_arg2         = int(waitmode);
        this_thread->m_cb_arg3         = int(result_pattern);
        this_thread->m_check_callbacks = is_cb;

        result = this_thread->m_wait_queue->AddWaitingThread(this_thread, WaitQueue::WAITTYPE_EVENTFLAG, sysclock, timeout);
    }
    while (is_cb && (result == SCE_KERNEL_ERROR_NOTIFY_CALLBACK));

    if (result > 0 && result_pattern)
    {
        *((p32< SceUInt >)result_pattern) = SceUInt(this->m_current_pattern);
    }

    return result;
}


int hle::kd::EventFlag::Poll(SceUInt pattern, SceUInt waitmode, u32 result_pattern)
{
    if (!(this->m_attributes & WAITATTR_MULTIPLE) && this->m_waiters_count > 0)
    {
        return SCE_KERNEL_ERROR_EVF_MULTI;
    }

    u32 matched;

    if (waitmode & WAITMODE_OR)
    {
        matched = this->m_current_pattern & pattern;
    }
    else
    {
        matched = ((this->m_current_pattern & pattern) == pattern);
    }

    if (result_pattern)
    {
        *((p32< SceUInt >)result_pattern) = SceUInt(this->m_current_pattern);
    }

    if (matched == 0)
    {
        return SCE_KERNEL_ERROR_EVF_COND;
    }

    if (waitmode & WAITMODE_CLEAR_ALL)
    {
        this->m_current_pattern = 0;
    }
    else if (waitmode & WAITMODE_CLEAR_MATCHED)
    {
        this->m_current_pattern &= ~pattern;
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::EventFlag::Cancel(SceUInt pattern, int * waiters)
{
    int result = WaitQueue::Cancel();

    this->m_current_pattern = pattern;

    if (waiters)
    {
        *waiters = result;
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::EventFlag::ReferStatus(SceKernelEventFlagInfo * info)
{
    u32 size = info->size < sizeof(SceKernelEventFlagInfo) ? info->size : sizeof(SceKernelEventFlagInfo);

    if (size >= sizeof(SceKernelStructureSize))
    {
        ::memset(info, 0, size);

        info->size = sizeof(SceKernelEventFlagInfo);

        if (size >= sizeof(SceKernelStructureName))
        {
            if (this->m_name)
            {
                ::strncpy(info->name, this->m_name, sizeof(this->m_name) - 1);
            }

            if (size >= sizeof(SceKernelStructureAttr))
            {
                info->attributes = this->m_attributes;

                if (size >= sizeof(SceKernelEventFlagInfo))
                {
                    info->initial_pattern = this->m_initial_pattern;
                    info->current_pattern = this->m_current_pattern;
                    info->waiting_threads = this->m_waiters_count;
                }
            }
        }
    }

    return 0;
}
