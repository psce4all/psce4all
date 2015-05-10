/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

char const * hle::kd::Timer::m_object_type  = "KernelTimer";
char const * hle::kd::Delay::m_object_type  = "KernelDelay";
//char const *hle::kd::Alarm::m_object_type = "KernelAlarm";
//char const *hle::kd::VTimer::m_object_type = "KernelVTimer";

/// KernelTimerList /////////////////////////////////////////////////////////

void hle::kd::TimerList::AddTimerToList(Timer * timer)
{
    u64 time = timer->m_time;
    Timer * next_timer;
    for (next_timer = this->First(); next_timer; next_timer = this->Next(next_timer))
    {
        if (time < next_timer->m_time)
        {
            timer->InsertInListBefore(next_timer);
            return;
        }
    }
    this->Append(timer);
}

void hle::kd::TimerList::RemoveTimerFromList(Timer * timer)
{
    timer->RemoveFromList();
}

void hle::kd::TimerList::Initialize()
{
#if 0
    theKernelScheduler.m_unk_690 = 1;
    theKernelScheduler.m_unk_694 = 1;

    theKernelScheduler.m_unk_688 = 100 /* µs */;
    theKernelScheduler.m_unk_68C = theKernelScheduler.m_unk_688 << 1;

    theKernelScheduler.m_sceKernelGetSystemTimeLow = 0 /* &sceKernelGetSystemTimeLow */;

    theKernelScheduler.m_timer_intr = 0x13;

    //*(0xBC600008) = 0x30;
    //*(0xBC60000C) = 0x1;
    //*(0xBC600010) = 0;
    //_SYNC();

    sceKernelRegisterIntrHandler(theKernelScheduler.m_timer_intr, 0x1, DispatchTimers, &gInfo, 0);

    sceKernelSetIntrLevel(theKernelScheduler.m_timer_intr, 0x2);

    CLEAR_LIST(gInfo.unk_604);

    CLEAR_LIST(gInfo.timers);

    gInfo.unk_5F8 = 0;

    int intr = sceKernelCpuSuspendIntr();

    uidControlBlock *cb;
    ASSERT(sceKernelCreateUID(uidTimerType, "SceThreadmanSysTimerOVF", 0, &cb) <= 0);

    TimerInfo *timer = UID_INFO(TimerInfo, cb, uidTimerType); //t6
    timer->time.low = 0xF0000000;
    timer->time.hi = 0;

    ADD_TO_LIST(timer, gInfo.timers);

    gInfo.unk_430.low = 0;
    gInfo.unk_430.hi = 0;

    gInfo.unk_438.low = timer->time.low;

    for(i = 31; i >= 0; i--)
    {
        ASSERT(sceKernelCreateUID(uidDelayType, "SceThreadmanDelay", 0, &cb) <= 0);

        AddToDelayList(cb);
    }

    *(0xBC600004) = gInfo.unk_438.low;
    _SYNC();

    *(0xBC600000) = 0;
    _SYNC();

    sceKernelSetPrimarySyscallHandler(0x18, loc_0000DDB0);

    sceKernelRegisterSuspendHandler(0x18, sub_0000DDC8, 0);

    sceKernelRegisterResumeHandler(0x18, loc_0000DE3C, 0);

    sceKernelEnableIntr(gInfo.unk_72C);

    sceKernelCpuResumeIntr(intr);
#endif
}

