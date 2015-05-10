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
    enum
    {
        label_syscall,
        label_recompile,
        label_trampoline,
        label_exit,
        label_exit_function,
        label_syscall_function,
        label_recompile_function,
        label_trampoline_function,
        label_cross_interpret_function,
    };

    push(rbx);
    push(rbp);
    push(rsi);
    push(rdi);
    push(r12);
    push(r13);
    push(r14);
    push(r15);
    sub(rsp, 0x28); // 4 registers w/ 16-byte alignment (http://blogs.msdn.com/b/oldnewthing/archive/2004/01/14/58579.aspx)

    lea(rsi, qword_ptr[rcx+s32(intptr_t(static_cast<Allegrex::Context *>(this)) - intptr_t(this))]);
    lea(edi, qword_rip_ptr[label_syscall]);
    lea(ebx, qword_rip_ptr[label_recompile]);
    lea(eax, qword_rip_ptr[label_exit]);
    lea(edx, qword_rip_ptr[label_trampoline]);
    lea(rbp, qword_ptr[rsp-8]);

    mov(dword_ptr[rsi+s32(offsetof(lle::cpu::Context, Context::exit_address))], eax);
    mov(qword_ptr[rsi+s32(offsetof(lle::cpu::Context, Context::return_address))], rbp);
    mov(dword_ptr[rsi+s32(offsetof(lle::cpu::Context, Context::syscall_address))], edi);
    mov(dword_ptr[rsi+s32(offsetof(lle::cpu::Context, Context::recompile_address))], ebx);
    mov(dword_ptr[rsi+s32(offsetof(lle::cpu::Context, Context::trampoline_address))], edx);

    mov(edx, ICACHE_MEMORY_ADDRESS);
    mov(eax, dword_ptr[rsi+s32(offsetof(Allegrex::Context, Allegrex::Context::pc))]);
    add(rdx, rax);  // it is important to keep the translated address into rdx because the function at address rax may need it to recompile
    mov(eax, dword_ptr[rdx]);
    jmp(rax);

    L(label_exit);
    add(rsp, 0x28);
    pop(r15);
    pop(r14);
    pop(r13);
    pop(r12);
    pop(rdi);
    pop(rsi);
    pop(rbp);
    pop(rbx);
    ret();

    auto syscall_pointer = &Context::Syscall;
    auto recompile_pointer = &Context::Recompile;
    auto cross_interpret_pointer = &Context::CrossInterpret;

    align(3);
    L(label_recompile_function);
    dq((intptr_t)recompile_pointer);
    L(label_syscall_function);
    dq((intptr_t)syscall_pointer);
    L(label_cross_interpret_function);
    dq((intptr_t)cross_interpret_pointer);
}

hle::kd::ThreadContext hle::kd::ThreadContext::main_thread;
