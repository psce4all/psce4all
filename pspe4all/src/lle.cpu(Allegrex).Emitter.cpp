/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "lle.cpu(Allegrex).h"

/* SLL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SLL(u32 address, u32 opcode, bool delayslot)
{
    auto RD  =    Allegrex::Instruction::rd(opcode);
    auto RT  =    Allegrex::Instruction::rt(opcode);
    auto SA  = u8(Allegrex::Instruction::sa(opcode));

    auto $rd = Gpr(RD);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RT)
        {
            gen($rd, $rt);
            if (SA) shl($rd, SA);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* SRL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SRL(u32 address, u32 opcode, bool delayslot)
{
    auto RD  =    Allegrex::Instruction::rd(opcode);
    auto RT  =    Allegrex::Instruction::rt(opcode);
    auto SA  = u8(Allegrex::Instruction::sa(opcode));

    auto $rd = Gpr(RD);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RT)
        {
            gen($rd, $rt);
            if (SA) shr($rd, SA);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* SRA */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SRA(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);
    auto SA = u8(Allegrex::Instruction::sa(opcode));

    auto $rd = Gpr(RD);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RT)
        {
            gen($rd, $rt);
            if (SA) sar($rd, SA);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* SLLV */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SLLV(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);

    auto $rd = Gpr(RD);
    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);

    if (RD)
    {
        if (RT)
        {
            if (RS) mov(ecx, $rs);
            gen($rd, $rt);
            if (RS) shl($rd, cl);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* SRLV */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SRLV(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);

    auto $rd = Gpr(RD);
    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);

    if (RD)
    {
        if (RT)
        {
            if (RS) mov(ecx, $rs);
            gen($rd, $rt);
            if (RS) shr($rd, cl);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* SRAV */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SRAV(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SRAV"); found = true; return address + 4;
}

/* JR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$JR(u32 address, u32 opcode, bool delayslot)
{
    auto RS  = Allegrex::Instruction::rs(opcode);

    auto $rs = Gpr(RS);

    gen($rs);
    mov(ebp, $rs); // using edx instead of ebp is dangerous as the delay slot may use it implicitly

    EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

    if (ICACHE_MEMORY_ADDRESS) mov(edx, ICACHE_MEMORY_ADDRESS);
    if (ICACHE_MEMORY_ADDRESS) add(rdx, rbp); // it is important to keep the translated address into rdx because the next jump may need it to recompile
    else                       mov(edx, ebp);
    mov(ebp, dword_ptr[rdx]);
    jmp(rbp);

    return 0;
}

/* JALR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$JALR(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);

    gen($rs);
    mov(ebp, $rs); // using edx instead of ebp is dangerous as the delay slot may use it implicitly

    EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

    mov($rd, u32(address + 8));
    kill($rd);

    if (ICACHE_MEMORY_ADDRESS) mov(edx, ICACHE_MEMORY_ADDRESS);
    if (ICACHE_MEMORY_ADDRESS) add(rdx, rbp); // it is important to keep the translated address into rdx because the next jump may need it to recompile
    else                       mov(edx, ebp);
    mov(ebp, dword_ptr[rdx]);
    jmp(rbp);

    return INTERPRETER_LIKE ? 0 : address + 8;
}

/* MOVZ */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MOVZ(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RT)
        {
            gen($rt);
            mov(eax, $rd);
            gen($rs);
            cmp($rt, 0);
            cmovz(eax, $rs);
            mov($rd, eax);
            kill($rd);
        }
    }

    return address + 4;
}

/* MOVN */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MOVN(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RT)
        {
            gen($rt);
            mov(eax, $rd);
            gen($rs);
            cmp($rt, 0);
            cmovnz(eax, $rs);
            mov($rd, eax);
            kill($rd);
        }
    }

    return address + 4;
}

/* SYSCALL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SYSCALL(u32 address, u32 opcode, bool delayslot)
{
    auto IMM = Allegrex::Instruction::uimm20(opcode);

    mov(edx, IMM);
    call(qword_ptr[rdi + s32(offsetof(SharedContext::Data, syscall_address))]);

    target_address_next.insert(address + 4);

    return address + 4;
}

/* BREAK */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BREAK(u32 address, u32 opcode, bool delayslot)
{
    (void)opcode;
    int3();
    return address + 4;
}

/* SYNC */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SYNC(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SYNC"); found = true; return address + 4;
}

/* MFHI */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MFHI(u32 address, u32 opcode, bool delayslot)
{
    auto RD  = Allegrex::Instruction::rd(opcode);

    auto $hi = hi_w;
    auto $rd = Gpr(RD);

    if (RD)
    {
        mov($rd, $hi);
        kill($rd);
    }

    return address + 4;
}

/* MTHI */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MTHI(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MTHI"); found = true; return address + 4;
}

/* MFLO */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MFLO(u32 address, u32 opcode, bool delayslot)
{
    auto RD  = Allegrex::Instruction::rd(opcode);

    auto $lo = lo_w;
    auto $rd = Gpr(RD);

    if (RD)
    {
        mov($rd, $lo);
        kill($rd);
    }

    return address + 4;
}

/* MTLO */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MTLO(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MTLO"); found = true; return address + 4;
}

/* CLZ */
__noinline u32 Allegrex::ICache::CodeBlock::emit$CLZ(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);

    if (RD)
    {
        if (RS)
        {
            gen($rd);
            gen($rs);
            mov(eax, 32 + 31);
            bsr($rd, $rs);
            cmovz($rd, eax);
            xor($rd, 31);
            kill($rd);
        }
        else
        {
            mov($rd, 32);
            kill($rd);
        }
    }

    return address + 4;
}

/* CLO */
__noinline u32 Allegrex::ICache::CodeBlock::emit$CLO(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$CLO"); found = true; return address + 4;
}

/* MULT */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MULT(u32 address, u32 opcode, bool delayslot)
{
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $lo = lo_w;
    auto $hi = hi_w;
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RS)
    {
        if (RT)
        {
            gen($rs);
            gen($rt);
            mov(eax, $rs);
            mov(edx, edx);
            imul($rt);
            mov($lo, eax);
            mov($hi, edx);
        }
    }

    return address + 4;
}

/* MULTU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MULTU(u32 address, u32 opcode, bool delayslot)
{
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $lo = lo_w;
    auto $hi = hi_w;
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RS)
    {
        if (RT)
        {
            gen($rs);
            gen($rt);
            mov(eax, $rs);
            mov(edx, edx);
            mul($rt);
            mov($lo, eax);
            mov($hi, edx);
        }
    }

    return address + 4;
}

/* DIV */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DIV(u32 address, u32 opcode, bool delayslot)
{
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $lo = lo_w;
    auto $hi = hi_w;
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RS)
    {
        if (RT)
        {
            gen($rs);
            gen($rt);
            mov(eax, $rs);
            mov(edx, edx);
            cdq();
            idiv($rt);
            mov($lo, eax);
            mov($hi, edx);
        }
    }

    return address + 4;
}

/* DIVU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DIVU(u32 address, u32 opcode, bool delayslot)
{
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);

    auto $lo = lo_w;
    auto $hi = hi_w;
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RS)
    {
        if (RT)
        {
            gen($rs);
            gen($rt);
            mov(eax, $rs);
            xor(edx, edx);
            div($rt);
            mov($lo, eax);
            mov($hi, edx);
        }
    }

    return address + 4;
}

/* MADD */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MADD(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MADD"); found = true; return address + 4;
}

/* MADDU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MADDU(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MADDU"); found = true; return address + 4;
}

/* ADD */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ADD(u32 address, u32 opcode, bool delayslot)
{
    return emit$ADDU(address, opcode, delayslot);
}

/* ADDU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ADDU(u32 address, u32 opcode, bool delayslot)
{
    auto RD  = Allegrex::Instruction::rd(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RT)
        {
            if (RS)
            {
                auto $ra = RD == RT ? $rt : $rs;
                auto $rb = RD == RT ? $rs : $rt;

                gen($rd, $ra);
                gen($rb);
                add($rd, $rb);
                kill($rd);
            }
            else
            {
                gen($rd, $rt);
                kill($rd);
            }
        }
        else if (RS)
        {
            gen($rd, $rs);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* SUB */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SUB(u32 address, u32 opcode, bool delayslot)
{
    return emit$SUBU(address, opcode, delayslot);
}

/* SUBU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SUBU(u32 address, u32 opcode, bool delayslot)
{
    auto RD  = Allegrex::Instruction::rd(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RT)
        {
            if (RS)
            {
                auto $ra = RD == RT ? $rt : $rs;
                auto $rb = RD == RT ? $rs : $rt;

                gen($rd, $ra);
                gen($rb);
                sub($rd, $rb);
                if (RD == RT) neg($rd);
                kill($rd);
            }
            else
            {
                gen($rd, $rt);
                neg($rd);
                kill($rd);
            }
        }
        else if (RS)
        {
            gen($rd, $rs);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* AND */
