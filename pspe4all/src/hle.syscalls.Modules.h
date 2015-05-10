////////////////////////////////////////////////////////////////////////////////
/// This file is auto-generated from pspe4all-nidgen version 0.3
///
#ifndef hle_syscalls_Modules_h__
#define hle_syscalls_Modules_h__

#include "lle.cpu(Allegrex).Context.h"

#define HLE_MODULE(name) { #name, libraries_##name, sizeof_array(libraries_##name) }
#define HLE_LIBRARY(name) { #name, functions_##name, sizeof_array(functions_##name), name##$Init, name##$Fini }
#define HLE_FUNCTION(library, nid, name, format) { 0x##nid, library##_##nid, #name, format, (emu::log::Category *)&emu::log::syscall_##name }

#include "emu.log.h"

namespace emu
{
    namespace log
    {
        extern Category syscalls;
    }
}

namespace hle
{
    struct Module;
    struct Library;

    typedef void __cdecl SyscallHandler(Allegrex::Context & context);
    typedef bool __cdecl InitHandler();
    typedef bool __cdecl FiniHandler();

    using emu::log::Category;

    struct Function
    {
        u32              nid;
        SyscallHandler * handler;
        char const     * name;
        char const     * format;
        Category       * log;
    };

    struct Library
    {
        char const     * name;
        Function       * function_array;
        u32              function_count;
        InitHandler    * init;
        FiniHandler    * fini;
    };

    struct Module
    {
        char const     * name;
        Library        * library_array;
        u32              library_count;
    };

    namespace syscalls
    {

        bool Init();

        bool Fini();

        Function * GetModuleFunction(u32 opcode);

        void WriteSyscall(char const * library_name, u32 nid, u32 address);

        const char * GetSyscallName(char const * library_name, u32 nid);
    }
}

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_sysmem_prx;
        extern SubCategory syscall_SysMemUserForUser;
        extern SubCategory syscall_sceKernelMaxFreeMemSize;
        extern SubCategory syscall_sceKernelTotalFreeMemSize;
        extern SubCategory syscall_sceKernelPrintf;
        extern SubCategory syscall_sceKernelSetCompilerVersion;
        extern SubCategory syscall_sceKernelSetCompiledSdkVersion;
        extern SubCategory syscall_sceKernelDevkitVersion;
        extern SubCategory syscall_sceKernelGetCompiledSdkVersion;
        extern SubCategory syscall_sceKernelAllocPartitionMemory;
        extern SubCategory syscall_sceKernelFreePartitionMemory;
        extern SubCategory syscall_sceKernelGetBlockHeadAddr;
        extern SubCategory syscall_sceKernelQueryMemoryInfo;
        extern SubCategory syscall_SysMemUserForUser_057E7380;
        extern SubCategory syscall_SysMemUserForUser_315AD3A0;
        extern SubCategory syscall_SysMemUserForUser_342061E5;
        extern SubCategory syscall_SysMemUserForUser_50F61D8A;
        extern SubCategory syscall_SysMemUserForUser_91DE343C;
        extern SubCategory syscall_SysMemUserForUser_A6848DF8;
        extern SubCategory syscall_SysMemUserForUser_ACBD88CA;
        extern SubCategory syscall_SysMemUserForUser_D8DE5C1E;
        extern SubCategory syscall_SysMemUserForUser_DB83A952;
        extern SubCategory syscall_SysMemUserForUser_EBD5C3E6;
        extern SubCategory syscall_SysMemUserForUser_FE707FDF;
        extern SubCategory syscall_sceSuspendForUser;
        extern SubCategory syscall_sceKernelPowerLock;
        extern SubCategory syscall_sceKernelPowerUnlock;
        extern SubCategory syscall_sceKernelPowerTick;
        extern SubCategory syscall_sceKernelVolatileMemLock;
        extern SubCategory syscall_sceKernelVolatileMemTryLock;
        extern SubCategory syscall_sceKernelVolatileMemUnlock;
        extern SubCategory syscall_UtilsForUser;
        extern SubCategory syscall_sceKernelDcacheWritebackAll;
        extern SubCategory syscall_sceKernelDcacheWritebackInvalidateAll;
        extern SubCategory syscall_sceKernelDcacheWritebackRange;
        extern SubCategory syscall_sceKernelDcacheWritebackInvalidateRange;
        extern SubCategory syscall_sceKernelDcacheInvalidateRange;
        extern SubCategory syscall_sceKernelDcacheProbe;
        extern SubCategory syscall_sceKernelDcacheProbeRange;
        extern SubCategory syscall_sceKernelDcacheReadTag;
        extern SubCategory syscall_sceKernelIcacheInvalidateAll;
        extern SubCategory syscall_sceKernelIcacheInvalidateRange;
        extern SubCategory syscall_sceKernelIcacheProbe;
        extern SubCategory syscall_sceKernelIcacheReadTag;
        extern SubCategory syscall_sceKernelUtilsMd5Digest;
        extern SubCategory syscall_sceKernelUtilsMd5BlockInit;
        extern SubCategory syscall_sceKernelUtilsMd5BlockUpdate;
        extern SubCategory syscall_sceKernelUtilsMd5BlockResult;
        extern SubCategory syscall_sceKernelUtilsSha1Digest;
        extern SubCategory syscall_sceKernelUtilsSha1BlockInit;
        extern SubCategory syscall_sceKernelUtilsSha1BlockUpdate;
        extern SubCategory syscall_sceKernelUtilsSha1BlockResult;
        extern SubCategory syscall_sceKernelUtilsMt19937Init;
        extern SubCategory syscall_sceKernelUtilsMt19937UInt;
        extern SubCategory syscall_sceKernelGetGPI;
        extern SubCategory syscall_sceKernelSetGPO;
        extern SubCategory syscall_sceKernelLibcClock;
        extern SubCategory syscall_sceKernelLibcTime;
        extern SubCategory syscall_sceKernelLibcGettimeofday;
        extern SubCategory syscall_sceKernelPutUserLog;
        extern SubCategory syscall_UtilsForUser_004D4DEE;
        extern SubCategory syscall_UtilsForUser_157A383A;
        extern SubCategory syscall_UtilsForUser_1B0592A3;
        extern SubCategory syscall_UtilsForUser_39F49610;
        extern SubCategory syscall_UtilsForUser_3FD3D324;
        extern SubCategory syscall_UtilsForUser_43C9A8DB;
        extern SubCategory syscall_UtilsForUser_515B4FAF;
        extern SubCategory syscall_UtilsForUser_5C7F2B1A;
        extern SubCategory syscall_UtilsForUser_6231A71D;
        extern SubCategory syscall_UtilsForUser_7333E539;
        extern SubCategory syscall_UtilsForUser_740DF7F0;
        extern SubCategory syscall_UtilsForUser_99134C3F;
        extern SubCategory syscall_UtilsForUser_AF3766BB;
        extern SubCategory syscall_UtilsForUser_B83A1E76;
        extern SubCategory syscall_UtilsForUser_DBBE9A46;
        extern SubCategory syscall_UtilsForUser_F0155BCA;
    }
}

///////////////// Module : sceSystemMemoryManager (sysmem.prx) /////////////////
///
/// ////////////////////////// Library : SysMemUserForUser /////////////////////////
/// ///
    extern "C" bool __cdecl SysMemUserForUser$Init();
    extern "C" bool __cdecl SysMemUserForUser$Fini();
    extern "C" void __cdecl SysMemUserForUser_A291F107(Allegrex::Context &); // sceKernelMaxFreeMemSize
    extern "C" void __cdecl SysMemUserForUser_F919F628(Allegrex::Context &); // sceKernelTotalFreeMemSize
    extern "C" void __cdecl SysMemUserForUser_13A5ABEF(Allegrex::Context &); // sceKernelPrintf
    extern "C" void __cdecl SysMemUserForUser_F77D77CB(Allegrex::Context &); // sceKernelSetCompilerVersion
    extern "C" void __cdecl SysMemUserForUser_7591C7DB(Allegrex::Context &); // sceKernelSetCompiledSdkVersion
    extern "C" void __cdecl SysMemUserForUser_3FC9AE6A(Allegrex::Context &); // sceKernelDevkitVersion
    extern "C" void __cdecl SysMemUserForUser_FC114573(Allegrex::Context &); // sceKernelGetCompiledSdkVersion
    extern "C" void __cdecl SysMemUserForUser_237DBD4F(Allegrex::Context &); // sceKernelAllocPartitionMemory
    extern "C" void __cdecl SysMemUserForUser_B6D61D02(Allegrex::Context &); // sceKernelFreePartitionMemory
    extern "C" void __cdecl SysMemUserForUser_9D9A5BA1(Allegrex::Context &); // sceKernelGetBlockHeadAddr
    extern "C" void __cdecl SysMemUserForUser_2A3E5280(Allegrex::Context &); // sceKernelQueryMemoryInfo
    extern "C" void __cdecl SysMemUserForUser_057E7380(Allegrex::Context &); // SysMemUserForUser_057E7380
    extern "C" void __cdecl SysMemUserForUser_315AD3A0(Allegrex::Context &); // SysMemUserForUser_315AD3A0
    extern "C" void __cdecl SysMemUserForUser_342061E5(Allegrex::Context &); // SysMemUserForUser_342061E5
    extern "C" void __cdecl SysMemUserForUser_50F61D8A(Allegrex::Context &); // SysMemUserForUser_50F61D8A
    extern "C" void __cdecl SysMemUserForUser_91DE343C(Allegrex::Context &); // SysMemUserForUser_91DE343C
    extern "C" void __cdecl SysMemUserForUser_A6848DF8(Allegrex::Context &); // SysMemUserForUser_A6848DF8
    extern "C" void __cdecl SysMemUserForUser_ACBD88CA(Allegrex::Context &); // SysMemUserForUser_ACBD88CA
    extern "C" void __cdecl SysMemUserForUser_D8DE5C1E(Allegrex::Context &); // SysMemUserForUser_D8DE5C1E
    extern "C" void __cdecl SysMemUserForUser_DB83A952(Allegrex::Context &); // SysMemUserForUser_DB83A952
    extern "C" void __cdecl SysMemUserForUser_EBD5C3E6(Allegrex::Context &); // SysMemUserForUser_EBD5C3E6
    extern "C" void __cdecl SysMemUserForUser_FE707FDF(Allegrex::Context &); // SysMemUserForUser_FE707FDF
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// ////////////////////////// Library : sceSuspendForUser /////////////////////////
/// ///
    extern "C" bool __cdecl sceSuspendForUser$Init();
    extern "C" bool __cdecl sceSuspendForUser$Fini();
    extern "C" void __cdecl sceSuspendForUser_EADB1BD7(Allegrex::Context &); // sceKernelPowerLock
    extern "C" void __cdecl sceSuspendForUser_3AEE7261(Allegrex::Context &); // sceKernelPowerUnlock
    extern "C" void __cdecl sceSuspendForUser_090CCB3F(Allegrex::Context &); // sceKernelPowerTick
    extern "C" void __cdecl sceSuspendForUser_3E0271D3(Allegrex::Context &); // sceKernelVolatileMemLock
    extern "C" void __cdecl sceSuspendForUser_A14F40B2(Allegrex::Context &); // sceKernelVolatileMemTryLock
    extern "C" void __cdecl sceSuspendForUser_A569E425(Allegrex::Context &); // sceKernelVolatileMemUnlock
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// //////////////////////////// Library : UtilsForUser ////////////////////////////
/// ///
    extern "C" bool __cdecl UtilsForUser$Init();
    extern "C" bool __cdecl UtilsForUser$Fini();
    extern "C" void __cdecl UtilsForUser_79D1C3FA(Allegrex::Context &); // sceKernelDcacheWritebackAll
    extern "C" void __cdecl UtilsForUser_B435DEC5(Allegrex::Context &); // sceKernelDcacheWritebackInvalidateAll
    extern "C" void __cdecl UtilsForUser_3EE30821(Allegrex::Context &); // sceKernelDcacheWritebackRange
    extern "C" void __cdecl UtilsForUser_34B9FA9E(Allegrex::Context &); // sceKernelDcacheWritebackInvalidateRange
    extern "C" void __cdecl UtilsForUser_BFA98062(Allegrex::Context &); // sceKernelDcacheInvalidateRange
    extern "C" void __cdecl UtilsForUser_80001C4C(Allegrex::Context &); // sceKernelDcacheProbe
    extern "C" void __cdecl UtilsForUser_77DFF087(Allegrex::Context &); // sceKernelDcacheProbeRange
    extern "C" void __cdecl UtilsForUser_16641D70(Allegrex::Context &); // sceKernelDcacheReadTag
    extern "C" void __cdecl UtilsForUser_920F104A(Allegrex::Context &); // sceKernelIcacheInvalidateAll
    extern "C" void __cdecl UtilsForUser_C2DF770E(Allegrex::Context &); // sceKernelIcacheInvalidateRange
    extern "C" void __cdecl UtilsForUser_4FD31C9D(Allegrex::Context &); // sceKernelIcacheProbe
    extern "C" void __cdecl UtilsForUser_FB05FAD0(Allegrex::Context &); // sceKernelIcacheReadTag
    extern "C" void __cdecl UtilsForUser_C8186A58(Allegrex::Context &); // sceKernelUtilsMd5Digest
    extern "C" void __cdecl UtilsForUser_9E5C5086(Allegrex::Context &); // sceKernelUtilsMd5BlockInit
    extern "C" void __cdecl UtilsForUser_61E1E525(Allegrex::Context &); // sceKernelUtilsMd5BlockUpdate
    extern "C" void __cdecl UtilsForUser_B8D24E78(Allegrex::Context &); // sceKernelUtilsMd5BlockResult
    extern "C" void __cdecl UtilsForUser_840259F1(Allegrex::Context &); // sceKernelUtilsSha1Digest
    extern "C" void __cdecl UtilsForUser_F8FCD5BA(Allegrex::Context &); // sceKernelUtilsSha1BlockInit
    extern "C" void __cdecl UtilsForUser_346F6DA8(Allegrex::Context &); // sceKernelUtilsSha1BlockUpdate
    extern "C" void __cdecl UtilsForUser_585F1C09(Allegrex::Context &); // sceKernelUtilsSha1BlockResult
    extern "C" void __cdecl UtilsForUser_E860E75E(Allegrex::Context &); // sceKernelUtilsMt19937Init
    extern "C" void __cdecl UtilsForUser_06FB8A63(Allegrex::Context &); // sceKernelUtilsMt19937UInt
    extern "C" void __cdecl UtilsForUser_37FB5C42(Allegrex::Context &); // sceKernelGetGPI
    extern "C" void __cdecl UtilsForUser_6AD345D7(Allegrex::Context &); // sceKernelSetGPO
    extern "C" void __cdecl UtilsForUser_91E4F6A7(Allegrex::Context &); // sceKernelLibcClock
    extern "C" void __cdecl UtilsForUser_27CC57F0(Allegrex::Context &); // sceKernelLibcTime
    extern "C" void __cdecl UtilsForUser_71EC4271(Allegrex::Context &); // sceKernelLibcGettimeofday
    extern "C" void __cdecl UtilsForUser_87E81561(Allegrex::Context &); // sceKernelPutUserLog
    extern "C" void __cdecl UtilsForUser_004D4DEE(Allegrex::Context &); // UtilsForUser_004D4DEE
    extern "C" void __cdecl UtilsForUser_157A383A(Allegrex::Context &); // UtilsForUser_157A383A
    extern "C" void __cdecl UtilsForUser_1B0592A3(Allegrex::Context &); // UtilsForUser_1B0592A3
    extern "C" void __cdecl UtilsForUser_39F49610(Allegrex::Context &); // UtilsForUser_39F49610
    extern "C" void __cdecl UtilsForUser_3FD3D324(Allegrex::Context &); // UtilsForUser_3FD3D324
    extern "C" void __cdecl UtilsForUser_43C9A8DB(Allegrex::Context &); // UtilsForUser_43C9A8DB
    extern "C" void __cdecl UtilsForUser_515B4FAF(Allegrex::Context &); // UtilsForUser_515B4FAF
    extern "C" void __cdecl UtilsForUser_5C7F2B1A(Allegrex::Context &); // UtilsForUser_5C7F2B1A
    extern "C" void __cdecl UtilsForUser_6231A71D(Allegrex::Context &); // UtilsForUser_6231A71D
    extern "C" void __cdecl UtilsForUser_7333E539(Allegrex::Context &); // UtilsForUser_7333E539
    extern "C" void __cdecl UtilsForUser_740DF7F0(Allegrex::Context &); // UtilsForUser_740DF7F0
    extern "C" void __cdecl UtilsForUser_99134C3F(Allegrex::Context &); // UtilsForUser_99134C3F
    extern "C" void __cdecl UtilsForUser_AF3766BB(Allegrex::Context &); // UtilsForUser_AF3766BB
    extern "C" void __cdecl UtilsForUser_B83A1E76(Allegrex::Context &); // UtilsForUser_B83A1E76
    extern "C" void __cdecl UtilsForUser_DBBE9A46(Allegrex::Context &); // UtilsForUser_DBBE9A46
    extern "C" void __cdecl UtilsForUser_F0155BCA(Allegrex::Context &); // UtilsForUser_F0155BCA
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_interruptman_prx;
        extern SubCategory syscall_InterruptManager;
        extern SubCategory syscall_sceKernelRegisterSubIntrHandler;
        extern SubCategory syscall_sceKernelReleaseSubIntrHandler;
        extern SubCategory syscall_sceKernelRegisterUserSpaceIntrStack;
        extern SubCategory syscall_sceKernelEnableSubIntr;
        extern SubCategory syscall_sceKernelDisableSubIntr;
        extern SubCategory syscall_sceKernelSuspendSubIntr;
        extern SubCategory syscall_sceKernelResumeSubIntr;
        extern SubCategory syscall_sceKernelIsSubInterruptOccurred;
        extern SubCategory syscall_QueryIntrHandlerInfo;
    }
}

