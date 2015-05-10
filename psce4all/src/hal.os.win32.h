/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "Winternl.h"

#include "hal.win32.h"

extern "C"
{
    extern NTSTATUS NTAPI NtClose(HANDLE Handle);

    extern NTSTATUS NTAPI NtCreateIoCompletion(PHANDLE IoCompletionHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, ULONG NumberOfConcurrentThreads);
    extern NTSTATUS NTAPI NtSetIoCompletion(HANDLE IoCompletionPortHandle, PVOID CompletionKey, PVOID CompletionContext, NTSTATUS CompletionStatus, ULONG_PTR CompletionInformation);
    extern NTSTATUS NTAPI NtRemoveIoCompletion(HANDLE IoCompletionHandle, PVOID * KeyContext, PVOID * ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER Timeout = 0);

    extern NTSTATUS NTAPI NtQueryPerformanceCounter(PLARGE_INTEGER Counter, PLARGE_INTEGER Frequency = 0);

    extern NTSTATUS NTAPI NtSetTimerResolution(ULONG DesiredResolution, BOOLEAN SetResolution, PULONG CurrentResolution);
    extern NTSTATUS NTAPI NtQueryTimerResolution(PULONG MinimumResolution, PULONG MaximumResolution, PULONG ActualResolution);

    extern NTSTATUS NTAPI NtYieldExecution(VOID);
    extern NTSTATUS NTAPI NtDelayExecution(BOOLEAN Alertable, PLARGE_INTEGER DelayInterval);

    extern NTSTATUS NTAPI NtCreateSemaphore(PHANDLE SemaphoreHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, ULONG InitialCount, ULONG MaximumCount);
    extern NTSTATUS NTAPI NtReleaseSemaphore(HANDLE SemaphoreHandle, ULONG ReleaseCount, PULONG PreviousCount);

    extern NTSTATUS NTAPI NtCreateKeyedEvent(OUT PHANDLE handle, IN ACCESS_MASK access, IN POBJECT_ATTRIBUTES attr, IN ULONG flags);
    extern NTSTATUS NTAPI NtOpenKeyedEvent(OUT PHANDLE handle, IN ACCESS_MASK access, IN POBJECT_ATTRIBUTES attr);
    extern NTSTATUS NTAPI NtWaitForKeyedEvent(IN HANDLE handle, IN PVOID key, IN BOOLEAN alertable, IN PLARGE_INTEGER mstimeout);
    extern NTSTATUS NTAPI NtReleaseKeyedEvent(IN HANDLE handle, IN PVOID key, IN BOOLEAN alertable, IN PLARGE_INTEGER mstimeout);
};

#if defined(__win64__)
#   define _GetCurrentProcessId()     ((DWORD)__readgsqword(0x40)) // fastest way to retrieve the current process id
#   define _GetCurrentThreadId()      ((DWORD)__readgsqword(0x48)) // fastest way to retrieve the thread process id
#else
#   define _GetCurrentProcessId()     ::GetCurrentProcessId()
#   define _GetCurrentThreadId()      ::GetCurrentThreadId()
#endif

namespace hal
{
    namespace os
    {
        namespace win32
        {
            struct SinglyLinkedList
            {
                struct Entry : SLIST_ENTRY
                {
                private:
                    void * operator new(size_t size) = delete; // you must override it
                    void   operator delete(void * pointer) = delete; // you must override it
                };

                /**/             SinglyLinkedList(bool initialize = true)
                {
                    if (initialize) Create();
                }
                /**/            ~SinglyLinkedList()
                {
                    assert(("Singly linked list is not empty", (nullptr != ::RtlFirstEntrySList(&m_head))));
                }

                void             Create()
                {
                    ::InitializeSListHead(&m_head);
                }

                template< typename T >
                T              * Flush()
                {
                    return static_cast< T * >((Entry *)::InterlockedFlushSList(&m_head));
                }