__noinline u32 Allegrex::ICache::CodeBlock::emit$AND(u32 address, u32 opcode, bool delayslot)
{
    auto RD  = Allegrex::Instruction::rd(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RS)
        {
            if (RT)
            {
                auto $ra = RD == RT ? $rt : $rs;
                auto $rb = RD == RT ? $rs : $rt;

                gen($rd, $ra);
                if (RS != RT) gen($rb);
                if (RS != RT) and($rd, $rb);
                kill($rd);
            }
            else
            {
                mov($rd, 0);
                kill($rd);
            }
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* OR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$OR(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RS)
        {
            if (RT && RS != RT)
            {
                if (RD != RT) gen($rd, $rs);
                else          gen($rd, $rt);
                if (RD != RT) gen($rt);
                else          gen($rs);
                if (RD != RT) or($rd, $rt);
                else          or($rd, $rs);
                kill($rd);
            }
            else
            {
                mov($rd, $rs);
                kill($rd);
            }
        }
        else if (RT)
        {
            gen($rd, $rt);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* XOR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$XOR(u32 address, u32 opcode, bool delayslot)
{
    auto RD  = Allegrex::Instruction::rd(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RS != RT)
        {
            if (RS)
            {
                if (RT)
                {
                    gen($rd, $rs);
                    gen($rt);
                    xor($rd, $rt);
                    kill($rd);
                }
                else
                {
                    gen($rd, $rs);
                    kill($rd);
                }
            }
            else
            {
                gen($rd, $rt);
                kill($rd);
            }
        }
        else
        {
            mov($rd, u32(-1));
            kill($rd);
        }
    }

    return address + 4;
}

/* NOR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$NOR(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RS)
        {
            gen($rd, $rs);
            if (RT && RS != RT)
            {
                gen($rt);
                or($rd, $rt);
            }
            not($rd);
            kill($rd);
        }
        else if (RT)
        {
            gen($rd, $rt);
            not($rd);
            kill($rd);
        }
        else
        {
            mov($rd, u32(-1));
            kill($rd);
        }
    }

    return address + 4;
}

/* SLT */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SLT(u32 address, u32 opcode, bool delayslot)
{
    auto RD  = Allegrex::Instruction::rd(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RS)
        {
            if (RT)
            {
                if (RD == RT && NO_REGISTER_ALLOCATION)
                {
                    gen($rs);
                    gen($rd, $rt);
                    neg($rd);
                    add($rd, $rs);
                    shr($rd, 31);
                    kill($rd);
                }
                else if (RS != RT)
                {
                    gen($rt);
                    gen($rd, $rs);
                    sub($rd, $rt);
                    shr($rd, 31);
                    kill($rd);
                }
                else
                {
                    mov($rd, 0);
                    kill($rd);
                }
            }
        }
        else
        {
            if (RT)
            {
                gen($rd, $rt);
                neg($rd);
                shr($rd, 31);
                kill($rd);
            }
            else
            {
                mov($rd, 0);
                kill($rd);
            }
        }
    }

    return address + 4;
}

/* SLTU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SLTU(u32 address, u32 opcode, bool delayslot)
{
    auto RD  = Allegrex::Instruction::rd(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RS)
        {
            if (RT)
            {
                if (RD == RT)
                {
                    gen($rs);
                    gen($rd, $rt);
                    cmp($rs, $rd);
                    sbb($rd, $rd);
                    neg($rd);
                    kill($rd);
                }
                else if (RS != RT)
                {
                    gen($rt);
                    gen($rd, $rs);
                    cmp($rd, $rt);
                    sbb($rd, $rd);
                    neg($rd);
                    kill($rd);
                }
                else
                {
                    mov($rd, 0);
                    kill($rd);
                }
            }
        }
        else
        {
            if (RT)
            {
                // TODO: check if there is a better way
                gen($rd, $rt);
                neg($rd);
                sbb($rd, $rd);
                neg($rd);
                kill($rd);
            }
            else
            {
                mov($rd, 0);
                kill($rd);
            }
        }
    }

    return address + 4;
}

/* MAX */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MAX(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RS)
        {
            if (RT)
            {
                if (RT != RD)
                {
                    gen($rt);
                    gen($rd, $rs);
                    cmp($rd, $rt);
                    cmovl($rd, $rt);
                    kill($rd);
                }
                else
                {
                    gen($rs);
                    gen($rd, $rt);
                    cmp($rd, $rs);
                    cmovl($rd, $rs);
                    kill($rd);
                }
            }
            else
            {
                gen($rs);
                mov($rd, 0);
                cmp($rd, $rs);
                cmovl($rd, $rs);
                kill($rd);
            }
        }
        else if (RT)
        {
            gen($rt);
            mov($rd, 0);
            cmp($rd, $rt);
            cmovl($rd, $rt);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* MIN */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MIN(u32 address, u32 opcode, bool delayslot)
{
    auto RD = Allegrex::Instruction::rd(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RS)
        {
            if (RT)
            {
                if (RT != RD)
                {
                    gen($rt);
                    gen($rd, $rs);
                    cmp($rd, $rt);
                    cmovg($rd, $rt);
                    kill($rd);
                }
                else
                {
                    gen($rs);
                    gen($rd, $rt);
                    cmp($rd, $rs);
                    cmovg($rd, $rs);
                    kill($rd);
                }
            }
            else
            {
                gen($rs);
                mov($rd, 0);
                cmp($rd, $rs);
                cmovg($rd, $rs);
                kill($rd);
            }
        }
        else if (RT)
        {
            gen($rt);
            mov($rd, 0);
            cmp($rd, $rt);
            cmovg($rd, $rt);
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* MSUB */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MSUB(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MSUB"); found = true; return address + 4;
}

/* MSUBU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MSUBU(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MSUBU"); found = true; return address + 4;
}

/* ROTRV */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ROTRV(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ROTRV"); found = true; return address + 4;
}

/* ROTR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ROTR(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ROTR"); found = true; return address + 4;
}

/* BLTZ */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BLTZ(u32 address, u32 opcode, bool delayslot)
{
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4 * (1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);

    auto $rs = Gpr(RS);

    if (RS)
    {
        gen($rs);
        mov(ebp, $rs);

        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        cmp(ebp, 0);
        jl(target_address);

        EmitInterpreterBranch(address + 8, opcode, delayslot);

        EmitInterpreterBranch(target_address, DST, opcode, delayslot);

        return INTERPRETER_LIKE ? 0 : address + 8;
    }

    return address + 4;
}

/* BGEZ */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BGEZ(u32 address, u32 opcode, bool delayslot)
{
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4*(1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);

    auto $rs = Gpr(RS);

    if (RS)
    {
        gen($rs);
        mov(ebp, $rs);

        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        cmp(ebp, 0);
        jge(target_address);

        EmitInterpreterBranch(address + 8, opcode, delayslot);

        EmitInterpreterBranch(target_address, DST, opcode, delayslot);

        return INTERPRETER_LIKE ? 0 : address + 8;
    }
    else
    {
        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        if (!INTERPRETER_LIKE) jmp(target_address);
    }

    EmitInterpreterBranch(target_address, DST, opcode, delayslot);

    return 0;
}

/* BLTZL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BLTZL(u32 address, u32 opcode, bool delayslot)
{
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4 * (1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);
    u32 skip_address = SetSkipLabel(address + 8);

    auto $rs = Gpr(RS);

    if (RS)
    {
        gen($rs);
        cmp($rs, 0);
        jnl(skip_address);

        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        if (!INTERPRETER_LIKE) jmp(target_address);

        EmitInterpreterBranch(target_address, DST, opcode, delayslot);

        EmitInterpreterBranch(skip_address, address + 8, opcode, delayslot);

        return INTERPRETER_LIKE ? 0 : address + 8;
    }
    else
    {
        if (!INTERPRETER_LIKE) jmp(target_address);

        EmitInterpreterBranch(target_address, DST, opcode, delayslot);

        return address + 8;
    }
}

/* BGEZL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BGEZL(u32 address, u32 opcode, bool delayslot)
{
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4 * (1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);
    u32 skip_address = SetSkipLabel(address + 8);

    auto $rs = Gpr(RS);

    if (RS)
    {
        gen($rs);
        cmp($rs, 0);
        jnge(skip_address);

        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        if (!INTERPRETER_LIKE) jmp(target_address);

        EmitInterpreterBranch(target_address, DST, opcode, delayslot);

        EmitInterpreterBranch(skip_address, address + 8, opcode, delayslot);

        return INTERPRETER_LIKE ? 0 : address + 8;
    }
    else
    {
        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        if (!INTERPRETER_LIKE) jmp(target_address);

        EmitInterpreterBranch(target_address, DST, opcode, delayslot);

        return address + 8;
    }
}

/* BLTZAL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BLTZAL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BLTZAL"); found = true; return address + 4;
}

/* BGEZAL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BGEZAL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BGEZAL"); found = true; return address + 4;
}

/* BLTZALL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BLTZALL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BLTZALL"); found = true; return address + 4;
}

/* BGEZALL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BGEZALL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BGEZALL"); found = true; return address + 4;
}

/* J */
__noinline u32 Allegrex::ICache::CodeBlock::emit$J(u32 address, u32 opcode, bool delayslot)
{
    auto IMM = Allegrex::Instruction::uimm26(opcode);
    auto DST = (address & 0xF0000000) + 4*IMM;

    u32 target_address = SetTargetLabel(DST);

    EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

    if (!INTERPRETER_LIKE) jmp(target_address);

    EmitInterpreterBranch(target_address, DST, opcode, delayslot);

    return 0;
}

/* JAL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$JAL(u32 address, u32 opcode, bool delayslot)
{
    auto IMM = Allegrex::Instruction::uimm26(opcode);
    auto DST = (address & 0xF0000000) + 4*IMM;

    if (!IMM) // unpatched JAL ? maybe a dead code
    {
        return 0;
    }

    auto $ra = Gpr(31);

    u32 target_address = SetTargetLabel(DST, address + 8);

    EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

    mov($ra, u32(address + 8));
    kill($ra);

    if (!INTERPRETER_LIKE) jmp(target_address, true);

    EmitInterpreterBranch(target_address, DST, opcode, delayslot);

    return INTERPRETER_LIKE ? 0 : address + 8;
}

/* BEQ */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BEQ(u32 address, u32 opcode, bool delayslot)
{
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4*(1 + IMM);

    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RS || RT)
    {
        u32 target_address = SetTargetLabel(DST, address + 8);

        if (RS)
        {
            if (RT)
            {
                gen($rs);
                mov(ebp, $rs);
                if (RT) gen($rt);
                if (RT) sub(ebp, $rt);
            }
            else
            {
                gen($rs);
                mov(ebp, $rs);
            }
        }
        else if (RT)
        {
            gen($rt);
            mov(ebp, $rt);
        }

        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        test(ebp, ebp);
        jz(target_address);

        EmitInterpreterBranch(address + 8, opcode, delayslot);

        EmitInterpreterBranch(target_address, DST, opcode, delayslot);

        return INTERPRETER_LIKE ? 0 : address + 8;
    }
    else
    {
        u32 target_address = SetTargetLabel(DST);

        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        if (!INTERPRETER_LIKE && DST != address + 4) jmp(target_address);

        EmitInterpreterBranch(target_address, DST, opcode, delayslot);
    }

    return 0;
}

/* BNE */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BNE(u32 address, u32 opcode, bool delayslot)
{
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4*(1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);

    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RS == RT)
    {
        return address + 4;
    }

    if (RS)
    {
        gen($rs);
        mov(ebp, $rs);
        if (RT) gen($rt);
        if (RT) sub(ebp, $rt);

        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        test(ebp, ebp);
        jnz(target_address);

        EmitInterpreterBranch(address + 8, opcode, delayslot);
    }
    else
    {
        if (RT)
        {
            gen($rt);
            mov(ebp, $rt);

            EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

            test(ebp, ebp);
            jnz(target_address);

            EmitInterpreterBranch(address + 8, opcode, delayslot);
        }
        else
        {
            return address + 4;
        }
    }

    EmitInterpreterBranch(target_address, DST, opcode, delayslot);

    return INTERPRETER_LIKE ? 0 : address + 8;
}

/* BLEZ */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BLEZ(u32 address, u32 opcode, bool delayslot)
{
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4 * (1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);

    auto $rs = Gpr(RS);

    if (RS)
    {
        gen($rs);
        mov(ebp, $rs);

        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        cmp(ebp, 0);
        jle(target_address);

        EmitInterpreterBranch(address + 8, opcode, delayslot);
    }
    else
    {
        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        if (!INTERPRETER_LIKE) jmp(target_address);
    }

    EmitInterpreterBranch(target_address, DST, opcode, delayslot);

    return INTERPRETER_LIKE ? 0 : address + 8;
}

/* BGTZ */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BGTZ(u32 address, u32 opcode, bool delayslot)
{
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4*(1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);

    auto $rs = Gpr(RS);

    if (RS)
    {
        gen($rs);
        mov(ebp, $rs);

        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        cmp(ebp, 0);
        jg(target_address);

        EmitInterpreterBranch(address + 8, opcode, delayslot);
    }
    else
    {
        EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

        if (!INTERPRETER_LIKE) jmp(target_address);
    }

    EmitInterpreterBranch(target_address, DST, opcode, delayslot);

    return INTERPRETER_LIKE ? 0 : address + 8;
}

/* ADDI */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ADDI(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ADDI"); found = true; return address + 4;
}

/* ADDIU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ADDIU(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);

    if (RT)
    {
        if (RS && IMM)
        {
            gen($rt, $rs);
            /**/ if (IMM < -1) sub($rt, -IMM);
            else if (IMM == -1) dec($rt);
            else if (IMM == +1) inc($rt);
            else if (IMM > +1) add($rt, +IMM);
            kill($rt);
        }
        else
        {
            mov($rt, IMM);
            kill($rt);
        }
    }

    return address + 4;
}

