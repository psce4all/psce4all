/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "lle.cpu(Allegrex).Context.h"
#include "lle.cpu(Allegrex).Instruction.h"

#define PROLOG /*using namespace Allegrex; ++count;*/ (void)context; (void)opcode
#define EPILOG

/* SLL */
__forceinline void Allegrex::Instruction$< 0x00000000, 0xFFE0003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SLL(rd(opcode), rt(opcode), sa(opcode)); EPILOG;
}

/* SRL */
__forceinline void Allegrex::Instruction$< 0x00000002, 0xFFE0003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SRL(rd(opcode), rt(opcode), sa(opcode)); EPILOG;
}

/* SRA */
__forceinline void Allegrex::Instruction$< 0x00000003, 0xFFE0003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SRA(rd(opcode), rt(opcode), sa(opcode)); EPILOG;
}

/* SLLV */
__forceinline void Allegrex::Instruction$< 0x00000004, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SLLV(rd(opcode), rt(opcode), rs(opcode)); EPILOG;
}

/* SRLV */
__forceinline void Allegrex::Instruction$< 0x00000006, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SRLV(rd(opcode), rt(opcode), rs(opcode)); EPILOG;
}

/* SRAV */
__forceinline void Allegrex::Instruction$< 0x00000007, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SRAV(rd(opcode), rt(opcode), rs(opcode)); EPILOG;
}

/* JR */
__forceinline void Allegrex::Instruction$< 0x00000008, 0xFC1FFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$JR(rs(opcode)); context.InterpretDelayslot(); EPILOG;
}

/* JALR */
__forceinline void Allegrex::Instruction$< 0x00000009, 0xFC1F07FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$JALR(rd(opcode), rs(opcode)); context.InterpretDelayslot(); EPILOG;
}

/* MOVZ */
__forceinline void Allegrex::Instruction$< 0x0000000A, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MOVZ(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* MOVN */
__forceinline void Allegrex::Instruction$< 0x0000000B, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MOVN(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* SYSCALL */
__forceinline void Allegrex::Instruction$< 0x0000000C, 0xFC00003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SYSCALL(uimm20(opcode)|0x80000000); EPILOG;
}

/* BREAK */
__forceinline void Allegrex::Instruction$< 0x0000000D, 0xFC00003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* SYNC */
__forceinline void Allegrex::Instruction$< 0x0000000F, 0xFFFFFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* MFHI */
__forceinline void Allegrex::Instruction$< 0x00000010, 0xFFFF07FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MFHI(rd(opcode)); EPILOG;
}

/* MTHI */
__forceinline void Allegrex::Instruction$< 0x00000011, 0xFC1FFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MTHI(rs(opcode)); EPILOG;
}

/* MFLO */
__forceinline void Allegrex::Instruction$< 0x00000012, 0xFFFF07FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MFLO(rd(opcode)); EPILOG;
}

/* MTLO */
__forceinline void Allegrex::Instruction$< 0x00000013, 0xFC1FFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MTLO(rs(opcode)); EPILOG;
}

/* CLZ */
__forceinline void Allegrex::Instruction$< 0x00000016, 0xFC1F07FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$CLZ(rd(opcode), rs(opcode)); EPILOG;
}

/* CLO */
__forceinline void Allegrex::Instruction$< 0x00000017, 0xFC1F07FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$CLO(rd(opcode), rs(opcode)); EPILOG;
}

/* MULT */
__forceinline void Allegrex::Instruction$< 0x00000018, 0xFC00FFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MULT(rs(opcode), rt(opcode)); EPILOG;
}

/* MULTU */
__forceinline void Allegrex::Instruction$< 0x00000019, 0xFC00FFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MULTU(rs(opcode), rt(opcode)); EPILOG;
}

/* DIV */
__forceinline void Allegrex::Instruction$< 0x0000001A, 0xFC00FFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$DIV(rs(opcode), rt(opcode)); EPILOG;
}

/* DIVU */
__forceinline void Allegrex::Instruction$< 0x0000001B, 0xFC00FFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$DIVU(rs(opcode), rt(opcode)); EPILOG;
}

/* MADD */
__forceinline void Allegrex::Instruction$< 0x0000001C, 0xFC00FFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MADD(rs(opcode), rt(opcode)); EPILOG;
}

/* MADDU */
__forceinline void Allegrex::Instruction$< 0x0000001D, 0xFC00FFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MADDU(rs(opcode), rt(opcode)); EPILOG;
}