bool hle::kd::TimerList::DispatchTimers()
{
    bool result = true;

    //int state = sceKernelCpuSuspendIntr();

    g_scheduler->m_unk_430 = g_scheduler->m_unk_438;

    u64 time = theSysClock->Get();

    Timer * timer, * next_timer = 0;

    for (timer = this->First(); timer; timer = next_timer)
    {
        next_timer = this->Next(timer);

        if (timer->m_time > time)
        {
            result = false;

            break;
        }

        this->RemoveTimerFromList(timer);

        if (timer->CheckExactType(Delay::m_object_type))
        {
            Delay * delay = static_cast< Delay * >(timer);

            Thread * this_thread = delay->m_thread;
            if (this_thread)
            {
                this_thread->ReleaseWaitingThread(1, 0);
            }

            g_scheduler->m_delays.Release(delay);
        }
//        else if (timer->CheckExactType(KernelAlarm::m_object_type))
//        {
//            theKernelScheduler.m_timer_id = timer->GetUid();
//
//            KernelAlarm *alarm = static_cast< KernelAlarm * >(timer);
//
//            al_Context &context = theKernelScheduler.m_current_thread->m_thread_context;
//
//            if (alarm->m_uhandler)
//            {
//                u32 old_gp = context.gpr[ALLEGREX_GP];
//                context.gpr[ALLEGREX_GP] = alarm->m_gp_reg;
//
//                //result = sceKernelCallUserIntrHandler(alarm->m_arg, 0, 0, 0, alarm->m_handler, sceKernelGetUserIntrStack());
//
//                context.gpr[ALLEGREX_GP] = old_gp;
//            }
//            else
//            {
//                sceKernelCpuResumeIntr(state);
//
//                result = alarm->m_khandler((void *)alarm->m_cookie);
//
//                state = sceKernelCpuSuspendIntr();
//            }
//
//            theKernelScheduler.m_timer_id = 0;
//
//            if (!result)
//            {
//                timer->m_unk_10 = 1;
//
//                //theKernelScheduler._AddThreadToCleanupQueue(timer->GetUid()); //???
//            }
//            else
//            {
//                timer->m_time += (u64)(result < 100 ? 100 : result);
//
//                this->AddTimerToList(timer);
//            }
//        }
//        else if (timer->CheckExactType(KernelVTimer::m_object_type))
//        {
//            KernelVTimer *vtimer = static_cast< KernelVTimer * >(timer);
//
//            (void)vtimer;
//
//            //result = sub_0000DF4C(cb);
//#if 0
//            if (result)
//            {
//                v1 = MAX(result, info->unk_688);
//
//                t1 = s2 + v1;
//                t3 = 0;
//                s4 = t1 < v1;
//                t9 = s3 + t3;
//                t8 = t9 + s4;
//                a0 = t8 >> 0;
//                timer->time.hi = a0;
//                s6 = s1 + 0xC;
//                v0 = 0;
//                timer->time.low = t1;
//                t2 = 0;
//                t4 = v1;
//                t6 = vtimer->schedule.low;
//                t7 = vtimer->schedule.hi;
//                a0 = timer;
//                t0 = v0 + t6;
//                t5 = t7 << 0;
//                s3 = t0 < t6;
//                s2 = t5 + t2;
//                v1 = t0 + v1;
//                a3 = s2 + s3;
//                a2 = v1 < t4;
//                timer = a3 + t3;
//                fp = timer + a2;
//                s7 = fp >> 0;
//                vtimer->schedule.low = v1;
//                vtimer->schedule.hi = s7;
//
//                AddToTimerList(timer);
//            }
//            else
//            {
//                vtimer->handler = 0;
//            }
//#endif
//        }
        else
        {
            timer->m_time = time + 0x00000000F0000000ULL;

            this->AddTimerToList(timer);
        }
    }

    RescheduleTimers();

    //sceKernelCpuResumeIntr(state);

    return result;
}

void hle::kd::TimerList::RescheduleTimers()
{
    Timer * timer = First();
    u64 next_time = timer->m_time + 200;
    do
    {
        if (next_time <= timer->m_time)
        {
            next_time = timer->m_time;
            break;
        }
    }
    while (timer = Next(timer));

    u64 current_time = theSysClock->Get();
    if (next_time - current_time < 200)
    {
        next_time = current_time + 200;
    }

    g_scheduler->m_unk_438 = next_time;

    theSysClock->Set(next_time);
}

/// KernelTimer /////////////////////////////////////////////////////////////

