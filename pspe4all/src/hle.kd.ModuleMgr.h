/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#define hle_kd_ModuleMgr_h__

#include "hle.syscalls.Modules.h"

namespace hle
{
    namespace kd
    {
        struct Syscall;

        struct Module;
        struct LibImport;
        struct LibExport;

        typedef hal::LinkedList< Module    > ModuleList;
        typedef hal::LinkedList< LibImport > LibImportList;
        typedef hal::LinkedList< LibExport > LibExportList;

#if 0
        struct KernelLibImport : KernelLibImportList::Node
        {
            char            name[PRX_LIB_MAX_NAME];
            u32             addr;
            //KernelLibImport stub; ???
            PrxEntry        funcs[PRX_MAX_F_ENTRIES];
            int             f_count;
            PrxEntry        vars[PRX_MAX_V_ENTRIES];
            int             v_count;
        };

        struct KernelLibExport : KernelLibExportList::Node
        {
            char            name[PRX_LIB_MAX_NAME];
            u32             addr;
            ///KernelLibExport stub; ???
            PrxEntry        funcs[PRX_MAX_F_ENTRIES];
            int             f_count;
            PrxEntry        vars[PRX_MAX_V_ENTRIES];
            int             v_count;
        };

        struct PrxModule
        {
            char             name[PRX_LIB_MAX_NAME+1];
            PrxModuleInfo    info;
            u32              addr;
            KernelLibExport *exp_head;
            KernelLibImport *imp_head;
        };
#endif

        struct Module : Object, ModuleList::Node, hle::Module
        {
            declare_kernel_type(Module, Object);

            char                  m_nsegment;
            char                  m_reserved[3];
            int                   m_segmentaddr[4];
            int                   m_segmentsize[4];
            unsigned int          m_entry_addr;
            unsigned int          m_gp_value;
            unsigned int          m_text_addr;
            unsigned int          m_text_size;
            unsigned int          m_data_size;
            unsigned int          m_bss_size;
            unsigned short        m_attribute;
            unsigned char         m_version[2];

            bool                  m_faked;
            SceUID                m_partition_uid;
            SceUID                m_memblock_uid;

            int                   m_module_idx;

            //special fields
            unsigned int          m_fileFormat;
            unsigned int          m_baseAddress;
            unsigned int          m_loadAddressLow;
            unsigned int          m_loadAddressHigh;
            unsigned int          m_ent_top;
            unsigned int          m_ent_size;
            unsigned int          m_stub_top;
            unsigned int          m_stub_size;
            char                  m_modname[32];


#if 0
            /**/                  Module();
#endif
            /**/                  Module(char const * name, u32 gp_value = 0, u16 attribute = 0, u16 version = 0);
            /**/                 ~Module();

            virtual int           Start(SceSize argsize, void * argp, int * status, SceKernelSMOption * option);
            virtual int           Stop(SceSize argsize, void * argp, int * status, SceKernelSMOption * option);
            virtual int           Unload();
            virtual int           QueryModuleInfo(SceKernelModuleInfo * info);

            int                   Delete(int intr);

#if 0 // NEED TO BE REVISED
            int                   GetModuleIndex() { return m_module_idx; }
            int                   GetSyscallIndex(u32 nid);
            hle::Function const * GetSyscall(u32 nid);
            char const          * GetSyscallName(u32 nid);
            bool                  WriteSyscall(u32 nid, u32 address);
#endif

        protected:
            int                   LoadElf(u32 elf);
            int                   LoadRelElf(u32 elf);
        };

        struct ModuleManager
        {
            ModuleList              m_modules;
            std::vector< Module * > m_modules_per_index;

            /**/                  ModuleManager();
            /**/                 ~ModuleManager();

            SceUID                Load(char const * pathname, int flags, SceKernelLMOption * option);
            SceUID                Load(char const * pathname, SceUID block, SceOff offset);
            SceUID                LoadByID(SceUID file, int flags, SceKernelLMOption * option);
            SceUID                LoadByID(SceUID file, SceUID block, SceOff offset);
            SceUID                LoadBufferUsbWlan(SceSize bufsize, void * buf, int flags, SceKernelLMOption * option);

            int                   StopUnloadSelf(SceSize argsize, void * argp, int * result, SceKernelSMOption * option);
            int                   StopUnloadSelf(int status, SceSize argsize, void * argp, int * result, SceKernelSMOption * option);

            int                   GetModuleId();
            int                   GetModuleIdByAddress(u32 addr);
            int                   GetModuleGPByAddress(u32 addr);
            int                   GetModuleIdList(SceUID * readbuf, int readbufsize, int * idcount);

#if 0 // NEED TO BE REVISED
            int                   GetModuleIndex(char const * moduleName);
            char const          * GetModuleName(int moduleIndex);
            int                   GetSyscallIndex(int moduleIndex, u32 nid);
            hle::Function const * GetSyscall(char const * moduleName, u32 nid);
            char const          * GetSyscallName(int moduleIndex, u32 nid);
            char const          * GetSyscallName(char const * moduleName, u32 nid);
            void                  WriteSyscall(char const * moduleName, u32 nid, u32 address);
#endif

            void                  CreateSyscallsModule(char const * moduleName, u16 version, hle::Function const * syscall_array, u32 syscall_count);
            void                  DeleteSyscallsModule(char const * moduleName);
            bool                  SyscallsModuleExists(char const * moduleName);
            void                  Clear();


        };
        //
        Module* LoadElfFromPtr(const u8 *ptr, u32 loadAddress);
        Module* LoadModule(u8 *fptr, SceKernelLMOption *options);
    }

    extern kd::ModuleManager theKernelModuleManager;
}