/* SLTI */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SLTI(u32 address, u32 opcode, bool delayslot)
{
    auto RT = Allegrex::Instruction::rt(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RT)
    {
        if (RS)
        {
            gen($rt, $rs);
            if (IMM) sub($rt, IMM);
            shr($rt, 31);
            kill($rt);
        }
        else
        {
            mov($rt, u32(0 - IMM) >> 31);
            kill($rt);
        }
    }

    return address + 4;
}

/* SLTIU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SLTIU(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RT)
    {
        if (RS)
        {
            gen($rt, $rs);
            sub($rt, IMM);
            sbb($rt, $rt);
            neg($rt);
            kill($rt);
        }
        else
        {
            mov($rt, 0);
            kill($rt);
        }
    }

    return address + 4;
}

/* ANDI */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ANDI(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::uimm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);

    if (RT)
    {
        if (RS)
        {
            gen($rt, $rs);
            if (IMM) and($rt, IMM);
            kill($rt);
        }
        else
        {
            mov($rt, 0);
            kill($rt);
        }
    }

    return address + 4;
}

/* ORI */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ORI(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::uimm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);

    if (RT)
    {
        if (RS)
        {
            gen($rt, $rs);
            if (IMM) or($rt, IMM);
            kill($rt);
        }
        else
        {
            mov($rt, IMM);
            kill($rt);
        }
    }

    return address + 4;
}

/* XORI */
__noinline u32 Allegrex::ICache::CodeBlock::emit$XORI(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::uimm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);

    if (RT)
    {
        if (RS)
        {
            gen($rt, $rs);
            if (IMM) xor($rt, IMM);
            kill($rt);
        }
        else
        {
            mov($rt, IMM);
            kill($rt);
        }
    }

    return address + 4;
}

/* LUI */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LUI(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);

    if (RT)
    {
        mov($rt, IMM<<16);
        kill($rt);
    }

    return address + 4;
}

/* MFC0 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MFC0(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MFC0"); found = true; return address + 4;
}

/* CFC0 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$CFC0(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$CFC0"); found = true; return address + 4;
}

/* MTC0 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MTC0(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MTC0"); found = true; return address + 4;
}

/* CTC0 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$CTC0(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$CTC0"); found = true; return address + 4;
}

/* ERET */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ERET(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ERET"); found = true; return address + 4;
}

/* MFC1 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MFC1(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MFC1"); found = true; return address + 4;
}

/* CFC1 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$CFC1(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$CFC1"); found = true; return address + 4;
}

/* MTC1 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MTC1(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "testing emit$MTC1"); found = true;

    auto RT = Allegrex::Instruction::rt(opcode);
    auto FS = Allegrex::Instruction::fs(opcode);

    auto $rt = Gpr(RT);
    auto $fs = fpr_w(FS);

    if (RT)
    {
        gen($rt);
        mov($fs, $rt);
    }
    else
    {
        mov($fs, 0);
    }

    return address + 4;
}

/* CTC1 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$CTC1(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$CTC1"); found = true; return address + 4;
}

/* BC1F */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BC1F(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BC1F"); found = true; return address + 4;
}

