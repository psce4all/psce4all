/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

namespace hle
{
    namespace kd
    {
        /// KernelPartitionBlock ///////////////////////////////////////////////////////

        char const * PartitionBlock::m_object_type = "KernelPartitionBlock";

        void PartitionBlock::GetQuickInfos(char * data, size_t size)
        {
            ::snprintf(data, size, "{ #%d, %08X-%08X }", m_partition.GetUid(), m_address, m_address + m_size);
        }

        PartitionBlock::PartitionBlock(Partition & partition, u32 address, u32 size, char const * name)
        : Object(name)
        , m_partition(partition)
        , m_address(address)
        , m_size(size)
        , m_heap(0)
        {
            m_free_blocks[address] = address + size;
        }

        PartitionBlock::~PartitionBlock()
        {
        }

        int PartitionBlock::Delete(int /*intr*/)
        {
            while (m_used_blocks.size())
            {
                delete m_used_blocks.begin()->second;
            }

            if (m_heap)
            {
                this->RemoveFromList();
                m_heap = 0;
            }

            m_partition.FreePartitionBlock(this);

            delete this;

            return SCE_KERNEL_ERROR_OK;
        }


        bool PartitionBlock::AllocateHeapBlock(Heap & heap, u32 size, u32 alignment, HeapBlock *& that)
        {
            if (alignment && ((alignment & 3) || (alignment > 128) || (alignment & (alignment - 1))))
            {
                return false;
            }

            if (heap.m_type < 2)
            {
                switch (heap.m_type)
                {
                    case 0: // heap-like allocation with alignment
                    {
                        size = (size + 3) & ~3;

                        for (HeapFreeBlockMap::iterator free = m_free_blocks.begin(); free != m_free_blocks.end(); ++free)
                        {
                            u32 lb = LowerBound(free);
                            u32 ub = UpperBound(free);

                            u32 address = (lb + alignment) & ~alignment;

                            if ((address < ub) && (address + size <= ub))
                            {
                                m_used_blocks[address] = that = __new HeapBlock(heap, *this, address, size);

                                m_free_blocks.erase(free);

                                lb = UpperBound(that);

                                if (lb < ub)
                                {
                                    m_free_blocks[lb] = ub;
                                }

                                heap.m_heap_blocks[address] = that;

                                this->m_heap = &heap;

                                return true;
                            }
                        }
                    }
                        break;

                    case 1: // stack-like allocation with alignment
                    {
                        size = (size + 3) & ~3;

                        for (HeapFreeBlockMap::reverse_iterator free = m_free_blocks.rbegin(); free != m_free_blocks.rend(); ++free)
                        {
                            u32 lb = LowerBound(free);
                            u32 ub = UpperBound(free);

                            u32 address = ub & ~alignment;

                            if ((lb < address) && (lb <= address - size))
                            {
                                address -= size;

                                m_used_blocks[address] = that = __new HeapBlock(heap, *this, address, size);

                                if (lb == address)
                                {
                                    m_free_blocks.erase(lb);
                                }
                                else
                                {
                                    UpperBound(free) = address;
                                }

                                heap.m_heap_blocks[address] = that;

                                return true;
                            }
                        }
                    }
                        break;
                }
            }
            return false;
        }

        bool PartitionBlock::FreeHeapBlock(Heap & heap, u32 address)
        {
            HeapUsedBlockMap::iterator used = m_used_blocks.find(address);

            if (used != m_used_blocks.end())
            {
                HeapFreeBlockMap::iterator next = m_free_blocks.lower_bound(UpperBound(used));
                HeapFreeBlockMap::iterator prev = next;

                --prev;

                u32 lb = LowerBound(used);
                u32 ub = UpperBound(used);

                if ((prev != m_free_blocks.end()) && (lb == UpperBound(prev)))
                {
                    UpperBound(prev) = ub;

                    if ((next != m_free_blocks.end()) && (LowerBound(next) == ub))
                    {
                        UpperBound(prev) = UpperBound(next);

                        m_free_blocks.erase(next);
                    }
                }
                else if ((next != m_free_blocks.end()) && (LowerBound(next) == ub))
                {
                    m_free_blocks[lb] = UpperBound(next);
                    m_free_blocks.erase(next);
                }
                else
                {
                    m_free_blocks[lb] = ub;
                }

                heap.m_heap_blocks.erase(lb);

                m_used_blocks.erase(used);

                return true;
            }

            return false;
        }

        void PartitionBlock::FreeHeapBlock(Heap & heap, HeapBlock * that)
        {
            FreeHeapBlock(heap, LowerBound(that));
        }

        /// KernelHeapBlock /////////////////////////////////////////////////////////

        HeapBlock::HeapBlock(Heap & heap, PartitionBlock & memory_block, u32 address, u32 size)
        : m_heap(heap)
        , m_partition_block(memory_block)
        , m_address(address)
        , m_size(size)
        {
        }

        HeapBlock::~HeapBlock()
        {
            m_partition_block.FreeHeapBlock(m_heap, this);
        }
    }
}