                template< typename T >
                bool             Flush(T *& entry)
                {
                    return 0 != (entry = Flush< T >());
                }

                template< typename T >
                void             Push(T * entry)
                {
                    ::InterlockedPushEntrySList(&m_head, (PSLIST_ENTRY)static_cast< Entry * >(entry));
                }

                template< typename T >
                T              * Pop()
                {
                    return static_cast< T * >((Entry *)::InterlockedPopEntrySList(&m_head));
                }

                template< typename T >
                bool             Pop(T *& entry)
                {
                    return 0 != (entry = Pop< T >());
                }

                void           * operator new(size_t size)
                {
                    return _aligned_malloc(size, MEMORY_ALLOCATION_ALIGNMENT);
                }

                void             operator delete(void * pointer)
                {
                    return _aligned_free(pointer);
                }

            private:
                SLIST_HEADER m_head;
            };

            struct KeyedEvent
            {
                HANDLE  m_keyed_event;

                enum
                {
                    WAITKEY_SHIFT = 1
                };

                KeyedEvent()
                {
                    NtCreateKeyedEvent(&m_keyed_event, EVENT_ALL_ACCESS, NULL, 0);
                }
                ~KeyedEvent()
                {
                    CloseHandle(m_keyed_event);
                }

                void wait(intptr_t key)
                {
                    assert(("key must be even", ((key&1) == 0)));
                    NtWaitForKeyedEvent(m_keyed_event, (PVOID)(key), FALSE, NULL);
                }

                void post(intptr_t key)
                {
                    assert(("key must be even", ((key&1) == 0)));
                    NtReleaseKeyedEvent(m_keyed_event, (PVOID)(key), FALSE, NULL);
                }
            };

            struct CriticalSection
            {
                /**/             CriticalSection(bool initialized = true) : m_initialized(initialized)
                {
                    if (m_initialized) Create();
                }
                /**/            ~CriticalSection()
                {
                    if (m_initialized) Delete();
                }

                void             Create()
                {
                    ::InitializeCriticalSection(&m_cs);
                }

                void             Delete()
                {
                    ::DeleteCriticalSection(&m_cs);
                    m_initialized = false;
                }

                void             Enter()
                {
                    ::EnterCriticalSection(&m_cs);
                }
                void             Leave()
                {
                    ::LeaveCriticalSection(&m_cs);
                }

                bool             TryEnter()
                {
                    return TRUE == ::TryEnterCriticalSection(&m_cs);
                }

            private:
                CRITICAL_SECTION m_cs;
                bool             m_initialized;
            };

            struct IoCompletionPort
            {
                struct Packet
                {
                    void      * key_context;
                    void      * apc_context;
                    NTSTATUS    status;
                    ULONG_PTR   information;
                };

                /**/             IoCompletionPort() : m_handle(0)
                {
                }
                /**/            ~IoCompletionPort()
                {
                    assert(("Io completion port is not closed", (0 != this->m_handle)));
                }

                void             Create(u32 concurrent_threads = 1)
                {
                    ::NtCreateIoCompletion(&m_handle, IO_COMPLETION_ALL_ACCESS, NULL, concurrent_threads);
                }

                void             Delete()
                {
                    if (m_handle) ::NtClose(m_handle);
                    m_handle = 0;
                }

                bool             Post(Packet const & packet)
                {
                    return 0 == ::NtSetIoCompletion(m_handle, packet.key_context, packet.apc_context, packet.status, packet.information);
                }

                bool             Wait(Packet & packet, PLARGE_INTEGER timeout)
                {
                    IO_STATUS_BLOCK iosb;
                    NTSTATUS status = ::NtRemoveIoCompletion(m_handle, &packet.key_context, &packet.apc_context, &iosb, timeout);
                    packet.status      = iosb.Status;
                    packet.information = iosb.Information;
                    return status == 0;
                }

