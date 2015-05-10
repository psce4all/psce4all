/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hal.os.UmsThread.h"

__declspec(thread) hal::os::UmsThread    * hal::os::UmsThread::m_Current = 0;
__declspec(thread) hal::os::UmsScheduler * hal::os::UmsScheduler::m_Current = 0;

/// UmsRunnable ///

hal::os::UmsRunnable::~UmsRunnable()
{

}

/// UmsThreadContext ///

hal::os::UmsThreadContext::UmsThreadContext() : m_UmsContext(0)
{
    __DbgCheckLastError("CreateUmsThreadContext", FALSE != ::CreateUmsThreadContext(&m_UmsContext));
}

hal::os::UmsThreadContext::~UmsThreadContext()
{
    __DbgCheckLastError("DeleteUmsThreadContext", FALSE != ::DeleteUmsThreadContext(m_UmsContext));
}

void hal::os::UmsThreadContext::SetThread(UmsThread * Thread)
{
    __DbgCheckLastError("SetUmsThreadInformation", FALSE != ::SetUmsThreadInformation(m_UmsContext, UmsThreadUserContext, &Thread, sizeof(PVOID)));
}

hal::os::UmsThread * hal::os::UmsThreadContext::GetThread(PUMS_CONTEXT UmsContext)
{
    UmsThread * Thread       = NULL;
    ULONG       ReturnLength = 0;
    __DbgCheckLastError("QueryUmsThreadInformation", FALSE != ::QueryUmsThreadInformation(UmsContext, UmsThreadUserContext, &Thread, sizeof(PVOID), &ReturnLength));
    return Thread;
}

BOOL hal::os::UmsThreadContext::IsSuspended(PUMS_CONTEXT UmsContext)
{
    BOOLEAN Suspended    = false;
    ULONG   ReturnLength = 0;
    __DbgCheckLastError("QueryUmsThreadInformation", FALSE != ::QueryUmsThreadInformation(UmsContext, UmsThreadIsSuspended, &Suspended, sizeof(Suspended), &ReturnLength));
    return (FALSE != Suspended);
}

BOOL hal::os::UmsThreadContext::IsTerminated(PUMS_CONTEXT UmsContext)
{
    BOOLEAN Terminated = false;
    ULONG ReturnLength = 0;
    __DbgCheckLastError("QueryUmsThreadInformation", FALSE != ::QueryUmsThreadInformation(UmsContext, UmsThreadIsTerminated, &Terminated, sizeof(Terminated), &ReturnLength));
    return (FALSE != Terminated);
}

/// UmsThreadAttributeList ///

SIZE_T hal::os::UmsThreadAttributeList::GetSize()
{
    SIZE_T Size;
    ::InitializeProcThreadAttributeList(0, 1, 0, &Size);
    return Size;
}

LPPROC_THREAD_ATTRIBUTE_LIST hal::os::UmsThreadAttributeList::GetList(void * Pointer, SIZE_T Size)
{
    if (__DbgCheckLastError("SetUmsThreadInformation", FALSE != ::InitializeProcThreadAttributeList((LPPROC_THREAD_ATTRIBUTE_LIST)Pointer, 1, 0, &Size)))
    {
        return (LPPROC_THREAD_ATTRIBUTE_LIST)Pointer;
    }
    return 0;
}

bool hal::os::UmsThreadAttributeList::Update(LPPROC_THREAD_ATTRIBUTE_LIST ThreadAttributeList, UMS_CREATE_THREAD_ATTRIBUTES * ThreadAttributes)
{
    return __DbgCheckLastError("UpdateProcThreadAttribute", FALSE != ::UpdateProcThreadAttribute(ThreadAttributeList, 0, PROC_THREAD_ATTRIBUTE_UMS_THREAD, ThreadAttributes, sizeof(UMS_CREATE_THREAD_ATTRIBUTES), NULL, NULL));
}

void hal::os::UmsThreadAttributeList::Delete(LPPROC_THREAD_ATTRIBUTE_LIST ThreadAttributeList)
{
    ::DeleteProcThreadAttributeList(ThreadAttributeList);
}

/// UmsCompletionList ///