void hle::kd::Timer::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

hle::kd::Timer::Timer(char const * name) : Object(name)
{
    this->Clear();
    this->m_unk_10 = 0;
}

hle::kd::Timer::~Timer()
{
    if (this->m_next != this)
    {
        this->RemoveFromList();
    }
}

hle::kd::Timer * hle::kd::Timer::Create(u64 time)
{
    Timer * ovf = new Timer("SceThreadmanSysTimerOVF");

    ovf->m_time   = time;
    ovf->m_unk_10 = 0;

    return ovf;
}

int hle::kd::Timer::Delete(int /*intr*/)
{
    delete this;

    return SCE_KERNEL_ERROR_OK;
}

/// KernelDelay /////////////////////////////////////////////////////////////

void hle::kd::Delay::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

hle::kd::Delay::Delay() : Timer("SceThreadmanDelay"), m_thread(0)
{
}

hle::kd::Delay::~Delay()
{
}


hle::kd::Delay * hle::kd::Delay::Create(u64 timeout, int * result, Thread * delayed_thread)
{
    Delay * delay                    = g_scheduler->m_delays.Acquire();
    delay->m_time                    = timeout;
    delay->m_thread                  = delayed_thread;
    delayed_thread->m_timeout_object = delay;
    delayed_thread->m_timeout        = result;

    g_scheduler->m_timers.AddTimerToList(delay);
    g_scheduler->m_timers.RescheduleTimers();

    return delay;
}

int hle::kd::Delay::Delete(int intr)
{
    Cancel();

    return Timer::Delete(intr);
}

void hle::kd::Delay::Cancel()
{
    if (this->m_thread)
    {
        if (this->m_thread->m_timeout)
        {
            *this->m_thread->m_timeout = u32(u64(this->m_time) - theSysClock->Get());
        }

        this->m_thread->m_timeout_object = 0;

        this->RemoveFromList();

        g_scheduler->m_delays.Release(this);
        g_scheduler->m_timers.RescheduleTimers();
    }
}

/// KernelDelayList /////////////////////////////////////////////////////////

hle::kd::DelayList::DelayList() : TimerList()
{
    // reserve 32 delay objects at first
    for (int i = 0; i < 32; ++i)
    {
        Release(new Delay);
    }
}

hle::kd::DelayList::~DelayList()
{
    Timer * timer;
    while (timer = First())
    {
        delete timer;
    }
}

void hle::kd::DelayList::Release(Delay * delay)
{
    delay->m_thread = 0;

    // recycle this delay object
    Append(delay);
}

hle::kd::Delay * hle::kd::DelayList::Acquire()
{
    // try to acquire a recycled delay object
    Delay * delay = static_cast< Delay * >(First());
    if (delay)
    {
        delay->RemoveFromList();
        return delay;
    }
    // if none, get a new delay object
    return new Delay;
}

#if 0

/// KernelAlarm /////////////////////////////////////////////////////////////

void KernelAlarm::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelAlarm::KernelAlarm(char const *name, u32 uhandler, u32 cookie)
:   KernelTimer(name)
,   m_uhandler(uhandler)
,   m_khandler(0)
,   m_cookie(cookie)
{
}

KernelAlarm::KernelAlarm(char const *name, SceKernelAlarmHandler khandler, void * /*cookie*/)
:   KernelTimer(name)
,   m_uhandler(0)
,   m_khandler(khandler)
,   m_cookie(0) //TODO (u32)cookie
{
}

KernelAlarm::~KernelAlarm()
{
}

