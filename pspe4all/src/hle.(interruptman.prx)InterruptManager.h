//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_interruptman_prx_InterruptManager_h__
#define hle_interruptman_prx_InterruptManager_h__

namespace hle
{
    namespace InterruptManager //@hle:library-start{InterruptManager|sceInterruptManager|interruptman.prx}
    {
        //@hle:function{CA04A2B9|InterruptManager|sceKernelRegisterSubIntrHandler|ggggg|int sceKernelRegisterSubIntrHandler(int intno, int no, void * handler, void * arg)}
        extern int  sceKernelRegisterSubIntrHandler(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{D61E6961|InterruptManager|sceKernelReleaseSubIntrHandler|ggg|int sceKernelReleaseSubIntrHandler(int intno, int no)}
        extern int  sceKernelReleaseSubIntrHandler(u32 $a0, u32 $a1);
        //@hle:function{EEE43F47|InterruptManager|sceKernelRegisterUserSpaceIntrStack|g|??? sceKernelRegisterUserSpaceIntrStack()}
        extern int  sceKernelRegisterUserSpaceIntrStack();
        //@hle:function{FB8E22EC|InterruptManager|sceKernelEnableSubIntr|ggg|int sceKernelEnableSubIntr(int intno, int no)}
        extern int  sceKernelEnableSubIntr(u32 $a0, u32 $a1);
        //@hle:function{8A389411|InterruptManager|sceKernelDisableSubIntr|ggg|int sceKernelDisableSubIntr(int intno, int no)}
        extern int  sceKernelDisableSubIntr(u32 $a0, u32 $a1);
        //@hle:function{5CB5A78B|InterruptManager|sceKernelSuspendSubIntr|gggg|int sceKernelSuspendSubIntr(int intno, int no, int * state)}
        extern int  sceKernelSuspendSubIntr(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{7860E0DC|InterruptManager|sceKernelResumeSubIntr|gggg|int sceKernelResumeSubIntr(int intno, int no, int state)}
        extern int  sceKernelResumeSubIntr(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{FC4374B8|InterruptManager|sceKernelIsSubInterruptOccurred|ggg|int sceKernelIsSubInterruptOccurred(int intno, int no)}
        extern int  sceKernelIsSubInterruptOccurred(u32 $a0, u32 $a1);
        //@hle:function{D2E8363F|InterruptManager|QueryIntrHandlerInfo|gggg|int QueryIntrHandlerInfo(int intno, int no, SceSubIntrHandlerInfo * info)}
        extern int  QueryIntrHandlerInfo(u32 $a0, u32 $a1, u32 $a2);
    } //@hle:library-end{InterruptManager|sceInterruptManager|interruptman.prx}
}
#endif