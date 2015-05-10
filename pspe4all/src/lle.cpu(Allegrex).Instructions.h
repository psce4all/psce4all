/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "lle.cpu(Allegrex).Instruction.h"

namespace Allegrex
{
    /* SLL */
    template< > struct Instruction$< 0x00000000, 0xFFE0003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SLL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000000, 0xFFE0003F > Instruction$SLL;

    extern Instruction$SLL & SLL;

    /* SRL */
    template< > struct Instruction$< 0x00000002, 0xFFE0003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SRL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000002, 0xFFE0003F > Instruction$SRL;

    extern Instruction$SRL & SRL;

    /* SRA */
    template< > struct Instruction$< 0x00000003, 0xFFE0003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SRA"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000003, 0xFFE0003F > Instruction$SRA;

    extern Instruction$SRA & SRA;

    /* SLLV */
    template< > struct Instruction$< 0x00000004, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SLLV"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000004, 0xFC0007FF > Instruction$SLLV;

    extern Instruction$SLLV & SLLV;

    /* SRLV */
    template< > struct Instruction$< 0x00000006, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SRLV"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000006, 0xFC0007FF > Instruction$SRLV;

    extern Instruction$SRLV & SRLV;

    /* SRAV */
    template< > struct Instruction$< 0x00000007, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SRAV"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000007, 0xFC0007FF > Instruction$SRAV;

    extern Instruction$SRAV & SRAV;

    /* JR */
    template< > struct Instruction$< 0x00000008, 0xFC1FFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "JR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000008, 0xFC1FFFFF > Instruction$JR;

    extern Instruction$JR & JR;

    /* JALR */
    template< > struct Instruction$< 0x00000009, 0xFC1F07FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "JALR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000009, 0xFC1F07FF > Instruction$JALR;

    extern Instruction$JALR & JALR;

    /* MOVZ */
    template< > struct Instruction$< 0x0000000A, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MOVZ"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000000A, 0xFC0007FF > Instruction$MOVZ;

    extern Instruction$MOVZ & MOVZ;

    /* MOVN */
    template< > struct Instruction$< 0x0000000B, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MOVN"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000000B, 0xFC0007FF > Instruction$MOVN;

    extern Instruction$MOVN & MOVN;

    /* SYSCALL */
    template< > struct Instruction$< 0x0000000C, 0xFC00003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SYSCALL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000000C, 0xFC00003F > Instruction$SYSCALL;

    extern Instruction$SYSCALL & SYSCALL;

    /* BREAK */
    template< > struct Instruction$< 0x0000000D, 0xFC00003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BREAK"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000000D, 0xFC00003F > Instruction$BREAK;

    extern Instruction$BREAK & BREAK;

    /* SYNC */
    template< > struct Instruction$< 0x0000000F, 0xFFFFFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SYNC"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000000F, 0xFFFFFFFF > Instruction$SYNC;

    extern Instruction$SYNC & SYNC;

    /* MFHI */
    template< > struct Instruction$< 0x00000010, 0xFFFF07FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MFHI"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000010, 0xFFFF07FF > Instruction$MFHI;

    extern Instruction$MFHI & MFHI;

    /* MTHI */
    template< > struct Instruction$< 0x00000011, 0xFC1FFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MTHI"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000011, 0xFC1FFFFF > Instruction$MTHI;

    extern Instruction$MTHI & MTHI;

    /* MFLO */
    template< > struct Instruction$< 0x00000012, 0xFFFF07FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MFLO"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000012, 0xFFFF07FF > Instruction$MFLO;

    extern Instruction$MFLO & MFLO;

    /* MTLO */
    template< > struct Instruction$< 0x00000013, 0xFC1FFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MTLO"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000013, 0xFC1FFFFF > Instruction$MTLO;

    extern Instruction$MTLO & MTLO;

    /* CLZ */
    template< > struct Instruction$< 0x00000016, 0xFC1F07FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "CLZ"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000016, 0xFC1F07FF > Instruction$CLZ;

    extern Instruction$CLZ & CLZ;

    /* CLO */
    template< > struct Instruction$< 0x00000017, 0xFC1F07FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "CLO"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000017, 0xFC1F07FF > Instruction$CLO;

    extern Instruction$CLO & CLO;

    /* MULT */
    template< > struct Instruction$< 0x00000018, 0xFC00FFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MULT"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000018, 0xFC00FFFF > Instruction$MULT;

    extern Instruction$MULT & MULT;

    /* MULTU */
    template< > struct Instruction$< 0x00000019, 0xFC00FFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MULTU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000019, 0xFC00FFFF > Instruction$MULTU;

    extern Instruction$MULTU & MULTU;

    /* DIV */
    template< > struct Instruction$< 0x0000001A, 0xFC00FFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DIV"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000001A, 0xFC00FFFF > Instruction$DIV;

    extern Instruction$DIV & DIV;

    /* DIVU */
    template< > struct Instruction$< 0x0000001B, 0xFC00FFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DIVU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000001B, 0xFC00FFFF > Instruction$DIVU;

    extern Instruction$DIVU & DIVU;

    /* MADD */
    template< > struct Instruction$< 0x0000001C, 0xFC00FFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MADD"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000001C, 0xFC00FFFF > Instruction$MADD;

    extern Instruction$MADD & MADD;

    /* MADDU */
    template< > struct Instruction$< 0x0000001D, 0xFC00FFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MADDU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000001D, 0xFC00FFFF > Instruction$MADDU;

    extern Instruction$MADDU & MADDU;

    /* ADD */
    template< > struct Instruction$< 0x00000020, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ADD"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000020, 0xFC0007FF > Instruction$ADD;

    extern Instruction$ADD & ADD;

    /* ADDU */
    template< > struct Instruction$< 0x00000021, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ADDU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000021, 0xFC0007FF > Instruction$ADDU;

    extern Instruction$ADDU & ADDU;

    /* SUB */
    template< > struct Instruction$< 0x00000022, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SUB"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000022, 0xFC0007FF > Instruction$SUB;

    extern Instruction$SUB & SUB;

    /* SUBU */
    template< > struct Instruction$< 0x00000023, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SUBU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000023, 0xFC0007FF > Instruction$SUBU;

    extern Instruction$SUBU & SUBU;

    /* AND */
    template< > struct Instruction$< 0x00000024, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "AND"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000024, 0xFC0007FF > Instruction$AND;

    extern Instruction$AND & AND;

    /* OR */
    template< > struct Instruction$< 0x00000025, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "OR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000025, 0xFC0007FF > Instruction$OR;

    extern Instruction$OR & OR;

    /* XOR */
    template< > struct Instruction$< 0x00000026, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "XOR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000026, 0xFC0007FF > Instruction$XOR;

    extern Instruction$XOR & XOR;

    /* NOR */
    template< > struct Instruction$< 0x00000027, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "NOR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000027, 0xFC0007FF > Instruction$NOR;

    extern Instruction$NOR & NOR;

    /* SLT */
    template< > struct Instruction$< 0x0000002A, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SLT"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000002A, 0xFC0007FF > Instruction$SLT;

    extern Instruction$SLT & SLT;

    /* SLTU */
    template< > struct Instruction$< 0x0000002B, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SLTU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000002B, 0xFC0007FF > Instruction$SLTU;

    extern Instruction$SLTU & SLTU;

    /* MAX */
    template< > struct Instruction$< 0x0000002C, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MAX"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000002C, 0xFC0007FF > Instruction$MAX;

    extern Instruction$MAX & MAX;

    /* MIN */
    template< > struct Instruction$< 0x0000002D, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MIN"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000002D, 0xFC0007FF > Instruction$MIN;

    extern Instruction$MIN & MIN;

    /* MSUB */
    template< > struct Instruction$< 0x0000002E, 0xFC00FFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MSUB"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000002E, 0xFC00FFFF > Instruction$MSUB;

    extern Instruction$MSUB & MSUB;

    /* MSUBU */
    template< > struct Instruction$< 0x0000002F, 0xFC00FFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MSUBU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0000002F, 0xFC00FFFF > Instruction$MSUBU;

    extern Instruction$MSUBU & MSUBU;

    /* ROTRV */
    template< > struct Instruction$< 0x00000046, 0xFC0007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ROTRV"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00000046, 0xFC0007FF > Instruction$ROTRV;

    extern Instruction$ROTRV & ROTRV;

    /* ROTR */
    template< > struct Instruction$< 0x00200002, 0xFFE0003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ROTR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x00200002, 0xFFE0003F > Instruction$ROTR;

    extern Instruction$ROTR & ROTR;

    /* BLTZ */
    template< > struct Instruction$< 0x04000000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BLTZ"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x04000000, 0xFC1F0000 > Instruction$BLTZ;

    extern Instruction$BLTZ & BLTZ;

    /* BGEZ */
    template< > struct Instruction$< 0x04010000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BGEZ"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x04010000, 0xFC1F0000 > Instruction$BGEZ;

    extern Instruction$BGEZ & BGEZ;

    /* BLTZL */
    template< > struct Instruction$< 0x04020000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BLTZL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x04020000, 0xFC1F0000 > Instruction$BLTZL;

    extern Instruction$BLTZL & BLTZL;

    /* BGEZL */
    template< > struct Instruction$< 0x04030000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BGEZL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x04030000, 0xFC1F0000 > Instruction$BGEZL;

    extern Instruction$BGEZL & BGEZL;

    /* BLTZAL */
    template< > struct Instruction$< 0x04100000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BLTZAL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x04100000, 0xFC1F0000 > Instruction$BLTZAL;

    extern Instruction$BLTZAL & BLTZAL;

    /* BGEZAL */
    template< > struct Instruction$< 0x04110000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BGEZAL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x04110000, 0xFC1F0000 > Instruction$BGEZAL;

    extern Instruction$BGEZAL & BGEZAL;

    /* BLTZALL */
    template< > struct Instruction$< 0x04120000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BLTZALL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x04120000, 0xFC1F0000 > Instruction$BLTZALL;

    extern Instruction$BLTZALL & BLTZALL;

    /* BGEZALL */
    template< > struct Instruction$< 0x04130000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BGEZALL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x04130000, 0xFC1F0000 > Instruction$BGEZALL;

    extern Instruction$BGEZALL & BGEZALL;

    /* J */
    template< > struct Instruction$< 0x08000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "J"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x08000000, 0xFC000000 > Instruction$J;

    extern Instruction$J & J;

    /* JAL */
    template< > struct Instruction$< 0x0C000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "JAL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x0C000000, 0xFC000000 > Instruction$JAL;

    extern Instruction$JAL & JAL;

    /* BEQ */
    template< > struct Instruction$< 0x10000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BEQ"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x10000000, 0xFC000000 > Instruction$BEQ;

    extern Instruction$BEQ & BEQ;

    /* BNE */
    template< > struct Instruction$< 0x14000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BNE"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x14000000, 0xFC000000 > Instruction$BNE;

    extern Instruction$BNE & BNE;

    /* BLEZ */
    template< > struct Instruction$< 0x18000000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BLEZ"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x18000000, 0xFC1F0000 > Instruction$BLEZ;

    extern Instruction$BLEZ & BLEZ;

    /* BGTZ */
    template< > struct Instruction$< 0x1C000000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BGTZ"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x1C000000, 0xFC1F0000 > Instruction$BGTZ;

    extern Instruction$BGTZ & BGTZ;

    /* ADDI */
    template< > struct Instruction$< 0x20000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ADDI"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x20000000, 0xFC000000 > Instruction$ADDI;

    extern Instruction$ADDI & ADDI;

    /* ADDIU */
    template< > struct Instruction$< 0x24000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ADDIU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x24000000, 0xFC000000 > Instruction$ADDIU;

    extern Instruction$ADDIU & ADDIU;

    /* SLTI */
    template< > struct Instruction$< 0x28000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SLTI"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x28000000, 0xFC000000 > Instruction$SLTI;

    extern Instruction$SLTI & SLTI;

    /* SLTIU */
    template< > struct Instruction$< 0x2C000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SLTIU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x2C000000, 0xFC000000 > Instruction$SLTIU;

