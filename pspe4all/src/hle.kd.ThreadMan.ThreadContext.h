/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifndef hle_kd_ThreadMan_h__
#error you must include "hle.kd.ThreadMan.h" instead
#endif

#include "hal.npa.h"
#include "hal.os.UmsThread.h"
#include "lle.cpu(Allegrex).h"
//#include "lle.Cpu.h"

namespace hle
{
    namespace kd
    {
        struct ThreadContext : lle::cpu::Context, lle::cpu::jitasm::Frontend, hal::os::UmsRunnable
        {
            union MethodCall
            {
                void (ThreadContext:: * execute)();
                void                  * pointer;
            };

            virtual void do$SYSCALL(u32 /*opcode*/);

            virtual void Run();

            virtual void InternalMain();

            static ThreadContext main_thread;
        };
    }

    typedef kd::ThreadContext KernelThreadContext;
}
