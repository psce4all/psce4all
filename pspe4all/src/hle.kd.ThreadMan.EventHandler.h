/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifndef hle_kd_ThreadMan_h__
#error you must include "hle.kd.ThreadMan.h" instead
#endif

namespace hle
{
    namespace kd
    {
        /// KernelEventHandler //////////////////////////////////////////////////////

        struct EventHandler;

        struct EventHandlerQueue : hal::LinkedList< EventHandler >
        {
        };

        struct EventHandler : WaitQueue, EventHandlerQueue::Node
        {
            declare_kernel_type(EventHandler, WaitQueue);

            int                         m_uses;
            bool                        m_invalid;
            Thread                    * m_thread;
            int                         m_mask;
            SceKernelThreadEventHandler m_handler;
            u32                         m_cookie;
            u32                         m_gp;

            EventHandler(char const * name, SceUInt attr, SceUInt initial_pattern, SceKernelEventFlagOptParam *opt_param);
            ~EventHandler();

            //static int                  Create(char const * name, SceUInt attr, SceUInt initial_pattern, SceKernelEventFlagOptParam * opt_param);
            //int                         Delete(int intr);

            //int                         ReferStatus(SceKernelThreadEventHandlerInfo * info, int intr);
        };
    }

    typedef kd::EventHandler KernelEventHandler;
}
