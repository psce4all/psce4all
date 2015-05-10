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

        struct Callback;

        struct CallbackQueue : hal::LinkedList< Callback >
        {
        };

        struct Callback : WaitQueue, CallbackQueue::Node
        {
            declare_kernel_type(Callback, WaitQueue);

            int                         m_uses;
            bool                        m_invalid;
            Thread                    * m_thread;
            int                         m_notify_count;
            int                         m_notify_arg;
            SceKernelCallbackFunction   m_function;
            u32                         m_cookie;
            u32                         m_gp;

            Callback(char const * name, SceKernelCallbackFunction callback, u32 cookie);
            ~Callback();

            static int                  Create(char const * name, SceKernelCallbackFunction callback, u32 cookie, int intr);
            int                         Delete(int intr);
            int                         Notify(int arg, int intr);
            int                         Cancel(int intr);
            int                         GetCount(int intr);
            int                         Check(int intr);
            int                         ReferStatus(SceKernelCallbackInfo * info, int intr);
        };
    }

    typedef kd::Callback      KernelCallback;
    typedef kd::CallbackQueue KernelCallbackQueue;
}
