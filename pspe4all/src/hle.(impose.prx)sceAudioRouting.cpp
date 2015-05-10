//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(impose.prx)sceAudioRouting.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceAudioRouting //@hle:library-start{sceAudioRouting|sceImpose_Driver|impose.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{28235C56|sceAudioRouting|sceAudioRoutingGetVolumeMode|g|??? sceAudioRoutingGetVolumeMode()}
        int  sceAudioRoutingGetVolumeMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{36FD8AA9|sceAudioRouting|sceAudioRoutingSetMode|g|??? sceAudioRoutingSetMode()}
        int  sceAudioRoutingSetMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{39240E7D|sceAudioRouting|sceAudioRoutingGetMode|g|??? sceAudioRoutingGetMode()}
        int  sceAudioRoutingGetMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BB548475|sceAudioRouting|sceAudioRoutingSetVolumeMode|g|??? sceAudioRoutingSetVolumeMode()}
        int  sceAudioRoutingSetVolumeMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceAudioRouting|sceImpose_Driver|impose.prx}
}

extern "C" bool __cdecl sceAudioRouting$Init() { return hle::sceAudioRouting::Init(); }
extern "C" bool __cdecl sceAudioRouting$Fini() { return hle::sceAudioRouting::Fini(); }
extern "C" void __cdecl sceAudioRouting_28235C56(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudioRouting::sceAudioRoutingGetVolumeMode                     >(c); } //@hle:syscall{28235C56|sceAudioRouting|sceAudioRoutingGetVolumeMode|g|??? sceAudioRoutingGetVolumeMode()}
extern "C" void __cdecl sceAudioRouting_36FD8AA9(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudioRouting::sceAudioRoutingSetMode                           >(c); } //@hle:syscall{36FD8AA9|sceAudioRouting|sceAudioRoutingSetMode|g|??? sceAudioRoutingSetMode()}
extern "C" void __cdecl sceAudioRouting_39240E7D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudioRouting::sceAudioRoutingGetMode                           >(c); } //@hle:syscall{39240E7D|sceAudioRouting|sceAudioRoutingGetMode|g|??? sceAudioRoutingGetMode()}
extern "C" void __cdecl sceAudioRouting_BB548475(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudioRouting::sceAudioRoutingSetVolumeMode                     >(c); } //@hle:syscall{BB548475|sceAudioRouting|sceAudioRoutingSetVolumeMode|g|??? sceAudioRoutingSetVolumeMode()}