//////////////// Module : sceInterruptManager (interruptman.prx) ///////////////
///
/// ////////////////////////// Library : InterruptManager //////////////////////////
/// ///
    extern "C" bool __cdecl InterruptManager$Init();
    extern "C" bool __cdecl InterruptManager$Fini();
    extern "C" void __cdecl InterruptManager_CA04A2B9(Allegrex::Context &); // sceKernelRegisterSubIntrHandler
    extern "C" void __cdecl InterruptManager_D61E6961(Allegrex::Context &); // sceKernelReleaseSubIntrHandler
    extern "C" void __cdecl InterruptManager_EEE43F47(Allegrex::Context &); // sceKernelRegisterUserSpaceIntrStack
    extern "C" void __cdecl InterruptManager_FB8E22EC(Allegrex::Context &); // sceKernelEnableSubIntr
    extern "C" void __cdecl InterruptManager_8A389411(Allegrex::Context &); // sceKernelDisableSubIntr
    extern "C" void __cdecl InterruptManager_5CB5A78B(Allegrex::Context &); // sceKernelSuspendSubIntr
    extern "C" void __cdecl InterruptManager_7860E0DC(Allegrex::Context &); // sceKernelResumeSubIntr
    extern "C" void __cdecl InterruptManager_FC4374B8(Allegrex::Context &); // sceKernelIsSubInterruptOccurred
    extern "C" void __cdecl InterruptManager_D2E8363F(Allegrex::Context &); // QueryIntrHandlerInfo
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_threadman_prx;
        extern SubCategory syscall_ThreadManForUser;
        extern SubCategory syscall_sceKernelCreateThread;
        extern SubCategory syscall_sceKernelDeleteThread;
        extern SubCategory syscall_sceKernelStartThread;
        extern SubCategory syscall_sceKernelExitThread;
        extern SubCategory syscall_sceKernelExitDeleteThread;
        extern SubCategory syscall_sceKernelTerminateThread;
        extern SubCategory syscall_sceKernelTerminateDeleteThread;
        extern SubCategory syscall_sceKernelSuspendDispatchThread;
        extern SubCategory syscall_sceKernelResumeDispatchThread;
        extern SubCategory syscall_sceKernelChangeCurrentThreadAttr;
        extern SubCategory syscall_sceKernelChangeThreadPriority;
        extern SubCategory syscall_sceKernelRotateThreadReadyQueue;
        extern SubCategory syscall_sceKernelReleaseWaitThread;
        extern SubCategory syscall_sceKernelGetThreadId;
        extern SubCategory syscall_sceKernelGetThreadCurrentPriority;
        extern SubCategory syscall_sceKernelGetThreadExitStatus;
        extern SubCategory syscall_sceKernelReferThreadStatus;
        extern SubCategory syscall_sceKernelReferThreadRunStatus;
        extern SubCategory syscall_sceKernelCheckThreadStack;
        extern SubCategory syscall_sceKernelGetThreadStackFreeSize;
        extern SubCategory syscall__sceKernelStartThread;
        extern SubCategory syscall__sceKernelExitThread;
        extern SubCategory syscall__sceKernelIdleThread;
        extern SubCategory syscall_sceKernelRegisterThreadEventHandler;
        extern SubCategory syscall_sceKernelReleaseThreadEventHandler;
        extern SubCategory syscall_sceKernelReferThreadEventHandlerStatus;
        extern SubCategory syscall_sceKernelSleepThread;
        extern SubCategory syscall_sceKernelSleepThreadCB;
        extern SubCategory syscall_sceKernelWakeupThread;
        extern SubCategory syscall_sceKernelCancelWakeupThread;
        extern SubCategory syscall_sceKernelSuspendThread;
        extern SubCategory syscall_sceKernelResumeThread;
        extern SubCategory syscall_sceKernelWaitThreadEnd;
        extern SubCategory syscall_sceKernelWaitThreadEndCB;
        extern SubCategory syscall_sceKernelCreateSema;
        extern SubCategory syscall_sceKernelDeleteSema;
        extern SubCategory syscall_sceKernelSignalSema;
        extern SubCategory syscall_sceKernelWaitSema;
        extern SubCategory syscall_sceKernelWaitSemaCB;
        extern SubCategory syscall_sceKernelPollSema;
        extern SubCategory syscall_sceKernelCancelSema;
        extern SubCategory syscall_sceKernelReferSemaStatus;
        extern SubCategory syscall_sceKernelCreateEventFlag;
        extern SubCategory syscall_sceKernelDeleteEventFlag;
        extern SubCategory syscall_sceKernelSetEventFlag;
        extern SubCategory syscall_sceKernelClearEventFlag;
        extern SubCategory syscall_sceKernelWaitEventFlag;
        extern SubCategory syscall_sceKernelWaitEventFlagCB;
        extern SubCategory syscall_sceKernelPollEventFlag;
        extern SubCategory syscall_sceKernelCancelEventFlag;
        extern SubCategory syscall_sceKernelReferEventFlagStatus;
        extern SubCategory syscall_sceKernelCreateMbx;
        extern SubCategory syscall_sceKernelDeleteMbx;
        extern SubCategory syscall_sceKernelSendMbx;
        extern SubCategory syscall_sceKernelReceiveMbx;
        extern SubCategory syscall_sceKernelReceiveMbxCB;
        extern SubCategory syscall_sceKernelPollMbx;
        extern SubCategory syscall_sceKernelCancelReceiveMbx;
        extern SubCategory syscall_sceKernelReferMbxStatus;
        extern SubCategory syscall_sceKernelCreateMsgPipe;
        extern SubCategory syscall_sceKernelDeleteMsgPipe;
        extern SubCategory syscall_sceKernelSendMsgPipe;
        extern SubCategory syscall_sceKernelSendMsgPipeCB;
        extern SubCategory syscall_sceKernelTrySendMsgPipe;
        extern SubCategory syscall_sceKernelReceiveMsgPipe;
        extern SubCategory syscall_sceKernelReceiveMsgPipeCB;
        extern SubCategory syscall_sceKernelTryReceiveMsgPipe;
        extern SubCategory syscall_sceKernelCancelMsgPipe;
        extern SubCategory syscall_sceKernelReferMsgPipeStatus;
        extern SubCategory syscall_sceKernelCreateVpl;
        extern SubCategory syscall_sceKernelDeleteVpl;
        extern SubCategory syscall_sceKernelAllocateVpl;
        extern SubCategory syscall_sceKernelAllocateVplCB;
        extern SubCategory syscall_sceKernelTryAllocateVpl;
        extern SubCategory syscall_sceKernelFreeVpl;
        extern SubCategory syscall_sceKernelCancelVpl;
        extern SubCategory syscall_sceKernelReferVplStatus;
        extern SubCategory syscall_sceKernelCreateFpl;
        extern SubCategory syscall_sceKernelDeleteFpl;
        extern SubCategory syscall_sceKernelAllocateFpl;
        extern SubCategory syscall_sceKernelAllocateFplCB;
        extern SubCategory syscall_sceKernelTryAllocateFpl;
        extern SubCategory syscall_sceKernelFreeFpl;
        extern SubCategory syscall_sceKernelCancelFpl;
        extern SubCategory syscall_sceKernelReferFplStatus;
        extern SubCategory syscall_sceKernelGetSystemTime;
        extern SubCategory syscall_sceKernelGetSystemTimeWide;
        extern SubCategory syscall_sceKernelGetSystemTimeLow;
        extern SubCategory syscall_sceKernelUSec2SysClock;
        extern SubCategory syscall_sceKernelSysClock2USec;
        extern SubCategory syscall_sceKernelUSec2SysClockWide;
        extern SubCategory syscall_sceKernelSysClock2USecWide;
        extern SubCategory syscall_sceKernelDelayThread;
        extern SubCategory syscall_sceKernelDelayThreadCB;
        extern SubCategory syscall_sceKernelDelaySysClockThread;
        extern SubCategory syscall_sceKernelDelaySysClockThreadCB;
        extern SubCategory syscall_sceKernelSetAlarm;
        extern SubCategory syscall_sceKernelSetSysClockAlarm;
        extern SubCategory syscall_sceKernelCancelAlarm;
        extern SubCategory syscall_sceKernelReferAlarmStatus;
        extern SubCategory syscall_sceKernelCreateVTimer;
        extern SubCategory syscall_sceKernelDeleteVTimer;
        extern SubCategory syscall_sceKernelGetVTimerBase;
        extern SubCategory syscall_sceKernelGetVTimerTime;
        extern SubCategory syscall_sceKernelSetVTimerTime;
        extern SubCategory syscall_sceKernelStartVTimer;
        extern SubCategory syscall_sceKernelStopVTimer;
        extern SubCategory syscall_sceKernelSetVTimerHandler;
        extern SubCategory syscall_sceKernelCancelVTimerHandler;
        extern SubCategory syscall_sceKernelGetVTimerBaseWide;
        extern SubCategory syscall_sceKernelGetVTimerTimeWide;
        extern SubCategory syscall_sceKernelSetVTimerTimeWide;
        extern SubCategory syscall_sceKernelSetVTimerHandlerWide;
        extern SubCategory syscall_sceKernelReferVTimerStatus;
        extern SubCategory syscall__sceKernelReturnFromTimerHandler;
        extern SubCategory syscall_sceKernelCreateCallback;
        extern SubCategory syscall_sceKernelDeleteCallback;
        extern SubCategory syscall_sceKernelNotifyCallback;
        extern SubCategory syscall_sceKernelCancelCallback;
        extern SubCategory syscall_sceKernelGetCallbackCount;
        extern SubCategory syscall_sceKernelCheckCallback;
        extern SubCategory syscall_sceKernelReferCallbackStatus;
        extern SubCategory syscall__sceKernelReturnFromCallback;
        extern SubCategory syscall_sceKernelReferSystemStatus;
        extern SubCategory syscall_sceKernelGetThreadmanIdList;
        extern SubCategory syscall_sceKernelGetThreadmanIdType;
        extern SubCategory syscall_sceKernelCreateMutex;
        extern SubCategory syscall_sceKernelDeleteMutex;
        extern SubCategory syscall_sceKernelLockMutex;
        extern SubCategory syscall_sceKernelLockMutexCB;
        extern SubCategory syscall_sceKernelTryLockMutex;
        extern SubCategory syscall_sceKernelUnlockMutex;
        extern SubCategory syscall_sceKernelCancelMutex;
        extern SubCategory syscall_sceKernelReferMutexStatus;
        extern SubCategory syscall_sceKernelCreateLwMutex;
        extern SubCategory syscall_sceKernelDeleteLwMutex;
        extern SubCategory syscall_sceKernelReferLwMutexStatusByID;
        extern SubCategory syscall_sceKernelReferThreadProfiler;
        extern SubCategory syscall_sceKernelReferGlobalProfiler;
        extern SubCategory syscall_sceKernelDonateWakeupThread;
        extern SubCategory syscall_ThreadManForUser_31327F19;
        extern SubCategory syscall_ThreadManForUser_71040D5C;
        extern SubCategory syscall_ThreadManForUser_7CFF8CF3;
        extern SubCategory syscall_ThreadManForUser_8672E3D0;
        extern SubCategory syscall_ThreadManForUser_BEED3A47;
    }
}

/////////////////// Module : sceThreadManager (threadman.prx) //////////////////
///
/// ////////////////////////// Library : ThreadManForUser //////////////////////////
/// ///
    extern "C" bool __cdecl ThreadManForUser$Init();
    extern "C" bool __cdecl ThreadManForUser$Fini();
    extern "C" void __cdecl ThreadManForUser_446D8DE6(Allegrex::Context &); // sceKernelCreateThread
    extern "C" void __cdecl ThreadManForUser_9FA03CD3(Allegrex::Context &); // sceKernelDeleteThread
    extern "C" void __cdecl ThreadManForUser_F475845D(Allegrex::Context &); // sceKernelStartThread
    extern "C" void __cdecl ThreadManForUser_AA73C935(Allegrex::Context &); // sceKernelExitThread
    extern "C" void __cdecl ThreadManForUser_809CE29B(Allegrex::Context &); // sceKernelExitDeleteThread
    extern "C" void __cdecl ThreadManForUser_616403BA(Allegrex::Context &); // sceKernelTerminateThread
    extern "C" void __cdecl ThreadManForUser_383F7BCC(Allegrex::Context &); // sceKernelTerminateDeleteThread
    extern "C" void __cdecl ThreadManForUser_3AD58B8C(Allegrex::Context &); // sceKernelSuspendDispatchThread
    extern "C" void __cdecl ThreadManForUser_27E22EC2(Allegrex::Context &); // sceKernelResumeDispatchThread
    extern "C" void __cdecl ThreadManForUser_EA748E31(Allegrex::Context &); // sceKernelChangeCurrentThreadAttr
    extern "C" void __cdecl ThreadManForUser_71BC9871(Allegrex::Context &); // sceKernelChangeThreadPriority
    extern "C" void __cdecl ThreadManForUser_912354A7(Allegrex::Context &); // sceKernelRotateThreadReadyQueue
    extern "C" void __cdecl ThreadManForUser_2C34E053(Allegrex::Context &); // sceKernelReleaseWaitThread
    extern "C" void __cdecl ThreadManForUser_293B45B8(Allegrex::Context &); // sceKernelGetThreadId
    extern "C" void __cdecl ThreadManForUser_94AA61EE(Allegrex::Context &); // sceKernelGetThreadCurrentPriority
    extern "C" void __cdecl ThreadManForUser_3B183E26(Allegrex::Context &); // sceKernelGetThreadExitStatus
    extern "C" void __cdecl ThreadManForUser_17C1684E(Allegrex::Context &); // sceKernelReferThreadStatus
    extern "C" void __cdecl ThreadManForUser_FFC36A14(Allegrex::Context &); // sceKernelReferThreadRunStatus
    extern "C" void __cdecl ThreadManForUser_D13BDE95(Allegrex::Context &); // sceKernelCheckThreadStack
    extern "C" void __cdecl ThreadManForUser_52089CA1(Allegrex::Context &); // sceKernelGetThreadStackFreeSize
    extern "C" void __cdecl ThreadManForUser_07F3A4BC(Allegrex::Context &); // _sceKernelStartThread
    extern "C" void __cdecl ThreadManForUser_532A522E(Allegrex::Context &); // _sceKernelExitThread
    extern "C" void __cdecl ThreadManForUser_E0A68B8C(Allegrex::Context &); // _sceKernelIdleThread
    extern "C" void __cdecl ThreadManForUser_0C106E53(Allegrex::Context &); // sceKernelRegisterThreadEventHandler
    extern "C" void __cdecl ThreadManForUser_72F3C145(Allegrex::Context &); // sceKernelReleaseThreadEventHandler
    extern "C" void __cdecl ThreadManForUser_369EEB6B(Allegrex::Context &); // sceKernelReferThreadEventHandlerStatus
    extern "C" void __cdecl ThreadManForUser_9ACE131E(Allegrex::Context &); // sceKernelSleepThread
    extern "C" void __cdecl ThreadManForUser_82826F70(Allegrex::Context &); // sceKernelSleepThreadCB
    extern "C" void __cdecl ThreadManForUser_D59EAD2F(Allegrex::Context &); // sceKernelWakeupThread
    extern "C" void __cdecl ThreadManForUser_FCCFAD26(Allegrex::Context &); // sceKernelCancelWakeupThread
    extern "C" void __cdecl ThreadManForUser_9944F31F(Allegrex::Context &); // sceKernelSuspendThread
    extern "C" void __cdecl ThreadManForUser_75156E8F(Allegrex::Context &); // sceKernelResumeThread
    extern "C" void __cdecl ThreadManForUser_278C0DF5(Allegrex::Context &); // sceKernelWaitThreadEnd
    extern "C" void __cdecl ThreadManForUser_840E8133(Allegrex::Context &); // sceKernelWaitThreadEndCB
    extern "C" void __cdecl ThreadManForUser_D6DA4BA1(Allegrex::Context &); // sceKernelCreateSema
    extern "C" void __cdecl ThreadManForUser_28B6489C(Allegrex::Context &); // sceKernelDeleteSema
    extern "C" void __cdecl ThreadManForUser_3F53E640(Allegrex::Context &); // sceKernelSignalSema
    extern "C" void __cdecl ThreadManForUser_4E3A1105(Allegrex::Context &); // sceKernelWaitSema
    extern "C" void __cdecl ThreadManForUser_6D212BAC(Allegrex::Context &); // sceKernelWaitSemaCB
    extern "C" void __cdecl ThreadManForUser_58B1F937(Allegrex::Context &); // sceKernelPollSema
    extern "C" void __cdecl ThreadManForUser_8FFDF9A2(Allegrex::Context &); // sceKernelCancelSema
    extern "C" void __cdecl ThreadManForUser_BC6FEBC5(Allegrex::Context &); // sceKernelReferSemaStatus
    extern "C" void __cdecl ThreadManForUser_55C20A00(Allegrex::Context &); // sceKernelCreateEventFlag
    extern "C" void __cdecl ThreadManForUser_EF9E4C70(Allegrex::Context &); // sceKernelDeleteEventFlag
    extern "C" void __cdecl ThreadManForUser_1FB15A32(Allegrex::Context &); // sceKernelSetEventFlag
    extern "C" void __cdecl ThreadManForUser_812346E4(Allegrex::Context &); // sceKernelClearEventFlag
    extern "C" void __cdecl ThreadManForUser_402FCF22(Allegrex::Context &); // sceKernelWaitEventFlag
    extern "C" void __cdecl ThreadManForUser_328C546A(Allegrex::Context &); // sceKernelWaitEventFlagCB
    extern "C" void __cdecl ThreadManForUser_30FD48F0(Allegrex::Context &); // sceKernelPollEventFlag
    extern "C" void __cdecl ThreadManForUser_CD203292(Allegrex::Context &); // sceKernelCancelEventFlag
    extern "C" void __cdecl ThreadManForUser_A66B0120(Allegrex::Context &); // sceKernelReferEventFlagStatus
    extern "C" void __cdecl ThreadManForUser_8125221D(Allegrex::Context &); // sceKernelCreateMbx
    extern "C" void __cdecl ThreadManForUser_86255ADA(Allegrex::Context &); // sceKernelDeleteMbx
    extern "C" void __cdecl ThreadManForUser_E9B3061E(Allegrex::Context &); // sceKernelSendMbx
    extern "C" void __cdecl ThreadManForUser_18260574(Allegrex::Context &); // sceKernelReceiveMbx
    extern "C" void __cdecl ThreadManForUser_F3986382(Allegrex::Context &); // sceKernelReceiveMbxCB
    extern "C" void __cdecl ThreadManForUser_0D81716A(Allegrex::Context &); // sceKernelPollMbx
    extern "C" void __cdecl ThreadManForUser_87D4DD36(Allegrex::Context &); // sceKernelCancelReceiveMbx
    extern "C" void __cdecl ThreadManForUser_A8E8C846(Allegrex::Context &); // sceKernelReferMbxStatus
    extern "C" void __cdecl ThreadManForUser_7C0DC2A0(Allegrex::Context &); // sceKernelCreateMsgPipe
    extern "C" void __cdecl ThreadManForUser_F0B7DA1C(Allegrex::Context &); // sceKernelDeleteMsgPipe
    extern "C" void __cdecl ThreadManForUser_876DBFAD(Allegrex::Context &); // sceKernelSendMsgPipe
    extern "C" void __cdecl ThreadManForUser_7C41F2C2(Allegrex::Context &); // sceKernelSendMsgPipeCB
    extern "C" void __cdecl ThreadManForUser_884C9F90(Allegrex::Context &); // sceKernelTrySendMsgPipe
    extern "C" void __cdecl ThreadManForUser_74829B76(Allegrex::Context &); // sceKernelReceiveMsgPipe
    extern "C" void __cdecl ThreadManForUser_FBFA697D(Allegrex::Context &); // sceKernelReceiveMsgPipeCB
    extern "C" void __cdecl ThreadManForUser_DF52098F(Allegrex::Context &); // sceKernelTryReceiveMsgPipe
    extern "C" void __cdecl ThreadManForUser_349B864D(Allegrex::Context &); // sceKernelCancelMsgPipe
    extern "C" void __cdecl ThreadManForUser_33BE4024(Allegrex::Context &); // sceKernelReferMsgPipeStatus
    extern "C" void __cdecl ThreadManForUser_56C039B5(Allegrex::Context &); // sceKernelCreateVpl
    extern "C" void __cdecl ThreadManForUser_89B3D48C(Allegrex::Context &); // sceKernelDeleteVpl
    extern "C" void __cdecl ThreadManForUser_BED27435(Allegrex::Context &); // sceKernelAllocateVpl
    extern "C" void __cdecl ThreadManForUser_EC0A693F(Allegrex::Context &); // sceKernelAllocateVplCB
    extern "C" void __cdecl ThreadManForUser_AF36D708(Allegrex::Context &); // sceKernelTryAllocateVpl
    extern "C" void __cdecl ThreadManForUser_B736E9FF(Allegrex::Context &); // sceKernelFreeVpl
    extern "C" void __cdecl ThreadManForUser_1D371B8A(Allegrex::Context &); // sceKernelCancelVpl
    extern "C" void __cdecl ThreadManForUser_39810265(Allegrex::Context &); // sceKernelReferVplStatus
    extern "C" void __cdecl ThreadManForUser_C07BB470(Allegrex::Context &); // sceKernelCreateFpl
    extern "C" void __cdecl ThreadManForUser_ED1410E0(Allegrex::Context &); // sceKernelDeleteFpl
    extern "C" void __cdecl ThreadManForUser_D979E9BF(Allegrex::Context &); // sceKernelAllocateFpl
    extern "C" void __cdecl ThreadManForUser_E7282CB6(Allegrex::Context &); // sceKernelAllocateFplCB
    extern "C" void __cdecl ThreadManForUser_623AE665(Allegrex::Context &); // sceKernelTryAllocateFpl
    extern "C" void __cdecl ThreadManForUser_F6414A71(Allegrex::Context &); // sceKernelFreeFpl
    extern "C" void __cdecl ThreadManForUser_A8AA591F(Allegrex::Context &); // sceKernelCancelFpl
    extern "C" void __cdecl ThreadManForUser_D8199E4C(Allegrex::Context &); // sceKernelReferFplStatus
    extern "C" void __cdecl ThreadManForUser_DB738F35(Allegrex::Context &); // sceKernelGetSystemTime
    extern "C" void __cdecl ThreadManForUser_82BC5777(Allegrex::Context &); // sceKernelGetSystemTimeWide
    extern "C" void __cdecl ThreadManForUser_369ED59D(Allegrex::Context &); // sceKernelGetSystemTimeLow
    extern "C" void __cdecl ThreadManForUser_110DEC9A(Allegrex::Context &); // sceKernelUSec2SysClock
    extern "C" void __cdecl ThreadManForUser_BA6B92E2(Allegrex::Context &); // sceKernelSysClock2USec
    extern "C" void __cdecl ThreadManForUser_C8CD158C(Allegrex::Context &); // sceKernelUSec2SysClockWide
    extern "C" void __cdecl ThreadManForUser_E1619D7C(Allegrex::Context &); // sceKernelSysClock2USecWide
    extern "C" void __cdecl ThreadManForUser_CEADEB47(Allegrex::Context &); // sceKernelDelayThread
    extern "C" void __cdecl ThreadManForUser_68DA9E36(Allegrex::Context &); // sceKernelDelayThreadCB
    extern "C" void __cdecl ThreadManForUser_BD123D9E(Allegrex::Context &); // sceKernelDelaySysClockThread
    extern "C" void __cdecl ThreadManForUser_1181E963(Allegrex::Context &); // sceKernelDelaySysClockThreadCB
    extern "C" void __cdecl ThreadManForUser_6652B8CA(Allegrex::Context &); // sceKernelSetAlarm
    extern "C" void __cdecl ThreadManForUser_B2C25152(Allegrex::Context &); // sceKernelSetSysClockAlarm
    extern "C" void __cdecl ThreadManForUser_7E65B999(Allegrex::Context &); // sceKernelCancelAlarm
    extern "C" void __cdecl ThreadManForUser_DAA3F564(Allegrex::Context &); // sceKernelReferAlarmStatus
    extern "C" void __cdecl ThreadManForUser_20FFF560(Allegrex::Context &); // sceKernelCreateVTimer
    extern "C" void __cdecl ThreadManForUser_328F9E52(Allegrex::Context &); // sceKernelDeleteVTimer
    extern "C" void __cdecl ThreadManForUser_B3A59970(Allegrex::Context &); // sceKernelGetVTimerBase
    extern "C" void __cdecl ThreadManForUser_034A921F(Allegrex::Context &); // sceKernelGetVTimerTime
    extern "C" void __cdecl ThreadManForUser_542AD630(Allegrex::Context &); // sceKernelSetVTimerTime
    extern "C" void __cdecl ThreadManForUser_C68D9437(Allegrex::Context &); // sceKernelStartVTimer
    extern "C" void __cdecl ThreadManForUser_D0AEEE87(Allegrex::Context &); // sceKernelStopVTimer
    extern "C" void __cdecl ThreadManForUser_D8B299AE(Allegrex::Context &); // sceKernelSetVTimerHandler
    extern "C" void __cdecl ThreadManForUser_D2D615EF(Allegrex::Context &); // sceKernelCancelVTimerHandler
    extern "C" void __cdecl ThreadManForUser_B7C18B77(Allegrex::Context &); // sceKernelGetVTimerBaseWide
    extern "C" void __cdecl ThreadManForUser_C0B3FFD2(Allegrex::Context &); // sceKernelGetVTimerTimeWide
    extern "C" void __cdecl ThreadManForUser_FB6425C3(Allegrex::Context &); // sceKernelSetVTimerTimeWide
    extern "C" void __cdecl ThreadManForUser_53B00E9A(Allegrex::Context &); // sceKernelSetVTimerHandlerWide
    extern "C" void __cdecl ThreadManForUser_5F32BEAA(Allegrex::Context &); // sceKernelReferVTimerStatus
    extern "C" void __cdecl ThreadManForUser_0E927AED(Allegrex::Context &); // _sceKernelReturnFromTimerHandler
    extern "C" void __cdecl ThreadManForUser_E81CAF8F(Allegrex::Context &); // sceKernelCreateCallback
    extern "C" void __cdecl ThreadManForUser_EDBA5844(Allegrex::Context &); // sceKernelDeleteCallback
    extern "C" void __cdecl ThreadManForUser_C11BA8C4(Allegrex::Context &); // sceKernelNotifyCallback
    extern "C" void __cdecl ThreadManForUser_BA4051D6(Allegrex::Context &); // sceKernelCancelCallback
    extern "C" void __cdecl ThreadManForUser_2A3D44FF(Allegrex::Context &); // sceKernelGetCallbackCount
    extern "C" void __cdecl ThreadManForUser_349D6D6C(Allegrex::Context &); // sceKernelCheckCallback
    extern "C" void __cdecl ThreadManForUser_730ED8BC(Allegrex::Context &); // sceKernelReferCallbackStatus
    extern "C" void __cdecl ThreadManForUser_6E9EA350(Allegrex::Context &); // _sceKernelReturnFromCallback
    extern "C" void __cdecl ThreadManForUser_627E6F3A(Allegrex::Context &); // sceKernelReferSystemStatus
    extern "C" void __cdecl ThreadManForUser_94416130(Allegrex::Context &); // sceKernelGetThreadmanIdList
    extern "C" void __cdecl ThreadManForUser_57CF62DD(Allegrex::Context &); // sceKernelGetThreadmanIdType
    extern "C" void __cdecl ThreadManForUser_B7D098C6(Allegrex::Context &); // sceKernelCreateMutex
    extern "C" void __cdecl ThreadManForUser_F8170FBE(Allegrex::Context &); // sceKernelDeleteMutex
    extern "C" void __cdecl ThreadManForUser_B011B11F(Allegrex::Context &); // sceKernelLockMutex
    extern "C" void __cdecl ThreadManForUser_5BF4DD27(Allegrex::Context &); // sceKernelLockMutexCB
    extern "C" void __cdecl ThreadManForUser_0DDCD2C9(Allegrex::Context &); // sceKernelTryLockMutex
    extern "C" void __cdecl ThreadManForUser_6B30100F(Allegrex::Context &); // sceKernelUnlockMutex
    extern "C" void __cdecl ThreadManForUser_87D9223C(Allegrex::Context &); // sceKernelCancelMutex
    extern "C" void __cdecl ThreadManForUser_A9C2CB9A(Allegrex::Context &); // sceKernelReferMutexStatus
    extern "C" void __cdecl ThreadManForUser_19CFF145(Allegrex::Context &); // sceKernelCreateLwMutex
    extern "C" void __cdecl ThreadManForUser_60107536(Allegrex::Context &); // sceKernelDeleteLwMutex
    extern "C" void __cdecl ThreadManForUser_4C145944(Allegrex::Context &); // sceKernelReferLwMutexStatusByID
    extern "C" void __cdecl ThreadManForUser_64D4540E(Allegrex::Context &); // sceKernelReferThreadProfiler
    extern "C" void __cdecl ThreadManForUser_8218B4DD(Allegrex::Context &); // sceKernelReferGlobalProfiler
    extern "C" void __cdecl ThreadManForUser_1AF94D03(Allegrex::Context &); // sceKernelDonateWakeupThread
    extern "C" void __cdecl ThreadManForUser_31327F19(Allegrex::Context &); // ThreadManForUser_31327F19
    extern "C" void __cdecl ThreadManForUser_71040D5C(Allegrex::Context &); // ThreadManForUser_71040D5C
    extern "C" void __cdecl ThreadManForUser_7CFF8CF3(Allegrex::Context &); // ThreadManForUser_7CFF8CF3
    extern "C" void __cdecl ThreadManForUser_8672E3D0(Allegrex::Context &); // ThreadManForUser_8672E3D0
    extern "C" void __cdecl ThreadManForUser_BEED3A47(Allegrex::Context &); // ThreadManForUser_BEED3A47
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_iofilemgr_prx;
        extern SubCategory syscall_StdioForUser;
        extern SubCategory syscall_sceKernelStdout;
        extern SubCategory syscall_sceKernelStderr;
        extern SubCategory syscall_sceKernelStdin;
        extern SubCategory syscall_sceKernelStdioOpen;
        extern SubCategory syscall_sceKernelStdioClose;
        extern SubCategory syscall_sceKernelStdioLseek;
        extern SubCategory syscall_sceKernelStdioRead;
        extern SubCategory syscall_sceKernelStdioWrite;
        extern SubCategory syscall_sceKernelStdioSendChar;
        extern SubCategory syscall_sceKernelRegisterStdoutPipe;
        extern SubCategory syscall_sceKernelRegisterStderrPipe;
        extern SubCategory syscall_IoFileMgrForUser;
        extern SubCategory syscall_sceIoChstat;
        extern SubCategory syscall_sceIoGetstat;
        extern SubCategory syscall_sceIoGetAsyncStat;
        extern SubCategory syscall_sceIoDopen;
        extern SubCategory syscall_sceIoDclose;
        extern SubCategory syscall_sceIoDread;
        extern SubCategory syscall_sceIoMkdir;
        extern SubCategory syscall_sceIoRmdir;
        extern SubCategory syscall_sceIoChdir;
        extern SubCategory syscall_sceIoRename;
        extern SubCategory syscall_sceIoRemove;
        extern SubCategory syscall_sceIoDevctl;
        extern SubCategory syscall_sceIoSync;
        extern SubCategory syscall_sceIoGetDevType;
        extern SubCategory syscall_sceIoOpen;
        extern SubCategory syscall_sceIoClose;
        extern SubCategory syscall_sceIoIoctl;
        extern SubCategory syscall_sceIoLseek;
        extern SubCategory syscall_sceIoLseek32;
        extern SubCategory syscall_sceIoRead;
        extern SubCategory syscall_sceIoWrite;
        extern SubCategory syscall_sceIoPollAsync;
        extern SubCategory syscall_sceIoWaitAsync;
        extern SubCategory syscall_sceIoWaitAsyncCB;
        extern SubCategory syscall_sceIoSetAsyncCallback;
        extern SubCategory syscall_sceIoOpenAsync;
        extern SubCategory syscall_sceIoCloseAsync;
        extern SubCategory syscall_sceIoIoctlAsync;
        extern SubCategory syscall_sceIoLseekAsync;
        extern SubCategory syscall_sceIoLseek32Async;
        extern SubCategory syscall_sceIoReadAsync;
        extern SubCategory syscall_sceIoWriteAsync;
        extern SubCategory syscall_sceIoChangeAsyncPriority;
        extern SubCategory syscall_sceIoCancel;
        extern SubCategory syscall_sceIoGetFdList;
        extern SubCategory syscall_sceIoAssign;
        extern SubCategory syscall_sceIoUnassign;
    }
}

