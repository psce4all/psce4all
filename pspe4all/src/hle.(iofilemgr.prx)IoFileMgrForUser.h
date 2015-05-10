//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_iofilemgr_prx_IoFileMgrForUser_h__
#define hle_iofilemgr_prx_IoFileMgrForUser_h__

namespace hle
{
    namespace IoFileMgrForUser //@hle:library-start{IoFileMgrForUser|sceIOFileManager|iofilemgr.prx}
    {
        //@hle:function{B8A740F4|IoFileMgrForUser|sceIoChstat|gggg|int sceIoChstat(const char * file, SceIoStat * stat, int bits)}
        extern int  sceIoChstat(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{ACE946E8|IoFileMgrForUser|sceIoGetstat|ggg|int sceIoGetstat(const char * file, SceIoStat * stat)}
        extern int  sceIoGetstat(u32 $a0, u32 $a1);
        //@hle:function{CB05F8D6|IoFileMgrForUser|sceIoGetAsyncStat|gggg|int sceIoGetAsyncStat(SceUID fd, int poll, SceInt64 * res)}
        extern int  sceIoGetAsyncStat(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{B29DDF9C|IoFileMgrForUser|sceIoDopen|gg|SceUID sceIoDopen(const char * dirname)}
        extern int  sceIoDopen(u32 $a0);
        //@hle:function{EB092469|IoFileMgrForUser|sceIoDclose|gg|int sceIoDclose(SceUID fd)}
        extern int  sceIoDclose(u32 $a0);
        //@hle:function{E3EB004C|IoFileMgrForUser|sceIoDread|ggg|int sceIoDread(SceUID fd, SceIoDirent * dir)}
        extern int  sceIoDread(u32 $a0, u32 $a1);
        //@hle:function{06A70004|IoFileMgrForUser|sceIoMkdir|ggg|int sceIoMkdir(const char * path, SceMode mode)}
        extern int  sceIoMkdir(u32 $a0, u32 $a1);
        //@hle:function{1117C65F|IoFileMgrForUser|sceIoRmdir|gg|int sceIoRmdir(const char * path)}
        extern int  sceIoRmdir(u32 $a0);
        //@hle:function{55F4717D|IoFileMgrForUser|sceIoChdir|gg|int sceIoChdir(const char * path)}
        extern int  sceIoChdir(u32 $a0);
        //@hle:function{779103A0|IoFileMgrForUser|sceIoRename|ggg|int sceIoRename(const char * oldname, const char * newname)}
        extern int  sceIoRename(u32 $a0, u32 $a1);
        //@hle:function{F27A9C51|IoFileMgrForUser|sceIoRemove|gg|int sceIoRemove(const char * path)}
        extern int  sceIoRemove(u32 $a0);
        //@hle:function{54F5FB11|IoFileMgrForUser|sceIoDevctl|ggggggg|int sceIoDevctl(const char * dev, int cmd, void * indata, int inlen, void * outdata, int outlen)}
        extern int  sceIoDevctl(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{AB96437F|IoFileMgrForUser|sceIoSync|ggg|int sceIoSync(const char * dev, int flag)}
        extern int  sceIoSync(u32 $a0, u32 $a1);
        //@hle:function{08BD7374|IoFileMgrForUser|sceIoGetDevType|gg|int sceIoGetDevType(SceUID fd)}
        extern int  sceIoGetDevType(u32 $a0);
        //@hle:function{109F50BC|IoFileMgrForUser|sceIoOpen|gggg|SceUID sceIoOpen(const char * file, int flags, SceMode mode)}
        extern int  sceIoOpen(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{810C4BC3|IoFileMgrForUser|sceIoClose|gg|int sceIoClose(SceUID fd)}
        extern int  sceIoClose(u32 $a0);
        //@hle:function{63632449|IoFileMgrForUser|sceIoIoctl|ggggggg|int sceIoIoctl(SceUID fd, int cmd, void * indata, int inlen, void * outdata, int outlen)}
        extern int  sceIoIoctl(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{27EB27B8|IoFileMgrForUser|sceIoLseek|GgGg|SceOff sceIoLseek(SceUID fd, SceOff offset, int whence)}
        extern s64  sceIoLseek(u32 $a0, u64 $a3a2, u32 $a4);
        //@hle:function{68963324|IoFileMgrForUser|sceIoLseek32|gggg|int sceIoLseek32(SceUID fd, int offset, int whence)}
        extern int  sceIoLseek32(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{6A638D83|IoFileMgrForUser|sceIoRead|gggg|int sceIoRead(SceUID fd, void * data, SceSize size)}
        extern int  sceIoRead(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{42EC03AC|IoFileMgrForUser|sceIoWrite|gggg|int sceIoWrite(SceUID fd, const void * data, SceSize size)}
        extern int  sceIoWrite(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{3251EA56|IoFileMgrForUser|sceIoPollAsync|ggg|int sceIoPollAsync(SceUID fd, SceInt64 * res)}
        extern int  sceIoPollAsync(u32 $a0, u32 $a1);
        //@hle:function{E23EEC33|IoFileMgrForUser|sceIoWaitAsync|ggg|int sceIoWaitAsync(SceUID fd, SceInt64 * res)}
        extern int  sceIoWaitAsync(u32 $a0, u32 $a1);
        //@hle:function{35DBD746|IoFileMgrForUser|sceIoWaitAsyncCB|ggg|int sceIoWaitAsyncCB(SceUID fd, SceInt64 * res)}
        extern int  sceIoWaitAsyncCB(u32 $a0, u32 $a1);
        //@hle:function{A12A0514|IoFileMgrForUser|sceIoSetAsyncCallback|gggg|int sceIoSetAsyncCallback(SceUID fd, SceUID cb, void * argp)}
        extern int  sceIoSetAsyncCallback(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{89AA9906|IoFileMgrForUser|sceIoOpenAsync|gggg|SceUID sceIoOpenAsync(const char * file, int flags, SceMode mode)}
        extern int  sceIoOpenAsync(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{FF5940B6|IoFileMgrForUser|sceIoCloseAsync|gg|int sceIoCloseAsync(SceUID fd)}
        extern int  sceIoCloseAsync(u32 $a0);
        //@hle:function{E95A012B|IoFileMgrForUser|sceIoIoctlAsync|ggggggg|int sceIoIoctlAsync(SceUID fd, unsigned int cmd, void * indata, int inlen, void * outdata, int outlen)}
        extern int  sceIoIoctlAsync(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{71B19E77|IoFileMgrForUser|sceIoLseekAsync|gggg|int sceIoLseekAsync(SceUID fd, SceOff offset, int whence)}
        extern int  sceIoLseekAsync(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{1B385D8F|IoFileMgrForUser|sceIoLseek32Async|gggg|int sceIoLseek32Async(SceUID fd, int offset, int whence)}
        extern int  sceIoLseek32Async(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{A0B5A7C2|IoFileMgrForUser|sceIoReadAsync|gggg|int sceIoReadAsync(SceUID fd, void * data, SceSize size)}
        extern int  sceIoReadAsync(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{0FACAB19|IoFileMgrForUser|sceIoWriteAsync|gggg|int sceIoWriteAsync(SceUID fd, const void * data, SceSize size)}
        extern int  sceIoWriteAsync(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{B293727F|IoFileMgrForUser|sceIoChangeAsyncPriority|ggg|int sceIoChangeAsyncPriority(SceUID fd, int pri)}
        extern int  sceIoChangeAsyncPriority(u32 $a0, u32 $a1);
        //@hle:function{E8BC6571|IoFileMgrForUser|sceIoCancel|gg|int sceIoCancel(SceUID fd)}
        extern int  sceIoCancel(u32 $a0);
        //@hle:function{5C2BE2CC|IoFileMgrForUser|sceIoGetFdList|gggg|int sceIoGetFdList(SceUID * readbuf, int size, int * fdcount)}
        extern int  sceIoGetFdList(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{B2A628C1|IoFileMgrForUser|sceIoAssign|ggggggg|int sceIoAssign(const char * dev1, const char * dev2, const char * dev3, int mode, void * unk1, long unk2)}
        extern int  sceIoAssign(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{6D08A871|IoFileMgrForUser|sceIoUnassign|gg|int sceIoUnassign(const char * dev)}
        extern int  sceIoUnassign(u32 $a0);
    } //@hle:library-end{IoFileMgrForUser|sceIOFileManager|iofilemgr.prx}
}
#endif