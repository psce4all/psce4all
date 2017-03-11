/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hal.os.Module.h"
#include "lle.mmu.h"
#include "lle.cpu(Allegrex).h"
#include "lle.cpu(Allegrex).jitasm.x86-64.h"

HANDLE lle_jitasm$heap = 0;

#include "capstone.h"
namespace capstone
{
    static hal::os::Module module("capstone.dll");

    static auto Open   = (cs_err    (*)(cs_arch arch, cs_mode mode, csh * handle)                                        )module["cs_open"];
    static auto Close  = (cs_err    (*)(csh * handle)                                                                    )module["cs_close"];
    static auto Free   = (void      (*)(cs_insn * insn, size_t count)                                                    )module["cs_free"];
    static auto Malloc = (cs_insn * (*)(csh ud)                                                                          )module["cs_malloc"];
    static auto Disasm = (bool      (*)(csh ud, const uint8_t ** code, size_t * size, uint64_t * address, cs_insn * insn))module["cs_disasm_iter"];

    static char * Disassemble(char * out, cs_insn & insn, bool use_underscore = false)
    {
        char address[32];

        sprintf(address, "0x%08llX(%2d):", insn.address, insn.size);

        char bytes[64], *p = bytes;

        for (size_t i = 0; i < insn.size; ++i)
        {
            p += sprintf(p, "%02zX", size_t(insn.bytes[insn.size - i - 1]));
        }

        char tmp[32];

        char * base = ::strstr(insn.op_str, "[rsi + ");

        tmp[0] = 0;
        if (base)
        {
            size_t reg = (size_t)::strtol(base + 7, NULL, 0) - offsetof(lle::cpu::Context, gpr[0]);
            if ((unsigned)reg < (32 + 32 + 128 + 6) * 4)
            {
                sprintf(tmp, " --- %s", &
                        (
                        "$zr\0    " "$at\0    " "$v0\0    " "$v1\0    "
                        "$a0\0    " "$a1\0    " "$a2\0    " "$a3\0    "
                        "$t0\0    " "$t1\0    " "$t2\0    " "$t3\0    "
                        "$t4\0    " "$t5\0    " "$t6\0    " "$t7\0    "
                        "$s0\0    " "$s1\0    " "$s2\0    " "$s3\0    "
                        "$s4\0    " "$s5\0    " "$s6\0    " "$s7\0    "
                        "$t8\0    " "$t9\0    " "$k0\0    " "$k1\0    "
                        "$gp\0    " "$sp\0    " "$fp\0    " "$ra\0    "

                        "$f0\0    " "$f1\0    " "$f2\0    " "$f3\0    "
                        "$f4\0    " "$f5\0    " "$f6\0    " "$f7\0    "
                        "$f8\0    " "$f9\0    " "$f10\0   " "$f11\0   "
                        "$f12\0   " "$f13\0   " "$f14\0   " "$f15\0   "
                        "$f16\0   " "$f17\0   " "$f18\0   " "$f19\0   "
                        "$f20\0   " "$f21\0   " "$f22\0   " "$f23\0   "
                        "$f24\0   " "$f25\0   " "$f26\0   " "$f27\0   "
                        "$f28\0   " "$f29\0   " "$f30\0   " "$f31\0   "

                        "$s000\0  " "$s001\0  " "$s002\0  " "$s003\0  "
                        "$s010\0  " "$s011\0  " "$s012\0  " "$s013\0  "
                        "$s020\0  " "$s021\0  " "$s022\0  " "$s023\0  "
                        "$s030\0  " "$s031\0  " "$s032\0  " "$s033\0  "

                        "$s100\0  " "$s101\0  " "$s102\0  " "$s103\0  "
                        "$s110\0  " "$s111\0  " "$s112\0  " "$s113\0  "
                        "$s120\0  " "$s121\0  " "$s122\0  " "$s123\0  "
                        "$s130\0  " "$s131\0  " "$s132\0  " "$s133\0  "

                        "$s200\0  " "$s201\0  " "$s202\0  " "$s203\0  "
                        "$s210\0  " "$s211\0  " "$s212\0  " "$s213\0  "
                        "$s220\0  " "$s221\0  " "$s222\0  " "$s223\0  "
                        "$s230\0  " "$s231\0  " "$s232\0  " "$s233\0  "

                        "$s300\0  " "$s301\0  " "$s302\0  " "$s303\0  "
                        "$s310\0  " "$s311\0  " "$s312\0  " "$s313\0  "
                        "$s320\0  " "$s321\0  " "$s322\0  " "$s323\0  "
                        "$s330\0  " "$s331\0  " "$s332\0  " "$s333\0  "

                        "$s400\0  " "$s401\0  " "$s402\0  " "$s403\0  "
                        "$s410\0  " "$s411\0  " "$s412\0  " "$s413\0  "
                        "$s420\0  " "$s421\0  " "$s422\0  " "$s423\0  "
                        "$s430\0  " "$s431\0  " "$s432\0  " "$s433\0  "

                        "$s500\0  " "$s501\0  " "$s502\0  " "$s503\0  "
                        "$s510\0  " "$s511\0  " "$s512\0  " "$s513\0  "
                        "$s520\0  " "$s521\0  " "$s522\0  " "$s523\0  "
                        "$s530\0  " "$s531\0  " "$s532\0  " "$s533\0  "

                        "$s600\0  " "$s601\0  " "$s602\0  " "$s603\0  "
                        "$s610\0  " "$s611\0  " "$s612\0  " "$s613\0  "
                        "$s620\0  " "$s621\0  " "$s622\0  " "$s623\0  "
                        "$s630\0  " "$s631\0  " "$s632\0  " "$s633\0  "

                        "$s700\0  " "$s701\0  " "$s702\0  " "$s703\0  "
                        "$s710\0  " "$s711\0  " "$s712\0  " "$s713\0  "
                        "$s720\0  " "$s721\0  " "$s722\0  " "$s723\0  "
                        "$s730\0  " "$s731\0  " "$s732\0  " "$s733\0  "

                        "$lo\0    " "$hi\0    " "$fcr0\0  " "$fcr31\0 "
                        "$pc\0    " "$npc\0   "


                        )[2 * reg]);
            }
        }

        if (use_underscore)
        {
            static const char u[] = "................................................................";
            sprintf(out, "%s%s%s%s %s%s%s", address, &u[32 + strlen(bytes)], bytes, insn.mnemonic, insn.op_str, tmp[0] ? tmp : "", &u[1 + strlen(insn.mnemonic) + strlen(insn.op_str) + strlen(tmp)]);
        }
        else
        {
            sprintf(out, "%s %32s %-16s %s%s", address, bytes, insn.mnemonic, insn.op_str, tmp[0] ? tmp : "");
        }

        return out;
    }
}