/* BC1T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BC1T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BC1T"); found = true; return address + 4;
}

/* BC1FL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BC1FL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BC1FL"); found = true; return address + 4;
}

/* BC1TL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BC1TL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BC1TL"); found = true; return address + 4;
}

/* ADD_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ADD_S(u32 address, u32 opcode, bool delayslot)
{
    auto FD = Allegrex::Instruction::fd(opcode);
    auto FS = Allegrex::Instruction::fs(opcode);
    auto FT = Allegrex::Instruction::ft(opcode);

    auto $fd = fpr_w(FD);
    auto $fs = fpr_w(FS);
    auto $ft = fpr_w(FT);

    __apply_aluss(addss, vaddss, xmm0, $fd, $fs, $ft);

    return address + 4;
}

/* SUB_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SUB_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SUB_S"); found = true; return address + 4;
}

/* MUL_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MUL_S(u32 address, u32 opcode, bool delayslot)
{
    auto FD = Allegrex::Instruction::fd(opcode);
    auto FS = Allegrex::Instruction::fs(opcode);
    auto FT = Allegrex::Instruction::ft(opcode);

    auto $fd = fpr_w(FD);
    auto $fs = fpr_w(FS);
    auto $ft = fpr_w(FT);

    __apply_aluss(mulss, vmulss, xmm0, $fd, $fs, $ft);

    return address + 4;
}

/* DIV_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DIV_S(u32 address, u32 opcode, bool delayslot)
{
    auto FD = Allegrex::Instruction::fd(opcode);
    auto FS = Allegrex::Instruction::fs(opcode);
    auto FT = Allegrex::Instruction::ft(opcode);

    auto $fd = fpr_w(FD);
    auto $fs = fpr_w(FS);
    auto $ft = fpr_w(FT);

    __apply_aluss(divss, vdivss, xmm0, $fd, $fs, $ft);

    return address + 4;
}

/* SQRT_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SQRT_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SQRT_S"); found = true; return address + 4;
}

/* ABS_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ABS_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ABS_S"); found = true; return address + 4;
}

/* MOV_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MOV_S(u32 address, u32 opcode, bool delayslot)
{
    auto FD = Allegrex::Instruction::fd(opcode);
    auto FS = Allegrex::Instruction::fs(opcode);

    auto $fd = fpr_w(FD);
    auto $fs = fpr_w(FS);

    __apply_movss(xmm0, $fd, $fs);

    return address + 4;
}

/* NEG_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$NEG_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$NEG_S"); found = true; return address + 4;
}

/* ROUND_W_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ROUND_W_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ROUND_W_S"); found = true; return address + 4;
}

/* TRUNC_W_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$TRUNC_W_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$TRUNC_W_S"); found = true; return address + 4;
}

/* CEIL_W_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$CEIL_W_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$CEIL_W_S"); found = true; return address + 4;
}

/* FLOOR_W_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$FLOOR_W_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$FLOOR_W_S"); found = true; return address + 4;
}

/* CVT_W_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$CVT_W_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$CVT_W_S"); found = true; return address + 4;
}

/* C_F_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_F_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<0>"); found = true; return address + 4;
}

/* C_UN_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_UN_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<1>"); found = true; return address + 4;
}

/* C_EQ_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_EQ_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<2>"); found = true; return address + 4;
}

/* C_UEQ_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_UEQ_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<3>"); found = true; return address + 4;
}

/* C_OLT_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_OLT_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<4>"); found = true; return address + 4;
}

/* C_ULT_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_ULT_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<5>"); found = true; return address + 4;
}

/* C_OLE_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_OLE_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<6>"); found = true; return address + 4;
}

/* C_ULE_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_ULE_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<7>"); found = true; return address + 4;
}

/* C_SF_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_SF_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<8>"); found = true; return address + 4;
}

/* C_NGLE_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_NGLE_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<9>"); found = true; return address + 4;
}

/* C_SEQ_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_SEQ_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<10>"); found = true; return address + 4;
}

/* C_NGL_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_NGL_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<11>"); found = true; return address + 4;
}

/* C_LT_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_LT_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<12>"); found = true; return address + 4;
}

/* C_NGE_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_NGE_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<13>"); found = true; return address + 4;
}

/* C_LE_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_LE_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<14>"); found = true; return address + 4;
}

/* C_NGT_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$C_NGT_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$C_COND_S<15>"); found = true; return address + 4;
}

/* CVT_S_W */
__noinline u32 Allegrex::ICache::CodeBlock::emit$CVT_S_W(u32 address, u32 opcode, bool delayslot)
{
    auto FD = Allegrex::Instruction::fd(opcode);
    auto FS = Allegrex::Instruction::fs(opcode);

    auto $fd = fpr_w(FD);
    auto $fs = fpr_w(FS);

#if !defined(__AVX__)
    cvtsi2ss(xmm0, $fs);
    movss($fd, xmm0);
#else
    vcvtsi2ss(xmm0, xmm0, $fs);
    vmovss($fd, xmm0);
#endif

    return address + 4;
}

/* MFV */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MFV(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MFV"); found = true; return address + 4;
}

/* MFVC */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MFVC(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MFVC"); found = true; return address + 4;
}

/* MTV */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MTV(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MTV"); found = true; return address + 4;
}

/* MTVC */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MTVC(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MTVC"); found = true; return address + 4;
}

/* BVF */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BVF(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BVF"); found = true; return address + 4;
}

/* BVT */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BVT(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BVT"); found = true; return address + 4;
}

/* BVFL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BVFL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BVFL"); found = true; return address + 4;
}

/* BVTL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BVTL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BVTL"); found = true; return address + 4;
}

/* BEQL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BEQL(u32 address, u32 opcode, bool delayslot)
{
    auto RS = Allegrex::Instruction::rs(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4 * (1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);
    u32 skip_address = SetSkipLabel(address + 8);

    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RS != RT)
    {

        if (RS)
        {
            gen($rs);
            if (RT)
            {
                gen($rt);
                cmp($rs, $rt);
            }
            else
            {
                cmp($rs, 0);
            }
        }
        else if (RT)
        {
            gen($rt);
            cmp($rt, 0);
        }
        jne(skip_address);
    }

    EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

    if (!INTERPRETER_LIKE) jmp(target_address);

    EmitInterpreterBranch(target_address, DST, opcode, delayslot);

    if (RS != RT) EmitInterpreterBranch(skip_address, address + 8, opcode, delayslot);

    return INTERPRETER_LIKE ? 0 : address + 8;
}

/* BNEL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BNEL(u32 address, u32 opcode, bool delayslot)
{
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4*(1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);
    u32 skip_address = SetSkipLabel(address + 8);

    if (RS == RT)
    {
        if (!INTERPRETER_LIKE) jmp(skip_address);

        EmitInterpreterBranch(skip_address, address + 8, opcode, delayslot);

        return INTERPRETER_LIKE ? 0 : address + 4;
    }

    auto $rs = Gpr(RS);
    auto $rt = Gpr(RT);

    if (RS)
    {
        gen($rs);
        if (RT)
        {
            gen($rt);
            cmp($rs, $rt);
        }
        else
        {
            cmp($rs, 0);
        }
    }
    else if (RT)
    {
        gen($rt);
        cmp($rt, 0);
    }
    je(skip_address);

    EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

    if (!INTERPRETER_LIKE) jmp(target_address);

    EmitInterpreterBranch(target_address, DST, opcode, delayslot);

    EmitInterpreterBranch(skip_address, address + 8, opcode, delayslot);

    return INTERPRETER_LIKE ? 0 : address + 8;
}

/* BLEZL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BLEZL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BLEZL"); found = true; return address + 4;
}

/* BGTZL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BGTZL(u32 address, u32 opcode, bool delayslot)
{
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);
    auto DST = address + 4*(1 + IMM);

    u32 target_address = SetTargetLabel(DST, address + 8);
    u32 skip_address = SetSkipLabel(address + 8);

    auto $rs = Gpr(RS);

    if (RS)
    {
        gen($rs);
        cmp($rs, 0);

        jle(skip_address);
    }
    else
    {
        if (!INTERPRETER_LIKE) jmp(skip_address);

        EmitInterpreterBranch(skip_address, address + 8, opcode, delayslot);

        return INTERPRETER_LIKE ? 0 : address + 4;
    }

    EmitInstruction(address + 4, *((p32u32)(address + 4)), true);

    if (!INTERPRETER_LIKE) jmp(target_address);

    EmitInterpreterBranch(target_address, DST, opcode, delayslot);

    EmitInterpreterBranch(skip_address, address + 8, opcode, delayslot);

    return INTERPRETER_LIKE ? 0 : address + 8;
}

/* VADD_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VADD_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VADD<1>"); found = true; return address + 4;
}

/* VADD_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VADD_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VADD<2>"); found = true; return address + 4;
}

/* VADD_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VADD_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VADD<3>"); found = true; return address + 4;
}

/* VADD_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VADD_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VADD<4>"); found = true; return address + 4;
}

/* VSUB_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSUB_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSUB<1>"); found = true; return address + 4;
}

/* VSUB_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSUB_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSUB<2>"); found = true; return address + 4;
}

/* VSUB_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSUB_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSUB<3>"); found = true; return address + 4;
}

/* VSUB_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSUB_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSUB<4>"); found = true; return address + 4;
}

/* VSBN_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSBN_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSBN<1>"); found = true; return address + 4;
}

/* VDIV_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VDIV_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VDIV<1>"); found = true; return address + 4;
}

/* VDIV_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VDIV_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VDIV<2>"); found = true; return address + 4;
}

/* VDIV_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VDIV_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VDIV<3>"); found = true; return address + 4;
}

/* VDIV_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VDIV_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VDIV<4>"); found = true; return address + 4;
}

/* VMUL_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMUL_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMUL<1>"); found = true; return address + 4;
}

/* VMUL_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMUL_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMUL<2>"); found = true; return address + 4;
}

/* VMUL_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMUL_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMUL<3>"); found = true; return address + 4;
}

/* VMUL_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMUL_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMUL<4>"); found = true; return address + 4;
}

/* VDOT_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VDOT_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VDOT<2>"); found = true; return address + 4;
}

/* VDOT_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VDOT_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VDOT<3>"); found = true; return address + 4;
}

/* VDOT_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VDOT_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VDOT<4>"); found = true; return address + 4;
}

/* VSCL_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSCL_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSCL<2>"); found = true; return address + 4;
}

/* VSCL_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSCL_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSCL<3>"); found = true; return address + 4;
}

/* VSCL_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSCL_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSCL<4>"); found = true; return address + 4;
}

/* VHDP_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VHDP_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VHDP<2>"); found = true; return address + 4;
}

/* VHDP_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VHDP_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VHDP<3>"); found = true; return address + 4;
}

/* VHDP_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VHDP_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VHDP<4>"); found = true; return address + 4;
}

/* VCRS_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCRS_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCRS<3>"); found = true; return address + 4;
}

/* VDET_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VDET_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VDET<2>"); found = true; return address + 4;
}

/* VCMP_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMP_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMP<1>"); found = true; return address + 4;
}

/* VCMP_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMP_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMP<2>"); found = true; return address + 4;
}

/* VCMP_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMP_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMP<3>"); found = true; return address + 4;
}

/* VCMP_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMP_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMP<4>"); found = true; return address + 4;
}

/* VMIN_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMIN_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMIN<1>"); found = true; return address + 4;
}

/* VMIN_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMIN_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMIN<2>"); found = true; return address + 4;
}

/* VMIN_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMIN_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMIN<3>"); found = true; return address + 4;
}

/* VMIN_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMIN_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMIN<4>"); found = true; return address + 4;
}

/* VMAX_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMAX_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMAX<1>"); found = true; return address + 4;
}

/* VMAX_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMAX_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMAX<2>"); found = true; return address + 4;
}

/* VMAX_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMAX_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMAX<3>"); found = true; return address + 4;
}

/* VMAX_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMAX_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMAX<4>"); found = true; return address + 4;
}

/* VSCMP_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSCMP_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSCMP<1>"); found = true; return address + 4;
}

/* VSCMP_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSCMP_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSCMP<2>"); found = true; return address + 4;
}

/* VSCMP_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSCMP_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSCMP<3>"); found = true; return address + 4;
}

/* VSCMP_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSCMP_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSCMP<4>"); found = true; return address + 4;
}

/* VSGE_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSGE_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSGE<1>"); found = true; return address + 4;
}

/* VSGE_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSGE_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSGE<2>"); found = true; return address + 4;
}

/* VSGE_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSGE_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSGE<3>"); found = true; return address + 4;
}

/* VSGE_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSGE_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSGE<4>"); found = true; return address + 4;
}

/* VSLT_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSLT_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSLT<1>"); found = true; return address + 4;
}

/* VSLT_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSLT_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSLT<2>"); found = true; return address + 4;
}

/* VSLT_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSLT_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSLT<3>"); found = true; return address + 4;
}

/* VSLT_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSLT_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSLT<4>"); found = true; return address + 4;
}

/* HALT */
__noinline u32 Allegrex::ICache::CodeBlock::emit$HALT(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$HALT"); found = true; return address + 4;
}

