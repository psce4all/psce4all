//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(wlan.prx)sceWlanDrv.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceWlanDrv //@hle:library-start{sceWlanDrv|sceWlan_Driver|wlan.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{0C622081|sceWlanDrv|sceWlanGetEtherAddr|gg|int sceWlanGetEtherAddr(char * etherAddr)}
        int  sceWlanGetEtherAddr(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{93440B11|sceWlanDrv|sceWlanDevIsPowerOn|g|int sceWlanDevIsPowerOn(void)}
        int  sceWlanDevIsPowerOn()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D7763699|sceWlanDrv|sceWlanGetSwitchState|g|int sceWlanGetSwitchState(void)}
        int  sceWlanGetSwitchState()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceWlanDrv|sceWlan_Driver|wlan.prx}
}

extern "C" bool __cdecl sceWlanDrv$Init() { return hle::sceWlanDrv::Init(); }
extern "C" bool __cdecl sceWlanDrv$Fini() { return hle::sceWlanDrv::Fini(); }
extern "C" void __cdecl sceWlanDrv_0C622081(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceWlanDrv::sceWlanGetEtherAddr                              >(c); } //@hle:syscall{0C622081|sceWlanDrv|sceWlanGetEtherAddr|gg|int sceWlanGetEtherAddr(char * etherAddr)}
extern "C" void __cdecl sceWlanDrv_93440B11(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceWlanDrv::sceWlanDevIsPowerOn                              >(c); } //@hle:syscall{93440B11|sceWlanDrv|sceWlanDevIsPowerOn|g|int sceWlanDevIsPowerOn(void)}
extern "C" void __cdecl sceWlanDrv_D7763699(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceWlanDrv::sceWlanGetSwitchState                            >(c); } //@hle:syscall{D7763699|sceWlanDrv|sceWlanGetSwitchState|g|int sceWlanGetSwitchState(void)}