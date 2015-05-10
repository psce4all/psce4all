/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <cstdio>
#include <cstdlib>

namespace Allegrex
{
    struct InstructionBase;
    struct Instruction;
    template< int signature, int mask > struct Instruction$;

    struct InstructionBase
    {
        virtual ~InstructionBase() {}

    protected:
        InstructionBase() {}
    };

    struct Context;

    struct Instruction : InstructionBase
    {
        virtual u64 Infos() { return 0; }

        virtual ~Instruction() {}

        virtual char const * OpcodeName() = 0;

        virtual void Interpret(Allegrex::Context & processor, u32 opcode) = 0;

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment) = 0;

        virtual u64 & GetCount() = 0;

        char const * GetSyscallName(u32 code) const;

        static inline u32 rd(u32 opcode) { return ((((u32)opcode) >> 11)&31); }
        static inline u32 rt(u32 opcode) { return ((((u32)opcode) >> 16)&31); }
        static inline u32 rs(u32 opcode) { return ((((u32)opcode) >> 21)&31); }

        static inline u32 sa(u32 opcode) { return ((((u32)opcode) >> 6)&31); }

        static inline s32 simm16(u32 opcode) { return (s32)(s16)opcode; }
        static inline u32 uimm16(u32 opcode) { return (u32)(u16)opcode; }
        static inline u32 uimm20(u32 opcode) { return (opcode >> 6) & 0x000FFFFF; }
        static inline u32 uimm24(u32 opcode) { return opcode & 0x00FFFFFF; }
        static inline u32 uimm26(u32 opcode) { return opcode & 0x03FFFFFF; }

        static inline u32 fd(u32 opcode) { return ((((u32)opcode) >> 6)&31); }
        static inline u32 fs(u32 opcode) { return ((((u32)opcode) >> 11)&31); }
        static inline u32 ft(u32 opcode) { return ((((u32)opcode) >> 16)&31); }

        static inline u32 cconds(u32 opcode) { return ((((u32)opcode) >> 0)&15); }

        static inline u32 vsize(u32 opcode) { return (1 + ((opcode >> 7) & 1) + (((opcode >> 15) & 1) << 1)); }

        static inline u32 vt(u32 opcode) { return ((opcode >> 16) & 127); }
        static inline u32 vs(u32 opcode) { return ((opcode >>  8) & 127); }
        static inline u32 vd(u32 opcode) { return ((opcode >>  0) & 127); }

        static inline u32 vt51(u32 opcode) { return (((opcode >> 16) & 31)|(((opcode >> 0) & 1) << 5)); }
        static inline u32 vt52(u32 opcode) { return (((opcode >> 16) & 31)|(((opcode >> 0) & 3) << 5)); }

        static inline s32 simm14(u32 opcode) { return (s32)(s16)(opcode & 0x0000FFFC); }
        static inline u32 uimm8(u32 opcode) { return ((opcode >> 16) & 255); }
        static inline u32 uimm5(u32 opcode) { return ((opcode >> 16) & 31); }
        static inline u32 uimm4(u32 opcode) { return ((opcode >>  0) & 15); }
        static inline u32 uimm3(u32 opcode) { return ((opcode >> 16) & 7); }
    };

    struct InstructionUnknown : Instruction
    {
        static InstructionUnknown & Self()
        {
            static InstructionUnknown insn;
            return insn;
        }

        static Instruction * GetInstance()
        {
            return &InstructionUnknown::Self();
        }

        virtual char const * OpcodeName()
        {
            return "???";
        }

        virtual u64 & GetCount()
        {
            static u64 dummy = u64(); return dummy;
        }

        virtual void Interpret(Allegrex::Context &processor, u32 opcode)
        {
            (void)&processor;
            (void)opcode;
        }

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment)
        {
            (void)address;
            ::strcpy(opcode_name, this->OpcodeName());
            ::strcpy(operands, "");
            ::sprintf(comment, "unknown or reserved instruction 0x%08X", opcode);
        }

        virtual u64 Infos() { return 0LL; }
    };

    template< int signature, int mask > struct Instruction$ : InstructionUnknown
    {
    };

    extern InstructionUnknown & reserved_instruction;

    extern char const * gpr_name[32];

    extern char const * fpr_name[32];

    extern char const * vpr_name[4][128];

    extern char const * mpr_name[4][128];

    extern char const * vfpu_constant[32];

    extern char const * fcr_name[32];

    extern char const * cop0_name[32];

    extern char const * vsuffix[4];

    extern char const * vpfx_name[4];

    extern char const * cconds_name[16];

    extern char const * vcond_name[16];
}

#include "lle.cpu(Allegrex).Instructions.h"
