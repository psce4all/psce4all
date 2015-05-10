/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

/* SLL */
u32 emit$SLL(u32 address, u32 opcode, bool delayslot);

/* SRL */
u32 emit$SRL(u32 address, u32 opcode, bool delayslot);

/* SRA */
u32 emit$SRA(u32 address, u32 opcode, bool delayslot);

/* SLLV */
u32 emit$SLLV(u32 address, u32 opcode, bool delayslot);

/* SRLV */
u32 emit$SRLV(u32 address, u32 opcode, bool delayslot);

/* SRAV */
u32 emit$SRAV(u32 address, u32 opcode, bool delayslot);

/* JR */
u32 emit$JR(u32 address, u32 opcode, bool delayslot);

/* JALR */
u32 emit$JALR(u32 address, u32 opcode, bool delayslot);

/* MOVZ */
u32 emit$MOVZ(u32 address, u32 opcode, bool delayslot);

/* MOVN */
u32 emit$MOVN(u32 address, u32 opcode, bool delayslot);

/* SYSCALL */
u32 emit$SYSCALL(u32 address, u32 opcode, bool delayslot);

/* BREAK */
u32 emit$BREAK(u32 address, u32 opcode, bool delayslot);

/* SYNC */
u32 emit$SYNC(u32 address, u32 opcode, bool delayslot);

/* MFHI */
u32 emit$MFHI(u32 address, u32 opcode, bool delayslot);

/* MTHI */
u32 emit$MTHI(u32 address, u32 opcode, bool delayslot);

/* MFLO */
u32 emit$MFLO(u32 address, u32 opcode, bool delayslot);

/* MTLO */
u32 emit$MTLO(u32 address, u32 opcode, bool delayslot);

/* CLZ */
u32 emit$CLZ(u32 address, u32 opcode, bool delayslot);

/* CLO */
u32 emit$CLO(u32 address, u32 opcode, bool delayslot);

/* MULT */
u32 emit$MULT(u32 address, u32 opcode, bool delayslot);

/* MULTU */
u32 emit$MULTU(u32 address, u32 opcode, bool delayslot);

/* DIV */
u32 emit$DIV(u32 address, u32 opcode, bool delayslot);

/* DIVU */
u32 emit$DIVU(u32 address, u32 opcode, bool delayslot);

/* MADD */
u32 emit$MADD(u32 address, u32 opcode, bool delayslot);

/* MADDU */
u32 emit$MADDU(u32 address, u32 opcode, bool delayslot);

/* ADD */
u32 emit$ADD(u32 address, u32 opcode, bool delayslot);

/* ADDU */
u32 emit$ADDU(u32 address, u32 opcode, bool delayslot);

/* SUB */
u32 emit$SUB(u32 address, u32 opcode, bool delayslot);

/* SUBU */
u32 emit$SUBU(u32 address, u32 opcode, bool delayslot);

/* AND */
u32 emit$AND(u32 address, u32 opcode, bool delayslot);

/* OR */
u32 emit$OR(u32 address, u32 opcode, bool delayslot);

/* XOR */
u32 emit$XOR(u32 address, u32 opcode, bool delayslot);

/* NOR */
u32 emit$NOR(u32 address, u32 opcode, bool delayslot);

/* SLT */
u32 emit$SLT(u32 address, u32 opcode, bool delayslot);

/* SLTU */
u32 emit$SLTU(u32 address, u32 opcode, bool delayslot);

/* MAX */
u32 emit$MAX(u32 address, u32 opcode, bool delayslot);

/* MIN */
u32 emit$MIN(u32 address, u32 opcode, bool delayslot);

/* MSUB */
u32 emit$MSUB(u32 address, u32 opcode, bool delayslot);

/* MSUBU */
u32 emit$MSUBU(u32 address, u32 opcode, bool delayslot);

/* ROTRV */
u32 emit$ROTRV(u32 address, u32 opcode, bool delayslot);

/* ROTR */
u32 emit$ROTR(u32 address, u32 opcode, bool delayslot);

/* BLTZ */
u32 emit$BLTZ(u32 address, u32 opcode, bool delayslot);

/* BGEZ */
u32 emit$BGEZ(u32 address, u32 opcode, bool delayslot);

/* BLTZL */
u32 emit$BLTZL(u32 address, u32 opcode, bool delayslot);

/* BGEZL */
u32 emit$BGEZL(u32 address, u32 opcode, bool delayslot);

/* BLTZAL */
u32 emit$BLTZAL(u32 address, u32 opcode, bool delayslot);

/* BGEZAL */
u32 emit$BGEZAL(u32 address, u32 opcode, bool delayslot);

/* BLTZALL */
u32 emit$BLTZALL(u32 address, u32 opcode, bool delayslot);

/* BGEZALL */
u32 emit$BGEZALL(u32 address, u32 opcode, bool delayslot);

/* J */
u32 emit$J(u32 address, u32 opcode, bool delayslot);

/* JAL */
u32 emit$JAL(u32 address, u32 opcode, bool delayslot);

/* BEQ */
u32 emit$BEQ(u32 address, u32 opcode, bool delayslot);

/* BNE */
u32 emit$BNE(u32 address, u32 opcode, bool delayslot);

/* BLEZ */
u32 emit$BLEZ(u32 address, u32 opcode, bool delayslot);

/* BGTZ */
u32 emit$BGTZ(u32 address, u32 opcode, bool delayslot);

/* ADDI */
u32 emit$ADDI(u32 address, u32 opcode, bool delayslot);

/* ADDIU */
u32 emit$ADDIU(u32 address, u32 opcode, bool delayslot);

/* SLTI */
u32 emit$SLTI(u32 address, u32 opcode, bool delayslot);

/* SLTIU */
u32 emit$SLTIU(u32 address, u32 opcode, bool delayslot);

