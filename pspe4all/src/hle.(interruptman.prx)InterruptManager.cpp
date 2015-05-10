//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(interruptman.prx)InterruptManager.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace InterruptManager //@hle:library-start{InterruptManager|sceInterruptManager|interruptman.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{CA04A2B9|InterruptManager|sceKernelRegisterSubIntrHandler|ggggg|int sceKernelRegisterSubIntrHandler(int intno, int no, void * handler, void * arg)}
        int  sceKernelRegisterSubIntrHandler(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D61E6961|InterruptManager|sceKernelReleaseSubIntrHandler|ggg|int sceKernelReleaseSubIntrHandler(int intno, int no)}
        int  sceKernelReleaseSubIntrHandler(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EEE43F47|InterruptManager|sceKernelRegisterUserSpaceIntrStack|g|??? sceKernelRegisterUserSpaceIntrStack()}
        int  sceKernelRegisterUserSpaceIntrStack()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FB8E22EC|InterruptManager|sceKernelEnableSubIntr|ggg|int sceKernelEnableSubIntr(int intno, int no)}
        int  sceKernelEnableSubIntr(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8A389411|InterruptManager|sceKernelDisableSubIntr|ggg|int sceKernelDisableSubIntr(int intno, int no)}
        int  sceKernelDisableSubIntr(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5CB5A78B|InterruptManager|sceKernelSuspendSubIntr|gggg|int sceKernelSuspendSubIntr(int intno, int no, int * state)}
        int  sceKernelSuspendSubIntr(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7860E0DC|InterruptManager|sceKernelResumeSubIntr|gggg|int sceKernelResumeSubIntr(int intno, int no, int state)}
        int  sceKernelResumeSubIntr(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FC4374B8|InterruptManager|sceKernelIsSubInterruptOccurred|ggg|int sceKernelIsSubInterruptOccurred(int intno, int no)}
        int  sceKernelIsSubInterruptOccurred(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D2E8363F|InterruptManager|QueryIntrHandlerInfo|gggg|int QueryIntrHandlerInfo(int intno, int no, SceSubIntrHandlerInfo * info)}
        int  QueryIntrHandlerInfo(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{InterruptManager|sceInterruptManager|interruptman.prx}
}

extern "C" bool __cdecl InterruptManager$Init() { return hle::InterruptManager::Init(); }
extern "C" bool __cdecl InterruptManager$Fini() { return hle::InterruptManager::Fini(); }
extern "C" void __cdecl InterruptManager_CA04A2B9(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::InterruptManager::sceKernelRegisterSubIntrHandler                  >(c); } //@hle:syscall{CA04A2B9|InterruptManager|sceKernelRegisterSubIntrHandler|ggggg|int sceKernelRegisterSubIntrHandler(int intno, int no, void * handler, void * arg)}
extern "C" void __cdecl InterruptManager_D61E6961(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::InterruptManager::sceKernelReleaseSubIntrHandler                   >(c); } //@hle:syscall{D61E6961|InterruptManager|sceKernelReleaseSubIntrHandler|ggg|int sceKernelReleaseSubIntrHandler(int intno, int no)}
extern "C" void __cdecl InterruptManager_EEE43F47(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::InterruptManager::sceKernelRegisterUserSpaceIntrStack              >(c); } //@hle:syscall{EEE43F47|InterruptManager|sceKernelRegisterUserSpaceIntrStack|g|??? sceKernelRegisterUserSpaceIntrStack()}
extern "C" void __cdecl InterruptManager_FB8E22EC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::InterruptManager::sceKernelEnableSubIntr                           >(c); } //@hle:syscall{FB8E22EC|InterruptManager|sceKernelEnableSubIntr|ggg|int sceKernelEnableSubIntr(int intno, int no)}
extern "C" void __cdecl InterruptManager_8A389411(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::InterruptManager::sceKernelDisableSubIntr                          >(c); } //@hle:syscall{8A389411|InterruptManager|sceKernelDisableSubIntr|ggg|int sceKernelDisableSubIntr(int intno, int no)}
extern "C" void __cdecl InterruptManager_5CB5A78B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::InterruptManager::sceKernelSuspendSubIntr                          >(c); } //@hle:syscall{5CB5A78B|InterruptManager|sceKernelSuspendSubIntr|gggg|int sceKernelSuspendSubIntr(int intno, int no, int * state)}
extern "C" void __cdecl InterruptManager_7860E0DC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::InterruptManager::sceKernelResumeSubIntr                           >(c); } //@hle:syscall{7860E0DC|InterruptManager|sceKernelResumeSubIntr|gggg|int sceKernelResumeSubIntr(int intno, int no, int state)}
extern "C" void __cdecl InterruptManager_FC4374B8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::InterruptManager::sceKernelIsSubInterruptOccurred                  >(c); } //@hle:syscall{FC4374B8|InterruptManager|sceKernelIsSubInterruptOccurred|ggg|int sceKernelIsSubInterruptOccurred(int intno, int no)}
extern "C" void __cdecl InterruptManager_D2E8363F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::InterruptManager::QueryIntrHandlerInfo                             >(c); } //@hle:syscall{D2E8363F|InterruptManager|QueryIntrHandlerInfo|gggg|int QueryIntrHandlerInfo(int intno, int no, SceSubIntrHandlerInfo * info)}