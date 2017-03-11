/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "emu.h"

#include "hal.os.win32.h"

namespace hal
{
    namespace os
    {
        struct Runnable
        {
            virtual             ~Runnable() {}
            virtual void         Run() = 0;
            virtual unsigned int StackSize() { return 0; }
        };

        struct Thread
        {
            typedef HANDLE Handle;

            enum { ThreadStackSize = 0 };

            struct Id
            {
                unsigned m_id;

                Id() : m_id(0) {}
                Id(unsigned id) : m_id(id) {}

                bool operator == (Id const & rhs) const { return m_id == rhs.m_id; }
                bool operator != (Id const & rhs) const { return m_id != rhs.m_id; }
                bool operator <= (Id const & rhs) const { return m_id <= rhs.m_id; }
                bool operator >= (Id const & rhs) const { return m_id >= rhs.m_id; }
                bool operator <  (Id const & rhs) const { return m_id <  rhs.m_id; }
                bool operator >  (Id const & rhs) const { return m_id >  rhs.m_id; }
            };

            Id     m_id;
            Handle m_handle;


            /**/     Thread(Runnable * runnable)         { Start(runnable); }
            template< typename F >
            /**/     Thread(F function)                  { Start(__new Function0$< F >(function)); }
            template< typename F, typename A >
            /**/     Thread(F function, A argument)      { Start(__new Function1$< F, A >(function, argument)); }
            /**/     Thread() : m_handle(0)              { }
            /**/     Thread(Thread const &) = delete;
            /**/     Thread(Thread && rhs) : m_handle(0) { Swap(rhs); }

            virtual ~Thread()                            { if (Joinable()) Detach(); }

            Thread & operator = (Thread const &) = delete;
            Thread & operator = (Thread && rhs)
            {
                if (Joinable()) Detach();
                Swap(rhs);
                return *this;
            }

            Handle     GetHandle() const { return m_handle; }
            Id         GetId()     const { return m_id; }

            operator Thread::Id() const { return m_id; }

            bool Joinable() const { return m_id != Id(); }
            bool Join(int * exit_code = 0)
            {
                bool result;
                if (m_handle)
                {
                    result = NT_SUCCESS(::NtWaitForSingleObject(m_handle, FALSE, 0));
                    if (result)
                    {
                        unsigned long code;
                        result = FALSE != ::GetExitCodeThread(m_handle, &code);
                        if (result)
                        {
                            if (exit_code) *exit_code = code;
                            result = Detach();
                        }
                    }
                    m_handle = 0;
                    m_id     = 0;
                }
                else
                {
                    result = false;
                }
                return result;
            }

            bool Detach()
            {
                bool result;
                if (m_handle)
                {
                    result = NT_SUCCESS(::NtClose(m_handle));
                    m_handle = 0;
                    m_id     = 0;
                }
                else
                {
                    result = false;
                }
                return result;
            }

            void Swap(Thread & rhs)
            {
                std::swap(m_id,     rhs.m_id);
                std::swap(m_handle, rhs.m_handle);
            }

            void StartRunnable(Runnable * runnable)
            {
                m_handle = (Handle)_beginthreadex(NULL, runnable->StackSize(), &RunWithoutDelete, runnable, 0, &m_id.m_id);
            }

            template< typename F >
            void Start(F * function)
            {
                m_handle = (Handle)_beginthreadex(NULL, ThreadStackSize, &RunAndDelete$< F >, function, 0, &m_id.m_id);
            }

            void WaitUntilStarted()
            {
                // WARNING: this method should only be called *AFTER* calling 'Start' method
                // this method ensures the id of the started thread is set before leaving here
                while (0 == (unsigned int volatile *)(&m_id.m_id))
                {
                    Yield();
                }
            }

            static void Yield()
            {
                ::NtYieldExecution();
            }

            static Thread::Id CurrentId()
            {
                return (unsigned int)_GetCurrentThreadId();
            }

        private:
            template< typename F >
            struct Function0$
            {
                F m_function;

                Function0$(F function) : m_function(function) {}

                void Run() { function(); }
            };

            template< typename F, typename A >
            struct Function1$ : Function0$< F >
            {
                A m_argument;

                Function1$(F function, A argument) : Function0$< F >(function), m_argument(argument) {}

                void Run() { m_function(m_argument); }
            };

            template< typename F >
            static unsigned __stdcall RunAndDelete$(void * p)
            {
                static_cast< F * >(p)->Run();
                __delete static_cast< F * >(p);
                return 0;
            }

            static unsigned __stdcall RunWithoutDelete(void * p)
            {
                static_cast< Runnable * >(p)->Run();
                return 0;
            }
        };

        struct ScopedThreadPriority
        {
            /**/        ScopedThreadPriority(int new_priority = THREAD_PRIORITY_TIME_CRITICAL) : old_priority(::GetThreadPriority((HANDLE)0xFFFFFFFEull))
            {
                ::SetThreadPriority((HANDLE)0xFFFFFFFEull, new_priority);
            }

            /**/       ~ScopedThreadPriority()
            {
                ::SetThreadPriority((HANDLE)0xFFFFFFFEull, old_priority);
            }

            operator bool() const { return true; }

        private:
            int old_priority;
        };

#define __ThreadPriority(priority) if (::hal::os::ScopedThreadPriority const __stp__ = ::hal::os::ScopedThreadPriority(priority))
    }
}