/* ANDI */
u32 emit$ANDI(u32 address, u32 opcode, bool delayslot);

/* ORI */
u32 emit$ORI(u32 address, u32 opcode, bool delayslot);

/* XORI */
u32 emit$XORI(u32 address, u32 opcode, bool delayslot);

/* LUI */
u32 emit$LUI(u32 address, u32 opcode, bool delayslot);

/* MFC0 */
u32 emit$MFC0(u32 address, u32 opcode, bool delayslot);

/* CFC0 */
u32 emit$CFC0(u32 address, u32 opcode, bool delayslot);

/* MTC0 */
u32 emit$MTC0(u32 address, u32 opcode, bool delayslot);

/* CTC0 */
u32 emit$CTC0(u32 address, u32 opcode, bool delayslot);

/* ERET */
u32 emit$ERET(u32 address, u32 opcode, bool delayslot);

/* MFC1 */
u32 emit$MFC1(u32 address, u32 opcode, bool delayslot);

/* CFC1 */
u32 emit$CFC1(u32 address, u32 opcode, bool delayslot);

/* MTC1 */
u32 emit$MTC1(u32 address, u32 opcode, bool delayslot);

/* CTC1 */
u32 emit$CTC1(u32 address, u32 opcode, bool delayslot);

/* BC1F */
u32 emit$BC1F(u32 address, u32 opcode, bool delayslot);

/* BC1T */
u32 emit$BC1T(u32 address, u32 opcode, bool delayslot);

/* BC1FL */
u32 emit$BC1FL(u32 address, u32 opcode, bool delayslot);

/* BC1TL */
u32 emit$BC1TL(u32 address, u32 opcode, bool delayslot);

/* ADD_S */
u32 emit$ADD_S(u32 address, u32 opcode, bool delayslot);

/* SUB_S */
u32 emit$SUB_S(u32 address, u32 opcode, bool delayslot);

/* MUL_S */
u32 emit$MUL_S(u32 address, u32 opcode, bool delayslot);

/* DIV_S */
u32 emit$DIV_S(u32 address, u32 opcode, bool delayslot);

/* SQRT_S */
u32 emit$SQRT_S(u32 address, u32 opcode, bool delayslot);

/* ABS_S */
u32 emit$ABS_S(u32 address, u32 opcode, bool delayslot);

/* MOV_S */
u32 emit$MOV_S(u32 address, u32 opcode, bool delayslot);

/* NEG_S */
u32 emit$NEG_S(u32 address, u32 opcode, bool delayslot);

/* ROUND_W_S */
u32 emit$ROUND_W_S(u32 address, u32 opcode, bool delayslot);

/* TRUNC_W_S */
u32 emit$TRUNC_W_S(u32 address, u32 opcode, bool delayslot);

/* CEIL_W_S */
u32 emit$CEIL_W_S(u32 address, u32 opcode, bool delayslot);

/* FLOOR_W_S */
u32 emit$FLOOR_W_S(u32 address, u32 opcode, bool delayslot);

/* CVT_W_S */
u32 emit$CVT_W_S(u32 address, u32 opcode, bool delayslot);

/* C_F_S */
u32 emit$C_F_S(u32 address, u32 opcode, bool delayslot);

/* C_UN_S */
u32 emit$C_UN_S(u32 address, u32 opcode, bool delayslot);

/* C_EQ_S */
u32 emit$C_EQ_S(u32 address, u32 opcode, bool delayslot);

/* C_UEQ_S */
u32 emit$C_UEQ_S(u32 address, u32 opcode, bool delayslot);

/* C_OLT_S */
u32 emit$C_OLT_S(u32 address, u32 opcode, bool delayslot);

/* C_ULT_S */
u32 emit$C_ULT_S(u32 address, u32 opcode, bool delayslot);

/* C_OLE_S */
u32 emit$C_OLE_S(u32 address, u32 opcode, bool delayslot);

/* C_ULE_S */
u32 emit$C_ULE_S(u32 address, u32 opcode, bool delayslot);

/* C_SF_S */
u32 emit$C_SF_S(u32 address, u32 opcode, bool delayslot);

/* C_NGLE_S */
u32 emit$C_NGLE_S(u32 address, u32 opcode, bool delayslot);

/* C_SEQ_S */
u32 emit$C_SEQ_S(u32 address, u32 opcode, bool delayslot);

/* C_NGL_S */
u32 emit$C_NGL_S(u32 address, u32 opcode, bool delayslot);

/* C_LT_S */
u32 emit$C_LT_S(u32 address, u32 opcode, bool delayslot);

/* C_NGE_S */
u32 emit$C_NGE_S(u32 address, u32 opcode, bool delayslot);

/* C_LE_S */
u32 emit$C_LE_S(u32 address, u32 opcode, bool delayslot);

/* C_NGT_S */
u32 emit$C_NGT_S(u32 address, u32 opcode, bool delayslot);

/* CVT_S_W */
u32 emit$CVT_S_W(u32 address, u32 opcode, bool delayslot);

/* MFV */
u32 emit$MFV(u32 address, u32 opcode, bool delayslot);

/* MFVC */
u32 emit$MFVC(u32 address, u32 opcode, bool delayslot);

/* MTV */
u32 emit$MTV(u32 address, u32 opcode, bool delayslot);

/* MTVC */
u32 emit$MTVC(u32 address, u32 opcode, bool delayslot);

/* BVF */
u32 emit$BVF(u32 address, u32 opcode, bool delayslot);

/* BVT */
u32 emit$BVT(u32 address, u32 opcode, bool delayslot);

/* BVFL */
u32 emit$BVFL(u32 address, u32 opcode, bool delayslot);

/* BVTL */
u32 emit$BVTL(u32 address, u32 opcode, bool delayslot);

/* BEQL */
u32 emit$BEQL(u32 address, u32 opcode, bool delayslot);

