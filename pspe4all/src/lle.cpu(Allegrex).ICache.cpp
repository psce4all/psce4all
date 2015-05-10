/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hal.npa.h"

#include "lle.cpu(Allegrex).h"

Allegrex::ICache Allegrex::icache;

Allegrex::ICache::ICache()
{
}

typedef enum _UNWIND_OP_CODES
{
    UWOP_PUSH_NONVOL = 0, /* info == register number */
    UWOP_ALLOC_LARGE,     /* no info, alloc size in next 2 slots */
    UWOP_ALLOC_SMALL,     /* info == size of allocation / 8 - 1 */
    UWOP_SET_FPREG,       /* no info, FP = RSP + UNWIND_INFO.FPRegOffset*16 */
    UWOP_SAVE_NONVOL,     /* info == register number, offset in next slot */
    UWOP_SAVE_NONVOL_FAR, /* info == register number, offset in next 2 slots */
    UWOP_SAVE_XMM128,     /* info == XMM reg number, offset in next slot */
    UWOP_SAVE_XMM128_FAR, /* info == XMM reg number, offset in next 2 slots */
    UWOP_PUSH_MACHFRAME   /* info == 0: no error-code, 1: error-code */
} UNWIND_CODE_OPS;

class UNWIND_REGISTER
{
public:
    enum _
    {
        RAX = 0,
        RCX = 1,
        RDX = 2,
        RBX = 3,
        RSP = 4,
        RBP = 5,
        RSI = 6,
        RDI = 7,
        R8 = 8,
        R9 = 9,
        R10 = 10,
        R11 = 11,
        R12 = 12,
        R13 = 13,
        R14 = 14,
        R15 = 15,
    };
};

typedef union _UNWIND_CODE
{
    struct
    {
        uint8_t CodeOffset;
        uint8_t UnwindOp : 4;
        uint8_t OpInfo : 4;
    };
    USHORT FrameOffset;
} UNWIND_CODE, *PUNWIND_CODE;

typedef struct _UNWIND_INFO
{
    uint8_t Version : 3;
    uint8_t Flags : 5;
    uint8_t SizeOfProlog;
    uint8_t CountOfCodes;
    uint8_t FrameRegister : 4;
    uint8_t FrameOffset : 4;
    UNWIND_CODE UnwindCode[1];
    /*  UNWIND_CODE MoreUnwindCode[((CountOfCodes + 1) & ~1) - 1];
    *   union {
    *       OPTIONAL ULONG ExceptionHandler;
    *       OPTIONAL ULONG FunctionEntry;
    *   };
    *   OPTIONAL ULONG ExceptionData[]; */
} UNWIND_INFO, *PUNWIND_INFO;


void Allegrex::ICache::UnwindInfoFrame0::InternalMain() // for thread_code, recompile_code, trampoline_code and super blocks
{
    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    dd((1/*Version*/) << 0 | (0/*Flags*/) << 3 | (16/*SizeOfProlog*/) << 8 | (9/*CountOfCodes*/) << 16 | (0/*FrameRegister*/) << 24 | (0/*FrameOffset*/) << 28);
    dw(0x0C | (UWOP_ALLOC_SMALL/*UnwindOp*/) << 8 | ((0x28 / 8 - 1)/*OpInfo*/) << 12);
    dw(0x0A | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::R15/*OpInfo*/) << 12);
    dw(0x08 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::R14/*OpInfo*/) << 12);
    dw(0x06 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::R13/*OpInfo*/) << 12);
    dw(0x04 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::R12/*OpInfo*/) << 12);
    dw(0x03 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::RDI/*OpInfo*/) << 12);
    dw(0x02 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::RSI/*OpInfo*/) << 12);
    dw(0x01 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::RBP/*OpInfo*/) << 12);
    dw(0x00 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::RBX/*OpInfo*/) << 12);
}

void Allegrex::ICache::UnwindInfoFrame1::InternalMain() // for trace_code, crossinterpret_code
{
    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R11                         |
    // | R10                         |
    // | R9                          |
    // | R8                          |
    // | RBX                         |
    // | RDX                         |
    // | RCX                         |
    // | RAX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    dd((1/*Version*/) << 0 | (0/*Flags*/) << 3 | (16/*SizeOfProlog*/) << 8 | (9/*CountOfCodes*/) << 16 | (0/*FrameRegister*/) << 24 | (0/*FrameOffset*/) << 28);
    dw(0x0C | (UWOP_ALLOC_SMALL/*UnwindOp*/) << 8 | ((0x28 / 8 - 1)/*OpInfo*/) << 12);
    dw(0x0A | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::R11/*OpInfo*/) << 12);
    dw(0x08 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::R10/*OpInfo*/) << 12);
    dw(0x06 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::R9/*OpInfo*/) << 12);
    dw(0x04 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::R8/*OpInfo*/) << 12);
    dw(0x03 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::RBX/*OpInfo*/) << 12);
    dw(0x02 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::RDX/*OpInfo*/) << 12);
    dw(0x01 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::RCX/*OpInfo*/) << 12);
    dw(0x00 | (UWOP_PUSH_NONVOL/*UnwindOp*/) << 8 | (UNWIND_REGISTER::RAX/*OpInfo*/) << 12);
}

