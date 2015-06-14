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


void Allegrex::ICache::SharedContext::InternalMain()
{
    dq(0); // debug_flags
    dq(0); // exit_address
    dq(0); // syscall_address;
    dq(0); // recompile_address;
    dq(0); // trampoline_address;
    dq(0); // cross_interpret_address;
    dq(0); // trace_address;

    // PSP 16-KByte icache consists of 64-byte cache blocks using a 2-way set associative configuration with 8-KByte per way.
    // 2 sets. Each set consist of 128 lines. 16 instructions per 64-byte.
    for (auto i = 0; i < 2*128*16; ++i)
    {
        dd(0);
    }
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
    
    db(0x65); mov(qword_ptr[0x00000028], rcx); // mov gs:[0x28], rcx

    mov(rsi, rcx);
    mov(rdi, uint32_t(Allegrex::icache.shared_context.GetData()));
    lea(eax, qword_rip_ptr[label_exit]);
    lea(rbp, qword_ptr[rsp - 8]);
    mov(dword_ptr[rdi][s32(offsetof(SharedContext::Data, Data::exit_address))], eax);
    mov(qword_ptr[rsi][s32(offsetof(Context, Context::return_address))], rbp);

    mov(edx, ICACHE_MEMORY_ADDRESS);
    mov(eax, dword_ptr[rsi + s32(offsetof(Context, Context::pc))]);
    add(rdx, rax);  // it is important to keep the translated address into rdx because the function at address rax may need it to recompile
    mov(ebp, dword_ptr[rdx]);
    jmp(rbp);

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

    auto shared_context_pointer = shared_context.GetData();

    auto trace_pointer = icache.trace_code.GetCode();
    auto crossinterpret_pointer = icache.crossinterpret_code.GetCode();
    auto syscall_pointer = icache.syscall_code.GetCode();
    auto thread_pointer = icache.thread_code.GetCode();
    auto recompile_pointer = icache.recompile_code.GetCode();
    auto trampoline_pointer = icache.trampoline_code.GetCode();

    shared_context_pointer->syscall_address = u64(syscall_pointer);
    shared_context_pointer->recompile_address = u64(recompile_pointer);
    shared_context_pointer->trampoline_address = u64(trampoline_pointer);
    shared_context_pointer->cross_interpret_address = u64(crossinterpret_pointer);
    shared_context_pointer->trace_address = u64(trace_pointer);

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

__noinline u64 lle::cpu::Context::Recompile(Context * that, u32 address)
{
    hal::npa::StartEvent(cpu_icache);
    u32 pc = address - ICACHE_MEMORY_ADDRESS;
    if (ICACHE_SLOW_MODE)
    {
        auto pc_start = pc & -64;
        for (auto pc = pc_start; pc < pc_start + 64; pc += 4)
        {
            auto & block = icache.blocks[pc];
            if (block)
            {
                if (*p32u32(pc) != block->opcode)
                {
                    delete block;
                    block = new ICache::CodeBlock(pc, 4);
                }
            }
            else
            {
                block = new ICache::CodeBlock(pc, 4);
            }
        }
    }
    else
    {
        auto & block = icache.blocks[pc];
        if (block)
        {
            if (*p32u32(pc) != block->opcode)
            {
                delete block;
                block = new ICache::CodeBlock(pc, 4);
            }
        }
        else
        {
            block = new ICache::CodeBlock(pc, 4);
        }
    }
    hal::npa::StopEvent(cpu_icache);
    return (u64(address) << 32ULL) | *((u32 *)(address));
}

__noinline void lle::cpu::Context::SetTrampoline(u32 address)
{
    pc = address;
    if (return_address) *return_address = icache.shared_context.GetData()->trampoline_address;
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
        //if ((pc - 0x08800000) > (0x0C000000 - 0x08800000))
        //{
        //    pc = 0;
        //    //__debugbreak();
        //    break;
        //}

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
}

#define IDO(x) do { address = emit$##x(address, opcode, delayslot); goto epilog; } while (-1 == __LINE__)

__noinline u32 Allegrex::ICache::CodeBlock::EmitInstruction(u32 address, u32 opcode, bool delayslot)
{
    EmitProlog(address, opcode, delayslot);
#include "lle.cpu(Allegrex).Decoder.h"
    address += 4;
epilog:
    return EmitEpilog(address, opcode, delayslot);
}

void Allegrex::ICache::CodeBlock::RewriteInstructions(size_t beg, size_t end)
{
    return;
}

u32 Allegrex::ICache::CodeBlock::SetTargetLabel(u32 taken_address, u32 untaken_address /*= 0*/)
{
    if (untaken_address)
    {
        target_address_next.insert(untaken_address);
    }
    target_address_next.insert(taken_address);
    return taken_address;
}

u32 Allegrex::ICache::CodeBlock::SetSkipLabel(u32 address)
{
    return address;
}

void Allegrex::ICache::CodeBlock::EmitCrossInterpret(u32 address, u32 opcode, bool delayslot)
{
    extern bool cross_interpreter_cmp;
    mov(dword_ptr[rsp], cross_interpreter_cmp ? address : (address + 1));
    call(qword_ptr[rdi + s32(offsetof(SharedContext::Data, cross_interpret_address))], true);
    cross_interpreter_cmp = false;
}

namespace Allegrex
{
    enum ICacheState
    {
        icache_hit = 1,
        icache_miss,
    };
}

static auto const Prolog_MainOpcode = 0x0000000000000200LL;

void Allegrex::ICache::CodeBlock::EmitProlog(u32 address, u32 opcode, bool delayslot)
{
    if (!delayslot)
    {
        if (INTERPRETER_LIKE)
        {
            if (Allegrex::use_debug_server)
            {
                switch (u64(opcode >> 26))
                {
                case 0x00:
                    if (opcode == 03e00008 /* JR $RA */)
                    {
                        goto return_instruction;
                    }
                    else if ((opcode & 0x0000003F) == 0x09) /* JALR */
                    {
                        goto call_instruction;
                    }
                    else
                    {
                        goto default_instruction;
                    }
                    break;
                case 0x01:
                    switch (opcode & 0x001F000000)
                    {
                    case 0x00100000: /* BLTZAL */
                    case 0x00110000: /* BGEZAL */
                    case 0x00120000: /* BLTZALL */
                    case 0x00130000: /* BGEZALL */
                        goto call_instruction;
                    default:
                        goto default_instruction;
                    }
                    break;
                return_instruction:
                    mov(eax, dword_ptr[rdi]);
                    test(eax, eax);
                    dw(0x0175); // jnz($+1)
                    int3();
                    movsx(eax, byte_ptr[rdi + 6]);
                    sub(dword_ptr[rdi], eax);
                    dw(0x0475); // jnz($+4)
                    mov(byte_ptr[rdi + 5], 0);
                    break;
                call_instruction:
                case 0x03: /* JAL */
                    movsx(eax, byte_ptr[rdi + 5]);
                    add(dword_ptr[rdi], eax);
                    dw(0x0175); // jnz($+1)
                    int3();
                    mov(byte_ptr[rdi + 6], 1);
                    break;
                default_instruction:
                default:
                    movsx(eax, byte_ptr[rdi + 4]);
                    sub(dword_ptr[rdi], eax);
                    dw(0x0175); // jnz($+1)
                    int3();
                    break;
                }
            }
            if (address & 0x40000000)
            {
                cmp(dword_ptr[rdx + DCACHE_MEMORY_ADDRESS - ICACHE_MEMORY_ADDRESS], opcode);
                jnz(icache_miss);
            }
            else if (ICACHE_SLOW_MODE)
            {
                auto index = s32(address & (4 * 16 * 128 - 1));
                mov(rcx, qword_ptr[rdi + 2 * index + s32(offsetof(SharedContext::Data, icache_tag[0]))]);
                cmp(ecx, edx);
                jz(icache_hit);
                rol(rcx, 32);
                cmp(ecx, edx);
                jnz(icache_miss);
                mov(qword_ptr[rdi + 2 * index + s32(offsetof(SharedContext::Data, icache_tag[0]))], rcx);
                L(icache_hit);
            }
        }
        L(address);
        target_address_done.insert(address);
        source(address);
        if (CROSS_INTERPRETER)
        {
            EmitCrossInterpret(address, opcode, delayslot);
        }
    }
    else
    {
        source(address);
    }
    if (TRACE_ALLEGREX_INSTRUCTION)
    {
        mov(dword_ptr[rsp], address);
        call(qword_ptr[rdi + s32(offsetof(SharedContext::Data, trace_address))], true);
    }
}

u32 Allegrex::ICache::CodeBlock::EmitEpilog(u32 address, u32 opcode, bool delayslot)
{
    if (INTERPRETER_LIKE)
    {
        if (!delayslot && address)
        {
            mov(edx, u32((address)+ICACHE_MEMORY_ADDRESS));
            mov(ebp, dword_ptr[rdx]);
            jmp(rbp);
        }
        if (ICACHE_SLOW_MODE)
        {
            L(icache_miss);
            mov(ebp, u32(icache.shared_context.GetData()->recompile_address));
            jmp(rbp);
        }
    }

    return address;
}

void Allegrex::ICache::CodeBlock::EmitInterpreterBranch(u32 address, u32 opcode, bool delayslot)
{
    if (INTERPRETER_LIKE)
    {
        if (!delayslot)
        {
            mov(edx, u32((address)+ICACHE_MEMORY_ADDRESS));
            mov(ebp, dword_ptr[rdx]);
            jmp(rbp);
        }
        if (ICACHE_SLOW_MODE)
        {
            L(icache_miss);
            mov(ebp, u32(icache.shared_context.GetData()->recompile_address));
            jmp(rbp);
        }
    }
}


void Allegrex::ICache::CodeBlock::EmitInterpreterBranch(u32 label, u32 address, u32 opcode, bool delayslot)
{
    if (INTERPRETER_LIKE)
    {
        L(label);
        mov(edx, u32((address)+ICACHE_MEMORY_ADDRESS));
        mov(ebp, dword_ptr[rdx]);
        jmp(rbp);
        if (ICACHE_SLOW_MODE)
        {
            L(icache_miss);
            mov(ebp, u32(icache.shared_context.GetData()->recompile_address));
            jmp(rbp);
        }
    }
}

#undef IDO

void Allegrex::ICache::RecompileCode::InternalMain()
{
    enum
    {
        label_p32,
        label_p64,
        label_skip,
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
    mov(rdx, rax);
    mov(ebp, eax);
    shr(rdx, 32);
    if (ICACHE_SLOW_MODE)
    {
        test(edx, 0x40000000);
        jnz(label_skip);
        mov(rax, -s32(ICACHE_MEMORY_ADDRESS));
        add(rax, rdx);
        and(rax, 4*16*128-1);
        mov(dword_ptr[rdi + 2 * rax + s32(offsetof(SharedContext::Data, icache_tag[0]))], edx);
        L(label_skip);
    }
    jmp(rbp);

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

