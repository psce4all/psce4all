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
        /// KernelFpl ///////////////////////////////////////////////////////////////

        struct Fpl : WaitQueue
        {
            declare_kernel_type(Fpl, WaitQueue);

            int                                 m_pool_blocks;
            int                                 m_free_blocks;
            SceKernelFplOptParam                m_opt_param;
            int                                 m_block_size;
            SceUID                              m_heap_uid;

            /**/                                Fpl(SceUID heap_uid, SceUInt attributes, SceSize block_size, int block_count, SceKernelFplOptParam * opt_param, char const *name);
            /**/                               ~Fpl();

            static int                          Create(char const * name, SceUID pid, SceUInt attributes, SceSize block_size, int block_count, SceKernelFplOptParam * opt_param, int intr);
            int                                 Delete(int intr);
            int                                 Allocate(u32 & addr, int * timeout, bool cb);
            int                                 TryAllocate(u32 & addr);
            int                                 Free(u32 addr);
            int                                 Cancel(int * waiting_threads);
            int                                 ReferStatus(SceKernelFplInfo * info);
        };
    }

    typedef kd::Fpl KernelFpl;
}
