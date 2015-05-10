//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_rtc_prx_sceRtc_h__
#define hle_rtc_prx_sceRtc_h__

namespace hle
{
    namespace sceRtc //@hle:library-start{sceRtc|sceRTC_Service|rtc.prx}
    {
        //@hle:function{44F45E05|sceRtc|sceRtcTickAddTicks|gggG|int sceRtcTickAddTicks(u64 * destTick, const u64 * srcTick, u64 numTicks)}
        extern int  sceRtcTickAddTicks(u32 $a0, u32 $a1, u64 $a3a2);
        //@hle:function{26D25A5D|sceRtc|sceRtcTickAddMicroseconds|gggg|int sceRtcTickAddMicroseconds(u64 * destTick, const u64 * srcTick, u64 numMS)}
        extern int  sceRtcTickAddMicroseconds(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{F2A4AFE5|sceRtc|sceRtcTickAddSeconds|gggg|int sceRtcTickAddSeconds(u64 * destTick, const u64 * srcTick, u64 numSecs)}
        extern int  sceRtcTickAddSeconds(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{E6605BCA|sceRtc|sceRtcTickAddMinutes|gggg|int sceRtcTickAddMinutes(u64 * destTick, const u64 * srcTick, u64 numMins)}
        extern int  sceRtcTickAddMinutes(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{26D7A24A|sceRtc|sceRtcTickAddHours|gggg|int sceRtcTickAddHours(u64 * destTick, const u64 * srcTick, int numHours)}
        extern int  sceRtcTickAddHours(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{E51B4B7A|sceRtc|sceRtcTickAddDays|gggg|int sceRtcTickAddDays(u64 * destTick, const u64 * srcTick, int numDays)}
        extern int  sceRtcTickAddDays(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{CF3A2CA8|sceRtc|sceRtcTickAddWeeks|gggg|int sceRtcTickAddWeeks(u64 * destTick, const u64 * srcTick, int numWeeks)}
        extern int  sceRtcTickAddWeeks(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{DBF74F1B|sceRtc|sceRtcTickAddMonths|gggg|int sceRtcTickAddMonths(u64 * destTick, const u64 * srcTick, int numMonths)}
        extern int  sceRtcTickAddMonths(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{42842C77|sceRtc|sceRtcTickAddYears|gggg|int sceRtcTickAddYears(u64 * destTick, const u64 * srcTick, int numYears)}
        extern int  sceRtcTickAddYears(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{011F03C1|sceRtc|sceRtcGetAccumulativeTime|g|??? sceRtcGetAccumulativeTime()}
        extern int  sceRtcGetAccumulativeTime();
        //@hle:function{029CA3B3|sceRtc|sceRtcGetAccumlativeTime|g|??? sceRtcGetAccumlativeTime()}
        extern int  sceRtcGetAccumlativeTime();
        //@hle:function{0498FB3C|sceRtc|sceRtcFormatRFC3339|g|??? sceRtcFormatRFC3339()}
        extern int  sceRtcFormatRFC3339();
        //@hle:function{05EF322C|sceRtc|sceRtcGetDaysInMonth|ggg|int sceRtcGetDaysInMonth(int year, int month)}
        extern int  sceRtcGetDaysInMonth(u32 $a0, u32 $a1);
        //@hle:function{1909C99B|sceRtc|sceRtcSetTime64_t|g|??? sceRtcSetTime64_t()}
        extern int  sceRtcSetTime64_t();
        //@hle:function{203CEB0D|sceRtc|sceRtcGetLastReincarnatedTime|g|??? sceRtcGetLastReincarnatedTime()}
        extern int  sceRtcGetLastReincarnatedTime();
        //@hle:function{27C4594C|sceRtc|sceRtcGetTime_t|ggg|int sceRtcGetTime_t(const pspTime * date, time_t time)}
        extern int  sceRtcGetTime_t(u32 $a0, u32 $a1);
        //@hle:function{27F98543|sceRtc|sceRtcFormatRFC3339LocalTime|g|??? sceRtcFormatRFC3339LocalTime()}
        extern int  sceRtcFormatRFC3339LocalTime();
        //@hle:function{28E1E988|sceRtc|sceRtcParseRFC3339|g|??? sceRtcParseRFC3339()}
        extern int  sceRtcParseRFC3339();
        //@hle:function{34885E0D|sceRtc|sceRtcConvertUtcToLocalTime|ggg|int sceRtcConvertUtcToLocalTime(const u64 * tickUTC, u64 * tickLocal)}
        extern int  sceRtcConvertUtcToLocalTime(u32 $a0, u32 $a1);
        //@hle:function{36075567|sceRtc|sceRtcGetDosTime|ggg|int sceRtcGetDosTime(pspTime * date, u32 dosTime)}
        extern int  sceRtcGetDosTime(u32 $a0, u32 $a1);
        //@hle:function{3A807CC8|sceRtc|sceRtcSetTime_t|ggg|int sceRtcSetTime_t(pspTime * date, const time_t time)}
        extern int  sceRtcSetTime_t(u32 $a0, u32 $a1);
        //@hle:function{3F7AD767|sceRtc|sceRtcGetCurrentTick|gg|int sceRtcGetCurrentTick(u64 * tick)}
        extern int  sceRtcGetCurrentTick(u32 $a0);
        //@hle:function{42307A17|sceRtc|sceRtcIsLeapYear|gg|int sceRtcIsLeapYear(int year)}
        extern int  sceRtcIsLeapYear(u32 $a0);
        //@hle:function{4B1B5E82|sceRtc|sceRtcCheckValid|gg|int sceRtcCheckValid(const pspTime * date)}
        extern int  sceRtcCheckValid(u32 $a0);
        //@hle:function{4CFA57B0|sceRtc|sceRtcGetCurrentClock|ggg|int sceRtcGetCurrentClock(pspTime * time, int tz)}
        extern int  sceRtcGetCurrentClock(u32 $a0, u32 $a1);
        //@hle:function{57726BC1|sceRtc|sceRtcGetDayOfWeek|gggg|int sceRtcGetDayOfWeek(int year, int month, int day)}
        extern int  sceRtcGetDayOfWeek(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{62685E98|sceRtc|sceRtcGetLastAdjustedTime|g|??? sceRtcGetLastAdjustedTime()}
        extern int  sceRtcGetLastAdjustedTime();
        //@hle:function{6A676D2D|sceRtc|sceRtcUnregisterCallback|g|??? sceRtcUnregisterCallback()}
        extern int  sceRtcUnregisterCallback();
        //@hle:function{6FF40ACC|sceRtc|sceRtcGetTick|ggg|int sceRtcGetTick(const pspTime * date, u64 * tick)}
        extern int  sceRtcGetTick(u32 $a0, u32 $a1);
        //@hle:function{779242A2|sceRtc|sceRtcConvertLocalTimeToUTC|ggg|int sceRtcConvertLocalTimeToUTC(const u64 * tickLocal, u64 * tickUTC)}
        extern int  sceRtcConvertLocalTimeToUTC(u32 $a0, u32 $a1);
        //@hle:function{7ACE4C04|sceRtc|sceRtcSetWin32FileTime|ggg|int sceRtcSetWin32FileTime(pspTime * date, u64 * win32Time)}
        extern int  sceRtcSetWin32FileTime(u32 $a0, u32 $a1);
        //@hle:function{7D1FBED3|sceRtc|sceRtc_7D1FBED3|g|??? sceRtc_7D1FBED3()}
        extern int  sceRtc_7D1FBED3();
        //@hle:function{7DE6711B|sceRtc|sceRtcFormatRFC2822LocalTime|g|??? sceRtcFormatRFC2822LocalTime()}
        extern int  sceRtcFormatRFC2822LocalTime();
        //@hle:function{7ED29E40|sceRtc|sceRtcSetTick|ggg|int sceRtcSetTick(pspTime * date, const u64 * tick)}
        extern int  sceRtcSetTick(u32 $a0, u32 $a1);
        //@hle:function{81FCDA34|sceRtc|sceRtcIsAlarmed|g|??? sceRtcIsAlarmed()}
        extern int  sceRtcIsAlarmed();
        //@hle:function{9ED0AE87|sceRtc|sceRtcCompareTick|ggg|int sceRtcCompareTick(const u64 * tick1, const u64 * tick2)}
        extern int  sceRtcCompareTick(u32 $a0, u32 $a1);
        //@hle:function{A93CF7D8|sceRtc|sceRtc_A93CF7D8|g|??? sceRtc_A93CF7D8()}
        extern int  sceRtc_A93CF7D8();
        //@hle:function{C2DDBEB5|sceRtc|sceRtc_C2DDBEB5|g|??? sceRtc_C2DDBEB5()}
        extern int  sceRtc_C2DDBEB5();
        //@hle:function{C41C2853|sceRtc|sceRtcGetTickResolution|g|u32 sceRtcGetTickResolution(void)}
        extern int  sceRtcGetTickResolution();
        //@hle:function{C663B3B9|sceRtc|sceRtcFormatRFC2822|g|??? sceRtcFormatRFC2822()}
        extern int  sceRtcFormatRFC2822();
        //@hle:function{CF561893|sceRtc|sceRtcGetWin32FileTime|ggg|int sceRtcGetWin32FileTime(pspTime * date, u64 * win32Time)}
        extern int  sceRtcGetWin32FileTime(u32 $a0, u32 $a1);
        //@hle:function{DFBC5F16|sceRtc|sceRtcParseDateTime|ggg|int sceRtcParseDateTime(u64 * destTick, const char * dateString)}
        extern int  sceRtcParseDateTime(u32 $a0, u32 $a1);
        //@hle:function{E1C93E47|sceRtc|sceRtcGetTime64_t|g|??? sceRtcGetTime64_t()}
        extern int  sceRtcGetTime64_t();
        //@hle:function{E7C27D1B|sceRtc|sceRtcGetCurrentClockLocalTime|gg|int sceRtcGetCurrentClockLocalTime(pspTime * time)}
        extern int  sceRtcGetCurrentClockLocalTime(u32 $a0);
        //@hle:function{F006F264|sceRtc|sceRtcSetDosTime|ggg|int sceRtcSetDosTime(pspTime * date, u32 dosTime)}
        extern int  sceRtcSetDosTime(u32 $a0, u32 $a1);
        //@hle:function{F5FCC995|sceRtc|sceRtc_F5FCC995|g|??? sceRtc_F5FCC995()}
        extern int  sceRtc_F5FCC995();
        //@hle:function{FB3B18CD|sceRtc|sceRtcRegisterCallback|g|??? sceRtcRegisterCallback()}
        extern int  sceRtcRegisterCallback();
    } //@hle:library-end{sceRtc|sceRTC_Service|rtc.prx}
}
#endif