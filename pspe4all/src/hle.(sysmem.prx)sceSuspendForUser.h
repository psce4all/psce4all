//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_sysmem_prx_sceSuspendForUser_h__
#define hle_sysmem_prx_sceSuspendForUser_h__

namespace hle
{
    namespace sceSuspendForUser //@hle:library-start{sceSuspendForUser|sceSystemMemoryManager|sysmem.prx}
    {
        //@hle:function{EADB1BD7|sceSuspendForUser|sceKernelPowerLock|gg|int sceKernelPowerLock(int locktype)}
        extern int  sceKernelPowerLock(u32 $a0);
        //@hle:function{3AEE7261|sceSuspendForUser|sceKernelPowerUnlock|gg|int sceKernelPowerUnlock(int locktype)}
        extern int  sceKernelPowerUnlock(u32 $a0);
        //@hle:function{090CCB3F|sceSuspendForUser|sceKernelPowerTick|gg|int sceKernelPowerTick(int ticktype)}
        extern int  sceKernelPowerTick(u32 $a0);
        //@hle:function{3E0271D3|sceSuspendForUser|sceKernelVolatileMemLock|gggg|int sceKernelVolatileMemLock(int arg, void * * ppAdr, unsigned int * puiSize)}
        extern int  sceKernelVolatileMemLock(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{A14F40B2|sceSuspendForUser|sceKernelVolatileMemTryLock|gggg|int sceKernelVolatileMemTryLock(int arg, void * * ppAdr, unsigned int * puiSize)}
        extern int  sceKernelVolatileMemTryLock(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{A569E425|sceSuspendForUser|sceKernelVolatileMemUnlock|gg|int sceKernelVolatileMemUnlock(int arg)}
        extern int  sceKernelVolatileMemUnlock(u32 $a0);
    } //@hle:library-end{sceSuspendForUser|sceSystemMemoryManager|sysmem.prx}
}
#endif