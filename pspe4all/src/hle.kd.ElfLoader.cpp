/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"
#include "hle.kd.SysMem.h"

size_t hle::kd::ElfLoader::LoadIntoAddress(u32 addr)
{
    entry          = header->e_entry;
    u32 totalStart = 0xFFFFFFFF;
    u32 totalEnd   = 0;
    for (size_t i = 0; i < size_t(header->e_phnum); ++i)
    {
        auto p = &pheader[i];
        if (p->p_type == PT_LOAD)
        {
            if (p->p_vaddr < totalStart)
            {
                totalStart = p->p_vaddr;
            }
            if (p->p_vaddr + p->p_memsz > totalEnd)
            {
                totalEnd = p->p_vaddr + p->p_memsz;
            }
        }
    }
    totalSize = totalEnd - totalStart;

    //todo check if we need to relocate assuming not atm

    //allocate
#if 0
    KernelPartitionBlock * info;
    if (!KernelPartition::Get(2)->AllocatePartitionBlock("ELF", 2, totalStart, totalSize, info))
    {
        debugf(kd, "Partition cannot be allocated for module");
    }
#endif
    //TODO relocate
    u32 baseAddress = 0;

    vaddr = totalStart;

    for (size_t i = 0; i < size_t(header->e_phnum); ++i)
    {
        ElfPHeader * p = pheader + i;
        debugf(kd, "ElfLoader: ElfProgramHeader Type: %08x Vaddr: %08x Filesz: %08x Memsz: %08x ", (int)p->p_type, (u32)p->p_vaddr, (int)p->p_filesz, (int)p->p_memsz);
        if (p->p_type == PT_LOAD)
        {
            segmentVAddr[i]   = baseAddress + p->p_vaddr;
            u32    writeAddr  = segmentVAddr[i];
            u8   * src        = GetSegmentPtr(i);
            u8   * dst        = lle::mmu::Addr< u8 >(writeAddr);
            size_t srcSize    = size_t(p->p_filesz);
            size_t dstSize    = size_t(p->p_memsz);
            if (srcSize < dstSize)
            {
                memset(dst + srcSize, 0, dstSize - srcSize); //zero out bss
            }
            memcpy(dst, src, srcSize);
            debugf(kd, "ElfLoader: Loadable Segment loaded at %08X, size %d", writeAddr, (u32)dstSize);

#if 1
            if (p->p_flags & 1)
            {
                for (u32 j = 0; j < dstSize / 4; ++j)
                {
                    auto va = writeAddr + 4 * j;
                    va_array.push_back(va);
                }
            }
#endif
        }
    }

    sectionOffsets = new u32[header->e_shnum];
    sectionAddrs   = new u32[header->e_shnum];

    for (size_t i = 0; i <header->e_shnum; i++)
    {
        ElfSHeader * s = &sheader[i];
        /*auto name = */GetSectionName(int(i));
        u32 writeAddr = s->sh_addr + baseAddress;
        sectionOffsets[i] = writeAddr - vaddr;
        sectionAddrs  [i] = writeAddr;
    }

    return 0;
}

size_t hle::kd::ElfLoader::GetSectionByName(char const *name, size_t firstSection)
{
    for (size_t i = firstSection; i < header->e_shnum; ++i)
    {
        auto secname = GetSectionName(i);
        if (secname != 0 && strcmp(name, secname) == 0)
        {
            return i;
        }
    }

    return size_t(-1);
}

char const * hle::kd::ElfLoader::GetSectionName(size_t section)
{
    if (sheader[section].sh_type != SHT_NULL)
    {
        auto nameOffset = sheader[section].sh_name;
        auto ptr        = GetSectionDataPtr(header->e_shstrndx);
        if (ptr)
        {
            return (char const *)(ptr + nameOffset);
        }
    }

    return 0;
}