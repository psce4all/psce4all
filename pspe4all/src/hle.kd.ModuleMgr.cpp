/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

hle::kd::ModuleManager hle::theKernelModuleManager;

/// KernelModule /////////////////////////////////////////////////////////

char const * hle::kd::Module::m_object_type = "KernelModule";

void hle::kd::Module::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size - 1);
}

// TODO
#if 0
hle::kd::Module::Module::Module()
{
}
#endif
hle::kd::Module::Module(char const * name, u32 gp_value, u16 attribute, u16 version)
:   Object(name)
,   m_nsegment(0)
,   m_entry_addr(0)
,   m_gp_value(gp_value)
,   m_text_addr(0)
,   m_text_size(0)
,   m_data_size(0)
,   m_bss_size(0)
,   m_attribute(attribute)
,   m_faked(false)
,   m_fileFormat(0)
,   m_baseAddress(0)
,   m_loadAddressLow(0)
,   m_loadAddressHigh(0)
,   m_ent_top(0)
,   m_ent_size(0)
,   m_stub_top(0)
,   m_stub_size(0)
{
    hle::Module::name          = m_modname;
    hle::Module::library_array = nullptr;
    hle::Module::library_count = 0;

    ::memset(m_modname, 0, 32);
    ::memset(m_segmentaddr, 0, sizeof(m_segmentaddr));
    ::memset(m_segmentsize, 0, sizeof(m_segmentsize));

    *((u16 *)m_version) = version;

    m_module_idx = int(theKernelModuleManager.m_modules_per_index.size());

    theKernelModuleManager.m_modules.Append(this);
    theKernelModuleManager.m_modules_per_index.push_back(this);
}

hle::kd::Module::~Module()
{
    theKernelModuleManager.m_modules_per_index[this->m_module_idx] = 0;
    this->RemoveFromList();
}

// TODO
int hle::kd::Module::Start(SceSize /*argsize*/, void * /*argp*/, int * /*status*/, SceKernelSMOption * /*option*/)
{
    TODO(needs implementation)
    return 0x80020001;
}

// TODO
int hle::kd::Module::Stop(SceSize /*argsize*/, void * /*argp*/, int * /*status*/, SceKernelSMOption * /*option*/)
{
    TODO(needs implementation)
    return 0x80020001;
}

// TODO
int hle::kd::Module::Unload()
{
    TODO(needs implementation)
    return 0x80020001;
}

// TODO
int hle::kd::Module::QueryModuleInfo(SceKernelModuleInfo * /*info*/)
{
    TODO(needs implementation)
    return 0x80020001;
}

#if 0 // NEED TO BE REVISED

int hle::kd::Module::GetSyscallIndex(u32 nid)
{
    for (u32 i = 0; i < this->library_count; ++i)
    {
        auto & library = this->library_array[i];
        for (u32 j = 0; j < library.function_count; ++j)
        {
            auto & function = library.function_array[j];
            if (function.nid == nid)
            {
                return i;
            }
        }
    }
    return -1;
}

hle::Function const * hle::kd::Module::GetSyscall(u32 nid)
{
    for (u32 i = 0; i < this->library_count; ++i)
    {
        auto & library = this->library_array[i];
        for (u32 j = 0; j < library.function_count; ++j)
        {
            auto & function = library.function_array[j];
            if (function.nid == nid)
            {
                return &function;
            }
        }
    }
    return 0;
}

char const * hle::kd::Module::GetSyscallName(u32 nid)
{
    hle::Function const * syscall = GetSyscall(nid);
    if (syscall)
    {
        return syscall->name;
    }
    return "[UNK]";
}

bool hle::kd::Module::WriteSyscall(u32 nid, u32 address)
{
    int handlerIndex = GetSyscallIndex(nid);
    if (handlerIndex < 0)
    {
        ((p32u32)address)[0] = 0x03E00008; // JR $RA
        ((p32u32)address)[1] = 0x03FFFFCC | (m_module_idx << 18); //invalid syscall
        return false;
    }
    ((p32u32)address)[0] = 0x03E00008; // JR $RA
    ((p32u32)address)[1] = 0x0000000C | (m_module_idx << 18) | (handlerIndex << 6);
    return true;
}

