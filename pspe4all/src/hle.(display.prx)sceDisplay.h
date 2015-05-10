//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_display_prx_sceDisplay_h__
#define hle_display_prx_sceDisplay_h__

namespace hle
{
    namespace sceDisplay //@hle:library-start{sceDisplay|sceDisplay_Service|display.prx}
    {
        //@hle:function{0E20F177|sceDisplay|sceDisplaySetMode|gggg|int sceDisplaySetMode(int mode, int width, int height)}
        extern int  sceDisplaySetMode(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{DEA197D4|sceDisplay|sceDisplayGetMode|gggg|int sceDisplayGetMode(int * mode, int * width, int * height)}
        extern int  sceDisplayGetMode(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{DBA6C4C4|sceDisplay|sceDisplayGetFramePerSec|f|float sceDisplayGetFramePerSec(void)}
        extern f32  sceDisplayGetFramePerSec();
        //@hle:function{289D82FE|sceDisplay|sceDisplaySetFrameBuf|0gggg|void sceDisplaySetFrameBuf(void * frame_buffer, int frame_width, int pixel_format, int mode)}
        extern void sceDisplaySetFrameBuf(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{EEDA2E54|sceDisplay|sceDisplayGetFrameBuf|ggggg|int sceDisplayGetFrameBuf(void * * frame_buffer, int * frame_width, int * pixelformat, int * mode)}
        extern int  sceDisplayGetFrameBuf(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{B4F378FA|sceDisplay|sceDisplayIsForeground|g|int sceDisplayIsForeground(void)}
        extern int  sceDisplayIsForeground();
        //@hle:function{7ED59BC4|sceDisplay|sceDisplaySetHoldMode|gg|int sceDisplaySetHoldMode(int mode)}
        extern int  sceDisplaySetHoldMode(u32 $a0);
        //@hle:function{9C6EAAD7|sceDisplay|sceDisplayGetVcount|g|int sceDisplayGetVcount(void)}
        extern int  sceDisplayGetVcount();
        //@hle:function{4D4E10EC|sceDisplay|sceDisplayIsVblank|g|??? sceDisplayIsVblank()}
        extern int  sceDisplayIsVblank();
        //@hle:function{69B53541|sceDisplay|sceDisplayGetVblankRest|g|??? sceDisplayGetVblankRest()}
        extern int  sceDisplayGetVblankRest();
        //@hle:function{36CDFADE|sceDisplay|sceDisplayWaitVblank|g|int sceDisplayWaitVblank(void)}
        extern int  sceDisplayWaitVblank();
        //@hle:function{8EB9EC49|sceDisplay|sceDisplayWaitVblankCB|g|int sceDisplayWaitVblankCB(void)}
        extern int  sceDisplayWaitVblankCB();
        //@hle:function{984C27E7|sceDisplay|sceDisplayWaitVblankStart|g|int sceDisplayWaitVblankStart(void)}
        extern int  sceDisplayWaitVblankStart();
        //@hle:function{46F186C3|sceDisplay|sceDisplayWaitVblankStartCB|g|int sceDisplayWaitVblankStartCB(void)}
        extern int  sceDisplayWaitVblankStartCB();
        //@hle:function{21038913|sceDisplay|sceDisplayIsVsync|g|int sceDisplayIsVsync(void)}
        extern int  sceDisplayIsVsync();
        //@hle:function{773DD3A3|sceDisplay|sceDisplayGetCurrentHcount|g|??? sceDisplayGetCurrentHcount()}
        extern int  sceDisplayGetCurrentHcount();
        //@hle:function{210EAB3A|sceDisplay|sceDisplayGetAccumulatedHcount|g|??? sceDisplayGetAccumulatedHcount()}
        extern int  sceDisplayGetAccumulatedHcount();
        //@hle:function{A83EF139|sceDisplay|sceDisplayAdjustAccumulatedHcount|g|??? sceDisplayAdjustAccumulatedHcount()}
        extern int  sceDisplayAdjustAccumulatedHcount();
        //@hle:function{A544C486|sceDisplay|sceDisplaySetResumeMode|g|??? sceDisplaySetResumeMode()}
        extern int  sceDisplaySetResumeMode();
        //@hle:function{BF79F646|sceDisplay|sceDisplayGetResumeMode|g|??? sceDisplayGetResumeMode()}
        extern int  sceDisplayGetResumeMode();
        //@hle:function{31C4BAA8|sceDisplay|sceDisplayGetBrightness|g|??? sceDisplayGetBrightness()}
        extern int  sceDisplayGetBrightness();
        //@hle:function{40F1469C|sceDisplay|sceDisplay_40F1469C|g|??? sceDisplay_40F1469C()}
        extern int  sceDisplay_40F1469C();
        //@hle:function{77ED8B3A|sceDisplay|sceDisplay_77ED8B3A|g|??? sceDisplay_77ED8B3A()}
        extern int  sceDisplay_77ED8B3A();
    } //@hle:library-end{sceDisplay|sceDisplay_Service|display.prx}
}
#endif