/* BNEL */
u32 emit$BNEL(u32 address, u32 opcode, bool delayslot);

/* BLEZL */
u32 emit$BLEZL(u32 address, u32 opcode, bool delayslot);

/* BGTZL */
u32 emit$BGTZL(u32 address, u32 opcode, bool delayslot);

/* VADD_S */
u32 emit$VADD_S(u32 address, u32 opcode, bool delayslot);

/* VADD_P */
u32 emit$VADD_P(u32 address, u32 opcode, bool delayslot);

/* VADD_T */
u32 emit$VADD_T(u32 address, u32 opcode, bool delayslot);

/* VADD_Q */
u32 emit$VADD_Q(u32 address, u32 opcode, bool delayslot);

/* VSUB_S */
u32 emit$VSUB_S(u32 address, u32 opcode, bool delayslot);

/* VSUB_P */
u32 emit$VSUB_P(u32 address, u32 opcode, bool delayslot);

/* VSUB_T */
u32 emit$VSUB_T(u32 address, u32 opcode, bool delayslot);

/* VSUB_Q */
u32 emit$VSUB_Q(u32 address, u32 opcode, bool delayslot);

/* VSBN_S */
u32 emit$VSBN_S(u32 address, u32 opcode, bool delayslot);

/* VDIV_S */
u32 emit$VDIV_S(u32 address, u32 opcode, bool delayslot);

/* VDIV_P */
u32 emit$VDIV_P(u32 address, u32 opcode, bool delayslot);

/* VDIV_T */
u32 emit$VDIV_T(u32 address, u32 opcode, bool delayslot);

/* VDIV_Q */
u32 emit$VDIV_Q(u32 address, u32 opcode, bool delayslot);

/* VMUL_S */
u32 emit$VMUL_S(u32 address, u32 opcode, bool delayslot);

/* VMUL_P */
u32 emit$VMUL_P(u32 address, u32 opcode, bool delayslot);

/* VMUL_T */
u32 emit$VMUL_T(u32 address, u32 opcode, bool delayslot);

/* VMUL_Q */
u32 emit$VMUL_Q(u32 address, u32 opcode, bool delayslot);

/* VDOT_P */
u32 emit$VDOT_P(u32 address, u32 opcode, bool delayslot);

/* VDOT_T */
u32 emit$VDOT_T(u32 address, u32 opcode, bool delayslot);

/* VDOT_Q */
u32 emit$VDOT_Q(u32 address, u32 opcode, bool delayslot);

/* VSCL_P */
u32 emit$VSCL_P(u32 address, u32 opcode, bool delayslot);

/* VSCL_T */
u32 emit$VSCL_T(u32 address, u32 opcode, bool delayslot);

/* VSCL_Q */
u32 emit$VSCL_Q(u32 address, u32 opcode, bool delayslot);

/* VHDP_P */
u32 emit$VHDP_P(u32 address, u32 opcode, bool delayslot);

/* VHDP_T */
u32 emit$VHDP_T(u32 address, u32 opcode, bool delayslot);

/* VHDP_Q */
u32 emit$VHDP_Q(u32 address, u32 opcode, bool delayslot);

/* VCRS_T */
u32 emit$VCRS_T(u32 address, u32 opcode, bool delayslot);

/* VDET_P */
u32 emit$VDET_P(u32 address, u32 opcode, bool delayslot);

/* VCMP_S */
u32 emit$VCMP_S(u32 address, u32 opcode, bool delayslot);

/* VCMP_P */
u32 emit$VCMP_P(u32 address, u32 opcode, bool delayslot);

/* VCMP_T */
u32 emit$VCMP_T(u32 address, u32 opcode, bool delayslot);

/* VCMP_Q */
u32 emit$VCMP_Q(u32 address, u32 opcode, bool delayslot);

/* VMIN_S */
u32 emit$VMIN_S(u32 address, u32 opcode, bool delayslot);

/* VMIN_P */
u32 emit$VMIN_P(u32 address, u32 opcode, bool delayslot);

/* VMIN_T */
u32 emit$VMIN_T(u32 address, u32 opcode, bool delayslot);

/* VMIN_Q */
u32 emit$VMIN_Q(u32 address, u32 opcode, bool delayslot);

/* VMAX_S */
u32 emit$VMAX_S(u32 address, u32 opcode, bool delayslot);

/* VMAX_P */
u32 emit$VMAX_P(u32 address, u32 opcode, bool delayslot);

/* VMAX_T */
u32 emit$VMAX_T(u32 address, u32 opcode, bool delayslot);

/* VMAX_Q */
u32 emit$VMAX_Q(u32 address, u32 opcode, bool delayslot);

/* VSCMP_S */
u32 emit$VSCMP_S(u32 address, u32 opcode, bool delayslot);

/* VSCMP_P */
u32 emit$VSCMP_P(u32 address, u32 opcode, bool delayslot);

/* VSCMP_T */
u32 emit$VSCMP_T(u32 address, u32 opcode, bool delayslot);

/* VSCMP_Q */
u32 emit$VSCMP_Q(u32 address, u32 opcode, bool delayslot);

/* VSGE_S */
u32 emit$VSGE_S(u32 address, u32 opcode, bool delayslot);

/* VSGE_P */
u32 emit$VSGE_P(u32 address, u32 opcode, bool delayslot);

/* VSGE_T */
u32 emit$VSGE_T(u32 address, u32 opcode, bool delayslot);

/* VSGE_Q */
u32 emit$VSGE_Q(u32 address, u32 opcode, bool delayslot);

/* VSLT_S */
u32 emit$VSLT_S(u32 address, u32 opcode, bool delayslot);

/* VSLT_P */
u32 emit$VSLT_P(u32 address, u32 opcode, bool delayslot);