    extern Instruction$SLTIU & SLTIU;

    /* ANDI */
    template< > struct Instruction$< 0x30000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ANDI"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x30000000, 0xFC000000 > Instruction$ANDI;

    extern Instruction$ANDI & ANDI;

    /* ORI */
    template< > struct Instruction$< 0x34000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ORI"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x34000000, 0xFC000000 > Instruction$ORI;

    extern Instruction$ORI & ORI;

    /* XORI */
    template< > struct Instruction$< 0x38000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "XORI"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x38000000, 0xFC000000 > Instruction$XORI;

    extern Instruction$XORI & XORI;

    /* LUI */
    template< > struct Instruction$< 0x3C000000, 0xFFE00000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LUI"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x3C000000, 0xFFE00000 > Instruction$LUI;

    extern Instruction$LUI & LUI;

    /* MFC0 */
    template< > struct Instruction$< 0x40000000, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MFC0"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x40000000, 0xFFE007FF > Instruction$MFC0;

    extern Instruction$MFC0 & MFC0;

    /* CFC0 */
    template< > struct Instruction$< 0x40400000, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "CFC0"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x40400000, 0xFFE007FF > Instruction$CFC0;

    extern Instruction$CFC0 & CFC0;

    /* MTC0 */
    template< > struct Instruction$< 0x40800000, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MTC0"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x40800000, 0xFFE007FF > Instruction$MTC0;

    extern Instruction$MTC0 & MTC0;

    /* CTC0 */
    template< > struct Instruction$< 0x40C00000, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "CTC0"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x40C00000, 0xFFE007FF > Instruction$CTC0;

    extern Instruction$CTC0 & CTC0;

    /* ERET */
    template< > struct Instruction$< 0x42000018, 0xFFFFFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ERET"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x42000018, 0xFFFFFFFF > Instruction$ERET;

    extern Instruction$ERET & ERET;

    /* MFC1 */
    template< > struct Instruction$< 0x44000000, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MFC1"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x44000000, 0xFFE007FF > Instruction$MFC1;

    extern Instruction$MFC1 & MFC1;

    /* CFC1 */
    template< > struct Instruction$< 0x44400000, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "CFC1"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x44400000, 0xFFE007FF > Instruction$CFC1;

    extern Instruction$CFC1 & CFC1;

    /* MTC1 */
    template< > struct Instruction$< 0x44800000, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MTC1"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x44800000, 0xFFE007FF > Instruction$MTC1;

    extern Instruction$MTC1 & MTC1;

    /* CTC1 */
    template< > struct Instruction$< 0x44C00000, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "CTC1"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x44C00000, 0xFFE007FF > Instruction$CTC1;

    extern Instruction$CTC1 & CTC1;

    /* BC1F */
    template< > struct Instruction$< 0x45000000, 0xFFFF0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BC1F"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x45000000, 0xFFFF0000 > Instruction$BC1F;

    extern Instruction$BC1F & BC1F;

    /* BC1T */
    template< > struct Instruction$< 0x45010000, 0xFFFF0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BC1T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x45010000, 0xFFFF0000 > Instruction$BC1T;

    extern Instruction$BC1T & BC1T;

    /* BC1FL */
    template< > struct Instruction$< 0x45020000, 0xFFFF0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BC1FL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x45020000, 0xFFFF0000 > Instruction$BC1FL;

    extern Instruction$BC1FL & BC1FL;

    /* BC1TL */
    template< > struct Instruction$< 0x45030000, 0xFFFF0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BC1TL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x45030000, 0xFFFF0000 > Instruction$BC1TL;

    extern Instruction$BC1TL & BC1TL;

    /* ADD_S */
    template< > struct Instruction$< 0x46000000, 0xFFE0003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ADD_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000000, 0xFFE0003F > Instruction$ADD_S;

    extern Instruction$ADD_S & ADD_S;

    /* SUB_S */
    template< > struct Instruction$< 0x46000001, 0xFFE0003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SUB_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000001, 0xFFE0003F > Instruction$SUB_S;

    extern Instruction$SUB_S & SUB_S;

    /* MUL_S */
    template< > struct Instruction$< 0x46000002, 0xFFE0003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MUL_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000002, 0xFFE0003F > Instruction$MUL_S;

    extern Instruction$MUL_S & MUL_S;

    /* DIV_S */
    template< > struct Instruction$< 0x46000003, 0xFFE0003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DIV_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000003, 0xFFE0003F > Instruction$DIV_S;

    extern Instruction$DIV_S & DIV_S;

    /* SQRT_S */
    template< > struct Instruction$< 0x46000004, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SQRT_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000004, 0xFFFF003F > Instruction$SQRT_S;

    extern Instruction$SQRT_S & SQRT_S;

    /* ABS_S */
    template< > struct Instruction$< 0x46000005, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ABS_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000005, 0xFFFF003F > Instruction$ABS_S;

    extern Instruction$ABS_S & ABS_S;

    /* MOV_S */
    template< > struct Instruction$< 0x46000006, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MOV_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000006, 0xFFFF003F > Instruction$MOV_S;

    extern Instruction$MOV_S & MOV_S;

    /* NEG_S */
    template< > struct Instruction$< 0x46000007, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "NEG_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000007, 0xFFFF003F > Instruction$NEG_S;

    extern Instruction$NEG_S & NEG_S;

    /* ROUND_W_S */
    template< > struct Instruction$< 0x4600000C, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ROUND_W_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600000C, 0xFFFF003F > Instruction$ROUND_W_S;

    extern Instruction$ROUND_W_S & ROUND_W_S;

    /* TRUNC_W_S */
    template< > struct Instruction$< 0x4600000D, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "TRUNC_W_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600000D, 0xFFFF003F > Instruction$TRUNC_W_S;

    extern Instruction$TRUNC_W_S & TRUNC_W_S;

    /* CEIL_W_S */
    template< > struct Instruction$< 0x4600000E, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "CEIL_W_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600000E, 0xFFFF003F > Instruction$CEIL_W_S;

    extern Instruction$CEIL_W_S & CEIL_W_S;

    /* FLOOR_W_S */
    template< > struct Instruction$< 0x4600000F, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "FLOOR_W_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600000F, 0xFFFF003F > Instruction$FLOOR_W_S;

    extern Instruction$FLOOR_W_S & FLOOR_W_S;

    /* CVT_W_S */
    template< > struct Instruction$< 0x46000024, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "CVT_W_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000024, 0xFFFF003F > Instruction$CVT_W_S;

    extern Instruction$CVT_W_S & CVT_W_S;

    /* C_F_S */
    template< > struct Instruction$< 0x46000030, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_F_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000030, 0xFFE007FF > Instruction$C_F_S;

    extern Instruction$C_F_S & C_F_S;

    /* C_UN_S */
    template< > struct Instruction$< 0x46000031, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_UN_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000031, 0xFFE007FF > Instruction$C_UN_S;

    extern Instruction$C_UN_S & C_UN_S;

    /* C_EQ_S */
    template< > struct Instruction$< 0x46000032, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_EQ_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000032, 0xFFE007FF > Instruction$C_EQ_S;

    extern Instruction$C_EQ_S & C_EQ_S;

    /* C_UEQ_S */
    template< > struct Instruction$< 0x46000033, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_UEQ_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000033, 0xFFE007FF > Instruction$C_UEQ_S;

    extern Instruction$C_UEQ_S & C_UEQ_S;

    /* C_OLT_S */
    template< > struct Instruction$< 0x46000034, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_OLT_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000034, 0xFFE007FF > Instruction$C_OLT_S;

    extern Instruction$C_OLT_S & C_OLT_S;

    /* C_ULT_S */
    template< > struct Instruction$< 0x46000035, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_ULT_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000035, 0xFFE007FF > Instruction$C_ULT_S;

    extern Instruction$C_ULT_S & C_ULT_S;

    /* C_OLE_S */
    template< > struct Instruction$< 0x46000036, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_OLE_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000036, 0xFFE007FF > Instruction$C_OLE_S;

    extern Instruction$C_OLE_S & C_OLE_S;

    /* C_ULE_S */
    template< > struct Instruction$< 0x46000037, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_ULE_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000037, 0xFFE007FF > Instruction$C_ULE_S;

    extern Instruction$C_ULE_S & C_ULE_S;

    /* C_SF_S */
    template< > struct Instruction$< 0x46000038, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_SF_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000038, 0xFFE007FF > Instruction$C_SF_S;

    extern Instruction$C_SF_S & C_SF_S;

    /* C_NGLE_S */
    template< > struct Instruction$< 0x46000039, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_NGLE_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46000039, 0xFFE007FF > Instruction$C_NGLE_S;

    extern Instruction$C_NGLE_S & C_NGLE_S;

    /* C_SEQ_S */
    template< > struct Instruction$< 0x4600003A, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_SEQ_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600003A, 0xFFE007FF > Instruction$C_SEQ_S;

    extern Instruction$C_SEQ_S & C_SEQ_S;

    /* C_NGL_S */
    template< > struct Instruction$< 0x4600003B, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_NGL_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600003B, 0xFFE007FF > Instruction$C_NGL_S;

    extern Instruction$C_NGL_S & C_NGL_S;

    /* C_LT_S */
    template< > struct Instruction$< 0x4600003C, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_LT_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600003C, 0xFFE007FF > Instruction$C_LT_S;

    extern Instruction$C_LT_S & C_LT_S;

    /* C_NGE_S */
    template< > struct Instruction$< 0x4600003D, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_NGE_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600003D, 0xFFE007FF > Instruction$C_NGE_S;

    extern Instruction$C_NGE_S & C_NGE_S;

    /* C_LE_S */
    template< > struct Instruction$< 0x4600003E, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_LE_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600003E, 0xFFE007FF > Instruction$C_LE_S;

    extern Instruction$C_LE_S & C_LE_S;

    /* C_NGT_S */
    template< > struct Instruction$< 0x4600003F, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "C_NGT_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x4600003F, 0xFFE007FF > Instruction$C_NGT_S;

    extern Instruction$C_NGT_S & C_NGT_S;

    /* CVT_S_W */
    template< > struct Instruction$< 0x46800020, 0xFFFF003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "CVT_S_W"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x46800020, 0xFFFF003F > Instruction$CVT_S_W;

    extern Instruction$CVT_S_W & CVT_S_W;

    /* MFV */
    template< > struct Instruction$< 0x48600000, 0xFFE0FF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MFV"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x48600000, 0xFFE0FF80 > Instruction$MFV;

    extern Instruction$MFV & MFV;

    /* MFVC */
    template< > struct Instruction$< 0x48600080, 0xFFE0FF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MFVC"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x48600080, 0xFFE0FF80 > Instruction$MFVC;

    extern Instruction$MFVC & MFVC;

    /* MTV */
    template< > struct Instruction$< 0x48E00000, 0xFFE0FF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MTV"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x48E00000, 0xFFE0FF80 > Instruction$MTV;

    extern Instruction$MTV & MTV;

    /* MTVC */
    template< > struct Instruction$< 0x48E00080, 0xFFE0FF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MTVC"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x48E00080, 0xFFE0FF80 > Instruction$MTVC;

    extern Instruction$MTVC & MTVC;

    /* BVF */
    template< > struct Instruction$< 0x49000000, 0xFFE30000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BVF"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x49000000, 0xFFE30000 > Instruction$BVF;

    extern Instruction$BVF & BVF;

    /* BVT */
    template< > struct Instruction$< 0x49010000, 0xFFE30000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BVT"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x49010000, 0xFFE30000 > Instruction$BVT;

    extern Instruction$BVT & BVT;

    /* BVFL */
    template< > struct Instruction$< 0x49020000, 0xFFE30000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BVFL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x49020000, 0xFFE30000 > Instruction$BVFL;

    extern Instruction$BVFL & BVFL;

    /* BVTL */
    template< > struct Instruction$< 0x49030000, 0xFFE30000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BVTL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x49030000, 0xFFE30000 > Instruction$BVTL;

