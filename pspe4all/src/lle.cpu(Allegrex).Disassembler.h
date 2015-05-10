/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

template< u64 infos, u32 signature, u32 mask >
static inline void disassemble_opcode(Allegrex::Instruction & /*insn*/, u32 /*address*/, u32 opcode, char const * const fmt, char * opcode_name)
{
    using namespace Allegrex;

    if (opcode_name)
    {
        if ((signature == 0x00000000) && !opcode)
        {
            ::strcpy(opcode_name, "nop");
        }
        else if (infos == IS_UNIMPLEMENTED)
        {
            ::strcpy(opcode_name, (strcmp(fmt, "") ? fmt : "???"));
        }
        else
        {
            ::strcpy(opcode_name, fmt);
        }
    }
}

template< u64 infos, u32 signature, u32 mask >
static inline void disassemble_operands(Allegrex::Instruction & insn, u32 address, u32 opcode, char * operands, char * comment)
{
    using namespace Allegrex;

    if (!operands || !comment) return;

    if ((signature != 0x00000000) || opcode)
    {
        if (infos & IS_BCU)
        {
            switch (infos & (HAS_RD_AS_OUTPUT|HAS_RA_AS_OUTPUT|HAS_RS_AS_INPUT|HAS_RT_AS_INPUT|HAS_IMM16|HAS_IMM26|IS_SYSCALL))
            {
                case HAS_RS_AS_INPUT:
                case HAS_RD_AS_OUTPUT|HAS_RA_AS_OUTPUT|HAS_RS_AS_INPUT:
                {
                    u32 rs = insn.rs(opcode);
                    ::sprintf(operands, "%s", gpr_name[rs]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RD_AS_OUTPUT|HAS_RS_AS_INPUT:
                {
                    u32 rs = insn.rs(opcode);
                    u32 rd = insn.rd(opcode);
                    ::sprintf(operands, "%s, %s", gpr_name[rd], gpr_name[rs]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RS_AS_INPUT|HAS_RT_AS_INPUT|HAS_IMM16:
                {
                    u32 rs = insn.rs(opcode);
                    u32 rt = insn.rt(opcode);
                    ::sprintf(operands, "%s, %s, 0x%08X", gpr_name[rs], gpr_name[rt], address + 4 + (insn.simm16(opcode) << 2));
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RS_AS_INPUT|HAS_IMM16:
                {
                    u32 rs = insn.rs(opcode);
                    ::sprintf(operands, "%s, 0x%08X", gpr_name[rs], address + 4 + (insn.simm16(opcode) << 2));
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RS_AS_INPUT|HAS_IMM16|HAS_RA_AS_OUTPUT:
                {
                    u32 rs = insn.rs(opcode);
                    ::sprintf(operands, "%s, 0x%08X", gpr_name[rs], address + 4 + (insn.simm16(opcode) << 2));
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_IMM16:
                {
                    ::sprintf(operands, "0x%08X", address + 4 + (insn.simm16(opcode) << 2));
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_IMM26:
                {
                    ::sprintf(operands, "0x%08X", ((address + 4) & 0xf0000000) | (insn.uimm26(opcode) << 2));
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_IMM26|HAS_RA_AS_OUTPUT:
                {
                    ::sprintf(operands, "0x%08X", ((address + 4) & 0xf0000000) | (insn.uimm26(opcode) << 2));
                    ::sprintf(comment, "%s", gpr_name[31]);
                    return;
                }

                case IS_SYSCALL:
                {
                    ::sprintf(operands, "0x%08X (%s)", insn.uimm20(opcode), insn.GetSyscallName(opcode));
                    ::strcpy(comment, "");
                    return;
                }

                case IS_BREAK:
                {
                    ::sprintf(operands, "0x%08X", insn.uimm20(opcode));
                    ::strcpy(comment, "");
                    return;
                }
            }
        }
        else if (infos & IS_LSU)
        {
            switch (infos & (HAS_RT_AS_OUTPUT|HAS_FT_AS_OUTPUT|HAS_RS_AS_BASE|HAS_RT_AS_INPUT|HAS_FT_AS_INPUT|HAS_IMM16|IS_CACHE|IS_LOAD|IS_STORE))
            {
                case HAS_RS_AS_BASE|HAS_IMM16|IS_CACHE:
                {
                    u32 rs   = insn.rs(opcode);
                    u32 code = insn.rt(opcode);
                    s32 offs = insn.simm16(opcode);
                    ::sprintf(operands, "0x%02X, 0x%08X(%s)", code, offs, gpr_name[rs]);
                    ::sprintf(comment, "offset : %d", offs);
                    return;
                }

                case HAS_RT_AS_OUTPUT|HAS_RS_AS_BASE|HAS_IMM16|IS_LOAD:
                case HAS_RT_AS_INPUT|HAS_RS_AS_BASE|HAS_IMM16|IS_STORE:
                {
                    u32 rs   = insn.rs(opcode);
                    u32 rt   = insn.rt(opcode);
                    s32 offs = insn.simm16(opcode);
                    ::sprintf(operands, "%s, 0x%08X(%s)", gpr_name[rt], offs, gpr_name[rs]);
                    ::sprintf(comment, "offset : %d", offs);
                    return;
                }

                case HAS_FT_AS_OUTPUT|HAS_RS_AS_BASE|HAS_IMM16|IS_LOAD:
                case HAS_FT_AS_INPUT|HAS_RS_AS_BASE|HAS_IMM16|IS_STORE:
                {
                    u32 rs   = insn.rs(opcode);
                    u32 ft   = insn.ft(opcode);
                    s32 offs = insn.simm16(opcode);
                    ::sprintf(operands, "%s, 0x%08X(%s)", fpr_name[ft], offs, gpr_name[rs]);
                    ::sprintf(comment, "offset : %d", offs);
                    return;
                }
            }
        }
        else if (infos & IS_MDU)
        {
            switch (infos & (HAS_HILO_AS_OUTPUT|HAS_RD_AS_OUTPUT|HAS_HILO_AS_INPUT|HAS_RS_AS_INPUT|HAS_RT_AS_INPUT))
            {
                case HAS_HILO_AS_OUTPUT|HAS_RS_AS_INPUT|HAS_RT_AS_INPUT:
                case HAS_HILO_AS_OUTPUT|HAS_HILO_AS_INPUT|HAS_RS_AS_INPUT|HAS_RT_AS_INPUT:
                {
                    u32 rs = insn.rs(opcode);
                    u32 rt = insn.rt(opcode);
                    ::sprintf(operands, "%s, %s", gpr_name[rs], gpr_name[rt]);
                    ::strcpy(comment, "");
                    return;
                }
                case HAS_LO_AS_INPUT|HAS_RD_AS_OUTPUT:
                case HAS_HI_AS_INPUT|HAS_RD_AS_OUTPUT:
                {
                    u32 rd = insn.rd(opcode);
                    ::sprintf(operands, "%s", gpr_name[rd]);
                    ::strcpy(comment, "");
                    return;
                }
                case HAS_LO_AS_OUTPUT|HAS_RS_AS_INPUT:
                case HAS_HI_AS_OUTPUT|HAS_RS_AS_INPUT:
                {
                    u32 rs = insn.rs(opcode);
                    ::sprintf(operands, "%s", gpr_name[rs]);
                    ::strcpy(comment, "");
                    return;
                }
            }
        }
        else if (infos & IS_FPU)
        {
            switch (infos & (HAS_FD_AS_OUTPUT|HAS_FS_AS_OUTPUT|HAS_RT_AS_OUTPUT|HAS_FCR31_AS_OUTPUT|HAS_FS_AS_INPUT|HAS_FT_AS_INPUT|HAS_RT_AS_INPUT|HAS_FCR31_AS_INPUT))
            {
                case HAS_FD_AS_OUTPUT|HAS_FS_AS_INPUT|HAS_FT_AS_INPUT:
                {
                    u32 fs   = insn.fs(opcode);
                    u32 ft   = insn.ft(opcode);
                    u32 fd   = insn.fd(opcode);
                    ::sprintf(operands, "%s, %s, %s", fpr_name[fd], fpr_name[fs], fpr_name[ft]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_FD_AS_OUTPUT|HAS_FS_AS_INPUT:
                {
                    u32 fs   = insn.fs(opcode);
                    u32 fd   = insn.fd(opcode);
                    ::sprintf(operands, "%s, %s", fpr_name[fd], fpr_name[fs]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_FS_AS_INPUT|HAS_FT_AS_INPUT:
                case HAS_FCR31_AS_OUTPUT|HAS_FS_AS_INPUT|HAS_FT_AS_INPUT:
                {
                    u32 fs   = insn.fs(opcode);
                    u32 ft   = insn.ft(opcode);
                    ::sprintf(operands, "%s, %s", fpr_name[fs], fpr_name[ft]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_FS_AS_OUTPUT|HAS_RT_AS_INPUT:
                case HAS_RT_AS_OUTPUT|HAS_FS_AS_INPUT:
                {
                    u32 rt   = insn.rt(opcode);
                    u32 fs   = insn.fs(opcode);
                    ::sprintf(operands, "%s, %s", gpr_name[rt], fpr_name[fs]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_FCR31_AS_OUTPUT|HAS_RT_AS_INPUT:
                case HAS_RT_AS_OUTPUT|HAS_FCR31_AS_INPUT:
                {
                    u32 rt   = insn.rt(opcode);
                    u32 fs   = insn.fs(opcode);
                    ::sprintf(operands, "%s, %s", gpr_name[rt], fcr_name[fs]);
                    ::strcpy(comment, "");
                    return;
                }
            }
        }
        else if (infos & IS_CPU)
        {
            switch (infos & (HAS_RT_AS_OUTPUT|HAS_RD_AS_OUTPUT|HAS_RS_AS_INPUT|HAS_RT_AS_INPUT|HAS_RT_AS_INPUT|HAS_SA|HAS_LSB|HAS_MSB|HAS_IMM16|IS_SHIFT|IS_ZEROEXTENDED))
            {
                case HAS_RD_AS_OUTPUT|HAS_RS_AS_INPUT|HAS_RT_AS_INPUT:
                {
                    u32 rd = insn.rd(opcode);
                    u32 rs = insn.rs(opcode);
                    u32 rt = insn.rt(opcode);
                    ::sprintf(operands, "%s, %s, %s", gpr_name[rd], gpr_name[rs], gpr_name[rt]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RD_AS_OUTPUT|HAS_RS_AS_INPUT:
                {
                    u32 rd = insn.rd(opcode);
                    u32 rs = insn.rs(opcode);
                    ::sprintf(operands, "%s, %s", gpr_name[rd], gpr_name[rs]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RD_AS_OUTPUT|HAS_RT_AS_INPUT:
                {
                    u32 rd = insn.rd(opcode);
                    u32 rt = insn.rt(opcode);
                    ::sprintf(operands, "%s, %s", gpr_name[rd], gpr_name[rt]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RD_AS_OUTPUT|HAS_RT_AS_INPUT|HAS_SA|IS_SHIFT:
                {
                    u32 rd = insn.rd(opcode);
                    u32 rt = insn.rt(opcode);
                    ::sprintf(operands, "%s, %s, %d", gpr_name[rd], gpr_name[rt], insn.sa(opcode));
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RD_AS_OUTPUT|HAS_RT_AS_INPUT|HAS_RS_AS_INPUT|IS_SHIFT:
                {
                    u32 rd = insn.rd(opcode);
                    u32 rs = insn.rs(opcode);
                    u32 rt = insn.rt(opcode);
                    ::sprintf(operands, "%s, %s, %s", gpr_name[rd], gpr_name[rt], gpr_name[rs]);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RT_AS_OUTPUT|HAS_RS_AS_INPUT|HAS_LSB:
                {
                    u32 rs = insn.rs(opcode);
                    u32 rt = insn.rt(opcode);
                    u32 pos = insn.sa(opcode);
                    u32 len = insn.rd(opcode) + 1;
                    ::sprintf(operands, "%s, %s, %d, %d", gpr_name[rt], gpr_name[rs], pos, len);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RT_AS_OUTPUT|HAS_RS_AS_INPUT|HAS_LSB|HAS_MSB:
                {
                    u32 rs = insn.rs(opcode);
                    u32 rt = insn.rt(opcode);
                    u32 pos = insn.sa(opcode);
                    u32 len = insn.rd(opcode) - pos + 1;
                    ::sprintf(operands, "%s, %s, %d, %d", gpr_name[rt], gpr_name[rs], pos, len);
                    ::strcpy(comment, "");
                    return;
                }

                case HAS_RT_AS_OUTPUT|HAS_RS_AS_INPUT|HAS_IMM16:
                {
                    u32 rs = insn.rs(opcode);
                    u32 rt = insn.rt(opcode);
                    s32 imm16 = insn.simm16(opcode);
                    ::sprintf(operands, "%s, %s, 0x%08X", gpr_name[rt], gpr_name[rs], imm16);
                    ::sprintf(comment, "constant : %d", imm16);
                    return;
                }

                case HAS_RT_AS_OUTPUT|HAS_RS_AS_INPUT|HAS_IMM16|IS_ZEROEXTENDED:
                {
                    u32 rs = insn.rs(opcode);
                    u32 rt = insn.rt(opcode);
                    u32 imm16 = insn.uimm16(opcode);
                    ::sprintf(operands, "%s, %s, 0x%08X", gpr_name[rt], gpr_name[rs], imm16);
                    ::sprintf(comment, "constant : %u", imm16);
                    return;
                }
                case HAS_RT_AS_OUTPUT|HAS_IMM16:
                {
                    u32 rt = insn.rt(opcode);
                    s32 imm16 = insn.simm16(opcode);
                    ::sprintf(operands, "%s, 0x%08X", gpr_name[rt], imm16);
                    imm16 <<= 16;
                    ::sprintf(comment, "constant : 0x%08X / %d / %u", imm16, imm16, imm16);
                    return;
                }
            }
        }
        else if (infos == IS_UNIMPLEMENTED)
        {
            ::sprintf(operands, "(0x%08X)", opcode);
            ::sprintf(comment, "Unimplemented instruction (0x%08X)", opcode);
            return;
        }
    }

    ::strcpy(operands, "");
    ::strcpy(comment, "");
}

#undef IDEF
#define IDEF(nam, m_msk, sig, res0, res1, fmt, inf) void Allegrex::Instruction$< sig, m_msk >::Disassemble(u32 address, u32 opcode, char * opcode_name, char * operands, char * comment) { using namespace Allegrex; disassemble_opcode< inf, sig, m_msk >(*this, address, opcode, fmt, opcode_name); disassemble_operands< inf, sig, m_msk >(*this, address, opcode, operands, comment); }

#include "lle.cpu(Allegrex).def"
