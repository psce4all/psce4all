//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_sysmem_prx_SysMemUserForUser_h__
#define hle_sysmem_prx_SysMemUserForUser_h__

namespace hle
{
    namespace SysMemUserForUser //@hle:library-start{SysMemUserForUser|sceSystemMemoryManager|sysmem.prx}
    {
        //@hle:function{A291F107|SysMemUserForUser|sceKernelMaxFreeMemSize|g|unsigned int sceKernelMaxFreeMemSize(void)}
        extern int  sceKernelMaxFreeMemSize();
        //@hle:function{F919F628|SysMemUserForUser|sceKernelTotalFreeMemSize|g|unsigned int sceKernelTotalFreeMemSize(void)}
        extern int  sceKernelTotalFreeMemSize();
        //@hle:function{13A5ABEF|SysMemUserForUser|sceKernelPrintf|gg|void * sceKernelPrintf(const char * format, ...)}
        extern int  sceKernelPrintf(u32 $a0);
        //@hle:function{F77D77CB|SysMemUserForUser|sceKernelSetCompilerVersion|gg|int sceKernelSetCompilerVersion(unsigned int version)}
        extern int  sceKernelSetCompilerVersion(u32 $a0);
        //@hle:function{7591C7DB|SysMemUserForUser|sceKernelSetCompiledSdkVersion|gg|int sceKernelSetCompiledSdkVersion(unsigned int version)}
        extern int  sceKernelSetCompiledSdkVersion(u32 $a0);
        //@hle:function{3FC9AE6A|SysMemUserForUser|sceKernelDevkitVersion|g|int sceKernelDevkitVersion(void)}
        extern int  sceKernelDevkitVersion();
        //@hle:function{FC114573|SysMemUserForUser|sceKernelGetCompiledSdkVersion|g|??? sceKernelGetCompiledSdkVersion()}
        extern int  sceKernelGetCompiledSdkVersion();
        //@hle:function{237DBD4F|SysMemUserForUser|sceKernelAllocPartitionMemory|gggggg|SceUID sceKernelAllocPartitionMemory(SceUID partitionid, const char * name, int type, SceSize size, void * addr)}
        extern int  sceKernelAllocPartitionMemory(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{B6D61D02|SysMemUserForUser|sceKernelFreePartitionMemory|gg|int sceKernelFreePartitionMemory(SceUID blockid)}
        extern int  sceKernelFreePartitionMemory(u32 $a0);
        //@hle:function{9D9A5BA1|SysMemUserForUser|sceKernelGetBlockHeadAddr|gg|void * sceKernelGetBlockHeadAddr(SceUID blockid)}
        extern int  sceKernelGetBlockHeadAddr(u32 $a0);
        //@hle:function{2A3E5280|SysMemUserForUser|sceKernelQueryMemoryInfo|g|??? sceKernelQueryMemoryInfo()}
        extern int  sceKernelQueryMemoryInfo();
        //@hle:function{057E7380|SysMemUserForUser|SysMemUserForUser_057E7380|g|??? SysMemUserForUser_057E7380()}
        extern int  SysMemUserForUser_057E7380();
        //@hle:function{315AD3A0|SysMemUserForUser|SysMemUserForUser_315AD3A0|g|??? SysMemUserForUser_315AD3A0()}
        extern int  SysMemUserForUser_315AD3A0();
        //@hle:function{342061E5|SysMemUserForUser|SysMemUserForUser_342061E5|g|??? SysMemUserForUser_342061E5()}
        extern int  SysMemUserForUser_342061E5();
        //@hle:function{50F61D8A|SysMemUserForUser|SysMemUserForUser_50F61D8A|g|??? SysMemUserForUser_50F61D8A()}
        extern int  SysMemUserForUser_50F61D8A();
        //@hle:function{91DE343C|SysMemUserForUser|SysMemUserForUser_91DE343C|g|??? SysMemUserForUser_91DE343C()}
        extern int  SysMemUserForUser_91DE343C();
        //@hle:function{A6848DF8|SysMemUserForUser|SysMemUserForUser_A6848DF8|g|??? SysMemUserForUser_A6848DF8()}
        extern int  SysMemUserForUser_A6848DF8();
        //@hle:function{ACBD88CA|SysMemUserForUser|SysMemUserForUser_ACBD88CA|g|??? SysMemUserForUser_ACBD88CA()}
        extern int  SysMemUserForUser_ACBD88CA();
        //@hle:function{D8DE5C1E|SysMemUserForUser|SysMemUserForUser_D8DE5C1E|g|??? SysMemUserForUser_D8DE5C1E()}
        extern int  SysMemUserForUser_D8DE5C1E();
        //@hle:function{DB83A952|SysMemUserForUser|SysMemUserForUser_DB83A952|g|??? SysMemUserForUser_DB83A952()}
        extern int  SysMemUserForUser_DB83A952();
        //@hle:function{EBD5C3E6|SysMemUserForUser|SysMemUserForUser_EBD5C3E6|g|??? SysMemUserForUser_EBD5C3E6()}
        extern int  SysMemUserForUser_EBD5C3E6();
        //@hle:function{FE707FDF|SysMemUserForUser|SysMemUserForUser_FE707FDF|g|??? SysMemUserForUser_FE707FDF()}
        extern int  SysMemUserForUser_FE707FDF();
    } //@hle:library-end{SysMemUserForUser|sceSystemMemoryManager|sysmem.prx}
}
#endif