    extern Instruction$BVTL & BVTL;

    /* BEQL */
    template< > struct Instruction$< 0x50000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BEQL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x50000000, 0xFC000000 > Instruction$BEQL;

    extern Instruction$BEQL & BEQL;

    /* BNEL */
    template< > struct Instruction$< 0x54000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BNEL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x54000000, 0xFC000000 > Instruction$BNEL;

    extern Instruction$BNEL & BNEL;

    /* BLEZL */
    template< > struct Instruction$< 0x58000000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BLEZL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x58000000, 0xFC1F0000 > Instruction$BLEZL;

    extern Instruction$BLEZL & BLEZL;

    /* BGTZL */
    template< > struct Instruction$< 0x5C000000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BGTZL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x5C000000, 0xFC1F0000 > Instruction$BGTZL;

    extern Instruction$BGTZL & BGTZL;

    /* VADD_S */
    template< > struct Instruction$< 0x60000000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VADD_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x60000000, 0xFF808080 > Instruction$VADD_S;

    extern Instruction$VADD_S & VADD_S;

    /* VADD_P */
    template< > struct Instruction$< 0x60000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VADD_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x60000080, 0xFF808080 > Instruction$VADD_P;

    extern Instruction$VADD_P & VADD_P;

    /* VADD_T */
    template< > struct Instruction$< 0x60008000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VADD_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x60008000, 0xFF808080 > Instruction$VADD_T;

    extern Instruction$VADD_T & VADD_T;

    /* VADD_Q */
    template< > struct Instruction$< 0x60008080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VADD_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x60008080, 0xFF808080 > Instruction$VADD_Q;

    extern Instruction$VADD_Q & VADD_Q;

    /* VSUB_S */
    template< > struct Instruction$< 0x60800000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSUB_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x60800000, 0xFF808080 > Instruction$VSUB_S;

    extern Instruction$VSUB_S & VSUB_S;

    /* VSUB_P */
    template< > struct Instruction$< 0x60800080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSUB_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x60800080, 0xFF808080 > Instruction$VSUB_P;

    extern Instruction$VSUB_P & VSUB_P;

    /* VSUB_T */
    template< > struct Instruction$< 0x60808000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSUB_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x60808000, 0xFF808080 > Instruction$VSUB_T;

    extern Instruction$VSUB_T & VSUB_T;

    /* VSUB_Q */
    template< > struct Instruction$< 0x60808080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSUB_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x60808080, 0xFF808080 > Instruction$VSUB_Q;

    extern Instruction$VSUB_Q & VSUB_Q;

    /* VSBN_S */
    template< > struct Instruction$< 0x61000000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSBN_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x61000000, 0xFF808080 > Instruction$VSBN_S;

    extern Instruction$VSBN_S & VSBN_S;

    /* VDIV_S */
    template< > struct Instruction$< 0x63800000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VDIV_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x63800000, 0xFF808080 > Instruction$VDIV_S;

    extern Instruction$VDIV_S & VDIV_S;

    /* VDIV_P */
    template< > struct Instruction$< 0x63800080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VDIV_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x63800080, 0xFF808080 > Instruction$VDIV_P;

    extern Instruction$VDIV_P & VDIV_P;

    /* VDIV_T */
    template< > struct Instruction$< 0x63808000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VDIV_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x63808000, 0xFF808080 > Instruction$VDIV_T;

    extern Instruction$VDIV_T & VDIV_T;

    /* VDIV_Q */
    template< > struct Instruction$< 0x63808080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VDIV_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x63808080, 0xFF808080 > Instruction$VDIV_Q;

    extern Instruction$VDIV_Q & VDIV_Q;

    /* VMUL_S */
    template< > struct Instruction$< 0x64000000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMUL_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x64000000, 0xFF808080 > Instruction$VMUL_S;

    extern Instruction$VMUL_S & VMUL_S;

    /* VMUL_P */
    template< > struct Instruction$< 0x64000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMUL_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x64000080, 0xFF808080 > Instruction$VMUL_P;

    extern Instruction$VMUL_P & VMUL_P;

    /* VMUL_T */
    template< > struct Instruction$< 0x64008000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMUL_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x64008000, 0xFF808080 > Instruction$VMUL_T;

    extern Instruction$VMUL_T & VMUL_T;

    /* VMUL_Q */
    template< > struct Instruction$< 0x64008080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMUL_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x64008080, 0xFF808080 > Instruction$VMUL_Q;

    extern Instruction$VMUL_Q & VMUL_Q;

    /* VDOT_P */
    template< > struct Instruction$< 0x64800080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VDOT_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x64800080, 0xFF808080 > Instruction$VDOT_P;

    extern Instruction$VDOT_P & VDOT_P;

    /* VDOT_T */
    template< > struct Instruction$< 0x64808000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VDOT_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x64808000, 0xFF808080 > Instruction$VDOT_T;

    extern Instruction$VDOT_T & VDOT_T;

    /* VDOT_Q */
    template< > struct Instruction$< 0x64808080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VDOT_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x64808080, 0xFF808080 > Instruction$VDOT_Q;

    extern Instruction$VDOT_Q & VDOT_Q;

    /* VSCL_P */
    template< > struct Instruction$< 0x65000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSCL_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x65000080, 0xFF808080 > Instruction$VSCL_P;

    extern Instruction$VSCL_P & VSCL_P;

    /* VSCL_T */
    template< > struct Instruction$< 0x65008000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSCL_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x65008000, 0xFF808080 > Instruction$VSCL_T;

    extern Instruction$VSCL_T & VSCL_T;

    /* VSCL_Q */
    template< > struct Instruction$< 0x65008080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSCL_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x65008080, 0xFF808080 > Instruction$VSCL_Q;

    extern Instruction$VSCL_Q & VSCL_Q;

    /* VHDP_P */
    template< > struct Instruction$< 0x66000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VHDP_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x66000080, 0xFF808080 > Instruction$VHDP_P;

    extern Instruction$VHDP_P & VHDP_P;

    /* VHDP_T */
    template< > struct Instruction$< 0x66008000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VHDP_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x66008000, 0xFF808080 > Instruction$VHDP_T;

    extern Instruction$VHDP_T & VHDP_T;

    /* VHDP_Q */
    template< > struct Instruction$< 0x66008080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VHDP_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x66008080, 0xFF808080 > Instruction$VHDP_Q;

    extern Instruction$VHDP_Q & VHDP_Q;

    /* VCRS_T */
    template< > struct Instruction$< 0x66808000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCRS_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x66808000, 0xFF808080 > Instruction$VCRS_T;

    extern Instruction$VCRS_T & VCRS_T;

    /* VDET_P */
    template< > struct Instruction$< 0x67000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VDET_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x67000080, 0xFF808080 > Instruction$VDET_P;

    extern Instruction$VDET_P & VDET_P;

    /* VCMP_S */
    template< > struct Instruction$< 0x6C000000, 0xFF8080F0 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMP_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6C000000, 0xFF8080F0 > Instruction$VCMP_S;

    extern Instruction$VCMP_S & VCMP_S;

    /* VCMP_P */
    template< > struct Instruction$< 0x6C000080, 0xFF8080F0 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMP_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6C000080, 0xFF8080F0 > Instruction$VCMP_P;

    extern Instruction$VCMP_P & VCMP_P;

    /* VCMP_T */
    template< > struct Instruction$< 0x6C008000, 0xFF8080F0 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMP_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6C008000, 0xFF8080F0 > Instruction$VCMP_T;

    extern Instruction$VCMP_T & VCMP_T;

    /* VCMP_Q */
    template< > struct Instruction$< 0x6C008080, 0xFF8080F0 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMP_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6C008080, 0xFF8080F0 > Instruction$VCMP_Q;

    extern Instruction$VCMP_Q & VCMP_Q;

    /* VMIN_S */
    template< > struct Instruction$< 0x6D000000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMIN_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6D000000, 0xFF808080 > Instruction$VMIN_S;

    extern Instruction$VMIN_S & VMIN_S;

    /* VMIN_P */
    template< > struct Instruction$< 0x6D000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMIN_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6D000080, 0xFF808080 > Instruction$VMIN_P;

    extern Instruction$VMIN_P & VMIN_P;

    /* VMIN_T */
    template< > struct Instruction$< 0x6D008000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMIN_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6D008000, 0xFF808080 > Instruction$VMIN_T;

    extern Instruction$VMIN_T & VMIN_T;

    /* VMIN_Q */
    template< > struct Instruction$< 0x6D008080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMIN_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6D008080, 0xFF808080 > Instruction$VMIN_Q;

    extern Instruction$VMIN_Q & VMIN_Q;

    /* VMAX_S */
    template< > struct Instruction$< 0x6D800000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMAX_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6D800000, 0xFF808080 > Instruction$VMAX_S;

    extern Instruction$VMAX_S & VMAX_S;

    /* VMAX_P */
    template< > struct Instruction$< 0x6D800080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMAX_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6D800080, 0xFF808080 > Instruction$VMAX_P;

    extern Instruction$VMAX_P & VMAX_P;

    /* VMAX_T */
    template< > struct Instruction$< 0x6D808000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMAX_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6D808000, 0xFF808080 > Instruction$VMAX_T;

    extern Instruction$VMAX_T & VMAX_T;

    /* VMAX_Q */
    template< > struct Instruction$< 0x6D808080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMAX_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6D808080, 0xFF808080 > Instruction$VMAX_Q;

    extern Instruction$VMAX_Q & VMAX_Q;

    /* VSCMP_S */
    template< > struct Instruction$< 0x6E800000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSCMP_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6E800000, 0xFF808080 > Instruction$VSCMP_S;

    extern Instruction$VSCMP_S & VSCMP_S;

    /* VSCMP_P */
    template< > struct Instruction$< 0x6E800080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSCMP_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6E800080, 0xFF808080 > Instruction$VSCMP_P;

    extern Instruction$VSCMP_P & VSCMP_P;

    /* VSCMP_T */
    template< > struct Instruction$< 0x6E808000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSCMP_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6E808000, 0xFF808080 > Instruction$VSCMP_T;

    extern Instruction$VSCMP_T & VSCMP_T;

    /* VSCMP_Q */
    template< > struct Instruction$< 0x6E808080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSCMP_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6E808080, 0xFF808080 > Instruction$VSCMP_Q;

    extern Instruction$VSCMP_Q & VSCMP_Q;

    /* VSGE_S */
    template< > struct Instruction$< 0x6F000000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSGE_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6F000000, 0xFF808080 > Instruction$VSGE_S;

    extern Instruction$VSGE_S & VSGE_S;

    /* VSGE_P */
    template< > struct Instruction$< 0x6F000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSGE_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6F000080, 0xFF808080 > Instruction$VSGE_P;

    extern Instruction$VSGE_P & VSGE_P;

    /* VSGE_T */
    template< > struct Instruction$< 0x6F008000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSGE_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6F008000, 0xFF808080 > Instruction$VSGE_T;

    extern Instruction$VSGE_T & VSGE_T;

    /* VSGE_Q */
    template< > struct Instruction$< 0x6F008080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSGE_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6F008080, 0xFF808080 > Instruction$VSGE_Q;

    extern Instruction$VSGE_Q & VSGE_Q;

    /* VSLT_S */
    template< > struct Instruction$< 0x6F800000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSLT_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6F800000, 0xFF808080 > Instruction$VSLT_S;

    extern Instruction$VSLT_S & VSLT_S;

    /* VSLT_P */
    template< > struct Instruction$< 0x6F800080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSLT_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6F800080, 0xFF808080 > Instruction$VSLT_P;

    extern Instruction$VSLT_P & VSLT_P;

    /* VSLT_T */
    template< > struct Instruction$< 0x6F808000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSLT_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6F808000, 0xFF808080 > Instruction$VSLT_T;

    extern Instruction$VSLT_T & VSLT_T;

    /* VSLT_Q */
    template< > struct Instruction$< 0x6F808080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSLT_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x6F808080, 0xFF808080 > Instruction$VSLT_Q;

