//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(rtc.prx)sceRtc.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceRtc //@hle:library-start{sceRtc|sceRTC_Service|rtc.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{44F45E05|sceRtc|sceRtcTickAddTicks|gggG|int sceRtcTickAddTicks(u64 * destTick, const u64 * srcTick, u64 numTicks)}
        int  sceRtcTickAddTicks(u32 $a0, u32 $a1, u64 $a3a2)
        {
            (void)($a0, $a1, $a3a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{26D25A5D|sceRtc|sceRtcTickAddMicroseconds|gggg|int sceRtcTickAddMicroseconds(u64 * destTick, const u64 * srcTick, u64 numMS)}
        int  sceRtcTickAddMicroseconds(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F2A4AFE5|sceRtc|sceRtcTickAddSeconds|gggg|int sceRtcTickAddSeconds(u64 * destTick, const u64 * srcTick, u64 numSecs)}
        int  sceRtcTickAddSeconds(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E6605BCA|sceRtc|sceRtcTickAddMinutes|gggg|int sceRtcTickAddMinutes(u64 * destTick, const u64 * srcTick, u64 numMins)}
        int  sceRtcTickAddMinutes(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{26D7A24A|sceRtc|sceRtcTickAddHours|gggg|int sceRtcTickAddHours(u64 * destTick, const u64 * srcTick, int numHours)}
        int  sceRtcTickAddHours(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E51B4B7A|sceRtc|sceRtcTickAddDays|gggg|int sceRtcTickAddDays(u64 * destTick, const u64 * srcTick, int numDays)}
        int  sceRtcTickAddDays(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CF3A2CA8|sceRtc|sceRtcTickAddWeeks|gggg|int sceRtcTickAddWeeks(u64 * destTick, const u64 * srcTick, int numWeeks)}
        int  sceRtcTickAddWeeks(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DBF74F1B|sceRtc|sceRtcTickAddMonths|gggg|int sceRtcTickAddMonths(u64 * destTick, const u64 * srcTick, int numMonths)}
        int  sceRtcTickAddMonths(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{42842C77|sceRtc|sceRtcTickAddYears|gggg|int sceRtcTickAddYears(u64 * destTick, const u64 * srcTick, int numYears)}
        int  sceRtcTickAddYears(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{011F03C1|sceRtc|sceRtcGetAccumulativeTime|g|??? sceRtcGetAccumulativeTime()}
        int  sceRtcGetAccumulativeTime()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{029CA3B3|sceRtc|sceRtcGetAccumlativeTime|g|??? sceRtcGetAccumlativeTime()}
        int  sceRtcGetAccumlativeTime()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0498FB3C|sceRtc|sceRtcFormatRFC3339|g|??? sceRtcFormatRFC3339()}
        int  sceRtcFormatRFC3339()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{05EF322C|sceRtc|sceRtcGetDaysInMonth|ggg|int sceRtcGetDaysInMonth(int year, int month)}
        int  sceRtcGetDaysInMonth(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1909C99B|sceRtc|sceRtcSetTime64_t|g|??? sceRtcSetTime64_t()}
        int  sceRtcSetTime64_t()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{203CEB0D|sceRtc|sceRtcGetLastReincarnatedTime|g|??? sceRtcGetLastReincarnatedTime()}
        int  sceRtcGetLastReincarnatedTime()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{27C4594C|sceRtc|sceRtcGetTime_t|ggg|int sceRtcGetTime_t(const pspTime * date, time_t time)}
        int  sceRtcGetTime_t(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{27F98543|sceRtc|sceRtcFormatRFC3339LocalTime|g|??? sceRtcFormatRFC3339LocalTime()}
        int  sceRtcFormatRFC3339LocalTime()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{28E1E988|sceRtc|sceRtcParseRFC3339|g|??? sceRtcParseRFC3339()}
        int  sceRtcParseRFC3339()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{34885E0D|sceRtc|sceRtcConvertUtcToLocalTime|ggg|int sceRtcConvertUtcToLocalTime(const u64 * tickUTC, u64 * tickLocal)}
        int  sceRtcConvertUtcToLocalTime(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{36075567|sceRtc|sceRtcGetDosTime|ggg|int sceRtcGetDosTime(pspTime * date, u32 dosTime)}
        int  sceRtcGetDosTime(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3A807CC8|sceRtc|sceRtcSetTime_t|ggg|int sceRtcSetTime_t(pspTime * date, const time_t time)}
        int  sceRtcSetTime_t(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3F7AD767|sceRtc|sceRtcGetCurrentTick|gg|int sceRtcGetCurrentTick(u64 * tick)}
        int  sceRtcGetCurrentTick(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{42307A17|sceRtc|sceRtcIsLeapYear|gg|int sceRtcIsLeapYear(int year)}
        int  sceRtcIsLeapYear(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4B1B5E82|sceRtc|sceRtcCheckValid|gg|int sceRtcCheckValid(const pspTime * date)}
        int  sceRtcCheckValid(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4CFA57B0|sceRtc|sceRtcGetCurrentClock|ggg|int sceRtcGetCurrentClock(pspTime * time, int tz)}
        int  sceRtcGetCurrentClock(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{57726BC1|sceRtc|sceRtcGetDayOfWeek|gggg|int sceRtcGetDayOfWeek(int year, int month, int day)}
        int  sceRtcGetDayOfWeek(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{62685E98|sceRtc|sceRtcGetLastAdjustedTime|g|??? sceRtcGetLastAdjustedTime()}
        int  sceRtcGetLastAdjustedTime()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6A676D2D|sceRtc|sceRtcUnregisterCallback|g|??? sceRtcUnregisterCallback()}
        int  sceRtcUnregisterCallback()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6FF40ACC|sceRtc|sceRtcGetTick|ggg|int sceRtcGetTick(const pspTime * date, u64 * tick)}
        int  sceRtcGetTick(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{779242A2|sceRtc|sceRtcConvertLocalTimeToUTC|ggg|int sceRtcConvertLocalTimeToUTC(const u64 * tickLocal, u64 * tickUTC)}
        int  sceRtcConvertLocalTimeToUTC(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7ACE4C04|sceRtc|sceRtcSetWin32FileTime|ggg|int sceRtcSetWin32FileTime(pspTime * date, u64 * win32Time)}
        int  sceRtcSetWin32FileTime(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7D1FBED3|sceRtc|sceRtc_7D1FBED3|g|??? sceRtc_7D1FBED3()}
        int  sceRtc_7D1FBED3()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7DE6711B|sceRtc|sceRtcFormatRFC2822LocalTime|g|??? sceRtcFormatRFC2822LocalTime()}
        int  sceRtcFormatRFC2822LocalTime()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7ED29E40|sceRtc|sceRtcSetTick|ggg|int sceRtcSetTick(pspTime * date, const u64 * tick)}
        int  sceRtcSetTick(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{81FCDA34|sceRtc|sceRtcIsAlarmed|g|??? sceRtcIsAlarmed()}
        int  sceRtcIsAlarmed()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9ED0AE87|sceRtc|sceRtcCompareTick|ggg|int sceRtcCompareTick(const u64 * tick1, const u64 * tick2)}
        int  sceRtcCompareTick(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A93CF7D8|sceRtc|sceRtc_A93CF7D8|g|??? sceRtc_A93CF7D8()}
        int  sceRtc_A93CF7D8()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C2DDBEB5|sceRtc|sceRtc_C2DDBEB5|g|??? sceRtc_C2DDBEB5()}
        int  sceRtc_C2DDBEB5()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C41C2853|sceRtc|sceRtcGetTickResolution|g|u32 sceRtcGetTickResolution(void)}
        int  sceRtcGetTickResolution()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C663B3B9|sceRtc|sceRtcFormatRFC2822|g|??? sceRtcFormatRFC2822()}
        int  sceRtcFormatRFC2822()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CF561893|sceRtc|sceRtcGetWin32FileTime|ggg|int sceRtcGetWin32FileTime(pspTime * date, u64 * win32Time)}
        int  sceRtcGetWin32FileTime(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DFBC5F16|sceRtc|sceRtcParseDateTime|ggg|int sceRtcParseDateTime(u64 * destTick, const char * dateString)}
        int  sceRtcParseDateTime(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E1C93E47|sceRtc|sceRtcGetTime64_t|g|??? sceRtcGetTime64_t()}
        int  sceRtcGetTime64_t()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E7C27D1B|sceRtc|sceRtcGetCurrentClockLocalTime|gg|int sceRtcGetCurrentClockLocalTime(pspTime * time)}
        int  sceRtcGetCurrentClockLocalTime(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F006F264|sceRtc|sceRtcSetDosTime|ggg|int sceRtcSetDosTime(pspTime * date, u32 dosTime)}
        int  sceRtcSetDosTime(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F5FCC995|sceRtc|sceRtc_F5FCC995|g|??? sceRtc_F5FCC995()}
        int  sceRtc_F5FCC995()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FB3B18CD|sceRtc|sceRtcRegisterCallback|g|??? sceRtcRegisterCallback()}
        int  sceRtcRegisterCallback()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceRtc|sceRTC_Service|rtc.prx}
}

