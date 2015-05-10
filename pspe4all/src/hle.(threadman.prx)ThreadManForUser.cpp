//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(threadman.prx)ThreadManForUser.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace ThreadManForUser //@hle:library-start{ThreadManForUser|sceThreadManager|threadman.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{446D8DE6|ThreadManForUser|sceKernelCreateThread|ggggggg|SceUID sceKernelCreateThread(const char * name, SceKernelThreadEntry entry, int initPriority, int stackSize, SceUInt attr, const SceKernelThreadOptParam * opt)}
        int  sceKernelCreateThread(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9FA03CD3|ThreadManForUser|sceKernelDeleteThread|gg|int sceKernelDeleteThread(SceUID thid)}
        int  sceKernelDeleteThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F475845D|ThreadManForUser|sceKernelStartThread|gggg|int sceKernelStartThread(SceUID thid, SceSize arglen, void * argp)}
        int  sceKernelStartThread(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AA73C935|ThreadManForUser|sceKernelExitThread|gg|int sceKernelExitThread(int status)}
        int  sceKernelExitThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{809CE29B|ThreadManForUser|sceKernelExitDeleteThread|gg|int sceKernelExitDeleteThread(int status)}
        int  sceKernelExitDeleteThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{616403BA|ThreadManForUser|sceKernelTerminateThread|gg|int sceKernelTerminateThread(SceUID thid)}
        int  sceKernelTerminateThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{383F7BCC|ThreadManForUser|sceKernelTerminateDeleteThread|gg|int sceKernelTerminateDeleteThread(SceUID thid)}
        int  sceKernelTerminateDeleteThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3AD58B8C|ThreadManForUser|sceKernelSuspendDispatchThread|g|int sceKernelSuspendDispatchThread(void)}
        int  sceKernelSuspendDispatchThread()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{27E22EC2|ThreadManForUser|sceKernelResumeDispatchThread|gg|int sceKernelResumeDispatchThread(int state)}
        int  sceKernelResumeDispatchThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EA748E31|ThreadManForUser|sceKernelChangeCurrentThreadAttr|ggg|int sceKernelChangeCurrentThreadAttr(int unknown, SceUInt attr)}
        int  sceKernelChangeCurrentThreadAttr(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{71BC9871|ThreadManForUser|sceKernelChangeThreadPriority|ggg|int sceKernelChangeThreadPriority(SceUID thid, int priority)}
        int  sceKernelChangeThreadPriority(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{912354A7|ThreadManForUser|sceKernelRotateThreadReadyQueue|gg|int sceKernelRotateThreadReadyQueue(int priority)}
        int  sceKernelRotateThreadReadyQueue(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2C34E053|ThreadManForUser|sceKernelReleaseWaitThread|gg|int sceKernelReleaseWaitThread(SceUID thid)}
        int  sceKernelReleaseWaitThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{293B45B8|ThreadManForUser|sceKernelGetThreadId|g|int sceKernelGetThreadId(void)}
        int  sceKernelGetThreadId()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{94AA61EE|ThreadManForUser|sceKernelGetThreadCurrentPriority|g|int sceKernelGetThreadCurrentPriority(void)}
        int  sceKernelGetThreadCurrentPriority()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3B183E26|ThreadManForUser|sceKernelGetThreadExitStatus|gg|int sceKernelGetThreadExitStatus(SceUID thid)}
        int  sceKernelGetThreadExitStatus(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{17C1684E|ThreadManForUser|sceKernelReferThreadStatus|ggg|int sceKernelReferThreadStatus(SceUID thid, SceKernelThreadInfo * info)}
        int  sceKernelReferThreadStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FFC36A14|ThreadManForUser|sceKernelReferThreadRunStatus|ggg|int sceKernelReferThreadRunStatus(SceUID thid, SceKernelThreadRunStatus * status)}
        int  sceKernelReferThreadRunStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D13BDE95|ThreadManForUser|sceKernelCheckThreadStack|g|int sceKernelCheckThreadStack(void)}
        int  sceKernelCheckThreadStack()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{52089CA1|ThreadManForUser|sceKernelGetThreadStackFreeSize|gg|int sceKernelGetThreadStackFreeSize(SceUID thid)}
        int  sceKernelGetThreadStackFreeSize(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{07F3A4BC|ThreadManForUser|_sceKernelStartThread|0|void _sceKernelStartThread(void)}
        void _sceKernelStartThread()
        {
        }
        //@hle:function{532A522E|ThreadManForUser|_sceKernelExitThread|0|void _sceKernelExitThread(void)}
        void _sceKernelExitThread()
        {
        }
        //@hle:function{E0A68B8C|ThreadManForUser|_sceKernelIdleThread|0|void _sceKernelIdleThread(void)}
        void _sceKernelIdleThread()
        {
        }
        //@hle:function{0C106E53|ThreadManForUser|sceKernelRegisterThreadEventHandler|gggggg|SceUID sceKernelRegisterThreadEventHandler(const char * name, SceUID threadID, int mask, SceKernelThreadEventHandler handler, void * arg)}
        int  sceKernelRegisterThreadEventHandler(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{72F3C145|ThreadManForUser|sceKernelReleaseThreadEventHandler|gg|int sceKernelReleaseThreadEventHandler(SceUID uid)}
        int  sceKernelReleaseThreadEventHandler(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{369EEB6B|ThreadManForUser|sceKernelReferThreadEventHandlerStatus|ggg|int sceKernelReferThreadEventHandlerStatus(SceUID uid, struct SceKernelThreadEventHandlerInfo * info)}
        int  sceKernelReferThreadEventHandlerStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9ACE131E|ThreadManForUser|sceKernelSleepThread|g|int sceKernelSleepThread(void)}
        int  sceKernelSleepThread()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{82826F70|ThreadManForUser|sceKernelSleepThreadCB|g|int sceKernelSleepThreadCB(void)}
        int  sceKernelSleepThreadCB()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D59EAD2F|ThreadManForUser|sceKernelWakeupThread|gg|int sceKernelWakeupThread(SceUID thid)}
        int  sceKernelWakeupThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FCCFAD26|ThreadManForUser|sceKernelCancelWakeupThread|gg|int sceKernelCancelWakeupThread(SceUID thid)}
        int  sceKernelCancelWakeupThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9944F31F|ThreadManForUser|sceKernelSuspendThread|gg|int sceKernelSuspendThread(SceUID thid)}
        int  sceKernelSuspendThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{75156E8F|ThreadManForUser|sceKernelResumeThread|gg|int sceKernelResumeThread(SceUID thid)}
        int  sceKernelResumeThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{278C0DF5|ThreadManForUser|sceKernelWaitThreadEnd|ggg|int sceKernelWaitThreadEnd(SceUID thid, SceUInt * timeout)}
        int  sceKernelWaitThreadEnd(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{840E8133|ThreadManForUser|sceKernelWaitThreadEndCB|ggg|int sceKernelWaitThreadEndCB(SceUID thid, SceUInt * timeout)}
        int  sceKernelWaitThreadEndCB(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D6DA4BA1|ThreadManForUser|sceKernelCreateSema|gggggg|SceUID sceKernelCreateSema(const char * name, SceUInt attr, int initVal, int maxVal, const SceKernelSemaOptParam * opt)}
        int  sceKernelCreateSema(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{28B6489C|ThreadManForUser|sceKernelDeleteSema|gg|int sceKernelDeleteSema(SceUID semaid)}
        int  sceKernelDeleteSema(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3F53E640|ThreadManForUser|sceKernelSignalSema|ggg|int sceKernelSignalSema(SceUID semaid, int signal)}
        int  sceKernelSignalSema(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4E3A1105|ThreadManForUser|sceKernelWaitSema|gggg|int sceKernelWaitSema(SceUID semaid, int signal, SceUInt * timeout)}
        int  sceKernelWaitSema(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6D212BAC|ThreadManForUser|sceKernelWaitSemaCB|gggg|int sceKernelWaitSemaCB(SceUID semaid, int signal, SceUInt * timeout)}
        int  sceKernelWaitSemaCB(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{58B1F937|ThreadManForUser|sceKernelPollSema|ggg|int sceKernelPollSema(SceUID semaid, int signal)}
        int  sceKernelPollSema(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8FFDF9A2|ThreadManForUser|sceKernelCancelSema|gggg|int sceKernelCancelSema(SceUID semid, int signal, int * numWaitThreads))}
        int  sceKernelCancelSema(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BC6FEBC5|ThreadManForUser|sceKernelReferSemaStatus|ggg|int sceKernelReferSemaStatus(SceUID semaid, SceKernelSemaInfo * info)}
        int  sceKernelReferSemaStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{55C20A00|ThreadManForUser|sceKernelCreateEventFlag|ggggg|SceUID sceKernelCreateEventFlag(const char * name, SceUInt attr, int bits, const SceKernelEventFlagOptParam * opt)}
        int  sceKernelCreateEventFlag(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EF9E4C70|ThreadManForUser|sceKernelDeleteEventFlag|gg|int sceKernelDeleteEventFlag(int evid)}
        int  sceKernelDeleteEventFlag(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1FB15A32|ThreadManForUser|sceKernelSetEventFlag|ggg|int sceKernelSetEventFlag(SceUID evid, SceUInt bits)}
        int  sceKernelSetEventFlag(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{812346E4|ThreadManForUser|sceKernelClearEventFlag|ggg|int sceKernelClearEventFlag(SceUID evid, SceUInt bits)}
        int  sceKernelClearEventFlag(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{402FCF22|ThreadManForUser|sceKernelWaitEventFlag|gggggg|int sceKernelWaitEventFlag(int evid, SceUInt bits, int waitmode, SceUInt * outBits, SceUInt * timeout)}
        int  sceKernelWaitEventFlag(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{328C546A|ThreadManForUser|sceKernelWaitEventFlagCB|gggggg|int sceKernelWaitEventFlagCB(int evid, SceUInt bits, int waitmode, SceUInt * outBits, SceUInt * timeout)}
        int  sceKernelWaitEventFlagCB(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{30FD48F0|ThreadManForUser|sceKernelPollEventFlag|ggggg|int sceKernelPollEventFlag(int evid, SceUInt bits, int waitmode, SceUInt * outBits)}
        int  sceKernelPollEventFlag(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CD203292|ThreadManForUser|sceKernelCancelEventFlag|gggg|int sceKernelCancelEventFlag(SceUID evid, SceUInt bits, int * numWaitThreads))}
        int  sceKernelCancelEventFlag(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A66B0120|ThreadManForUser|sceKernelReferEventFlagStatus|ggg|int sceKernelReferEventFlagStatus(SceUID event, SceKernelEventFlagInfo * status)}
        int  sceKernelReferEventFlagStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8125221D|ThreadManForUser|sceKernelCreateMbx|gggg|SceUID sceKernelCreateMbx(const char * name, SceUInt attr, const SceKernelMbxOptParam * opt)}
        int  sceKernelCreateMbx(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{86255ADA|ThreadManForUser|sceKernelDeleteMbx|gg|int sceKernelDeleteMbx(SceUID mbxid)}
        int  sceKernelDeleteMbx(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E9B3061E|ThreadManForUser|sceKernelSendMbx|ggg|int sceKernelSendMbx(SceUID mbxid, void * message)}
        int  sceKernelSendMbx(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{18260574|ThreadManForUser|sceKernelReceiveMbx|gggg|int sceKernelReceiveMbx(SceUID mbxid, void * pmessage, SceUInt * timeout)}
        int  sceKernelReceiveMbx(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F3986382|ThreadManForUser|sceKernelReceiveMbxCB|gggg|int sceKernelReceiveMbxCB(SceUID mbxid, void * pmessage, SceUInt * timeout)}
        int  sceKernelReceiveMbxCB(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0D81716A|ThreadManForUser|sceKernelPollMbx|ggg|int sceKernelPollMbx(SceUID mbxid, void * pmessage)}
        int  sceKernelPollMbx(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{87D4DD36|ThreadManForUser|sceKernelCancelReceiveMbx|ggg|int sceKernelCancelReceiveMbx(SceUID mbxid, int * numWaitThreads)}
        int  sceKernelCancelReceiveMbx(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A8E8C846|ThreadManForUser|sceKernelReferMbxStatus|ggg|int sceKernelReferMbxStatus(SceUID mbxid, SceKernelMbxInfo * info)}
        int  sceKernelReferMbxStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7C0DC2A0|ThreadManForUser|sceKernelCreateMsgPipe|gggggg|SceUID sceKernelCreateMsgPipe(const char * name, SceUID mpid, SceUInt attr, SceSize bufsize, const SceKernelMppOptParam * opt)}
        int  sceKernelCreateMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F0B7DA1C|ThreadManForUser|sceKernelDeleteMsgPipe|gg|int sceKernelDeleteMsgPipe(SceUID uid)}
        int  sceKernelDeleteMsgPipe(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{876DBFAD|ThreadManForUser|sceKernelSendMsgPipe|ggggggg|int sceKernelSendMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        int  sceKernelSendMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7C41F2C2|ThreadManForUser|sceKernelSendMsgPipeCB|ggggggg|int sceKernelSendMsgPipeCB(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        int  sceKernelSendMsgPipeCB(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{884C9F90|ThreadManForUser|sceKernelTrySendMsgPipe|gggggg|int sceKernelTrySendMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result)}
        int  sceKernelTrySendMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{74829B76|ThreadManForUser|sceKernelReceiveMsgPipe|ggggggg|int sceKernelReceiveMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        int  sceKernelReceiveMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FBFA697D|ThreadManForUser|sceKernelReceiveMsgPipeCB|ggggggg|int sceKernelReceiveMsgPipeCB(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        int  sceKernelReceiveMsgPipeCB(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DF52098F|ThreadManForUser|sceKernelTryReceiveMsgPipe|gggggg|int sceKernelTryReceiveMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        int  sceKernelTryReceiveMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{349B864D|ThreadManForUser|sceKernelCancelMsgPipe|gggg|int sceKernelCancelMsgPipe(SceUID uid, int * numSendWaitThreads, int * numRecvWaitThreads)}
        int  sceKernelCancelMsgPipe(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{33BE4024|ThreadManForUser|sceKernelReferMsgPipeStatus|ggg|int sceKernelReferMsgPipeStatus(SceUID uid, SceKernelMppInfo * info)}
        int  sceKernelReferMsgPipeStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{56C039B5|ThreadManForUser|sceKernelCreateVpl|gggggg|SceUID sceKernelCreateVpl(const char * name, SceUID mpid, SceUInt attr, unsigned int size, SceKernelVplOptParam * opt)}
        int  sceKernelCreateVpl(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{89B3D48C|ThreadManForUser|sceKernelDeleteVpl|gg|int sceKernelDeleteVpl(SceUID uid)}
        int  sceKernelDeleteVpl(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BED27435|ThreadManForUser|sceKernelAllocateVpl|ggggg|int sceKernelAllocateVpl(SceUID uid, unsigned int size, void * * data, SceUInt * timeout)}
        int  sceKernelAllocateVpl(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EC0A693F|ThreadManForUser|sceKernelAllocateVplCB|ggggg|int sceKernelAllocateVplCB(SceUID uid, unsigned int size, void * * data, SceUInt * timeout)}
        int  sceKernelAllocateVplCB(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AF36D708|ThreadManForUser|sceKernelTryAllocateVpl|gggg|int sceKernelTryAllocateVpl(SceUID uid, unsigned int size, void * * data)}
        int  sceKernelTryAllocateVpl(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B736E9FF|ThreadManForUser|sceKernelFreeVpl|ggg|int sceKernelFreeVpl(SceUID uid, void * data)}
        int  sceKernelFreeVpl(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1D371B8A|ThreadManForUser|sceKernelCancelVpl|ggg|int sceKernelCancelVpl(SceUID uid, int * numWaitThreads)}
        int  sceKernelCancelVpl(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{39810265|ThreadManForUser|sceKernelReferVplStatus|ggg|int sceKernelReferVplStatus(SceUID uid, SceKernelVplInfo * info)}
        int  sceKernelReferVplStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C07BB470|ThreadManForUser|sceKernelCreateFpl|ggggggg|int sceKernelCreateFpl(const char * name, SceUID mpid, SceUInt attr, unsigned int size, int blocks, SceKernelFplOptParam * opt)}
        int  sceKernelCreateFpl(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{ED1410E0|ThreadManForUser|sceKernelDeleteFpl|gg|int sceKernelDeleteFpl(SceUID uid)}
        int  sceKernelDeleteFpl(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D979E9BF|ThreadManForUser|sceKernelAllocateFpl|gggg|int sceKernelAllocateFpl(SceUID uid, void * * data, SceUInt * timeout)}
        int  sceKernelAllocateFpl(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E7282CB6|ThreadManForUser|sceKernelAllocateFplCB|gggg|int sceKernelAllocateFplCB(SceUID uid, void * * data, SceUInt * timeout)}
        int  sceKernelAllocateFplCB(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{623AE665|ThreadManForUser|sceKernelTryAllocateFpl|ggg|int sceKernelTryAllocateFpl(SceUID uid, void * * data)}
        int  sceKernelTryAllocateFpl(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F6414A71|ThreadManForUser|sceKernelFreeFpl|ggg|int sceKernelFreeFpl(SceUID uid, void * data)}
        int  sceKernelFreeFpl(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A8AA591F|ThreadManForUser|sceKernelCancelFpl|ggg|int sceKernelCancelFpl(SceUID uid, int * numWaitThreads)}
        int  sceKernelCancelFpl(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D8199E4C|ThreadManForUser|sceKernelReferFplStatus|ggg|int sceKernelReferFplStatus(SceUID uid, SceKernelFplInfo * info)}
        int  sceKernelReferFplStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DB738F35|ThreadManForUser|sceKernelGetSystemTime|gg|int sceKernelGetSystemTime(SceKernelSysClock * time)}
        int  sceKernelGetSystemTime(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{82BC5777|ThreadManForUser|sceKernelGetSystemTimeWide|G|SceInt64 sceKernelGetSystemTimeWide(void)}
        s64  sceKernelGetSystemTimeWide()
        {
            s64 $v1v0;
            $v1v0 = 0;
            return $v1v0;
        }
        //@hle:function{369ED59D|ThreadManForUser|sceKernelGetSystemTimeLow|g|unsigned int sceKernelGetSystemTimeLow(void)}
        int  sceKernelGetSystemTimeLow()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{110DEC9A|ThreadManForUser|sceKernelUSec2SysClock|ggg|int sceKernelUSec2SysClock(unsigned int usec, SceKernelSysClock * clock)}
        int  sceKernelUSec2SysClock(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BA6B92E2|ThreadManForUser|sceKernelSysClock2USec|gggg|int sceKernelSysClock2USec(const SceKernelSysClock * clock, unsigned int * low, unsigned int * high)}
        int  sceKernelSysClock2USec(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C8CD158C|ThreadManForUser|sceKernelUSec2SysClockWide|Gg|SceInt64 sceKernelUSec2SysClockWide(unsigned int usec)}
        s64  sceKernelUSec2SysClockWide(u32 $a0)
        {
            (void)($a0);
            s64 $v1v0;
            $v1v0 = 0;
            return $v1v0;
        }
        //@hle:function{E1619D7C|ThreadManForUser|sceKernelSysClock2USecWide|gGgg|int sceKernelSysClock2USecWide(SceInt64 clock, unsigned * low, unsigned int * high)}
        int  sceKernelSysClock2USecWide(u64 $a1a0, u32 $a2, u32 $a3)
        {
            (void)($a1a0, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CEADEB47|ThreadManForUser|sceKernelDelayThread|gg|int sceKernelDelayThread(SceUInt delay)}
        int  sceKernelDelayThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{68DA9E36|ThreadManForUser|sceKernelDelayThreadCB|gg|int sceKernelDelayThreadCB(SceUInt delay)}
        int  sceKernelDelayThreadCB(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BD123D9E|ThreadManForUser|sceKernelDelaySysClockThread|gg|int sceKernelDelaySysClockThread(const SceKernelSysClock * delay)}
        int  sceKernelDelaySysClockThread(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1181E963|ThreadManForUser|sceKernelDelaySysClockThreadCB|gg|int sceKernelDelaySysClockThreadCB(const SceKernelSysClock * delay)}
        int  sceKernelDelaySysClockThreadCB(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6652B8CA|ThreadManForUser|sceKernelSetAlarm|gggg|SceUID sceKernelSetAlarm(SceUInt clock, SceKernelAlarmHandler handler, void * common)}
        int  sceKernelSetAlarm(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B2C25152|ThreadManForUser|sceKernelSetSysClockAlarm|gggg|SceUID sceKernelSetSysClockAlarm(SceKernelSysClock * clock, SceKernelAlarmHandler handler, void * arg)}
        int  sceKernelSetSysClockAlarm(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7E65B999|ThreadManForUser|sceKernelCancelAlarm|gg|int sceKernelCancelAlarm(SceUID uid)}
        int  sceKernelCancelAlarm(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DAA3F564|ThreadManForUser|sceKernelReferAlarmStatus|ggg|int sceKernelReferAlarmStatus(SceUID uid, SceKernelAlarmInfo * info)}
        int  sceKernelReferAlarmStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{20FFF560|ThreadManForUser|sceKernelCreateVTimer|ggg|SceUID sceKernelCreateVTimer(const char * name, const SceKernelVTimerOptParam * opt)}
        int  sceKernelCreateVTimer(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{328F9E52|ThreadManForUser|sceKernelDeleteVTimer|gg|int sceKernelDeleteVTimer(SceUID uid)}
        int  sceKernelDeleteVTimer(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B3A59970|ThreadManForUser|sceKernelGetVTimerBase|ggg|int sceKernelGetVTimerBase(SceUID uid, SceKernelSysClock * base)}
        int  sceKernelGetVTimerBase(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{034A921F|ThreadManForUser|sceKernelGetVTimerTime|ggg|int sceKernelGetVTimerTime(SceUID uid, SceKernelSysClock * time)}
        int  sceKernelGetVTimerTime(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{542AD630|ThreadManForUser|sceKernelSetVTimerTime|ggg|int sceKernelSetVTimerTime(SceUID uid, SceKernelSysClock * time)}
        int  sceKernelSetVTimerTime(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C68D9437|ThreadManForUser|sceKernelStartVTimer|gg|int sceKernelStartVTimer(SceUID uid)}
        int  sceKernelStartVTimer(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D0AEEE87|ThreadManForUser|sceKernelStopVTimer|gg|int sceKernelStopVTimer(SceUID uid)}
        int  sceKernelStopVTimer(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D8B299AE|ThreadManForUser|sceKernelSetVTimerHandler|ggggg|int sceKernelSetVTimerHandler(SceUID uid, SceKernelSysClock * time, SceKernelVTimerHandler handler, void * arg)}
        int  sceKernelSetVTimerHandler(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D2D615EF|ThreadManForUser|sceKernelCancelVTimerHandler|gg|int sceKernelCancelVTimerHandler(SceUID uid)}
        int  sceKernelCancelVTimerHandler(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B7C18B77|ThreadManForUser|sceKernelGetVTimerBaseWide|Gg|SceInt64 sceKernelGetVTimerBaseWide(SceUID uid)}
        s64  sceKernelGetVTimerBaseWide(u32 $a0)
        {
            (void)($a0);
            s64 $v1v0;
            $v1v0 = 0;
            return $v1v0;
        }
        //@hle:function{C0B3FFD2|ThreadManForUser|sceKernelGetVTimerTimeWide|Gg|SceInt64 sceKernelGetVTimerTimeWide(SceUID uid)}
        s64  sceKernelGetVTimerTimeWide(u32 $a0)
        {
            (void)($a0);
            s64 $v1v0;
            $v1v0 = 0;
            return $v1v0;
        }
        //@hle:function{FB6425C3|ThreadManForUser|sceKernelSetVTimerTimeWide|GgG|SceInt64 sceKernelSetVTimerTimeWide(SceUID uid, SceInt64 time)}
        s64  sceKernelSetVTimerTimeWide(u32 $a0, u64 $a3a2)
        {
            (void)($a0, $a3a2);
            s64 $v1v0;
            $v1v0 = 0;
            return $v1v0;
        }
        //@hle:function{53B00E9A|ThreadManForUser|sceKernelSetVTimerHandlerWide|ggGgg|int sceKernelSetVTimerHandlerWide(SceUID uid, SceInt64 time, SceKernelVTimerHandlerWide handler, void * arg)}
        int  sceKernelSetVTimerHandlerWide(u32 $a0, u64 $a3a2, u32 $a4, u32 $a5)
        {
            (void)($a0, $a3a2, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5F32BEAA|ThreadManForUser|sceKernelReferVTimerStatus|ggg|int sceKernelReferVTimerStatus(SceUID uid, SceKernelVTimerInfo * info)}
        int  sceKernelReferVTimerStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0E927AED|ThreadManForUser|_sceKernelReturnFromTimerHandler|0|void _sceKernelReturnFromTimerHandler(void)}
        void _sceKernelReturnFromTimerHandler()
        {
        }
        //@hle:function{E81CAF8F|ThreadManForUser|sceKernelCreateCallback|gggg|int sceKernelCreateCallback(const char * name, SceKernelCallbackFunction func, void * arg)}
        int  sceKernelCreateCallback(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EDBA5844|ThreadManForUser|sceKernelDeleteCallback|gg|int sceKernelDeleteCallback(SceUID cbid)}
        int  sceKernelDeleteCallback(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C11BA8C4|ThreadManForUser|sceKernelNotifyCallback|ggg|int sceKernelNotifyCallback(SceUID cbid, int arg)}
        int  sceKernelNotifyCallback(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BA4051D6|ThreadManForUser|sceKernelCancelCallback|gg|int sceKernelCancelCallback(SceUID cbid)}
        int  sceKernelCancelCallback(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2A3D44FF|ThreadManForUser|sceKernelGetCallbackCount|gg|int sceKernelGetCallbackCount(SceUID cbid)}
        int  sceKernelGetCallbackCount(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{349D6D6C|ThreadManForUser|sceKernelCheckCallback|g|int sceKernelCheckCallback(void)}
        int  sceKernelCheckCallback()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{730ED8BC|ThreadManForUser|sceKernelReferCallbackStatus|ggg|int sceKernelReferCallbackStatus(SceUID cb, SceKernelCallbackInfo * status)}
        int  sceKernelReferCallbackStatus(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6E9EA350|ThreadManForUser|_sceKernelReturnFromCallback|0|void _sceKernelReturnFromCallback(void)}
        void _sceKernelReturnFromCallback()
        {
        }
        //@hle:function{627E6F3A|ThreadManForUser|sceKernelReferSystemStatus|gg|int sceKernelReferSystemStatus(SceKernelSystemStatus * status)}
        int  sceKernelReferSystemStatus(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{94416130|ThreadManForUser|sceKernelGetThreadmanIdList|ggggg|int sceKernelGetThreadmanIdList(enum SceKernelIdListType type, SceUID * readbuf, int readbufsize, int * idcount)}
        int  sceKernelGetThreadmanIdList(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{57CF62DD|ThreadManForUser|sceKernelGetThreadmanIdType|gg|enum sceKernelGetThreadmanIdType(SceUID uid)}
        int  sceKernelGetThreadmanIdType(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B7D098C6|ThreadManForUser|sceKernelCreateMutex|g|??? sceKernelCreateMutex()}
        int  sceKernelCreateMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F8170FBE|ThreadManForUser|sceKernelDeleteMutex|g|??? sceKernelDeleteMutex()}
        int  sceKernelDeleteMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B011B11F|ThreadManForUser|sceKernelLockMutex|g|??? sceKernelLockMutex()}
        int  sceKernelLockMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5BF4DD27|ThreadManForUser|sceKernelLockMutexCB|g|??? sceKernelLockMutexCB()}
        int  sceKernelLockMutexCB()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0DDCD2C9|ThreadManForUser|sceKernelTryLockMutex|g|??? sceKernelTryLockMutex()}
        int  sceKernelTryLockMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6B30100F|ThreadManForUser|sceKernelUnlockMutex|g|??? sceKernelUnlockMutex()}
        int  sceKernelUnlockMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{87D9223C|ThreadManForUser|sceKernelCancelMutex|g|??? sceKernelCancelMutex()}
        int  sceKernelCancelMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A9C2CB9A|ThreadManForUser|sceKernelReferMutexStatus|g|??? sceKernelReferMutexStatus()}
        int  sceKernelReferMutexStatus()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{19CFF145|ThreadManForUser|sceKernelCreateLwMutex|g|??? sceKernelCreateLwMutex()}
        int  sceKernelCreateLwMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{60107536|ThreadManForUser|sceKernelDeleteLwMutex|g|??? sceKernelDeleteLwMutex()}
        int  sceKernelDeleteLwMutex()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4C145944|ThreadManForUser|sceKernelReferLwMutexStatusByID|g|??? sceKernelReferLwMutexStatusByID()}
        int  sceKernelReferLwMutexStatusByID()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{64D4540E|ThreadManForUser|sceKernelReferThreadProfiler|g|SceProfilerRegs * sceKernelReferThreadProfiler(void)}
        int  sceKernelReferThreadProfiler()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8218B4DD|ThreadManForUser|sceKernelReferGlobalProfiler|g|SceProfilerRegs * sceKernelReferGlobalProfiler(void)}
        int  sceKernelReferGlobalProfiler()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1AF94D03|ThreadManForUser|sceKernelDonateWakeupThread|g|??? sceKernelDonateWakeupThread()}
        int  sceKernelDonateWakeupThread()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{31327F19|ThreadManForUser|ThreadManForUser_31327F19|g|??? ThreadManForUser_31327F19()}
        int  ThreadManForUser_31327F19()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{71040D5C|ThreadManForUser|ThreadManForUser_71040D5C|g|??? ThreadManForUser_71040D5C()}
        int  ThreadManForUser_71040D5C()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7CFF8CF3|ThreadManForUser|ThreadManForUser_7CFF8CF3|g|??? ThreadManForUser_7CFF8CF3()}
        int  ThreadManForUser_7CFF8CF3()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8672E3D0|ThreadManForUser|ThreadManForUser_8672E3D0|g|??? ThreadManForUser_8672E3D0()}
        int  ThreadManForUser_8672E3D0()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BEED3A47|ThreadManForUser|ThreadManForUser_BEED3A47|g|??? ThreadManForUser_BEED3A47()}
        int  ThreadManForUser_BEED3A47()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{ThreadManForUser|sceThreadManager|threadman.prx}
}

extern "C" bool __cdecl ThreadManForUser$Init() { return hle::ThreadManForUser::Init(); }
extern "C" bool __cdecl ThreadManForUser$Fini() { return hle::ThreadManForUser::Fini(); }
extern "C" void __cdecl ThreadManForUser_446D8DE6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::ThreadManForUser::sceKernelCreateThread                            >(c); } //@hle:syscall{446D8DE6|ThreadManForUser|sceKernelCreateThread|ggggggg|SceUID sceKernelCreateThread(const char * name, SceKernelThreadEntry entry, int initPriority, int stackSize, SceUInt attr, const SceKernelThreadOptParam * opt)}
extern "C" void __cdecl ThreadManForUser_9FA03CD3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDeleteThread                            >(c); } //@hle:syscall{9FA03CD3|ThreadManForUser|sceKernelDeleteThread|gg|int sceKernelDeleteThread(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_F475845D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelStartThread                             >(c); } //@hle:syscall{F475845D|ThreadManForUser|sceKernelStartThread|gggg|int sceKernelStartThread(SceUID thid, SceSize arglen, void * argp)}
extern "C" void __cdecl ThreadManForUser_AA73C935(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelExitThread                              >(c); } //@hle:syscall{AA73C935|ThreadManForUser|sceKernelExitThread|gg|int sceKernelExitThread(int status)}
extern "C" void __cdecl ThreadManForUser_809CE29B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelExitDeleteThread                        >(c); } //@hle:syscall{809CE29B|ThreadManForUser|sceKernelExitDeleteThread|gg|int sceKernelExitDeleteThread(int status)}
extern "C" void __cdecl ThreadManForUser_616403BA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelTerminateThread                         >(c); } //@hle:syscall{616403BA|ThreadManForUser|sceKernelTerminateThread|gg|int sceKernelTerminateThread(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_383F7BCC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelTerminateDeleteThread                   >(c); } //@hle:syscall{383F7BCC|ThreadManForUser|sceKernelTerminateDeleteThread|gg|int sceKernelTerminateDeleteThread(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_3AD58B8C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelSuspendDispatchThread                   >(c); } //@hle:syscall{3AD58B8C|ThreadManForUser|sceKernelSuspendDispatchThread|g|int sceKernelSuspendDispatchThread(void)}
extern "C" void __cdecl ThreadManForUser_27E22EC2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelResumeDispatchThread                    >(c); } //@hle:syscall{27E22EC2|ThreadManForUser|sceKernelResumeDispatchThread|gg|int sceKernelResumeDispatchThread(int state)}
extern "C" void __cdecl ThreadManForUser_EA748E31(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelChangeCurrentThreadAttr                 >(c); } //@hle:syscall{EA748E31|ThreadManForUser|sceKernelChangeCurrentThreadAttr|ggg|int sceKernelChangeCurrentThreadAttr(int unknown, SceUInt attr)}
extern "C" void __cdecl ThreadManForUser_71BC9871(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelChangeThreadPriority                    >(c); } //@hle:syscall{71BC9871|ThreadManForUser|sceKernelChangeThreadPriority|ggg|int sceKernelChangeThreadPriority(SceUID thid, int priority)}
extern "C" void __cdecl ThreadManForUser_912354A7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelRotateThreadReadyQueue                  >(c); } //@hle:syscall{912354A7|ThreadManForUser|sceKernelRotateThreadReadyQueue|gg|int sceKernelRotateThreadReadyQueue(int priority)}
extern "C" void __cdecl ThreadManForUser_2C34E053(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelReleaseWaitThread                       >(c); } //@hle:syscall{2C34E053|ThreadManForUser|sceKernelReleaseWaitThread|gg|int sceKernelReleaseWaitThread(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_293B45B8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelGetThreadId                             >(c); } //@hle:syscall{293B45B8|ThreadManForUser|sceKernelGetThreadId|g|int sceKernelGetThreadId(void)}
extern "C" void __cdecl ThreadManForUser_94AA61EE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelGetThreadCurrentPriority                >(c); } //@hle:syscall{94AA61EE|ThreadManForUser|sceKernelGetThreadCurrentPriority|g|int sceKernelGetThreadCurrentPriority(void)}
extern "C" void __cdecl ThreadManForUser_3B183E26(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelGetThreadExitStatus                     >(c); } //@hle:syscall{3B183E26|ThreadManForUser|sceKernelGetThreadExitStatus|gg|int sceKernelGetThreadExitStatus(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_17C1684E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferThreadStatus                       >(c); } //@hle:syscall{17C1684E|ThreadManForUser|sceKernelReferThreadStatus|ggg|int sceKernelReferThreadStatus(SceUID thid, SceKernelThreadInfo * info)}
extern "C" void __cdecl ThreadManForUser_FFC36A14(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferThreadRunStatus                    >(c); } //@hle:syscall{FFC36A14|ThreadManForUser|sceKernelReferThreadRunStatus|ggg|int sceKernelReferThreadRunStatus(SceUID thid, SceKernelThreadRunStatus * status)}
extern "C" void __cdecl ThreadManForUser_D13BDE95(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelCheckThreadStack                        >(c); } //@hle:syscall{D13BDE95|ThreadManForUser|sceKernelCheckThreadStack|g|int sceKernelCheckThreadStack(void)}
extern "C" void __cdecl ThreadManForUser_52089CA1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelGetThreadStackFreeSize                  >(c); } //@hle:syscall{52089CA1|ThreadManForUser|sceKernelGetThreadStackFreeSize|gg|int sceKernelGetThreadStackFreeSize(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_07F3A4BC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0               < hle::ThreadManForUser::_sceKernelStartThread                            >(c); } //@hle:syscall{07F3A4BC|ThreadManForUser|_sceKernelStartThread|0|void _sceKernelStartThread(void)}
extern "C" void __cdecl ThreadManForUser_532A522E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0               < hle::ThreadManForUser::_sceKernelExitThread                             >(c); } //@hle:syscall{532A522E|ThreadManForUser|_sceKernelExitThread|0|void _sceKernelExitThread(void)}
extern "C" void __cdecl ThreadManForUser_E0A68B8C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0               < hle::ThreadManForUser::_sceKernelIdleThread                             >(c); } //@hle:syscall{E0A68B8C|ThreadManForUser|_sceKernelIdleThread|0|void _sceKernelIdleThread(void)}
extern "C" void __cdecl ThreadManForUser_0C106E53(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ThreadManForUser::sceKernelRegisterThreadEventHandler              >(c); } //@hle:syscall{0C106E53|ThreadManForUser|sceKernelRegisterThreadEventHandler|gggggg|SceUID sceKernelRegisterThreadEventHandler(const char * name, SceUID threadID, int mask, SceKernelThreadEventHandler handler, void * arg)}
extern "C" void __cdecl ThreadManForUser_72F3C145(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelReleaseThreadEventHandler               >(c); } //@hle:syscall{72F3C145|ThreadManForUser|sceKernelReleaseThreadEventHandler|gg|int sceKernelReleaseThreadEventHandler(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_369EEB6B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferThreadEventHandlerStatus           >(c); } //@hle:syscall{369EEB6B|ThreadManForUser|sceKernelReferThreadEventHandlerStatus|ggg|int sceKernelReferThreadEventHandlerStatus(SceUID uid, struct SceKernelThreadEventHandlerInfo * info)}
extern "C" void __cdecl ThreadManForUser_9ACE131E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelSleepThread                             >(c); } //@hle:syscall{9ACE131E|ThreadManForUser|sceKernelSleepThread|g|int sceKernelSleepThread(void)}
extern "C" void __cdecl ThreadManForUser_82826F70(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelSleepThreadCB                           >(c); } //@hle:syscall{82826F70|ThreadManForUser|sceKernelSleepThreadCB|g|int sceKernelSleepThreadCB(void)}
extern "C" void __cdecl ThreadManForUser_D59EAD2F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelWakeupThread                            >(c); } //@hle:syscall{D59EAD2F|ThreadManForUser|sceKernelWakeupThread|gg|int sceKernelWakeupThread(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_FCCFAD26(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelCancelWakeupThread                      >(c); } //@hle:syscall{FCCFAD26|ThreadManForUser|sceKernelCancelWakeupThread|gg|int sceKernelCancelWakeupThread(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_9944F31F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelSuspendThread                           >(c); } //@hle:syscall{9944F31F|ThreadManForUser|sceKernelSuspendThread|gg|int sceKernelSuspendThread(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_75156E8F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelResumeThread                            >(c); } //@hle:syscall{75156E8F|ThreadManForUser|sceKernelResumeThread|gg|int sceKernelResumeThread(SceUID thid)}
extern "C" void __cdecl ThreadManForUser_278C0DF5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelWaitThreadEnd                           >(c); } //@hle:syscall{278C0DF5|ThreadManForUser|sceKernelWaitThreadEnd|ggg|int sceKernelWaitThreadEnd(SceUID thid, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_840E8133(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelWaitThreadEndCB                         >(c); } //@hle:syscall{840E8133|ThreadManForUser|sceKernelWaitThreadEndCB|ggg|int sceKernelWaitThreadEndCB(SceUID thid, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_D6DA4BA1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ThreadManForUser::sceKernelCreateSema                              >(c); } //@hle:syscall{D6DA4BA1|ThreadManForUser|sceKernelCreateSema|gggggg|SceUID sceKernelCreateSema(const char * name, SceUInt attr, int initVal, int maxVal, const SceKernelSemaOptParam * opt)}
extern "C" void __cdecl ThreadManForUser_28B6489C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDeleteSema                              >(c); } //@hle:syscall{28B6489C|ThreadManForUser|sceKernelDeleteSema|gg|int sceKernelDeleteSema(SceUID semaid)}
extern "C" void __cdecl ThreadManForUser_3F53E640(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelSignalSema                              >(c); } //@hle:syscall{3F53E640|ThreadManForUser|sceKernelSignalSema|ggg|int sceKernelSignalSema(SceUID semaid, int signal)}
extern "C" void __cdecl ThreadManForUser_4E3A1105(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelWaitSema                                >(c); } //@hle:syscall{4E3A1105|ThreadManForUser|sceKernelWaitSema|gggg|int sceKernelWaitSema(SceUID semaid, int signal, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_6D212BAC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelWaitSemaCB                              >(c); } //@hle:syscall{6D212BAC|ThreadManForUser|sceKernelWaitSemaCB|gggg|int sceKernelWaitSemaCB(SceUID semaid, int signal, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_58B1F937(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelPollSema                                >(c); } //@hle:syscall{58B1F937|ThreadManForUser|sceKernelPollSema|ggg|int sceKernelPollSema(SceUID semaid, int signal)}
extern "C" void __cdecl ThreadManForUser_8FFDF9A2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelCancelSema                              >(c); } //@hle:syscall{8FFDF9A2|ThreadManForUser|sceKernelCancelSema|gggg|int sceKernelCancelSema(SceUID semid, int signal, int * numWaitThreads))}
extern "C" void __cdecl ThreadManForUser_BC6FEBC5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferSemaStatus                         >(c); } //@hle:syscall{BC6FEBC5|ThreadManForUser|sceKernelReferSemaStatus|ggg|int sceKernelReferSemaStatus(SceUID semaid, SceKernelSemaInfo * info)}
extern "C" void __cdecl ThreadManForUser_55C20A00(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::ThreadManForUser::sceKernelCreateEventFlag                         >(c); } //@hle:syscall{55C20A00|ThreadManForUser|sceKernelCreateEventFlag|ggggg|SceUID sceKernelCreateEventFlag(const char * name, SceUInt attr, int bits, const SceKernelEventFlagOptParam * opt)}
extern "C" void __cdecl ThreadManForUser_EF9E4C70(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDeleteEventFlag                         >(c); } //@hle:syscall{EF9E4C70|ThreadManForUser|sceKernelDeleteEventFlag|gg|int sceKernelDeleteEventFlag(int evid)}
extern "C" void __cdecl ThreadManForUser_1FB15A32(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelSetEventFlag                            >(c); } //@hle:syscall{1FB15A32|ThreadManForUser|sceKernelSetEventFlag|ggg|int sceKernelSetEventFlag(SceUID evid, SceUInt bits)}
extern "C" void __cdecl ThreadManForUser_812346E4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelClearEventFlag                          >(c); } //@hle:syscall{812346E4|ThreadManForUser|sceKernelClearEventFlag|ggg|int sceKernelClearEventFlag(SceUID evid, SceUInt bits)}
extern "C" void __cdecl ThreadManForUser_402FCF22(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ThreadManForUser::sceKernelWaitEventFlag                           >(c); } //@hle:syscall{402FCF22|ThreadManForUser|sceKernelWaitEventFlag|gggggg|int sceKernelWaitEventFlag(int evid, SceUInt bits, int waitmode, SceUInt * outBits, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_328C546A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ThreadManForUser::sceKernelWaitEventFlagCB                         >(c); } //@hle:syscall{328C546A|ThreadManForUser|sceKernelWaitEventFlagCB|gggggg|int sceKernelWaitEventFlagCB(int evid, SceUInt bits, int waitmode, SceUInt * outBits, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_30FD48F0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::ThreadManForUser::sceKernelPollEventFlag                           >(c); } //@hle:syscall{30FD48F0|ThreadManForUser|sceKernelPollEventFlag|ggggg|int sceKernelPollEventFlag(int evid, SceUInt bits, int waitmode, SceUInt * outBits)}
extern "C" void __cdecl ThreadManForUser_CD203292(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelCancelEventFlag                         >(c); } //@hle:syscall{CD203292|ThreadManForUser|sceKernelCancelEventFlag|gggg|int sceKernelCancelEventFlag(SceUID evid, SceUInt bits, int * numWaitThreads))}
extern "C" void __cdecl ThreadManForUser_A66B0120(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferEventFlagStatus                    >(c); } //@hle:syscall{A66B0120|ThreadManForUser|sceKernelReferEventFlagStatus|ggg|int sceKernelReferEventFlagStatus(SceUID event, SceKernelEventFlagInfo * status)}
extern "C" void __cdecl ThreadManForUser_8125221D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelCreateMbx                               >(c); } //@hle:syscall{8125221D|ThreadManForUser|sceKernelCreateMbx|gggg|SceUID sceKernelCreateMbx(const char * name, SceUInt attr, const SceKernelMbxOptParam * opt)}
extern "C" void __cdecl ThreadManForUser_86255ADA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDeleteMbx                               >(c); } //@hle:syscall{86255ADA|ThreadManForUser|sceKernelDeleteMbx|gg|int sceKernelDeleteMbx(SceUID mbxid)}
extern "C" void __cdecl ThreadManForUser_E9B3061E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelSendMbx                                 >(c); } //@hle:syscall{E9B3061E|ThreadManForUser|sceKernelSendMbx|ggg|int sceKernelSendMbx(SceUID mbxid, void * message)}
extern "C" void __cdecl ThreadManForUser_18260574(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelReceiveMbx                              >(c); } //@hle:syscall{18260574|ThreadManForUser|sceKernelReceiveMbx|gggg|int sceKernelReceiveMbx(SceUID mbxid, void * pmessage, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_F3986382(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelReceiveMbxCB                            >(c); } //@hle:syscall{F3986382|ThreadManForUser|sceKernelReceiveMbxCB|gggg|int sceKernelReceiveMbxCB(SceUID mbxid, void * pmessage, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_0D81716A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelPollMbx                                 >(c); } //@hle:syscall{0D81716A|ThreadManForUser|sceKernelPollMbx|ggg|int sceKernelPollMbx(SceUID mbxid, void * pmessage)}
extern "C" void __cdecl ThreadManForUser_87D4DD36(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelCancelReceiveMbx                        >(c); } //@hle:syscall{87D4DD36|ThreadManForUser|sceKernelCancelReceiveMbx|ggg|int sceKernelCancelReceiveMbx(SceUID mbxid, int * numWaitThreads)}
extern "C" void __cdecl ThreadManForUser_A8E8C846(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferMbxStatus                          >(c); } //@hle:syscall{A8E8C846|ThreadManForUser|sceKernelReferMbxStatus|ggg|int sceKernelReferMbxStatus(SceUID mbxid, SceKernelMbxInfo * info)}
extern "C" void __cdecl ThreadManForUser_7C0DC2A0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ThreadManForUser::sceKernelCreateMsgPipe                           >(c); } //@hle:syscall{7C0DC2A0|ThreadManForUser|sceKernelCreateMsgPipe|gggggg|SceUID sceKernelCreateMsgPipe(const char * name, SceUID mpid, SceUInt attr, SceSize bufsize, const SceKernelMppOptParam * opt)}
extern "C" void __cdecl ThreadManForUser_F0B7DA1C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDeleteMsgPipe                           >(c); } //@hle:syscall{F0B7DA1C|ThreadManForUser|sceKernelDeleteMsgPipe|gg|int sceKernelDeleteMsgPipe(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_876DBFAD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::ThreadManForUser::sceKernelSendMsgPipe                             >(c); } //@hle:syscall{876DBFAD|ThreadManForUser|sceKernelSendMsgPipe|ggggggg|int sceKernelSendMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_7C41F2C2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::ThreadManForUser::sceKernelSendMsgPipeCB                           >(c); } //@hle:syscall{7C41F2C2|ThreadManForUser|sceKernelSendMsgPipeCB|ggggggg|int sceKernelSendMsgPipeCB(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_884C9F90(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ThreadManForUser::sceKernelTrySendMsgPipe                          >(c); } //@hle:syscall{884C9F90|ThreadManForUser|sceKernelTrySendMsgPipe|gggggg|int sceKernelTrySendMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result)}
extern "C" void __cdecl ThreadManForUser_74829B76(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::ThreadManForUser::sceKernelReceiveMsgPipe                          >(c); } //@hle:syscall{74829B76|ThreadManForUser|sceKernelReceiveMsgPipe|ggggggg|int sceKernelReceiveMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_FBFA697D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::ThreadManForUser::sceKernelReceiveMsgPipeCB                        >(c); } //@hle:syscall{FBFA697D|ThreadManForUser|sceKernelReceiveMsgPipeCB|ggggggg|int sceKernelReceiveMsgPipeCB(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_DF52098F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ThreadManForUser::sceKernelTryReceiveMsgPipe                       >(c); } //@hle:syscall{DF52098F|ThreadManForUser|sceKernelTryReceiveMsgPipe|gggggg|int sceKernelTryReceiveMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_349B864D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelCancelMsgPipe                           >(c); } //@hle:syscall{349B864D|ThreadManForUser|sceKernelCancelMsgPipe|gggg|int sceKernelCancelMsgPipe(SceUID uid, int * numSendWaitThreads, int * numRecvWaitThreads)}
extern "C" void __cdecl ThreadManForUser_33BE4024(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferMsgPipeStatus                      >(c); } //@hle:syscall{33BE4024|ThreadManForUser|sceKernelReferMsgPipeStatus|ggg|int sceKernelReferMsgPipeStatus(SceUID uid, SceKernelMppInfo * info)}
extern "C" void __cdecl ThreadManForUser_56C039B5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ThreadManForUser::sceKernelCreateVpl                               >(c); } //@hle:syscall{56C039B5|ThreadManForUser|sceKernelCreateVpl|gggggg|SceUID sceKernelCreateVpl(const char * name, SceUID mpid, SceUInt attr, unsigned int size, SceKernelVplOptParam * opt)}
extern "C" void __cdecl ThreadManForUser_89B3D48C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDeleteVpl                               >(c); } //@hle:syscall{89B3D48C|ThreadManForUser|sceKernelDeleteVpl|gg|int sceKernelDeleteVpl(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_BED27435(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::ThreadManForUser::sceKernelAllocateVpl                             >(c); } //@hle:syscall{BED27435|ThreadManForUser|sceKernelAllocateVpl|ggggg|int sceKernelAllocateVpl(SceUID uid, unsigned int size, void * * data, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_EC0A693F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::ThreadManForUser::sceKernelAllocateVplCB                           >(c); } //@hle:syscall{EC0A693F|ThreadManForUser|sceKernelAllocateVplCB|ggggg|int sceKernelAllocateVplCB(SceUID uid, unsigned int size, void * * data, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_AF36D708(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelTryAllocateVpl                          >(c); } //@hle:syscall{AF36D708|ThreadManForUser|sceKernelTryAllocateVpl|gggg|int sceKernelTryAllocateVpl(SceUID uid, unsigned int size, void * * data)}
extern "C" void __cdecl ThreadManForUser_B736E9FF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelFreeVpl                                 >(c); } //@hle:syscall{B736E9FF|ThreadManForUser|sceKernelFreeVpl|ggg|int sceKernelFreeVpl(SceUID uid, void * data)}
extern "C" void __cdecl ThreadManForUser_1D371B8A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelCancelVpl                               >(c); } //@hle:syscall{1D371B8A|ThreadManForUser|sceKernelCancelVpl|ggg|int sceKernelCancelVpl(SceUID uid, int * numWaitThreads)}
extern "C" void __cdecl ThreadManForUser_39810265(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferVplStatus                          >(c); } //@hle:syscall{39810265|ThreadManForUser|sceKernelReferVplStatus|ggg|int sceKernelReferVplStatus(SceUID uid, SceKernelVplInfo * info)}
extern "C" void __cdecl ThreadManForUser_C07BB470(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::ThreadManForUser::sceKernelCreateFpl                               >(c); } //@hle:syscall{C07BB470|ThreadManForUser|sceKernelCreateFpl|ggggggg|int sceKernelCreateFpl(const char * name, SceUID mpid, SceUInt attr, unsigned int size, int blocks, SceKernelFplOptParam * opt)}
extern "C" void __cdecl ThreadManForUser_ED1410E0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDeleteFpl                               >(c); } //@hle:syscall{ED1410E0|ThreadManForUser|sceKernelDeleteFpl|gg|int sceKernelDeleteFpl(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_D979E9BF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelAllocateFpl                             >(c); } //@hle:syscall{D979E9BF|ThreadManForUser|sceKernelAllocateFpl|gggg|int sceKernelAllocateFpl(SceUID uid, void * * data, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_E7282CB6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelAllocateFplCB                           >(c); } //@hle:syscall{E7282CB6|ThreadManForUser|sceKernelAllocateFplCB|gggg|int sceKernelAllocateFplCB(SceUID uid, void * * data, SceUInt * timeout)}
extern "C" void __cdecl ThreadManForUser_623AE665(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelTryAllocateFpl                          >(c); } //@hle:syscall{623AE665|ThreadManForUser|sceKernelTryAllocateFpl|ggg|int sceKernelTryAllocateFpl(SceUID uid, void * * data)}
extern "C" void __cdecl ThreadManForUser_F6414A71(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelFreeFpl                                 >(c); } //@hle:syscall{F6414A71|ThreadManForUser|sceKernelFreeFpl|ggg|int sceKernelFreeFpl(SceUID uid, void * data)}
extern "C" void __cdecl ThreadManForUser_A8AA591F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelCancelFpl                               >(c); } //@hle:syscall{A8AA591F|ThreadManForUser|sceKernelCancelFpl|ggg|int sceKernelCancelFpl(SceUID uid, int * numWaitThreads)}
extern "C" void __cdecl ThreadManForUser_D8199E4C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferFplStatus                          >(c); } //@hle:syscall{D8199E4C|ThreadManForUser|sceKernelReferFplStatus|ggg|int sceKernelReferFplStatus(SceUID uid, SceKernelFplInfo * info)}
extern "C" void __cdecl ThreadManForUser_DB738F35(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelGetSystemTime                           >(c); } //@hle:syscall{DB738F35|ThreadManForUser|sceKernelGetSystemTime|gg|int sceKernelGetSystemTime(SceKernelSysClock * time)}
extern "C" void __cdecl ThreadManForUser_82BC5777(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$G               < hle::ThreadManForUser::sceKernelGetSystemTimeWide                       >(c); } //@hle:syscall{82BC5777|ThreadManForUser|sceKernelGetSystemTimeWide|G|SceInt64 sceKernelGetSystemTimeWide(void)}
extern "C" void __cdecl ThreadManForUser_369ED59D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelGetSystemTimeLow                        >(c); } //@hle:syscall{369ED59D|ThreadManForUser|sceKernelGetSystemTimeLow|g|unsigned int sceKernelGetSystemTimeLow(void)}
extern "C" void __cdecl ThreadManForUser_110DEC9A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelUSec2SysClock                           >(c); } //@hle:syscall{110DEC9A|ThreadManForUser|sceKernelUSec2SysClock|ggg|int sceKernelUSec2SysClock(unsigned int usec, SceKernelSysClock * clock)}
extern "C" void __cdecl ThreadManForUser_BA6B92E2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelSysClock2USec                           >(c); } //@hle:syscall{BA6B92E2|ThreadManForUser|sceKernelSysClock2USec|gggg|int sceKernelSysClock2USec(const SceKernelSysClock * clock, unsigned int * low, unsigned int * high)}
extern "C" void __cdecl ThreadManForUser_C8CD158C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$Gg              < hle::ThreadManForUser::sceKernelUSec2SysClockWide                       >(c); } //@hle:syscall{C8CD158C|ThreadManForUser|sceKernelUSec2SysClockWide|Gg|SceInt64 sceKernelUSec2SysClockWide(unsigned int usec)}
extern "C" void __cdecl ThreadManForUser_E1619D7C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gGgg            < hle::ThreadManForUser::sceKernelSysClock2USecWide                       >(c); } //@hle:syscall{E1619D7C|ThreadManForUser|sceKernelSysClock2USecWide|gGgg|int sceKernelSysClock2USecWide(SceInt64 clock, unsigned * low, unsigned int * high)}
extern "C" void __cdecl ThreadManForUser_CEADEB47(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDelayThread                             >(c); } //@hle:syscall{CEADEB47|ThreadManForUser|sceKernelDelayThread|gg|int sceKernelDelayThread(SceUInt delay)}
extern "C" void __cdecl ThreadManForUser_68DA9E36(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDelayThreadCB                           >(c); } //@hle:syscall{68DA9E36|ThreadManForUser|sceKernelDelayThreadCB|gg|int sceKernelDelayThreadCB(SceUInt delay)}
extern "C" void __cdecl ThreadManForUser_BD123D9E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDelaySysClockThread                     >(c); } //@hle:syscall{BD123D9E|ThreadManForUser|sceKernelDelaySysClockThread|gg|int sceKernelDelaySysClockThread(const SceKernelSysClock * delay)}
extern "C" void __cdecl ThreadManForUser_1181E963(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDelaySysClockThreadCB                   >(c); } //@hle:syscall{1181E963|ThreadManForUser|sceKernelDelaySysClockThreadCB|gg|int sceKernelDelaySysClockThreadCB(const SceKernelSysClock * delay)}
extern "C" void __cdecl ThreadManForUser_6652B8CA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelSetAlarm                                >(c); } //@hle:syscall{6652B8CA|ThreadManForUser|sceKernelSetAlarm|gggg|SceUID sceKernelSetAlarm(SceUInt clock, SceKernelAlarmHandler handler, void * common)}
extern "C" void __cdecl ThreadManForUser_B2C25152(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelSetSysClockAlarm                        >(c); } //@hle:syscall{B2C25152|ThreadManForUser|sceKernelSetSysClockAlarm|gggg|SceUID sceKernelSetSysClockAlarm(SceKernelSysClock * clock, SceKernelAlarmHandler handler, void * arg)}
extern "C" void __cdecl ThreadManForUser_7E65B999(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelCancelAlarm                             >(c); } //@hle:syscall{7E65B999|ThreadManForUser|sceKernelCancelAlarm|gg|int sceKernelCancelAlarm(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_DAA3F564(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferAlarmStatus                        >(c); } //@hle:syscall{DAA3F564|ThreadManForUser|sceKernelReferAlarmStatus|ggg|int sceKernelReferAlarmStatus(SceUID uid, SceKernelAlarmInfo * info)}
extern "C" void __cdecl ThreadManForUser_20FFF560(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelCreateVTimer                            >(c); } //@hle:syscall{20FFF560|ThreadManForUser|sceKernelCreateVTimer|ggg|SceUID sceKernelCreateVTimer(const char * name, const SceKernelVTimerOptParam * opt)}
extern "C" void __cdecl ThreadManForUser_328F9E52(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDeleteVTimer                            >(c); } //@hle:syscall{328F9E52|ThreadManForUser|sceKernelDeleteVTimer|gg|int sceKernelDeleteVTimer(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_B3A59970(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelGetVTimerBase                           >(c); } //@hle:syscall{B3A59970|ThreadManForUser|sceKernelGetVTimerBase|ggg|int sceKernelGetVTimerBase(SceUID uid, SceKernelSysClock * base)}
extern "C" void __cdecl ThreadManForUser_034A921F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelGetVTimerTime                           >(c); } //@hle:syscall{034A921F|ThreadManForUser|sceKernelGetVTimerTime|ggg|int sceKernelGetVTimerTime(SceUID uid, SceKernelSysClock * time)}
extern "C" void __cdecl ThreadManForUser_542AD630(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelSetVTimerTime                           >(c); } //@hle:syscall{542AD630|ThreadManForUser|sceKernelSetVTimerTime|ggg|int sceKernelSetVTimerTime(SceUID uid, SceKernelSysClock * time)}
extern "C" void __cdecl ThreadManForUser_C68D9437(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelStartVTimer                             >(c); } //@hle:syscall{C68D9437|ThreadManForUser|sceKernelStartVTimer|gg|int sceKernelStartVTimer(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_D0AEEE87(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelStopVTimer                              >(c); } //@hle:syscall{D0AEEE87|ThreadManForUser|sceKernelStopVTimer|gg|int sceKernelStopVTimer(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_D8B299AE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::ThreadManForUser::sceKernelSetVTimerHandler                        >(c); } //@hle:syscall{D8B299AE|ThreadManForUser|sceKernelSetVTimerHandler|ggggg|int sceKernelSetVTimerHandler(SceUID uid, SceKernelSysClock * time, SceKernelVTimerHandler handler, void * arg)}
extern "C" void __cdecl ThreadManForUser_D2D615EF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelCancelVTimerHandler                     >(c); } //@hle:syscall{D2D615EF|ThreadManForUser|sceKernelCancelVTimerHandler|gg|int sceKernelCancelVTimerHandler(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_B7C18B77(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$Gg              < hle::ThreadManForUser::sceKernelGetVTimerBaseWide                       >(c); } //@hle:syscall{B7C18B77|ThreadManForUser|sceKernelGetVTimerBaseWide|Gg|SceInt64 sceKernelGetVTimerBaseWide(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_C0B3FFD2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$Gg              < hle::ThreadManForUser::sceKernelGetVTimerTimeWide                       >(c); } //@hle:syscall{C0B3FFD2|ThreadManForUser|sceKernelGetVTimerTimeWide|Gg|SceInt64 sceKernelGetVTimerTimeWide(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_FB6425C3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$GgG             < hle::ThreadManForUser::sceKernelSetVTimerTimeWide                       >(c); } //@hle:syscall{FB6425C3|ThreadManForUser|sceKernelSetVTimerTimeWide|GgG|SceInt64 sceKernelSetVTimerTimeWide(SceUID uid, SceInt64 time)}
extern "C" void __cdecl ThreadManForUser_53B00E9A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggGgg           < hle::ThreadManForUser::sceKernelSetVTimerHandlerWide                    >(c); } //@hle:syscall{53B00E9A|ThreadManForUser|sceKernelSetVTimerHandlerWide|ggGgg|int sceKernelSetVTimerHandlerWide(SceUID uid, SceInt64 time, SceKernelVTimerHandlerWide handler, void * arg)}
extern "C" void __cdecl ThreadManForUser_5F32BEAA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferVTimerStatus                       >(c); } //@hle:syscall{5F32BEAA|ThreadManForUser|sceKernelReferVTimerStatus|ggg|int sceKernelReferVTimerStatus(SceUID uid, SceKernelVTimerInfo * info)}
extern "C" void __cdecl ThreadManForUser_0E927AED(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0               < hle::ThreadManForUser::_sceKernelReturnFromTimerHandler                 >(c); } //@hle:syscall{0E927AED|ThreadManForUser|_sceKernelReturnFromTimerHandler|0|void _sceKernelReturnFromTimerHandler(void)}
extern "C" void __cdecl ThreadManForUser_E81CAF8F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ThreadManForUser::sceKernelCreateCallback                          >(c); } //@hle:syscall{E81CAF8F|ThreadManForUser|sceKernelCreateCallback|gggg|int sceKernelCreateCallback(const char * name, SceKernelCallbackFunction func, void * arg)}
extern "C" void __cdecl ThreadManForUser_EDBA5844(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelDeleteCallback                          >(c); } //@hle:syscall{EDBA5844|ThreadManForUser|sceKernelDeleteCallback|gg|int sceKernelDeleteCallback(SceUID cbid)}
extern "C" void __cdecl ThreadManForUser_C11BA8C4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelNotifyCallback                          >(c); } //@hle:syscall{C11BA8C4|ThreadManForUser|sceKernelNotifyCallback|ggg|int sceKernelNotifyCallback(SceUID cbid, int arg)}
extern "C" void __cdecl ThreadManForUser_BA4051D6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelCancelCallback                          >(c); } //@hle:syscall{BA4051D6|ThreadManForUser|sceKernelCancelCallback|gg|int sceKernelCancelCallback(SceUID cbid)}
extern "C" void __cdecl ThreadManForUser_2A3D44FF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelGetCallbackCount                        >(c); } //@hle:syscall{2A3D44FF|ThreadManForUser|sceKernelGetCallbackCount|gg|int sceKernelGetCallbackCount(SceUID cbid)}
extern "C" void __cdecl ThreadManForUser_349D6D6C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelCheckCallback                           >(c); } //@hle:syscall{349D6D6C|ThreadManForUser|sceKernelCheckCallback|g|int sceKernelCheckCallback(void)}
extern "C" void __cdecl ThreadManForUser_730ED8BC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ThreadManForUser::sceKernelReferCallbackStatus                     >(c); } //@hle:syscall{730ED8BC|ThreadManForUser|sceKernelReferCallbackStatus|ggg|int sceKernelReferCallbackStatus(SceUID cb, SceKernelCallbackInfo * status)}
extern "C" void __cdecl ThreadManForUser_6E9EA350(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0               < hle::ThreadManForUser::_sceKernelReturnFromCallback                     >(c); } //@hle:syscall{6E9EA350|ThreadManForUser|_sceKernelReturnFromCallback|0|void _sceKernelReturnFromCallback(void)}
extern "C" void __cdecl ThreadManForUser_627E6F3A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelReferSystemStatus                       >(c); } //@hle:syscall{627E6F3A|ThreadManForUser|sceKernelReferSystemStatus|gg|int sceKernelReferSystemStatus(SceKernelSystemStatus * status)}
extern "C" void __cdecl ThreadManForUser_94416130(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::ThreadManForUser::sceKernelGetThreadmanIdList                      >(c); } //@hle:syscall{94416130|ThreadManForUser|sceKernelGetThreadmanIdList|ggggg|int sceKernelGetThreadmanIdList(enum SceKernelIdListType type, SceUID * readbuf, int readbufsize, int * idcount)}
extern "C" void __cdecl ThreadManForUser_57CF62DD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ThreadManForUser::sceKernelGetThreadmanIdType                      >(c); } //@hle:syscall{57CF62DD|ThreadManForUser|sceKernelGetThreadmanIdType|gg|enum sceKernelGetThreadmanIdType(SceUID uid)}
extern "C" void __cdecl ThreadManForUser_B7D098C6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelCreateMutex                             >(c); } //@hle:syscall{B7D098C6|ThreadManForUser|sceKernelCreateMutex|g|??? sceKernelCreateMutex()}
extern "C" void __cdecl ThreadManForUser_F8170FBE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelDeleteMutex                             >(c); } //@hle:syscall{F8170FBE|ThreadManForUser|sceKernelDeleteMutex|g|??? sceKernelDeleteMutex()}
extern "C" void __cdecl ThreadManForUser_B011B11F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelLockMutex                               >(c); } //@hle:syscall{B011B11F|ThreadManForUser|sceKernelLockMutex|g|??? sceKernelLockMutex()}
extern "C" void __cdecl ThreadManForUser_5BF4DD27(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelLockMutexCB                             >(c); } //@hle:syscall{5BF4DD27|ThreadManForUser|sceKernelLockMutexCB|g|??? sceKernelLockMutexCB()}
extern "C" void __cdecl ThreadManForUser_0DDCD2C9(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelTryLockMutex                            >(c); } //@hle:syscall{0DDCD2C9|ThreadManForUser|sceKernelTryLockMutex|g|??? sceKernelTryLockMutex()}
extern "C" void __cdecl ThreadManForUser_6B30100F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelUnlockMutex                             >(c); } //@hle:syscall{6B30100F|ThreadManForUser|sceKernelUnlockMutex|g|??? sceKernelUnlockMutex()}
extern "C" void __cdecl ThreadManForUser_87D9223C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelCancelMutex                             >(c); } //@hle:syscall{87D9223C|ThreadManForUser|sceKernelCancelMutex|g|??? sceKernelCancelMutex()}
extern "C" void __cdecl ThreadManForUser_A9C2CB9A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelReferMutexStatus                        >(c); } //@hle:syscall{A9C2CB9A|ThreadManForUser|sceKernelReferMutexStatus|g|??? sceKernelReferMutexStatus()}
extern "C" void __cdecl ThreadManForUser_19CFF145(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelCreateLwMutex                           >(c); } //@hle:syscall{19CFF145|ThreadManForUser|sceKernelCreateLwMutex|g|??? sceKernelCreateLwMutex()}
extern "C" void __cdecl ThreadManForUser_60107536(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelDeleteLwMutex                           >(c); } //@hle:syscall{60107536|ThreadManForUser|sceKernelDeleteLwMutex|g|??? sceKernelDeleteLwMutex()}
extern "C" void __cdecl ThreadManForUser_4C145944(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelReferLwMutexStatusByID                  >(c); } //@hle:syscall{4C145944|ThreadManForUser|sceKernelReferLwMutexStatusByID|g|??? sceKernelReferLwMutexStatusByID()}
extern "C" void __cdecl ThreadManForUser_64D4540E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelReferThreadProfiler                     >(c); } //@hle:syscall{64D4540E|ThreadManForUser|sceKernelReferThreadProfiler|g|SceProfilerRegs * sceKernelReferThreadProfiler(void)}
extern "C" void __cdecl ThreadManForUser_8218B4DD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelReferGlobalProfiler                     >(c); } //@hle:syscall{8218B4DD|ThreadManForUser|sceKernelReferGlobalProfiler|g|SceProfilerRegs * sceKernelReferGlobalProfiler(void)}
extern "C" void __cdecl ThreadManForUser_1AF94D03(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::sceKernelDonateWakeupThread                      >(c); } //@hle:syscall{1AF94D03|ThreadManForUser|sceKernelDonateWakeupThread|g|??? sceKernelDonateWakeupThread()}
extern "C" void __cdecl ThreadManForUser_31327F19(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::ThreadManForUser_31327F19                        >(c); } //@hle:syscall{31327F19|ThreadManForUser|ThreadManForUser_31327F19|g|??? ThreadManForUser_31327F19()}
extern "C" void __cdecl ThreadManForUser_71040D5C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::ThreadManForUser_71040D5C                        >(c); } //@hle:syscall{71040D5C|ThreadManForUser|ThreadManForUser_71040D5C|g|??? ThreadManForUser_71040D5C()}
extern "C" void __cdecl ThreadManForUser_7CFF8CF3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::ThreadManForUser_7CFF8CF3                        >(c); } //@hle:syscall{7CFF8CF3|ThreadManForUser|ThreadManForUser_7CFF8CF3|g|??? ThreadManForUser_7CFF8CF3()}
extern "C" void __cdecl ThreadManForUser_8672E3D0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::ThreadManForUser_8672E3D0                        >(c); } //@hle:syscall{8672E3D0|ThreadManForUser|ThreadManForUser_8672E3D0|g|??? ThreadManForUser_8672E3D0()}
extern "C" void __cdecl ThreadManForUser_BEED3A47(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ThreadManForUser::ThreadManForUser_BEED3A47                        >(c); } //@hle:syscall{BEED3A47|ThreadManForUser|ThreadManForUser_BEED3A47|g|??? ThreadManForUser_BEED3A47()}