/* ADD */
__forceinline void Allegrex::Instruction$< 0x00000020, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ADD(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* ADDU */
__forceinline void Allegrex::Instruction$< 0x00000021, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ADDU(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* SUB */
__forceinline void Allegrex::Instruction$< 0x00000022, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SUB(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* SUBU */
__forceinline void Allegrex::Instruction$< 0x00000023, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SUBU(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* AND */
__forceinline void Allegrex::Instruction$< 0x00000024, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$AND(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* OR */
__forceinline void Allegrex::Instruction$< 0x00000025, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$OR(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* XOR */
__forceinline void Allegrex::Instruction$< 0x00000026, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$XOR(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* NOR */
__forceinline void Allegrex::Instruction$< 0x00000027, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$NOR(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* SLT */
__forceinline void Allegrex::Instruction$< 0x0000002A, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SLT(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* SLTU */
__forceinline void Allegrex::Instruction$< 0x0000002B, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SLTU(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* MAX */
__forceinline void Allegrex::Instruction$< 0x0000002C, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MAX(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* MIN */
__forceinline void Allegrex::Instruction$< 0x0000002D, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MIN(rd(opcode), rs(opcode), rt(opcode)); EPILOG;
}

/* MSUB */
__forceinline void Allegrex::Instruction$< 0x0000002E, 0xFC00FFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MSUB(rs(opcode), rt(opcode)); EPILOG;
}

/* MSUBU */
__forceinline void Allegrex::Instruction$< 0x0000002F, 0xFC00FFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MSUBU(rs(opcode), rt(opcode)); EPILOG;
}

/* ROTRV */
__forceinline void Allegrex::Instruction$< 0x00000046, 0xFC0007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ROTRV(rd(opcode), rt(opcode), rs(opcode)); EPILOG;
}

/* ROTR */
__forceinline void Allegrex::Instruction$< 0x00200002, 0xFFE0003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ROTR(rd(opcode), rt(opcode), sa(opcode)); EPILOG;
}

/* BLTZ */
__forceinline void Allegrex::Instruction$< 0x04000000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BLTZ(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BGEZ */
__forceinline void Allegrex::Instruction$< 0x04010000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BGEZ(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BLTZL */
__forceinline void Allegrex::Instruction$< 0x04020000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BLTZL(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BGEZL */
__forceinline void Allegrex::Instruction$< 0x04030000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BGEZL(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BLTZAL */
__forceinline void Allegrex::Instruction$< 0x04100000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BLTZAL(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BGEZAL */
__forceinline void Allegrex::Instruction$< 0x04110000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BGEZAL(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BLTZALL */
__forceinline void Allegrex::Instruction$< 0x04120000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BLTZALL(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BGEZALL */
__forceinline void Allegrex::Instruction$< 0x04130000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BGEZALL(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* J */
__forceinline void Allegrex::Instruction$< 0x08000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$J(uimm26(opcode)); context.InterpretDelayslot(); EPILOG;
}

/* JAL */
__forceinline void Allegrex::Instruction$< 0x0C000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$JAL(uimm26(opcode)); context.InterpretDelayslot(); EPILOG;
}

/* BEQ */
__forceinline void Allegrex::Instruction$< 0x10000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BEQ(rs(opcode), rt(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BNE */
__forceinline void Allegrex::Instruction$< 0x14000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BNE(rs(opcode), rt(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BLEZ */
__forceinline void Allegrex::Instruction$< 0x18000000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BLEZ(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BGTZ */
__forceinline void Allegrex::Instruction$< 0x1C000000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BGTZ(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* ADDI */
__forceinline void Allegrex::Instruction$< 0x20000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ADDI(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* ADDIU */
__forceinline void Allegrex::Instruction$< 0x24000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ADDIU(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* SLTI */
__forceinline void Allegrex::Instruction$< 0x28000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SLTI(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* SLTIU */
__forceinline void Allegrex::Instruction$< 0x2C000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SLTIU(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* ANDI */
__forceinline void Allegrex::Instruction$< 0x30000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ANDI(rt(opcode), rs(opcode), uimm16(opcode)); EPILOG;
}

/* ORI */
__forceinline void Allegrex::Instruction$< 0x34000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ORI(rt(opcode), rs(opcode), uimm16(opcode)); EPILOG;
}

/* XORI */
__forceinline void Allegrex::Instruction$< 0x38000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$XORI(rt(opcode), rs(opcode), uimm16(opcode)); EPILOG;
}

/* LUI */
__forceinline void Allegrex::Instruction$< 0x3C000000, 0xFFE00000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LUI(rt(opcode), simm16(opcode)); EPILOG;
}

/* MFC0 */
__forceinline void Allegrex::Instruction$< 0x40000000, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* CFC0 */
__forceinline void Allegrex::Instruction$< 0x40400000, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* MTC0 */
__forceinline void Allegrex::Instruction$< 0x40800000, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* CTC0 */
__forceinline void Allegrex::Instruction$< 0x40C00000, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* ERET */
__forceinline void Allegrex::Instruction$< 0x42000018, 0xFFFFFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* MFC1 */
__forceinline void Allegrex::Instruction$< 0x44000000, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MFC1(rt(opcode), fs(opcode)); EPILOG;
}

/* CFC1 */
__forceinline void Allegrex::Instruction$< 0x44400000, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$CFC1(rt(opcode), fs(opcode)); EPILOG;
}

/* MTC1 */
__forceinline void Allegrex::Instruction$< 0x44800000, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MTC1(rt(opcode), fs(opcode)); EPILOG;
}

/* CTC1 */
__forceinline void Allegrex::Instruction$< 0x44C00000, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$CTC1(rt(opcode), fs(opcode)); EPILOG;
}

/* BC1F */
__forceinline void Allegrex::Instruction$< 0x45000000, 0xFFFF0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BC1F(simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BC1T */
__forceinline void Allegrex::Instruction$< 0x45010000, 0xFFFF0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BC1T(simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BC1FL */
__forceinline void Allegrex::Instruction$< 0x45020000, 0xFFFF0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BC1FL(simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BC1TL */
__forceinline void Allegrex::Instruction$< 0x45030000, 0xFFFF0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BC1TL(simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* ADD_S */
__forceinline void Allegrex::Instruction$< 0x46000000, 0xFFE0003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ADD_S(fd(opcode), fs(opcode), ft(opcode)); EPILOG;
}

/* SUB_S */
__forceinline void Allegrex::Instruction$< 0x46000001, 0xFFE0003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SUB_S(fd(opcode), fs(opcode), ft(opcode)); EPILOG;
}

/* MUL_S */
__forceinline void Allegrex::Instruction$< 0x46000002, 0xFFE0003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MUL_S(fd(opcode), fs(opcode), ft(opcode)); EPILOG;
}

/* DIV_S */
__forceinline void Allegrex::Instruction$< 0x46000003, 0xFFE0003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$DIV_S(fd(opcode), fs(opcode), ft(opcode)); EPILOG;
}

/* SQRT_S */
__forceinline void Allegrex::Instruction$< 0x46000004, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SQRT_S(fd(opcode), fs(opcode)); EPILOG;
}

/* ABS_S */
__forceinline void Allegrex::Instruction$< 0x46000005, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ABS_S(fd(opcode), fs(opcode)); EPILOG;
}

/* MOV_S */
__forceinline void Allegrex::Instruction$< 0x46000006, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MOV_S(fd(opcode), fs(opcode)); EPILOG;
}

/* NEG_S */
__forceinline void Allegrex::Instruction$< 0x46000007, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$NEG_S(fd(opcode), fs(opcode)); EPILOG;
}

/* ROUND_W_S */
__forceinline void Allegrex::Instruction$< 0x4600000C, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$ROUND_W_S(fd(opcode), fs(opcode)); EPILOG;
}

/* TRUNC_W_S */
__forceinline void Allegrex::Instruction$< 0x4600000D, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$TRUNC_W_S(fd(opcode), fs(opcode)); EPILOG;
}

/* CEIL_W_S */
__forceinline void Allegrex::Instruction$< 0x4600000E, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$CEIL_W_S(fd(opcode), fs(opcode)); EPILOG;
}

/* FLOOR_W_S */
__forceinline void Allegrex::Instruction$< 0x4600000F, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$FLOOR_W_S(fd(opcode), fs(opcode)); EPILOG;
}

/* CVT_W_S */
__forceinline void Allegrex::Instruction$< 0x46000024, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$CVT_W_S(fd(opcode), fs(opcode)); EPILOG;
}

/* C_F_S */
__forceinline void Allegrex::Instruction$< 0x46000030, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<0>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_UN_S */
__forceinline void Allegrex::Instruction$< 0x46000031, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<1>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_EQ_S */
__forceinline void Allegrex::Instruction$< 0x46000032, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<2>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_UEQ_S */
__forceinline void Allegrex::Instruction$< 0x46000033, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<3>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_OLT_S */
__forceinline void Allegrex::Instruction$< 0x46000034, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<4>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_ULT_S */
__forceinline void Allegrex::Instruction$< 0x46000035, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<5>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_OLE_S */
__forceinline void Allegrex::Instruction$< 0x46000036, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<6>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_ULE_S */
__forceinline void Allegrex::Instruction$< 0x46000037, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<7>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_SF_S */
__forceinline void Allegrex::Instruction$< 0x46000038, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<8>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_NGLE_S */
__forceinline void Allegrex::Instruction$< 0x46000039, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<9>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_SEQ_S */
__forceinline void Allegrex::Instruction$< 0x4600003A, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<10>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_NGL_S */
__forceinline void Allegrex::Instruction$< 0x4600003B, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<11>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_LT_S */
__forceinline void Allegrex::Instruction$< 0x4600003C, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<12>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_NGE_S */
__forceinline void Allegrex::Instruction$< 0x4600003D, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<13>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_LE_S */
__forceinline void Allegrex::Instruction$< 0x4600003E, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<14>(fs(opcode), ft(opcode)); EPILOG;
}

/* C_NGT_S */
__forceinline void Allegrex::Instruction$< 0x4600003F, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$C_COND_S<15>(fs(opcode), ft(opcode)); EPILOG;
}

/* CVT_S_W */
__forceinline void Allegrex::Instruction$< 0x46800020, 0xFFFF003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$CVT_S_W(fd(opcode), fs(opcode)); EPILOG;
}

/* MFV */
__forceinline void Allegrex::Instruction$< 0x48600000, 0xFFE0FF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MFV(rt(opcode), vd(opcode)); EPILOG;
}

/* MFVC */
__forceinline void Allegrex::Instruction$< 0x48600080, 0xFFE0FF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MFVC(rt(opcode), vd(opcode)); EPILOG;
}