#endif

/// SyscallModule ////////////////////////////////////////////////////////

/// KernelModuleManager //////////////////////////////////////////////////

hle::kd::ModuleManager::ModuleManager()
{
    m_modules.Clear();
}

hle::kd::ModuleManager::~ModuleManager()
{
    Clear();
}

int hle::kd::Module::Delete(int /*intr*/)
{
    __delete this;

    return SCE_KERNEL_ERROR_OK;
}

void hle::kd::ModuleManager::Clear()
{
    Module * module = m_modules.First();

    while (module)
    {
        Module * next = m_modules.Next(module);

        module->Delete(0);

        module = next;
    }

    m_modules_per_index.clear();
}

SceUID hle::kd::ModuleManager::Load(char const * /*pathname*/, int /*flags*/, SceKernelLMOption * /*option*/)
{
    TODO(needs implementation);
    return 0x80020001;
}

SceUID hle::kd::ModuleManager::Load(char const * /*pathname*/, SceUID /*block*/, SceOff /*offset*/)
{
    TODO(needs implementation);
    return 0x80020001;
}

SceUID hle::kd::ModuleManager::LoadByID(SceUID /*file*/, int /*flags*/, SceKernelLMOption * /*option*/)
{
    TODO(needs implementation);
    return 0x80020001;
}

SceUID hle::kd::ModuleManager::LoadByID(SceUID /*file*/, SceUID /*block*/, SceOff /*offset*/)
{
    TODO(needs implementation);
    return 0x80020001;
}

SceUID hle::kd::ModuleManager::LoadBufferUsbWlan(SceSize /*bufsize*/, void * /*buf*/, int /*flags*/, SceKernelLMOption * /*option*/)
{
    TODO(needs implementation);
    return 0x80020001;
}

int hle::kd::ModuleManager::StopUnloadSelf(SceSize /*argsize*/, void * /*argp*/, int * /*result*/, SceKernelSMOption * /*option*/)
{
    TODO(needs implementation);
    return 0x80020001;
}

int hle::kd::ModuleManager::StopUnloadSelf(int /*status*/, SceSize /*argsize*/, void * /*argp*/, int * /*result*/, SceKernelSMOption * /*option*/)
{
    TODO(needs implementation);
    return 0x80020001;
}


int hle::kd::ModuleManager::GetModuleId()
{
    KernelThread * current_thread = 0; // theKernelScheduler->GetCurrentThread();

    if (current_thread)
    {
        return current_thread->GetApiModuleId();
    }
    return 0x80020001;
}

int hle::kd::ModuleManager::GetModuleGPByAddress(u32 addr)
{
    Module * module = m_modules.First();

    while (module)
    {
        if (!module->m_faked && (module->m_text_addr <= addr) && (addr < module->m_text_addr + module->m_text_size))
        {
            return int(module->m_gp_value);
        }

        module = m_modules.Next(module);
    }

    return 0;
}


int hle::kd::ModuleManager::GetModuleIdByAddress(u32 addr)
{
    Module * module = m_modules.First();

    while (module)
    {
        if (!module->m_faked && (module->m_text_addr <= addr) && (addr < module->m_text_addr + module->m_text_size))
        {
            return module->GetUid();
        }

        module = m_modules.Next(module);
    }

    return 0x800200D3;
}

int hle::kd::ModuleManager::GetModuleIdList(SceUID *readbuf, int readbufsize, int *idcount)
{
    Module * module = m_modules.First();

    (void)idcount;

    while (readbufsize && module)
    {
        *readbuf = module->GetUid();
        readbufsize--;
        readbuf++;

        module = m_modules.Next(module);
    }

    return 0;
}

