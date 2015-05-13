/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#define USE_REAL_INTERPRETER Allegrex::use_real_interpreter
#define CROSS_INTERPRETER Allegrex::use_cross_interpreter
#define INTERPRETER_LIKE Allegrex::interpreter_like_mode
#define NO_REGISTER_ALLOCATION Allegrex::no_register_allocation
#define TRACE_ALLEGREX_INSTRUCTION Allegrex::trace_instruction
#define JITASM_TRACE_CFG Allegrex::jitasm_trace_cfg
#define ICACHE_SLOW_MODE !Allegrex::icache_fast_mode

#include "emu.Log.h"

#include "lle.cpu(Allegrex).Instruction.h"
#include "lle.cpu(Allegrex).Context.h"

namespace Allegrex
{
    extern bool use_real_interpreter;
    extern bool use_cross_interpreter;
    extern bool interpreter_like_mode;
    extern bool no_register_allocation;
    extern bool trace_instruction;
    extern bool jitasm_trace_cfg;
    extern bool icache_fast_mode;

    extern Instruction * instruction_array[];

    extern void FastInterpret(Allegrex::Context & processor, u32 opcode);

    extern Instruction * DecodeInstruction(u32 opcode);

    extern u64 Disassemble(u32 address, u32 opcode, char * line);

    extern u64 Infos(u32 opcode);

    static u64 const IS_CONDITIONAL_BRANCH  = 0x0000000000000001ULL;
    static u64 const IS_DIRECT_JUMP         = 0x0000000000000002ULL;
    static u64 const IS_INDIRECT_JUMP       = 0x0000000000000004ULL;
    static u64 const IS_SYSCALL             = 0x0000000000000008ULL;

    static u64 const HAS_DELAY_SLOT         = IS_CONDITIONAL_BRANCH|IS_DIRECT_JUMP|IS_INDIRECT_JUMP;

    static u64 const HAS_RS_AS_INPUT        = 0x0000000000000010ULL;
    static u64 const HAS_RS_AS_BASE         = 0x0000000000000020ULL;
    static u64 const HAS_RT_AS_INPUT        = 0x0000000000000040ULL;
    static u64 const HAS_RT_AS_OUTPUT       = 0x0000000000000080ULL;
    static u64 const HAS_RD_AS_OUTPUT       = 0x0000000000000100ULL;
    static u64 const HAS_LO_AS_INPUT        = 0x0000000000000200ULL;
    static u64 const HAS_LO_AS_OUTPUT       = 0x0000000000000400ULL;
    static u64 const HAS_HI_AS_INPUT        = 0x0000000000000800ULL;
    static u64 const HAS_HI_AS_OUTPUT       = 0x0000000000001000ULL;
    static u64 const HAS_RA_AS_INPUT        = 0x0000000000002000ULL;
    static u64 const HAS_RA_AS_OUTPUT       = 0x0000000000004000ULL;
    static u64 const HAS_SA                 = 0x0000000000008000ULL;
    static u64 const HAS_IMM16              = 0x0000000000010000ULL;
    static u64 const HAS_IMM26              = 0x0000000000020000ULL;
    static u64 const HAS_LSB                = 0x0000000000040000ULL;
    static u64 const HAS_MSB                = 0x0000000000080000ULL;

    static u64 const IS_ZEROEXTENDED        = 0x0000000000100000ULL;
    static u64 const IS_SHIFT               = 0x0000000000200000ULL;
    static u64 const IS_BITOP               = 0x0000000000400000ULL;
    static u64 const IS_CACHE               = 0x0000000000800000ULL;
    static u64 const IS_LOAD                = 0x0000000001000000ULL;
    static u64 const IS_STORE               = 0x0000000002000000ULL;
    static u64 const IS_BREAK               = 0x0000000004000000ULL;

    static u64 const HAS_FS_AS_INPUT        = 0x0000000010000000ULL;
    static u64 const HAS_FS_AS_OUTPUT       = 0x0000000020000000ULL;
    static u64 const HAS_FT_AS_INPUT        = 0x0000000040000000ULL;
    static u64 const HAS_FT_AS_OUTPUT       = 0x0000000080000000ULL;
    static u64 const HAS_FD_AS_OUTPUT       = 0x0000000100000000ULL;
    static u64 const HAS_FCOND              = 0x0000000200000000ULL;
    static u64 const HAS_FCR31_AS_INPUT     = 0x0000000400000000ULL;
    static u64 const HAS_FCR31_AS_OUTPUT    = 0x0000000800000000ULL;

