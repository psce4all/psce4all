////////////////////////////////////////////////////////////////////////////////
/// This file is auto-generated from pspe4all-nidgen version 0.3
///
#include "hle.syscalls.Modules.h"
#include "lle.mmu.h"

char const * Allegrex::Instruction::GetSyscallName(u32 opcode) const
{
    hle::Function * function = hle::syscalls::GetModuleFunction(opcode);
    if (function)
    {
        return function->name;
    }

    return "";
}
