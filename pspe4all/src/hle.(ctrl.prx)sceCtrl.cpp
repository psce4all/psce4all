//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(ctrl.prx)sceCtrl.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceCtrl //@hle:library-start{sceCtrl|sceController_Service|ctrl.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{1F4011E6|sceCtrl|sceCtrlSetSamplingMode|gg|int sceCtrlSetSamplingMode(int mode)}
        int  sceCtrlSetSamplingMode(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DA6B76A1|sceCtrl|sceCtrlGetSamplingMode|gg|int sceCtrlGetSamplingMode(int * pmode)}
        int  sceCtrlGetSamplingMode(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6A2774F3|sceCtrl|sceCtrlSetSamplingCycle|gg|int sceCtrlSetSamplingCycle(int cycle)}
        int  sceCtrlSetSamplingCycle(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{02BAAD91|sceCtrl|sceCtrlGetSamplingCycle|gg|int sceCtrlGetSamplingCycle(int * pcycle)}
        int  sceCtrlGetSamplingCycle(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A7144800|sceCtrl|sceCtrlSetIdleCancelThreshold|ggg|int sceCtrlSetIdleCancelThreshold(int unhold_threshold, int hold_threshold)}
        int  sceCtrlSetIdleCancelThreshold(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{687660FA|sceCtrl|sceCtrlGetIdleCancelThreshold|ggg|int sceCtrlGetIdleCancelThreshold(int * unhold_threshold, int * hold_threshold)}
        int  sceCtrlGetIdleCancelThreshold(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3A622550|sceCtrl|sceCtrlPeekBufferPositive|ggg|int sceCtrlPeekBufferPositive(SceCtrlData * pad_data, int count)}
        int  sceCtrlPeekBufferPositive(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C152080A|sceCtrl|sceCtrlPeekBufferNegative|ggg|int sceCtrlPeekBufferNegative(SceCtrlData * pad_data, int count)}
        int  sceCtrlPeekBufferNegative(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1F803938|sceCtrl|sceCtrlReadBufferPositive|ggg|int sceCtrlReadBufferPositive(SceCtrlData * pad_data, int count)}
        int  sceCtrlReadBufferPositive(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{60B81F86|sceCtrl|sceCtrlReadBufferNegative|ggg|int sceCtrlReadBufferNegative(SceCtrlData * pad_data, int count)}
        int  sceCtrlReadBufferNegative(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B1D0E5CD|sceCtrl|sceCtrlPeekLatch|gg|int sceCtrlPeekLatch(SceCtrlLatch * latch_data)}
        int  sceCtrlPeekLatch(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0B588501|sceCtrl|sceCtrlReadLatch|gg|int sceCtrlReadLatch(SceCtrlLatch * latch_data)}
        int  sceCtrlReadLatch(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A68FD260|sceCtrl|sceCtrlClearRapidFire|g|??? sceCtrlClearRapidFire()}
        int  sceCtrlClearRapidFire()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6841BE1A|sceCtrl|sceCtrlSetRapidFire|g|??? sceCtrlSetRapidFire()}
        int  sceCtrlSetRapidFire()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{348D99D4|sceCtrl|sceCtrl_348D99D4|g|??? sceCtrl_348D99D4()}
        int  sceCtrl_348D99D4()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AF5960F3|sceCtrl|sceCtrl_AF5960F3|g|??? sceCtrl_AF5960F3()}
        int  sceCtrl_AF5960F3()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceCtrl|sceController_Service|ctrl.prx}
}