#if 0 // NEED TO BE REVISED

int hle::kd::ModuleManager::GetModuleIndex(char const *moduleName)
{
    Module * module = m_modules.First();

    while (module)
    {
        if (::strcmp(moduleName, module->m_name) == 0)
        {
            return module->m_module_idx;
        }

        module = m_modules.Next(module);
    }

    return -1;
}

int hle::kd::ModuleManager::GetSyscallIndex(int moduleIndex, u32 nid)
{
    Module * module = m_modules_per_index[moduleIndex];

    for (u32 i = 0; i < module->m_syscall_count; ++i)
    {
        if (module->m_syscall_array[i].nid == nid)
        {
            return i;
        }
    }
    return -1;
}

hle::kd::Syscall const * hle::kd::ModuleManager::GetSyscall(char const * moduleName, u32 nid)
{
    int moduleIndex = GetModuleIndex(moduleName);
    if (moduleIndex >= 0)
    {
        Module * module = m_modules_per_index[moduleIndex];

        for (u32 i = 0; i < module->m_syscall_count; ++i)
        {
            if (module->m_syscall_array[i].nid == nid)
            {
                return &module->m_syscall_array[i];
            }
        }
    }
    return 0;
}

char const * hle::kd::ModuleManager::GetSyscallName(int moduleIndex, u32 nid)
{
    if ((u32)moduleIndex < m_modules_per_index.size())
    {
        Module * module = m_modules_per_index[moduleIndex];
        if (module)
        {
            return module->GetSyscallName(nid);
        }
    }
    return "[UNK]";
}

char const * hle::kd::ModuleManager::GetSyscallName(char const * moduleName, u32 nid)
{
    Syscall const * syscall = GetSyscall(moduleName, nid);
    if (syscall)
    {
        return syscall->name;

    }
    return "[UNK]";
}

char const * hle::kd::ModuleManager::GetModuleName(int moduleIndex)
{
    return m_modules_per_index[moduleIndex]->m_name;
}

void hle::kd::ModuleManager::WriteSyscall(char const * moduleName, u32 nid, u32 address)
{
    if (nid == 0)
    {
        ((p32u32)address)[0] = 0x03E00008; // JR $RA
        ((p32u32)address)[1] = 0x00000000; // NOP
        return;
    }

    int moduleIndex = GetModuleIndex(moduleName);
    if (moduleIndex >= 0)
    {
        if (!m_modules_per_index[moduleIndex]->WriteSyscall(nid, address))
        {
            errorf(hle, "Unknown nid in module '%s' : nid = 0x%08X, address = 0x%08X", moduleName, nid, address);
        }
    }
    else
    {
        errorf(hle, "Unknown module '%s' : nid = 0x%08X, address = 0x%08X", moduleName, nid, address);
        ((p32u32)address)[0] = 0x03E00008; // JR $RA
        ((p32u32)address)[1] = 0x03FFFFCC; // invalid syscall
    }
}

#endif

void hle::kd::ModuleManager::CreateSyscallsModule(char const * /*moduleName*/, u16 version, hle::Function const * /*syscall_array*/, u32 /*syscall_count*/)
{
    (void)version;

    //if (GetModuleIndex(moduleName) == -1)
    //{
    //    __new Module(moduleName, syscall_array, syscall_count);
    //}
}

void hle::kd::ModuleManager::DeleteSyscallsModule(char const * moduleName)
{
    int index = 0; // GetModuleIndex(moduleName);
    if (index != -1)
    {
        __delete this->m_modules_per_index[index];
        this->m_modules_per_index[index] = 0;
    }
}

bool hle::kd::ModuleManager::SyscallsModuleExists(char const * moduleName)
{
    return false; // GetModuleIndex(moduleName) != -1;
}

