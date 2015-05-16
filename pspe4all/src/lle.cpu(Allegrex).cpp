/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "lle.mmu.h"
#include "lle.cpu(Allegrex).h"

bool Allegrex::use_real_interpreter = false;
bool Allegrex::use_cross_interpreter = false;
bool Allegrex::interpreter_like_mode = false;
bool Allegrex::no_register_allocation = false;
bool Allegrex::trace_instruction = false;
bool Allegrex::jitasm_trace_cfg = false;
bool Allegrex::icache_fast_mode = true;

std::wstring Allegrex::use_debugger(L"none");
bool         Allegrex::use_debug_server = false;

namespace emu
{
    namespace log
    {
        __weaksymbol SubCategory cpu(lle, "cpu", "Allegrex");
    }
}

#undef IDEF
#define IDEF(nam, m_msk, sig, res0, res1, fmt, inf) u64 Allegrex::Instruction$< sig, m_msk >::Infos() { using namespace Allegrex; return inf; }
#include "lle.cpu(Allegrex).def"

#include "lle.cpu(Allegrex).Disassembler.h"
#include "lle.cpu(Allegrex).Interpreter.h"

#undef IDEF

#define IDEF(nam, m_msk, sig, res0, res1, fmt, inf) void Allegrex::Instruction$##nam::Interpret(Allegrex::Context & context, u32 opcode) { FastInterpret(context, opcode); }
#include "lle.cpu(Allegrex).def"
#undef IDEF

#define IDEF(nam, m_msk, sig, res0, res1, fmt, inf) __forceinline char const * Allegrex::Instruction$##nam::FastOpcodeName() { return #nam; }
#include "lle.cpu(Allegrex).def"
#undef IDEF

#define IDEF(nam, m_msk, sig, res0, res1, fmt, inf) u64 Allegrex::Instruction$##nam::count = u64();
#include "lle.cpu(Allegrex).def"
#undef IDEF

namespace Allegrex
{
    InstructionUnknown & reserved_instruction = InstructionUnknown::Self();

#define IDEF(nam, m_msk, sig, res0, res1, fmt, inf) Instruction$##nam &nam = Instruction$##nam ::Self();
#include "lle.cpu(Allegrex).def"
#undef IDEF

    Instruction * instruction_array[] =
    {
#define IDEF(nam, m_msk, sig, res0, res1, fmt, inf) &nam,
#include "lle.cpu(Allegrex).def"
#undef IDEF
        0
    };

    char const * gpr_name[32] =
    {
        "$zr", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
    };

    char const * fpr_name[32] =
    {
        "$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7",
        "$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15",
        "$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23",
        "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31"
    };