/* MTV */
__forceinline void Allegrex::Instruction$< 0x48E00000, 0xFFE0FF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MTV(rt(opcode), vd(opcode)); EPILOG;
}

/* MTVC */
__forceinline void Allegrex::Instruction$< 0x48E00080, 0xFFE0FF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$MTVC(rt(opcode), vd(opcode)); EPILOG;
}

/* BVF */
__forceinline void Allegrex::Instruction$< 0x49000000, 0xFFE30000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BVF((opcode>>18)&7, simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BVT */
__forceinline void Allegrex::Instruction$< 0x49010000, 0xFFE30000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BVT((opcode>>18)&7, simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BVFL */
__forceinline void Allegrex::Instruction$< 0x49020000, 0xFFE30000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BVFL((opcode>>18)&7, simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BVTL */
__forceinline void Allegrex::Instruction$< 0x49030000, 0xFFE30000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BVTL((opcode>>18)&7, simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BEQL */
__forceinline void Allegrex::Instruction$< 0x50000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BEQL(rs(opcode), rt(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BNEL */
__forceinline void Allegrex::Instruction$< 0x54000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BNEL(rs(opcode), rt(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BLEZL */
__forceinline void Allegrex::Instruction$< 0x58000000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BLEZL(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* BGTZL */
__forceinline void Allegrex::Instruction$< 0x5C000000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; if (context.do$BGTZL(rs(opcode), simm16(opcode))) context.InterpretDelayslot(); EPILOG;
}

/* VADD_S */
__forceinline void Allegrex::Instruction$< 0x60000000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VADD<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VADD_P */
__forceinline void Allegrex::Instruction$< 0x60000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VADD<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VADD_T */
__forceinline void Allegrex::Instruction$< 0x60008000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VADD<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VADD_Q */
__forceinline void Allegrex::Instruction$< 0x60008080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VADD<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSUB_S */
__forceinline void Allegrex::Instruction$< 0x60800000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSUB<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSUB_P */
__forceinline void Allegrex::Instruction$< 0x60800080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSUB<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSUB_T */
__forceinline void Allegrex::Instruction$< 0x60808000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSUB<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSUB_Q */
__forceinline void Allegrex::Instruction$< 0x60808080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSUB<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSBN_S */
__forceinline void Allegrex::Instruction$< 0x61000000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSBN<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VDIV_S */
__forceinline void Allegrex::Instruction$< 0x63800000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VDIV<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VDIV_P */
__forceinline void Allegrex::Instruction$< 0x63800080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VDIV<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VDIV_T */
__forceinline void Allegrex::Instruction$< 0x63808000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VDIV<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VDIV_Q */
__forceinline void Allegrex::Instruction$< 0x63808080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VDIV<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMUL_S */
__forceinline void Allegrex::Instruction$< 0x64000000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMUL<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMUL_P */
__forceinline void Allegrex::Instruction$< 0x64000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMUL<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMUL_T */
__forceinline void Allegrex::Instruction$< 0x64008000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMUL<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMUL_Q */
__forceinline void Allegrex::Instruction$< 0x64008080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMUL<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VDOT_P */
__forceinline void Allegrex::Instruction$< 0x64800080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VDOT<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VDOT_T */
__forceinline void Allegrex::Instruction$< 0x64808000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VDOT<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VDOT_Q */
__forceinline void Allegrex::Instruction$< 0x64808080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VDOT<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSCL_P */
__forceinline void Allegrex::Instruction$< 0x65000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSCL<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSCL_T */
__forceinline void Allegrex::Instruction$< 0x65008000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSCL<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSCL_Q */
__forceinline void Allegrex::Instruction$< 0x65008080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSCL<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VHDP_P */
__forceinline void Allegrex::Instruction$< 0x66000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VHDP<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VHDP_T */
__forceinline void Allegrex::Instruction$< 0x66008000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VHDP<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VHDP_Q */
__forceinline void Allegrex::Instruction$< 0x66008080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VHDP<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VCRS_T */
__forceinline void Allegrex::Instruction$< 0x66808000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCRS<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VDET_P */
__forceinline void Allegrex::Instruction$< 0x67000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VDET<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VCMP_S */
__forceinline void Allegrex::Instruction$< 0x6C000000, 0xFF8080F0 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMP<1>(rd(opcode), rt(opcode), uimm4(opcode)); EPILOG;
}

/* VCMP_P */
__forceinline void Allegrex::Instruction$< 0x6C000080, 0xFF8080F0 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMP<2>(rd(opcode), rt(opcode), uimm4(opcode)); EPILOG;
}

/* VCMP_T */
__forceinline void Allegrex::Instruction$< 0x6C008000, 0xFF8080F0 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMP<3>(rd(opcode), rt(opcode), uimm4(opcode)); EPILOG;
}

/* VCMP_Q */
__forceinline void Allegrex::Instruction$< 0x6C008080, 0xFF8080F0 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMP<4>(rd(opcode), rt(opcode), uimm4(opcode)); EPILOG;
}

/* VMIN_S */
__forceinline void Allegrex::Instruction$< 0x6D000000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMIN<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMIN_P */
__forceinline void Allegrex::Instruction$< 0x6D000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMIN<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMIN_T */
__forceinline void Allegrex::Instruction$< 0x6D008000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMIN<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMIN_Q */
__forceinline void Allegrex::Instruction$< 0x6D008080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMIN<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMAX_S */
__forceinline void Allegrex::Instruction$< 0x6D800000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMAX<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMAX_P */
__forceinline void Allegrex::Instruction$< 0x6D800080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMAX<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMAX_T */
__forceinline void Allegrex::Instruction$< 0x6D808000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMAX<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMAX_Q */
__forceinline void Allegrex::Instruction$< 0x6D808080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMAX<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSCMP_S */
__forceinline void Allegrex::Instruction$< 0x6E800000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSCMP<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSCMP_P */
__forceinline void Allegrex::Instruction$< 0x6E800080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSCMP<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSCMP_T */
__forceinline void Allegrex::Instruction$< 0x6E808000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSCMP<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSCMP_Q */
__forceinline void Allegrex::Instruction$< 0x6E808080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSCMP<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSGE_S */
__forceinline void Allegrex::Instruction$< 0x6F000000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSGE<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSGE_P */
__forceinline void Allegrex::Instruction$< 0x6F000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSGE<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSGE_T */
__forceinline void Allegrex::Instruction$< 0x6F008000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSGE<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSGE_Q */
__forceinline void Allegrex::Instruction$< 0x6F008080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSGE<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSLT_S */
__forceinline void Allegrex::Instruction$< 0x6F800000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSLT<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSLT_P */
__forceinline void Allegrex::Instruction$< 0x6F800080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSLT<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSLT_T */
__forceinline void Allegrex::Instruction$< 0x6F808000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSLT<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VSLT_Q */
__forceinline void Allegrex::Instruction$< 0x6F808080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSLT<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* HALT */
__forceinline void Allegrex::Instruction$< 0x70000000, 0xFFFFFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* MFIC */
__forceinline void Allegrex::Instruction$< 0x70000024, 0xFC1FFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* MTIC */
__forceinline void Allegrex::Instruction$< 0x70000026, 0xFC1FFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* MFDR */
__forceinline void Allegrex::Instruction$< 0x7000003D, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DRET */
__forceinline void Allegrex::Instruction$< 0x7000003E, 0xFFFFFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DBREAK */
__forceinline void Allegrex::Instruction$< 0x7000003F, 0xFC00003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* MTDR */
__forceinline void Allegrex::Instruction$< 0x7080003D, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* EXT */
__forceinline void Allegrex::Instruction$< 0x7C000000, 0xFC00003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$EXT(rt(opcode), rs(opcode), sa(opcode), rd(opcode)); EPILOG;
}

/* INS */
__forceinline void Allegrex::Instruction$< 0x7C000004, 0xFC00003F >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$INS(rt(opcode), rs(opcode), sa(opcode), rd(opcode)); EPILOG;
}

/* WSBH */
__forceinline void Allegrex::Instruction$< 0x7C0000A0, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$WSBH(rd(opcode), rt(opcode)); EPILOG;
}

/* WSBW */
__forceinline void Allegrex::Instruction$< 0x7C0000E0, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$WSBW(rd(opcode), rt(opcode)); EPILOG;
}