void Allegrex::ICache::UnwindInfoFrame2::InternalMain() // for syscall_code
{
    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    dd((1/*Version*/) << 0 | (0/*Flags*/) << 3 | (4/*SizeOfProlog*/) << 8 | (1/*CountOfCodes*/) << 16 | (0/*FrameRegister*/) << 24 | (0/*FrameOffset*/) << 28);
    dw(0x00 | (UWOP_ALLOC_SMALL/*UnwindOp*/) << 8 | ((0x28 / 8 - 1)/*OpInfo*/) << 12);
}

void Allegrex::ICache::ThreadCode::InternalMain()
{
    enum
    {
        label_exit
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

    mov(rsi, rcx);
    mov(edi, uint32_t(Allegrex::icache.syscall_code.GetCode()));
    mov(ebx, uint32_t(Allegrex::icache.recompile_code.GetCode()));
    lea(eax, qword_rip_ptr[label_exit]);
    mov(edx, uint32_t(Allegrex::icache.trampoline_code.GetCode()));
    mov(r15d, uint32_t(Allegrex::icache.crossinterpret_code.GetCode()));
    mov(r14d, uint32_t(Allegrex::icache.trace_code.GetCode()));
    lea(rbp, qword_ptr[rsp - 8]);
    mov(dword_ptr[rsi + s32(offsetof(lle::cpu::Context, Context::exit_address))], eax);
    mov(qword_ptr[rsi + s32(offsetof(lle::cpu::Context, Context::return_address))], rbp);
    mov(dword_ptr[rsi + s32(offsetof(lle::cpu::Context, Context::syscall_address))], edi);
    mov(dword_ptr[rsi + s32(offsetof(lle::cpu::Context, Context::recompile_address))], ebx);
    mov(dword_ptr[rsi + s32(offsetof(lle::cpu::Context, Context::trampoline_address))], edx);
    mov(qword_ptr[rsi + s32(offsetof(lle::cpu::Context, Context::cross_interpret_address))], r15);
    mov(qword_ptr[rsi + s32(offsetof(lle::cpu::Context, Context::trace_address))], r14);

    mov(edx, ICACHE_MEMORY_ADDRESS);
    mov(eax, dword_ptr[rsi + s32(offsetof(Allegrex::Context, Allegrex::Context::pc))]);
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
}

void Allegrex::ICache::Start()
{
    ::memset(runtime_function_array, 0, sizeof(runtime_function_array));

    auto base_pointer = u32(JITASM_MEMORY_ADDRESS);

    auto unwind_info_frame0_pointer = icache.unwind_info_frame0.GetCode();
    auto unwind_info_frame1_pointer = icache.unwind_info_frame1.GetCode();
    auto unwind_info_frame2_pointer = icache.unwind_info_frame2.GetCode();

    auto trace_pointer = icache.trace_code.GetCode();
    auto crossinterpret_pointer = icache.crossinterpret_code.GetCode();
    auto syscall_pointer = icache.syscall_code.GetCode();
    auto thread_pointer = icache.thread_code.GetCode();
    auto recompile_pointer = icache.recompile_code.GetCode();

    icache.trampoline_code.GetCode();

    // Initialize icache for SRAM address range
    for (auto pc = 0x00010000; pc < 0x00014000; pc += 4)
    {
        *(p32icache< u32 >(pc + 0x00000000)) = u32(recompile_pointer); // cached SRAM
        *(p32icache< u32 >(pc + 0x40000000)) = u32(recompile_pointer); // uncached SRAM
    }

    // Initialize icache for DRAM address range
    for (auto pc = 0x08000000; pc < 0x0C000000; pc += 4)
    {
        *(p32icache< u32 >(pc + 0x00000000)) = u32(recompile_pointer); // cached DRAM
        *(p32icache< u32 >(pc + 0x40000000)) = u32(recompile_pointer); // uncached DRAM
    }

    // Function tables are used on 64-bit Windows to determine how to unwind or walk the stack.
    // These tables are usually generated by the compiler and stored as part of the image.
    // However, applications must provide the function table for dynamically generated code.
    runtime_function_array[0].BeginAddress = u32(trace_pointer) - base_pointer;
    runtime_function_array[0].EndAddress = u32(trace_pointer) - base_pointer + u32(icache.trace_code.GetCodeSize());
    runtime_function_array[0].UnwindInfoAddress = u32(unwind_info_frame1_pointer) - base_pointer;

    runtime_function_array[1].BeginAddress = u32(crossinterpret_pointer) - base_pointer;
    runtime_function_array[1].EndAddress = u32(crossinterpret_pointer) - base_pointer + u32(icache.crossinterpret_code.GetCodeSize());
    runtime_function_array[1].UnwindInfoAddress = u32(unwind_info_frame1_pointer) - base_pointer;

    runtime_function_array[2].BeginAddress = u32(syscall_pointer) - base_pointer;
    runtime_function_array[2].EndAddress = u32(syscall_pointer) - base_pointer + u32(icache.syscall_code.GetCodeSize());
    runtime_function_array[2].UnwindInfoAddress = u32(unwind_info_frame2_pointer) - base_pointer;

    runtime_function_array[3].BeginAddress = u32(thread_pointer) - base_pointer;
    runtime_function_array[3].EndAddress = u32(JITASM_MEMORY_SIZE);
    runtime_function_array[3].UnwindInfoAddress = u32(unwind_info_frame0_pointer) - base_pointer;

    // This function call is necessary for code that is generated from a template or generated only once during the life of the process.
    ::RtlAddFunctionTable(runtime_function_array, 4, base_pointer);
}

void Allegrex::ICache::Stop()
{
    ::RtlDeleteFunctionTable(runtime_function_array);

    ::memset(runtime_function_array, 0, sizeof(runtime_function_array));
}

static hal::npa::Event cpu_icache("CPU ICache Recompiler");

__noinline u32 lle::cpu::Context::Recompile(Context * that, u32 address)
{
    hal::npa::StartEvent(cpu_icache);
    u32 pc = address - ICACHE_MEMORY_ADDRESS;
    icache.blocks[pc] = new ICache::CodeBlock(pc, 4);
    hal::npa::StopEvent(cpu_icache);
    return *((u32 *)(address));
}

bool cross_interpreter_cmp = false;

__noinline void Allegrex::ICache::CodeBlock::InternalMain()
{
    u32    pc = initial_address;
    size_t end = 0ULL;
    size_t beg = 0ULL;

    if (CROSS_INTERPRETER)
    {
        cross_interpreter_cmp = true;
    }

    while (pc)
    {
        if ((pc - 0x08800000) > (0x0C000000 - 0x08800000))
        {
            pc = 0;
            //__debugbreak();
            break;
        }
        auto opcode = *((p32u32)pc);
        pc = EmitInstruction(pc, opcode, false);
        if (INTERPRETER_LIKE)
        {
            end = Frontend::instrs_.size();
            beg = end;
            break;
        }
        else
        {
            if (!pc)
            {
                end = Frontend::instrs_.size();
                beg = end;

            loop:
                if (target_address_next.empty())
                {
                    break;
                }

                pc = *target_address_next.begin();
                target_address_next.erase(target_address_next.begin());

                if (!pc || target_address_done.find(pc) != target_address_done.end()) goto loop;

                if (CROSS_INTERPRETER)
                {
                    cross_interpreter_cmp = true;
                }
            }
        }
    }
    target_address_done.clear();

    if (INTERPRETER_LIKE && pc)
    {
        mov(edx, u32((pc)+ICACHE_MEMORY_ADDRESS));
        mov(ebp, dword_ptr[rdx]);
        jmp(rbp);
    }
}

#define IDO(x) do { return emit$##x(address, opcode, delayslot); } while (-1 == __LINE__)

__noinline u32 Allegrex::ICache::CodeBlock::EmitInstruction(u32 address, u32 opcode, bool delayslot)
{
#include "lle.cpu(Allegrex).Decoder.h"
    return address + 4;
}

void Allegrex::ICache::CodeBlock::RewriteInstructions(size_t beg, size_t end)
{
    return;
}

#undef IDO

void Allegrex::ICache::RecompileCode::InternalMain()
{
    enum
    {
        label_p32,
        label_p64,
    };

    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    L(label_p32); // call through a 'jmp'
    mov(rcx, rsi);
    // +-----------------------------+ RSP
    // | RIP - Return Caller Address |
    // +---------------------------- + CALL
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    call(qword_rip_ptr[label_p64]);
    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    jmp(rax);

    auto function = &Context::Recompile;

    align(3);

    L(label_p64);
    dq((intptr_t)function);
}

void Allegrex::ICache::TrampolineCode::InternalMain()
{
    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    mov(edx, ICACHE_MEMORY_ADDRESS);
    mov(ebp, dword_ptr[rsi + s32(offsetof(Allegrex::Context, Allegrex::Context::pc))]);
    add(rdx, rbp);  // it is important to keep the translated address into rdx because the function at address rax may need it to recompile
    mov(ebp, dword_ptr[rdx]);
    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    jmp(rbp);
}

void Allegrex::ICache::TraceCode::InternalMain()
{
    enum
    {
        label_p32,
        label_p64,
    };

    // +-----------------------------+ RSP
    // | RIP - Return Caller Address |
    // +-----------------------------+ CALL
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    L(label_p32); // call through a 'call'
    push(rax);
    push(rcx);
    push(rdx);
    push(rbx);
    push(r8);
    push(r9);
    push(r10);
    push(r11);
    mov(edx, dword_ptr[rsp + 8 * (1 + 8)]);
    sub(rsp, 0x28); // 4 registers w/ 16-byte alignment
    mov(rcx, rsi);
    // +-----------------------------+ RSP
    // | RIP - Return Caller Address |
    // +-----------------------------+ CALL QWORD PTR[label_p64]
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R11                         |
    // | R10                         |
    // | R9                          |
    // | R8                          |
    // | RBX                         |
    // | RDX                         |
    // | RCX                         |
    // | RAX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    call(qword_rip_ptr[label_p64]);
    add(rsp, 0x28);
    pop(r11);
    pop(r10);
    pop(r9);
    pop(r8);
    pop(rbx);
    pop(rdx);
    pop(rcx);
    pop(rax);
    ret();
    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+

    auto function = &Context::Trace;

    align(3);
    L(label_p64);
    dq((intptr_t)function);
}

void Allegrex::ICache::SyscallCode::InternalMain()
{
    enum
    {
        label_p32,
        label_p64,
    };

    // +-----------------------------+ RSP
    // | RIP - Return Caller Address |
    // +-----------------------------+ CALL
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    L(label_p32); // call through a 'call'
    sub(rsp, 0x28); // 4 registers w/ 16-byte alignment
    mov(rcx, rsi);
    // +-----------------------------+ RSP
    // | RIP - Return Caller Address |
    // +-----------------------------+ CALL QWORD PTR[label_p64]
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    call(qword_rip_ptr[label_p64]);
    add(rsp, 0x28);
    ret();
    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+

    auto function = &Context::Syscall;

    align(3);
    L(label_p64);
    dq((intptr_t)function);
}

void Allegrex::ICache::CrossInterpretCode::InternalMain()
{
    enum
    {
        label_p32,
        label_p64,
    };

    // +-----------------------------+ RSP
    // | RIP - Return Caller Address |
    // +-----------------------------+ CALL
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    L(label_p32); // call through a 'call'
    push(rax);
    push(rcx);
    push(rdx);
    push(rbx);
    push(r8);
    push(r9);
    push(r10);
    push(r11);
    mov(edx, dword_ptr[rsp + 8 * (1 + 8)]);
    sub(rsp, 0x28); // 4 registers w/ 16-byte alignment
    mov(rcx, rsi);
    // +-----------------------------+ RSP
    // | RIP - Return Caller Address |
    // +-----------------------------+ CALL QWORD PTR[label_p64]
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R11                         |
    // | R10                         |
    // | R9                          |
    // | R8                          |
    // | RBX                         |
    // | RDX                         |
    // | RCX                         |
    // | RAX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+
    call(qword_rip_ptr[label_p64]);
    add(rsp, 0x28);
    pop(r11);
    pop(r10);
    pop(r9);
    pop(r8);
    pop(rbx);
    pop(rdx);
    pop(rcx);
    pop(rax);
    ret();
    // +-----------------------------+ RSP
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | ---                         |
    // | R15                         |
    // | R14                         |
    // | R13                         |
    // | R12                         |
    // | RDI                         |
    // | RSI                         |
    // | RBP                         |
    // | RBX                         |
    // | RIP - Return Caller Address |
    // +-----------------------------+

    auto function = &Context::CrossInterpret;

    align(3);
    L(label_p64);
    dq((intptr_t)function);
}

