/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <malloc.h>

#include "hal.os.win32.h"
#include "hal.dbg.h"
#include "hal.Atomic.h"

namespace hal
{
    namespace hmm
    {
#if defined(EMU_EXPORTS)
        void   Startup();
        void   Cleanup();
#endif

        void * Allocate(char const * name, size_t size, size_t alignment = MEMORY_ALLOCATION_ALIGNMENT);
        void * ReAllocate(char const * name, void * pointer, size_t size, size_t alignment = MEMORY_ALLOCATION_ALIGNMENT);
        void   Free(void * pointer);

        void * AllocateAndFill(char const * name, int fill, size_t size, size_t alignment = MEMORY_ALLOCATION_ALIGNMENT);

        void   DumpMemoryLeak();

        template< typename T > struct Allocator
        {
            void * operator new (size_t size)
            {
                return hal::hmm::Allocate(typeid(T).name(), size, __alignof(T));
            }
            void * operator new[] (size_t size)
            {
                return hal::hmm::Allocate(typeid(T).name(), size, __alignof(T));
            }
            void   operator delete (void * pointer)
            {
                return hal::hmm::Free(pointer);
            }
            void   operator delete[] (void * pointer)
            {
                return hal::hmm::Free(pointer);
            }
        };

        struct Interface : emu::Interface
        {
            /**/     Interface()
            {
            }
            virtual ~Interface()
            {
            }

            /* interface v 1.0 */

            virtual void * Allocate(char const * name, size_t size, size_t alignment = MEMORY_ALLOCATION_ALIGNMENT) = 0;
            virtual void * ReAllocate(char const * name, void * pointer, size_t size, size_t alignment = MEMORY_ALLOCATION_ALIGNMENT) = 0;
            virtual void   Free(void * pointer) = 0;

            virtual void   DumpMemoryLeak() = 0;
        };

        struct Proxy
        {
            Proxy();

            __forceinline Interface * operator -> ();

            Interface * that;
        };

        __weaksymbol Proxy proxy;
    }
}

#if defined(EMU_EXPORTS)
extern "C" __declspec(dllexport) hal::hmm::Interface * hal_hmm$GetInterface(long version);
#else
extern "C" __forceinline hal::hmm::Interface * hal_hmm$GetInterface(long version)
{
    typedef hal::hmm::Interface * (Function)(long version);
    static Function * function = emu::Module::GetFunction< Function >("hal_heap$GetInterface");
    if (function)
    {
        return function(version);
    }
    return 0;
}
#endif

__forceinline hal::hmm::Proxy::Proxy()
{
    that = hal_hmm$GetInterface(Interface::version);
}

__forceinline hal::hmm::Interface * hal::hmm::Proxy::operator->()
{
    return that;
}

__forceinline void * hal::hmm::Allocate(char const * name, size_t size, size_t alignment /*= MEMORY_ALLOCATION_ALIGNMENT*/)
{
    return proxy->Allocate(name, size, alignment);
}

__forceinline void * hal::hmm::ReAllocate(char const * name, void * pointer, size_t size, size_t alignment /*= MEMORY_ALLOCATION_ALIGNMENT*/)
{
    return proxy->ReAllocate(name, pointer, size, alignment);
}

__forceinline void hal::hmm::Free(void * pointer)
{
    proxy->Free(pointer);
}

__forceinline void * hal::hmm::AllocateAndFill(char const * name, int fill, size_t size, size_t alignment /*= MEMORY_ALLOCATION_ALIGNMENT*/)
{
    void * result = proxy->Allocate(name, size, alignment);
    ::memset(result, fill, size);
    return result;
}

__forceinline void hal::hmm::DumpMemoryLeak()
{
    proxy->DumpMemoryLeak();
}

//#undef  __new
//#undef  __delete
//#undef  malloc
//#undef  realloc
//#undef  free
//
//#define   __new                   new(__FILE__,__LINE__,__FUNCTION__)
//#define   __delete                if (MemDeleteScope __delete_scope__ = MemDeleteScope(__FILE__,__LINE__,__FUNCTION__)) delete
//#define   malloc(sz)              ::hal::heap::Allocate(sz)
//#define   realloc(ptr,sz)         ::hal::heap::ReAllocate(sz,ptr)
//#define   free(ptr)               ::hal::heap::Free(ptr)