namespace Allegrex
{
    namespace jitasm
    {
        Reg8    Frontend::al = Reg8(AL);
        Reg8    Frontend::cl = Reg8(CL);
        Reg8    Frontend::dl = Reg8(DL);
        Reg8    Frontend::bl = Reg8(BL);
        Reg8    Frontend::ah = Reg8(AH);
        Reg8    Frontend::ch = Reg8(CH);
        Reg8    Frontend::dh = Reg8(DH);
        Reg8    Frontend::bh = Reg8(BH);
        Reg16   Frontend::ax = Reg16(AX);
        Reg16   Frontend::cx = Reg16(CX);
        Reg16   Frontend::dx = Reg16(DX);
        Reg16   Frontend::bx = Reg16(BX);
        Reg16   Frontend::sp = Reg16(SP);
        Reg16   Frontend::bp = Reg16(BP);
        Reg16   Frontend::si = Reg16(SI);
        Reg16   Frontend::di = Reg16(DI);
        Reg32   Frontend::eax = Reg32(EAX);
        Reg32   Frontend::ecx = Reg32(ECX);
        Reg32   Frontend::edx = Reg32(EDX);
        Reg32   Frontend::ebx = Reg32(EBX);
        Reg32   Frontend::esp = Reg32(ESP);
        Reg32   Frontend::ebp = Reg32(EBP);
        Reg32   Frontend::esi = Reg32(ESI);
        Reg32   Frontend::edi = Reg32(EDI);
        FpuReg_st0  Frontend::st0;
        FpuReg  Frontend::st1 = FpuReg(ST1);
        FpuReg  Frontend::st2 = FpuReg(ST2);
        FpuReg  Frontend::st3 = FpuReg(ST3);
        FpuReg  Frontend::st4 = FpuReg(ST4);
        FpuReg  Frontend::st5 = FpuReg(ST5);
        FpuReg  Frontend::st6 = FpuReg(ST6);
        FpuReg  Frontend::st7 = FpuReg(ST7);
        MmxReg  Frontend::mm0 = MmxReg(MM0);
        MmxReg  Frontend::mm1 = MmxReg(MM1);
        MmxReg  Frontend::mm2 = MmxReg(MM2);
        MmxReg  Frontend::mm3 = MmxReg(MM3);
        MmxReg  Frontend::mm4 = MmxReg(MM4);
        MmxReg  Frontend::mm5 = MmxReg(MM5);
        MmxReg  Frontend::mm6 = MmxReg(MM6);
        MmxReg  Frontend::mm7 = MmxReg(MM7);
        XmmReg  Frontend::xmm0 = XmmReg(XMM0);
        XmmReg  Frontend::xmm1 = XmmReg(XMM1);
        XmmReg  Frontend::xmm2 = XmmReg(XMM2);
        XmmReg  Frontend::xmm3 = XmmReg(XMM3);
        XmmReg  Frontend::xmm4 = XmmReg(XMM4);
        XmmReg  Frontend::xmm5 = XmmReg(XMM5);
        XmmReg  Frontend::xmm6 = XmmReg(XMM6);
        XmmReg  Frontend::xmm7 = XmmReg(XMM7);
        YmmReg  Frontend::ymm0 = YmmReg(YMM0);
        YmmReg  Frontend::ymm1 = YmmReg(YMM1);
        YmmReg  Frontend::ymm2 = YmmReg(YMM2);
        YmmReg  Frontend::ymm3 = YmmReg(YMM3);
        YmmReg  Frontend::ymm4 = YmmReg(YMM4);
        YmmReg  Frontend::ymm5 = YmmReg(YMM5);
        YmmReg  Frontend::ymm6 = YmmReg(YMM6);
        YmmReg  Frontend::ymm7 = YmmReg(YMM7);
        Reg8    Frontend::r8b  = Reg8(R8B);
        Reg8    Frontend::r9b  = Reg8(R9B);
        Reg8    Frontend::r10b = Reg8(R10B);
        Reg8    Frontend::r11b = Reg8(R11B);
        Reg8    Frontend::r12b = Reg8(R12B);
        Reg8    Frontend::r13b = Reg8(R13B);
        Reg8    Frontend::r14b = Reg8(R14B);
        Reg8    Frontend::r15b = Reg8(R15B);
        Reg16   Frontend::r8w  = Reg16(R8W);
        Reg16   Frontend::r9w  = Reg16(R9W);
        Reg16   Frontend::r10w = Reg16(R10W);
        Reg16   Frontend::r11w = Reg16(R11W);
        Reg16   Frontend::r12w = Reg16(R12W);
        Reg16   Frontend::r13w = Reg16(R13W);
        Reg16   Frontend::r14w = Reg16(R14W);
        Reg16   Frontend::r15w = Reg16(R15W);
        Reg32   Frontend::r8d  = Reg32(R8D);
        Reg32   Frontend::r9d  = Reg32(R9D);
        Reg32   Frontend::r10d = Reg32(R10D);
        Reg32   Frontend::r11d = Reg32(R11D);
        Reg32   Frontend::r12d = Reg32(R12D);
        Reg32   Frontend::r13d = Reg32(R13D);
        Reg32   Frontend::r14d = Reg32(R14D);
        Reg32   Frontend::r15d = Reg32(R15D);
        Reg64   Frontend::rax = Reg64(RAX);
        Reg64   Frontend::rcx = Reg64(RCX);
        Reg64   Frontend::rdx = Reg64(RDX);
        Reg64   Frontend::rbx = Reg64(RBX);
        Reg64   Frontend::rsp = Reg64(RSP);
        Reg64   Frontend::rbp = Reg64(RBP);
        Reg64   Frontend::rsi = Reg64(RSI);
        Reg64   Frontend::rdi = Reg64(RDI);
        Reg64   Frontend::r8  = Reg64(R8);
        Reg64   Frontend::r9  = Reg64(R9);
        Reg64   Frontend::r10 = Reg64(R10);
        Reg64   Frontend::r11 = Reg64(R11);
        Reg64   Frontend::r12 = Reg64(R12);
        Reg64   Frontend::r13 = Reg64(R13);
        Reg64   Frontend::r14 = Reg64(R14);
        Reg64   Frontend::r15 = Reg64(R15);
        Rip64   Frontend::rip = Rip64();
        XmmReg  Frontend::xmm8  = XmmReg(XMM8);
        XmmReg  Frontend::xmm9  = XmmReg(XMM9);
        XmmReg  Frontend::xmm10 = XmmReg(XMM10);
        XmmReg  Frontend::xmm11 = XmmReg(XMM11);
        XmmReg  Frontend::xmm12 = XmmReg(XMM12);
        XmmReg  Frontend::xmm13 = XmmReg(XMM13);
        XmmReg  Frontend::xmm14 = XmmReg(XMM14);
        XmmReg  Frontend::xmm15 = XmmReg(XMM15);
        YmmReg  Frontend::ymm8  = YmmReg(YMM8);
        YmmReg  Frontend::ymm9  = YmmReg(YMM9);
        YmmReg  Frontend::ymm10 = YmmReg(YMM10);
        YmmReg  Frontend::ymm11 = YmmReg(YMM11);
        YmmReg  Frontend::ymm12 = YmmReg(YMM12);
        YmmReg  Frontend::ymm13 = YmmReg(YMM13);
        YmmReg  Frontend::ymm14 = YmmReg(YMM14);
        YmmReg  Frontend::ymm15 = YmmReg(YMM15);
        Reg64   Frontend::zax = Reg64(RAX);
        Reg64   Frontend::zcx = Reg64(RCX);
        Reg64   Frontend::zdx = Reg64(RDX);
        Reg64   Frontend::zbx = Reg64(RBX);
        Reg64   Frontend::zsp = Reg64(RSP);
        Reg64   Frontend::zbp = Reg64(RBP);
        Reg64   Frontend::zsi = Reg64(RSI);
        Reg64   Frontend::zdi = Reg64(RDI);