/////////////////// Module : sceIOFileManager (iofilemgr.prx) //////////////////
///
/// //////////////////////////// Library : StdioForUser ////////////////////////////
/// ///
    extern "C" bool __cdecl StdioForUser$Init();
    extern "C" bool __cdecl StdioForUser$Fini();
    extern "C" void __cdecl StdioForUser_A6BAB2E9(Allegrex::Context &); // sceKernelStdout
    extern "C" void __cdecl StdioForUser_F78BA90A(Allegrex::Context &); // sceKernelStderr
    extern "C" void __cdecl StdioForUser_172D316E(Allegrex::Context &); // sceKernelStdin
    extern "C" void __cdecl StdioForUser_924ABA61(Allegrex::Context &); // sceKernelStdioOpen
    extern "C" void __cdecl StdioForUser_9D061C19(Allegrex::Context &); // sceKernelStdioClose
    extern "C" void __cdecl StdioForUser_0CBB0571(Allegrex::Context &); // sceKernelStdioLseek
    extern "C" void __cdecl StdioForUser_3054D478(Allegrex::Context &); // sceKernelStdioRead
    extern "C" void __cdecl StdioForUser_A3B931DB(Allegrex::Context &); // sceKernelStdioWrite
    extern "C" void __cdecl StdioForUser_A46785C9(Allegrex::Context &); // sceKernelStdioSendChar
    extern "C" void __cdecl StdioForUser_432D8F5C(Allegrex::Context &); // sceKernelRegisterStdoutPipe
    extern "C" void __cdecl StdioForUser_6F797E03(Allegrex::Context &); // sceKernelRegisterStderrPipe
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// ////////////////////////// Library : IoFileMgrForUser //////////////////////////
/// ///
    extern "C" bool __cdecl IoFileMgrForUser$Init();
    extern "C" bool __cdecl IoFileMgrForUser$Fini();
    extern "C" void __cdecl IoFileMgrForUser_B8A740F4(Allegrex::Context &); // sceIoChstat
    extern "C" void __cdecl IoFileMgrForUser_ACE946E8(Allegrex::Context &); // sceIoGetstat
    extern "C" void __cdecl IoFileMgrForUser_CB05F8D6(Allegrex::Context &); // sceIoGetAsyncStat
    extern "C" void __cdecl IoFileMgrForUser_B29DDF9C(Allegrex::Context &); // sceIoDopen
    extern "C" void __cdecl IoFileMgrForUser_EB092469(Allegrex::Context &); // sceIoDclose
    extern "C" void __cdecl IoFileMgrForUser_E3EB004C(Allegrex::Context &); // sceIoDread
    extern "C" void __cdecl IoFileMgrForUser_06A70004(Allegrex::Context &); // sceIoMkdir
    extern "C" void __cdecl IoFileMgrForUser_1117C65F(Allegrex::Context &); // sceIoRmdir
    extern "C" void __cdecl IoFileMgrForUser_55F4717D(Allegrex::Context &); // sceIoChdir
    extern "C" void __cdecl IoFileMgrForUser_779103A0(Allegrex::Context &); // sceIoRename
    extern "C" void __cdecl IoFileMgrForUser_F27A9C51(Allegrex::Context &); // sceIoRemove
    extern "C" void __cdecl IoFileMgrForUser_54F5FB11(Allegrex::Context &); // sceIoDevctl
    extern "C" void __cdecl IoFileMgrForUser_AB96437F(Allegrex::Context &); // sceIoSync
    extern "C" void __cdecl IoFileMgrForUser_08BD7374(Allegrex::Context &); // sceIoGetDevType
    extern "C" void __cdecl IoFileMgrForUser_109F50BC(Allegrex::Context &); // sceIoOpen
    extern "C" void __cdecl IoFileMgrForUser_810C4BC3(Allegrex::Context &); // sceIoClose
    extern "C" void __cdecl IoFileMgrForUser_63632449(Allegrex::Context &); // sceIoIoctl
    extern "C" void __cdecl IoFileMgrForUser_27EB27B8(Allegrex::Context &); // sceIoLseek
    extern "C" void __cdecl IoFileMgrForUser_68963324(Allegrex::Context &); // sceIoLseek32
    extern "C" void __cdecl IoFileMgrForUser_6A638D83(Allegrex::Context &); // sceIoRead
    extern "C" void __cdecl IoFileMgrForUser_42EC03AC(Allegrex::Context &); // sceIoWrite
    extern "C" void __cdecl IoFileMgrForUser_3251EA56(Allegrex::Context &); // sceIoPollAsync
    extern "C" void __cdecl IoFileMgrForUser_E23EEC33(Allegrex::Context &); // sceIoWaitAsync
    extern "C" void __cdecl IoFileMgrForUser_35DBD746(Allegrex::Context &); // sceIoWaitAsyncCB
    extern "C" void __cdecl IoFileMgrForUser_A12A0514(Allegrex::Context &); // sceIoSetAsyncCallback
    extern "C" void __cdecl IoFileMgrForUser_89AA9906(Allegrex::Context &); // sceIoOpenAsync
    extern "C" void __cdecl IoFileMgrForUser_FF5940B6(Allegrex::Context &); // sceIoCloseAsync
    extern "C" void __cdecl IoFileMgrForUser_E95A012B(Allegrex::Context &); // sceIoIoctlAsync
    extern "C" void __cdecl IoFileMgrForUser_71B19E77(Allegrex::Context &); // sceIoLseekAsync
    extern "C" void __cdecl IoFileMgrForUser_1B385D8F(Allegrex::Context &); // sceIoLseek32Async
    extern "C" void __cdecl IoFileMgrForUser_A0B5A7C2(Allegrex::Context &); // sceIoReadAsync
    extern "C" void __cdecl IoFileMgrForUser_0FACAB19(Allegrex::Context &); // sceIoWriteAsync
    extern "C" void __cdecl IoFileMgrForUser_B293727F(Allegrex::Context &); // sceIoChangeAsyncPriority
    extern "C" void __cdecl IoFileMgrForUser_E8BC6571(Allegrex::Context &); // sceIoCancel
    extern "C" void __cdecl IoFileMgrForUser_5C2BE2CC(Allegrex::Context &); // sceIoGetFdList
    extern "C" void __cdecl IoFileMgrForUser_B2A628C1(Allegrex::Context &); // sceIoAssign
    extern "C" void __cdecl IoFileMgrForUser_6D08A871(Allegrex::Context &); // sceIoUnassign
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_modulemgr_prx;
        extern SubCategory syscall_ModuleMgrForUser;
        extern SubCategory syscall_sceKernelLoadModule;
        extern SubCategory syscall_sceKernelLoadModuleMs;
        extern SubCategory syscall_sceKernelLoadModuleBufferUsbWlan;
        extern SubCategory syscall_sceKernelLoadModuleByID;
        extern SubCategory syscall_sceKernelStartModule;
        extern SubCategory syscall_sceKernelStopModule;
        extern SubCategory syscall_sceKernelUnloadModule;
        extern SubCategory syscall_sceKernelSelfStopUnloadModule;
        extern SubCategory syscall_sceKernelStopUnloadSelfModule;
        extern SubCategory syscall_sceKernelQueryModuleInfo;
        extern SubCategory syscall_sceKernelGetModuleId;
        extern SubCategory syscall_sceKernelGetModuleIdByAddress;
        extern SubCategory syscall_sceKernelGetModuleGPByAddress;
        extern SubCategory syscall_sceKernelGetModuleIdList;
        extern SubCategory syscall_ModuleMgrForUser_1196472E;
        extern SubCategory syscall_ModuleMgrForUser_24EC0641;
        extern SubCategory syscall_ModuleMgrForUser_8F2DF740;
        extern SubCategory syscall_ModuleMgrForUser_E4C4211C;
        extern SubCategory syscall_ModuleMgrForUser_F2D8D1B4;
        extern SubCategory syscall_ModuleMgrForUser_FBE27467;
        extern SubCategory syscall_ModuleMgrForUser_FEF27DC1;
    }
}

/////////////////// Module : sceModuleManager (modulemgr.prx) //////////////////
///
/// ////////////////////////// Library : ModuleMgrForUser //////////////////////////
/// ///
    extern "C" bool __cdecl ModuleMgrForUser$Init();
    extern "C" bool __cdecl ModuleMgrForUser$Fini();
    extern "C" void __cdecl ModuleMgrForUser_977DE386(Allegrex::Context &); // sceKernelLoadModule
    extern "C" void __cdecl ModuleMgrForUser_710F61B5(Allegrex::Context &); // sceKernelLoadModuleMs
    extern "C" void __cdecl ModuleMgrForUser_F9275D98(Allegrex::Context &); // sceKernelLoadModuleBufferUsbWlan
    extern "C" void __cdecl ModuleMgrForUser_B7F46618(Allegrex::Context &); // sceKernelLoadModuleByID
    extern "C" void __cdecl ModuleMgrForUser_50F0C1EC(Allegrex::Context &); // sceKernelStartModule
    extern "C" void __cdecl ModuleMgrForUser_D1FF982A(Allegrex::Context &); // sceKernelStopModule
    extern "C" void __cdecl ModuleMgrForUser_2E0911AA(Allegrex::Context &); // sceKernelUnloadModule
    extern "C" void __cdecl ModuleMgrForUser_D675EBB8(Allegrex::Context &); // sceKernelSelfStopUnloadModule
    extern "C" void __cdecl ModuleMgrForUser_CC1D3699(Allegrex::Context &); // sceKernelStopUnloadSelfModule
    extern "C" void __cdecl ModuleMgrForUser_748CBED9(Allegrex::Context &); // sceKernelQueryModuleInfo
    extern "C" void __cdecl ModuleMgrForUser_F0A26395(Allegrex::Context &); // sceKernelGetModuleId
    extern "C" void __cdecl ModuleMgrForUser_D8B73127(Allegrex::Context &); // sceKernelGetModuleIdByAddress
    extern "C" void __cdecl ModuleMgrForUser_D2FBC957(Allegrex::Context &); // sceKernelGetModuleGPByAddress
    extern "C" void __cdecl ModuleMgrForUser_644395E2(Allegrex::Context &); // sceKernelGetModuleIdList
    extern "C" void __cdecl ModuleMgrForUser_1196472E(Allegrex::Context &); // ModuleMgrForUser_1196472E
    extern "C" void __cdecl ModuleMgrForUser_24EC0641(Allegrex::Context &); // ModuleMgrForUser_24EC0641
    extern "C" void __cdecl ModuleMgrForUser_8F2DF740(Allegrex::Context &); // ModuleMgrForUser_8F2DF740
    extern "C" void __cdecl ModuleMgrForUser_E4C4211C(Allegrex::Context &); // ModuleMgrForUser_E4C4211C
    extern "C" void __cdecl ModuleMgrForUser_F2D8D1B4(Allegrex::Context &); // ModuleMgrForUser_F2D8D1B4
    extern "C" void __cdecl ModuleMgrForUser_FBE27467(Allegrex::Context &); // ModuleMgrForUser_FBE27467
    extern "C" void __cdecl ModuleMgrForUser_FEF27DC1(Allegrex::Context &); // ModuleMgrForUser_FEF27DC1
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_loadexec_prx;
        extern SubCategory syscall_LoadExecForUser;
        extern SubCategory syscall_sceKernelLoadExec;
        extern SubCategory syscall_sceKernelExitGame;
        extern SubCategory syscall_sceKernelExitGameWithStatus;
        extern SubCategory syscall_sceKernelRegisterExitCallback;
        extern SubCategory syscall_LoadExecForUser_362A956B;
        extern SubCategory syscall_LoadExecForUser_8ADA38D3;
        extern SubCategory syscall_LoadExecForUser_D1FB50DC;
    }
}

////////////////////// Module : sceLoadExec (loadexec.prx) /////////////////////
///
/// /////////////////////////// Library : LoadExecForUser //////////////////////////
/// ///
    extern "C" bool __cdecl LoadExecForUser$Init();
    extern "C" bool __cdecl LoadExecForUser$Fini();
    extern "C" void __cdecl LoadExecForUser_BD2F1094(Allegrex::Context &); // sceKernelLoadExec
    extern "C" void __cdecl LoadExecForUser_05572A5F(Allegrex::Context &); // sceKernelExitGame
    extern "C" void __cdecl LoadExecForUser_2AC9954B(Allegrex::Context &); // sceKernelExitGameWithStatus
    extern "C" void __cdecl LoadExecForUser_4AC57943(Allegrex::Context &); // sceKernelRegisterExitCallback
    extern "C" void __cdecl LoadExecForUser_362A956B(Allegrex::Context &); // LoadExecForUser_362A956B
    extern "C" void __cdecl LoadExecForUser_8ADA38D3(Allegrex::Context &); // LoadExecForUser_8ADA38D3
    extern "C" void __cdecl LoadExecForUser_D1FB50DC(Allegrex::Context &); // LoadExecForUser_D1FB50DC
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_ge_prx;
        extern SubCategory syscall_sceGe_user;
        extern SubCategory syscall_sceGeEdramGetSize;
        extern SubCategory syscall_sceGeEdramGetAddr;
        extern SubCategory syscall_sceGeEdramSetAddrTranslation;
        extern SubCategory syscall_sceGeGetCmd;
        extern SubCategory syscall_sceGeGetMtx;
        extern SubCategory syscall_sceGeSaveContext;
        extern SubCategory syscall_sceGeRestoreContext;
        extern SubCategory syscall_sceGeListEnQueue;
        extern SubCategory syscall_sceGeListEnQueueHead;
        extern SubCategory syscall_sceGeListDeQueue;
        extern SubCategory syscall_sceGeListUpdateStallAddr;
        extern SubCategory syscall_sceGeListSync;
        extern SubCategory syscall_sceGeDrawSync;
        extern SubCategory syscall_sceGeBreak;
        extern SubCategory syscall_sceGeContinue;
        extern SubCategory syscall_sceGeSetCallback;
        extern SubCategory syscall_sceGeUnsetCallback;
        extern SubCategory syscall_sceGeGetStack;
    }
}