SceUID KernelAlarm::Set(u64 delta, SceKernelAlarmHandler khandler, void *cookie)
{
    int state = sceKernelCpuSuspendIntr();

    KernelAlarm *alarm = __new KernelAlarm("SceThreadmanAlarm", khandler, cookie);

    SceUID result = alarm->GetUid();

    if ((int)result <= 0)
    {
        __delete alarm;

        sceKernelCpuResumeIntr(state);

        return result;
    }

    alarm->m_time = KernelSysClock::Get() + delta;

    //u32 *mod = (u32 *)sceKernelFindModuleByAddress(s2);
    //alarm->m_gp_reg = mod ? mod[0x68 / 4] : gp;

    theKernelScheduler.m_timers.AddTimerToList(alarm);

#if 0
    sub_0000B304();
#endif
    sceKernelCpuResumeIntr(state);

    return result;
}

SceUID KernelAlarm::Set(u64 delta, u32 uhandler, u32 cookie)
{
    int state = sceKernelCpuSuspendIntr();

    KernelAlarm *alarm = __new KernelAlarm("SceThreadmanAlarm", uhandler, cookie);

    SceUID result = alarm->GetUid();

    if ((int)result <= 0)
    {
        __delete alarm;

        sceKernelCpuResumeIntr(state);

        return result;
    }

    alarm->m_time = SysClock::Get() + delta;

    //u32 *mod = (u32 *)sceKernelFindModuleByAddress(s2);
    //alarm->m_gp_reg = mod ? mod[0x68 / 4] : gp;

    theKernelScheduler.m_timers.AddTimerToList(alarm);

#if 0
    sub_0000B304();
#endif
    sceKernelCpuResumeIntr(state);

    return result;
}

SceUID KernelAlarm::Set(SceUInt delta, SceKernelAlarmHandler khandler, void *cookie)
{
    return Set(u64(delta), khandler, cookie);
}

SceUID KernelAlarm::Set(SceUInt delta, u32 uhandler, u32 cookie)
{
    if (!uhandler)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_ADDR;
    }

    return Set(u64(delta), uhandler, cookie);
}

SceUID KernelAlarm::SetSysClock(SceKernelSysClock *delta, SceKernelAlarmHandler khandler, void *cookie)
{
    if (!delta)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_ADDR;
    }

    return Set(u64(*delta), khandler, cookie);
}

SceUID KernelAlarm::SetSysClock(SceKernelSysClock *delta, u32 uhandler, u32 cookie)
{
    if (!delta || !uhandler)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_ADDR;
    }

    return Set(u64(*delta), uhandler, cookie);
}

int KernelAlarm::Cancel()
{
    if (this->GetUid() == theKernelScheduler.m_timer_id)
    {
        return SCE_KERNEL_ERROR_UNKNOWN_ALMID;
    }

    int state = sceKernelCpuSuspendIntr();

    Timer *timer = static_cast< Timer * >(this);

    if (timer->m_unk_10)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_UNKNOWN_ALMID;
    }

    timer->RemoveFromList();

    if (!sceKernelIsIntrContext())
    {
        //ASSERT(sceKernelDeleteUID(alarmid) <= 0);
    }

    timer->m_unk_10 = 1;

    int result = 0; //sub_0000F0DC(alarmid);

    if (result == 0)
    {
        theKernelScheduler.m_timers.RescheduleTimers(); //sub_0000B304();
    }

    sceKernelCpuResumeIntr(state);

    return result;
}

int KernelAlarm::ReferStatus(SceKernelAlarmInfo *info)
{
    (void)info;
    return 0;
}

/// KernelVTimer ////////////////////////////////////////////////////////////

void KernelVTimer::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

#endif

/// KernelSysClock //////////////////////////////////////////////////////////

hle::kd::SysClock * theSysClock = 0;

bool hle::kd::SysClock::Handle()
{
    return g_scheduler->m_timers.DispatchTimers();
}

hle::kd::SysClock::SysClock()
{
    u64 time = Get();
    g_scheduler->m_timers.AddTimerToList(Timer::Create(time + 0x00000000F0000000ULL));
    g_scheduler->m_unk_430 = time;
    g_scheduler->m_unk_438 = time;
    m_current_time = time;
    m_compare_time = time;
}

hle::kd::SysClock::~SysClock()
{
}