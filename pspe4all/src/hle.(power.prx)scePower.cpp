//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(power.prx)scePower.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace scePower //@hle:library-start{scePower|scePower_Service|power.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{0074EF9B|scePower|scePowerGetResumeCount|g|??? scePowerGetResumeCount()}
        int  scePowerGetResumeCount()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0442D852|scePower|scePowerRequestColdReset|g|??? scePowerRequestColdReset()}
        int  scePowerRequestColdReset()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{04B7766E|scePower|scePowerRegisterCallback|ggg|int scePowerRegisterCallback(int slot, SceUID cbid)}
        int  scePowerRegisterCallback(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0AFD0D8B|scePower|scePowerIsBatteryExist|g|int scePowerIsBatteryExist(void)}
        int  scePowerIsBatteryExist()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0CD21B1F|scePower|scePowerSetPowerSwMode|g|??? scePowerSetPowerSwMode()}
        int  scePowerSetPowerSwMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{165CE085|scePower|scePowerGetPowerSwMode|g|??? scePowerGetPowerSwMode()}
        int  scePowerGetPowerSwMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1E490401|scePower|scePowerIsBatteryCharging|g|int scePowerIsBatteryCharging(void)}
        int  scePowerIsBatteryCharging()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2085D15D|scePower|scePowerGetBatteryLifePercent|g|int scePowerGetBatteryLifePercent(void)}
        int  scePowerGetBatteryLifePercent()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{23436A4A|scePower|scePowerGetInnerTemp|g|??? scePowerGetInnerTemp()}
        int  scePowerGetInnerTemp()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{23C31FFE|scePower|scePowerVolatileMemLock|g|??? scePowerVolatileMemLock()}
        int  scePowerVolatileMemLock()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{27F3292C|scePower|scePowerBatteryUpdateInfo|g|??? scePowerBatteryUpdateInfo()}
        int  scePowerBatteryUpdateInfo()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2875994B|scePower|scePower_2875994B|g|??? scePower_2875994B()}
        int  scePower_2875994B()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{28E12023|scePower|scePowerGetBatteryTemp|g|int scePowerGetBatteryTemp(void)}
        int  scePowerGetBatteryTemp()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2B51FE2F|scePower|scePower_2B51FE2F|g|??? scePower_2B51FE2F()}
        int  scePower_2B51FE2F()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2B7C7CF4|scePower|scePowerRequestStandby|g|int scePowerRequestStandby(void)}
        int  scePowerRequestStandby()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{34F9C463|scePower|scePowerGetPllClockFrequencyInt|g|??? scePowerGetPllClockFrequencyInt()}
        int  scePowerGetPllClockFrequencyInt()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3951AF53|scePower|scePowerWaitRequestCompletion|g|??? scePowerWaitRequestCompletion()}
        int  scePowerWaitRequestCompletion()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{442BFBAC|scePower|scePowerGetBacklightMaximum|g|??? scePowerGetBacklightMaximum()}
        int  scePowerGetBacklightMaximum()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{478FE6F5|scePower|scePowerGetBusClockFrequency|g|int scePowerGetBusClockFrequency(void)}
        int  scePowerGetBusClockFrequency()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{483CE86B|scePower|scePowerGetBatteryVolt|g|int scePowerGetBatteryVolt(void)}
        int  scePowerGetBatteryVolt()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{545A7F3C|scePower|scePower_545A7F3C|g|??? scePower_545A7F3C()}
        int  scePower_545A7F3C()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{737486F2|scePower|scePowerSetClockFrequency|gggg|int scePowerSetClockFrequency(int cpufreq, int ramfreq, int busfreq)}
        int  scePowerSetClockFrequency(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{78A1A796|scePower|scePowerIsSuspendRequired|g|??? scePowerIsSuspendRequired()}
        int  scePowerIsSuspendRequired()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7F30B3B1|scePower|scePowerIdleTimerEnable|gg|int scePowerIdleTimerEnable(int unknown)}
        int  scePowerIdleTimerEnable(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7FA406DD|scePower|scePowerIsRequest|g|??? scePowerIsRequest()}
        int  scePowerIsRequest()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{843FBF43|scePower|scePowerSetCpuClockFrequency|gg|int scePowerSetCpuClockFrequency(int cpufreq)}
        int  scePowerSetCpuClockFrequency(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{862AE1A6|scePower|scePowerGetBatteryElec|g|int scePowerGetBatteryElec(void)}
        int  scePowerGetBatteryElec()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{87440F5E|scePower|scePowerIsPowerOnline|g|int scePowerIsPowerOnline(void)}
        int  scePowerIsPowerOnline()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8EFB3FA2|scePower|scePowerGetBatteryLifeTime|g|int scePowerGetBatteryLifeTime(void)}
        int  scePowerGetBatteryLifeTime()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{94F5A53F|scePower|scePowerGetBatteryRemainCapacity|g|??? scePowerGetBatteryRemainCapacity()}
        int  scePowerGetBatteryRemainCapacity()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{972CE941|scePower|scePowerIdleTimerDisable|gg|int scePowerIdleTimerDisable(int unknown)}
        int  scePowerIdleTimerDisable(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9BADB3EB|scePower|scePowerGetBusClockFrequencyFloat|g|float scePowerGetBusClockFrequencyFloat(void)}
        int  scePowerGetBusClockFrequencyFloat()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A4E93389|scePower|scePower_A4E93389|g|??? scePower_A4E93389()}
        int  scePower_A4E93389()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A9D22232|scePower|scePowerSetCallbackMode|g|??? scePowerSetCallbackMode()}
        int  scePowerSetCallbackMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AC32C9CC|scePower|scePowerRequestSuspend|g|int scePowerRequestSuspend(void)}
        int  scePowerRequestSuspend()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B1A52C83|scePower|scePowerGetCpuClockFrequencyFloat|g|float scePowerGetCpuClockFrequencyFloat(void)}
        int  scePowerGetCpuClockFrequencyFloat()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B3EDD801|scePower|scePowerVolatileMemUnlock|g|??? scePowerVolatileMemUnlock()}
        int  scePowerVolatileMemUnlock()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B4432BC8|scePower|scePowerGetBatteryChargingStatus|g|int scePowerGetBatteryChargingStatus(void)}
        int  scePowerGetBatteryChargingStatus()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B8D7B3FB|scePower|scePowerSetBusClockFrequency|gg|int scePowerSetBusClockFrequency(int busfreq)}
        int  scePowerSetBusClockFrequency(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B999184C|scePower|scePowerGetLowBatteryCapacity|g|??? scePowerGetLowBatteryCapacity()}
        int  scePowerGetLowBatteryCapacity()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BAFA3DF0|scePower|scePowerGetCallbackMode|g|??? scePowerGetCallbackMode()}
        int  scePowerGetCallbackMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BD681969|scePower|scePowerGetBusClockFrequencyInt|g|int scePowerGetBusClockFrequencyInt(void)}
        int  scePowerGetBusClockFrequencyInt()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CA3D34C1|scePower|scePowerUnlock|gg|int scePowerUnlock(int unknown)}
        int  scePowerUnlock(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CB49F5CE|scePower|scePowerGetBatteryChargeCycle|g|??? scePowerGetBatteryChargeCycle()}
        int  scePowerGetBatteryChargeCycle()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D3075926|scePower|scePowerIsLowBattery|g|int scePowerIsLowBattery(void)}
        int  scePowerIsLowBattery()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D6D016EF|scePower|scePowerLock|gg|int scePowerLock(int unknown)}
        int  scePowerLock(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DB62C9CF|scePower|scePowerCancelRequest|g|??? scePowerCancelRequest()}
        int  scePowerCancelRequest()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DB9D28DD|scePower|scePowerUnregitserCallback|g|??? scePowerUnregitserCallback()}
        int  scePowerUnregitserCallback()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DFA8BAF8|scePower|scePowerUnregisterCallback|g|??? scePowerUnregisterCallback()}
        int  scePowerUnregisterCallback()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E8E4E204|scePower|scePower_E8E4E204|g|??? scePower_E8E4E204()}
        int  scePower_E8E4E204()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EA382A27|scePower|scePowerGetPllClockFrequencyFloat|g|??? scePowerGetPllClockFrequencyFloat()}
        int  scePowerGetPllClockFrequencyFloat()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EBD177D6|scePower|scePower_EBD177D6|g|??? scePower_EBD177D6()}
        int  scePower_EBD177D6()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EDC13FE5|scePower|scePowerGetIdleTimer|g|int scePowerGetIdleTimer(void)}
        int  scePowerGetIdleTimer()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{EFD3C963|scePower|scePowerTick|gg|int scePowerTick(int unknown)}
        int  scePowerTick(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FA97A599|scePower|scePowerVolatileMemTryLock|g|??? scePowerVolatileMemTryLock()}
        int  scePowerVolatileMemTryLock()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FD18A0FF|scePower|scePowerGetBatteryFullCapacity|g|??? scePowerGetBatteryFullCapacity()}
        int  scePowerGetBatteryFullCapacity()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FDB5BFE9|scePower|scePowerGetCpuClockFrequencyInt|g|int scePowerGetCpuClockFrequencyInt(void)}
        int  scePowerGetCpuClockFrequencyInt()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FEE03A2F|scePower|scePowerGetCpuClockFrequency|g|int scePowerGetCpuClockFrequency(void)}
        int  scePowerGetCpuClockFrequency()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{scePower|scePower_Service|power.prx}
}