                bool             Peek(Packet & packet)
                {
                    LARGE_INTEGER li = { 0, 0 }; // no wait
                    return Wait(packet, &li);
                }

            private:
                HANDLE m_handle;
            };

            struct ThreadLocalStorage
            {
                /**/                        ThreadLocalStorage() : m_tls_index(TLS_OUT_OF_INDEXES)
                {
                }
                /**/                       ~ThreadLocalStorage()
                {
                    assert(("Thread local storage is not deleted", (TLS_OUT_OF_INDEXES != this->m_tls_index)));
                }

                bool                        Create()
                {
                    assert(("Thread local storage is already allocated", (TLS_OUT_OF_INDEXES == this->m_tls_index)));

                    m_tls_index = ::TlsAlloc();

                    return m_tls_index < 64;
                }

                void                        Delete()
                {
                    assert(("Thread local storage is not valid", (TLS_OUT_OF_INDEXES != this->m_tls_index)));

                    ::TlsFree(m_tls_index);
                    m_tls_index = 0;
                }

                template< typename T > void Set(T * value)
                {
                    assert(("Thread local storage is not valid", (TLS_OUT_OF_INDEXES != this->m_tls_index)));

                    ::TlsSetValue(m_tls_index, (LPVOID)value);
                }

                template< typename T > bool Get(T *& value)
                {
                    assert(("Thread local storage is not valid", (TLS_OUT_OF_INDEXES != this->m_tls_index)));

                    T * data = ::TlsGetValue(m_tls_index);
                    value = data;
                    return 0 != data;
                }

                template< typename T > T ** Slot() const
                {
                    assert(("Thread local storage is not valid", (64 > this->m_tls_index)));

                    return __readgsqword(0x58) + 8*m_tls_index;
                }

                template< typename T > __forceinline T & operator = (T const & value)
                {
                    T * address = Slot< T >();
                    *address = value;
                    return *address;
                }

                template< typename T > __forceinline operator T const () const
                {
                    T * address = Slot< T >();
                    return *address;
                }

                template< typename T > __forceinline operator T & ()
                {
                    T * address = Slot< T >();
                    return *address;
                }

            private:
                DWORD m_tls_index;
            };

            typedef void (* FiberFunction)(void *);

            struct Fiber
            {
            private:
                Fiber::Fiber() : m_function(0), m_argument(0)
                {
                    m_thread       = this;
                    m_native_fiber = ::ConvertThreadToFiber((LPVOID)0);
                }

                static void Fiber::EntryPoint(void * that)
                {
                    Fiber * fiber = (Fiber *)that;

                    if (fiber->m_function)
                    {
                        fiber->m_function(fiber->m_argument);
                    }

                    m_thread->SwitchTo();
                }

            public:
                static const u32 StackSize = 8 * 4096;

                Fiber(FiberFunction function, void * argument) : m_function(function), m_argument(0)
                {
                    static Fiber thread_converted_into_fiber;

                    m_native_fiber = ::CreateFiber((SIZE_T)StackSize, (LPFIBER_START_ROUTINE)EntryPoint, (LPVOID)this);
                }

                virtual ~Fiber()
                {
                    if (m_thread == this)
                    {
                        ::ConvertFiberToThread();

                        m_thread = 0;
                    }
                    else if (::GetCurrentFiber() != m_native_fiber)
                    {
                        ::DeleteFiber(m_native_fiber);
                    }
                }

                static Fiber * Create(FiberFunction function, void * argument)
                {
                    return __new Fiber(function, argument);
                }

                static void Delete(Fiber * fiber)
                {
                    __delete fiber;
                }

                void SwitchTo()
                {
                    ::SwitchToFiber(m_native_fiber);
                }

            private: // not copyable
                Fiber(Fiber const &);
                Fiber        & operator =(Fiber const &);

                FiberFunction  m_function;
                void         * m_argument;
                LPVOID         m_native_fiber;
                static Fiber * m_thread;
            };
        }
    }
}

