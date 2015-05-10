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
        struct Heap;
        struct PartitionBlock;

        /// KernelHeapBlock /////////////////////////////////////////////////////////

        struct HeapBlock
        {
            friend struct PartitionBlock;

            Heap           & m_heap;
            PartitionBlock & m_partition_block;
            u32              m_address;
            u32              m_size;

            /**/             HeapBlock(Heap & heap, PartitionBlock & memory_block, u32 address, u32 size);
            /**/            ~HeapBlock();

        private:
            HeapBlock & operator = (HeapBlock const &) = delete;
        };

        /// KernelPartitionBlock ////////////////////////////////////////////////////

        struct PartitionBlock : Object, hal::LinkedList< PartitionBlock >::Node
        {
            declare_kernel_type(PartitionBlock, Object);

            friend struct Partition;

            typedef std::map< u32, HeapBlock * > HeapUsedBlockMap;
            typedef std::map< u32, u32         > HeapFreeBlockMap;

            Partition         & m_partition;
            u32                 m_address;
            u32                 m_size;
            Heap              * m_heap;

            HeapUsedBlockMap    m_used_blocks;
            HeapFreeBlockMap    m_free_blocks;

            PartitionBlock(Partition & partition, u32 address, u32 size, char const * name = 0);
            ~PartitionBlock();

            static inline u32   LowerBound(HeapBlock * block)
            {
                return block->m_address;
            }
            static inline u32   LowerBound(HeapUsedBlockMap::iterator & iter)
            {
                return iter->second->m_address;
            }
            static inline u32   LowerBound(HeapFreeBlockMap::iterator & iter)
            {
                return iter->first;
            }
            static inline u32   LowerBound(HeapFreeBlockMap::reverse_iterator & iter)
            {
                return iter->first;
            }

            static inline u32   UpperBound(HeapBlock * block)
            {
                return block->m_address + block->m_size;
            }
            static inline u32   UpperBound(HeapUsedBlockMap::iterator & iter)
            {
                return iter->second->m_address + iter->second->m_size;
            }
            static inline u32 & UpperBound(HeapFreeBlockMap::iterator & iter)
            {
                return iter->second;
            }
            static inline u32 & UpperBound(HeapFreeBlockMap::reverse_iterator & iter)
            {
                return iter->second;
            }

            static inline u32   Length(HeapBlock * block)
            {
                return block->m_size;
            }
            static inline u32   Length(HeapUsedBlockMap::iterator & iter)
            {
                return iter->second->m_size;
            }
            static inline u32   Length(HeapFreeBlockMap::iterator & iter)
            {
                return iter->second - iter->first;
            }
            static inline u32   Length(HeapFreeBlockMap::reverse_iterator & iter)
            {
                return iter->second - iter->first;
            }

            int                 Delete(int intr);
            bool                AllocateHeapBlock(Heap & heap, u32 size, u32 alignment, HeapBlock *& that);
            void                FreeHeapBlock(Heap & heap, HeapBlock * that);
            bool                FreeHeapBlock(Heap & heap, u32 address);

        private:
            PartitionBlock & operator = (PartitionBlock const &) = delete;
        };
    }

    typedef kd::HeapBlock      KernelHeapBlock;
    typedef kd::PartitionBlock KernelPartitionBlock;
}