/* SEB */
__forceinline void Allegrex::Instruction$< 0x7C000420, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SEB(rd(opcode), rt(opcode)); EPILOG;
}

/* BITREV */
__forceinline void Allegrex::Instruction$< 0x7C000520, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$BITREV(rd(opcode), rt(opcode)); EPILOG;
}

/* SEH */
__forceinline void Allegrex::Instruction$< 0x7C000620, 0xFFE007FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SEH(rd(opcode), rt(opcode)); EPILOG;
}

/* LB */
__forceinline void Allegrex::Instruction$< 0x80000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LB(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* LH */
__forceinline void Allegrex::Instruction$< 0x84000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LH(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* LWL */
__forceinline void Allegrex::Instruction$< 0x88000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LWL(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* LW */
__forceinline void Allegrex::Instruction$< 0x8C000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LW(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* LBU */
__forceinline void Allegrex::Instruction$< 0x90000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LBU(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* LHU */
__forceinline void Allegrex::Instruction$< 0x94000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LHU(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* LWR */
__forceinline void Allegrex::Instruction$< 0x98000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LWR(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* SB */
__forceinline void Allegrex::Instruction$< 0xA0000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SB(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* SH */
__forceinline void Allegrex::Instruction$< 0xA4000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SH(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* SWL */
__forceinline void Allegrex::Instruction$< 0xA8000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SWL(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* SW */
__forceinline void Allegrex::Instruction$< 0xAC000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SW(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* SWR */
__forceinline void Allegrex::Instruction$< 0xB8000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SWR(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* ICACHE_INDEX_INVALIDATE */
__forceinline void Allegrex::Instruction$< 0xBC040000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* ICACHE_INDEX_UNLOCK */
__forceinline void Allegrex::Instruction$< 0xBC060000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* ICACHE_HIT_INVALIDATE */
__forceinline void Allegrex::Instruction$< 0xBC080000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* ICACHE_FILL */
__forceinline void Allegrex::Instruction$< 0xBC0A0000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* ICACHE_FILL_WITH_LOCK */
__forceinline void Allegrex::Instruction$< 0xBC0B0000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DCACHE_INDEX_WRITEBACK_INVALIDATE */
__forceinline void Allegrex::Instruction$< 0xBC140000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DCACHE_INDEX_UNLOCK */
__forceinline void Allegrex::Instruction$< 0xBC160000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DCACHE_CREATE_DIRTY_EXCLUSIVE */
__forceinline void Allegrex::Instruction$< 0xBC180000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DCACHE_HIT_INVALIDATE */
__forceinline void Allegrex::Instruction$< 0xBC190000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DCACHE_HIT_WRITEBACK */
__forceinline void Allegrex::Instruction$< 0xBC1A0000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DCACHE_HIT_WRITEBACK_INVALIDATE */
__forceinline void Allegrex::Instruction$< 0xBC1B0000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK */
__forceinline void Allegrex::Instruction$< 0xBC1C0000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DCACHE_FILL */
__forceinline void Allegrex::Instruction$< 0xBC1E0000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* DCACHE_FILL_WITH_LOCK */
__forceinline void Allegrex::Instruction$< 0xBC1F0000, 0xFC1F0000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* LL */
__forceinline void Allegrex::Instruction$< 0xC0000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LL(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* LWC1 */
__forceinline void Allegrex::Instruction$< 0xC4000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LWC1(ft(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* LV_S */
__forceinline void Allegrex::Instruction$< 0xC8000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LV_S(vt52(opcode), rs(opcode), simm14(opcode)); EPILOG;
}

/* VMOV_S */
__forceinline void Allegrex::Instruction$< 0xD0000000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMOV<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VMOV_P */
__forceinline void Allegrex::Instruction$< 0xD0000080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMOV<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VMOV_T */
__forceinline void Allegrex::Instruction$< 0xD0008000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMOV<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VMOV_Q */
__forceinline void Allegrex::Instruction$< 0xD0008080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMOV<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VABS_S */
__forceinline void Allegrex::Instruction$< 0xD0010000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VABS<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VABS_P */
__forceinline void Allegrex::Instruction$< 0xD0010080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VABS<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VABS_T */
__forceinline void Allegrex::Instruction$< 0xD0018000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VABS<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VABS_Q */
__forceinline void Allegrex::Instruction$< 0xD0018080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VABS<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNEG_S */
__forceinline void Allegrex::Instruction$< 0xD0020000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNEG<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNEG_P */
__forceinline void Allegrex::Instruction$< 0xD0020080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNEG<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNEG_T */
__forceinline void Allegrex::Instruction$< 0xD0028000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNEG<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNEG_Q */
__forceinline void Allegrex::Instruction$< 0xD0028080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNEG<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VIDT_S */
__forceinline void Allegrex::Instruction$< 0xD0030000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VIDT<1>(vd(opcode)); EPILOG;
}

/* VIDT_P */
__forceinline void Allegrex::Instruction$< 0xD0030080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VIDT<2>(vd(opcode)); EPILOG;
}

/* VIDT_T */
__forceinline void Allegrex::Instruction$< 0xD0038000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VIDT<3>(vd(opcode)); EPILOG;
}

/* VIDT_Q */
__forceinline void Allegrex::Instruction$< 0xD0038080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VIDT<4>(vd(opcode)); EPILOG;
}

/* VSAT0_S */
__forceinline void Allegrex::Instruction$< 0xD0040000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSAT0<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSAT0_P */
__forceinline void Allegrex::Instruction$< 0xD0040080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSAT0<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSAT0_T */
__forceinline void Allegrex::Instruction$< 0xD0048000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSAT0<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSAT0_Q */
__forceinline void Allegrex::Instruction$< 0xD0048080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSAT0<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSAT1_S */
__forceinline void Allegrex::Instruction$< 0xD0050000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSAT1<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSAT1_P */
__forceinline void Allegrex::Instruction$< 0xD0050080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSAT1<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSAT1_T */
__forceinline void Allegrex::Instruction$< 0xD0058000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSAT1<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSAT1_Q */
__forceinline void Allegrex::Instruction$< 0xD0058080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSAT1<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VZERO_S */
__forceinline void Allegrex::Instruction$< 0xD0060000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VZERO<1>(vd(opcode)); EPILOG;
}

/* VZERO_P */
__forceinline void Allegrex::Instruction$< 0xD0060080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VZERO<2>(vd(opcode)); EPILOG;
}

/* VZERO_T */
__forceinline void Allegrex::Instruction$< 0xD0068000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VZERO<3>(vd(opcode)); EPILOG;
}

/* VZERO_Q */
__forceinline void Allegrex::Instruction$< 0xD0068080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VZERO<4>(vd(opcode)); EPILOG;
}

/* VONE_S */
__forceinline void Allegrex::Instruction$< 0xD0070000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VONE<1>(vd(opcode)); EPILOG;
}

/* VONE_P */
__forceinline void Allegrex::Instruction$< 0xD0070080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VONE<2>(vd(opcode)); EPILOG;
}

/* VONE_T */
__forceinline void Allegrex::Instruction$< 0xD0078000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VONE<3>(vd(opcode)); EPILOG;
}

/* VONE_Q */
__forceinline void Allegrex::Instruction$< 0xD0078080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VONE<4>(vd(opcode)); EPILOG;
}

/* VRCP_S */
__forceinline void Allegrex::Instruction$< 0xD0100000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRCP<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VRCP_P */
__forceinline void Allegrex::Instruction$< 0xD0100080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRCP<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VRCP_T */
__forceinline void Allegrex::Instruction$< 0xD0108000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRCP<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VRCP_Q */
__forceinline void Allegrex::Instruction$< 0xD0108080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRCP<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VRSQ_S */
__forceinline void Allegrex::Instruction$< 0xD0110000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRSQ<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VRSQ_P */
__forceinline void Allegrex::Instruction$< 0xD0110080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRSQ<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VRSQ_T */
__forceinline void Allegrex::Instruction$< 0xD0118000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRSQ<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VRSQ_Q */
__forceinline void Allegrex::Instruction$< 0xD0118080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRSQ<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSIN_S */
__forceinline void Allegrex::Instruction$< 0xD0120000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSIN<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSIN_P */
__forceinline void Allegrex::Instruction$< 0xD0120080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSIN<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSIN_T */
__forceinline void Allegrex::Instruction$< 0xD0128000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSIN<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSIN_Q */
__forceinline void Allegrex::Instruction$< 0xD0128080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSIN<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VCOS_S */
__forceinline void Allegrex::Instruction$< 0xD0130000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCOS<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VCOS_P */
__forceinline void Allegrex::Instruction$< 0xD0130080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCOS<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VCOS_T */
__forceinline void Allegrex::Instruction$< 0xD0138000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCOS<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VCOS_Q */
__forceinline void Allegrex::Instruction$< 0xD0138080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCOS<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VEXP2_S */
__forceinline void Allegrex::Instruction$< 0xD0140000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VEXP2<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VEXP2_P */
__forceinline void Allegrex::Instruction$< 0xD0140080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VEXP2<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VEXP2_T */
__forceinline void Allegrex::Instruction$< 0xD0148000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VEXP2<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VEXP2_Q */
__forceinline void Allegrex::Instruction$< 0xD0148080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VEXP2<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VLOG2_S */
__forceinline void Allegrex::Instruction$< 0xD0150000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VLOG2<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VLOG2_P */
__forceinline void Allegrex::Instruction$< 0xD0150080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VLOG2<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VLOG2_T */
__forceinline void Allegrex::Instruction$< 0xD0158000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VLOG2<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VLOG2_Q */
__forceinline void Allegrex::Instruction$< 0xD0158080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VLOG2<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSQRT_S */
__forceinline void Allegrex::Instruction$< 0xD0160000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSQRT<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSQRT_P */
__forceinline void Allegrex::Instruction$< 0xD0160080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSQRT<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSQRT_T */
__forceinline void Allegrex::Instruction$< 0xD0168000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSQRT<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSQRT_Q */
__forceinline void Allegrex::Instruction$< 0xD0168080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSQRT<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VASIN_S */
__forceinline void Allegrex::Instruction$< 0xD0170000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VASIN<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VASIN_P */
__forceinline void Allegrex::Instruction$< 0xD0170080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VASIN<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VASIN_T */
__forceinline void Allegrex::Instruction$< 0xD0178000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VASIN<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VASIN_Q */
__forceinline void Allegrex::Instruction$< 0xD0178080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VASIN<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNRCP_S */
__forceinline void Allegrex::Instruction$< 0xD0180000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNRCP<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNRCP_P */
__forceinline void Allegrex::Instruction$< 0xD0180080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNRCP<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNRCP_T */
__forceinline void Allegrex::Instruction$< 0xD0188000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNRCP<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNRCP_Q */
__forceinline void Allegrex::Instruction$< 0xD0188080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNRCP<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNSIN_S */
__forceinline void Allegrex::Instruction$< 0xD01A0000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNSIN<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNSIN_P */
__forceinline void Allegrex::Instruction$< 0xD01A0080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNSIN<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNSIN_T */
__forceinline void Allegrex::Instruction$< 0xD01A8000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNSIN<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VNSIN_Q */
__forceinline void Allegrex::Instruction$< 0xD01A8080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VNSIN<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VREXP2_S */
__forceinline void Allegrex::Instruction$< 0xD01C0000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VREXP2<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VREXP2_P */
__forceinline void Allegrex::Instruction$< 0xD01C0080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VREXP2<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VREXP2_T */
__forceinline void Allegrex::Instruction$< 0xD01C8000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VREXP2<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VREXP2_Q */
__forceinline void Allegrex::Instruction$< 0xD01C8080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VREXP2<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VRNDS_S */
__forceinline void Allegrex::Instruction$< 0xD0200000, 0xFFFF80FF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDS<1>(vs(opcode)); EPILOG;
}

/* VRNDI_S */
__forceinline void Allegrex::Instruction$< 0xD0210000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDI<1>(vd(opcode)); EPILOG;
}