/* MFIC */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MFIC(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MFIC"); found = true; return address + 4;
}

/* MTIC */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MTIC(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MTIC"); found = true; return address + 4;
}

/* MFDR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MFDR(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MFDR"); found = true; return address + 4;
}

/* DRET */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DRET(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DRET"); found = true; return address + 4;
}

/* DBREAK */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DBREAK(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DBREAK"); found = true; return address + 4;
}

/* MTDR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$MTDR(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$MTDR"); found = true; return address + 4;
}

/* EXT */
__noinline u32 Allegrex::ICache::CodeBlock::emit$EXT(u32 address, u32 opcode, bool delayslot)
{
    auto RT = Allegrex::Instruction::rt(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto SA = Allegrex::Instruction::sa(opcode);
    auto RD = Allegrex::Instruction::rd(opcode);

    auto $rt  = Gpr(RT);
    auto $rs  = Gpr(RS);

    if (RT)
    {
        if (RS)
        {
            gen($rt, $rs);
            if (SA) shr($rt, s8(SA));
            and($rt, (2 << RD) - 1);
            kill($rt);
        }
        else
        {
            mov($rt, 0);
            kill($rt);
        }
    }

    return address + 4;
}

/* INS */
__noinline u32 Allegrex::ICache::CodeBlock::emit$INS(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto SA  = Allegrex::Instruction::sa(opcode);
    auto RD  = Allegrex::Instruction::rd(opcode);
    auto MSK = ~(~0 << (RD - SA + 1)) << SA;

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);

    // INS: (_rt & ~x) | ((_rs << pos) & x); where x = ~(~0 << len) << pos;

    if (RT)
    {
        gen($rt);
        if (RS)
        {
            gen($rs);
            mov(eax, $rs);
            and($rt, ~MSK);
            shl(eax, s8(SA));
            and(eax, MSK);
            or($rt, eax);
        }
        else
        {
            and($rt, ~MSK);
        }
        kill($rt);
    }

    return address + 4;
}

/* WSBH */
__noinline u32 Allegrex::ICache::CodeBlock::emit$WSBH(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$WSBH"); found = true; return address + 4;
}

/* WSBW */
__noinline u32 Allegrex::ICache::CodeBlock::emit$WSBW(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$WSBW"); found = true; return address + 4;
}

/* SEB */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SEB(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "testing emit$SEB"); found = true;

    auto RD = Allegrex::Instruction::rd(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RT)
        {
            gen($rt);
            movsx($rd, Reg8($rt));
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* BITREV */
__noinline u32 Allegrex::ICache::CodeBlock::emit$BITREV(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$BITREV"); found = true; return address + 4;
}

/* SEH */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SEH(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "testing emit$SEH"); found = true;

    auto RD = Allegrex::Instruction::rd(opcode);
    auto RT = Allegrex::Instruction::rt(opcode);

    auto $rd = Gpr(RD);
    auto $rt = Gpr(RT);

    if (RD)
    {
        if (RT)
        {
            gen($rt);
            movsx($rd, Reg16($rt));
            kill($rd);
        }
        else
        {
            mov($rd, 0);
            kill($rd);
        }
    }

    return address + 4;
}

/* LB */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LB(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RT)
    {
        if (RS)
        {
            gen($rs);
            if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
            movsx($rt, byte_ptr[$rb+s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        else
        {
            movsx($rt, byte_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        kill($rt);
    }

    return address + 4;
}

/* LH */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LH(u32 address, u32 opcode, bool delayslot)
{
    //static bool found = false; if (!found) forcef(emu, "testing emit$LH"); found = true;

    auto RT = Allegrex::Instruction::rt(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RT)
    {
        if (RS)
        {
            gen($rs);
            if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
            movsx($rt, word_ptr[$rb + s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        else
        {
            movsx($rt, word_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        kill($rt);
    }

    return address + 4;
}

/* LWL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LWL(u32 address, u32 opcode, bool delayslot)
{
    //static bool found = false; if (!found) forcef(emu, "testing emit$LWL"); found = true;

    // Note: LWL is scary to emulate !
    auto RT = Allegrex::Instruction::rt(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RT)
    {
        gen($rt);
        if (RS)
        {
            gen($rs);
            if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
            lea(rdx, qword_ptr[$rb + s32(DCACHE_MEMORY_ADDRESS + IMM)]);
            lea(ecx, dword_ptr[rdx * 8]);
            and(edx, 0xFFFFFFFC);
            and(ecx, 0x18);
            mov(eax, dword_ptr[rdx]); // ijkl
            xor(ecx, 0x18);
            mov(edx, $rt); // efgh
            ror(edx, cl); // 24: efgh -> hefg -> ghef -> fghe, 16: efgh -> hefg -> ghef, 8: efgh -> hefg, 0: efgh
            shld(eax, edx, cl); // 24: ijkl -> jklf -> klfg -> lfgh, 16: ijkl -> jklg -> klgh, 8: ijkl -> jklh, 0: ijkl
            mov($rt, eax);
        }
        else
        {
            switch (IMM & 3)
            {
            case 0:
                mov(edx, $rt);
                mov(eax, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM) & 0xFFFFFFFC]);
                ror(edx, 24);
                shld(edx, eax, 24);
                mov($rt, edx);
                break;
            case 1:
                mov(edx, $rt);
                mov(eax, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM) & 0xFFFFFFFC]);
                ror(edx, 16);
                shrd(edx, eax, 16);
                mov($rt, edx);
                break;
            case 2:
                mov(edx, $rt);
                mov(eax, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM) & 0xFFFFFFFC]);
                ror(edx, 8);
                shrd(edx, eax, 8);
                mov($rt, edx);
                break;
            default:
                mov($rt, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM) & 0xFFFFFFFC]);
                mov($rt, $rt);
                break;
            }
        }
        kill($rt);
    }

    //static u32 const lwl_mask[4] = { 0xffffff, 0xffff, 0xff, 0 };
    //static u32 const lwl_shift[4] = { 24, 16, 8, 0 };
    //if (rt != 0)
    //{
    //    u32 address = gpr[rs] + simm16;
    //    u32 offset = address & 0x3;
    //    u32 data = *lle::mmu::Addr< u32 >(address & 0xfffffffc);
    //    gpr[rt] = (data << lwl_shift[offset]) | (gpr[rt] & lwl_mask[offset]);
    //}

    return address + 4;
}

/* LW */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LW(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RT)
    {
        if (RS)
        {
            gen($rs);
            if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
            mov($rt, dword_ptr[$rb+s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        else
        {
            mov($rt, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        kill($rt);
    }

    return address + 4;
}

/* LBU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LBU(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RT)
    {
        if (RS)
        {
            gen($rs);
            if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
            movzx($rt, byte_ptr[$rb+s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        else
        {
            movzx($rt, byte_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        kill($rt);
    }

    return address + 4;
}

/* LHU */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LHU(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RT)
    {
        if (RS)
        {
            gen($rs);
            if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
            movzx($rt, word_ptr[$rb+s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        else
        {
            movzx($rt, word_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)]);
        }
        kill($rt);
    }

    return address + 4;
}

/* LWR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LWR(u32 address, u32 opcode, bool delayslot)
{
    //static bool found = false; if (!found) forcef(emu, "testing emit$LWR"); found = true;

    auto RT = Allegrex::Instruction::rt(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RT)
    {
        gen($rt);
        if (RS)
        {
            gen($rs);
            if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
            lea(rdx, qword_ptr[$rb + s32(DCACHE_MEMORY_ADDRESS + IMM)]);
            lea(ecx, dword_ptr[rdx * 8]);
            and(edx, 0xFFFFFFFC);
            and(ecx, 0x18);
            mov(eax, dword_ptr[rdx]);
            mov(edx, $rt);
            rol(edx, cl);
            shrd(eax, edx, cl);
            mov($rt, eax);
        }
        else
        {
            switch (IMM & 3)
            {
            case 0:
                mov($rt, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM) & 0xFFFFFFFC]);
                mov($rt, $rt);
                break;
            case 1:
                mov(edx, $rt);
                mov(eax, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM) & 0xFFFFFFFC]);
                rol(edx, 8);
                shrd(eax, edx, 8);
                mov($rt, eax);
                break;
            case 2:
                mov(edx, $rt);
                mov(eax, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM) & 0xFFFFFFFC]);
                rol(edx, 16);
                shrd(eax, edx, 16);
                mov($rt, eax);
                break;
            default:
                mov(edx, $rt);
                mov(eax, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM) & 0xFFFFFFFC]);
                rol(edx, 24);
                shrd(eax, edx, 24);
                mov($rt, eax);
                break;
            }
        }
        kill($rt);
    }

    return address + 4;
}

/* SB */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SB(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RS)
    {
        gen($rs);
        if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
        if (RT)
        {
            gen($rt);
            mov(byte_ptr[$rb+s32(DCACHE_MEMORY_ADDRESS + IMM)], $rt);
        }
        else
        {
            mov(byte_ptr[$rb+s32(DCACHE_MEMORY_ADDRESS + IMM)], 0);
        }
    }
    else
    {
        if (RT)
        {
            gen($rt);
            mov(byte_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)], $rt);
        }
        else
        {
            mov(byte_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)], 0);
        }
    }

    return address + 4;
}

/* SH */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SH(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RS)
    {
        gen($rs);
        if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
        if (RT)
        {
            gen($rt);
            mov(word_ptr[$rb + s32(DCACHE_MEMORY_ADDRESS + IMM)], $rt);
        }
        else
        {
            mov(word_ptr[$rb+s32(DCACHE_MEMORY_ADDRESS + IMM)], 0);
        }
    }
    else
    {
        if (RT)
        {
            gen($rt);
            mov(word_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)], $rt);
        }
        else
        {
            mov(word_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)], 0);
        }
    }

    return address + 4;
}

/* SWL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SWL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SWL"); found = true; return address + 4;
}

/* SW */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SW(u32 address, u32 opcode, bool delayslot)
{
    auto RT  = Allegrex::Instruction::rt(opcode);
    auto RS  = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $rt = Gpr(RT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

    if (RS)
    {
        gen($rs);
        if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
        if (RT)
        {
            gen($rt);
            mov(dword_ptr[$rb + s32(DCACHE_MEMORY_ADDRESS + IMM)], $rt);
        }
        else
        {
            mov(dword_ptr[$rb+s32(DCACHE_MEMORY_ADDRESS + IMM)], 0);
        }
    }
    else
    {
        if (RT)
        {
            gen($rt);
            mov(dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)], $rt);
        }
        else
        {
            mov(dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)], 0);
        }
    }

    return address + 4;
}

