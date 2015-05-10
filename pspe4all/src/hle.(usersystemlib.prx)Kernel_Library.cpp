//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(usersystemlib.prx)Kernel_Library.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace Kernel_Library //@hle:library-start{Kernel_Library|sceKernelLibrary|usersystemlib.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{092968F4|Kernel_Library|sceKernelCpuSuspendIntr|g|unsigned int sceKernelCpuSuspendIntr(void)}
        int  sceKernelCpuSuspendIntr()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{15B6446B|Kernel_Library|sceKernelUnlockLwMutex|g|??? sceKernelUnlockLwMutex()}
        int  sceKernelUnlockLwMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1FC64E09|Kernel_Library|sceKernelLockLwMutexCB|g|??? sceKernelLockLwMutexCB()}
        int  sceKernelLockLwMutexCB()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3B84732D|Kernel_Library|sceKernelCpuResumeIntrWithSync|0g|void sceKernelCpuResumeIntrWithSync(unsigned int flags)}
        void sceKernelCpuResumeIntrWithSync(u32 $a0)
        {
            (void)($a0);
        }
        //@hle:function{47A0B729|Kernel_Library|sceKernelIsCpuIntrSuspended|gg|int sceKernelIsCpuIntrSuspended(unsigned int flags)}
        int  sceKernelIsCpuIntrSuspended(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5F10D406|Kernel_Library|sceKernelCpuResumeIntr|0g|void sceKernelCpuResumeIntr(unsigned int flags)}
        void sceKernelCpuResumeIntr(u32 $a0)
        {
            (void)($a0);
        }
        //@hle:function{B55249D2|Kernel_Library|sceKernelIsCpuIntrEnable|g|int sceKernelIsCpuIntrEnable(void)}
        int  sceKernelIsCpuIntrEnable()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BEA46419|Kernel_Library|sceKernelLockLwMutex|g|??? sceKernelLockLwMutex()}
        int  sceKernelLockLwMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C1734599|Kernel_Library|sceKernelReferLwMutexStatus|g|??? sceKernelReferLwMutexStatus()}
        int  sceKernelReferLwMutexStatus()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DC692EE3|Kernel_Library|sceKernelTryLockLwMutex|g|??? sceKernelTryLockLwMutex()}
        int  sceKernelTryLockLwMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{Kernel_Library|sceKernelLibrary|usersystemlib.prx}
}

extern "C" bool __cdecl Kernel_Library$Init() { return hle::Kernel_Library::Init(); }
extern "C" bool __cdecl Kernel_Library$Fini() { return hle::Kernel_Library::Fini(); }
extern "C" void __cdecl Kernel_Library_092968F4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::Kernel_Library::sceKernelCpuSuspendIntr                          >(c); } //@hle:syscall{092968F4|Kernel_Library|sceKernelCpuSuspendIntr|g|unsigned int sceKernelCpuSuspendIntr(void)}
extern "C" void __cdecl Kernel_Library_15B6446B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::Kernel_Library::sceKernelUnlockLwMutex                           >(c); } //@hle:syscall{15B6446B|Kernel_Library|sceKernelUnlockLwMutex|g|??? sceKernelUnlockLwMutex()}
extern "C" void __cdecl Kernel_Library_1FC64E09(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::Kernel_Library::sceKernelLockLwMutexCB                           >(c); } //@hle:syscall{1FC64E09|Kernel_Library|sceKernelLockLwMutexCB|g|??? sceKernelLockLwMutexCB()}
extern "C" void __cdecl Kernel_Library_3B84732D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0g              < hle::Kernel_Library::sceKernelCpuResumeIntrWithSync                   >(c); } //@hle:syscall{3B84732D|Kernel_Library|sceKernelCpuResumeIntrWithSync|0g|void sceKernelCpuResumeIntrWithSync(unsigned int flags)}
extern "C" void __cdecl Kernel_Library_47A0B729(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::Kernel_Library::sceKernelIsCpuIntrSuspended                      >(c); } //@hle:syscall{47A0B729|Kernel_Library|sceKernelIsCpuIntrSuspended|gg|int sceKernelIsCpuIntrSuspended(unsigned int flags)}
extern "C" void __cdecl Kernel_Library_5F10D406(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0g              < hle::Kernel_Library::sceKernelCpuResumeIntr                           >(c); } //@hle:syscall{5F10D406|Kernel_Library|sceKernelCpuResumeIntr|0g|void sceKernelCpuResumeIntr(unsigned int flags)}
extern "C" void __cdecl Kernel_Library_B55249D2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::Kernel_Library::sceKernelIsCpuIntrEnable                         >(c); } //@hle:syscall{B55249D2|Kernel_Library|sceKernelIsCpuIntrEnable|g|int sceKernelIsCpuIntrEnable(void)}
extern "C" void __cdecl Kernel_Library_BEA46419(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::Kernel_Library::sceKernelLockLwMutex                             >(c); } //@hle:syscall{BEA46419|Kernel_Library|sceKernelLockLwMutex|g|??? sceKernelLockLwMutex()}
extern "C" void __cdecl Kernel_Library_C1734599(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::Kernel_Library::sceKernelReferLwMutexStatus                      >(c); } //@hle:syscall{C1734599|Kernel_Library|sceKernelReferLwMutexStatus|g|??? sceKernelReferLwMutexStatus()}
extern "C" void __cdecl Kernel_Library_DC692EE3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::Kernel_Library::sceKernelTryLockLwMutex                          >(c); } //@hle:syscall{DC692EE3|Kernel_Library|sceKernelTryLockLwMutex|g|??? sceKernelTryLockLwMutex()}