        bool compiler::RewriteInstructions(Frontend& f, size_t beg, size_t end)
        {
            using namespace jitasm;
            using namespace jitasm::detail;

            struct Gpr2Reg
            {
                size_t                        regmap;    // associated physical register to a MIPS GPR register
                size_t                        locmin[2]; // read/write minimal location referencing a MIPS GPR register
                size_t                        locmax[2]; // read/write maximal location referencing a MIPS GPR register
                bool                          regmem;    // set if a MIPS GPR register acts as a base or index register in a memory operand
                std::vector< detail::Opd  * > opdmap;    // operand placeholder referencing a MIPS GPR register
                std::vector< size_t >         locmap;    // instruction location referencing a MIPS GPR register
                std::vector< size_t >         nilmap;    // instruction map containing I_ADD to transform into I_NULL

                Gpr2Reg()
                {
                    regmap    = size_t(-1);
                    locmin[0] = size_t(-1);
                    locmin[1] = size_t(-1);
                    locmax[0] = size_t(0);
                    locmax[1] = size_t(0);
                    regmem    = false;
                }
            };

            struct Fpr2Reg
            {
            };

            struct Vpr2Reg
            {
            };

            size_t                     gpr2reg_regset; // allocatable physical register set (bitmap)
            Gpr2Reg                    gpr2reg[32];

            gpr2reg_regset = 0xFF0E; // RCX, RDX, RBX, R8, R9, R10, R11, R12, R13, R14, R15 (RAX may interfere in some cases so we discard it until a solution is found out)

            // Step 1 - Scan all instructions referencing a MIPS GPR register:
            //          - if a physical register is explicitly used, this register is excluded from the free physical register pool
            //          - if a MIPS GPR register acts as a base or index register in a memory operand, set gpr_regmem to true
            //          - if instruction is a "mov" with both operands being the same, it must be counted as optional
            for (size_t loc = beg; loc < end; ++loc)
            {
                auto & instr    = f.instrs_[loc];
                auto   instr_id = instr.id_;

                auto & instr_opd0 = instr.opd_[0];
                auto & instr_opd1 = instr.opd_[1];

                bool reg0 = instr_opd0.IsReg();
                bool reg1 = instr_opd1.IsReg();
                bool mem1 = instr_opd1.IsMem();

                bool allegrex0 = reg0 && instr_opd0.GetReg()  .type == R_TYPE_ALLEGREX_GPR;
                bool allegrex1 = reg1 && instr_opd1.GetReg()  .type == R_TYPE_ALLEGREX_GPR;
                bool allegrex2 = mem1 && instr_opd1.GetBase() .type == R_TYPE_ALLEGREX_GPR;
                bool allegrex3 = mem1 && instr_opd1.GetIndex().type == R_TYPE_ALLEGREX_GPR;

                if (reg0 && instr_opd0.GetReg().type == R_TYPE_GP) gpr2reg_regset &= ~(1ULL<<instr_opd0.GetReg().id);
                if (reg1 && instr_opd1.GetReg().type == R_TYPE_GP) gpr2reg_regset &= ~(1ULL<<instr_opd1.GetReg().id);
                if (mem1)
                {
                    if (instr_opd1.GetBase() .type == R_TYPE_GP) gpr2reg_regset &= ~(1ULL<<instr_opd1.GetBase() .id);
                    if (instr_opd1.GetIndex().type == R_TYPE_GP) gpr2reg_regset &= ~(1ULL<<instr_opd1.GetIndex().id);
                }

                if (instr_id == I_MOV && allegrex1) // if instruction is "mov" (using gen(gpr1) or gen(gpr1, gpr2) or kill(gpr1))
                {
                    if (allegrex0 && instr_opd0.GetReg().id == instr_opd1.GetReg().id) // where both operands are the same MIPS register
                    {
                        unsigned gpr = instr_opd1.GetReg().id;

                        gpr2reg[gpr].locmap.push_back(loc);
                        gpr2reg[gpr].opdmap.push_back(&instr_opd0);

                        gpr2reg[gpr].locmap.push_back(loc);
                        gpr2reg[gpr].opdmap.push_back(&instr_opd1);

                        continue; // don't update the minimal/maximal locations because we want to remove that "mov" by default (aka. optional "mov")
                    }
                }
                else if (instr_id == I_ADD && allegrex1 && instr.opd_[2].IsImm() && !instr.opd_[2].GetImm()) // if instruction is "add X, 0" (using gen(gpr1, gpr2))
                {
                    unsigned gpr = instr_opd1.GetReg().id;

                    // only keep this instruction if gpr1 and gpr2 will be replaced with a coalesced physical register
                    gpr2reg[gpr].nilmap.push_back(loc);
                }

                if (allegrex0) // first operand references a MIPS register
                {
                    bool r = instr_opd0.IsRead();
                    bool w = instr_opd0.IsWrite();

                    unsigned gpr = instr_opd0.GetReg().id;

                    if (r && loc < gpr2reg[gpr].locmin[0]) gpr2reg[gpr].locmin[0] = loc;
                    if (w && loc < gpr2reg[gpr].locmin[1]) gpr2reg[gpr].locmin[1] = loc;
                    if (r && loc > gpr2reg[gpr].locmax[0]) gpr2reg[gpr].locmax[0] = loc;
                    if (w && loc > gpr2reg[gpr].locmax[1]) gpr2reg[gpr].locmax[1] = loc;

                    gpr2reg[gpr].locmap.push_back(loc);
                    gpr2reg[gpr].opdmap.push_back(&instr_opd0);
                }

                if (allegrex1) // second operand references a MIPS register
                {
                    bool r = instr_opd1.IsRead();
                    bool w = instr_opd1.IsWrite();

                    unsigned gpr = instr_opd1.GetReg().id;

                    if (r && loc < gpr2reg[gpr].locmin[0]) gpr2reg[gpr].locmin[0] = loc;
                    if (w && loc < gpr2reg[gpr].locmin[1]) gpr2reg[gpr].locmin[1] = loc;
                    if (r && loc > gpr2reg[gpr].locmax[0]) gpr2reg[gpr].locmax[0] = loc;
                    if (w && loc > gpr2reg[gpr].locmax[1]) gpr2reg[gpr].locmax[1] = loc;

                    gpr2reg[gpr].locmap.push_back(loc);
                    gpr2reg[gpr].opdmap.push_back(&instr_opd1);
                }

                if (allegrex2) // MIPS register acts as a base register in a memory operand
                {
                    unsigned gpr = instr_opd1.GetBase().id;

                    if (loc < gpr2reg[gpr].locmin[0]) gpr2reg[gpr].locmin[0] = loc;
                    if (loc > gpr2reg[gpr].locmax[0]) gpr2reg[gpr].locmax[0] = loc;

                    gpr2reg[gpr].locmap.push_back(loc);
                    gpr2reg[gpr].opdmap.push_back(&instr_opd1);

                    gpr2reg[gpr].regmem = true;
                }

                if (allegrex3) // MIPS register acts as an index register in a memory operand
                {
                    unsigned gpr = instr_opd1.GetIndex().id;

                    if (loc < gpr2reg[gpr].locmin[0]) gpr2reg[gpr].locmin[0] = loc;
                    if (loc > gpr2reg[gpr].locmax[0]) gpr2reg[gpr].locmax[0] = loc;

                    gpr2reg[gpr].locmap.push_back(loc);
                    gpr2reg[gpr].opdmap.push_back(&instr_opd1);

                    gpr2reg[gpr].regmem = true;
                }
            }

            // Step 2 - Do linear scan register allocation
            if (!NO_REGISTER_ALLOCATION)
            {
                // Step 2.1 - Create live interval for each MIPS register
                auto live_interval_map   = std::map< size_t /* startpoint */, std::pair< size_t /* endpoint */, size_t /* register */ > >();
                auto active_interval_map = std::map< size_t /* endpoint */, std::pair< size_t /* startpoint */, size_t /* register */ > >();

                for (int gpr = 0; gpr < 32; ++gpr)
                {
                    auto locmin = std::min(gpr2reg[gpr].locmin[0], gpr2reg[gpr].locmin[1]);
                    auto locmax = std::max(gpr2reg[gpr].locmax[0], gpr2reg[gpr].locmax[1]);
                    if (locmin < locmax || gpr2reg[gpr].regmem) // this MIPS register is used in several places
                    {
                        size_t n = gpr2reg[gpr].locmap.size();

                        // minimal/maximal locations are updated
                        // to find out which one must load/store in the MIPS registers context
                        for (size_t p = 0; p < n; ++p)
                        {
                            auto   loc = gpr2reg[gpr].locmap[p];
                            auto * opd = gpr2reg[gpr].opdmap[p];
                            if (opd->IsRead()  && loc < gpr2reg[gpr].locmin[0]) gpr2reg[gpr].locmin[0] = loc;
                            if (opd->IsWrite() && loc > gpr2reg[gpr].locmax[1]) gpr2reg[gpr].locmax[1] = loc;
                        }

                        // minimal/maximal locations are also updated to all the optional "mov" now
                        // since one of them might load/store in the MIPS registers context
                        locmin = std::min(gpr2reg[gpr].locmin[0], gpr2reg[gpr].locmin[1]);
                        locmax = std::max(gpr2reg[gpr].locmax[0], gpr2reg[gpr].locmax[1]);

                        // create its live interval
                        live_interval_map[locmin] = std::make_pair(locmax, gpr);
                    }
                    else // this MIPS register is referenced only once here
                    {
                        size_t n = gpr2reg[gpr].locmap.size();

                        for (size_t p = 0; p < n; ++p)
                        {
                            auto loc = gpr2reg[gpr].locmap[p];
                            if (loc >= locmin)
                            {
                                if (loc == locmin && !f.instrs_[loc].GetOpd(0).IsImm())
                                {
                                    // create its live interval
                                    live_interval_map[locmin] = std::make_pair(locmax, gpr);
                                }

                                break;
                            }
                        }
                    }
                }

                // Step 2.2 - Allocate/Coalesce physical registers
                for (auto & live_interval : live_interval_map)
                {
                    auto coalesced_gpr = size_t(-1);

                    // Expire old intervals
                    for (auto j = active_interval_map.begin(); j != active_interval_map.end();)
                    {
                        auto & active_interval = *j;

                        if (active_interval.first < live_interval.first)
                        {
                            // free the associated physical register of this MIPS GPR register
                            gpr2reg_regset |= 1ULL << gpr2reg[active_interval.second.second].regmap;
                            active_interval_map.erase(j++);
                        }
                        //else if (active_interval.first == live_interval.first && !gpr2reg[active_interval.second.second].regmem)
                        //{
                        //    // coalesce both MIPS GPR registers into the same physical register provided the later is not used a base/index for a memory operand
                        //    coalesced_reg = active_interval.second.second;
                        //    active_interval_map.erase(j++);
                        //}
                        else
                        {
                            ++j;
                        }
                    }

                    if (coalesced_gpr != size_t(-1)) // if a coalesced physical register is found, use it
                    {
                        gpr2reg[live_interval.second.second].regmap = gpr2reg[coalesced_gpr].regmap;
                        active_interval_map[live_interval.second.first] = std::make_pair(live_interval.first, live_interval.second.second);

                        auto & addmap = gpr2reg[coalesced_gpr].nilmap;
                        auto   range = std::equal_range(addmap.begin(), addmap.end(), live_interval.first);
                        if (range.first != range.second)
                        {
                            // keep this/those I_ADD instruction(s)
                            addmap.erase(range.first, range.second);
                        }
                    }
                    else if (gpr2reg_regset) // else allocate a physical register from the free physical register pool
                    {
                        DWORD index;
                        _BitScanForward((DWORD *)&index, (DWORD)gpr2reg_regset);
                        gpr2reg[live_interval.second.second].regmap = size_t(index);
                        gpr2reg_regset &= size_t(~(1ULL<<index));
                        active_interval_map[live_interval.second.first] = std::make_pair(live_interval.first, live_interval.second.second);
                    }
                    else // we're asking for big trouble :(
                    {
                        //SpillAtInterval(i)
                        //    spill ? last interval in active
                        //    if endpoint[spill] > endpoint[i] then
                        //        register[i] ? register[spill]
                        //        location[spill] ? new stack location
                        //        remove spill from active
                        //        add i to active, sorted by increasing end point
                        //    else
                        //    location[i] ? new stack location
                        // Spill at interval
                        __debugbreak(); // TODO

                        // not enough registers, bail out
                        return false;
                    }
                }
            }

            // Step 3 - Reorder physical registers in decreasing order of weight.
            //          Physical registers R8-R15 generates longer instructions
            //          so we should prefer RAX, RCX, RDX and RBX to them if possible.
            if (1)
            {
                size_t weight[32];
                size_t regmap[32];
                size_t regset = 0;
                for (int reg = 0; reg < 32; ++reg)
                {
                    weight[reg] = reg;
                }
                for (int gpr = 0; gpr < 32; ++gpr)
                {
                    auto size = gpr2reg[gpr].locmap.size(); // usage count
                    auto reg  = gpr2reg[gpr].regmap;
                    regmap[gpr] = reg;
                    if (size && reg != size_t(-1))
                    {
                        weight[reg] += size<<5; // weight for all MIPS GPR registers using that physical register
                        regset |= 1ULL<<reg;
                    }
                }
                std::sort(weight, weight + 32); // order the weight array
                for (int i = 31; i >= 0; --i)
                {
                    auto old = weight[i]; // we need to allocate a physical register in decreasing order of weight
                    if (old & ~31) // usage count of this physical old register
                    {
                        DWORD index;
                        _BitScanForward((DWORD *)&index, (DWORD)regset);
                        regset &= size_t(~(1ULL<<index));
                        old &= 31; // old physical register id
                        for (int gpr = 0; gpr < 32; ++gpr)
                        {
                            if (regmap[gpr] == old)
                            {
                                gpr2reg[gpr].regmap = size_t(index); // set the new physical register for this MIPS register
                            }
                        }
                    }
                }
            }

            // Step 4 - Replace MIPS GPR references by their associated physical registers
            //          or by memory operands to a context through RSI
            for (unsigned int gpr = 0; gpr < 32; ++gpr)
            {
                auto rreg = Reg32(PhysicalRegID(gpr2reg[gpr].regmap));
                auto mreg = f.dword_ptr[f.rsi+s32(4*gpr)];
                if (gpr2reg[gpr].regmap != size_t(-1))
                {
                    auto locmin = std::min(gpr2reg[gpr].locmin[0], gpr2reg[gpr].locmin[1]);
                    auto locmax = std::max(gpr2reg[gpr].locmax[0], gpr2reg[gpr].locmax[1]);

                    if (locmin == locmax)
                    {
                        for (size_t p = 0; p < gpr2reg[gpr].locmap.size(); ++p)
                        {
                            auto   loc = gpr2reg[gpr].locmap[p];
                            auto * opd = gpr2reg[gpr].opdmap[p];
                            bool   r   = opd->IsRead();
                            bool   w   = opd->IsWrite();
                            *opd       = r ? w ? RW(mreg) : R(mreg) : W(mreg);
                            if (loc == locmin)
                            {
                                f.instrs_[loc].opd_[2] = rreg;
                            }
                        }
                    }
                    else
                    {
                        auto opdr = (Opd *)0;
                        auto opdw = (Opd *)0;
                        for (size_t p = 0; p < gpr2reg[gpr].locmap.size(); ++p)
                        {
                            auto * opd = gpr2reg[gpr].opdmap[p];

                            if (opd->IsReg() && opd->GetReg().type == R_TYPE_ALLEGREX_GPR && gpr == opd->GetReg().id)
                            {
                                bool r = opd->IsRead();
                                bool w = opd->IsWrite();
                                *opd = r ? (w ? RW(rreg) : R(rreg)) : W(rreg);
                                if (r) if (!opdr) opdr = opd;
                                if (w) opdw = opd;
                            }

                            if (opd->IsMem())
                            {
                                if (opd->GetBase().type == R_TYPE_ALLEGREX_GPR && gpr == opd->GetBase().id)
                                {
                                    opd->base_.type = R_TYPE_GP;
                                    opd->base_.id = gpr2reg[gpr].regmap;
                                }
                                else if (opd->GetIndex().type == R_TYPE_ALLEGREX_GPR && gpr == opd->GetIndex().id)
                                {
                                    opd->index_.type = R_TYPE_GP;
                                    opd->index_.id = gpr2reg[gpr].regmap;
                                }
                            }
                        }

                        if (opdr && gpr2reg[gpr].locmin[0] <= std::min(gpr2reg[gpr].locmin[1], gpr2reg[gpr].locmax[0]))
                        {
                            *opdr = opdr->IsWrite() ? RW(mreg) : R(mreg);
                        }

                        if (opdw && gpr2reg[gpr].locmin[1] <= gpr2reg[gpr].locmax[1])
                        {
                            *opdw = opdw->IsRead() ? RW(mreg) : W(mreg);
                        }
                    }
                }
                else
                {
                    for (size_t p = 0; p < gpr2reg[gpr].locmap.size(); ++p)
                    {
                        auto * opd = gpr2reg[gpr].opdmap[p];
                        bool   r   = opd->IsRead();
                        bool   w   = opd->IsWrite();
                        *opd       = r ? w ? RW(mreg) : R(mreg) : W(mreg);
                    }
                }
            }

            // Step 5 - Replace "I_ADD, GPR, 0" with "I_NULL"
            for (unsigned int gpr = 0; gpr < 32; ++gpr)
            {
                for (auto loc : gpr2reg[gpr].nilmap)
                {
                    f.instrs_[loc] = Instr(I_NULL, 0, E_SPECIAL);
                }
            }

            return true;
        }

