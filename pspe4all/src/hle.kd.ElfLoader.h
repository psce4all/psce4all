/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#define hle_kd_ElfLoader_h__

#define ELF_MAGIC   0x464C457F

///////////////////////
// ELF Header Constants
// File type
enum ElfType
{
    ET_NONE = 0,
    ET_REL = 1,
    ET_EXEC = 2,
    ET_DYN = 3,
    ET_CORE = 4,
    ET_LOPROC = 0xFF00,
    ET_HIPROC = 0xFFFF,
    ET_PSP_PRX = 0xFFA0,
};
// Machine/Architecture
enum ElfMachine
{
    EM_NONE = 0,
    EM_M32 = 1,
    EM_SPARC = 2,
    EM_386 = 3,
    EM_68K = 4,
    EM_88K = 5,
    EM_860 = 7,
    EM_MIPS = 8
};
// File version
#define EV_NONE 0
#define EV_CURRENT 1
// Identification index
#define EI_MAG0 0
#define EI_MAG1 1
#define EI_MAG2 2
#define EI_MAG3 3
#define EI_CLASS 4
#define EI_DATA 5
#define EI_VERSION 6
#define EI_PAD 7
#define EI_NIDENT 16

// File class
#define ELFCLASSNONE 0
#define ELFCLASS32 1
#define ELFCLASS64 2
// Encoding
#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2
// MIPS-specific header flags.
#define EF_MIPS_NOREORDER 0x00000001
#define EF_MIPS_PIC 0x00000002
#define EF_MIPS_CPIC 0x00000004
#define EF_MIPS_XGOT 0x00000008
#define EF_MIPS_UCODE 0x00000010
#define EF_MIPS_ABI2 0x00000020
#define EF_MIPS_DYNAMIC 0x00000040
#define EF_MIPS_32BITMODE 0x00000100
#define EF_MIPS_ABI_MASK 0x0000f000
#define EF_MIPS_ABI_O32 0x00001000
#define EF_MIPS_ABI_O64 0x00002000
#define E_MIPS_ABI_EABI32 0x00003000
#define E_MIPS_ABI_EABI64 0x00004000
#define EF_MIPS_MACH_MASK 0x00ff0000
#define EF_MIPS_MACH_PSP 0x00a20000
#define EF_MIPS_ARCH_MASK 0xf0000000
#define EF_MIPS_ARCH_1 0x00000000
#define EF_MIPS_ARCH_2 0x10000000
#define EF_MIPS_ARCH_3 0x20000000
#define EF_MIPS_ARCH_4 0x30000000
#define EF_MIPS_ARCH_5 0x40000000
#define EF_MIPS_ARCH_32 0x50000000
#define EF_MIPS_ARCH_64 0x60000000
#define EF_MIPS_ARCH_32R2 0x70000000
#define EF_MIPS_ARCH_64R2 0x80000000

/////////////////////
// Sections constants
// Section indexes
#define SHN_UNDEF 0
#define SHN_LORESERVE 0xFF00
#define SHN_LOPROC 0xFF00
#define SHN_HIPROC 0xFF1F
#define SHN_ABS 0xFFF1
#define SHN_COMMON 0xFFF2
#define SHN_HIRESERVE 0xFFFF
// Section types
#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_LOPROC 0x70000000
#define SHT_HIPROC 0x7FFFFFFF
#define SHT_LOUSER 0x80000000
#define SHT_HIUSER 0xFFFFFFFF
// Custom section types
#define SHT_PSPREL 0x700000a0
// Section flags
enum ElfSectionFlags
{
    SHF_WRITE = 0x1,
    SHF_ALLOC = 0x2,
    SHF_EXECINSTR = 0x4,
    SHF_MASKPROC = 0xF0000000,
};
// Relocation types
#define R_386_NONE 0
#define R_386_32 1
#define R_386_PC32 2
#define R_386_GOT32 3
#define R_386_PLT32 4
#define R_386_COPY 5
#define R_386_GLOB_DAT 6
#define R_386_JMP_SLOT 7
#define R_386_RELATIVE 8
#define R_386_GOTOFF 9
#define R_386_GOTPC 10
// Segment types
#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7FFFFFFF
// Custom segment types
#define PT_PSPREL1 0x700000a0
#define PT_PSPREL2 0x700000a1
// Segment flags
#define PF_X 1
#define PF_W 2
#define PF_R 4

