//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(sysmem.prx)SysMemUserForUser.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

#include "hle.kd.h"

namespace hle
{
    namespace SysMemUserForUser //@hle:library-start{SysMemUserForUser|sceSystemMemoryManager|sysmem.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{A291F107|SysMemUserForUser|sceKernelMaxFreeMemSize|g|unsigned int sceKernelMaxFreeMemSize(void)}
        int  sceKernelMaxFreeMemSize()
        {
            u32 max_size = 0;

            SceKernelCpuSuspendIntrScope intr;

            kd::Partition * partition = kd::Partition::Get(2);

            if (!partition->m_free_blocks.empty())
            {
                for (auto i = partition->m_free_blocks.begin(); i != partition->m_free_blocks.end(); ++i)
                {
                    u32 size = kd::Partition::Length(i);

                    if (size > max_size)
                    {
                        max_size = size;
                    }
                }
            }

            return int(max_size);
        }
        //@hle:function{F919F628|SysMemUserForUser|sceKernelTotalFreeMemSize|g|unsigned int sceKernelTotalFreeMemSize(void)}
        int  sceKernelTotalFreeMemSize()
        {
            u32 size = 0;

            SceKernelCpuSuspendIntrScope intr;

            kd::Partition * partition = kd::Partition::Get(2);

            if (partition)
            {
                for (auto i = partition->m_free_blocks.begin(); i != partition->m_free_blocks.end(); ++i)
                {
                    size += kd::Partition::Length(i);
                }
            }

            return int(size);
        }
        //@hle:function{13A5ABEF|SysMemUserForUser|sceKernelPrintf|g|void * sceKernelPrintf(void)}
        int  sceKernelPrintf()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED sceKernelPrintf");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F77D77CB|SysMemUserForUser|sceKernelSetCompilerVersion|gg|int sceKernelSetCompilerVersion(unsigned int version)}
        int  sceKernelSetCompilerVersion(u32 $a0)
        {
            kd::KernelSetCompilerVersion(int($a0));

            return SCE_KERNEL_ERROR_OK;
        }
        //@hle:function{7591C7DB|SysMemUserForUser|sceKernelSetCompiledSdkVersion|gg|int sceKernelSetCompiledSdkVersion(unsigned int version)}
        int  sceKernelSetCompiledSdkVersion(u32 $a0)
        {
            kd::KernelSetCompiledSdkVersion(int($a0));

            return SCE_KERNEL_ERROR_OK;
        }
        //@hle:function{3FC9AE6A|SysMemUserForUser|sceKernelDevkitVersion|g|int sceKernelDevkitVersion(void)}
        int  sceKernelDevkitVersion()
        {
            return SCE_FIRMWARE_500;
        }
        //@hle:function{FC114573|SysMemUserForUser|sceKernelGetCompiledSdkVersion|g|??? sceKernelGetCompiledSdkVersion()}
        int  sceKernelGetCompiledSdkVersion()
        {
            return kd::KernelGetCompiledSdkVersion();
        }
        //@hle:function{237DBD4F|SysMemUserForUser|sceKernelAllocPartitionMemory|gggggg|SceUID sceKernelAllocPartitionMemory(SceUID partitionid, const char * name, int type, SceSize size, void * addr)}
        int  sceKernelAllocPartitionMemory(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            SceSysMemPartitionInfo data;

            SceUID       id        = (SceUID)$a0;
            char const * name      = lle::mmu::Addr< char const >($a1);
            int          type      = (int)$a2;
            u32          size      = (u32)$a3;
            u32          addr      = (u32)$a4;

            data.size = sizeof(data);

            int result = kd::KernelQueryMemoryPartitionInfo(id, &data);

            if (result >=  0)
            {
                if (data.attr & 2)
                {
                    return kd::KernelAllocPartitionMemory(id, (name ? name : "BlockForUser"), type, size, addr);
                }

                result = SCE_KERNEL_ERROR_ERROR;
            }

            return result;
        }
        //@hle:function{B6D61D02|SysMemUserForUser|sceKernelFreePartitionMemory|gg|int sceKernelFreePartitionMemory(SceUID blockid)}
        int  sceKernelFreePartitionMemory(u32 $a0)
        {
            return kd::KernelFreePartitionMemory((SceUID)$a0);
        }
        //@hle:function{9D9A5BA1|SysMemUserForUser|sceKernelGetBlockHeadAddr|gg|void * sceKernelGetBlockHeadAddr(SceUID blockid)}
        int  sceKernelGetBlockHeadAddr(u32 $a0)
        {
            return kd::KernelGetBlockHeadAddr((SceUID)$a0);
        }
        //@hle:function{2A3E5280|SysMemUserForUser|sceKernelQueryMemoryInfo|g|??? sceKernelQueryMemoryInfo()}
        int  sceKernelQueryMemoryInfo()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED sceKernelQueryMemoryInfo");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{057E7380|SysMemUserForUser|SysMemUserForUser_057E7380|g|??? SysMemUserForUser_057E7380()}
        int  SysMemUserForUser_057E7380()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_057E7380");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{315AD3A0|SysMemUserForUser|SysMemUserForUser_315AD3A0|g|??? SysMemUserForUser_315AD3A0()}
        int  SysMemUserForUser_315AD3A0()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_315AD3A0");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{342061E5|SysMemUserForUser|SysMemUserForUser_342061E5|g|??? SysMemUserForUser_342061E5()}
        int  SysMemUserForUser_342061E5()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_342061E5");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{50F61D8A|SysMemUserForUser|SysMemUserForUser_50F61D8A|g|??? SysMemUserForUser_50F61D8A()}
        int  SysMemUserForUser_50F61D8A()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_50F61D8A");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{91DE343C|SysMemUserForUser|SysMemUserForUser_91DE343C|g|??? SysMemUserForUser_91DE343C()}
        int  SysMemUserForUser_91DE343C()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_91DE343C");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A6848DF8|SysMemUserForUser|SysMemUserForUser_A6848DF8|g|??? SysMemUserForUser_A6848DF8()}
        int  SysMemUserForUser_A6848DF8()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_A6848DF8");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{ACBD88CA|SysMemUserForUser|SysMemUserForUser_ACBD88CA|g|??? SysMemUserForUser_ACBD88CA()}
        int  SysMemUserForUser_ACBD88CA()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_ACBD88CA");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D8DE5C1E|SysMemUserForUser|SysMemUserForUser_D8DE5C1E|g|??? SysMemUserForUser_D8DE5C1E()}
        int  SysMemUserForUser_D8DE5C1E()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_D8DE5C1E");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DB83A952|SysMemUserForUser|SysMemUserForUser_DB83A952|g|??? SysMemUserForUser_DB83A952()}
        int  SysMemUserForUser_DB83A952()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_DB83A952");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EBD5C3E6|SysMemUserForUser|SysMemUserForUser_EBD5C3E6|g|??? SysMemUserForUser_EBD5C3E6()}
        int  SysMemUserForUser_EBD5C3E6()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_EBD5C3E6");
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FE707FDF|SysMemUserForUser|SysMemUserForUser_FE707FDF|g|??? SysMemUserForUser_FE707FDF()}
        int  SysMemUserForUser_FE707FDF()
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED SysMemUserForUser_FE707FDF");
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{SysMemUserForUser|sceSystemMemoryManager|sysmem.prx}
}