    extern Instruction$VSLT_Q & VSLT_Q;

    /* HALT */
    template< > struct Instruction$< 0x70000000, 0xFFFFFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "HALT"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x70000000, 0xFFFFFFFF > Instruction$HALT;

    extern Instruction$HALT & HALT;

    /* MFIC */
    template< > struct Instruction$< 0x70000024, 0xFC1FFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MFIC"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x70000024, 0xFC1FFFFF > Instruction$MFIC;

    extern Instruction$MFIC & MFIC;

    /* MTIC */
    template< > struct Instruction$< 0x70000026, 0xFC1FFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MTIC"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x70000026, 0xFC1FFFFF > Instruction$MTIC;

    extern Instruction$MTIC & MTIC;

    /* MFDR */
    template< > struct Instruction$< 0x7000003D, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MFDR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7000003D, 0xFFE007FF > Instruction$MFDR;

    extern Instruction$MFDR & MFDR;

    /* DRET */
    template< > struct Instruction$< 0x7000003E, 0xFFFFFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DRET"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7000003E, 0xFFFFFFFF > Instruction$DRET;

    extern Instruction$DRET & DRET;

    /* DBREAK */
    template< > struct Instruction$< 0x7000003F, 0xFC00003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DBREAK"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7000003F, 0xFC00003F > Instruction$DBREAK;

    extern Instruction$DBREAK & DBREAK;

    /* MTDR */
    template< > struct Instruction$< 0x7080003D, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "MTDR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7080003D, 0xFFE007FF > Instruction$MTDR;

    extern Instruction$MTDR & MTDR;

    /* EXT */
    template< > struct Instruction$< 0x7C000000, 0xFC00003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "EXT"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7C000000, 0xFC00003F > Instruction$EXT;

    extern Instruction$EXT & EXT;

    /* INS */
    template< > struct Instruction$< 0x7C000004, 0xFC00003F > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "INS"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7C000004, 0xFC00003F > Instruction$INS;

    extern Instruction$INS & INS;

    /* WSBH */
    template< > struct Instruction$< 0x7C0000A0, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "WSBH"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7C0000A0, 0xFFE007FF > Instruction$WSBH;

    extern Instruction$WSBH & WSBH;

    /* WSBW */
    template< > struct Instruction$< 0x7C0000E0, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "WSBW"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7C0000E0, 0xFFE007FF > Instruction$WSBW;

    extern Instruction$WSBW & WSBW;

    /* SEB */
    template< > struct Instruction$< 0x7C000420, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SEB"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7C000420, 0xFFE007FF > Instruction$SEB;

    extern Instruction$SEB & SEB;

    /* BITREV */
    template< > struct Instruction$< 0x7C000520, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "BITREV"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7C000520, 0xFFE007FF > Instruction$BITREV;

    extern Instruction$BITREV & BITREV;

    /* SEH */
    template< > struct Instruction$< 0x7C000620, 0xFFE007FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SEH"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x7C000620, 0xFFE007FF > Instruction$SEH;

    extern Instruction$SEH & SEH;

    /* LB */
    template< > struct Instruction$< 0x80000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LB"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x80000000, 0xFC000000 > Instruction$LB;

    extern Instruction$LB & LB;

    /* LH */
    template< > struct Instruction$< 0x84000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LH"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x84000000, 0xFC000000 > Instruction$LH;

    extern Instruction$LH & LH;

    /* LWL */
    template< > struct Instruction$< 0x88000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LWL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x88000000, 0xFC000000 > Instruction$LWL;

    extern Instruction$LWL & LWL;

    /* LW */
    template< > struct Instruction$< 0x8C000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LW"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x8C000000, 0xFC000000 > Instruction$LW;

    extern Instruction$LW & LW;

    /* LBU */
    template< > struct Instruction$< 0x90000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LBU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x90000000, 0xFC000000 > Instruction$LBU;

    extern Instruction$LBU & LBU;

    /* LHU */
    template< > struct Instruction$< 0x94000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LHU"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x94000000, 0xFC000000 > Instruction$LHU;

    extern Instruction$LHU & LHU;

    /* LWR */
    template< > struct Instruction$< 0x98000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LWR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0x98000000, 0xFC000000 > Instruction$LWR;

    extern Instruction$LWR & LWR;

    /* SB */
    template< > struct Instruction$< 0xA0000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SB"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xA0000000, 0xFC000000 > Instruction$SB;

    extern Instruction$SB & SB;

    /* SH */
    template< > struct Instruction$< 0xA4000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SH"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xA4000000, 0xFC000000 > Instruction$SH;

    extern Instruction$SH & SH;

    /* SWL */
    template< > struct Instruction$< 0xA8000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SWL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xA8000000, 0xFC000000 > Instruction$SWL;

    extern Instruction$SWL & SWL;

    /* SW */
    template< > struct Instruction$< 0xAC000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SW"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xAC000000, 0xFC000000 > Instruction$SW;

    extern Instruction$SW & SW;

    /* SWR */
    template< > struct Instruction$< 0xB8000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SWR"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xB8000000, 0xFC000000 > Instruction$SWR;

    extern Instruction$SWR & SWR;

    /* ICACHE_INDEX_INVALIDATE */
    template< > struct Instruction$< 0xBC040000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ICACHE_INDEX_INVALIDATE"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC040000, 0xFC1F0000 > Instruction$ICACHE_INDEX_INVALIDATE;

    extern Instruction$ICACHE_INDEX_INVALIDATE & ICACHE_INDEX_INVALIDATE;

    /* ICACHE_INDEX_UNLOCK */
    template< > struct Instruction$< 0xBC060000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ICACHE_INDEX_UNLOCK"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC060000, 0xFC1F0000 > Instruction$ICACHE_INDEX_UNLOCK;

    extern Instruction$ICACHE_INDEX_UNLOCK & ICACHE_INDEX_UNLOCK;

    /* ICACHE_HIT_INVALIDATE */
    template< > struct Instruction$< 0xBC080000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ICACHE_HIT_INVALIDATE"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC080000, 0xFC1F0000 > Instruction$ICACHE_HIT_INVALIDATE;

    extern Instruction$ICACHE_HIT_INVALIDATE & ICACHE_HIT_INVALIDATE;

    /* ICACHE_FILL */
    template< > struct Instruction$< 0xBC0A0000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ICACHE_FILL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC0A0000, 0xFC1F0000 > Instruction$ICACHE_FILL;

    extern Instruction$ICACHE_FILL & ICACHE_FILL;

    /* ICACHE_FILL_WITH_LOCK */
    template< > struct Instruction$< 0xBC0B0000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "ICACHE_FILL_WITH_LOCK"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC0B0000, 0xFC1F0000 > Instruction$ICACHE_FILL_WITH_LOCK;

    extern Instruction$ICACHE_FILL_WITH_LOCK & ICACHE_FILL_WITH_LOCK;

    /* DCACHE_INDEX_WRITEBACK_INVALIDATE */
    template< > struct Instruction$< 0xBC140000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DCACHE_INDEX_WRITEBACK_INVALIDATE"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC140000, 0xFC1F0000 > Instruction$DCACHE_INDEX_WRITEBACK_INVALIDATE;

    extern Instruction$DCACHE_INDEX_WRITEBACK_INVALIDATE & DCACHE_INDEX_WRITEBACK_INVALIDATE;

    /* DCACHE_INDEX_UNLOCK */
    template< > struct Instruction$< 0xBC160000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DCACHE_INDEX_UNLOCK"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC160000, 0xFC1F0000 > Instruction$DCACHE_INDEX_UNLOCK;

    extern Instruction$DCACHE_INDEX_UNLOCK & DCACHE_INDEX_UNLOCK;

    /* DCACHE_CREATE_DIRTY_EXCLUSIVE */
    template< > struct Instruction$< 0xBC180000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DCACHE_CREATE_DIRTY_EXCLUSIVE"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC180000, 0xFC1F0000 > Instruction$DCACHE_CREATE_DIRTY_EXCLUSIVE;

    extern Instruction$DCACHE_CREATE_DIRTY_EXCLUSIVE & DCACHE_CREATE_DIRTY_EXCLUSIVE;

    /* DCACHE_HIT_INVALIDATE */
    template< > struct Instruction$< 0xBC190000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DCACHE_HIT_INVALIDATE"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC190000, 0xFC1F0000 > Instruction$DCACHE_HIT_INVALIDATE;

    extern Instruction$DCACHE_HIT_INVALIDATE & DCACHE_HIT_INVALIDATE;

    /* DCACHE_HIT_WRITEBACK */
    template< > struct Instruction$< 0xBC1A0000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DCACHE_HIT_WRITEBACK"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC1A0000, 0xFC1F0000 > Instruction$DCACHE_HIT_WRITEBACK;

    extern Instruction$DCACHE_HIT_WRITEBACK & DCACHE_HIT_WRITEBACK;

    /* DCACHE_HIT_WRITEBACK_INVALIDATE */
    template< > struct Instruction$< 0xBC1B0000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DCACHE_HIT_WRITEBACK_INVALIDATE"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC1B0000, 0xFC1F0000 > Instruction$DCACHE_HIT_WRITEBACK_INVALIDATE;

    extern Instruction$DCACHE_HIT_WRITEBACK_INVALIDATE & DCACHE_HIT_WRITEBACK_INVALIDATE;

    /* DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK */
    template< > struct Instruction$< 0xBC1C0000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC1C0000, 0xFC1F0000 > Instruction$DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK;

    extern Instruction$DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK & DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK;

    /* DCACHE_FILL */
    template< > struct Instruction$< 0xBC1E0000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DCACHE_FILL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC1E0000, 0xFC1F0000 > Instruction$DCACHE_FILL;

    extern Instruction$DCACHE_FILL & DCACHE_FILL;

    /* DCACHE_FILL_WITH_LOCK */
    template< > struct Instruction$< 0xBC1F0000, 0xFC1F0000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "DCACHE_FILL_WITH_LOCK"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xBC1F0000, 0xFC1F0000 > Instruction$DCACHE_FILL_WITH_LOCK;

    extern Instruction$DCACHE_FILL_WITH_LOCK & DCACHE_FILL_WITH_LOCK;

    /* LL */
    template< > struct Instruction$< 0xC0000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LL"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xC0000000, 0xFC000000 > Instruction$LL;

    extern Instruction$LL & LL;

    /* LWC1 */
    template< > struct Instruction$< 0xC4000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LWC1"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xC4000000, 0xFC000000 > Instruction$LWC1;

    extern Instruction$LWC1 & LWC1;

    /* LV_S */
    template< > struct Instruction$< 0xC8000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LV_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xC8000000, 0xFC000000 > Instruction$LV_S;

    extern Instruction$LV_S & LV_S;

    /* VMOV_S */
    template< > struct Instruction$< 0xD0000000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMOV_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0000000, 0xFFFF8080 > Instruction$VMOV_S;

    extern Instruction$VMOV_S & VMOV_S;

    /* VMOV_P */
    template< > struct Instruction$< 0xD0000080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMOV_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0000080, 0xFFFF8080 > Instruction$VMOV_P;

    extern Instruction$VMOV_P & VMOV_P;

    /* VMOV_T */
    template< > struct Instruction$< 0xD0008000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMOV_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0008000, 0xFFFF8080 > Instruction$VMOV_T;

    extern Instruction$VMOV_T & VMOV_T;

    /* VMOV_Q */
    template< > struct Instruction$< 0xD0008080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMOV_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0008080, 0xFFFF8080 > Instruction$VMOV_Q;

    extern Instruction$VMOV_Q & VMOV_Q;

    /* VABS_S */
    template< > struct Instruction$< 0xD0010000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VABS_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0010000, 0xFFFF8080 > Instruction$VABS_S;

    extern Instruction$VABS_S & VABS_S;

    /* VABS_P */
    template< > struct Instruction$< 0xD0010080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VABS_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0010080, 0xFFFF8080 > Instruction$VABS_P;

    extern Instruction$VABS_P & VABS_P;