        void compiler::RewriteInstructions(Frontend& f, const ControlFlowGraph& cfg)
        {
            f.indices_.clear();
            f.links_.clear();
            for (auto const block : cfg)
            {
                size_t beg = block->instr_begin;
                size_t end = block->instr_end;
                if (beg < end)
                {
                    if (RewriteInstructions(f, beg, end))
                    {
                        f.indices_.insert(end-1);
                        f.links_[end-1].first  = block->successor[0] ? block->successor[0]->instr_end-1 : size_t(-1);
                        f.links_[end-1].second = block->successor[1] ? block->successor[1]->instr_end-1 : size_t(-1);
                    }
                }
            }
        }

        void compiler::ControlFlowGraph::Build(const Frontend& f)
        {
            initialize(f.instrs_.size());
            size_t block_idx = 0;
            for (size_t instr_idx = 0; instr_idx < f.instrs_.size(); ++instr_idx)
            {
                auto & instr = f.instrs_[instr_idx];
                auto   instr_id = instr.GetID();
                if ((Frontend::IsJump(instr_id) || instr_id == I_RET || instr_id == I_IRET || instr_id == I_CALL) && !(instr.encoding_flag_ & E_NO_BREAK))
                {
                    BlockList::iterator next_block = get_block(instr_idx);
                    block_idx = static_cast<size_t>(std::distance(blocks_.begin(), next_block));
                    BasicBlock * bb = *next_block;

                    // Jump instruction always terminate basic block
                    if (instr_idx + 1 < bb->instr_end)
                    {
                        // Split basic block
                        split(blocks_.begin() + block_idx, instr_idx + 1);
                    }

                    // Set successors of current block
                    if (instr_id == I_RET || instr_id == I_IRET)
                    {
                        if (bb->successor[0])
                            bb->successor[0]->RemovePredecessor(bb);
                        bb->successor[0] = NULL;
                        //bb->successor[0] = *get_exit_block();
                        //(*get_exit_block())->predecessor.push_back(bb);
                    }
                    else if (instr_id != I_CALL)
                    {
                        const size_t jump_to = f.GetJumpTo(instr);  // jump target instruction index
                        BasicBlock * target_bb = *split(get_block(jump_to), jump_to);

                        // Update cur_block if split cur_block
                        if (target_bb->instr_begin <= instr_idx && instr_idx < target_bb->instr_end)
                        {
                            bb = target_bb;
                        }

                        if (instr_id == I_JMP && !(instr.encoding_flag_ & E_SPECIAL))
                        {
                            if (bb->successor[0])
                            {
                                bb->successor[0]->RemovePredecessor(bb);
                            }
                            bb->successor[0] = target_bb;
                            target_bb->predecessor.push_back(bb);
                        }
                        else
                        {
                            if (bb->successor[1])
                            {
                                bb->successor[1]->RemovePredecessor(bb);
                            }
                            bb->successor[1] = target_bb;
                            target_bb->predecessor.push_back(bb);
                        }
                    }
                    else if (instr.encoding_flag_ & E_SPECIAL)
                    {
                        if (bb->successor[0])
                        {
                            bb->successor[0]->RemovePredecessor(bb);
                            bb->successor[0] = NULL;
                        }
                    }
                }
            }

            // Make depth first ordered list
            MakeDepthFirstBlocks(*get_block(0));

            // Numbering depth
            for (size_t i = 0; i < depth_first_blocks_.size(); ++i)
            {
                depth_first_blocks_[i]->depth = i;
            }

            // Detect loops
            DetectLoops();
        }