hle::kd::Module * hle::kd::LoadModule(u8 * fptr, SceKernelLMOption * options)
{
    Module * module = nullptr;

    if (memcmp(fptr, "\0PBP", 4) == 0)
    {
        u32 version;
        memcpy(&version, fptr + 4, 4);
        u32 offset0, offsets[16];
        int numfiles;
        memcpy(&offset0, fptr + 8, 4);
        numfiles = (offset0 - 8) / 4;
        offsets[0] = offset0;
        for (int i = 1; i < numfiles; i++)
        {
            memcpy(&offsets[i], fptr + 12 + 4 * i, 4);
        }

        module = LoadElfFromPtr(fptr + offsets[5], 0x08804000);
    }
    else  //it is elf file load properly
    {
        module = LoadElfFromPtr(fptr, 0x08804000);
    }
    return module;

}
hle::kd::Module * hle::kd::LoadElfFromPtr(u8 const * ptr, u32 loadAddress)
{
    Module * module   = nullptr;
    u32    * magicPtr = (u32 *)ptr; //get the magic

    if (*magicPtr != 0x464c457f)
    {
        debugf(kd, "Module Header is not valid");
        return 0;
    }

    hle::kd::ElfLoader reader((void *)ptr);

    reader.LoadIntoAddress(loadAddress);

    struct PspModuleInfo
    {
        // 0, 0, 1, 1 ?
        u16  moduleAttrs; //0x0000 User Mode, 0x1000 Kernel Mode
        u16  moduleVersion;
        // 28 bytes of module name, packed with 0's.
        char name[28];
        u32  gp;           // ptr to MIPS GOT data  (global offset table)
        u32  libent;       // ptr to .lib.ent section
        u32  libentend;    // ptr to end of .lib.ent section
        u32  libstub;      // ptr to .lib.stub section
        u32  libstubend;   // ptr to end of .lib.stub section
    };

    size_t sceModuleInfoSection = reader.GetSectionByName(".rodata.sceModuleInfo");
    PspModuleInfo * modinfo;
    if (sceModuleInfoSection != -1)
    {
        modinfo = lle::mmu::Addr< PspModuleInfo >(reader.GetSectionAddr(sceModuleInfoSection));//(PspModuleInfo *)Memory::GetPointer(reader.GetSectionAddr(sceModuleInfoSection));
    }
    else
    {
        return nullptr;
    }

    debugf(kd, "Module %s: %08x %08x %08x", modinfo->name, modinfo->gp, modinfo->libent, modinfo->libstub);

    module = new Module(modinfo->name, modinfo->gp, modinfo->moduleAttrs, modinfo->moduleVersion);
    module->m_entry_addr = reader.GetEntry();

    struct PspLibStubEntry
    {
        // pointer to module name (will be in .rodata.sceResident section)
        unsigned long  moduleNameSymbol;
        // mod version??
        unsigned short version;
        unsigned short val1;
        unsigned char  val2; // 0x5
        unsigned char  val3;
        // number of function symbols
        unsigned short numFuncs;
        // each symbol has an associated nid; nidData is a pointer
        // (in .rodata.sceNid section) to an array of longs, one
        // for each function, which identifies the function whose
        // address is to be inserted.
        //
        // The hash is the first 4 bytes of a SHA-1 hash of the function
        // name.  (Represented as a little-endian long, so the order
        // of the bytes is reversed.)
        unsigned long  nidData;
        // the address of the function stubs where the function address jumps
        // should be filled in
        unsigned long  firstSymAddr;
    };
    int numModules = (modinfo->libstubend - modinfo->libstub) / sizeof(PspLibStubEntry);

    debugf(kd, "# Modules: %i", numModules);
    debugf(kd, "===================================================");
    if (numModules)
    {
        auto entry = lle::mmu::Addr< PspLibStubEntry >(modinfo->libstub);

        int numSyms = 0;

        for (size_t m = 0; m < numModules; ++m)
        {
            auto modulename = lle::mmu::Addr< char >(entry[m].moduleNameSymbol);
            auto nidDataPtr = lle::mmu::Addr< u32  >(entry[m].nidData);
            /*auto stubs      = */lle::mmu::Addr< u32  >(entry[m].firstSymAddr);

            debugf(kd, "Importing Module %s, stubs at %08x", modulename, entry[m].firstSymAddr);

            for (size_t i = 0; i < entry[m].numFuncs; ++i)
            {
                auto addrToWriteSyscall = u32(entry[m].firstSymAddr + i*8);
                debugf(kd, "%s : %08x", hle::syscalls::GetSyscallName(modulename, nidDataPtr[i]), addrToWriteSyscall);

                //write a syscall here
                hle::syscalls::WriteSyscall(modulename, nidDataPtr[i], addrToWriteSyscall);
                numSyms++;
            }
            debugf(kd, "-------------------------------------------------------------");
        }
    }

    if (0)
    {
        char line[4096];
        for (auto va : reader.va_array)
        {
            auto ra = lle::mmu::Addr< u32 >(va);
            lle::cpu::Disassemble(va, *ra, line);
            debugf(kd, "%08X: %s", va, line);
        }
    }

    return module;
}
#if 0




