/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hal.hmm.h"

#define ALLOCATOR_RETRIEVES_CALLSTACK

namespace emu
{
    namespace log
    {
        SubCategory hmm(hal, "hmm", "HMM - Heap Memory Manager");
    }
}

namespace hal
{
    namespace hmm
    {
        struct Callstack : hal::os::win32::SinglyLinkedList::Entry
        {
            Callstack         * m_link;
            void              * m_addr;
            size_t              m_size;
            char const        * m_name;
            hal::dbg::Callstack m_data;

            /**/        Callstack(void * addr, size_t size, char const * name);
            /**/        Callstack(Callstack *& slob, void * addr, size_t size, char const * name);
            /**/        Callstack(bool);

            virtual    ~Callstack();

            void      * operator new(size_t size);
            void      * operator new(size_t size, void * pointer);
            void        operator delete(void * pointer);
            void        operator delete(void * pointer, void *);
        };


        struct Implementation : Interface
        {
            /* interface v 1.0 */

            /**/           Implementation();

            virtual bool   DllProcessAttach();
            virtual void   DllProcessDetach();

            virtual void * Allocate(char const * name, size_t size, size_t alignment = MEMORY_ALLOCATION_ALIGNMENT);
            virtual void * ReAllocate(char const * name, void * pointer, size_t size, size_t alignment = MEMORY_ALLOCATION_ALIGNMENT);
            virtual void   Free(void * pointer);

            virtual void   DumpMemoryLeak();

            hal::os::win32::SinglyLinkedList m_callstack_pool;
            hal::Atomic< Callstack * >       m_root;
            Callstack                        m_stub;
        };
    }
}

static hal::hmm::Implementation * implementation = 0;

extern "C" __declspec(dllexport) hal::hmm::Interface * hal_hmm$GetInterface(long version)
{
    long version_major = (version >> 8) & 255;
    long version_minor = (version >> 0) & 255;

    if (version_major == hal::hmm::Implementation::version_major && version_minor <= hal::hmm::Implementation::version_minor)
    {
        return implementation;
    }

    return 0;
}

hal::hmm::Implementation::Implementation() : m_stub(false), m_root(&m_stub)
{
}

extern void ForceLinkWithStartupCleanup();

void hal::hmm::Startup()
{
    ForceLinkWithStartupCleanup();

    implementation = new Implementation;
}

void hal::hmm::Cleanup()
{
    implementation->m_root = nullptr;

    Callstack * node = implementation->m_callstack_pool.Flush< Callstack >();
    Callstack * next;
    do
    {
        next = node->m_link;
        _aligned_free(node);
        node = next;
    }
    while (next);

    delete implementation;
}

__noinline bool hal::hmm::Implementation::DllProcessAttach()
{
    return true;
}

__noinline void hal::hmm::Implementation::DllProcessDetach()
{
    DumpMemoryLeak();
}

void * hal::hmm::Implementation::Allocate(char const * name, size_t size, size_t alignment)
{
#if defined(ALLOCATOR_RETRIEVES_CALLSTACK)
    Callstack ** slob = (Callstack **)_aligned_offset_malloc(size + sizeof(Callstack *), alignment, sizeof(Callstack *));
    void       * data = (void *)(slob + 1);
    new Callstack(*slob, data, size, name);
#else
    void * data = _aligned_malloc(size, alignment);
#endif
    return data;
}

void * hal::hmm::Implementation::ReAllocate(char const * name, void * pointer, size_t size, size_t alignment)
{
#if defined(ALLOCATOR_RETRIEVES_CALLSTACK)
    Callstack ** slob = (Callstack **)_aligned_offset_realloc(pointer, size + sizeof(Callstack*), alignment, sizeof(Callstack*));
    void       * data = (void *)(slob + 1);
    new (*slob) Callstack(data, size, name);
#else
    void * data = _aligned_realloc(pointer, size, alignment));
#endif
    return data;
}

void hal::hmm::Implementation::Free(void * data)
{
#if defined(ALLOCATOR_RETRIEVES_CALLSTACK)
    Callstack ** slob = ((Callstack **)data) - 1;
    delete *slob;
    return _aligned_free(slob);
#else
    return _aligned_free(data);
#endif
}

__noinline hal::hmm::Callstack::Callstack(void * addr, size_t size, char const * name) : m_addr(addr), m_size(size), m_name(name)
{
    hal::dbg::Walk(m_data, 2);
}

__noinline hal::hmm::Callstack::Callstack(Callstack *& placeholder, void * addr, size_t size, char const * name) : m_addr(addr), m_size(size), m_name(name)
{
    hal::dbg::Walk(m_data, 2);

    placeholder = this;
}

hal::hmm::Callstack::Callstack(bool) : m_link(0), m_addr(0), m_size(0)
{
    m_data[0] = 0;
}

hal::hmm::Callstack::~Callstack()
{
    m_data[0] = 0;
}

void * hal::hmm::Callstack::operator new(size_t size)
{
    Callstack * callstack = implementation->m_callstack_pool.Pop< Callstack >();

    if (!callstack)
    {
        // no more free callstack so allocate one
        callstack = (Callstack *)_aligned_malloc(size, MEMORY_ALLOCATION_ALIGNMENT);
        callstack->m_data[0] = 0;
        callstack->m_link    = 0;
        Callstack * old = implementation->m_root;
        do
        {
            callstack->m_link = old;
        }
        while (!implementation->m_root.CompareExchange(old, callstack));
    }

    return callstack;
}

void * hal::hmm::Callstack::operator new(size_t size, void * pointer)
{
    return pointer;
}

void hal::hmm::Callstack::operator delete(void * pointer)
{
    if (pointer)
    {
        implementation->m_callstack_pool.Push((Callstack *)pointer);
    }
}

void hal::hmm::Callstack::operator delete(void * pointer, void *)
{
    // compiler complains if not defined here
}

void hal::hmm::Implementation::DumpMemoryLeak()
{
    time_t       t   = time(NULL);
    struct  tm * tme = localtime(&t);

    forcef(hmm, " ---------------------------------------------------------------------------------------------------------------------------------- ");
    forcef(hmm, "|                                          Memory leak report for:  %02d/%02d/%04d %02d:%02d:%02d                                            |", tme->tm_mon + 1, tme->tm_mday, tme->tm_year + 1900, tme->tm_hour, tme->tm_min, tme->tm_sec);
    forcef(hmm, " ---------------------------------------------------------------------------------------------------------------------------------- ");

    for (Callstack * callstack = implementation->m_root; callstack; callstack = callstack->m_link)
    {
        if (callstack->m_data[0])
        {
            forcef(hmm, " --- BLOCK [ NAME: %-32s - ADDRESS: %016I64X - SIZE: %8u ]--------------- ", callstack->m_name, callstack->m_addr, callstack->m_size);
            hal::dbg::EnumCallstack(callstack->m_data);
            forcef(hmm, " ---------------------------------------------------------------------------------------------------------------------------------- ");
        }
    }
}