        void compiler::Compile(Frontend& f)
        {
            // Available registers : rax, rcx, rdx, rsi, rdi, r8 ~ r15, mm0 ~ mm7, xmm0/ymm0 ~ xmm15/ymm15
            //const uint32 available_reg[3] = { 0xFFC7, 0xFF, 0xFFFF };

            // Win64 preserved registers : rbx, rsi, rdi, r12 ~ r15, xmm6 ~ xmm15
            //uint32 preserved_reg[3] = { (1<<RBX)|(1<<RSI)|(1<<RDI)|(1<<R12)|(1<<R13)|(1<<R14)|(1<<R15), 0, 0xFFC0 };

            ControlFlowGraph cfg;

            cfg.Build(f);

#ifdef JITASM_DEBUG_DUMP
            cfg.DumpDot();
#endif

            RewriteInstructions(f, cfg);
        }

        void Frontend::ResolveJumpAndRIP()
        {
            // Replace label indexes with instruction numbers.
            for (InstrList::iterator it = instrs_.begin(); it != instrs_.end(); ++it)
            {
                Instr& instr = *it;
                if (IsJump(instr.GetID()))
                {
                    size_t target = GetJumpTo(instr);
                    instr.GetOpd(1) = Imm64(target);    // Opd(1) = instruction number
                    instr.GetOpd(0) = Imm8(0x7F);       // Opd(0) = max value in sint8
                }
                else if (HasRIP(instr.GetOpd(1)))
                {
                    size_t label_id = (size_t)instr.GetOpd(1).GetDisp();
                    JITASM_ASSERT(labels_[label_id].instr_number != (size_t)-1);    // invalid label
                    instr.GetOpd(1).disp_ = sint64(labels_[label_id].instr_number); // Opd(1) = instruction number
                }
            }

            // Resolve operand sizes.
            std::vector<int> offsets;
            offsets.reserve(instrs_.size() + 1);
            bool retry;
            do
            {
                offsets.clear();
                offsets.push_back(0);
                Backend pre;
                for (InstrList::const_iterator it = instrs_.begin(); it != instrs_.end(); ++it)
                {
                    pre.Assemble(*it);
                    offsets.push_back((int)pre.GetSize());
                }

                retry = false;
                for (size_t i = 0; i < instrs_.size(); i++)
                {
                    Instr& instr = instrs_[i];
                    if (IsJump(instr.GetID()))
                    {
                        size_t d = (size_t)instr.GetOpd(1).GetImm();
                        int rel = (int)offsets[d] - offsets[i + 1];
                        if ((instr.GetID() == I_JMP || instr.GetID() == I_JCC) && !rel)
                        {
                            instr = Instr(I_NULL, 0, 0);
                            retry = true;
                            break;
                        }
                        OpdSize size = instr.GetOpd(0).GetSize();
                        if (size == O_SIZE_8)
                        {
                            if (!detail::IsInt8(rel))
                            {
                                // Retry with immediate 32
                                instr.GetOpd(0) = Imm32(0x7FFFFFFF);

                                retry = true;
                                break;
                            }
                        }
                        if (size_t(d-1) < instrs_.size())
                        {
                            auto & target = instrs_[d-1];
                            if (target.GetID() == I_ALIGN && target.GetOpd(0).GetImm() == 0)
                            {
                                target.GetOpd(0) = Imm8(4);
                                retry = true;
                                break;
                            }
                        }
                    }
                }
            }
            while (retry);

            // Resolve immediates
            for (size_t i = 0; i < instrs_.size(); i++)
            {
                Instr& instr = instrs_[i];
                if (IsJump(instr.GetID()))
                {
                    size_t d = (size_t)instr.GetOpd(1).GetImm();
                    int rel = (int)offsets[d] - offsets[i + 1];
                    OpdSize size = instr.GetOpd(0).GetSize();
                    if (size == O_SIZE_8)
                    {
                        JITASM_ASSERT(detail::IsInt8(rel));
                        instr.GetOpd(0) = Imm8((uint8)rel);
                    }
                    else if (size == O_SIZE_32)
                    {
                        JITASM_ASSERT(detail::IsInt32(rel));
                        instr.GetOpd(0) = Imm32((uint32)rel);
                        instr.GetOpd(1) = detail::Opd();
                    }
                }
                else if (HasRIP(instr.GetOpd(1)))
                {
                    size_t d = (size_t)instr.GetOpd(1).GetDisp();
                    int rel = (int)offsets[d] - offsets[i + 1];
                    JITASM_ASSERT(detail::IsInt32(rel));
                    instr.GetOpd(1).disp_ = sint64(rel);
                }
            }
        }