KernelModule *__KernelLoadELFFromPtr(u8 const *elfImage, u32 loadAddress)
{
    if (*(u32*)elfImage != 0x464c457f)
    {
        DebugBreak();
    }

    ElfReader *reader = __new ElfReader((void *)elfImage);

    if (!reader->LoadInto(loadAddress))
    {
        DebugBreak();
    }

    struct libent
    {
        u32 exportName; //default 0
        u16 bcdVersion;
        u16 moduleAttributes;
        u8  exportEntrySize;
        u8  numVariables;
        u16 numFunctions;
        unsigned long __entrytableAddr;
    };

    SectionID entSection  = reader->GetSectionByName(".lib.ent");
    SectionID textSection = reader->GetSectionByName(".text");
    SectionID dataSection = reader->GetSectionByName(".data");
    SectionID bssSection  = reader->GetSectionByName(".bss");

    u32 sceResidentAddr = 0;
    u32 moduleInfoAddr  = 0;

    u32 textStart = reader->GetSectionAddr(textSection);
    u32 textSize  = reader->GetSectionSize(textSection);
    u32 dataSize  = reader->GetSectionSize(dataSection);
    u32 bssSize   = reader->GetSectionSize(bssSection);

    SectionID sceResidentSection   = reader->GetSectionByName(".rodata.sceResident");
    SectionID sceModuleInfoSection = reader->GetSectionByName(".rodata.sceModuleInfo");

    bool hasSymbols = false;
    bool dontadd    = false;

    sceResidentAddr = reader->GetSectionAddr(sceResidentSection);
    moduleInfoAddr  = reader->GetSectionAddr(sceModuleInfoSection);

    struct PspResidentData
    {
        unsigned long l1;             // unknown 0xd632acdb
        unsigned long l2;             // unknown 0xf01d73a7
        unsigned long startAddress;   // address of _start
        unsigned long moduleInfoAddr; // address of sceModuleInfo struct
    };

    Log::loader.info("Resident data addr: %08X", sceResidentAddr);

    PspModuleInfo *modinfo = Memory::addr< PspModuleInfo >(moduleInfoAddr);

    KernelModule *module = __new KernelModule(modinfo->name, modinfo->gp, modinfo->moduleAttrs, modinfo->moduleVersion);

    module->m_text_addr = textStart;
    module->m_text_size = textSize;
    module->m_data_size = dataSize;
    module->m_bss_size  = bssSize;

    Log::loader.info("Module %s: %08x %08x %08x", modinfo->name, modinfo->gp, modinfo->libent, modinfo->libstub);

    int numModules = (modinfo->libstubend - modinfo->libstub)/sizeof(PspLibStubEntry);

    Log::loader.info("# Modules: %i", numModules);
    Log::loader.info("===================================================");

    PspLibStubEntry *entry = Memory::addr< PspLibStubEntry >(modinfo->libstub);

    int numSyms = 0;
    for (int m = 0; m < numModules; m++)
    {
        char *modulename = Memory::addr< char >(entry[m].moduleNameSymbol);
        u32  *nidDataPtr = Memory::addr< u32  >(entry[m].nidData);
        u32  *stubs      = Memory::addr< u32  >(entry[m].firstSymAddr);

        Log::loader.info("Importing Module %s, stubs at %08x", modulename, entry[m].firstSymAddr);

        for (int i = 0; i < entry[m].numFuncs; i++)
        {
            u32 addrToWriteSyscall = entry[m].firstSymAddr + i*8;
            Log::loader.info("%s : %08x", hle::GetFuncName(modulename, nidDataPtr[i]), addrToWriteSyscall);

            //write a syscall here
            hle::WriteSyscall(modulename, nidDataPtr[i], addrToWriteSyscall);
            if (!dontadd)
            {
                char temp[256];
                _snprintf(temp,255,"zz_%s", hle::GetFuncName(modulename, nidDataPtr[i]));
            }
            numSyms++;
        }
        Log::loader.info("-------------------------------------------------------------");
    }

    return __new KernelModule(modinfo->name, reader->GetEntryPoint(), modinfo->gp, textStart, textSize,);
}
#endif

