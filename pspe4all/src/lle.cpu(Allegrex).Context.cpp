/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "lle.mmu.h"
#include "lle.cpu(Allegrex).h"

#define LOG_INTERPRETER_WITH_DISASSEMBLY 0

namespace Allegrex
{
    Context::Context()
    {
        Reset();
    }

#if LOG_INTERPRETER_WITH_DISASSEMBLY
    void Context::Interpret()
    {
        static char line[4096];

        if (!InterpretAutogeneratedCode())
        {
            u32 address = pc;
            u32 opcode = FetchOpcode();
            Allegrex::Disassemble(address, opcode, line);
            tracef(cpu, "%08X --- %40s --- %s", address, line, ""/*theKernelScheduler->GetCurrentThread()->GetName()*/);
            Allegrex::FastInterpret(*this, opcode);
        }
    }

    void Context::InterpretDelayslot()
    {
        static char line[4096];

        u32 address = pc;
        u32 opcode = FetchDelayslotOpcode();
        Allegrex::Disassemble(address, opcode, line);
        tracef(cpu, "%08X -*- %40s --- %s", address, line, ""/*theKernelScheduler->GetCurrentThread()->GetName()*/);
        Allegrex::FastInterpret(*this, opcode);

        NextPC();

        Step();
    }
#else
    void Context::Interpret()
    {
        if (!InterpretAutogeneratedCode())
        {
            u32 opcode = FetchOpcode();
            Allegrex::FastInterpret(*this, opcode);
        }
    }

    void Context::InterpretDelayslot()
    {
        u32 opcode = FetchDelayslotOpcode();

        Allegrex::FastInterpret(*this, opcode);

        NextPC();

        Step();
    }
#endif

    void Context::Reset()
    {
        reset_gpr();
        reset_fpr();
        reset_vpr();
        reset_mdr();
        reset_fcr();
        reset_vcr();
        reset_bcr();
        reset_c0r();
    }

    void Context::Step()
    {
#if 0
        static s64 delta = 100 * os_Clock::GetElpasedTimeStampPerMicrosecond();
        static u64 old   = os_Clock::GetTimeStamp();

        u64 tsc = old;
        if (os_Clock::GetElpasedTimeStamp(tsc) > delta)
        {
            theSysClock->Step();

            old = tsc;
        }
#endif
    }

    struct SortPerCategoryAndName
    {
        bool operator ()(Instruction * x, Instruction * y)
        {
            u64 x_infos = x->Infos();
            u64 y_infos = y->Infos();

            int x_cat = int(!!(x_infos & Allegrex::IS_FPU)) | int(!!(x_infos & Allegrex::IS_VFPU) << 1);
            int y_cat = int(!!(y_infos & Allegrex::IS_FPU)) | int(!!(y_infos & Allegrex::IS_VFPU) << 1);

            return (x_cat < y_cat) || ((x_cat == y_cat) && ::strcmp(x->OpcodeName(), y->OpcodeName()) < 0);
        }
    };

    void Context::CountInstructions()
    {
        std::vector< Instruction * > insn;
        for (Instruction ** i = Allegrex::instruction_array; ; ++i)
        {
            if (*i)
            {
                insn.push_back(*i);
            }
            else
            {
                std::stable_sort(insn.begin(), insn.end(), SortPerCategoryAndName());
                break;
            }
        }
        for (size_t i = 0; i < insn.size(); ++i)
        {
            if (0 != insn[i]->GetCount())
            {
                tracef(cpu, "%-16s = %d", insn[i]->OpcodeName(), insn[i]->GetCount());
            }
        }
    }
}