/* VSLT_T */
u32 emit$VSLT_T(u32 address, u32 opcode, bool delayslot);

/* VSLT_Q */
u32 emit$VSLT_Q(u32 address, u32 opcode, bool delayslot);

/* HALT */
u32 emit$HALT(u32 address, u32 opcode, bool delayslot);

/* MFIC */
u32 emit$MFIC(u32 address, u32 opcode, bool delayslot);

/* MTIC */
u32 emit$MTIC(u32 address, u32 opcode, bool delayslot);

/* MFDR */
u32 emit$MFDR(u32 address, u32 opcode, bool delayslot);

/* DRET */
u32 emit$DRET(u32 address, u32 opcode, bool delayslot);

/* DBREAK */
u32 emit$DBREAK(u32 address, u32 opcode, bool delayslot);

/* MTDR */
u32 emit$MTDR(u32 address, u32 opcode, bool delayslot);

/* EXT */
u32 emit$EXT(u32 address, u32 opcode, bool delayslot);

/* INS */
u32 emit$INS(u32 address, u32 opcode, bool delayslot);

/* WSBH */
u32 emit$WSBH(u32 address, u32 opcode, bool delayslot);

/* WSBW */
u32 emit$WSBW(u32 address, u32 opcode, bool delayslot);

/* SEB */
u32 emit$SEB(u32 address, u32 opcode, bool delayslot);

/* BITREV */
u32 emit$BITREV(u32 address, u32 opcode, bool delayslot);

/* SEH */
u32 emit$SEH(u32 address, u32 opcode, bool delayslot);

/* LB */
u32 emit$LB(u32 address, u32 opcode, bool delayslot);

/* LH */
u32 emit$LH(u32 address, u32 opcode, bool delayslot);

/* LWL */
u32 emit$LWL(u32 address, u32 opcode, bool delayslot);

/* LW */
u32 emit$LW(u32 address, u32 opcode, bool delayslot);

/* LBU */
u32 emit$LBU(u32 address, u32 opcode, bool delayslot);

/* LHU */
u32 emit$LHU(u32 address, u32 opcode, bool delayslot);

/* LWR */
u32 emit$LWR(u32 address, u32 opcode, bool delayslot);

/* SB */
u32 emit$SB(u32 address, u32 opcode, bool delayslot);

/* SH */
u32 emit$SH(u32 address, u32 opcode, bool delayslot);

/* SWL */
u32 emit$SWL(u32 address, u32 opcode, bool delayslot);

/* SW */
u32 emit$SW(u32 address, u32 opcode, bool delayslot);

/* SWR */
u32 emit$SWR(u32 address, u32 opcode, bool delayslot);

/* ICACHE_INDEX_INVALIDATE */
u32 emit$ICACHE_INDEX_INVALIDATE(u32 address, u32 opcode, bool delayslot);

/* ICACHE_INDEX_UNLOCK */
u32 emit$ICACHE_INDEX_UNLOCK(u32 address, u32 opcode, bool delayslot);

/* ICACHE_HIT_INVALIDATE */
u32 emit$ICACHE_HIT_INVALIDATE(u32 address, u32 opcode, bool delayslot);

/* ICACHE_FILL */
u32 emit$ICACHE_FILL(u32 address, u32 opcode, bool delayslot);

/* ICACHE_FILL_WITH_LOCK */
u32 emit$ICACHE_FILL_WITH_LOCK(u32 address, u32 opcode, bool delayslot);

/* DCACHE_INDEX_WRITEBACK_INVALIDATE */
u32 emit$DCACHE_INDEX_WRITEBACK_INVALIDATE(u32 address, u32 opcode, bool delayslot);

/* DCACHE_INDEX_UNLOCK */
u32 emit$DCACHE_INDEX_UNLOCK(u32 address, u32 opcode, bool delayslot);

/* DCACHE_CREATE_DIRTY_EXCLUSIVE */
u32 emit$DCACHE_CREATE_DIRTY_EXCLUSIVE(u32 address, u32 opcode, bool delayslot);

/* DCACHE_HIT_INVALIDATE */
u32 emit$DCACHE_HIT_INVALIDATE(u32 address, u32 opcode, bool delayslot);

/* DCACHE_HIT_WRITEBACK */
u32 emit$DCACHE_HIT_WRITEBACK(u32 address, u32 opcode, bool delayslot);

/* DCACHE_HIT_WRITEBACK_INVALIDATE */
u32 emit$DCACHE_HIT_WRITEBACK_INVALIDATE(u32 address, u32 opcode, bool delayslot);

/* DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK */
u32 emit$DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK(u32 address, u32 opcode, bool delayslot);

/* DCACHE_FILL */
u32 emit$DCACHE_FILL(u32 address, u32 opcode, bool delayslot);

/* DCACHE_FILL_WITH_LOCK */
u32 emit$DCACHE_FILL_WITH_LOCK(u32 address, u32 opcode, bool delayslot);

/* LL */
u32 emit$LL(u32 address, u32 opcode, bool delayslot);

/* LWC1 */
u32 emit$LWC1(u32 address, u32 opcode, bool delayslot);

/* LV_S */
u32 emit$LV_S(u32 address, u32 opcode, bool delayslot);

/* VMOV_S */
u32 emit$VMOV_S(u32 address, u32 opcode, bool delayslot);

/* VMOV_P */
u32 emit$VMOV_P(u32 address, u32 opcode, bool delayslot);

/* VMOV_T */
u32 emit$VMOV_T(u32 address, u32 opcode, bool delayslot);

/* VMOV_Q */
u32 emit$VMOV_Q(u32 address, u32 opcode, bool delayslot);

/* VABS_S */
u32 emit$VABS_S(u32 address, u32 opcode, bool delayslot);

/* VABS_P */
u32 emit$VABS_P(u32 address, u32 opcode, bool delayslot);

