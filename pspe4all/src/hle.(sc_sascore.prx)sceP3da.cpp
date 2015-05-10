//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(sc_sascore.prx)sceP3da.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceP3da //@hle:library-start{sceP3da|sceSAScore|sc_sascore.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{013016F3|sceP3da|sceP3daBridgeCore|g|??? sceP3daBridgeCore()}
        int  sceP3daBridgeCore()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{374500A5|sceP3da|sceP3daBridgeInit|g|??? sceP3daBridgeInit()}
        int  sceP3daBridgeInit()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{43F756A2|sceP3da|sceP3daBridgeExit|g|??? sceP3daBridgeExit()}
        int  sceP3daBridgeExit()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceP3da|sceSAScore|sc_sascore.prx}
}

extern "C" bool __cdecl sceP3da$Init() { return hle::sceP3da::Init(); }
extern "C" bool __cdecl sceP3da$Fini() { return hle::sceP3da::Fini(); }
extern "C" void __cdecl sceP3da_013016F3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceP3da::sceP3daBridgeCore                                >(c); } //@hle:syscall{013016F3|sceP3da|sceP3daBridgeCore|g|??? sceP3daBridgeCore()}
extern "C" void __cdecl sceP3da_374500A5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceP3da::sceP3daBridgeInit                                >(c); } //@hle:syscall{374500A5|sceP3da|sceP3daBridgeInit|g|??? sceP3daBridgeInit()}
extern "C" void __cdecl sceP3da_43F756A2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceP3da::sceP3daBridgeExit                                >(c); } //@hle:syscall{43F756A2|sceP3da|sceP3daBridgeExit|g|??? sceP3daBridgeExit()}