        struct CfgDumper
        {
            struct DataRef
            {
                uint64_t             addr;
                size_t               size;
                std::set< uint64_t > refs;
            };

            CfgDumper(Frontend & frontend, u32 code, u32 size) : frontend(frontend), err(CS_ERR_HANDLE), cfgout(0), previous_node(0)
            {
                forcef(cpu, "+--- Super Block 0x%08X - %d bytes", code, size);

                if (capstone::Open)
                {
                    err = capstone::Open(CS_ARCH_X86, CS_MODE_64, &handle);

                    if (CS_ERR_OK == err)
                    {
                        char tmp[1024];
                        _snprintf(tmp, 1024, "cfg\\sb_0x%08X.gv", code);
                        cfgout = fopen(tmp, "wt");

                        if (cfgout)
                        {
                            fprintf(
                                cfgout,
                                "digraph CFG\n"
                                "{\n"
                                "    concentrate = true;\n"
                                "    fontname = Courier;\n"
                                "    fontsize = 10;\n"
                                "    splines = true;\n"
                                "    overlap = false;\n"
                                "    node[shape = Mrecord, margin = 0, fontname = Consolas, fontsize = 9];\n"
                                "    edge[fontname = Consolas, fontsize = 8];\n"
                                "    subgraph cluster_sb\n"
                                "    {\n"
                                "        style = dotted;\n"
                                "        label = \"Super Block 0x%08X - %d bytes\";\n"
                                "        style = dotted;\n"
                                "        label = \"\";\n"
                                "        subgraph \"Node 0\"\n"
                                "        {\n"
                                "            style = invis;\n"
                                "            label = \"Node 0\";\n"
                                "            node_0[label = \"START\", shape = diamond, fontsize = 12];\n"
                                "        }\n"
                                ,
                                code,
                                size);
                        }
                    }
                }
            }