/* VABS_T */
u32 emit$VABS_T(u32 address, u32 opcode, bool delayslot);

/* VABS_Q */
u32 emit$VABS_Q(u32 address, u32 opcode, bool delayslot);

/* VNEG_S */
u32 emit$VNEG_S(u32 address, u32 opcode, bool delayslot);

/* VNEG_P */
u32 emit$VNEG_P(u32 address, u32 opcode, bool delayslot);

/* VNEG_T */
u32 emit$VNEG_T(u32 address, u32 opcode, bool delayslot);

/* VNEG_Q */
u32 emit$VNEG_Q(u32 address, u32 opcode, bool delayslot);

/* VIDT_S */
u32 emit$VIDT_S(u32 address, u32 opcode, bool delayslot);

/* VIDT_P */
u32 emit$VIDT_P(u32 address, u32 opcode, bool delayslot);

/* VIDT_T */
u32 emit$VIDT_T(u32 address, u32 opcode, bool delayslot);

/* VIDT_Q */
u32 emit$VIDT_Q(u32 address, u32 opcode, bool delayslot);

/* VSAT0_S */
u32 emit$VSAT0_S(u32 address, u32 opcode, bool delayslot);

/* VSAT0_P */
u32 emit$VSAT0_P(u32 address, u32 opcode, bool delayslot);

/* VSAT0_T */
u32 emit$VSAT0_T(u32 address, u32 opcode, bool delayslot);

/* VSAT0_Q */
u32 emit$VSAT0_Q(u32 address, u32 opcode, bool delayslot);

/* VSAT1_S */
u32 emit$VSAT1_S(u32 address, u32 opcode, bool delayslot);

/* VSAT1_P */
u32 emit$VSAT1_P(u32 address, u32 opcode, bool delayslot);

/* VSAT1_T */
u32 emit$VSAT1_T(u32 address, u32 opcode, bool delayslot);

/* VSAT1_Q */
u32 emit$VSAT1_Q(u32 address, u32 opcode, bool delayslot);

/* VZERO_S */
u32 emit$VZERO_S(u32 address, u32 opcode, bool delayslot);

/* VZERO_P */
u32 emit$VZERO_P(u32 address, u32 opcode, bool delayslot);

/* VZERO_T */
u32 emit$VZERO_T(u32 address, u32 opcode, bool delayslot);

/* VZERO_Q */
u32 emit$VZERO_Q(u32 address, u32 opcode, bool delayslot);

/* VONE_S */
u32 emit$VONE_S(u32 address, u32 opcode, bool delayslot);

/* VONE_P */
u32 emit$VONE_P(u32 address, u32 opcode, bool delayslot);

/* VONE_T */
u32 emit$VONE_T(u32 address, u32 opcode, bool delayslot);

/* VONE_Q */
u32 emit$VONE_Q(u32 address, u32 opcode, bool delayslot);

/* VRCP_S */
u32 emit$VRCP_S(u32 address, u32 opcode, bool delayslot);

/* VRCP_P */
u32 emit$VRCP_P(u32 address, u32 opcode, bool delayslot);

/* VRCP_T */
u32 emit$VRCP_T(u32 address, u32 opcode, bool delayslot);

/* VRCP_Q */
u32 emit$VRCP_Q(u32 address, u32 opcode, bool delayslot);

/* VRSQ_S */
u32 emit$VRSQ_S(u32 address, u32 opcode, bool delayslot);

/* VRSQ_P */
u32 emit$VRSQ_P(u32 address, u32 opcode, bool delayslot);

/* VRSQ_T */
u32 emit$VRSQ_T(u32 address, u32 opcode, bool delayslot);

/* VRSQ_Q */
u32 emit$VRSQ_Q(u32 address, u32 opcode, bool delayslot);

/* VSIN_S */
u32 emit$VSIN_S(u32 address, u32 opcode, bool delayslot);

/* VSIN_P */
u32 emit$VSIN_P(u32 address, u32 opcode, bool delayslot);

/* VSIN_T */
u32 emit$VSIN_T(u32 address, u32 opcode, bool delayslot);

/* VSIN_Q */
u32 emit$VSIN_Q(u32 address, u32 opcode, bool delayslot);

/* VCOS_S */
u32 emit$VCOS_S(u32 address, u32 opcode, bool delayslot);

/* VCOS_P */
u32 emit$VCOS_P(u32 address, u32 opcode, bool delayslot);

/* VCOS_T */
u32 emit$VCOS_T(u32 address, u32 opcode, bool delayslot);

/* VCOS_Q */
u32 emit$VCOS_Q(u32 address, u32 opcode, bool delayslot);

/* VEXP2_S */
u32 emit$VEXP2_S(u32 address, u32 opcode, bool delayslot);

/* VEXP2_P */
u32 emit$VEXP2_P(u32 address, u32 opcode, bool delayslot);

/* VEXP2_T */
u32 emit$VEXP2_T(u32 address, u32 opcode, bool delayslot);

/* VEXP2_Q */
u32 emit$VEXP2_Q(u32 address, u32 opcode, bool delayslot);

/* VLOG2_S */
u32 emit$VLOG2_S(u32 address, u32 opcode, bool delayslot);

/* VLOG2_P */
u32 emit$VLOG2_P(u32 address, u32 opcode, bool delayslot);

/* VLOG2_T */
u32 emit$VLOG2_T(u32 address, u32 opcode, bool delayslot);

/* VLOG2_Q */
u32 emit$VLOG2_Q(u32 address, u32 opcode, bool delayslot);

/* VSQRT_S */
u32 emit$VSQRT_S(u32 address, u32 opcode, bool delayslot);

/* VSQRT_P */
u32 emit$VSQRT_P(u32 address, u32 opcode, bool delayslot);