    /* VABS_T */
    template< > struct Instruction$< 0xD0018000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VABS_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0018000, 0xFFFF8080 > Instruction$VABS_T;

    extern Instruction$VABS_T & VABS_T;

    /* VABS_Q */
    template< > struct Instruction$< 0xD0018080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VABS_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0018080, 0xFFFF8080 > Instruction$VABS_Q;

    extern Instruction$VABS_Q & VABS_Q;

    /* VNEG_S */
    template< > struct Instruction$< 0xD0020000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNEG_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0020000, 0xFFFF8080 > Instruction$VNEG_S;

    extern Instruction$VNEG_S & VNEG_S;

    /* VNEG_P */
    template< > struct Instruction$< 0xD0020080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNEG_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0020080, 0xFFFF8080 > Instruction$VNEG_P;

    extern Instruction$VNEG_P & VNEG_P;

    /* VNEG_T */
    template< > struct Instruction$< 0xD0028000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNEG_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0028000, 0xFFFF8080 > Instruction$VNEG_T;

    extern Instruction$VNEG_T & VNEG_T;

    /* VNEG_Q */
    template< > struct Instruction$< 0xD0028080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNEG_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0028080, 0xFFFF8080 > Instruction$VNEG_Q;

    extern Instruction$VNEG_Q & VNEG_Q;

    /* VIDT_S */
    template< > struct Instruction$< 0xD0030000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VIDT_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0030000, 0xFFFFFF80 > Instruction$VIDT_S;

    extern Instruction$VIDT_S & VIDT_S;

    /* VIDT_P */
    template< > struct Instruction$< 0xD0030080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VIDT_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0030080, 0xFFFFFF80 > Instruction$VIDT_P;

    extern Instruction$VIDT_P & VIDT_P;

    /* VIDT_T */
    template< > struct Instruction$< 0xD0038000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VIDT_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0038000, 0xFFFFFF80 > Instruction$VIDT_T;

    extern Instruction$VIDT_T & VIDT_T;

    /* VIDT_Q */
    template< > struct Instruction$< 0xD0038080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VIDT_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0038080, 0xFFFFFF80 > Instruction$VIDT_Q;

    extern Instruction$VIDT_Q & VIDT_Q;

    /* VSAT0_S */
    template< > struct Instruction$< 0xD0040000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSAT0_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0040000, 0xFFFF8080 > Instruction$VSAT0_S;

    extern Instruction$VSAT0_S & VSAT0_S;

    /* VSAT0_P */
    template< > struct Instruction$< 0xD0040080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSAT0_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0040080, 0xFFFF8080 > Instruction$VSAT0_P;

    extern Instruction$VSAT0_P & VSAT0_P;

    /* VSAT0_T */
    template< > struct Instruction$< 0xD0048000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSAT0_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0048000, 0xFFFF8080 > Instruction$VSAT0_T;

    extern Instruction$VSAT0_T & VSAT0_T;

    /* VSAT0_Q */
    template< > struct Instruction$< 0xD0048080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSAT0_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0048080, 0xFFFF8080 > Instruction$VSAT0_Q;

    extern Instruction$VSAT0_Q & VSAT0_Q;

    /* VSAT1_S */
    template< > struct Instruction$< 0xD0050000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSAT1_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0050000, 0xFFFF8080 > Instruction$VSAT1_S;

    extern Instruction$VSAT1_S & VSAT1_S;

    /* VSAT1_P */
    template< > struct Instruction$< 0xD0050080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSAT1_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0050080, 0xFFFF8080 > Instruction$VSAT1_P;

    extern Instruction$VSAT1_P & VSAT1_P;

    /* VSAT1_T */
    template< > struct Instruction$< 0xD0058000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSAT1_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0058000, 0xFFFF8080 > Instruction$VSAT1_T;

    extern Instruction$VSAT1_T & VSAT1_T;

    /* VSAT1_Q */
    template< > struct Instruction$< 0xD0058080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSAT1_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0058080, 0xFFFF8080 > Instruction$VSAT1_Q;

    extern Instruction$VSAT1_Q & VSAT1_Q;

    /* VZERO_S */
    template< > struct Instruction$< 0xD0060000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VZERO_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0060000, 0xFFFFFF80 > Instruction$VZERO_S;

    extern Instruction$VZERO_S & VZERO_S;

    /* VZERO_P */
    template< > struct Instruction$< 0xD0060080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VZERO_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0060080, 0xFFFFFF80 > Instruction$VZERO_P;

    extern Instruction$VZERO_P & VZERO_P;

    /* VZERO_T */
    template< > struct Instruction$< 0xD0068000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VZERO_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0068000, 0xFFFFFF80 > Instruction$VZERO_T;

    extern Instruction$VZERO_T & VZERO_T;

    /* VZERO_Q */
    template< > struct Instruction$< 0xD0068080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VZERO_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0068080, 0xFFFFFF80 > Instruction$VZERO_Q;

    extern Instruction$VZERO_Q & VZERO_Q;

    /* VONE_S */
    template< > struct Instruction$< 0xD0070000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VONE_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0070000, 0xFFFFFF80 > Instruction$VONE_S;

    extern Instruction$VONE_S & VONE_S;

    /* VONE_P */
    template< > struct Instruction$< 0xD0070080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VONE_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0070080, 0xFFFFFF80 > Instruction$VONE_P;

    extern Instruction$VONE_P & VONE_P;

    /* VONE_T */
    template< > struct Instruction$< 0xD0078000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VONE_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0078000, 0xFFFFFF80 > Instruction$VONE_T;

    extern Instruction$VONE_T & VONE_T;

    /* VONE_Q */
    template< > struct Instruction$< 0xD0078080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VONE_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0078080, 0xFFFFFF80 > Instruction$VONE_Q;

    extern Instruction$VONE_Q & VONE_Q;

    /* VRCP_S */
    template< > struct Instruction$< 0xD0100000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRCP_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0100000, 0xFFFF8080 > Instruction$VRCP_S;

    extern Instruction$VRCP_S & VRCP_S;

    /* VRCP_P */
    template< > struct Instruction$< 0xD0100080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRCP_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0100080, 0xFFFF8080 > Instruction$VRCP_P;

    extern Instruction$VRCP_P & VRCP_P;

    /* VRCP_T */
    template< > struct Instruction$< 0xD0108000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRCP_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0108000, 0xFFFF8080 > Instruction$VRCP_T;

    extern Instruction$VRCP_T & VRCP_T;

    /* VRCP_Q */
    template< > struct Instruction$< 0xD0108080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRCP_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0108080, 0xFFFF8080 > Instruction$VRCP_Q;

    extern Instruction$VRCP_Q & VRCP_Q;

    /* VRSQ_S */
    template< > struct Instruction$< 0xD0110000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRSQ_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0110000, 0xFFFF8080 > Instruction$VRSQ_S;

    extern Instruction$VRSQ_S & VRSQ_S;

    /* VRSQ_P */
    template< > struct Instruction$< 0xD0110080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRSQ_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0110080, 0xFFFF8080 > Instruction$VRSQ_P;

    extern Instruction$VRSQ_P & VRSQ_P;

    /* VRSQ_T */
    template< > struct Instruction$< 0xD0118000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRSQ_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0118000, 0xFFFF8080 > Instruction$VRSQ_T;

    extern Instruction$VRSQ_T & VRSQ_T;

    /* VRSQ_Q */
    template< > struct Instruction$< 0xD0118080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRSQ_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0118080, 0xFFFF8080 > Instruction$VRSQ_Q;

    extern Instruction$VRSQ_Q & VRSQ_Q;

    /* VSIN_S */
    template< > struct Instruction$< 0xD0120000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSIN_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0120000, 0xFFFF8080 > Instruction$VSIN_S;

    extern Instruction$VSIN_S & VSIN_S;

    /* VSIN_P */
    template< > struct Instruction$< 0xD0120080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSIN_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0120080, 0xFFFF8080 > Instruction$VSIN_P;

    extern Instruction$VSIN_P & VSIN_P;

    /* VSIN_T */
    template< > struct Instruction$< 0xD0128000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSIN_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0128000, 0xFFFF8080 > Instruction$VSIN_T;

    extern Instruction$VSIN_T & VSIN_T;

    /* VSIN_Q */
    template< > struct Instruction$< 0xD0128080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSIN_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0128080, 0xFFFF8080 > Instruction$VSIN_Q;

    extern Instruction$VSIN_Q & VSIN_Q;

    /* VCOS_S */
    template< > struct Instruction$< 0xD0130000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCOS_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0130000, 0xFFFF8080 > Instruction$VCOS_S;

    extern Instruction$VCOS_S & VCOS_S;

    /* VCOS_P */
    template< > struct Instruction$< 0xD0130080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCOS_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0130080, 0xFFFF8080 > Instruction$VCOS_P;

    extern Instruction$VCOS_P & VCOS_P;

    /* VCOS_T */
    template< > struct Instruction$< 0xD0138000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCOS_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0138000, 0xFFFF8080 > Instruction$VCOS_T;

    extern Instruction$VCOS_T & VCOS_T;

    /* VCOS_Q */
    template< > struct Instruction$< 0xD0138080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCOS_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0138080, 0xFFFF8080 > Instruction$VCOS_Q;

    extern Instruction$VCOS_Q & VCOS_Q;

    /* VEXP2_S */
    template< > struct Instruction$< 0xD0140000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VEXP2_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0140000, 0xFFFF8080 > Instruction$VEXP2_S;

    extern Instruction$VEXP2_S & VEXP2_S;

    /* VEXP2_P */
    template< > struct Instruction$< 0xD0140080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VEXP2_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0140080, 0xFFFF8080 > Instruction$VEXP2_P;

    extern Instruction$VEXP2_P & VEXP2_P;

    /* VEXP2_T */
    template< > struct Instruction$< 0xD0148000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VEXP2_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0148000, 0xFFFF8080 > Instruction$VEXP2_T;

    extern Instruction$VEXP2_T & VEXP2_T;

    /* VEXP2_Q */
    template< > struct Instruction$< 0xD0148080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VEXP2_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0148080, 0xFFFF8080 > Instruction$VEXP2_Q;

    extern Instruction$VEXP2_Q & VEXP2_Q;

    /* VLOG2_S */
    template< > struct Instruction$< 0xD0150000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VLOG2_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0150000, 0xFFFF8080 > Instruction$VLOG2_S;

    extern Instruction$VLOG2_S & VLOG2_S;

    /* VLOG2_P */
    template< > struct Instruction$< 0xD0150080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VLOG2_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0150080, 0xFFFF8080 > Instruction$VLOG2_P;

    extern Instruction$VLOG2_P & VLOG2_P;

    /* VLOG2_T */
    template< > struct Instruction$< 0xD0158000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VLOG2_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0158000, 0xFFFF8080 > Instruction$VLOG2_T;

    extern Instruction$VLOG2_T & VLOG2_T;

    /* VLOG2_Q */
    template< > struct Instruction$< 0xD0158080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VLOG2_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0158080, 0xFFFF8080 > Instruction$VLOG2_Q;

    extern Instruction$VLOG2_Q & VLOG2_Q;

    /* VSQRT_S */
    template< > struct Instruction$< 0xD0160000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSQRT_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0160000, 0xFFFF8080 > Instruction$VSQRT_S;

    extern Instruction$VSQRT_S & VSQRT_S;

    /* VSQRT_P */
    template< > struct Instruction$< 0xD0160080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSQRT_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0160080, 0xFFFF8080 > Instruction$VSQRT_P;

    extern Instruction$VSQRT_P & VSQRT_P;

    /* VSQRT_T */
    template< > struct Instruction$< 0xD0168000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSQRT_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0168000, 0xFFFF8080 > Instruction$VSQRT_T;

    extern Instruction$VSQRT_T & VSQRT_T;

    /* VSQRT_Q */
    template< > struct Instruction$< 0xD0168080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSQRT_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0168080, 0xFFFF8080 > Instruction$VSQRT_Q;

    extern Instruction$VSQRT_Q & VSQRT_Q;

