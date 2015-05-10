//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(openpsid.prx)sceDdrdb.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceDdrdb //@hle:library-start{sceDdrdb|sceOpenPSID_Service|openpsid.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{F013F8BF|sceDdrdb|sceDdrdb_F013F8BF|g|??? sceDdrdb_F013F8BF()}
        int  sceDdrdb_F013F8BF()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceDdrdb|sceOpenPSID_Service|openpsid.prx}
}

extern "C" bool __cdecl sceDdrdb$Init() { return hle::sceDdrdb::Init(); }
extern "C" bool __cdecl sceDdrdb$Fini() { return hle::sceDdrdb::Fini(); }
extern "C" void __cdecl sceDdrdb_F013F8BF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceDdrdb::sceDdrdb_F013F8BF                                >(c); } //@hle:syscall{F013F8BF|sceDdrdb|sceDdrdb_F013F8BF|g|??? sceDdrdb_F013F8BF()}