//////////////////////// Module : sceGE_Manager (ge.prx) ///////////////////////
///
/// ///////////////////////////// Library : sceGe_user /////////////////////////////
/// ///
    extern "C" bool __cdecl sceGe_user$Init();
    extern "C" bool __cdecl sceGe_user$Fini();
    extern "C" void __cdecl sceGe_user_1F6752AD(Allegrex::Context &); // sceGeEdramGetSize
    extern "C" void __cdecl sceGe_user_E47E40E4(Allegrex::Context &); // sceGeEdramGetAddr
    extern "C" void __cdecl sceGe_user_B77905EA(Allegrex::Context &); // sceGeEdramSetAddrTranslation
    extern "C" void __cdecl sceGe_user_DC93CFEF(Allegrex::Context &); // sceGeGetCmd
    extern "C" void __cdecl sceGe_user_57C8945B(Allegrex::Context &); // sceGeGetMtx
    extern "C" void __cdecl sceGe_user_438A385A(Allegrex::Context &); // sceGeSaveContext
    extern "C" void __cdecl sceGe_user_0BF608FB(Allegrex::Context &); // sceGeRestoreContext
    extern "C" void __cdecl sceGe_user_AB49E76A(Allegrex::Context &); // sceGeListEnQueue
    extern "C" void __cdecl sceGe_user_1C0D95A6(Allegrex::Context &); // sceGeListEnQueueHead
    extern "C" void __cdecl sceGe_user_5FB86AB0(Allegrex::Context &); // sceGeListDeQueue
    extern "C" void __cdecl sceGe_user_E0D68148(Allegrex::Context &); // sceGeListUpdateStallAddr
    extern "C" void __cdecl sceGe_user_03444EB4(Allegrex::Context &); // sceGeListSync
    extern "C" void __cdecl sceGe_user_B287BD61(Allegrex::Context &); // sceGeDrawSync
    extern "C" void __cdecl sceGe_user_B448EC0D(Allegrex::Context &); // sceGeBreak
    extern "C" void __cdecl sceGe_user_4C06E472(Allegrex::Context &); // sceGeContinue
    extern "C" void __cdecl sceGe_user_A4FC06A4(Allegrex::Context &); // sceGeSetCallback
    extern "C" void __cdecl sceGe_user_05DB22CE(Allegrex::Context &); // sceGeUnsetCallback
    extern "C" void __cdecl sceGe_user_E66CB92E(Allegrex::Context &); // sceGeGetStack
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_rtc_prx;
        extern SubCategory syscall_sceRtc;
        extern SubCategory syscall_sceRtcTickAddTicks;
        extern SubCategory syscall_sceRtcTickAddMicroseconds;
        extern SubCategory syscall_sceRtcTickAddSeconds;
        extern SubCategory syscall_sceRtcTickAddMinutes;
        extern SubCategory syscall_sceRtcTickAddHours;
        extern SubCategory syscall_sceRtcTickAddDays;
        extern SubCategory syscall_sceRtcTickAddWeeks;
        extern SubCategory syscall_sceRtcTickAddMonths;
        extern SubCategory syscall_sceRtcTickAddYears;
        extern SubCategory syscall_sceRtcGetAccumulativeTime;
        extern SubCategory syscall_sceRtcGetAccumlativeTime;
        extern SubCategory syscall_sceRtcFormatRFC3339;
        extern SubCategory syscall_sceRtcGetDaysInMonth;
        extern SubCategory syscall_sceRtcSetTime64_t;
        extern SubCategory syscall_sceRtcGetLastReincarnatedTime;
        extern SubCategory syscall_sceRtcGetTime_t;
        extern SubCategory syscall_sceRtcFormatRFC3339LocalTime;
        extern SubCategory syscall_sceRtcParseRFC3339;
        extern SubCategory syscall_sceRtcConvertUtcToLocalTime;
        extern SubCategory syscall_sceRtcGetDosTime;
        extern SubCategory syscall_sceRtcSetTime_t;
        extern SubCategory syscall_sceRtcGetCurrentTick;
        extern SubCategory syscall_sceRtcIsLeapYear;
        extern SubCategory syscall_sceRtcCheckValid;
        extern SubCategory syscall_sceRtcGetCurrentClock;
        extern SubCategory syscall_sceRtcGetDayOfWeek;
        extern SubCategory syscall_sceRtcGetLastAdjustedTime;
        extern SubCategory syscall_sceRtcUnregisterCallback;
        extern SubCategory syscall_sceRtcGetTick;
        extern SubCategory syscall_sceRtcConvertLocalTimeToUTC;
        extern SubCategory syscall_sceRtcSetWin32FileTime;
        extern SubCategory syscall_sceRtc_7D1FBED3;
        extern SubCategory syscall_sceRtcFormatRFC2822LocalTime;
        extern SubCategory syscall_sceRtcSetTick;
        extern SubCategory syscall_sceRtcIsAlarmed;
        extern SubCategory syscall_sceRtcCompareTick;
        extern SubCategory syscall_sceRtc_A93CF7D8;
        extern SubCategory syscall_sceRtc_C2DDBEB5;
        extern SubCategory syscall_sceRtcGetTickResolution;
        extern SubCategory syscall_sceRtcFormatRFC2822;
        extern SubCategory syscall_sceRtcGetWin32FileTime;
        extern SubCategory syscall_sceRtcParseDateTime;
        extern SubCategory syscall_sceRtcGetTime64_t;
        extern SubCategory syscall_sceRtcGetCurrentClockLocalTime;
        extern SubCategory syscall_sceRtcSetDosTime;
        extern SubCategory syscall_sceRtc_F5FCC995;
        extern SubCategory syscall_sceRtcRegisterCallback;
    }
}

/////////////////////// Module : sceRTC_Service (rtc.prx) //////////////////////
///
/// /////////////////////////////// Library : sceRtc ///////////////////////////////
/// ///
    extern "C" bool __cdecl sceRtc$Init();
    extern "C" bool __cdecl sceRtc$Fini();
    extern "C" void __cdecl sceRtc_44F45E05(Allegrex::Context &); // sceRtcTickAddTicks
    extern "C" void __cdecl sceRtc_26D25A5D(Allegrex::Context &); // sceRtcTickAddMicroseconds
    extern "C" void __cdecl sceRtc_F2A4AFE5(Allegrex::Context &); // sceRtcTickAddSeconds
    extern "C" void __cdecl sceRtc_E6605BCA(Allegrex::Context &); // sceRtcTickAddMinutes
    extern "C" void __cdecl sceRtc_26D7A24A(Allegrex::Context &); // sceRtcTickAddHours
    extern "C" void __cdecl sceRtc_E51B4B7A(Allegrex::Context &); // sceRtcTickAddDays
    extern "C" void __cdecl sceRtc_CF3A2CA8(Allegrex::Context &); // sceRtcTickAddWeeks
    extern "C" void __cdecl sceRtc_DBF74F1B(Allegrex::Context &); // sceRtcTickAddMonths
    extern "C" void __cdecl sceRtc_42842C77(Allegrex::Context &); // sceRtcTickAddYears
    extern "C" void __cdecl sceRtc_011F03C1(Allegrex::Context &); // sceRtcGetAccumulativeTime
    extern "C" void __cdecl sceRtc_029CA3B3(Allegrex::Context &); // sceRtcGetAccumlativeTime
    extern "C" void __cdecl sceRtc_0498FB3C(Allegrex::Context &); // sceRtcFormatRFC3339
    extern "C" void __cdecl sceRtc_05EF322C(Allegrex::Context &); // sceRtcGetDaysInMonth
    extern "C" void __cdecl sceRtc_1909C99B(Allegrex::Context &); // sceRtcSetTime64_t
    extern "C" void __cdecl sceRtc_203CEB0D(Allegrex::Context &); // sceRtcGetLastReincarnatedTime
    extern "C" void __cdecl sceRtc_27C4594C(Allegrex::Context &); // sceRtcGetTime_t
    extern "C" void __cdecl sceRtc_27F98543(Allegrex::Context &); // sceRtcFormatRFC3339LocalTime
    extern "C" void __cdecl sceRtc_28E1E988(Allegrex::Context &); // sceRtcParseRFC3339
    extern "C" void __cdecl sceRtc_34885E0D(Allegrex::Context &); // sceRtcConvertUtcToLocalTime
    extern "C" void __cdecl sceRtc_36075567(Allegrex::Context &); // sceRtcGetDosTime
    extern "C" void __cdecl sceRtc_3A807CC8(Allegrex::Context &); // sceRtcSetTime_t
    extern "C" void __cdecl sceRtc_3F7AD767(Allegrex::Context &); // sceRtcGetCurrentTick
    extern "C" void __cdecl sceRtc_42307A17(Allegrex::Context &); // sceRtcIsLeapYear
    extern "C" void __cdecl sceRtc_4B1B5E82(Allegrex::Context &); // sceRtcCheckValid
    extern "C" void __cdecl sceRtc_4CFA57B0(Allegrex::Context &); // sceRtcGetCurrentClock
    extern "C" void __cdecl sceRtc_57726BC1(Allegrex::Context &); // sceRtcGetDayOfWeek
    extern "C" void __cdecl sceRtc_62685E98(Allegrex::Context &); // sceRtcGetLastAdjustedTime
    extern "C" void __cdecl sceRtc_6A676D2D(Allegrex::Context &); // sceRtcUnregisterCallback
    extern "C" void __cdecl sceRtc_6FF40ACC(Allegrex::Context &); // sceRtcGetTick
    extern "C" void __cdecl sceRtc_779242A2(Allegrex::Context &); // sceRtcConvertLocalTimeToUTC
    extern "C" void __cdecl sceRtc_7ACE4C04(Allegrex::Context &); // sceRtcSetWin32FileTime
    extern "C" void __cdecl sceRtc_7D1FBED3(Allegrex::Context &); // sceRtc_7D1FBED3
    extern "C" void __cdecl sceRtc_7DE6711B(Allegrex::Context &); // sceRtcFormatRFC2822LocalTime
    extern "C" void __cdecl sceRtc_7ED29E40(Allegrex::Context &); // sceRtcSetTick
    extern "C" void __cdecl sceRtc_81FCDA34(Allegrex::Context &); // sceRtcIsAlarmed
    extern "C" void __cdecl sceRtc_9ED0AE87(Allegrex::Context &); // sceRtcCompareTick
    extern "C" void __cdecl sceRtc_A93CF7D8(Allegrex::Context &); // sceRtc_A93CF7D8
    extern "C" void __cdecl sceRtc_C2DDBEB5(Allegrex::Context &); // sceRtc_C2DDBEB5
    extern "C" void __cdecl sceRtc_C41C2853(Allegrex::Context &); // sceRtcGetTickResolution
    extern "C" void __cdecl sceRtc_C663B3B9(Allegrex::Context &); // sceRtcFormatRFC2822
    extern "C" void __cdecl sceRtc_CF561893(Allegrex::Context &); // sceRtcGetWin32FileTime
    extern "C" void __cdecl sceRtc_DFBC5F16(Allegrex::Context &); // sceRtcParseDateTime
    extern "C" void __cdecl sceRtc_E1C93E47(Allegrex::Context &); // sceRtcGetTime64_t
    extern "C" void __cdecl sceRtc_E7C27D1B(Allegrex::Context &); // sceRtcGetCurrentClockLocalTime
    extern "C" void __cdecl sceRtc_F006F264(Allegrex::Context &); // sceRtcSetDosTime
    extern "C" void __cdecl sceRtc_F5FCC995(Allegrex::Context &); // sceRtc_F5FCC995
    extern "C" void __cdecl sceRtc_FB3B18CD(Allegrex::Context &); // sceRtcRegisterCallback
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_audio_prx;
        extern SubCategory syscall_sceAudio;
        extern SubCategory syscall_sceAudioChReserve;
        extern SubCategory syscall_sceAudioChRelease;
        extern SubCategory syscall_sceAudioOutput;
        extern SubCategory syscall_sceAudioOutputBlocking;
        extern SubCategory syscall_sceAudioOutputPanned;
        extern SubCategory syscall_sceAudioOutputPannedBlocking;
        extern SubCategory syscall_sceAudioChangeChannelVolume;
        extern SubCategory syscall_sceAudioChangeChannelConfig;
        extern SubCategory syscall_sceAudioSetChannelDataLen;
        extern SubCategory syscall_sceAudioGetChannelRestLen;
        extern SubCategory syscall_sceAudioGetChannelRestLength;
        extern SubCategory syscall_sceAudioSRCChReserve;
        extern SubCategory syscall_sceAudioSRCChRelease;
        extern SubCategory syscall_sceAudioSRCOutputBlocking;
        extern SubCategory syscall_sceAudioOutput2Reserve;
        extern SubCategory syscall_sceAudioOutput2Release;
        extern SubCategory syscall_sceAudioOutput2OutputBlocking;
        extern SubCategory syscall_sceAudioOutput2ChangeLength;
        extern SubCategory syscall_sceAudioOutput2GetRestSample;
        extern SubCategory syscall_sceAudioOneshotOutput;
        extern SubCategory syscall_sceAudioInputInit;
        extern SubCategory syscall_sceAudioInputInitEx;
        extern SubCategory syscall_sceAudioInput;
        extern SubCategory syscall_sceAudioInputBlocking;
        extern SubCategory syscall_sceAudioPollInputEnd;
        extern SubCategory syscall_sceAudioWaitInputEnd;
        extern SubCategory syscall_sceAudioGetInputLength;
    }
}

///////////////////// Module : sceAudio_Driver (audio.prx) /////////////////////
///
/// ////////////////////////////// Library : sceAudio //////////////////////////////
/// ///
    extern "C" bool __cdecl sceAudio$Init();
    extern "C" bool __cdecl sceAudio$Fini();
    extern "C" void __cdecl sceAudio_5EC81C55(Allegrex::Context &); // sceAudioChReserve
    extern "C" void __cdecl sceAudio_6FC46853(Allegrex::Context &); // sceAudioChRelease
    extern "C" void __cdecl sceAudio_8C1009B2(Allegrex::Context &); // sceAudioOutput
    extern "C" void __cdecl sceAudio_136CAF51(Allegrex::Context &); // sceAudioOutputBlocking
    extern "C" void __cdecl sceAudio_E2D56B2D(Allegrex::Context &); // sceAudioOutputPanned
    extern "C" void __cdecl sceAudio_13F592BC(Allegrex::Context &); // sceAudioOutputPannedBlocking
    extern "C" void __cdecl sceAudio_B7E1D8E7(Allegrex::Context &); // sceAudioChangeChannelVolume
    extern "C" void __cdecl sceAudio_95FD0C2D(Allegrex::Context &); // sceAudioChangeChannelConfig
    extern "C" void __cdecl sceAudio_CB2E439E(Allegrex::Context &); // sceAudioSetChannelDataLen
    extern "C" void __cdecl sceAudio_E9D97901(Allegrex::Context &); // sceAudioGetChannelRestLen
    extern "C" void __cdecl sceAudio_B011922F(Allegrex::Context &); // sceAudioGetChannelRestLength
    extern "C" void __cdecl sceAudio_38553111(Allegrex::Context &); // sceAudioSRCChReserve
    extern "C" void __cdecl sceAudio_5C37C0AE(Allegrex::Context &); // sceAudioSRCChRelease
    extern "C" void __cdecl sceAudio_E0727056(Allegrex::Context &); // sceAudioSRCOutputBlocking
    extern "C" void __cdecl sceAudio_01562BA3(Allegrex::Context &); // sceAudioOutput2Reserve
    extern "C" void __cdecl sceAudio_43196845(Allegrex::Context &); // sceAudioOutput2Release
    extern "C" void __cdecl sceAudio_2D53F36E(Allegrex::Context &); // sceAudioOutput2OutputBlocking
    extern "C" void __cdecl sceAudio_63F2889C(Allegrex::Context &); // sceAudioOutput2ChangeLength
    extern "C" void __cdecl sceAudio_647CEF33(Allegrex::Context &); // sceAudioOutput2GetRestSample
    extern "C" void __cdecl sceAudio_41EFADE7(Allegrex::Context &); // sceAudioOneshotOutput
    extern "C" void __cdecl sceAudio_7DE61688(Allegrex::Context &); // sceAudioInputInit
    extern "C" void __cdecl sceAudio_E926D3FB(Allegrex::Context &); // sceAudioInputInitEx
    extern "C" void __cdecl sceAudio_6D4BEC68(Allegrex::Context &); // sceAudioInput
    extern "C" void __cdecl sceAudio_086E5895(Allegrex::Context &); // sceAudioInputBlocking
    extern "C" void __cdecl sceAudio_A633048E(Allegrex::Context &); // sceAudioPollInputEnd
    extern "C" void __cdecl sceAudio_87B2E651(Allegrex::Context &); // sceAudioWaitInputEnd
    extern "C" void __cdecl sceAudio_A708C6A6(Allegrex::Context &); // sceAudioGetInputLength
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_display_prx;
        extern SubCategory syscall_sceDisplay;
        extern SubCategory syscall_sceDisplaySetMode;
        extern SubCategory syscall_sceDisplayGetMode;
        extern SubCategory syscall_sceDisplayGetFramePerSec;
        extern SubCategory syscall_sceDisplaySetFrameBuf;
        extern SubCategory syscall_sceDisplayGetFrameBuf;
        extern SubCategory syscall_sceDisplayIsForeground;
        extern SubCategory syscall_sceDisplaySetHoldMode;
        extern SubCategory syscall_sceDisplayGetVcount;
        extern SubCategory syscall_sceDisplayIsVblank;
        extern SubCategory syscall_sceDisplayGetVblankRest;
        extern SubCategory syscall_sceDisplayWaitVblank;
        extern SubCategory syscall_sceDisplayWaitVblankCB;
        extern SubCategory syscall_sceDisplayWaitVblankStart;
        extern SubCategory syscall_sceDisplayWaitVblankStartCB;
        extern SubCategory syscall_sceDisplayIsVsync;
        extern SubCategory syscall_sceDisplayGetCurrentHcount;
        extern SubCategory syscall_sceDisplayGetAccumulatedHcount;
        extern SubCategory syscall_sceDisplayAdjustAccumulatedHcount;
        extern SubCategory syscall_sceDisplaySetResumeMode;
        extern SubCategory syscall_sceDisplayGetResumeMode;
        extern SubCategory syscall_sceDisplayGetBrightness;
        extern SubCategory syscall_sceDisplay_40F1469C;
        extern SubCategory syscall_sceDisplay_77ED8B3A;
    }
}

/////////////////// Module : sceDisplay_Service (display.prx) //////////////////
///
/// ///////////////////////////// Library : sceDisplay /////////////////////////////
/// ///
    extern "C" bool __cdecl sceDisplay$Init();
    extern "C" bool __cdecl sceDisplay$Fini();
    extern "C" void __cdecl sceDisplay_0E20F177(Allegrex::Context &); // sceDisplaySetMode
    extern "C" void __cdecl sceDisplay_DEA197D4(Allegrex::Context &); // sceDisplayGetMode
    extern "C" void __cdecl sceDisplay_DBA6C4C4(Allegrex::Context &); // sceDisplayGetFramePerSec
    extern "C" void __cdecl sceDisplay_289D82FE(Allegrex::Context &); // sceDisplaySetFrameBuf
    extern "C" void __cdecl sceDisplay_EEDA2E54(Allegrex::Context &); // sceDisplayGetFrameBuf
    extern "C" void __cdecl sceDisplay_B4F378FA(Allegrex::Context &); // sceDisplayIsForeground
    extern "C" void __cdecl sceDisplay_7ED59BC4(Allegrex::Context &); // sceDisplaySetHoldMode
    extern "C" void __cdecl sceDisplay_9C6EAAD7(Allegrex::Context &); // sceDisplayGetVcount
    extern "C" void __cdecl sceDisplay_4D4E10EC(Allegrex::Context &); // sceDisplayIsVblank
    extern "C" void __cdecl sceDisplay_69B53541(Allegrex::Context &); // sceDisplayGetVblankRest
    extern "C" void __cdecl sceDisplay_36CDFADE(Allegrex::Context &); // sceDisplayWaitVblank
    extern "C" void __cdecl sceDisplay_8EB9EC49(Allegrex::Context &); // sceDisplayWaitVblankCB
    extern "C" void __cdecl sceDisplay_984C27E7(Allegrex::Context &); // sceDisplayWaitVblankStart
    extern "C" void __cdecl sceDisplay_46F186C3(Allegrex::Context &); // sceDisplayWaitVblankStartCB
    extern "C" void __cdecl sceDisplay_21038913(Allegrex::Context &); // sceDisplayIsVsync
    extern "C" void __cdecl sceDisplay_773DD3A3(Allegrex::Context &); // sceDisplayGetCurrentHcount
    extern "C" void __cdecl sceDisplay_210EAB3A(Allegrex::Context &); // sceDisplayGetAccumulatedHcount
    extern "C" void __cdecl sceDisplay_A83EF139(Allegrex::Context &); // sceDisplayAdjustAccumulatedHcount
    extern "C" void __cdecl sceDisplay_A544C486(Allegrex::Context &); // sceDisplaySetResumeMode
    extern "C" void __cdecl sceDisplay_BF79F646(Allegrex::Context &); // sceDisplayGetResumeMode
    extern "C" void __cdecl sceDisplay_31C4BAA8(Allegrex::Context &); // sceDisplayGetBrightness
    extern "C" void __cdecl sceDisplay_40F1469C(Allegrex::Context &); // sceDisplay_40F1469C
    extern "C" void __cdecl sceDisplay_77ED8B3A(Allegrex::Context &); // sceDisplay_77ED8B3A
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_ctrl_prx;
        extern SubCategory syscall_sceCtrl;
        extern SubCategory syscall_sceCtrlSetSamplingMode;
        extern SubCategory syscall_sceCtrlGetSamplingMode;
        extern SubCategory syscall_sceCtrlSetSamplingCycle;
        extern SubCategory syscall_sceCtrlGetSamplingCycle;
        extern SubCategory syscall_sceCtrlSetIdleCancelThreshold;
        extern SubCategory syscall_sceCtrlGetIdleCancelThreshold;
        extern SubCategory syscall_sceCtrlPeekBufferPositive;
        extern SubCategory syscall_sceCtrlPeekBufferNegative;
        extern SubCategory syscall_sceCtrlReadBufferPositive;
        extern SubCategory syscall_sceCtrlReadBufferNegative;
        extern SubCategory syscall_sceCtrlPeekLatch;
        extern SubCategory syscall_sceCtrlReadLatch;
        extern SubCategory syscall_sceCtrlClearRapidFire;
        extern SubCategory syscall_sceCtrlSetRapidFire;
        extern SubCategory syscall_sceCtrl_348D99D4;
        extern SubCategory syscall_sceCtrl_AF5960F3;
    }
}