#if 0
int KernelModule::LoadElf(u32 elf)
{
    int i, j, n, minaddr, maxaddr;

    Elf32_Ehdr *ehdr = Memory::addr< Elf32_Ehdr >(elf);
    Elf32_Phdr *phdr = Memory::addr< Elf32_Phdr >(elf + ehdr->e_phoff);

    for (i = n = ehdr->e_phnum; i > 0; --i)
    {
        if (phdr[n - i].p_type == PT_LOAD)
        {
            break;
        }
    }

    this->m_segmentaddr[0] = execFileInfo->unk_24;
    this->m_segmentsize[0] = phdr[n - i].p_filesz;

    j = 1;

    if (i > 1 && phdr[n - i + 1].p_type == PT_LOAD)
    {
        for (; j < i && phdr[n - i + j].p_type == PT_LOAD; ++j)
        {
            this->m_segmentaddr[j] = execFileInfo->unk_24 + phdr[n - i + j].p_vaddr;
            this->m_segmentsize[j] = phdr[n - i + j].p_filesz;
        }
    }

    this->m_nsegment = j;

    minaddr = -1;
    maxaddr = 0;

    for (j = 0; j < n; ++j)
    {
        if(phdr[j].p_type == PT_LOAD)
        {
            if (minaddr == -1)
            {
                minaddr = phdr[j].p_vaddr;
            }

            maxaddr = phdr[j].p_vaddr + phdr[j].p_memsz;
        }
    }

    SceUID memuid = sysmem::hleKernelAllocPartitionMemory(this->m_partition_uid, "SceLoadElfBlock", 2, ((maxaddr + 255) & -256) - (minaddr & -256), (minaddr & -256));

    this->m_memblock_uid = memuid;

    if (memuid < 0)
    {
        return memuid;
    }

    //sysmem::hleKernelGetBlockHeadAddr(memuid);

    for (j = 0; j < n; ++j)
    {
        if (phdr[j].p_type == PT_LOAD)
        {
            if (phdr[j].p_vaddr != elf + phdr[j].p_offset)
            {
                memcpy(Memory::addr< u8 >(phdr[j].p_vaddr), Memory::addr< u8 >(elf) + phdr[j].p_offset, phdr[j].p_filesz);
            }

            if (phdr[j].p_filesz < phdr[j].p_memsz)
            {
                memset(Memory::addr< u8 >(phdr[j].p_vaddr) + phdr[j].p_filesz, 0, phdr[j].p_memsz - phdr[j].p_filesz);
            }
        }
    }

    return 0;
}

int KernelModule::LoadRelElf(u32 elf)
{
}

#endif