    char const * vpr_name[4][128] =
    {
        {
            "S000.s", "S010.s", "S020.s", "S030.s",
            "S100.s", "S110.s", "S120.s", "S130.s",
            "S200.s", "S210.s", "S220.s", "S230.s",
            "S300.s", "S310.s", "S320.s", "S330.s",
            "S400.s", "S410.s", "S420.s", "S430.s",
            "S500.s", "S510.s", "S520.s", "S530.s",
            "S600.s", "S610.s", "S620.s", "S630.s",
            "S700.s", "S710.s", "S720.s", "S730.s",
            "S001.s", "S011.s", "S021.s", "S031.s",
            "S101.s", "S111.s", "S121.s", "S131.s",
            "S201.s", "S211.s", "S221.s", "S231.s",
            "S301.s", "S311.s", "S321.s", "S331.s",
            "S401.s", "S411.s", "S421.s", "S431.s",
            "S501.s", "S511.s", "S521.s", "S531.s",
            "S601.s", "S611.s", "S621.s", "S631.s",
            "S701.s", "S711.s", "S721.s", "S731.s",
            "S002.s", "S012.s", "S022.s", "S032.s",
            "S102.s", "S112.s", "S122.s", "S132.s",
            "S202.s", "S212.s", "S222.s", "S232.s",
            "S302.s", "S312.s", "S322.s", "S332.s",
            "S402.s", "S412.s", "S422.s", "S432.s",
            "S502.s", "S512.s", "S522.s", "S532.s",
            "S602.s", "S612.s", "S622.s", "S632.s",
            "S702.s", "S712.s", "S722.s", "S732.s",
            "S003.s", "S013.s", "S023.s", "S033.s",
            "S103.s", "S113.s", "S123.s", "S133.s",
            "S203.s", "S213.s", "S223.s", "S233.s",
            "S303.s", "S313.s", "S323.s", "S333.s",
            "S403.s", "S413.s", "S423.s", "S433.s",
            "S503.s", "S513.s", "S523.s", "S533.s",
            "S603.s", "S613.s", "S623.s", "S633.s",
            "S703.s", "S713.s", "S723.s", "S733.s"
        },
        {
            "C000.p", "C010.p", "C020.p", "C030.p",
            "C100.p", "C110.p", "C120.p", "C130.p",
            "C200.p", "C210.p", "C220.p", "C230.p",
            "C300.p", "C310.p", "C320.p", "C330.p",
            "C400.p", "C410.p", "C420.p", "C430.p",
            "C500.p", "C510.p", "C520.p", "C530.p",
            "C600.p", "C610.p", "C620.p", "C630.p",
            "C700.p", "C710.p", "C720.p", "C730.p",
            "R000.p", "R001.p", "R002.p", "R003.p",
            "R100.p", "R101.p", "R102.p", "R103.p",
            "R200.p", "R201.p", "R202.p", "R203.p",
            "R300.p", "R301.p", "R302.p", "R303.p",
            "R400.p", "R401.p", "R402.p", "R403.p",
            "R500.p", "R501.p", "R502.p", "R503.p",
            "R600.p", "R601.p", "R602.p", "R603.p",
            "R700.p", "R701.p", "R702.p", "R703.p",
            "C002.p", "C012.p", "C022.p", "C032.p",
            "C102.p", "C112.p", "C122.p", "C132.p",
            "C202.p", "C212.p", "C222.p", "C232.p",
            "C302.p", "C312.p", "C322.p", "C332.p",
            "C402.p", "C412.p", "C422.p", "C432.p",
            "C502.p", "C512.p", "C522.p", "C532.p",
            "C602.p", "C612.p", "C622.p", "C632.p",
            "C702.p", "C712.p", "C722.p", "C732.p",
            "R020.p", "R021.p", "R022.p", "R023.p",
            "R120.p", "R121.p", "R122.p", "R123.p",
            "R220.p", "R221.p", "R222.p", "R223.p",
            "R320.p", "R321.p", "R322.p", "R323.p",
            "R420.p", "R421.p", "R422.p", "R423.p",
            "R520.p", "R521.p", "R522.p", "R523.p",
            "R620.p", "R621.p", "R622.p", "R623.p",
            "R720.p", "R721.p", "R722.p", "R723.p"
        },
        {
            "C000.t", "C010.t", "C020.t", "C030.t",
            "C100.t", "C110.t", "C120.t", "C130.t",
            "C200.t", "C210.t", "C220.t", "C230.t",
            "C300.t", "C310.t", "C320.t", "C330.t",
            "C400.t", "C410.t", "C420.t", "C430.t",
            "C500.t", "C510.t", "C520.t", "C530.t",
            "C600.t", "C610.t", "C620.t", "C630.t",
            "C700.t", "C710.t", "C720.t", "C730.t",
            "R000.t", "R001.t", "R002.t", "R003.t",
            "R100.t", "R101.t", "R102.t", "R103.t",
            "R200.t", "R201.t", "R202.t", "R203.t",
            "R300.t", "R301.t", "R302.t", "R303.t",
            "R400.t", "R401.t", "R402.t", "R403.t",
            "R500.t", "R501.t", "R502.t", "R503.t",
            "R600.t", "R601.t", "R602.t", "R603.t",
            "R700.t", "R701.t", "R702.t", "R703.t",
            "C001.t", "C011.t", "C021.t", "C031.t",
            "C101.t", "C111.t", "C121.t", "C131.t",
            "C201.t", "C211.t", "C221.t", "C231.t",
            "C301.t", "C311.t", "C321.t", "C331.t",
            "C401.t", "C411.t", "C421.t", "C431.t",
            "C501.t", "C511.t", "C521.t", "C531.t",
            "C601.t", "C611.t", "C621.t", "C631.t",
            "C701.t", "C711.t", "C721.t", "C731.t",
            "R010.t", "R011.t", "R012.t", "R013.t",
            "R110.t", "R111.t", "R112.t", "R113.t",
            "R210.t", "R211.t", "R212.t", "R213.t",
            "R310.t", "R311.t", "R312.t", "R313.t",
            "R410.t", "R411.t", "R412.t", "R413.t",
            "R510.t", "R511.t", "R512.t", "R513.t",
            "R610.t", "R611.t", "R612.t", "R613.t",
            "R710.t", "R711.t", "R712.t", "R713.t"
        }, {
            "C000.q", "C010.q", "C020.q", "C030.q",
            "C100.q", "C110.q", "C120.q", "C130.q",
            "C200.q", "C210.q", "C220.q", "C230.q",
            "C300.q", "C310.q", "C320.q", "C330.q",
            "C400.q", "C410.q", "C420.q", "C430.q",
            "C500.q", "C510.q", "C520.q", "C530.q",
            "C600.q", "C610.q", "C620.q", "C630.q",
            "C700.q", "C710.q", "C720.q", "C730.q",
            "R000.q", "R001.q", "R002.q", "R003.q",
            "R100.q", "R101.q", "R102.q", "R103.q",
            "R200.q", "R201.q", "R202.q", "R203.q",
            "R300.q", "R301.q", "R302.q", "R303.q",
            "R400.q", "R401.q", "R402.q", "R403.q",
            "R500.q", "R501.q", "R502.q", "R503.q",
            "R600.q", "R601.q", "R602.q", "R603.q",
            "R700.q", "R701.q", "R702.q", "R703.q",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", "",
            "", "", "", ""
        }
    };