/* VSQRT_T */
u32 emit$VSQRT_T(u32 address, u32 opcode, bool delayslot);

/* VSQRT_Q */
u32 emit$VSQRT_Q(u32 address, u32 opcode, bool delayslot);

/* VASIN_S */
u32 emit$VASIN_S(u32 address, u32 opcode, bool delayslot);

/* VASIN_P */
u32 emit$VASIN_P(u32 address, u32 opcode, bool delayslot);

/* VASIN_T */
u32 emit$VASIN_T(u32 address, u32 opcode, bool delayslot);

/* VASIN_Q */
u32 emit$VASIN_Q(u32 address, u32 opcode, bool delayslot);

/* VNRCP_S */
u32 emit$VNRCP_S(u32 address, u32 opcode, bool delayslot);

/* VNRCP_P */
u32 emit$VNRCP_P(u32 address, u32 opcode, bool delayslot);

/* VNRCP_T */
u32 emit$VNRCP_T(u32 address, u32 opcode, bool delayslot);

/* VNRCP_Q */
u32 emit$VNRCP_Q(u32 address, u32 opcode, bool delayslot);

/* VNSIN_S */
u32 emit$VNSIN_S(u32 address, u32 opcode, bool delayslot);

/* VNSIN_P */
u32 emit$VNSIN_P(u32 address, u32 opcode, bool delayslot);

/* VNSIN_T */
u32 emit$VNSIN_T(u32 address, u32 opcode, bool delayslot);

/* VNSIN_Q */
u32 emit$VNSIN_Q(u32 address, u32 opcode, bool delayslot);

/* VREXP2_S */
u32 emit$VREXP2_S(u32 address, u32 opcode, bool delayslot);

/* VREXP2_P */
u32 emit$VREXP2_P(u32 address, u32 opcode, bool delayslot);

/* VREXP2_T */
u32 emit$VREXP2_T(u32 address, u32 opcode, bool delayslot);

/* VREXP2_Q */
u32 emit$VREXP2_Q(u32 address, u32 opcode, bool delayslot);

/* VRNDS_S */
u32 emit$VRNDS_S(u32 address, u32 opcode, bool delayslot);

/* VRNDI_S */
u32 emit$VRNDI_S(u32 address, u32 opcode, bool delayslot);

/* VRNDI_P */
u32 emit$VRNDI_P(u32 address, u32 opcode, bool delayslot);

/* VRNDI_T */
u32 emit$VRNDI_T(u32 address, u32 opcode, bool delayslot);

/* VRNDI_Q */
u32 emit$VRNDI_Q(u32 address, u32 opcode, bool delayslot);

/* VRNDF1_S */
u32 emit$VRNDF1_S(u32 address, u32 opcode, bool delayslot);

/* VRNDF1_P */
u32 emit$VRNDF1_P(u32 address, u32 opcode, bool delayslot);

/* VRNDF1_T */
u32 emit$VRNDF1_T(u32 address, u32 opcode, bool delayslot);

/* VRNDF1_Q */
u32 emit$VRNDF1_Q(u32 address, u32 opcode, bool delayslot);

/* VRNDF2_S */
u32 emit$VRNDF2_S(u32 address, u32 opcode, bool delayslot);

/* VRNDF2_P */
u32 emit$VRNDF2_P(u32 address, u32 opcode, bool delayslot);

/* VRNDF2_T */
u32 emit$VRNDF2_T(u32 address, u32 opcode, bool delayslot);

/* VRNDF2_Q */
u32 emit$VRNDF2_Q(u32 address, u32 opcode, bool delayslot);

/* VF2H_P */
u32 emit$VF2H_P(u32 address, u32 opcode, bool delayslot);

/* VF2H_Q */
u32 emit$VF2H_Q(u32 address, u32 opcode, bool delayslot);

/* VH2F_S */
u32 emit$VH2F_S(u32 address, u32 opcode, bool delayslot);

/* VH2F_P */
u32 emit$VH2F_P(u32 address, u32 opcode, bool delayslot);

/* VSBZ_S */
u32 emit$VSBZ_S(u32 address, u32 opcode, bool delayslot);

/* VLGB_S */
u32 emit$VLGB_S(u32 address, u32 opcode, bool delayslot);

/* VUC2I_S */
u32 emit$VUC2I_S(u32 address, u32 opcode, bool delayslot);

/* VC2I_S */
u32 emit$VC2I_S(u32 address, u32 opcode, bool delayslot);

/* VUS2I_S */
u32 emit$VUS2I_S(u32 address, u32 opcode, bool delayslot);

/* VUS2I_P */
u32 emit$VUS2I_P(u32 address, u32 opcode, bool delayslot);

/* VS2I_S */
u32 emit$VS2I_S(u32 address, u32 opcode, bool delayslot);

/* VS2I_P */
u32 emit$VS2I_P(u32 address, u32 opcode, bool delayslot);

/* VI2UC_Q */
u32 emit$VI2UC_Q(u32 address, u32 opcode, bool delayslot);

/* VI2C_Q */
u32 emit$VI2C_Q(u32 address, u32 opcode, bool delayslot);

/* VI2US_P */
u32 emit$VI2US_P(u32 address, u32 opcode, bool delayslot);

/* VI2US_Q */
u32 emit$VI2US_Q(u32 address, u32 opcode, bool delayslot);

/* VI2S_P */
u32 emit$VI2S_P(u32 address, u32 opcode, bool delayslot);

/* VI2S_Q */
u32 emit$VI2S_Q(u32 address, u32 opcode, bool delayslot);

/* VSRT1_Q */
u32 emit$VSRT1_Q(u32 address, u32 opcode, bool delayslot);

/* VSRT2_Q */
u32 emit$VSRT2_Q(u32 address, u32 opcode, bool delayslot);

