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
        struct Partition;
        struct PartitionBlock;

        /// KernelHeap //////////////////////////////////////////////////////////////

        struct Heap : Object, hal::hmm::Allocator< Heap >
        {
            declare_kernel_type(Heap, Object);

            Partition                       & m_partition;
            u32                               m_size;
            u32                               m_type;
            hal::LinkedList< PartitionBlock > m_partition_blocks;
            PartitionBlock::HeapUsedBlockMap  m_heap_blocks;

            /**/                              Heap(Partition & partition, SceSize size, SceUInt attribute, char const * name);
            /**/                             ~Heap();

            static Heap                     * Create(SceUID uid, SceSize size, int attr, const char *name);
            int                               Delete(int intr);
            u32                               AllocMemoryWithOption(SceSize size, SceKernelHeapOptParam * option);
            u32                               AllocMemory(SceSize size);
            int                               FreeMemory(u32 address);
            SceSize                           TotalFreeSize();

        private:
            Heap & operator = (Heap const &) = delete;
        };
    }

    typedef kd::Heap KernelHeap;
}
