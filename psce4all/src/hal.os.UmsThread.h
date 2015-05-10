/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "emu.h"

#include "hal.dbg.h"
#include "hal.hmm.h"
#include "hal.os.win32.h"
#include "hal.os.Thread.h"

#include <winbase.h>

namespace hal
{
    namespace os
    {
        enum ThreadPriority
        {
            Normal = 1, High = 2
        };

        struct UmsRunnable
        {
            virtual             ~UmsRunnable();
            virtual void         Run() = 0;
        };

        struct UmsThreadContext
        {
            PUMS_CONTEXT m_UmsContext;

            UmsThreadContext();

            __forceinline PUMS_CONTEXT GetUmsContext()
            {
                return m_UmsContext;
            }

            virtual ~UmsThreadContext();

            void SetThread(struct UmsThread * Thread);

            static struct UmsThread * GetThread(PUMS_CONTEXT UmsContext);

            static BOOL IsSuspended(PUMS_CONTEXT UmsContext);

            static BOOL IsTerminated(PUMS_CONTEXT UmsContext);
        };

        struct UmsThreadAttributeList
        {
            static SIZE_T GetSize();

            static LPPROC_THREAD_ATTRIBUTE_LIST GetList(void * Pointer, SIZE_T Size);

            static bool Update(LPPROC_THREAD_ATTRIBUTE_LIST ThreadAttributeList, UMS_CREATE_THREAD_ATTRIBUTES * ThreadAttributes);

            static void Delete(LPPROC_THREAD_ATTRIBUTE_LIST ThreadAttributeList);
        };

        struct UmsCompletionList
        {
            struct UmsThreadCount
            {
                int m_Count;
                UmsThreadCount();
                void Increment();
                void Decrement();
                bool ReadyToExit();
            };

            PUMS_COMPLETION_LIST     m_UmsCompletionList;
            HANDLE                   m_hEvent;
            UmsThreadCount           m_ThreadCount;
            std::deque<PUMS_CONTEXT> m_Completions;

            UmsCompletionList();

            virtual ~UmsCompletionList();

            __forceinline PUMS_COMPLETION_LIST GetUmsCompletionList()
            {
                return m_UmsCompletionList;
            }

            __forceinline UmsThreadCount & GetThreadCount()
            {
                return m_ThreadCount;
            }

            __forceinline HANDLE GetEvent()
            {
                return m_hEvent;
            }

            PUMS_CONTEXT GetCompletion();

            void DequeueCompletions(bool Waitable);
        };

        struct UmsScheduler : hal::os::Runnable, hal::os::Thread, hal::hmm::Allocator< UmsScheduler >
        {
            static __declspec(thread) UmsScheduler * m_Current;
            UmsCompletionList                        m_CompletionList;
            HANDLE                                   m_CompletionListEvent;
            struct UmsThread                       * m_CurrentWorker;

            __forceinline PUMS_COMPLETION_LIST GetUmsCompletionList()
            {
                return m_CompletionList.GetUmsCompletionList();
            }

            virtual struct UmsThread * QueueWorker(Runnable * Worker);

            virtual void Dispatch();

            /**/     UmsScheduler();
            virtual ~UmsScheduler();

            void Run();
            void Startup();
            void Cleanup();

            virtual void OnUmsSchedulerStartup();
            virtual void OnUmsThreadInterrupted();
            virtual void OnUmsThreadBlocked();

            static VOID __stdcall UmsSchedulerProc(UMS_SCHEDULER_REASON Reason, ULONG_PTR ActivationPayload, PVOID SchedulerParam);
        };

        __weaksymbol UmsScheduler test_UmsScheduler;

        struct UmsThread : hal::hmm::Allocator< UmsThread >
        {
            static _declspec(thread) UmsThread * m_Current;
            struct UmsScheduler                * m_Scheduler;
            Runnable                           * m_Runnable;
            UmsThreadContext                     m_Context;
            HANDLE                               m_hThread;
            DWORD                                m_ThreadId;

            UmsThread(struct UmsScheduler * Scheduler, Runnable * runnable);

            virtual ~UmsThread();

            __forceinline UmsScheduler * Scheduler()
            {
                return m_Scheduler;
            }

            void Start();

            virtual DWORD Run();

            void SwitchTo();

            virtual void OnUmsThreadYield(void * Parameter);

            static DWORD WINAPI UmsThreadProc(LPVOID lpThreadParameter);
        };
    }
}
