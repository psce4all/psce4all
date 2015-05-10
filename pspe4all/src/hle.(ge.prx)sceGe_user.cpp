//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(ge.prx)sceGe_user.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceGe_user //@hle:library-start{sceGe_user|sceGE_Manager|ge.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{1F6752AD|sceGe_user|sceGeEdramGetSize|g|unsigned int sceGeEdramGetSize(void)}
        int  sceGeEdramGetSize()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E47E40E4|sceGe_user|sceGeEdramGetAddr|g|void * sceGeEdramGetAddr(void)}
        int  sceGeEdramGetAddr()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B77905EA|sceGe_user|sceGeEdramSetAddrTranslation|gg|??? sceGeEdramSetAddrTranslation()}
        int  sceGeEdramSetAddrTranslation(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DC93CFEF|sceGe_user|sceGeGetCmd|gg|unsigned int sceGeGetCmd(int cmd)}
        int  sceGeGetCmd(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{57C8945B|sceGe_user|sceGeGetMtx|ggg|unsigned int sceGeGetMtx(int type, void * matrix)}
        int  sceGeGetMtx(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{438A385A|sceGe_user|sceGeSaveContext|gg|int sceGeSaveContext(SceGeContext * context)}
        int  sceGeSaveContext(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0BF608FB|sceGe_user|sceGeRestoreContext|gg|int sceGeRestoreContext(const SceGeContext * context)}
        int  sceGeRestoreContext(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AB49E76A|sceGe_user|sceGeListEnQueue|ggggg|int sceGeListEnQueue(const void * madr, void * sadr, int cbid, const SceGeListOptParam * opt)}
        int  sceGeListEnQueue(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1C0D95A6|sceGe_user|sceGeListEnQueueHead|ggggg|int sceGeListEnQueueHead(const void * madr, void * sadr, int cbid, const SceGeListOptParam * opt)}
        int  sceGeListEnQueueHead(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5FB86AB0|sceGe_user|sceGeListDeQueue|gg|int sceGeListDeQueue(int dlid)}
        int  sceGeListDeQueue(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E0D68148|sceGe_user|sceGeListUpdateStallAddr|ggg|int sceGeListUpdateStallAddr(int dlid, void * sadr)}
        int  sceGeListUpdateStallAddr(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{03444EB4|sceGe_user|sceGeListSync|ggg|int sceGeListSync(int dlid, int mode)}
        int  sceGeListSync(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B287BD61|sceGe_user|sceGeDrawSync|gg|int sceGeDrawSync(int mode)}
        int  sceGeDrawSync(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B448EC0D|sceGe_user|sceGeBreak|ggg|int sceGeBreak(int mode, SceGeBreakParam * param)}
        int  sceGeBreak(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4C06E472|sceGe_user|sceGeContinue|g|int sceGeContinue(void)}
        int  sceGeContinue()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A4FC06A4|sceGe_user|sceGeSetCallback|gg|int sceGeSetCallback(const SceGeCbParam * param)}
        int  sceGeSetCallback(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{05DB22CE|sceGe_user|sceGeUnsetCallback|gg|int sceGeUnsetCallback(int cbid)}
        int  sceGeUnsetCallback(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E66CB92E|sceGe_user|sceGeGetStack|ggggg|int sceGeGetStack(int arg1, int arg2, int arg3, int arg4)}
        int  sceGeGetStack(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceGe_user|sceGE_Manager|ge.prx}
}

extern "C" bool __cdecl sceGe_user$Init() { return hle::sceGe_user::Init(); }
extern "C" bool __cdecl sceGe_user$Fini() { return hle::sceGe_user::Fini(); }
extern "C" void __cdecl sceGe_user_1F6752AD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceGe_user::sceGeEdramGetSize                                >(c); } //@hle:syscall{1F6752AD|sceGe_user|sceGeEdramGetSize|g|unsigned int sceGeEdramGetSize(void)}
extern "C" void __cdecl sceGe_user_E47E40E4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceGe_user::sceGeEdramGetAddr                                >(c); } //@hle:syscall{E47E40E4|sceGe_user|sceGeEdramGetAddr|g|void * sceGeEdramGetAddr(void)}
extern "C" void __cdecl sceGe_user_B77905EA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceGe_user::sceGeEdramSetAddrTranslation                     >(c); } //@hle:syscall{B77905EA|sceGe_user|sceGeEdramSetAddrTranslation|gg|??? sceGeEdramSetAddrTranslation()}
extern "C" void __cdecl sceGe_user_DC93CFEF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceGe_user::sceGeGetCmd                                      >(c); } //@hle:syscall{DC93CFEF|sceGe_user|sceGeGetCmd|gg|unsigned int sceGeGetCmd(int cmd)}
extern "C" void __cdecl sceGe_user_57C8945B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceGe_user::sceGeGetMtx                                      >(c); } //@hle:syscall{57C8945B|sceGe_user|sceGeGetMtx|ggg|unsigned int sceGeGetMtx(int type, void * matrix)}
extern "C" void __cdecl sceGe_user_438A385A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceGe_user::sceGeSaveContext                                 >(c); } //@hle:syscall{438A385A|sceGe_user|sceGeSaveContext|gg|int sceGeSaveContext(SceGeContext * context)}
extern "C" void __cdecl sceGe_user_0BF608FB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceGe_user::sceGeRestoreContext                              >(c); } //@hle:syscall{0BF608FB|sceGe_user|sceGeRestoreContext|gg|int sceGeRestoreContext(const SceGeContext * context)}
extern "C" void __cdecl sceGe_user_AB49E76A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceGe_user::sceGeListEnQueue                                 >(c); } //@hle:syscall{AB49E76A|sceGe_user|sceGeListEnQueue|ggggg|int sceGeListEnQueue(const void * madr, void * sadr, int cbid, const SceGeListOptParam * opt)}
extern "C" void __cdecl sceGe_user_1C0D95A6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceGe_user::sceGeListEnQueueHead                             >(c); } //@hle:syscall{1C0D95A6|sceGe_user|sceGeListEnQueueHead|ggggg|int sceGeListEnQueueHead(const void * madr, void * sadr, int cbid, const SceGeListOptParam * opt)}
extern "C" void __cdecl sceGe_user_5FB86AB0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceGe_user::sceGeListDeQueue                                 >(c); } //@hle:syscall{5FB86AB0|sceGe_user|sceGeListDeQueue|gg|int sceGeListDeQueue(int dlid)}
extern "C" void __cdecl sceGe_user_E0D68148(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceGe_user::sceGeListUpdateStallAddr                         >(c); } //@hle:syscall{E0D68148|sceGe_user|sceGeListUpdateStallAddr|ggg|int sceGeListUpdateStallAddr(int dlid, void * sadr)}
extern "C" void __cdecl sceGe_user_03444EB4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceGe_user::sceGeListSync                                    >(c); } //@hle:syscall{03444EB4|sceGe_user|sceGeListSync|ggg|int sceGeListSync(int dlid, int mode)}
extern "C" void __cdecl sceGe_user_B287BD61(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceGe_user::sceGeDrawSync                                    >(c); } //@hle:syscall{B287BD61|sceGe_user|sceGeDrawSync|gg|int sceGeDrawSync(int mode)}
extern "C" void __cdecl sceGe_user_B448EC0D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceGe_user::sceGeBreak                                       >(c); } //@hle:syscall{B448EC0D|sceGe_user|sceGeBreak|ggg|int sceGeBreak(int mode, SceGeBreakParam * param)}
extern "C" void __cdecl sceGe_user_4C06E472(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceGe_user::sceGeContinue                                    >(c); } //@hle:syscall{4C06E472|sceGe_user|sceGeContinue|g|int sceGeContinue(void)}
extern "C" void __cdecl sceGe_user_A4FC06A4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceGe_user::sceGeSetCallback                                 >(c); } //@hle:syscall{A4FC06A4|sceGe_user|sceGeSetCallback|gg|int sceGeSetCallback(const SceGeCbParam * param)}
extern "C" void __cdecl sceGe_user_05DB22CE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceGe_user::sceGeUnsetCallback                               >(c); } //@hle:syscall{05DB22CE|sceGe_user|sceGeUnsetCallback|gg|int sceGeUnsetCallback(int cbid)}
extern "C" void __cdecl sceGe_user_E66CB92E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceGe_user::sceGeGetStack                                    >(c); } //@hle:syscall{E66CB92E|sceGe_user|sceGeGetStack|ggggg|int sceGeGetStack(int arg1, int arg2, int arg3, int arg4)}