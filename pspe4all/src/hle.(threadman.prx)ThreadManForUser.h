//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_threadman_prx_ThreadManForUser_h__
#define hle_threadman_prx_ThreadManForUser_h__

namespace hle
{
    namespace ThreadManForUser //@hle:library-start{ThreadManForUser|sceThreadManager|threadman.prx}
    {
        //@hle:function{446D8DE6|ThreadManForUser|sceKernelCreateThread|ggggggg|SceUID sceKernelCreateThread(const char * name, SceKernelThreadEntry entry, int initPriority, int stackSize, SceUInt attr, const SceKernelThreadOptParam * opt)}
        extern int  sceKernelCreateThread(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{9FA03CD3|ThreadManForUser|sceKernelDeleteThread|gg|int sceKernelDeleteThread(SceUID thid)}
        extern int  sceKernelDeleteThread(u32 $a0);
        //@hle:function{F475845D|ThreadManForUser|sceKernelStartThread|gggg|int sceKernelStartThread(SceUID thid, SceSize arglen, void * argp)}
        extern int  sceKernelStartThread(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{AA73C935|ThreadManForUser|sceKernelExitThread|gg|int sceKernelExitThread(int status)}
        extern int  sceKernelExitThread(u32 $a0);
        //@hle:function{809CE29B|ThreadManForUser|sceKernelExitDeleteThread|gg|int sceKernelExitDeleteThread(int status)}
        extern int  sceKernelExitDeleteThread(u32 $a0);
        //@hle:function{616403BA|ThreadManForUser|sceKernelTerminateThread|gg|int sceKernelTerminateThread(SceUID thid)}
        extern int  sceKernelTerminateThread(u32 $a0);
        //@hle:function{383F7BCC|ThreadManForUser|sceKernelTerminateDeleteThread|gg|int sceKernelTerminateDeleteThread(SceUID thid)}
        extern int  sceKernelTerminateDeleteThread(u32 $a0);
        //@hle:function{3AD58B8C|ThreadManForUser|sceKernelSuspendDispatchThread|g|int sceKernelSuspendDispatchThread(void)}
        extern int  sceKernelSuspendDispatchThread();
        //@hle:function{27E22EC2|ThreadManForUser|sceKernelResumeDispatchThread|gg|int sceKernelResumeDispatchThread(int state)}
        extern int  sceKernelResumeDispatchThread(u32 $a0);
        //@hle:function{EA748E31|ThreadManForUser|sceKernelChangeCurrentThreadAttr|ggg|int sceKernelChangeCurrentThreadAttr(int unknown, SceUInt attr)}
        extern int  sceKernelChangeCurrentThreadAttr(u32 $a0, u32 $a1);
        //@hle:function{71BC9871|ThreadManForUser|sceKernelChangeThreadPriority|ggg|int sceKernelChangeThreadPriority(SceUID thid, int priority)}
        extern int  sceKernelChangeThreadPriority(u32 $a0, u32 $a1);
        //@hle:function{912354A7|ThreadManForUser|sceKernelRotateThreadReadyQueue|gg|int sceKernelRotateThreadReadyQueue(int priority)}
        extern int  sceKernelRotateThreadReadyQueue(u32 $a0);
        //@hle:function{2C34E053|ThreadManForUser|sceKernelReleaseWaitThread|gg|int sceKernelReleaseWaitThread(SceUID thid)}
        extern int  sceKernelReleaseWaitThread(u32 $a0);
        //@hle:function{293B45B8|ThreadManForUser|sceKernelGetThreadId|g|int sceKernelGetThreadId(void)}
        extern int  sceKernelGetThreadId();
        //@hle:function{94AA61EE|ThreadManForUser|sceKernelGetThreadCurrentPriority|g|int sceKernelGetThreadCurrentPriority(void)}
        extern int  sceKernelGetThreadCurrentPriority();
        //@hle:function{3B183E26|ThreadManForUser|sceKernelGetThreadExitStatus|gg|int sceKernelGetThreadExitStatus(SceUID thid)}
        extern int  sceKernelGetThreadExitStatus(u32 $a0);
        //@hle:function{17C1684E|ThreadManForUser|sceKernelReferThreadStatus|ggg|int sceKernelReferThreadStatus(SceUID thid, SceKernelThreadInfo * info)}
        extern int  sceKernelReferThreadStatus(u32 $a0, u32 $a1);
        //@hle:function{FFC36A14|ThreadManForUser|sceKernelReferThreadRunStatus|ggg|int sceKernelReferThreadRunStatus(SceUID thid, SceKernelThreadRunStatus * status)}
        extern int  sceKernelReferThreadRunStatus(u32 $a0, u32 $a1);
        //@hle:function{D13BDE95|ThreadManForUser|sceKernelCheckThreadStack|g|int sceKernelCheckThreadStack(void)}
        extern int  sceKernelCheckThreadStack();
        //@hle:function{52089CA1|ThreadManForUser|sceKernelGetThreadStackFreeSize|gg|int sceKernelGetThreadStackFreeSize(SceUID thid)}
        extern int  sceKernelGetThreadStackFreeSize(u32 $a0);
        //@hle:function{07F3A4BC|ThreadManForUser|_sceKernelStartThread|0|void _sceKernelStartThread(void)}
        extern void _sceKernelStartThread();
        //@hle:function{532A522E|ThreadManForUser|_sceKernelExitThread|0|void _sceKernelExitThread(void)}
        extern void _sceKernelExitThread();
        //@hle:function{E0A68B8C|ThreadManForUser|_sceKernelIdleThread|0|void _sceKernelIdleThread(void)}
        extern void _sceKernelIdleThread();
        //@hle:function{0C106E53|ThreadManForUser|sceKernelRegisterThreadEventHandler|gggggg|SceUID sceKernelRegisterThreadEventHandler(const char * name, SceUID threadID, int mask, SceKernelThreadEventHandler handler, void * arg)}
        extern int  sceKernelRegisterThreadEventHandler(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{72F3C145|ThreadManForUser|sceKernelReleaseThreadEventHandler|gg|int sceKernelReleaseThreadEventHandler(SceUID uid)}
        extern int  sceKernelReleaseThreadEventHandler(u32 $a0);
        //@hle:function{369EEB6B|ThreadManForUser|sceKernelReferThreadEventHandlerStatus|ggg|int sceKernelReferThreadEventHandlerStatus(SceUID uid, struct SceKernelThreadEventHandlerInfo * info)}
        extern int  sceKernelReferThreadEventHandlerStatus(u32 $a0, u32 $a1);
        //@hle:function{9ACE131E|ThreadManForUser|sceKernelSleepThread|g|int sceKernelSleepThread(void)}
        extern int  sceKernelSleepThread();
        //@hle:function{82826F70|ThreadManForUser|sceKernelSleepThreadCB|g|int sceKernelSleepThreadCB(void)}
        extern int  sceKernelSleepThreadCB();
        //@hle:function{D59EAD2F|ThreadManForUser|sceKernelWakeupThread|gg|int sceKernelWakeupThread(SceUID thid)}
        extern int  sceKernelWakeupThread(u32 $a0);
        //@hle:function{FCCFAD26|ThreadManForUser|sceKernelCancelWakeupThread|gg|int sceKernelCancelWakeupThread(SceUID thid)}
        extern int  sceKernelCancelWakeupThread(u32 $a0);
        //@hle:function{9944F31F|ThreadManForUser|sceKernelSuspendThread|gg|int sceKernelSuspendThread(SceUID thid)}
        extern int  sceKernelSuspendThread(u32 $a0);
        //@hle:function{75156E8F|ThreadManForUser|sceKernelResumeThread|gg|int sceKernelResumeThread(SceUID thid)}
        extern int  sceKernelResumeThread(u32 $a0);
        //@hle:function{278C0DF5|ThreadManForUser|sceKernelWaitThreadEnd|ggg|int sceKernelWaitThreadEnd(SceUID thid, SceUInt * timeout)}
        extern int  sceKernelWaitThreadEnd(u32 $a0, u32 $a1);
        //@hle:function{840E8133|ThreadManForUser|sceKernelWaitThreadEndCB|ggg|int sceKernelWaitThreadEndCB(SceUID thid, SceUInt * timeout)}
        extern int  sceKernelWaitThreadEndCB(u32 $a0, u32 $a1);
        //@hle:function{D6DA4BA1|ThreadManForUser|sceKernelCreateSema|gggggg|SceUID sceKernelCreateSema(const char * name, SceUInt attr, int initVal, int maxVal, const SceKernelSemaOptParam * opt)}
        extern int  sceKernelCreateSema(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{28B6489C|ThreadManForUser|sceKernelDeleteSema|gg|int sceKernelDeleteSema(SceUID semaid)}
        extern int  sceKernelDeleteSema(u32 $a0);
        //@hle:function{3F53E640|ThreadManForUser|sceKernelSignalSema|ggg|int sceKernelSignalSema(SceUID semaid, int signal)}
        extern int  sceKernelSignalSema(u32 $a0, u32 $a1);
        //@hle:function{4E3A1105|ThreadManForUser|sceKernelWaitSema|gggg|int sceKernelWaitSema(SceUID semaid, int signal, SceUInt * timeout)}
        extern int  sceKernelWaitSema(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{6D212BAC|ThreadManForUser|sceKernelWaitSemaCB|gggg|int sceKernelWaitSemaCB(SceUID semaid, int signal, SceUInt * timeout)}
        extern int  sceKernelWaitSemaCB(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{58B1F937|ThreadManForUser|sceKernelPollSema|ggg|int sceKernelPollSema(SceUID semaid, int signal)}
        extern int  sceKernelPollSema(u32 $a0, u32 $a1);
        //@hle:function{8FFDF9A2|ThreadManForUser|sceKernelCancelSema|gggg|int sceKernelCancelSema(SceUID semid, int signal, int * numWaitThreads))}
        extern int  sceKernelCancelSema(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{BC6FEBC5|ThreadManForUser|sceKernelReferSemaStatus|ggg|int sceKernelReferSemaStatus(SceUID semaid, SceKernelSemaInfo * info)}
        extern int  sceKernelReferSemaStatus(u32 $a0, u32 $a1);
        //@hle:function{55C20A00|ThreadManForUser|sceKernelCreateEventFlag|ggggg|SceUID sceKernelCreateEventFlag(const char * name, SceUInt attr, int bits, const SceKernelEventFlagOptParam * opt)}
        extern int  sceKernelCreateEventFlag(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{EF9E4C70|ThreadManForUser|sceKernelDeleteEventFlag|gg|int sceKernelDeleteEventFlag(int evid)}
        extern int  sceKernelDeleteEventFlag(u32 $a0);
        //@hle:function{1FB15A32|ThreadManForUser|sceKernelSetEventFlag|ggg|int sceKernelSetEventFlag(SceUID evid, SceUInt bits)}
        extern int  sceKernelSetEventFlag(u32 $a0, u32 $a1);
        //@hle:function{812346E4|ThreadManForUser|sceKernelClearEventFlag|ggg|int sceKernelClearEventFlag(SceUID evid, SceUInt bits)}
        extern int  sceKernelClearEventFlag(u32 $a0, u32 $a1);
        //@hle:function{402FCF22|ThreadManForUser|sceKernelWaitEventFlag|gggggg|int sceKernelWaitEventFlag(int evid, SceUInt bits, int waitmode, SceUInt * outBits, SceUInt * timeout)}
        extern int  sceKernelWaitEventFlag(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{328C546A|ThreadManForUser|sceKernelWaitEventFlagCB|gggggg|int sceKernelWaitEventFlagCB(int evid, SceUInt bits, int waitmode, SceUInt * outBits, SceUInt * timeout)}
        extern int  sceKernelWaitEventFlagCB(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{30FD48F0|ThreadManForUser|sceKernelPollEventFlag|ggggg|int sceKernelPollEventFlag(int evid, SceUInt bits, int waitmode, SceUInt * outBits)}
        extern int  sceKernelPollEventFlag(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{CD203292|ThreadManForUser|sceKernelCancelEventFlag|gggg|int sceKernelCancelEventFlag(SceUID evid, SceUInt bits, int * numWaitThreads))}
        extern int  sceKernelCancelEventFlag(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{A66B0120|ThreadManForUser|sceKernelReferEventFlagStatus|ggg|int sceKernelReferEventFlagStatus(SceUID event, SceKernelEventFlagInfo * status)}
        extern int  sceKernelReferEventFlagStatus(u32 $a0, u32 $a1);
        //@hle:function{8125221D|ThreadManForUser|sceKernelCreateMbx|gggg|SceUID sceKernelCreateMbx(const char * name, SceUInt attr, const SceKernelMbxOptParam * opt)}
        extern int  sceKernelCreateMbx(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{86255ADA|ThreadManForUser|sceKernelDeleteMbx|gg|int sceKernelDeleteMbx(SceUID mbxid)}
        extern int  sceKernelDeleteMbx(u32 $a0);
        //@hle:function{E9B3061E|ThreadManForUser|sceKernelSendMbx|ggg|int sceKernelSendMbx(SceUID mbxid, void * message)}
        extern int  sceKernelSendMbx(u32 $a0, u32 $a1);
        //@hle:function{18260574|ThreadManForUser|sceKernelReceiveMbx|gggg|int sceKernelReceiveMbx(SceUID mbxid, void * pmessage, SceUInt * timeout)}
        extern int  sceKernelReceiveMbx(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{F3986382|ThreadManForUser|sceKernelReceiveMbxCB|gggg|int sceKernelReceiveMbxCB(SceUID mbxid, void * pmessage, SceUInt * timeout)}
        extern int  sceKernelReceiveMbxCB(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{0D81716A|ThreadManForUser|sceKernelPollMbx|ggg|int sceKernelPollMbx(SceUID mbxid, void * pmessage)}
        extern int  sceKernelPollMbx(u32 $a0, u32 $a1);
        //@hle:function{87D4DD36|ThreadManForUser|sceKernelCancelReceiveMbx|ggg|int sceKernelCancelReceiveMbx(SceUID mbxid, int * numWaitThreads)}
        extern int  sceKernelCancelReceiveMbx(u32 $a0, u32 $a1);
        //@hle:function{A8E8C846|ThreadManForUser|sceKernelReferMbxStatus|ggg|int sceKernelReferMbxStatus(SceUID mbxid, SceKernelMbxInfo * info)}
        extern int  sceKernelReferMbxStatus(u32 $a0, u32 $a1);
        //@hle:function{7C0DC2A0|ThreadManForUser|sceKernelCreateMsgPipe|gggggg|SceUID sceKernelCreateMsgPipe(const char * name, SceUID mpid, SceUInt attr, SceSize bufsize, const SceKernelMppOptParam * opt)}
        extern int  sceKernelCreateMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{F0B7DA1C|ThreadManForUser|sceKernelDeleteMsgPipe|gg|int sceKernelDeleteMsgPipe(SceUID uid)}
        extern int  sceKernelDeleteMsgPipe(u32 $a0);
        //@hle:function{876DBFAD|ThreadManForUser|sceKernelSendMsgPipe|ggggggg|int sceKernelSendMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        extern int  sceKernelSendMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{7C41F2C2|ThreadManForUser|sceKernelSendMsgPipeCB|ggggggg|int sceKernelSendMsgPipeCB(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        extern int  sceKernelSendMsgPipeCB(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{884C9F90|ThreadManForUser|sceKernelTrySendMsgPipe|gggggg|int sceKernelTrySendMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result)}
        extern int  sceKernelTrySendMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{74829B76|ThreadManForUser|sceKernelReceiveMsgPipe|ggggggg|int sceKernelReceiveMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        extern int  sceKernelReceiveMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{FBFA697D|ThreadManForUser|sceKernelReceiveMsgPipeCB|ggggggg|int sceKernelReceiveMsgPipeCB(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        extern int  sceKernelReceiveMsgPipeCB(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{DF52098F|ThreadManForUser|sceKernelTryReceiveMsgPipe|gggggg|int sceKernelTryReceiveMsgPipe(SceUID uid, void * message, unsigned int size, int waitmode, SceSize * result, SceUInt * timeout)}
        extern int  sceKernelTryReceiveMsgPipe(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{349B864D|ThreadManForUser|sceKernelCancelMsgPipe|gggg|int sceKernelCancelMsgPipe(SceUID uid, int * numSendWaitThreads, int * numRecvWaitThreads)}
        extern int  sceKernelCancelMsgPipe(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{33BE4024|ThreadManForUser|sceKernelReferMsgPipeStatus|ggg|int sceKernelReferMsgPipeStatus(SceUID uid, SceKernelMppInfo * info)}
        extern int  sceKernelReferMsgPipeStatus(u32 $a0, u32 $a1);
        //@hle:function{56C039B5|ThreadManForUser|sceKernelCreateVpl|gggggg|SceUID sceKernelCreateVpl(const char * name, SceUID mpid, SceUInt attr, unsigned int size, SceKernelVplOptParam * opt)}
        extern int  sceKernelCreateVpl(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{89B3D48C|ThreadManForUser|sceKernelDeleteVpl|gg|int sceKernelDeleteVpl(SceUID uid)}
        extern int  sceKernelDeleteVpl(u32 $a0);
        //@hle:function{BED27435|ThreadManForUser|sceKernelAllocateVpl|ggggg|int sceKernelAllocateVpl(SceUID uid, unsigned int size, void * * data, SceUInt * timeout)}
        extern int  sceKernelAllocateVpl(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{EC0A693F|ThreadManForUser|sceKernelAllocateVplCB|ggggg|int sceKernelAllocateVplCB(SceUID uid, unsigned int size, void * * data, SceUInt * timeout)}
        extern int  sceKernelAllocateVplCB(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{AF36D708|ThreadManForUser|sceKernelTryAllocateVpl|gggg|int sceKernelTryAllocateVpl(SceUID uid, unsigned int size, void * * data)}
        extern int  sceKernelTryAllocateVpl(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{B736E9FF|ThreadManForUser|sceKernelFreeVpl|ggg|int sceKernelFreeVpl(SceUID uid, void * data)}
        extern int  sceKernelFreeVpl(u32 $a0, u32 $a1);
        //@hle:function{1D371B8A|ThreadManForUser|sceKernelCancelVpl|ggg|int sceKernelCancelVpl(SceUID uid, int * numWaitThreads)}
        extern int  sceKernelCancelVpl(u32 $a0, u32 $a1);
        //@hle:function{39810265|ThreadManForUser|sceKernelReferVplStatus|ggg|int sceKernelReferVplStatus(SceUID uid, SceKernelVplInfo * info)}
        extern int  sceKernelReferVplStatus(u32 $a0, u32 $a1);
        //@hle:function{C07BB470|ThreadManForUser|sceKernelCreateFpl|ggggggg|int sceKernelCreateFpl(const char * name, SceUID mpid, SceUInt attr, unsigned int size, int blocks, SceKernelFplOptParam * opt)}
        extern int  sceKernelCreateFpl(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{ED1410E0|ThreadManForUser|sceKernelDeleteFpl|gg|int sceKernelDeleteFpl(SceUID uid)}
        extern int  sceKernelDeleteFpl(u32 $a0);
        //@hle:function{D979E9BF|ThreadManForUser|sceKernelAllocateFpl|gggg|int sceKernelAllocateFpl(SceUID uid, void * * data, SceUInt * timeout)}
        extern int  sceKernelAllocateFpl(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{E7282CB6|ThreadManForUser|sceKernelAllocateFplCB|gggg|int sceKernelAllocateFplCB(SceUID uid, void * * data, SceUInt * timeout)}
        extern int  sceKernelAllocateFplCB(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{623AE665|ThreadManForUser|sceKernelTryAllocateFpl|ggg|int sceKernelTryAllocateFpl(SceUID uid, void * * data)}
        extern int  sceKernelTryAllocateFpl(u32 $a0, u32 $a1);
        //@hle:function{F6414A71|ThreadManForUser|sceKernelFreeFpl|ggg|int sceKernelFreeFpl(SceUID uid, void * data)}
        extern int  sceKernelFreeFpl(u32 $a0, u32 $a1);
        //@hle:function{A8AA591F|ThreadManForUser|sceKernelCancelFpl|ggg|int sceKernelCancelFpl(SceUID uid, int * numWaitThreads)}
        extern int  sceKernelCancelFpl(u32 $a0, u32 $a1);
        //@hle:function{D8199E4C|ThreadManForUser|sceKernelReferFplStatus|ggg|int sceKernelReferFplStatus(SceUID uid, SceKernelFplInfo * info)}
        extern int  sceKernelReferFplStatus(u32 $a0, u32 $a1);
        //@hle:function{DB738F35|ThreadManForUser|sceKernelGetSystemTime|gg|int sceKernelGetSystemTime(SceKernelSysClock * time)}
        extern int  sceKernelGetSystemTime(u32 $a0);
        //@hle:function{82BC5777|ThreadManForUser|sceKernelGetSystemTimeWide|G|SceInt64 sceKernelGetSystemTimeWide(void)}
        extern s64  sceKernelGetSystemTimeWide();
        //@hle:function{369ED59D|ThreadManForUser|sceKernelGetSystemTimeLow|g|unsigned int sceKernelGetSystemTimeLow(void)}
        extern int  sceKernelGetSystemTimeLow();
        //@hle:function{110DEC9A|ThreadManForUser|sceKernelUSec2SysClock|ggg|int sceKernelUSec2SysClock(unsigned int usec, SceKernelSysClock * clock)}
        extern int  sceKernelUSec2SysClock(u32 $a0, u32 $a1);
        //@hle:function{BA6B92E2|ThreadManForUser|sceKernelSysClock2USec|gggg|int sceKernelSysClock2USec(const SceKernelSysClock * clock, unsigned int * low, unsigned int * high)}
        extern int  sceKernelSysClock2USec(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{C8CD158C|ThreadManForUser|sceKernelUSec2SysClockWide|Gg|SceInt64 sceKernelUSec2SysClockWide(unsigned int usec)}
        extern s64  sceKernelUSec2SysClockWide(u32 $a0);
        //@hle:function{E1619D7C|ThreadManForUser|sceKernelSysClock2USecWide|gGgg|int sceKernelSysClock2USecWide(SceInt64 clock, unsigned * low, unsigned int * high)}
        extern int  sceKernelSysClock2USecWide(u64 $a1a0, u32 $a2, u32 $a3);
        //@hle:function{CEADEB47|ThreadManForUser|sceKernelDelayThread|gg|int sceKernelDelayThread(SceUInt delay)}
        extern int  sceKernelDelayThread(u32 $a0);
        //@hle:function{68DA9E36|ThreadManForUser|sceKernelDelayThreadCB|gg|int sceKernelDelayThreadCB(SceUInt delay)}
        extern int  sceKernelDelayThreadCB(u32 $a0);
        //@hle:function{BD123D9E|ThreadManForUser|sceKernelDelaySysClockThread|gg|int sceKernelDelaySysClockThread(const SceKernelSysClock * delay)}
        extern int  sceKernelDelaySysClockThread(u32 $a0);
        //@hle:function{1181E963|ThreadManForUser|sceKernelDelaySysClockThreadCB|gg|int sceKernelDelaySysClockThreadCB(const SceKernelSysClock * delay)}
        extern int  sceKernelDelaySysClockThreadCB(u32 $a0);
        //@hle:function{6652B8CA|ThreadManForUser|sceKernelSetAlarm|gggg|SceUID sceKernelSetAlarm(SceUInt clock, SceKernelAlarmHandler handler, void * common)}
        extern int  sceKernelSetAlarm(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{B2C25152|ThreadManForUser|sceKernelSetSysClockAlarm|gggg|SceUID sceKernelSetSysClockAlarm(SceKernelSysClock * clock, SceKernelAlarmHandler handler, void * arg)}
        extern int  sceKernelSetSysClockAlarm(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{7E65B999|ThreadManForUser|sceKernelCancelAlarm|gg|int sceKernelCancelAlarm(SceUID uid)}
        extern int  sceKernelCancelAlarm(u32 $a0);
        //@hle:function{DAA3F564|ThreadManForUser|sceKernelReferAlarmStatus|ggg|int sceKernelReferAlarmStatus(SceUID uid, SceKernelAlarmInfo * info)}
        extern int  sceKernelReferAlarmStatus(u32 $a0, u32 $a1);
        //@hle:function{20FFF560|ThreadManForUser|sceKernelCreateVTimer|ggg|SceUID sceKernelCreateVTimer(const char * name, const SceKernelVTimerOptParam * opt)}
        extern int  sceKernelCreateVTimer(u32 $a0, u32 $a1);
        //@hle:function{328F9E52|ThreadManForUser|sceKernelDeleteVTimer|gg|int sceKernelDeleteVTimer(SceUID uid)}
        extern int  sceKernelDeleteVTimer(u32 $a0);
        //@hle:function{B3A59970|ThreadManForUser|sceKernelGetVTimerBase|ggg|int sceKernelGetVTimerBase(SceUID uid, SceKernelSysClock * base)}
        extern int  sceKernelGetVTimerBase(u32 $a0, u32 $a1);
        //@hle:function{034A921F|ThreadManForUser|sceKernelGetVTimerTime|ggg|int sceKernelGetVTimerTime(SceUID uid, SceKernelSysClock * time)}
        extern int  sceKernelGetVTimerTime(u32 $a0, u32 $a1);
        //@hle:function{542AD630|ThreadManForUser|sceKernelSetVTimerTime|ggg|int sceKernelSetVTimerTime(SceUID uid, SceKernelSysClock * time)}
        extern int  sceKernelSetVTimerTime(u32 $a0, u32 $a1);
        //@hle:function{C68D9437|ThreadManForUser|sceKernelStartVTimer|gg|int sceKernelStartVTimer(SceUID uid)}
        extern int  sceKernelStartVTimer(u32 $a0);
        //@hle:function{D0AEEE87|ThreadManForUser|sceKernelStopVTimer|gg|int sceKernelStopVTimer(SceUID uid)}
        extern int  sceKernelStopVTimer(u32 $a0);
        //@hle:function{D8B299AE|ThreadManForUser|sceKernelSetVTimerHandler|ggggg|int sceKernelSetVTimerHandler(SceUID uid, SceKernelSysClock * time, SceKernelVTimerHandler handler, void * arg)}
        extern int  sceKernelSetVTimerHandler(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{D2D615EF|ThreadManForUser|sceKernelCancelVTimerHandler|gg|int sceKernelCancelVTimerHandler(SceUID uid)}
        extern int  sceKernelCancelVTimerHandler(u32 $a0);
        //@hle:function{B7C18B77|ThreadManForUser|sceKernelGetVTimerBaseWide|Gg|SceInt64 sceKernelGetVTimerBaseWide(SceUID uid)}
        extern s64  sceKernelGetVTimerBaseWide(u32 $a0);
        //@hle:function{C0B3FFD2|ThreadManForUser|sceKernelGetVTimerTimeWide|Gg|SceInt64 sceKernelGetVTimerTimeWide(SceUID uid)}
        extern s64  sceKernelGetVTimerTimeWide(u32 $a0);
        //@hle:function{FB6425C3|ThreadManForUser|sceKernelSetVTimerTimeWide|GgG|SceInt64 sceKernelSetVTimerTimeWide(SceUID uid, SceInt64 time)}
        extern s64  sceKernelSetVTimerTimeWide(u32 $a0, u64 $a3a2);
        //@hle:function{53B00E9A|ThreadManForUser|sceKernelSetVTimerHandlerWide|ggGgg|int sceKernelSetVTimerHandlerWide(SceUID uid, SceInt64 time, SceKernelVTimerHandlerWide handler, void * arg)}
        extern int  sceKernelSetVTimerHandlerWide(u32 $a0, u64 $a3a2, u32 $a4, u32 $a5);
        //@hle:function{5F32BEAA|ThreadManForUser|sceKernelReferVTimerStatus|ggg|int sceKernelReferVTimerStatus(SceUID uid, SceKernelVTimerInfo * info)}
        extern int  sceKernelReferVTimerStatus(u32 $a0, u32 $a1);
        //@hle:function{0E927AED|ThreadManForUser|_sceKernelReturnFromTimerHandler|0|void _sceKernelReturnFromTimerHandler(void)}
        extern void _sceKernelReturnFromTimerHandler();
        //@hle:function{E81CAF8F|ThreadManForUser|sceKernelCreateCallback|gggg|int sceKernelCreateCallback(const char * name, SceKernelCallbackFunction func, void * arg)}
        extern int  sceKernelCreateCallback(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{EDBA5844|ThreadManForUser|sceKernelDeleteCallback|gg|int sceKernelDeleteCallback(SceUID cbid)}
        extern int  sceKernelDeleteCallback(u32 $a0);
        //@hle:function{C11BA8C4|ThreadManForUser|sceKernelNotifyCallback|ggg|int sceKernelNotifyCallback(SceUID cbid, int arg)}
        extern int  sceKernelNotifyCallback(u32 $a0, u32 $a1);
        //@hle:function{BA4051D6|ThreadManForUser|sceKernelCancelCallback|gg|int sceKernelCancelCallback(SceUID cbid)}
        extern int  sceKernelCancelCallback(u32 $a0);
        //@hle:function{2A3D44FF|ThreadManForUser|sceKernelGetCallbackCount|gg|int sceKernelGetCallbackCount(SceUID cbid)}
        extern int  sceKernelGetCallbackCount(u32 $a0);
        //@hle:function{349D6D6C|ThreadManForUser|sceKernelCheckCallback|g|int sceKernelCheckCallback(void)}
        extern int  sceKernelCheckCallback();
        //@hle:function{730ED8BC|ThreadManForUser|sceKernelReferCallbackStatus|ggg|int sceKernelReferCallbackStatus(SceUID cb, SceKernelCallbackInfo * status)}
        extern int  sceKernelReferCallbackStatus(u32 $a0, u32 $a1);
        //@hle:function{6E9EA350|ThreadManForUser|_sceKernelReturnFromCallback|0|void _sceKernelReturnFromCallback(void)}
        extern void _sceKernelReturnFromCallback();
        //@hle:function{627E6F3A|ThreadManForUser|sceKernelReferSystemStatus|gg|int sceKernelReferSystemStatus(SceKernelSystemStatus * status)}
        extern int  sceKernelReferSystemStatus(u32 $a0);
        //@hle:function{94416130|ThreadManForUser|sceKernelGetThreadmanIdList|ggggg|int sceKernelGetThreadmanIdList(enum SceKernelIdListType type, SceUID * readbuf, int readbufsize, int * idcount)}
        extern int  sceKernelGetThreadmanIdList(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{57CF62DD|ThreadManForUser|sceKernelGetThreadmanIdType|gg|enum sceKernelGetThreadmanIdType(SceUID uid)}
        extern int  sceKernelGetThreadmanIdType(u32 $a0);
        //@hle:function{B7D098C6|ThreadManForUser|sceKernelCreateMutex|g|??? sceKernelCreateMutex()}
        extern int  sceKernelCreateMutex();
        //@hle:function{F8170FBE|ThreadManForUser|sceKernelDeleteMutex|g|??? sceKernelDeleteMutex()}
        extern int  sceKernelDeleteMutex();
        //@hle:function{B011B11F|ThreadManForUser|sceKernelLockMutex|g|??? sceKernelLockMutex()}
        extern int  sceKernelLockMutex();
        //@hle:function{5BF4DD27|ThreadManForUser|sceKernelLockMutexCB|g|??? sceKernelLockMutexCB()}
        extern int  sceKernelLockMutexCB();
        //@hle:function{0DDCD2C9|ThreadManForUser|sceKernelTryLockMutex|g|??? sceKernelTryLockMutex()}
        extern int  sceKernelTryLockMutex();
        //@hle:function{6B30100F|ThreadManForUser|sceKernelUnlockMutex|g|??? sceKernelUnlockMutex()}
        extern int  sceKernelUnlockMutex();
        //@hle:function{87D9223C|ThreadManForUser|sceKernelCancelMutex|g|??? sceKernelCancelMutex()}
        extern int  sceKernelCancelMutex();
        //@hle:function{A9C2CB9A|ThreadManForUser|sceKernelReferMutexStatus|g|??? sceKernelReferMutexStatus()}
        extern int  sceKernelReferMutexStatus();
        //@hle:function{19CFF145|ThreadManForUser|sceKernelCreateLwMutex|g|??? sceKernelCreateLwMutex()}
        extern int  sceKernelCreateLwMutex();
        //@hle:function{60107536|ThreadManForUser|sceKernelDeleteLwMutex|g|??? sceKernelDeleteLwMutex()}
        extern int  sceKernelDeleteLwMutex();
        //@hle:function{4C145944|ThreadManForUser|sceKernelReferLwMutexStatusByID|g|??? sceKernelReferLwMutexStatusByID()}
        extern int  sceKernelReferLwMutexStatusByID();
        //@hle:function{64D4540E|ThreadManForUser|sceKernelReferThreadProfiler|g|SceProfilerRegs * sceKernelReferThreadProfiler(void)}
        extern int  sceKernelReferThreadProfiler();
        //@hle:function{8218B4DD|ThreadManForUser|sceKernelReferGlobalProfiler|g|SceProfilerRegs * sceKernelReferGlobalProfiler(void)}
        extern int  sceKernelReferGlobalProfiler();
        //@hle:function{1AF94D03|ThreadManForUser|sceKernelDonateWakeupThread|g|??? sceKernelDonateWakeupThread()}
        extern int  sceKernelDonateWakeupThread();
        //@hle:function{31327F19|ThreadManForUser|ThreadManForUser_31327F19|g|??? ThreadManForUser_31327F19()}
        extern int  ThreadManForUser_31327F19();
        //@hle:function{71040D5C|ThreadManForUser|ThreadManForUser_71040D5C|g|??? ThreadManForUser_71040D5C()}
        extern int  ThreadManForUser_71040D5C();
        //@hle:function{7CFF8CF3|ThreadManForUser|ThreadManForUser_7CFF8CF3|g|??? ThreadManForUser_7CFF8CF3()}
        extern int  ThreadManForUser_7CFF8CF3();
        //@hle:function{8672E3D0|ThreadManForUser|ThreadManForUser_8672E3D0|g|??? ThreadManForUser_8672E3D0()}
        extern int  ThreadManForUser_8672E3D0();
        //@hle:function{BEED3A47|ThreadManForUser|ThreadManForUser_BEED3A47|g|??? ThreadManForUser_BEED3A47()}
        extern int  ThreadManForUser_BEED3A47();
    } //@hle:library-end{ThreadManForUser|sceThreadManager|threadman.prx}
}
#endif