// Dynamic Array Tags
#define DT_NULL 0
#define DT_NEEDED 1
#define DT_PLTRELSZ 2
#define DT_PLTGOT 3
#define DT_HASH 4
#define DT_STRTAB 5
#define DT_SYMTAB 6
#define DT_RELA 7
#define DT_RELASZ 8
#define DT_RELAENT 9
#define DT_STRSZ 10
#define DT_SYMENT 11
#define DT_INIT 12
#define DT_FINI 13
#define DT_SONAME 14
#define DT_RPATH 15
#define DT_SYMBOLIC 16
#define DT_REL 17
#define DT_RELSZ 18
#define DT_RELENT 19
#define DT_PLTREL 20
#define DT_DEBUG 21
#define DT_TEXTREL 22
#define DT_JMPREL 23
#define DT_LOPROC 0x70000000
#define DT_HIPROC 0x7FFFFFFF


struct ElfHeader
{
    u32 e_magic;
    u8 e_class;
    u8 e_data;
    u8 e_idver;
    u8 e_pad[9];
    u16 e_type;
    u16 e_machine;
    u32 e_version;
    u32 e_entry;
    u32 e_phoff;
    u32 e_shoff;
    u32 e_flags;
    u16 e_ehsize;
    u16 e_phentsize;
    u16 e_phnum;
    u16 e_shentsize;
    u16 e_shnum;
    u16 e_shstrndx;
};
struct ElfPHeader
{
    u32 p_type;
    u32 p_offset;
    u32 p_vaddr;
    u32 p_paddr;
    u32 p_filesz;
    u32 p_memsz;
    u32 p_flags;
    u32 p_align;
};
struct ElfSHeader
{
    u32 sh_name;
    u32 sh_type;
    u32 sh_flags;
    u32 sh_addr;
    u32 sh_offset;
    u32 sh_size;
    u32 sh_link;
    u32 sh_info;
    u32 sh_addralign;
    u32 sh_entsize;
};


namespace hle
{
    namespace kd
    {
        class ElfLoader
        {
        public:
            ElfLoader(void * fptr)
            {
                base    = (u8         *)fptr;
                header  = (ElfHeader  *)fptr;
                pheader = (ElfPHeader *)(base + header->e_phoff);
                sheader = (ElfSHeader *)(base + header->e_shoff);
            }

            u8         * GetPtr(u32 offset) const
            {
                return base + offset;
            }

            u8         * GetSegmentPtr(size_t segment) const
            {
                return GetPtr(pheader[segment].p_offset);
            }

            u8         * GetSectionDataPtr(size_t section) const
            {
                if (section < 0 || section >= header->e_shnum)
                {
                    return 0;
                }
                if (sheader[section].sh_type != SHT_NOBITS)
                {
                    return GetPtr(sheader[section].sh_offset);
                }

                return 0;
            }

            u32          GetSectionAddr(size_t section) const
            {
                return sectionAddrs[section];
            }

            size_t       LoadIntoAddress(u32 addr);

            size_t       GetSectionByName(char const * name, size_t firstSection = 0);

            char const * GetSectionName(size_t section);

            u32          GetEntry() const
            {
                return entry;
            }


            std::vector< u32 > va_array;

        private:
            u8         * base;
            ElfHeader  * header;
            ElfPHeader * pheader;
            ElfSHeader * sheader;

            u32          entry;
            u32          totalSize; //size that needs to be allocated
            u32          segmentVAddr[32];
            u32        * sectionOffsets;
            u32        * sectionAddrs;
            u32          vaddr;
        };
    }

}
