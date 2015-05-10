/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

/// KernelHeap //////////////////////////////////////////////////////////////

char const * hle::kd::Heap::m_object_type = "KernelHeap";

void hle::kd::Heap::GetQuickInfos(char * data, size_t size)
{
    ::snprintf(data, size, "{ #%d, %d }", m_partition.GetUid(), m_size);
}

hle::kd::Heap::Heap(Partition & partition, SceSize size, SceUInt attribute, char const * name)
:   Object(name)
,   m_partition(partition)
,   m_size((u32)size)
,   m_type((u32)(attribute>>1)&1)
{
    PartitionBlock * block;

    if (m_partition.AllocatePartitionBlock(name, m_type, 0, m_size, block))
    {
        block->m_heap = this;
        m_partition_blocks.Append(block);
    }
    else
    {
        m_uid = SCE_KERNEL_ERROR_HEAPBLOCK_ALLOC_FAILED;
    }
}

hle::kd::Heap::~Heap()
{
}

hle::kd::Heap * hle::kd::Heap::Create(SceUID uid, SceSize size, int attr, const char * name)
{
    Partition * partition = Partition::Get(uid);

    if (!partition)
    {
        return 0;
    }

    return new Heap(*partition, size, attr, name);
}

int hle::kd::Heap::Delete(int intr)
{
    PartitionBlock * block;

    while (block = this->m_partition_blocks.First())
    {
        block->Delete(intr);
    }

    this->m_partition_blocks.ClearList();

    delete this;

    return SCE_KERNEL_ERROR_OK;
}

u32 hle::kd::Heap::AllocMemoryWithOption(SceSize size, SceKernelHeapOptParam * option)
{
    PartitionBlock * block = m_partition_blocks.First();

    for (;;)
    {
        for (; block; block = m_partition_blocks.Next(block))
        {
            HeapBlock * heap_block = 0;

            if (block->AllocateHeapBlock(*this, size, (option ? option->alignment : 0), heap_block))
            {
                return (u32)heap_block->m_address;
            }
        }

        if (!m_partition.AllocatePartitionBlock(GetName(), m_type, 0, m_size, block))
        {
            break;
        }

        block->m_heap = this;
        m_partition_blocks.Append(block);
    }

    return 0;
}

u32 hle::kd::Heap::AllocMemory(SceSize size)
{
    return AllocMemoryWithOption(size, 0);
}

int hle::kd::Heap::FreeMemory(u32 address)
{
    PartitionBlock * block = m_partition_blocks.First();

    for (; block; block = m_partition_blocks.Next(block))
    {
        if (block->FreeHeapBlock(*this, address))
        {
            return SCE_KERNEL_ERROR_OK;
        }
    }

    return SCE_KERNEL_ERROR_ILLEGAL_ADDRESS;
}

SceSize hle::kd::Heap::TotalFreeSize()
{
    u32 max_size = 0;

    PartitionBlock * block = m_partition_blocks.First();

    for (; block; block = m_partition_blocks.Next(block))
    {
        for (PartitionBlock::HeapFreeBlockMap::iterator i = block->m_free_blocks.begin(); i != block->m_free_blocks.end(); ++i)
        {
            max_size += PartitionBlock::Length(i);
        }
    }

    return max_size;
}