/* VRNDI_P */
__forceinline void Allegrex::Instruction$< 0xD0210080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDI<2>(vd(opcode)); EPILOG;
}

/* VRNDI_T */
__forceinline void Allegrex::Instruction$< 0xD0218000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDI<3>(vd(opcode)); EPILOG;
}

/* VRNDI_Q */
__forceinline void Allegrex::Instruction$< 0xD0218080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDI<4>(vd(opcode)); EPILOG;
}

/* VRNDF1_S */
__forceinline void Allegrex::Instruction$< 0xD0220000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDF1<1>(vd(opcode)); EPILOG;
}

/* VRNDF1_P */
__forceinline void Allegrex::Instruction$< 0xD0220080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDF1<2>(vd(opcode)); EPILOG;
}

/* VRNDF1_T */
__forceinline void Allegrex::Instruction$< 0xD0228000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDF1<3>(vd(opcode)); EPILOG;
}

/* VRNDF1_Q */
__forceinline void Allegrex::Instruction$< 0xD0228080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDF1<4>(vd(opcode)); EPILOG;
}

/* VRNDF2_S */
__forceinline void Allegrex::Instruction$< 0xD0230000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDF2<1>(vd(opcode)); EPILOG;
}

/* VRNDF2_P */
__forceinline void Allegrex::Instruction$< 0xD0230080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDF2<2>(vd(opcode)); EPILOG;
}

