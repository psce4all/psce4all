//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_power_prx_scePower_h__
#define hle_power_prx_scePower_h__

namespace hle
{
    namespace scePower //@hle:library-start{scePower|scePower_Service|power.prx}
    {
        //@hle:function{0074EF9B|scePower|scePowerGetResumeCount|g|??? scePowerGetResumeCount()}
        extern int  scePowerGetResumeCount();
        //@hle:function{0442D852|scePower|scePowerRequestColdReset|g|??? scePowerRequestColdReset()}
        extern int  scePowerRequestColdReset();
        //@hle:function{04B7766E|scePower|scePowerRegisterCallback|ggg|int scePowerRegisterCallback(int slot, SceUID cbid)}
        extern int  scePowerRegisterCallback(u32 $a0, u32 $a1);
        //@hle:function{0AFD0D8B|scePower|scePowerIsBatteryExist|g|int scePowerIsBatteryExist(void)}
        extern int  scePowerIsBatteryExist();
        //@hle:function{0CD21B1F|scePower|scePowerSetPowerSwMode|g|??? scePowerSetPowerSwMode()}
        extern int  scePowerSetPowerSwMode();
        //@hle:function{165CE085|scePower|scePowerGetPowerSwMode|g|??? scePowerGetPowerSwMode()}
        extern int  scePowerGetPowerSwMode();
        //@hle:function{1E490401|scePower|scePowerIsBatteryCharging|g|int scePowerIsBatteryCharging(void)}
        extern int  scePowerIsBatteryCharging();
        //@hle:function{2085D15D|scePower|scePowerGetBatteryLifePercent|g|int scePowerGetBatteryLifePercent(void)}
        extern int  scePowerGetBatteryLifePercent();
        //@hle:function{23436A4A|scePower|scePowerGetInnerTemp|g|??? scePowerGetInnerTemp()}
        extern int  scePowerGetInnerTemp();
        //@hle:function{23C31FFE|scePower|scePowerVolatileMemLock|g|??? scePowerVolatileMemLock()}
        extern int  scePowerVolatileMemLock();
        //@hle:function{27F3292C|scePower|scePowerBatteryUpdateInfo|g|??? scePowerBatteryUpdateInfo()}
        extern int  scePowerBatteryUpdateInfo();
        //@hle:function{2875994B|scePower|scePower_2875994B|g|??? scePower_2875994B()}
        extern int  scePower_2875994B();
        //@hle:function{28E12023|scePower|scePowerGetBatteryTemp|g|int scePowerGetBatteryTemp(void)}
        extern int  scePowerGetBatteryTemp();
        //@hle:function{2B51FE2F|scePower|scePower_2B51FE2F|g|??? scePower_2B51FE2F()}
        extern int  scePower_2B51FE2F();
        //@hle:function{2B7C7CF4|scePower|scePowerRequestStandby|g|int scePowerRequestStandby(void)}
        extern int  scePowerRequestStandby();
        //@hle:function{34F9C463|scePower|scePowerGetPllClockFrequencyInt|g|??? scePowerGetPllClockFrequencyInt()}
        extern int  scePowerGetPllClockFrequencyInt();
        //@hle:function{3951AF53|scePower|scePowerWaitRequestCompletion|g|??? scePowerWaitRequestCompletion()}
        extern int  scePowerWaitRequestCompletion();
        //@hle:function{442BFBAC|scePower|scePowerGetBacklightMaximum|g|??? scePowerGetBacklightMaximum()}
        extern int  scePowerGetBacklightMaximum();
        //@hle:function{478FE6F5|scePower|scePowerGetBusClockFrequency|g|int scePowerGetBusClockFrequency(void)}
        extern int  scePowerGetBusClockFrequency();
        //@hle:function{483CE86B|scePower|scePowerGetBatteryVolt|g|int scePowerGetBatteryVolt(void)}
        extern int  scePowerGetBatteryVolt();
        //@hle:function{545A7F3C|scePower|scePower_545A7F3C|g|??? scePower_545A7F3C()}
        extern int  scePower_545A7F3C();
        //@hle:function{737486F2|scePower|scePowerSetClockFrequency|gggg|int scePowerSetClockFrequency(int cpufreq, int ramfreq, int busfreq)}
        extern int  scePowerSetClockFrequency(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{78A1A796|scePower|scePowerIsSuspendRequired|g|??? scePowerIsSuspendRequired()}
        extern int  scePowerIsSuspendRequired();
        //@hle:function{7F30B3B1|scePower|scePowerIdleTimerEnable|gg|int scePowerIdleTimerEnable(int unknown)}
        extern int  scePowerIdleTimerEnable(u32 $a0);
        //@hle:function{7FA406DD|scePower|scePowerIsRequest|g|??? scePowerIsRequest()}
        extern int  scePowerIsRequest();
        //@hle:function{843FBF43|scePower|scePowerSetCpuClockFrequency|gg|int scePowerSetCpuClockFrequency(int cpufreq)}
        extern int  scePowerSetCpuClockFrequency(u32 $a0);
        //@hle:function{862AE1A6|scePower|scePowerGetBatteryElec|g|int scePowerGetBatteryElec(void)}
        extern int  scePowerGetBatteryElec();
        //@hle:function{87440F5E|scePower|scePowerIsPowerOnline|g|int scePowerIsPowerOnline(void)}
        extern int  scePowerIsPowerOnline();
        //@hle:function{8EFB3FA2|scePower|scePowerGetBatteryLifeTime|g|int scePowerGetBatteryLifeTime(void)}
        extern int  scePowerGetBatteryLifeTime();
        //@hle:function{94F5A53F|scePower|scePowerGetBatteryRemainCapacity|g|??? scePowerGetBatteryRemainCapacity()}
        extern int  scePowerGetBatteryRemainCapacity();
        //@hle:function{972CE941|scePower|scePowerIdleTimerDisable|gg|int scePowerIdleTimerDisable(int unknown)}
        extern int  scePowerIdleTimerDisable(u32 $a0);
        //@hle:function{9BADB3EB|scePower|scePowerGetBusClockFrequencyFloat|g|float scePowerGetBusClockFrequencyFloat(void)}
        extern int  scePowerGetBusClockFrequencyFloat();
        //@hle:function{A4E93389|scePower|scePower_A4E93389|g|??? scePower_A4E93389()}
        extern int  scePower_A4E93389();
        //@hle:function{A9D22232|scePower|scePowerSetCallbackMode|g|??? scePowerSetCallbackMode()}
        extern int  scePowerSetCallbackMode();
        //@hle:function{AC32C9CC|scePower|scePowerRequestSuspend|g|int scePowerRequestSuspend(void)}
        extern int  scePowerRequestSuspend();
        //@hle:function{B1A52C83|scePower|scePowerGetCpuClockFrequencyFloat|g|float scePowerGetCpuClockFrequencyFloat(void)}
        extern int  scePowerGetCpuClockFrequencyFloat();
        //@hle:function{B3EDD801|scePower|scePowerVolatileMemUnlock|g|??? scePowerVolatileMemUnlock()}
        extern int  scePowerVolatileMemUnlock();
        //@hle:function{B4432BC8|scePower|scePowerGetBatteryChargingStatus|g|int scePowerGetBatteryChargingStatus(void)}
        extern int  scePowerGetBatteryChargingStatus();
        //@hle:function{B8D7B3FB|scePower|scePowerSetBusClockFrequency|gg|int scePowerSetBusClockFrequency(int busfreq)}
        extern int  scePowerSetBusClockFrequency(u32 $a0);
        //@hle:function{B999184C|scePower|scePowerGetLowBatteryCapacity|g|??? scePowerGetLowBatteryCapacity()}
        extern int  scePowerGetLowBatteryCapacity();
        //@hle:function{BAFA3DF0|scePower|scePowerGetCallbackMode|g|??? scePowerGetCallbackMode()}
        extern int  scePowerGetCallbackMode();
        //@hle:function{BD681969|scePower|scePowerGetBusClockFrequencyInt|g|int scePowerGetBusClockFrequencyInt(void)}
        extern int  scePowerGetBusClockFrequencyInt();
        //@hle:function{CA3D34C1|scePower|scePowerUnlock|gg|int scePowerUnlock(int unknown)}
        extern int  scePowerUnlock(u32 $a0);
        //@hle:function{CB49F5CE|scePower|scePowerGetBatteryChargeCycle|g|??? scePowerGetBatteryChargeCycle()}
        extern int  scePowerGetBatteryChargeCycle();
        //@hle:function{D3075926|scePower|scePowerIsLowBattery|g|int scePowerIsLowBattery(void)}
        extern int  scePowerIsLowBattery();
        //@hle:function{D6D016EF|scePower|scePowerLock|gg|int scePowerLock(int unknown)}
        extern int  scePowerLock(u32 $a0);
        //@hle:function{DB62C9CF|scePower|scePowerCancelRequest|g|??? scePowerCancelRequest()}
        extern int  scePowerCancelRequest();
        //@hle:function{DB9D28DD|scePower|scePowerUnregitserCallback|g|??? scePowerUnregitserCallback()}
        extern int  scePowerUnregitserCallback();
        //@hle:function{DFA8BAF8|scePower|scePowerUnregisterCallback|g|??? scePowerUnregisterCallback()}
        extern int  scePowerUnregisterCallback();
        //@hle:function{E8E4E204|scePower|scePower_E8E4E204|g|??? scePower_E8E4E204()}
        extern int  scePower_E8E4E204();
        //@hle:function{EA382A27|scePower|scePowerGetPllClockFrequencyFloat|g|??? scePowerGetPllClockFrequencyFloat()}
        extern int  scePowerGetPllClockFrequencyFloat();
        //@hle:function{EBD177D6|scePower|scePower_EBD177D6|g|??? scePower_EBD177D6()}
        extern int  scePower_EBD177D6();
        //@hle:function{EDC13FE5|scePower|scePowerGetIdleTimer|g|int scePowerGetIdleTimer(void)}
        extern int  scePowerGetIdleTimer();
        //@hle:function{EFD3C963|scePower|scePowerTick|gg|int scePowerTick(int unknown)}
        extern int  scePowerTick(u32 $a0);
        //@hle:function{FA97A599|scePower|scePowerVolatileMemTryLock|g|??? scePowerVolatileMemTryLock()}
        extern int  scePowerVolatileMemTryLock();
        //@hle:function{FD18A0FF|scePower|scePowerGetBatteryFullCapacity|g|??? scePowerGetBatteryFullCapacity()}
        extern int  scePowerGetBatteryFullCapacity();
        //@hle:function{FDB5BFE9|scePower|scePowerGetCpuClockFrequencyInt|g|int scePowerGetCpuClockFrequencyInt(void)}
        extern int  scePowerGetCpuClockFrequencyInt();
        //@hle:function{FEE03A2F|scePower|scePowerGetCpuClockFrequency|g|int scePowerGetCpuClockFrequency(void)}
        extern int  scePowerGetCpuClockFrequency();
    } //@hle:library-end{scePower|scePower_Service|power.prx}
}
#endif