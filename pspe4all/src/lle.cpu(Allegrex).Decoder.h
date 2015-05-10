/*
Binary decoder synthesized by decgen version 4.0.0

Input statistics
Total entries  : 427
Unique labels  : 427
Shannon entropy     : 8.73809
Huffman tree height : 8.80094

Decoder characteristics
Gamma          : 0.5
1 bit only     : 0
Average height : 2.73419
Maximum height : 5
Minimum height : 1
Table entries  : 776
Total nodes    : 289
*/

    switch ((opcode >> 25) & 0x0000007f)
    {
        case 0:
        {
            switch ((opcode >> 0) & 0x0000003f)
            {
                case 0:
                {
                    IDO(SLL);
                    break;
                }
                case 1:
                {
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00200000))
                    {
                        IDO(SRL);
                    }
                    else
                    {
                        IDO(ROTR);
                    }
                    break;
                }
                case 3:
                {
                    IDO(SRA);
                    break;
                }
                case 4:
                {
                    IDO(SLLV);
                    break;
                }
                case 5:
                {
                    break;
                }
                case 6:
                {
                    if (0x00000000 == (opcode & 0x00000040))
                    {
                        IDO(SRLV);
                    }
                    else
                    {
                        IDO(ROTRV);
                    }
                    break;
                }
                case 7:
                {
                    IDO(SRAV);
                    break;
                }
                case 8:
                {
                    IDO(JR);
                    break;
                }
                case 9:
                {
                    IDO(JALR);
                    break;
                }
                case 10:
                {
                    IDO(MOVZ);
                    break;
                }
                case 11:
                {
                    IDO(MOVN);
                    break;
                }
                case 12:
                {
                    IDO(SYSCALL);
                    break;
                }
                case 13:
                {
                    IDO(BREAK);
                    break;
                }
                case 14:
                {
                    break;
                }
                case 15:
                {
                    IDO(SYNC);
                    break;
                }
                case 16:
                {
                    IDO(MFHI);
                    break;
                }
                case 17:
                {
                    IDO(MTHI);
                    break;
                }
                case 18:
                {
                    IDO(MFLO);
                    break;
                }
                case 19:
                {
                    IDO(MTLO);
                    break;
                }
                case 20:
                case 21:
                {
                    break;
                }
                case 22:
                {
                    IDO(CLZ);
                    break;
                }
                case 23:
                {
                    IDO(CLO);
                    break;
                }
                case 24:
                {
                    IDO(MULT);
                    break;
                }
                case 25:
                {
                    IDO(MULTU);
                    break;
                }
                case 26:
                {
                    IDO(DIV);
                    break;
                }
                case 27:
                {
                    IDO(DIVU);
                    break;
                }
                case 28:
                {
                    IDO(MADD);
                    break;
                }
                case 29:
                {
                    IDO(MADDU);
                    break;
                }
                case 30:
                case 31:
                {
                    break;
                }
                case 32:
                {
                    IDO(ADD);
                    break;
                }
                case 33:
                {
                    IDO(ADDU);
                    break;
                }
                case 34:
                {
                    IDO(SUB);
                    break;
                }
                case 35:
                {
                    IDO(SUBU);
                    break;
                }
                case 36:
                {
                    IDO(AND);
                    break;
                }
                case 37:
                {
                    IDO(OR);
                    break;
                }
                case 38:
                {
                    IDO(XOR);
                    break;
                }
                case 39:
                {
                    IDO(NOR);
                    break;
                }
                case 40:
                case 41:
                {
                    break;
                }
                case 42:
                {
                    IDO(SLT);
                    break;
                }
                case 43:
                {
                    IDO(SLTU);
                    break;
                }
                case 44:
                {
                    IDO(MAX);
                    break;
                }
                case 45:
                {
                    IDO(MIN);
                    break;
                }
                case 46:
                {
                    IDO(MSUB);
                    break;
                }
                case 47:
                {
                    IDO(MSUBU);
                    break;
                }
                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                case 56:
                case 57:
                case 58:
                case 59:
                case 60:
                case 61:
                case 62:
                case 63:
                {
                    break;
                }
            }
            break;
        }
        case 1:
        {
            switch ((opcode >> 0) & 0x0000003f)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                {
                    break;
                }
                case 4:
                {
                    IDO(SLLV);
                    break;
                }
                case 5:
                {
                    break;
                }
                case 6:
                {
                    if (0x00000000 == (opcode & 0x00000040))
                    {
                        IDO(SRLV);
                    }
                    else
                    {
                        IDO(ROTRV);
                    }
                    break;
                }
                case 7:
                {
                    IDO(SRAV);
                    break;
                }
                case 8:
                {
                    IDO(JR);
                    break;
                }
                case 9:
                {
                    IDO(JALR);
                    break;
                }
                case 10:
                {
                    IDO(MOVZ);
                    break;
                }
                case 11:
                {
                    IDO(MOVN);
                    break;
                }
                case 12:
                {
                    IDO(SYSCALL);
                    break;
                }
                case 13:
                {
                    IDO(BREAK);
                    break;
                }
                case 14:
                case 15:
                case 16:
                {
                    break;
                }
                case 17:
                {
                    IDO(MTHI);
                    break;
                }
                case 18:
                {
                    break;
                }
                case 19:
                {
                    IDO(MTLO);
                    break;
                }
                case 20:
                case 21:
                {
                    break;
                }
                case 22:
                {
                    IDO(CLZ);
                    break;
                }
                case 23:
                {
                    IDO(CLO);
                    break;
                }
                case 24:
                {
                    IDO(MULT);
                    break;
                }
                case 25:
                {
                    IDO(MULTU);
                    break;
                }
                case 26:
                {
                    IDO(DIV);
                    break;
                }
                case 27:
                {
                    IDO(DIVU);
                    break;
                }
                case 28:
                {
                    IDO(MADD);
                    break;
                }
                case 29:
                {
                    IDO(MADDU);
                    break;
                }
                case 30:
                case 31:
                {
                    break;
                }
                case 32:
                {
                    IDO(ADD);
                    break;
                }
                case 33:
                {
                    IDO(ADDU);
                    break;
                }
                case 34:
                {
                    IDO(SUB);
                    break;
                }
                case 35:
                {
                    IDO(SUBU);
                    break;
                }
                case 36:
                {
                    IDO(AND);
                    break;
                }
                case 37:
                {
                    IDO(OR);
                    break;
                }
                case 38:
                {
                    IDO(XOR);
                    break;
                }
                case 39:
                {
                    IDO(NOR);
                    break;
                }
                case 40:
                case 41:
                {
                    break;
                }
                case 42:
                {
                    IDO(SLT);
                    break;
                }
                case 43:
                {
                    IDO(SLTU);
                    break;
                }
                case 44:
                {
                    IDO(MAX);
                    break;
                }
                case 45:
                {
                    IDO(MIN);
                    break;
                }
                case 46:
                {
                    IDO(MSUB);
                    break;
                }
                case 47:
                {
                    IDO(MSUBU);
                    break;
                }
                case 48:
                case 49:
                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                case 56:
                case 57:
                case 58:
                case 59:
                case 60:
                case 61:
                case 62:
                case 63:
                {
                    break;
                }
            }
            break;
        }
        case 2:
        case 3:
        {
            switch ((opcode >> 16) & 0x00000003)
            {
                case 0:
                {
                    if (0x00000000 == (opcode & 0x00100000))
                    {
                        IDO(BLTZ);
                    }
                    else
                    {
                        IDO(BLTZAL);
                    }
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00100000))
                    {
                        IDO(BGEZ);
                    }
                    else
                    {
                        IDO(BGEZAL);
                    }
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00100000))
                    {
                        IDO(BLTZL);
                    }
                    else
                    {
                        IDO(BLTZALL);
                    }
                    break;
                }
                case 3:
                {
                    if (0x00000000 == (opcode & 0x00100000))
                    {
                        IDO(BGEZL);
                    }
                    else
                    {
                        IDO(BGEZALL);
                    }
                    break;
                }
            }
            break;
        }
        case 4:
        case 5:
        {
            IDO(J);
            break;
        }
        case 6:
        case 7:
        {
            IDO(JAL);
            break;
        }
        case 8:
        case 9:
        {
            IDO(BEQ);
            break;
        }
        case 10:
        case 11:
        {
            IDO(BNE);
            break;
        }
        case 12:
        case 13:
        {
            IDO(BLEZ);
            break;
        }
        case 14:
        case 15:
        {
            IDO(BGTZ);
            break;
        }
        case 16:
        case 17:
        {
            IDO(ADDI);
            break;
        }
        case 18:
        case 19:
        {
            IDO(ADDIU);
            break;
        }
        case 20:
        case 21:
        {
            IDO(SLTI);
            break;
        }
        case 22:
        case 23:
        {
            IDO(SLTIU);
            break;
        }
        case 24:
        case 25:
        {
            IDO(ANDI);
            break;
        }
        case 26:
        case 27:
        {
            IDO(ORI);
            break;
        }
        case 28:
        case 29:
        {
            IDO(XORI);
            break;
        }
        case 30:
        {
            IDO(LUI);
            break;
        }
        case 31:
        {
            break;
        }
        case 32:
        {
            switch ((opcode >> 22) & 0x00000003)
            {
                case 0:
                {
                    IDO(MFC0);
                    break;
                }
                case 1:
                {
                    IDO(CFC0);
                    break;
                }
                case 2:
                {
                    IDO(MTC0);
                    break;
                }
                case 3:
                {
                    IDO(CTC0);
                    break;
                }
            }
            break;
        }
        case 33:
        {
            IDO(ERET);
            break;
        }
        case 34:
        {
            switch ((opcode >> 22) & 0x00000007)
            {
                case 0:
                {
                    IDO(MFC1);
                    break;
                }
                case 1:
                {
                    IDO(CFC1);
                    break;
                }
                case 2:
                {
                    IDO(MTC1);
                    break;
                }
                case 3:
                {
                    IDO(CTC1);
                    break;
                }
                case 4:
                {
                    switch ((opcode >> 16) & 0x00000003)
                    {
                        case 0:
                        {
                            IDO(BC1F);
                            break;
                        }
                        case 1:
                        {
                            IDO(BC1T);
                            break;
                        }
                        case 2:
                        {
                            IDO(BC1FL);
                            break;
                        }
                        case 3:
                        {
                            IDO(BC1TL);
                            break;
                        }
                    }
                    break;
                }
                case 5:
                case 6:
                case 7:
                {
                    break;
                }
            }
            break;
        }
        case 35:
        {
            switch ((opcode >> 0) & 0x0000001f)
            {
                case 0:
                {
                    if (0x00000000 == (opcode & 0x00000020))
                    {
                        IDO(ADD_S);
                    }
                    else
                    {
                        IDO(CVT_S_W);
                    }
                    break;
                }
                case 1:
                {
                    IDO(SUB_S);
                    break;
                }
                case 2:
                {
                    IDO(MUL_S);
                    break;
                }
                case 3:
                {
                    IDO(DIV_S);
                    break;
                }
                case 4:
                {
                    if (0x00000000 == (opcode & 0x00000020))
                    {
                        IDO(SQRT_S);
                    }
                    else
                    {
                        IDO(CVT_W_S);
                    }
                    break;
                }
                case 5:
                {
                    IDO(ABS_S);
                    break;
                }
                case 6:
                {
                    IDO(MOV_S);
                    break;
                }
                case 7:
                {
                    IDO(NEG_S);
                    break;
                }
                case 8:
                case 9:
                case 10:
                case 11:
                {
                    break;
                }
                case 12:
                {
                    IDO(ROUND_W_S);
                    break;
                }
                case 13:
                {
                    IDO(TRUNC_W_S);
                    break;
                }
                case 14:
                {
                    IDO(CEIL_W_S);
                    break;
                }
                case 15:
                {
                    IDO(FLOOR_W_S);
                    break;
                }
                case 16:
                {
                    IDO(C_F_S);
                    break;
                }
                case 17:
                {
                    IDO(C_UN_S);
                    break;
                }
                case 18:
                {
                    IDO(C_EQ_S);
                    break;
                }
                case 19:
                {
                    IDO(C_UEQ_S);
                    break;
                }
                case 20:
                {
                    IDO(C_OLT_S);
                    break;
                }
                case 21:
                {
                    IDO(C_ULT_S);
                    break;
                }
                case 22:
                {
                    IDO(C_OLE_S);
                    break;
                }
                case 23:
                {
                    IDO(C_ULE_S);
                    break;
                }
                case 24:
                {
                    IDO(C_SF_S);
                    break;
                }
                case 25:
                {
                    IDO(C_NGLE_S);
                    break;
                }
                case 26:
                {
                    IDO(C_SEQ_S);
                    break;
                }
                case 27:
                {
                    IDO(C_NGL_S);
                    break;
                }
                case 28:
                {
                    IDO(C_LT_S);
                    break;
                }
                case 29:
                {
                    IDO(C_NGE_S);
                    break;
                }
                case 30:
                {
                    IDO(C_LE_S);
                    break;
                }
                case 31:
                {
                    IDO(C_NGT_S);
                    break;
                }
            }
            break;
        }
        case 36:
        {
            switch ((opcode >> 22) & 0x00000003)
            {
                case 0:
                {
                    switch ((opcode >> 16) & 0x00000003)
                    {
                        case 0:
                        {
                            IDO(BVF);
                            break;
                        }
                        case 1:
                        {
                            IDO(BVT);
                            break;
                        }
                        case 2:
                        {
                            IDO(BVFL);
                            break;
                        }
                        case 3:
                        {
                            IDO(BVTL);
                            break;
                        }
                    }
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(MFV);
                    }
                    else
                    {
                        IDO(MFVC);
                    }
                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(MTV);
                    }
                    else
                    {
                        IDO(MTVC);
                    }
                    break;
                }
            }
            break;
        }
        case 37:
        case 38:
        case 39:
        {
            break;
        }
        case 40:
        case 41:
        {
            IDO(BEQL);
            break;
        }
        case 42:
        case 43:
        {
            IDO(BNEL);
            break;
        }
        case 44:
        case 45:
        {
            IDO(BLEZL);
            break;
        }
        case 46:
        case 47:
        {
            IDO(BGTZL);
            break;
        }
        case 48:
        {
            switch ((opcode >> 23) & 0x00000003)
            {
                case 0:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VADD_S);
                        }
                        else
                        {
                            IDO(VADD_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VADD_P);
                        }
                        else
                        {
                            IDO(VADD_Q);
                        }
                    }
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VSUB_S);
                        }
                        else
                        {
                            IDO(VSUB_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VSUB_P);
                        }
                        else
                        {
                            IDO(VSUB_Q);
                        }
                    }
                    break;
                }
                case 2:
                {
                    IDO(VSBN_S);
                    break;
                }
                case 3:
                {
                    break;
                }
            }
            break;
        }
        case 49:
        {
            if (0x00000000 == (opcode & 0x00000080))
            {
                if (0x00000000 == (opcode & 0x00008000))
                {
                    IDO(VDIV_S);
                }
                else
                {
                    IDO(VDIV_T);
                }
            }
            else
            {
                if (0x00000000 == (opcode & 0x00008000))
                {
                    IDO(VDIV_P);
                }
                else
                {
                    IDO(VDIV_Q);
                }
            }
            break;
        }
        case 50:
        {
            switch ((opcode >> 23) & 0x00000003)
            {
                case 0:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VMUL_S);
                        }
                        else
                        {
                            IDO(VMUL_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VMUL_P);
                        }
                        else
                        {
                            IDO(VMUL_Q);
                        }
                    }
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VDOT_T);
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VDOT_P);
                        }
                        else
                        {
                            IDO(VDOT_Q);
                        }
                    }
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSCL_T);
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VSCL_P);
                        }
                        else
                        {
                            IDO(VSCL_Q);
                        }
                    }
                    break;
                }
                case 3:
                {
                    break;
                }
            }
            break;
        }
        case 51:
        {
            if (0x00000000 == (opcode & 0x00000080))
            {
                if (0x00000000 == (opcode & 0x00800000))
                {
                    IDO(VHDP_T);
                }
                else
                {
                    IDO(VCRS_T);
                }
            }
            else
            {
                if (0x00000000 == (opcode & 0x00008000))
                {
                    if (0x00000000 == (opcode & 0x01000000))
                    {
                        IDO(VHDP_P);
                    }
                    else
                    {
                        IDO(VDET_P);
                    }
                }
                else
                {
                    IDO(VHDP_Q);
                }
            }
            break;
        }
        case 52:
        case 53:
        {
            break;
        }
        case 54:
        {
            switch ((opcode >> 23) & 0x00000003)
            {
                case 0:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VCMP_S);
                        }
                        else
                        {
                            IDO(VCMP_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VCMP_P);
                        }
                        else
                        {
                            IDO(VCMP_Q);
                        }
                    }
                    break;
                }
                case 1:
                {
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VMIN_S);
                        }
                        else
                        {
                            IDO(VMIN_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VMIN_P);
                        }
                        else
                        {
                            IDO(VMIN_Q);
                        }
                    }
                    break;
                }
                case 3:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VMAX_S);
                        }
                        else
                        {
                            IDO(VMAX_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VMAX_P);
                        }
                        else
                        {
                            IDO(VMAX_Q);
                        }
                    }
                    break;
                }
            }
            break;
        }
        case 55:
        {
            switch ((opcode >> 23) & 0x00000003)
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VSCMP_S);
                        }
                        else
                        {
                            IDO(VSCMP_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VSCMP_P);
                        }
                        else
                        {
                            IDO(VSCMP_Q);
                        }
                    }
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VSGE_S);
                        }
                        else
                        {
                            IDO(VSGE_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VSGE_P);
                        }
                        else
                        {
                            IDO(VSGE_Q);
                        }
                    }
                    break;
                }
                case 3:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VSLT_S);
                        }
                        else
                        {
                            IDO(VSLT_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VSLT_P);
                        }
                        else
                        {
                            IDO(VSLT_Q);
                        }
                    }
                    break;
                }
            }
            break;
        }
        case 56:
        {
            switch ((opcode >> 0) & 0x00000007)
            {
                case 0:
                {
                    IDO(HALT);
                    break;
                }
                case 1:
                case 2:
                case 3:
                {
                    break;
                }
                case 4:
                {
                    IDO(MFIC);
                    break;
                }
                case 5:
                {
                    if (0x00000000 == (opcode & 0x00800000))
                    {
                        IDO(MFDR);
                    }
                    else
                    {
                        IDO(MTDR);
                    }
                    break;
                }
                case 6:
                {
                    if (0x00000000 == (opcode & 0x00000008))
                    {
                        IDO(MTIC);
                    }
                    else
                    {
                        IDO(DRET);
                    }
                    break;
                }
                case 7:
                {
                    IDO(DBREAK);
                    break;
                }
            }
            break;
        }
        case 57:
        {
            switch ((opcode >> 0) & 0x00000003)
            {
                case 0:
                {
                    IDO(MFIC);
                    break;
                }
                case 1:
                {
                    break;
                }
                case 2:
                {
                    IDO(MTIC);
                    break;
                }
                case 3:
                {
                    IDO(DBREAK);
                    break;
                }
            }
            break;
        }
        case 58:
        case 59:
        case 60:
        case 61:
        {
            break;
        }
        case 62:
        {
            switch ((opcode >> 5) & 0x0000000f)
            {
                case 0:
                {
                    if (0x00000000 == (opcode & 0x00000004))
                    {
                        IDO(EXT);
                    }
                    else
                    {
                        IDO(INS);
                    }
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00000200))
                    {
                        IDO(SEB);
                    }
                    else
                    {
                        IDO(SEH);
                    }
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00000004))
                    {
                        IDO(EXT);
                    }
                    else
                    {
                        IDO(INS);
                    }
                    break;
                }
                case 3:
                {
                    break;
                }
                case 4:
                {
                    if (0x00000000 == (opcode & 0x00000004))
                    {
                        IDO(EXT);
                    }
                    else
                    {
                        IDO(INS);
                    }
                    break;
                }
                case 5:
                {
                    IDO(WSBH);
                    break;
                }
                case 6:
                {
                    if (0x00000000 == (opcode & 0x00000004))
                    {
                        IDO(EXT);
                    }
                    else
                    {
                        IDO(INS);
                    }
                    break;
                }
                case 7:
                {
                    IDO(WSBW);
                    break;
                }
                case 8:
                {
                    if (0x00000000 == (opcode & 0x00000004))
                    {
                        IDO(EXT);
                    }
                    else
                    {
                        IDO(INS);
                    }
                    break;
                }
                case 9:
                {
                    IDO(BITREV);
                    break;
                }
                case 10:
                {
                    if (0x00000000 == (opcode & 0x00000004))
                    {
                        IDO(EXT);
                    }
                    else
                    {
                        IDO(INS);
                    }
                    break;
                }
                case 11:
                {
                    break;
                }
                case 12:
                {
                    if (0x00000000 == (opcode & 0x00000004))
                    {
                        IDO(EXT);
                    }
                    else
                    {
                        IDO(INS);
                    }
                    break;
                }
                case 13:
                {
                    break;
                }
                case 14:
                {
                    if (0x00000000 == (opcode & 0x00000004))
                    {
                        IDO(EXT);
                    }
                    else
                    {
                        IDO(INS);
                    }
                    break;
                }
                case 15:
                {
                    break;
                }
            }
            break;
        }
        case 63:
        {
            if (0x00000000 == (opcode & 0x00000004))
            {
                IDO(EXT);
            }
            else
            {
                IDO(INS);
            }
            break;
        }
        case 64:
        case 65:
        {
            IDO(LB);
            break;
        }
        case 66:
        case 67:
        {
            IDO(LH);
            break;
        }
        case 68:
        case 69:
        {
            IDO(LWL);
            break;
        }
        case 70:
        case 71:
        {
            IDO(LW);
            break;
        }
        case 72:
        case 73:
        {
            IDO(LBU);
            break;
        }
        case 74:
        case 75:
        {
            IDO(LHU);
            break;
        }
        case 76:
        case 77:
        {
            IDO(LWR);
            break;
        }
        case 78:
        case 79:
        {
            break;
        }
        case 80:
        case 81:
        {
            IDO(SB);
            break;
        }
        case 82:
        case 83:
        {
            IDO(SH);
            break;
        }
        case 84:
        case 85:
        {
            IDO(SWL);
            break;
        }
        case 86:
        case 87:
        {
            IDO(SW);
            break;
        }
        case 88:
        case 89:
        case 90:
        case 91:
        {
            break;
        }
        case 92:
        case 93:
        {
            IDO(SWR);
            break;
        }
        case 94:
        case 95:
        {
            switch ((opcode >> 16) & 0x0000001f)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                {
                    break;
                }
                case 4:
                {
                    IDO(ICACHE_INDEX_INVALIDATE);
                    break;
                }
                case 5:
                {
                    break;
                }
                case 6:
                {
                    IDO(ICACHE_INDEX_UNLOCK);
                    break;
                }
                case 7:
                {
                    break;
                }
                case 8:
                {
                    IDO(ICACHE_HIT_INVALIDATE);
                    break;
                }
                case 9:
                {
                    break;
                }
                case 10:
                {
                    IDO(ICACHE_FILL);
                    break;
                }
                case 11:
                {
                    IDO(ICACHE_FILL_WITH_LOCK);
                    break;
                }
                case 12:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                {
                    break;
                }
                case 20:
                {
                    IDO(DCACHE_INDEX_WRITEBACK_INVALIDATE);
                    break;
                }
                case 21:
                {
                    break;
                }
                case 22:
                {
                    IDO(DCACHE_INDEX_UNLOCK);
                    break;
                }
                case 23:
                {
                    break;
                }
                case 24:
                {
                    IDO(DCACHE_CREATE_DIRTY_EXCLUSIVE);
                    break;
                }
                case 25:
                {
                    IDO(DCACHE_HIT_INVALIDATE);
                    break;
                }
                case 26:
                {
                    IDO(DCACHE_HIT_WRITEBACK);
                    break;
                }
                case 27:
                {
                    IDO(DCACHE_HIT_WRITEBACK_INVALIDATE);
                    break;
                }
                case 28:
                {
                    IDO(DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK);
                    break;
                }
                case 29:
                {
                    break;
                }
                case 30:
                {
                    IDO(DCACHE_FILL);
                    break;
                }
                case 31:
                {
                    IDO(DCACHE_FILL_WITH_LOCK);
                    break;
                }
            }
            break;
        }
        case 96:
        case 97:
        {
            IDO(LL);
            break;
        }
        case 98:
        case 99:
        {
            IDO(LWC1);
            break;
        }
        case 100:
        case 101:
        {
            IDO(LV_S);
            break;
        }
        case 102:
        case 103:
        {
            break;
        }
        case 104:
        {
            switch ((opcode >> 15) & 0x000000ff)
            {
                case 0:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VMOV_S);
                    }
                    else
                    {
                        IDO(VMOV_P);
                    }
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VMOV_T);
                    }
                    else
                    {
                        IDO(VMOV_Q);
                    }
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VABS_S);
                    }
                    else
                    {
                        IDO(VABS_P);
                    }
                    break;
                }
                case 3:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VABS_T);
                    }
                    else
                    {
                        IDO(VABS_Q);
                    }
                    break;
                }
                case 4:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VNEG_S);
                    }
                    else
                    {
                        IDO(VNEG_P);
                    }
                    break;
                }
                case 5:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VNEG_T);
                    }
                    else
                    {
                        IDO(VNEG_Q);
                    }
                    break;
                }
                case 6:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VIDT_S);
                    }
                    else
                    {
                        IDO(VIDT_P);
                    }
                    break;
                }
                case 7:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VIDT_T);
                    }
                    else
                    {
                        IDO(VIDT_Q);
                    }
                    break;
                }
                case 8:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSAT0_S);
                    }
                    else
                    {
                        IDO(VSAT0_P);
                    }
                    break;
                }
                case 9:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSAT0_T);
                    }
                    else
                    {
                        IDO(VSAT0_Q);
                    }
                    break;
                }
                case 10:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSAT1_S);
                    }
                    else
                    {
                        IDO(VSAT1_P);
                    }
                    break;
                }
                case 11:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSAT1_T);
                    }
                    else
                    {
                        IDO(VSAT1_Q);
                    }
                    break;
                }
                case 12:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VZERO_S);
                    }
                    else
                    {
                        IDO(VZERO_P);
                    }
                    break;
                }
                case 13:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VZERO_T);
                    }
                    else
                    {
                        IDO(VZERO_Q);
                    }
                    break;
                }
                case 14:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VONE_S);
                    }
                    else
                    {
                        IDO(VONE_P);
                    }
                    break;
                }
                case 15:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VONE_T);
                    }
                    else
                    {
                        IDO(VONE_Q);
                    }
                    break;
                }
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                case 29:
                case 30:
                case 31:
                {
                    break;
                }
                case 32:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRCP_S);
                    }
                    else
                    {
                        IDO(VRCP_P);
                    }
                    break;
                }
                case 33:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRCP_T);
                    }
                    else
                    {
                        IDO(VRCP_Q);
                    }
                    break;
                }
                case 34:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRSQ_S);
                    }
                    else
                    {
                        IDO(VRSQ_P);
                    }
                    break;
                }
                case 35:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRSQ_T);
                    }
                    else
                    {
                        IDO(VRSQ_Q);
                    }
                    break;
                }
                case 36:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSIN_S);
                    }
                    else
                    {
                        IDO(VSIN_P);
                    }
                    break;
                }
                case 37:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSIN_T);
                    }
                    else
                    {
                        IDO(VSIN_Q);
                    }
                    break;
                }
                case 38:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCOS_S);
                    }
                    else
                    {
                        IDO(VCOS_P);
                    }
                    break;
                }
                case 39:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCOS_T);
                    }
                    else
                    {
                        IDO(VCOS_Q);
                    }
                    break;
                }
                case 40:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VEXP2_S);
                    }
                    else
                    {
                        IDO(VEXP2_P);
                    }
                    break;
                }
                case 41:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VEXP2_T);
                    }
                    else
                    {
                        IDO(VEXP2_Q);
                    }
                    break;
                }
                case 42:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VLOG2_S);
                    }
                    else
                    {
                        IDO(VLOG2_P);
                    }
                    break;
                }
                case 43:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VLOG2_T);
                    }
                    else
                    {
                        IDO(VLOG2_Q);
                    }
                    break;
                }
                case 44:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSQRT_S);
                    }
                    else
                    {
                        IDO(VSQRT_P);
                    }
                    break;
                }
                case 45:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSQRT_T);
                    }
                    else
                    {
                        IDO(VSQRT_Q);
                    }
                    break;
                }
                case 46:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VASIN_S);
                    }
                    else
                    {
                        IDO(VASIN_P);
                    }
                    break;
                }
                case 47:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VASIN_T);
                    }
                    else
                    {
                        IDO(VASIN_Q);
                    }
                    break;
                }
                case 48:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VNRCP_S);
                    }
                    else
                    {
                        IDO(VNRCP_P);
                    }
                    break;
                }
                case 49:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VNRCP_T);
                    }
                    else
                    {
                        IDO(VNRCP_Q);
                    }
                    break;
                }
                case 50:
                case 51:
                {
                    break;
                }
                case 52:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VNSIN_S);
                    }
                    else
                    {
                        IDO(VNSIN_P);
                    }
                    break;
                }
                case 53:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VNSIN_T);
                    }
                    else
                    {
                        IDO(VNSIN_Q);
                    }
                    break;
                }
                case 54:
                case 55:
                {
                    break;
                }
                case 56:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VREXP2_S);
                    }
                    else
                    {
                        IDO(VREXP2_P);
                    }
                    break;
                }
                case 57:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VREXP2_T);
                    }
                    else
                    {
                        IDO(VREXP2_Q);
                    }
                    break;
                }
                case 58:
                case 59:
                case 60:
                case 61:
                case 62:
                case 63:
                {
                    break;
                }
                case 64:
                {
                    IDO(VRNDS_S);
                    break;
                }
                case 65:
                {
                    break;
                }
                case 66:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRNDI_S);
                    }
                    else
                    {
                        IDO(VRNDI_P);
                    }
                    break;
                }
                case 67:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRNDI_T);
                    }
                    else
                    {
                        IDO(VRNDI_Q);
                    }
                    break;
                }
                case 68:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRNDF1_S);
                    }
                    else
                    {
                        IDO(VRNDF1_P);
                    }
                    break;
                }
                case 69:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRNDF1_T);
                    }
                    else
                    {
                        IDO(VRNDF1_Q);
                    }
                    break;
                }
                case 70:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRNDF2_S);
                    }
                    else
                    {
                        IDO(VRNDF2_P);
                    }
                    break;
                }
                case 71:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VRNDF2_T);
                    }
                    else
                    {
                        IDO(VRNDF2_Q);
                    }
                    break;
                }
                case 72:
                case 73:
                case 74:
                case 75:
                case 76:
                case 77:
                case 78:
                case 79:
                case 80:
                case 81:
                case 82:
                case 83:
                case 84:
                case 85:
                case 86:
                case 87:
                case 88:
                case 89:
                case 90:
                case 91:
                case 92:
                case 93:
                case 94:
                case 95:
                case 96:
                case 97:
                case 98:
                case 99:
                {
                    break;
                }
                case 100:
                {
                    IDO(VF2H_P);
                    break;
                }
                case 101:
                {
                    IDO(VF2H_Q);
                    break;
                }
                case 102:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VH2F_S);
                    }
                    else
                    {
                        IDO(VH2F_P);
                    }
                    break;
                }
                case 103:
                case 104:
                case 105:
                case 106:
                case 107:
                {
                    break;
                }
                case 108:
                {
                    IDO(VSBZ_S);
                    break;
                }
                case 109:
                {
                    break;
                }
                case 110:
                {
                    IDO(VLGB_S);
                    break;
                }
                case 111:
                {
                    break;
                }
                case 112:
                {
                    IDO(VUC2I_S);
                    break;
                }
                case 113:
                {
                    break;
                }
                case 114:
                {
                    IDO(VC2I_S);
                    break;
                }
                case 115:
                {
                    break;
                }
                case 116:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VUS2I_S);
                    }
                    else
                    {
                        IDO(VUS2I_P);
                    }
                    break;
                }
                case 117:
                {
                    break;
                }
                case 118:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VS2I_S);
                    }
                    else
                    {
                        IDO(VS2I_P);
                    }
                    break;
                }
                case 119:
                case 120:
                {
                    break;
                }
                case 121:
                {
                    IDO(VI2UC_Q);
                    break;
                }
                case 122:
                {
                    break;
                }
                case 123:
                {
                    IDO(VI2C_Q);
                    break;
                }
                case 124:
                {
                    IDO(VI2US_P);
                    break;
                }
                case 125:
                {
                    IDO(VI2US_Q);
                    break;
                }
                case 126:
                {
                    IDO(VI2S_P);
                    break;
                }
                case 127:
                {
                    IDO(VI2S_Q);
                    break;
                }
                case 128:
                {
                    break;
                }
                case 129:
                {
                    IDO(VSRT1_Q);
                    break;
                }
                case 130:
                {
                    break;
                }
                case 131:
                {
                    IDO(VSRT2_Q);
                    break;
                }
                case 132:
                {
                    IDO(VBFY1_P);
                    break;
                }
                case 133:
                {
                    IDO(VBFY1_Q);
                    break;
                }
                case 134:
                {
                    break;
                }
                case 135:
                {
                    IDO(VBFY2_Q);
                    break;
                }
                case 136:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VOCP_S);
                    }
                    else
                    {
                        IDO(VOCP_P);
                    }
                    break;
                }
                case 137:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VOCP_T);
                    }
                    else
                    {
                        IDO(VOCP_Q);
                    }
                    break;
                }
                case 138:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSOCP_S);
                    }
                    else
                    {
                        IDO(VSOCP_P);
                    }
                    break;
                }
                case 139:
                {
                    break;
                }
                case 140:
                {
                    IDO(VFAD_P);
                    break;
                }
                case 141:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VFAD_T);
                    }
                    else
                    {
                        IDO(VFAD_Q);
                    }
                    break;
                }
                case 142:
                {
                    IDO(VAVG_P);
                    break;
                }
                case 143:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VAVG_T);
                    }
                    else
                    {
                        IDO(VAVG_Q);
                    }
                    break;
                }
                case 144:
                {
                    break;
                }
                case 145:
                {
                    IDO(VSRT3_Q);
                    break;
                }
                case 146:
                {
                    break;
                }
                case 147:
                {
                    IDO(VSRT4_Q);
                    break;
                }
                case 148:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSGN_S);
                    }
                    else
                    {
                        IDO(VSGN_P);
                    }
                    break;
                }
                case 149:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VSGN_T);
                    }
                    else
                    {
                        IDO(VSGN_Q);
                    }
                    break;
                }
                case 150:
                case 151:
                case 152:
                case 153:
                case 154:
                case 155:
                case 156:
                case 157:
                case 158:
                case 159:
                case 160:
                {
                    break;
                }
                case 161:
                {
                    IDO(VMFVC);
                    break;
                }
                case 162:
                {
                    IDO(VMTVC);
                    break;
                }
                case 163:
                case 164:
                case 165:
                case 166:
                case 167:
                case 168:
                case 169:
                case 170:
                case 171:
                case 172:
                case 173:
                case 174:
                case 175:
                case 176:
                case 177:
                case 178:
                {
                    break;
                }
                case 179:
                {
                    IDO(VT4444_Q);
                    break;
                }
                case 180:
                {
                    break;
                }
                case 181:
                {
                    IDO(VT5551_Q);
                    break;
                }
                case 182:
                {
                    break;
                }
                case 183:
                {
                    IDO(VT5650_Q);
                    break;
                }
                case 184:
                case 185:
                case 186:
                case 187:
                case 188:
                case 189:
                case 190:
                case 191:
                {
                    break;
                }
                case 192:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 193:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 194:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 195:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 196:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 197:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 198:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 199:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 200:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 201:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 202:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 203:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 204:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 205:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 206:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 207:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 208:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 209:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 210:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 211:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 212:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 213:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 214:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 215:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 216:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 217:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 218:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 219:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 220:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 221:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 222:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 223:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 224:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 225:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 226:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 227:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 228:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 229:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 230:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 231:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 232:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 233:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 234:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 235:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 236:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 237:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 238:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 239:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 240:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 241:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 242:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 243:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 244:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 245:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 246:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 247:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 248:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 249:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 250:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 251:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 252:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 253:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
                case 254:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_S);
                    }
                    else
                    {
                        IDO(VCST_P);
                    }
                    break;
                }
                case 255:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VCST_T);
                    }
                    else
                    {
                        IDO(VCST_Q);
                    }
                    break;
                }
            }
            break;
        }
        case 105:
        {
            switch ((opcode >> 21) & 0x0000000f)
            {
                case 0:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VF2IN_S);
                        }
                        else
                        {
                            IDO(VF2IN_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VF2IN_P);
                        }
                        else
                        {
                            IDO(VF2IN_Q);
                        }
                    }
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VF2IZ_S);
                        }
                        else
                        {
                            IDO(VF2IZ_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VF2IZ_P);
                        }
                        else
                        {
                            IDO(VF2IZ_Q);
                        }
                    }
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VF2IU_S);
                        }
                        else
                        {
                            IDO(VF2IU_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VF2IU_P);
                        }
                        else
                        {
                            IDO(VF2IU_Q);
                        }
                    }
                    break;
                }
                case 3:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VF2ID_S);
                        }
                        else
                        {
                            IDO(VF2ID_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VF2ID_P);
                        }
                        else
                        {
                            IDO(VF2ID_Q);
                        }
                    }
                    break;
                }
                case 4:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VI2F_S);
                        }
                        else
                        {
                            IDO(VI2F_T);
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VI2F_P);
                        }
                        else
                        {
                            IDO(VI2F_Q);
                        }
                    }
                    break;
                }
                case 5:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            if (0x00000000 == (opcode & 0x00080000))
                            {
                                IDO(VCMOVT_S);
                            }
                            else
                            {
                                IDO(VCMOVF_S);
                            }
                        }
                        else
                        {
                            if (0x00000000 == (opcode & 0x00080000))
                            {
                                IDO(VCMOVT_T);
                            }
                            else
                            {
                                IDO(VCMOVF_T);
                            }
                        }
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            if (0x00000000 == (opcode & 0x00080000))
                            {
                                IDO(VCMOVT_P);
                            }
                            else
                            {
                                IDO(VCMOVF_P);
                            }
                        }
                        else
                        {
                            if (0x00000000 == (opcode & 0x00080000))
                            {
                                IDO(VCMOVT_Q);
                            }
                            else
                            {
                                IDO(VCMOVF_Q);
                            }
                        }
                    }
                    break;
                }
                case 6:
                case 7:
                {
                    break;
                }
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                case 14:
                case 15:
                {
                    IDO(VWBN_S);
                    break;
                }
            }
            break;
        }
        case 106:
        case 107:
        {
            if (0x00000000 == (opcode & 0x00000002))
            {
                IDO(LVL_Q);
            }
            else
            {
                IDO(LVR_Q);
            }
            break;
        }
        case 108:
        case 109:
        {
            IDO(LV_Q);
            break;
        }
        case 110:
        {
            if (0x00000000 == (opcode & 0x01000000))
            {
                IDO(VPFXS);
            }
            else
            {
                IDO(VPFXT);
            }
            break;
        }
        case 111:
        {
            switch ((opcode >> 23) & 0x00000003)
            {
                case 0:
                case 1:
                {
                    IDO(VPFXD);
                    break;
                }
                case 2:
                {
                    IDO(VIIM);
                    break;
                }
                case 3:
                {
                    IDO(VFIM);
                    break;
                }
            }
            break;
        }
        case 112:
        case 113:
        {
            IDO(SC);
            break;
        }
        case 114:
        case 115:
        {
            IDO(SWC1);
            break;
        }
        case 116:
        case 117:
        {
            IDO(SV_S);
            break;
        }
        case 118:
        case 119:
        {
            break;
        }
        case 120:
        {
            switch ((opcode >> 23) & 0x00000003)
            {
                case 0:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VMMUL_T);
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00008000))
                        {
                            IDO(VMMUL_P);
                        }
                        else
                        {
                            IDO(VMMUL_Q);
                        }
                    }
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VHTFM2_P);
                    }
                    else
                    {
                        IDO(VTFM2_P);
                    }
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VTFM3_T);
                    }
                    else
                    {
                        IDO(VHTFM3_T);
                    }
                    break;
                }
                case 3:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        IDO(VHTFM4_Q);
                    }
                    else
                    {
                        IDO(VTFM4_Q);
                    }
                    break;
                }
            }
            break;
        }
        case 121:
        {
            switch ((opcode >> 15) & 0x0000000f)
            {
                case 0:
                {
                    if (0x00800000 == (opcode & 0x00a00000))
                    {
                        IDO(VMMOV_P);
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00800000))
                        {
                            IDO(VMSCL_P);
                        }
                        else
                        {
                            IDO(VROT_P);
                        }
                    }
                    break;
                }
                case 1:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x01000000 == (opcode & 0x01200000))
                        {
                            IDO(VMMOV_T);
                        }
                        else
                        {
                            switch ((opcode >> 23) & 0x00000003)
                            {
                                case 0:
                                {
                                    IDO(VMSCL_T);
                                    break;
                                }
                                case 1:
                                {
                                    IDO(VCRSP_T);
                                    break;
                                }
                                case 2:
                                {
                                    break;
                                }
                                case 3:
                                {
                                    IDO(VROT_T);
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (0x01000000 == (opcode & 0x01200000))
                        {
                            IDO(VMMOV_Q);
                        }
                        else
                        {
                            switch ((opcode >> 23) & 0x00000003)
                            {
                                case 0:
                                {
                                    IDO(VMSCL_Q);
                                    break;
                                }
                                case 1:
                                {
                                    IDO(VQMUL_Q);
                                    break;
                                }
                                case 2:
                                {
                                    break;
                                }
                                case 3:
                                {
                                    IDO(VROT_Q);
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
                case 2:
                {
                    if (0x00000000 == (opcode & 0x00800000))
                    {
                        IDO(VMSCL_P);
                    }
                    else
                    {
                        IDO(VROT_P);
                    }
                    break;
                }
                case 3:
                {
                    switch ((opcode >> 23) & 0x00000003)
                    {
                        case 0:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VMSCL_T);
                            }
                            else
                            {
                                IDO(VMSCL_Q);
                            }
                            break;
                        }
                        case 1:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VCRSP_T);
                            }
                            else
                            {
                                IDO(VQMUL_Q);
                            }
                            break;
                        }
                        case 2:
                        {
                            break;
                        }
                        case 3:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VROT_T);
                            }
                            else
                            {
                                IDO(VROT_Q);
                            }
                            break;
                        }
                    }
                    break;
                }
                case 4:
                {
                    if (0x00000000 == (opcode & 0x00800000))
                    {
                        IDO(VMSCL_P);
                    }
                    else
                    {
                        IDO(VROT_P);
                    }
                    break;
                }
                case 5:
                {
                    switch ((opcode >> 23) & 0x00000003)
                    {
                        case 0:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VMSCL_T);
                            }
                            else
                            {
                                IDO(VMSCL_Q);
                            }
                            break;
                        }
                        case 1:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VCRSP_T);
                            }
                            else
                            {
                                IDO(VQMUL_Q);
                            }
                            break;
                        }
                        case 2:
                        {
                            break;
                        }
                        case 3:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VROT_T);
                            }
                            else
                            {
                                IDO(VROT_Q);
                            }
                            break;
                        }
                    }
                    break;
                }
                case 6:
                {
                    if (0x00800000 == (opcode & 0x00a00000))
                    {
                        IDO(VMIDT_P);
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00800000))
                        {
                            IDO(VMSCL_P);
                        }
                        else
                        {
                            IDO(VROT_P);
                        }
                    }
                    break;
                }
                case 7:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x01000000 == (opcode & 0x01200000))
                        {
                            IDO(VMIDT_T);
                        }
                        else
                        {
                            switch ((opcode >> 23) & 0x00000003)
                            {
                                case 0:
                                {
                                    IDO(VMSCL_T);
                                    break;
                                }
                                case 1:
                                {
                                    IDO(VCRSP_T);
                                    break;
                                }
                                case 2:
                                {
                                    break;
                                }
                                case 3:
                                {
                                    IDO(VROT_T);
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (0x01000000 == (opcode & 0x01200000))
                        {
                            IDO(VMIDT_Q);
                        }
                        else
                        {
                            switch ((opcode >> 23) & 0x00000003)
                            {
                                case 0:
                                {
                                    IDO(VMSCL_Q);
                                    break;
                                }
                                case 1:
                                {
                                    IDO(VQMUL_Q);
                                    break;
                                }
                                case 2:
                                {
                                    break;
                                }
                                case 3:
                                {
                                    IDO(VROT_Q);
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
                case 8:
                {
                    if (0x00000000 == (opcode & 0x00800000))
                    {
                        IDO(VMSCL_P);
                    }
                    else
                    {
                        IDO(VROT_P);
                    }
                    break;
                }
                case 9:
                {
                    switch ((opcode >> 23) & 0x00000003)
                    {
                        case 0:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VMSCL_T);
                            }
                            else
                            {
                                IDO(VMSCL_Q);
                            }
                            break;
                        }
                        case 1:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VCRSP_T);
                            }
                            else
                            {
                                IDO(VQMUL_Q);
                            }
                            break;
                        }
                        case 2:
                        {
                            break;
                        }
                        case 3:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VROT_T);
                            }
                            else
                            {
                                IDO(VROT_Q);
                            }
                            break;
                        }
                    }
                    break;
                }
                case 10:
                {
                    if (0x00000000 == (opcode & 0x00800000))
                    {
                        IDO(VMSCL_P);
                    }
                    else
                    {
                        IDO(VROT_P);
                    }
                    break;
                }
                case 11:
                {
                    switch ((opcode >> 23) & 0x00000003)
                    {
                        case 0:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VMSCL_T);
                            }
                            else
                            {
                                IDO(VMSCL_Q);
                            }
                            break;
                        }
                        case 1:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VCRSP_T);
                            }
                            else
                            {
                                IDO(VQMUL_Q);
                            }
                            break;
                        }
                        case 2:
                        {
                            break;
                        }
                        case 3:
                        {
                            if (0x00000000 == (opcode & 0x00000080))
                            {
                                IDO(VROT_T);
                            }
                            else
                            {
                                IDO(VROT_Q);
                            }
                            break;
                        }
                    }
                    break;
                }
                case 12:
                {
                    if (0x00800000 == (opcode & 0x00a00000))
                    {
                        IDO(VMZERO_P);
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00800000))
                        {
                            IDO(VMSCL_P);
                        }
                        else
                        {
                            IDO(VROT_P);
                        }
                    }
                    break;
                }
                case 13:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x01000000 == (opcode & 0x01200000))
                        {
                            IDO(VMZERO_T);
                        }
                        else
                        {
                            switch ((opcode >> 23) & 0x00000003)
                            {
                                case 0:
                                {
                                    IDO(VMSCL_T);
                                    break;
                                }
                                case 1:
                                {
                                    IDO(VCRSP_T);
                                    break;
                                }
                                case 2:
                                {
                                    break;
                                }
                                case 3:
                                {
                                    IDO(VROT_T);
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (0x01000000 == (opcode & 0x01200000))
                        {
                            IDO(VMZERO_Q);
                        }
                        else
                        {
                            switch ((opcode >> 23) & 0x00000003)
                            {
                                case 0:
                                {
                                    IDO(VMSCL_Q);
                                    break;
                                }
                                case 1:
                                {
                                    IDO(VQMUL_Q);
                                    break;
                                }
                                case 2:
                                {
                                    break;
                                }
                                case 3:
                                {
                                    IDO(VROT_Q);
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
                case 14:
                {
                    if (0x00800000 == (opcode & 0x00a00000))
                    {
                        IDO(VMONE_P);
                    }
                    else
                    {
                        if (0x00000000 == (opcode & 0x00800000))
                        {
                            IDO(VMSCL_P);
                        }
                        else
                        {
                            IDO(VROT_P);
                        }
                    }
                    break;
                }
                case 15:
                {
                    if (0x00000000 == (opcode & 0x00000080))
                    {
                        if (0x01000000 == (opcode & 0x01200000))
                        {
                            IDO(VMONE_T);
                        }
                        else
                        {
                            switch ((opcode >> 23) & 0x00000003)
                            {
                                case 0:
                                {
                                    IDO(VMSCL_T);
                                    break;
                                }
                                case 1:
                                {
                                    IDO(VCRSP_T);
                                    break;
                                }
                                case 2:
                                {
                                    break;
                                }
                                case 3:
                                {
                                    IDO(VROT_T);
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (0x01000000 == (opcode & 0x01200000))
                        {
                            IDO(VMONE_Q);
                        }
                        else
                        {
                            switch ((opcode >> 23) & 0x00000003)
                            {
                                case 0:
                                {
                                    IDO(VMSCL_Q);
                                    break;
                                }
                                case 1:
                                {
                                    IDO(VQMUL_Q);
                                    break;
                                }
                                case 2:
                                {
                                    break;
                                }
                                case 3:
                                {
                                    IDO(VROT_Q);
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
            }
            break;
        }
        case 122:
        case 123:
        {
            if (0x00000000 == (opcode & 0x00000002))
            {
                IDO(SVL_Q);
            }
            else
            {
                IDO(SVR_Q);
            }
            break;
        }
        case 124:
        case 125:
        {
            IDO(SV_Q);
            break;
        }
        case 126:
        {
            break;
        }
        case 127:
        {
            switch ((opcode >> 9) & 0x00000003)
            {
                case 0:
                {
                    IDO(VNOP);
                    break;
                }
                case 1:
                {
                    IDO(VSYNC);
                    break;
                }
                case 2:
                {
                    IDO(VFLUSH);
                    break;
                }
                case 3:
                {
                    break;
                }
            }
            break;
        }
    }
/* End of decoder */
