/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

// THIS IS A TEMPORARY STUFF UNTIL TRUE THREADMANAGER WORKS
 
#pragma once

#include "hal.Atomic.h"
#include "hal.hmm.h"
#include "hal.os.UmsThread.h"
#include "lle.cpu(Allegrex).h"
#include "lle.cpu(Allegrex).Context.h"

class CCpu
    : public  lle::cpu::Context
    , private hal::os::UmsRunnable
    , private hal::os::UmsScheduler
    , public  hal::hmm::Allocator< CCpu >
{
public:

    enum SyscallCode
    {
        DoNothing,
        DoLeave,
        DoSceSetDisplayMode,
        DoSceDisplaySetFrameBuf,
        DoSceDisplayWaitVblankStart,
        DoSceCtrlPeekBufferPositive
    };

    void Initialize(wchar_t const filename[]);
    void Terminate();
    void Step();
    void Interpret();
    void StartThread();
    void StopThread();
    void Run();

    struct SyscallEvent
    {
        hal::Atomic< SyscallCode > code;
        HANDLE                     event[2];

        void Enter(SyscallCode value)
        {
            ::ResetEvent(event[1]);
            code.Exchange(value);
            ::SetEvent(event[0]);
        }

        void Leave(SyscallCode value = CCpu::DoNothing)
        {
            ::ResetEvent(event[0]);
            code.Exchange(value);
            ::SetEvent(event[1]);
        }
    };

    SyscallEvent syscall;

    using hal::hmm::Allocator< CCpu >::operator new;
    using hal::hmm::Allocator< CCpu >::operator delete;
};

extern CCpu Cpu;