/* SWR */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SWR(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SWR"); found = true; return address + 4;
}

/* ICACHE_INDEX_INVALIDATE */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ICACHE_INDEX_INVALIDATE(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ICACHE_INDEX_INVALIDATE"); found = true; return address + 4;
}

/* ICACHE_INDEX_UNLOCK */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ICACHE_INDEX_UNLOCK(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ICACHE_INDEX_UNLOCK"); found = true; return address + 4;
}

/* ICACHE_HIT_INVALIDATE */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ICACHE_HIT_INVALIDATE(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ICACHE_HIT_INVALIDATE"); found = true; return address + 4;
}

/* ICACHE_FILL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ICACHE_FILL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ICACHE_FILL"); found = true; return address + 4;
}

/* ICACHE_FILL_WITH_LOCK */
__noinline u32 Allegrex::ICache::CodeBlock::emit$ICACHE_FILL_WITH_LOCK(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$ICACHE_FILL_WITH_LOCK"); found = true; return address + 4;
}

/* DCACHE_INDEX_WRITEBACK_INVALIDATE */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DCACHE_INDEX_WRITEBACK_INVALIDATE(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DCACHE_INDEX_WRITEBACK_INVALIDATE"); found = true; return address + 4;
}

/* DCACHE_INDEX_UNLOCK */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DCACHE_INDEX_UNLOCK(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DCACHE_INDEX_UNLOCK"); found = true; return address + 4;
}

/* DCACHE_CREATE_DIRTY_EXCLUSIVE */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DCACHE_CREATE_DIRTY_EXCLUSIVE(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DCACHE_CREATE_DIRTY_EXCLUSIVE"); found = true; return address + 4;
}

/* DCACHE_HIT_INVALIDATE */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DCACHE_HIT_INVALIDATE(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DCACHE_HIT_INVALIDATE"); found = true; return address + 4;
}

/* DCACHE_HIT_WRITEBACK */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DCACHE_HIT_WRITEBACK(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DCACHE_HIT_WRITEBACK"); found = true; return address + 4;
}

/* DCACHE_HIT_WRITEBACK_INVALIDATE */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DCACHE_HIT_WRITEBACK_INVALIDATE(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DCACHE_HIT_WRITEBACK_INVALIDATE"); found = true; return address + 4;
}

/* DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK"); found = true; return address + 4;
}

/* DCACHE_FILL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DCACHE_FILL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DCACHE_FILL"); found = true; return address + 4;
}

/* DCACHE_FILL_WITH_LOCK */
__noinline u32 Allegrex::ICache::CodeBlock::emit$DCACHE_FILL_WITH_LOCK(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$DCACHE_FILL_WITH_LOCK"); found = true; return address + 4;
}

/* LL */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LL(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$LL"); found = true; return address + 4;
}