/* VBFY1_P */
u32 emit$VBFY1_P(u32 address, u32 opcode, bool delayslot);

/* VBFY1_Q */
u32 emit$VBFY1_Q(u32 address, u32 opcode, bool delayslot);

/* VBFY2_Q */
u32 emit$VBFY2_Q(u32 address, u32 opcode, bool delayslot);

/* VOCP_S */
u32 emit$VOCP_S(u32 address, u32 opcode, bool delayslot);

/* VOCP_P */
u32 emit$VOCP_P(u32 address, u32 opcode, bool delayslot);

/* VOCP_T */
u32 emit$VOCP_T(u32 address, u32 opcode, bool delayslot);

/* VOCP_Q */
u32 emit$VOCP_Q(u32 address, u32 opcode, bool delayslot);

/* VSOCP_S */
u32 emit$VSOCP_S(u32 address, u32 opcode, bool delayslot);

/* VSOCP_P */
u32 emit$VSOCP_P(u32 address, u32 opcode, bool delayslot);

/* VFAD_P */
u32 emit$VFAD_P(u32 address, u32 opcode, bool delayslot);

/* VFAD_T */
u32 emit$VFAD_T(u32 address, u32 opcode, bool delayslot);

/* VFAD_Q */
u32 emit$VFAD_Q(u32 address, u32 opcode, bool delayslot);

/* VAVG_P */
u32 emit$VAVG_P(u32 address, u32 opcode, bool delayslot);

/* VAVG_T */
u32 emit$VAVG_T(u32 address, u32 opcode, bool delayslot);

/* VAVG_Q */
u32 emit$VAVG_Q(u32 address, u32 opcode, bool delayslot);

/* VSRT3_Q */
u32 emit$VSRT3_Q(u32 address, u32 opcode, bool delayslot);

/* VSRT4_Q */
u32 emit$VSRT4_Q(u32 address, u32 opcode, bool delayslot);

/* VSGN_S */
u32 emit$VSGN_S(u32 address, u32 opcode, bool delayslot);

/* VSGN_P */
u32 emit$VSGN_P(u32 address, u32 opcode, bool delayslot);

/* VSGN_T */
u32 emit$VSGN_T(u32 address, u32 opcode, bool delayslot);

/* VSGN_Q */
u32 emit$VSGN_Q(u32 address, u32 opcode, bool delayslot);

/* VMFVC */
u32 emit$VMFVC(u32 address, u32 opcode, bool delayslot);

/* VMTVC */
u32 emit$VMTVC(u32 address, u32 opcode, bool delayslot);

/* VT4444_Q */
u32 emit$VT4444_Q(u32 address, u32 opcode, bool delayslot);

/* VT5551_Q */
u32 emit$VT5551_Q(u32 address, u32 opcode, bool delayslot);

/* VT5650_Q */
u32 emit$VT5650_Q(u32 address, u32 opcode, bool delayslot);

/* VCST_S */
u32 emit$VCST_S(u32 address, u32 opcode, bool delayslot);

/* VCST_P */
u32 emit$VCST_P(u32 address, u32 opcode, bool delayslot);

/* VCST_T */
u32 emit$VCST_T(u32 address, u32 opcode, bool delayslot);

/* VCST_Q */
u32 emit$VCST_Q(u32 address, u32 opcode, bool delayslot);

/* VF2IN_S */
u32 emit$VF2IN_S(u32 address, u32 opcode, bool delayslot);

/* VF2IN_P */
u32 emit$VF2IN_P(u32 address, u32 opcode, bool delayslot);

/* VF2IN_T */
u32 emit$VF2IN_T(u32 address, u32 opcode, bool delayslot);

/* VF2IN_Q */
u32 emit$VF2IN_Q(u32 address, u32 opcode, bool delayslot);

/* VF2IZ_S */
u32 emit$VF2IZ_S(u32 address, u32 opcode, bool delayslot);

/* VF2IZ_P */
u32 emit$VF2IZ_P(u32 address, u32 opcode, bool delayslot);

/* VF2IZ_T */
u32 emit$VF2IZ_T(u32 address, u32 opcode, bool delayslot);

/* VF2IZ_Q */
u32 emit$VF2IZ_Q(u32 address, u32 opcode, bool delayslot);

/* VF2IU_S */
u32 emit$VF2IU_S(u32 address, u32 opcode, bool delayslot);

/* VF2IU_P */
u32 emit$VF2IU_P(u32 address, u32 opcode, bool delayslot);

/* VF2IU_T */
u32 emit$VF2IU_T(u32 address, u32 opcode, bool delayslot);

/* VF2IU_Q */
u32 emit$VF2IU_Q(u32 address, u32 opcode, bool delayslot);

/* VF2ID_S */
u32 emit$VF2ID_S(u32 address, u32 opcode, bool delayslot);

/* VF2ID_P */
u32 emit$VF2ID_P(u32 address, u32 opcode, bool delayslot);

/* VF2ID_T */
u32 emit$VF2ID_T(u32 address, u32 opcode, bool delayslot);

/* VF2ID_Q */
u32 emit$VF2ID_Q(u32 address, u32 opcode, bool delayslot);

/* VI2F_S */
u32 emit$VI2F_S(u32 address, u32 opcode, bool delayslot);

/* VI2F_P */
u32 emit$VI2F_P(u32 address, u32 opcode, bool delayslot);

/* VI2F_T */
u32 emit$VI2F_T(u32 address, u32 opcode, bool delayslot);

/* VI2F_Q */
u32 emit$VI2F_Q(u32 address, u32 opcode, bool delayslot);

/* VCMOVT_S */
u32 emit$VCMOVT_S(u32 address, u32 opcode, bool delayslot);

/* VCMOVT_P */
u32 emit$VCMOVT_P(u32 address, u32 opcode, bool delayslot);