    static u64 const HAS_VSIZE              = 0x0800000000000000ULL;
    static u64 const IS_VFPU0               = 0x4000000000000000ULL;
    static u64 const IS_VFPU1               = 0x4000001000000000ULL;
    static u64 const IS_VFPU2               = 0x4000002000000000ULL;
    static u64 const IS_VFPU3               = 0x4000003000000000ULL;
    static u64 const IS_VFPU4               = 0x4000004000000000ULL;
    static u64 const IS_VFPU5               = 0x4000005000000000ULL;
    static u64 const IS_VFPU6               = 0x4000006000000000ULL;
    static u64 const IS_VFPU7               = 0x4000007000000000ULL;
    static u64 const HAS_VD_AS_INPUT        = 0x0000010000000000ULL;
    static u64 const HAS_VD_AS_OUTPUT       = 0x0000020000000000ULL;
    static u64 const HAS_VT_AS_OUTPUT       = 0x0000040000000000ULL;
    static u64 const HAS_VT_AS_INPUT        = 0x0000080000000000ULL;
    static u64 const HAS_VS_AS_INPUT        = 0x0000100000000000ULL;
    static u64 const HAS_VCC_AS_INPUT       = 0x0000400000000000ULL;
    static u64 const HAS_VCC_AS_OUTPUT      = 0x0000800000000000ULL;
    static u64 const HAS_IMM24              = 0x0001000000000000ULL;
    static u64 const HAS_IMM14              = 0x0002000000000000ULL;
    static u64 const HAS_IMM8               = 0x0004000000000000ULL;
    static u64 const HAS_IMM5               = 0x0008000000000000ULL;
    static u64 const HAS_IMM4               = 0x0010000000000000ULL;
    static u64 const HAS_IMM3               = 0x0020000000000000ULL;

    static u64 const IS_UNIMPLEMENTED       = 0x0400000000000000ULL;
    static u64 const IS_BREAKPOINT          = 0x8000000000000000ULL;

    static u64 const HAS_HILO_AS_INPUT      = HAS_HI_AS_INPUT|HAS_LO_AS_INPUT;
    static u64 const HAS_HILO_AS_OUTPUT     = HAS_HI_AS_OUTPUT|HAS_LO_AS_OUTPUT;

    static u64 const IS_CPU                 = HAS_RD_AS_OUTPUT|HAS_RT_AS_OUTPUT|HAS_RS_AS_INPUT|HAS_RT_AS_INPUT;
    static u64 const IS_LSU                 = IS_LOAD|IS_STORE|IS_CACHE;
    static u64 const IS_BCU                 = IS_CONDITIONAL_BRANCH|IS_DIRECT_JUMP|IS_INDIRECT_JUMP|IS_SYSCALL|IS_BREAK;
    static u64 const IS_MDU                 = HAS_HILO_AS_OUTPUT|HAS_HILO_AS_INPUT;
    static u64 const IS_FPU                 = HAS_FD_AS_OUTPUT|HAS_FS_AS_OUTPUT|HAS_FT_AS_OUTPUT|HAS_FCR31_AS_OUTPUT|HAS_FS_AS_INPUT|HAS_FT_AS_INPUT|HAS_FCR31_AS_INPUT;
    static u64 const IS_VFPU                = IS_VFPU0|IS_VFPU1|IS_VFPU2|IS_VFPU3|IS_VFPU4|IS_VFPU5|IS_VFPU6|IS_VFPU7;

    extern void scan_for_functions(u32 start, u32 end);

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

    extern char const * cache_name[32];
}

#define ALLEGREX_MAKE_J(address)      (0x08000000 | ((address)>>2))
#define ALLEGREX_MAKE_JAL(address)    (0x0C000000 | ((address)>>2))
#define ALLEGREX_MAKE_JR_RA()         (0x03e00008)
#define ALLEGREX_MAKE_NOP()           (0)
#define ALLEGREX_MAKE_LUI(reg, value) (0x3c000000 | (reg<<16) | value)

#include "lle.cpu(Allegrex).ICache.h"

namespace lle
{
    namespace cpu = Allegrex;
}
