/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#define hle_kd_SysMem_h__

#include "lle.mmu.h"
#include "hle.kd.Sysmem.Block.h"
#include "hle.kd.Sysmem.Heap.h"
#include "hle.kd.Sysmem.Partition.h"

namespace hle
{
    namespace kd
    {
        KernelPartition * KernelGetPartition(SceUID id);
        int               KernelQueryMemoryPartitionInfo(SceUID id, SceSysMemPartitionInfo * info);
        SceUID            KernelAllocPartitionMemory(KernelPartition & partition, const char * name, int type, u32 size, u32 addr, KernelPartitionBlock *& that);
        SceUID            KernelAllocPartitionMemory(SceUID id, const char * name, int type, u32 size, u32 addr);
        int               KernelFreePartitionMemory(SceUID uid);
        int               KernelGetBlockHeadAddr(SceUID uid);

        SceUID            KernelCreateHeap(SceUID uid, SceSize size, int attr, const char * name);
        int               KernelDeleteHeap(SceUID uid);
        u32               KernelAllocHeapMemoryWithOption(SceUID uid, SceSize size, SceKernelHeapOptParam * option);
        u32               KernelAllocHeapMemory(SceUID uid, SceSize size);
        int               KernelFreeHeapMemory(SceUID uid, u32 address);
        SceSize           KernelHeapTotalFreeSize(SceUID uid);

        void              KernelSetCompilerVersion(int version);
        void              KernelSetCompiledSdkVersion(int version);
        int               KernelGetCompiledSdkVersion();

        int               KernelVolatileMemLock(int unk1, p32< p32< void > > paddr, p32< unsigned int > psize, bool trylock);
        int               KernelVolatileMemUnlock(int unk1);
    }
}