hal::os::UmsCompletionList::UmsCompletionList() : m_UmsCompletionList(0), m_hEvent(0)
{
    __DbgCheckLastError("CreateUmsCompletionList", FALSE != ::CreateUmsCompletionList(&m_UmsCompletionList));
    __DbgCheckLastError("GetUmsCompletionListEvent", FALSE != ::GetUmsCompletionListEvent(m_UmsCompletionList, &m_hEvent));
}

hal::os::UmsCompletionList::~UmsCompletionList()
{
    __DbgCheckLastError("DeleteUmsCompletionList", FALSE != ::DeleteUmsCompletionList(m_UmsCompletionList));
    __DbgCheckLastError("CloseHandle", FALSE != ::CloseHandle(m_hEvent));
}

void hal::os::UmsCompletionList::DequeueCompletions(bool Waitable)
{
    PUMS_CONTEXT completion = 0;
    __DbgCheckLastError("DequeueUmsCompletionListItems", FALSE != ::DequeueUmsCompletionListItems(m_UmsCompletionList, Waitable ? INFINITE : 0, &completion));
    while (0 != completion)
    {
        UmsThread * thread = UmsThreadContext::GetThread(completion);
        if (0 == thread) hal::dbg::DumpLastError("UmsThreadContext::GetThread returned 0", 0);
        m_Completions.push_back(completion);
        completion = ::GetNextUmsListItem(completion);
    }
}

PUMS_CONTEXT hal::os::UmsCompletionList::GetCompletion()
{
    while (m_Completions.size() > 0)
    {
        PUMS_CONTEXT front = m_Completions.front();
        m_Completions.pop_front();
        if (TRUE == UmsThreadContext::IsTerminated(front))
        {
            UmsThread * TerminatedThread = UmsThreadContext::GetThread(front);
            tracef(hal, "%s: thread %04X terminated", __FUNCTION__, TerminatedThread->m_ThreadId);
            delete TerminatedThread;
            GetThreadCount().Decrement();
            continue;
        }
        else if (TRUE == UmsThreadContext::IsSuspended(front))
        {
            UmsThread * SuspendedThread = UmsThreadContext::GetThread(front);
            tracef(hal, "%s: thread %04X suspended", __FUNCTION__, SuspendedThread->m_ThreadId);
            continue;
        }
        else
        {
            return front;
        }
    }
    return 0;
}

/// UmsThreadList ///

hal::os::UmsCompletionList::UmsThreadCount::UmsThreadCount() : m_Count(0)
{

}

void hal::os::UmsCompletionList::UmsThreadCount::Increment()
{
    m_Count++;
}

void hal::os::UmsCompletionList::UmsThreadCount::Decrement()
{
    m_Count--;
}

bool hal::os::UmsCompletionList::UmsThreadCount::ReadyToExit()
{
    if (m_Count < 0) hal::dbg::DumpLastError("%s returned negative count", 0);
    return (m_Count == 0);
}

/// UmsScheduler ///

hal::os::UmsScheduler::UmsScheduler() : m_CurrentWorker(0)
{

}

hal::os::UmsScheduler::~UmsScheduler()
{

}

void hal::os::UmsScheduler::Run()
{
    emu::log::hal.SetLevel(emu::log::Level::E_OFF);
    UMS_SCHEDULER_STARTUP_INFO UmsStartupInfo;
    UmsStartupInfo.UmsVersion     = UMS_VERSION;
    UmsStartupInfo.SchedulerParam = this;
    UmsStartupInfo.SchedulerProc  = UmsScheduler::UmsSchedulerProc;
    UmsStartupInfo.CompletionList = m_CompletionList.GetUmsCompletionList();
    __DbgCheckLastError("EnterUmsSchedulingMode", FALSE != ::EnterUmsSchedulingMode(&UmsStartupInfo));
}

