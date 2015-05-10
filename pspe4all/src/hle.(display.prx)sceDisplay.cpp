//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(display.prx)sceDisplay.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceDisplay //@hle:library-start{sceDisplay|sceDisplay_Service|display.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{0E20F177|sceDisplay|sceDisplaySetMode|gggg|int sceDisplaySetMode(int mode, int width, int height)}
        int  sceDisplaySetMode(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DEA197D4|sceDisplay|sceDisplayGetMode|gggg|int sceDisplayGetMode(int * mode, int * width, int * height)}
        int  sceDisplayGetMode(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DBA6C4C4|sceDisplay|sceDisplayGetFramePerSec|f|float sceDisplayGetFramePerSec(void)}
        f32  sceDisplayGetFramePerSec()
        {
            f32 $f0;
            $f0 = 0.0f;
            return $f0;
        }
        //@hle:function{289D82FE|sceDisplay|sceDisplaySetFrameBuf|0gggg|void sceDisplaySetFrameBuf(void * frame_buffer, int frame_width, int pixel_format, int mode)}
        void sceDisplaySetFrameBuf(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
        }
        //@hle:function{EEDA2E54|sceDisplay|sceDisplayGetFrameBuf|ggggg|int sceDisplayGetFrameBuf(void * * frame_buffer, int * frame_width, int * pixelformat, int * mode)}
        int  sceDisplayGetFrameBuf(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B4F378FA|sceDisplay|sceDisplayIsForeground|g|int sceDisplayIsForeground(void)}
        int  sceDisplayIsForeground()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7ED59BC4|sceDisplay|sceDisplaySetHoldMode|gg|int sceDisplaySetHoldMode(int mode)}
        int  sceDisplaySetHoldMode(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9C6EAAD7|sceDisplay|sceDisplayGetVcount|g|int sceDisplayGetVcount(void)}
        int  sceDisplayGetVcount()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4D4E10EC|sceDisplay|sceDisplayIsVblank|g|??? sceDisplayIsVblank()}
        int  sceDisplayIsVblank()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{69B53541|sceDisplay|sceDisplayGetVblankRest|g|??? sceDisplayGetVblankRest()}
        int  sceDisplayGetVblankRest()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{36CDFADE|sceDisplay|sceDisplayWaitVblank|g|int sceDisplayWaitVblank(void)}
        int  sceDisplayWaitVblank()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8EB9EC49|sceDisplay|sceDisplayWaitVblankCB|g|int sceDisplayWaitVblankCB(void)}
        int  sceDisplayWaitVblankCB()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{984C27E7|sceDisplay|sceDisplayWaitVblankStart|g|int sceDisplayWaitVblankStart(void)}
        int  sceDisplayWaitVblankStart()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{46F186C3|sceDisplay|sceDisplayWaitVblankStartCB|g|int sceDisplayWaitVblankStartCB(void)}
        int  sceDisplayWaitVblankStartCB()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{21038913|sceDisplay|sceDisplayIsVsync|g|int sceDisplayIsVsync(void)}
        int  sceDisplayIsVsync()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{773DD3A3|sceDisplay|sceDisplayGetCurrentHcount|g|??? sceDisplayGetCurrentHcount()}
        int  sceDisplayGetCurrentHcount()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{210EAB3A|sceDisplay|sceDisplayGetAccumulatedHcount|g|??? sceDisplayGetAccumulatedHcount()}
        int  sceDisplayGetAccumulatedHcount()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A83EF139|sceDisplay|sceDisplayAdjustAccumulatedHcount|g|??? sceDisplayAdjustAccumulatedHcount()}
        int  sceDisplayAdjustAccumulatedHcount()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A544C486|sceDisplay|sceDisplaySetResumeMode|g|??? sceDisplaySetResumeMode()}
        int  sceDisplaySetResumeMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BF79F646|sceDisplay|sceDisplayGetResumeMode|g|??? sceDisplayGetResumeMode()}
        int  sceDisplayGetResumeMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{31C4BAA8|sceDisplay|sceDisplayGetBrightness|g|??? sceDisplayGetBrightness()}
        int  sceDisplayGetBrightness()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{40F1469C|sceDisplay|sceDisplay_40F1469C|g|??? sceDisplay_40F1469C()}
        int  sceDisplay_40F1469C()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{77ED8B3A|sceDisplay|sceDisplay_77ED8B3A|g|??? sceDisplay_77ED8B3A()}
        int  sceDisplay_77ED8B3A()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceDisplay|sceDisplay_Service|display.prx}
}