/////////////////// Module : sceController_Service (ctrl.prx) //////////////////
///
/// /////////////////////////////// Library : sceCtrl //////////////////////////////
/// ///
    extern "C" bool __cdecl sceCtrl$Init();
    extern "C" bool __cdecl sceCtrl$Fini();
    extern "C" void __cdecl sceCtrl_1F4011E6(Allegrex::Context &); // sceCtrlSetSamplingMode
    extern "C" void __cdecl sceCtrl_DA6B76A1(Allegrex::Context &); // sceCtrlGetSamplingMode
    extern "C" void __cdecl sceCtrl_6A2774F3(Allegrex::Context &); // sceCtrlSetSamplingCycle
    extern "C" void __cdecl sceCtrl_02BAAD91(Allegrex::Context &); // sceCtrlGetSamplingCycle
    extern "C" void __cdecl sceCtrl_A7144800(Allegrex::Context &); // sceCtrlSetIdleCancelThreshold
    extern "C" void __cdecl sceCtrl_687660FA(Allegrex::Context &); // sceCtrlGetIdleCancelThreshold
    extern "C" void __cdecl sceCtrl_3A622550(Allegrex::Context &); // sceCtrlPeekBufferPositive
    extern "C" void __cdecl sceCtrl_C152080A(Allegrex::Context &); // sceCtrlPeekBufferNegative
    extern "C" void __cdecl sceCtrl_1F803938(Allegrex::Context &); // sceCtrlReadBufferPositive
    extern "C" void __cdecl sceCtrl_60B81F86(Allegrex::Context &); // sceCtrlReadBufferNegative
    extern "C" void __cdecl sceCtrl_B1D0E5CD(Allegrex::Context &); // sceCtrlPeekLatch
    extern "C" void __cdecl sceCtrl_0B588501(Allegrex::Context &); // sceCtrlReadLatch
    extern "C" void __cdecl sceCtrl_A68FD260(Allegrex::Context &); // sceCtrlClearRapidFire
    extern "C" void __cdecl sceCtrl_6841BE1A(Allegrex::Context &); // sceCtrlSetRapidFire
    extern "C" void __cdecl sceCtrl_348D99D4(Allegrex::Context &); // sceCtrl_348D99D4
    extern "C" void __cdecl sceCtrl_AF5960F3(Allegrex::Context &); // sceCtrl_AF5960F3
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_hpremote_prx;
        extern SubCategory syscall_sceHprm;
        extern SubCategory syscall_sceHprmPeekCurrentKey;
        extern SubCategory syscall_sceHprmIsRemoteExist;
        extern SubCategory syscall_sceHprmIsMicrophoneExist;
        extern SubCategory syscall_sceHprmPeekLatch;
        extern SubCategory syscall_sceHprm_3953DE6B;
        extern SubCategory syscall_sceHprm_396FD885;
        extern SubCategory syscall_sceHprmReadLatch;
        extern SubCategory syscall_sceHprmUnregitserCallback;
        extern SubCategory syscall_sceHprmGetHpDetect;
        extern SubCategory syscall_sceHprmIsHeadphoneExist;
        extern SubCategory syscall_sceHprmRegisterCallback;
        extern SubCategory syscall_sceHprm_FD7DE6CD;
    }
}

////////////////// Module : sceHP_Remote_Driver (hpremote.prx) /////////////////
///
/// /////////////////////////////// Library : sceHprm //////////////////////////////
/// ///
    extern "C" bool __cdecl sceHprm$Init();
    extern "C" bool __cdecl sceHprm$Fini();
    extern "C" void __cdecl sceHprm_1910B327(Allegrex::Context &); // sceHprmPeekCurrentKey
    extern "C" void __cdecl sceHprm_208DB1BD(Allegrex::Context &); // sceHprmIsRemoteExist
    extern "C" void __cdecl sceHprm_219C58F1(Allegrex::Context &); // sceHprmIsMicrophoneExist
    extern "C" void __cdecl sceHprm_2BCEC83E(Allegrex::Context &); // sceHprmPeekLatch
    extern "C" void __cdecl sceHprm_3953DE6B(Allegrex::Context &); // sceHprm_3953DE6B
    extern "C" void __cdecl sceHprm_396FD885(Allegrex::Context &); // sceHprm_396FD885
    extern "C" void __cdecl sceHprm_40D2F9F0(Allegrex::Context &); // sceHprmReadLatch
    extern "C" void __cdecl sceHprm_444ED0B7(Allegrex::Context &); // sceHprmUnregitserCallback
    extern "C" void __cdecl sceHprm_71B5FB67(Allegrex::Context &); // sceHprmGetHpDetect
    extern "C" void __cdecl sceHprm_7E69EDA4(Allegrex::Context &); // sceHprmIsHeadphoneExist
    extern "C" void __cdecl sceHprm_C7154136(Allegrex::Context &); // sceHprmRegisterCallback
    extern "C" void __cdecl sceHprm_FD7DE6CD(Allegrex::Context &); // sceHprm_FD7DE6CD
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_power_prx;
        extern SubCategory syscall_scePower;
        extern SubCategory syscall_scePowerGetResumeCount;
        extern SubCategory syscall_scePowerRequestColdReset;
        extern SubCategory syscall_scePowerRegisterCallback;
        extern SubCategory syscall_scePowerIsBatteryExist;
        extern SubCategory syscall_scePowerSetPowerSwMode;
        extern SubCategory syscall_scePowerGetPowerSwMode;
        extern SubCategory syscall_scePowerIsBatteryCharging;
        extern SubCategory syscall_scePowerGetBatteryLifePercent;
        extern SubCategory syscall_scePowerGetInnerTemp;
        extern SubCategory syscall_scePowerVolatileMemLock;
        extern SubCategory syscall_scePowerBatteryUpdateInfo;
        extern SubCategory syscall_scePower_2875994B;
        extern SubCategory syscall_scePowerGetBatteryTemp;
        extern SubCategory syscall_scePower_2B51FE2F;
        extern SubCategory syscall_scePowerRequestStandby;
        extern SubCategory syscall_scePowerGetPllClockFrequencyInt;
        extern SubCategory syscall_scePowerWaitRequestCompletion;
        extern SubCategory syscall_scePowerGetBacklightMaximum;
        extern SubCategory syscall_scePowerGetBusClockFrequency;
        extern SubCategory syscall_scePowerGetBatteryVolt;
        extern SubCategory syscall_scePower_545A7F3C;
        extern SubCategory syscall_scePowerSetClockFrequency;
        extern SubCategory syscall_scePowerIsSuspendRequired;
        extern SubCategory syscall_scePowerIdleTimerEnable;
        extern SubCategory syscall_scePowerIsRequest;
        extern SubCategory syscall_scePowerSetCpuClockFrequency;
        extern SubCategory syscall_scePowerGetBatteryElec;
        extern SubCategory syscall_scePowerIsPowerOnline;
        extern SubCategory syscall_scePowerGetBatteryLifeTime;
        extern SubCategory syscall_scePowerGetBatteryRemainCapacity;
        extern SubCategory syscall_scePowerIdleTimerDisable;
        extern SubCategory syscall_scePowerGetBusClockFrequencyFloat;
        extern SubCategory syscall_scePower_A4E93389;
        extern SubCategory syscall_scePowerSetCallbackMode;
        extern SubCategory syscall_scePowerRequestSuspend;
        extern SubCategory syscall_scePowerGetCpuClockFrequencyFloat;
        extern SubCategory syscall_scePowerVolatileMemUnlock;
        extern SubCategory syscall_scePowerGetBatteryChargingStatus;
        extern SubCategory syscall_scePowerSetBusClockFrequency;
        extern SubCategory syscall_scePowerGetLowBatteryCapacity;
        extern SubCategory syscall_scePowerGetCallbackMode;
        extern SubCategory syscall_scePowerGetBusClockFrequencyInt;
        extern SubCategory syscall_scePowerUnlock;
        extern SubCategory syscall_scePowerGetBatteryChargeCycle;
        extern SubCategory syscall_scePowerIsLowBattery;
        extern SubCategory syscall_scePowerLock;
        extern SubCategory syscall_scePowerCancelRequest;
        extern SubCategory syscall_scePowerUnregitserCallback;
        extern SubCategory syscall_scePowerUnregisterCallback;
        extern SubCategory syscall_scePower_E8E4E204;
        extern SubCategory syscall_scePowerGetPllClockFrequencyFloat;
        extern SubCategory syscall_scePower_EBD177D6;
        extern SubCategory syscall_scePowerGetIdleTimer;
        extern SubCategory syscall_scePowerTick;
        extern SubCategory syscall_scePowerVolatileMemTryLock;
        extern SubCategory syscall_scePowerGetBatteryFullCapacity;
        extern SubCategory syscall_scePowerGetCpuClockFrequencyInt;
        extern SubCategory syscall_scePowerGetCpuClockFrequency;
    }
}

///////////////////// Module : scePower_Service (power.prx) ////////////////////
///
/// ////////////////////////////// Library : scePower //////////////////////////////
/// ///
    extern "C" bool __cdecl scePower$Init();
    extern "C" bool __cdecl scePower$Fini();
    extern "C" void __cdecl scePower_0074EF9B(Allegrex::Context &); // scePowerGetResumeCount
    extern "C" void __cdecl scePower_0442D852(Allegrex::Context &); // scePowerRequestColdReset
    extern "C" void __cdecl scePower_04B7766E(Allegrex::Context &); // scePowerRegisterCallback
    extern "C" void __cdecl scePower_0AFD0D8B(Allegrex::Context &); // scePowerIsBatteryExist
    extern "C" void __cdecl scePower_0CD21B1F(Allegrex::Context &); // scePowerSetPowerSwMode
    extern "C" void __cdecl scePower_165CE085(Allegrex::Context &); // scePowerGetPowerSwMode
    extern "C" void __cdecl scePower_1E490401(Allegrex::Context &); // scePowerIsBatteryCharging
    extern "C" void __cdecl scePower_2085D15D(Allegrex::Context &); // scePowerGetBatteryLifePercent
    extern "C" void __cdecl scePower_23436A4A(Allegrex::Context &); // scePowerGetInnerTemp
    extern "C" void __cdecl scePower_23C31FFE(Allegrex::Context &); // scePowerVolatileMemLock
    extern "C" void __cdecl scePower_27F3292C(Allegrex::Context &); // scePowerBatteryUpdateInfo
    extern "C" void __cdecl scePower_2875994B(Allegrex::Context &); // scePower_2875994B
    extern "C" void __cdecl scePower_28E12023(Allegrex::Context &); // scePowerGetBatteryTemp
    extern "C" void __cdecl scePower_2B51FE2F(Allegrex::Context &); // scePower_2B51FE2F
    extern "C" void __cdecl scePower_2B7C7CF4(Allegrex::Context &); // scePowerRequestStandby
    extern "C" void __cdecl scePower_34F9C463(Allegrex::Context &); // scePowerGetPllClockFrequencyInt
    extern "C" void __cdecl scePower_3951AF53(Allegrex::Context &); // scePowerWaitRequestCompletion
    extern "C" void __cdecl scePower_442BFBAC(Allegrex::Context &); // scePowerGetBacklightMaximum
    extern "C" void __cdecl scePower_478FE6F5(Allegrex::Context &); // scePowerGetBusClockFrequency
    extern "C" void __cdecl scePower_483CE86B(Allegrex::Context &); // scePowerGetBatteryVolt
    extern "C" void __cdecl scePower_545A7F3C(Allegrex::Context &); // scePower_545A7F3C
    extern "C" void __cdecl scePower_737486F2(Allegrex::Context &); // scePowerSetClockFrequency
    extern "C" void __cdecl scePower_78A1A796(Allegrex::Context &); // scePowerIsSuspendRequired
    extern "C" void __cdecl scePower_7F30B3B1(Allegrex::Context &); // scePowerIdleTimerEnable
    extern "C" void __cdecl scePower_7FA406DD(Allegrex::Context &); // scePowerIsRequest
    extern "C" void __cdecl scePower_843FBF43(Allegrex::Context &); // scePowerSetCpuClockFrequency
    extern "C" void __cdecl scePower_862AE1A6(Allegrex::Context &); // scePowerGetBatteryElec
    extern "C" void __cdecl scePower_87440F5E(Allegrex::Context &); // scePowerIsPowerOnline
    extern "C" void __cdecl scePower_8EFB3FA2(Allegrex::Context &); // scePowerGetBatteryLifeTime
    extern "C" void __cdecl scePower_94F5A53F(Allegrex::Context &); // scePowerGetBatteryRemainCapacity
    extern "C" void __cdecl scePower_972CE941(Allegrex::Context &); // scePowerIdleTimerDisable
    extern "C" void __cdecl scePower_9BADB3EB(Allegrex::Context &); // scePowerGetBusClockFrequencyFloat
    extern "C" void __cdecl scePower_A4E93389(Allegrex::Context &); // scePower_A4E93389
    extern "C" void __cdecl scePower_A9D22232(Allegrex::Context &); // scePowerSetCallbackMode
    extern "C" void __cdecl scePower_AC32C9CC(Allegrex::Context &); // scePowerRequestSuspend
    extern "C" void __cdecl scePower_B1A52C83(Allegrex::Context &); // scePowerGetCpuClockFrequencyFloat
    extern "C" void __cdecl scePower_B3EDD801(Allegrex::Context &); // scePowerVolatileMemUnlock
    extern "C" void __cdecl scePower_B4432BC8(Allegrex::Context &); // scePowerGetBatteryChargingStatus
    extern "C" void __cdecl scePower_B8D7B3FB(Allegrex::Context &); // scePowerSetBusClockFrequency
    extern "C" void __cdecl scePower_B999184C(Allegrex::Context &); // scePowerGetLowBatteryCapacity
    extern "C" void __cdecl scePower_BAFA3DF0(Allegrex::Context &); // scePowerGetCallbackMode
    extern "C" void __cdecl scePower_BD681969(Allegrex::Context &); // scePowerGetBusClockFrequencyInt
    extern "C" void __cdecl scePower_CA3D34C1(Allegrex::Context &); // scePowerUnlock
    extern "C" void __cdecl scePower_CB49F5CE(Allegrex::Context &); // scePowerGetBatteryChargeCycle
    extern "C" void __cdecl scePower_D3075926(Allegrex::Context &); // scePowerIsLowBattery
    extern "C" void __cdecl scePower_D6D016EF(Allegrex::Context &); // scePowerLock
    extern "C" void __cdecl scePower_DB62C9CF(Allegrex::Context &); // scePowerCancelRequest
    extern "C" void __cdecl scePower_DB9D28DD(Allegrex::Context &); // scePowerUnregitserCallback
    extern "C" void __cdecl scePower_DFA8BAF8(Allegrex::Context &); // scePowerUnregisterCallback
    extern "C" void __cdecl scePower_E8E4E204(Allegrex::Context &); // scePower_E8E4E204
    extern "C" void __cdecl scePower_EA382A27(Allegrex::Context &); // scePowerGetPllClockFrequencyFloat
    extern "C" void __cdecl scePower_EBD177D6(Allegrex::Context &); // scePower_EBD177D6
    extern "C" void __cdecl scePower_EDC13FE5(Allegrex::Context &); // scePowerGetIdleTimer
    extern "C" void __cdecl scePower_EFD3C963(Allegrex::Context &); // scePowerTick
    extern "C" void __cdecl scePower_FA97A599(Allegrex::Context &); // scePowerVolatileMemTryLock
    extern "C" void __cdecl scePower_FD18A0FF(Allegrex::Context &); // scePowerGetBatteryFullCapacity
    extern "C" void __cdecl scePower_FDB5BFE9(Allegrex::Context &); // scePowerGetCpuClockFrequencyInt
    extern "C" void __cdecl scePower_FEE03A2F(Allegrex::Context &); // scePowerGetCpuClockFrequency
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_usb_prx;
        extern SubCategory syscall_sceUsb;
        extern SubCategory syscall_sceUsbGetDrvState;
        extern SubCategory syscall_sceUsbWaitCancel;
        extern SubCategory syscall_sceUsbGetDrvList;
        extern SubCategory syscall_sceUsbActivate;
        extern SubCategory syscall_sceUsbWaitState;
        extern SubCategory syscall_sceUsbWaitStateCB;
        extern SubCategory syscall_sceUsb_89DE0DC5;
        extern SubCategory syscall_sceUsb_8BFC3DE8;
        extern SubCategory syscall_sceUsbStart;
        extern SubCategory syscall_sceUsbGetState;
        extern SubCategory syscall_sceUsbStop;
        extern SubCategory syscall_sceUsbDeactivate;
        extern SubCategory syscall_sceUsbActivateWithCharging;
    }
}

/////////////////////// Module : sceUSB_Driver (usb.prx) ///////////////////////
///
/// /////////////////////////////// Library : sceUsb ///////////////////////////////
/// ///
    extern "C" bool __cdecl sceUsb$Init();
    extern "C" bool __cdecl sceUsb$Fini();
    extern "C" void __cdecl sceUsb_112CC951(Allegrex::Context &); // sceUsbGetDrvState
    extern "C" void __cdecl sceUsb_1C360735(Allegrex::Context &); // sceUsbWaitCancel
    extern "C" void __cdecl sceUsb_4E537366(Allegrex::Context &); // sceUsbGetDrvList
    extern "C" void __cdecl sceUsb_586DB82C(Allegrex::Context &); // sceUsbActivate
    extern "C" void __cdecl sceUsb_5BE0E002(Allegrex::Context &); // sceUsbWaitState
    extern "C" void __cdecl sceUsb_616F2B61(Allegrex::Context &); // sceUsbWaitStateCB
    extern "C" void __cdecl sceUsb_89DE0DC5(Allegrex::Context &); // sceUsb_89DE0DC5
    extern "C" void __cdecl sceUsb_8BFC3DE8(Allegrex::Context &); // sceUsb_8BFC3DE8
    extern "C" void __cdecl sceUsb_AE5DE6AF(Allegrex::Context &); // sceUsbStart
    extern "C" void __cdecl sceUsb_C21645A4(Allegrex::Context &); // sceUsbGetState
    extern "C" void __cdecl sceUsb_C2464FA0(Allegrex::Context &); // sceUsbStop
    extern "C" void __cdecl sceUsb_C572A9C8(Allegrex::Context &); // sceUsbDeactivate
    extern "C" void __cdecl sceUsb_E20B23A6(Allegrex::Context &); // sceUsbActivateWithCharging
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_openpsid_prx;
        extern SubCategory syscall_sceOpenPSID;
        extern SubCategory syscall_sceOpenPSIDGetOpenPSID;
        extern SubCategory syscall_sceDdrdb;
        extern SubCategory syscall_sceDdrdb_F013F8BF;
    }
}

////////////////// Module : sceOpenPSID_Service (openpsid.prx) /////////////////
///
/// ///////////////////////////// Library : sceOpenPSID ////////////////////////////
/// ///
    extern "C" bool __cdecl sceOpenPSID$Init();
    extern "C" bool __cdecl sceOpenPSID$Fini();
    extern "C" void __cdecl sceOpenPSID_C69BEBCE(Allegrex::Context &); // sceOpenPSIDGetOpenPSID
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// ////////////////////////////// Library : sceDdrdb //////////////////////////////
/// ///
    extern "C" bool __cdecl sceDdrdb$Init();
    extern "C" bool __cdecl sceDdrdb$Fini();
    extern "C" void __cdecl sceDdrdb_F013F8BF(Allegrex::Context &); // sceDdrdb_F013F8BF
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_sircs_prx;
        extern SubCategory syscall_sceSircs;
        extern SubCategory syscall_sceSircsSend;
        extern SubCategory syscall_sceSircsReceive;
    }
}

