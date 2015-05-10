/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

namespace hle
{
    namespace kd
    {
        static Partition * kernel_partitions[11] =
        {
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0
        };

        static Partition * MapKernelPartition(u32 lower_bound, u32 upper_bound, u32 attributes, char const * name)
        {
            Partition * partition = new Partition(lower_bound, upper_bound - lower_bound, attributes, name);

            if (partition->GetUid() <= 0)
            {
                partition->Delete(0);
                partition = 0;
            }

            return partition;
        }

        bool Partition::Initialize()
        {
            // we only consider partitions in GAME mode, not in VSH mode
            kernel_partitions[0]  = 0;
            kernel_partitions[1]  = MapKernelPartition(0x88000000, 0x88300000, 0x0C, "Kernel Partition (3MB)");
            kernel_partitions[2]  = MapKernelPartition(0x08800000, 0x0A000000, 0x0F, "User Partition (24MB)");
            kernel_partitions[3]  = kernel_partitions[1];
            kernel_partitions[4]  = MapKernelPartition(0x88300000, 0x88400000, 0x0C, "Other Kernel Partition (1MB)");
            kernel_partitions[5]  = MapKernelPartition(0x08400000, 0x08800000, 0x0F, "Volatile Partition (4MB)");
            kernel_partitions[6]  = kernel_partitions[2];
            kernel_partitions[7]  = 0;
            kernel_partitions[8]  = MapKernelPartition(0x8A000000, 0x8BC00000, 0x0C, "UMD Cache Partition (28MB)");
            kernel_partitions[9]  = 0;
            kernel_partitions[10] = MapKernelPartition(0x8BC00000, 0x8C000000, 0x0C, "ME Partition (4MB)");

            return true;
        }

        bool Partition::Terminate()
        {
            Partition * partition = 0, * next;

            for (partition = Objects.Next(partition); partition; partition = next)
            {
                next = Objects.Next(partition);

                partition->Delete(0);
            }

            ::memset(kernel_partitions, 0, sizeof(kernel_partitions));

            return true;
        }

        /// KernelPartition /////////////////////////////////////////////////////////

        char const * Partition::m_object_type = "KernelPartition";

        Partition * Partition::Get(SceUID id)
        {
            switch (id)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    return kernel_partitions[id];
            }

            Partition * partition;

            if (!Objects.Get(id, partition))
            {
                return partition;
            }

            return 0;
        }

        void Partition::GetQuickInfos(char * data, size_t size)
        {
            ::snprintf(data, size, "{ %08X-%08X, %d }", m_base_address, m_base_address + m_size, m_free_size);
        }

        Partition::Partition(u32 base_address, u32 size, u32 attributes, char const * name)
        :   Object(name)
        ,   m_base_address(base_address)
        ,   m_size(size)
        ,   m_attributes(attributes)
        ,   m_free_size(size)
        {
            m_free_blocks[base_address] = base_address + size;
        }

        Partition::~Partition()
        {
        }

        int Partition::Delete(int intr)
        {
            while (m_used_blocks.size())
            {
                m_used_blocks.begin()->second->Delete(intr);
            }

            delete this;

            return SCE_KERNEL_ERROR_OK;
        }

        bool Partition::AllocatePartitionBlock(char const name[32], int type, u32 address, u32 size, PartitionBlock *& that)
        {
            if (type == 2)
            {
                assert((address & 255) == 0);
            }

            if (size)
            {
                if ((type < 5) && (size <= m_free_size))
                {
                    switch (type)
                    {
                        case 0: // heap-like allocation
                        case 3: // heap-like allocation with alignment
                        {
                            u32 alignment = (type == 3) ? (address - 1) : 255;

                            assert(alignment >= 255);

                            size = (size + alignment) & ~alignment;

                            for (PartitionFreeBlockMap::iterator free = m_free_blocks.begin(); free != m_free_blocks.end(); ++free)
                            {
                                u32 lb = LowerBound(free);
                                u32 ub = UpperBound(free);

                                address = (lb + alignment) & ~alignment;

                                if ((address < ub) && (address + size <= ub))
                                {
                                    m_used_blocks[address] = that = __new PartitionBlock(*this, address, size, name);

                                    m_free_blocks.erase(free);

                                    lb = UpperBound(that);

                                    if (lb < ub)
                                    {
                                        m_free_blocks[lb] = ub;
                                    }

                                    m_free_size -= size;

                                    return true;
                                }
                            }
                        }
                            break;

                        case 1: // stack-like allocation
                        case 4: // stack-like allocation with alignment
                        {
                            u32 alignment = (type == 4) ? (address - 1) : 255;

                            assert(alignment >= 255);

                            size = (size + alignment) & ~alignment;

                            for (PartitionFreeBlockMap::reverse_iterator free = m_free_blocks.rbegin(); free != m_free_blocks.rend(); ++free)
                            {
                                u32 lb = LowerBound(free);
                                u32 ub = UpperBound(free);

                                address = ub & ~alignment;

                                if ((lb < address) && (lb <= address - size))
                                {
                                    address -= size;

                                    m_used_blocks[address] = that = __new PartitionBlock(*this, address, size, name);

                                    if (lb == address)
                                    {
                                        m_free_blocks.erase(lb);
                                    }
                                    else
                                    {
                                        UpperBound(free) = address;
                                    }

                                    m_free_size -= size;

                                    return true;
                                }
                            }
                        }
                            break;

                        case 2: // specific address allocation
                        {
                            address &= ~255;
                            size = (size + 255) & ~255;

                            PartitionFreeBlockMap::iterator free = m_free_blocks.lower_bound(address + size);

                            if (--free != m_free_blocks.end())
                            {
                                u32 lb = LowerBound(free);
                                u32 ub = UpperBound(free);

                                if ((lb <= address) && (address + size <= ub))
                                {
                                    m_used_blocks[address] = that = __new PartitionBlock(*this, address, size, name);

                                    if (lb < LowerBound(that))
                                    {
                                        UpperBound(free) = LowerBound(that);
                                    }
                                    else
                                    {
                                        m_free_blocks.erase(free);
                                    }

                                    if (UpperBound(that) < ub)
                                    {
                                        m_free_blocks[UpperBound(that)] = ub;
                                    }

                                    m_free_size -= size;

                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }

        bool Partition::ResizePartitionBlock(u32 head, u32 tail, PartitionBlock *& that)
        {
            // this function is not highly optimized but not used in official games anyway
            bool result = true;
            u32 new_size = (tail - (head & ~255) + 255) & ~255;
            if (new_size)
            {
                u32  old_address = that->m_address;
                u32  old_size    = that->m_size;
                u32  new_address = (old_address + head) & ~255;
                char name[32];
                ::memcpy(name, that->GetName(), 32);

                FreePartitionBlock(that);
                int result = AllocatePartitionBlock(name, 2, new_address, new_size, that);
                if (result != SCE_KERNEL_ERROR_OK)
                {
                    result = AllocatePartitionBlock(name, 2, old_address, old_size, that);
                }
            }
            return result;
        }

        void Partition::FreePartitionBlock(PartitionBlock * that)
        {
            PartitionUsedBlockMap::iterator used = m_used_blocks.find(LowerBound(that));

            if (used != m_used_blocks.end())
            {
                m_free_size += Length(used);

                PartitionFreeBlockMap::iterator next = m_free_blocks.lower_bound(UpperBound(used));
                PartitionFreeBlockMap::iterator prev = next;

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
            }

            m_used_blocks.erase(used);
        }
    }
}
