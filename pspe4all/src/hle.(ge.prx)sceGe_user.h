//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_ge_prx_sceGe_user_h__
#define hle_ge_prx_sceGe_user_h__

namespace hle
{
    namespace sceGe_user //@hle:library-start{sceGe_user|sceGE_Manager|ge.prx}
    {
        //@hle:function{1F6752AD|sceGe_user|sceGeEdramGetSize|g|unsigned int sceGeEdramGetSize(void)}
        extern int  sceGeEdramGetSize();
        //@hle:function{E47E40E4|sceGe_user|sceGeEdramGetAddr|g|void * sceGeEdramGetAddr(void)}
        extern int  sceGeEdramGetAddr();
        //@hle:function{B77905EA|sceGe_user|sceGeEdramSetAddrTranslation|gg|??? sceGeEdramSetAddrTranslation()}
        extern int  sceGeEdramSetAddrTranslation(u32 $a0);
        //@hle:function{DC93CFEF|sceGe_user|sceGeGetCmd|gg|unsigned int sceGeGetCmd(int cmd)}
        extern int  sceGeGetCmd(u32 $a0);
        //@hle:function{57C8945B|sceGe_user|sceGeGetMtx|ggg|unsigned int sceGeGetMtx(int type, void * matrix)}
        extern int  sceGeGetMtx(u32 $a0, u32 $a1);
        //@hle:function{438A385A|sceGe_user|sceGeSaveContext|gg|int sceGeSaveContext(SceGeContext * context)}
        extern int  sceGeSaveContext(u32 $a0);
        //@hle:function{0BF608FB|sceGe_user|sceGeRestoreContext|gg|int sceGeRestoreContext(const SceGeContext * context)}
        extern int  sceGeRestoreContext(u32 $a0);
        //@hle:function{AB49E76A|sceGe_user|sceGeListEnQueue|ggggg|int sceGeListEnQueue(const void * madr, void * sadr, int cbid, const SceGeListOptParam * opt)}
        extern int  sceGeListEnQueue(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{1C0D95A6|sceGe_user|sceGeListEnQueueHead|ggggg|int sceGeListEnQueueHead(const void * madr, void * sadr, int cbid, const SceGeListOptParam * opt)}
        extern int  sceGeListEnQueueHead(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{5FB86AB0|sceGe_user|sceGeListDeQueue|gg|int sceGeListDeQueue(int dlid)}
        extern int  sceGeListDeQueue(u32 $a0);
        //@hle:function{E0D68148|sceGe_user|sceGeListUpdateStallAddr|ggg|int sceGeListUpdateStallAddr(int dlid, void * sadr)}
        extern int  sceGeListUpdateStallAddr(u32 $a0, u32 $a1);
        //@hle:function{03444EB4|sceGe_user|sceGeListSync|ggg|int sceGeListSync(int dlid, int mode)}
        extern int  sceGeListSync(u32 $a0, u32 $a1);
        //@hle:function{B287BD61|sceGe_user|sceGeDrawSync|gg|int sceGeDrawSync(int mode)}
        extern int  sceGeDrawSync(u32 $a0);
        //@hle:function{B448EC0D|sceGe_user|sceGeBreak|ggg|int sceGeBreak(int mode, SceGeBreakParam * param)}
        extern int  sceGeBreak(u32 $a0, u32 $a1);
        //@hle:function{4C06E472|sceGe_user|sceGeContinue|g|int sceGeContinue(void)}
        extern int  sceGeContinue();
        //@hle:function{A4FC06A4|sceGe_user|sceGeSetCallback|gg|int sceGeSetCallback(const SceGeCbParam * param)}
        extern int  sceGeSetCallback(u32 $a0);
        //@hle:function{05DB22CE|sceGe_user|sceGeUnsetCallback|gg|int sceGeUnsetCallback(int cbid)}
        extern int  sceGeUnsetCallback(u32 $a0);
        //@hle:function{E66CB92E|sceGe_user|sceGeGetStack|ggggg|int sceGeGetStack(int arg1, int arg2, int arg3, int arg4)}
        extern int  sceGeGetStack(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
    } //@hle:library-end{sceGe_user|sceGE_Manager|ge.prx}
}
#endif