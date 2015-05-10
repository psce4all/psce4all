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
        /// KernelThreadQueue ///////////////////////////////////////////////////////

        struct ThreadQueue : hal::LinkedList< Thread >
        {
            int  AddWaitingThread(Thread *, int wait_type);
            void InsertWaitingThread(Thread *);
        };
    }

    typedef kd::ThreadQueue KernelThreadQueue;
}