            ~CfgDumper()
            {
                if (capstone::Close)
                {
                    if (cfgout)
                    {
                        bool started = false;
                        for (auto & link : frontend.links_)
                        {
                            bool link1 = link.second.first != size_t(-1) && frontend.indices_.end() != frontend.indices_.find(link.second.first);
                            bool link2 = link.second.second != size_t(-1) && frontend.indices_.end() != frontend.indices_.find(link.second.second) && link.second.first != link.second.second;
                            if (link1)
                            {
                                if (!started)
                                {
                                    fprintf(
                                        cfgout,
                                        "        \"Node 0\":s -> \"Node %zd\":n [style = bold]\n",
                                        link.first);
                                    started = true;
                                }

                                if (link2)
                                {
                                    fprintf(
                                        cfgout,
                                        "        \"Node %zd\":s -> \"Node %zd\":n\n",
                                        link.first,
                                        link.second.first);
                                }
                                else
                                {
                                    fprintf(
                                        cfgout,
                                        "        \"Node %zd\":s -> \"Node %zd\":n [style = bold]\n",
                                        link.first,
                                        link.second.first);
                                }
                            }
                            if (link2)
                            {
                                fprintf(
                                    cfgout,
                                    "        \"Node %zd\":se -> \"Node %zd\":ne [style = dashed]\n",
                                    link.first,
                                    link.second.second);
                            }
                        }

                        fprintf(
                            cfgout,
                            "    }\n"
                            "}\n");

                        fclose(cfgout);
                    }

                    if (CS_ERR_OK == err)
                    {
                        capstone::Close(&handle);
                    }
                }
            }

            void DumpNode(u32 node, u32 code, u32 size, Backend & backend)
            {
                if (capstone::Disasm)
                {
                    if (CS_ERR_OK == err)
                    {
                        char      out[256];

                        if (size)
                        {
                            forcef(cpu, "| +--- Basic Block 0x%08X - %d bytes", code, size);

                            if (cfgout)
                            {
                                fprintf(
                                    cfgout,
                                    "        subgraph \"Node %d\"\n"
                                    "        {\n"
                                    "            style = invis;\n"
                                    "            label = \"Node %d\";\n"
                                    "            node_%d[label=<<TABLE border=\"0\" cellborder=\"0\" cellspacing=\"4\">\n"
                                    "                              <TR><TD colspan=\"3\">Basic Block 0x%08X - %d bytes</TD></TR><HR/>\n",
                                    node,
                                    node,
                                    node,
                                    code,
                                    size);
                            }

                            auto insn = (cs_insn *)capstone::Malloc(handle);
                            auto address = (u8 const *)code;
                            auto left = size_t(size);
                            auto offset = u64(code);

                            while (left)
                            {
                                auto previous_size = left;

                                auto i = datarefs.find(u64(offset));
                                if (i != datarefs.end())
                                {
                                    auto & dataref = i->second;
                                    switch (dataref.size)
                                    {
                                    case 4:
                                        insn->address = offset;
                                        insn->size = 4;
                                        memcpy(insn->bytes, address, 4);
                                        strcpy(insn->mnemonic, ".dword");
                                        sprintf(insn->op_str, "0x%04X", *((u32 *)(insn->bytes)));
                                        address += 4;
                                        left -= 4;
                                        offset += 4;
                                        break;
                                    case 8:
                                        insn->address = offset;
                                        insn->size = 8;
                                        memcpy(insn->bytes, address, 8);
                                        strcpy(insn->mnemonic, ".qword");
                                        sprintf(insn->op_str, "0x%08I64X", *((u64 *)(insn->bytes)));
                                        address += 8;
                                        left -= 8;
                                        offset += 8;
                                        break;
                                    }

                                    if (previous_size < left) // bail out
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    if (!capstone::Disasm(handle, &address, &left, &offset, insn))
                                    {
                                        insn->address = offset;
                                        insn->size = 1;
                                        strcpy(insn->mnemonic, ".byte");
                                        sprintf(insn->op_str, "0x%02X", u32(insn->bytes[0]));
                                        address += 1;
                                        left -= 1;
                                        offset += 1;
                                    }

                                    if (previous_size < left) // bail out
                                    {
                                        break;
                                    }

                                    switch (insn->id)
                                    {
                                    case X86_INS_CALL:
                                        if (*((unsigned short *)insn->bytes) == 0x15FF)
                                        {
                                            uint64_t target = uint64_t(insn->address + int64_t(insn->size) + int64_t(*((u32 *)(insn->bytes + 2))));
                                            DataRef & dataref = datarefs[target];
                                            dataref.addr = target;
                                            dataref.size = sizeof(uintptr_t);
                                            dataref.refs.insert(insn->address);
                                        }
                                        break;
                                    case X86_INS_LEA:
                                        {
                                            //size_t ofs = insn->bytes[0] == 0x48 ? 1 : 0;
                                            //if ((*((unsigned short *)(insn->bytes + ofs)) & 0x07FF) == 0x058D)
                                            //{
                                            //    uint64_t target = uint64_t(insn->address + int64_t(insn->size) + int64_t(*((u32 *)(insn->bytes + 2 + ofs))));
                                            //    DataRef & dataref = datarefs[target];
                                            //    dataref.addr = target;
                                            //    dataref.size = 4 * (1 + ofs);
                                            //    dataref.refs.insert(insn->address);
                                            //    break;
                                            //}
                                        }
                                    default:
                                        break;
                                    }
                                }

                                for (auto source : backend.GetSources(insn->address - size_t(backend.pbuff_)))
                                {
                                    char line[1024];

                                    lle::cpu::Disassemble(source, *p32u32(source), line);
                                    forcef(cpu, "| +--- Source: 0x%08X [ %s ]", source, line);

                                    if (cfgout)
                                    {
                                        fprintf(
                                            cfgout,
                                            "                              <TR><TD colspan=\"3\" bgcolor=\"#EEEEEE\">Source: 0x%08X [ %s ]</TD></TR><HR/>\n",
                                            source,
                                            line);
                                    }
                                }

                                forcef(cpu, "| | %s", capstone::Disassemble(out, *insn, false));

                                if (cfgout)
                                {
                                    capstone::Disassemble(out, *insn, true);

                                    std::string line(out);

                                    fprintf(
                                        cfgout,
                                        "                              <TR><TD align=\"left\" >%s</TD><VR/>\n"
                                        "                                  <TD align=\"right\">%s</TD><VR/>\n"
                                        "                                  <TD align=\"left\" >%s</TD></TR><HR/>\n",
                                        line.substr(0, 14).c_str(),
                                        line.substr(15, 32).c_str(),
                                        line.substr(47, 64).c_str());
                                }
                            }
                            capstone::Free(insn, 1);

                            if (cfgout)
                            {
                                fprintf(
                                    cfgout,
                                    "                              <TR><TD colspan=\"3\">Node %d</TD></TR></TABLE>>];\n"
                                    "        }\n"
                                    "        node_%zd -> \"Node %d\" [style = invis]\n"
                                    "        node_%zd:s -> node_%d:n [style = invis]\n"
                                    ,
                                    node,
                                    previous_node,
                                    node,
                                    previous_node,
                                    node);

                                previous_node = node;
                            }
                        }
                    }
                }
            }

