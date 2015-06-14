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

        struct Fragment : Allegrex::jitasm::Frontend
        {
            void * GetFragment() { return GetCode(); }
        };

        struct DataFragment : Fragment
        {
            void * GetData() { return GetFragment(); }
        };

        struct CodeFragment : Fragment
        {
            void * GetCode() { return GetFragment(); }
        };

        struct UnwindInfoFrame0 :DataFragment
        {
            virtual void InternalMain() override;
        } unwind_info_frame0;

        struct UnwindInfoFrame1 : DataFragment
        {
            virtual void InternalMain() override;
        } unwind_info_frame1;

        struct UnwindInfoFrame2 : DataFragment
        {
            virtual void InternalMain() override;
        } unwind_info_frame2;

        struct SharedContext : DataFragment
        {
            struct Data
            {
                u64 debug_flags;
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

        struct ThreadCode : CodeFragment
        {
            virtual void InternalMain() override;
        } thread_code;

        struct RecompileCode : CodeFragment
        {
            virtual void InternalMain() override;
        } recompile_code;

        struct TrampolineCode : CodeFragment
        {
            virtual void InternalMain() override;
        } trampoline_code;

        struct TraceCode : CodeFragment
        {
            virtual void InternalMain() override;
        } trace_code;

        struct SyscallCode : CodeFragment
        {
            virtual void InternalMain() override;
        } syscall_code;

        struct CrossInterpretCode : CodeFragment
        {
            virtual void InternalMain() override;
        } crossinterpret_code;

        struct CodeBlock : CodeFragment
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

            u32   SetTargetLabel(u32 taken_address, u32 untaken_address = 0);
            u32   SetSkipLabel(u32 address);

            void  EmitCrossInterpret(u32 address, u32 opcode, bool delayslot);
            void  EmitProlog(u32 address, u32 opcode, bool delayslot);
            u32   EmitEpilog(u32 address, u32 opcode, bool delayslot);
            void  EmitInterpreterBranch(u32 address, u32 opcode, bool delayslot);
            void  EmitInterpreterBranch(u32 label, u32 address, u32 opcode, bool delayslot);
            u32   EmitInstruction(u32 address, u32 opcode, bool delayslot);
            void  RewriteInstructions(size_t beg, size_t end);

            virtual void InternalMain() override;

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

#define lo_w (dword_ptr[rsi+s32(0 + offsetof(lle::cpu::Context, hilo))])
#define hi_w (dword_ptr[rsi+s32(4 + offsetof(lle::cpu::Context, hilo))])


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