/////////////////// Module : sceSIRCS_IrDA_Driver (sircs.prx) //////////////////
///
/// ////////////////////////////// Library : sceSircs //////////////////////////////
/// ///
    extern "C" bool __cdecl sceSircs$Init();
    extern "C" bool __cdecl sceSircs$Fini();
    extern "C" void __cdecl sceSircs_71EEF62D(Allegrex::Context &); // sceSircsSend
    extern "C" void __cdecl sceSircs_83381633(Allegrex::Context &); // sceSircsReceive
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_mediaman_prx;
        extern SubCategory syscall_sceUmdUser;
        extern SubCategory syscall_sceUmdGetErrorStat;
        extern SubCategory syscall_sceUmdGetDiscInfo;
        extern SubCategory syscall_sceUmdCheckMedium;
        extern SubCategory syscall_sceUmdWaitDriveStatCB;
        extern SubCategory syscall_sceUmdWaitDriveStatWithTimer;
        extern SubCategory syscall_sceUmdCancelWaitDriveStat;
        extern SubCategory syscall_sceUmdGetDriveStat;
        extern SubCategory syscall_sceUmdReplaceProhibit;
        extern SubCategory syscall_sceUmdWaitDriveStat;
        extern SubCategory syscall_sceUmdRegisterUMDCallBack;
        extern SubCategory syscall_sceUmdUnRegisterUMDCallBack;
        extern SubCategory syscall_sceUmdActivate;
        extern SubCategory syscall_sceUmdReplacePermit;
        extern SubCategory syscall_sceUmdDeactivate;
    }
}

///////////////////// Module : sceUmd_driver (mediaman.prx) ////////////////////
///
/// ///////////////////////////// Library : sceUmdUser /////////////////////////////
/// ///
    extern "C" bool __cdecl sceUmdUser$Init();
    extern "C" bool __cdecl sceUmdUser$Fini();
    extern "C" void __cdecl sceUmdUser_20628E6F(Allegrex::Context &); // sceUmdGetErrorStat
    extern "C" void __cdecl sceUmdUser_340B7686(Allegrex::Context &); // sceUmdGetDiscInfo
    extern "C" void __cdecl sceUmdUser_46EBB729(Allegrex::Context &); // sceUmdCheckMedium
    extern "C" void __cdecl sceUmdUser_4A9E5E29(Allegrex::Context &); // sceUmdWaitDriveStatCB
    extern "C" void __cdecl sceUmdUser_56202973(Allegrex::Context &); // sceUmdWaitDriveStatWithTimer
    extern "C" void __cdecl sceUmdUser_6AF9B50A(Allegrex::Context &); // sceUmdCancelWaitDriveStat
    extern "C" void __cdecl sceUmdUser_6B4A146C(Allegrex::Context &); // sceUmdGetDriveStat
    extern "C" void __cdecl sceUmdUser_87533940(Allegrex::Context &); // sceUmdReplaceProhibit
    extern "C" void __cdecl sceUmdUser_8EF08FCE(Allegrex::Context &); // sceUmdWaitDriveStat
    extern "C" void __cdecl sceUmdUser_AEE7404D(Allegrex::Context &); // sceUmdRegisterUMDCallBack
    extern "C" void __cdecl sceUmdUser_BD2BDE07(Allegrex::Context &); // sceUmdUnRegisterUMDCallBack
    extern "C" void __cdecl sceUmdUser_C6183D47(Allegrex::Context &); // sceUmdActivate
    extern "C" void __cdecl sceUmdUser_CBE9F02A(Allegrex::Context &); // sceUmdReplacePermit
    extern "C" void __cdecl sceUmdUser_E83742BA(Allegrex::Context &); // sceUmdDeactivate
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_wlan_prx;
        extern SubCategory syscall_sceWlanDrv;
        extern SubCategory syscall_sceWlanGetEtherAddr;
        extern SubCategory syscall_sceWlanDevIsPowerOn;
        extern SubCategory syscall_sceWlanGetSwitchState;
        extern SubCategory syscall_sceWlanDrv_lib;
        extern SubCategory syscall_sceWlanDevGetStateGPIO;
        extern SubCategory syscall_sceWlanDevGetMacAddr;
        extern SubCategory syscall_sceWlanDrv_lib_2D0FAE4E;
        extern SubCategory syscall_sceWlanDrv_lib_40B0AA4A;
        extern SubCategory syscall_sceWlanGetDropRate;
        extern SubCategory syscall_sceWlanDevAttach;
        extern SubCategory syscall_sceWlanDrv_lib_4C14BACA;
        extern SubCategory syscall_sceWlanGPUnRegisterCallback;
        extern SubCategory syscall_sceWlanDrv_lib_56F467CA;
        extern SubCategory syscall_sceWlanDrv_lib_5BAA1FE5;
        extern SubCategory syscall_sceWlanDevIsGameMode;
        extern SubCategory syscall_sceWlanGPPrevEstablishActive;
        extern SubCategory syscall_sceWlanDrv_lib_6D5C839E;
        extern SubCategory syscall_sceWlanSetHostDiscover;
        extern SubCategory syscall_sceWlanDevSetGPIO;
        extern SubCategory syscall_sceWlanDrv_lib_81579D36;
        extern SubCategory syscall_sceWlanDrv_lib_8D5F551B;
        extern SubCategory syscall_sceWlanGPRegisterCallback;
        extern SubCategory syscall_sceWlanGPRecv;
        extern SubCategory syscall_sceWlanGPSend;
        extern SubCategory syscall_sceWlanDevDetach;
        extern SubCategory syscall_sceWlanSetDropRate;
        extern SubCategory syscall_sceWlanDropCheck;
        extern SubCategory syscall_sceWlanSetWakeUp;
    }
}

////////////////////// Module : sceWlan_Driver (wlan.prx) //////////////////////
///
/// ///////////////////////////// Library : sceWlanDrv /////////////////////////////
/// ///
    extern "C" bool __cdecl sceWlanDrv$Init();
    extern "C" bool __cdecl sceWlanDrv$Fini();
    extern "C" void __cdecl sceWlanDrv_0C622081(Allegrex::Context &); // sceWlanGetEtherAddr
    extern "C" void __cdecl sceWlanDrv_93440B11(Allegrex::Context &); // sceWlanDevIsPowerOn
    extern "C" void __cdecl sceWlanDrv_D7763699(Allegrex::Context &); // sceWlanGetSwitchState
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// /////////////////////////// Library : sceWlanDrv_lib ///////////////////////////
/// ///
    extern "C" bool __cdecl sceWlanDrv_lib$Init();
    extern "C" bool __cdecl sceWlanDrv_lib$Fini();
    extern "C" void __cdecl sceWlanDrv_lib_05FE320C(Allegrex::Context &); // sceWlanDevGetStateGPIO
    extern "C" void __cdecl sceWlanDrv_lib_19E51F54(Allegrex::Context &); // sceWlanDevGetMacAddr
    extern "C" void __cdecl sceWlanDrv_lib_2D0FAE4E(Allegrex::Context &); // sceWlanDrv_lib_2D0FAE4E
    extern "C" void __cdecl sceWlanDrv_lib_40B0AA4A(Allegrex::Context &); // sceWlanDrv_lib_40B0AA4A
    extern "C" void __cdecl sceWlanDrv_lib_44A99F9D(Allegrex::Context &); // sceWlanGetDropRate
    extern "C" void __cdecl sceWlanDrv_lib_482CAE9A(Allegrex::Context &); // sceWlanDevAttach
    extern "C" void __cdecl sceWlanDrv_lib_4C14BACA(Allegrex::Context &); // sceWlanDrv_lib_4C14BACA
    extern "C" void __cdecl sceWlanDrv_lib_4C7F62E0(Allegrex::Context &); // sceWlanGPUnRegisterCallback
    extern "C" void __cdecl sceWlanDrv_lib_56F467CA(Allegrex::Context &); // sceWlanDrv_lib_56F467CA
    extern "C" void __cdecl sceWlanDrv_lib_5BAA1FE5(Allegrex::Context &); // sceWlanDrv_lib_5BAA1FE5
    extern "C" void __cdecl sceWlanDrv_lib_5E7C8D94(Allegrex::Context &); // sceWlanDevIsGameMode
    extern "C" void __cdecl sceWlanDrv_lib_5ED4049A(Allegrex::Context &); // sceWlanGPPrevEstablishActive
    extern "C" void __cdecl sceWlanDrv_lib_6D5C839E(Allegrex::Context &); // sceWlanDrv_lib_6D5C839E
    extern "C" void __cdecl sceWlanDrv_lib_749B813A(Allegrex::Context &); // sceWlanSetHostDiscover
    extern "C" void __cdecl sceWlanDrv_lib_7FF54BD2(Allegrex::Context &); // sceWlanDevSetGPIO
    extern "C" void __cdecl sceWlanDrv_lib_81579D36(Allegrex::Context &); // sceWlanDrv_lib_81579D36
    extern "C" void __cdecl sceWlanDrv_lib_8D5F551B(Allegrex::Context &); // sceWlanDrv_lib_8D5F551B
    extern "C" void __cdecl sceWlanDrv_lib_9658C9F7(Allegrex::Context &); // sceWlanGPRegisterCallback
    extern "C" void __cdecl sceWlanDrv_lib_A447103A(Allegrex::Context &); // sceWlanGPRecv
    extern "C" void __cdecl sceWlanDrv_lib_B4D7CB74(Allegrex::Context &); // sceWlanGPSend
    extern "C" void __cdecl sceWlanDrv_lib_C9A8CAB7(Allegrex::Context &); // sceWlanDevDetach
    extern "C" void __cdecl sceWlanDrv_lib_EB3235B5(Allegrex::Context &); // sceWlanSetDropRate
    extern "C" void __cdecl sceWlanDrv_lib_FBD385FB(Allegrex::Context &); // sceWlanDropCheck
    extern "C" void __cdecl sceWlanDrv_lib_FE8A0B46(Allegrex::Context &); // sceWlanSetWakeUp
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_registry_prx;
        extern SubCategory syscall_sceReg;
        extern SubCategory syscall_sceRegCloseCategory;
        extern SubCategory syscall_sceRegFlushCategory;
        extern SubCategory syscall_sceRegSetKeyValue;
        extern SubCategory syscall_sceRegOpenCategory;
        extern SubCategory syscall_sceRegGetKeyValue;
        extern SubCategory syscall_sceRegGetKeysNum;
        extern SubCategory syscall_sceRegGetKeys;
        extern SubCategory syscall_sceRegGetKeyValueByName;
        extern SubCategory syscall_sceRegRemoveKey;
        extern SubCategory syscall_sceRegFlushRegistry;
        extern SubCategory syscall_sceRegRemoveCategory;
        extern SubCategory syscall_sceRegCreateKey;
        extern SubCategory syscall_sceReg_835ECE6F;
        extern SubCategory syscall_sceRegOpenRegistry;
        extern SubCategory syscall_sceRegExit;
        extern SubCategory syscall_sceReg_BE8C1263;
        extern SubCategory syscall_sceRegGetKeyInfoByName;
        extern SubCategory syscall_sceRegGetKeyInfo;
        extern SubCategory syscall_sceRegRemoveRegistry;
        extern SubCategory syscall_sceRegCloseRegistry;
    }
}

////////////////// Module : sceRegistry_Service (registry.prx) /////////////////
///
/// /////////////////////////////// Library : sceReg ///////////////////////////////
/// ///
    extern "C" bool __cdecl sceReg$Init();
    extern "C" bool __cdecl sceReg$Fini();
    extern "C" void __cdecl sceReg_0CAE832B(Allegrex::Context &); // sceRegCloseCategory
    extern "C" void __cdecl sceReg_0D69BF40(Allegrex::Context &); // sceRegFlushCategory
    extern "C" void __cdecl sceReg_17768E14(Allegrex::Context &); // sceRegSetKeyValue
    extern "C" void __cdecl sceReg_1D8A762E(Allegrex::Context &); // sceRegOpenCategory
    extern "C" void __cdecl sceReg_28A8E98A(Allegrex::Context &); // sceRegGetKeyValue
    extern "C" void __cdecl sceReg_2C0DB9DD(Allegrex::Context &); // sceRegGetKeysNum
    extern "C" void __cdecl sceReg_2D211135(Allegrex::Context &); // sceRegGetKeys
    extern "C" void __cdecl sceReg_30BE0259(Allegrex::Context &); // sceRegGetKeyValueByName
    extern "C" void __cdecl sceReg_3615BC87(Allegrex::Context &); // sceRegRemoveKey
    extern "C" void __cdecl sceReg_39461B4D(Allegrex::Context &); // sceRegFlushRegistry
    extern "C" void __cdecl sceReg_4CA16893(Allegrex::Context &); // sceRegRemoveCategory
    extern "C" void __cdecl sceReg_57641A81(Allegrex::Context &); // sceRegCreateKey
    extern "C" void __cdecl sceReg_835ECE6F(Allegrex::Context &); // sceReg_835ECE6F
    extern "C" void __cdecl sceReg_92E41280(Allegrex::Context &); // sceRegOpenRegistry
    extern "C" void __cdecl sceReg_9B25EDF1(Allegrex::Context &); // sceRegExit
    extern "C" void __cdecl sceReg_BE8C1263(Allegrex::Context &); // sceReg_BE8C1263
    extern "C" void __cdecl sceReg_C5768D02(Allegrex::Context &); // sceRegGetKeyInfoByName
    extern "C" void __cdecl sceReg_D4475AA8(Allegrex::Context &); // sceRegGetKeyInfo
    extern "C" void __cdecl sceReg_DEDA92BF(Allegrex::Context &); // sceRegRemoveRegistry
    extern "C" void __cdecl sceReg_FA8A5739(Allegrex::Context &); // sceRegCloseRegistry
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_utility_prx;
        extern SubCategory syscall_sceUtility;
        extern SubCategory syscall_sceUtility_0251B134;
        extern SubCategory syscall_sceUtilityHtmlViewerUpdate;
        extern SubCategory syscall_sceUtility_06A48659;
        extern SubCategory syscall_sceUtilityLoadUsbModule;
        extern SubCategory syscall_sceUtility_0F3EEAAC;
        extern SubCategory syscall_sceUtilityInstallInitStart;
        extern SubCategory syscall_sceUtility_147F7C85;
        extern SubCategory syscall_sceUtility_149A7895;
        extern SubCategory syscall_sceUtilityLoadNetModule;
        extern SubCategory syscall_sceUtility_16A1A8D8;
        extern SubCategory syscall_sceUtility_16D02AF0;
        extern SubCategory syscall_sceUtility_28D35634;
        extern SubCategory syscall_sceUtility_2995D020;
        extern SubCategory syscall_sceUtilityLoadModule;
        extern SubCategory syscall_sceUtilityMsgDialogInitStart;
        extern SubCategory syscall_sceUtility_2B96173B;
        extern SubCategory syscall_sceUtilityGetSystemParamString;
        extern SubCategory syscall_sceUtility_3AAD51DC;
        extern SubCategory syscall_sceNetplayDialogInitStart;
        extern SubCategory syscall_sceUtilityOskShutdownStart;
        extern SubCategory syscall_sceNetplayDialogUpdate;
        extern SubCategory syscall_sceUtilitySetSystemParamString;
        extern SubCategory syscall_sceUtility_42071A83;
        extern SubCategory syscall_sceUtilityGetNetParam;
        extern SubCategory syscall_sceUtilitySetSystemParamInt;
        extern SubCategory syscall_sceUtilityMsgDialogAbort;
        extern SubCategory syscall_sceUtility_4A833BA4;
        extern SubCategory syscall_sceUtility_4B0A8FE5;
        extern SubCategory syscall_sceUtilityOskUpdate;
        extern SubCategory syscall_sceUtilityNetconfInitStart;
        extern SubCategory syscall_sceUtilityGetNetParamLatestID;
        extern SubCategory syscall_sceUtilitySavedataInitStart;
        extern SubCategory syscall_sceUtility_54A5C62F;
        extern SubCategory syscall_sceUtilityCheckNetParam;
        extern SubCategory syscall_sceUtilityInstallShutdownStart;
        extern SubCategory syscall_sceUtilityNetconfGetStatus;
        extern SubCategory syscall_sceUtilityUnloadNetModule;
        extern SubCategory syscall_sceUtilityMsgDialogShutdownStart;
        extern SubCategory syscall_sceUtility_6F56F9CF;
        extern SubCategory syscall_sceUtility_70267ADF;
        extern SubCategory syscall_sceUtilityGameSharingUpdate;
        extern SubCategory syscall_sceUtility_81C44706;
        extern SubCategory syscall_sceUtility_8326AB05;
        extern SubCategory syscall_sceUtility_86A03A27;
        extern SubCategory syscall_sceUtility_86ABDB1B;
        extern SubCategory syscall_sceUtilitySavedataGetStatus;
        extern SubCategory syscall_sceUtility_88BC7406;
        extern SubCategory syscall_sceUtility_89317C8F;
        extern SubCategory syscall_sceUtilityNetconfUpdate;
        extern SubCategory syscall_sceUtility_943CBA46;
        extern SubCategory syscall_sceUtilityGameSharingGetStatus;
        extern SubCategory syscall_sceUtilityMsgDialogUpdate;
        extern SubCategory syscall_sceUtilitySavedataShutdownStart;
        extern SubCategory syscall_sceUtilityMsgDialogGetStatus;
        extern SubCategory syscall_sceUtilityInstallUpdate;
        extern SubCategory syscall_sceUtility_A084E056;
        extern SubCategory syscall_sceUtility_A50E5B30;
        extern SubCategory syscall_sceUtilityGetSystemParamInt;
        extern SubCategory syscall_sceUtility_AB083EA9;
        extern SubCategory syscall_sceUtility_B0FB7FF5;
        extern SubCategory syscall_sceUtility_B62A4061;
        extern SubCategory syscall_sceNetplayDialogGetStatus;
        extern SubCategory syscall_sceUtility_B8592D5F;
        extern SubCategory syscall_sceNetplayDialogShutdownStart;
        extern SubCategory syscall_sceUtilityHtmlViewerGetStatus;
        extern SubCategory syscall_sceUtilityInstallGetStatus;
        extern SubCategory syscall_sceUtilityGameSharingInitStart;
        extern SubCategory syscall_sceUtilityLoadAvModule;
        extern SubCategory syscall_sceUtilityHtmlViewerInitStart;
        extern SubCategory syscall_sceUtility_D17A0573;
        extern SubCategory syscall_sceUtilitySavedataUpdate;
        extern SubCategory syscall_sceUtility_D81957B7;
        extern SubCategory syscall_sceUtility_D852CDCE;
        extern SubCategory syscall_sceUtility_DA97F1AA;
        extern SubCategory syscall_sceUtility_DDE5389D;
        extern SubCategory syscall_sceUtility_E19C97D6;
        extern SubCategory syscall_sceUtilityUnloadModule;
        extern SubCategory syscall_sceUtility_E7B778D8;
        extern SubCategory syscall_sceUtility_ECE1D3E5;
        extern SubCategory syscall_sceUtility_ED0FAD38;
        extern SubCategory syscall_sceUtility_EF3582B2;
        extern SubCategory syscall_sceUtilityGameSharingShutdownStart;
        extern SubCategory syscall_sceUtilityOskGetStatus;
        extern SubCategory syscall_sceUtility_F3FBC572;
        extern SubCategory syscall_sceUtilityHtmlViewerShutdownStart;
        extern SubCategory syscall_sceUtilityOskInitStart;
        extern SubCategory syscall_sceUtilityUnloadUsbModule;
        extern SubCategory syscall_sceUtilityUnloadAvModule;
        extern SubCategory syscall_sceUtilityNetconfShutdownStart;
        extern SubCategory syscall_sceUtility_F9E0008C;
        extern SubCategory syscall_sceUtility_private;
        extern SubCategory syscall_sceUtility_private_03043DAF;
        extern SubCategory syscall_sceUtility_private_0CF833E5;
        extern SubCategory syscall_sceUtility_private_107CA63E;
        extern SubCategory syscall_sceUtility_private_11236637;
        extern SubCategory syscall_sceUtility_private_1FD567D4;
        extern SubCategory syscall_sceUtility_private_23FE0D1B;
        extern SubCategory syscall_sceUtility_private_284DBC23;
        extern SubCategory syscall_sceUtility_private_2A9524EF;
        extern SubCategory syscall_sceUtility_private_2F265D64;
        extern SubCategory syscall_sceUtility_private_34892525;
        extern SubCategory syscall_sceUtility_private_3B76A6D0;
        extern SubCategory syscall_sceUtility_private_3EBDB7F6;
        extern SubCategory syscall_sceUtility_private_47FA0F9B;
        extern SubCategory syscall_sceUtility_private_4B069019;
        extern SubCategory syscall_sceUtility_private_5B3C096F;
        extern SubCategory syscall_sceUtility_private_6513E388;
        extern SubCategory syscall_sceUtility_private_6B0356F6;
        extern SubCategory syscall_sceUtility_private_6D2D8A41;
        extern SubCategory syscall_sceUtility_private_6D73DD7C;
        extern SubCategory syscall_sceUtility_private_7139732A;
        extern SubCategory syscall_sceUtility_private_84A1E70F;
        extern SubCategory syscall_sceUtility_private_84FEFEAD;
        extern SubCategory syscall_sceUtility_private_8A80D4EE;
        extern SubCategory syscall_sceUtility_private_8E7B9318;
        extern SubCategory syscall_sceUtility_private_9AEFABC9;
        extern SubCategory syscall_sceUtility_private_9E8CD6BC;
        extern SubCategory syscall_sceUtility_private_A1A4A4D3;
        extern SubCategory syscall_sceUtility_private_A1DF25E8;
        extern SubCategory syscall_sceUtility_private_A5D7DC3E;
        extern SubCategory syscall_sceUtility_private_ACAFCBA3;
        extern SubCategory syscall_sceUtility_private_ACDC84F3;
        extern SubCategory syscall_sceUtility_private_AEADFF11;
        extern SubCategory syscall_sceUtility_private_AFC70B22;
        extern SubCategory syscall_sceUtility_private_B06FE2AB;
        extern SubCategory syscall_sceUtility_private_B618DCC7;
        extern SubCategory syscall_sceUtility_private_BF218ECC;
        extern SubCategory syscall_sceUtility_private_C5F825B6;
        extern SubCategory syscall_sceUtility_private_C652A9B0;
        extern SubCategory syscall_sceUtility_private_CF9DB393;
        extern SubCategory syscall_sceUtility_private_D6F31E47;
        extern SubCategory syscall_sceUtility_private_DCCC4CE2;
        extern SubCategory syscall_sceUtility_private_E16F76D4;
        extern SubCategory syscall_sceUtility_private_EAABCB99;
        extern SubCategory syscall_sceUtility_private_EF6B75B3;
        extern SubCategory syscall_sceUtility_private_FBCC79F8;
        extern SubCategory syscall_sceUtility_private_FC6A5184;
        extern SubCategory syscall_sceUtility_netparam_internal;
        extern SubCategory syscall_sceUtility_netparam_internal_0BA36F3F;
        extern SubCategory syscall_sceUtility_netparam_internal_0E244DD7;
        extern SubCategory syscall_sceUtility_netparam_internal_4CBB0CA0;
        extern SubCategory syscall_sceUtility_netparam_internal_BEE92A0A;
        extern SubCategory syscall_sceUtility_netparam_internal_F161E17A;
        extern SubCategory syscall_sceUtility_netparam_internal_F547B8FC;
        extern SubCategory syscall_sceUtility_netparam_internal_FD539533;
    }
}

