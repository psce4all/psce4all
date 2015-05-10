/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifndef hle_kd_SysMem_h__
#error you must include "hle.kd.SysMem.h" instead
#endif

namespace hle
{
    namespace kd
    {
        /// KernelPartition /////////////////////////////////////////////////////////

        struct Partition : Object, hal::hmm::Allocator< Partition >
        {
            declare_kernel_type(Partition, Object);

            typedef std::map< u32, PartitionBlock * > PartitionUsedBlockMap;
            typedef std::map< u32, u32              > PartitionFreeBlockMap;

            u32                                 m_base_address;
            u32                                 m_size;
            u32                                 m_attributes;
            u32                                 m_free_size;
            PartitionUsedBlockMap               m_used_blocks;
            PartitionFreeBlockMap               m_free_blocks;

            /**/                                Partition(u32 base_address, u32 size, u32 attributes, char const * name = "");
            /**/                               ~Partition();

            int                                 Delete(int intr);
            static Partition                  * Get(SceUID id);

            static bool                         Initialize();
            static bool                         Terminate();

            static inline u32                   LowerBound(PartitionBlock * block)
            {
                return block->m_address;
            }
            static inline u32                   LowerBound(PartitionUsedBlockMap::iterator & iter)
            {
                return iter->second->m_address;
            }
            static inline u32                   LowerBound(PartitionFreeBlockMap::iterator & iter)
            {
                return iter->first;
            }
            static inline u32                   LowerBound(PartitionFreeBlockMap::reverse_iterator & iter)
            {
                return iter->first;
            }

            static inline u32                   UpperBound(PartitionBlock * block)
            {
                return block->m_address + block->m_size;
            }
            static inline u32                   UpperBound(PartitionUsedBlockMap::iterator & iter)
            {
                return iter->second->m_address + iter->second->m_size;
            }
            static inline u32                 & UpperBound(PartitionFreeBlockMap::iterator & iter)
            {
                return iter->second;
            }
            static inline u32                 & UpperBound(PartitionFreeBlockMap::reverse_iterator & iter)
            {
                return iter->second;
            }

            static inline u32                   Length(PartitionBlock * block)
            {
                return block->m_size;
            }
            static inline u32                   Length(PartitionUsedBlockMap::iterator & iter)
            {
                return iter->second->m_size;
            }
            static inline u32                   Length(PartitionFreeBlockMap::iterator & iter)
            {
                return iter->second - iter->first;
            }
            static inline u32                   Length(PartitionFreeBlockMap::reverse_iterator & iter)
            {
                return iter->second - iter->first;
            }

            bool                                AllocatePartitionBlock(char const name[32], int type, u32 address, u32 size, PartitionBlock *& that);
            bool                                ResizePartitionBlock(u32 head, u32 tail, PartitionBlock *& that);
            void                                FreePartitionBlock(PartitionBlock * that);
        };
    }

    typedef kd::Partition KernelPartition;
}