/* LWC1 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LWC1(u32 address, u32 opcode, bool delayslot)
{
    auto FT = Allegrex::Instruction::ft(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $ft = fpr_w(FT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

#if !defined(__AVX__)
    if (RS)
    {
        gen($rs);
        if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
        movss(xmm0, dword_ptr[$rb + s32(DCACHE_MEMORY_ADDRESS + IMM)]);
    }
    else
    {
        movss(xmm0, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)]);
    }
    movss($ft, xmm0);
#else
    if (RS)
    {
        gen($rs);
        if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
        vmovss(xmm0, dword_ptr[$rb + s32(DCACHE_MEMORY_ADDRESS + IMM)]);
    }
    else
    {
        vmovss(xmm0, dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)]);
    }
    vmovss($ft, xmm0);
#endif

    return address + 4;
}

/* LV_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LV_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$LV_S"); found = true; return address + 4;
}

/* VMOV_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMOV_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMOV<1>"); found = true; return address + 4;
}

/* VMOV_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMOV_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMOV<2>"); found = true; return address + 4;
}

/* VMOV_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMOV_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMOV<3>"); found = true; return address + 4;
}

/* VMOV_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMOV_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMOV<4>"); found = true; return address + 4;
}

/* VABS_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VABS_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VABS<1>"); found = true; return address + 4;
}

/* VABS_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VABS_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VABS<2>"); found = true; return address + 4;
}

/* VABS_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VABS_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VABS<3>"); found = true; return address + 4;
}

/* VABS_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VABS_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VABS<4>"); found = true; return address + 4;
}

/* VNEG_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNEG_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNEG<1>"); found = true; return address + 4;
}

/* VNEG_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNEG_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNEG<2>"); found = true; return address + 4;
}

/* VNEG_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNEG_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNEG<3>"); found = true; return address + 4;
}

/* VNEG_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNEG_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNEG<4>"); found = true; return address + 4;
}

/* VIDT_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VIDT_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VIDT<1>"); found = true; return address + 4;
}

/* VIDT_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VIDT_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VIDT<2>"); found = true; return address + 4;
}

/* VIDT_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VIDT_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VIDT<3>"); found = true; return address + 4;
}

/* VIDT_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VIDT_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VIDT<4>"); found = true; return address + 4;
}

/* VSAT0_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSAT0_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSAT0<1>"); found = true; return address + 4;
}

/* VSAT0_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSAT0_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSAT0<2>"); found = true; return address + 4;
}

/* VSAT0_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSAT0_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSAT0<3>"); found = true; return address + 4;
}

/* VSAT0_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSAT0_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSAT0<4>"); found = true; return address + 4;
}

/* VSAT1_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSAT1_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSAT1<1>"); found = true; return address + 4;
}

/* VSAT1_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSAT1_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSAT1<2>"); found = true; return address + 4;
}

/* VSAT1_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSAT1_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSAT1<3>"); found = true; return address + 4;
}

/* VSAT1_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSAT1_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSAT1<4>"); found = true; return address + 4;
}

/* VZERO_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VZERO_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VZERO<1>"); found = true; return address + 4;
}

/* VZERO_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VZERO_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VZERO<2>"); found = true; return address + 4;
}

/* VZERO_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VZERO_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VZERO<3>"); found = true; return address + 4;
}

/* VZERO_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VZERO_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VZERO<4>"); found = true; return address + 4;
}

/* VONE_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VONE_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VONE<1>"); found = true; return address + 4;
}

/* VONE_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VONE_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VONE<2>"); found = true; return address + 4;
}

/* VONE_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VONE_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VONE<3>"); found = true; return address + 4;
}

/* VONE_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VONE_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VONE<4>"); found = true; return address + 4;
}

/* VRCP_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRCP_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRCP<1>"); found = true; return address + 4;
}

/* VRCP_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRCP_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRCP<2>"); found = true; return address + 4;
}

/* VRCP_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRCP_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRCP<3>"); found = true; return address + 4;
}

/* VRCP_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRCP_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRCP<4>"); found = true; return address + 4;
}

/* VRSQ_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRSQ_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRSQ<1>"); found = true; return address + 4;
}

/* VRSQ_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRSQ_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRSQ<2>"); found = true; return address + 4;
}

/* VRSQ_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRSQ_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRSQ<3>"); found = true; return address + 4;
}

/* VRSQ_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRSQ_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRSQ<4>"); found = true; return address + 4;
}

/* VSIN_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSIN_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSIN<1>"); found = true; return address + 4;
}

/* VSIN_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSIN_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSIN<2>"); found = true; return address + 4;
}

/* VSIN_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSIN_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSIN<3>"); found = true; return address + 4;
}

/* VSIN_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSIN_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSIN<4>"); found = true; return address + 4;
}

/* VCOS_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCOS_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCOS<1>"); found = true; return address + 4;
}

/* VCOS_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCOS_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCOS<2>"); found = true; return address + 4;
}

/* VCOS_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCOS_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCOS<3>"); found = true; return address + 4;
}

/* VCOS_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCOS_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCOS<4>"); found = true; return address + 4;
}

/* VEXP2_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VEXP2_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VEXP2<1>"); found = true; return address + 4;
}

/* VEXP2_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VEXP2_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VEXP2<2>"); found = true; return address + 4;
}

/* VEXP2_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VEXP2_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VEXP2<3>"); found = true; return address + 4;
}

/* VEXP2_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VEXP2_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VEXP2<4>"); found = true; return address + 4;
}

/* VLOG2_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VLOG2_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VLOG2<1>"); found = true; return address + 4;
}

/* VLOG2_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VLOG2_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VLOG2<2>"); found = true; return address + 4;
}

/* VLOG2_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VLOG2_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VLOG2<3>"); found = true; return address + 4;
}

/* VLOG2_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VLOG2_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VLOG2<4>"); found = true; return address + 4;
}

/* VSQRT_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSQRT_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSQRT<1>"); found = true; return address + 4;
}

/* VSQRT_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSQRT_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSQRT<2>"); found = true; return address + 4;
}

/* VSQRT_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSQRT_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSQRT<3>"); found = true; return address + 4;
}

/* VSQRT_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSQRT_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSQRT<4>"); found = true; return address + 4;
}

/* VASIN_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VASIN_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VASIN<1>"); found = true; return address + 4;
}

/* VASIN_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VASIN_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VASIN<2>"); found = true; return address + 4;
}

/* VASIN_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VASIN_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VASIN<3>"); found = true; return address + 4;
}

/* VASIN_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VASIN_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VASIN<4>"); found = true; return address + 4;
}

/* VNRCP_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNRCP_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNRCP<1>"); found = true; return address + 4;
}

/* VNRCP_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNRCP_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNRCP<2>"); found = true; return address + 4;
}

/* VNRCP_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNRCP_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNRCP<3>"); found = true; return address + 4;
}

/* VNRCP_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNRCP_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNRCP<4>"); found = true; return address + 4;
}

/* VNSIN_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNSIN_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNSIN<1>"); found = true; return address + 4;
}

/* VNSIN_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNSIN_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNSIN<2>"); found = true; return address + 4;
}

/* VNSIN_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNSIN_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNSIN<3>"); found = true; return address + 4;
}

/* VNSIN_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNSIN_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNSIN<4>"); found = true; return address + 4;
}

/* VREXP2_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VREXP2_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VREXP2<1>"); found = true; return address + 4;
}

/* VREXP2_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VREXP2_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VREXP2<2>"); found = true; return address + 4;
}

/* VREXP2_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VREXP2_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VREXP2<3>"); found = true; return address + 4;
}

/* VREXP2_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VREXP2_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VREXP2<4>"); found = true; return address + 4;
}

/* VRNDS_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDS_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDS<1>"); found = true; return address + 4;
}

/* VRNDI_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDI_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDI<1>"); found = true; return address + 4;
}

/* VRNDI_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDI_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDI<2>"); found = true; return address + 4;
}

/* VRNDI_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDI_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDI<3>"); found = true; return address + 4;
}

/* VRNDI_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDI_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDI<4>"); found = true; return address + 4;
}

/* VRNDF1_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDF1_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDF1<1>"); found = true; return address + 4;
}

/* VRNDF1_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDF1_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDF1<2>"); found = true; return address + 4;
}

/* VRNDF1_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDF1_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDF1<3>"); found = true; return address + 4;
}

/* VRNDF1_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDF1_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDF1<4>"); found = true; return address + 4;
}

/* VRNDF2_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDF2_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDF2<1>"); found = true; return address + 4;
}

/* VRNDF2_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDF2_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDF2<2>"); found = true; return address + 4;
}

/* VRNDF2_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDF2_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDF2<3>"); found = true; return address + 4;
}

/* VRNDF2_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VRNDF2_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VRNDF2<4>"); found = true; return address + 4;
}

/* VF2H_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2H_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2H<2>"); found = true; return address + 4;
}

/* VF2H_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2H_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2H<4>"); found = true; return address + 4;
}

/* VH2F_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VH2F_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VH2F<1>"); found = true; return address + 4;
}

/* VH2F_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VH2F_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VH2F<2>"); found = true; return address + 4;
}

/* VSBZ_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSBZ_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSBZ<1>"); found = true; return address + 4;
}

/* VLGB_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VLGB_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VLGB<1>"); found = true; return address + 4;
}

/* VUC2I_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VUC2I_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VUC2I<1>"); found = true; return address + 4;
}

/* VC2I_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VC2I_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VC2I<1>"); found = true; return address + 4;
}

/* VUS2I_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VUS2I_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VUS2I<1>"); found = true; return address + 4;
}

/* VUS2I_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VUS2I_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VUS2I<2>"); found = true; return address + 4;
}

/* VS2I_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VS2I_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VS2I<1>"); found = true; return address + 4;
}

/* VS2I_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VS2I_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VS2I<2>"); found = true; return address + 4;
}

/* VI2UC_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2UC_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2UC<4>"); found = true; return address + 4;
}

/* VI2C_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2C_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2C<4>"); found = true; return address + 4;
}

/* VI2US_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2US_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2US<2>"); found = true; return address + 4;
}

/* VI2US_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2US_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2US<4>"); found = true; return address + 4;
}

/* VI2S_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2S_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2S<2>"); found = true; return address + 4;
}

/* VI2S_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2S_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2S<4>"); found = true; return address + 4;
}

/* VSRT1_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSRT1_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSRT1<4>"); found = true; return address + 4;
}

/* VSRT2_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSRT2_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSRT2<4>"); found = true; return address + 4;
}

/* VBFY1_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VBFY1_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VBFY1<2>"); found = true; return address + 4;
}

/* VBFY1_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VBFY1_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VBFY1<4>"); found = true; return address + 4;
}

/* VBFY2_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VBFY2_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VBFY2<4>"); found = true; return address + 4;
}

/* VOCP_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VOCP_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VOCP<1>"); found = true; return address + 4;
}

/* VOCP_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VOCP_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VOCP<2>"); found = true; return address + 4;
}

/* VOCP_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VOCP_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VOCP<3>"); found = true; return address + 4;
}

/* VOCP_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VOCP_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VOCP<4>"); found = true; return address + 4;
}

/* VSOCP_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSOCP_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSOCP<1>"); found = true; return address + 4;
}

/* VSOCP_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSOCP_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSOCP<2>"); found = true; return address + 4;
}

/* VFAD_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VFAD_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VFAD<2>"); found = true; return address + 4;
}

/* VFAD_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VFAD_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VFAD<3>"); found = true; return address + 4;
}

/* VFAD_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VFAD_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VFAD<4>"); found = true; return address + 4;
}

/* VAVG_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VAVG_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VAVG<2>"); found = true; return address + 4;
}

/* VAVG_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VAVG_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VAVG<3>"); found = true; return address + 4;
}

/* VAVG_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VAVG_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VAVG<4>"); found = true; return address + 4;
}

/* VSRT3_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSRT3_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSRT3<4>"); found = true; return address + 4;
}

/* VSRT4_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSRT4_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSRT4<4>"); found = true; return address + 4;
}

/* VSGN_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSGN_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSGN<1>"); found = true; return address + 4;
}

/* VSGN_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSGN_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSGN<2>"); found = true; return address + 4;
}

/* VSGN_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSGN_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSGN<3>"); found = true; return address + 4;
}

/* VSGN_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSGN_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSGN<4>"); found = true; return address + 4;
}

/* VMFVC */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMFVC(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMFVC"); found = true; return address + 4;
}

