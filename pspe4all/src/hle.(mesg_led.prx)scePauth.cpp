//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(mesg_led.prx)scePauth.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace scePauth //@hle:library-start{scePauth|sceMesgLed|mesg_led.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{F7AA47F6|scePauth|scePauth_F7AA47F6|g|??? scePauth_F7AA47F6()}
        int  scePauth_F7AA47F6()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{scePauth|sceMesgLed|mesg_led.prx}
}

extern "C" bool __cdecl scePauth$Init() { return hle::scePauth::Init(); }
extern "C" bool __cdecl scePauth$Fini() { return hle::scePauth::Fini(); }
extern "C" void __cdecl scePauth_F7AA47F6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePauth::scePauth_F7AA47F6                                >(c); } //@hle:syscall{F7AA47F6|scePauth|scePauth_F7AA47F6|g|??? scePauth_F7AA47F6()}