    char const * mpr_name[4][128] =
    {
        {
        },
        {
            "M000.p", "", "M020.p", "",
            "M100.p", "", "M120.p", "",
            "M200.p", "", "M220.p", "",
            "M300.p", "", "M320.p", "",
            "M400.p", "", "M420.p", "",
            "M500.p", "", "M520.p", "",
            "M600.p", "", "M620.p", "",
            "M700.p", "", "M720.p", "",
            "E000.p", "", "E002.p", "",
            "E100.p", "", "E102.p", "",
            "E200.p", "", "E202.p", "",
            "E300.p", "", "E302.p", "",
            "E400.p", "", "E402.p", "",
            "E500.p", "", "E502.p", "",
            "E600.p", "", "E602.p", "",
            "E700.p", "", "E702.p", "",
            "M002.p", "", "M022.p", "",
            "M102.p", "", "M122.p", "",
            "M202.p", "", "M222.p", "",
            "M302.p", "", "M322.p", "",
            "M402.p", "", "M422.p", "",
            "M502.p", "", "M522.p", "",
            "M602.p", "", "M622.p", "",
            "M702.p", "", "M722.p", "",
            "E020.p", "", "E022.p", "",
            "E120.p", "", "E122.p", "",
            "E220.p", "", "E222.p", "",
            "E320.p", "", "E322.p", "",
            "E420.p", "", "E422.p", "",
            "E520.p", "", "E522.p", "",
            "E620.p", "", "E622.p", "",
            "E720.p", "", "E722.p", ""
        },
        {
            "M000.t", "M010.t", "", "",
            "M100.t", "M110.t", "", "",
            "M200.t", "M210.t", "", "",
            "M300.t", "M310.t", "", "",
            "M400.t", "M410.t", "", "",
            "M500.t", "M510.t", "", "",
            "M600.t", "M610.t", "", "",
            "M700.t", "M710.t", "", "",
            "E000.t", "E001.t", "", "",
            "E100.t", "E101.t", "", "",
            "E200.t", "E201.t", "", "",
            "E300.t", "E301.t", "", "",
            "E400.t", "E401.t", "", "",
            "E500.t", "E501.t", "", "",
            "E600.t", "E601.t", "", "",
            "E700.t", "E701.t", "", "",
            "M001.t", "M011.t", "", "",
            "M101.t", "M111.t", "", "",
            "M201.t", "M211.t", "", "",
            "M301.t", "M311.t", "", "",
            "M401.t", "M411.t", "", "",
            "M501.t", "M511.t", "", "",
            "M601.t", "M611.t", "", "",
            "M701.t", "M711.t", "", "",
            "E010.t", "E011.t", "", "",
            "E110.t", "E111.t", "", "",
            "E210.t", "E211.t", "", "",
            "E310.t", "E311.t", "", "",
            "E410.t", "E411.t", "", "",
            "E510.t", "E511.t", "", "",
            "E610.t", "E611.t", "", "",
            "E710.t", "E711.t", "", ""
        }, {
            "M000.q", "", "", "",
            "M100.q", "", "", "",
            "M200.q", "", "", "",
            "M300.q", "", "", "",
            "M400.q", "", "", "",
            "M500.q", "", "", "",
            "M600.q", "", "", "",
            "M700.q", "", "", "",
            "E000.q", "", "", "",
            "E100.q", "", "", "",
            "E200.q", "", "", "",
            "E300.q", "", "", "",
            "E400.q", "", "", "",
            "E500.q", "", "", "",
            "E600.q", "", "", "",
            "E700.q", "", "", ""
        }
    };