extern "C" bool __cdecl scePower$Init() { return hle::scePower::Init(); }
extern "C" bool __cdecl scePower$Fini() { return hle::scePower::Fini(); }
extern "C" void __cdecl scePower_0074EF9B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetResumeCount                           >(c); } //@hle:syscall{0074EF9B|scePower|scePowerGetResumeCount|g|??? scePowerGetResumeCount()}
extern "C" void __cdecl scePower_0442D852(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerRequestColdReset                         >(c); } //@hle:syscall{0442D852|scePower|scePowerRequestColdReset|g|??? scePowerRequestColdReset()}
extern "C" void __cdecl scePower_04B7766E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::scePower::scePowerRegisterCallback                         >(c); } //@hle:syscall{04B7766E|scePower|scePowerRegisterCallback|ggg|int scePowerRegisterCallback(int slot, SceUID cbid)}
extern "C" void __cdecl scePower_0AFD0D8B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerIsBatteryExist                           >(c); } //@hle:syscall{0AFD0D8B|scePower|scePowerIsBatteryExist|g|int scePowerIsBatteryExist(void)}
extern "C" void __cdecl scePower_0CD21B1F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerSetPowerSwMode                           >(c); } //@hle:syscall{0CD21B1F|scePower|scePowerSetPowerSwMode|g|??? scePowerSetPowerSwMode()}
extern "C" void __cdecl scePower_165CE085(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetPowerSwMode                           >(c); } //@hle:syscall{165CE085|scePower|scePowerGetPowerSwMode|g|??? scePowerGetPowerSwMode()}
extern "C" void __cdecl scePower_1E490401(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerIsBatteryCharging                        >(c); } //@hle:syscall{1E490401|scePower|scePowerIsBatteryCharging|g|int scePowerIsBatteryCharging(void)}
extern "C" void __cdecl scePower_2085D15D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBatteryLifePercent                    >(c); } //@hle:syscall{2085D15D|scePower|scePowerGetBatteryLifePercent|g|int scePowerGetBatteryLifePercent(void)}
extern "C" void __cdecl scePower_23436A4A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetInnerTemp                             >(c); } //@hle:syscall{23436A4A|scePower|scePowerGetInnerTemp|g|??? scePowerGetInnerTemp()}
extern "C" void __cdecl scePower_23C31FFE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerVolatileMemLock                          >(c); } //@hle:syscall{23C31FFE|scePower|scePowerVolatileMemLock|g|??? scePowerVolatileMemLock()}
extern "C" void __cdecl scePower_27F3292C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerBatteryUpdateInfo                        >(c); } //@hle:syscall{27F3292C|scePower|scePowerBatteryUpdateInfo|g|??? scePowerBatteryUpdateInfo()}
extern "C" void __cdecl scePower_2875994B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePower_2875994B                                >(c); } //@hle:syscall{2875994B|scePower|scePower_2875994B|g|??? scePower_2875994B()}
extern "C" void __cdecl scePower_28E12023(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBatteryTemp                           >(c); } //@hle:syscall{28E12023|scePower|scePowerGetBatteryTemp|g|int scePowerGetBatteryTemp(void)}
extern "C" void __cdecl scePower_2B51FE2F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePower_2B51FE2F                                >(c); } //@hle:syscall{2B51FE2F|scePower|scePower_2B51FE2F|g|??? scePower_2B51FE2F()}
extern "C" void __cdecl scePower_2B7C7CF4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerRequestStandby                           >(c); } //@hle:syscall{2B7C7CF4|scePower|scePowerRequestStandby|g|int scePowerRequestStandby(void)}
extern "C" void __cdecl scePower_34F9C463(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetPllClockFrequencyInt                  >(c); } //@hle:syscall{34F9C463|scePower|scePowerGetPllClockFrequencyInt|g|??? scePowerGetPllClockFrequencyInt()}
extern "C" void __cdecl scePower_3951AF53(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerWaitRequestCompletion                    >(c); } //@hle:syscall{3951AF53|scePower|scePowerWaitRequestCompletion|g|??? scePowerWaitRequestCompletion()}
extern "C" void __cdecl scePower_442BFBAC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBacklightMaximum                      >(c); } //@hle:syscall{442BFBAC|scePower|scePowerGetBacklightMaximum|g|??? scePowerGetBacklightMaximum()}
extern "C" void __cdecl scePower_478FE6F5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBusClockFrequency                     >(c); } //@hle:syscall{478FE6F5|scePower|scePowerGetBusClockFrequency|g|int scePowerGetBusClockFrequency(void)}
extern "C" void __cdecl scePower_483CE86B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBatteryVolt                           >(c); } //@hle:syscall{483CE86B|scePower|scePowerGetBatteryVolt|g|int scePowerGetBatteryVolt(void)}
extern "C" void __cdecl scePower_545A7F3C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePower_545A7F3C                                >(c); } //@hle:syscall{545A7F3C|scePower|scePower_545A7F3C|g|??? scePower_545A7F3C()}
extern "C" void __cdecl scePower_737486F2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::scePower::scePowerSetClockFrequency                        >(c); } //@hle:syscall{737486F2|scePower|scePowerSetClockFrequency|gggg|int scePowerSetClockFrequency(int cpufreq, int ramfreq, int busfreq)}
extern "C" void __cdecl scePower_78A1A796(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerIsSuspendRequired                        >(c); } //@hle:syscall{78A1A796|scePower|scePowerIsSuspendRequired|g|??? scePowerIsSuspendRequired()}
extern "C" void __cdecl scePower_7F30B3B1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::scePower::scePowerIdleTimerEnable                          >(c); } //@hle:syscall{7F30B3B1|scePower|scePowerIdleTimerEnable|gg|int scePowerIdleTimerEnable(int unknown)}
extern "C" void __cdecl scePower_7FA406DD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerIsRequest                                >(c); } //@hle:syscall{7FA406DD|scePower|scePowerIsRequest|g|??? scePowerIsRequest()}
extern "C" void __cdecl scePower_843FBF43(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::scePower::scePowerSetCpuClockFrequency                     >(c); } //@hle:syscall{843FBF43|scePower|scePowerSetCpuClockFrequency|gg|int scePowerSetCpuClockFrequency(int cpufreq)}
extern "C" void __cdecl scePower_862AE1A6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBatteryElec                           >(c); } //@hle:syscall{862AE1A6|scePower|scePowerGetBatteryElec|g|int scePowerGetBatteryElec(void)}
extern "C" void __cdecl scePower_87440F5E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerIsPowerOnline                            >(c); } //@hle:syscall{87440F5E|scePower|scePowerIsPowerOnline|g|int scePowerIsPowerOnline(void)}
extern "C" void __cdecl scePower_8EFB3FA2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBatteryLifeTime                       >(c); } //@hle:syscall{8EFB3FA2|scePower|scePowerGetBatteryLifeTime|g|int scePowerGetBatteryLifeTime(void)}
extern "C" void __cdecl scePower_94F5A53F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBatteryRemainCapacity                 >(c); } //@hle:syscall{94F5A53F|scePower|scePowerGetBatteryRemainCapacity|g|??? scePowerGetBatteryRemainCapacity()}
extern "C" void __cdecl scePower_972CE941(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::scePower::scePowerIdleTimerDisable                         >(c); } //@hle:syscall{972CE941|scePower|scePowerIdleTimerDisable|gg|int scePowerIdleTimerDisable(int unknown)}
extern "C" void __cdecl scePower_9BADB3EB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBusClockFrequencyFloat                >(c); } //@hle:syscall{9BADB3EB|scePower|scePowerGetBusClockFrequencyFloat|g|float scePowerGetBusClockFrequencyFloat(void)}
extern "C" void __cdecl scePower_A4E93389(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePower_A4E93389                                >(c); } //@hle:syscall{A4E93389|scePower|scePower_A4E93389|g|??? scePower_A4E93389()}
extern "C" void __cdecl scePower_A9D22232(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerSetCallbackMode                          >(c); } //@hle:syscall{A9D22232|scePower|scePowerSetCallbackMode|g|??? scePowerSetCallbackMode()}
extern "C" void __cdecl scePower_AC32C9CC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerRequestSuspend                           >(c); } //@hle:syscall{AC32C9CC|scePower|scePowerRequestSuspend|g|int scePowerRequestSuspend(void)}
extern "C" void __cdecl scePower_B1A52C83(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetCpuClockFrequencyFloat                >(c); } //@hle:syscall{B1A52C83|scePower|scePowerGetCpuClockFrequencyFloat|g|float scePowerGetCpuClockFrequencyFloat(void)}
extern "C" void __cdecl scePower_B3EDD801(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerVolatileMemUnlock                        >(c); } //@hle:syscall{B3EDD801|scePower|scePowerVolatileMemUnlock|g|??? scePowerVolatileMemUnlock()}
extern "C" void __cdecl scePower_B4432BC8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBatteryChargingStatus                 >(c); } //@hle:syscall{B4432BC8|scePower|scePowerGetBatteryChargingStatus|g|int scePowerGetBatteryChargingStatus(void)}
extern "C" void __cdecl scePower_B8D7B3FB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::scePower::scePowerSetBusClockFrequency                     >(c); } //@hle:syscall{B8D7B3FB|scePower|scePowerSetBusClockFrequency|gg|int scePowerSetBusClockFrequency(int busfreq)}
extern "C" void __cdecl scePower_B999184C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetLowBatteryCapacity                    >(c); } //@hle:syscall{B999184C|scePower|scePowerGetLowBatteryCapacity|g|??? scePowerGetLowBatteryCapacity()}
extern "C" void __cdecl scePower_BAFA3DF0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetCallbackMode                          >(c); } //@hle:syscall{BAFA3DF0|scePower|scePowerGetCallbackMode|g|??? scePowerGetCallbackMode()}
extern "C" void __cdecl scePower_BD681969(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBusClockFrequencyInt                  >(c); } //@hle:syscall{BD681969|scePower|scePowerGetBusClockFrequencyInt|g|int scePowerGetBusClockFrequencyInt(void)}
extern "C" void __cdecl scePower_CA3D34C1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::scePower::scePowerUnlock                                   >(c); } //@hle:syscall{CA3D34C1|scePower|scePowerUnlock|gg|int scePowerUnlock(int unknown)}
extern "C" void __cdecl scePower_CB49F5CE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBatteryChargeCycle                    >(c); } //@hle:syscall{CB49F5CE|scePower|scePowerGetBatteryChargeCycle|g|??? scePowerGetBatteryChargeCycle()}
extern "C" void __cdecl scePower_D3075926(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerIsLowBattery                             >(c); } //@hle:syscall{D3075926|scePower|scePowerIsLowBattery|g|int scePowerIsLowBattery(void)}
extern "C" void __cdecl scePower_D6D016EF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::scePower::scePowerLock                                     >(c); } //@hle:syscall{D6D016EF|scePower|scePowerLock|gg|int scePowerLock(int unknown)}
extern "C" void __cdecl scePower_DB62C9CF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerCancelRequest                            >(c); } //@hle:syscall{DB62C9CF|scePower|scePowerCancelRequest|g|??? scePowerCancelRequest()}
extern "C" void __cdecl scePower_DB9D28DD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerUnregitserCallback                       >(c); } //@hle:syscall{DB9D28DD|scePower|scePowerUnregitserCallback|g|??? scePowerUnregitserCallback()}
extern "C" void __cdecl scePower_DFA8BAF8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerUnregisterCallback                       >(c); } //@hle:syscall{DFA8BAF8|scePower|scePowerUnregisterCallback|g|??? scePowerUnregisterCallback()}
extern "C" void __cdecl scePower_E8E4E204(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePower_E8E4E204                                >(c); } //@hle:syscall{E8E4E204|scePower|scePower_E8E4E204|g|??? scePower_E8E4E204()}
extern "C" void __cdecl scePower_EA382A27(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetPllClockFrequencyFloat                >(c); } //@hle:syscall{EA382A27|scePower|scePowerGetPllClockFrequencyFloat|g|??? scePowerGetPllClockFrequencyFloat()}
extern "C" void __cdecl scePower_EBD177D6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePower_EBD177D6                                >(c); } //@hle:syscall{EBD177D6|scePower|scePower_EBD177D6|g|??? scePower_EBD177D6()}
extern "C" void __cdecl scePower_EDC13FE5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetIdleTimer                             >(c); } //@hle:syscall{EDC13FE5|scePower|scePowerGetIdleTimer|g|int scePowerGetIdleTimer(void)}
extern "C" void __cdecl scePower_EFD3C963(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::scePower::scePowerTick                                     >(c); } //@hle:syscall{EFD3C963|scePower|scePowerTick|gg|int scePowerTick(int unknown)}
extern "C" void __cdecl scePower_FA97A599(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerVolatileMemTryLock                       >(c); } //@hle:syscall{FA97A599|scePower|scePowerVolatileMemTryLock|g|??? scePowerVolatileMemTryLock()}
extern "C" void __cdecl scePower_FD18A0FF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetBatteryFullCapacity                   >(c); } //@hle:syscall{FD18A0FF|scePower|scePowerGetBatteryFullCapacity|g|??? scePowerGetBatteryFullCapacity()}
extern "C" void __cdecl scePower_FDB5BFE9(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetCpuClockFrequencyInt                  >(c); } //@hle:syscall{FDB5BFE9|scePower|scePowerGetCpuClockFrequencyInt|g|int scePowerGetCpuClockFrequencyInt(void)}
extern "C" void __cdecl scePower_FEE03A2F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::scePower::scePowerGetCpuClockFrequency                     >(c); } //@hle:syscall{FEE03A2F|scePower|scePowerGetCpuClockFrequency|g|int scePowerGetCpuClockFrequency(void)}