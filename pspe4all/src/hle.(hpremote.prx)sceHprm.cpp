//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(hpremote.prx)sceHprm.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceHprm //@hle:library-start{sceHprm|sceHP_Remote_Driver|hpremote.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{1910B327|sceHprm|sceHprmPeekCurrentKey|gg|int sceHprmPeekCurrentKey(u32 * key)}
        int  sceHprmPeekCurrentKey(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{208DB1BD|sceHprm|sceHprmIsRemoteExist|g|int sceHprmIsRemoteExist(void)}
        int  sceHprmIsRemoteExist()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{219C58F1|sceHprm|sceHprmIsMicrophoneExist|g|int sceHprmIsMicrophoneExist(void)}
        int  sceHprmIsMicrophoneExist()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2BCEC83E|sceHprm|sceHprmPeekLatch|gg|int sceHprmPeekLatch(u32 * latch)}
        int  sceHprmPeekLatch(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3953DE6B|sceHprm|sceHprm_3953DE6B|g|??? sceHprm_3953DE6B()}
        int  sceHprm_3953DE6B()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{396FD885|sceHprm|sceHprm_396FD885|g|??? sceHprm_396FD885()}
        int  sceHprm_396FD885()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{40D2F9F0|sceHprm|sceHprmReadLatch|gg|int sceHprmReadLatch(u32 * latch)}
        int  sceHprmReadLatch(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{444ED0B7|sceHprm|sceHprmUnregitserCallback|g|??? sceHprmUnregitserCallback()}
        int  sceHprmUnregitserCallback()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{71B5FB67|sceHprm|sceHprmGetHpDetect|g|??? sceHprmGetHpDetect()}
        int  sceHprmGetHpDetect()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7E69EDA4|sceHprm|sceHprmIsHeadphoneExist|g|int sceHprmIsHeadphoneExist(void)}
        int  sceHprmIsHeadphoneExist()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C7154136|sceHprm|sceHprmRegisterCallback|g|??? sceHprmRegisterCallback()}
        int  sceHprmRegisterCallback()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FD7DE6CD|sceHprm|sceHprm_FD7DE6CD|g|??? sceHprm_FD7DE6CD()}
        int  sceHprm_FD7DE6CD()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceHprm|sceHP_Remote_Driver|hpremote.prx}
}

extern "C" bool __cdecl sceHprm$Init() { return hle::sceHprm::Init(); }
extern "C" bool __cdecl sceHprm$Fini() { return hle::sceHprm::Fini(); }
extern "C" void __cdecl sceHprm_1910B327(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceHprm::sceHprmPeekCurrentKey                            >(c); } //@hle:syscall{1910B327|sceHprm|sceHprmPeekCurrentKey|gg|int sceHprmPeekCurrentKey(u32 * key)}
extern "C" void __cdecl sceHprm_208DB1BD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceHprm::sceHprmIsRemoteExist                             >(c); } //@hle:syscall{208DB1BD|sceHprm|sceHprmIsRemoteExist|g|int sceHprmIsRemoteExist(void)}
extern "C" void __cdecl sceHprm_219C58F1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceHprm::sceHprmIsMicrophoneExist                         >(c); } //@hle:syscall{219C58F1|sceHprm|sceHprmIsMicrophoneExist|g|int sceHprmIsMicrophoneExist(void)}
extern "C" void __cdecl sceHprm_2BCEC83E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceHprm::sceHprmPeekLatch                                 >(c); } //@hle:syscall{2BCEC83E|sceHprm|sceHprmPeekLatch|gg|int sceHprmPeekLatch(u32 * latch)}
extern "C" void __cdecl sceHprm_3953DE6B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceHprm::sceHprm_3953DE6B                                 >(c); } //@hle:syscall{3953DE6B|sceHprm|sceHprm_3953DE6B|g|??? sceHprm_3953DE6B()}
extern "C" void __cdecl sceHprm_396FD885(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceHprm::sceHprm_396FD885                                 >(c); } //@hle:syscall{396FD885|sceHprm|sceHprm_396FD885|g|??? sceHprm_396FD885()}
extern "C" void __cdecl sceHprm_40D2F9F0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceHprm::sceHprmReadLatch                                 >(c); } //@hle:syscall{40D2F9F0|sceHprm|sceHprmReadLatch|gg|int sceHprmReadLatch(u32 * latch)}
extern "C" void __cdecl sceHprm_444ED0B7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceHprm::sceHprmUnregitserCallback                        >(c); } //@hle:syscall{444ED0B7|sceHprm|sceHprmUnregitserCallback|g|??? sceHprmUnregitserCallback()}
extern "C" void __cdecl sceHprm_71B5FB67(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceHprm::sceHprmGetHpDetect                               >(c); } //@hle:syscall{71B5FB67|sceHprm|sceHprmGetHpDetect|g|??? sceHprmGetHpDetect()}
extern "C" void __cdecl sceHprm_7E69EDA4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceHprm::sceHprmIsHeadphoneExist                          >(c); } //@hle:syscall{7E69EDA4|sceHprm|sceHprmIsHeadphoneExist|g|int sceHprmIsHeadphoneExist(void)}
extern "C" void __cdecl sceHprm_C7154136(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceHprm::sceHprmRegisterCallback                          >(c); } //@hle:syscall{C7154136|sceHprm|sceHprmRegisterCallback|g|??? sceHprmRegisterCallback()}
extern "C" void __cdecl sceHprm_FD7DE6CD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceHprm::sceHprm_FD7DE6CD                                 >(c); } //@hle:syscall{FD7DE6CD|sceHprm|sceHprm_FD7DE6CD|g|??? sceHprm_FD7DE6CD()}