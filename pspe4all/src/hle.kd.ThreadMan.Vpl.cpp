/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

char const * hle::kd::Vpl::m_object_type = "KernelVpl";

void hle::kd::Vpl::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

hle::kd::Vpl::Vpl(SceUID heap_uid, SceUInt attributes, SceSize size, SceKernelVplOptParam * opt_param, char const * name)
:   WaitQueue(name, attributes)
,   m_pool_size(size)
,   m_free_size(size)
,   m_heap_uid(heap_uid)
{
    if (opt_param)
    {
        m_opt_param = *opt_param;
    }
    else
    {
        memset(&m_opt_param, 0, sizeof(m_opt_param));
    }
}

hle::kd::Vpl::~Vpl()
{
}

int hle::kd::Vpl::Create(char const * name, SceUID pid, SceUInt attributes, SceSize size, SceKernelVplOptParam * opt_param, int intr)
{
    int result = 0;

    auto * heap = Heap::Create(pid, size, (attributes & SCE_KERNEL_VA_MEMBTM) >> 13, name);

    result = heap->GetUid();

    if (result > 0)
    {
        auto * vpl = new Vpl(SceUID(result), attributes, size, opt_param, name);

        result = vpl->GetUid();

        if (result <= 0)
        {
            delete vpl;
        }

        //vpl->m_free_size = heap->TotalFreeSize();
    }
    else
    {
        heap->Delete(intr);
    }

    return result;
}

int hle::kd::Vpl::Delete(int intr)
{
    KernelHeap * heap;

    int result = Objects.Get(m_heap_uid, heap);
    if (SCE_KERNEL_ERROR_OK == result)
    {
        heap->Delete(intr);

        delete this;
    }

    return result;
}

int hle::kd::Vpl::Allocate(SceSize size, u32 &addr, SceUInt * timeout, bool cb, int intr)
{
    int result;

    if (size == 0 || SceSize(m_pool_size) < size)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_MEMSIZE;
    }

    auto * this_thread = g_scheduler->GetCurrentThread();

    SceKernelSysClock sysclock(theSysClock->Get());

    if (timeout)
    {
        sysclock += u64(*timeout);
    }

    do
    {
        if (cb && this_thread->m_callback_notify != 0)
        {
            this_thread->DispatchCallbacks(intr);
        }

        KernelHeap * heap;

        if (!Objects.Get(m_heap_uid, heap))
        {
            u32 block = heap->AllocMemoryWithOption(size, 0);
            if (block)
            {
                addr = block;
                return SCE_KERNEL_ERROR_OK;
            }
        }

        this_thread->m_cb_arg2 = int(size);
        this_thread->m_check_callbacks = cb;

        result = this_thread->m_wait_queue->AddWaitingThread(this_thread, WaitQueue::WAITTYPE_VPL, sysclock, timeout);
        if (!result)
        {
            addr = this_thread->m_cb_arg1;
        }
    }
    while (cb && (result == SCE_KERNEL_ERROR_NOTIFY_CALLBACK));

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Vpl::TryAllocate(SceSize size, u32 & addr)
{
    if (size == 0 || (SceSize)this->m_pool_size < size)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_MEMSIZE;
    }

    KernelHeap * heap;

    if (!Objects.Get(m_heap_uid, heap))
    {
        u32 result = heap->AllocMemoryWithOption(size, 0);
        if (result)
        {
            addr = result;
            return SCE_KERNEL_ERROR_OK;
        }
    }

    return SCE_KERNEL_ERROR_NO_MEMORY;
}

int hle::kd::Vpl::Free(u32 addr, int intr)
{
    KernelHeap * heap;

    if (!Objects.Get(m_heap_uid, heap))
    {
        if (!heap->FreeMemory(addr))
        {
            Thread * this_thread, * last_thread = nullptr;

            int ready_threads = 0;

            for (this_thread = this->m_waiters_queue.First(); this_thread;)
            {
                u32 block = heap->AllocMemoryWithOption(SceSize(this_thread->m_cb_arg2), 0);
                if (block)
                {
                    this_thread->m_cb_arg1 = int(block);
                    this_thread->m_callback_status = SCE_KERNEL_ERROR_OK;

                    auto *next_thread = this->m_waiters_queue.Next(this_thread);

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
                g_scheduler->GetCurrentThread()->ReleaseWait(0, intr);
            }

            return SCE_KERNEL_ERROR_OK;
        }
    }

    return SCE_KERNEL_ERROR_NO_MEMORY;
}

int hle::kd::Vpl::Cancel(int * waiting_threads)
{
    int result = WaitQueue::Cancel();

    if (waiting_threads)
    {
        *waiting_threads = result;
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Vpl::ReferStatus(SceKernelVplInfo * info)
{
    u32 size = info->size < sizeof(SceKernelVplInfo) ? info->size : sizeof(SceKernelVplInfo);

    if (size >= sizeof(SceKernelStructureSize))
    {
        ::memset(info, 0, size);

        info->size = sizeof(SceKernelVplInfo);

        if (size >= sizeof(SceKernelStructureName))
        {
            if (this->m_name)
            {
                ::strncpy(info->name, this->m_name, sizeof(this->m_name) - 1);
            }

            if (size >= sizeof(SceKernelStructureAttr))
            {
                info->attributes = this->m_attributes;

                if (size >= sizeof(SceKernelVplInfo))
                {
                    Heap * heap;

                    int result = Objects.Get(this->m_heap_uid, heap);

                    info->pool_size       = this->m_pool_size;
                    info->free_size       = !result ? heap->TotalFreeSize() : 0;
                    info->waiting_threads = this->m_waiters_count;
                }
            }
        }
    }

    return SCE_KERNEL_ERROR_OK;
}