            Frontend       & frontend;
            FILE           * cfgout;
            FILE           * binout;
            csh              handle;
            cs_err           err;
            size_t           previous_node;

            std::map< uint64_t, DataRef > datarefs;

        private:
            CfgDumper & operator=(CfgDumper const &);
        };

        struct DebugAllegrexInstruction
        {
            DebugAllegrexInstruction(Frontend & frontend) : frontend(frontend)
            {
            }

            ~DebugAllegrexInstruction()
            {
            }

            static void SetDebugAllegrexInstruction(DWORD dwAddr, BOOL bDelaySlot, UINT_PTR qwAddr, UINT_PTR qwSize)
            {
                ULONG_PTR info[4] = { dwAddr, ULONG_PTR(bDelaySlot), qwAddr, qwSize };

                __try
                {
                    RaiseException(0x414CA449, 0, 4, (ULONG_PTR*)&info);
                }
                __except (EXCEPTION_EXECUTE_HANDLER)
                {
                }
            }

            void Set(u32 code, u32 size, Backend & backend, u32 & previous_base)
            {
                if (size)
                {
                    auto offset = size_t((u8 const *)code - backend.pbuff_);
                    auto length = size_t(size);
                    auto base = u32(0);
                    auto lower = size_t(-1);
                    auto upper = size_t(+0);
                    for (auto source : backend.GetSourcesInRange(offset, length))
                    {
                        for (auto address : source.second.second)
                        {
                            base = address;
                            if (lower > source.first)
                            {
                                lower = source.first;
                            }
                            if (upper < source.first + source.second.first)
                            {
                                upper = source.first + source.second.first;
                            }
                            if (base)
                            {
                                SetDebugAllegrexInstruction(base, false, lower, upper - lower);
                            }
                        }
                    }
                    if (!base)
                    {
                        base = previous_base;
                    }
                    else
                    {
                        previous_base = base;
                    }
                    if (base)
                    {
                        SetDebugAllegrexInstruction(base, false, lower, upper - lower);
                    }
                }
            }

            Frontend & frontend;

        private:
            DebugAllegrexInstruction & operator=(DebugAllegrexInstruction const &);
        };

        void Frontend::Assemble()
        {
            detail::ScopedLock<detail::SpinLock> lock(codelock_);
            if (assembled_) return;

            instrs_.clear();
            labels_.clear();
            instrs_.reserve(128);

            InternalMain();

            compiler::Compile(*this);

            // Resolve jump and RIP-relative instructions
            if (!labels_.empty())
            {
                ResolveJumpAndRIP();
            }

            // Count total size of machine code
            Backend pre;
            for (InstrList::const_iterator it = instrs_.begin(); it != instrs_.end(); ++it)
            {
                pre.Assemble(*it);
            }
            size_t codesize = pre.GetSize();

            // Write machine code to the buffer
            codebuff_.Reset(codesize);
            Backend backend(codebuff_.GetPointer(), codebuff_.GetBufferSize());

            auto buffer_code = (char *)codebuff_.GetPointer();
            auto buffer_size = (size_t)0;

            if (JITASM_TRACE_CFG)
            {
                CfgDumper cfgout(*this, u32(codebuff_.GetPointer()), u32(codebuff_.GetCodeSize()));

                for (size_t i = 0; i < instrs_.size(); ++i)
                {
                    backend.Assemble(instrs_[i]);

                    if (indices_.end() != indices_.find(i))
                    {
                        auto code = buffer_code;
                        auto size = backend.GetSize() - buffer_size;

                        for (auto pc : backend.GetSources(buffer_size))
                        {
                            *(p32icache< u32 >(pc)) = u32(code);
                        }

                        buffer_code += size;
                        buffer_size = backend.GetSize();

                        cfgout.DumpNode(u32(i), u32(code), u32(size), backend);
                    }
                }
            }
            else
            {
                auto base = u32();

                for (size_t i = 0; i < instrs_.size(); ++i)
                {
                    DebugAllegrexInstruction dbginsn(*this);

                    backend.Assemble(instrs_[i]);

                    if (indices_.end() != indices_.find(i))
                    {
                        auto code = buffer_code;
                        auto size = backend.GetSize() - buffer_size;

                        for (auto pc : backend.GetSources(buffer_size))
                        {
                            *(p32icache< u32 >(pc)) = u32(buffer_code);
                        }

                        buffer_code += size;
                        buffer_size = backend.GetSize();

                        if (Allegrex::use_debug_server)
                        {
                            dbginsn.Set(u32(code), u32(size), backend, base);
                        }
                    }
                }
            }

#if 0
            char tmp[1024];
            _snprintf(tmp, 1024, "cfg\\sb_0x%08X.bin", u32(codebuff_.GetPointer()));
            FILE * binout = fopen(tmp, "wb");
            if (binout)
            {
                u8 const * code = (u8 const *)codebuff_.GetPointer();
                size_t     size = codebuff_.GetCodeSize();
                for (size_t k = 0; k < size; ++k)
                    fputc(code[k], binout);
                fclose(binout);
            }
#endif
            InstrList().swap(instrs_);
            LabelList().swap(labels_);
            assembled_ = true;
        }
    }   // namespace jitasm
}
