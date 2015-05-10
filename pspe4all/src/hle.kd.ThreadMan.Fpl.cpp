/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

char const * hle::kd::Fpl::m_object_type = "KernelFpl";

void hle::kd::Fpl::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

hle::kd::Fpl::Fpl(SceUID heap_uid, SceUInt attributes, SceSize block_size, int block_count, SceKernelFplOptParam * opt_param, char const * name)
:   WaitQueue(name, attributes)
,   m_pool_blocks(block_count)
,   m_free_blocks(block_count)
,   m_block_size(block_size)
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

hle::kd::Fpl::~Fpl()
{
}


int hle::kd::Fpl::Create(char const * name, SceUID pid, SceUInt attributes, SceSize block_size, int block_count, SceKernelFplOptParam * opt_param, int intr)
{
    int result = 0;

    KernelHeap * heap = KernelHeap::Create(pid, block_size * SceSize(block_count), 0, "FPL");

    result = heap->GetUid();

    if (result > 0)
    {
        Fpl * fpl = new Fpl(SceUID(result), attributes, block_size, block_count, opt_param, name);

        result = fpl->GetUid();

        if (result <= 0)
        {
            heap->Delete(intr);
        }
    }

    return result;
}


int hle::kd::Fpl::Delete(int intr)
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

int hle::kd::Fpl::TryAllocate(u32 & addr)
{
    KernelHeap * heap;

    addr = 0;

    int result = Objects.Get(m_heap_uid, heap);
    if (SCE_KERNEL_ERROR_OK == result)
    {
        addr = heap->AllocMemoryWithOption(m_block_size, 0);

        if (addr)
        {
            if (this->m_free_blocks-- == 0)
            {
                this->m_free_blocks += this->m_pool_blocks;
            }
        }
    }

    return result;
}

int hle::kd::Fpl::Allocate(u32 &addr, int * /*timeout*/, bool /*cb*/)
{
    return TryAllocate(addr);
}

int hle::kd::Fpl::Free(u32 addr)
{
    KernelHeap * heap;

    int result = Objects.Get(m_heap_uid, heap);

    if (SCE_KERNEL_ERROR_OK == result)
    {
        result = heap->FreeMemory(addr);
        if (!result) this->m_free_blocks++;
    }

    return result;
}

int hle::kd::Fpl::Cancel(int * waiting_threads)
{
    if (waiting_threads)
    {
        *waiting_threads = this->m_waiters_count;
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Fpl::ReferStatus(SceKernelFplInfo * info)
{
    int size = info->size < sizeof(SceKernelFplInfo) ? info->size : sizeof(SceKernelFplInfo);

    if (size >= sizeof(SceKernelStructureSize))
    {
        ::memset(info, 0, size);

        info->size = sizeof(SceKernelFplInfo);

        if (size >= sizeof(SceKernelStructureName))
        {
            if (this->m_name)
            {
                ::strncpy(info->name, this->m_name, sizeof(this->m_name) - 1);
            }

            if (size >= sizeof(SceKernelStructureAttr))
            {
                info->attributes = this->m_attributes;

                if (size >= sizeof(SceKernelFplInfo))
                {
                    info->block_size      = this->m_block_size;
                    info->pool_blocks     = this->m_pool_blocks;
                    info->free_blocks     = this->m_free_blocks;
                    info->waiting_threads = this->m_waiters_count;
                }
            }
        }
    }

    return SCE_KERNEL_ERROR_OK;
}