/* VRNDF2_T */
__forceinline void Allegrex::Instruction$< 0xD0238000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDF2<3>(vd(opcode)); EPILOG;
}

/* VRNDF2_Q */
__forceinline void Allegrex::Instruction$< 0xD0238080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VRNDF2<4>(vd(opcode)); EPILOG;
}

/* VF2H_P */
__forceinline void Allegrex::Instruction$< 0xD0320080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2H<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VF2H_Q */
__forceinline void Allegrex::Instruction$< 0xD0328080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2H<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VH2F_S */
__forceinline void Allegrex::Instruction$< 0xD0330000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VH2F<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VH2F_P */
__forceinline void Allegrex::Instruction$< 0xD0330080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VH2F<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSBZ_S */
__forceinline void Allegrex::Instruction$< 0xD0360000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSBZ<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VLGB_S */
__forceinline void Allegrex::Instruction$< 0xD0370000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VLGB<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VUC2I_S */
__forceinline void Allegrex::Instruction$< 0xD0380000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VUC2I<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VC2I_S */
__forceinline void Allegrex::Instruction$< 0xD0390000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VC2I<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VUS2I_S */
__forceinline void Allegrex::Instruction$< 0xD03A0000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VUS2I<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VUS2I_P */
__forceinline void Allegrex::Instruction$< 0xD03A0080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VUS2I<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VS2I_S */
__forceinline void Allegrex::Instruction$< 0xD03B0000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VS2I<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VS2I_P */
__forceinline void Allegrex::Instruction$< 0xD03B0080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VS2I<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VI2UC_Q */
__forceinline void Allegrex::Instruction$< 0xD03C8080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2UC<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VI2C_Q */
__forceinline void Allegrex::Instruction$< 0xD03D8080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2C<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VI2US_P */
__forceinline void Allegrex::Instruction$< 0xD03E0080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2US<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VI2US_Q */
__forceinline void Allegrex::Instruction$< 0xD03E8080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2US<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VI2S_P */
__forceinline void Allegrex::Instruction$< 0xD03F0080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2S<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VI2S_Q */
__forceinline void Allegrex::Instruction$< 0xD03F8080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2S<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSRT1_Q */
__forceinline void Allegrex::Instruction$< 0xD0408080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSRT1<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSRT2_Q */
__forceinline void Allegrex::Instruction$< 0xD0418080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSRT2<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VBFY1_P */
__forceinline void Allegrex::Instruction$< 0xD0420080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VBFY1<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VBFY1_Q */
__forceinline void Allegrex::Instruction$< 0xD0428080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VBFY1<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VBFY2_Q */
__forceinline void Allegrex::Instruction$< 0xD0438080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VBFY2<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VOCP_S */
__forceinline void Allegrex::Instruction$< 0xD0440000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VOCP<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VOCP_P */
__forceinline void Allegrex::Instruction$< 0xD0440080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VOCP<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VOCP_T */
__forceinline void Allegrex::Instruction$< 0xD0448000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VOCP<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VOCP_Q */
__forceinline void Allegrex::Instruction$< 0xD0448080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VOCP<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSOCP_S */
__forceinline void Allegrex::Instruction$< 0xD0450000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSOCP<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSOCP_P */
__forceinline void Allegrex::Instruction$< 0xD0450080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSOCP<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VFAD_P */
__forceinline void Allegrex::Instruction$< 0xD0460080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VFAD<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VFAD_T */
__forceinline void Allegrex::Instruction$< 0xD0468000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VFAD<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VFAD_Q */
__forceinline void Allegrex::Instruction$< 0xD0468080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VFAD<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VAVG_P */
__forceinline void Allegrex::Instruction$< 0xD0470080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VAVG<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VAVG_T */
__forceinline void Allegrex::Instruction$< 0xD0478000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VAVG<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VAVG_Q */
__forceinline void Allegrex::Instruction$< 0xD0478080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VAVG<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSRT3_Q */
__forceinline void Allegrex::Instruction$< 0xD0488080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSRT3<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSRT4_Q */
__forceinline void Allegrex::Instruction$< 0xD0498080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSRT4<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSGN_S */
__forceinline void Allegrex::Instruction$< 0xD04A0000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSGN<1>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSGN_P */
__forceinline void Allegrex::Instruction$< 0xD04A0080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSGN<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSGN_T */
__forceinline void Allegrex::Instruction$< 0xD04A8000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSGN<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VSGN_Q */
__forceinline void Allegrex::Instruction$< 0xD04A8080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VSGN<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VMFVC */
__forceinline void Allegrex::Instruction$< 0xD0508000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMFVC(vd(opcode), vs(opcode)); EPILOG;
}