/////////////////// Module : sceUtility_Driver (utility.prx) ///////////////////
///
/// ///////////////////////////// Library : sceUtility /////////////////////////////
/// ///
    extern "C" bool __cdecl sceUtility$Init();
    extern "C" bool __cdecl sceUtility$Fini();
    extern "C" void __cdecl sceUtility_0251B134(Allegrex::Context &); // sceUtility_0251B134
    extern "C" void __cdecl sceUtility_05AFB9E4(Allegrex::Context &); // sceUtilityHtmlViewerUpdate
    extern "C" void __cdecl sceUtility_06A48659(Allegrex::Context &); // sceUtility_06A48659
    extern "C" void __cdecl sceUtility_0D5BC6D2(Allegrex::Context &); // sceUtilityLoadUsbModule
    extern "C" void __cdecl sceUtility_0F3EEAAC(Allegrex::Context &); // sceUtility_0F3EEAAC
    extern "C" void __cdecl sceUtility_1281DA8E(Allegrex::Context &); // sceUtilityInstallInitStart
    extern "C" void __cdecl sceUtility_147F7C85(Allegrex::Context &); // sceUtility_147F7C85
    extern "C" void __cdecl sceUtility_149A7895(Allegrex::Context &); // sceUtility_149A7895
    extern "C" void __cdecl sceUtility_1579A159(Allegrex::Context &); // sceUtilityLoadNetModule
    extern "C" void __cdecl sceUtility_16A1A8D8(Allegrex::Context &); // sceUtility_16A1A8D8
    extern "C" void __cdecl sceUtility_16D02AF0(Allegrex::Context &); // sceUtility_16D02AF0
    extern "C" void __cdecl sceUtility_28D35634(Allegrex::Context &); // sceUtility_28D35634
    extern "C" void __cdecl sceUtility_2995D020(Allegrex::Context &); // sceUtility_2995D020
    extern "C" void __cdecl sceUtility_2A2B3DE0(Allegrex::Context &); // sceUtilityLoadModule
    extern "C" void __cdecl sceUtility_2AD8E239(Allegrex::Context &); // sceUtilityMsgDialogInitStart
    extern "C" void __cdecl sceUtility_2B96173B(Allegrex::Context &); // sceUtility_2B96173B
    extern "C" void __cdecl sceUtility_34B78343(Allegrex::Context &); // sceUtilityGetSystemParamString
    extern "C" void __cdecl sceUtility_3AAD51DC(Allegrex::Context &); // sceUtility_3AAD51DC
    extern "C" void __cdecl sceUtility_3AD50AE7(Allegrex::Context &); // sceNetplayDialogInitStart
    extern "C" void __cdecl sceUtility_3DFAEBA9(Allegrex::Context &); // sceUtilityOskShutdownStart
    extern "C" void __cdecl sceUtility_417BED54(Allegrex::Context &); // sceNetplayDialogUpdate
    extern "C" void __cdecl sceUtility_41E30674(Allegrex::Context &); // sceUtilitySetSystemParamString
    extern "C" void __cdecl sceUtility_42071A83(Allegrex::Context &); // sceUtility_42071A83
    extern "C" void __cdecl sceUtility_434D4B3A(Allegrex::Context &); // sceUtilityGetNetParam
    extern "C" void __cdecl sceUtility_45C18506(Allegrex::Context &); // sceUtilitySetSystemParamInt
    extern "C" void __cdecl sceUtility_4928BD96(Allegrex::Context &); // sceUtilityMsgDialogAbort
    extern "C" void __cdecl sceUtility_4A833BA4(Allegrex::Context &); // sceUtility_4A833BA4
    extern "C" void __cdecl sceUtility_4B0A8FE5(Allegrex::Context &); // sceUtility_4B0A8FE5
    extern "C" void __cdecl sceUtility_4B85C861(Allegrex::Context &); // sceUtilityOskUpdate
    extern "C" void __cdecl sceUtility_4DB1E739(Allegrex::Context &); // sceUtilityNetconfInitStart
    extern "C" void __cdecl sceUtility_4FED24D8(Allegrex::Context &); // sceUtilityGetNetParamLatestID
    extern "C" void __cdecl sceUtility_50C4CD57(Allegrex::Context &); // sceUtilitySavedataInitStart
    extern "C" void __cdecl sceUtility_54A5C62F(Allegrex::Context &); // sceUtility_54A5C62F
    extern "C" void __cdecl sceUtility_5EEE6548(Allegrex::Context &); // sceUtilityCheckNetParam
    extern "C" void __cdecl sceUtility_5EF1C24A(Allegrex::Context &); // sceUtilityInstallShutdownStart
    extern "C" void __cdecl sceUtility_6332AA39(Allegrex::Context &); // sceUtilityNetconfGetStatus
    extern "C" void __cdecl sceUtility_64D50C56(Allegrex::Context &); // sceUtilityUnloadNetModule
    extern "C" void __cdecl sceUtility_67AF3428(Allegrex::Context &); // sceUtilityMsgDialogShutdownStart
    extern "C" void __cdecl sceUtility_6F56F9CF(Allegrex::Context &); // sceUtility_6F56F9CF
    extern "C" void __cdecl sceUtility_70267ADF(Allegrex::Context &); // sceUtility_70267ADF
    extern "C" void __cdecl sceUtility_7853182D(Allegrex::Context &); // sceUtilityGameSharingUpdate
    extern "C" void __cdecl sceUtility_81C44706(Allegrex::Context &); // sceUtility_81C44706
    extern "C" void __cdecl sceUtility_8326AB05(Allegrex::Context &); // sceUtility_8326AB05
    extern "C" void __cdecl sceUtility_86A03A27(Allegrex::Context &); // sceUtility_86A03A27
    extern "C" void __cdecl sceUtility_86ABDB1B(Allegrex::Context &); // sceUtility_86ABDB1B
    extern "C" void __cdecl sceUtility_8874DBE0(Allegrex::Context &); // sceUtilitySavedataGetStatus
    extern "C" void __cdecl sceUtility_88BC7406(Allegrex::Context &); // sceUtility_88BC7406
    extern "C" void __cdecl sceUtility_89317C8F(Allegrex::Context &); // sceUtility_89317C8F
    extern "C" void __cdecl sceUtility_91E70E35(Allegrex::Context &); // sceUtilityNetconfUpdate
    extern "C" void __cdecl sceUtility_943CBA46(Allegrex::Context &); // sceUtility_943CBA46
    extern "C" void __cdecl sceUtility_946963F3(Allegrex::Context &); // sceUtilityGameSharingGetStatus
    extern "C" void __cdecl sceUtility_95FC253B(Allegrex::Context &); // sceUtilityMsgDialogUpdate
    extern "C" void __cdecl sceUtility_9790B33C(Allegrex::Context &); // sceUtilitySavedataShutdownStart
    extern "C" void __cdecl sceUtility_9A1C91D7(Allegrex::Context &); // sceUtilityMsgDialogGetStatus
    extern "C" void __cdecl sceUtility_A03D29BA(Allegrex::Context &); // sceUtilityInstallUpdate
    extern "C" void __cdecl sceUtility_A084E056(Allegrex::Context &); // sceUtility_A084E056
    extern "C" void __cdecl sceUtility_A50E5B30(Allegrex::Context &); // sceUtility_A50E5B30
    extern "C" void __cdecl sceUtility_A5DA2406(Allegrex::Context &); // sceUtilityGetSystemParamInt
    extern "C" void __cdecl sceUtility_AB083EA9(Allegrex::Context &); // sceUtility_AB083EA9
    extern "C" void __cdecl sceUtility_B0FB7FF5(Allegrex::Context &); // sceUtility_B0FB7FF5
    extern "C" void __cdecl sceUtility_B62A4061(Allegrex::Context &); // sceUtility_B62A4061
    extern "C" void __cdecl sceUtility_B6CEE597(Allegrex::Context &); // sceNetplayDialogGetStatus
    extern "C" void __cdecl sceUtility_B8592D5F(Allegrex::Context &); // sceUtility_B8592D5F
    extern "C" void __cdecl sceUtility_BC6B6296(Allegrex::Context &); // sceNetplayDialogShutdownStart
    extern "C" void __cdecl sceUtility_BDA7D894(Allegrex::Context &); // sceUtilityHtmlViewerGetStatus
    extern "C" void __cdecl sceUtility_C4700FA3(Allegrex::Context &); // sceUtilityInstallGetStatus
    extern "C" void __cdecl sceUtility_C492F751(Allegrex::Context &); // sceUtilityGameSharingInitStart
    extern "C" void __cdecl sceUtility_C629AF26(Allegrex::Context &); // sceUtilityLoadAvModule
    extern "C" void __cdecl sceUtility_CDC3AA41(Allegrex::Context &); // sceUtilityHtmlViewerInitStart
    extern "C" void __cdecl sceUtility_D17A0573(Allegrex::Context &); // sceUtility_D17A0573
    extern "C" void __cdecl sceUtility_D4B95FFB(Allegrex::Context &); // sceUtilitySavedataUpdate
    extern "C" void __cdecl sceUtility_D81957B7(Allegrex::Context &); // sceUtility_D81957B7
    extern "C" void __cdecl sceUtility_D852CDCE(Allegrex::Context &); // sceUtility_D852CDCE
    extern "C" void __cdecl sceUtility_DA97F1AA(Allegrex::Context &); // sceUtility_DA97F1AA
    extern "C" void __cdecl sceUtility_DDE5389D(Allegrex::Context &); // sceUtility_DDE5389D
    extern "C" void __cdecl sceUtility_E19C97D6(Allegrex::Context &); // sceUtility_E19C97D6
    extern "C" void __cdecl sceUtility_E49BFE92(Allegrex::Context &); // sceUtilityUnloadModule
    extern "C" void __cdecl sceUtility_E7B778D8(Allegrex::Context &); // sceUtility_E7B778D8
    extern "C" void __cdecl sceUtility_ECE1D3E5(Allegrex::Context &); // sceUtility_ECE1D3E5
    extern "C" void __cdecl sceUtility_ED0FAD38(Allegrex::Context &); // sceUtility_ED0FAD38
    extern "C" void __cdecl sceUtility_EF3582B2(Allegrex::Context &); // sceUtility_EF3582B2
    extern "C" void __cdecl sceUtility_EFC6F80F(Allegrex::Context &); // sceUtilityGameSharingShutdownStart
    extern "C" void __cdecl sceUtility_F3F76017(Allegrex::Context &); // sceUtilityOskGetStatus
    extern "C" void __cdecl sceUtility_F3FBC572(Allegrex::Context &); // sceUtility_F3FBC572
    extern "C" void __cdecl sceUtility_F5CE1134(Allegrex::Context &); // sceUtilityHtmlViewerShutdownStart
    extern "C" void __cdecl sceUtility_F6269B82(Allegrex::Context &); // sceUtilityOskInitStart
    extern "C" void __cdecl sceUtility_F64910F0(Allegrex::Context &); // sceUtilityUnloadUsbModule
    extern "C" void __cdecl sceUtility_F7D8D092(Allegrex::Context &); // sceUtilityUnloadAvModule
    extern "C" void __cdecl sceUtility_F88155F6(Allegrex::Context &); // sceUtilityNetconfShutdownStart
    extern "C" void __cdecl sceUtility_F9E0008C(Allegrex::Context &); // sceUtility_F9E0008C
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// ///////////////////////// Library : sceUtility_private /////////////////////////
/// ///
    extern "C" bool __cdecl sceUtility_private$Init();
    extern "C" bool __cdecl sceUtility_private$Fini();
    extern "C" void __cdecl sceUtility_private_03043DAF(Allegrex::Context &); // sceUtility_private_03043DAF
    extern "C" void __cdecl sceUtility_private_0CF833E5(Allegrex::Context &); // sceUtility_private_0CF833E5
    extern "C" void __cdecl sceUtility_private_107CA63E(Allegrex::Context &); // sceUtility_private_107CA63E
    extern "C" void __cdecl sceUtility_private_11236637(Allegrex::Context &); // sceUtility_private_11236637
    extern "C" void __cdecl sceUtility_private_1FD567D4(Allegrex::Context &); // sceUtility_private_1FD567D4
    extern "C" void __cdecl sceUtility_private_23FE0D1B(Allegrex::Context &); // sceUtility_private_23FE0D1B
    extern "C" void __cdecl sceUtility_private_284DBC23(Allegrex::Context &); // sceUtility_private_284DBC23
    extern "C" void __cdecl sceUtility_private_2A9524EF(Allegrex::Context &); // sceUtility_private_2A9524EF
    extern "C" void __cdecl sceUtility_private_2F265D64(Allegrex::Context &); // sceUtility_private_2F265D64
    extern "C" void __cdecl sceUtility_private_34892525(Allegrex::Context &); // sceUtility_private_34892525
    extern "C" void __cdecl sceUtility_private_3B76A6D0(Allegrex::Context &); // sceUtility_private_3B76A6D0
    extern "C" void __cdecl sceUtility_private_3EBDB7F6(Allegrex::Context &); // sceUtility_private_3EBDB7F6
    extern "C" void __cdecl sceUtility_private_47FA0F9B(Allegrex::Context &); // sceUtility_private_47FA0F9B
    extern "C" void __cdecl sceUtility_private_4B069019(Allegrex::Context &); // sceUtility_private_4B069019
    extern "C" void __cdecl sceUtility_private_5B3C096F(Allegrex::Context &); // sceUtility_private_5B3C096F
    extern "C" void __cdecl sceUtility_private_6513E388(Allegrex::Context &); // sceUtility_private_6513E388
    extern "C" void __cdecl sceUtility_private_6B0356F6(Allegrex::Context &); // sceUtility_private_6B0356F6
    extern "C" void __cdecl sceUtility_private_6D2D8A41(Allegrex::Context &); // sceUtility_private_6D2D8A41
    extern "C" void __cdecl sceUtility_private_6D73DD7C(Allegrex::Context &); // sceUtility_private_6D73DD7C
    extern "C" void __cdecl sceUtility_private_7139732A(Allegrex::Context &); // sceUtility_private_7139732A
    extern "C" void __cdecl sceUtility_private_84A1E70F(Allegrex::Context &); // sceUtility_private_84A1E70F
    extern "C" void __cdecl sceUtility_private_84FEFEAD(Allegrex::Context &); // sceUtility_private_84FEFEAD
    extern "C" void __cdecl sceUtility_private_8A80D4EE(Allegrex::Context &); // sceUtility_private_8A80D4EE
    extern "C" void __cdecl sceUtility_private_8E7B9318(Allegrex::Context &); // sceUtility_private_8E7B9318
    extern "C" void __cdecl sceUtility_private_9AEFABC9(Allegrex::Context &); // sceUtility_private_9AEFABC9
    extern "C" void __cdecl sceUtility_private_9E8CD6BC(Allegrex::Context &); // sceUtility_private_9E8CD6BC
    extern "C" void __cdecl sceUtility_private_A1A4A4D3(Allegrex::Context &); // sceUtility_private_A1A4A4D3
    extern "C" void __cdecl sceUtility_private_A1DF25E8(Allegrex::Context &); // sceUtility_private_A1DF25E8
    extern "C" void __cdecl sceUtility_private_A5D7DC3E(Allegrex::Context &); // sceUtility_private_A5D7DC3E
    extern "C" void __cdecl sceUtility_private_ACAFCBA3(Allegrex::Context &); // sceUtility_private_ACAFCBA3
    extern "C" void __cdecl sceUtility_private_ACDC84F3(Allegrex::Context &); // sceUtility_private_ACDC84F3
    extern "C" void __cdecl sceUtility_private_AEADFF11(Allegrex::Context &); // sceUtility_private_AEADFF11
    extern "C" void __cdecl sceUtility_private_AFC70B22(Allegrex::Context &); // sceUtility_private_AFC70B22
    extern "C" void __cdecl sceUtility_private_B06FE2AB(Allegrex::Context &); // sceUtility_private_B06FE2AB
    extern "C" void __cdecl sceUtility_private_B618DCC7(Allegrex::Context &); // sceUtility_private_B618DCC7
    extern "C" void __cdecl sceUtility_private_BF218ECC(Allegrex::Context &); // sceUtility_private_BF218ECC
    extern "C" void __cdecl sceUtility_private_C5F825B6(Allegrex::Context &); // sceUtility_private_C5F825B6
    extern "C" void __cdecl sceUtility_private_C652A9B0(Allegrex::Context &); // sceUtility_private_C652A9B0
    extern "C" void __cdecl sceUtility_private_CF9DB393(Allegrex::Context &); // sceUtility_private_CF9DB393
    extern "C" void __cdecl sceUtility_private_D6F31E47(Allegrex::Context &); // sceUtility_private_D6F31E47
    extern "C" void __cdecl sceUtility_private_DCCC4CE2(Allegrex::Context &); // sceUtility_private_DCCC4CE2
    extern "C" void __cdecl sceUtility_private_E16F76D4(Allegrex::Context &); // sceUtility_private_E16F76D4
    extern "C" void __cdecl sceUtility_private_EAABCB99(Allegrex::Context &); // sceUtility_private_EAABCB99
    extern "C" void __cdecl sceUtility_private_EF6B75B3(Allegrex::Context &); // sceUtility_private_EF6B75B3
    extern "C" void __cdecl sceUtility_private_FBCC79F8(Allegrex::Context &); // sceUtility_private_FBCC79F8
    extern "C" void __cdecl sceUtility_private_FC6A5184(Allegrex::Context &); // sceUtility_private_FC6A5184
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// //////////////////// Library : sceUtility_netparam_internal ////////////////////
/// ///
    extern "C" bool __cdecl sceUtility_netparam_internal$Init();
    extern "C" bool __cdecl sceUtility_netparam_internal$Fini();
    extern "C" void __cdecl sceUtility_netparam_internal_0BA36F3F(Allegrex::Context &); // sceUtility_netparam_internal_0BA36F3F
    extern "C" void __cdecl sceUtility_netparam_internal_0E244DD7(Allegrex::Context &); // sceUtility_netparam_internal_0E244DD7
    extern "C" void __cdecl sceUtility_netparam_internal_4CBB0CA0(Allegrex::Context &); // sceUtility_netparam_internal_4CBB0CA0
    extern "C" void __cdecl sceUtility_netparam_internal_BEE92A0A(Allegrex::Context &); // sceUtility_netparam_internal_BEE92A0A
    extern "C" void __cdecl sceUtility_netparam_internal_F161E17A(Allegrex::Context &); // sceUtility_netparam_internal_F161E17A
    extern "C" void __cdecl sceUtility_netparam_internal_F547B8FC(Allegrex::Context &); // sceUtility_netparam_internal_F547B8FC
    extern "C" void __cdecl sceUtility_netparam_internal_FD539533(Allegrex::Context &); // sceUtility_netparam_internal_FD539533
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_mesg_led_prx;
        extern SubCategory syscall_sceResmgr;
        extern SubCategory syscall_sceResmgr_9DC14891;
        extern SubCategory syscall_scePauth;
        extern SubCategory syscall_scePauth_F7AA47F6;
    }
}

