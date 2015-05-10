/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

namespace hal
{
    namespace os
    {
        // note that in Benaphore/RecursiveBenaphore _InterlockedIncrement and _InterlockedDecrement are systematically replaced with
        // _InterlockedExchangeAdd as they all issue the same instruction XADD in the final assembly code but _InterlockedIncrement
        // and _InterlockedDecrement issued more instructions because they return the value *AFTER* addition whereas XADD returns
        // the value *BEFORE* addition. As a result, _InterlockedExchangeAdd must be used instead to avoid superfluous instructions.

        // TO DO OR NOT: Semaphore can also be replaced with a manual-reset Event

        struct Benaphore /* link:http://preshing.com/20120226/roll-your-own-lightweight-mutex/ */
        {
            /**/             Benaphore(bool initialize = true)
            {
                if (initialize) Create();
            }

            /**/            ~Benaphore()
            {
                Delete();
            }

            void             Create()
            {
                m_counter = 0;
                ::NtCreateSemaphore(&m_semaphore, SEMAPHORE_ALL_ACCESS, NULL, 0, 1);
            }

            void             Delete()
            {
                if (m_semaphore) ::NtClose(m_semaphore); // CloseHandle(m_semaphore);
                m_semaphore = 0;
            }

            void             Enter()
            {
                if (_InterlockedExchangeAdd(&m_counter, 1) > 0)
                {
                    ::NtWaitForSingleObject(m_semaphore, FALSE, 0); // WaitForSingleObject(m_semaphore, INFINITE);
                }
            }

            void             Leave()
            {
                if (_InterlockedExchangeAdd(&m_counter, -1) > 1)
                {
                    ::ReleaseSemaphore(m_semaphore, 1, NULL);
                }
            }

            bool             TryEnter()
            {
                return !_InterlockedCompareExchange(&m_counter, 1, 0);
            }

        private:
            LONG             m_counter;
            HANDLE           m_semaphore;
        };

        struct RecursiveBenaphore /* link:http://preshing.com/20120305/implementing-a-recursive-mutex/ */
        {
            /**/             RecursiveBenaphore(bool initialize = true)
            {
                if (initialize) Create();
            }

            /**/            ~RecursiveBenaphore()
            {
                Delete();
            }

            void             Create()
            {
                m_counter   = 0;
                m_owner     = 0;
                m_recursion = 0;
                m_semaphore = 0;
                if (!m_semaphore) ::NtCreateSemaphore(&m_semaphore, SEMAPHORE_ALL_ACCESS, NULL, 0, 1);
            }

            void             Delete()
            {
                if (m_semaphore) ::NtClose(m_semaphore); // CloseHandle(m_semaphore);
                m_semaphore = 0;
            }

            void             Enter()
            {
                DWORD_PTR owner = _GetCurrentThreadId();
                if (_InterlockedExchangeAdd(&m_counter, 1) > 0)
                {
                    if (owner != m_owner)
                    {
                        ::NtWaitForSingleObject(m_semaphore, FALSE, 0); // WaitForSingleObject(m_semaphore, INFINITE);
                    }
                }
                m_owner = owner;
                m_recursion++;
            }

            void             Leave()
            {
                DWORD recursion = --m_recursion;
                if (recursion == 0)
                {
                    m_owner = 0;
                }
                DWORD result = _InterlockedExchangeAdd(&m_counter, -1);
                if (result > 1)
                {
                    if (recursion == 0)
                    {
                        ::NtReleaseSemaphore(m_semaphore, 1, NULL); //::ReleaseSemaphore(m_semaphore, 1, NULL);
                    }
                }
            }

            bool             TryEnter()
            {
                DWORD_PTR owner = _GetCurrentThreadId();
                if (m_owner == owner)
                {
                    _InterlockedExchangeAdd(&m_counter, 1);
                }
                else
                {
                    bool entered = !_InterlockedCompareExchange(&m_counter, 1, 0);
                    if (!entered)
                    {
                        return false;
                    }
                    m_owner = owner;
                }
                m_recursion++;
                return true;
            }

        private:
            LONG             m_counter;
            DWORD_PTR        m_owner;
            DWORD            m_recursion;
            HANDLE           m_semaphore;
        };

#if   CRITICALSECTION_USE_WIN32_CRITICALSECTION
        typedef win32::CriticalSection CriticalSection;
#elif CRITICALSECTION_USE_RECURSIVE_BENAPHORE
        typedef RecursiveBenaphore     CriticalSection;
#endif
    }
}