extern "C" bool __cdecl sceCtrl$Init() { return hle::sceCtrl::Init(); }
extern "C" bool __cdecl sceCtrl$Fini() { return hle::sceCtrl::Fini(); }
extern "C" void __cdecl sceCtrl_1F4011E6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceCtrl::sceCtrlSetSamplingMode                           >(c); } //@hle:syscall{1F4011E6|sceCtrl|sceCtrlSetSamplingMode|gg|int sceCtrlSetSamplingMode(int mode)}
extern "C" void __cdecl sceCtrl_DA6B76A1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceCtrl::sceCtrlGetSamplingMode                           >(c); } //@hle:syscall{DA6B76A1|sceCtrl|sceCtrlGetSamplingMode|gg|int sceCtrlGetSamplingMode(int * pmode)}
extern "C" void __cdecl sceCtrl_6A2774F3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceCtrl::sceCtrlSetSamplingCycle                          >(c); } //@hle:syscall{6A2774F3|sceCtrl|sceCtrlSetSamplingCycle|gg|int sceCtrlSetSamplingCycle(int cycle)}
extern "C" void __cdecl sceCtrl_02BAAD91(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceCtrl::sceCtrlGetSamplingCycle                          >(c); } //@hle:syscall{02BAAD91|sceCtrl|sceCtrlGetSamplingCycle|gg|int sceCtrlGetSamplingCycle(int * pcycle)}
extern "C" void __cdecl sceCtrl_A7144800(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceCtrl::sceCtrlSetIdleCancelThreshold                    >(c); } //@hle:syscall{A7144800|sceCtrl|sceCtrlSetIdleCancelThreshold|ggg|int sceCtrlSetIdleCancelThreshold(int unhold_threshold, int hold_threshold)}
extern "C" void __cdecl sceCtrl_687660FA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceCtrl::sceCtrlGetIdleCancelThreshold                    >(c); } //@hle:syscall{687660FA|sceCtrl|sceCtrlGetIdleCancelThreshold|ggg|int sceCtrlGetIdleCancelThreshold(int * unhold_threshold, int * hold_threshold)}
extern "C" void __cdecl sceCtrl_3A622550(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceCtrl::sceCtrlPeekBufferPositive                        >(c); } //@hle:syscall{3A622550|sceCtrl|sceCtrlPeekBufferPositive|ggg|int sceCtrlPeekBufferPositive(SceCtrlData * pad_data, int count)}
extern "C" void __cdecl sceCtrl_C152080A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceCtrl::sceCtrlPeekBufferNegative                        >(c); } //@hle:syscall{C152080A|sceCtrl|sceCtrlPeekBufferNegative|ggg|int sceCtrlPeekBufferNegative(SceCtrlData * pad_data, int count)}
extern "C" void __cdecl sceCtrl_1F803938(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceCtrl::sceCtrlReadBufferPositive                        >(c); } //@hle:syscall{1F803938|sceCtrl|sceCtrlReadBufferPositive|ggg|int sceCtrlReadBufferPositive(SceCtrlData * pad_data, int count)}
extern "C" void __cdecl sceCtrl_60B81F86(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceCtrl::sceCtrlReadBufferNegative                        >(c); } //@hle:syscall{60B81F86|sceCtrl|sceCtrlReadBufferNegative|ggg|int sceCtrlReadBufferNegative(SceCtrlData * pad_data, int count)}
extern "C" void __cdecl sceCtrl_B1D0E5CD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceCtrl::sceCtrlPeekLatch                                 >(c); } //@hle:syscall{B1D0E5CD|sceCtrl|sceCtrlPeekLatch|gg|int sceCtrlPeekLatch(SceCtrlLatch * latch_data)}
extern "C" void __cdecl sceCtrl_0B588501(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceCtrl::sceCtrlReadLatch                                 >(c); } //@hle:syscall{0B588501|sceCtrl|sceCtrlReadLatch|gg|int sceCtrlReadLatch(SceCtrlLatch * latch_data)}
extern "C" void __cdecl sceCtrl_A68FD260(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceCtrl::sceCtrlClearRapidFire                            >(c); } //@hle:syscall{A68FD260|sceCtrl|sceCtrlClearRapidFire|g|??? sceCtrlClearRapidFire()}
extern "C" void __cdecl sceCtrl_6841BE1A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceCtrl::sceCtrlSetRapidFire                              >(c); } //@hle:syscall{6841BE1A|sceCtrl|sceCtrlSetRapidFire|g|??? sceCtrlSetRapidFire()}
extern "C" void __cdecl sceCtrl_348D99D4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceCtrl::sceCtrl_348D99D4                                 >(c); } //@hle:syscall{348D99D4|sceCtrl|sceCtrl_348D99D4|g|??? sceCtrl_348D99D4()}
extern "C" void __cdecl sceCtrl_AF5960F3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceCtrl::sceCtrl_AF5960F3                                 >(c); } //@hle:syscall{AF5960F3|sceCtrl|sceCtrl_AF5960F3|g|??? sceCtrl_AF5960F3()}