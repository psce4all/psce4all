/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

hle::kd::Partition * hle::kd::KernelGetPartition(SceUID id)
{
    return hle::kd::Partition::Get(id);
}

int hle::kd::KernelQueryMemoryPartitionInfo(SceUID id, SceSysMemPartitionInfo * info)
{
    int result = 0;

    KernelPartition * partition = KernelGetPartition(id);

    if (partition)
    {
        SceKernelCpuSuspendIntrScope intr;

        if (info->size == sizeof(SceSysMemPartitionInfo))
        {
            info->startaddr = partition->m_base_address;
            info->memsize = partition->m_size;
            info->attr = partition->m_attributes & 0xF;
        }
        else
        {
            result = SCE_KERNEL_ERROR_ILLEGAL_ARGUMENT;
        }
    }
    else
    {
        result = SCE_KERNEL_ERROR_ILLEGAL_PARTITION;
    }

    return result;
}

SceUID hle::kd::KernelAllocPartitionMemory(Partition &partition, const char * name, int type, u32 size, u32 addr, PartitionBlock *& that)
{
    int result;

    if (partition.AllocatePartitionBlock(name, type, addr, size, that))
    {
        result = (SceUID)that->m_uid;
    }
    else
    {
        result = SCE_KERNEL_ERROR_MEMBLOCK_ALLOC_FAILED;
    }

    return result;
}

SceUID hle::kd::KernelAllocPartitionMemory(SceUID id, const char * name, int type, u32 size, u32 addr)
{
    int result;

    if (type < 5)
    {
        SceKernelCpuSuspendIntrScope intr;

        Partition * partition = KernelGetPartition(id);

        PartitionBlock * that;

        if (partition)
        {
            result = KernelAllocPartitionMemory(*partition, name, type, size, addr, that);
        }
        else
        {
            result = SCE_KERNEL_ERROR_ILLEGAL_PARTITION;
        }
    }
    else
    {
        result = SCE_KERNEL_ERROR_ILLEGAL_MEMBLOCKTYPE;
    }

    return (SceUID)result;
}

int hle::kd::KernelFreePartitionMemory(SceUID uid)
{
    SceKernelCpuSuspendIntrScope intr;

    PartitionBlock * object;

    int result = Objects.Get< PartitionBlock >(uid, object);

    if (!result)
    {
        object->Delete(intr);
    }

    return result;
}

int hle::kd::KernelGetBlockHeadAddr(SceUID uid)
{
    SceKernelCpuSuspendIntrScope intr;

    PartitionBlock * object;

    int result = Objects.Get(uid, object);

    if (!result)
    {
        result = (int)object->m_address;
    }

    return result;
}

SceUID hle::kd::KernelCreateHeap(SceUID uid, SceSize size, int attr, const char * name)
{
    int result = 0;

    SceKernelCpuSuspendIntrScope intr;

    Heap * heap = Heap::Create(uid, size, attr, name);

    result = heap->GetUid();

    if (result <= 0)
    {
        heap->Delete(intr);
    }

    return result;
}

int hle::kd::KernelDeleteHeap(SceUID uid)
{
    SceKernelCpuSuspendIntrScope intr;

    Heap * heap;

    int result = Objects.Get(uid, heap);

    if (!result)
    {
        heap->Delete(intr);
    }

    return result;
}

u32 hle::kd::KernelAllocHeapMemoryWithOption(SceUID uid, SceSize size, SceKernelHeapOptParam * option)
{
    u32 result = 0;

    SceKernelCpuSuspendIntrScope intr;

    Heap * heap;

    if (!Objects.Get(uid, heap))
    {
        result = heap->AllocMemoryWithOption(size, option);
    }

    return result;
}

u32 hle::kd::KernelAllocHeapMemory(SceUID uid, SceSize size)
{
    return KernelAllocHeapMemoryWithOption(uid, size, 0);
}

int hle::kd::KernelFreeHeapMemory(SceUID uid, u32 address)
{
    SceKernelCpuSuspendIntrScope intr;

    Heap * heap;

    int result = Objects.Get(uid, heap);

    if (!result)
    {
        heap->FreeMemory(address);
    }

    return result;
}

SceSize hle::kd::KernelHeapTotalFreeSize(SceUID uid)
{
    u32 max_size = 0;

    SceKernelCpuSuspendIntrScope intr;

    Heap * heap;

    int result = Objects.Get(uid, heap);

    if (!result)
    {
        max_size = heap->TotalFreeSize();
    }

    return max_size;
}

static int _hleKernelSetCompilerVersion = 0;
static int _hleKernelSetCompiledSdkVersion = 0;

void hle::kd::KernelSetCompilerVersion(int version)
{
    _hleKernelSetCompilerVersion = version;
}

void hle::kd::KernelSetCompiledSdkVersion(int version)
{
    _hleKernelSetCompiledSdkVersion = version;
}

int hle::kd::KernelGetCompiledSdkVersion()
{
    return _hleKernelSetCompiledSdkVersion;
}

static hle::kd::PartitionBlock * hleKernelVolatileMem = 0;

int hle::kd::KernelVolatileMemLock(int unk1, p32< p32< void > > paddr, p32< unsigned int > psize, bool trylock)
{
    TODO(implement with Semaphore);

    if (unk1 != 0)
    {
        errorf(kd, "hleKernelVolatileMemLock bad param: unk1 != 0");
        return SCE_ERROR_INVALID_MODE;
    }
    else
    {
        Partition * partition = Partition::Get(5);

        if (partition->AllocatePartitionBlock("VolatileMemory", 0, 0, 0x00400000, hleKernelVolatileMem))
        {
            *paddr = (p32< void > )Partition::LowerBound(hleKernelVolatileMem);
            *psize = (unsigned int)Partition::Length(hleKernelVolatileMem);

            return 0;
        }
        else
        {
            if (trylock)
            {
                return 0x802B0200; // unknown meaning
            }
            else
            {
                errorf(kd, "UNIMPLEMENTED:hleKernelVolatileMemLock blocking current thread");
                return -1;
            }
        }
    }
}

int hle::kd::KernelVolatileMemUnlock(int unk1)
{
    TODO(implement with Semaphore);

    if (unk1 != 0)
    {
        errorf(kd, "sceKernelVolatileMemUnlock bad param: unk1 != 0");

        return SCE_ERROR_INVALID_MODE;
    }
    else if (hleKernelVolatileMem)
    {
        errorf(kd, "sceKernelVolatileMemUnlock - Volatile Memory was not locked!");

        return SCE_KERNEL_ERROR_SEMA_OVF;
    }
    else
    {
        Partition * partition = Partition::Get(5);
        partition->FreePartitionBlock(hleKernelVolatileMem);
        hleKernelVolatileMem = 0;
        return 0;
    }
}