/* VCMOVT_T */
u32 emit$VCMOVT_T(u32 address, u32 opcode, bool delayslot);

/* VCMOVT_Q */
u32 emit$VCMOVT_Q(u32 address, u32 opcode, bool delayslot);

/* VCMOVF_S */
u32 emit$VCMOVF_S(u32 address, u32 opcode, bool delayslot);

/* VCMOVF_P */
u32 emit$VCMOVF_P(u32 address, u32 opcode, bool delayslot);

/* VCMOVF_T */
u32 emit$VCMOVF_T(u32 address, u32 opcode, bool delayslot);

/* VCMOVF_Q */
u32 emit$VCMOVF_Q(u32 address, u32 opcode, bool delayslot);

/* VWBN_S */
u32 emit$VWBN_S(u32 address, u32 opcode, bool delayslot);

/* LVL_Q */
u32 emit$LVL_Q(u32 address, u32 opcode, bool delayslot);

/* LVR_Q */
u32 emit$LVR_Q(u32 address, u32 opcode, bool delayslot);

/* LV_Q */
u32 emit$LV_Q(u32 address, u32 opcode, bool delayslot);

/* VPFXS */
u32 emit$VPFXS(u32 address, u32 opcode, bool delayslot);

/* VPFXT */
u32 emit$VPFXT(u32 address, u32 opcode, bool delayslot);

/* VPFXD */
u32 emit$VPFXD(u32 address, u32 opcode, bool delayslot);

/* VIIM */
u32 emit$VIIM(u32 address, u32 opcode, bool delayslot);

/* VFIM */
u32 emit$VFIM(u32 address, u32 opcode, bool delayslot);

/* SC */
u32 emit$SC(u32 address, u32 opcode, bool delayslot);

/* SWC1 */
u32 emit$SWC1(u32 address, u32 opcode, bool delayslot);

/* SV_S */
u32 emit$SV_S(u32 address, u32 opcode, bool delayslot);

/* VMMUL_P */
u32 emit$VMMUL_P(u32 address, u32 opcode, bool delayslot);

/* VMMUL_T */
u32 emit$VMMUL_T(u32 address, u32 opcode, bool delayslot);

/* VMMUL_Q */
u32 emit$VMMUL_Q(u32 address, u32 opcode, bool delayslot);

/* VHTFM2_P */
u32 emit$VHTFM2_P(u32 address, u32 opcode, bool delayslot);

/* VTFM2_P */
u32 emit$VTFM2_P(u32 address, u32 opcode, bool delayslot);

/* VHTFM3_T */
u32 emit$VHTFM3_T(u32 address, u32 opcode, bool delayslot);

/* VTFM3_T */
u32 emit$VTFM3_T(u32 address, u32 opcode, bool delayslot);

/* VHTFM4_Q */
u32 emit$VHTFM4_Q(u32 address, u32 opcode, bool delayslot);

/* VTFM4_Q */
u32 emit$VTFM4_Q(u32 address, u32 opcode, bool delayslot);

/* VMSCL_P */
u32 emit$VMSCL_P(u32 address, u32 opcode, bool delayslot);

/* VMSCL_T */
u32 emit$VMSCL_T(u32 address, u32 opcode, bool delayslot);

/* VMSCL_Q */
u32 emit$VMSCL_Q(u32 address, u32 opcode, bool delayslot);

/* VCRSP_T */
u32 emit$VCRSP_T(u32 address, u32 opcode, bool delayslot);

/* VQMUL_Q */
u32 emit$VQMUL_Q(u32 address, u32 opcode, bool delayslot);

/* VMMOV_P */
u32 emit$VMMOV_P(u32 address, u32 opcode, bool delayslot);

/* VMMOV_T */
u32 emit$VMMOV_T(u32 address, u32 opcode, bool delayslot);

/* VMMOV_Q */
u32 emit$VMMOV_Q(u32 address, u32 opcode, bool delayslot);

/* VMIDT_P */
u32 emit$VMIDT_P(u32 address, u32 opcode, bool delayslot);

/* VMIDT_T */
u32 emit$VMIDT_T(u32 address, u32 opcode, bool delayslot);

/* VMIDT_Q */
u32 emit$VMIDT_Q(u32 address, u32 opcode, bool delayslot);

/* VMZERO_P */
u32 emit$VMZERO_P(u32 address, u32 opcode, bool delayslot);

/* VMZERO_T */
u32 emit$VMZERO_T(u32 address, u32 opcode, bool delayslot);

/* VMZERO_Q */
u32 emit$VMZERO_Q(u32 address, u32 opcode, bool delayslot);

/* VMONE_P */
u32 emit$VMONE_P(u32 address, u32 opcode, bool delayslot);

/* VMONE_T */
u32 emit$VMONE_T(u32 address, u32 opcode, bool delayslot);

/* VMONE_Q */
u32 emit$VMONE_Q(u32 address, u32 opcode, bool delayslot);

/* VROT_P */
u32 emit$VROT_P(u32 address, u32 opcode, bool delayslot);

/* VROT_T */
u32 emit$VROT_T(u32 address, u32 opcode, bool delayslot);

/* VROT_Q */
u32 emit$VROT_Q(u32 address, u32 opcode, bool delayslot);

/* SVL_Q */
u32 emit$SVL_Q(u32 address, u32 opcode, bool delayslot);

/* SVR_Q */
u32 emit$SVR_Q(u32 address, u32 opcode, bool delayslot);

/* SV_Q */
u32 emit$SV_Q(u32 address, u32 opcode, bool delayslot);

/* VNOP */
u32 emit$VNOP(u32 address, u32 opcode, bool delayslot);

/* VSYNC */
u32 emit$VSYNC(u32 address, u32 opcode, bool delayslot);

/* VFLUSH */
u32 emit$VFLUSH(u32 address, u32 opcode, bool delayslot);