extern "C" bool __cdecl sceRtc$Init() { return hle::sceRtc::Init(); }
extern "C" bool __cdecl sceRtc$Fini() { return hle::sceRtc::Fini(); }
extern "C" void __cdecl sceRtc_44F45E05(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggG            < hle::sceRtc::sceRtcTickAddTicks                               >(c); } //@hle:syscall{44F45E05|sceRtc|sceRtcTickAddTicks|gggG|int sceRtcTickAddTicks(u64 * destTick, const u64 * srcTick, u64 numTicks)}
extern "C" void __cdecl sceRtc_26D25A5D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceRtc::sceRtcTickAddMicroseconds                        >(c); } //@hle:syscall{26D25A5D|sceRtc|sceRtcTickAddMicroseconds|gggg|int sceRtcTickAddMicroseconds(u64 * destTick, const u64 * srcTick, u64 numMS)}
extern "C" void __cdecl sceRtc_F2A4AFE5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceRtc::sceRtcTickAddSeconds                             >(c); } //@hle:syscall{F2A4AFE5|sceRtc|sceRtcTickAddSeconds|gggg|int sceRtcTickAddSeconds(u64 * destTick, const u64 * srcTick, u64 numSecs)}
extern "C" void __cdecl sceRtc_E6605BCA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceRtc::sceRtcTickAddMinutes                             >(c); } //@hle:syscall{E6605BCA|sceRtc|sceRtcTickAddMinutes|gggg|int sceRtcTickAddMinutes(u64 * destTick, const u64 * srcTick, u64 numMins)}
extern "C" void __cdecl sceRtc_26D7A24A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceRtc::sceRtcTickAddHours                               >(c); } //@hle:syscall{26D7A24A|sceRtc|sceRtcTickAddHours|gggg|int sceRtcTickAddHours(u64 * destTick, const u64 * srcTick, int numHours)}
extern "C" void __cdecl sceRtc_E51B4B7A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceRtc::sceRtcTickAddDays                                >(c); } //@hle:syscall{E51B4B7A|sceRtc|sceRtcTickAddDays|gggg|int sceRtcTickAddDays(u64 * destTick, const u64 * srcTick, int numDays)}
extern "C" void __cdecl sceRtc_CF3A2CA8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceRtc::sceRtcTickAddWeeks                               >(c); } //@hle:syscall{CF3A2CA8|sceRtc|sceRtcTickAddWeeks|gggg|int sceRtcTickAddWeeks(u64 * destTick, const u64 * srcTick, int numWeeks)}
extern "C" void __cdecl sceRtc_DBF74F1B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceRtc::sceRtcTickAddMonths                              >(c); } //@hle:syscall{DBF74F1B|sceRtc|sceRtcTickAddMonths|gggg|int sceRtcTickAddMonths(u64 * destTick, const u64 * srcTick, int numMonths)}
extern "C" void __cdecl sceRtc_42842C77(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceRtc::sceRtcTickAddYears                               >(c); } //@hle:syscall{42842C77|sceRtc|sceRtcTickAddYears|gggg|int sceRtcTickAddYears(u64 * destTick, const u64 * srcTick, int numYears)}
extern "C" void __cdecl sceRtc_011F03C1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcGetAccumulativeTime                        >(c); } //@hle:syscall{011F03C1|sceRtc|sceRtcGetAccumulativeTime|g|??? sceRtcGetAccumulativeTime()}
extern "C" void __cdecl sceRtc_029CA3B3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcGetAccumlativeTime                         >(c); } //@hle:syscall{029CA3B3|sceRtc|sceRtcGetAccumlativeTime|g|??? sceRtcGetAccumlativeTime()}
extern "C" void __cdecl sceRtc_0498FB3C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcFormatRFC3339                              >(c); } //@hle:syscall{0498FB3C|sceRtc|sceRtcFormatRFC3339|g|??? sceRtcFormatRFC3339()}
extern "C" void __cdecl sceRtc_05EF322C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcGetDaysInMonth                             >(c); } //@hle:syscall{05EF322C|sceRtc|sceRtcGetDaysInMonth|ggg|int sceRtcGetDaysInMonth(int year, int month)}
extern "C" void __cdecl sceRtc_1909C99B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcSetTime64_t                                >(c); } //@hle:syscall{1909C99B|sceRtc|sceRtcSetTime64_t|g|??? sceRtcSetTime64_t()}
extern "C" void __cdecl sceRtc_203CEB0D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcGetLastReincarnatedTime                    >(c); } //@hle:syscall{203CEB0D|sceRtc|sceRtcGetLastReincarnatedTime|g|??? sceRtcGetLastReincarnatedTime()}
extern "C" void __cdecl sceRtc_27C4594C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcGetTime_t                                  >(c); } //@hle:syscall{27C4594C|sceRtc|sceRtcGetTime_t|ggg|int sceRtcGetTime_t(const pspTime * date, time_t time)}
extern "C" void __cdecl sceRtc_27F98543(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcFormatRFC3339LocalTime                     >(c); } //@hle:syscall{27F98543|sceRtc|sceRtcFormatRFC3339LocalTime|g|??? sceRtcFormatRFC3339LocalTime()}
extern "C" void __cdecl sceRtc_28E1E988(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcParseRFC3339                               >(c); } //@hle:syscall{28E1E988|sceRtc|sceRtcParseRFC3339|g|??? sceRtcParseRFC3339()}
extern "C" void __cdecl sceRtc_34885E0D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcConvertUtcToLocalTime                      >(c); } //@hle:syscall{34885E0D|sceRtc|sceRtcConvertUtcToLocalTime|ggg|int sceRtcConvertUtcToLocalTime(const u64 * tickUTC, u64 * tickLocal)}
extern "C" void __cdecl sceRtc_36075567(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcGetDosTime                                 >(c); } //@hle:syscall{36075567|sceRtc|sceRtcGetDosTime|ggg|int sceRtcGetDosTime(pspTime * date, u32 dosTime)}
extern "C" void __cdecl sceRtc_3A807CC8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcSetTime_t                                  >(c); } //@hle:syscall{3A807CC8|sceRtc|sceRtcSetTime_t|ggg|int sceRtcSetTime_t(pspTime * date, const time_t time)}
extern "C" void __cdecl sceRtc_3F7AD767(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceRtc::sceRtcGetCurrentTick                             >(c); } //@hle:syscall{3F7AD767|sceRtc|sceRtcGetCurrentTick|gg|int sceRtcGetCurrentTick(u64 * tick)}
extern "C" void __cdecl sceRtc_42307A17(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceRtc::sceRtcIsLeapYear                                 >(c); } //@hle:syscall{42307A17|sceRtc|sceRtcIsLeapYear|gg|int sceRtcIsLeapYear(int year)}
extern "C" void __cdecl sceRtc_4B1B5E82(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceRtc::sceRtcCheckValid                                 >(c); } //@hle:syscall{4B1B5E82|sceRtc|sceRtcCheckValid|gg|int sceRtcCheckValid(const pspTime * date)}
extern "C" void __cdecl sceRtc_4CFA57B0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcGetCurrentClock                            >(c); } //@hle:syscall{4CFA57B0|sceRtc|sceRtcGetCurrentClock|ggg|int sceRtcGetCurrentClock(pspTime * time, int tz)}
extern "C" void __cdecl sceRtc_57726BC1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceRtc::sceRtcGetDayOfWeek                               >(c); } //@hle:syscall{57726BC1|sceRtc|sceRtcGetDayOfWeek|gggg|int sceRtcGetDayOfWeek(int year, int month, int day)}
extern "C" void __cdecl sceRtc_62685E98(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcGetLastAdjustedTime                        >(c); } //@hle:syscall{62685E98|sceRtc|sceRtcGetLastAdjustedTime|g|??? sceRtcGetLastAdjustedTime()}
extern "C" void __cdecl sceRtc_6A676D2D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcUnregisterCallback                         >(c); } //@hle:syscall{6A676D2D|sceRtc|sceRtcUnregisterCallback|g|??? sceRtcUnregisterCallback()}
extern "C" void __cdecl sceRtc_6FF40ACC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcGetTick                                    >(c); } //@hle:syscall{6FF40ACC|sceRtc|sceRtcGetTick|ggg|int sceRtcGetTick(const pspTime * date, u64 * tick)}
extern "C" void __cdecl sceRtc_779242A2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcConvertLocalTimeToUTC                      >(c); } //@hle:syscall{779242A2|sceRtc|sceRtcConvertLocalTimeToUTC|ggg|int sceRtcConvertLocalTimeToUTC(const u64 * tickLocal, u64 * tickUTC)}
extern "C" void __cdecl sceRtc_7ACE4C04(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcSetWin32FileTime                           >(c); } //@hle:syscall{7ACE4C04|sceRtc|sceRtcSetWin32FileTime|ggg|int sceRtcSetWin32FileTime(pspTime * date, u64 * win32Time)}
extern "C" void __cdecl sceRtc_7D1FBED3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtc_7D1FBED3                                  >(c); } //@hle:syscall{7D1FBED3|sceRtc|sceRtc_7D1FBED3|g|??? sceRtc_7D1FBED3()}
extern "C" void __cdecl sceRtc_7DE6711B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcFormatRFC2822LocalTime                     >(c); } //@hle:syscall{7DE6711B|sceRtc|sceRtcFormatRFC2822LocalTime|g|??? sceRtcFormatRFC2822LocalTime()}
extern "C" void __cdecl sceRtc_7ED29E40(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcSetTick                                    >(c); } //@hle:syscall{7ED29E40|sceRtc|sceRtcSetTick|ggg|int sceRtcSetTick(pspTime * date, const u64 * tick)}
extern "C" void __cdecl sceRtc_81FCDA34(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcIsAlarmed                                  >(c); } //@hle:syscall{81FCDA34|sceRtc|sceRtcIsAlarmed|g|??? sceRtcIsAlarmed()}
extern "C" void __cdecl sceRtc_9ED0AE87(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcCompareTick                                >(c); } //@hle:syscall{9ED0AE87|sceRtc|sceRtcCompareTick|ggg|int sceRtcCompareTick(const u64 * tick1, const u64 * tick2)}
extern "C" void __cdecl sceRtc_A93CF7D8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtc_A93CF7D8                                  >(c); } //@hle:syscall{A93CF7D8|sceRtc|sceRtc_A93CF7D8|g|??? sceRtc_A93CF7D8()}
extern "C" void __cdecl sceRtc_C2DDBEB5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtc_C2DDBEB5                                  >(c); } //@hle:syscall{C2DDBEB5|sceRtc|sceRtc_C2DDBEB5|g|??? sceRtc_C2DDBEB5()}
extern "C" void __cdecl sceRtc_C41C2853(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcGetTickResolution                          >(c); } //@hle:syscall{C41C2853|sceRtc|sceRtcGetTickResolution|g|u32 sceRtcGetTickResolution(void)}
extern "C" void __cdecl sceRtc_C663B3B9(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcFormatRFC2822                              >(c); } //@hle:syscall{C663B3B9|sceRtc|sceRtcFormatRFC2822|g|??? sceRtcFormatRFC2822()}
extern "C" void __cdecl sceRtc_CF561893(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcGetWin32FileTime                           >(c); } //@hle:syscall{CF561893|sceRtc|sceRtcGetWin32FileTime|ggg|int sceRtcGetWin32FileTime(pspTime * date, u64 * win32Time)}
extern "C" void __cdecl sceRtc_DFBC5F16(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcParseDateTime                              >(c); } //@hle:syscall{DFBC5F16|sceRtc|sceRtcParseDateTime|ggg|int sceRtcParseDateTime(u64 * destTick, const char * dateString)}
extern "C" void __cdecl sceRtc_E1C93E47(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcGetTime64_t                                >(c); } //@hle:syscall{E1C93E47|sceRtc|sceRtcGetTime64_t|g|??? sceRtcGetTime64_t()}
extern "C" void __cdecl sceRtc_E7C27D1B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceRtc::sceRtcGetCurrentClockLocalTime                   >(c); } //@hle:syscall{E7C27D1B|sceRtc|sceRtcGetCurrentClockLocalTime|gg|int sceRtcGetCurrentClockLocalTime(pspTime * time)}
extern "C" void __cdecl sceRtc_F006F264(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceRtc::sceRtcSetDosTime                                 >(c); } //@hle:syscall{F006F264|sceRtc|sceRtcSetDosTime|ggg|int sceRtcSetDosTime(pspTime * date, u32 dosTime)}
extern "C" void __cdecl sceRtc_F5FCC995(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtc_F5FCC995                                  >(c); } //@hle:syscall{F5FCC995|sceRtc|sceRtc_F5FCC995|g|??? sceRtc_F5FCC995()}
extern "C" void __cdecl sceRtc_FB3B18CD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceRtc::sceRtcRegisterCallback                           >(c); } //@hle:syscall{FB3B18CD|sceRtc|sceRtcRegisterCallback|g|??? sceRtcRegisterCallback()}