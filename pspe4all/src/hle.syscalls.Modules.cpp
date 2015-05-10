////////////////////////////////////////////////////////////////////////////////
/// This file is auto-generated from pspe4all-nidgen version 0.3
///
#include "hle.syscalls.Modules.h"
#include "lle.mmu.h"

namespace hle
{
    namespace syscalls
    {
        ///////////////// Module : sceSystemMemoryManager (sysmem.prx) /////////////////
        ///
        /// ////////////////////////// Library : SysMemUserForUser /////////////////////////
        /// ///
        hle::Function functions_SysMemUserForUser[] =
        {
            HLE_FUNCTION(SysMemUserForUser, A291F107, sceKernelMaxFreeMemSize, ""),
            HLE_FUNCTION(SysMemUserForUser, F919F628, sceKernelTotalFreeMemSize, ""),
            HLE_FUNCTION(SysMemUserForUser, 13A5ABEF, sceKernelPrintf, ""),
            HLE_FUNCTION(SysMemUserForUser, F77D77CB, sceKernelSetCompilerVersion, "$a0:x"),
            HLE_FUNCTION(SysMemUserForUser, 7591C7DB, sceKernelSetCompiledSdkVersion, "$a0:x"),
            HLE_FUNCTION(SysMemUserForUser, 3FC9AE6A, sceKernelDevkitVersion, ""),
            HLE_FUNCTION(SysMemUserForUser, FC114573, sceKernelGetCompiledSdkVersion, ""),
            HLE_FUNCTION(SysMemUserForUser, 237DBD4F, sceKernelAllocPartitionMemory, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(SysMemUserForUser, B6D61D02, sceKernelFreePartitionMemory, "$a0:x"),
            HLE_FUNCTION(SysMemUserForUser, 9D9A5BA1, sceKernelGetBlockHeadAddr, "$a0:x"),
            HLE_FUNCTION(SysMemUserForUser, 2A3E5280, sceKernelQueryMemoryInfo, ""),
            HLE_FUNCTION(SysMemUserForUser, 057E7380, SysMemUserForUser_057E7380, ""),
            HLE_FUNCTION(SysMemUserForUser, 315AD3A0, SysMemUserForUser_315AD3A0, ""),
            HLE_FUNCTION(SysMemUserForUser, 342061E5, SysMemUserForUser_342061E5, ""),
            HLE_FUNCTION(SysMemUserForUser, 50F61D8A, SysMemUserForUser_50F61D8A, ""),
            HLE_FUNCTION(SysMemUserForUser, 91DE343C, SysMemUserForUser_91DE343C, ""),
            HLE_FUNCTION(SysMemUserForUser, A6848DF8, SysMemUserForUser_A6848DF8, ""),
            HLE_FUNCTION(SysMemUserForUser, ACBD88CA, SysMemUserForUser_ACBD88CA, ""),
            HLE_FUNCTION(SysMemUserForUser, D8DE5C1E, SysMemUserForUser_D8DE5C1E, ""),
            HLE_FUNCTION(SysMemUserForUser, DB83A952, SysMemUserForUser_DB83A952, ""),
            HLE_FUNCTION(SysMemUserForUser, EBD5C3E6, SysMemUserForUser_EBD5C3E6, ""),
            HLE_FUNCTION(SysMemUserForUser, FE707FDF, SysMemUserForUser_FE707FDF, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// ////////////////////////// Library : sceSuspendForUser /////////////////////////
        /// ///
        hle::Function functions_sceSuspendForUser[] =
        {
            HLE_FUNCTION(sceSuspendForUser, EADB1BD7, sceKernelPowerLock, "$a0:x"),
            HLE_FUNCTION(sceSuspendForUser, 3AEE7261, sceKernelPowerUnlock, "$a0:x"),
            HLE_FUNCTION(sceSuspendForUser, 090CCB3F, sceKernelPowerTick, "$a0:x"),
            HLE_FUNCTION(sceSuspendForUser, 3E0271D3, sceKernelVolatileMemLock, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSuspendForUser, A14F40B2, sceKernelVolatileMemTryLock, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSuspendForUser, A569E425, sceKernelVolatileMemUnlock, "$a0:x")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// //////////////////////////// Library : UtilsForUser ////////////////////////////
        /// ///
        hle::Function functions_UtilsForUser[] =
        {
            HLE_FUNCTION(UtilsForUser, 79D1C3FA, sceKernelDcacheWritebackAll, ""),
            HLE_FUNCTION(UtilsForUser, B435DEC5, sceKernelDcacheWritebackInvalidateAll, ""),
            HLE_FUNCTION(UtilsForUser, 3EE30821, sceKernelDcacheWritebackRange, "$a0:x$a1:x"),
            HLE_FUNCTION(UtilsForUser, 34B9FA9E, sceKernelDcacheWritebackInvalidateRange, "$a0:x$a1:x"),
            HLE_FUNCTION(UtilsForUser, BFA98062, sceKernelDcacheInvalidateRange, "$a0:x$a1:x"),
            HLE_FUNCTION(UtilsForUser, 80001C4C, sceKernelDcacheProbe, "$a0:x"),
            HLE_FUNCTION(UtilsForUser, 77DFF087, sceKernelDcacheProbeRange, "$a0:x$a1:x"),
            HLE_FUNCTION(UtilsForUser, 16641D70, sceKernelDcacheReadTag, ""),
            HLE_FUNCTION(UtilsForUser, 920F104A, sceKernelIcacheInvalidateAll, ""),
            HLE_FUNCTION(UtilsForUser, C2DF770E, sceKernelIcacheInvalidateRange, "$a0:x$a1:x"),
            HLE_FUNCTION(UtilsForUser, 4FD31C9D, sceKernelIcacheProbe, "$a0:x"),
            HLE_FUNCTION(UtilsForUser, FB05FAD0, sceKernelIcacheReadTag, ""),
            HLE_FUNCTION(UtilsForUser, C8186A58, sceKernelUtilsMd5Digest, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(UtilsForUser, 9E5C5086, sceKernelUtilsMd5BlockInit, "$a0:x"),
            HLE_FUNCTION(UtilsForUser, 61E1E525, sceKernelUtilsMd5BlockUpdate, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(UtilsForUser, B8D24E78, sceKernelUtilsMd5BlockResult, "$a0:x$a1:x"),
            HLE_FUNCTION(UtilsForUser, 840259F1, sceKernelUtilsSha1Digest, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(UtilsForUser, F8FCD5BA, sceKernelUtilsSha1BlockInit, "$a0:x"),
            HLE_FUNCTION(UtilsForUser, 346F6DA8, sceKernelUtilsSha1BlockUpdate, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(UtilsForUser, 585F1C09, sceKernelUtilsSha1BlockResult, "$a0:x$a1:x"),
            HLE_FUNCTION(UtilsForUser, E860E75E, sceKernelUtilsMt19937Init, "$a0:x$a1:x"),
            HLE_FUNCTION(UtilsForUser, 06FB8A63, sceKernelUtilsMt19937UInt, "$a0:x"),
            HLE_FUNCTION(UtilsForUser, 37FB5C42, sceKernelGetGPI, ""),
            HLE_FUNCTION(UtilsForUser, 6AD345D7, sceKernelSetGPO, "$a0:x"),
            HLE_FUNCTION(UtilsForUser, 91E4F6A7, sceKernelLibcClock, ""),
            HLE_FUNCTION(UtilsForUser, 27CC57F0, sceKernelLibcTime, "$a0:x"),
            HLE_FUNCTION(UtilsForUser, 71EC4271, sceKernelLibcGettimeofday, "$a0:x$a1:x"),
            HLE_FUNCTION(UtilsForUser, 87E81561, sceKernelPutUserLog, ""),
            HLE_FUNCTION(UtilsForUser, 004D4DEE, UtilsForUser_004D4DEE, ""),
            HLE_FUNCTION(UtilsForUser, 157A383A, UtilsForUser_157A383A, ""),
            HLE_FUNCTION(UtilsForUser, 1B0592A3, UtilsForUser_1B0592A3, ""),
            HLE_FUNCTION(UtilsForUser, 39F49610, UtilsForUser_39F49610, ""),
            HLE_FUNCTION(UtilsForUser, 3FD3D324, UtilsForUser_3FD3D324, ""),
            HLE_FUNCTION(UtilsForUser, 43C9A8DB, UtilsForUser_43C9A8DB, ""),
            HLE_FUNCTION(UtilsForUser, 515B4FAF, UtilsForUser_515B4FAF, ""),
            HLE_FUNCTION(UtilsForUser, 5C7F2B1A, UtilsForUser_5C7F2B1A, ""),
            HLE_FUNCTION(UtilsForUser, 6231A71D, UtilsForUser_6231A71D, ""),
            HLE_FUNCTION(UtilsForUser, 7333E539, UtilsForUser_7333E539, ""),
            HLE_FUNCTION(UtilsForUser, 740DF7F0, UtilsForUser_740DF7F0, ""),
            HLE_FUNCTION(UtilsForUser, 99134C3F, UtilsForUser_99134C3F, ""),
            HLE_FUNCTION(UtilsForUser, AF3766BB, UtilsForUser_AF3766BB, ""),
            HLE_FUNCTION(UtilsForUser, B83A1E76, UtilsForUser_B83A1E76, ""),
            HLE_FUNCTION(UtilsForUser, DBBE9A46, UtilsForUser_DBBE9A46, ""),
            HLE_FUNCTION(UtilsForUser, F0155BCA, UtilsForUser_F0155BCA, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceSystemMemoryManager[] =
        {
            HLE_LIBRARY(SysMemUserForUser),
            HLE_LIBRARY(sceSuspendForUser),
            HLE_LIBRARY(UtilsForUser)
        };
        static hle::Module module_sceSystemMemoryManager = HLE_MODULE(sceSystemMemoryManager);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        //////////////// Module : sceInterruptManager (interruptman.prx) ///////////////
        ///
        /// ////////////////////////// Library : InterruptManager //////////////////////////
        /// ///
        hle::Function functions_InterruptManager[] =
        {
            HLE_FUNCTION(InterruptManager, CA04A2B9, sceKernelRegisterSubIntrHandler, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(InterruptManager, D61E6961, sceKernelReleaseSubIntrHandler, "$a0:x$a1:x"),
            HLE_FUNCTION(InterruptManager, EEE43F47, sceKernelRegisterUserSpaceIntrStack, ""),
            HLE_FUNCTION(InterruptManager, FB8E22EC, sceKernelEnableSubIntr, "$a0:x$a1:x"),
            HLE_FUNCTION(InterruptManager, 8A389411, sceKernelDisableSubIntr, "$a0:x$a1:x"),
            HLE_FUNCTION(InterruptManager, 5CB5A78B, sceKernelSuspendSubIntr, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(InterruptManager, 7860E0DC, sceKernelResumeSubIntr, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(InterruptManager, FC4374B8, sceKernelIsSubInterruptOccurred, "$a0:x$a1:x"),
            HLE_FUNCTION(InterruptManager, D2E8363F, QueryIntrHandlerInfo, "$a0:x$a1:x$a2:x")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceInterruptManager[] =
        {
            HLE_LIBRARY(InterruptManager)
        };
        static hle::Module module_sceInterruptManager = HLE_MODULE(sceInterruptManager);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        /////////////////// Module : sceThreadManager (threadman.prx) //////////////////
        ///
        /// ////////////////////////// Library : ThreadManForUser //////////////////////////
        /// ///
        hle::Function functions_ThreadManForUser[] =
        {
            HLE_FUNCTION(ThreadManForUser, 446D8DE6, sceKernelCreateThread, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(ThreadManForUser, 9FA03CD3, sceKernelDeleteThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, F475845D, sceKernelStartThread, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, AA73C935, sceKernelExitThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 809CE29B, sceKernelExitDeleteThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 616403BA, sceKernelTerminateThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 383F7BCC, sceKernelTerminateDeleteThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 3AD58B8C, sceKernelSuspendDispatchThread, ""),
            HLE_FUNCTION(ThreadManForUser, 27E22EC2, sceKernelResumeDispatchThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, EA748E31, sceKernelChangeCurrentThreadAttr, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 71BC9871, sceKernelChangeThreadPriority, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 912354A7, sceKernelRotateThreadReadyQueue, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 2C34E053, sceKernelReleaseWaitThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 293B45B8, sceKernelGetThreadId, ""),
            HLE_FUNCTION(ThreadManForUser, 94AA61EE, sceKernelGetThreadCurrentPriority, ""),
            HLE_FUNCTION(ThreadManForUser, 3B183E26, sceKernelGetThreadExitStatus, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 17C1684E, sceKernelReferThreadStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, FFC36A14, sceKernelReferThreadRunStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, D13BDE95, sceKernelCheckThreadStack, ""),
            HLE_FUNCTION(ThreadManForUser, 52089CA1, sceKernelGetThreadStackFreeSize, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 07F3A4BC, _sceKernelStartThread, ""),
            HLE_FUNCTION(ThreadManForUser, 532A522E, _sceKernelExitThread, ""),
            HLE_FUNCTION(ThreadManForUser, E0A68B8C, _sceKernelIdleThread, ""),
            HLE_FUNCTION(ThreadManForUser, 0C106E53, sceKernelRegisterThreadEventHandler, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ThreadManForUser, 72F3C145, sceKernelReleaseThreadEventHandler, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 369EEB6B, sceKernelReferThreadEventHandlerStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 9ACE131E, sceKernelSleepThread, ""),
            HLE_FUNCTION(ThreadManForUser, 82826F70, sceKernelSleepThreadCB, ""),
            HLE_FUNCTION(ThreadManForUser, D59EAD2F, sceKernelWakeupThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, FCCFAD26, sceKernelCancelWakeupThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 9944F31F, sceKernelSuspendThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 75156E8F, sceKernelResumeThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 278C0DF5, sceKernelWaitThreadEnd, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 840E8133, sceKernelWaitThreadEndCB, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, D6DA4BA1, sceKernelCreateSema, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ThreadManForUser, 28B6489C, sceKernelDeleteSema, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 3F53E640, sceKernelSignalSema, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 4E3A1105, sceKernelWaitSema, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, 6D212BAC, sceKernelWaitSemaCB, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, 58B1F937, sceKernelPollSema, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 8FFDF9A2, sceKernelCancelSema, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, BC6FEBC5, sceKernelReferSemaStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 55C20A00, sceKernelCreateEventFlag, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(ThreadManForUser, EF9E4C70, sceKernelDeleteEventFlag, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 1FB15A32, sceKernelSetEventFlag, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 812346E4, sceKernelClearEventFlag, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 402FCF22, sceKernelWaitEventFlag, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ThreadManForUser, 328C546A, sceKernelWaitEventFlagCB, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ThreadManForUser, 30FD48F0, sceKernelPollEventFlag, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(ThreadManForUser, CD203292, sceKernelCancelEventFlag, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, A66B0120, sceKernelReferEventFlagStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 8125221D, sceKernelCreateMbx, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, 86255ADA, sceKernelDeleteMbx, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, E9B3061E, sceKernelSendMbx, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 18260574, sceKernelReceiveMbx, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, F3986382, sceKernelReceiveMbxCB, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, 0D81716A, sceKernelPollMbx, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 87D4DD36, sceKernelCancelReceiveMbx, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, A8E8C846, sceKernelReferMbxStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 7C0DC2A0, sceKernelCreateMsgPipe, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ThreadManForUser, F0B7DA1C, sceKernelDeleteMsgPipe, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 876DBFAD, sceKernelSendMsgPipe, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(ThreadManForUser, 7C41F2C2, sceKernelSendMsgPipeCB, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(ThreadManForUser, 884C9F90, sceKernelTrySendMsgPipe, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ThreadManForUser, 74829B76, sceKernelReceiveMsgPipe, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(ThreadManForUser, FBFA697D, sceKernelReceiveMsgPipeCB, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(ThreadManForUser, DF52098F, sceKernelTryReceiveMsgPipe, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ThreadManForUser, 349B864D, sceKernelCancelMsgPipe, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, 33BE4024, sceKernelReferMsgPipeStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 56C039B5, sceKernelCreateVpl, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ThreadManForUser, 89B3D48C, sceKernelDeleteVpl, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, BED27435, sceKernelAllocateVpl, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(ThreadManForUser, EC0A693F, sceKernelAllocateVplCB, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(ThreadManForUser, AF36D708, sceKernelTryAllocateVpl, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, B736E9FF, sceKernelFreeVpl, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 1D371B8A, sceKernelCancelVpl, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 39810265, sceKernelReferVplStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, C07BB470, sceKernelCreateFpl, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(ThreadManForUser, ED1410E0, sceKernelDeleteFpl, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, D979E9BF, sceKernelAllocateFpl, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, E7282CB6, sceKernelAllocateFplCB, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, 623AE665, sceKernelTryAllocateFpl, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, F6414A71, sceKernelFreeFpl, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, A8AA591F, sceKernelCancelFpl, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, D8199E4C, sceKernelReferFplStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, DB738F35, sceKernelGetSystemTime, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 82BC5777, sceKernelGetSystemTimeWide, ""),
            HLE_FUNCTION(ThreadManForUser, 369ED59D, sceKernelGetSystemTimeLow, ""),
            HLE_FUNCTION(ThreadManForUser, 110DEC9A, sceKernelUSec2SysClock, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, BA6B92E2, sceKernelSysClock2USec, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, C8CD158C, sceKernelUSec2SysClockWide, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, E1619D7C, sceKernelSysClock2USecWide, "$a1a0:8x$a2:x$a3:x"),
            HLE_FUNCTION(ThreadManForUser, CEADEB47, sceKernelDelayThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 68DA9E36, sceKernelDelayThreadCB, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, BD123D9E, sceKernelDelaySysClockThread, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 1181E963, sceKernelDelaySysClockThreadCB, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 6652B8CA, sceKernelSetAlarm, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, B2C25152, sceKernelSetSysClockAlarm, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, 7E65B999, sceKernelCancelAlarm, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, DAA3F564, sceKernelReferAlarmStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 20FFF560, sceKernelCreateVTimer, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 328F9E52, sceKernelDeleteVTimer, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, B3A59970, sceKernelGetVTimerBase, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 034A921F, sceKernelGetVTimerTime, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 542AD630, sceKernelSetVTimerTime, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, C68D9437, sceKernelStartVTimer, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, D0AEEE87, sceKernelStopVTimer, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, D8B299AE, sceKernelSetVTimerHandler, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(ThreadManForUser, D2D615EF, sceKernelCancelVTimerHandler, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, B7C18B77, sceKernelGetVTimerBaseWide, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, C0B3FFD2, sceKernelGetVTimerTimeWide, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, FB6425C3, sceKernelSetVTimerTimeWide, "$a0:x$a3a2:8x"),
            HLE_FUNCTION(ThreadManForUser, 53B00E9A, sceKernelSetVTimerHandlerWide, "$a0:x$a3a2:8x$a4:x$a5:x"),
            HLE_FUNCTION(ThreadManForUser, 5F32BEAA, sceKernelReferVTimerStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 0E927AED, _sceKernelReturnFromTimerHandler, ""),
            HLE_FUNCTION(ThreadManForUser, E81CAF8F, sceKernelCreateCallback, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ThreadManForUser, EDBA5844, sceKernelDeleteCallback, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, C11BA8C4, sceKernelNotifyCallback, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, BA4051D6, sceKernelCancelCallback, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 2A3D44FF, sceKernelGetCallbackCount, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 349D6D6C, sceKernelCheckCallback, ""),
            HLE_FUNCTION(ThreadManForUser, 730ED8BC, sceKernelReferCallbackStatus, "$a0:x$a1:x"),
            HLE_FUNCTION(ThreadManForUser, 6E9EA350, _sceKernelReturnFromCallback, ""),
            HLE_FUNCTION(ThreadManForUser, 627E6F3A, sceKernelReferSystemStatus, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, 94416130, sceKernelGetThreadmanIdList, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(ThreadManForUser, 57CF62DD, sceKernelGetThreadmanIdType, "$a0:x"),
            HLE_FUNCTION(ThreadManForUser, B7D098C6, sceKernelCreateMutex, ""),
            HLE_FUNCTION(ThreadManForUser, F8170FBE, sceKernelDeleteMutex, ""),
            HLE_FUNCTION(ThreadManForUser, B011B11F, sceKernelLockMutex, ""),
            HLE_FUNCTION(ThreadManForUser, 5BF4DD27, sceKernelLockMutexCB, ""),
            HLE_FUNCTION(ThreadManForUser, 0DDCD2C9, sceKernelTryLockMutex, ""),
            HLE_FUNCTION(ThreadManForUser, 6B30100F, sceKernelUnlockMutex, ""),
            HLE_FUNCTION(ThreadManForUser, 87D9223C, sceKernelCancelMutex, ""),
            HLE_FUNCTION(ThreadManForUser, A9C2CB9A, sceKernelReferMutexStatus, ""),
            HLE_FUNCTION(ThreadManForUser, 19CFF145, sceKernelCreateLwMutex, ""),
            HLE_FUNCTION(ThreadManForUser, 60107536, sceKernelDeleteLwMutex, ""),
            HLE_FUNCTION(ThreadManForUser, 4C145944, sceKernelReferLwMutexStatusByID, ""),
            HLE_FUNCTION(ThreadManForUser, 64D4540E, sceKernelReferThreadProfiler, ""),
            HLE_FUNCTION(ThreadManForUser, 8218B4DD, sceKernelReferGlobalProfiler, ""),
            HLE_FUNCTION(ThreadManForUser, 1AF94D03, sceKernelDonateWakeupThread, ""),
            HLE_FUNCTION(ThreadManForUser, 31327F19, ThreadManForUser_31327F19, ""),
            HLE_FUNCTION(ThreadManForUser, 71040D5C, ThreadManForUser_71040D5C, ""),
            HLE_FUNCTION(ThreadManForUser, 7CFF8CF3, ThreadManForUser_7CFF8CF3, ""),
            HLE_FUNCTION(ThreadManForUser, 8672E3D0, ThreadManForUser_8672E3D0, ""),
            HLE_FUNCTION(ThreadManForUser, BEED3A47, ThreadManForUser_BEED3A47, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceThreadManager[] =
        {
            HLE_LIBRARY(ThreadManForUser)
        };
        static hle::Module module_sceThreadManager = HLE_MODULE(sceThreadManager);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        /////////////////// Module : sceIOFileManager (iofilemgr.prx) //////////////////
        ///
        /// //////////////////////////// Library : StdioForUser ////////////////////////////
        /// ///
        hle::Function functions_StdioForUser[] =
        {
            HLE_FUNCTION(StdioForUser, A6BAB2E9, sceKernelStdout, ""),
            HLE_FUNCTION(StdioForUser, F78BA90A, sceKernelStderr, ""),
            HLE_FUNCTION(StdioForUser, 172D316E, sceKernelStdin, ""),
            HLE_FUNCTION(StdioForUser, 924ABA61, sceKernelStdioOpen, ""),
            HLE_FUNCTION(StdioForUser, 9D061C19, sceKernelStdioClose, ""),
            HLE_FUNCTION(StdioForUser, 0CBB0571, sceKernelStdioLseek, ""),
            HLE_FUNCTION(StdioForUser, 3054D478, sceKernelStdioRead, ""),
            HLE_FUNCTION(StdioForUser, A3B931DB, sceKernelStdioWrite, ""),
            HLE_FUNCTION(StdioForUser, A46785C9, sceKernelStdioSendChar, ""),
            HLE_FUNCTION(StdioForUser, 432D8F5C, sceKernelRegisterStdoutPipe, ""),
            HLE_FUNCTION(StdioForUser, 6F797E03, sceKernelRegisterStderrPipe, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// ////////////////////////// Library : IoFileMgrForUser //////////////////////////
        /// ///
        hle::Function functions_IoFileMgrForUser[] =
        {
            HLE_FUNCTION(IoFileMgrForUser, B8A740F4, sceIoChstat, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, ACE946E8, sceIoGetstat, "$a0:x$a1:x"),
            HLE_FUNCTION(IoFileMgrForUser, CB05F8D6, sceIoGetAsyncStat, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, B29DDF9C, sceIoDopen, "$a0:x"),
            HLE_FUNCTION(IoFileMgrForUser, EB092469, sceIoDclose, "$a0:x"),
            HLE_FUNCTION(IoFileMgrForUser, E3EB004C, sceIoDread, "$a0:x$a1:x"),
            HLE_FUNCTION(IoFileMgrForUser, 06A70004, sceIoMkdir, "$a0:x$a1:x"),
            HLE_FUNCTION(IoFileMgrForUser, 1117C65F, sceIoRmdir, "$a0:x"),
            HLE_FUNCTION(IoFileMgrForUser, 55F4717D, sceIoChdir, "$a0:x"),
            HLE_FUNCTION(IoFileMgrForUser, 779103A0, sceIoRename, "$a0:x$a1:x"),
            HLE_FUNCTION(IoFileMgrForUser, F27A9C51, sceIoRemove, "$a0:x"),
            HLE_FUNCTION(IoFileMgrForUser, 54F5FB11, sceIoDevctl, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(IoFileMgrForUser, AB96437F, sceIoSync, "$a0:x$a1:x"),
            HLE_FUNCTION(IoFileMgrForUser, 08BD7374, sceIoGetDevType, "$a0:x"),
            HLE_FUNCTION(IoFileMgrForUser, 109F50BC, sceIoOpen, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, 810C4BC3, sceIoClose, "$a0:x"),
            HLE_FUNCTION(IoFileMgrForUser, 63632449, sceIoIoctl, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(IoFileMgrForUser, 27EB27B8, sceIoLseek, "$a0:x$a3a2:8x$a4:x"),
            HLE_FUNCTION(IoFileMgrForUser, 68963324, sceIoLseek32, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, 6A638D83, sceIoRead, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, 42EC03AC, sceIoWrite, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, 3251EA56, sceIoPollAsync, "$a0:x$a1:x"),
            HLE_FUNCTION(IoFileMgrForUser, E23EEC33, sceIoWaitAsync, "$a0:x$a1:x"),
            HLE_FUNCTION(IoFileMgrForUser, 35DBD746, sceIoWaitAsyncCB, "$a0:x$a1:x"),
            HLE_FUNCTION(IoFileMgrForUser, A12A0514, sceIoSetAsyncCallback, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, 89AA9906, sceIoOpenAsync, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, FF5940B6, sceIoCloseAsync, "$a0:x"),
            HLE_FUNCTION(IoFileMgrForUser, E95A012B, sceIoIoctlAsync, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(IoFileMgrForUser, 71B19E77, sceIoLseekAsync, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, 1B385D8F, sceIoLseek32Async, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, A0B5A7C2, sceIoReadAsync, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, 0FACAB19, sceIoWriteAsync, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, B293727F, sceIoChangeAsyncPriority, "$a0:x$a1:x"),
            HLE_FUNCTION(IoFileMgrForUser, E8BC6571, sceIoCancel, "$a0:x"),
            HLE_FUNCTION(IoFileMgrForUser, 5C2BE2CC, sceIoGetFdList, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(IoFileMgrForUser, B2A628C1, sceIoAssign, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(IoFileMgrForUser, 6D08A871, sceIoUnassign, "$a0:x")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceIOFileManager[] =
        {
            HLE_LIBRARY(StdioForUser),
            HLE_LIBRARY(IoFileMgrForUser)
        };
        static hle::Module module_sceIOFileManager = HLE_MODULE(sceIOFileManager);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        /////////////////// Module : sceModuleManager (modulemgr.prx) //////////////////
        ///
        /// ////////////////////////// Library : ModuleMgrForUser //////////////////////////
        /// ///
        hle::Function functions_ModuleMgrForUser[] =
        {
            HLE_FUNCTION(ModuleMgrForUser, 977DE386, sceKernelLoadModule, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ModuleMgrForUser, 710F61B5, sceKernelLoadModuleMs, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ModuleMgrForUser, F9275D98, sceKernelLoadModuleBufferUsbWlan, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(ModuleMgrForUser, B7F46618, sceKernelLoadModuleByID, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ModuleMgrForUser, 50F0C1EC, sceKernelStartModule, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ModuleMgrForUser, D1FF982A, sceKernelStopModule, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(ModuleMgrForUser, 2E0911AA, sceKernelUnloadModule, "$a0:x"),
            HLE_FUNCTION(ModuleMgrForUser, D675EBB8, sceKernelSelfStopUnloadModule, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ModuleMgrForUser, CC1D3699, sceKernelStopUnloadSelfModule, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(ModuleMgrForUser, 748CBED9, sceKernelQueryModuleInfo, "$a0:x$a1:x"),
            HLE_FUNCTION(ModuleMgrForUser, F0A26395, sceKernelGetModuleId, ""),
            HLE_FUNCTION(ModuleMgrForUser, D8B73127, sceKernelGetModuleIdByAddress, "$a0:x"),
            HLE_FUNCTION(ModuleMgrForUser, D2FBC957, sceKernelGetModuleGPByAddress, "$a0:x"),
            HLE_FUNCTION(ModuleMgrForUser, 644395E2, sceKernelGetModuleIdList, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(ModuleMgrForUser, 1196472E, ModuleMgrForUser_1196472E, ""),
            HLE_FUNCTION(ModuleMgrForUser, 24EC0641, ModuleMgrForUser_24EC0641, ""),
            HLE_FUNCTION(ModuleMgrForUser, 8F2DF740, ModuleMgrForUser_8F2DF740, ""),
            HLE_FUNCTION(ModuleMgrForUser, E4C4211C, ModuleMgrForUser_E4C4211C, ""),
            HLE_FUNCTION(ModuleMgrForUser, F2D8D1B4, ModuleMgrForUser_F2D8D1B4, ""),
            HLE_FUNCTION(ModuleMgrForUser, FBE27467, ModuleMgrForUser_FBE27467, ""),
            HLE_FUNCTION(ModuleMgrForUser, FEF27DC1, ModuleMgrForUser_FEF27DC1, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceModuleManager[] =
        {
            HLE_LIBRARY(ModuleMgrForUser)
        };
        static hle::Module module_sceModuleManager = HLE_MODULE(sceModuleManager);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ////////////////////// Module : sceLoadExec (loadexec.prx) /////////////////////
        ///
        /// /////////////////////////// Library : LoadExecForUser //////////////////////////
        /// ///
        hle::Function functions_LoadExecForUser[] =
        {
            HLE_FUNCTION(LoadExecForUser, BD2F1094, sceKernelLoadExec, "$a0:x$a1:x"),
            HLE_FUNCTION(LoadExecForUser, 05572A5F, sceKernelExitGame, ""),
            HLE_FUNCTION(LoadExecForUser, 2AC9954B, sceKernelExitGameWithStatus, "$a0:x"),
            HLE_FUNCTION(LoadExecForUser, 4AC57943, sceKernelRegisterExitCallback, "$a0:x"),
            HLE_FUNCTION(LoadExecForUser, 362A956B, LoadExecForUser_362A956B, ""),
            HLE_FUNCTION(LoadExecForUser, 8ADA38D3, LoadExecForUser_8ADA38D3, ""),
            HLE_FUNCTION(LoadExecForUser, D1FB50DC, LoadExecForUser_D1FB50DC, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceLoadExec[] =
        {
            HLE_LIBRARY(LoadExecForUser)
        };
        static hle::Module module_sceLoadExec = HLE_MODULE(sceLoadExec);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        //////////////////////// Module : sceGE_Manager (ge.prx) ///////////////////////
        ///
        /// ///////////////////////////// Library : sceGe_user /////////////////////////////
        /// ///
        hle::Function functions_sceGe_user[] =
        {
            HLE_FUNCTION(sceGe_user, 1F6752AD, sceGeEdramGetSize, ""),
            HLE_FUNCTION(sceGe_user, E47E40E4, sceGeEdramGetAddr, ""),
            HLE_FUNCTION(sceGe_user, B77905EA, sceGeEdramSetAddrTranslation, "$a0:x"),
            HLE_FUNCTION(sceGe_user, DC93CFEF, sceGeGetCmd, "$a0:x"),
            HLE_FUNCTION(sceGe_user, 57C8945B, sceGeGetMtx, "$a0:x$a1:x"),
            HLE_FUNCTION(sceGe_user, 438A385A, sceGeSaveContext, "$a0:x"),
            HLE_FUNCTION(sceGe_user, 0BF608FB, sceGeRestoreContext, "$a0:x"),
            HLE_FUNCTION(sceGe_user, AB49E76A, sceGeListEnQueue, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceGe_user, 1C0D95A6, sceGeListEnQueueHead, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceGe_user, 5FB86AB0, sceGeListDeQueue, "$a0:x"),
            HLE_FUNCTION(sceGe_user, E0D68148, sceGeListUpdateStallAddr, "$a0:x$a1:x"),
            HLE_FUNCTION(sceGe_user, 03444EB4, sceGeListSync, "$a0:x$a1:x"),
            HLE_FUNCTION(sceGe_user, B287BD61, sceGeDrawSync, "$a0:x"),
            HLE_FUNCTION(sceGe_user, B448EC0D, sceGeBreak, "$a0:x$a1:x"),
            HLE_FUNCTION(sceGe_user, 4C06E472, sceGeContinue, ""),
            HLE_FUNCTION(sceGe_user, A4FC06A4, sceGeSetCallback, "$a0:x"),
            HLE_FUNCTION(sceGe_user, 05DB22CE, sceGeUnsetCallback, "$a0:x"),
            HLE_FUNCTION(sceGe_user, E66CB92E, sceGeGetStack, "$a0:x$a1:x$a2:x$a3:x")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceGE_Manager[] =
        {
            HLE_LIBRARY(sceGe_user)
        };
        static hle::Module module_sceGE_Manager = HLE_MODULE(sceGE_Manager);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        /////////////////////// Module : sceRTC_Service (rtc.prx) //////////////////////
        ///
        /// /////////////////////////////// Library : sceRtc ///////////////////////////////
        /// ///
        hle::Function functions_sceRtc[] =
        {
            HLE_FUNCTION(sceRtc, 44F45E05, sceRtcTickAddTicks, "$a0:x$a1:x$a3a2:8x"),
            HLE_FUNCTION(sceRtc, 26D25A5D, sceRtcTickAddMicroseconds, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceRtc, F2A4AFE5, sceRtcTickAddSeconds, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceRtc, E6605BCA, sceRtcTickAddMinutes, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceRtc, 26D7A24A, sceRtcTickAddHours, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceRtc, E51B4B7A, sceRtcTickAddDays, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceRtc, CF3A2CA8, sceRtcTickAddWeeks, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceRtc, DBF74F1B, sceRtcTickAddMonths, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceRtc, 42842C77, sceRtcTickAddYears, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceRtc, 011F03C1, sceRtcGetAccumulativeTime, ""),
            HLE_FUNCTION(sceRtc, 029CA3B3, sceRtcGetAccumlativeTime, ""),
            HLE_FUNCTION(sceRtc, 0498FB3C, sceRtcFormatRFC3339, ""),
            HLE_FUNCTION(sceRtc, 05EF322C, sceRtcGetDaysInMonth, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 1909C99B, sceRtcSetTime64_t, ""),
            HLE_FUNCTION(sceRtc, 203CEB0D, sceRtcGetLastReincarnatedTime, ""),
            HLE_FUNCTION(sceRtc, 27C4594C, sceRtcGetTime_t, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 27F98543, sceRtcFormatRFC3339LocalTime, ""),
            HLE_FUNCTION(sceRtc, 28E1E988, sceRtcParseRFC3339, ""),
            HLE_FUNCTION(sceRtc, 34885E0D, sceRtcConvertUtcToLocalTime, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 36075567, sceRtcGetDosTime, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 3A807CC8, sceRtcSetTime_t, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 3F7AD767, sceRtcGetCurrentTick, "$a0:x"),
            HLE_FUNCTION(sceRtc, 42307A17, sceRtcIsLeapYear, "$a0:x"),
            HLE_FUNCTION(sceRtc, 4B1B5E82, sceRtcCheckValid, "$a0:x"),
            HLE_FUNCTION(sceRtc, 4CFA57B0, sceRtcGetCurrentClock, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 57726BC1, sceRtcGetDayOfWeek, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceRtc, 62685E98, sceRtcGetLastAdjustedTime, ""),
            HLE_FUNCTION(sceRtc, 6A676D2D, sceRtcUnregisterCallback, ""),
            HLE_FUNCTION(sceRtc, 6FF40ACC, sceRtcGetTick, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 779242A2, sceRtcConvertLocalTimeToUTC, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 7ACE4C04, sceRtcSetWin32FileTime, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 7D1FBED3, sceRtc_7D1FBED3, ""),
            HLE_FUNCTION(sceRtc, 7DE6711B, sceRtcFormatRFC2822LocalTime, ""),
            HLE_FUNCTION(sceRtc, 7ED29E40, sceRtcSetTick, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, 81FCDA34, sceRtcIsAlarmed, ""),
            HLE_FUNCTION(sceRtc, 9ED0AE87, sceRtcCompareTick, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, A93CF7D8, sceRtc_A93CF7D8, ""),
            HLE_FUNCTION(sceRtc, C2DDBEB5, sceRtc_C2DDBEB5, ""),
            HLE_FUNCTION(sceRtc, C41C2853, sceRtcGetTickResolution, ""),
            HLE_FUNCTION(sceRtc, C663B3B9, sceRtcFormatRFC2822, ""),
            HLE_FUNCTION(sceRtc, CF561893, sceRtcGetWin32FileTime, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, DFBC5F16, sceRtcParseDateTime, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, E1C93E47, sceRtcGetTime64_t, ""),
            HLE_FUNCTION(sceRtc, E7C27D1B, sceRtcGetCurrentClockLocalTime, "$a0:x"),
            HLE_FUNCTION(sceRtc, F006F264, sceRtcSetDosTime, "$a0:x$a1:x"),
            HLE_FUNCTION(sceRtc, F5FCC995, sceRtc_F5FCC995, ""),
            HLE_FUNCTION(sceRtc, FB3B18CD, sceRtcRegisterCallback, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceRTC_Service[] =
        {
            HLE_LIBRARY(sceRtc)
        };
        static hle::Module module_sceRTC_Service = HLE_MODULE(sceRTC_Service);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ///////////////////// Module : sceAudio_Driver (audio.prx) /////////////////////
        ///
        /// ////////////////////////////// Library : sceAudio //////////////////////////////
        /// ///
        hle::Function functions_sceAudio[] =
        {
            HLE_FUNCTION(sceAudio, 5EC81C55, sceAudioChReserve, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAudio, 6FC46853, sceAudioChRelease, "$a0:x"),
            HLE_FUNCTION(sceAudio, 8C1009B2, sceAudioOutput, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAudio, 136CAF51, sceAudioOutputBlocking, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAudio, E2D56B2D, sceAudioOutputPanned, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceAudio, 13F592BC, sceAudioOutputPannedBlocking, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceAudio, B7E1D8E7, sceAudioChangeChannelVolume, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAudio, 95FD0C2D, sceAudioChangeChannelConfig, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAudio, CB2E439E, sceAudioSetChannelDataLen, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAudio, E9D97901, sceAudioGetChannelRestLen, "$a0:x"),
            HLE_FUNCTION(sceAudio, B011922F, sceAudioGetChannelRestLength, "$a0:x"),
            HLE_FUNCTION(sceAudio, 38553111, sceAudioSRCChReserve, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAudio, 5C37C0AE, sceAudioSRCChRelease, ""),
            HLE_FUNCTION(sceAudio, E0727056, sceAudioSRCOutputBlocking, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAudio, 01562BA3, sceAudioOutput2Reserve, "$a0:x"),
            HLE_FUNCTION(sceAudio, 43196845, sceAudioOutput2Release, ""),
            HLE_FUNCTION(sceAudio, 2D53F36E, sceAudioOutput2OutputBlocking, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAudio, 63F2889C, sceAudioOutput2ChangeLength, "$a0:x"),
            HLE_FUNCTION(sceAudio, 647CEF33, sceAudioOutput2GetRestSample, ""),
            HLE_FUNCTION(sceAudio, 41EFADE7, sceAudioOneshotOutput, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(sceAudio, 7DE61688, sceAudioInputInit, ""),
            HLE_FUNCTION(sceAudio, E926D3FB, sceAudioInputInitEx, ""),
            HLE_FUNCTION(sceAudio, 6D4BEC68, sceAudioInput, ""),
            HLE_FUNCTION(sceAudio, 086E5895, sceAudioInputBlocking, ""),
            HLE_FUNCTION(sceAudio, A633048E, sceAudioPollInputEnd, ""),
            HLE_FUNCTION(sceAudio, 87B2E651, sceAudioWaitInputEnd, ""),
            HLE_FUNCTION(sceAudio, A708C6A6, sceAudioGetInputLength, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceAudio_Driver[] =
        {
            HLE_LIBRARY(sceAudio)
        };
        static hle::Module module_sceAudio_Driver = HLE_MODULE(sceAudio_Driver);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        /////////////////// Module : sceDisplay_Service (display.prx) //////////////////
        ///
        /// ///////////////////////////// Library : sceDisplay /////////////////////////////
        /// ///
        hle::Function functions_sceDisplay[] =
        {
            HLE_FUNCTION(sceDisplay, 0E20F177, sceDisplaySetMode, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceDisplay, DEA197D4, sceDisplayGetMode, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceDisplay, DBA6C4C4, sceDisplayGetFramePerSec, ""),
            HLE_FUNCTION(sceDisplay, 289D82FE, sceDisplaySetFrameBuf, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceDisplay, EEDA2E54, sceDisplayGetFrameBuf, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceDisplay, B4F378FA, sceDisplayIsForeground, ""),
            HLE_FUNCTION(sceDisplay, 7ED59BC4, sceDisplaySetHoldMode, "$a0:x"),
            HLE_FUNCTION(sceDisplay, 9C6EAAD7, sceDisplayGetVcount, ""),
            HLE_FUNCTION(sceDisplay, 4D4E10EC, sceDisplayIsVblank, ""),
            HLE_FUNCTION(sceDisplay, 69B53541, sceDisplayGetVblankRest, ""),
            HLE_FUNCTION(sceDisplay, 36CDFADE, sceDisplayWaitVblank, ""),
            HLE_FUNCTION(sceDisplay, 8EB9EC49, sceDisplayWaitVblankCB, ""),
            HLE_FUNCTION(sceDisplay, 984C27E7, sceDisplayWaitVblankStart, ""),
            HLE_FUNCTION(sceDisplay, 46F186C3, sceDisplayWaitVblankStartCB, ""),
            HLE_FUNCTION(sceDisplay, 21038913, sceDisplayIsVsync, ""),
            HLE_FUNCTION(sceDisplay, 773DD3A3, sceDisplayGetCurrentHcount, ""),
            HLE_FUNCTION(sceDisplay, 210EAB3A, sceDisplayGetAccumulatedHcount, ""),
            HLE_FUNCTION(sceDisplay, A83EF139, sceDisplayAdjustAccumulatedHcount, ""),
            HLE_FUNCTION(sceDisplay, A544C486, sceDisplaySetResumeMode, ""),
            HLE_FUNCTION(sceDisplay, BF79F646, sceDisplayGetResumeMode, ""),
            HLE_FUNCTION(sceDisplay, 31C4BAA8, sceDisplayGetBrightness, ""),
            HLE_FUNCTION(sceDisplay, 40F1469C, sceDisplay_40F1469C, ""),
            HLE_FUNCTION(sceDisplay, 77ED8B3A, sceDisplay_77ED8B3A, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceDisplay_Service[] =
        {
            HLE_LIBRARY(sceDisplay)
        };
        static hle::Module module_sceDisplay_Service = HLE_MODULE(sceDisplay_Service);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        /////////////////// Module : sceController_Service (ctrl.prx) //////////////////
        ///
        /// /////////////////////////////// Library : sceCtrl //////////////////////////////
        /// ///
        hle::Function functions_sceCtrl[] =
        {
            HLE_FUNCTION(sceCtrl, 1F4011E6, sceCtrlSetSamplingMode, "$a0:x"),
            HLE_FUNCTION(sceCtrl, DA6B76A1, sceCtrlGetSamplingMode, "$a0:x"),
            HLE_FUNCTION(sceCtrl, 6A2774F3, sceCtrlSetSamplingCycle, "$a0:x"),
            HLE_FUNCTION(sceCtrl, 02BAAD91, sceCtrlGetSamplingCycle, "$a0:x"),
            HLE_FUNCTION(sceCtrl, A7144800, sceCtrlSetIdleCancelThreshold, "$a0:x$a1:x"),
            HLE_FUNCTION(sceCtrl, 687660FA, sceCtrlGetIdleCancelThreshold, "$a0:x$a1:x"),
            HLE_FUNCTION(sceCtrl, 3A622550, sceCtrlPeekBufferPositive, "$a0:x$a1:x"),
            HLE_FUNCTION(sceCtrl, C152080A, sceCtrlPeekBufferNegative, "$a0:x$a1:x"),
            HLE_FUNCTION(sceCtrl, 1F803938, sceCtrlReadBufferPositive, "$a0:x$a1:x"),
            HLE_FUNCTION(sceCtrl, 60B81F86, sceCtrlReadBufferNegative, "$a0:x$a1:x"),
            HLE_FUNCTION(sceCtrl, B1D0E5CD, sceCtrlPeekLatch, "$a0:x"),
            HLE_FUNCTION(sceCtrl, 0B588501, sceCtrlReadLatch, "$a0:x"),
            HLE_FUNCTION(sceCtrl, A68FD260, sceCtrlClearRapidFire, ""),
            HLE_FUNCTION(sceCtrl, 6841BE1A, sceCtrlSetRapidFire, ""),
            HLE_FUNCTION(sceCtrl, 348D99D4, sceCtrl_348D99D4, ""),
            HLE_FUNCTION(sceCtrl, AF5960F3, sceCtrl_AF5960F3, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceController_Service[] =
        {
            HLE_LIBRARY(sceCtrl)
        };
        static hle::Module module_sceController_Service = HLE_MODULE(sceController_Service);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ////////////////// Module : sceHP_Remote_Driver (hpremote.prx) /////////////////
        ///
        /// /////////////////////////////// Library : sceHprm //////////////////////////////
        /// ///
        hle::Function functions_sceHprm[] =
        {
            HLE_FUNCTION(sceHprm, 1910B327, sceHprmPeekCurrentKey, "$a0:x"),
            HLE_FUNCTION(sceHprm, 208DB1BD, sceHprmIsRemoteExist, ""),
            HLE_FUNCTION(sceHprm, 219C58F1, sceHprmIsMicrophoneExist, ""),
            HLE_FUNCTION(sceHprm, 2BCEC83E, sceHprmPeekLatch, "$a0:x"),
            HLE_FUNCTION(sceHprm, 3953DE6B, sceHprm_3953DE6B, ""),
            HLE_FUNCTION(sceHprm, 396FD885, sceHprm_396FD885, ""),
            HLE_FUNCTION(sceHprm, 40D2F9F0, sceHprmReadLatch, "$a0:x"),
            HLE_FUNCTION(sceHprm, 444ED0B7, sceHprmUnregitserCallback, ""),
            HLE_FUNCTION(sceHprm, 71B5FB67, sceHprmGetHpDetect, ""),
            HLE_FUNCTION(sceHprm, 7E69EDA4, sceHprmIsHeadphoneExist, ""),
            HLE_FUNCTION(sceHprm, C7154136, sceHprmRegisterCallback, ""),
            HLE_FUNCTION(sceHprm, FD7DE6CD, sceHprm_FD7DE6CD, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceHP_Remote_Driver[] =
        {
            HLE_LIBRARY(sceHprm)
        };
        static hle::Module module_sceHP_Remote_Driver = HLE_MODULE(sceHP_Remote_Driver);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ///////////////////// Module : scePower_Service (power.prx) ////////////////////
        ///
        /// ////////////////////////////// Library : scePower //////////////////////////////
        /// ///
        hle::Function functions_scePower[] =
        {
            HLE_FUNCTION(scePower, 0074EF9B, scePowerGetResumeCount, ""),
            HLE_FUNCTION(scePower, 0442D852, scePowerRequestColdReset, ""),
            HLE_FUNCTION(scePower, 04B7766E, scePowerRegisterCallback, "$a0:x$a1:x"),
            HLE_FUNCTION(scePower, 0AFD0D8B, scePowerIsBatteryExist, ""),
            HLE_FUNCTION(scePower, 0CD21B1F, scePowerSetPowerSwMode, ""),
            HLE_FUNCTION(scePower, 165CE085, scePowerGetPowerSwMode, ""),
            HLE_FUNCTION(scePower, 1E490401, scePowerIsBatteryCharging, ""),
            HLE_FUNCTION(scePower, 2085D15D, scePowerGetBatteryLifePercent, ""),
            HLE_FUNCTION(scePower, 23436A4A, scePowerGetInnerTemp, ""),
            HLE_FUNCTION(scePower, 23C31FFE, scePowerVolatileMemLock, ""),
            HLE_FUNCTION(scePower, 27F3292C, scePowerBatteryUpdateInfo, ""),
            HLE_FUNCTION(scePower, 2875994B, scePower_2875994B, ""),
            HLE_FUNCTION(scePower, 28E12023, scePowerGetBatteryTemp, ""),
            HLE_FUNCTION(scePower, 2B51FE2F, scePower_2B51FE2F, ""),
            HLE_FUNCTION(scePower, 2B7C7CF4, scePowerRequestStandby, ""),
            HLE_FUNCTION(scePower, 34F9C463, scePowerGetPllClockFrequencyInt, ""),
            HLE_FUNCTION(scePower, 3951AF53, scePowerWaitRequestCompletion, ""),
            HLE_FUNCTION(scePower, 442BFBAC, scePowerGetBacklightMaximum, ""),
            HLE_FUNCTION(scePower, 478FE6F5, scePowerGetBusClockFrequency, ""),
            HLE_FUNCTION(scePower, 483CE86B, scePowerGetBatteryVolt, ""),
            HLE_FUNCTION(scePower, 545A7F3C, scePower_545A7F3C, ""),
            HLE_FUNCTION(scePower, 737486F2, scePowerSetClockFrequency, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(scePower, 78A1A796, scePowerIsSuspendRequired, ""),
            HLE_FUNCTION(scePower, 7F30B3B1, scePowerIdleTimerEnable, "$a0:x"),
            HLE_FUNCTION(scePower, 7FA406DD, scePowerIsRequest, ""),
            HLE_FUNCTION(scePower, 843FBF43, scePowerSetCpuClockFrequency, "$a0:x"),
            HLE_FUNCTION(scePower, 862AE1A6, scePowerGetBatteryElec, ""),
            HLE_FUNCTION(scePower, 87440F5E, scePowerIsPowerOnline, ""),
            HLE_FUNCTION(scePower, 8EFB3FA2, scePowerGetBatteryLifeTime, ""),
            HLE_FUNCTION(scePower, 94F5A53F, scePowerGetBatteryRemainCapacity, ""),
            HLE_FUNCTION(scePower, 972CE941, scePowerIdleTimerDisable, "$a0:x"),
            HLE_FUNCTION(scePower, 9BADB3EB, scePowerGetBusClockFrequencyFloat, ""),
            HLE_FUNCTION(scePower, A4E93389, scePower_A4E93389, ""),
            HLE_FUNCTION(scePower, A9D22232, scePowerSetCallbackMode, ""),
            HLE_FUNCTION(scePower, AC32C9CC, scePowerRequestSuspend, ""),
            HLE_FUNCTION(scePower, B1A52C83, scePowerGetCpuClockFrequencyFloat, ""),
            HLE_FUNCTION(scePower, B3EDD801, scePowerVolatileMemUnlock, ""),
            HLE_FUNCTION(scePower, B4432BC8, scePowerGetBatteryChargingStatus, ""),
            HLE_FUNCTION(scePower, B8D7B3FB, scePowerSetBusClockFrequency, "$a0:x"),
            HLE_FUNCTION(scePower, B999184C, scePowerGetLowBatteryCapacity, ""),
            HLE_FUNCTION(scePower, BAFA3DF0, scePowerGetCallbackMode, ""),
            HLE_FUNCTION(scePower, BD681969, scePowerGetBusClockFrequencyInt, ""),
            HLE_FUNCTION(scePower, CA3D34C1, scePowerUnlock, "$a0:x"),
            HLE_FUNCTION(scePower, CB49F5CE, scePowerGetBatteryChargeCycle, ""),
            HLE_FUNCTION(scePower, D3075926, scePowerIsLowBattery, ""),
            HLE_FUNCTION(scePower, D6D016EF, scePowerLock, "$a0:x"),
            HLE_FUNCTION(scePower, DB62C9CF, scePowerCancelRequest, ""),
            HLE_FUNCTION(scePower, DB9D28DD, scePowerUnregitserCallback, ""),
            HLE_FUNCTION(scePower, DFA8BAF8, scePowerUnregisterCallback, ""),
            HLE_FUNCTION(scePower, E8E4E204, scePower_E8E4E204, ""),
            HLE_FUNCTION(scePower, EA382A27, scePowerGetPllClockFrequencyFloat, ""),
            HLE_FUNCTION(scePower, EBD177D6, scePower_EBD177D6, ""),
            HLE_FUNCTION(scePower, EDC13FE5, scePowerGetIdleTimer, ""),
            HLE_FUNCTION(scePower, EFD3C963, scePowerTick, "$a0:x"),
            HLE_FUNCTION(scePower, FA97A599, scePowerVolatileMemTryLock, ""),
            HLE_FUNCTION(scePower, FD18A0FF, scePowerGetBatteryFullCapacity, ""),
            HLE_FUNCTION(scePower, FDB5BFE9, scePowerGetCpuClockFrequencyInt, ""),
            HLE_FUNCTION(scePower, FEE03A2F, scePowerGetCpuClockFrequency, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_scePower_Service[] =
        {
            HLE_LIBRARY(scePower)
        };
        static hle::Module module_scePower_Service = HLE_MODULE(scePower_Service);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        /////////////////////// Module : sceUSB_Driver (usb.prx) ///////////////////////
        ///
        /// /////////////////////////////// Library : sceUsb ///////////////////////////////
        /// ///
        hle::Function functions_sceUsb[] =
        {
            HLE_FUNCTION(sceUsb, 112CC951, sceUsbGetDrvState, "$a0:x"),
            HLE_FUNCTION(sceUsb, 1C360735, sceUsbWaitCancel, ""),
            HLE_FUNCTION(sceUsb, 4E537366, sceUsbGetDrvList, ""),
            HLE_FUNCTION(sceUsb, 586DB82C, sceUsbActivate, "$a0:x"),
            HLE_FUNCTION(sceUsb, 5BE0E002, sceUsbWaitState, ""),
            HLE_FUNCTION(sceUsb, 616F2B61, sceUsbWaitStateCB, ""),
            HLE_FUNCTION(sceUsb, 89DE0DC5, sceUsb_89DE0DC5, ""),
            HLE_FUNCTION(sceUsb, 8BFC3DE8, sceUsb_8BFC3DE8, ""),
            HLE_FUNCTION(sceUsb, AE5DE6AF, sceUsbStart, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceUsb, C21645A4, sceUsbGetState, ""),
            HLE_FUNCTION(sceUsb, C2464FA0, sceUsbStop, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceUsb, C572A9C8, sceUsbDeactivate, "$a0:x"),
            HLE_FUNCTION(sceUsb, E20B23A6, sceUsbActivateWithCharging, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceUSB_Driver[] =
        {
            HLE_LIBRARY(sceUsb)
        };
        static hle::Module module_sceUSB_Driver = HLE_MODULE(sceUSB_Driver);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ////////////////// Module : sceOpenPSID_Service (openpsid.prx) /////////////////
        ///
        /// ///////////////////////////// Library : sceOpenPSID ////////////////////////////
        /// ///
        hle::Function functions_sceOpenPSID[] =
        {
            HLE_FUNCTION(sceOpenPSID, C69BEBCE, sceOpenPSIDGetOpenPSID, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// ////////////////////////////// Library : sceDdrdb //////////////////////////////
        /// ///
        hle::Function functions_sceDdrdb[] =
        {
            HLE_FUNCTION(sceDdrdb, F013F8BF, sceDdrdb_F013F8BF, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceOpenPSID_Service[] =
        {
            HLE_LIBRARY(sceOpenPSID),
            HLE_LIBRARY(sceDdrdb)
        };
        static hle::Module module_sceOpenPSID_Service = HLE_MODULE(sceOpenPSID_Service);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        /////////////////// Module : sceSIRCS_IrDA_Driver (sircs.prx) //////////////////
        ///
        /// ////////////////////////////// Library : sceSircs //////////////////////////////
        /// ///
        hle::Function functions_sceSircs[] =
        {
            HLE_FUNCTION(sceSircs, 71EEF62D, sceSircsSend, "$a0:x$a1:x"),
            HLE_FUNCTION(sceSircs, 83381633, sceSircsReceive, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceSIRCS_IrDA_Driver[] =
        {
            HLE_LIBRARY(sceSircs)
        };
        static hle::Module module_sceSIRCS_IrDA_Driver = HLE_MODULE(sceSIRCS_IrDA_Driver);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ///////////////////// Module : sceUmd_driver (mediaman.prx) ////////////////////
        ///
        /// ///////////////////////////// Library : sceUmdUser /////////////////////////////
        /// ///
        hle::Function functions_sceUmdUser[] =
        {
            HLE_FUNCTION(sceUmdUser, 20628E6F, sceUmdGetErrorStat, ""),
            HLE_FUNCTION(sceUmdUser, 340B7686, sceUmdGetDiscInfo, ""),
            HLE_FUNCTION(sceUmdUser, 46EBB729, sceUmdCheckMedium, "$a0:x"),
            HLE_FUNCTION(sceUmdUser, 4A9E5E29, sceUmdWaitDriveStatCB, ""),
            HLE_FUNCTION(sceUmdUser, 56202973, sceUmdWaitDriveStatWithTimer, ""),
            HLE_FUNCTION(sceUmdUser, 6AF9B50A, sceUmdCancelWaitDriveStat, ""),
            HLE_FUNCTION(sceUmdUser, 6B4A146C, sceUmdGetDriveStat, ""),
            HLE_FUNCTION(sceUmdUser, 87533940, sceUmdReplaceProhibit, ""),
            HLE_FUNCTION(sceUmdUser, 8EF08FCE, sceUmdWaitDriveStat, "$a0:x"),
            HLE_FUNCTION(sceUmdUser, AEE7404D, sceUmdRegisterUMDCallBack, "$a0:x"),
            HLE_FUNCTION(sceUmdUser, BD2BDE07, sceUmdUnRegisterUMDCallBack, ""),
            HLE_FUNCTION(sceUmdUser, C6183D47, sceUmdActivate, "$a0:x$a1:x"),
            HLE_FUNCTION(sceUmdUser, CBE9F02A, sceUmdReplacePermit, ""),
            HLE_FUNCTION(sceUmdUser, E83742BA, sceUmdDeactivate, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceUmd_driver[] =
        {
            HLE_LIBRARY(sceUmdUser)
        };
        static hle::Module module_sceUmd_driver = HLE_MODULE(sceUmd_driver);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ////////////////////// Module : sceWlan_Driver (wlan.prx) //////////////////////
        ///
        /// ///////////////////////////// Library : sceWlanDrv /////////////////////////////
        /// ///
        hle::Function functions_sceWlanDrv[] =
        {
            HLE_FUNCTION(sceWlanDrv, 0C622081, sceWlanGetEtherAddr, "$a0:x"),
            HLE_FUNCTION(sceWlanDrv, 93440B11, sceWlanDevIsPowerOn, ""),
            HLE_FUNCTION(sceWlanDrv, D7763699, sceWlanGetSwitchState, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// /////////////////////////// Library : sceWlanDrv_lib ///////////////////////////
        /// ///
        hle::Function functions_sceWlanDrv_lib[] =
        {
            HLE_FUNCTION(sceWlanDrv_lib, 05FE320C, sceWlanDevGetStateGPIO, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 19E51F54, sceWlanDevGetMacAddr, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 2D0FAE4E, sceWlanDrv_lib_2D0FAE4E, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 40B0AA4A, sceWlanDrv_lib_40B0AA4A, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 44A99F9D, sceWlanGetDropRate, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 482CAE9A, sceWlanDevAttach, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 4C14BACA, sceWlanDrv_lib_4C14BACA, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 4C7F62E0, sceWlanGPUnRegisterCallback, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 56F467CA, sceWlanDrv_lib_56F467CA, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 5BAA1FE5, sceWlanDrv_lib_5BAA1FE5, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 5E7C8D94, sceWlanDevIsGameMode, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 5ED4049A, sceWlanGPPrevEstablishActive, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 6D5C839E, sceWlanDrv_lib_6D5C839E, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 749B813A, sceWlanSetHostDiscover, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 7FF54BD2, sceWlanDevSetGPIO, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 81579D36, sceWlanDrv_lib_81579D36, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 8D5F551B, sceWlanDrv_lib_8D5F551B, ""),
            HLE_FUNCTION(sceWlanDrv_lib, 9658C9F7, sceWlanGPRegisterCallback, ""),
            HLE_FUNCTION(sceWlanDrv_lib, A447103A, sceWlanGPRecv, ""),
            HLE_FUNCTION(sceWlanDrv_lib, B4D7CB74, sceWlanGPSend, ""),
            HLE_FUNCTION(sceWlanDrv_lib, C9A8CAB7, sceWlanDevDetach, ""),
            HLE_FUNCTION(sceWlanDrv_lib, EB3235B5, sceWlanSetDropRate, ""),
            HLE_FUNCTION(sceWlanDrv_lib, FBD385FB, sceWlanDropCheck, ""),
            HLE_FUNCTION(sceWlanDrv_lib, FE8A0B46, sceWlanSetWakeUp, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceWlan_Driver[] =
        {
            HLE_LIBRARY(sceWlanDrv),
            HLE_LIBRARY(sceWlanDrv_lib)
        };
        static hle::Module module_sceWlan_Driver = HLE_MODULE(sceWlan_Driver);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ////////////////// Module : sceRegistry_Service (registry.prx) /////////////////
        ///
        /// /////////////////////////////// Library : sceReg ///////////////////////////////
        /// ///
        hle::Function functions_sceReg[] =
        {
            HLE_FUNCTION(sceReg, 0CAE832B, sceRegCloseCategory, "$a0:x"),
            HLE_FUNCTION(sceReg, 0D69BF40, sceRegFlushCategory, "$a0:x"),
            HLE_FUNCTION(sceReg, 17768E14, sceRegSetKeyValue, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceReg, 1D8A762E, sceRegOpenCategory, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceReg, 28A8E98A, sceRegGetKeyValue, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceReg, 2C0DB9DD, sceRegGetKeysNum, "$a0:x$a1:x"),
            HLE_FUNCTION(sceReg, 2D211135, sceRegGetKeys, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceReg, 30BE0259, sceRegGetKeyValueByName, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceReg, 3615BC87, sceRegRemoveKey, ""),
            HLE_FUNCTION(sceReg, 39461B4D, sceRegFlushRegistry, "$a0:x"),
            HLE_FUNCTION(sceReg, 4CA16893, sceRegRemoveCategory, "$a0:x$a1:x"),
            HLE_FUNCTION(sceReg, 57641A81, sceRegCreateKey, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceReg, 835ECE6F, sceReg_835ECE6F, ""),
            HLE_FUNCTION(sceReg, 92E41280, sceRegOpenRegistry, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceReg, 9B25EDF1, sceRegExit, ""),
            HLE_FUNCTION(sceReg, BE8C1263, sceReg_BE8C1263, ""),
            HLE_FUNCTION(sceReg, C5768D02, sceRegGetKeyInfoByName, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceReg, D4475AA8, sceRegGetKeyInfo, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(sceReg, DEDA92BF, sceRegRemoveRegistry, "$a0:x"),
            HLE_FUNCTION(sceReg, FA8A5739, sceRegCloseRegistry, "$a0:x")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceRegistry_Service[] =
        {
            HLE_LIBRARY(sceReg)
        };
        static hle::Module module_sceRegistry_Service = HLE_MODULE(sceRegistry_Service);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        /////////////////// Module : sceUtility_Driver (utility.prx) ///////////////////
        ///
        /// ///////////////////////////// Library : sceUtility /////////////////////////////
        /// ///
        hle::Function functions_sceUtility[] =
        {
            HLE_FUNCTION(sceUtility, 0251B134, sceUtility_0251B134, ""),
            HLE_FUNCTION(sceUtility, 05AFB9E4, sceUtilityHtmlViewerUpdate, ""),
            HLE_FUNCTION(sceUtility, 06A48659, sceUtility_06A48659, ""),
            HLE_FUNCTION(sceUtility, 0D5BC6D2, sceUtilityLoadUsbModule, ""),
            HLE_FUNCTION(sceUtility, 0F3EEAAC, sceUtility_0F3EEAAC, ""),
            HLE_FUNCTION(sceUtility, 1281DA8E, sceUtilityInstallInitStart, ""),
            HLE_FUNCTION(sceUtility, 147F7C85, sceUtility_147F7C85, ""),
            HLE_FUNCTION(sceUtility, 149A7895, sceUtility_149A7895, ""),
            HLE_FUNCTION(sceUtility, 1579A159, sceUtilityLoadNetModule, "$a0:x"),
            HLE_FUNCTION(sceUtility, 16A1A8D8, sceUtility_16A1A8D8, ""),
            HLE_FUNCTION(sceUtility, 16D02AF0, sceUtility_16D02AF0, ""),
            HLE_FUNCTION(sceUtility, 28D35634, sceUtility_28D35634, ""),
            HLE_FUNCTION(sceUtility, 2995D020, sceUtility_2995D020, ""),
            HLE_FUNCTION(sceUtility, 2A2B3DE0, sceUtilityLoadModule, ""),
            HLE_FUNCTION(sceUtility, 2AD8E239, sceUtilityMsgDialogInitStart, "$a0:x"),
            HLE_FUNCTION(sceUtility, 2B96173B, sceUtility_2B96173B, ""),
            HLE_FUNCTION(sceUtility, 34B78343, sceUtilityGetSystemParamString, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceUtility, 3AAD51DC, sceUtility_3AAD51DC, ""),
            HLE_FUNCTION(sceUtility, 3AD50AE7, sceNetplayDialogInitStart, ""),
            HLE_FUNCTION(sceUtility, 3DFAEBA9, sceUtilityOskShutdownStart, ""),
            HLE_FUNCTION(sceUtility, 417BED54, sceNetplayDialogUpdate, ""),
            HLE_FUNCTION(sceUtility, 41E30674, sceUtilitySetSystemParamString, "$a0:x$a1:x"),
            HLE_FUNCTION(sceUtility, 42071A83, sceUtility_42071A83, ""),
            HLE_FUNCTION(sceUtility, 434D4B3A, sceUtilityGetNetParam, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceUtility, 45C18506, sceUtilitySetSystemParamInt, "$a0:x$a1:x"),
            HLE_FUNCTION(sceUtility, 4928BD96, sceUtilityMsgDialogAbort, ""),
            HLE_FUNCTION(sceUtility, 4A833BA4, sceUtility_4A833BA4, ""),
            HLE_FUNCTION(sceUtility, 4B0A8FE5, sceUtility_4B0A8FE5, ""),
            HLE_FUNCTION(sceUtility, 4B85C861, sceUtilityOskUpdate, "$a0:x"),
            HLE_FUNCTION(sceUtility, 4DB1E739, sceUtilityNetconfInitStart, "$a0:x"),
            HLE_FUNCTION(sceUtility, 4FED24D8, sceUtilityGetNetParamLatestID, ""),
            HLE_FUNCTION(sceUtility, 50C4CD57, sceUtilitySavedataInitStart, "$a0:x"),
            HLE_FUNCTION(sceUtility, 54A5C62F, sceUtility_54A5C62F, ""),
            HLE_FUNCTION(sceUtility, 5EEE6548, sceUtilityCheckNetParam, "$a0:x"),
            HLE_FUNCTION(sceUtility, 5EF1C24A, sceUtilityInstallShutdownStart, ""),
            HLE_FUNCTION(sceUtility, 6332AA39, sceUtilityNetconfGetStatus, ""),
            HLE_FUNCTION(sceUtility, 64D50C56, sceUtilityUnloadNetModule, "$a0:x"),
            HLE_FUNCTION(sceUtility, 67AF3428, sceUtilityMsgDialogShutdownStart, ""),
            HLE_FUNCTION(sceUtility, 6F56F9CF, sceUtility_6F56F9CF, ""),
            HLE_FUNCTION(sceUtility, 70267ADF, sceUtility_70267ADF, ""),
            HLE_FUNCTION(sceUtility, 7853182D, sceUtilityGameSharingUpdate, ""),
            HLE_FUNCTION(sceUtility, 81C44706, sceUtility_81C44706, ""),
            HLE_FUNCTION(sceUtility, 8326AB05, sceUtility_8326AB05, ""),
            HLE_FUNCTION(sceUtility, 86A03A27, sceUtility_86A03A27, ""),
            HLE_FUNCTION(sceUtility, 86ABDB1B, sceUtility_86ABDB1B, ""),
            HLE_FUNCTION(sceUtility, 8874DBE0, sceUtilitySavedataGetStatus, ""),
            HLE_FUNCTION(sceUtility, 88BC7406, sceUtility_88BC7406, ""),
            HLE_FUNCTION(sceUtility, 89317C8F, sceUtility_89317C8F, ""),
            HLE_FUNCTION(sceUtility, 91E70E35, sceUtilityNetconfUpdate, "$a0:x"),
            HLE_FUNCTION(sceUtility, 943CBA46, sceUtility_943CBA46, ""),
            HLE_FUNCTION(sceUtility, 946963F3, sceUtilityGameSharingGetStatus, ""),
            HLE_FUNCTION(sceUtility, 95FC253B, sceUtilityMsgDialogUpdate, "$a0:x"),
            HLE_FUNCTION(sceUtility, 9790B33C, sceUtilitySavedataShutdownStart, ""),
            HLE_FUNCTION(sceUtility, 9A1C91D7, sceUtilityMsgDialogGetStatus, ""),
            HLE_FUNCTION(sceUtility, A03D29BA, sceUtilityInstallUpdate, ""),
            HLE_FUNCTION(sceUtility, A084E056, sceUtility_A084E056, ""),
            HLE_FUNCTION(sceUtility, A50E5B30, sceUtility_A50E5B30, ""),
            HLE_FUNCTION(sceUtility, A5DA2406, sceUtilityGetSystemParamInt, "$a0:x$a1:x"),
            HLE_FUNCTION(sceUtility, AB083EA9, sceUtility_AB083EA9, ""),
            HLE_FUNCTION(sceUtility, B0FB7FF5, sceUtility_B0FB7FF5, ""),
            HLE_FUNCTION(sceUtility, B62A4061, sceUtility_B62A4061, ""),
            HLE_FUNCTION(sceUtility, B6CEE597, sceNetplayDialogGetStatus, ""),
            HLE_FUNCTION(sceUtility, B8592D5F, sceUtility_B8592D5F, ""),
            HLE_FUNCTION(sceUtility, BC6B6296, sceNetplayDialogShutdownStart, ""),
            HLE_FUNCTION(sceUtility, BDA7D894, sceUtilityHtmlViewerGetStatus, ""),
            HLE_FUNCTION(sceUtility, C4700FA3, sceUtilityInstallGetStatus, ""),
            HLE_FUNCTION(sceUtility, C492F751, sceUtilityGameSharingInitStart, ""),
            HLE_FUNCTION(sceUtility, C629AF26, sceUtilityLoadAvModule, ""),
            HLE_FUNCTION(sceUtility, CDC3AA41, sceUtilityHtmlViewerInitStart, ""),
            HLE_FUNCTION(sceUtility, D17A0573, sceUtility_D17A0573, ""),
            HLE_FUNCTION(sceUtility, D4B95FFB, sceUtilitySavedataUpdate, "$a0:x"),
            HLE_FUNCTION(sceUtility, D81957B7, sceUtility_D81957B7, ""),
            HLE_FUNCTION(sceUtility, D852CDCE, sceUtility_D852CDCE, ""),
            HLE_FUNCTION(sceUtility, DA97F1AA, sceUtility_DA97F1AA, ""),
            HLE_FUNCTION(sceUtility, DDE5389D, sceUtility_DDE5389D, ""),
            HLE_FUNCTION(sceUtility, E19C97D6, sceUtility_E19C97D6, ""),
            HLE_FUNCTION(sceUtility, E49BFE92, sceUtilityUnloadModule, ""),
            HLE_FUNCTION(sceUtility, E7B778D8, sceUtility_E7B778D8, ""),
            HLE_FUNCTION(sceUtility, ECE1D3E5, sceUtility_ECE1D3E5, ""),
            HLE_FUNCTION(sceUtility, ED0FAD38, sceUtility_ED0FAD38, ""),
            HLE_FUNCTION(sceUtility, EF3582B2, sceUtility_EF3582B2, ""),
            HLE_FUNCTION(sceUtility, EFC6F80F, sceUtilityGameSharingShutdownStart, ""),
            HLE_FUNCTION(sceUtility, F3F76017, sceUtilityOskGetStatus, ""),
            HLE_FUNCTION(sceUtility, F3FBC572, sceUtility_F3FBC572, ""),
            HLE_FUNCTION(sceUtility, F5CE1134, sceUtilityHtmlViewerShutdownStart, ""),
            HLE_FUNCTION(sceUtility, F6269B82, sceUtilityOskInitStart, "$a0:x"),
            HLE_FUNCTION(sceUtility, F64910F0, sceUtilityUnloadUsbModule, ""),
            HLE_FUNCTION(sceUtility, F7D8D092, sceUtilityUnloadAvModule, ""),
            HLE_FUNCTION(sceUtility, F88155F6, sceUtilityNetconfShutdownStart, ""),
            HLE_FUNCTION(sceUtility, F9E0008C, sceUtility_F9E0008C, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// ///////////////////////// Library : sceUtility_private /////////////////////////
        /// ///
        hle::Function functions_sceUtility_private[] =
        {
            HLE_FUNCTION(sceUtility_private, 03043DAF, sceUtility_private_03043DAF, ""),
            HLE_FUNCTION(sceUtility_private, 0CF833E5, sceUtility_private_0CF833E5, ""),
            HLE_FUNCTION(sceUtility_private, 107CA63E, sceUtility_private_107CA63E, ""),
            HLE_FUNCTION(sceUtility_private, 11236637, sceUtility_private_11236637, ""),
            HLE_FUNCTION(sceUtility_private, 1FD567D4, sceUtility_private_1FD567D4, ""),
            HLE_FUNCTION(sceUtility_private, 23FE0D1B, sceUtility_private_23FE0D1B, ""),
            HLE_FUNCTION(sceUtility_private, 284DBC23, sceUtility_private_284DBC23, ""),
            HLE_FUNCTION(sceUtility_private, 2A9524EF, sceUtility_private_2A9524EF, ""),
            HLE_FUNCTION(sceUtility_private, 2F265D64, sceUtility_private_2F265D64, ""),
            HLE_FUNCTION(sceUtility_private, 34892525, sceUtility_private_34892525, ""),
            HLE_FUNCTION(sceUtility_private, 3B76A6D0, sceUtility_private_3B76A6D0, ""),
            HLE_FUNCTION(sceUtility_private, 3EBDB7F6, sceUtility_private_3EBDB7F6, ""),
            HLE_FUNCTION(sceUtility_private, 47FA0F9B, sceUtility_private_47FA0F9B, ""),
            HLE_FUNCTION(sceUtility_private, 4B069019, sceUtility_private_4B069019, ""),
            HLE_FUNCTION(sceUtility_private, 5B3C096F, sceUtility_private_5B3C096F, ""),
            HLE_FUNCTION(sceUtility_private, 6513E388, sceUtility_private_6513E388, ""),
            HLE_FUNCTION(sceUtility_private, 6B0356F6, sceUtility_private_6B0356F6, ""),
            HLE_FUNCTION(sceUtility_private, 6D2D8A41, sceUtility_private_6D2D8A41, ""),
            HLE_FUNCTION(sceUtility_private, 6D73DD7C, sceUtility_private_6D73DD7C, ""),
            HLE_FUNCTION(sceUtility_private, 7139732A, sceUtility_private_7139732A, ""),
            HLE_FUNCTION(sceUtility_private, 84A1E70F, sceUtility_private_84A1E70F, ""),
            HLE_FUNCTION(sceUtility_private, 84FEFEAD, sceUtility_private_84FEFEAD, ""),
            HLE_FUNCTION(sceUtility_private, 8A80D4EE, sceUtility_private_8A80D4EE, ""),
            HLE_FUNCTION(sceUtility_private, 8E7B9318, sceUtility_private_8E7B9318, ""),
            HLE_FUNCTION(sceUtility_private, 9AEFABC9, sceUtility_private_9AEFABC9, ""),
            HLE_FUNCTION(sceUtility_private, 9E8CD6BC, sceUtility_private_9E8CD6BC, ""),
            HLE_FUNCTION(sceUtility_private, A1A4A4D3, sceUtility_private_A1A4A4D3, ""),
            HLE_FUNCTION(sceUtility_private, A1DF25E8, sceUtility_private_A1DF25E8, ""),
            HLE_FUNCTION(sceUtility_private, A5D7DC3E, sceUtility_private_A5D7DC3E, ""),
            HLE_FUNCTION(sceUtility_private, ACAFCBA3, sceUtility_private_ACAFCBA3, ""),
            HLE_FUNCTION(sceUtility_private, ACDC84F3, sceUtility_private_ACDC84F3, ""),
            HLE_FUNCTION(sceUtility_private, AEADFF11, sceUtility_private_AEADFF11, ""),
            HLE_FUNCTION(sceUtility_private, AFC70B22, sceUtility_private_AFC70B22, ""),
            HLE_FUNCTION(sceUtility_private, B06FE2AB, sceUtility_private_B06FE2AB, ""),
            HLE_FUNCTION(sceUtility_private, B618DCC7, sceUtility_private_B618DCC7, ""),
            HLE_FUNCTION(sceUtility_private, BF218ECC, sceUtility_private_BF218ECC, ""),
            HLE_FUNCTION(sceUtility_private, C5F825B6, sceUtility_private_C5F825B6, ""),
            HLE_FUNCTION(sceUtility_private, C652A9B0, sceUtility_private_C652A9B0, ""),
            HLE_FUNCTION(sceUtility_private, CF9DB393, sceUtility_private_CF9DB393, ""),
            HLE_FUNCTION(sceUtility_private, D6F31E47, sceUtility_private_D6F31E47, ""),
            HLE_FUNCTION(sceUtility_private, DCCC4CE2, sceUtility_private_DCCC4CE2, ""),
            HLE_FUNCTION(sceUtility_private, E16F76D4, sceUtility_private_E16F76D4, ""),
            HLE_FUNCTION(sceUtility_private, EAABCB99, sceUtility_private_EAABCB99, ""),
            HLE_FUNCTION(sceUtility_private, EF6B75B3, sceUtility_private_EF6B75B3, ""),
            HLE_FUNCTION(sceUtility_private, FBCC79F8, sceUtility_private_FBCC79F8, ""),
            HLE_FUNCTION(sceUtility_private, FC6A5184, sceUtility_private_FC6A5184, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// //////////////////// Library : sceUtility_netparam_internal ////////////////////
        /// ///
        hle::Function functions_sceUtility_netparam_internal[] =
        {
            HLE_FUNCTION(sceUtility_netparam_internal, 0BA36F3F, sceUtility_netparam_internal_0BA36F3F, ""),
            HLE_FUNCTION(sceUtility_netparam_internal, 0E244DD7, sceUtility_netparam_internal_0E244DD7, ""),
            HLE_FUNCTION(sceUtility_netparam_internal, 4CBB0CA0, sceUtility_netparam_internal_4CBB0CA0, ""),
            HLE_FUNCTION(sceUtility_netparam_internal, BEE92A0A, sceUtility_netparam_internal_BEE92A0A, ""),
            HLE_FUNCTION(sceUtility_netparam_internal, F161E17A, sceUtility_netparam_internal_F161E17A, ""),
            HLE_FUNCTION(sceUtility_netparam_internal, F547B8FC, sceUtility_netparam_internal_F547B8FC, ""),
            HLE_FUNCTION(sceUtility_netparam_internal, FD539533, sceUtility_netparam_internal_FD539533, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceUtility_Driver[] =
        {
            HLE_LIBRARY(sceUtility),
            HLE_LIBRARY(sceUtility_private),
            HLE_LIBRARY(sceUtility_netparam_internal)
        };
        static hle::Module module_sceUtility_Driver = HLE_MODULE(sceUtility_Driver);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ////////////////////// Module : sceMesgLed (mesg_led.prx) //////////////////////
        ///
        /// ////////////////////////////// Library : sceResmgr /////////////////////////////
        /// ///
        hle::Function functions_sceResmgr[] =
        {
            HLE_FUNCTION(sceResmgr, 9DC14891, sceResmgr_9DC14891, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// ////////////////////////////// Library : scePauth //////////////////////////////
        /// ///
        hle::Function functions_scePauth[] =
        {
            HLE_FUNCTION(scePauth, F7AA47F6, scePauth_F7AA47F6, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceMesgLed[] =
        {
            HLE_LIBRARY(sceResmgr),
            HLE_LIBRARY(scePauth)
        };
        static hle::Module module_sceMesgLed = HLE_MODULE(sceMesgLed);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        //////////////////// Module : sceImpose_Driver (impose.prx) ////////////////////
        ///
        /// ////////////////////////////// Library : sceImpose /////////////////////////////
        /// ///
        hle::Function functions_sceImpose[] =
        {
            HLE_FUNCTION(sceImpose, 0F341BE4, sceImposeGetHomePopup, ""),
            HLE_FUNCTION(sceImpose, 24FD7BCF, sceImposeGetLanguageMode, ""),
            HLE_FUNCTION(sceImpose, 36AA6E91, sceImposeSetLanguageMode, ""),
            HLE_FUNCTION(sceImpose, 381BD9E7, sceImposeHomeButton, ""),
            HLE_FUNCTION(sceImpose, 5595A71A, sceImposeSetHomePopup, ""),
            HLE_FUNCTION(sceImpose, 72189C48, sceImposeSetUMDPopup, ""),
            HLE_FUNCTION(sceImpose, 8C943191, sceImposeGetBatteryIconStatus, ""),
            HLE_FUNCTION(sceImpose, 8F6E3518, sceImposeGetBacklightOffTime, ""),
            HLE_FUNCTION(sceImpose, 967F6D4A, sceImposeSetBacklightOffTime, ""),
            HLE_FUNCTION(sceImpose, 9BA61B49, sceImpose_9BA61B49, ""),
            HLE_FUNCTION(sceImpose, A9884B00, sceImpose_A9884B00, ""),
            HLE_FUNCTION(sceImpose, BB3F5DEC, sceImpose_BB3F5DEC, ""),
            HLE_FUNCTION(sceImpose, E0887BC8, sceImposeGetUMDPopup, ""),
            HLE_FUNCTION(sceImpose, FCD44963, sceImpose_FCD44963, ""),
            HLE_FUNCTION(sceImpose, FF1A2F07, sceImpose_FF1A2F07, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// /////////////////////////// Library : sceAudioRouting //////////////////////////
        /// ///
        hle::Function functions_sceAudioRouting[] =
        {
            HLE_FUNCTION(sceAudioRouting, 28235C56, sceAudioRoutingGetVolumeMode, ""),
            HLE_FUNCTION(sceAudioRouting, 36FD8AA9, sceAudioRoutingSetMode, ""),
            HLE_FUNCTION(sceAudioRouting, 39240E7D, sceAudioRoutingGetMode, ""),
            HLE_FUNCTION(sceAudioRouting, BB548475, sceAudioRoutingSetVolumeMode, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceImpose_Driver[] =
        {
            HLE_LIBRARY(sceImpose),
            HLE_LIBRARY(sceAudioRouting)
        };
        static hle::Module module_sceImpose_Driver = HLE_MODULE(sceImpose_Driver);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ///////////////// Module : sceKernelLibrary (usersystemlib.prx) ////////////////
        ///
        /// /////////////////////////// Library : Kernel_Library ///////////////////////////
        /// ///
        hle::Function functions_Kernel_Library[] =
        {
            HLE_FUNCTION(Kernel_Library, 092968F4, sceKernelCpuSuspendIntr, ""),
            HLE_FUNCTION(Kernel_Library, 15B6446B, sceKernelUnlockLwMutex, ""),
            HLE_FUNCTION(Kernel_Library, 1FC64E09, sceKernelLockLwMutexCB, ""),
            HLE_FUNCTION(Kernel_Library, 3B84732D, sceKernelCpuResumeIntrWithSync, "$a0:x"),
            HLE_FUNCTION(Kernel_Library, 47A0B729, sceKernelIsCpuIntrSuspended, "$a0:x"),
            HLE_FUNCTION(Kernel_Library, 5F10D406, sceKernelCpuResumeIntr, "$a0:x"),
            HLE_FUNCTION(Kernel_Library, B55249D2, sceKernelIsCpuIntrEnable, ""),
            HLE_FUNCTION(Kernel_Library, BEA46419, sceKernelLockLwMutex, ""),
            HLE_FUNCTION(Kernel_Library, C1734599, sceKernelReferLwMutexStatus, ""),
            HLE_FUNCTION(Kernel_Library, DC692EE3, sceKernelTryLockLwMutex, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceKernelLibrary[] =
        {
            HLE_LIBRARY(Kernel_Library)
        };
        static hle::Module module_sceKernelLibrary = HLE_MODULE(sceKernelLibrary);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ///////////////////// Module : sceSAScore (sc_sascore.prx) /////////////////////
        ///
        /// ///////////////////////////// Library : sceSasCore /////////////////////////////
        /// ///
        hle::Function functions_sceSasCore[] =
        {
            HLE_FUNCTION(sceSasCore, 42778A9F, __sceSasInit, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(sceSasCore, A3589D81, __sceSasCore, "$a0:x$a1:x"),
            HLE_FUNCTION(sceSasCore, 50A14DFC, __sceSasCoreWithMix, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceSasCore, 76F01ACA, __sceSasSetKeyOn, "$a0:x$a1:x"),
            HLE_FUNCTION(sceSasCore, A0CF2FA4, __sceSasSetKeyOff, "$a0:x$a1:x"),
            HLE_FUNCTION(sceSasCore, 787D04D5, __sceSasSetPause, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, 2C8E6AB3, __sceSasGetPauseFlag, "$a0:x"),
            HLE_FUNCTION(sceSasCore, 440CA7D8, __sceSasSetVolume, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x"),
            HLE_FUNCTION(sceSasCore, AD84D37F, __sceSasSetPitch, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, 99944089, __sceSasSetVoice, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(sceSasCore, B7660A23, __sceSasSetNoise, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, D5EBBBCD, __sceSasSetSteepWave, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, A232CBE6, __sceSasSetTrianglarWave, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, E1CD9561, __sceSasSetVoicePCM, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(sceSasCore, 019B25EB, __sceSasSetADSR, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x$a6:x"),
            HLE_FUNCTION(sceSasCore, 9EC3676A, __sceSasSetADSRmode, "$a0:x$a1:x$a2:x$a3:x$a4:x$a5:x$a6:x"),
            HLE_FUNCTION(sceSasCore, 5F9529F6, __sceSasSetSL, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, CBCD4F79, __sceSasSetSimpleADSR, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceSasCore, 68A46B95, __sceSasGetEndFlag, "$a0:x"),
            HLE_FUNCTION(sceSasCore, 74AE582A, __sceSasGetEnvelopeHeight, "$a0:x$a1:x"),
            HLE_FUNCTION(sceSasCore, 07F58C24, __sceSasGetAllEnvelopeHeights, "$a0:x$a1:x"),
            HLE_FUNCTION(sceSasCore, D1E0A01E, __sceSasSetGrain, "$a0:x$a1:x"),
            HLE_FUNCTION(sceSasCore, BD11B7C2, __sceSasGetGrain, "$a0:x"),
            HLE_FUNCTION(sceSasCore, E855BF76, __sceSasSetOutputmode, "$a0:x$a1:x"),
            HLE_FUNCTION(sceSasCore, E175EF66, __sceSasGetOutputmode, "$a0:x"),
            HLE_FUNCTION(sceSasCore, 33D4AB37, __sceSasRevType, "$a0:x$a1:x"),
            HLE_FUNCTION(sceSasCore, 267A6DD2, __sceSasRevParam, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, D5A229C9, __sceSasRevEVOL, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, F983B186, __sceSasRevVON, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, 4AA9EAD6, __sceSasSetVoiceATRAC3, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceSasCore, 7497EA85, __sceSasConcatenateATRAC3, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceSasCore, F6107F00, __sceSasUnsetATRAC3, "$a0:x$a1:x")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        /// /////////////////////////////// Library : sceP3da //////////////////////////////
        /// ///
        hle::Function functions_sceP3da[] =
        {
            HLE_FUNCTION(sceP3da, 013016F3, sceP3daBridgeCore, ""),
            HLE_FUNCTION(sceP3da, 374500A5, sceP3daBridgeInit, ""),
            HLE_FUNCTION(sceP3da, 43F756A2, sceP3daBridgeExit, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceSAScore[] =
        {
            HLE_LIBRARY(sceSasCore),
            HLE_LIBRARY(sceP3da)
        };
        static hle::Module module_sceSAScore = HLE_MODULE(sceSAScore);
        ///
        ////////////////////////////////////////////////////////////////////////////////

        ////////////// Module : sceATRAC3plus_Library (libatrac3plus.prx) //////////////
        ///
        /// //////////////////////////// Library : sceAtrac3plus ///////////////////////////
        /// ///
        hle::Function functions_sceAtrac3plus[] =
        {
            HLE_FUNCTION(sceAtrac3plus, 780F88D1, sceAtracGetAtracID, "$a0:x"),
            HLE_FUNCTION(sceAtrac3plus, 61EB33F5, sceAtracReleaseAtracID, "$a0:x"),
            HLE_FUNCTION(sceAtrac3plus, 132F1ECA, sceAtracReinit, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, 0E2A73AB, sceAtracSetData, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAtrac3plus, 3F6E26B5, sceAtracSetHalfwayBuffer, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceAtrac3plus, 7A20E7AF, sceAtracSetDataAndGetID, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, 0FAE370E, sceAtracSetHalfwayBufferAndGetID, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAtrac3plus, 6A8C3CD5, sceAtracDecodeData, "$a0:x$a1:x$a2:x$a3:x$a4:x"),
            HLE_FUNCTION(sceAtrac3plus, 5D268707, sceAtracGetStreamDataInfo, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceAtrac3plus, 7DB31251, sceAtracAddStreamData, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, 83E85EA0, sceAtracGetSecondBufferInfo, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAtrac3plus, 83BF7AFD, sceAtracSetSecondBuffer, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAtrac3plus, ECA32A99, sceAtracIsSecondBufferNeeded, "$a0:x"),
            HLE_FUNCTION(sceAtrac3plus, 9AE849A7, sceAtracGetRemainFrame, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, 31668BAA, sceAtracGetChannel, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, B3B5D042, sceAtracGetOutputChannel, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, D6A5F2F7, sceAtracGetMaxSample, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, 36FAABFB, sceAtracGetNextSample, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, A2BBA8BE, sceAtracGetSoundSample, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceAtrac3plus, E23E3A35, sceAtracGetNextDecodePosition, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, A554A158, sceAtracGetBitrate, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, FAA4F89B, sceAtracGetLoopStatus, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAtrac3plus, 868120B5, sceAtracSetLoopNum, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, 2DD3E298, sceAtracGetBufferInfoForResetting, "$a0:x$a1:x$a2:x"),
            HLE_FUNCTION(sceAtrac3plus, 644E5607, sceAtracResetPlayPosition, "$a0:x$a1:x$a2:x$a3:x"),
            HLE_FUNCTION(sceAtrac3plus, E88F759B, sceAtracGetInternalErrorInfo, "$a0:x$a1:x"),
            HLE_FUNCTION(sceAtrac3plus, 5622B7C1, sceAtracSetAA3DataAndGetID, ""),
            HLE_FUNCTION(sceAtrac3plus, 5CF9D852, sceAtracSetMOutHalfwayBuffer, ""),
            HLE_FUNCTION(sceAtrac3plus, 5DD66588, sceAtracSetAA3HalfwayBufferAndGetID, ""),
            HLE_FUNCTION(sceAtrac3plus, CA3CA3D2, sceAtracGetBufferInfoForReseting, ""),
            HLE_FUNCTION(sceAtrac3plus, D1F59FDB, sceAtracStartEntry, ""),
            HLE_FUNCTION(sceAtrac3plus, D5C28CC0, sceAtracEndEntry, ""),
            HLE_FUNCTION(sceAtrac3plus, 9CD7DE03, sceAtracSetMOutHalfwayBufferAndGetID, "")
        };
        /// ///
        /// ////////////////////////////////////////////////////////////////////////////////
        ///
        static hle::Library libraries_sceATRAC3plus_Library[] =
        {
            HLE_LIBRARY(sceAtrac3plus)
        };
        static hle::Module module_sceATRAC3plus_Library = HLE_MODULE(sceATRAC3plus_Library);
        ///
        ////////////////////////////////////////////////////////////////////////////////


        static hle::Module module_array[] =
        {
            module_sceSystemMemoryManager,
            module_sceInterruptManager,
            module_sceThreadManager,
            module_sceIOFileManager,
            module_sceModuleManager,
            module_sceLoadExec,
            module_sceGE_Manager,
            module_sceRTC_Service,
            module_sceAudio_Driver,
            module_sceDisplay_Service,
            module_sceController_Service,
            module_sceHP_Remote_Driver,
            module_scePower_Service,
            module_sceUSB_Driver,
            module_sceOpenPSID_Service,
            module_sceSIRCS_IrDA_Driver,
            module_sceUmd_driver,
            module_sceWlan_Driver,
            module_sceRegistry_Service,
            module_sceUtility_Driver,
            module_sceMesgLed,
            module_sceImpose_Driver,
            module_sceKernelLibrary,
            module_sceSAScore,
            module_sceATRAC3plus_Library
        };

        std::map< std::string, std::map< u32, long > > syscall_map;

        bool Init()
        {
            for (long i = 0; i < long(sizeof_array(module_array)); ++i)
            {
                for (long j = 0; j < long(module_array[i].library_count); ++j)
                {
                    if (!(*module_array[i].library_array[j].init)()) return false;
                    for (long k = 0; k < long(module_array[i].library_array[j].function_count); ++k)
                    {
                        syscall_map[module_array[i].library_array[j].name][module_array[i].library_array[j].function_array[k].nid] = (i << 19) | (j << 16) | (k << 6);
                    }
                }
            }
            return true;
        }

        bool Fini()
        {
            for (long i = long(sizeof_array(module_array))-1; i >= 0; --i)
            {
                for (long j = long(module_array[i].library_count)-1; j >= 0; --j)
                {
                    if (!(*module_array[i].library_array[j].fini)()) return false;
                    syscall_map.erase(module_array[i].library_array[j].name);
                }
            }
            return true;
        }

        Function * GetModuleFunction(u32 opcode)
        {
            u32 function_id = (opcode >>  6) & 0x000001FF; // up to 511 functions per library
            if (function_id != 0x1FF)
            {
                u32 library_id = (opcode >> 16) & 0x00000007; // up to 7 libraries per module
                if (library_id != 0x7)
                {
                    u32 module_id = (opcode >> 19) & 0x0000003F; // up to 127 modules
                    if (module_id != 0x3F)
                    {
                        if (module_id < sizeof_array(module_array) && library_id < module_array[module_id].library_count && function_id < module_array[module_id].library_array[library_id].function_count)
                        {
                            return module_array[module_id].library_array[library_id].function_array + function_id;
                        }
                    }
                }
            }
            return 0;
        }

        void WriteSyscall(char const * library_name, u32 nid, u32 address)
        {
            if (nid == 0)
            {
                ((p32u32)address)[0] = 0x03E00008; // JR $RA
                ((p32u32)address)[1] = 0x00000000; // NOP
                return;
            }
            auto library = syscall_map.find(library_name);
            if (library != syscall_map.end())
            {
                auto function = library->second.find(nid);
                if (function != library->second.end())
                {
                    ((p32u32)address)[0] = 0x03E00008; // JR $RA
                    ((p32u32)address)[1] = 0x0000000C | u32(function->second);
                    return;
                }
            }
            ((p32u32)address)[0] = 0x03E00008; // JR $RA
            ((p32u32)address)[1] = 0x03FFFFCC; // invalid syscall
        }

        char const * GetSyscallName(char const * library_name, u32 nid)
        {
            if (nid == 0)
            {
                return "---";
            }
            auto library = syscall_map.find(library_name);
            if (library != syscall_map.end())
            {
                auto function = library->second.find(nid);
                if (function != library->second.end())
                {
                    u32 function_id = (function->second >>  6) & 0x000001FF; // up to 511 functions per library
                    u32 library_id  = (function->second >> 16) & 0x00000007; // up to 7 libraries per module
                    u32 module_id   = (function->second >> 19) & 0x0000003F; // up to 127 modules
                    return module_array[module_id].library_array[library_id].function_array[function_id].name;
                }
            }
            return "???";
        }
    }
}

namespace emu
{
    namespace log
    {
        Category syscalls("syscalls");
        /**/SubCategory syscall_sysmem_prx                                      (syscalls, "sysmem.prx");
        /**  **/SubCategory syscall_SysMemUserForUser                               (syscall_sysmem_prx, "SysMemUserForUser");
        /**  **  **/SubCategory syscall_sceKernelMaxFreeMemSize                         (syscall_SysMemUserForUser, "sceKernelMaxFreeMemSize");
        /**  **  **/SubCategory syscall_sceKernelTotalFreeMemSize                       (syscall_SysMemUserForUser, "sceKernelTotalFreeMemSize");
        /**  **  **/SubCategory syscall_sceKernelPrintf                                 (syscall_SysMemUserForUser, "sceKernelPrintf");
        /**  **  **/SubCategory syscall_sceKernelSetCompilerVersion                     (syscall_SysMemUserForUser, "sceKernelSetCompilerVersion");
        /**  **  **/SubCategory syscall_sceKernelSetCompiledSdkVersion                  (syscall_SysMemUserForUser, "sceKernelSetCompiledSdkVersion");
        /**  **  **/SubCategory syscall_sceKernelDevkitVersion                          (syscall_SysMemUserForUser, "sceKernelDevkitVersion");
        /**  **  **/SubCategory syscall_sceKernelGetCompiledSdkVersion                  (syscall_SysMemUserForUser, "sceKernelGetCompiledSdkVersion");
        /**  **  **/SubCategory syscall_sceKernelAllocPartitionMemory                   (syscall_SysMemUserForUser, "sceKernelAllocPartitionMemory");
        /**  **  **/SubCategory syscall_sceKernelFreePartitionMemory                    (syscall_SysMemUserForUser, "sceKernelFreePartitionMemory");
        /**  **  **/SubCategory syscall_sceKernelGetBlockHeadAddr                       (syscall_SysMemUserForUser, "sceKernelGetBlockHeadAddr");
        /**  **  **/SubCategory syscall_sceKernelQueryMemoryInfo                        (syscall_SysMemUserForUser, "sceKernelQueryMemoryInfo");
        /**  **  **/SubCategory syscall_SysMemUserForUser_057E7380                      (syscall_SysMemUserForUser, "SysMemUserForUser_057E7380");
        /**  **  **/SubCategory syscall_SysMemUserForUser_315AD3A0                      (syscall_SysMemUserForUser, "SysMemUserForUser_315AD3A0");
        /**  **  **/SubCategory syscall_SysMemUserForUser_342061E5                      (syscall_SysMemUserForUser, "SysMemUserForUser_342061E5");
        /**  **  **/SubCategory syscall_SysMemUserForUser_50F61D8A                      (syscall_SysMemUserForUser, "SysMemUserForUser_50F61D8A");
        /**  **  **/SubCategory syscall_SysMemUserForUser_91DE343C                      (syscall_SysMemUserForUser, "SysMemUserForUser_91DE343C");
        /**  **  **/SubCategory syscall_SysMemUserForUser_A6848DF8                      (syscall_SysMemUserForUser, "SysMemUserForUser_A6848DF8");
        /**  **  **/SubCategory syscall_SysMemUserForUser_ACBD88CA                      (syscall_SysMemUserForUser, "SysMemUserForUser_ACBD88CA");
        /**  **  **/SubCategory syscall_SysMemUserForUser_D8DE5C1E                      (syscall_SysMemUserForUser, "SysMemUserForUser_D8DE5C1E");
        /**  **  **/SubCategory syscall_SysMemUserForUser_DB83A952                      (syscall_SysMemUserForUser, "SysMemUserForUser_DB83A952");
        /**  **  **/SubCategory syscall_SysMemUserForUser_EBD5C3E6                      (syscall_SysMemUserForUser, "SysMemUserForUser_EBD5C3E6");
        /**  **  **/SubCategory syscall_SysMemUserForUser_FE707FDF                      (syscall_SysMemUserForUser, "SysMemUserForUser_FE707FDF");
        /**  **/SubCategory syscall_sceSuspendForUser                               (syscall_sysmem_prx, "sceSuspendForUser");
        /**  **  **/SubCategory syscall_sceKernelPowerLock                              (syscall_sceSuspendForUser, "sceKernelPowerLock");
        /**  **  **/SubCategory syscall_sceKernelPowerUnlock                            (syscall_sceSuspendForUser, "sceKernelPowerUnlock");
        /**  **  **/SubCategory syscall_sceKernelPowerTick                              (syscall_sceSuspendForUser, "sceKernelPowerTick");
        /**  **  **/SubCategory syscall_sceKernelVolatileMemLock                        (syscall_sceSuspendForUser, "sceKernelVolatileMemLock");
        /**  **  **/SubCategory syscall_sceKernelVolatileMemTryLock                     (syscall_sceSuspendForUser, "sceKernelVolatileMemTryLock");
        /**  **  **/SubCategory syscall_sceKernelVolatileMemUnlock                      (syscall_sceSuspendForUser, "sceKernelVolatileMemUnlock");
        /**  **/SubCategory syscall_UtilsForUser                                    (syscall_sysmem_prx, "UtilsForUser");
        /**  **  **/SubCategory syscall_sceKernelDcacheWritebackAll                     (syscall_UtilsForUser, "sceKernelDcacheWritebackAll");
        /**  **  **/SubCategory syscall_sceKernelDcacheWritebackInvalidateAll           (syscall_UtilsForUser, "sceKernelDcacheWritebackInvalidateAll");
        /**  **  **/SubCategory syscall_sceKernelDcacheWritebackRange                   (syscall_UtilsForUser, "sceKernelDcacheWritebackRange");
        /**  **  **/SubCategory syscall_sceKernelDcacheWritebackInvalidateRange         (syscall_UtilsForUser, "sceKernelDcacheWritebackInvalidateRange");
        /**  **  **/SubCategory syscall_sceKernelDcacheInvalidateRange                  (syscall_UtilsForUser, "sceKernelDcacheInvalidateRange");
        /**  **  **/SubCategory syscall_sceKernelDcacheProbe                            (syscall_UtilsForUser, "sceKernelDcacheProbe");
        /**  **  **/SubCategory syscall_sceKernelDcacheProbeRange                       (syscall_UtilsForUser, "sceKernelDcacheProbeRange");
        /**  **  **/SubCategory syscall_sceKernelDcacheReadTag                          (syscall_UtilsForUser, "sceKernelDcacheReadTag");
        /**  **  **/SubCategory syscall_sceKernelIcacheInvalidateAll                    (syscall_UtilsForUser, "sceKernelIcacheInvalidateAll");
        /**  **  **/SubCategory syscall_sceKernelIcacheInvalidateRange                  (syscall_UtilsForUser, "sceKernelIcacheInvalidateRange");
        /**  **  **/SubCategory syscall_sceKernelIcacheProbe                            (syscall_UtilsForUser, "sceKernelIcacheProbe");
        /**  **  **/SubCategory syscall_sceKernelIcacheReadTag                          (syscall_UtilsForUser, "sceKernelIcacheReadTag");
        /**  **  **/SubCategory syscall_sceKernelUtilsMd5Digest                         (syscall_UtilsForUser, "sceKernelUtilsMd5Digest");
        /**  **  **/SubCategory syscall_sceKernelUtilsMd5BlockInit                      (syscall_UtilsForUser, "sceKernelUtilsMd5BlockInit");
        /**  **  **/SubCategory syscall_sceKernelUtilsMd5BlockUpdate                    (syscall_UtilsForUser, "sceKernelUtilsMd5BlockUpdate");
        /**  **  **/SubCategory syscall_sceKernelUtilsMd5BlockResult                    (syscall_UtilsForUser, "sceKernelUtilsMd5BlockResult");
        /**  **  **/SubCategory syscall_sceKernelUtilsSha1Digest                        (syscall_UtilsForUser, "sceKernelUtilsSha1Digest");
        /**  **  **/SubCategory syscall_sceKernelUtilsSha1BlockInit                     (syscall_UtilsForUser, "sceKernelUtilsSha1BlockInit");
        /**  **  **/SubCategory syscall_sceKernelUtilsSha1BlockUpdate                   (syscall_UtilsForUser, "sceKernelUtilsSha1BlockUpdate");
        /**  **  **/SubCategory syscall_sceKernelUtilsSha1BlockResult                   (syscall_UtilsForUser, "sceKernelUtilsSha1BlockResult");
        /**  **  **/SubCategory syscall_sceKernelUtilsMt19937Init                       (syscall_UtilsForUser, "sceKernelUtilsMt19937Init");
        /**  **  **/SubCategory syscall_sceKernelUtilsMt19937UInt                       (syscall_UtilsForUser, "sceKernelUtilsMt19937UInt");
        /**  **  **/SubCategory syscall_sceKernelGetGPI                                 (syscall_UtilsForUser, "sceKernelGetGPI");
        /**  **  **/SubCategory syscall_sceKernelSetGPO                                 (syscall_UtilsForUser, "sceKernelSetGPO");
        /**  **  **/SubCategory syscall_sceKernelLibcClock                              (syscall_UtilsForUser, "sceKernelLibcClock");
        /**  **  **/SubCategory syscall_sceKernelLibcTime                               (syscall_UtilsForUser, "sceKernelLibcTime");
        /**  **  **/SubCategory syscall_sceKernelLibcGettimeofday                       (syscall_UtilsForUser, "sceKernelLibcGettimeofday");
        /**  **  **/SubCategory syscall_sceKernelPutUserLog                             (syscall_UtilsForUser, "sceKernelPutUserLog");
        /**  **  **/SubCategory syscall_UtilsForUser_004D4DEE                           (syscall_UtilsForUser, "UtilsForUser_004D4DEE");
        /**  **  **/SubCategory syscall_UtilsForUser_157A383A                           (syscall_UtilsForUser, "UtilsForUser_157A383A");
        /**  **  **/SubCategory syscall_UtilsForUser_1B0592A3                           (syscall_UtilsForUser, "UtilsForUser_1B0592A3");
        /**  **  **/SubCategory syscall_UtilsForUser_39F49610                           (syscall_UtilsForUser, "UtilsForUser_39F49610");
        /**  **  **/SubCategory syscall_UtilsForUser_3FD3D324                           (syscall_UtilsForUser, "UtilsForUser_3FD3D324");
        /**  **  **/SubCategory syscall_UtilsForUser_43C9A8DB                           (syscall_UtilsForUser, "UtilsForUser_43C9A8DB");
        /**  **  **/SubCategory syscall_UtilsForUser_515B4FAF                           (syscall_UtilsForUser, "UtilsForUser_515B4FAF");
        /**  **  **/SubCategory syscall_UtilsForUser_5C7F2B1A                           (syscall_UtilsForUser, "UtilsForUser_5C7F2B1A");
        /**  **  **/SubCategory syscall_UtilsForUser_6231A71D                           (syscall_UtilsForUser, "UtilsForUser_6231A71D");
        /**  **  **/SubCategory syscall_UtilsForUser_7333E539                           (syscall_UtilsForUser, "UtilsForUser_7333E539");
        /**  **  **/SubCategory syscall_UtilsForUser_740DF7F0                           (syscall_UtilsForUser, "UtilsForUser_740DF7F0");
        /**  **  **/SubCategory syscall_UtilsForUser_99134C3F                           (syscall_UtilsForUser, "UtilsForUser_99134C3F");
        /**  **  **/SubCategory syscall_UtilsForUser_AF3766BB                           (syscall_UtilsForUser, "UtilsForUser_AF3766BB");
        /**  **  **/SubCategory syscall_UtilsForUser_B83A1E76                           (syscall_UtilsForUser, "UtilsForUser_B83A1E76");
        /**  **  **/SubCategory syscall_UtilsForUser_DBBE9A46                           (syscall_UtilsForUser, "UtilsForUser_DBBE9A46");
        /**  **  **/SubCategory syscall_UtilsForUser_F0155BCA                           (syscall_UtilsForUser, "UtilsForUser_F0155BCA");
        /**/SubCategory syscall_interruptman_prx                                (syscalls, "interruptman.prx");
        /**  **/SubCategory syscall_InterruptManager                                (syscall_interruptman_prx, "InterruptManager");
        /**  **  **/SubCategory syscall_sceKernelRegisterSubIntrHandler                 (syscall_InterruptManager, "sceKernelRegisterSubIntrHandler");
        /**  **  **/SubCategory syscall_sceKernelReleaseSubIntrHandler                  (syscall_InterruptManager, "sceKernelReleaseSubIntrHandler");
        /**  **  **/SubCategory syscall_sceKernelRegisterUserSpaceIntrStack             (syscall_InterruptManager, "sceKernelRegisterUserSpaceIntrStack");
        /**  **  **/SubCategory syscall_sceKernelEnableSubIntr                          (syscall_InterruptManager, "sceKernelEnableSubIntr");
        /**  **  **/SubCategory syscall_sceKernelDisableSubIntr                         (syscall_InterruptManager, "sceKernelDisableSubIntr");
        /**  **  **/SubCategory syscall_sceKernelSuspendSubIntr                         (syscall_InterruptManager, "sceKernelSuspendSubIntr");
        /**  **  **/SubCategory syscall_sceKernelResumeSubIntr                          (syscall_InterruptManager, "sceKernelResumeSubIntr");
        /**  **  **/SubCategory syscall_sceKernelIsSubInterruptOccurred                 (syscall_InterruptManager, "sceKernelIsSubInterruptOccurred");
        /**  **  **/SubCategory syscall_QueryIntrHandlerInfo                            (syscall_InterruptManager, "QueryIntrHandlerInfo");
        /**/SubCategory syscall_threadman_prx                                   (syscalls, "threadman.prx");
        /**  **/SubCategory syscall_ThreadManForUser                                (syscall_threadman_prx, "ThreadManForUser");
        /**  **  **/SubCategory syscall_sceKernelCreateThread                           (syscall_ThreadManForUser, "sceKernelCreateThread");
        /**  **  **/SubCategory syscall_sceKernelDeleteThread                           (syscall_ThreadManForUser, "sceKernelDeleteThread");
        /**  **  **/SubCategory syscall_sceKernelStartThread                            (syscall_ThreadManForUser, "sceKernelStartThread");
        /**  **  **/SubCategory syscall_sceKernelExitThread                             (syscall_ThreadManForUser, "sceKernelExitThread");
        /**  **  **/SubCategory syscall_sceKernelExitDeleteThread                       (syscall_ThreadManForUser, "sceKernelExitDeleteThread");
        /**  **  **/SubCategory syscall_sceKernelTerminateThread                        (syscall_ThreadManForUser, "sceKernelTerminateThread");
        /**  **  **/SubCategory syscall_sceKernelTerminateDeleteThread                  (syscall_ThreadManForUser, "sceKernelTerminateDeleteThread");
        /**  **  **/SubCategory syscall_sceKernelSuspendDispatchThread                  (syscall_ThreadManForUser, "sceKernelSuspendDispatchThread");
        /**  **  **/SubCategory syscall_sceKernelResumeDispatchThread                   (syscall_ThreadManForUser, "sceKernelResumeDispatchThread");
        /**  **  **/SubCategory syscall_sceKernelChangeCurrentThreadAttr                (syscall_ThreadManForUser, "sceKernelChangeCurrentThreadAttr");
        /**  **  **/SubCategory syscall_sceKernelChangeThreadPriority                   (syscall_ThreadManForUser, "sceKernelChangeThreadPriority");
        /**  **  **/SubCategory syscall_sceKernelRotateThreadReadyQueue                 (syscall_ThreadManForUser, "sceKernelRotateThreadReadyQueue");
        /**  **  **/SubCategory syscall_sceKernelReleaseWaitThread                      (syscall_ThreadManForUser, "sceKernelReleaseWaitThread");
        /**  **  **/SubCategory syscall_sceKernelGetThreadId                            (syscall_ThreadManForUser, "sceKernelGetThreadId");
        /**  **  **/SubCategory syscall_sceKernelGetThreadCurrentPriority               (syscall_ThreadManForUser, "sceKernelGetThreadCurrentPriority");
        /**  **  **/SubCategory syscall_sceKernelGetThreadExitStatus                    (syscall_ThreadManForUser, "sceKernelGetThreadExitStatus");
        /**  **  **/SubCategory syscall_sceKernelReferThreadStatus                      (syscall_ThreadManForUser, "sceKernelReferThreadStatus");
        /**  **  **/SubCategory syscall_sceKernelReferThreadRunStatus                   (syscall_ThreadManForUser, "sceKernelReferThreadRunStatus");
        /**  **  **/SubCategory syscall_sceKernelCheckThreadStack                       (syscall_ThreadManForUser, "sceKernelCheckThreadStack");
        /**  **  **/SubCategory syscall_sceKernelGetThreadStackFreeSize                 (syscall_ThreadManForUser, "sceKernelGetThreadStackFreeSize");
        /**  **  **/SubCategory syscall__sceKernelStartThread                           (syscall_ThreadManForUser, "_sceKernelStartThread");
        /**  **  **/SubCategory syscall__sceKernelExitThread                            (syscall_ThreadManForUser, "_sceKernelExitThread");
        /**  **  **/SubCategory syscall__sceKernelIdleThread                            (syscall_ThreadManForUser, "_sceKernelIdleThread");
        /**  **  **/SubCategory syscall_sceKernelRegisterThreadEventHandler             (syscall_ThreadManForUser, "sceKernelRegisterThreadEventHandler");
        /**  **  **/SubCategory syscall_sceKernelReleaseThreadEventHandler              (syscall_ThreadManForUser, "sceKernelReleaseThreadEventHandler");
        /**  **  **/SubCategory syscall_sceKernelReferThreadEventHandlerStatus          (syscall_ThreadManForUser, "sceKernelReferThreadEventHandlerStatus");
        /**  **  **/SubCategory syscall_sceKernelSleepThread                            (syscall_ThreadManForUser, "sceKernelSleepThread");
        /**  **  **/SubCategory syscall_sceKernelSleepThreadCB                          (syscall_ThreadManForUser, "sceKernelSleepThreadCB");
        /**  **  **/SubCategory syscall_sceKernelWakeupThread                           (syscall_ThreadManForUser, "sceKernelWakeupThread");
        /**  **  **/SubCategory syscall_sceKernelCancelWakeupThread                     (syscall_ThreadManForUser, "sceKernelCancelWakeupThread");
        /**  **  **/SubCategory syscall_sceKernelSuspendThread                          (syscall_ThreadManForUser, "sceKernelSuspendThread");
        /**  **  **/SubCategory syscall_sceKernelResumeThread                           (syscall_ThreadManForUser, "sceKernelResumeThread");
        /**  **  **/SubCategory syscall_sceKernelWaitThreadEnd                          (syscall_ThreadManForUser, "sceKernelWaitThreadEnd");
        /**  **  **/SubCategory syscall_sceKernelWaitThreadEndCB                        (syscall_ThreadManForUser, "sceKernelWaitThreadEndCB");
        /**  **  **/SubCategory syscall_sceKernelCreateSema                             (syscall_ThreadManForUser, "sceKernelCreateSema");
        /**  **  **/SubCategory syscall_sceKernelDeleteSema                             (syscall_ThreadManForUser, "sceKernelDeleteSema");
        /**  **  **/SubCategory syscall_sceKernelSignalSema                             (syscall_ThreadManForUser, "sceKernelSignalSema");
        /**  **  **/SubCategory syscall_sceKernelWaitSema                               (syscall_ThreadManForUser, "sceKernelWaitSema");
        /**  **  **/SubCategory syscall_sceKernelWaitSemaCB                             (syscall_ThreadManForUser, "sceKernelWaitSemaCB");
        /**  **  **/SubCategory syscall_sceKernelPollSema                               (syscall_ThreadManForUser, "sceKernelPollSema");
        /**  **  **/SubCategory syscall_sceKernelCancelSema                             (syscall_ThreadManForUser, "sceKernelCancelSema");
        /**  **  **/SubCategory syscall_sceKernelReferSemaStatus                        (syscall_ThreadManForUser, "sceKernelReferSemaStatus");
        /**  **  **/SubCategory syscall_sceKernelCreateEventFlag                        (syscall_ThreadManForUser, "sceKernelCreateEventFlag");
        /**  **  **/SubCategory syscall_sceKernelDeleteEventFlag                        (syscall_ThreadManForUser, "sceKernelDeleteEventFlag");
        /**  **  **/SubCategory syscall_sceKernelSetEventFlag                           (syscall_ThreadManForUser, "sceKernelSetEventFlag");
        /**  **  **/SubCategory syscall_sceKernelClearEventFlag                         (syscall_ThreadManForUser, "sceKernelClearEventFlag");
        /**  **  **/SubCategory syscall_sceKernelWaitEventFlag                          (syscall_ThreadManForUser, "sceKernelWaitEventFlag");
        /**  **  **/SubCategory syscall_sceKernelWaitEventFlagCB                        (syscall_ThreadManForUser, "sceKernelWaitEventFlagCB");
        /**  **  **/SubCategory syscall_sceKernelPollEventFlag                          (syscall_ThreadManForUser, "sceKernelPollEventFlag");
        /**  **  **/SubCategory syscall_sceKernelCancelEventFlag                        (syscall_ThreadManForUser, "sceKernelCancelEventFlag");
        /**  **  **/SubCategory syscall_sceKernelReferEventFlagStatus                   (syscall_ThreadManForUser, "sceKernelReferEventFlagStatus");
        /**  **  **/SubCategory syscall_sceKernelCreateMbx                              (syscall_ThreadManForUser, "sceKernelCreateMbx");
        /**  **  **/SubCategory syscall_sceKernelDeleteMbx                              (syscall_ThreadManForUser, "sceKernelDeleteMbx");
        /**  **  **/SubCategory syscall_sceKernelSendMbx                                (syscall_ThreadManForUser, "sceKernelSendMbx");
        /**  **  **/SubCategory syscall_sceKernelReceiveMbx                             (syscall_ThreadManForUser, "sceKernelReceiveMbx");
        /**  **  **/SubCategory syscall_sceKernelReceiveMbxCB                           (syscall_ThreadManForUser, "sceKernelReceiveMbxCB");
        /**  **  **/SubCategory syscall_sceKernelPollMbx                                (syscall_ThreadManForUser, "sceKernelPollMbx");
        /**  **  **/SubCategory syscall_sceKernelCancelReceiveMbx                       (syscall_ThreadManForUser, "sceKernelCancelReceiveMbx");
        /**  **  **/SubCategory syscall_sceKernelReferMbxStatus                         (syscall_ThreadManForUser, "sceKernelReferMbxStatus");
        /**  **  **/SubCategory syscall_sceKernelCreateMsgPipe                          (syscall_ThreadManForUser, "sceKernelCreateMsgPipe");
        /**  **  **/SubCategory syscall_sceKernelDeleteMsgPipe                          (syscall_ThreadManForUser, "sceKernelDeleteMsgPipe");
        /**  **  **/SubCategory syscall_sceKernelSendMsgPipe                            (syscall_ThreadManForUser, "sceKernelSendMsgPipe");
        /**  **  **/SubCategory syscall_sceKernelSendMsgPipeCB                          (syscall_ThreadManForUser, "sceKernelSendMsgPipeCB");
        /**  **  **/SubCategory syscall_sceKernelTrySendMsgPipe                         (syscall_ThreadManForUser, "sceKernelTrySendMsgPipe");
        /**  **  **/SubCategory syscall_sceKernelReceiveMsgPipe                         (syscall_ThreadManForUser, "sceKernelReceiveMsgPipe");
        /**  **  **/SubCategory syscall_sceKernelReceiveMsgPipeCB                       (syscall_ThreadManForUser, "sceKernelReceiveMsgPipeCB");
        /**  **  **/SubCategory syscall_sceKernelTryReceiveMsgPipe                      (syscall_ThreadManForUser, "sceKernelTryReceiveMsgPipe");
        /**  **  **/SubCategory syscall_sceKernelCancelMsgPipe                          (syscall_ThreadManForUser, "sceKernelCancelMsgPipe");
        /**  **  **/SubCategory syscall_sceKernelReferMsgPipeStatus                     (syscall_ThreadManForUser, "sceKernelReferMsgPipeStatus");
        /**  **  **/SubCategory syscall_sceKernelCreateVpl                              (syscall_ThreadManForUser, "sceKernelCreateVpl");
        /**  **  **/SubCategory syscall_sceKernelDeleteVpl                              (syscall_ThreadManForUser, "sceKernelDeleteVpl");
        /**  **  **/SubCategory syscall_sceKernelAllocateVpl                            (syscall_ThreadManForUser, "sceKernelAllocateVpl");
        /**  **  **/SubCategory syscall_sceKernelAllocateVplCB                          (syscall_ThreadManForUser, "sceKernelAllocateVplCB");
        /**  **  **/SubCategory syscall_sceKernelTryAllocateVpl                         (syscall_ThreadManForUser, "sceKernelTryAllocateVpl");
        /**  **  **/SubCategory syscall_sceKernelFreeVpl                                (syscall_ThreadManForUser, "sceKernelFreeVpl");
        /**  **  **/SubCategory syscall_sceKernelCancelVpl                              (syscall_ThreadManForUser, "sceKernelCancelVpl");
        /**  **  **/SubCategory syscall_sceKernelReferVplStatus                         (syscall_ThreadManForUser, "sceKernelReferVplStatus");
        /**  **  **/SubCategory syscall_sceKernelCreateFpl                              (syscall_ThreadManForUser, "sceKernelCreateFpl");
        /**  **  **/SubCategory syscall_sceKernelDeleteFpl                              (syscall_ThreadManForUser, "sceKernelDeleteFpl");
        /**  **  **/SubCategory syscall_sceKernelAllocateFpl                            (syscall_ThreadManForUser, "sceKernelAllocateFpl");
        /**  **  **/SubCategory syscall_sceKernelAllocateFplCB                          (syscall_ThreadManForUser, "sceKernelAllocateFplCB");
        /**  **  **/SubCategory syscall_sceKernelTryAllocateFpl                         (syscall_ThreadManForUser, "sceKernelTryAllocateFpl");
        /**  **  **/SubCategory syscall_sceKernelFreeFpl                                (syscall_ThreadManForUser, "sceKernelFreeFpl");
        /**  **  **/SubCategory syscall_sceKernelCancelFpl                              (syscall_ThreadManForUser, "sceKernelCancelFpl");
        /**  **  **/SubCategory syscall_sceKernelReferFplStatus                         (syscall_ThreadManForUser, "sceKernelReferFplStatus");
        /**  **  **/SubCategory syscall_sceKernelGetSystemTime                          (syscall_ThreadManForUser, "sceKernelGetSystemTime");
        /**  **  **/SubCategory syscall_sceKernelGetSystemTimeWide                      (syscall_ThreadManForUser, "sceKernelGetSystemTimeWide");
        /**  **  **/SubCategory syscall_sceKernelGetSystemTimeLow                       (syscall_ThreadManForUser, "sceKernelGetSystemTimeLow");
        /**  **  **/SubCategory syscall_sceKernelUSec2SysClock                          (syscall_ThreadManForUser, "sceKernelUSec2SysClock");
        /**  **  **/SubCategory syscall_sceKernelSysClock2USec                          (syscall_ThreadManForUser, "sceKernelSysClock2USec");
        /**  **  **/SubCategory syscall_sceKernelUSec2SysClockWide                      (syscall_ThreadManForUser, "sceKernelUSec2SysClockWide");
        /**  **  **/SubCategory syscall_sceKernelSysClock2USecWide                      (syscall_ThreadManForUser, "sceKernelSysClock2USecWide");
        /**  **  **/SubCategory syscall_sceKernelDelayThread                            (syscall_ThreadManForUser, "sceKernelDelayThread");
        /**  **  **/SubCategory syscall_sceKernelDelayThreadCB                          (syscall_ThreadManForUser, "sceKernelDelayThreadCB");
        /**  **  **/SubCategory syscall_sceKernelDelaySysClockThread                    (syscall_ThreadManForUser, "sceKernelDelaySysClockThread");
        /**  **  **/SubCategory syscall_sceKernelDelaySysClockThreadCB                  (syscall_ThreadManForUser, "sceKernelDelaySysClockThreadCB");
        /**  **  **/SubCategory syscall_sceKernelSetAlarm                               (syscall_ThreadManForUser, "sceKernelSetAlarm");
        /**  **  **/SubCategory syscall_sceKernelSetSysClockAlarm                       (syscall_ThreadManForUser, "sceKernelSetSysClockAlarm");
        /**  **  **/SubCategory syscall_sceKernelCancelAlarm                            (syscall_ThreadManForUser, "sceKernelCancelAlarm");
        /**  **  **/SubCategory syscall_sceKernelReferAlarmStatus                       (syscall_ThreadManForUser, "sceKernelReferAlarmStatus");
        /**  **  **/SubCategory syscall_sceKernelCreateVTimer                           (syscall_ThreadManForUser, "sceKernelCreateVTimer");
        /**  **  **/SubCategory syscall_sceKernelDeleteVTimer                           (syscall_ThreadManForUser, "sceKernelDeleteVTimer");
        /**  **  **/SubCategory syscall_sceKernelGetVTimerBase                          (syscall_ThreadManForUser, "sceKernelGetVTimerBase");
        /**  **  **/SubCategory syscall_sceKernelGetVTimerTime                          (syscall_ThreadManForUser, "sceKernelGetVTimerTime");
        /**  **  **/SubCategory syscall_sceKernelSetVTimerTime                          (syscall_ThreadManForUser, "sceKernelSetVTimerTime");
        /**  **  **/SubCategory syscall_sceKernelStartVTimer                            (syscall_ThreadManForUser, "sceKernelStartVTimer");
        /**  **  **/SubCategory syscall_sceKernelStopVTimer                             (syscall_ThreadManForUser, "sceKernelStopVTimer");
        /**  **  **/SubCategory syscall_sceKernelSetVTimerHandler                       (syscall_ThreadManForUser, "sceKernelSetVTimerHandler");
        /**  **  **/SubCategory syscall_sceKernelCancelVTimerHandler                    (syscall_ThreadManForUser, "sceKernelCancelVTimerHandler");
        /**  **  **/SubCategory syscall_sceKernelGetVTimerBaseWide                      (syscall_ThreadManForUser, "sceKernelGetVTimerBaseWide");
        /**  **  **/SubCategory syscall_sceKernelGetVTimerTimeWide                      (syscall_ThreadManForUser, "sceKernelGetVTimerTimeWide");
        /**  **  **/SubCategory syscall_sceKernelSetVTimerTimeWide                      (syscall_ThreadManForUser, "sceKernelSetVTimerTimeWide");
        /**  **  **/SubCategory syscall_sceKernelSetVTimerHandlerWide                   (syscall_ThreadManForUser, "sceKernelSetVTimerHandlerWide");
        /**  **  **/SubCategory syscall_sceKernelReferVTimerStatus                      (syscall_ThreadManForUser, "sceKernelReferVTimerStatus");
        /**  **  **/SubCategory syscall__sceKernelReturnFromTimerHandler                (syscall_ThreadManForUser, "_sceKernelReturnFromTimerHandler");
        /**  **  **/SubCategory syscall_sceKernelCreateCallback                         (syscall_ThreadManForUser, "sceKernelCreateCallback");
        /**  **  **/SubCategory syscall_sceKernelDeleteCallback                         (syscall_ThreadManForUser, "sceKernelDeleteCallback");
        /**  **  **/SubCategory syscall_sceKernelNotifyCallback                         (syscall_ThreadManForUser, "sceKernelNotifyCallback");
        /**  **  **/SubCategory syscall_sceKernelCancelCallback                         (syscall_ThreadManForUser, "sceKernelCancelCallback");
        /**  **  **/SubCategory syscall_sceKernelGetCallbackCount                       (syscall_ThreadManForUser, "sceKernelGetCallbackCount");
        /**  **  **/SubCategory syscall_sceKernelCheckCallback                          (syscall_ThreadManForUser, "sceKernelCheckCallback");
        /**  **  **/SubCategory syscall_sceKernelReferCallbackStatus                    (syscall_ThreadManForUser, "sceKernelReferCallbackStatus");
        /**  **  **/SubCategory syscall__sceKernelReturnFromCallback                    (syscall_ThreadManForUser, "_sceKernelReturnFromCallback");
        /**  **  **/SubCategory syscall_sceKernelReferSystemStatus                      (syscall_ThreadManForUser, "sceKernelReferSystemStatus");
        /**  **  **/SubCategory syscall_sceKernelGetThreadmanIdList                     (syscall_ThreadManForUser, "sceKernelGetThreadmanIdList");
        /**  **  **/SubCategory syscall_sceKernelGetThreadmanIdType                     (syscall_ThreadManForUser, "sceKernelGetThreadmanIdType");
        /**  **  **/SubCategory syscall_sceKernelCreateMutex                            (syscall_ThreadManForUser, "sceKernelCreateMutex");
        /**  **  **/SubCategory syscall_sceKernelDeleteMutex                            (syscall_ThreadManForUser, "sceKernelDeleteMutex");
        /**  **  **/SubCategory syscall_sceKernelLockMutex                              (syscall_ThreadManForUser, "sceKernelLockMutex");
        /**  **  **/SubCategory syscall_sceKernelLockMutexCB                            (syscall_ThreadManForUser, "sceKernelLockMutexCB");
        /**  **  **/SubCategory syscall_sceKernelTryLockMutex                           (syscall_ThreadManForUser, "sceKernelTryLockMutex");
        /**  **  **/SubCategory syscall_sceKernelUnlockMutex                            (syscall_ThreadManForUser, "sceKernelUnlockMutex");
        /**  **  **/SubCategory syscall_sceKernelCancelMutex                            (syscall_ThreadManForUser, "sceKernelCancelMutex");
        /**  **  **/SubCategory syscall_sceKernelReferMutexStatus                       (syscall_ThreadManForUser, "sceKernelReferMutexStatus");
        /**  **  **/SubCategory syscall_sceKernelCreateLwMutex                          (syscall_ThreadManForUser, "sceKernelCreateLwMutex");
        /**  **  **/SubCategory syscall_sceKernelDeleteLwMutex                          (syscall_ThreadManForUser, "sceKernelDeleteLwMutex");
        /**  **  **/SubCategory syscall_sceKernelReferLwMutexStatusByID                 (syscall_ThreadManForUser, "sceKernelReferLwMutexStatusByID");
        /**  **  **/SubCategory syscall_sceKernelReferThreadProfiler                    (syscall_ThreadManForUser, "sceKernelReferThreadProfiler");
        /**  **  **/SubCategory syscall_sceKernelReferGlobalProfiler                    (syscall_ThreadManForUser, "sceKernelReferGlobalProfiler");
        /**  **  **/SubCategory syscall_sceKernelDonateWakeupThread                     (syscall_ThreadManForUser, "sceKernelDonateWakeupThread");
        /**  **  **/SubCategory syscall_ThreadManForUser_31327F19                       (syscall_ThreadManForUser, "ThreadManForUser_31327F19");
        /**  **  **/SubCategory syscall_ThreadManForUser_71040D5C                       (syscall_ThreadManForUser, "ThreadManForUser_71040D5C");
        /**  **  **/SubCategory syscall_ThreadManForUser_7CFF8CF3                       (syscall_ThreadManForUser, "ThreadManForUser_7CFF8CF3");
        /**  **  **/SubCategory syscall_ThreadManForUser_8672E3D0                       (syscall_ThreadManForUser, "ThreadManForUser_8672E3D0");
        /**  **  **/SubCategory syscall_ThreadManForUser_BEED3A47                       (syscall_ThreadManForUser, "ThreadManForUser_BEED3A47");
        /**/SubCategory syscall_iofilemgr_prx                                   (syscalls, "iofilemgr.prx");
        /**  **/SubCategory syscall_StdioForUser                                    (syscall_iofilemgr_prx, "StdioForUser");
        /**  **  **/SubCategory syscall_sceKernelStdout                                 (syscall_StdioForUser, "sceKernelStdout");
        /**  **  **/SubCategory syscall_sceKernelStderr                                 (syscall_StdioForUser, "sceKernelStderr");
        /**  **  **/SubCategory syscall_sceKernelStdin                                  (syscall_StdioForUser, "sceKernelStdin");
        /**  **  **/SubCategory syscall_sceKernelStdioOpen                              (syscall_StdioForUser, "sceKernelStdioOpen");
        /**  **  **/SubCategory syscall_sceKernelStdioClose                             (syscall_StdioForUser, "sceKernelStdioClose");
        /**  **  **/SubCategory syscall_sceKernelStdioLseek                             (syscall_StdioForUser, "sceKernelStdioLseek");
        /**  **  **/SubCategory syscall_sceKernelStdioRead                              (syscall_StdioForUser, "sceKernelStdioRead");
        /**  **  **/SubCategory syscall_sceKernelStdioWrite                             (syscall_StdioForUser, "sceKernelStdioWrite");
        /**  **  **/SubCategory syscall_sceKernelStdioSendChar                          (syscall_StdioForUser, "sceKernelStdioSendChar");
        /**  **  **/SubCategory syscall_sceKernelRegisterStdoutPipe                     (syscall_StdioForUser, "sceKernelRegisterStdoutPipe");
        /**  **  **/SubCategory syscall_sceKernelRegisterStderrPipe                     (syscall_StdioForUser, "sceKernelRegisterStderrPipe");
        /**  **/SubCategory syscall_IoFileMgrForUser                                (syscall_iofilemgr_prx, "IoFileMgrForUser");
        /**  **  **/SubCategory syscall_sceIoChstat                                     (syscall_IoFileMgrForUser, "sceIoChstat");
        /**  **  **/SubCategory syscall_sceIoGetstat                                    (syscall_IoFileMgrForUser, "sceIoGetstat");
        /**  **  **/SubCategory syscall_sceIoGetAsyncStat                               (syscall_IoFileMgrForUser, "sceIoGetAsyncStat");
        /**  **  **/SubCategory syscall_sceIoDopen                                      (syscall_IoFileMgrForUser, "sceIoDopen");
        /**  **  **/SubCategory syscall_sceIoDclose                                     (syscall_IoFileMgrForUser, "sceIoDclose");
        /**  **  **/SubCategory syscall_sceIoDread                                      (syscall_IoFileMgrForUser, "sceIoDread");
        /**  **  **/SubCategory syscall_sceIoMkdir                                      (syscall_IoFileMgrForUser, "sceIoMkdir");
        /**  **  **/SubCategory syscall_sceIoRmdir                                      (syscall_IoFileMgrForUser, "sceIoRmdir");
        /**  **  **/SubCategory syscall_sceIoChdir                                      (syscall_IoFileMgrForUser, "sceIoChdir");
        /**  **  **/SubCategory syscall_sceIoRename                                     (syscall_IoFileMgrForUser, "sceIoRename");
        /**  **  **/SubCategory syscall_sceIoRemove                                     (syscall_IoFileMgrForUser, "sceIoRemove");
        /**  **  **/SubCategory syscall_sceIoDevctl                                     (syscall_IoFileMgrForUser, "sceIoDevctl");
        /**  **  **/SubCategory syscall_sceIoSync                                       (syscall_IoFileMgrForUser, "sceIoSync");
        /**  **  **/SubCategory syscall_sceIoGetDevType                                 (syscall_IoFileMgrForUser, "sceIoGetDevType");
        /**  **  **/SubCategory syscall_sceIoOpen                                       (syscall_IoFileMgrForUser, "sceIoOpen");
        /**  **  **/SubCategory syscall_sceIoClose                                      (syscall_IoFileMgrForUser, "sceIoClose");
        /**  **  **/SubCategory syscall_sceIoIoctl                                      (syscall_IoFileMgrForUser, "sceIoIoctl");
        /**  **  **/SubCategory syscall_sceIoLseek                                      (syscall_IoFileMgrForUser, "sceIoLseek");
        /**  **  **/SubCategory syscall_sceIoLseek32                                    (syscall_IoFileMgrForUser, "sceIoLseek32");
        /**  **  **/SubCategory syscall_sceIoRead                                       (syscall_IoFileMgrForUser, "sceIoRead");
        /**  **  **/SubCategory syscall_sceIoWrite                                      (syscall_IoFileMgrForUser, "sceIoWrite");
        /**  **  **/SubCategory syscall_sceIoPollAsync                                  (syscall_IoFileMgrForUser, "sceIoPollAsync");
        /**  **  **/SubCategory syscall_sceIoWaitAsync                                  (syscall_IoFileMgrForUser, "sceIoWaitAsync");
        /**  **  **/SubCategory syscall_sceIoWaitAsyncCB                                (syscall_IoFileMgrForUser, "sceIoWaitAsyncCB");
        /**  **  **/SubCategory syscall_sceIoSetAsyncCallback                           (syscall_IoFileMgrForUser, "sceIoSetAsyncCallback");
        /**  **  **/SubCategory syscall_sceIoOpenAsync                                  (syscall_IoFileMgrForUser, "sceIoOpenAsync");
        /**  **  **/SubCategory syscall_sceIoCloseAsync                                 (syscall_IoFileMgrForUser, "sceIoCloseAsync");
        /**  **  **/SubCategory syscall_sceIoIoctlAsync                                 (syscall_IoFileMgrForUser, "sceIoIoctlAsync");
        /**  **  **/SubCategory syscall_sceIoLseekAsync                                 (syscall_IoFileMgrForUser, "sceIoLseekAsync");
        /**  **  **/SubCategory syscall_sceIoLseek32Async                               (syscall_IoFileMgrForUser, "sceIoLseek32Async");
        /**  **  **/SubCategory syscall_sceIoReadAsync                                  (syscall_IoFileMgrForUser, "sceIoReadAsync");
        /**  **  **/SubCategory syscall_sceIoWriteAsync                                 (syscall_IoFileMgrForUser, "sceIoWriteAsync");
        /**  **  **/SubCategory syscall_sceIoChangeAsyncPriority                        (syscall_IoFileMgrForUser, "sceIoChangeAsyncPriority");
        /**  **  **/SubCategory syscall_sceIoCancel                                     (syscall_IoFileMgrForUser, "sceIoCancel");
        /**  **  **/SubCategory syscall_sceIoGetFdList                                  (syscall_IoFileMgrForUser, "sceIoGetFdList");
        /**  **  **/SubCategory syscall_sceIoAssign                                     (syscall_IoFileMgrForUser, "sceIoAssign");
        /**  **  **/SubCategory syscall_sceIoUnassign                                   (syscall_IoFileMgrForUser, "sceIoUnassign");
        /**/SubCategory syscall_modulemgr_prx                                   (syscalls, "modulemgr.prx");
        /**  **/SubCategory syscall_ModuleMgrForUser                                (syscall_modulemgr_prx, "ModuleMgrForUser");
        /**  **  **/SubCategory syscall_sceKernelLoadModule                             (syscall_ModuleMgrForUser, "sceKernelLoadModule");
        /**  **  **/SubCategory syscall_sceKernelLoadModuleMs                           (syscall_ModuleMgrForUser, "sceKernelLoadModuleMs");
        /**  **  **/SubCategory syscall_sceKernelLoadModuleBufferUsbWlan                (syscall_ModuleMgrForUser, "sceKernelLoadModuleBufferUsbWlan");
        /**  **  **/SubCategory syscall_sceKernelLoadModuleByID                         (syscall_ModuleMgrForUser, "sceKernelLoadModuleByID");
        /**  **  **/SubCategory syscall_sceKernelStartModule                            (syscall_ModuleMgrForUser, "sceKernelStartModule");
        /**  **  **/SubCategory syscall_sceKernelStopModule                             (syscall_ModuleMgrForUser, "sceKernelStopModule");
        /**  **  **/SubCategory syscall_sceKernelUnloadModule                           (syscall_ModuleMgrForUser, "sceKernelUnloadModule");
        /**  **  **/SubCategory syscall_sceKernelSelfStopUnloadModule                   (syscall_ModuleMgrForUser, "sceKernelSelfStopUnloadModule");
        /**  **  **/SubCategory syscall_sceKernelStopUnloadSelfModule                   (syscall_ModuleMgrForUser, "sceKernelStopUnloadSelfModule");
        /**  **  **/SubCategory syscall_sceKernelQueryModuleInfo                        (syscall_ModuleMgrForUser, "sceKernelQueryModuleInfo");
        /**  **  **/SubCategory syscall_sceKernelGetModuleId                            (syscall_ModuleMgrForUser, "sceKernelGetModuleId");
        /**  **  **/SubCategory syscall_sceKernelGetModuleIdByAddress                   (syscall_ModuleMgrForUser, "sceKernelGetModuleIdByAddress");
        /**  **  **/SubCategory syscall_sceKernelGetModuleGPByAddress                   (syscall_ModuleMgrForUser, "sceKernelGetModuleGPByAddress");
        /**  **  **/SubCategory syscall_sceKernelGetModuleIdList                        (syscall_ModuleMgrForUser, "sceKernelGetModuleIdList");
        /**  **  **/SubCategory syscall_ModuleMgrForUser_1196472E                       (syscall_ModuleMgrForUser, "ModuleMgrForUser_1196472E");
        /**  **  **/SubCategory syscall_ModuleMgrForUser_24EC0641                       (syscall_ModuleMgrForUser, "ModuleMgrForUser_24EC0641");
        /**  **  **/SubCategory syscall_ModuleMgrForUser_8F2DF740                       (syscall_ModuleMgrForUser, "ModuleMgrForUser_8F2DF740");
        /**  **  **/SubCategory syscall_ModuleMgrForUser_E4C4211C                       (syscall_ModuleMgrForUser, "ModuleMgrForUser_E4C4211C");
        /**  **  **/SubCategory syscall_ModuleMgrForUser_F2D8D1B4                       (syscall_ModuleMgrForUser, "ModuleMgrForUser_F2D8D1B4");
        /**  **  **/SubCategory syscall_ModuleMgrForUser_FBE27467                       (syscall_ModuleMgrForUser, "ModuleMgrForUser_FBE27467");
        /**  **  **/SubCategory syscall_ModuleMgrForUser_FEF27DC1                       (syscall_ModuleMgrForUser, "ModuleMgrForUser_FEF27DC1");
        /**/SubCategory syscall_loadexec_prx                                    (syscalls, "loadexec.prx");
        /**  **/SubCategory syscall_LoadExecForUser                                 (syscall_loadexec_prx, "LoadExecForUser");
        /**  **  **/SubCategory syscall_sceKernelLoadExec                               (syscall_LoadExecForUser, "sceKernelLoadExec");
        /**  **  **/SubCategory syscall_sceKernelExitGame                               (syscall_LoadExecForUser, "sceKernelExitGame");
        /**  **  **/SubCategory syscall_sceKernelExitGameWithStatus                     (syscall_LoadExecForUser, "sceKernelExitGameWithStatus");
        /**  **  **/SubCategory syscall_sceKernelRegisterExitCallback                   (syscall_LoadExecForUser, "sceKernelRegisterExitCallback");
        /**  **  **/SubCategory syscall_LoadExecForUser_362A956B                        (syscall_LoadExecForUser, "LoadExecForUser_362A956B");
        /**  **  **/SubCategory syscall_LoadExecForUser_8ADA38D3                        (syscall_LoadExecForUser, "LoadExecForUser_8ADA38D3");
        /**  **  **/SubCategory syscall_LoadExecForUser_D1FB50DC                        (syscall_LoadExecForUser, "LoadExecForUser_D1FB50DC");
        /**/SubCategory syscall_ge_prx                                          (syscalls, "ge.prx");
        /**  **/SubCategory syscall_sceGe_user                                      (syscall_ge_prx, "sceGe_user");
        /**  **  **/SubCategory syscall_sceGeEdramGetSize                               (syscall_sceGe_user, "sceGeEdramGetSize");
        /**  **  **/SubCategory syscall_sceGeEdramGetAddr                               (syscall_sceGe_user, "sceGeEdramGetAddr");
        /**  **  **/SubCategory syscall_sceGeEdramSetAddrTranslation                    (syscall_sceGe_user, "sceGeEdramSetAddrTranslation");
        /**  **  **/SubCategory syscall_sceGeGetCmd                                     (syscall_sceGe_user, "sceGeGetCmd");
        /**  **  **/SubCategory syscall_sceGeGetMtx                                     (syscall_sceGe_user, "sceGeGetMtx");
        /**  **  **/SubCategory syscall_sceGeSaveContext                                (syscall_sceGe_user, "sceGeSaveContext");
        /**  **  **/SubCategory syscall_sceGeRestoreContext                             (syscall_sceGe_user, "sceGeRestoreContext");
        /**  **  **/SubCategory syscall_sceGeListEnQueue                                (syscall_sceGe_user, "sceGeListEnQueue");
        /**  **  **/SubCategory syscall_sceGeListEnQueueHead                            (syscall_sceGe_user, "sceGeListEnQueueHead");
        /**  **  **/SubCategory syscall_sceGeListDeQueue                                (syscall_sceGe_user, "sceGeListDeQueue");
        /**  **  **/SubCategory syscall_sceGeListUpdateStallAddr                        (syscall_sceGe_user, "sceGeListUpdateStallAddr");
        /**  **  **/SubCategory syscall_sceGeListSync                                   (syscall_sceGe_user, "sceGeListSync");
        /**  **  **/SubCategory syscall_sceGeDrawSync                                   (syscall_sceGe_user, "sceGeDrawSync");
        /**  **  **/SubCategory syscall_sceGeBreak                                      (syscall_sceGe_user, "sceGeBreak");
        /**  **  **/SubCategory syscall_sceGeContinue                                   (syscall_sceGe_user, "sceGeContinue");
        /**  **  **/SubCategory syscall_sceGeSetCallback                                (syscall_sceGe_user, "sceGeSetCallback");
        /**  **  **/SubCategory syscall_sceGeUnsetCallback                              (syscall_sceGe_user, "sceGeUnsetCallback");
        /**  **  **/SubCategory syscall_sceGeGetStack                                   (syscall_sceGe_user, "sceGeGetStack");
        /**/SubCategory syscall_rtc_prx                                         (syscalls, "rtc.prx");
        /**  **/SubCategory syscall_sceRtc                                          (syscall_rtc_prx, "sceRtc");
        /**  **  **/SubCategory syscall_sceRtcTickAddTicks                              (syscall_sceRtc, "sceRtcTickAddTicks");
        /**  **  **/SubCategory syscall_sceRtcTickAddMicroseconds                       (syscall_sceRtc, "sceRtcTickAddMicroseconds");
        /**  **  **/SubCategory syscall_sceRtcTickAddSeconds                            (syscall_sceRtc, "sceRtcTickAddSeconds");
        /**  **  **/SubCategory syscall_sceRtcTickAddMinutes                            (syscall_sceRtc, "sceRtcTickAddMinutes");
        /**  **  **/SubCategory syscall_sceRtcTickAddHours                              (syscall_sceRtc, "sceRtcTickAddHours");
        /**  **  **/SubCategory syscall_sceRtcTickAddDays                               (syscall_sceRtc, "sceRtcTickAddDays");
        /**  **  **/SubCategory syscall_sceRtcTickAddWeeks                              (syscall_sceRtc, "sceRtcTickAddWeeks");
        /**  **  **/SubCategory syscall_sceRtcTickAddMonths                             (syscall_sceRtc, "sceRtcTickAddMonths");
        /**  **  **/SubCategory syscall_sceRtcTickAddYears                              (syscall_sceRtc, "sceRtcTickAddYears");
        /**  **  **/SubCategory syscall_sceRtcGetAccumulativeTime                       (syscall_sceRtc, "sceRtcGetAccumulativeTime");
        /**  **  **/SubCategory syscall_sceRtcGetAccumlativeTime                        (syscall_sceRtc, "sceRtcGetAccumlativeTime");
        /**  **  **/SubCategory syscall_sceRtcFormatRFC3339                             (syscall_sceRtc, "sceRtcFormatRFC3339");
        /**  **  **/SubCategory syscall_sceRtcGetDaysInMonth                            (syscall_sceRtc, "sceRtcGetDaysInMonth");
        /**  **  **/SubCategory syscall_sceRtcSetTime64_t                               (syscall_sceRtc, "sceRtcSetTime64_t");
        /**  **  **/SubCategory syscall_sceRtcGetLastReincarnatedTime                   (syscall_sceRtc, "sceRtcGetLastReincarnatedTime");
        /**  **  **/SubCategory syscall_sceRtcGetTime_t                                 (syscall_sceRtc, "sceRtcGetTime_t");
        /**  **  **/SubCategory syscall_sceRtcFormatRFC3339LocalTime                    (syscall_sceRtc, "sceRtcFormatRFC3339LocalTime");
        /**  **  **/SubCategory syscall_sceRtcParseRFC3339                              (syscall_sceRtc, "sceRtcParseRFC3339");
        /**  **  **/SubCategory syscall_sceRtcConvertUtcToLocalTime                     (syscall_sceRtc, "sceRtcConvertUtcToLocalTime");
        /**  **  **/SubCategory syscall_sceRtcGetDosTime                                (syscall_sceRtc, "sceRtcGetDosTime");
        /**  **  **/SubCategory syscall_sceRtcSetTime_t                                 (syscall_sceRtc, "sceRtcSetTime_t");
        /**  **  **/SubCategory syscall_sceRtcGetCurrentTick                            (syscall_sceRtc, "sceRtcGetCurrentTick");
        /**  **  **/SubCategory syscall_sceRtcIsLeapYear                                (syscall_sceRtc, "sceRtcIsLeapYear");
        /**  **  **/SubCategory syscall_sceRtcCheckValid                                (syscall_sceRtc, "sceRtcCheckValid");
        /**  **  **/SubCategory syscall_sceRtcGetCurrentClock                           (syscall_sceRtc, "sceRtcGetCurrentClock");
        /**  **  **/SubCategory syscall_sceRtcGetDayOfWeek                              (syscall_sceRtc, "sceRtcGetDayOfWeek");
        /**  **  **/SubCategory syscall_sceRtcGetLastAdjustedTime                       (syscall_sceRtc, "sceRtcGetLastAdjustedTime");
        /**  **  **/SubCategory syscall_sceRtcUnregisterCallback                        (syscall_sceRtc, "sceRtcUnregisterCallback");
        /**  **  **/SubCategory syscall_sceRtcGetTick                                   (syscall_sceRtc, "sceRtcGetTick");
        /**  **  **/SubCategory syscall_sceRtcConvertLocalTimeToUTC                     (syscall_sceRtc, "sceRtcConvertLocalTimeToUTC");
        /**  **  **/SubCategory syscall_sceRtcSetWin32FileTime                          (syscall_sceRtc, "sceRtcSetWin32FileTime");
        /**  **  **/SubCategory syscall_sceRtc_7D1FBED3                                 (syscall_sceRtc, "sceRtc_7D1FBED3");
        /**  **  **/SubCategory syscall_sceRtcFormatRFC2822LocalTime                    (syscall_sceRtc, "sceRtcFormatRFC2822LocalTime");
        /**  **  **/SubCategory syscall_sceRtcSetTick                                   (syscall_sceRtc, "sceRtcSetTick");
        /**  **  **/SubCategory syscall_sceRtcIsAlarmed                                 (syscall_sceRtc, "sceRtcIsAlarmed");
        /**  **  **/SubCategory syscall_sceRtcCompareTick                               (syscall_sceRtc, "sceRtcCompareTick");
        /**  **  **/SubCategory syscall_sceRtc_A93CF7D8                                 (syscall_sceRtc, "sceRtc_A93CF7D8");
        /**  **  **/SubCategory syscall_sceRtc_C2DDBEB5                                 (syscall_sceRtc, "sceRtc_C2DDBEB5");
        /**  **  **/SubCategory syscall_sceRtcGetTickResolution                         (syscall_sceRtc, "sceRtcGetTickResolution");
        /**  **  **/SubCategory syscall_sceRtcFormatRFC2822                             (syscall_sceRtc, "sceRtcFormatRFC2822");
        /**  **  **/SubCategory syscall_sceRtcGetWin32FileTime                          (syscall_sceRtc, "sceRtcGetWin32FileTime");
        /**  **  **/SubCategory syscall_sceRtcParseDateTime                             (syscall_sceRtc, "sceRtcParseDateTime");
        /**  **  **/SubCategory syscall_sceRtcGetTime64_t                               (syscall_sceRtc, "sceRtcGetTime64_t");
        /**  **  **/SubCategory syscall_sceRtcGetCurrentClockLocalTime                  (syscall_sceRtc, "sceRtcGetCurrentClockLocalTime");
        /**  **  **/SubCategory syscall_sceRtcSetDosTime                                (syscall_sceRtc, "sceRtcSetDosTime");
        /**  **  **/SubCategory syscall_sceRtc_F5FCC995                                 (syscall_sceRtc, "sceRtc_F5FCC995");
        /**  **  **/SubCategory syscall_sceRtcRegisterCallback                          (syscall_sceRtc, "sceRtcRegisterCallback");
        /**/SubCategory syscall_audio_prx                                       (syscalls, "audio.prx");
        /**  **/SubCategory syscall_sceAudio                                        (syscall_audio_prx, "sceAudio");
        /**  **  **/SubCategory syscall_sceAudioChReserve                               (syscall_sceAudio, "sceAudioChReserve");
        /**  **  **/SubCategory syscall_sceAudioChRelease                               (syscall_sceAudio, "sceAudioChRelease");
        /**  **  **/SubCategory syscall_sceAudioOutput                                  (syscall_sceAudio, "sceAudioOutput");
        /**  **  **/SubCategory syscall_sceAudioOutputBlocking                          (syscall_sceAudio, "sceAudioOutputBlocking");
        /**  **  **/SubCategory syscall_sceAudioOutputPanned                            (syscall_sceAudio, "sceAudioOutputPanned");
        /**  **  **/SubCategory syscall_sceAudioOutputPannedBlocking                    (syscall_sceAudio, "sceAudioOutputPannedBlocking");
        /**  **  **/SubCategory syscall_sceAudioChangeChannelVolume                     (syscall_sceAudio, "sceAudioChangeChannelVolume");
        /**  **  **/SubCategory syscall_sceAudioChangeChannelConfig                     (syscall_sceAudio, "sceAudioChangeChannelConfig");
        /**  **  **/SubCategory syscall_sceAudioSetChannelDataLen                       (syscall_sceAudio, "sceAudioSetChannelDataLen");
        /**  **  **/SubCategory syscall_sceAudioGetChannelRestLen                       (syscall_sceAudio, "sceAudioGetChannelRestLen");
        /**  **  **/SubCategory syscall_sceAudioGetChannelRestLength                    (syscall_sceAudio, "sceAudioGetChannelRestLength");
        /**  **  **/SubCategory syscall_sceAudioSRCChReserve                            (syscall_sceAudio, "sceAudioSRCChReserve");
        /**  **  **/SubCategory syscall_sceAudioSRCChRelease                            (syscall_sceAudio, "sceAudioSRCChRelease");
        /**  **  **/SubCategory syscall_sceAudioSRCOutputBlocking                       (syscall_sceAudio, "sceAudioSRCOutputBlocking");
        /**  **  **/SubCategory syscall_sceAudioOutput2Reserve                          (syscall_sceAudio, "sceAudioOutput2Reserve");
        /**  **  **/SubCategory syscall_sceAudioOutput2Release                          (syscall_sceAudio, "sceAudioOutput2Release");
        /**  **  **/SubCategory syscall_sceAudioOutput2OutputBlocking                   (syscall_sceAudio, "sceAudioOutput2OutputBlocking");
        /**  **  **/SubCategory syscall_sceAudioOutput2ChangeLength                     (syscall_sceAudio, "sceAudioOutput2ChangeLength");
        /**  **  **/SubCategory syscall_sceAudioOutput2GetRestSample                    (syscall_sceAudio, "sceAudioOutput2GetRestSample");
        /**  **  **/SubCategory syscall_sceAudioOneshotOutput                           (syscall_sceAudio, "sceAudioOneshotOutput");
        /**  **  **/SubCategory syscall_sceAudioInputInit                               (syscall_sceAudio, "sceAudioInputInit");
        /**  **  **/SubCategory syscall_sceAudioInputInitEx                             (syscall_sceAudio, "sceAudioInputInitEx");
        /**  **  **/SubCategory syscall_sceAudioInput                                   (syscall_sceAudio, "sceAudioInput");
        /**  **  **/SubCategory syscall_sceAudioInputBlocking                           (syscall_sceAudio, "sceAudioInputBlocking");
        /**  **  **/SubCategory syscall_sceAudioPollInputEnd                            (syscall_sceAudio, "sceAudioPollInputEnd");
        /**  **  **/SubCategory syscall_sceAudioWaitInputEnd                            (syscall_sceAudio, "sceAudioWaitInputEnd");
        /**  **  **/SubCategory syscall_sceAudioGetInputLength                          (syscall_sceAudio, "sceAudioGetInputLength");
        /**/SubCategory syscall_display_prx                                     (syscalls, "display.prx");
        /**  **/SubCategory syscall_sceDisplay                                      (syscall_display_prx, "sceDisplay");
        /**  **  **/SubCategory syscall_sceDisplaySetMode                               (syscall_sceDisplay, "sceDisplaySetMode");
        /**  **  **/SubCategory syscall_sceDisplayGetMode                               (syscall_sceDisplay, "sceDisplayGetMode");
        /**  **  **/SubCategory syscall_sceDisplayGetFramePerSec                        (syscall_sceDisplay, "sceDisplayGetFramePerSec");
        /**  **  **/SubCategory syscall_sceDisplaySetFrameBuf                           (syscall_sceDisplay, "sceDisplaySetFrameBuf");
        /**  **  **/SubCategory syscall_sceDisplayGetFrameBuf                           (syscall_sceDisplay, "sceDisplayGetFrameBuf");
        /**  **  **/SubCategory syscall_sceDisplayIsForeground                          (syscall_sceDisplay, "sceDisplayIsForeground");
        /**  **  **/SubCategory syscall_sceDisplaySetHoldMode                           (syscall_sceDisplay, "sceDisplaySetHoldMode");
        /**  **  **/SubCategory syscall_sceDisplayGetVcount                             (syscall_sceDisplay, "sceDisplayGetVcount");
        /**  **  **/SubCategory syscall_sceDisplayIsVblank                              (syscall_sceDisplay, "sceDisplayIsVblank");
        /**  **  **/SubCategory syscall_sceDisplayGetVblankRest                         (syscall_sceDisplay, "sceDisplayGetVblankRest");
        /**  **  **/SubCategory syscall_sceDisplayWaitVblank                            (syscall_sceDisplay, "sceDisplayWaitVblank");
        /**  **  **/SubCategory syscall_sceDisplayWaitVblankCB                          (syscall_sceDisplay, "sceDisplayWaitVblankCB");
        /**  **  **/SubCategory syscall_sceDisplayWaitVblankStart                       (syscall_sceDisplay, "sceDisplayWaitVblankStart");
        /**  **  **/SubCategory syscall_sceDisplayWaitVblankStartCB                     (syscall_sceDisplay, "sceDisplayWaitVblankStartCB");
        /**  **  **/SubCategory syscall_sceDisplayIsVsync                               (syscall_sceDisplay, "sceDisplayIsVsync");
        /**  **  **/SubCategory syscall_sceDisplayGetCurrentHcount                      (syscall_sceDisplay, "sceDisplayGetCurrentHcount");
        /**  **  **/SubCategory syscall_sceDisplayGetAccumulatedHcount                  (syscall_sceDisplay, "sceDisplayGetAccumulatedHcount");
        /**  **  **/SubCategory syscall_sceDisplayAdjustAccumulatedHcount               (syscall_sceDisplay, "sceDisplayAdjustAccumulatedHcount");
        /**  **  **/SubCategory syscall_sceDisplaySetResumeMode                         (syscall_sceDisplay, "sceDisplaySetResumeMode");
        /**  **  **/SubCategory syscall_sceDisplayGetResumeMode                         (syscall_sceDisplay, "sceDisplayGetResumeMode");
        /**  **  **/SubCategory syscall_sceDisplayGetBrightness                         (syscall_sceDisplay, "sceDisplayGetBrightness");
        /**  **  **/SubCategory syscall_sceDisplay_40F1469C                             (syscall_sceDisplay, "sceDisplay_40F1469C");
        /**  **  **/SubCategory syscall_sceDisplay_77ED8B3A                             (syscall_sceDisplay, "sceDisplay_77ED8B3A");
        /**/SubCategory syscall_ctrl_prx                                        (syscalls, "ctrl.prx");
        /**  **/SubCategory syscall_sceCtrl                                         (syscall_ctrl_prx, "sceCtrl");
        /**  **  **/SubCategory syscall_sceCtrlSetSamplingMode                          (syscall_sceCtrl, "sceCtrlSetSamplingMode");
        /**  **  **/SubCategory syscall_sceCtrlGetSamplingMode                          (syscall_sceCtrl, "sceCtrlGetSamplingMode");
        /**  **  **/SubCategory syscall_sceCtrlSetSamplingCycle                         (syscall_sceCtrl, "sceCtrlSetSamplingCycle");
        /**  **  **/SubCategory syscall_sceCtrlGetSamplingCycle                         (syscall_sceCtrl, "sceCtrlGetSamplingCycle");
        /**  **  **/SubCategory syscall_sceCtrlSetIdleCancelThreshold                   (syscall_sceCtrl, "sceCtrlSetIdleCancelThreshold");
        /**  **  **/SubCategory syscall_sceCtrlGetIdleCancelThreshold                   (syscall_sceCtrl, "sceCtrlGetIdleCancelThreshold");
        /**  **  **/SubCategory syscall_sceCtrlPeekBufferPositive                       (syscall_sceCtrl, "sceCtrlPeekBufferPositive");
        /**  **  **/SubCategory syscall_sceCtrlPeekBufferNegative                       (syscall_sceCtrl, "sceCtrlPeekBufferNegative");
        /**  **  **/SubCategory syscall_sceCtrlReadBufferPositive                       (syscall_sceCtrl, "sceCtrlReadBufferPositive");
        /**  **  **/SubCategory syscall_sceCtrlReadBufferNegative                       (syscall_sceCtrl, "sceCtrlReadBufferNegative");
        /**  **  **/SubCategory syscall_sceCtrlPeekLatch                                (syscall_sceCtrl, "sceCtrlPeekLatch");
        /**  **  **/SubCategory syscall_sceCtrlReadLatch                                (syscall_sceCtrl, "sceCtrlReadLatch");
        /**  **  **/SubCategory syscall_sceCtrlClearRapidFire                           (syscall_sceCtrl, "sceCtrlClearRapidFire");
        /**  **  **/SubCategory syscall_sceCtrlSetRapidFire                             (syscall_sceCtrl, "sceCtrlSetRapidFire");
        /**  **  **/SubCategory syscall_sceCtrl_348D99D4                                (syscall_sceCtrl, "sceCtrl_348D99D4");
        /**  **  **/SubCategory syscall_sceCtrl_AF5960F3                                (syscall_sceCtrl, "sceCtrl_AF5960F3");
        /**/SubCategory syscall_hpremote_prx                                    (syscalls, "hpremote.prx");
        /**  **/SubCategory syscall_sceHprm                                         (syscall_hpremote_prx, "sceHprm");
        /**  **  **/SubCategory syscall_sceHprmPeekCurrentKey                           (syscall_sceHprm, "sceHprmPeekCurrentKey");
        /**  **  **/SubCategory syscall_sceHprmIsRemoteExist                            (syscall_sceHprm, "sceHprmIsRemoteExist");
        /**  **  **/SubCategory syscall_sceHprmIsMicrophoneExist                        (syscall_sceHprm, "sceHprmIsMicrophoneExist");
        /**  **  **/SubCategory syscall_sceHprmPeekLatch                                (syscall_sceHprm, "sceHprmPeekLatch");
        /**  **  **/SubCategory syscall_sceHprm_3953DE6B                                (syscall_sceHprm, "sceHprm_3953DE6B");
        /**  **  **/SubCategory syscall_sceHprm_396FD885                                (syscall_sceHprm, "sceHprm_396FD885");
        /**  **  **/SubCategory syscall_sceHprmReadLatch                                (syscall_sceHprm, "sceHprmReadLatch");
        /**  **  **/SubCategory syscall_sceHprmUnregitserCallback                       (syscall_sceHprm, "sceHprmUnregitserCallback");
        /**  **  **/SubCategory syscall_sceHprmGetHpDetect                              (syscall_sceHprm, "sceHprmGetHpDetect");
        /**  **  **/SubCategory syscall_sceHprmIsHeadphoneExist                         (syscall_sceHprm, "sceHprmIsHeadphoneExist");
        /**  **  **/SubCategory syscall_sceHprmRegisterCallback                         (syscall_sceHprm, "sceHprmRegisterCallback");
        /**  **  **/SubCategory syscall_sceHprm_FD7DE6CD                                (syscall_sceHprm, "sceHprm_FD7DE6CD");
        /**/SubCategory syscall_power_prx                                       (syscalls, "power.prx");
        /**  **/SubCategory syscall_scePower                                        (syscall_power_prx, "scePower");
        /**  **  **/SubCategory syscall_scePowerGetResumeCount                          (syscall_scePower, "scePowerGetResumeCount");
        /**  **  **/SubCategory syscall_scePowerRequestColdReset                        (syscall_scePower, "scePowerRequestColdReset");
        /**  **  **/SubCategory syscall_scePowerRegisterCallback                        (syscall_scePower, "scePowerRegisterCallback");
        /**  **  **/SubCategory syscall_scePowerIsBatteryExist                          (syscall_scePower, "scePowerIsBatteryExist");
        /**  **  **/SubCategory syscall_scePowerSetPowerSwMode                          (syscall_scePower, "scePowerSetPowerSwMode");
        /**  **  **/SubCategory syscall_scePowerGetPowerSwMode                          (syscall_scePower, "scePowerGetPowerSwMode");
        /**  **  **/SubCategory syscall_scePowerIsBatteryCharging                       (syscall_scePower, "scePowerIsBatteryCharging");
        /**  **  **/SubCategory syscall_scePowerGetBatteryLifePercent                   (syscall_scePower, "scePowerGetBatteryLifePercent");
        /**  **  **/SubCategory syscall_scePowerGetInnerTemp                            (syscall_scePower, "scePowerGetInnerTemp");
        /**  **  **/SubCategory syscall_scePowerVolatileMemLock                         (syscall_scePower, "scePowerVolatileMemLock");
        /**  **  **/SubCategory syscall_scePowerBatteryUpdateInfo                       (syscall_scePower, "scePowerBatteryUpdateInfo");
        /**  **  **/SubCategory syscall_scePower_2875994B                               (syscall_scePower, "scePower_2875994B");
        /**  **  **/SubCategory syscall_scePowerGetBatteryTemp                          (syscall_scePower, "scePowerGetBatteryTemp");
        /**  **  **/SubCategory syscall_scePower_2B51FE2F                               (syscall_scePower, "scePower_2B51FE2F");
        /**  **  **/SubCategory syscall_scePowerRequestStandby                          (syscall_scePower, "scePowerRequestStandby");
        /**  **  **/SubCategory syscall_scePowerGetPllClockFrequencyInt                 (syscall_scePower, "scePowerGetPllClockFrequencyInt");
        /**  **  **/SubCategory syscall_scePowerWaitRequestCompletion                   (syscall_scePower, "scePowerWaitRequestCompletion");
        /**  **  **/SubCategory syscall_scePowerGetBacklightMaximum                     (syscall_scePower, "scePowerGetBacklightMaximum");
        /**  **  **/SubCategory syscall_scePowerGetBusClockFrequency                    (syscall_scePower, "scePowerGetBusClockFrequency");
        /**  **  **/SubCategory syscall_scePowerGetBatteryVolt                          (syscall_scePower, "scePowerGetBatteryVolt");
        /**  **  **/SubCategory syscall_scePower_545A7F3C                               (syscall_scePower, "scePower_545A7F3C");
        /**  **  **/SubCategory syscall_scePowerSetClockFrequency                       (syscall_scePower, "scePowerSetClockFrequency");
        /**  **  **/SubCategory syscall_scePowerIsSuspendRequired                       (syscall_scePower, "scePowerIsSuspendRequired");
        /**  **  **/SubCategory syscall_scePowerIdleTimerEnable                         (syscall_scePower, "scePowerIdleTimerEnable");
        /**  **  **/SubCategory syscall_scePowerIsRequest                               (syscall_scePower, "scePowerIsRequest");
        /**  **  **/SubCategory syscall_scePowerSetCpuClockFrequency                    (syscall_scePower, "scePowerSetCpuClockFrequency");
        /**  **  **/SubCategory syscall_scePowerGetBatteryElec                          (syscall_scePower, "scePowerGetBatteryElec");
        /**  **  **/SubCategory syscall_scePowerIsPowerOnline                           (syscall_scePower, "scePowerIsPowerOnline");
        /**  **  **/SubCategory syscall_scePowerGetBatteryLifeTime                      (syscall_scePower, "scePowerGetBatteryLifeTime");
        /**  **  **/SubCategory syscall_scePowerGetBatteryRemainCapacity                (syscall_scePower, "scePowerGetBatteryRemainCapacity");
        /**  **  **/SubCategory syscall_scePowerIdleTimerDisable                        (syscall_scePower, "scePowerIdleTimerDisable");
        /**  **  **/SubCategory syscall_scePowerGetBusClockFrequencyFloat               (syscall_scePower, "scePowerGetBusClockFrequencyFloat");
        /**  **  **/SubCategory syscall_scePower_A4E93389                               (syscall_scePower, "scePower_A4E93389");
        /**  **  **/SubCategory syscall_scePowerSetCallbackMode                         (syscall_scePower, "scePowerSetCallbackMode");
        /**  **  **/SubCategory syscall_scePowerRequestSuspend                          (syscall_scePower, "scePowerRequestSuspend");
        /**  **  **/SubCategory syscall_scePowerGetCpuClockFrequencyFloat               (syscall_scePower, "scePowerGetCpuClockFrequencyFloat");
        /**  **  **/SubCategory syscall_scePowerVolatileMemUnlock                       (syscall_scePower, "scePowerVolatileMemUnlock");
        /**  **  **/SubCategory syscall_scePowerGetBatteryChargingStatus                (syscall_scePower, "scePowerGetBatteryChargingStatus");
        /**  **  **/SubCategory syscall_scePowerSetBusClockFrequency                    (syscall_scePower, "scePowerSetBusClockFrequency");
        /**  **  **/SubCategory syscall_scePowerGetLowBatteryCapacity                   (syscall_scePower, "scePowerGetLowBatteryCapacity");
        /**  **  **/SubCategory syscall_scePowerGetCallbackMode                         (syscall_scePower, "scePowerGetCallbackMode");
        /**  **  **/SubCategory syscall_scePowerGetBusClockFrequencyInt                 (syscall_scePower, "scePowerGetBusClockFrequencyInt");
        /**  **  **/SubCategory syscall_scePowerUnlock                                  (syscall_scePower, "scePowerUnlock");
        /**  **  **/SubCategory syscall_scePowerGetBatteryChargeCycle                   (syscall_scePower, "scePowerGetBatteryChargeCycle");
        /**  **  **/SubCategory syscall_scePowerIsLowBattery                            (syscall_scePower, "scePowerIsLowBattery");
        /**  **  **/SubCategory syscall_scePowerLock                                    (syscall_scePower, "scePowerLock");
        /**  **  **/SubCategory syscall_scePowerCancelRequest                           (syscall_scePower, "scePowerCancelRequest");
        /**  **  **/SubCategory syscall_scePowerUnregitserCallback                      (syscall_scePower, "scePowerUnregitserCallback");
        /**  **  **/SubCategory syscall_scePowerUnregisterCallback                      (syscall_scePower, "scePowerUnregisterCallback");
        /**  **  **/SubCategory syscall_scePower_E8E4E204                               (syscall_scePower, "scePower_E8E4E204");
        /**  **  **/SubCategory syscall_scePowerGetPllClockFrequencyFloat               (syscall_scePower, "scePowerGetPllClockFrequencyFloat");
        /**  **  **/SubCategory syscall_scePower_EBD177D6                               (syscall_scePower, "scePower_EBD177D6");
        /**  **  **/SubCategory syscall_scePowerGetIdleTimer                            (syscall_scePower, "scePowerGetIdleTimer");
        /**  **  **/SubCategory syscall_scePowerTick                                    (syscall_scePower, "scePowerTick");
        /**  **  **/SubCategory syscall_scePowerVolatileMemTryLock                      (syscall_scePower, "scePowerVolatileMemTryLock");
        /**  **  **/SubCategory syscall_scePowerGetBatteryFullCapacity                  (syscall_scePower, "scePowerGetBatteryFullCapacity");
        /**  **  **/SubCategory syscall_scePowerGetCpuClockFrequencyInt                 (syscall_scePower, "scePowerGetCpuClockFrequencyInt");
        /**  **  **/SubCategory syscall_scePowerGetCpuClockFrequency                    (syscall_scePower, "scePowerGetCpuClockFrequency");
        /**/SubCategory syscall_usb_prx                                         (syscalls, "usb.prx");
        /**  **/SubCategory syscall_sceUsb                                          (syscall_usb_prx, "sceUsb");
        /**  **  **/SubCategory syscall_sceUsbGetDrvState                               (syscall_sceUsb, "sceUsbGetDrvState");
        /**  **  **/SubCategory syscall_sceUsbWaitCancel                                (syscall_sceUsb, "sceUsbWaitCancel");
        /**  **  **/SubCategory syscall_sceUsbGetDrvList                                (syscall_sceUsb, "sceUsbGetDrvList");
        /**  **  **/SubCategory syscall_sceUsbActivate                                  (syscall_sceUsb, "sceUsbActivate");
        /**  **  **/SubCategory syscall_sceUsbWaitState                                 (syscall_sceUsb, "sceUsbWaitState");
        /**  **  **/SubCategory syscall_sceUsbWaitStateCB                               (syscall_sceUsb, "sceUsbWaitStateCB");
        /**  **  **/SubCategory syscall_sceUsb_89DE0DC5                                 (syscall_sceUsb, "sceUsb_89DE0DC5");
        /**  **  **/SubCategory syscall_sceUsb_8BFC3DE8                                 (syscall_sceUsb, "sceUsb_8BFC3DE8");
        /**  **  **/SubCategory syscall_sceUsbStart                                     (syscall_sceUsb, "sceUsbStart");
        /**  **  **/SubCategory syscall_sceUsbGetState                                  (syscall_sceUsb, "sceUsbGetState");
        /**  **  **/SubCategory syscall_sceUsbStop                                      (syscall_sceUsb, "sceUsbStop");
        /**  **  **/SubCategory syscall_sceUsbDeactivate                                (syscall_sceUsb, "sceUsbDeactivate");
        /**  **  **/SubCategory syscall_sceUsbActivateWithCharging                      (syscall_sceUsb, "sceUsbActivateWithCharging");
        /**/SubCategory syscall_openpsid_prx                                    (syscalls, "openpsid.prx");
        /**  **/SubCategory syscall_sceOpenPSID                                     (syscall_openpsid_prx, "sceOpenPSID");
        /**  **  **/SubCategory syscall_sceOpenPSIDGetOpenPSID                          (syscall_sceOpenPSID, "sceOpenPSIDGetOpenPSID");
        /**  **/SubCategory syscall_sceDdrdb                                        (syscall_openpsid_prx, "sceDdrdb");
        /**  **  **/SubCategory syscall_sceDdrdb_F013F8BF                               (syscall_sceDdrdb, "sceDdrdb_F013F8BF");
        /**/SubCategory syscall_sircs_prx                                       (syscalls, "sircs.prx");
        /**  **/SubCategory syscall_sceSircs                                        (syscall_sircs_prx, "sceSircs");
        /**  **  **/SubCategory syscall_sceSircsSend                                    (syscall_sceSircs, "sceSircsSend");
        /**  **  **/SubCategory syscall_sceSircsReceive                                 (syscall_sceSircs, "sceSircsReceive");
        /**/SubCategory syscall_mediaman_prx                                    (syscalls, "mediaman.prx");
        /**  **/SubCategory syscall_sceUmdUser                                      (syscall_mediaman_prx, "sceUmdUser");
        /**  **  **/SubCategory syscall_sceUmdGetErrorStat                              (syscall_sceUmdUser, "sceUmdGetErrorStat");
        /**  **  **/SubCategory syscall_sceUmdGetDiscInfo                               (syscall_sceUmdUser, "sceUmdGetDiscInfo");
        /**  **  **/SubCategory syscall_sceUmdCheckMedium                               (syscall_sceUmdUser, "sceUmdCheckMedium");
        /**  **  **/SubCategory syscall_sceUmdWaitDriveStatCB                           (syscall_sceUmdUser, "sceUmdWaitDriveStatCB");
        /**  **  **/SubCategory syscall_sceUmdWaitDriveStatWithTimer                    (syscall_sceUmdUser, "sceUmdWaitDriveStatWithTimer");
        /**  **  **/SubCategory syscall_sceUmdCancelWaitDriveStat                       (syscall_sceUmdUser, "sceUmdCancelWaitDriveStat");
        /**  **  **/SubCategory syscall_sceUmdGetDriveStat                              (syscall_sceUmdUser, "sceUmdGetDriveStat");
        /**  **  **/SubCategory syscall_sceUmdReplaceProhibit                           (syscall_sceUmdUser, "sceUmdReplaceProhibit");
        /**  **  **/SubCategory syscall_sceUmdWaitDriveStat                             (syscall_sceUmdUser, "sceUmdWaitDriveStat");
        /**  **  **/SubCategory syscall_sceUmdRegisterUMDCallBack                       (syscall_sceUmdUser, "sceUmdRegisterUMDCallBack");
        /**  **  **/SubCategory syscall_sceUmdUnRegisterUMDCallBack                     (syscall_sceUmdUser, "sceUmdUnRegisterUMDCallBack");
        /**  **  **/SubCategory syscall_sceUmdActivate                                  (syscall_sceUmdUser, "sceUmdActivate");
        /**  **  **/SubCategory syscall_sceUmdReplacePermit                             (syscall_sceUmdUser, "sceUmdReplacePermit");
        /**  **  **/SubCategory syscall_sceUmdDeactivate                                (syscall_sceUmdUser, "sceUmdDeactivate");
        /**/SubCategory syscall_wlan_prx                                        (syscalls, "wlan.prx");
        /**  **/SubCategory syscall_sceWlanDrv                                      (syscall_wlan_prx, "sceWlanDrv");
        /**  **  **/SubCategory syscall_sceWlanGetEtherAddr                             (syscall_sceWlanDrv, "sceWlanGetEtherAddr");
        /**  **  **/SubCategory syscall_sceWlanDevIsPowerOn                             (syscall_sceWlanDrv, "sceWlanDevIsPowerOn");
        /**  **  **/SubCategory syscall_sceWlanGetSwitchState                           (syscall_sceWlanDrv, "sceWlanGetSwitchState");
        /**  **/SubCategory syscall_sceWlanDrv_lib                                  (syscall_wlan_prx, "sceWlanDrv_lib");
        /**  **  **/SubCategory syscall_sceWlanDevGetStateGPIO                          (syscall_sceWlanDrv_lib, "sceWlanDevGetStateGPIO");
        /**  **  **/SubCategory syscall_sceWlanDevGetMacAddr                            (syscall_sceWlanDrv_lib, "sceWlanDevGetMacAddr");
        /**  **  **/SubCategory syscall_sceWlanDrv_lib_2D0FAE4E                         (syscall_sceWlanDrv_lib, "sceWlanDrv_lib_2D0FAE4E");
        /**  **  **/SubCategory syscall_sceWlanDrv_lib_40B0AA4A                         (syscall_sceWlanDrv_lib, "sceWlanDrv_lib_40B0AA4A");
        /**  **  **/SubCategory syscall_sceWlanGetDropRate                              (syscall_sceWlanDrv_lib, "sceWlanGetDropRate");
        /**  **  **/SubCategory syscall_sceWlanDevAttach                                (syscall_sceWlanDrv_lib, "sceWlanDevAttach");
        /**  **  **/SubCategory syscall_sceWlanDrv_lib_4C14BACA                         (syscall_sceWlanDrv_lib, "sceWlanDrv_lib_4C14BACA");
        /**  **  **/SubCategory syscall_sceWlanGPUnRegisterCallback                     (syscall_sceWlanDrv_lib, "sceWlanGPUnRegisterCallback");
        /**  **  **/SubCategory syscall_sceWlanDrv_lib_56F467CA                         (syscall_sceWlanDrv_lib, "sceWlanDrv_lib_56F467CA");
        /**  **  **/SubCategory syscall_sceWlanDrv_lib_5BAA1FE5                         (syscall_sceWlanDrv_lib, "sceWlanDrv_lib_5BAA1FE5");
        /**  **  **/SubCategory syscall_sceWlanDevIsGameMode                            (syscall_sceWlanDrv_lib, "sceWlanDevIsGameMode");
        /**  **  **/SubCategory syscall_sceWlanGPPrevEstablishActive                    (syscall_sceWlanDrv_lib, "sceWlanGPPrevEstablishActive");
        /**  **  **/SubCategory syscall_sceWlanDrv_lib_6D5C839E                         (syscall_sceWlanDrv_lib, "sceWlanDrv_lib_6D5C839E");
        /**  **  **/SubCategory syscall_sceWlanSetHostDiscover                          (syscall_sceWlanDrv_lib, "sceWlanSetHostDiscover");
        /**  **  **/SubCategory syscall_sceWlanDevSetGPIO                               (syscall_sceWlanDrv_lib, "sceWlanDevSetGPIO");
        /**  **  **/SubCategory syscall_sceWlanDrv_lib_81579D36                         (syscall_sceWlanDrv_lib, "sceWlanDrv_lib_81579D36");
        /**  **  **/SubCategory syscall_sceWlanDrv_lib_8D5F551B                         (syscall_sceWlanDrv_lib, "sceWlanDrv_lib_8D5F551B");
        /**  **  **/SubCategory syscall_sceWlanGPRegisterCallback                       (syscall_sceWlanDrv_lib, "sceWlanGPRegisterCallback");
        /**  **  **/SubCategory syscall_sceWlanGPRecv                                   (syscall_sceWlanDrv_lib, "sceWlanGPRecv");
        /**  **  **/SubCategory syscall_sceWlanGPSend                                   (syscall_sceWlanDrv_lib, "sceWlanGPSend");
        /**  **  **/SubCategory syscall_sceWlanDevDetach                                (syscall_sceWlanDrv_lib, "sceWlanDevDetach");
        /**  **  **/SubCategory syscall_sceWlanSetDropRate                              (syscall_sceWlanDrv_lib, "sceWlanSetDropRate");
        /**  **  **/SubCategory syscall_sceWlanDropCheck                                (syscall_sceWlanDrv_lib, "sceWlanDropCheck");
        /**  **  **/SubCategory syscall_sceWlanSetWakeUp                                (syscall_sceWlanDrv_lib, "sceWlanSetWakeUp");
        /**/SubCategory syscall_registry_prx                                    (syscalls, "registry.prx");
        /**  **/SubCategory syscall_sceReg                                          (syscall_registry_prx, "sceReg");
        /**  **  **/SubCategory syscall_sceRegCloseCategory                             (syscall_sceReg, "sceRegCloseCategory");
        /**  **  **/SubCategory syscall_sceRegFlushCategory                             (syscall_sceReg, "sceRegFlushCategory");
        /**  **  **/SubCategory syscall_sceRegSetKeyValue                               (syscall_sceReg, "sceRegSetKeyValue");
        /**  **  **/SubCategory syscall_sceRegOpenCategory                              (syscall_sceReg, "sceRegOpenCategory");
        /**  **  **/SubCategory syscall_sceRegGetKeyValue                               (syscall_sceReg, "sceRegGetKeyValue");
        /**  **  **/SubCategory syscall_sceRegGetKeysNum                                (syscall_sceReg, "sceRegGetKeysNum");
        /**  **  **/SubCategory syscall_sceRegGetKeys                                   (syscall_sceReg, "sceRegGetKeys");
        /**  **  **/SubCategory syscall_sceRegGetKeyValueByName                         (syscall_sceReg, "sceRegGetKeyValueByName");
        /**  **  **/SubCategory syscall_sceRegRemoveKey                                 (syscall_sceReg, "sceRegRemoveKey");
        /**  **  **/SubCategory syscall_sceRegFlushRegistry                             (syscall_sceReg, "sceRegFlushRegistry");
        /**  **  **/SubCategory syscall_sceRegRemoveCategory                            (syscall_sceReg, "sceRegRemoveCategory");
        /**  **  **/SubCategory syscall_sceRegCreateKey                                 (syscall_sceReg, "sceRegCreateKey");
        /**  **  **/SubCategory syscall_sceReg_835ECE6F                                 (syscall_sceReg, "sceReg_835ECE6F");
        /**  **  **/SubCategory syscall_sceRegOpenRegistry                              (syscall_sceReg, "sceRegOpenRegistry");
        /**  **  **/SubCategory syscall_sceRegExit                                      (syscall_sceReg, "sceRegExit");
        /**  **  **/SubCategory syscall_sceReg_BE8C1263                                 (syscall_sceReg, "sceReg_BE8C1263");
        /**  **  **/SubCategory syscall_sceRegGetKeyInfoByName                          (syscall_sceReg, "sceRegGetKeyInfoByName");
        /**  **  **/SubCategory syscall_sceRegGetKeyInfo                                (syscall_sceReg, "sceRegGetKeyInfo");
        /**  **  **/SubCategory syscall_sceRegRemoveRegistry                            (syscall_sceReg, "sceRegRemoveRegistry");
        /**  **  **/SubCategory syscall_sceRegCloseRegistry                             (syscall_sceReg, "sceRegCloseRegistry");
        /**/SubCategory syscall_utility_prx                                     (syscalls, "utility.prx");
        /**  **/SubCategory syscall_sceUtility                                      (syscall_utility_prx, "sceUtility");
        /**  **  **/SubCategory syscall_sceUtility_0251B134                             (syscall_sceUtility, "sceUtility_0251B134");
        /**  **  **/SubCategory syscall_sceUtilityHtmlViewerUpdate                      (syscall_sceUtility, "sceUtilityHtmlViewerUpdate");
        /**  **  **/SubCategory syscall_sceUtility_06A48659                             (syscall_sceUtility, "sceUtility_06A48659");
        /**  **  **/SubCategory syscall_sceUtilityLoadUsbModule                         (syscall_sceUtility, "sceUtilityLoadUsbModule");
        /**  **  **/SubCategory syscall_sceUtility_0F3EEAAC                             (syscall_sceUtility, "sceUtility_0F3EEAAC");
        /**  **  **/SubCategory syscall_sceUtilityInstallInitStart                      (syscall_sceUtility, "sceUtilityInstallInitStart");
        /**  **  **/SubCategory syscall_sceUtility_147F7C85                             (syscall_sceUtility, "sceUtility_147F7C85");
        /**  **  **/SubCategory syscall_sceUtility_149A7895                             (syscall_sceUtility, "sceUtility_149A7895");
        /**  **  **/SubCategory syscall_sceUtilityLoadNetModule                         (syscall_sceUtility, "sceUtilityLoadNetModule");
        /**  **  **/SubCategory syscall_sceUtility_16A1A8D8                             (syscall_sceUtility, "sceUtility_16A1A8D8");
        /**  **  **/SubCategory syscall_sceUtility_16D02AF0                             (syscall_sceUtility, "sceUtility_16D02AF0");
        /**  **  **/SubCategory syscall_sceUtility_28D35634                             (syscall_sceUtility, "sceUtility_28D35634");
        /**  **  **/SubCategory syscall_sceUtility_2995D020                             (syscall_sceUtility, "sceUtility_2995D020");
        /**  **  **/SubCategory syscall_sceUtilityLoadModule                            (syscall_sceUtility, "sceUtilityLoadModule");
        /**  **  **/SubCategory syscall_sceUtilityMsgDialogInitStart                    (syscall_sceUtility, "sceUtilityMsgDialogInitStart");
        /**  **  **/SubCategory syscall_sceUtility_2B96173B                             (syscall_sceUtility, "sceUtility_2B96173B");
        /**  **  **/SubCategory syscall_sceUtilityGetSystemParamString                  (syscall_sceUtility, "sceUtilityGetSystemParamString");
        /**  **  **/SubCategory syscall_sceUtility_3AAD51DC                             (syscall_sceUtility, "sceUtility_3AAD51DC");
        /**  **  **/SubCategory syscall_sceNetplayDialogInitStart                       (syscall_sceUtility, "sceNetplayDialogInitStart");
        /**  **  **/SubCategory syscall_sceUtilityOskShutdownStart                      (syscall_sceUtility, "sceUtilityOskShutdownStart");
        /**  **  **/SubCategory syscall_sceNetplayDialogUpdate                          (syscall_sceUtility, "sceNetplayDialogUpdate");
        /**  **  **/SubCategory syscall_sceUtilitySetSystemParamString                  (syscall_sceUtility, "sceUtilitySetSystemParamString");
        /**  **  **/SubCategory syscall_sceUtility_42071A83                             (syscall_sceUtility, "sceUtility_42071A83");
        /**  **  **/SubCategory syscall_sceUtilityGetNetParam                           (syscall_sceUtility, "sceUtilityGetNetParam");
        /**  **  **/SubCategory syscall_sceUtilitySetSystemParamInt                     (syscall_sceUtility, "sceUtilitySetSystemParamInt");
        /**  **  **/SubCategory syscall_sceUtilityMsgDialogAbort                        (syscall_sceUtility, "sceUtilityMsgDialogAbort");
        /**  **  **/SubCategory syscall_sceUtility_4A833BA4                             (syscall_sceUtility, "sceUtility_4A833BA4");
        /**  **  **/SubCategory syscall_sceUtility_4B0A8FE5                             (syscall_sceUtility, "sceUtility_4B0A8FE5");
        /**  **  **/SubCategory syscall_sceUtilityOskUpdate                             (syscall_sceUtility, "sceUtilityOskUpdate");
        /**  **  **/SubCategory syscall_sceUtilityNetconfInitStart                      (syscall_sceUtility, "sceUtilityNetconfInitStart");
        /**  **  **/SubCategory syscall_sceUtilityGetNetParamLatestID                   (syscall_sceUtility, "sceUtilityGetNetParamLatestID");
        /**  **  **/SubCategory syscall_sceUtilitySavedataInitStart                     (syscall_sceUtility, "sceUtilitySavedataInitStart");
        /**  **  **/SubCategory syscall_sceUtility_54A5C62F                             (syscall_sceUtility, "sceUtility_54A5C62F");
        /**  **  **/SubCategory syscall_sceUtilityCheckNetParam                         (syscall_sceUtility, "sceUtilityCheckNetParam");
        /**  **  **/SubCategory syscall_sceUtilityInstallShutdownStart                  (syscall_sceUtility, "sceUtilityInstallShutdownStart");
        /**  **  **/SubCategory syscall_sceUtilityNetconfGetStatus                      (syscall_sceUtility, "sceUtilityNetconfGetStatus");
        /**  **  **/SubCategory syscall_sceUtilityUnloadNetModule                       (syscall_sceUtility, "sceUtilityUnloadNetModule");
        /**  **  **/SubCategory syscall_sceUtilityMsgDialogShutdownStart                (syscall_sceUtility, "sceUtilityMsgDialogShutdownStart");
        /**  **  **/SubCategory syscall_sceUtility_6F56F9CF                             (syscall_sceUtility, "sceUtility_6F56F9CF");
        /**  **  **/SubCategory syscall_sceUtility_70267ADF                             (syscall_sceUtility, "sceUtility_70267ADF");
        /**  **  **/SubCategory syscall_sceUtilityGameSharingUpdate                     (syscall_sceUtility, "sceUtilityGameSharingUpdate");
        /**  **  **/SubCategory syscall_sceUtility_81C44706                             (syscall_sceUtility, "sceUtility_81C44706");
        /**  **  **/SubCategory syscall_sceUtility_8326AB05                             (syscall_sceUtility, "sceUtility_8326AB05");
        /**  **  **/SubCategory syscall_sceUtility_86A03A27                             (syscall_sceUtility, "sceUtility_86A03A27");
        /**  **  **/SubCategory syscall_sceUtility_86ABDB1B                             (syscall_sceUtility, "sceUtility_86ABDB1B");
        /**  **  **/SubCategory syscall_sceUtilitySavedataGetStatus                     (syscall_sceUtility, "sceUtilitySavedataGetStatus");
        /**  **  **/SubCategory syscall_sceUtility_88BC7406                             (syscall_sceUtility, "sceUtility_88BC7406");
        /**  **  **/SubCategory syscall_sceUtility_89317C8F                             (syscall_sceUtility, "sceUtility_89317C8F");
        /**  **  **/SubCategory syscall_sceUtilityNetconfUpdate                         (syscall_sceUtility, "sceUtilityNetconfUpdate");
        /**  **  **/SubCategory syscall_sceUtility_943CBA46                             (syscall_sceUtility, "sceUtility_943CBA46");
        /**  **  **/SubCategory syscall_sceUtilityGameSharingGetStatus                  (syscall_sceUtility, "sceUtilityGameSharingGetStatus");
        /**  **  **/SubCategory syscall_sceUtilityMsgDialogUpdate                       (syscall_sceUtility, "sceUtilityMsgDialogUpdate");
        /**  **  **/SubCategory syscall_sceUtilitySavedataShutdownStart                 (syscall_sceUtility, "sceUtilitySavedataShutdownStart");
        /**  **  **/SubCategory syscall_sceUtilityMsgDialogGetStatus                    (syscall_sceUtility, "sceUtilityMsgDialogGetStatus");
        /**  **  **/SubCategory syscall_sceUtilityInstallUpdate                         (syscall_sceUtility, "sceUtilityInstallUpdate");
        /**  **  **/SubCategory syscall_sceUtility_A084E056                             (syscall_sceUtility, "sceUtility_A084E056");
        /**  **  **/SubCategory syscall_sceUtility_A50E5B30                             (syscall_sceUtility, "sceUtility_A50E5B30");
        /**  **  **/SubCategory syscall_sceUtilityGetSystemParamInt                     (syscall_sceUtility, "sceUtilityGetSystemParamInt");
        /**  **  **/SubCategory syscall_sceUtility_AB083EA9                             (syscall_sceUtility, "sceUtility_AB083EA9");
        /**  **  **/SubCategory syscall_sceUtility_B0FB7FF5                             (syscall_sceUtility, "sceUtility_B0FB7FF5");
        /**  **  **/SubCategory syscall_sceUtility_B62A4061                             (syscall_sceUtility, "sceUtility_B62A4061");
        /**  **  **/SubCategory syscall_sceNetplayDialogGetStatus                       (syscall_sceUtility, "sceNetplayDialogGetStatus");
        /**  **  **/SubCategory syscall_sceUtility_B8592D5F                             (syscall_sceUtility, "sceUtility_B8592D5F");
        /**  **  **/SubCategory syscall_sceNetplayDialogShutdownStart                   (syscall_sceUtility, "sceNetplayDialogShutdownStart");
        /**  **  **/SubCategory syscall_sceUtilityHtmlViewerGetStatus                   (syscall_sceUtility, "sceUtilityHtmlViewerGetStatus");
        /**  **  **/SubCategory syscall_sceUtilityInstallGetStatus                      (syscall_sceUtility, "sceUtilityInstallGetStatus");
        /**  **  **/SubCategory syscall_sceUtilityGameSharingInitStart                  (syscall_sceUtility, "sceUtilityGameSharingInitStart");
        /**  **  **/SubCategory syscall_sceUtilityLoadAvModule                          (syscall_sceUtility, "sceUtilityLoadAvModule");
        /**  **  **/SubCategory syscall_sceUtilityHtmlViewerInitStart                   (syscall_sceUtility, "sceUtilityHtmlViewerInitStart");
        /**  **  **/SubCategory syscall_sceUtility_D17A0573                             (syscall_sceUtility, "sceUtility_D17A0573");
        /**  **  **/SubCategory syscall_sceUtilitySavedataUpdate                        (syscall_sceUtility, "sceUtilitySavedataUpdate");
        /**  **  **/SubCategory syscall_sceUtility_D81957B7                             (syscall_sceUtility, "sceUtility_D81957B7");
        /**  **  **/SubCategory syscall_sceUtility_D852CDCE                             (syscall_sceUtility, "sceUtility_D852CDCE");
        /**  **  **/SubCategory syscall_sceUtility_DA97F1AA                             (syscall_sceUtility, "sceUtility_DA97F1AA");
        /**  **  **/SubCategory syscall_sceUtility_DDE5389D                             (syscall_sceUtility, "sceUtility_DDE5389D");
        /**  **  **/SubCategory syscall_sceUtility_E19C97D6                             (syscall_sceUtility, "sceUtility_E19C97D6");
        /**  **  **/SubCategory syscall_sceUtilityUnloadModule                          (syscall_sceUtility, "sceUtilityUnloadModule");
        /**  **  **/SubCategory syscall_sceUtility_E7B778D8                             (syscall_sceUtility, "sceUtility_E7B778D8");
        /**  **  **/SubCategory syscall_sceUtility_ECE1D3E5                             (syscall_sceUtility, "sceUtility_ECE1D3E5");
        /**  **  **/SubCategory syscall_sceUtility_ED0FAD38                             (syscall_sceUtility, "sceUtility_ED0FAD38");
        /**  **  **/SubCategory syscall_sceUtility_EF3582B2                             (syscall_sceUtility, "sceUtility_EF3582B2");
        /**  **  **/SubCategory syscall_sceUtilityGameSharingShutdownStart              (syscall_sceUtility, "sceUtilityGameSharingShutdownStart");
        /**  **  **/SubCategory syscall_sceUtilityOskGetStatus                          (syscall_sceUtility, "sceUtilityOskGetStatus");
        /**  **  **/SubCategory syscall_sceUtility_F3FBC572                             (syscall_sceUtility, "sceUtility_F3FBC572");
        /**  **  **/SubCategory syscall_sceUtilityHtmlViewerShutdownStart               (syscall_sceUtility, "sceUtilityHtmlViewerShutdownStart");
        /**  **  **/SubCategory syscall_sceUtilityOskInitStart                          (syscall_sceUtility, "sceUtilityOskInitStart");
        /**  **  **/SubCategory syscall_sceUtilityUnloadUsbModule                       (syscall_sceUtility, "sceUtilityUnloadUsbModule");
        /**  **  **/SubCategory syscall_sceUtilityUnloadAvModule                        (syscall_sceUtility, "sceUtilityUnloadAvModule");
        /**  **  **/SubCategory syscall_sceUtilityNetconfShutdownStart                  (syscall_sceUtility, "sceUtilityNetconfShutdownStart");
        /**  **  **/SubCategory syscall_sceUtility_F9E0008C                             (syscall_sceUtility, "sceUtility_F9E0008C");
        /**  **/SubCategory syscall_sceUtility_private                              (syscall_utility_prx, "sceUtility_private");
        /**  **  **/SubCategory syscall_sceUtility_private_03043DAF                     (syscall_sceUtility_private, "sceUtility_private_03043DAF");
        /**  **  **/SubCategory syscall_sceUtility_private_0CF833E5                     (syscall_sceUtility_private, "sceUtility_private_0CF833E5");
        /**  **  **/SubCategory syscall_sceUtility_private_107CA63E                     (syscall_sceUtility_private, "sceUtility_private_107CA63E");
        /**  **  **/SubCategory syscall_sceUtility_private_11236637                     (syscall_sceUtility_private, "sceUtility_private_11236637");
        /**  **  **/SubCategory syscall_sceUtility_private_1FD567D4                     (syscall_sceUtility_private, "sceUtility_private_1FD567D4");
        /**  **  **/SubCategory syscall_sceUtility_private_23FE0D1B                     (syscall_sceUtility_private, "sceUtility_private_23FE0D1B");
        /**  **  **/SubCategory syscall_sceUtility_private_284DBC23                     (syscall_sceUtility_private, "sceUtility_private_284DBC23");
        /**  **  **/SubCategory syscall_sceUtility_private_2A9524EF                     (syscall_sceUtility_private, "sceUtility_private_2A9524EF");
        /**  **  **/SubCategory syscall_sceUtility_private_2F265D64                     (syscall_sceUtility_private, "sceUtility_private_2F265D64");
        /**  **  **/SubCategory syscall_sceUtility_private_34892525                     (syscall_sceUtility_private, "sceUtility_private_34892525");
        /**  **  **/SubCategory syscall_sceUtility_private_3B76A6D0                     (syscall_sceUtility_private, "sceUtility_private_3B76A6D0");
        /**  **  **/SubCategory syscall_sceUtility_private_3EBDB7F6                     (syscall_sceUtility_private, "sceUtility_private_3EBDB7F6");
        /**  **  **/SubCategory syscall_sceUtility_private_47FA0F9B                     (syscall_sceUtility_private, "sceUtility_private_47FA0F9B");
        /**  **  **/SubCategory syscall_sceUtility_private_4B069019                     (syscall_sceUtility_private, "sceUtility_private_4B069019");
        /**  **  **/SubCategory syscall_sceUtility_private_5B3C096F                     (syscall_sceUtility_private, "sceUtility_private_5B3C096F");
        /**  **  **/SubCategory syscall_sceUtility_private_6513E388                     (syscall_sceUtility_private, "sceUtility_private_6513E388");
        /**  **  **/SubCategory syscall_sceUtility_private_6B0356F6                     (syscall_sceUtility_private, "sceUtility_private_6B0356F6");
        /**  **  **/SubCategory syscall_sceUtility_private_6D2D8A41                     (syscall_sceUtility_private, "sceUtility_private_6D2D8A41");
        /**  **  **/SubCategory syscall_sceUtility_private_6D73DD7C                     (syscall_sceUtility_private, "sceUtility_private_6D73DD7C");
        /**  **  **/SubCategory syscall_sceUtility_private_7139732A                     (syscall_sceUtility_private, "sceUtility_private_7139732A");
        /**  **  **/SubCategory syscall_sceUtility_private_84A1E70F                     (syscall_sceUtility_private, "sceUtility_private_84A1E70F");
        /**  **  **/SubCategory syscall_sceUtility_private_84FEFEAD                     (syscall_sceUtility_private, "sceUtility_private_84FEFEAD");
        /**  **  **/SubCategory syscall_sceUtility_private_8A80D4EE                     (syscall_sceUtility_private, "sceUtility_private_8A80D4EE");
        /**  **  **/SubCategory syscall_sceUtility_private_8E7B9318                     (syscall_sceUtility_private, "sceUtility_private_8E7B9318");
        /**  **  **/SubCategory syscall_sceUtility_private_9AEFABC9                     (syscall_sceUtility_private, "sceUtility_private_9AEFABC9");
        /**  **  **/SubCategory syscall_sceUtility_private_9E8CD6BC                     (syscall_sceUtility_private, "sceUtility_private_9E8CD6BC");
        /**  **  **/SubCategory syscall_sceUtility_private_A1A4A4D3                     (syscall_sceUtility_private, "sceUtility_private_A1A4A4D3");
        /**  **  **/SubCategory syscall_sceUtility_private_A1DF25E8                     (syscall_sceUtility_private, "sceUtility_private_A1DF25E8");
        /**  **  **/SubCategory syscall_sceUtility_private_A5D7DC3E                     (syscall_sceUtility_private, "sceUtility_private_A5D7DC3E");
        /**  **  **/SubCategory syscall_sceUtility_private_ACAFCBA3                     (syscall_sceUtility_private, "sceUtility_private_ACAFCBA3");
        /**  **  **/SubCategory syscall_sceUtility_private_ACDC84F3                     (syscall_sceUtility_private, "sceUtility_private_ACDC84F3");
        /**  **  **/SubCategory syscall_sceUtility_private_AEADFF11                     (syscall_sceUtility_private, "sceUtility_private_AEADFF11");
        /**  **  **/SubCategory syscall_sceUtility_private_AFC70B22                     (syscall_sceUtility_private, "sceUtility_private_AFC70B22");
        /**  **  **/SubCategory syscall_sceUtility_private_B06FE2AB                     (syscall_sceUtility_private, "sceUtility_private_B06FE2AB");
        /**  **  **/SubCategory syscall_sceUtility_private_B618DCC7                     (syscall_sceUtility_private, "sceUtility_private_B618DCC7");
        /**  **  **/SubCategory syscall_sceUtility_private_BF218ECC                     (syscall_sceUtility_private, "sceUtility_private_BF218ECC");
        /**  **  **/SubCategory syscall_sceUtility_private_C5F825B6                     (syscall_sceUtility_private, "sceUtility_private_C5F825B6");
        /**  **  **/SubCategory syscall_sceUtility_private_C652A9B0                     (syscall_sceUtility_private, "sceUtility_private_C652A9B0");
        /**  **  **/SubCategory syscall_sceUtility_private_CF9DB393                     (syscall_sceUtility_private, "sceUtility_private_CF9DB393");
        /**  **  **/SubCategory syscall_sceUtility_private_D6F31E47                     (syscall_sceUtility_private, "sceUtility_private_D6F31E47");
        /**  **  **/SubCategory syscall_sceUtility_private_DCCC4CE2                     (syscall_sceUtility_private, "sceUtility_private_DCCC4CE2");
        /**  **  **/SubCategory syscall_sceUtility_private_E16F76D4                     (syscall_sceUtility_private, "sceUtility_private_E16F76D4");
        /**  **  **/SubCategory syscall_sceUtility_private_EAABCB99                     (syscall_sceUtility_private, "sceUtility_private_EAABCB99");
        /**  **  **/SubCategory syscall_sceUtility_private_EF6B75B3                     (syscall_sceUtility_private, "sceUtility_private_EF6B75B3");
        /**  **  **/SubCategory syscall_sceUtility_private_FBCC79F8                     (syscall_sceUtility_private, "sceUtility_private_FBCC79F8");
        /**  **  **/SubCategory syscall_sceUtility_private_FC6A5184                     (syscall_sceUtility_private, "sceUtility_private_FC6A5184");
        /**  **/SubCategory syscall_sceUtility_netparam_internal                    (syscall_utility_prx, "sceUtility_netparam_internal");
        /**  **  **/SubCategory syscall_sceUtility_netparam_internal_0BA36F3F           (syscall_sceUtility_netparam_internal, "sceUtility_netparam_internal_0BA36F3F");
        /**  **  **/SubCategory syscall_sceUtility_netparam_internal_0E244DD7           (syscall_sceUtility_netparam_internal, "sceUtility_netparam_internal_0E244DD7");
        /**  **  **/SubCategory syscall_sceUtility_netparam_internal_4CBB0CA0           (syscall_sceUtility_netparam_internal, "sceUtility_netparam_internal_4CBB0CA0");
        /**  **  **/SubCategory syscall_sceUtility_netparam_internal_BEE92A0A           (syscall_sceUtility_netparam_internal, "sceUtility_netparam_internal_BEE92A0A");
        /**  **  **/SubCategory syscall_sceUtility_netparam_internal_F161E17A           (syscall_sceUtility_netparam_internal, "sceUtility_netparam_internal_F161E17A");
        /**  **  **/SubCategory syscall_sceUtility_netparam_internal_F547B8FC           (syscall_sceUtility_netparam_internal, "sceUtility_netparam_internal_F547B8FC");
        /**  **  **/SubCategory syscall_sceUtility_netparam_internal_FD539533           (syscall_sceUtility_netparam_internal, "sceUtility_netparam_internal_FD539533");
        /**/SubCategory syscall_mesg_led_prx                                    (syscalls, "mesg_led.prx");
        /**  **/SubCategory syscall_sceResmgr                                       (syscall_mesg_led_prx, "sceResmgr");
        /**  **  **/SubCategory syscall_sceResmgr_9DC14891                              (syscall_sceResmgr, "sceResmgr_9DC14891");
        /**  **/SubCategory syscall_scePauth                                        (syscall_mesg_led_prx, "scePauth");
        /**  **  **/SubCategory syscall_scePauth_F7AA47F6                               (syscall_scePauth, "scePauth_F7AA47F6");
        /**/SubCategory syscall_impose_prx                                      (syscalls, "impose.prx");
        /**  **/SubCategory syscall_sceImpose                                       (syscall_impose_prx, "sceImpose");
        /**  **  **/SubCategory syscall_sceImposeGetHomePopup                           (syscall_sceImpose, "sceImposeGetHomePopup");
        /**  **  **/SubCategory syscall_sceImposeGetLanguageMode                        (syscall_sceImpose, "sceImposeGetLanguageMode");
        /**  **  **/SubCategory syscall_sceImposeSetLanguageMode                        (syscall_sceImpose, "sceImposeSetLanguageMode");
        /**  **  **/SubCategory syscall_sceImposeHomeButton                             (syscall_sceImpose, "sceImposeHomeButton");
        /**  **  **/SubCategory syscall_sceImposeSetHomePopup                           (syscall_sceImpose, "sceImposeSetHomePopup");
        /**  **  **/SubCategory syscall_sceImposeSetUMDPopup                            (syscall_sceImpose, "sceImposeSetUMDPopup");
        /**  **  **/SubCategory syscall_sceImposeGetBatteryIconStatus                   (syscall_sceImpose, "sceImposeGetBatteryIconStatus");
        /**  **  **/SubCategory syscall_sceImposeGetBacklightOffTime                    (syscall_sceImpose, "sceImposeGetBacklightOffTime");
        /**  **  **/SubCategory syscall_sceImposeSetBacklightOffTime                    (syscall_sceImpose, "sceImposeSetBacklightOffTime");
        /**  **  **/SubCategory syscall_sceImpose_9BA61B49                              (syscall_sceImpose, "sceImpose_9BA61B49");
        /**  **  **/SubCategory syscall_sceImpose_A9884B00                              (syscall_sceImpose, "sceImpose_A9884B00");
        /**  **  **/SubCategory syscall_sceImpose_BB3F5DEC                              (syscall_sceImpose, "sceImpose_BB3F5DEC");
        /**  **  **/SubCategory syscall_sceImposeGetUMDPopup                            (syscall_sceImpose, "sceImposeGetUMDPopup");
        /**  **  **/SubCategory syscall_sceImpose_FCD44963                              (syscall_sceImpose, "sceImpose_FCD44963");
        /**  **  **/SubCategory syscall_sceImpose_FF1A2F07                              (syscall_sceImpose, "sceImpose_FF1A2F07");
        /**  **/SubCategory syscall_sceAudioRouting                                 (syscall_impose_prx, "sceAudioRouting");
        /**  **  **/SubCategory syscall_sceAudioRoutingGetVolumeMode                    (syscall_sceAudioRouting, "sceAudioRoutingGetVolumeMode");
        /**  **  **/SubCategory syscall_sceAudioRoutingSetMode                          (syscall_sceAudioRouting, "sceAudioRoutingSetMode");
        /**  **  **/SubCategory syscall_sceAudioRoutingGetMode                          (syscall_sceAudioRouting, "sceAudioRoutingGetMode");
        /**  **  **/SubCategory syscall_sceAudioRoutingSetVolumeMode                    (syscall_sceAudioRouting, "sceAudioRoutingSetVolumeMode");
        /**/SubCategory syscall_usersystemlib_prx                               (syscalls, "usersystemlib.prx");
        /**  **/SubCategory syscall_Kernel_Library                                  (syscall_usersystemlib_prx, "Kernel_Library");
        /**  **  **/SubCategory syscall_sceKernelCpuSuspendIntr                         (syscall_Kernel_Library, "sceKernelCpuSuspendIntr");
        /**  **  **/SubCategory syscall_sceKernelUnlockLwMutex                          (syscall_Kernel_Library, "sceKernelUnlockLwMutex");
        /**  **  **/SubCategory syscall_sceKernelLockLwMutexCB                          (syscall_Kernel_Library, "sceKernelLockLwMutexCB");
        /**  **  **/SubCategory syscall_sceKernelCpuResumeIntrWithSync                  (syscall_Kernel_Library, "sceKernelCpuResumeIntrWithSync");
        /**  **  **/SubCategory syscall_sceKernelIsCpuIntrSuspended                     (syscall_Kernel_Library, "sceKernelIsCpuIntrSuspended");
        /**  **  **/SubCategory syscall_sceKernelCpuResumeIntr                          (syscall_Kernel_Library, "sceKernelCpuResumeIntr");
        /**  **  **/SubCategory syscall_sceKernelIsCpuIntrEnable                        (syscall_Kernel_Library, "sceKernelIsCpuIntrEnable");
        /**  **  **/SubCategory syscall_sceKernelLockLwMutex                            (syscall_Kernel_Library, "sceKernelLockLwMutex");
        /**  **  **/SubCategory syscall_sceKernelReferLwMutexStatus                     (syscall_Kernel_Library, "sceKernelReferLwMutexStatus");
        /**  **  **/SubCategory syscall_sceKernelTryLockLwMutex                         (syscall_Kernel_Library, "sceKernelTryLockLwMutex");
        /**/SubCategory syscall_sc_sascore_prx                                  (syscalls, "sc_sascore.prx");
        /**  **/SubCategory syscall_sceSasCore                                      (syscall_sc_sascore_prx, "sceSasCore");
        /**  **  **/SubCategory syscall___sceSasInit                                    (syscall_sceSasCore, "__sceSasInit");
        /**  **  **/SubCategory syscall___sceSasCore                                    (syscall_sceSasCore, "__sceSasCore");
        /**  **  **/SubCategory syscall___sceSasCoreWithMix                             (syscall_sceSasCore, "__sceSasCoreWithMix");
        /**  **  **/SubCategory syscall___sceSasSetKeyOn                                (syscall_sceSasCore, "__sceSasSetKeyOn");
        /**  **  **/SubCategory syscall___sceSasSetKeyOff                               (syscall_sceSasCore, "__sceSasSetKeyOff");
        /**  **  **/SubCategory syscall___sceSasSetPause                                (syscall_sceSasCore, "__sceSasSetPause");
        /**  **  **/SubCategory syscall___sceSasGetPauseFlag                            (syscall_sceSasCore, "__sceSasGetPauseFlag");
        /**  **  **/SubCategory syscall___sceSasSetVolume                               (syscall_sceSasCore, "__sceSasSetVolume");
        /**  **  **/SubCategory syscall___sceSasSetPitch                                (syscall_sceSasCore, "__sceSasSetPitch");
        /**  **  **/SubCategory syscall___sceSasSetVoice                                (syscall_sceSasCore, "__sceSasSetVoice");
        /**  **  **/SubCategory syscall___sceSasSetNoise                                (syscall_sceSasCore, "__sceSasSetNoise");
        /**  **  **/SubCategory syscall___sceSasSetSteepWave                            (syscall_sceSasCore, "__sceSasSetSteepWave");
        /**  **  **/SubCategory syscall___sceSasSetTrianglarWave                        (syscall_sceSasCore, "__sceSasSetTrianglarWave");
        /**  **  **/SubCategory syscall___sceSasSetVoicePCM                             (syscall_sceSasCore, "__sceSasSetVoicePCM");
        /**  **  **/SubCategory syscall___sceSasSetADSR                                 (syscall_sceSasCore, "__sceSasSetADSR");
        /**  **  **/SubCategory syscall___sceSasSetADSRmode                             (syscall_sceSasCore, "__sceSasSetADSRmode");
        /**  **  **/SubCategory syscall___sceSasSetSL                                   (syscall_sceSasCore, "__sceSasSetSL");
        /**  **  **/SubCategory syscall___sceSasSetSimpleADSR                           (syscall_sceSasCore, "__sceSasSetSimpleADSR");
        /**  **  **/SubCategory syscall___sceSasGetEndFlag                              (syscall_sceSasCore, "__sceSasGetEndFlag");
        /**  **  **/SubCategory syscall___sceSasGetEnvelopeHeight                       (syscall_sceSasCore, "__sceSasGetEnvelopeHeight");
        /**  **  **/SubCategory syscall___sceSasGetAllEnvelopeHeights                   (syscall_sceSasCore, "__sceSasGetAllEnvelopeHeights");
        /**  **  **/SubCategory syscall___sceSasSetGrain                                (syscall_sceSasCore, "__sceSasSetGrain");
        /**  **  **/SubCategory syscall___sceSasGetGrain                                (syscall_sceSasCore, "__sceSasGetGrain");
        /**  **  **/SubCategory syscall___sceSasSetOutputmode                           (syscall_sceSasCore, "__sceSasSetOutputmode");
        /**  **  **/SubCategory syscall___sceSasGetOutputmode                           (syscall_sceSasCore, "__sceSasGetOutputmode");
        /**  **  **/SubCategory syscall___sceSasRevType                                 (syscall_sceSasCore, "__sceSasRevType");
        /**  **  **/SubCategory syscall___sceSasRevParam                                (syscall_sceSasCore, "__sceSasRevParam");
        /**  **  **/SubCategory syscall___sceSasRevEVOL                                 (syscall_sceSasCore, "__sceSasRevEVOL");
        /**  **  **/SubCategory syscall___sceSasRevVON                                  (syscall_sceSasCore, "__sceSasRevVON");
        /**  **  **/SubCategory syscall___sceSasSetVoiceATRAC3                          (syscall_sceSasCore, "__sceSasSetVoiceATRAC3");
        /**  **  **/SubCategory syscall___sceSasConcatenateATRAC3                       (syscall_sceSasCore, "__sceSasConcatenateATRAC3");
        /**  **  **/SubCategory syscall___sceSasUnsetATRAC3                             (syscall_sceSasCore, "__sceSasUnsetATRAC3");
        /**  **/SubCategory syscall_sceP3da                                         (syscall_sc_sascore_prx, "sceP3da");
        /**  **  **/SubCategory syscall_sceP3daBridgeCore                               (syscall_sceP3da, "sceP3daBridgeCore");
        /**  **  **/SubCategory syscall_sceP3daBridgeInit                               (syscall_sceP3da, "sceP3daBridgeInit");
        /**  **  **/SubCategory syscall_sceP3daBridgeExit                               (syscall_sceP3da, "sceP3daBridgeExit");
        /**/SubCategory syscall_libatrac3plus_prx                               (syscalls, "libatrac3plus.prx");
        /**  **/SubCategory syscall_sceAtrac3plus                                   (syscall_libatrac3plus_prx, "sceAtrac3plus");
        /**  **  **/SubCategory syscall_sceAtracGetAtracID                              (syscall_sceAtrac3plus, "sceAtracGetAtracID");
        /**  **  **/SubCategory syscall_sceAtracReleaseAtracID                          (syscall_sceAtrac3plus, "sceAtracReleaseAtracID");
        /**  **  **/SubCategory syscall_sceAtracReinit                                  (syscall_sceAtrac3plus, "sceAtracReinit");
        /**  **  **/SubCategory syscall_sceAtracSetData                                 (syscall_sceAtrac3plus, "sceAtracSetData");
        /**  **  **/SubCategory syscall_sceAtracSetHalfwayBuffer                        (syscall_sceAtrac3plus, "sceAtracSetHalfwayBuffer");
        /**  **  **/SubCategory syscall_sceAtracSetDataAndGetID                         (syscall_sceAtrac3plus, "sceAtracSetDataAndGetID");
        /**  **  **/SubCategory syscall_sceAtracSetHalfwayBufferAndGetID                (syscall_sceAtrac3plus, "sceAtracSetHalfwayBufferAndGetID");
        /**  **  **/SubCategory syscall_sceAtracDecodeData                              (syscall_sceAtrac3plus, "sceAtracDecodeData");
        /**  **  **/SubCategory syscall_sceAtracGetStreamDataInfo                       (syscall_sceAtrac3plus, "sceAtracGetStreamDataInfo");
        /**  **  **/SubCategory syscall_sceAtracAddStreamData                           (syscall_sceAtrac3plus, "sceAtracAddStreamData");
        /**  **  **/SubCategory syscall_sceAtracGetSecondBufferInfo                     (syscall_sceAtrac3plus, "sceAtracGetSecondBufferInfo");
        /**  **  **/SubCategory syscall_sceAtracSetSecondBuffer                         (syscall_sceAtrac3plus, "sceAtracSetSecondBuffer");
        /**  **  **/SubCategory syscall_sceAtracIsSecondBufferNeeded                    (syscall_sceAtrac3plus, "sceAtracIsSecondBufferNeeded");
        /**  **  **/SubCategory syscall_sceAtracGetRemainFrame                          (syscall_sceAtrac3plus, "sceAtracGetRemainFrame");
        /**  **  **/SubCategory syscall_sceAtracGetChannel                              (syscall_sceAtrac3plus, "sceAtracGetChannel");
        /**  **  **/SubCategory syscall_sceAtracGetOutputChannel                        (syscall_sceAtrac3plus, "sceAtracGetOutputChannel");
        /**  **  **/SubCategory syscall_sceAtracGetMaxSample                            (syscall_sceAtrac3plus, "sceAtracGetMaxSample");
        /**  **  **/SubCategory syscall_sceAtracGetNextSample                           (syscall_sceAtrac3plus, "sceAtracGetNextSample");
        /**  **  **/SubCategory syscall_sceAtracGetSoundSample                          (syscall_sceAtrac3plus, "sceAtracGetSoundSample");
        /**  **  **/SubCategory syscall_sceAtracGetNextDecodePosition                   (syscall_sceAtrac3plus, "sceAtracGetNextDecodePosition");
        /**  **  **/SubCategory syscall_sceAtracGetBitrate                              (syscall_sceAtrac3plus, "sceAtracGetBitrate");
        /**  **  **/SubCategory syscall_sceAtracGetLoopStatus                           (syscall_sceAtrac3plus, "sceAtracGetLoopStatus");
        /**  **  **/SubCategory syscall_sceAtracSetLoopNum                              (syscall_sceAtrac3plus, "sceAtracSetLoopNum");
        /**  **  **/SubCategory syscall_sceAtracGetBufferInfoForResetting               (syscall_sceAtrac3plus, "sceAtracGetBufferInfoForResetting");
        /**  **  **/SubCategory syscall_sceAtracResetPlayPosition                       (syscall_sceAtrac3plus, "sceAtracResetPlayPosition");
        /**  **  **/SubCategory syscall_sceAtracGetInternalErrorInfo                    (syscall_sceAtrac3plus, "sceAtracGetInternalErrorInfo");
        /**  **  **/SubCategory syscall_sceAtracSetAA3DataAndGetID                      (syscall_sceAtrac3plus, "sceAtracSetAA3DataAndGetID");
        /**  **  **/SubCategory syscall_sceAtracSetMOutHalfwayBuffer                    (syscall_sceAtrac3plus, "sceAtracSetMOutHalfwayBuffer");
        /**  **  **/SubCategory syscall_sceAtracSetAA3HalfwayBufferAndGetID             (syscall_sceAtrac3plus, "sceAtracSetAA3HalfwayBufferAndGetID");
        /**  **  **/SubCategory syscall_sceAtracGetBufferInfoForReseting                (syscall_sceAtrac3plus, "sceAtracGetBufferInfoForReseting");
        /**  **  **/SubCategory syscall_sceAtracStartEntry                              (syscall_sceAtrac3plus, "sceAtracStartEntry");
        /**  **  **/SubCategory syscall_sceAtracEndEntry                                (syscall_sceAtrac3plus, "sceAtracEndEntry");
        /**  **  **/SubCategory syscall_sceAtracSetMOutHalfwayBufferAndGetID            (syscall_sceAtrac3plus, "sceAtracSetMOutHalfwayBufferAndGetID");
    }
}