/* VMTVC */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMTVC(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMTVC"); found = true; return address + 4;
}

/* VT4444_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VT4444_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VT4444<4>"); found = true; return address + 4;
}

/* VT5551_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VT5551_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VT5551<4>"); found = true; return address + 4;
}

/* VT5650_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VT5650_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VT5650<4>"); found = true; return address + 4;
}

/* VCST_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCST_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCST<1>"); found = true; return address + 4;
}

/* VCST_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCST_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCST<2>"); found = true; return address + 4;
}

/* VCST_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCST_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCST<3>"); found = true; return address + 4;
}

/* VCST_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCST_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCST<4>"); found = true; return address + 4;
}

/* VF2IN_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IN_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IN<1>"); found = true; return address + 4;
}

/* VF2IN_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IN_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IN<2>"); found = true; return address + 4;
}

/* VF2IN_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IN_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IN<3>"); found = true; return address + 4;
}

/* VF2IN_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IN_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IN<4>"); found = true; return address + 4;
}

/* VF2IZ_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IZ_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IZ<1>"); found = true; return address + 4;
}

/* VF2IZ_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IZ_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IZ<2>"); found = true; return address + 4;
}

/* VF2IZ_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IZ_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IZ<3>"); found = true; return address + 4;
}

/* VF2IZ_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IZ_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IZ<4>"); found = true; return address + 4;
}

/* VF2IU_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IU_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IU<1>"); found = true; return address + 4;
}

/* VF2IU_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IU_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IU<2>"); found = true; return address + 4;
}

/* VF2IU_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IU_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IU<3>"); found = true; return address + 4;
}

/* VF2IU_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2IU_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2IU<4>"); found = true; return address + 4;
}

/* VF2ID_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2ID_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2ID<1>"); found = true; return address + 4;
}

/* VF2ID_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2ID_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2ID<2>"); found = true; return address + 4;
}

/* VF2ID_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2ID_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2ID<3>"); found = true; return address + 4;
}

/* VF2ID_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VF2ID_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VF2ID<4>"); found = true; return address + 4;
}

/* VI2F_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2F_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2F<1>"); found = true; return address + 4;
}

/* VI2F_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2F_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2F<2>"); found = true; return address + 4;
}

/* VI2F_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2F_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2F<3>"); found = true; return address + 4;
}

/* VI2F_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VI2F_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VI2F<4>"); found = true; return address + 4;
}

/* VCMOVT_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMOVT_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMOVT<1>"); found = true; return address + 4;
}

/* VCMOVT_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMOVT_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMOVT<2>"); found = true; return address + 4;
}

/* VCMOVT_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMOVT_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMOVT<3>"); found = true; return address + 4;
}

/* VCMOVT_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMOVT_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMOVT<4>"); found = true; return address + 4;
}

/* VCMOVF_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMOVF_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMOVF<1>"); found = true; return address + 4;
}

/* VCMOVF_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMOVF_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMOVF<2>"); found = true; return address + 4;
}

/* VCMOVF_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMOVF_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMOVF<3>"); found = true; return address + 4;
}

/* VCMOVF_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCMOVF_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCMOVF<4>"); found = true; return address + 4;
}

/* VWBN_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VWBN_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VWBN<1>"); found = true; return address + 4;
}

/* LVL_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LVL_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$LVL_Q"); found = true; return address + 4;
}

/* LVR_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LVR_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$LVR_Q"); found = true; return address + 4;
}

/* LV_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$LV_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$LV_Q"); found = true; return address + 4;
}

/* VPFXS */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VPFXS(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VPFXS"); found = true; return address + 4;
}

/* VPFXT */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VPFXT(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VPFXT"); found = true; return address + 4;
}

/* VPFXD */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VPFXD(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VPFXD"); found = true; return address + 4;
}

/* VIIM */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VIIM(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VIIM"); found = true; return address + 4;
}

/* VFIM */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VFIM(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VFIM"); found = true; return address + 4;
}

/* SC */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SC(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SC"); found = true; return address + 4;
}

/* SWC1 */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SWC1(u32 address, u32 opcode, bool delayslot)
{
    auto FT = Allegrex::Instruction::ft(opcode);
    auto RS = Allegrex::Instruction::rs(opcode);
    auto IMM = Allegrex::Instruction::simm16(opcode);

    auto $ft = fpr_w(FT);
    auto $rs = Gpr(RS);
    auto $rb = NO_REGISTER_ALLOCATION ? rdx : Reg64($rs);

#if !defined(__AVX__)
    movss(xmm0, $ft);
    if (RS)
    {
        gen($rs);
        if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
        movss(dword_ptr[$rb + s32(DCACHE_MEMORY_ADDRESS + IMM)], xmm0);
    }
    else
    {
        movss(dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)], xmm0);
    }
#else
    vmovss(xmm0, $ft);
    if (RS)
    {
        gen($rs);
        if (NO_REGISTER_ALLOCATION) mov(edx, $rs);
        vmovss(dword_ptr[$rb + s32(DCACHE_MEMORY_ADDRESS + IMM)], xmm0);
    }
    else
    {
        vmovss(dword_ptr[s32(DCACHE_MEMORY_ADDRESS + IMM)], xmm0);
    }
#endif
    return address + 4;
}

/* SV_S */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SV_S(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SV_S"); found = true; return address + 4;
}

/* VMMUL_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMMUL_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMMUL<2>"); found = true; return address + 4;
}

/* VMMUL_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMMUL_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMMUL<3>"); found = true; return address + 4;
}

/* VMMUL_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMMUL_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMMUL<4>"); found = true; return address + 4;
}

/* VHTFM2_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VHTFM2_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VHTFM2<1>"); found = true; return address + 4;
}

/* VTFM2_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VTFM2_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VTFM2<2>"); found = true; return address + 4;
}

/* VHTFM3_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VHTFM3_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VHTFM3<2>"); found = true; return address + 4;
}

/* VTFM3_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VTFM3_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VTFM3<3>"); found = true; return address + 4;
}

/* VHTFM4_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VHTFM4_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VHTFM4<3>"); found = true; return address + 4;
}

/* VTFM4_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VTFM4_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VTFM4<4>"); found = true; return address + 4;
}

/* VMSCL_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMSCL_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMSCL<2>"); found = true; return address + 4;
}

/* VMSCL_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMSCL_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMSCL<3>"); found = true; return address + 4;
}

/* VMSCL_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMSCL_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMSCL<4>"); found = true; return address + 4;
}

/* VCRSP_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VCRSP_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VCRSP<3>"); found = true; return address + 4;
}

/* VQMUL_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VQMUL_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VQMUL<4>"); found = true; return address + 4;
}

/* VMMOV_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMMOV_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMMOV<2>"); found = true; return address + 4;
}

/* VMMOV_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMMOV_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMMOV<3>"); found = true; return address + 4;
}

/* VMMOV_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMMOV_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMMOV<4>"); found = true; return address + 4;
}

/* VMIDT_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMIDT_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMIDT<2>"); found = true; return address + 4;
}

/* VMIDT_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMIDT_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMIDT<3>"); found = true; return address + 4;
}

/* VMIDT_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMIDT_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMIDT<4>"); found = true; return address + 4;
}

/* VMZERO_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMZERO_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMZERO<2>"); found = true; return address + 4;
}

/* VMZERO_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMZERO_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMZERO<3>"); found = true; return address + 4;
}

/* VMZERO_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMZERO_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMZERO<4>"); found = true; return address + 4;
}

/* VMONE_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMONE_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMONE<2>"); found = true; return address + 4;
}

/* VMONE_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMONE_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMONE<3>"); found = true; return address + 4;
}

/* VMONE_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VMONE_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VMONE<4>"); found = true; return address + 4;
}

/* VROT_P */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VROT_P(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VROT<2>"); found = true; return address + 4;
}

/* VROT_T */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VROT_T(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VROT<3>"); found = true; return address + 4;
}

/* VROT_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VROT_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VROT<4>"); found = true; return address + 4;
}

/* SVL_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SVL_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SVL_Q"); found = true; return address + 4;
}

/* SVR_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SVR_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SVR_Q"); found = true; return address + 4;
}

/* SV_Q */
__noinline u32 Allegrex::ICache::CodeBlock::emit$SV_Q(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$SV_Q"); found = true; return address + 4;
}

/* VNOP */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VNOP(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VNOP"); found = true; return address + 4;
}

/* VSYNC */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VSYNC(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VSYNC"); found = true; return address + 4;
}

/* VFLUSH */
__noinline u32 Allegrex::ICache::CodeBlock::emit$VFLUSH(u32 address, u32 opcode, bool delayslot)
{
    static bool found = false; if (!found) forcef(emu, "needs emit$VFLUSH"); found = true; return address + 4;
}

