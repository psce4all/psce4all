//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_ctrl_prx_sceCtrl_h__
#define hle_ctrl_prx_sceCtrl_h__

namespace hle
{
    namespace sceCtrl //@hle:library-start{sceCtrl|sceController_Service|ctrl.prx}
    {
        //@hle:function{1F4011E6|sceCtrl|sceCtrlSetSamplingMode|gg|int sceCtrlSetSamplingMode(int mode)}
        extern int  sceCtrlSetSamplingMode(u32 $a0);
        //@hle:function{DA6B76A1|sceCtrl|sceCtrlGetSamplingMode|gg|int sceCtrlGetSamplingMode(int * pmode)}
        extern int  sceCtrlGetSamplingMode(u32 $a0);
        //@hle:function{6A2774F3|sceCtrl|sceCtrlSetSamplingCycle|gg|int sceCtrlSetSamplingCycle(int cycle)}
        extern int  sceCtrlSetSamplingCycle(u32 $a0);
        //@hle:function{02BAAD91|sceCtrl|sceCtrlGetSamplingCycle|gg|int sceCtrlGetSamplingCycle(int * pcycle)}
        extern int  sceCtrlGetSamplingCycle(u32 $a0);
        //@hle:function{A7144800|sceCtrl|sceCtrlSetIdleCancelThreshold|ggg|int sceCtrlSetIdleCancelThreshold(int unhold_threshold, int hold_threshold)}
        extern int  sceCtrlSetIdleCancelThreshold(u32 $a0, u32 $a1);
        //@hle:function{687660FA|sceCtrl|sceCtrlGetIdleCancelThreshold|ggg|int sceCtrlGetIdleCancelThreshold(int * unhold_threshold, int * hold_threshold)}
        extern int  sceCtrlGetIdleCancelThreshold(u32 $a0, u32 $a1);
        //@hle:function{3A622550|sceCtrl|sceCtrlPeekBufferPositive|ggg|int sceCtrlPeekBufferPositive(SceCtrlData * pad_data, int count)}
        extern int  sceCtrlPeekBufferPositive(u32 $a0, u32 $a1);
        //@hle:function{C152080A|sceCtrl|sceCtrlPeekBufferNegative|ggg|int sceCtrlPeekBufferNegative(SceCtrlData * pad_data, int count)}
        extern int  sceCtrlPeekBufferNegative(u32 $a0, u32 $a1);
        //@hle:function{1F803938|sceCtrl|sceCtrlReadBufferPositive|ggg|int sceCtrlReadBufferPositive(SceCtrlData * pad_data, int count)}
        extern int  sceCtrlReadBufferPositive(u32 $a0, u32 $a1);
        //@hle:function{60B81F86|sceCtrl|sceCtrlReadBufferNegative|ggg|int sceCtrlReadBufferNegative(SceCtrlData * pad_data, int count)}
        extern int  sceCtrlReadBufferNegative(u32 $a0, u32 $a1);
        //@hle:function{B1D0E5CD|sceCtrl|sceCtrlPeekLatch|gg|int sceCtrlPeekLatch(SceCtrlLatch * latch_data)}
        extern int  sceCtrlPeekLatch(u32 $a0);
        //@hle:function{0B588501|sceCtrl|sceCtrlReadLatch|gg|int sceCtrlReadLatch(SceCtrlLatch * latch_data)}
        extern int  sceCtrlReadLatch(u32 $a0);
        //@hle:function{A68FD260|sceCtrl|sceCtrlClearRapidFire|g|??? sceCtrlClearRapidFire()}
        extern int  sceCtrlClearRapidFire();
        //@hle:function{6841BE1A|sceCtrl|sceCtrlSetRapidFire|g|??? sceCtrlSetRapidFire()}
        extern int  sceCtrlSetRapidFire();
        //@hle:function{348D99D4|sceCtrl|sceCtrl_348D99D4|g|??? sceCtrl_348D99D4()}
        extern int  sceCtrl_348D99D4();
        //@hle:function{AF5960F3|sceCtrl|sceCtrl_AF5960F3|g|??? sceCtrl_AF5960F3()}
        extern int  sceCtrl_AF5960F3();
    } //@hle:library-end{sceCtrl|sceController_Service|ctrl.prx}
}
#endif