void hal::os::UmsScheduler::Dispatch()
{
    for (;;)
    {
        bool Waitable = !m_CompletionList.m_Completions.size();
    loop:
        m_CompletionList.DequeueCompletions(Waitable);
        PUMS_CONTEXT Context = m_CompletionList.GetCompletion();
        if (0 != Context)
        {
            UmsThread * ReadyThread = UmsThreadContext::GetThread(Context);
            m_CurrentWorker = ReadyThread;
            for (;;)
            {
                tracef(hal, "%s: thread %04X", __FUNCTION__, ReadyThread->m_ThreadId);
                ::ExecuteUmsThread(Context);
            }
        }
        if (!m_CompletionList.GetThreadCount().ReadyToExit())
        {
            tracef(hal, "%s: waiting for ready threads...", __FUNCTION__);
            goto loop;
        }
        else
        {
            break;
        }
    }
}

void hal::os::UmsScheduler::OnUmsSchedulerStartup()
{
    Dispatch();
}

void hal::os::UmsScheduler::OnUmsThreadBlocked()
{
    if (m_CurrentWorker) tracef(hal, "%s: thread %04X blocked on a system call", __FUNCTION__, m_CurrentWorker->m_ThreadId);
    else                 tracef(hal, "%s: thread ???? blocked on a system call", __FUNCTION__);
    Dispatch();
}

void hal::os::UmsScheduler::OnUmsThreadInterrupted()
{
    if (m_CurrentWorker) tracef(hal, "%s: thread %04X blocked on a trap or an interrupt", __FUNCTION__, m_CurrentWorker->m_ThreadId);
    Dispatch();
}

VOID __stdcall hal::os::UmsScheduler::UmsSchedulerProc(UMS_SCHEDULER_REASON Reason, ULONG_PTR ActivationPayload, PVOID SchedulerParam)
{
    switch (Reason)
    {
        case UmsSchedulerStartup:
        {
            UmsScheduler * Scheduler = ((UmsScheduler *)SchedulerParam);
            m_Current = Scheduler;
            return Scheduler->OnUmsSchedulerStartup();
        }

        case UmsSchedulerThreadYield:
        {
            PUMS_CONTEXT context = (PUMS_CONTEXT)ActivationPayload;
            UmsThread * that = UmsThreadContext::GetThread(context);
            return that->OnUmsThreadYield(SchedulerParam);
        }

        case UmsSchedulerThreadBlocked:
        {
            if (ActivationPayload & 1)
            {
                return m_Current->OnUmsThreadBlocked();
            }
            else
            {
                return m_Current->OnUmsThreadInterrupted();
            }
        }
    }
}

/// UmsThread ///

hal::os::UmsThread::UmsThread(struct UmsScheduler * Scheduler, Runnable * Worker) : m_Scheduler(Scheduler), m_Runnable(Worker)
{
    SIZE_T                       l_AttrSize = 0;
    LPPROC_THREAD_ATTRIBUTE_LIST l_AttrList;
    UMS_CREATE_THREAD_ATTRIBUTES l_UmsAttribs;

    m_Context.SetThread(this);

    l_AttrSize = UmsThreadAttributeList::GetSize();
    l_AttrList = UmsThreadAttributeList::GetList(_malloca(l_AttrSize), l_AttrSize);

    l_UmsAttribs.UmsVersion        = UMS_VERSION;
    l_UmsAttribs.UmsContext        = m_Context.GetUmsContext();
    l_UmsAttribs.UmsCompletionList = Scheduler->GetUmsCompletionList();
    UmsThreadAttributeList::Update(l_AttrList, &l_UmsAttribs);

    m_hThread = ::CreateRemoteThreadEx(::GetCurrentProcess(), NULL, 0, &UmsThreadProc, this, CREATE_SUSPENDED, l_AttrList, &m_ThreadId);
    __DbgCheckLastError("CreateRemoteThreadEx", 0 != m_hThread);

    UmsThreadAttributeList::Delete(l_AttrList);

    _freea(l_AttrList);
}

hal::os::UmsThread::~UmsThread()
{
    __DbgCheckLastError("CloseHandle", TRUE == ::CloseHandle(m_hThread));
}

void hal::os::UmsThread::Start()
{
    ::ResumeThread(m_hThread);
}

DWORD hal::os::UmsThread::Run()
{
    if (m_Runnable) m_Runnable->Run();

    return 0; // Terminate UMS thread
}

