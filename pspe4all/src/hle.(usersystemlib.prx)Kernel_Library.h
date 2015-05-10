//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_usersystemlib_prx_Kernel_Library_h__
#define hle_usersystemlib_prx_Kernel_Library_h__

namespace hle
{
    namespace Kernel_Library //@hle:library-start{Kernel_Library|sceKernelLibrary|usersystemlib.prx}
    {
        //@hle:function{092968F4|Kernel_Library|sceKernelCpuSuspendIntr|g|unsigned int sceKernelCpuSuspendIntr(void)}
        extern int  sceKernelCpuSuspendIntr();
        //@hle:function{15B6446B|Kernel_Library|sceKernelUnlockLwMutex|g|??? sceKernelUnlockLwMutex()}
        extern int  sceKernelUnlockLwMutex();
        //@hle:function{1FC64E09|Kernel_Library|sceKernelLockLwMutexCB|g|??? sceKernelLockLwMutexCB()}
        extern int  sceKernelLockLwMutexCB();
        //@hle:function{3B84732D|Kernel_Library|sceKernelCpuResumeIntrWithSync|0g|void sceKernelCpuResumeIntrWithSync(unsigned int flags)}
        extern void sceKernelCpuResumeIntrWithSync(u32 $a0);
        //@hle:function{47A0B729|Kernel_Library|sceKernelIsCpuIntrSuspended|gg|int sceKernelIsCpuIntrSuspended(unsigned int flags)}
        extern int  sceKernelIsCpuIntrSuspended(u32 $a0);
        //@hle:function{5F10D406|Kernel_Library|sceKernelCpuResumeIntr|0g|void sceKernelCpuResumeIntr(unsigned int flags)}
        extern void sceKernelCpuResumeIntr(u32 $a0);
        //@hle:function{B55249D2|Kernel_Library|sceKernelIsCpuIntrEnable|g|int sceKernelIsCpuIntrEnable(void)}
        extern int  sceKernelIsCpuIntrEnable();
        //@hle:function{BEA46419|Kernel_Library|sceKernelLockLwMutex|g|??? sceKernelLockLwMutex()}
        extern int  sceKernelLockLwMutex();
        //@hle:function{C1734599|Kernel_Library|sceKernelReferLwMutexStatus|g|??? sceKernelReferLwMutexStatus()}
        extern int  sceKernelReferLwMutexStatus();
        //@hle:function{DC692EE3|Kernel_Library|sceKernelTryLockLwMutex|g|??? sceKernelTryLockLwMutex()}
        extern int  sceKernelTryLockLwMutex();
    } //@hle:library-end{Kernel_Library|sceKernelLibrary|usersystemlib.prx}
}
#endif