/* VMTVC */
__forceinline void Allegrex::Instruction$< 0xD0510080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMTVC(vd(opcode), vs(opcode)); EPILOG;
}

/* VT4444_Q */
__forceinline void Allegrex::Instruction$< 0xD0598080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VT4444<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VT5551_Q */
__forceinline void Allegrex::Instruction$< 0xD05A8080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VT5551<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VT5650_Q */
__forceinline void Allegrex::Instruction$< 0xD05B8080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VT5650<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VCST_S */
__forceinline void Allegrex::Instruction$< 0xD0600000, 0xFFE0FF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCST<1>(vd(opcode), uimm4(opcode)); EPILOG;
}

/* VCST_P */
__forceinline void Allegrex::Instruction$< 0xD0600080, 0xFFE0FF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCST<2>(vd(opcode), uimm4(opcode)); EPILOG;
}

/* VCST_T */
__forceinline void Allegrex::Instruction$< 0xD0608000, 0xFFE0FF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCST<3>(vd(opcode), uimm4(opcode)); EPILOG;
}

/* VCST_Q */
__forceinline void Allegrex::Instruction$< 0xD0608080, 0xFFE0FF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCST<4>(vd(opcode), uimm4(opcode)); EPILOG;
}

/* VF2IN_S */
__forceinline void Allegrex::Instruction$< 0xD2000000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IN<1>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IN_P */
__forceinline void Allegrex::Instruction$< 0xD2000080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IN<2>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IN_T */
__forceinline void Allegrex::Instruction$< 0xD2008000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IN<3>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IN_Q */
__forceinline void Allegrex::Instruction$< 0xD2008080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IN<4>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IZ_S */
__forceinline void Allegrex::Instruction$< 0xD2200000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IZ<1>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IZ_P */
__forceinline void Allegrex::Instruction$< 0xD2200080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IZ<2>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IZ_T */
__forceinline void Allegrex::Instruction$< 0xD2208000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IZ<3>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IZ_Q */
__forceinline void Allegrex::Instruction$< 0xD2208080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IZ<4>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IU_S */
__forceinline void Allegrex::Instruction$< 0xD2400000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IU<1>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IU_P */
__forceinline void Allegrex::Instruction$< 0xD2400080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IU<2>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IU_T */
__forceinline void Allegrex::Instruction$< 0xD2408000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IU<3>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2IU_Q */
__forceinline void Allegrex::Instruction$< 0xD2408080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2IU<4>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2ID_S */
__forceinline void Allegrex::Instruction$< 0xD2600000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2ID<1>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2ID_P */
__forceinline void Allegrex::Instruction$< 0xD2600080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2ID<2>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2ID_T */
__forceinline void Allegrex::Instruction$< 0xD2608000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2ID<3>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VF2ID_Q */
__forceinline void Allegrex::Instruction$< 0xD2608080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VF2ID<4>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VI2F_S */
__forceinline void Allegrex::Instruction$< 0xD2800000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2F<1>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VI2F_P */
__forceinline void Allegrex::Instruction$< 0xD2800080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2F<2>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VI2F_T */
__forceinline void Allegrex::Instruction$< 0xD2808000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2F<3>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VI2F_Q */
__forceinline void Allegrex::Instruction$< 0xD2808080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VI2F<4>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VCMOVT_S */
__forceinline void Allegrex::Instruction$< 0xD2A00000, 0xFFF88080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMOVT<1>(vd(opcode), vs(opcode), uimm3(opcode)); EPILOG;
}

/* VCMOVT_P */
__forceinline void Allegrex::Instruction$< 0xD2A00080, 0xFFF88080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMOVT<2>(vd(opcode), vs(opcode), uimm3(opcode)); EPILOG;
}

/* VCMOVT_T */
__forceinline void Allegrex::Instruction$< 0xD2A08000, 0xFFF88080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMOVT<3>(vd(opcode), vs(opcode), uimm3(opcode)); EPILOG;
}

/* VCMOVT_Q */
__forceinline void Allegrex::Instruction$< 0xD2A08080, 0xFFF88080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMOVT<4>(vd(opcode), vs(opcode), uimm3(opcode)); EPILOG;
}

/* VCMOVF_S */
__forceinline void Allegrex::Instruction$< 0xD2A80000, 0xFFF88080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMOVF<1>(vd(opcode), vs(opcode), uimm3(opcode)); EPILOG;
}

/* VCMOVF_P */
__forceinline void Allegrex::Instruction$< 0xD2A80080, 0xFFF88080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMOVF<2>(vd(opcode), vs(opcode), uimm3(opcode)); EPILOG;
}

/* VCMOVF_T */
__forceinline void Allegrex::Instruction$< 0xD2A88000, 0xFFF88080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMOVF<3>(vd(opcode), vs(opcode), uimm3(opcode)); EPILOG;
}

/* VCMOVF_Q */
__forceinline void Allegrex::Instruction$< 0xD2A88080, 0xFFF88080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCMOVF<4>(vd(opcode), vs(opcode), uimm3(opcode)); EPILOG;
}

/* VWBN_S */
__forceinline void Allegrex::Instruction$< 0xD3000000, 0xFF008080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VWBN<1>(vd(opcode), vs(opcode), uimm8(opcode)); EPILOG;
}

/* LVL_Q */
__forceinline void Allegrex::Instruction$< 0xD4000000, 0xFC000002 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LVL_Q(vt52(opcode), rs(opcode), simm14(opcode)); EPILOG;
}

/* LVR_Q */
__forceinline void Allegrex::Instruction$< 0xD4000002, 0xFC000002 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LVR_Q(vt52(opcode), rs(opcode), simm14(opcode)); EPILOG;
}

