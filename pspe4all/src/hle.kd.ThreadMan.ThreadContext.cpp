/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

void hle::kd::ThreadContext::do$SYSCALL(u32 /*opcode*/)
{

}

void hle::kd::ThreadContext::Run()
{
    if (1/*!lle::Cpu::use_real_interpreter*/)
    {
        MethodCall method;
        //hal::npa::StartEvent(cpu_event1);
        (this->*(method.pointer = GetCode(), method).execute)();
        //hal::npa::StopEvent(cpu_event1);
    }
    else
    {
        do
        {
            //switch (Cpu.syscall.code)
            //{
            //    case DoNothing:
            //    {
            //        __npa_Event(cpu_event1)
            //        {
            //            do Cpu.Step(); while (Cpu.syscall.code == DoNothing);
            //        }
            //        break;
            //    }
            //    case DoLeave:
            //    {
            //        return;
            //    }
            //    default:
            //    {
            //        __npa_Event(cpu_event2)
            //        {
            //            ::WaitForSingleObject(Cpu.syscall.event[1], INFINITE);
            //        }
            //        ::ResetEvent(Cpu.syscall.event[1]);
            //    }
            //}
        }
        while (true);
    }
}

void hle::kd::ThreadContext::InternalMain()
{
}

hle::kd::ThreadContext hle::kd::ThreadContext::main_thread;
