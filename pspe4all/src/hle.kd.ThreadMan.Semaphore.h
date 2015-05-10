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
        /// KernelSemaphore /////////////////////////////////////////////////////////

        struct Semaphore : WaitQueue
        {
            declare_kernel_type(Semaphore, WaitQueue);

            int                     m_initial_count;
            int                     m_maximum_count;
            int                     m_current_count;
            SceKernelSemaOptParam * m_opt_param;

            /**/                    Semaphore(char const * name, SceUInt attributes, int initial_count, int maximum_count, SceKernelSemaOptParam * opt_param);
            /**/                   ~Semaphore();

            static int              Create(char const * name, SceUInt attributes, int initial_count, int maximum_count, SceKernelSemaOptParam * opt_param);
            int                     Delete(int intr);
            int                     Signal(int count, int intr, int is_intr_context);
            int                     Wait(int count, SceUInt * timeout, bool cb, int intr);
            int                     Poll(int count);
            int                     Cancel(int count, int * waiters);
            int                     ReferStatus(SceKernelSemaInfo * info);
        };
    }

    typedef kd::Semaphore KernelSemaphore;
}
