/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "emu.log.h"
#include "emu.Module.h"
#include "hal.Atomic.h"
#include "hal.os.h"

namespace hal
{
    namespace npa
    {
#if defined(EMU_EXPORTS)
        void   Startup();
        void   Cleanup();
#endif

        struct Event
        {
            int                         m_index;
            char const                * m_name;
            /**/                        Event(char const * name);
            /**/                       ~Event();
        };

        void    StartEvent(Event const & event, u16 data = 0);
        void    StopEvent(Event const & event, u16 data = 0);

        struct Interface : emu::Interface
        {
            /**/     Interface()
            {
            }
            virtual ~Interface()
            {
            }

            /* interface v 1.0 */

            virtual int     AllocateIndex() = 0;

            virtual void    StartEvent(Event const & event, u16 data = 0) = 0;
            virtual void    StopEvent(Event const & event, u16 data = 0) = 0;
        };

        struct Proxy
        {
            Proxy();

            __forceinline Interface * operator -> ();

            Interface * that;
        };

        __weaksymbol Proxy proxy;

        struct EventScope
        {
            EventScope(Event & event) : event(&event)
            {
                proxy->StartEvent(event);
            }
            ~EventScope()
            {
                proxy->StopEvent(*event);
            }

            operator bool() const
            {
                return true;
            }

            Event * event;
        };
    }
}

#if defined(EMU_EXPORTS)
extern "C" __declspec(dllexport) hal::npa::Interface * hal_npa$GetInterface(long version);
#else
extern "C" __forceinline hal::npa::Interface * hal_npa$GetInterface(long version)
{
    typedef hal::npa::Interface * (Function)(long version);
    static Function * function = emu::Module::GetFunction< Function >("hal_npa$GetInterface");
    if (function)
    {
        return function(version);
    }
    return 0;
}
#endif

__forceinline hal::npa::Proxy::Proxy()
{
    that = hal_npa$GetInterface(Interface::version);
}

__forceinline hal::npa::Interface * hal::npa::Proxy::operator->()
{
    return that;
}

__forceinline hal::npa::Event::Event(char const * name) : m_index(proxy->AllocateIndex()), m_name(name)
{
}

__forceinline hal::npa::Event::~Event()
{
}

__forceinline void hal::npa::StartEvent(Event const & event, u16 data /*= 0*/)
{
    proxy->StartEvent(event, data);
}

__forceinline void hal::npa::StopEvent(Event const & event, u16 data /*= 0*/)
{
    proxy->StopEvent(event, data);
}

#define __npa_Event(event) if (hal::npa::EventScope __EventScope__ = hal::npa::EventScope(event))