extern "C" bool __cdecl SysMemUserForUser$Init() { return hle::SysMemUserForUser::Init(); }
extern "C" bool __cdecl SysMemUserForUser$Fini() { return hle::SysMemUserForUser::Fini(); }
extern "C" void __cdecl SysMemUserForUser_A291F107(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::sceKernelMaxFreeMemSize                          >(c); } //@hle:syscall{A291F107|SysMemUserForUser|sceKernelMaxFreeMemSize|g|unsigned int sceKernelMaxFreeMemSize(void)}
extern "C" void __cdecl SysMemUserForUser_F919F628(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::sceKernelTotalFreeMemSize                        >(c); } //@hle:syscall{F919F628|SysMemUserForUser|sceKernelTotalFreeMemSize|g|unsigned int sceKernelTotalFreeMemSize(void)}
extern "C" void __cdecl SysMemUserForUser_13A5ABEF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::sceKernelPrintf                                  >(c); } //@hle:syscall{13A5ABEF|SysMemUserForUser|sceKernelPrintf|g|void * sceKernelPrintf(void)}
extern "C" void __cdecl SysMemUserForUser_F77D77CB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::SysMemUserForUser::sceKernelSetCompilerVersion                      >(c); } //@hle:syscall{F77D77CB|SysMemUserForUser|sceKernelSetCompilerVersion|gg|int sceKernelSetCompilerVersion(unsigned int version)}
extern "C" void __cdecl SysMemUserForUser_7591C7DB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::SysMemUserForUser::sceKernelSetCompiledSdkVersion                   >(c); } //@hle:syscall{7591C7DB|SysMemUserForUser|sceKernelSetCompiledSdkVersion|gg|int sceKernelSetCompiledSdkVersion(unsigned int version)}
extern "C" void __cdecl SysMemUserForUser_3FC9AE6A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::sceKernelDevkitVersion                           >(c); } //@hle:syscall{3FC9AE6A|SysMemUserForUser|sceKernelDevkitVersion|g|int sceKernelDevkitVersion(void)}
extern "C" void __cdecl SysMemUserForUser_FC114573(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::sceKernelGetCompiledSdkVersion                   >(c); } //@hle:syscall{FC114573|SysMemUserForUser|sceKernelGetCompiledSdkVersion|g|??? sceKernelGetCompiledSdkVersion()}
extern "C" void __cdecl SysMemUserForUser_237DBD4F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::SysMemUserForUser::sceKernelAllocPartitionMemory                    >(c); } //@hle:syscall{237DBD4F|SysMemUserForUser|sceKernelAllocPartitionMemory|gggggg|SceUID sceKernelAllocPartitionMemory(SceUID partitionid, const char * name, int type, SceSize size, void * addr)}
extern "C" void __cdecl SysMemUserForUser_B6D61D02(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::SysMemUserForUser::sceKernelFreePartitionMemory                     >(c); } //@hle:syscall{B6D61D02|SysMemUserForUser|sceKernelFreePartitionMemory|gg|int sceKernelFreePartitionMemory(SceUID blockid)}
extern "C" void __cdecl SysMemUserForUser_9D9A5BA1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::SysMemUserForUser::sceKernelGetBlockHeadAddr                        >(c); } //@hle:syscall{9D9A5BA1|SysMemUserForUser|sceKernelGetBlockHeadAddr|gg|void * sceKernelGetBlockHeadAddr(SceUID blockid)}
extern "C" void __cdecl SysMemUserForUser_2A3E5280(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::sceKernelQueryMemoryInfo                         >(c); } //@hle:syscall{2A3E5280|SysMemUserForUser|sceKernelQueryMemoryInfo|g|??? sceKernelQueryMemoryInfo()}
extern "C" void __cdecl SysMemUserForUser_057E7380(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_057E7380                       >(c); } //@hle:syscall{057E7380|SysMemUserForUser|SysMemUserForUser_057E7380|g|??? SysMemUserForUser_057E7380()}
extern "C" void __cdecl SysMemUserForUser_315AD3A0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_315AD3A0                       >(c); } //@hle:syscall{315AD3A0|SysMemUserForUser|SysMemUserForUser_315AD3A0|g|??? SysMemUserForUser_315AD3A0()}
extern "C" void __cdecl SysMemUserForUser_342061E5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_342061E5                       >(c); } //@hle:syscall{342061E5|SysMemUserForUser|SysMemUserForUser_342061E5|g|??? SysMemUserForUser_342061E5()}
extern "C" void __cdecl SysMemUserForUser_50F61D8A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_50F61D8A                       >(c); } //@hle:syscall{50F61D8A|SysMemUserForUser|SysMemUserForUser_50F61D8A|g|??? SysMemUserForUser_50F61D8A()}
extern "C" void __cdecl SysMemUserForUser_91DE343C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_91DE343C                       >(c); } //@hle:syscall{91DE343C|SysMemUserForUser|SysMemUserForUser_91DE343C|g|??? SysMemUserForUser_91DE343C()}
extern "C" void __cdecl SysMemUserForUser_A6848DF8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_A6848DF8                       >(c); } //@hle:syscall{A6848DF8|SysMemUserForUser|SysMemUserForUser_A6848DF8|g|??? SysMemUserForUser_A6848DF8()}
extern "C" void __cdecl SysMemUserForUser_ACBD88CA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_ACBD88CA                       >(c); } //@hle:syscall{ACBD88CA|SysMemUserForUser|SysMemUserForUser_ACBD88CA|g|??? SysMemUserForUser_ACBD88CA()}
extern "C" void __cdecl SysMemUserForUser_D8DE5C1E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_D8DE5C1E                       >(c); } //@hle:syscall{D8DE5C1E|SysMemUserForUser|SysMemUserForUser_D8DE5C1E|g|??? SysMemUserForUser_D8DE5C1E()}
extern "C" void __cdecl SysMemUserForUser_DB83A952(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_DB83A952                       >(c); } //@hle:syscall{DB83A952|SysMemUserForUser|SysMemUserForUser_DB83A952|g|??? SysMemUserForUser_DB83A952()}
extern "C" void __cdecl SysMemUserForUser_EBD5C3E6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_EBD5C3E6                       >(c); } //@hle:syscall{EBD5C3E6|SysMemUserForUser|SysMemUserForUser_EBD5C3E6|g|??? SysMemUserForUser_EBD5C3E6()}
extern "C" void __cdecl SysMemUserForUser_FE707FDF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::SysMemUserForUser::SysMemUserForUser_FE707FDF                       >(c); } //@hle:syscall{FE707FDF|SysMemUserForUser|SysMemUserForUser_FE707FDF|g|??? SysMemUserForUser_FE707FDF()}