    char const * vfpu_constant[32] =
    {
        "", "VFPU_HUGE", "VFPU_SQRT2", "VFPU_SQRT1_2",
        "VFPU_2_SQRTPI", "VFPU_2_PI", "VFPU_1_PI", "VFPU_PI_4",
        "VFPU_PI_2", "VFPU_PI", "VFPU_E", "VFPU_LOG2E",
        "VFPU_LOG10E", "VFPU_LN2", "VFPU_LN10", "VFPU_2PI",
        "VFPU_PI_6", "VFPU_LOG10TWO", "VFPU_LOG2TEN", "VFPU_SQRT3_2",
    };

    char const * fcr_name[32] =
    {
        "$fcsr0", "$fcsr1", "$fcsr2", "$fcsr3", "$fcsr4", "$fcsr5", "$fcsr6", "$fcsr7",
        "$fcsr8", "$fcsr9", "$fcsr10", "$fcsr11", "$fcsr12", "$fcsr13", "$fcsr14", "$fcsr15",
        "$fcsr16", "$fcsr17", "$fcsr18", "$fcsr19", "$fcsr20", "$fcsr21", "$fcsr22", "$fcsr23",
        "$fcsr24", "$fcsr25", "$fcsr26", "$fcsr27", "$fcsr28", "$fcsr29", "$fcsr30", "$fcsr31"
    };

    char const * cop0_name[32] =
    {
        "Index", "Random", "EntryLo0", "EntryLo1", "Context", "PageMask", "Wired", "cop0reg7",
        "BadVaddr", "Count", "EntryHi", "Compare", "Status", "Cause", "EPC", "PrID",
        "Config", "LLAddr", "WatchLo", "WatchHi", "XContext", "cop0reg21", "cop0reg22", "cop0reg23",
        "cop0reg24", "EBase", "ECC", "CacheErr", "TagLo", "TagHi", "ErrorPC", "cop0reg31"
    };



    char const * vsuffix[4] =
    {
        ".s",
        ".p",
        ".t",
        ".q"
    };

    char const * vpfx_name[4] =
    {
        "x",
        "y",
        "z",
        "w"
    };

    char const * cconds_name[16] =
    {
        "f",
        "un",
        "eq",
        "ueq",
        "olt",
        "ult",
        "ole",
        "ule",
        "sf",
        "ngle",
        "seq",
        "ngl",
        "lt",
        "nge",
        "le",
        "ngt"
    };

    char const * vcond_name[16] =
    {
        "FL",
        "EQ",
        "LT",
        "LE",
        "TR",
        "NE",
        "GE",
        "GT",
        "EZ",
        "EN",
        "EI",
        "ES",
        "NZ",
        "NN",
        "NI",
        "NS"
    };