DWORD WINAPI hal::os::UmsThread::UmsThreadProc(LPVOID lpThreadParameter)
{
    m_Current = (UmsThread *)lpThreadParameter;
    return ((UmsThread *)lpThreadParameter)->Run();
}

void hal::os::UmsThread::SwitchTo()
{
    for (;;)
    {
        if (0 == ::ExecuteUmsThread(m_Context.GetUmsContext()))
        {
            DWORD error = ::GetLastError();
            if (ERROR_RETRY != error)
            {
                hal::dbg::DumpLastError("ExecuteUmsThread", error);
                break;
            }
        }
    }
}

void hal::os::UmsThread::OnUmsThreadYield(void * Parameter)
{
    tracef(hal, "%s: thread %04X yielded control", __FUNCTION__, m_ThreadId);
    Scheduler()->m_CompletionList.m_Completions.push_back(this->m_Context.GetUmsContext());
    Scheduler()->Dispatch();
}

/// test ///

struct test_Runnable1 : hal::os::Runnable
{
    virtual void Run()
    {
        tracef(hal, "%s: thread %04X creating event...", __FUNCTION__, ::GetCurrentThreadId());
        HANDLE Event = ::CreateEventA(0, TRUE, FALSE, "test_UmsRunnable");

        tracef(hal, "%s: thread %04X sleeping 5s...", __FUNCTION__, ::GetCurrentThreadId());
        ::Sleep(5000);

        tracef(hal, "%s: thread %04X signaling event...", __FUNCTION__, ::GetCurrentThreadId());
        ::SetEvent(Event);

        tracef(hal, "%s: thread %04X sleeping 5s...", __FUNCTION__, ::GetCurrentThreadId());
        ::Sleep(4000);

        tracef(hal, "%s: thread %04X closing event...", __FUNCTION__, ::GetCurrentThreadId());
        ::CloseHandle(Event);

        tracef(hal, "%s: thread %04X terminating...", __FUNCTION__, ::GetCurrentThreadId());
    }
};

struct test_Runnable2 : hal::os::Runnable
{
    virtual void Run()
    {
        tracef(hal, "%s: thread %04X sleeping 2s...", __FUNCTION__, ::GetCurrentThreadId());
        ::Sleep(2000);

        tracef(hal, "%s: thread %04X opening event...", __FUNCTION__, ::GetCurrentThreadId());
        HANDLE Event = ::OpenEventA(EVENT_ALL_ACCESS, TRUE, "test_UmsRunnable");

        tracef(hal, "%s: thread %04X waiting event...", __FUNCTION__, ::GetCurrentThreadId());
        ::WaitForSingleObject(Event, INFINITE);

        tracef(hal, "%s: thread %04X closing event...", __FUNCTION__, ::GetCurrentThreadId());
        ::CloseHandle(Event);

        tracef(hal, "%s: thread %04X terminating...", __FUNCTION__, ::GetCurrentThreadId());
    }
};

struct test_Runnable3 : hal::os::Runnable
{
    virtual void Run()
    {
        tracef(hal, "%s: thread %04X sleeping 1s...", __FUNCTION__, ::GetCurrentThreadId());
        ::Sleep(1000);

        tracef(hal, "%s: thread %04X yielding control...", __FUNCTION__, ::GetCurrentThreadId());
        ::UmsThreadYield((PVOID)::GetCurrentThreadId());

        tracef(hal, "%s: thread %04X terminating...", __FUNCTION__, ::GetCurrentThreadId());
    }
};

void hal::os::UmsScheduler::Startup()
{
    test_Runnable1 * r1 = new test_Runnable1;
    test_Runnable2 * r2 = new test_Runnable2;
    test_Runnable3 * r3 = new test_Runnable3;
    QueueWorker(r1)->Start();
    QueueWorker(r2)->Start();
    QueueWorker(r3)->Start();
    StartRunnable(this);
}

void hal::os::UmsScheduler::Cleanup()
{
    Thread::Join();
}

hal::os::UmsThread * hal::os::UmsScheduler::QueueWorker(Runnable * Worker)
{
    m_CompletionList.GetThreadCount().Increment();
    return new UmsThread(this, Worker);
}

