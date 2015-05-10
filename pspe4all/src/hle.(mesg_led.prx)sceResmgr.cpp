//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(mesg_led.prx)sceResmgr.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceResmgr //@hle:library-start{sceResmgr|sceMesgLed|mesg_led.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{9DC14891|sceResmgr|sceResmgr_9DC14891|g|??? sceResmgr_9DC14891()}
        int  sceResmgr_9DC14891()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceResmgr|sceMesgLed|mesg_led.prx}
}

extern "C" bool __cdecl sceResmgr$Init() { return hle::sceResmgr::Init(); }
extern "C" bool __cdecl sceResmgr$Fini() { return hle::sceResmgr::Fini(); }
extern "C" void __cdecl sceResmgr_9DC14891(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceResmgr::sceResmgr_9DC14891                               >(c); } //@hle:syscall{9DC14891|sceResmgr|sceResmgr_9DC14891|g|??? sceResmgr_9DC14891()}