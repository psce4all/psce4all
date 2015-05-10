//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(iofilemgr.prx)IoFileMgrForUser.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace IoFileMgrForUser //@hle:library-start{IoFileMgrForUser|sceIOFileManager|iofilemgr.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{B8A740F4|IoFileMgrForUser|sceIoChstat|gggg|int sceIoChstat(const char * file, SceIoStat * stat, int bits)}
        int  sceIoChstat(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{ACE946E8|IoFileMgrForUser|sceIoGetstat|ggg|int sceIoGetstat(const char * file, SceIoStat * stat)}
        int  sceIoGetstat(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CB05F8D6|IoFileMgrForUser|sceIoGetAsyncStat|gggg|int sceIoGetAsyncStat(SceUID fd, int poll, SceInt64 * res)}
        int  sceIoGetAsyncStat(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B29DDF9C|IoFileMgrForUser|sceIoDopen|gg|SceUID sceIoDopen(const char * dirname)}
        int  sceIoDopen(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EB092469|IoFileMgrForUser|sceIoDclose|gg|int sceIoDclose(SceUID fd)}
        int  sceIoDclose(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E3EB004C|IoFileMgrForUser|sceIoDread|ggg|int sceIoDread(SceUID fd, SceIoDirent * dir)}
        int  sceIoDread(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{06A70004|IoFileMgrForUser|sceIoMkdir|ggg|int sceIoMkdir(const char * path, SceMode mode)}
        int  sceIoMkdir(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1117C65F|IoFileMgrForUser|sceIoRmdir|gg|int sceIoRmdir(const char * path)}
        int  sceIoRmdir(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{55F4717D|IoFileMgrForUser|sceIoChdir|gg|int sceIoChdir(const char * path)}
        int  sceIoChdir(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{779103A0|IoFileMgrForUser|sceIoRename|ggg|int sceIoRename(const char * oldname, const char * newname)}
        int  sceIoRename(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F27A9C51|IoFileMgrForUser|sceIoRemove|gg|int sceIoRemove(const char * path)}
        int  sceIoRemove(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{54F5FB11|IoFileMgrForUser|sceIoDevctl|ggggggg|int sceIoDevctl(const char * dev, int cmd, void * indata, int inlen, void * outdata, int outlen)}
        int  sceIoDevctl(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AB96437F|IoFileMgrForUser|sceIoSync|ggg|int sceIoSync(const char * dev, int flag)}
        int  sceIoSync(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{08BD7374|IoFileMgrForUser|sceIoGetDevType|gg|int sceIoGetDevType(SceUID fd)}
        int  sceIoGetDevType(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{109F50BC|IoFileMgrForUser|sceIoOpen|gggg|SceUID sceIoOpen(const char * file, int flags, SceMode mode)}
        int  sceIoOpen(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{810C4BC3|IoFileMgrForUser|sceIoClose|gg|int sceIoClose(SceUID fd)}
        int  sceIoClose(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{63632449|IoFileMgrForUser|sceIoIoctl|ggggggg|int sceIoIoctl(SceUID fd, int cmd, void * indata, int inlen, void * outdata, int outlen)}
        int  sceIoIoctl(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{27EB27B8|IoFileMgrForUser|sceIoLseek|GgGg|SceOff sceIoLseek(SceUID fd, SceOff offset, int whence)}
        s64  sceIoLseek(u32 $a0, u64 $a3a2, u32 $a4)
        {
            (void)($a0, $a3a2, $a4);
            s64 $v1v0;
            $v1v0 = 0;
            return $v1v0;
        }
        //@hle:function{68963324|IoFileMgrForUser|sceIoLseek32|gggg|int sceIoLseek32(SceUID fd, int offset, int whence)}
        int  sceIoLseek32(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6A638D83|IoFileMgrForUser|sceIoRead|gggg|int sceIoRead(SceUID fd, void * data, SceSize size)}
        int  sceIoRead(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{42EC03AC|IoFileMgrForUser|sceIoWrite|gggg|int sceIoWrite(SceUID fd, const void * data, SceSize size)}
        int  sceIoWrite(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3251EA56|IoFileMgrForUser|sceIoPollAsync|ggg|int sceIoPollAsync(SceUID fd, SceInt64 * res)}
        int  sceIoPollAsync(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E23EEC33|IoFileMgrForUser|sceIoWaitAsync|ggg|int sceIoWaitAsync(SceUID fd, SceInt64 * res)}
        int  sceIoWaitAsync(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{35DBD746|IoFileMgrForUser|sceIoWaitAsyncCB|ggg|int sceIoWaitAsyncCB(SceUID fd, SceInt64 * res)}
        int  sceIoWaitAsyncCB(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A12A0514|IoFileMgrForUser|sceIoSetAsyncCallback|gggg|int sceIoSetAsyncCallback(SceUID fd, SceUID cb, void * argp)}
        int  sceIoSetAsyncCallback(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{89AA9906|IoFileMgrForUser|sceIoOpenAsync|gggg|SceUID sceIoOpenAsync(const char * file, int flags, SceMode mode)}
        int  sceIoOpenAsync(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FF5940B6|IoFileMgrForUser|sceIoCloseAsync|gg|int sceIoCloseAsync(SceUID fd)}
        int  sceIoCloseAsync(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E95A012B|IoFileMgrForUser|sceIoIoctlAsync|ggggggg|int sceIoIoctlAsync(SceUID fd, unsigned int cmd, void * indata, int inlen, void * outdata, int outlen)}
        int  sceIoIoctlAsync(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{71B19E77|IoFileMgrForUser|sceIoLseekAsync|gggg|int sceIoLseekAsync(SceUID fd, SceOff offset, int whence)}
        int  sceIoLseekAsync(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1B385D8F|IoFileMgrForUser|sceIoLseek32Async|gggg|int sceIoLseek32Async(SceUID fd, int offset, int whence)}
        int  sceIoLseek32Async(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A0B5A7C2|IoFileMgrForUser|sceIoReadAsync|gggg|int sceIoReadAsync(SceUID fd, void * data, SceSize size)}
        int  sceIoReadAsync(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0FACAB19|IoFileMgrForUser|sceIoWriteAsync|gggg|int sceIoWriteAsync(SceUID fd, const void * data, SceSize size)}
        int  sceIoWriteAsync(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B293727F|IoFileMgrForUser|sceIoChangeAsyncPriority|ggg|int sceIoChangeAsyncPriority(SceUID fd, int pri)}
        int  sceIoChangeAsyncPriority(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E8BC6571|IoFileMgrForUser|sceIoCancel|gg|int sceIoCancel(SceUID fd)}
        int  sceIoCancel(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5C2BE2CC|IoFileMgrForUser|sceIoGetFdList|gggg|int sceIoGetFdList(SceUID * readbuf, int size, int * fdcount)}
        int  sceIoGetFdList(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B2A628C1|IoFileMgrForUser|sceIoAssign|ggggggg|int sceIoAssign(const char * dev1, const char * dev2, const char * dev3, int mode, void * unk1, long unk2)}
        int  sceIoAssign(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6D08A871|IoFileMgrForUser|sceIoUnassign|gg|int sceIoUnassign(const char * dev)}
        int  sceIoUnassign(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{IoFileMgrForUser|sceIOFileManager|iofilemgr.prx}
}

extern "C" bool __cdecl IoFileMgrForUser$Init() { return hle::IoFileMgrForUser::Init(); }
extern "C" bool __cdecl IoFileMgrForUser$Fini() { return hle::IoFileMgrForUser::Fini(); }
extern "C" void __cdecl IoFileMgrForUser_B8A740F4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoChstat                                      >(c); } //@hle:syscall{B8A740F4|IoFileMgrForUser|sceIoChstat|gggg|int sceIoChstat(const char * file, SceIoStat * stat, int bits)}
extern "C" void __cdecl IoFileMgrForUser_ACE946E8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::IoFileMgrForUser::sceIoGetstat                                     >(c); } //@hle:syscall{ACE946E8|IoFileMgrForUser|sceIoGetstat|ggg|int sceIoGetstat(const char * file, SceIoStat * stat)}
extern "C" void __cdecl IoFileMgrForUser_CB05F8D6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoGetAsyncStat                                >(c); } //@hle:syscall{CB05F8D6|IoFileMgrForUser|sceIoGetAsyncStat|gggg|int sceIoGetAsyncStat(SceUID fd, int poll, SceInt64 * res)}
extern "C" void __cdecl IoFileMgrForUser_B29DDF9C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoDopen                                       >(c); } //@hle:syscall{B29DDF9C|IoFileMgrForUser|sceIoDopen|gg|SceUID sceIoDopen(const char * dirname)}
extern "C" void __cdecl IoFileMgrForUser_EB092469(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoDclose                                      >(c); } //@hle:syscall{EB092469|IoFileMgrForUser|sceIoDclose|gg|int sceIoDclose(SceUID fd)}
extern "C" void __cdecl IoFileMgrForUser_E3EB004C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::IoFileMgrForUser::sceIoDread                                       >(c); } //@hle:syscall{E3EB004C|IoFileMgrForUser|sceIoDread|ggg|int sceIoDread(SceUID fd, SceIoDirent * dir)}
extern "C" void __cdecl IoFileMgrForUser_06A70004(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::IoFileMgrForUser::sceIoMkdir                                       >(c); } //@hle:syscall{06A70004|IoFileMgrForUser|sceIoMkdir|ggg|int sceIoMkdir(const char * path, SceMode mode)}
extern "C" void __cdecl IoFileMgrForUser_1117C65F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoRmdir                                       >(c); } //@hle:syscall{1117C65F|IoFileMgrForUser|sceIoRmdir|gg|int sceIoRmdir(const char * path)}
extern "C" void __cdecl IoFileMgrForUser_55F4717D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoChdir                                       >(c); } //@hle:syscall{55F4717D|IoFileMgrForUser|sceIoChdir|gg|int sceIoChdir(const char * path)}
extern "C" void __cdecl IoFileMgrForUser_779103A0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::IoFileMgrForUser::sceIoRename                                      >(c); } //@hle:syscall{779103A0|IoFileMgrForUser|sceIoRename|ggg|int sceIoRename(const char * oldname, const char * newname)}
extern "C" void __cdecl IoFileMgrForUser_F27A9C51(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoRemove                                      >(c); } //@hle:syscall{F27A9C51|IoFileMgrForUser|sceIoRemove|gg|int sceIoRemove(const char * path)}
extern "C" void __cdecl IoFileMgrForUser_54F5FB11(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::IoFileMgrForUser::sceIoDevctl                                      >(c); } //@hle:syscall{54F5FB11|IoFileMgrForUser|sceIoDevctl|ggggggg|int sceIoDevctl(const char * dev, int cmd, void * indata, int inlen, void * outdata, int outlen)}
extern "C" void __cdecl IoFileMgrForUser_AB96437F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::IoFileMgrForUser::sceIoSync                                        >(c); } //@hle:syscall{AB96437F|IoFileMgrForUser|sceIoSync|ggg|int sceIoSync(const char * dev, int flag)}
extern "C" void __cdecl IoFileMgrForUser_08BD7374(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoGetDevType                                  >(c); } //@hle:syscall{08BD7374|IoFileMgrForUser|sceIoGetDevType|gg|int sceIoGetDevType(SceUID fd)}
extern "C" void __cdecl IoFileMgrForUser_109F50BC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoOpen                                        >(c); } //@hle:syscall{109F50BC|IoFileMgrForUser|sceIoOpen|gggg|SceUID sceIoOpen(const char * file, int flags, SceMode mode)}
extern "C" void __cdecl IoFileMgrForUser_810C4BC3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoClose                                       >(c); } //@hle:syscall{810C4BC3|IoFileMgrForUser|sceIoClose|gg|int sceIoClose(SceUID fd)}
extern "C" void __cdecl IoFileMgrForUser_63632449(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::IoFileMgrForUser::sceIoIoctl                                       >(c); } //@hle:syscall{63632449|IoFileMgrForUser|sceIoIoctl|ggggggg|int sceIoIoctl(SceUID fd, int cmd, void * indata, int inlen, void * outdata, int outlen)}
extern "C" void __cdecl IoFileMgrForUser_27EB27B8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$GgGg            < hle::IoFileMgrForUser::sceIoLseek                                       >(c); } //@hle:syscall{27EB27B8|IoFileMgrForUser|sceIoLseek|GgGg|SceOff sceIoLseek(SceUID fd, SceOff offset, int whence)}
extern "C" void __cdecl IoFileMgrForUser_68963324(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoLseek32                                     >(c); } //@hle:syscall{68963324|IoFileMgrForUser|sceIoLseek32|gggg|int sceIoLseek32(SceUID fd, int offset, int whence)}
extern "C" void __cdecl IoFileMgrForUser_6A638D83(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoRead                                        >(c); } //@hle:syscall{6A638D83|IoFileMgrForUser|sceIoRead|gggg|int sceIoRead(SceUID fd, void * data, SceSize size)}
extern "C" void __cdecl IoFileMgrForUser_42EC03AC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoWrite                                       >(c); } //@hle:syscall{42EC03AC|IoFileMgrForUser|sceIoWrite|gggg|int sceIoWrite(SceUID fd, const void * data, SceSize size)}
extern "C" void __cdecl IoFileMgrForUser_3251EA56(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::IoFileMgrForUser::sceIoPollAsync                                   >(c); } //@hle:syscall{3251EA56|IoFileMgrForUser|sceIoPollAsync|ggg|int sceIoPollAsync(SceUID fd, SceInt64 * res)}
extern "C" void __cdecl IoFileMgrForUser_E23EEC33(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::IoFileMgrForUser::sceIoWaitAsync                                   >(c); } //@hle:syscall{E23EEC33|IoFileMgrForUser|sceIoWaitAsync|ggg|int sceIoWaitAsync(SceUID fd, SceInt64 * res)}
extern "C" void __cdecl IoFileMgrForUser_35DBD746(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::IoFileMgrForUser::sceIoWaitAsyncCB                                 >(c); } //@hle:syscall{35DBD746|IoFileMgrForUser|sceIoWaitAsyncCB|ggg|int sceIoWaitAsyncCB(SceUID fd, SceInt64 * res)}
extern "C" void __cdecl IoFileMgrForUser_A12A0514(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoSetAsyncCallback                            >(c); } //@hle:syscall{A12A0514|IoFileMgrForUser|sceIoSetAsyncCallback|gggg|int sceIoSetAsyncCallback(SceUID fd, SceUID cb, void * argp)}
extern "C" void __cdecl IoFileMgrForUser_89AA9906(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoOpenAsync                                   >(c); } //@hle:syscall{89AA9906|IoFileMgrForUser|sceIoOpenAsync|gggg|SceUID sceIoOpenAsync(const char * file, int flags, SceMode mode)}
extern "C" void __cdecl IoFileMgrForUser_FF5940B6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoCloseAsync                                  >(c); } //@hle:syscall{FF5940B6|IoFileMgrForUser|sceIoCloseAsync|gg|int sceIoCloseAsync(SceUID fd)}
extern "C" void __cdecl IoFileMgrForUser_E95A012B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::IoFileMgrForUser::sceIoIoctlAsync                                  >(c); } //@hle:syscall{E95A012B|IoFileMgrForUser|sceIoIoctlAsync|ggggggg|int sceIoIoctlAsync(SceUID fd, unsigned int cmd, void * indata, int inlen, void * outdata, int outlen)}
extern "C" void __cdecl IoFileMgrForUser_71B19E77(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoLseekAsync                                  >(c); } //@hle:syscall{71B19E77|IoFileMgrForUser|sceIoLseekAsync|gggg|int sceIoLseekAsync(SceUID fd, SceOff offset, int whence)}
extern "C" void __cdecl IoFileMgrForUser_1B385D8F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoLseek32Async                                >(c); } //@hle:syscall{1B385D8F|IoFileMgrForUser|sceIoLseek32Async|gggg|int sceIoLseek32Async(SceUID fd, int offset, int whence)}
extern "C" void __cdecl IoFileMgrForUser_A0B5A7C2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoReadAsync                                   >(c); } //@hle:syscall{A0B5A7C2|IoFileMgrForUser|sceIoReadAsync|gggg|int sceIoReadAsync(SceUID fd, void * data, SceSize size)}
extern "C" void __cdecl IoFileMgrForUser_0FACAB19(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoWriteAsync                                  >(c); } //@hle:syscall{0FACAB19|IoFileMgrForUser|sceIoWriteAsync|gggg|int sceIoWriteAsync(SceUID fd, const void * data, SceSize size)}
extern "C" void __cdecl IoFileMgrForUser_B293727F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::IoFileMgrForUser::sceIoChangeAsyncPriority                         >(c); } //@hle:syscall{B293727F|IoFileMgrForUser|sceIoChangeAsyncPriority|ggg|int sceIoChangeAsyncPriority(SceUID fd, int pri)}
extern "C" void __cdecl IoFileMgrForUser_E8BC6571(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoCancel                                      >(c); } //@hle:syscall{E8BC6571|IoFileMgrForUser|sceIoCancel|gg|int sceIoCancel(SceUID fd)}
extern "C" void __cdecl IoFileMgrForUser_5C2BE2CC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::IoFileMgrForUser::sceIoGetFdList                                   >(c); } //@hle:syscall{5C2BE2CC|IoFileMgrForUser|sceIoGetFdList|gggg|int sceIoGetFdList(SceUID * readbuf, int size, int * fdcount)}
extern "C" void __cdecl IoFileMgrForUser_B2A628C1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::IoFileMgrForUser::sceIoAssign                                      >(c); } //@hle:syscall{B2A628C1|IoFileMgrForUser|sceIoAssign|ggggggg|int sceIoAssign(const char * dev1, const char * dev2, const char * dev3, int mode, void * unk1, long unk2)}
extern "C" void __cdecl IoFileMgrForUser_6D08A871(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::IoFileMgrForUser::sceIoUnassign                                    >(c); } //@hle:syscall{6D08A871|IoFileMgrForUser|sceIoUnassign|gg|int sceIoUnassign(const char * dev)}