////////////////////// Module : sceMesgLed (mesg_led.prx) //////////////////////
///
/// ////////////////////////////// Library : sceResmgr /////////////////////////////
/// ///
    extern "C" bool __cdecl sceResmgr$Init();
    extern "C" bool __cdecl sceResmgr$Fini();
    extern "C" void __cdecl sceResmgr_9DC14891(Allegrex::Context &); // sceResmgr_9DC14891
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// ////////////////////////////// Library : scePauth //////////////////////////////
/// ///
    extern "C" bool __cdecl scePauth$Init();
    extern "C" bool __cdecl scePauth$Fini();
    extern "C" void __cdecl scePauth_F7AA47F6(Allegrex::Context &); // scePauth_F7AA47F6
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_impose_prx;
        extern SubCategory syscall_sceImpose;
        extern SubCategory syscall_sceImposeGetHomePopup;
        extern SubCategory syscall_sceImposeGetLanguageMode;
        extern SubCategory syscall_sceImposeSetLanguageMode;
        extern SubCategory syscall_sceImposeHomeButton;
        extern SubCategory syscall_sceImposeSetHomePopup;
        extern SubCategory syscall_sceImposeSetUMDPopup;
        extern SubCategory syscall_sceImposeGetBatteryIconStatus;
        extern SubCategory syscall_sceImposeGetBacklightOffTime;
        extern SubCategory syscall_sceImposeSetBacklightOffTime;
        extern SubCategory syscall_sceImpose_9BA61B49;
        extern SubCategory syscall_sceImpose_A9884B00;
        extern SubCategory syscall_sceImpose_BB3F5DEC;
        extern SubCategory syscall_sceImposeGetUMDPopup;
        extern SubCategory syscall_sceImpose_FCD44963;
        extern SubCategory syscall_sceImpose_FF1A2F07;
        extern SubCategory syscall_sceAudioRouting;
        extern SubCategory syscall_sceAudioRoutingGetVolumeMode;
        extern SubCategory syscall_sceAudioRoutingSetMode;
        extern SubCategory syscall_sceAudioRoutingGetMode;
        extern SubCategory syscall_sceAudioRoutingSetVolumeMode;
    }
}

//////////////////// Module : sceImpose_Driver (impose.prx) ////////////////////
///
/// ////////////////////////////// Library : sceImpose /////////////////////////////
/// ///
    extern "C" bool __cdecl sceImpose$Init();
    extern "C" bool __cdecl sceImpose$Fini();
    extern "C" void __cdecl sceImpose_0F341BE4(Allegrex::Context &); // sceImposeGetHomePopup
    extern "C" void __cdecl sceImpose_24FD7BCF(Allegrex::Context &); // sceImposeGetLanguageMode
    extern "C" void __cdecl sceImpose_36AA6E91(Allegrex::Context &); // sceImposeSetLanguageMode
    extern "C" void __cdecl sceImpose_381BD9E7(Allegrex::Context &); // sceImposeHomeButton
    extern "C" void __cdecl sceImpose_5595A71A(Allegrex::Context &); // sceImposeSetHomePopup
    extern "C" void __cdecl sceImpose_72189C48(Allegrex::Context &); // sceImposeSetUMDPopup
    extern "C" void __cdecl sceImpose_8C943191(Allegrex::Context &); // sceImposeGetBatteryIconStatus
    extern "C" void __cdecl sceImpose_8F6E3518(Allegrex::Context &); // sceImposeGetBacklightOffTime
    extern "C" void __cdecl sceImpose_967F6D4A(Allegrex::Context &); // sceImposeSetBacklightOffTime
    extern "C" void __cdecl sceImpose_9BA61B49(Allegrex::Context &); // sceImpose_9BA61B49
    extern "C" void __cdecl sceImpose_A9884B00(Allegrex::Context &); // sceImpose_A9884B00
    extern "C" void __cdecl sceImpose_BB3F5DEC(Allegrex::Context &); // sceImpose_BB3F5DEC
    extern "C" void __cdecl sceImpose_E0887BC8(Allegrex::Context &); // sceImposeGetUMDPopup
    extern "C" void __cdecl sceImpose_FCD44963(Allegrex::Context &); // sceImpose_FCD44963
    extern "C" void __cdecl sceImpose_FF1A2F07(Allegrex::Context &); // sceImpose_FF1A2F07
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// /////////////////////////// Library : sceAudioRouting //////////////////////////
/// ///
    extern "C" bool __cdecl sceAudioRouting$Init();
    extern "C" bool __cdecl sceAudioRouting$Fini();
    extern "C" void __cdecl sceAudioRouting_28235C56(Allegrex::Context &); // sceAudioRoutingGetVolumeMode
    extern "C" void __cdecl sceAudioRouting_36FD8AA9(Allegrex::Context &); // sceAudioRoutingSetMode
    extern "C" void __cdecl sceAudioRouting_39240E7D(Allegrex::Context &); // sceAudioRoutingGetMode
    extern "C" void __cdecl sceAudioRouting_BB548475(Allegrex::Context &); // sceAudioRoutingSetVolumeMode
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_usersystemlib_prx;
        extern SubCategory syscall_Kernel_Library;
        extern SubCategory syscall_sceKernelCpuSuspendIntr;
        extern SubCategory syscall_sceKernelUnlockLwMutex;
        extern SubCategory syscall_sceKernelLockLwMutexCB;
        extern SubCategory syscall_sceKernelCpuResumeIntrWithSync;
        extern SubCategory syscall_sceKernelIsCpuIntrSuspended;
        extern SubCategory syscall_sceKernelCpuResumeIntr;
        extern SubCategory syscall_sceKernelIsCpuIntrEnable;
        extern SubCategory syscall_sceKernelLockLwMutex;
        extern SubCategory syscall_sceKernelReferLwMutexStatus;
        extern SubCategory syscall_sceKernelTryLockLwMutex;
    }
}

///////////////// Module : sceKernelLibrary (usersystemlib.prx) ////////////////
///
/// /////////////////////////// Library : Kernel_Library ///////////////////////////
/// ///
    extern "C" bool __cdecl Kernel_Library$Init();
    extern "C" bool __cdecl Kernel_Library$Fini();
    extern "C" void __cdecl Kernel_Library_092968F4(Allegrex::Context &); // sceKernelCpuSuspendIntr
    extern "C" void __cdecl Kernel_Library_15B6446B(Allegrex::Context &); // sceKernelUnlockLwMutex
    extern "C" void __cdecl Kernel_Library_1FC64E09(Allegrex::Context &); // sceKernelLockLwMutexCB
    extern "C" void __cdecl Kernel_Library_3B84732D(Allegrex::Context &); // sceKernelCpuResumeIntrWithSync
    extern "C" void __cdecl Kernel_Library_47A0B729(Allegrex::Context &); // sceKernelIsCpuIntrSuspended
    extern "C" void __cdecl Kernel_Library_5F10D406(Allegrex::Context &); // sceKernelCpuResumeIntr
    extern "C" void __cdecl Kernel_Library_B55249D2(Allegrex::Context &); // sceKernelIsCpuIntrEnable
    extern "C" void __cdecl Kernel_Library_BEA46419(Allegrex::Context &); // sceKernelLockLwMutex
    extern "C" void __cdecl Kernel_Library_C1734599(Allegrex::Context &); // sceKernelReferLwMutexStatus
    extern "C" void __cdecl Kernel_Library_DC692EE3(Allegrex::Context &); // sceKernelTryLockLwMutex
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_sc_sascore_prx;
        extern SubCategory syscall_sceSasCore;
        extern SubCategory syscall___sceSasInit;
        extern SubCategory syscall___sceSasCore;
        extern SubCategory syscall___sceSasCoreWithMix;
        extern SubCategory syscall___sceSasSetKeyOn;
        extern SubCategory syscall___sceSasSetKeyOff;
        extern SubCategory syscall___sceSasSetPause;
        extern SubCategory syscall___sceSasGetPauseFlag;
        extern SubCategory syscall___sceSasSetVolume;
        extern SubCategory syscall___sceSasSetPitch;
        extern SubCategory syscall___sceSasSetVoice;
        extern SubCategory syscall___sceSasSetNoise;
        extern SubCategory syscall___sceSasSetSteepWave;
        extern SubCategory syscall___sceSasSetTrianglarWave;
        extern SubCategory syscall___sceSasSetVoicePCM;
        extern SubCategory syscall___sceSasSetADSR;
        extern SubCategory syscall___sceSasSetADSRmode;
        extern SubCategory syscall___sceSasSetSL;
        extern SubCategory syscall___sceSasSetSimpleADSR;
        extern SubCategory syscall___sceSasGetEndFlag;
        extern SubCategory syscall___sceSasGetEnvelopeHeight;
        extern SubCategory syscall___sceSasGetAllEnvelopeHeights;
        extern SubCategory syscall___sceSasSetGrain;
        extern SubCategory syscall___sceSasGetGrain;
        extern SubCategory syscall___sceSasSetOutputmode;
        extern SubCategory syscall___sceSasGetOutputmode;
        extern SubCategory syscall___sceSasRevType;
        extern SubCategory syscall___sceSasRevParam;
        extern SubCategory syscall___sceSasRevEVOL;
        extern SubCategory syscall___sceSasRevVON;
        extern SubCategory syscall___sceSasSetVoiceATRAC3;
        extern SubCategory syscall___sceSasConcatenateATRAC3;
        extern SubCategory syscall___sceSasUnsetATRAC3;
        extern SubCategory syscall_sceP3da;
        extern SubCategory syscall_sceP3daBridgeCore;
        extern SubCategory syscall_sceP3daBridgeInit;
        extern SubCategory syscall_sceP3daBridgeExit;
    }
}

///////////////////// Module : sceSAScore (sc_sascore.prx) /////////////////////
///
/// ///////////////////////////// Library : sceSasCore /////////////////////////////
/// ///
    extern "C" bool __cdecl sceSasCore$Init();
    extern "C" bool __cdecl sceSasCore$Fini();
    extern "C" void __cdecl sceSasCore_42778A9F(Allegrex::Context &); // __sceSasInit
    extern "C" void __cdecl sceSasCore_A3589D81(Allegrex::Context &); // __sceSasCore
    extern "C" void __cdecl sceSasCore_50A14DFC(Allegrex::Context &); // __sceSasCoreWithMix
    extern "C" void __cdecl sceSasCore_76F01ACA(Allegrex::Context &); // __sceSasSetKeyOn
    extern "C" void __cdecl sceSasCore_A0CF2FA4(Allegrex::Context &); // __sceSasSetKeyOff
    extern "C" void __cdecl sceSasCore_787D04D5(Allegrex::Context &); // __sceSasSetPause
    extern "C" void __cdecl sceSasCore_2C8E6AB3(Allegrex::Context &); // __sceSasGetPauseFlag
    extern "C" void __cdecl sceSasCore_440CA7D8(Allegrex::Context &); // __sceSasSetVolume
    extern "C" void __cdecl sceSasCore_AD84D37F(Allegrex::Context &); // __sceSasSetPitch
    extern "C" void __cdecl sceSasCore_99944089(Allegrex::Context &); // __sceSasSetVoice
    extern "C" void __cdecl sceSasCore_B7660A23(Allegrex::Context &); // __sceSasSetNoise
    extern "C" void __cdecl sceSasCore_D5EBBBCD(Allegrex::Context &); // __sceSasSetSteepWave
    extern "C" void __cdecl sceSasCore_A232CBE6(Allegrex::Context &); // __sceSasSetTrianglarWave
    extern "C" void __cdecl sceSasCore_E1CD9561(Allegrex::Context &); // __sceSasSetVoicePCM
    extern "C" void __cdecl sceSasCore_019B25EB(Allegrex::Context &); // __sceSasSetADSR
    extern "C" void __cdecl sceSasCore_9EC3676A(Allegrex::Context &); // __sceSasSetADSRmode
    extern "C" void __cdecl sceSasCore_5F9529F6(Allegrex::Context &); // __sceSasSetSL
    extern "C" void __cdecl sceSasCore_CBCD4F79(Allegrex::Context &); // __sceSasSetSimpleADSR
    extern "C" void __cdecl sceSasCore_68A46B95(Allegrex::Context &); // __sceSasGetEndFlag
    extern "C" void __cdecl sceSasCore_74AE582A(Allegrex::Context &); // __sceSasGetEnvelopeHeight
    extern "C" void __cdecl sceSasCore_07F58C24(Allegrex::Context &); // __sceSasGetAllEnvelopeHeights
    extern "C" void __cdecl sceSasCore_D1E0A01E(Allegrex::Context &); // __sceSasSetGrain
    extern "C" void __cdecl sceSasCore_BD11B7C2(Allegrex::Context &); // __sceSasGetGrain
    extern "C" void __cdecl sceSasCore_E855BF76(Allegrex::Context &); // __sceSasSetOutputmode
    extern "C" void __cdecl sceSasCore_E175EF66(Allegrex::Context &); // __sceSasGetOutputmode
    extern "C" void __cdecl sceSasCore_33D4AB37(Allegrex::Context &); // __sceSasRevType
    extern "C" void __cdecl sceSasCore_267A6DD2(Allegrex::Context &); // __sceSasRevParam
    extern "C" void __cdecl sceSasCore_D5A229C9(Allegrex::Context &); // __sceSasRevEVOL
    extern "C" void __cdecl sceSasCore_F983B186(Allegrex::Context &); // __sceSasRevVON
    extern "C" void __cdecl sceSasCore_4AA9EAD6(Allegrex::Context &); // __sceSasSetVoiceATRAC3
    extern "C" void __cdecl sceSasCore_7497EA85(Allegrex::Context &); // __sceSasConcatenateATRAC3
    extern "C" void __cdecl sceSasCore_F6107F00(Allegrex::Context &); // __sceSasUnsetATRAC3
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
/// /////////////////////////////// Library : sceP3da //////////////////////////////
/// ///
    extern "C" bool __cdecl sceP3da$Init();
    extern "C" bool __cdecl sceP3da$Fini();
    extern "C" void __cdecl sceP3da_013016F3(Allegrex::Context &); // sceP3daBridgeCore
    extern "C" void __cdecl sceP3da_374500A5(Allegrex::Context &); // sceP3daBridgeInit
    extern "C" void __cdecl sceP3da_43F756A2(Allegrex::Context &); // sceP3daBridgeExit
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

namespace emu
{
    namespace log
    {
        extern SubCategory syscall_libatrac3plus_prx;
        extern SubCategory syscall_sceAtrac3plus;
        extern SubCategory syscall_sceAtracGetAtracID;
        extern SubCategory syscall_sceAtracReleaseAtracID;
        extern SubCategory syscall_sceAtracReinit;
        extern SubCategory syscall_sceAtracSetData;
        extern SubCategory syscall_sceAtracSetHalfwayBuffer;
        extern SubCategory syscall_sceAtracSetDataAndGetID;
        extern SubCategory syscall_sceAtracSetHalfwayBufferAndGetID;
        extern SubCategory syscall_sceAtracDecodeData;
        extern SubCategory syscall_sceAtracGetStreamDataInfo;
        extern SubCategory syscall_sceAtracAddStreamData;
        extern SubCategory syscall_sceAtracGetSecondBufferInfo;
        extern SubCategory syscall_sceAtracSetSecondBuffer;
        extern SubCategory syscall_sceAtracIsSecondBufferNeeded;
        extern SubCategory syscall_sceAtracGetRemainFrame;
        extern SubCategory syscall_sceAtracGetChannel;
        extern SubCategory syscall_sceAtracGetOutputChannel;
        extern SubCategory syscall_sceAtracGetMaxSample;
        extern SubCategory syscall_sceAtracGetNextSample;
        extern SubCategory syscall_sceAtracGetSoundSample;
        extern SubCategory syscall_sceAtracGetNextDecodePosition;
        extern SubCategory syscall_sceAtracGetBitrate;
        extern SubCategory syscall_sceAtracGetLoopStatus;
        extern SubCategory syscall_sceAtracSetLoopNum;
        extern SubCategory syscall_sceAtracGetBufferInfoForResetting;
        extern SubCategory syscall_sceAtracResetPlayPosition;
        extern SubCategory syscall_sceAtracGetInternalErrorInfo;
        extern SubCategory syscall_sceAtracSetAA3DataAndGetID;
        extern SubCategory syscall_sceAtracSetMOutHalfwayBuffer;
        extern SubCategory syscall_sceAtracSetAA3HalfwayBufferAndGetID;
        extern SubCategory syscall_sceAtracGetBufferInfoForReseting;
        extern SubCategory syscall_sceAtracStartEntry;
        extern SubCategory syscall_sceAtracEndEntry;
        extern SubCategory syscall_sceAtracSetMOutHalfwayBufferAndGetID;
    }
}

////////////// Module : sceATRAC3plus_Library (libatrac3plus.prx) //////////////
///
/// //////////////////////////// Library : sceAtrac3plus ///////////////////////////
/// ///
    extern "C" bool __cdecl sceAtrac3plus$Init();
    extern "C" bool __cdecl sceAtrac3plus$Fini();
    extern "C" void __cdecl sceAtrac3plus_780F88D1(Allegrex::Context &); // sceAtracGetAtracID
    extern "C" void __cdecl sceAtrac3plus_61EB33F5(Allegrex::Context &); // sceAtracReleaseAtracID
    extern "C" void __cdecl sceAtrac3plus_132F1ECA(Allegrex::Context &); // sceAtracReinit
    extern "C" void __cdecl sceAtrac3plus_0E2A73AB(Allegrex::Context &); // sceAtracSetData
    extern "C" void __cdecl sceAtrac3plus_3F6E26B5(Allegrex::Context &); // sceAtracSetHalfwayBuffer
    extern "C" void __cdecl sceAtrac3plus_7A20E7AF(Allegrex::Context &); // sceAtracSetDataAndGetID
    extern "C" void __cdecl sceAtrac3plus_0FAE370E(Allegrex::Context &); // sceAtracSetHalfwayBufferAndGetID
    extern "C" void __cdecl sceAtrac3plus_6A8C3CD5(Allegrex::Context &); // sceAtracDecodeData
    extern "C" void __cdecl sceAtrac3plus_5D268707(Allegrex::Context &); // sceAtracGetStreamDataInfo
    extern "C" void __cdecl sceAtrac3plus_7DB31251(Allegrex::Context &); // sceAtracAddStreamData
    extern "C" void __cdecl sceAtrac3plus_83E85EA0(Allegrex::Context &); // sceAtracGetSecondBufferInfo
    extern "C" void __cdecl sceAtrac3plus_83BF7AFD(Allegrex::Context &); // sceAtracSetSecondBuffer
    extern "C" void __cdecl sceAtrac3plus_ECA32A99(Allegrex::Context &); // sceAtracIsSecondBufferNeeded
    extern "C" void __cdecl sceAtrac3plus_9AE849A7(Allegrex::Context &); // sceAtracGetRemainFrame
    extern "C" void __cdecl sceAtrac3plus_31668BAA(Allegrex::Context &); // sceAtracGetChannel
    extern "C" void __cdecl sceAtrac3plus_B3B5D042(Allegrex::Context &); // sceAtracGetOutputChannel
    extern "C" void __cdecl sceAtrac3plus_D6A5F2F7(Allegrex::Context &); // sceAtracGetMaxSample
    extern "C" void __cdecl sceAtrac3plus_36FAABFB(Allegrex::Context &); // sceAtracGetNextSample
    extern "C" void __cdecl sceAtrac3plus_A2BBA8BE(Allegrex::Context &); // sceAtracGetSoundSample
    extern "C" void __cdecl sceAtrac3plus_E23E3A35(Allegrex::Context &); // sceAtracGetNextDecodePosition
    extern "C" void __cdecl sceAtrac3plus_A554A158(Allegrex::Context &); // sceAtracGetBitrate
    extern "C" void __cdecl sceAtrac3plus_FAA4F89B(Allegrex::Context &); // sceAtracGetLoopStatus
    extern "C" void __cdecl sceAtrac3plus_868120B5(Allegrex::Context &); // sceAtracSetLoopNum
    extern "C" void __cdecl sceAtrac3plus_2DD3E298(Allegrex::Context &); // sceAtracGetBufferInfoForResetting
    extern "C" void __cdecl sceAtrac3plus_644E5607(Allegrex::Context &); // sceAtracResetPlayPosition
    extern "C" void __cdecl sceAtrac3plus_E88F759B(Allegrex::Context &); // sceAtracGetInternalErrorInfo
    extern "C" void __cdecl sceAtrac3plus_5622B7C1(Allegrex::Context &); // sceAtracSetAA3DataAndGetID
    extern "C" void __cdecl sceAtrac3plus_5CF9D852(Allegrex::Context &); // sceAtracSetMOutHalfwayBuffer
    extern "C" void __cdecl sceAtrac3plus_5DD66588(Allegrex::Context &); // sceAtracSetAA3HalfwayBufferAndGetID
    extern "C" void __cdecl sceAtrac3plus_CA3CA3D2(Allegrex::Context &); // sceAtracGetBufferInfoForReseting
    extern "C" void __cdecl sceAtrac3plus_D1F59FDB(Allegrex::Context &); // sceAtracStartEntry
    extern "C" void __cdecl sceAtrac3plus_D5C28CC0(Allegrex::Context &); // sceAtracEndEntry
    extern "C" void __cdecl sceAtrac3plus_9CD7DE03(Allegrex::Context &); // sceAtracSetMOutHalfwayBufferAndGetID
/// ///
/// ////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

#endif