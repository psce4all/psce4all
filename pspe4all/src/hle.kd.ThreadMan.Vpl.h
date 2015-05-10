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
        /// KernelVpl ///////////////////////////////////////////////////////////////

        struct Vpl : WaitQueue
        {
            declare_kernel_type(Vpl, WaitQueue);

            int                                 m_pool_size;
            int                                 m_free_size;
            SceKernelVplOptParam                m_opt_param;
            SceUID                              m_heap_uid;

            /**/                                Vpl(SceUID heap_uid, SceUInt attributes, SceSize size, SceKernelVplOptParam * opt_param, char const * name);
            /**/                               ~Vpl();

            static int                          Create(char const * name, SceUID pid, SceUInt attr, SceSize size, SceKernelVplOptParam * opt_param, int intr);
            int                                 Delete(int intr);
            int                                 Allocate(SceSize size, u32 & addr, SceUInt * timeout, bool cb, int intr);
            int                                 TryAllocate(SceSize size, u32 & addr);
            int                                 Free(u32 addr, int intr);
            int                                 Cancel(int * waiting_threads);
            int                                 ReferStatus(SceKernelVplInfo * info);
        };
    }

    typedef kd::Vpl KernelVpl;
}
