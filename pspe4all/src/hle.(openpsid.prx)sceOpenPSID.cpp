//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(openpsid.prx)sceOpenPSID.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceOpenPSID //@hle:library-start{sceOpenPSID|sceOpenPSID_Service|openpsid.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{C69BEBCE|sceOpenPSID|sceOpenPSIDGetOpenPSID|g|??? sceOpenPSIDGetOpenPSID()}
        int  sceOpenPSIDGetOpenPSID()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceOpenPSID|sceOpenPSID_Service|openpsid.prx}
}

extern "C" bool __cdecl sceOpenPSID$Init() { return hle::sceOpenPSID::Init(); }
extern "C" bool __cdecl sceOpenPSID$Fini() { return hle::sceOpenPSID::Fini(); }
extern "C" void __cdecl sceOpenPSID_C69BEBCE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceOpenPSID::sceOpenPSIDGetOpenPSID                           >(c); } //@hle:syscall{C69BEBCE|sceOpenPSID|sceOpenPSIDGetOpenPSID|g|??? sceOpenPSIDGetOpenPSID()}