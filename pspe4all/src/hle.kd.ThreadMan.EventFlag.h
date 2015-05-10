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
        /// KernelEventFlag /////////////////////////////////////////////////////////

        struct EventFlag : WaitQueue
        {
            declare_kernel_type(EventFlag, WaitQueue);

            enum WaitAttribute
            {
                WAITATTR_SINGLE          = 0x0000U,
                WAITATTR_MULTIPLE        = 0x0200U
            };

            enum WaitMode
            {
                WAITMODE_AND             = 0x0000,
                WAITMODE_OR              = 0x0001,
                WAITMODE_CLEAR_ALL       = 0x0010,
                WAITMODE_CLEAR_MATCHED   = 0x0020
            };

            int                         m_initial_pattern;
            int                         m_current_pattern;
            SceKernelEventFlagOptParam  m_opt_param;

            /**/                        EventFlag(char const * name, SceUInt attr, SceUInt initial_pattern, SceKernelEventFlagOptParam * opt_param);
            /**/                       ~EventFlag();

            static int                  Create(char const * name, SceUInt attr, SceUInt initial_pattern, SceKernelEventFlagOptParam * opt_param);
            int                         Delete(int intr);
            int                         Set(SceUInt pattern, int is_intr_context, int intr);
            int                         Clear(SceUInt pattern);
            int                         Wait(SceUInt pattern, SceUInt waitmode, u32 result_pattern, SceUInt * timeout, bool is_cb, int intr);
            int                         Poll(SceUInt pattern, SceUInt waitmode, u32 result_pattern);
            int                         Cancel(SceUInt pattern, int * waiters);
            int                         ReferStatus(SceKernelEventFlagInfo * info);
        };
    }

    typedef kd::EventFlag KernelEventFlag;
}