    /* VASIN_S */
    template< > struct Instruction$< 0xD0170000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VASIN_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0170000, 0xFFFF8080 > Instruction$VASIN_S;

    extern Instruction$VASIN_S & VASIN_S;

    /* VASIN_P */
    template< > struct Instruction$< 0xD0170080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VASIN_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0170080, 0xFFFF8080 > Instruction$VASIN_P;

    extern Instruction$VASIN_P & VASIN_P;

    /* VASIN_T */
    template< > struct Instruction$< 0xD0178000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VASIN_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0178000, 0xFFFF8080 > Instruction$VASIN_T;

    extern Instruction$VASIN_T & VASIN_T;

    /* VASIN_Q */
    template< > struct Instruction$< 0xD0178080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VASIN_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0178080, 0xFFFF8080 > Instruction$VASIN_Q;

    extern Instruction$VASIN_Q & VASIN_Q;

    /* VNRCP_S */
    template< > struct Instruction$< 0xD0180000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNRCP_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0180000, 0xFFFF8080 > Instruction$VNRCP_S;

    extern Instruction$VNRCP_S & VNRCP_S;

    /* VNRCP_P */
    template< > struct Instruction$< 0xD0180080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNRCP_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0180080, 0xFFFF8080 > Instruction$VNRCP_P;

    extern Instruction$VNRCP_P & VNRCP_P;

    /* VNRCP_T */
    template< > struct Instruction$< 0xD0188000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNRCP_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0188000, 0xFFFF8080 > Instruction$VNRCP_T;

    extern Instruction$VNRCP_T & VNRCP_T;

    /* VNRCP_Q */
    template< > struct Instruction$< 0xD0188080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNRCP_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0188080, 0xFFFF8080 > Instruction$VNRCP_Q;

    extern Instruction$VNRCP_Q & VNRCP_Q;

    /* VNSIN_S */
    template< > struct Instruction$< 0xD01A0000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNSIN_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD01A0000, 0xFFFF8080 > Instruction$VNSIN_S;

    extern Instruction$VNSIN_S & VNSIN_S;

    /* VNSIN_P */
    template< > struct Instruction$< 0xD01A0080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNSIN_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD01A0080, 0xFFFF8080 > Instruction$VNSIN_P;

    extern Instruction$VNSIN_P & VNSIN_P;

    /* VNSIN_T */
    template< > struct Instruction$< 0xD01A8000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNSIN_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD01A8000, 0xFFFF8080 > Instruction$VNSIN_T;

    extern Instruction$VNSIN_T & VNSIN_T;

    /* VNSIN_Q */
    template< > struct Instruction$< 0xD01A8080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNSIN_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD01A8080, 0xFFFF8080 > Instruction$VNSIN_Q;

    extern Instruction$VNSIN_Q & VNSIN_Q;

    /* VREXP2_S */
    template< > struct Instruction$< 0xD01C0000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VREXP2_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD01C0000, 0xFFFF8080 > Instruction$VREXP2_S;

    extern Instruction$VREXP2_S & VREXP2_S;

    /* VREXP2_P */
    template< > struct Instruction$< 0xD01C0080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VREXP2_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD01C0080, 0xFFFF8080 > Instruction$VREXP2_P;

    extern Instruction$VREXP2_P & VREXP2_P;

    /* VREXP2_T */
    template< > struct Instruction$< 0xD01C8000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VREXP2_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD01C8000, 0xFFFF8080 > Instruction$VREXP2_T;

    extern Instruction$VREXP2_T & VREXP2_T;

    /* VREXP2_Q */
    template< > struct Instruction$< 0xD01C8080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VREXP2_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD01C8080, 0xFFFF8080 > Instruction$VREXP2_Q;

    extern Instruction$VREXP2_Q & VREXP2_Q;

    /* VRNDS_S */
    template< > struct Instruction$< 0xD0200000, 0xFFFF80FF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDS_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0200000, 0xFFFF80FF > Instruction$VRNDS_S;

    extern Instruction$VRNDS_S & VRNDS_S;

    /* VRNDI_S */
    template< > struct Instruction$< 0xD0210000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDI_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0210000, 0xFFFFFF80 > Instruction$VRNDI_S;

    extern Instruction$VRNDI_S & VRNDI_S;

    /* VRNDI_P */
    template< > struct Instruction$< 0xD0210080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDI_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0210080, 0xFFFFFF80 > Instruction$VRNDI_P;

    extern Instruction$VRNDI_P & VRNDI_P;

    /* VRNDI_T */
    template< > struct Instruction$< 0xD0218000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDI_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0218000, 0xFFFFFF80 > Instruction$VRNDI_T;

    extern Instruction$VRNDI_T & VRNDI_T;

    /* VRNDI_Q */
    template< > struct Instruction$< 0xD0218080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDI_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0218080, 0xFFFFFF80 > Instruction$VRNDI_Q;

    extern Instruction$VRNDI_Q & VRNDI_Q;

    /* VRNDF1_S */
    template< > struct Instruction$< 0xD0220000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDF1_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0220000, 0xFFFFFF80 > Instruction$VRNDF1_S;

    extern Instruction$VRNDF1_S & VRNDF1_S;

    /* VRNDF1_P */
    template< > struct Instruction$< 0xD0220080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDF1_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0220080, 0xFFFFFF80 > Instruction$VRNDF1_P;

    extern Instruction$VRNDF1_P & VRNDF1_P;

    /* VRNDF1_T */
    template< > struct Instruction$< 0xD0228000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDF1_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0228000, 0xFFFFFF80 > Instruction$VRNDF1_T;

    extern Instruction$VRNDF1_T & VRNDF1_T;

    /* VRNDF1_Q */
    template< > struct Instruction$< 0xD0228080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDF1_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0228080, 0xFFFFFF80 > Instruction$VRNDF1_Q;

    extern Instruction$VRNDF1_Q & VRNDF1_Q;

    /* VRNDF2_S */
    template< > struct Instruction$< 0xD0230000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDF2_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0230000, 0xFFFFFF80 > Instruction$VRNDF2_S;

    extern Instruction$VRNDF2_S & VRNDF2_S;

    /* VRNDF2_P */
    template< > struct Instruction$< 0xD0230080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDF2_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0230080, 0xFFFFFF80 > Instruction$VRNDF2_P;

    extern Instruction$VRNDF2_P & VRNDF2_P;

    /* VRNDF2_T */
    template< > struct Instruction$< 0xD0238000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDF2_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0238000, 0xFFFFFF80 > Instruction$VRNDF2_T;

    extern Instruction$VRNDF2_T & VRNDF2_T;

    /* VRNDF2_Q */
    template< > struct Instruction$< 0xD0238080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VRNDF2_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0238080, 0xFFFFFF80 > Instruction$VRNDF2_Q;

    extern Instruction$VRNDF2_Q & VRNDF2_Q;

    /* VF2H_P */
    template< > struct Instruction$< 0xD0320080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2H_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0320080, 0xFFFF8080 > Instruction$VF2H_P;

    extern Instruction$VF2H_P & VF2H_P;

    /* VF2H_Q */
    template< > struct Instruction$< 0xD0328080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2H_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0328080, 0xFFFF8080 > Instruction$VF2H_Q;

    extern Instruction$VF2H_Q & VF2H_Q;

    /* VH2F_S */
    template< > struct Instruction$< 0xD0330000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VH2F_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0330000, 0xFFFF8080 > Instruction$VH2F_S;

    extern Instruction$VH2F_S & VH2F_S;

    /* VH2F_P */
    template< > struct Instruction$< 0xD0330080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VH2F_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0330080, 0xFFFF8080 > Instruction$VH2F_P;

    extern Instruction$VH2F_P & VH2F_P;

    /* VSBZ_S */
    template< > struct Instruction$< 0xD0360000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSBZ_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0360000, 0xFFFF8080 > Instruction$VSBZ_S;

    extern Instruction$VSBZ_S & VSBZ_S;

    /* VLGB_S */
    template< > struct Instruction$< 0xD0370000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VLGB_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0370000, 0xFFFF8080 > Instruction$VLGB_S;

    extern Instruction$VLGB_S & VLGB_S;

    /* VUC2I_S */
    template< > struct Instruction$< 0xD0380000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VUC2I_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0380000, 0xFFFF8080 > Instruction$VUC2I_S;

    extern Instruction$VUC2I_S & VUC2I_S;

    /* VC2I_S */
    template< > struct Instruction$< 0xD0390000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VC2I_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0390000, 0xFFFF8080 > Instruction$VC2I_S;

    extern Instruction$VC2I_S & VC2I_S;

    /* VUS2I_S */
    template< > struct Instruction$< 0xD03A0000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VUS2I_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03A0000, 0xFFFF8080 > Instruction$VUS2I_S;

    extern Instruction$VUS2I_S & VUS2I_S;

    /* VUS2I_P */
    template< > struct Instruction$< 0xD03A0080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VUS2I_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03A0080, 0xFFFF8080 > Instruction$VUS2I_P;

    extern Instruction$VUS2I_P & VUS2I_P;

    /* VS2I_S */
    template< > struct Instruction$< 0xD03B0000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VS2I_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03B0000, 0xFFFF8080 > Instruction$VS2I_S;

    extern Instruction$VS2I_S & VS2I_S;

    /* VS2I_P */
    template< > struct Instruction$< 0xD03B0080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VS2I_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03B0080, 0xFFFF8080 > Instruction$VS2I_P;

    extern Instruction$VS2I_P & VS2I_P;

    /* VI2UC_Q */
    template< > struct Instruction$< 0xD03C8080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2UC_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03C8080, 0xFFFF8080 > Instruction$VI2UC_Q;

    extern Instruction$VI2UC_Q & VI2UC_Q;

    /* VI2C_Q */
    template< > struct Instruction$< 0xD03D8080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2C_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03D8080, 0xFFFF8080 > Instruction$VI2C_Q;

    extern Instruction$VI2C_Q & VI2C_Q;

    /* VI2US_P */
    template< > struct Instruction$< 0xD03E0080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2US_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03E0080, 0xFFFF8080 > Instruction$VI2US_P;

    extern Instruction$VI2US_P & VI2US_P;

    /* VI2US_Q */
    template< > struct Instruction$< 0xD03E8080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2US_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03E8080, 0xFFFF8080 > Instruction$VI2US_Q;

    extern Instruction$VI2US_Q & VI2US_Q;

    /* VI2S_P */
    template< > struct Instruction$< 0xD03F0080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2S_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03F0080, 0xFFFF8080 > Instruction$VI2S_P;

    extern Instruction$VI2S_P & VI2S_P;

    /* VI2S_Q */
    template< > struct Instruction$< 0xD03F8080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2S_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD03F8080, 0xFFFF8080 > Instruction$VI2S_Q;

    extern Instruction$VI2S_Q & VI2S_Q;

    /* VSRT1_Q */
    template< > struct Instruction$< 0xD0408080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSRT1_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0408080, 0xFFFF8080 > Instruction$VSRT1_Q;

    extern Instruction$VSRT1_Q & VSRT1_Q;

    /* VSRT2_Q */
    template< > struct Instruction$< 0xD0418080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSRT2_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0418080, 0xFFFF8080 > Instruction$VSRT2_Q;

    extern Instruction$VSRT2_Q & VSRT2_Q;

    /* VBFY1_P */
    template< > struct Instruction$< 0xD0420080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VBFY1_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0420080, 0xFFFF8080 > Instruction$VBFY1_P;

    extern Instruction$VBFY1_P & VBFY1_P;

    /* VBFY1_Q */
    template< > struct Instruction$< 0xD0428080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VBFY1_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0428080, 0xFFFF8080 > Instruction$VBFY1_Q;

    extern Instruction$VBFY1_Q & VBFY1_Q;

    /* VBFY2_Q */
    template< > struct Instruction$< 0xD0438080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VBFY2_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0438080, 0xFFFF8080 > Instruction$VBFY2_Q;

    extern Instruction$VBFY2_Q & VBFY2_Q;