/* LV_Q */
__forceinline void Allegrex::Instruction$< 0xD8000000, 0xFC000002 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$LV_Q(vt52(opcode), rs(opcode), simm14(opcode)); EPILOG;
}

/* VPFXS */
__forceinline void Allegrex::Instruction$< 0xDC000000, 0xFF000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VPFXS(uimm24(opcode)); EPILOG;
}

/* VPFXT */
__forceinline void Allegrex::Instruction$< 0xDD000000, 0xFF000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VPFXT(uimm24(opcode)); EPILOG;
}

/* VPFXD */
__forceinline void Allegrex::Instruction$< 0xDE000000, 0xFF000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VPFXD(uimm24(opcode)); EPILOG;
}

/* VIIM */
__forceinline void Allegrex::Instruction$< 0xDF000000, 0xFF800000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VIIM(vt(opcode), uimm16(opcode)); EPILOG;
}

/* VFIM */
__forceinline void Allegrex::Instruction$< 0xDF800000, 0xFF800000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VFIM(vt(opcode), uimm16(opcode)); EPILOG;
}

/* SC */
__forceinline void Allegrex::Instruction$< 0xE0000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SC(rt(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* SWC1 */
__forceinline void Allegrex::Instruction$< 0xE4000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SWC1(ft(opcode), rs(opcode), simm16(opcode)); EPILOG;
}

/* SV_S */
__forceinline void Allegrex::Instruction$< 0xE8000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SV_S(vt52(opcode), rs(opcode), simm14(opcode)); EPILOG;
}

/* VMMUL_P */
__forceinline void Allegrex::Instruction$< 0xF0000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMMUL<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMMUL_T */
__forceinline void Allegrex::Instruction$< 0xF0008000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMMUL<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMMUL_Q */
__forceinline void Allegrex::Instruction$< 0xF0008080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMMUL<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VHTFM2_P */
__forceinline void Allegrex::Instruction$< 0xF0800000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VHTFM2<1>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VTFM2_P */
__forceinline void Allegrex::Instruction$< 0xF0800080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VTFM2<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VHTFM3_T */
__forceinline void Allegrex::Instruction$< 0xF1000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VHTFM3<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VTFM3_T */
__forceinline void Allegrex::Instruction$< 0xF1008000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VTFM3<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VHTFM4_Q */
__forceinline void Allegrex::Instruction$< 0xF1808000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VHTFM4<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VTFM4_Q */
__forceinline void Allegrex::Instruction$< 0xF1808080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VTFM4<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMSCL_P */
__forceinline void Allegrex::Instruction$< 0xF2000080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMSCL<2>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMSCL_T */
__forceinline void Allegrex::Instruction$< 0xF2008000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMSCL<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMSCL_Q */
__forceinline void Allegrex::Instruction$< 0xF2008080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMSCL<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VCRSP_T */
__forceinline void Allegrex::Instruction$< 0xF2808000, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VCRSP<3>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VQMUL_Q */
__forceinline void Allegrex::Instruction$< 0xF2808080, 0xFF808080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VQMUL<4>(vd(opcode), vs(opcode), vt(opcode)); EPILOG;
}

/* VMMOV_P */
__forceinline void Allegrex::Instruction$< 0xF3800080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMMOV<2>(vd(opcode), vs(opcode)); EPILOG;
}

/* VMMOV_T */
__forceinline void Allegrex::Instruction$< 0xF3808000, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMMOV<3>(vd(opcode), vs(opcode)); EPILOG;
}

/* VMMOV_Q */
__forceinline void Allegrex::Instruction$< 0xF3808080, 0xFFFF8080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMMOV<4>(vd(opcode), vs(opcode)); EPILOG;
}

/* VMIDT_P */
__forceinline void Allegrex::Instruction$< 0xF3830080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMIDT<2>(vd(opcode)); EPILOG;
}

/* VMIDT_T */
__forceinline void Allegrex::Instruction$< 0xF3838000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMIDT<3>(vd(opcode)); EPILOG;
}

/* VMIDT_Q */
__forceinline void Allegrex::Instruction$< 0xF3838080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMIDT<4>(vd(opcode)); EPILOG;
}

/* VMZERO_P */
__forceinline void Allegrex::Instruction$< 0xF3860080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMZERO<2>(vd(opcode)); EPILOG;
}

/* VMZERO_T */
__forceinline void Allegrex::Instruction$< 0xF3868000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMZERO<3>(vd(opcode)); EPILOG;
}

/* VMZERO_Q */
__forceinline void Allegrex::Instruction$< 0xF3868080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMZERO<4>(vd(opcode)); EPILOG;
}

/* VMONE_P */
__forceinline void Allegrex::Instruction$< 0xF3870080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMONE<2>(vd(opcode)); EPILOG;
}

/* VMONE_T */
__forceinline void Allegrex::Instruction$< 0xF3878000, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMONE<3>(vd(opcode)); EPILOG;
}

/* VMONE_Q */
__forceinline void Allegrex::Instruction$< 0xF3878080, 0xFFFFFF80 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VMONE<4>(vd(opcode)); EPILOG;
}

/* VROT_P */
__forceinline void Allegrex::Instruction$< 0xF3A00080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VROT<2>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VROT_T */
__forceinline void Allegrex::Instruction$< 0xF3A08000, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VROT<3>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* VROT_Q */
__forceinline void Allegrex::Instruction$< 0xF3A08080, 0xFFE08080 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$VROT<4>(vd(opcode), vs(opcode), uimm5(opcode)); EPILOG;
}

/* SVL_Q */
__forceinline void Allegrex::Instruction$< 0xF4000000, 0xFC000002 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SVL_Q(vt52(opcode), rs(opcode), simm14(opcode)); EPILOG;
}

/* SVR_Q */
__forceinline void Allegrex::Instruction$< 0xF4000002, 0xFC000002 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SVR_Q(vt52(opcode), rs(opcode), simm14(opcode)); EPILOG;
}

/* SV_Q */
__forceinline void Allegrex::Instruction$< 0xF8000000, 0xFC000000 >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; context.do$SV_Q(vt52(opcode), rs(opcode), simm14(opcode)); EPILOG;
}

/* VNOP */
__forceinline void Allegrex::Instruction$< 0xFFFF0000, 0xFFFFFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* VSYNC */
__forceinline void Allegrex::Instruction$< 0xFFFF0320, 0xFFFFFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

/* VFLUSH */
__forceinline void Allegrex::Instruction$< 0xFFFF040D, 0xFFFFFFFF >::FastInterpret(Allegrex::Context & context, u32 opcode)
{
    PROLOG; //warnf(cpu, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName()); EPILOG;
}

#undef PROLOG
#undef EPILOG
