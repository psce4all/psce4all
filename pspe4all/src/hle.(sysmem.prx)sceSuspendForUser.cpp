//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(sysmem.prx)sceSuspendForUser.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "emu.log.h"
#include "lle.cpu(Allegrex).Context.h"
#include "hle.kd.h"

namespace hle
{
    namespace sceSuspendForUser //@hle:library-start{sceSuspendForUser|sceSystemMemoryManager|sysmem.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{EADB1BD7|sceSuspendForUser|sceKernelPowerLock|gg|int sceKernelPowerLock(int locktype)}
        int  sceKernelPowerLock(u32 $a0)
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED sceKernelPowerLock");
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3AEE7261|sceSuspendForUser|sceKernelPowerUnlock|gg|int sceKernelPowerUnlock(int locktype)}
        int  sceKernelPowerUnlock(u32 $a0)
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED sceKernelPowerUnlock");
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{090CCB3F|sceSuspendForUser|sceKernelPowerTick|gg|int sceKernelPowerTick(int ticktype)}
        int  sceKernelPowerTick(u32 $a0)
        {
            TODO(implement me);
            errorf(kd, "UNIMPLEMENTED sceKernelPowerTick");
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3E0271D3|sceSuspendForUser|sceKernelVolatileMemLock|gggg|int sceKernelVolatileMemLock(int arg, void * * ppAdr, unsigned int * puiSize)}
        int  sceKernelVolatileMemLock(u32 $a0, u32 $a1, u32 $a2)
        {
            return kd::KernelVolatileMemLock(int($a0), p32< p32< void > >($a1), p32< unsigned int >($a2), false);
        }
        //@hle:function{A14F40B2|sceSuspendForUser|sceKernelVolatileMemTryLock|gggg|int sceKernelVolatileMemTryLock(int arg, void * * ppAdr, unsigned int * puiSize)}
        int  sceKernelVolatileMemTryLock(u32 $a0, u32 $a1, u32 $a2)
        {
            return kd::KernelVolatileMemLock(int($a0), p32< p32< void > >($a1), p32< unsigned int >($a2), true);
        }
        //@hle:function{A569E425|sceSuspendForUser|sceKernelVolatileMemUnlock|gg|int sceKernelVolatileMemUnlock(int arg)}
        int  sceKernelVolatileMemUnlock(u32 $a0)
        {
            return kd::KernelVolatileMemUnlock(int($a0));
        }
    } //@hle:library-end{sceSuspendForUser|sceSystemMemoryManager|sysmem.prx}
}

extern "C" bool __cdecl sceSuspendForUser$Init() { return hle::sceSuspendForUser::Init(); }
extern "C" bool __cdecl sceSuspendForUser$Fini() { return hle::sceSuspendForUser::Fini(); }
extern "C" void __cdecl sceSuspendForUser_EADB1BD7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceSuspendForUser::sceKernelPowerLock                               >(c); } //@hle:syscall{EADB1BD7|sceSuspendForUser|sceKernelPowerLock|gg|int sceKernelPowerLock(int locktype)}
extern "C" void __cdecl sceSuspendForUser_3AEE7261(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceSuspendForUser::sceKernelPowerUnlock                             >(c); } //@hle:syscall{3AEE7261|sceSuspendForUser|sceKernelPowerUnlock|gg|int sceKernelPowerUnlock(int locktype)}
extern "C" void __cdecl sceSuspendForUser_090CCB3F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceSuspendForUser::sceKernelPowerTick                               >(c); } //@hle:syscall{090CCB3F|sceSuspendForUser|sceKernelPowerTick|gg|int sceKernelPowerTick(int ticktype)}
extern "C" void __cdecl sceSuspendForUser_3E0271D3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSuspendForUser::sceKernelVolatileMemLock                         >(c); } //@hle:syscall{3E0271D3|sceSuspendForUser|sceKernelVolatileMemLock|gggg|int sceKernelVolatileMemLock(int arg, void * * ppAdr, unsigned int * puiSize)}
extern "C" void __cdecl sceSuspendForUser_A14F40B2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSuspendForUser::sceKernelVolatileMemTryLock                      >(c); } //@hle:syscall{A14F40B2|sceSuspendForUser|sceKernelVolatileMemTryLock|gggg|int sceKernelVolatileMemTryLock(int arg, void * * ppAdr, unsigned int * puiSize)}
extern "C" void __cdecl sceSuspendForUser_A569E425(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceSuspendForUser::sceKernelVolatileMemUnlock                       >(c); } //@hle:syscall{A569E425|sceSuspendForUser|sceKernelVolatileMemUnlock|gg|int sceKernelVolatileMemUnlock(int arg)}