    char const * cache_name[32] =
    {
        /* 0x00 */ "ICACHE - ???",
        /* 0x01 */ "ICACHE - ???",
        /* 0x02 */ "ICACHE - ???",
        /* 0x03 */ "ICACHE - ???",
        /* 0x04 */ "ICACHE - INDEX INVALIDATE",
        /* 0x05 */ "ICACHE - ???",
        /* 0x06 */ "ICACHE - INDEX_UNLOCK",
        /* 0x07 */ "ICACHE - ???",
        /* 0x08 */ "ICACHE - HIT INVALIDATE",
        /* 0x09 */ "ICACHE - ???",
        /* 0x0A */ "ICACHE - FILL",
        /* 0x0B */ "ICACHE - FILL WITH LOCK",
        /* 0x0C */ "ICACHE - ???",
        /* 0x0D */ "ICACHE - ???",
        /* 0x0E */ "ICACHE - ???",
        /* 0x0F */ "ICACHE - ???",
        /* 0x10 */ "DCACHE - ???",
        /* 0x11 */ "DCACHE - ???",
        /* 0x12 */ "DCACHE - ???",
        /* 0x13 */ "DCACHE - ???",
        /* 0x14 */ "DCACHE - INDEX WRITEBACK INVALIDATE",
        /* 0x15 */ "DCACHE - ???",
        /* 0x16 */ "DCACHE - INDEX UNLOCK",
        /* 0x17 */ "DCACHE - ???",
        /* 0x18 */ "DCACHE - CREATE DIRTY EXCLUSIVE",
        /* 0x19 */ "DCACHE - HIT INVALIDATE",
        /* 0x1A */ "DCACHE - HIT WRITEBACK",
        /* 0x1B */ "DCACHE - HIT WRITEBACK INVALIDATE",
        /* 0x1C */ "DCACHE - CREATE DIRTY EXCLUSIVE WITH LOCK",
        /* 0x1D */ "DCACHE - ???",
        /* 0x1E */ "DCACHE - FILL",
        /* 0x1F */ "DCACHE - FILL WITH LOCK"
    };

    u64 Disassemble(u32 address, u32 opcode, char * line)
    {
        char opcode_name[16];
        char operands[256];
        char comment[256];
        Instruction * insn = Allegrex::DecodeInstruction(opcode);
        insn->Disassemble(address, opcode, opcode_name, operands, comment);
        ::sprintf(line, "%08X  %-15s %-48s ", opcode, opcode_name, operands);
        return insn->Infos();
    }

    u64 Infos(u32 opcode)
    {
        return Allegrex::DecodeInstruction(opcode)->Infos();
    }

#define IDO(x) return ((Allegrex::Instruction *)&Allegrex::x)
    Instruction * DecodeInstruction(u32 opcode)
    {
#include "lle.cpu(Allegrex).Decoder.h"
        IDO(reserved_instruction);
    }
#undef IDO

#define IDO(x) do { Instruction$##x::FastInterpret(context, opcode); return; } while (0)
    void FastInterpret(Allegrex::Context & context, u32 opcode)
    {
#include "lle.cpu(Allegrex).Decoder.h"
        Allegrex::reserved_instruction.Interpret(context, opcode); return;
    }
#undef IDO
#undef IDO_VSIZE

#if 0
    struct Function
    {
        u32  start;
        u32  end;
        u32  hash;
        u32  size;
        bool is_straight_leaf;
        bool has_hash;
        bool uses_vfpu;
        char name[64];
    };

    std::vector< Function > functions;

    std::map< u32, Function * > hash_to_function;

    void update_hash_to_function_map()
    {
        hash_to_function.clear();
        for (std::vector< Function >::iterator iter = functions.begin(); iter != functions.end(); ++iter)
        {
            Function & f = *iter;
            if (f.has_hash)
            {
                hash_to_function[f.hash] = &f;
            }
        }
    }


    void hash_functions()
    {
        for (std::vector< Function >::iterator iter = functions.begin(); iter != functions.end(); ++iter)
        {
            Function & f = *iter;
            u32 hash = 0x1337babe;
            for (u32 addr = f.start; addr <= f.end; ++addr)
            {
                u32 validbits = 0xFFFFFFFF;
                u32 insn = *lle::mmu::Addr< u32 >(addr);
                u64 flags = Allegrex::Infos(insn);
                if (flags & HAS_IMM16)
                {
                    validbits &= ~0xFFFF;
                }
                else if (flags & HAS_IMM26)
                {
                    validbits &= ~0x3FFFFFF;
                }
                hash = _rotl(hash, 13);
                hash ^= (insn & validbits);
            }
            f.hash = hash;
            f.has_hash = true;
        }
    }