    /* VOCP_S */
    template< > struct Instruction$< 0xD0440000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VOCP_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0440000, 0xFFFF8080 > Instruction$VOCP_S;

    extern Instruction$VOCP_S & VOCP_S;

    /* VOCP_P */
    template< > struct Instruction$< 0xD0440080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VOCP_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0440080, 0xFFFF8080 > Instruction$VOCP_P;

    extern Instruction$VOCP_P & VOCP_P;

    /* VOCP_T */
    template< > struct Instruction$< 0xD0448000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VOCP_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0448000, 0xFFFF8080 > Instruction$VOCP_T;

    extern Instruction$VOCP_T & VOCP_T;

    /* VOCP_Q */
    template< > struct Instruction$< 0xD0448080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VOCP_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0448080, 0xFFFF8080 > Instruction$VOCP_Q;

    extern Instruction$VOCP_Q & VOCP_Q;

    /* VSOCP_S */
    template< > struct Instruction$< 0xD0450000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSOCP_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0450000, 0xFFFF8080 > Instruction$VSOCP_S;

    extern Instruction$VSOCP_S & VSOCP_S;

    /* VSOCP_P */
    template< > struct Instruction$< 0xD0450080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSOCP_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0450080, 0xFFFF8080 > Instruction$VSOCP_P;

    extern Instruction$VSOCP_P & VSOCP_P;

    /* VFAD_P */
    template< > struct Instruction$< 0xD0460080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VFAD_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0460080, 0xFFFF8080 > Instruction$VFAD_P;

    extern Instruction$VFAD_P & VFAD_P;

    /* VFAD_T */
    template< > struct Instruction$< 0xD0468000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VFAD_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0468000, 0xFFFF8080 > Instruction$VFAD_T;

    extern Instruction$VFAD_T & VFAD_T;

    /* VFAD_Q */
    template< > struct Instruction$< 0xD0468080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VFAD_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0468080, 0xFFFF8080 > Instruction$VFAD_Q;

    extern Instruction$VFAD_Q & VFAD_Q;

    /* VAVG_P */
    template< > struct Instruction$< 0xD0470080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VAVG_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0470080, 0xFFFF8080 > Instruction$VAVG_P;

    extern Instruction$VAVG_P & VAVG_P;

    /* VAVG_T */
    template< > struct Instruction$< 0xD0478000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VAVG_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0478000, 0xFFFF8080 > Instruction$VAVG_T;

    extern Instruction$VAVG_T & VAVG_T;

    /* VAVG_Q */
    template< > struct Instruction$< 0xD0478080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VAVG_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0478080, 0xFFFF8080 > Instruction$VAVG_Q;

    extern Instruction$VAVG_Q & VAVG_Q;

    /* VSRT3_Q */
    template< > struct Instruction$< 0xD0488080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSRT3_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0488080, 0xFFFF8080 > Instruction$VSRT3_Q;

    extern Instruction$VSRT3_Q & VSRT3_Q;

    /* VSRT4_Q */
    template< > struct Instruction$< 0xD0498080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSRT4_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0498080, 0xFFFF8080 > Instruction$VSRT4_Q;

    extern Instruction$VSRT4_Q & VSRT4_Q;

    /* VSGN_S */
    template< > struct Instruction$< 0xD04A0000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSGN_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD04A0000, 0xFFFF8080 > Instruction$VSGN_S;

    extern Instruction$VSGN_S & VSGN_S;

    /* VSGN_P */
    template< > struct Instruction$< 0xD04A0080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSGN_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD04A0080, 0xFFFF8080 > Instruction$VSGN_P;

    extern Instruction$VSGN_P & VSGN_P;

    /* VSGN_T */
    template< > struct Instruction$< 0xD04A8000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSGN_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD04A8000, 0xFFFF8080 > Instruction$VSGN_T;

    extern Instruction$VSGN_T & VSGN_T;

    /* VSGN_Q */
    template< > struct Instruction$< 0xD04A8080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSGN_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD04A8080, 0xFFFF8080 > Instruction$VSGN_Q;

    extern Instruction$VSGN_Q & VSGN_Q;

    /* VMFVC */
    template< > struct Instruction$< 0xD0508000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMFVC"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0508000, 0xFFFF8080 > Instruction$VMFVC;

    extern Instruction$VMFVC & VMFVC;

    /* VMTVC */
    template< > struct Instruction$< 0xD0510080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMTVC"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0510080, 0xFFFF8080 > Instruction$VMTVC;

    extern Instruction$VMTVC & VMTVC;

    /* VT4444_Q */
    template< > struct Instruction$< 0xD0598080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VT4444_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0598080, 0xFFFF8080 > Instruction$VT4444_Q;

    extern Instruction$VT4444_Q & VT4444_Q;

    /* VT5551_Q */
    template< > struct Instruction$< 0xD05A8080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VT5551_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD05A8080, 0xFFFF8080 > Instruction$VT5551_Q;

    extern Instruction$VT5551_Q & VT5551_Q;

    /* VT5650_Q */
    template< > struct Instruction$< 0xD05B8080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VT5650_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD05B8080, 0xFFFF8080 > Instruction$VT5650_Q;

    extern Instruction$VT5650_Q & VT5650_Q;

    /* VCST_S */
    template< > struct Instruction$< 0xD0600000, 0xFFE0FF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCST_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0600000, 0xFFE0FF80 > Instruction$VCST_S;

    extern Instruction$VCST_S & VCST_S;

    /* VCST_P */
    template< > struct Instruction$< 0xD0600080, 0xFFE0FF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCST_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0600080, 0xFFE0FF80 > Instruction$VCST_P;

    extern Instruction$VCST_P & VCST_P;

    /* VCST_T */
    template< > struct Instruction$< 0xD0608000, 0xFFE0FF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCST_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0608000, 0xFFE0FF80 > Instruction$VCST_T;

    extern Instruction$VCST_T & VCST_T;

    /* VCST_Q */
    template< > struct Instruction$< 0xD0608080, 0xFFE0FF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCST_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD0608080, 0xFFE0FF80 > Instruction$VCST_Q;

    extern Instruction$VCST_Q & VCST_Q;

    /* VF2IN_S */
    template< > struct Instruction$< 0xD2000000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IN_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2000000, 0xFFE08080 > Instruction$VF2IN_S;

    extern Instruction$VF2IN_S & VF2IN_S;

    /* VF2IN_P */
    template< > struct Instruction$< 0xD2000080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IN_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2000080, 0xFFE08080 > Instruction$VF2IN_P;

    extern Instruction$VF2IN_P & VF2IN_P;

    /* VF2IN_T */
    template< > struct Instruction$< 0xD2008000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IN_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2008000, 0xFFE08080 > Instruction$VF2IN_T;

    extern Instruction$VF2IN_T & VF2IN_T;

    /* VF2IN_Q */
    template< > struct Instruction$< 0xD2008080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IN_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2008080, 0xFFE08080 > Instruction$VF2IN_Q;

    extern Instruction$VF2IN_Q & VF2IN_Q;

    /* VF2IZ_S */
    template< > struct Instruction$< 0xD2200000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IZ_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2200000, 0xFFE08080 > Instruction$VF2IZ_S;

    extern Instruction$VF2IZ_S & VF2IZ_S;

    /* VF2IZ_P */
    template< > struct Instruction$< 0xD2200080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IZ_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2200080, 0xFFE08080 > Instruction$VF2IZ_P;

    extern Instruction$VF2IZ_P & VF2IZ_P;

    /* VF2IZ_T */
    template< > struct Instruction$< 0xD2208000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IZ_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2208000, 0xFFE08080 > Instruction$VF2IZ_T;

    extern Instruction$VF2IZ_T & VF2IZ_T;

    /* VF2IZ_Q */
    template< > struct Instruction$< 0xD2208080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IZ_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2208080, 0xFFE08080 > Instruction$VF2IZ_Q;

    extern Instruction$VF2IZ_Q & VF2IZ_Q;

    /* VF2IU_S */
    template< > struct Instruction$< 0xD2400000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IU_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2400000, 0xFFE08080 > Instruction$VF2IU_S;

    extern Instruction$VF2IU_S & VF2IU_S;

    /* VF2IU_P */
    template< > struct Instruction$< 0xD2400080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IU_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2400080, 0xFFE08080 > Instruction$VF2IU_P;

    extern Instruction$VF2IU_P & VF2IU_P;

    /* VF2IU_T */
    template< > struct Instruction$< 0xD2408000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IU_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2408000, 0xFFE08080 > Instruction$VF2IU_T;

    extern Instruction$VF2IU_T & VF2IU_T;

    /* VF2IU_Q */
    template< > struct Instruction$< 0xD2408080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2IU_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2408080, 0xFFE08080 > Instruction$VF2IU_Q;

    extern Instruction$VF2IU_Q & VF2IU_Q;

    /* VF2ID_S */
    template< > struct Instruction$< 0xD2600000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2ID_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2600000, 0xFFE08080 > Instruction$VF2ID_S;

    extern Instruction$VF2ID_S & VF2ID_S;

    /* VF2ID_P */
    template< > struct Instruction$< 0xD2600080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2ID_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2600080, 0xFFE08080 > Instruction$VF2ID_P;

    extern Instruction$VF2ID_P & VF2ID_P;

    /* VF2ID_T */
    template< > struct Instruction$< 0xD2608000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2ID_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2608000, 0xFFE08080 > Instruction$VF2ID_T;

    extern Instruction$VF2ID_T & VF2ID_T;

    /* VF2ID_Q */
    template< > struct Instruction$< 0xD2608080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VF2ID_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2608080, 0xFFE08080 > Instruction$VF2ID_Q;

    extern Instruction$VF2ID_Q & VF2ID_Q;

    /* VI2F_S */
    template< > struct Instruction$< 0xD2800000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2F_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2800000, 0xFFE08080 > Instruction$VI2F_S;

    extern Instruction$VI2F_S & VI2F_S;

    /* VI2F_P */
    template< > struct Instruction$< 0xD2800080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2F_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2800080, 0xFFE08080 > Instruction$VI2F_P;

    extern Instruction$VI2F_P & VI2F_P;

    /* VI2F_T */
    template< > struct Instruction$< 0xD2808000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2F_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2808000, 0xFFE08080 > Instruction$VI2F_T;

    extern Instruction$VI2F_T & VI2F_T;

    /* VI2F_Q */
    template< > struct Instruction$< 0xD2808080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VI2F_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2808080, 0xFFE08080 > Instruction$VI2F_Q;

    extern Instruction$VI2F_Q & VI2F_Q;

    /* VCMOVT_S */
    template< > struct Instruction$< 0xD2A00000, 0xFFF88080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMOVT_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2A00000, 0xFFF88080 > Instruction$VCMOVT_S;

    extern Instruction$VCMOVT_S & VCMOVT_S;

    /* VCMOVT_P */
    template< > struct Instruction$< 0xD2A00080, 0xFFF88080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMOVT_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2A00080, 0xFFF88080 > Instruction$VCMOVT_P;

    extern Instruction$VCMOVT_P & VCMOVT_P;

    /* VCMOVT_T */
    template< > struct Instruction$< 0xD2A08000, 0xFFF88080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMOVT_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2A08000, 0xFFF88080 > Instruction$VCMOVT_T;

    extern Instruction$VCMOVT_T & VCMOVT_T;

    /* VCMOVT_Q */
    template< > struct Instruction$< 0xD2A08080, 0xFFF88080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMOVT_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2A08080, 0xFFF88080 > Instruction$VCMOVT_Q;

    extern Instruction$VCMOVT_Q & VCMOVT_Q;

    /* VCMOVF_S */
    template< > struct Instruction$< 0xD2A80000, 0xFFF88080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMOVF_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2A80000, 0xFFF88080 > Instruction$VCMOVF_S;

    extern Instruction$VCMOVF_S & VCMOVF_S;

    /* VCMOVF_P */
    template< > struct Instruction$< 0xD2A80080, 0xFFF88080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMOVF_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2A80080, 0xFFF88080 > Instruction$VCMOVF_P;