extern "C" bool __cdecl sceDisplay$Init() { return hle::sceDisplay::Init(); }
extern "C" bool __cdecl sceDisplay$Fini() { return hle::sceDisplay::Fini(); }
extern "C" void __cdecl sceDisplay_0E20F177(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceDisplay::sceDisplaySetMode                                >(c); } //@hle:syscall{0E20F177|sceDisplay|sceDisplaySetMode|gggg|int sceDisplaySetMode(int mode, int width, int height)}
extern "C" void __cdecl sceDisplay_DEA197D4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceDisplay::sceDisplayGetMode                                >(c); } //@hle:syscall{DEA197D4|sceDisplay|sceDisplayGetMode|gggg|int sceDisplayGetMode(int * mode, int * width, int * height)}
extern "C" void __cdecl sceDisplay_DBA6C4C4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$f               < hle::sceDisplay::sceDisplayGetFramePerSec                         >(c); } //@hle:syscall{DBA6C4C4|sceDisplay|sceDisplayGetFramePerSec|f|float sceDisplayGetFramePerSec(void)}
extern "C" void __cdecl sceDisplay_289D82FE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0gggg           < hle::sceDisplay::sceDisplaySetFrameBuf                            >(c); } //@hle:syscall{289D82FE|sceDisplay|sceDisplaySetFrameBuf|0gggg|void sceDisplaySetFrameBuf(void * frame_buffer, int frame_width, int pixel_format, int mode)}
extern "C" void __cdecl sceDisplay_EEDA2E54(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceDisplay::sceDisplayGetFrameBuf                            >(c); } //@hle:syscall{EEDA2E54|sceDisplay|sceDisplayGetFrameBuf|ggggg|int sceDisplayGetFrameBuf(void * * frame_buffer, int * frame_width, int * pixelformat, int * mode)}
extern "C" void __cdecl sceDisplay_B4F378FA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayIsForeground                           >(c); } //@hle:syscall{B4F378FA|sceDisplay|sceDisplayIsForeground|g|int sceDisplayIsForeground(void)}
extern "C" void __cdecl sceDisplay_7ED59BC4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceDisplay::sceDisplaySetHoldMode                            >(c); } //@hle:syscall{7ED59BC4|sceDisplay|sceDisplaySetHoldMode|gg|int sceDisplaySetHoldMode(int mode)}
extern "C" void __cdecl sceDisplay_9C6EAAD7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayGetVcount                              >(c); } //@hle:syscall{9C6EAAD7|sceDisplay|sceDisplayGetVcount|g|int sceDisplayGetVcount(void)}
extern "C" void __cdecl sceDisplay_4D4E10EC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayIsVblank                               >(c); } //@hle:syscall{4D4E10EC|sceDisplay|sceDisplayIsVblank|g|??? sceDisplayIsVblank()}
extern "C" void __cdecl sceDisplay_69B53541(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayGetVblankRest                          >(c); } //@hle:syscall{69B53541|sceDisplay|sceDisplayGetVblankRest|g|??? sceDisplayGetVblankRest()}
extern "C" void __cdecl sceDisplay_36CDFADE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayWaitVblank                             >(c); } //@hle:syscall{36CDFADE|sceDisplay|sceDisplayWaitVblank|g|int sceDisplayWaitVblank(void)}
extern "C" void __cdecl sceDisplay_8EB9EC49(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayWaitVblankCB                           >(c); } //@hle:syscall{8EB9EC49|sceDisplay|sceDisplayWaitVblankCB|g|int sceDisplayWaitVblankCB(void)}
extern "C" void __cdecl sceDisplay_984C27E7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayWaitVblankStart                        >(c); } //@hle:syscall{984C27E7|sceDisplay|sceDisplayWaitVblankStart|g|int sceDisplayWaitVblankStart(void)}
extern "C" void __cdecl sceDisplay_46F186C3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayWaitVblankStartCB                      >(c); } //@hle:syscall{46F186C3|sceDisplay|sceDisplayWaitVblankStartCB|g|int sceDisplayWaitVblankStartCB(void)}
extern "C" void __cdecl sceDisplay_21038913(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayIsVsync                                >(c); } //@hle:syscall{21038913|sceDisplay|sceDisplayIsVsync|g|int sceDisplayIsVsync(void)}
extern "C" void __cdecl sceDisplay_773DD3A3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayGetCurrentHcount                       >(c); } //@hle:syscall{773DD3A3|sceDisplay|sceDisplayGetCurrentHcount|g|??? sceDisplayGetCurrentHcount()}
extern "C" void __cdecl sceDisplay_210EAB3A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayGetAccumulatedHcount                   >(c); } //@hle:syscall{210EAB3A|sceDisplay|sceDisplayGetAccumulatedHcount|g|??? sceDisplayGetAccumulatedHcount()}
extern "C" void __cdecl sceDisplay_A83EF139(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayAdjustAccumulatedHcount                >(c); } //@hle:syscall{A83EF139|sceDisplay|sceDisplayAdjustAccumulatedHcount|g|??? sceDisplayAdjustAccumulatedHcount()}
extern "C" void __cdecl sceDisplay_A544C486(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplaySetResumeMode                          >(c); } //@hle:syscall{A544C486|sceDisplay|sceDisplaySetResumeMode|g|??? sceDisplaySetResumeMode()}
extern "C" void __cdecl sceDisplay_BF79F646(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayGetResumeMode                          >(c); } //@hle:syscall{BF79F646|sceDisplay|sceDisplayGetResumeMode|g|??? sceDisplayGetResumeMode()}
extern "C" void __cdecl sceDisplay_31C4BAA8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplayGetBrightness                          >(c); } //@hle:syscall{31C4BAA8|sceDisplay|sceDisplayGetBrightness|g|??? sceDisplayGetBrightness()}
extern "C" void __cdecl sceDisplay_40F1469C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplay_40F1469C                              >(c); } //@hle:syscall{40F1469C|sceDisplay|sceDisplay_40F1469C|g|??? sceDisplay_40F1469C()}
extern "C" void __cdecl sceDisplay_77ED8B3A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDisplay::sceDisplay_77ED8B3A                              >(c); } //@hle:syscall{77ED8B3A|sceDisplay|sceDisplay_77ED8B3A|g|??? sceDisplay_77ED8B3A()}