    void scan_for_functions(u32 startAddr, u32 endAddr)
    {
        Function currentFunction = { startAddr, 0, 0, 0, false, false, false, "" };

        u32 furthest_branch = 0;
        bool looking = false;
        bool end = false;
        bool is_straight_leaf = true;
        u32 address;
        for (address = startAddr; address <= endAddr; address += 4)
        {
            int n = SymbolMap::get_symbol_number(address, ST_FUNCTION);
            if (n != -1)
            {
                address = SymbolMap::get_symbol_address(n) + SymbolMap::get_symbol_size(n);
                continue;
            }

            u32 opcode = mm::memw(address);

            u32 direct_jump_opcode = opcode & 0xFC000000;

            u64 infos = Allegrex::Infos(opcode);

            u32 target = -1;

            if (infos & IS_CONDITIONAL_BRANCH)
            {
                target = address + (Instruction::simm16(opcode) << 2);

                is_straight_leaf = false;

                if (target > furthest_branch)
                {
                    furthest_branch = target;
                }
            }
            else if ((direct_jump_opcode == 0x08000000) || (opcode == 0x03E00008)) // JR $RA
            {
                if (furthest_branch >= address)
                {
                    looking = true;

                    address += 4;
                }
                else
                {
                    end = true;
                }
            }

            if (looking)
            {
                if (address >= furthest_branch)
                {
                    u32 target = -1;

                    if (infos & IS_CONDITIONAL_BRANCH)
                    {
                        u32 unconditional_branch_opcode = opcode & 0xFFFF0000;

                        switch (unconditional_branch_opcode)
                        {
                        case 0x10000000:
                        case 0x18000000:
                        case 0x04010000:
                        case 0x04030000:
                        case 0x50000000:
                        case 0x58000000:
                            target = address + (Instruction::simm16(opcode) << 2);
                        }

                        if (target < address)
                            end = true;
                    }
                    else if (direct_jump_opcode == 0x08000000)
                    {
                        target = (address & 0xF0000000)|(Instruction::uimm26(opcode) << 2);

                        if (target < address)
                            end = true;
                    }
                }
            }

            if (end)
            {
                currentFunction.end = address + 4;
                currentFunction.is_straight_leaf = is_straight_leaf;
                functions.push_back(currentFunction);
                furthest_branch = 0;
                address += 4;
                looking = false;
                end = false;
                is_straight_leaf = true;
                currentFunction.start = address+4;
            }
        }
        currentFunction.end = address + 4;
        functions.push_back(currentFunction);

        for (std::vector< Function >::iterator iter = functions.begin(); iter != functions.end(); ++iter)
        {
            (*iter).size = ((*iter).end - (*iter).start + 4);
            char temp[256];
            ::sprintf(temp, "z_un_%08x", (*iter).start);
            //Debugger::add_symbol(std::string(temp), (*iter).start, (*iter).end - (*iter).start + 4, ST_FUNCTION);
        }
        hash_functions();
    }

    struct HashMapFunc
    {
        char name[64];
        u32 hash;
        u32 size;
    };

    void store_hash_map(char const *filename)
    {
        FILE *file = ::fopen(filename, "wb");

        u32 n = 0;

        ::fwrite(&n, 4, 1, file);

        for (std::vector< Function >::iterator iter = functions.begin(); iter != functions.end(); ++iter)
        {
            Function &f = *iter;
            if (f.has_hash && f.size >= 12)
            {
                HashMapFunc temp;
                ::memset(&temp, 0, sizeof(temp));
                ::strcpy(temp.name, f.name);
                temp.hash = f.hash;
                temp.size = f.size;
                ::fwrite((char*)&temp, sizeof(temp), 1, file);
                n++;
            }
        }
        ::fseek(file, 0, SEEK_SET);
        ::fwrite(&n, 4, 1, file);
        ::fclose(file);
    }


    void load_hash_map(char const *filename)
    {
        hash_functions();
        update_hash_to_function_map();

        FILE *file = ::fopen(filename, "rb");
        int n;

        ::fread(&n, 4, 1, file);

        for (int i = 0; i < n; i++)
        {
            HashMapFunc temp;
            ::fread(&temp, sizeof(temp), 1, file);
            std::map< u32, Function * >::iterator iter = hash_to_function.find(temp.hash);
            if (iter != hash_to_function.end())
            {
                Function &f = *(iter->second);
                if (f.size == temp.size)
                {
                    ::strcpy(f.name, temp.name);
                    f.hash = temp.hash;
                    f.size = temp.size;
                }
            }
        }

        ::fclose(file);
    }
#endif
}
