//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(sircs.prx)sceSircs.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceSircs //@hle:library-start{sceSircs|sceSIRCS_IrDA_Driver|sircs.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{71EEF62D|sceSircs|sceSircsSend|ggg|int sceSircsSend(struct sircs_data * sd, int count)}
        int  sceSircsSend(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{83381633|sceSircs|sceSircsReceive|g|??? sceSircsReceive()}
        int  sceSircsReceive()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceSircs|sceSIRCS_IrDA_Driver|sircs.prx}
}

extern "C" bool __cdecl sceSircs$Init() { return hle::sceSircs::Init(); }
extern "C" bool __cdecl sceSircs$Fini() { return hle::sceSircs::Fini(); }
extern "C" void __cdecl sceSircs_71EEF62D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSircs::sceSircsSend                                     >(c); } //@hle:syscall{71EEF62D|sceSircs|sceSircsSend|ggg|int sceSircsSend(struct sircs_data * sd, int count)}
extern "C" void __cdecl sceSircs_83381633(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceSircs::sceSircsReceive                                  >(c); } //@hle:syscall{83381633|sceSircs|sceSircsReceive|g|??? sceSircsReceive()}