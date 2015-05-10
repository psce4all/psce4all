/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <stdio.h>
#include <functional>

#include "emu.h"
#include "emu.log.h"
#include "emu.Module.h"

namespace hal
{
    namespace dbg
    {
#if defined(EMU_EXPORTS)
        void   Startup();
        void   Cleanup();
#endif

        typedef size_t Callstack[64];

        bool                         Refresh();

        void                         Walk(size_t * callstack, int skip);

        void                         EnumCallstack(size_t * callstack, std::function< void(uintptr_t address, wchar_t * modulename, wchar_t * filename, int linenumber, wchar_t * symbolname, wchar_t * undecoratedname) > callback);
        void                         EnumCallstack(size_t * callstack);

        void                         DumpCallstack(char const fmt[], ...);
        void                         DumpLastError(char const message[], DWORD error);

        int                          TinyDumpFilter(EXCEPTION_POINTERS * pep);
        int                          MiniDumpFilter(EXCEPTION_POINTERS * pep);
        int                          MidiDumpFilter(EXCEPTION_POINTERS * pep);
        int                          MaxiDumpFilter(EXCEPTION_POINTERS * pep);

        LPTOP_LEVEL_EXCEPTION_FILTER EnforceFilter(bool enforce, LPTOP_LEVEL_EXCEPTION_FILTER filter = nullptr);

        struct Interface : emu::Interface
        {
            /**/     Interface()
            {
            }
            virtual ~Interface()
            {
            }

            /* interface v 1.0 */

            virtual bool                         Refresh() = 0;

            virtual void                         Walk(size_t * callstack, int skip) = 0;

            virtual void                         EnumCallstack(size_t * callstack, std::function< void(uintptr_t address, wchar_t * modulename, wchar_t * filename, int linenumber, wchar_t * symbolname, wchar_t * undecoratedname) > callback) = 0;
            virtual void                         EnumCallstack(size_t * callstack) = 0;

            virtual void                         DumpLastError(char const message[], DWORD error) = 0;

            enum DumpType
            {
                TinyDump, MiniDump, MidiDump, MaxiDump
            };

            virtual int                          DumpFilter(DumpType type, EXCEPTION_POINTERS * pep = nullptr) = 0;
            virtual LPTOP_LEVEL_EXCEPTION_FILTER EnforceFilter(bool enforce, LPTOP_LEVEL_EXCEPTION_FILTER filter = nullptr) = 0;
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
extern "C" __declspec(dllexport) hal::dbg::Interface * hal_dbg$GetInterface(long version);
#else
extern "C" __forceinline hal::dbg::Interface * hal_dbg$GetInterface(long version)
{
    typedef hal::dbg::Interface * (Function)(long version);
    static Function * function = emu::Module::GetFunction< Function >("hal_dbg$GetInterface");
    if (function)
    {
        return function(version);
    }
    return 0;
}
#endif

__forceinline hal::dbg::Proxy::Proxy()
{
    that = hal_dbg$GetInterface(Interface::version);
}

__forceinline hal::dbg::Interface * hal::dbg::Proxy::operator->()
{
    return that;
}

__forceinline bool hal::dbg::Refresh()
{
    return proxy->Refresh();
}

__forceinline void hal::dbg::Walk(size_t * callstack, int skip)
{
    int i = ::RtlCaptureStackBackTrace(skip, 63 - skip, (PVOID*)callstack, 0);
    callstack[i] = 0;
}

__forceinline void hal::dbg::EnumCallstack(size_t * callstack, std::function< void(uintptr_t address, wchar_t * modulename, wchar_t * filename, int linenumber, wchar_t * symbolname, wchar_t * undecoratedname) > callback)
{
    proxy->EnumCallstack(callstack, callback);
}

__forceinline void hal::dbg::EnumCallstack(size_t * callstack)
{
    proxy->EnumCallstack(callstack);
}

__forceinline void hal::dbg::DumpCallstack(char const fmt[], ...)
{
    va_list ap;
    va_start(ap, fmt);
    int     n, size = 128;
    va_list save_ap;
    char ** s;
    if ((*s = (char*)malloc(size)) == NULL)
    {
        hal::dbg::DumpLastError("Not enough memory", 0);
        va_end(ap);
        return;
    }
    while (1)
    {
        va_copy(save_ap, ap);
        n = _vsnprintf(*s, size, fmt, save_ap);
        va_end(save_ap);
        if (n > -1 && n < size)
        {
            hal::dbg::DumpLastError(*s, 0);
            va_end(ap);
            return;
        }
        if (n > -1)
        {
            size = n + 1;
        }
        else
        {
            size *= 2;
        }
        if ((*s = (char*)realloc(*s, size)) == NULL)
        {
            hal::dbg::DumpLastError("Not enough memory", 0);
            va_end(ap);
            return;
        }
    }
}

__forceinline void hal::dbg::DumpLastError(char const message[], DWORD error)
{
    proxy->DumpLastError(message, error);
}

template< typename Boolean > __forceinline Boolean __DbgCheckLastError(char const message[], Boolean const & check)
{
    if (!check)
    {
        DWORD error = ::GetLastError();
        if (error) hal::dbg::DumpLastError(message, error);
    }
    return check;
}

__forceinline int hal::dbg::TinyDumpFilter(EXCEPTION_POINTERS * pep)
{
    return proxy->DumpFilter(Interface::TinyDump, pep);
}

__forceinline int hal::dbg::MiniDumpFilter(EXCEPTION_POINTERS * pep)
{
    return proxy->DumpFilter(Interface::MiniDump, pep);
}

__forceinline int hal::dbg::MidiDumpFilter(EXCEPTION_POINTERS * pep)
{
    return proxy->DumpFilter(Interface::MidiDump, pep);
}

__forceinline int hal::dbg::MaxiDumpFilter(EXCEPTION_POINTERS * pep)
{
    return proxy->DumpFilter(Interface::MaxiDump, pep);
}

__forceinline LPTOP_LEVEL_EXCEPTION_FILTER hal::dbg::EnforceFilter(bool enforce, LPTOP_LEVEL_EXCEPTION_FILTER filter)
{
    return proxy->EnforceFilter(enforce, filter);
}
