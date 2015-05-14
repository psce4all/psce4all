/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

namespace Allegrex
{
    struct ICache
    {
        ICache();

        void Start();
        void Stop();

        struct UnwindInfoFrame0 : Allegrex::jitasm::Frontend
        {
            virtual void InternalMain() override;
        } unwind_info_frame0;

        struct UnwindInfoFrame1 : Allegrex::jitasm::Frontend
        {
            virtual void InternalMain() override;
        } unwind_info_frame1;

        struct UnwindInfoFrame2 : Allegrex::jitasm::Frontend
        {
            virtual void InternalMain() override;
        } unwind_info_frame2;

        struct SharedContext : Allegrex::jitasm::Frontend
        {
            struct Data
            {
                u64 exit_address;
                u64 syscall_address;
                u64 recompile_address;
                u64 trampoline_address;
                u64 cross_interpret_address;
                u64 trace_address;

                // PSP 16-KByte icache consists of 64-byte cache blocks using a 2-way set associative configuration with 8-KByte per way.
                // Each set consist of 128 lines.
                u64 icache_tag[16*128]; // two-way set x 16 instructions x 128 lines
            };

            Data * GetData() { return (Data *)GetCode(); }

            virtual void InternalMain() override;
        } shared_context;

        struct ThreadCode : Allegrex::jitasm::Frontend
        {
            virtual void InternalMain() override;
        } thread_code;

        struct RecompileCode : Allegrex::jitasm::Frontend
        {
            virtual void InternalMain() override;
        } recompile_code;

        struct TrampolineCode : Allegrex::jitasm::Frontend
        {
            virtual void InternalMain() override;
        } trampoline_code;

        struct TraceCode : Allegrex::jitasm::Frontend
        {
            virtual void InternalMain() override;
        } trace_code;

        struct SyscallCode : Allegrex::jitasm::Frontend
        {
            virtual void InternalMain() override;
        } syscall_code;

        struct CrossInterpretCode : Allegrex::jitasm::Frontend
        {
            virtual void InternalMain() override;
        } crossinterpret_code;

        struct CodeBlock : Allegrex::jitasm::Frontend
        {
            typedef Allegrex::jitasm::Gpr    Gpr;
            typedef Allegrex::jitasm::XmmReg Fpr;
            typedef Allegrex::jitasm::XmmReg Vpr;

            /**/  CodeBlock()
            {
            }

            /**/  CodeBlock(u32 pc, size_t size) : initial_address(pc), opcode(*(p32dcache< u32 >(pc)))
            {
                *(p32icache< u32 >(pc)) = u32(GetCode());
            }

            virtual ~CodeBlock()
            {
            }

            __forceinline void gen(Gpr const & src)
            {
                mov(src, src);
            }

            __forceinline void gen(Gpr const & dst, Gpr const & src)
            {
                if (dst.reg_.id != src.reg_.id)
                {
                    mov(src, src);
                    add(src, 0); // trick to help coalescing the allocated register between src and dst nicely
                }
                mov(dst, src);
            }

            __forceinline void kill(Gpr const & dst)
            {
                mov(dst, dst);
            }

            template < typename Ldu, typename Alu, typename Stu >
            __forceinline void alu(Ldu & lo, Alu & bo, Stu & so)
            {
                lo();
                bo();
                so();
            }

            u32   EmitInstruction(u32 address, u32 opcode, bool delayslot);
            void  RewriteInstructions(size_t beg, size_t end);

            virtual void InternalMain() override;

#define __cross_interpret__ if (CROSS_INTERPRETER) { extern bool cross_interpreter_cmp; mov(dword_ptr[rsp], cross_interpreter_cmp ? address : (address + 1)); call(qword_ptr[rdi+s32(offsetof(SharedContext::Data, cross_interpret_address))], true); cross_interpreter_cmp = false; }
#define __label__ if (!delayslot) { L(address); target_address_done.insert(address); source(address); __cross_interpret__ } else source(address); if (TRACE_ALLEGREX_INSTRUCTION) { mov(dword_ptr[rsp], address); call(qword_ptr[rdi + s32(offsetof(SharedContext::Data, trace_address))], true); }
#define __target_label__(address1, address2) u32 target_address = address1; if ((address2)) target_address_next.insert((address2)); target_address_next.insert((address1))
#define __skip_label__(address) u32 skip_address = address

#define __interpreter_jmp__(address) if (INTERPRETER_LIKE) if (!delayslot) { mov(edx, u32((address)+ICACHE_MEMORY_ADDRESS)); mov(ebp, dword_ptr[rdx]); jmp(rbp); }
#define __interpreter_jmp_with_label__(label, address) if (INTERPRETER_LIKE)  { L(label); mov(edx, u32((address)+ICACHE_MEMORY_ADDRESS)); mov(ebp, dword_ptr[rdx]); jmp(rbp); }

#if !defined(__AVX__) 
#define __apply_aluss(alu1, alu2, reg, dst, src1, src2) do { \
    auto lduss = [&]() { movss(reg, src1); }; \
    auto aluss = [&]() { alu1(reg, src2); }; \
    auto stuss = [&]() { movss(dst, reg); }; \
    alu(lduss, aluss, stuss); } while(0)
#else
#define __apply_aluss(alu1, alu2, reg, dst, src1, src2) do { \
    auto lduss = [&]() { vmovss(reg, src1); }; \
    auto aluss = [&]() { alu2(reg, reg, src2); }; \
    auto stuss = [&]() { vmovss(dst, reg); }; \
    alu(lduss, aluss, stuss); } while(0)
#endif

#if !defined(__AVX__) 
#define __apply_movss(reg, dst, src) do { \
    auto lduss = [&]() { movss(reg, src); }; \
    auto aluss = [&]() { }; \
    auto stuss = [&]() { movss(dst, reg); }; \
    alu(lduss, aluss, stuss); } while(0)
#else
#define __apply_movss(reg, dst, src) do { \
    auto lduss = [&]() { vmovss(reg, src); }; \
    auto aluss = [&]() { }; \
    auto stuss = [&]() { vmovss(dst, reg); }; \
    alu(lduss, aluss, stuss); } while(0)
#endif

#define gpr_w(r) (dword_ptr[rsi+s32(offsetof(lle::cpu::Context, gpr[r]))])
#define gpr_h(r) (word_ptr[rsi+s32(offsetof(lle::cpu::Context, gpr[r]))])
#define gpr_b(r) (byte_ptr[rsi+s32(offsetof(lle::cpu::Context, gpr[r]))])
#define fpr_w(r) (dword_ptr[rsi+s32(offsetof(lle::cpu::Context, fpr[r]))])

#define lo_w dword_ptr[rsi+s32(0 + offsetof(lle::cpu::Context, hilo))]
#define hi_w dword_ptr[rsi+s32(4 + offsetof(lle::cpu::Context, hilo))]

#define syscall_q qword_ptr[rsi+s32(offsetof(lle::cpu::Context, doSyscall))]

#include "lle.cpu(Allegrex).Emitter.h"

            u32             initial_address;
            u32             opcode;
            std::set< u32 > target_address_next;
            std::set< u32 > target_address_done;
        };

        std::map< u32, CodeBlock * > blocks;

        RUNTIME_FUNCTION runtime_function_array[4];

        static u32 const cache_size = 16 * 1024;
        static u32 const cache_lines = cache_size / 64;
    };

    extern ICache icache;
}