    extern Instruction$VCMOVF_P & VCMOVF_P;

    /* VCMOVF_T */
    template< > struct Instruction$< 0xD2A88000, 0xFFF88080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMOVF_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2A88000, 0xFFF88080 > Instruction$VCMOVF_T;

    extern Instruction$VCMOVF_T & VCMOVF_T;

    /* VCMOVF_Q */
    template< > struct Instruction$< 0xD2A88080, 0xFFF88080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCMOVF_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD2A88080, 0xFFF88080 > Instruction$VCMOVF_Q;

    extern Instruction$VCMOVF_Q & VCMOVF_Q;

    /* VWBN_S */
    template< > struct Instruction$< 0xD3000000, 0xFF008080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VWBN_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD3000000, 0xFF008080 > Instruction$VWBN_S;

    extern Instruction$VWBN_S & VWBN_S;

    /* LVL_Q */
    template< > struct Instruction$< 0xD4000000, 0xFC000002 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LVL_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD4000000, 0xFC000002 > Instruction$LVL_Q;

    extern Instruction$LVL_Q & LVL_Q;

    /* LVR_Q */
    template< > struct Instruction$< 0xD4000002, 0xFC000002 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LVR_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD4000002, 0xFC000002 > Instruction$LVR_Q;

    extern Instruction$LVR_Q & LVR_Q;

    /* LV_Q */
    template< > struct Instruction$< 0xD8000000, 0xFC000002 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "LV_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xD8000000, 0xFC000002 > Instruction$LV_Q;

    extern Instruction$LV_Q & LV_Q;

    /* VPFXS */
    template< > struct Instruction$< 0xDC000000, 0xFF000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VPFXS"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xDC000000, 0xFF000000 > Instruction$VPFXS;

    extern Instruction$VPFXS & VPFXS;

    /* VPFXT */
    template< > struct Instruction$< 0xDD000000, 0xFF000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VPFXT"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xDD000000, 0xFF000000 > Instruction$VPFXT;

    extern Instruction$VPFXT & VPFXT;

    /* VPFXD */
    template< > struct Instruction$< 0xDE000000, 0xFF000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VPFXD"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xDE000000, 0xFF000000 > Instruction$VPFXD;

    extern Instruction$VPFXD & VPFXD;

    /* VIIM */
    template< > struct Instruction$< 0xDF000000, 0xFF800000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VIIM"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xDF000000, 0xFF800000 > Instruction$VIIM;

    extern Instruction$VIIM & VIIM;

    /* VFIM */
    template< > struct Instruction$< 0xDF800000, 0xFF800000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VFIM"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xDF800000, 0xFF800000 > Instruction$VFIM;

    extern Instruction$VFIM & VFIM;

    /* SC */
    template< > struct Instruction$< 0xE0000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SC"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xE0000000, 0xFC000000 > Instruction$SC;

    extern Instruction$SC & SC;

    /* SWC1 */
    template< > struct Instruction$< 0xE4000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SWC1"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xE4000000, 0xFC000000 > Instruction$SWC1;

    extern Instruction$SWC1 & SWC1;

    /* SV_S */
    template< > struct Instruction$< 0xE8000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SV_S"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xE8000000, 0xFC000000 > Instruction$SV_S;

    extern Instruction$SV_S & SV_S;

    /* VMMUL_P */
    template< > struct Instruction$< 0xF0000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMMUL_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF0000080, 0xFF808080 > Instruction$VMMUL_P;

    extern Instruction$VMMUL_P & VMMUL_P;

    /* VMMUL_T */
    template< > struct Instruction$< 0xF0008000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMMUL_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF0008000, 0xFF808080 > Instruction$VMMUL_T;

    extern Instruction$VMMUL_T & VMMUL_T;

    /* VMMUL_Q */
    template< > struct Instruction$< 0xF0008080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMMUL_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF0008080, 0xFF808080 > Instruction$VMMUL_Q;

    extern Instruction$VMMUL_Q & VMMUL_Q;

    /* VHTFM2_P */
    template< > struct Instruction$< 0xF0800000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VHTFM2_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF0800000, 0xFF808080 > Instruction$VHTFM2_P;

    extern Instruction$VHTFM2_P & VHTFM2_P;

    /* VTFM2_P */
    template< > struct Instruction$< 0xF0800080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VTFM2_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF0800080, 0xFF808080 > Instruction$VTFM2_P;

    extern Instruction$VTFM2_P & VTFM2_P;

    /* VHTFM3_T */
    template< > struct Instruction$< 0xF1000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VHTFM3_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF1000080, 0xFF808080 > Instruction$VHTFM3_T;

    extern Instruction$VHTFM3_T & VHTFM3_T;

    /* VTFM3_T */
    template< > struct Instruction$< 0xF1008000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VTFM3_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF1008000, 0xFF808080 > Instruction$VTFM3_T;

    extern Instruction$VTFM3_T & VTFM3_T;

    /* VHTFM4_Q */
    template< > struct Instruction$< 0xF1808000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VHTFM4_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF1808000, 0xFF808080 > Instruction$VHTFM4_Q;

    extern Instruction$VHTFM4_Q & VHTFM4_Q;

    /* VTFM4_Q */
    template< > struct Instruction$< 0xF1808080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VTFM4_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF1808080, 0xFF808080 > Instruction$VTFM4_Q;

    extern Instruction$VTFM4_Q & VTFM4_Q;

    /* VMSCL_P */
    template< > struct Instruction$< 0xF2000080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMSCL_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF2000080, 0xFF808080 > Instruction$VMSCL_P;

    extern Instruction$VMSCL_P & VMSCL_P;

    /* VMSCL_T */
    template< > struct Instruction$< 0xF2008000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMSCL_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF2008000, 0xFF808080 > Instruction$VMSCL_T;

    extern Instruction$VMSCL_T & VMSCL_T;

    /* VMSCL_Q */
    template< > struct Instruction$< 0xF2008080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMSCL_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF2008080, 0xFF808080 > Instruction$VMSCL_Q;

    extern Instruction$VMSCL_Q & VMSCL_Q;

    /* VCRSP_T */
    template< > struct Instruction$< 0xF2808000, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VCRSP_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF2808000, 0xFF808080 > Instruction$VCRSP_T;

    extern Instruction$VCRSP_T & VCRSP_T;

    /* VQMUL_Q */
    template< > struct Instruction$< 0xF2808080, 0xFF808080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VQMUL_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF2808080, 0xFF808080 > Instruction$VQMUL_Q;

    extern Instruction$VQMUL_Q & VQMUL_Q;

    /* VMMOV_P */
    template< > struct Instruction$< 0xF3800080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMMOV_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3800080, 0xFFFF8080 > Instruction$VMMOV_P;

    extern Instruction$VMMOV_P & VMMOV_P;

    /* VMMOV_T */
    template< > struct Instruction$< 0xF3808000, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMMOV_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3808000, 0xFFFF8080 > Instruction$VMMOV_T;

    extern Instruction$VMMOV_T & VMMOV_T;

    /* VMMOV_Q */
    template< > struct Instruction$< 0xF3808080, 0xFFFF8080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMMOV_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3808080, 0xFFFF8080 > Instruction$VMMOV_Q;

    extern Instruction$VMMOV_Q & VMMOV_Q;

    /* VMIDT_P */
    template< > struct Instruction$< 0xF3830080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMIDT_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3830080, 0xFFFFFF80 > Instruction$VMIDT_P;

    extern Instruction$VMIDT_P & VMIDT_P;

    /* VMIDT_T */
    template< > struct Instruction$< 0xF3838000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMIDT_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3838000, 0xFFFFFF80 > Instruction$VMIDT_T;

    extern Instruction$VMIDT_T & VMIDT_T;

    /* VMIDT_Q */
    template< > struct Instruction$< 0xF3838080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMIDT_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3838080, 0xFFFFFF80 > Instruction$VMIDT_Q;

    extern Instruction$VMIDT_Q & VMIDT_Q;

    /* VMZERO_P */
    template< > struct Instruction$< 0xF3860080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMZERO_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3860080, 0xFFFFFF80 > Instruction$VMZERO_P;

    extern Instruction$VMZERO_P & VMZERO_P;

    /* VMZERO_T */
    template< > struct Instruction$< 0xF3868000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMZERO_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3868000, 0xFFFFFF80 > Instruction$VMZERO_T;

    extern Instruction$VMZERO_T & VMZERO_T;

    /* VMZERO_Q */
    template< > struct Instruction$< 0xF3868080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMZERO_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3868080, 0xFFFFFF80 > Instruction$VMZERO_Q;

    extern Instruction$VMZERO_Q & VMZERO_Q;

    /* VMONE_P */
    template< > struct Instruction$< 0xF3870080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMONE_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3870080, 0xFFFFFF80 > Instruction$VMONE_P;

    extern Instruction$VMONE_P & VMONE_P;

    /* VMONE_T */
    template< > struct Instruction$< 0xF3878000, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMONE_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3878000, 0xFFFFFF80 > Instruction$VMONE_T;

    extern Instruction$VMONE_T & VMONE_T;

    /* VMONE_Q */
    template< > struct Instruction$< 0xF3878080, 0xFFFFFF80 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VMONE_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3878080, 0xFFFFFF80 > Instruction$VMONE_Q;

    extern Instruction$VMONE_Q & VMONE_Q;

    /* VROT_P */
    template< > struct Instruction$< 0xF3A00080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VROT_P"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3A00080, 0xFFE08080 > Instruction$VROT_P;

    extern Instruction$VROT_P & VROT_P;

    /* VROT_T */
    template< > struct Instruction$< 0xF3A08000, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VROT_T"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3A08000, 0xFFE08080 > Instruction$VROT_T;

    extern Instruction$VROT_T & VROT_T;

    /* VROT_Q */
    template< > struct Instruction$< 0xF3A08080, 0xFFE08080 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VROT_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF3A08080, 0xFFE08080 > Instruction$VROT_Q;

    extern Instruction$VROT_Q & VROT_Q;

    /* SVL_Q */
    template< > struct Instruction$< 0xF4000000, 0xFC000002 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SVL_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF4000000, 0xFC000002 > Instruction$SVL_Q;

    extern Instruction$SVL_Q & SVL_Q;

    /* SVR_Q */
    template< > struct Instruction$< 0xF4000002, 0xFC000002 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SVR_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF4000002, 0xFC000002 > Instruction$SVR_Q;

    extern Instruction$SVR_Q & SVR_Q;

    /* SV_Q */
    template< > struct Instruction$< 0xF8000000, 0xFC000000 > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "SV_Q"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xF8000000, 0xFC000000 > Instruction$SV_Q;

    extern Instruction$SV_Q & SV_Q;

    /* VNOP */
    template< > struct Instruction$< 0xFFFF0000, 0xFFFFFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VNOP"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xFFFF0000, 0xFFFFFFFF > Instruction$VNOP;

    extern Instruction$VNOP & VNOP;

    /* VSYNC */
    template< > struct Instruction$< 0xFFFF0320, 0xFFFFFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VSYNC"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xFFFF0320, 0xFFFFFFFF > Instruction$VSYNC;

    extern Instruction$VSYNC & VSYNC;

    /* VFLUSH */
    template< > struct Instruction$< 0xFFFF040D, 0xFFFFFFFF > : InstructionUnknown
    {
        static Instruction$ & Self()
        {
            static Instruction$ insn;
            return insn;
        }

        static __forceinline char const * FastOpcodeName();
        virtual char const * OpcodeName() { return "VFLUSH"; }

        static __forceinline void FastInterpret(Allegrex::Context & processor, u32 opcode);
        virtual void Interpret(Allegrex::Context & processor, u32 opcode);

        virtual void Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment);
        virtual u64 Infos();

        static u64 count;

        virtual u64 & GetCount() { return count; }

    protected:
        Instruction$() {}
    };

    typedef Instruction$< 0xFFFF040D, 0xFFFFFFFF > Instruction$VFLUSH;

    extern Instruction$VFLUSH & VFLUSH;

}

