/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "emu.log.h"
#include "lle.mmu.h"
#include "lle.cpu(Allegrex).Host.h"
#include "lle.cpu(Allegrex).jitasm.x86-64.h"
#include "lle.cpu(Allegrex).Instruction.h"

namespace emu
{
    namespace log
    {
        extern SubCategory cpu;
    }
}

namespace Allegrex
{
    struct Context$base
    {
        /* GPR */
        u32 gpr[32];

        /* FPR */
        f32 fpr[32];

        /* VPR */
        f32 vpr[8][4][4];

        /* VCR */
        //u32 vcr[16];

        /* MDR */
        u64 hilo;

        /* FCR */
        u32 fcr0;
        u32 fcr31;

        /* BCR */
        u32 pc;
        u32 npc;

        /* COP0 */
        u32 ie;
    };

    struct Context : Context$base
    {
        u64 * return_address;

        __forceinline void reset_c0r()
        {
            ie = 1;
        }

        __forceinline void reset_bcr()
        {
            pc = 0x00010000;
            npc = 0x00010004;
        }

        u32 mxcsr;

        __forceinline void reset_fcr()
        {
            fcr0 = fcr31 = 0;

            mxcsr = _mm_getcsr() | _MM_MASK_MASK;
            _mm_setcsr(mxcsr);
        }

        __forceinline void reset_mdr()
        {
            hilo = 0;
        }

        struct Random
        {
            int seed;

            static const long long multiplier = 0x00000005DEECE66DLL;
            static const long long addend     = 0x000000000000000BLL;
            static const long long mask       = 0xFFFFFFFFFFFFFFFFLL;

        protected:
            int Next(int bits)
            {
                seed = (seed * multiplier + addend) & mask;
                return (int)((u32)seed >> (32 - bits));
            }

        public:
            Random()
            {
                Random(0x3f800001);
            }

            Random(int seed)
            {
                SetSeed(seed);
            }

            void SetSeed(int seed)
            {
                this->seed = seed & mask;
            }

            int GetSeed()
            {
                return (int)seed;
            }

            int NextInt()
            {
                return Next(32);
            }

            int NextInt(int n)
            {
                if (n <= 0)
                {
                    return 0;
                }

                if ((n & -n) == n)  // i.e., n is a power of 2
                {
                    return (int)((n * (long)Next(31)) >> 31);
                }

                int bits, val;
                do
                {
                    bits = Next(31);
                    val = bits % n;
                }
                while (bits - val + (n-1) < 0);
                return val;
            }

            float NextFloat()
            {
                return Next(24) / ((float)(1 << 24));
            }
        };

        struct PfxSrc
        {
            int     swz[4];
            bool    abs[4];
            bool    cst[4];
            bool    neg[4];
            bool    enabled;

            PfxSrc()
            {
                enabled = false;
            }

            PfxSrc (const PfxSrc& right)
            {
                Copy(right);
            }

            void Reset()
            {
                memset(swz, 0, sizeof(swz));
                memset(abs, 0, sizeof(abs));
                memset(cst, 0, sizeof(cst));
                memset(neg, 0, sizeof(neg));

                enabled = false;
            }

            void Copy(const PfxSrc& right)
            {
                memcpy(swz, right.swz, sizeof(swz));
                memcpy(abs, right.abs, sizeof(abs));
                memcpy(cst, right.cst, sizeof(cst));
                memcpy(neg, right.neg, sizeof(neg));

                enabled = right.enabled;
            }
        };

        struct PfxDst
        {
            int sat[4];
            bool msk[4];
            bool enabled;

            PfxDst()
            {
                enabled = false;
            }

            PfxDst(const PfxDst& right)
            {
                Copy(right);
            }

            void Reset()
            {
                ::memset(sat, 0, sizeof(sat));
                ::memset(msk, 0, sizeof(msk));
                enabled = false;
            }

            void Copy(PfxDst const &right)
            {
                ::memcpy(sat, right.sat, sizeof(sat));
                ::memcpy(msk, right.msk, sizeof(msk));

                enabled = right.enabled;
            }
        };

        struct Vcr
        {
            PfxSrc pfxs;
            PfxSrc pfxt;

            PfxDst pfxd;
            bool   cc[6];

            Vcr()
            {
            }

            Vcr(const Vcr& right)
            {
                Copy(right);
            }

            void Reset()
            {
                pfxs.Reset();
                pfxt.Reset();
                pfxd.Reset();
                ::memset(cc, 1, sizeof(cc)); //cc must be set 1 when resetting
            }

            void Copy(Vcr const &right)
            {
                pfxs.Copy(right.pfxs);
                pfxt.Copy(right.pfxt);
                pfxd.Copy(right.pfxd);
                ::memcpy(cc, right.cc, sizeof(cc));
            }
        };

        Random  rnd;
        Vcr     vcr;

        __forceinline void reset_vcr()
        {
            vcr.Reset();
            rnd.SetSeed(0x3f800001);
        }


        __forceinline void reset_gpr()
        {
            ::memset(gpr, 0, sizeof(gpr));
        }

        __forceinline void reset_fpr()
        {
            ::memset(fpr, 0, sizeof(fpr));
        }

        __forceinline void reset_vpr()
        {
            ::memset(vpr, 0, sizeof(vpr));
        }

        __forceinline void do$SLL(u32 rd, u32 rt, u32 sa)
        {
            if (rd != 0)
            {
                gpr[rd] = (u32(gpr[rt]) << sa);
            }
        }

        __forceinline void do$SRL(u32 rd, u32 rt, u32 sa)
        {
            if (rd != 0)
            {
                gpr[rd] = (u32(gpr[rt]) >> sa);
            }
        }

        __forceinline void do$SRA(u32 rd, u32 rt, u32 sa)
        {
            if (rd != 0)
            {
                gpr[rd] = (s32(gpr[rt]) >> sa);
            }
        }

        __forceinline void do$SLLV(u32 rd, u32 rt, u32 rs)
        {
            if (rd != 0)
            {
                gpr[rd] = (u32(gpr[rt]) << (gpr[rs] & 31));
            }
        }

        __forceinline void do$SRLV(u32 rd, u32 rt, u32 rs)
        {
            if (rd != 0)
            {
                gpr[rd] = (u32(gpr[rt]) >> (gpr[rs] & 31));
            }
        }

        __forceinline void do$SRAV(u32 rd, u32 rt, u32 rs)
        {
            if (rd != 0)
            {
                gpr[rd] = (s32(gpr[rt]) >> (gpr[rs] & 31));
            }
        }

        __forceinline void do$ADDU(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = gpr[rs] + gpr[rt];
            }
        }
        __forceinline void do$ADD(u32 rd, u32 rs, u32 rt)
        {
            return do$ADDU(rd, rs, rt);
        }

        __forceinline void do$SUBU(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = gpr[rs] - gpr[rt];
            }
        }
        __forceinline void do$SUB(u32 rd, u32 rs, u32 rt)
        {
            return do$SUBU(rd, rs, rt);
        }

        __forceinline void do$AND(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = gpr[rs] & gpr[rt];
            }
        }

        __forceinline void do$OR(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = gpr[rs] | gpr[rt];
            }
        }

        __forceinline void do$XOR(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = gpr[rs] ^ gpr[rt];
            }
        }

        __forceinline void do$NOR(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = ~(gpr[rs] | gpr[rt]);
            }
        }

        __forceinline void do$SLT(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = (s32(gpr[rs]) < s32(gpr[rt]));
            }
        }

        __forceinline void do$SLTU(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = (u32(gpr[rs]) < u32(gpr[rt]));
            }
        }

        __forceinline void do$ADDIU(u32 rt, u32 rs, s32 simm16)
        {
            if (rt != 0)
            {
                gpr[rt] = gpr[rs] + simm16;
            }
        }
        __forceinline void do$ADDI(u32 rt, u32 rs, s32 simm16)
        {
            return do$ADDIU(rt, rs, simm16);
        }

        __forceinline void do$SLTI(u32 rt, u32 rs, s32 simm16)
        {
            if (rt != 0)
            {
                gpr[rt] = (s32(gpr[rs]) < simm16);
            }
        }

        __forceinline void do$SLTIU(u32 rt, u32 rs, s32 simm16)
        {
            if (rt != 0)
            {
                gpr[rt] = (u32(gpr[rs]) < u32(simm16));
            }
        }

        __forceinline void do$ANDI(u32 rt, u32 rs, u32 uimm16)
        {
            if (rt != 0)
            {
                gpr[rt] = gpr[rs] & uimm16;
            }
        }

        __forceinline void do$ORI(u32 rt, u32 rs, u32 uimm16)
        {
            if (rt != 0)
            {
                gpr[rt] = gpr[rs] | uimm16;
            }
        }

        __forceinline void do$XORI(u32 rt, u32 rs, u32 uimm16)
        {
            if (rt != 0)
            {
                gpr[rt] = gpr[rs] ^ uimm16;
            }
        }

        /* load upper 16-bit immediate */
        __forceinline void do$LUI(u32 rt, u32 uimm16)
        {
            if (rt != 0)
            {
                gpr[rt] = uimm16 << 16;
            }
        }

        /* bitwise right rotation */
        __forceinline void do$ROTR(u32 rd, u32 rt, u32 sa)
        {
            if (rd != 0)
            {
                gpr[rd] = __host_rotr(gpr[rt], sa);
            }
        }

        /* bitwise right rotation */
        __forceinline void do$ROTRV(u32 rd, u32 rt, u32 rs)
        {
            if (rd != 0)
            {
                gpr[rd] = __host_rotr(gpr[rt], gpr[rs]);
            }
        }

        /* move if zero */
        __forceinline void do$MOVZ(u32 rd, u32 rs, u32 rt)
        {
            if ((rd != 0) && (gpr[rt] == 0))
            {
                gpr[rd] = gpr[rs];
            }
        }

        /* move if non-zero */
        __forceinline void do$MOVN(u32 rd, u32 rs, u32 rt)
        {
            if ((rd != 0) && (gpr[rt] != 0))
            {
                gpr[rd] = gpr[rs];
            }
        }

        /* count leading zeroes */
        __forceinline void do$CLZ(u32 rd, u32 rs)
        {
            if (rd != 0)
            {
                gpr[rd] = __host_clz(gpr[rs]);
            }
        }

        /* count leading ones */
        __forceinline void do$CLO(u32 rd, u32 rs)
        {
            if (rd != 0)
            {
                gpr[rd] = __host_clo(gpr[rs]);
            }
        }

        /* maximal value between two signed integers */
        __forceinline void do$MAX(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = __host_max(gpr[rs], gpr[rt]);
            }
        }

        /* minimal value between two signed integers */
        __forceinline void do$MIN(u32 rd, u32 rs, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = __host_min(gpr[rs], gpr[rt]);
            }
        }

        /* bitwise extraction */
        __forceinline void do$EXT(u32 rt, u32 rs, u32 lsb, u32 dbmalsb)
        {
            if (rt != 0)
            {
                // lsb = least significant bit for bitwise extraction
                // dbmalsb = distance between most and least significant bits for bitwise extraction
                gpr[rt] = __host_ext(gpr[rs], lsb, (dbmalsb + 1));
            }
        }

        /* bitwise insertion */
        __forceinline void do$INS(u32 rt, u32 rs, u32 lsb, u32 msb)
        {
            if (rt != 0)
            {
                // lsb = least significant bit for bitwise insertion
                // msb = most significant bit for bitwise insertion
                gpr[rt] = __host_ins(gpr[rt], gpr[rs], lsb, (msb - lsb + 1));
            }
        }

        /* word swap byte within halfword : XYZW -> YXWZ */
        __forceinline void do$WSBH(u32 rd, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = __host_wsbh(gpr[rt]);
            }
        }

        /* word swap byte within word : XYZW -> ZWYX */
        __forceinline void do$WSBW(u32 rd, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = __host_wsbw(gpr[rt]);
            }
        }

        /* sign-extend byte */
        __forceinline void do$SEB(u32 rd, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = u32((s32) (s8) gpr[rt]);
            }
        }

        /* bit reverse */
        __forceinline void do$BITREV(u32 rd, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = __host_bitrev(gpr[rt]);
            }
        }

        /* sign-extend halfword */
        __forceinline void do$SEH(u32 rd, u32 rt)
        {
            if (rd != 0)
            {
                gpr[rd] = u32((s32) (s16) gpr[rt]);
            }
        }

        __forceinline void do$MFC1(u32 rt, u32 fs)
        {
            if (rt)
            {
                gpr[rt] = *((u32 *) (fpr + fs));
            }
        }

        __forceinline u32 getFCR31()
        {
            switch (mxcsr & _MM_ROUND_MASK)
            {
            case _MM_ROUND_UP:          fcr31 = (fcr31 & ~3) | 2; break;
            case _MM_ROUND_DOWN:        fcr31 = (fcr31 & ~3) | 3; break;
            case _MM_ROUND_TOWARD_ZERO: fcr31 = (fcr31 & ~3) | 1; break;
            default:                    fcr31 = (fcr31 & ~3) | 0; break;
            }
            fcr31 &= ~(1<<24);
            if (mxcsr & _MM_FLUSH_ZERO_ON)
            {
                fcr31 |= (1<<24);
            }
            return fcr31;
        }

        __forceinline void do$CFC1(u32 rt, u32 fs)
        {
            if (rt)
            {
                switch (fs)
                {
                case 0:
                    gpr[rt] = fcr0;
                    break;

                case 31:
                    gpr[rt] = getFCR31();
                    break;

                default:

                    break;
                    //fatalf(al_interpreter, "CFC1 Unsupported for fcr%d", fs);
                }
            }
        }

        __forceinline void do$MTC1(u32 rt, u32 fs)
        {
            *((u32 *) (fpr + fs)) = gpr[rt];
        }

        __forceinline void setFCR31(u32 value)
        {
            mxcsr = _mm_getcsr() | _MM_MASK_MASK;
            {
                fcr31 = value & 0x01800003;
                switch (value & 3)
                {
                case 2:  mxcsr = (mxcsr & ~_MM_ROUND_MASK) | _MM_ROUND_UP; break;
                case 3:  mxcsr = (mxcsr & ~_MM_ROUND_MASK) | _MM_ROUND_DOWN; break;
                case 1:  mxcsr = (mxcsr & ~_MM_ROUND_MASK) | _MM_ROUND_TOWARD_ZERO; break;
                default: mxcsr = (mxcsr & ~_MM_ROUND_MASK) | _MM_ROUND_NEAREST; break;
                }
                if (fcr31 & (1<<24))
                {
                    mxcsr = (mxcsr & ~_MM_FLUSH_ZERO_MASK) | _MM_FLUSH_ZERO_ON;
                }
            }
            _mm_setcsr(mxcsr);
        }

        __forceinline void do$CTC1(u32 rt, u32 fs)
        {
            switch (fs)
            {
            case 31:
                setFCR31(gpr[rt]);
                break;

            default:
                //      fatalf(al_interpreter, "CTC1 Unsupported for fcr%d", fs);
                break;
            }
        }

        __forceinline void do$CVT_S_W(u32 fd, u32 fs)
        {
            _mm_store_ss(&fpr[fd], _mm_cvt_si2ss(_mm_setzero_ps(), *((s32 *) (fpr + fs))));
        }

        __forceinline void do$ADD_S(u32 fd, u32 fs, u32 ft)
        {
            _mm_store_ss(&fpr[fd], _mm_add_ss(_mm_load_ss(&fpr[fs]), _mm_load_ss(&fpr[ft])));
        }

        __forceinline void do$SUB_S(u32 fd, u32 fs, u32 ft)
        {
            _mm_store_ss(&fpr[fd], _mm_sub_ss(_mm_load_ss(&fpr[fs]), _mm_load_ss(&fpr[ft])));
        }

        __forceinline void do$MUL_S(u32 fd, u32 fs, u32 ft)
        {
            _mm_store_ss(&fpr[fd], _mm_mul_ss(_mm_load_ss(&fpr[fs]), _mm_load_ss(&fpr[ft])));
        }

        __forceinline void do$DIV_S(u32 fd, u32 fs, u32 ft)
        {
            _mm_store_ss(&fpr[fd], _mm_div_ss(_mm_load_ss(&fpr[fs]), _mm_load_ss(&fpr[ft])));
        }

        __forceinline void do$SQRT_S(u32 fd, u32 fs)
        {
            _mm_store_ss(&fpr[fd], _mm_sqrt_ss(_mm_load_ss(&fpr[fs])));
        }

        __forceinline void do$CVT_W_S(u32 fd, u32 fs)
        {
            // *((s32 *) (fpr + fd)) = _mm_cvt_ss2si(_mm_load_ss(&fpr[fs]));
            s32 msk = *((s32 *)(&fpr[fs]));
            if ((msk & 0x7F800000) == 0x7F800000)
                *((s32 *) (fpr + fd)) = msk == 0xFF800000 ? 0x80000000 : 0x7FFFFFFF;
            else
                *((s32 *) (fpr + fd)) = _mm_cvt_ss2si(_mm_load_ss(&fpr[fs]));

        }

        __forceinline void do$ABS_S(u32 fd, u32 fs)
        {
            ((u32 *)fpr)[fd] = ((u32 *)fpr)[fs] & 0x7FFFFFFF;
        }

        __forceinline void do$MOV_S(u32 fd, u32 fs)
        {
            ((u32 *)fpr)[fd] = ((u32 *)fpr)[fs];
        }

        __forceinline void do$NEG_S(u32 fd, u32 fs)
        {
            ((u32 *)fpr)[fd] = ((u32 *)fpr)[fs] ^ 0x80000000;
        }

        __forceinline void do$ROUND_W_S(u32 fd, u32 fs)
        {
            s32 msk = *((s32 *)(&fpr[fs]));
            if ((msk & 0x7F800000) == 0x7F800000)
            {
                *((s32 *) (fpr + fd)) = msk == 0xFF800000 ? 0x80000000 : 0x7FFFFFFF;
            }
            else
            {
                _mm_setcsr((mxcsr & ~_MM_ROUND_MASK)|_MM_ROUND_NEAREST);
                *((s32 *) (fpr + fd)) = _mm_cvt_ss2si(_mm_load_ss(&fpr[fs]));
                _mm_setcsr(mxcsr);
            }
        }

        __forceinline void do$TRUNC_W_S(u32 fd, u32 fs)
        {
            //*((s32 *) (fpr + fd)) = _mm_cvtt_ss2si(_mm_load_ss(&fpr[fs]));
            s32 msk = *((s32 *)(&fpr[fs]));
            if ((msk & 0x7F800000) == 0x7F800000)
            {
                *((s32 *) (fpr + fd)) = msk == 0xFF800000 ? 0x80000000 : 0x7FFFFFFF;
            }
            else
            {
                *((s32 *) (fpr + fd)) = _mm_cvtt_ss2si(_mm_load_ss(&fpr[fs]));
            }

        }

        __forceinline void do$CEIL_W_S(u32 fd, u32 fs)
        {
            s32 msk = *((s32 *)(&fpr[fs]));
            if ((msk & 0x7F800000) == 0x7F800000)
            {
                *((s32 *) (fpr + fd)) = msk == 0xFF800000 ? 0x80000000 : 0x7FFFFFFF;
            }
            else
            {
                _mm_setcsr((mxcsr & ~_MM_ROUND_MASK)|_MM_ROUND_UP);
                *((s32 *) (fpr + fd)) = _mm_cvt_ss2si(_mm_load_ss(&fpr[fs]));
                _mm_setcsr(mxcsr);
            }
        }

        __forceinline void do$FLOOR_W_S(u32 fd, u32 fs)
        {
            s32 msk = *((s32 *)(&fpr[fs]));
            if ((msk & 0x7F800000) == 0x7F800000)
            {
                *((s32 *) (fpr + fd)) = msk == 0xFF800000 ? 0x80000000 : 0x7FFFFFFF;
            }
            else
            {
                _mm_setcsr((mxcsr & ~_MM_ROUND_MASK)|_MM_ROUND_DOWN);
                *((s32 *) (fpr + fd)) = _mm_cvt_ss2si(_mm_load_ss(&fpr[fs]));
                _mm_setcsr(mxcsr);
            }
        }

        template< u32 cond >
        __forceinline void do$C_COND_S(u32 const fs, u32 const ft)
        {
            __m128 x = _mm_load_ss(&fpr[fs]);
            __m128 y = _mm_load_ss(&fpr[ft]);

            fcr31 &= ~(1 << 23);

            if (_mm_movemask_ps(_mm_cmpunord_ss(x, y)) & 1)
            {
                if (cond & 1)
                {
                    fcr31 |= 1 << 23;
                }
            }
            else if ((cond & 4) && (_mm_movemask_ps(_mm_cmplt_ss(x, y)) & 1))
            {
                fcr31 |= 1 << 23;
            }
            else if ((cond & 2) && (_mm_movemask_ps(_mm_cmpeq_ss(x, y)) & 1))
            {
                fcr31 |= 1 << 23;
            }
        }

        float   v1[4], v2[4], v3[4];

        __forceinline float intBitsToFloat(int i)
        {
            return *((float*)(&i));
        }

        __forceinline int floatToRawIntBits(float i)
        {
            return *((int*)(&i));
        }

        __forceinline int branchTarget(int npc, int simm16)
        {
            return npc + (simm16 << 2);
        }

        __forceinline float signum(float i) //TODO it probably can be do$ne better
        {
            int x = floatToRawIntBits(i);
            int s = ((x >> 16) & 0x00008000); // sign
            float signf = (s == 1) ? -1.0f : 1.0f;
            if (i == -0.0f || i == 0.0f)
            {
                return 0.0f*signf;
            }
            int & v = *((int *)&i);
            return ((v & 0x80000000) ? -1.0f : 1.0f);
        }

        __forceinline bool isNaN( float value )
        {
            return ((*(UINT*)&value) & 0x7fffffff) > 0x7f800000;
        }

        __forceinline int is_even(float d)
        {
            float int_part;
            modff(d / 2.0f, &int_part);
            return 2.0f * int_part == d;
        }

        // Rounds *.5 to closest even number
        __forceinline float round_ieee_754(float d)
        {
            float i = floorf(d);
            d -= i;
            if (d < 0.5f)
            {
                return i;
            }
            if (d > 0.5f)
            {
                return i + 1.0f;
            }
            if(is_even(i))
            {
                return i;
            }
            return i + 1.0f;
        }

        //#define VFPU_LOGGING //disable it it uses heavy logging!!!
        // VFPU stuff
        __forceinline float transformVr(int swz, bool abs, bool cst, bool neg, float* x)
        {
            float value = 0.0f;
            if (cst)
            {
                switch (swz)
                {
                case 0:
                    value = abs ? 3.0f : 0.0f;
                    break;
                case 1:
                    value = abs ? (1.0f / 3.0f) : 1.0f;
                    break;
                case 2:
                    value = abs ? (1.0f / 4.0f) : 2.0f;
                    break;
                case 3:
                    value = abs ? (1.0f / 6.0f) : 0.5f;
                    break;
                }
            }
            else
            {
                value = x[swz];
            }

            if (abs)
            {
                value = fabsf(value);
            }

            return neg ? (0.0f - value) : value;
        }

        __forceinline float applyPrefixVs(int i, float* x)
        {
            return transformVr(vcr.pfxs.swz[i], vcr.pfxs.abs[i], vcr.pfxs.cst[i], vcr.pfxs.neg[i], x);
        }

        __forceinline float applyPrefixVt(int i, float* x)
        {
            return transformVr(vcr.pfxt.swz[i], vcr.pfxt.abs[i], vcr.pfxt.cst[i], vcr.pfxt.neg[i], x);
        }

        __forceinline float applyPrefixVd(int i, float value)
        {
            switch (vcr.pfxd.sat[i])
            {
            case 1:
                return max(0.0f, min(1.0f, value));
            case 3:
                return max(-1.0f, min(1.0f, value));
            }

            return value;
        }

        template< int vsize > __forceinline void loadVs(int vs)
        {
            int m, s, i;

            m = (vs >> 2) & 7;
            i = (vs >> 0) & 3;

            switch (vsize)
            {
            case 1:
                {
                    s = (vs >> 5) & 3;
                    v1[0] = vpr[m][i][s];

                    if (vcr.pfxs.enabled)
                    {
                        v1[0] = applyPrefixVs(0, v1);
                        vcr.pfxs.enabled = false;
                    }
                    break;
                }

            case 2:
                {
                    s = (vs & 64) >> 5;
                    if ((vs & 32) != 0)
                    {
                        v1[0] = vpr[m][s + 0][i];
                        v1[1] = vpr[m][s + 1][i];
                    }
                    else
                    {
                        v1[0] = vpr[m][i][s + 0];
                        v1[1] = vpr[m][i][s + 1];
                    }

                    if (vcr.pfxs.enabled)
                    {
                        v3[0] = applyPrefixVs(0, v1);
                        v3[1] = applyPrefixVs(1, v1);
                        v1[0] = v3[0];
                        v1[1] = v3[1];
                        vcr.pfxs.enabled = false;
                    }
                    break;
                }

            case 3:
                {
                    s = (vs & 64) >> 6;
                    if ((vs & 32) != 0)
                    {
                        v1[0] = vpr[m][s + 0][i];
                        v1[1] = vpr[m][s + 1][i];
                        v1[2] = vpr[m][s + 2][i];
                    }
                    else
                    {
                        v1[0] = vpr[m][i][s + 0];
                        v1[1] = vpr[m][i][s + 1];
                        v1[2] = vpr[m][i][s + 2];
                    }

                    if (vcr.pfxs.enabled)
                    {
                        v3[0] = applyPrefixVs(0, v1);
                        v3[1] = applyPrefixVs(1, v1);
                        v3[2] = applyPrefixVs(2, v1);
                        v1[0] = v3[0];
                        v1[1] = v3[1];
                        v1[2] = v3[2];
                        vcr.pfxs.enabled = false;
                    }
                    break;
                }

            case 4:
                {
                    if ((vs & 32) != 0)
                    {
                        v1[0] = vpr[m][0][i];
                        v1[1] = vpr[m][1][i];
                        v1[2] = vpr[m][2][i];
                        v1[3] = vpr[m][3][i];
                    }
                    else
                    {
                        v1[0] = vpr[m][i][0];
                        v1[1] = vpr[m][i][1];
                        v1[2] = vpr[m][i][2];
                        v1[3] = vpr[m][i][3];
                    }

                    if (vcr.pfxs.enabled)
                    {
                        v3[0] = applyPrefixVs(0, v1);
                        v3[1] = applyPrefixVs(1, v1);
                        v3[2] = applyPrefixVs(2, v1);
                        v3[3] = applyPrefixVs(3, v1);
                        v1[0] = v3[0];
                        v1[1] = v3[1];
                        v1[2] = v3[2];
                        v1[3] = v3[3];
                        vcr.pfxs.enabled = false;
                    }
                    break;
                }
            }
        }

        template< int vsize > __forceinline void loadVt(int vt)
        {
            int m, s, i;

            m = (vt >> 2) & 7;
            i = (vt >> 0) & 3;

            switch (vsize)
            {
            case 1:
                s = (vt >> 5) & 3;
                v2[0] = vpr[m][i][s];

                if (vcr.pfxt.enabled)
                {
                    v2[0] = applyPrefixVt(0, v2);
                    vcr.pfxt.enabled = false;
                }
                return;

            case 2:
                s = (vt & 64) >> 5;
                if ((vt & 32) != 0)
                {
                    v2[0] = vpr[m][s + 0][i];
                    v2[1] = vpr[m][s + 1][i];
                }
                else
                {
                    v2[0] = vpr[m][i][s + 0];
                    v2[1] = vpr[m][i][s + 1];
                }

                if (vcr.pfxt.enabled)
                {
                    v3[0] = applyPrefixVt(0, v2);
                    v3[1] = applyPrefixVt(1, v2);
                    v2[0] = v3[0];
                    v2[1] = v3[1];
                    vcr.pfxt.enabled = false;
                }
                return;

            case 3:
                s = (vt & 64) >> 6;
                if ((vt & 32) != 0)
                {
                    v2[0] = vpr[m][s + 0][i];
                    v2[1] = vpr[m][s + 1][i];
                    v2[2] = vpr[m][s + 2][i];
                }
                else
                {
                    v2[0] = vpr[m][i][s + 0];
                    v2[1] = vpr[m][i][s + 1];
                    v2[2] = vpr[m][i][s + 2];
                }

                if (vcr.pfxt.enabled)
                {
                    v3[0] = applyPrefixVt(0, v2);
                    v3[1] = applyPrefixVt(1, v2);
                    v3[2] = applyPrefixVt(2, v2);
                    v2[0] = v3[0];
                    v2[1] = v3[1];
                    v2[2] = v3[2];
                    vcr.pfxt.enabled = false;
                }
                return;

            case 4:
                if ((vt & 32) != 0)
                {
                    v2[0] = vpr[m][0][i];
                    v2[1] = vpr[m][1][i];
                    v2[2] = vpr[m][2][i];
                    v2[3] = vpr[m][3][i];
                }
                else
                {
                    v2[0] = vpr[m][i][0];
                    v2[1] = vpr[m][i][1];
                    v2[2] = vpr[m][i][2];
                    v2[3] = vpr[m][i][3];
                }

                if (vcr.pfxt.enabled)
                {
                    v3[0] = applyPrefixVt(0, v2);
                    v3[1] = applyPrefixVt(1, v2);
                    v3[2] = applyPrefixVt(2, v2);
                    v3[3] = applyPrefixVt(3, v2);
                    v2[0] = v3[0];
                    v2[1] = v3[1];
                    v2[2] = v3[2];
                    v2[3] = v3[3];
                    vcr.pfxt.enabled = false;
                }
                break;
            }
        }

        template< int vsize > __forceinline void loadVd(int vd)
        {
            int m, s, i;

            m = (vd >> 2) & 7;
            i = (vd >> 0) & 3;

            switch (vsize)
            {
            case 1:
                s = (vd >> 5) & 3;
                v3[0] = vpr[m][i][s];
                return;

            case 2:
                s = (vd & 64) >> 5;
                if ((vd & 32) != 0)
                {
                    v3[0] = vpr[m][s + 0][i];
                    v3[1] = vpr[m][s + 1][i];
                }
                else
                {
                    v3[0] = vpr[m][i][s + 0];
                    v3[1] = vpr[m][i][s + 1];
                }
                return;

            case 3:
                s = (vd & 64) >> 6;
                if ((vd & 32) != 0)
                {
                    v3[0] = vpr[m][s + 0][i];
                    v3[1] = vpr[m][s + 1][i];
                    v3[2] = vpr[m][s + 2][i];
                }
                else
                {
                    v3[0] = vpr[m][i][s + 0];
                    v3[1] = vpr[m][i][s + 1];
                    v3[2] = vpr[m][i][s + 2];
                }
                return;

            case 4:
                if ((vd & 32) != 0)
                {
                    v3[0] = vpr[m][0][i];
                    v3[1] = vpr[m][1][i];
                    v3[2] = vpr[m][2][i];
                    v3[3] = vpr[m][3][i];
                }
                else
                {
                    v3[0] = vpr[m][i][0];
                    v3[1] = vpr[m][i][1];
                    v3[2] = vpr[m][i][2];
                    v3[3] = vpr[m][i][3];
                }
                break;
            }
        }

        template< int vsize > __forceinline void saveVd(int vd, float* vr)
        {
            int m, s, i;

            m = (vd >> 2) & 7;
            i = (vd >> 0) & 3;

            vcr.pfxs.enabled = false;

            switch (vsize)
            {
            case 1:
                s = (vd >> 5) & 3;
                if (vcr.pfxd.enabled)
                {
                    if (!vcr.pfxd.msk[0])
                    {
                        vpr[m][i][s] = applyPrefixVd(0, vr[0]);
                    }
                    vcr.pfxd.enabled = false;
                }
                else
                {
                    vpr[m][i][s] = vr[0];
                }
                break;

            case 2:
                s = (vd & 64) >> 5;
                if (vcr.pfxd.enabled)
                {
                    if ((vd & 32) != 0)
                    {
                        for (int j = 0; j < 2; ++j)
                        {
                            if (!vcr.pfxd.msk[j])
                            {
                                vpr[m][s + j][i] = applyPrefixVd(j, vr[j]);
                            }
                        }
                    }
                    else
                    {
                        for (int j = 0; j < 2; ++j)
                        {
                            if (!vcr.pfxd.msk[j])
                            {
                                vpr[m][i][s + j] = applyPrefixVd(j, vr[j]);
                            }
                        }
                    }
                    vcr.pfxd.enabled = false;
                }
                else
                {
                    if ((vd & 32) != 0)
                    {
                        for (int j = 0; j < 2; ++j)
                        {
                            vpr[m][s + j][i] = vr[j];
                        }
                    }
                    else
                    {
                        for (int j = 0; j < 2; ++j)
                        {
                            vpr[m][i][s + j] = vr[j];
                        }
                    }
                }
                break;

            case 3:
                s = (vd & 64) >> 6;
                if (vcr.pfxd.enabled)
                {
                    if ((vd & 32) != 0)
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            if (!vcr.pfxd.msk[j])
                            {
                                vpr[m][s + j][i] = applyPrefixVd(j, vr[j]);
                            }
                        }
                    }
                    else
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            if (!vcr.pfxd.msk[j])
                            {
                                vpr[m][i][s + j] = applyPrefixVd(j, vr[j]);
                            }
                        }
                    }
                    vcr.pfxd.enabled = false;
                }
                else
                {
                    if ((vd & 32) != 0)
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            vpr[m][s + j][i] = vr[j];
                        }
                    }
                    else
                    {
                        for (int j = 0; j < 3; ++j)
                        {
                            vpr[m][i][s + j] = vr[j];
                        }
                    }
                }
                break;

            case 4:
                if (vcr.pfxd.enabled)
                {
                    if ((vd & 32) != 0)
                    {
                        for (int j = 0; j < 4; ++j)
                        {
                            if (!vcr.pfxd.msk[j])
                            {
                                vpr[m][j][i] = applyPrefixVd(j, vr[j]);
                            }
                        }
                    }
                    else
                    {
                        for (int j = 0; j < 4; ++j)
                        {
                            if (!vcr.pfxd.msk[j])
                            {
                                vpr[m][i][j] = applyPrefixVd(j, vr[j]);
                            }
                        }
                    }
                    vcr.pfxd.enabled = false;
                }
                else
                {
                    if ((vd & 32) != 0)
                    {
                        for (int j = 0; j < 4; ++j)
                        {
                            vpr[m][j][i] = vr[j];
                        }
                    }
                    else
                    {
                        for (int j = 0; j < 4; ++j)
                        {
                            vpr[m][i][j] = vr[j];
                        }
                    }
                }
                break;

            default:
                break;
            }
        }

        __forceinline float halffloatToFloat(int imm16)
        {
            int s = (imm16 >> 15) & 0x00000001; // sign
            int e = (imm16 >> 10) & 0x0000001f; // exponent
            int f = (imm16 >>  0) & 0x000003ff; // fraction

            // need to handle 0x7C00 INF and 0xFC00 -INF?
            if (e == 0)
            {
                // need to handle +-0 case f==0 or f=0x8000?
                if (f == 0)
                {
                    // Plus or minus zero
                    return intBitsToFloat(s << 31);
                }
                else
                {
                    // Denormalized number -- renormalize it
                    while ((f & 0x00000400) == 0)
                    {
                        f <<= 1;
                        e -=  1;
                    }
                    e += 1;
                    f &= ~0x00000400;
                }
            }
            else if (e == 31)
            {
                if (f == 0)
                {
                    // Inf
                    return intBitsToFloat((s << 31) | 0x7f800000);
                }
                else
                {
                    // NaN
                    return intBitsToFloat((s << 31) | 0x7f800000 | (f << 13));
                }
            }

            e = e + (127 - 15);
            f = f << 13;

            return intBitsToFloat((s << 31) | (e << 23) | f);
        }

        __forceinline int floatToHalffloat(float v)
        {
            int i = floatToRawIntBits(v);
            int s = ((i >> 16) & 0x00008000);              // sign
            int e = ((i >> 23) & 0x000000ff) - (127 - 15); // exponent
            int f = ((i >>  0) & 0x007fffff);              // fraction

            // need to handle NaNs and Inf?
            if (e <= 0)
            {
                if (e < -10)
                {
                    if (s != 0)
                    {
                        // handle -0.0
                        return 0x8000;
                    }
                    return 0;
                }
                f = (f | 0x00800000) >> (1 - e);
                return s | (f >> 13);
            }
            else if (e == 0xff - (127 - 15))
            {
                if (f == 0)
                {
                    // Inf
                    return s | 0x7c00;
                }
                // NAN
                f >>= 13;
                return s | 0x7c00 | f | ((f == 0) ? 1 : 0);
            }
            if (e > 30)
            {
                // Overflow
                return s | 0x7c00;
            }
            return s | (e << 10) | (f >> 13);
        }

        // group VFPU0
        // VFPU0:VADD
        template< int vsize > void do$VADD(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VADD<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                v1[i] += v2[i];
            }

            saveVd<vsize>(vd, v1);
        }

        // VFPU0:VSUB
        template< int vsize > void do$VSUB(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSUB<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                v1[i] -= v2[i];
            }

            saveVd<vsize>(vd, v1);
        }

        // VFPU0:VSBN
        template< int vsize > void do$VSBN(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSBN<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            if (vsize != 1)
            {
                do$UNK("Only supported VSBN.S");
            }

            loadVs<1>(vs);
            loadVt<1>(vt);

            v1[0] = __host_vsbn(v1[0], floatToRawIntBits(v2[0]));

            saveVd<1>(vd, v1);
        }

        // VFPU0:VDIV
        template< int vsize > void do$VDIV(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VDIV<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                v1[i] /= v2[i];
            }

            saveVd<vsize>(vd, v1);
        }

        // group VFPU1
        // VFPU1:VMUL
        template< int vsize > void do$VMUL(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VMUL<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                v1[i] *= v2[i];
            }

            saveVd<vsize>(vd, v1);
        }

        // VFPU1:VDOT
        template< int vsize > void do$VDOT(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VDOT<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            float dot = v1[0] * v2[0];

            for (int i = 1; i < vsize; ++i)
            {
                dot += v1[i] * v2[i];
            }

            v3[0] = dot;

            saveVd<1>(vd, v3);
        }

        // VFPU1:VSCL
        template< int vsize > void do$VSCL(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSCL<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<1>(vt);

            float scale = v2[0];

            for (int i = 0; i < vsize; ++i)
            {
                v1[i] *= scale;
            }

            saveVd<vsize>(vd, v1);
        }

        // VFPU1:VHDP
        template< int vsize > void do$VHDP(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VHDP<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            float hdp = v1[0] * v2[0];

            int i;

            for (i = 1; i < vsize - 1; ++i)
            {
                hdp += v1[i] * v2[i];
            }

            v2[0] = hdp + v2[i];

            saveVd<1>(vd, v2);
        }

        // VFPU1:VCRS
        template< int vsize > void do$VCRS(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VCRS<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<3>(vs);
            loadVt<3>(vt);

            v3[0] = v1[1] * v2[2];
            v3[1] = v1[2] * v2[0];
            v3[2] = v1[0] * v2[1];

            saveVd<3>(vd, v3);
        }

        // VFPU1:VDET
        template< int vsize > void do$VDET(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VDET<%02d> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<2>(vs);
            loadVt<2>(vt);

            v1[0] = v1[0] * v2[1] - v1[1] * v2[0];

            saveVd<1>(vd, v1);
        }

        // VFPU2

        // VFPU2:MFV
        void do$MFV(int rt, int imm7)
        {
#ifdef VFPU_LOGGING
            debugf(al,"MFV rt=%08X,imm7=%08x",rt,imm7);
#endif
            int r = (imm7 >> 5) & 3;
            int m = (imm7 >> 2) & 7;
            int c = (imm7 >> 0) & 3;

            gpr[rt] = floatToRawIntBits(vpr[m][c][r]);
        }
        // VFPU2:MFVC
        void do$MFVC(int rt, int imm7)
        {
#ifdef VFPU_LOGGING
            debugf(al,"MFVC rt=%08X,imm7=%08x",rt,imm7);
#endif
            if (rt != 0)
            {
                int value = 0;
                switch (imm7)
                {
                case 0: /* 128 */
                    value |= vcr.pfxs.swz[0] << 0;
                    value |= vcr.pfxs.swz[1] << 2;
                    value |= vcr.pfxs.swz[2] << 4;
                    value |= vcr.pfxs.swz[3] << 6;
                    if (vcr.pfxs.abs[0]) value |=  1 <<  8;
                    if (vcr.pfxs.abs[1]) value |=  1 <<  9;
                    if (vcr.pfxs.abs[2]) value |=  1 << 10;
                    if (vcr.pfxs.abs[3]) value |=  1 << 11;
                    if (vcr.pfxs.cst[0]) value |=  1 << 12;
                    if (vcr.pfxs.cst[1]) value |=  1 << 13;
                    if (vcr.pfxs.cst[2]) value |=  1 << 14;
                    if (vcr.pfxs.cst[3]) value |=  1 << 15;
                    if (vcr.pfxs.neg[0]) value |=  1 << 16;
                    if (vcr.pfxs.neg[1]) value |=  1 << 17;
                    if (vcr.pfxs.neg[2]) value |=  1 << 18;
                    if (vcr.pfxs.neg[3]) value |=  1 << 19;
                    gpr[rt] = value;
                    break;
                case 1: /* 129 */
                    value |= vcr.pfxt.swz[0] << 0;
                    value |= vcr.pfxt.swz[1] << 2;
                    value |= vcr.pfxt.swz[2] << 4;
                    value |= vcr.pfxt.swz[3] << 6;
                    if (vcr.pfxt.abs[0]) value |=  1 <<  8;
                    if (vcr.pfxt.abs[1]) value |=  1 <<  9;
                    if (vcr.pfxt.abs[2]) value |=  1 << 10;
                    if (vcr.pfxt.abs[3]) value |=  1 << 11;
                    if (vcr.pfxt.cst[0]) value |=  1 << 12;
                    if (vcr.pfxt.cst[1]) value |=  1 << 13;
                    if (vcr.pfxt.cst[2]) value |=  1 << 14;
                    if (vcr.pfxt.cst[3]) value |=  1 << 15;
                    if (vcr.pfxt.neg[0]) value |=  1 << 16;
                    if (vcr.pfxt.neg[1]) value |=  1 << 17;
                    if (vcr.pfxt.neg[2]) value |=  1 << 18;
                    if (vcr.pfxt.neg[3]) value |=  1 << 19;
                    gpr[rt] = value;
                    break;
                case 2: /* 130 */
                    value |= vcr.pfxd.sat[0] << 0;
                    value |= vcr.pfxd.sat[1] << 2;
                    value |= vcr.pfxd.sat[2] << 4;
                    value |= vcr.pfxd.sat[3] << 6;
                    if (vcr.pfxd.msk[0]) value |=  1 <<  8;
                    if (vcr.pfxd.msk[1]) value |=  1 <<  9;
                    if (vcr.pfxd.msk[2]) value |=  1 << 10;
                    if (vcr.pfxd.msk[3]) value |=  1 << 11;
                    gpr[rt] = value;
                    break;
                case 3: /* 131 */
                    for (int i = 6 - 1; i >= 0; i--) {
                        value <<= 1;
                        if (vcr.cc[i]) {
                            value |= 1;
                        }
                    }
                    gpr[rt] = value;
                    break;
                case 8: /* 136 - RCX0 */
                    gpr[rt] = rnd.GetSeed();
                    break;
                case 9:  /* 137 - RCX1 */
                case 10: /* 138 - RCX2 */
                case 11: /* 139 - RCX3 */
                case 12: /* 140 - RCX4 */
                case 13: /* 141 - RCX5 */
                case 14: /* 142 - RCX6 */
                case 15: /* 143 - RCX7 */
                    // as we do not know how VFPU generates a random number through those 8 registers, we ignore 7 of them
                    gpr[rt] = 0x3f800000;
                    break;
                default:
                    break;
                }
            }
        }
        // VFPU2:MTV
        void do$MTV(int rt, int imm7)
        {
#ifdef VFPU_LOGGING
            debugf(al,"MTV rt=%08X,imm7=%08x",rt,imm7);
#endif
            int r = (imm7 >> 5) & 3;
            int m = (imm7 >> 2) & 7;
            int c = (imm7 >> 0) & 3;

            vpr[m][c][r] = intBitsToFloat(gpr[rt]);
        }

        // VFPU2:MTVC
        void do$MTVC(int rt, int imm7)
        {
#ifdef VFPU_LOGGING
            debugf(al,"MTVC rt=%08X,imm7=%08x",rt,imm7);
#endif
            int value = gpr[rt];

            switch (imm7)
            {
            case 0: /* 128 */
                vcr.pfxs.swz[0] = ((value >> 0 ) & 3);
                vcr.pfxs.swz[1] = ((value >> 2 ) & 3);
                vcr.pfxs.swz[2] = ((value >> 4 ) & 3);
                vcr.pfxs.swz[3] = ((value >> 6 ) & 3);
                vcr.pfxs.abs[0] = ((value >> 8 ) & 1) == 1;
                vcr.pfxs.abs[1] = ((value >> 9 ) & 1) == 1;
                vcr.pfxs.abs[2] = ((value >> 10) & 1) == 1;
                vcr.pfxs.abs[3] = ((value >> 11) & 1) == 1;
                vcr.pfxs.cst[0] = ((value >> 12) & 1) == 1;
                vcr.pfxs.cst[1] = ((value >> 13) & 1) == 1;
                vcr.pfxs.cst[2] = ((value >> 14) & 1) == 1;
                vcr.pfxs.cst[3] = ((value >> 15) & 1) == 1;
                vcr.pfxs.neg[0] = ((value >> 16) & 1) == 1;
                vcr.pfxs.neg[1] = ((value >> 17) & 1) == 1;
                vcr.pfxs.neg[2] = ((value >> 18) & 1) == 1;
                vcr.pfxs.neg[3] = ((value >> 19) & 1) == 1;
                vcr.pfxs.enabled = true;
                break;
            case 1: /* 129 */
                vcr.pfxt.swz[0] = ((value >> 0 ) & 3);
                vcr.pfxt.swz[1] = ((value >> 2 ) & 3);
                vcr.pfxt.swz[2] = ((value >> 4 ) & 3);
                vcr.pfxt.swz[3] = ((value >> 6 ) & 3);
                vcr.pfxt.abs[0] = ((value >> 8 ) & 1) == 1;
                vcr.pfxt.abs[1] = ((value >> 9 ) & 1) == 1;
                vcr.pfxt.abs[2] = ((value >> 10) & 1) == 1;
                vcr.pfxt.abs[3] = ((value >> 11) & 1) == 1;
                vcr.pfxt.cst[0] = ((value >> 12) & 1) == 1;
                vcr.pfxt.cst[1] = ((value >> 13) & 1) == 1;
                vcr.pfxt.cst[2] = ((value >> 14) & 1) == 1;
                vcr.pfxt.cst[3] = ((value >> 15) & 1) == 1;
                vcr.pfxt.neg[0] = ((value >> 16) & 1) == 1;
                vcr.pfxt.neg[1] = ((value >> 17) & 1) == 1;
                vcr.pfxt.neg[2] = ((value >> 18) & 1) == 1;
                vcr.pfxt.neg[3] = ((value >> 19) & 1) == 1;
                vcr.pfxt.enabled = true;
                break;
            case 2: /* 130 */
                vcr.pfxd.sat[0] = ((value >> 0 ) & 3);
                vcr.pfxd.sat[1] = ((value >> 2 ) & 3);
                vcr.pfxd.sat[2] = ((value >> 4 ) & 3);
                vcr.pfxd.sat[3] = ((value >> 6 ) & 3);
                vcr.pfxd.msk[0] = ((value >> 8 ) & 1) == 1;
                vcr.pfxd.msk[1] = ((value >> 9 ) & 1) == 1;
                vcr.pfxd.msk[2] = ((value >> 10) & 1) == 1;
                vcr.pfxd.msk[3] = ((value >> 11) & 1) == 1;
                vcr.pfxd.enabled = true;
                break;
            case 3: /* 131 */
                for (int i = 0; i < 6; i++) {
                    vcr.cc[i] = (value & 1) != 0;
                    //value >>= 1;
                    value = (u32)value >>1;
                }
                break;
            case 8: /* 136 - RCX0 */
                rnd.SetSeed(value);
                break;
            case 9:  /* 137 - RCX1 */
            case 10: /* 138 - RCX2 */
            case 11: /* 139 - RCX3 */
            case 12: /* 140 - RCX4 */
            case 13: /* 141 - RCX5 */
            case 14: /* 142 - RCX6 */
            case 15: /* 143 - RCX7 */
                // as we do not know how VFPU generates a random number through those 8 registers, we ignore 7 of them
                break;
            default:
                break;
            }
        }

        // VFPU2:BVF
        bool do$BVF(int imm3, int simm16)
        {
#ifdef VFPU_LOGGING
            debugf(al,"BVF imm3=%08X,simm16=%08x",imm3,simm16);
#endif
            npc = (!vcr.cc[imm3]) ? branchTarget(pc, simm16) : (pc + 4);
            return true;
        }
        // VFPU2:BVT
        bool do$BVT(int imm3, int simm16)
        {
#ifdef VFPU_LOGGING
            debugf(al,"BVT imm3=%08X,simm16=%08x",imm3,simm16);
#endif
            npc = (vcr.cc[imm3]) ? branchTarget(pc, simm16) : (pc + 4);
            return true;
        }
        // VFPU2:BVFL
        bool do$BVFL(int imm3, int simm16)
        {
#ifdef VFPU_LOGGING
            debugf(al,"BVFL imm3=%08X,simm16=%08x",imm3,simm16);
#endif
            if (!vcr.cc[imm3])
            {
                npc = branchTarget(pc, simm16);
                return true;
            }
            else
            {
                pc = pc + 4;
            }
            return false;
        }
        // VFPU2:BVTL
        bool do$BVTL(int imm3, int simm16)
        {
#ifdef VFPU_LOGGING
            debugf(al,"BVTL imm3=%08X,simm16=%08x",imm3,simm16);
#endif
            if (vcr.cc[imm3])
            {
                npc = branchTarget(pc, simm16);
                return true;
            }
            else
            {
                pc = pc + 4;
            }
            return false;
        }
        // group VFPU3


        // VFPU3:VCMP
        template< int vsize > void do$VCMP(int vs, int vt, int cond)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VCMP<%02x> vs=%08X,vt=%08x,cond=%02x",vsize,vs,vt,cond);
#endif
            bool cc_or = false;
            bool cc_and = true;

            if ((cond & 8) == 0)
            {
                bool not_ = ((cond & 4) == 4);

                bool cc = false;

                loadVs<vsize>(vs);
                loadVt<vsize>(vt);

                for (int i = 0; i < vsize; ++i)
                {
                    switch (cond & 3)
                    {
                    case 0:
                        cc = not_;
                        break;

                    case 1:
                        cc = not_ ? (v1[i] != v2[i]) : (v1[i] == v2[i]);
                        break;

                    case 2:
                        if (isNaN(v1[i]) || isNaN(v2[i]))
                        {
                            cc = false;
                        }
                        else
                        {
                            cc = not_ ? (v1[i] >= v2[i]) : (v1[i] < v2[i]);
                        }
                        break;

                    case 3:
                        if (isNaN(v1[i]) || isNaN(v2[i]))
                        {
                            cc = false;
                        }
                        else
                        {
                            cc = not_ ? (v1[i] > v2[i]) : (v1[i] <= v2[i]);
                        }
                        break;

                    }

                    vcr.cc[i] = cc;
                    cc_or = cc_or || cc;
                    cc_and = cc_and && cc;
                }

            }
            else
            {
                loadVs<vsize>(vs);

                bool not_ = ((cond & 4) == 4);
                bool cc = false;

                for (int i = 0; i < vsize; ++i)
                {
                    switch (cond & 3)
                    {
                    case 0:
                        cc = (abs(v1[i]) == 0.0f);
                        break;

                    case 1:
                        cc = isNaN(v1[i]);
                        break;

                    case 2:
                        cc = !_finite(v1[i]);
                        break;

                    case 3:
                        cc = isNaN(abs(v1[i])) || !_finite(v1[i]);
                        break;

                    }
                    if (not_)
                    {
                        cc = !cc;
                    }
                    vcr.cc[i] = cc;
                    cc_or = cc_or || cc;
                    cc_and = cc_and && cc;
                }

            }
            vcr.cc[4] = cc_or;
            vcr.cc[5] = cc_and;
        }

        // VFPU3:VMIN
        template< int vsize > void do$VMIN(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VMIN<%02x> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = min(v1[i], v2[i]);
            }

            saveVd<vsize>(vd, v3);
        }

        // VFPU3:VMAX
        template< int vsize > void do$VMAX(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VMAX<%02x> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = max(v1[i], v2[i]);
            }

            saveVd<vsize>(vd, v3);
        }

        // VFPU3:VSCMP
        template< int vsize > void do$VSCMP(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSCMP<%02x> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                //v3[i] = signum(v1[i] - v2[i]);
                float a = v1[i] - v2[i];
                v3[i] = (float) ((0.0 < a) - (a < 0.0));
            }

            saveVd<vsize>(vd, v3);
        }

        // VFPU3:VSGE
        template< int vsize > void do$VSGE(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSGE<%02x> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = (v1[i] >= v2[i]) ? 1.0f : 0.0f;
            }

            saveVd<vsize>(vd, v3);
        }

        // VFPU3:VSLT
        template< int vsize > void do$VSLT(int vd, int vs, int vt)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSLT<%02x> vd=%08X,vs=%08x,vt=%08x",vsize,vd,vs,vt);
#endif
            loadVs<vsize>(vs);
            loadVt<vsize>(vt);

            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = (v1[i] < v2[i]) ? 1.0f : 0.0f;
            }

            saveVd<vsize>(vd, v3);
        }

        // group VFPU4
        // VFPU4:VMOV
        template< int vsize > void do$VMOV(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VMOV<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            saveVd<vsize>(vd, v1);
        }

        // VFPU4:VABS
        template< int vsize > void do$VABS(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VABS<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = fabsf(v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }

        // VFPU4:VNEG
        template< int vsize > void do$VNEG(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VNEG<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = 0.0f - v1[i];
            }
            saveVd<vsize>(vd, v3);
        }

        // VFPU4:VIDT
        template< int vsize > void do$VIDT(int vd)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VIDT<%02x> vd=%08X",vsize,vd);
#endif
            int id = vd % vsize;
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = (id == i) ? 1.0f : 0.0f;
            }
            saveVd<vsize>(vd, v3);
        }

        // VFPU4:VSAT0
        template< int vsize > void do$VSAT0(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSAT0<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                if(isNaN(v1[i]))
                {
                    v3[i] = v1[i];
                }
                else
                {
                    v3[i] = min(max(0.0f, v1[i]), 1.0f);
                }
            }
            saveVd<vsize>(vd, v3);
        }

        // VFPU4:VSAT1
        template< int vsize > void do$VSAT1(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSAT1<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                if(isNaN(v1[i]))
                {
                    v3[i] = v1[i];
                }
                else
                {
                    v3[i] = min(max(-1.0f, v1[i]), 1.0f);
                }
            }
            saveVd<vsize>(vd, v3);
        }

        // VFPU4:VZERO
        template< int vsize > void do$VZERO(int vd)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VZERO<%02x> vd=%08X",vsize,vd);
#endif
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = 0.0f;
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VONE
        template< int vsize > void do$VONE(int vd)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VONE<%02x> vd=%08X",vsize,vd);
#endif
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = 1.0f;
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VRCP
        template< int vsize > void do$VRCP(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VRCP<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = 1.0f / v1[i];
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VRSQ
        template< int vsize > void do$VRSQ(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VRSQ<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = 1.f / sqrtf(v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VSIN
        template< int vsize > void do$VSIN(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSIN<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = sinf(0.5f * f32(M_PI) * v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VCOS
        template< int vsize > void do$VCOS(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VCOS<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = cosf(0.5f * (float)M_PI * v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VEXP2
        template< int vsize > void do$VEXP2(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VEXP2<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = powf(2.f, v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VLOG2
        template< int vsize > void do$VLOG2(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VLOG2<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = logf(v1[i]) / log(2.0f);
            }
            saveVd<vsize>(vd, v3);
        }

        // VFPU4:VSQRT
        template< int vsize > void do$VSQRT(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSQRT<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = sqrtf(v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }

        // VFPU4:VASIN
        template< int vsize > void do$VASIN(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VASIN<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                //v3[i] = asinf(v1[i]) * 2.f / (float)M_PI;
                v3[i] = asinf(v1[i]) / f32(M_PI_2);
            }
            saveVd<vsize>(vd, v3);
        }

        // VFPU4:VNRCP
        template< int vsize > void do$VNRCP(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VNRCP<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = 0.0f - (1.0f / v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }

        // VFPU4:VNSIN
        template< int vsize > void do$VNSIN(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VNSIN<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = 0.0f - sinf(0.5f * (float)M_PI * v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VREXP2
        template< int vsize > void do$VREXP2(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VREXP2<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = 1.f / powf(2.f, v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VRNDS
        template< int vsize > void do$VRNDS(int vs)
        {
            // temporary solution
            loadVs<1>(vs);
            rnd.SetSeed(floatToRawIntBits(v1[0]));
        }
        // VFPU4:VRNDI
        template< int vsize > void do$VRNDI(int vd)
        {
            // temporary solution
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = intBitsToFloat(rnd.NextInt());
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VRNDF1
        template< int vsize > void do$VRNDF1(int vd)
        {
            // temporary solution
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = 1.0f + rnd.NextFloat();
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VRNDF2
        template< int vsize > void do$VRNDF2(int vd)
        {
            // temporary solution
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = (1.0f + rnd.NextFloat())*2.0f;
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VF2H
        template< int vsize > void do$VF2H(int vd, int vs)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; i += 2)
            {
                v3[i >> 1] = intBitsToFloat((floatToHalffloat(v1[i + 1]) << 16) | floatToHalffloat(v1[i]));
            }
            saveVd<(vsize >> 1)>(vd, v3);
        }
        // VFPU4:VH2F
        template< int vsize > void do$VH2F(int vd, int vs)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                int imm32 = floatToRawIntBits(v1[i]);
                v3[0+2*i] = halffloatToFloat(imm32 & 65535);
                v3[1+2*i] = halffloatToFloat((u32)imm32 >> 16);
            }
            saveVd<vsize*2>(vd, v3);
        }
        // VFPU4:VSBZ
        template< int vsize > void do$VSBZ(int vd, int vs)
        {
            (void)vd;
            (void)vs;
            do$UNK("Unimplemented VSBZ");
        }
        // VFPU4:VLGB
        template< int vsize > void do$VLGB(int vd, int vs)
        {
            (void)vd;
            (void)vs;
            do$UNK("Unimplemented VLGB");
        }
        // VFPU4:VUC2I
        template< int vsize > void do$VUC2I(int vd, int vs)
        {
            /*int size = vsize; //TODO need to check it
            if(vsize!=1)
            {
            do$UNK("Unsupported VUC2I size (not 1)");
            }*/
            loadVs<1>(vs);
            int n = floatToRawIntBits(v1[0]);
            // Performs pseudo$-full-scale conversion
            v3[0] = intBitsToFloat((u32)(((n      ) & 0xFF) * 0x01010101) >> 1);
            v3[1] = intBitsToFloat((u32)(((n >>  8) & 0xFF) * 0x01010101) >> 1);
            v3[2] = intBitsToFloat((u32)(((n >> 16) & 0xFF) * 0x01010101) >> 1);
            v3[3] = intBitsToFloat((u32)(((n >> 24) & 0xFF) * 0x01010101) >> 1);
            saveVd<4>(vd, v3);
        }
        // VFPU4:VC2I
        template< int vsize > void do$VC2I(int vd, int vs)
        {
            loadVs<1>(vs);
            int n = floatToRawIntBits(v1[0]);
            v3[0] = intBitsToFloat(((n      ) & 0xFF) << 24);
            v3[1] = intBitsToFloat(((n >>  8) & 0xFF) << 24);
            v3[2] = intBitsToFloat(((n >> 16) & 0xFF) << 24);
            v3[3] = intBitsToFloat(((n >> 24) & 0xFF) << 24);
            saveVd<4>(vd, v3);
        }
        // VFPU4:VUS2I
        template< int vsize > void do$VUS2I(int vd, int vs)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                int imm32 = floatToRawIntBits(v1[i]);
                v3[0+2*i] = intBitsToFloat(((imm32       ) & 0xFFFF) << 15);
                v3[1+2*i] = intBitsToFloat((((u32)imm32 >> 16) & 0xFFFF) << 15);
            }
            saveVd<vsize*2>(vd, v3);
        }
        // VFPU4:VS2I
        template< int vsize > void do$VS2I(int vd, int vs)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                int imm32 = floatToRawIntBits(v1[i]);
                v3[0+2*i] = intBitsToFloat(((imm32       ) & 0xFFFF) << 16);
                v3[1+2*i] = intBitsToFloat((((u32)imm32 >> 16) & 0xFFFF) << 16);
            }
            saveVd<vsize*2>(vd, v3);
        }

        // VFPU4:VI2UC
        template< int vsize > void do$VI2UC(int vd, int vs)
        {
            loadVs<4>(vs);
            int x = floatToRawIntBits(v1[0]);
            int y = floatToRawIntBits(v1[1]);
            int z = floatToRawIntBits(v1[2]);
            int w = floatToRawIntBits(v1[3]);
            v3[0] = intBitsToFloat(
                ((x < 0) ? 0 : ((x >> 23) << 0 )) |
                ((y < 0) ? 0 : ((y >> 23) << 8 )) |
                ((z < 0) ? 0 : ((z >> 23) << 16)) |
                ((w < 0) ? 0 : ((w >> 23) << 24)));
            saveVd<1>(vd, v3);
        }

        // VFPU4:VI2C
        template< int vsize > void do$VI2C(int vd, int vs)
        {
            loadVs<4>(vs);
            int x = floatToRawIntBits(v1[0]);
            int y = floatToRawIntBits(v1[1]);
            int z = floatToRawIntBits(v1[2]);
            int w = floatToRawIntBits(v1[3]);
            v3[0] = intBitsToFloat(
                (((u32)x >> 24) << 0 ) |
                (((u32)y >> 24) << 8 ) |
                (((u32)z >> 24) << 16) |
                (((u32)w >> 24) << 24));
            saveVd<1>(vd, v3);
        }
        // VFPU4:VI2US
        template< int vsize > void do$VI2US(int vd, int vs)
        {
            loadVs<vsize>(vs);
            int x = floatToRawIntBits(v1[0]);
            int y = floatToRawIntBits(v1[1]);
            v3[0] = intBitsToFloat(
                ((x < 0) ? 0 : ((x >> 15) << 0 )) |
                ((y < 0) ? 0 : ((y >> 15) << 16)));
            if (vsize == 4)
            {
                int z = floatToRawIntBits(v1[2]);
                int w = floatToRawIntBits(v1[3]);

                v3[1] = intBitsToFloat(
                    ((z < 0) ? 0 : ((z >> 15) << 0 )) |
                    ((w < 0) ? 0 : ((w >> 15) << 16)));
                saveVd<2>(vd, v3);
            }
            else
            {
                saveVd<1>(vd, v3);
            }
        }
        // VFPU4:VI2S
        template< int vsize > void do$VI2S(int vd, int vs)
        {
            loadVs<vsize>(vs);
            int x = floatToRawIntBits(v1[0]);
            int y = floatToRawIntBits(v1[1]);
            v3[0] = intBitsToFloat(
                (((u32)x >> 16) << 0 ) |
                (((u32)y >> 16) << 16));
            if (vsize == 4)
            {
                int z = floatToRawIntBits(v1[2]);
                int w = floatToRawIntBits(v1[3]);

                v3[1] = intBitsToFloat(
                    (((u32)z >> 16) << 0 ) |
                    (((u32)w >> 16) << 16));
                saveVd<2>(vd, v3);
            }
            else
            {
                saveVd<1>(vd, v3);
            }
        }
        // VFPU4:VSRT1
        template< int vsize > void do$VSRT1(int vd, int vs)
        {
            loadVs<4>(vs);
            float x = v1[0];
            float y = v1[1];
            float z = v1[2];
            float w = v1[3];
            v3[0] = min(x, y);
            v3[1] = max(x, y);
            v3[2] = min(z, w);
            v3[3] = max(z, w);
            saveVd<4>(vd, v3);
        }
        // VFPU4:VSRT2
        template< int vsize > void do$VSRT2(int vd, int vs)
        {
            loadVs<4>(vs);
            float x = v1[0];
            float y = v1[1];
            float z = v1[2];
            float w = v1[3];
            v3[0] = min(x, w);
            v3[1] = min(y, z);
            v3[2] = max(y, z);
            v3[3] = max(x, w);
            saveVd<4>(vd, v3);
        }
        // VFPU4:VBFY1
        template< int vsize > void do$VBFY1(int vd, int vs)
        {
            loadVs<vsize>(vs);
            float x = v1[0];
            float y = v1[1];
            v3[0] = x + y;
            v3[1] = x - y;
            if (vsize > 2)
            {
                float z = v1[2];
                float w = v1[3];
                v3[2] = z + w;
                v3[3] = z - w;
                saveVd<4>(vd, v3);
            }
            else
            {
                saveVd<2>(vd, v3);
            }
        }
        // VFPU4:VBFY2
        template< int vsize > void do$VBFY2(int vd, int vs)
        {
            loadVs<vsize>(vs);
            float x = v1[0];
            float y = v1[1];
            float z = v1[2];
            float w = v1[3];
            v3[0] = x + z;
            v3[1] = y + w;
            v3[2] = x - z;
            v3[3] = y - w;
            saveVd<4>(vd, v3);
        }
        // VFPU4:VOCP
        template< int vsize > void do$VOCP(int vd, int vs)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v1[i] = 1.0f - v1[i];
            }
            saveVd<vsize>(vd, v1);
        }
        // VFPU4:VSOCP
        template< int vsize > void do$VSOCP(int vd, int vs)
        {
            loadVs<vsize>(vs);
            float x = v1[0];
            v3[0] = min(max(0.0f, 1.0f - x), 1.0f);
            v3[1] = min(max(0.0f,x), 1.0f);
            if (vsize > 1)
            {
                float y = v1[1];
                v3[2] = min(max(0.0f, 1.0f - y), 1.0f);
                v3[3] = min(max(0.0f, y), 1.0f);
                saveVd<4>(vd, v3);
            }
            else
            {
                saveVd<2>(vd, v3);
            }
        }
        // VFPU4:VFAD
        template< int vsize > void do$VFAD(int vd, int vs)
        {
            loadVs<vsize>(vs);
            for (int i = 1; i < vsize; ++i)
            {
                v1[0] += v1[i];
            }
            saveVd<1>(vd, v1);
        }
        // VFPU4:VAVG
        template< int vsize > void do$VAVG(int vd, int vs)
        {
            loadVs<vsize>(vs);
            for (int i = 1; i < vsize; ++i)
            {
                v1[0] += v1[i];
            }
            v1[0] /= vsize;
            saveVd<1>(vd, v1);
        }
        // VFPU4:VSRT3
        template< int vsize > void do$VSRT3(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSRT3<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<4>(vs);
            float x = v1[0];
            float y = v1[1];
            float z = v1[2];
            float w = v1[3];
            v3[0] = max(x, y);
            v3[1] = min(x, y);
            v3[2] = max(z, w);
            v3[3] = min(z, w);
            saveVd<4>(vd, v3);
        }
        // VFPU4:VSRT4
        template< int vsize > void do$VSRT4(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSRT4<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<4>(vs);
            float x = v1[0];
            float y = v1[1];
            float z = v1[2];
            float w = v1[3];
            v3[0] = max(x, w);
            v3[1] = max(y, z);
            v3[2] = min(y, z);
            v3[3] = min(x, w);
            saveVd<4>(vd, v3);
        }
        // VFPU4:VSGN
        template< int vsize > void do$VSGN(int vd, int vs)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VSGN<%02x> vd=%08X,vs=%08x",vsize,vd,vs);
#endif
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = signum(v1[i]);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VMFVC
        void do$VMFVC(int vd, int imm7)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VMFVC vd=%08X,imm7=%08x",vd,imm7);
#endif
            int value = 0;
            switch (imm7)
            {
            case 0: /* 128 */
                value |= vcr.pfxs.swz[0] << 0;
                value |= vcr.pfxs.swz[1] << 2;
                value |= vcr.pfxs.swz[2] << 4;
                value |= vcr.pfxs.swz[3] << 6;
                if (vcr.pfxs.abs[0]) value |=  1 <<  8;
                if (vcr.pfxs.abs[1]) value |=  1 <<  9;
                if (vcr.pfxs.abs[2]) value |=  1 << 10;
                if (vcr.pfxs.abs[3]) value |=  1 << 11;
                if (vcr.pfxs.cst[0]) value |=  1 << 12;
                if (vcr.pfxs.cst[1]) value |=  1 << 13;
                if (vcr.pfxs.cst[2]) value |=  1 << 14;
                if (vcr.pfxs.cst[3]) value |=  1 << 15;
                if (vcr.pfxs.neg[0]) value |=  1 << 16;
                if (vcr.pfxs.neg[1]) value |=  1 << 17;
                if (vcr.pfxs.neg[2]) value |=  1 << 18;
                if (vcr.pfxs.neg[3]) value |=  1 << 19;
                v3[0] = intBitsToFloat(value);
                saveVd<1>(vd, v3);
                break;
            case 1: /* 129 */
                value |= vcr.pfxt.swz[0] << 0;
                value |= vcr.pfxt.swz[1] << 2;
                value |= vcr.pfxt.swz[2] << 4;
                value |= vcr.pfxt.swz[3] << 6;
                if (vcr.pfxt.abs[0]) value |=  1 <<  8;
                if (vcr.pfxt.abs[1]) value |=  1 <<  9;
                if (vcr.pfxt.abs[2]) value |=  1 << 10;
                if (vcr.pfxt.abs[3]) value |=  1 << 11;
                if (vcr.pfxt.cst[0]) value |=  1 << 12;
                if (vcr.pfxt.cst[1]) value |=  1 << 13;
                if (vcr.pfxt.cst[2]) value |=  1 << 14;
                if (vcr.pfxt.cst[3]) value |=  1 << 15;
                if (vcr.pfxt.neg[0]) value |=  1 << 16;
                if (vcr.pfxt.neg[1]) value |=  1 << 17;
                if (vcr.pfxt.neg[2]) value |=  1 << 18;
                if (vcr.pfxt.neg[3]) value |=  1 << 19;
                v3[0] = intBitsToFloat(value);
                saveVd<1>(vd, v3);
                break;
            case 2: /* 130 */
                value |= vcr.pfxd.sat[0] << 0;
                value |= vcr.pfxd.sat[1] << 2;
                value |= vcr.pfxd.sat[2] << 4;
                value |= vcr.pfxd.sat[3] << 6;
                if (vcr.pfxd.msk[0]) value |=  1 <<  8;
                if (vcr.pfxd.msk[1]) value |=  1 <<  9;
                if (vcr.pfxd.msk[2]) value |=  1 << 10;
                if (vcr.pfxd.msk[3]) value |=  1 << 11;
                v3[0] = intBitsToFloat(value);
                saveVd<1>(vd, v3);
                break;
            case 3: /* 131 */
                for (int i = 6 - 1; i >= 0; i--) {
                    value <<= 1;
                    if (vcr.cc[i]) {
                        value |= 1;
                    }
                }
                v3[0] = intBitsToFloat(value);
                saveVd<1>(vd, v3);
                break;
            case 8: /* 136 - RCX0 */
                v3[0] = intBitsToFloat(rnd.GetSeed());
                saveVd<1>(vd, v3);
                break;
            case 9:  /* 137 - RCX1 */
            case 10: /* 138 - RCX2 */
            case 11: /* 139 - RCX3 */
            case 12: /* 140 - RCX4 */
            case 13: /* 141 - RCX5 */
            case 14: /* 142 - RCX6 */
            case 15: /* 143 - RCX7 */
                // as we do not know how VFPU generates a random number through those 8 registers, we ignore 7 of them
                v3[0] = intBitsToFloat(0x3f800000);
                saveVd<1>(vd, v3);
                break;
            default:
                break;
            }
        }
        // VFPU4:VMTVC
        void do$VMTVC(int vd, int imm7)
        {
#ifdef VFPU_LOGGING
            debugf(al,"VMTVC vd=%08X,imm7=%08x",vd,imm7);
#endif
            loadVs<1>(vd);
            int value = floatToRawIntBits(v1[0]);
            switch (imm7)
            {
            case 0: /* 128 */
                vcr.pfxs.swz[0] = ((value >> 0 ) & 3);
                vcr.pfxs.swz[1] = ((value >> 2 ) & 3);
                vcr.pfxs.swz[2] = ((value >> 4 ) & 3);
                vcr.pfxs.swz[3] = ((value >> 6 ) & 3);
                vcr.pfxs.abs[0] = ((value >> 8 ) & 1) == 1;
                vcr.pfxs.abs[1] = ((value >> 9 ) & 1) == 1;
                vcr.pfxs.abs[2] = ((value >> 10) & 1) == 1;
                vcr.pfxs.abs[3] = ((value >> 11) & 1) == 1;
                vcr.pfxs.cst[0] = ((value >> 12) & 1) == 1;
                vcr.pfxs.cst[1] = ((value >> 13) & 1) == 1;
                vcr.pfxs.cst[2] = ((value >> 14) & 1) == 1;
                vcr.pfxs.cst[3] = ((value >> 15) & 1) == 1;
                vcr.pfxs.neg[0] = ((value >> 16) & 1) == 1;
                vcr.pfxs.neg[1] = ((value >> 17) & 1) == 1;
                vcr.pfxs.neg[2] = ((value >> 18) & 1) == 1;
                vcr.pfxs.neg[3] = ((value >> 19) & 1) == 1;
                vcr.pfxs.enabled = true;
                break;
            case 1: /* 129 */
                vcr.pfxt.swz[0] = ((value >> 0 ) & 3);
                vcr.pfxt.swz[1] = ((value >> 2 ) & 3);
                vcr.pfxt.swz[2] = ((value >> 4 ) & 3);
                vcr.pfxt.swz[3] = ((value >> 6 ) & 3);
                vcr.pfxt.abs[0] = ((value >> 8 ) & 1) == 1;
                vcr.pfxt.abs[1] = ((value >> 9 ) & 1) == 1;
                vcr.pfxt.abs[2] = ((value >> 10) & 1) == 1;
                vcr.pfxt.abs[3] = ((value >> 11) & 1) == 1;
                vcr.pfxt.cst[0] = ((value >> 12) & 1) == 1;
                vcr.pfxt.cst[1] = ((value >> 13) & 1) == 1;
                vcr.pfxt.cst[2] = ((value >> 14) & 1) == 1;
                vcr.pfxt.cst[3] = ((value >> 15) & 1) == 1;
                vcr.pfxt.neg[0] = ((value >> 16) & 1) == 1;
                vcr.pfxt.neg[1] = ((value >> 17) & 1) == 1;
                vcr.pfxt.neg[2] = ((value >> 18) & 1) == 1;
                vcr.pfxt.neg[3] = ((value >> 19) & 1) == 1;
                vcr.pfxt.enabled = true;
                break;
            case 2: /* 130 */
                vcr.pfxd.sat[0] = ((value >> 0 ) & 3);
                vcr.pfxd.sat[1] = ((value >> 2 ) & 3);
                vcr.pfxd.sat[2] = ((value >> 4 ) & 3);
                vcr.pfxd.sat[3] = ((value >> 6 ) & 3);
                vcr.pfxd.msk[0] = ((value >> 8 ) & 1) == 1;
                vcr.pfxd.msk[1] = ((value >> 9 ) & 1) == 1;
                vcr.pfxd.msk[2] = ((value >> 10) & 1) == 1;
                vcr.pfxd.msk[3] = ((value >> 11) & 1) == 1;
                vcr.pfxd.enabled = true;
                break;
            case 3: /* 131 */
                for (int i = 0; i < 6; i++) {
                    vcr.cc[i] = (value & 1) != 0;
                    //value >>= 1;
                    value = (u32)value >>1;
                }
                break;
            case 8: /* 136 - RCX0 */
                rnd.SetSeed(value);
                break;
            case 9:  /* 137 - RCX1 */
            case 10: /* 138 - RCX2 */
            case 11: /* 139 - RCX3 */
            case 12: /* 140 - RCX4 */
            case 13: /* 141 - RCX5 */
            case 14: /* 142 - RCX6 */
            case 15: /* 143 - RCX7 */
                // as we do not know how VFPU generates a random number through those 8 registers, we ignore 7 of them
                break;
            default:
                break;
            }
        }
        // VFPU4:VT4444
        template< int vsize > void do$VT4444(int vd, int vs)
        {
            loadVs<4>(vs);
            int i0 = floatToRawIntBits(v1[0]);
            int i1 = floatToRawIntBits(v1[1]);
            int i2 = floatToRawIntBits(v1[2]);
            int i3 = floatToRawIntBits(v1[3]);
            int o0 = 0, o1 = 0;
            o0 |= ((i0>> 4)&15) << 0;
            o0 |= ((i0>>12)&15) << 4;
            o0 |= ((i0>>20)&15) << 8;
            o0 |= ((i0>>28)&15) <<12;
            o0 |= ((i1>> 4)&15) <<16;
            o0 |= ((i1>>12)&15) <<20;
            o0 |= ((i1>>20)&15) <<24;
            o0 |= ((i1>>28)&15) <<28;
            o1 |= ((i2>> 4)&15) << 0;
            o1 |= ((i2>>12)&15) << 4;
            o1 |= ((i2>>20)&15) << 8;
            o1 |= ((i2>>28)&15) <<12;
            o1 |= ((i3>> 4)&15) <<16;
            o1 |= ((i3>>12)&15) <<20;
            o1 |= ((i3>>20)&15) <<24;
            o1 |= ((i3>>28)&15) <<28;
            v3[0] = intBitsToFloat(o0);
            v3[1] = intBitsToFloat(o1);
            saveVd<2>(vd, v3);
        }
        // VFPU4:VT5551
        template< int vsize > void do$VT5551(int vd, int vs)
        {
            loadVs<4>(vs);


            int i0 = floatToRawIntBits(v1[0]);
            int i1 = floatToRawIntBits(v1[1]);
            int i2 = floatToRawIntBits(v1[2]);
            int i3 = floatToRawIntBits(v1[3]);

            int o0 = 0, o1 = 0;
            o0 |= ((i0>> 3)&31) << 0;
            o0 |= ((i0>>11)&31) << 5;
            o0 |= ((i0>>19)&31) <<10;
            o0 |= ((i0>>31)& 1) <<15;
            o0 |= ((i1>> 3)&31) <<16;
            o0 |= ((i1>>11)&31) <<21;
            o0 |= ((i1>>19)&31) <<26;
            o0 |= ((i1>>31)& 1) <<31;
            o1 |= ((i2>> 3)&31) << 0;
            o1 |= ((i2>>11)&31) << 5;
            o1 |= ((i2>>19)&31) <<10;
            o1 |= ((i2>>31)& 1) <<15;
            o1 |= ((i3>> 3)&31) <<16;
            o1 |= ((i3>>11)&31) <<21;
            o1 |= ((i3>>19)&31) <<26;
            o1 |= ((i3>>31)& 1) <<31;
            v3[0] = intBitsToFloat(o0);
            v3[1] = intBitsToFloat(o1);
            saveVd<2>(vd, v3);
        }
        // VFPU4:VT5650
        template< int vsize > void do$VT5650(int vd, int vs)
        {
            loadVs<4>(vs);
            int i0 = floatToRawIntBits(v1[0]);
            int i1 = floatToRawIntBits(v1[1]);
            int i2 = floatToRawIntBits(v1[2]);
            int i3 = floatToRawIntBits(v1[3]);
            int o0 = 0, o1 = 0;
            o0 |= ((i0>> 3)&31) << 0;
            o0 |= ((i0>>10)&63) << 5;
            o0 |= ((i0>>19)&31) <<11;
            o0 |= ((i1>> 3)&31) <<16;
            o0 |= ((i1>>10)&63) <<21;
            o0 |= ((i1>>19)&31) <<27;
            o1 |= ((i2>> 3)&31) << 0;
            o1 |= ((i2>>10)&63) << 5;
            o1 |= ((i2>>19)&31) <<11;
            o1 |= ((i3>> 3)&31) <<16;
            o1 |= ((i3>>10)&63) <<21;
            o1 |= ((i3>>19)&31) <<27;
            v3[0] = intBitsToFloat(o0);
            v3[1] = intBitsToFloat(o1);
            saveVd<2>(vd, v3);
        }
        // VFPU4:VCST
        template< int vsize > void do$VCST(int vd, int imm5)
        {
            static float floatConstants[] =
            {
                0.0f,
                FLT_MAX,
                sqrtf(2.0f),
                sqrtf(0.5f),
                2.0f / sqrtf((float)M_PI),
                2.0f / (float)M_PI,
                1.0f / (float)M_PI,
                (float)M_PI / 4.0f,
                (float)M_PI / 2.0f,
                (float)M_PI,
                (float)M_E,
                logf((float)M_E) / logf(2.0f), // log2(E) = log(E) / log(2)
                log10f((float)M_E),
                logf(2.0f),
                logf(10.0f),
                (float)M_PI * 2.0f,
                (float)M_PI / 6.0f,
                log10f(2.0),
                logf(10.0f) / logf(2.0f), // log2(10) = log(10) / log(2)
                sqrtf(3.0f) / 2.0f
            };
            float constant = 0.0f;
            if (imm5 >= 0 && imm5 < (int)(sizeof(floatConstants)/sizeof(float)))
            {
                constant = floatConstants[imm5];
            }
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = constant;
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VF2IN
        template< int vsize > void do$VF2IN(int vd, int vs, int imm5)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                float vs = v1[i];
                float vr = round_ieee_754(ldexpf(vs,imm5));
                int   vo = int(vr);
                if (vo == 0x80000000)
                {
                    if (isNaN(vs) || vs > 0.0f)
                    {
                        vo = 0x7FFFFFFF;
                    }
                }
                v3[i] = intBitsToFloat(vo);
            }
            saveVd<vsize>(vd, v3);

        }
        // VFPU4:VF2IZ
        template< int vsize > void do$VF2IZ(int vd, int vs, int imm5)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                float vs = v1[i];
                float vr = (vs >= 0 ? floorf(ldexpf(vs,imm5)) : ceilf(ldexpf(vs,imm5)));
                int   vo = int(vr);
                if (vo == 0x80000000)
                {
                    if (isNaN(vs) || vs > 0.0f)
                    {
                        vo = 0x7FFFFFFF;
                    }
                }
                v3[i] = intBitsToFloat(vo);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VF2IU
        template< int vsize > void do$VF2IU(int vd, int vs, int imm5)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                float vs = v1[i];
                float vr = ceil(ldexpf(vs,imm5));
                int   vo = int(vr);
                if (vo == 0x80000000)
                {
                    if (isNaN(vs) || vs > 0.0f)
                    {
                        vo = 0x7FFFFFFF;
                    }
                }
                v3[i] = intBitsToFloat(vo);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VF2ID
        template< int vsize > void do$VF2ID(int vd, int vs, int imm5)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                float vs = v1[i];
                float vr = floorf(ldexpf(vs,imm5));
                int   vo = int(vr);
                if (vo == 0x80000000)
                {
                    if (isNaN(vs) || vs > 0.0f)
                    {
                        vo = 0x7FFFFFFF;
                    }
                }
                v3[i] = intBitsToFloat(vo);
            }
            saveVd<vsize>(vd, v3);

        }
        // VFPU4:VI2F
        template< int vsize > void do$VI2F(int vd, int vs, int imm5)
        {
            loadVs<vsize>(vs);
            for (int i = 0; i < vsize; ++i)
            {
                v3[i] = __host_vsbn(v1[i], -imm5);
            }
            saveVd<vsize>(vd, v3);
        }
        // VFPU4:VCMOVT
        template< int vsize > void do$VCMOVT(int vd, int vs,int imm3)
        {
            if (imm3 < 6)
            {
                if (vcr.cc[imm3])
                {
                    loadVs<vsize>(vs);
                    saveVd<vsize>(vd, v1);
                }
                else
                {
                    vcr.pfxs.enabled = false;
                    if (vcr.pfxd.enabled)
                    {
                        loadVd<vsize>(vd);
                        saveVd<vsize>(vd, v3);
                    }
                }
            }
            else if (imm3 == 6)
            {
                loadVs<vsize>(vs);
                loadVd<vsize>(vd);
                for (int i = 0; i < vsize; ++i)
                {
                    if (vcr.cc[i])
                    {
                        v3[i] = v1[i];
                    }
                }
                saveVd<vsize>(vd, v3);
            }
            else
            {
                //never copy
            }
        }
        // VFPU4:VCMOVF
        template< int vsize > void do$VCMOVF(int vd, int vs,int imm3)
        {
            if (imm3 < 6)
            {
                if (!vcr.cc[imm3])
                {
                    loadVs<vsize>(vs);
                    saveVd<vsize>(vd, v1);
                }
                else
                {
                    vcr.pfxs.enabled = false;
                    if (vcr.pfxd.enabled)
                    {
                        loadVd<vsize>(vd);
                        saveVd<vsize>(vd, v3);
                    }
                }
            }
            else if (imm3 == 6)
            {
                loadVs<vsize>(vs);
                loadVd<vsize>(vd);
                for (int i = 0; i < vsize; ++i)
                {
                    if (!vcr.cc[i])
                    {
                        v3[i] = v1[i];
                    }
                }
                saveVd<vsize>(vd, v3);
            }
            else
            {
                loadVs<vsize>(vs);
                saveVd<vsize>(vd, v1);
            }
        }
        // VFPU4:VWBN
        template< int vsize > void do$VWBN(int vd, int vs, int imm8)
        {
            (void)vd;
            (void)vs;
            (void)imm8;
            do$UNK("Unimplemented VWBN");
        }
        // group VFPU5
        // VFPU5:VPFXS
        void do$VPFXS(u32 imm24)
        {
            u32 swzx = (imm24>>0)&3;
            u32 swzy = (imm24>>2)&3;
            u32 swzz = (imm24>>4)&3;
            u32 swzw = (imm24>>6)&3;
            u32 absx = (imm24>>8)&1;
            u32 absy = (imm24>>9)&1;
            u32 absz = (imm24>>10)&1;
            u32 absw = (imm24>>11)&1;
            u32 cstx = (imm24>>12)&1;
            u32 csty = (imm24>>13)&1;
            u32 cstz = (imm24>>14)&1;
            u32 cstw = (imm24>>15)&1;
            u32 negx = (imm24>>16)&1;
            u32 negy = (imm24>>17)&1;
            u32 negz = (imm24>>18)&1;
            u32 negw = (imm24>>19)&1;
            vcr.pfxs.swz[0] = swzx;
            vcr.pfxs.swz[1] = swzy;
            vcr.pfxs.swz[2] = swzz;
            vcr.pfxs.swz[3] = swzw;
            vcr.pfxs.abs[0] = absx != 0;
            vcr.pfxs.abs[1] = absy != 0;
            vcr.pfxs.abs[2] = absz != 0;
            vcr.pfxs.abs[3] = absw != 0;
            vcr.pfxs.cst[0] = cstx != 0;
            vcr.pfxs.cst[1] = csty != 0;
            vcr.pfxs.cst[2] = cstz != 0;
            vcr.pfxs.cst[3] = cstw != 0;
            vcr.pfxs.neg[0] = negx != 0;
            vcr.pfxs.neg[1] = negy != 0;
            vcr.pfxs.neg[2] = negz != 0;
            vcr.pfxs.neg[3] = negw != 0;
            vcr.pfxs.enabled = true;
        }

        // VFPU5:VPFXT
        void do$VPFXT(u32 imm24)
        {
            u32 swzx = (imm24>>0)&3;
            u32 swzy = (imm24>>2)&3;
            u32 swzz = (imm24>>4)&3;
            u32 swzw = (imm24>>6)&3;
            u32 absx = (imm24>>8)&1;
            u32 absy = (imm24>>9)&1;
            u32 absz = (imm24>>10)&1;
            u32 absw = (imm24>>11)&1;
            u32 cstx = (imm24>>12)&1;
            u32 csty = (imm24>>13)&1;
            u32 cstz = (imm24>>14)&1;
            u32 cstw = (imm24>>15)&1;
            u32 negx = (imm24>>16)&1;
            u32 negy = (imm24>>17)&1;
            u32 negz = (imm24>>18)&1;
            u32 negw = (imm24>>19)&1;
            vcr.pfxt.swz[0] = swzx;
            vcr.pfxt.swz[1] = swzy;
            vcr.pfxt.swz[2] = swzz;
            vcr.pfxt.swz[3] = swzw;
            vcr.pfxt.abs[0] = absx != 0;
            vcr.pfxt.abs[1] = absy != 0;
            vcr.pfxt.abs[2] = absz != 0;
            vcr.pfxt.abs[3] = absw != 0;
            vcr.pfxt.cst[0] = cstx != 0;
            vcr.pfxt.cst[1] = csty != 0;
            vcr.pfxt.cst[2] = cstz != 0;
            vcr.pfxt.cst[3] = cstw != 0;
            vcr.pfxt.neg[0] = negx != 0;
            vcr.pfxt.neg[1] = negy != 0;
            vcr.pfxt.neg[2] = negz != 0;
            vcr.pfxt.neg[3] = negw != 0;
            vcr.pfxt.enabled = true;
        }

        // VFPU5:VPFXD
        void do$VPFXD(u32 imm24)
        {
            u32 satx = (imm24>>0)&3;
            u32 saty = (imm24>>2)&3;
            u32 satz = (imm24>>4)&3;
            u32 satw = (imm24>>6)&3;
            u32 mskx = (imm24>>8)&1;
            u32 msky = (imm24>>9)&1;
            u32 mskz = (imm24>>10)&1;
            u32 mskw = (imm24>>11)&1;
            vcr.pfxd.sat[0] = satx;
            vcr.pfxd.sat[1] = saty;
            vcr.pfxd.sat[2] = satz;
            vcr.pfxd.sat[3] = satw;
            vcr.pfxd.msk[0] = mskx != 0;
            vcr.pfxd.msk[1] = msky != 0;
            vcr.pfxd.msk[2] = mskz != 0;
            vcr.pfxd.msk[3] = mskw != 0;
            vcr.pfxd.enabled = true;
        }

        // VFPU5:VIIM
        void do$VIIM(int vd, int imm16)
        {
            v3[0] = (float) imm16;
            saveVd<1>(vd, v3);
        }

        // VFPU5:VFIM
        void do$VFIM(int vd, int imm16)
        {
            v3[0] = halffloatToFloat(imm16);
            saveVd<1>(vd, v3);
        }

        // group VFPU6
        // VFPU6:VMMUL
        template< int vsize > void do$VMMUL(int vd, int vs, int vt)
        {
            // you must do it for disasm, not for emulation !
            //vs = vs ^ 32;
            for (int i = 0; i < vsize; ++i)
            {
                loadVt<vsize>(vt + i);
                for (int j = 0; j < vsize; ++j)
                {
                    loadVs<vsize>(vs + j);
                    float dot = v1[0] * v2[0];
                    for (int k = 1; k < vsize; ++k)
                    {
                        dot += v1[k] * v2[k];
                    }
                    v3[j] = dot;
                }
                saveVd<vsize>(vd + i, v3);
            }
        }

        // VFPU6:VHTFM2
        template< int vsize > void do$VHTFM2(int vd, int vs, int vt)
        {
            // you must do it for disasm, not for emulation !
            //vs = vs ^ 32;
            loadVt<1>(vt);
            loadVs<2>(vs + 0);
            v3[0] = v1[0] * v2[0] + v1[1];
            loadVs<2>(vs + 1);
            v3[1] = v1[0] * v2[0] + v1[1];
            saveVd<2>(vd, v3);
        }

        // VFPU6:VTFM2
        template< int vsize > void do$VTFM2(int vd, int vs, int vt)
        {
            // you must do it for disasm, not for emulation !
            //vs = vs ^ 32;
            loadVt<2>(vt);
            loadVs<2>(vs + 0);
            v3[0] = v1[0] * v2[0] + v1[1] * v2[1];
            loadVs<2>(vs + 1);
            v3[1] = v1[0] * v2[0] + v1[1] * v2[1];
            saveVd<2>(vd, v3);
        }

        // VFPU6:VHTFM3
        template< int vsize > void do$VHTFM3(int vd, int vs, int vt)
        {
            // you must do it for disasm, not for emulation !
            //vs = vs ^ 32;
            loadVt<2>(vt);
            loadVs<3>(vs + 0);
            v3[0] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2];
            loadVs<3>(vs + 1);
            v3[1] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2];
            loadVs<3>(vs + 2);
            v3[2] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2];
            saveVd<3>(vd, v3);
        }

        // VFPU6:VTFM3
        template< int vsize > void do$VTFM3(int vd, int vs, int vt)
        {
            // you must do it for disasm, not for emulation !
            //vs = vs ^ 32;
            loadVt<3>(vt);
            loadVs<3>(vs + 0);
            v3[0] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
            loadVs<3>(vs + 1);
            v3[1] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
            loadVs<3>(vs + 2);
            v3[2] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
            saveVd<3>(vd, v3);
        }

        // VFPU6:VHTFM4
        template< int vsize > void do$VHTFM4(int vd, int vs, int vt)
        {
            // you must do it for disasm, not for emulation !
            //vs = vs ^ 32;
            loadVt<3>(vt);
            loadVs<4>(vs + 0);
            v3[0] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3];
            loadVs<4>(vs + 1);
            v3[1] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3];
            loadVs<4>(vs + 2);
            v3[2] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3];
            loadVs<4>(vs + 3);
            v3[3] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3];
            saveVd<4>(vd, v3);
        }

        // VFPU6:VTFM4
        template< int vsize > void do$VTFM4(int vd, int vs, int vt)
        {
            // you must do it for disasm, not for emulation !
            //vs = vs ^ 32;
            loadVt<4>(vt);
            loadVs<4>(vs + 0);
            v3[0] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
            loadVs<4>(vs + 1);
            v3[1] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
            loadVs<4>(vs + 2);
            v3[2] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
            loadVs<4>(vs + 3);
            v3[3] = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
            saveVd<4>(vd, v3);
        }

        // VFPU6:VMSCL
        template< int vsize > void do$VMSCL(int vd, int vs, int vt)
        {
            for (int i = 0; i < vsize; ++i)
            {
                do$VSCL<vsize>(vd + i, vs + i, vt);
            }
        }

        // VFPU6:VCRSP
        template< int vsize > void do$VCRSP(int vd, int vs, int vt)
        {
            loadVs<3>(vs);
            loadVt<3>(vt);
            v3[0] = +v1[1] * v2[2] - v1[2] * v2[1];
            v3[1] = +v1[2] * v2[0] - v1[0] * v2[2];
            v3[2] = +v1[0] * v2[1] - v1[1] * v2[0];
            saveVd<3>(vd, v3);
        }

        // VFPU6:VQMUL
        template< int vsize > void do$VQMUL(int vd, int vs, int vt)
        {
            loadVs<4>(vs);
            loadVt<4>(vt);
            v3[0] = +v1[0] * v2[3] + v1[1] * v2[2] - v1[2] * v2[1] + v1[3] * v2[0];
            v3[1] = -v1[0] * v2[2] + v1[1] * v2[3] + v1[2] * v2[0] + v1[3] * v2[1];
            v3[2] = +v1[0] * v2[1] - v1[1] * v2[0] + v1[2] * v2[3] + v1[3] * v2[2];
            v3[3] = -v1[0] * v2[0] - v1[1] * v2[1] - v1[2] * v2[2] + v1[3] * v2[3];
            saveVd<4>(vd, v3);
        }

        // VFPU6:VMMOV
        template< int vsize > void do$VMMOV(int vd, int vs)
        {
            for (int i = 0; i < vsize; ++i)
            {
                do$VMOV<vsize>(vd + i, vs + i);
            }
        }

        // VFPU6:VMIDT
        template< int vsize > void do$VMIDT(int vd)
        {
            for (int i = 0; i < vsize; ++i)
            {
                for (int j = 0; j < vsize; ++j)
                {
                    v3[j] = (i == j) ? 1.0f : 0.0f;
                }
                saveVd<vsize>(vd + i, v3);
            }
        }

        // VFPU6:VMZERO
        template< int vsize > void do$VMZERO(int vd)
        {
            for (int i = 0; i < vsize; ++i)
            {
                do$VZERO<vsize>(vd + i);
            }
        }

        // VFPU7:VMONE
        template< int vsize > void do$VMONE(int vd)
        {
            for (int i = 0; i < vsize; ++i)
            {
                do$VONE<vsize>(vd + i);
            }
        }

        // VFPU6:VROT
        template< int vsize > void do$VROT(int vd, int vs, int imm5)
        {
            loadVs<1>(vs);
            double a = 0.5 * (float)M_PI * v1[0];
            double ca = cos(a);
            double sa = sin(a);
            int i;
            int si = ((u32)imm5 >> 2) & 3;
            int ci = ((u32)imm5 >> 0) & 3;
            if (((imm5 & 16) != 0))
            {
                sa = 0.0 - sa;
            }
            if (si == ci)
            {
                for (i = 0; i < vsize; ++i)
                {
                    v3[i] = (float) sa;
                }
            }
            else
            {
                for (i = 0; i < vsize; ++i)
                {
                    v3[i] = (float) 0.0;
                }
                v3[si] = (float) sa;
            }
            v3[ci] = (float) ca;
            saveVd<vsize>(vd, v3);
        }

        // group VLSU
        // LSU:LVS
        void do$LV_S(int vt, int rs, int simm14_a16)
        {
            int s = (vt >> 5) & 3;
            int m = (vt >> 2) & 7;
            int i = (vt >> 0) & 3;
            *((u32 *)(&vpr[m][i][s])) = *lle::mmu::Addr< u32 >(gpr[rs] + simm14_a16);
        }

        // LSU:SVS
        void do$SV_S(int vt, int rs, int simm14_a16)
        {
            int s = (vt >> 5) & 3;
            int m = (vt >> 2) & 7;
            int i = (vt >> 0) & 3;
            *lle::mmu::Addr< u32 >(gpr[rs] + simm14_a16) = *((u32 *)(&vpr[m][i][s]));
        }

        // LSU:LVQ
        void do$LV_Q(int vt, int rs, int simm14_a16)
        {
            int m = (vt >> 2) & 7;
            int i = (vt >> 0) & 3;
            int address = gpr[rs] + simm14_a16;
            u32 *p = lle::mmu::Addr< u32 >(address);
            if ((vt & 32) != 0)
            {
                for (int j = 0; j < 4; ++j)
                {
                    *((u32 *)(&vpr[m][j][i])) = *p++;
                }
            }
            else
            {
                for (int j = 0; j < 4; ++j)
                {
                    *((u32 *)(&vpr[m][i][j])) = *p++;
                }
            }
        }

        // LSU:LVLQ
        void do$LVL_Q(int vt, int rs, int simm14_a16)
        {
            int m = (vt >> 2) & 7;
            int i = (vt >> 0) & 3;
            int address = gpr[rs] + simm14_a16;
            int k = 3 - ((address >> 2) & 3);
            u32 *p = lle::mmu::Addr< u32 >(address & ~15);
            if ((vt & 32) != 0)
            {
                for (int j = k; j < 4; ++j)
                {
                    *((u32 *)(&vpr[m][j][i])) = *p++;
                }
            }
            else
            {
                for (int j = k; j < 4; ++j)
                {
                    *((u32 *)(&vpr[m][i][j])) = *p++;
                }
            }
        }

        // LSU:LVRQ
        void do$LVR_Q(int vt, int rs, int simm14_a16)
        {
            int m = (vt >> 2) & 7;
            int i = (vt >> 0) & 3;
            int address = gpr[rs] + simm14_a16;
            int k = 4 - ((address >> 2) & 3);
            u32 *p = lle::mmu::Addr< u32 >(address);
            if ((vt & 32) != 0)
            {
                for (int j = 0; j < k; ++j)
                {
                    *((u32 *)(&vpr[m][j][i])) = *p++;
                }
            }
            else
            {
                for (int j = 0; j < k; ++j)
                {
                    *((u32 *)(&vpr[m][i][j])) = *p++;
                }
            }
        }

        // LSU:SVQ
        void do$SV_Q(int vt, int rs, int simm14_a16)
        {
            int m = (vt >> 2) & 7;
            int i = (vt >> 0) & 3;
            int address = gpr[rs] + simm14_a16;
            u32 *p = lle::mmu::Addr< u32 >(address);
            if ((vt & 32) != 0)
            {
                for (int j = 0; j < 4; ++j)
                {
                    *p++ = *((u32 *)(&vpr[m][j][i]));
                }
            }
            else
            {
                for (int j = 0; j < 4; ++j)
                {
                    *p++ = *((u32 *)(&vpr[m][i][j]));
                }
            }
        }

        void do$SVL_Q(int vt, int rs, int simm14_a16)
        {
            int m = (vt >> 2) & 7;
            int i = (vt >> 0) & 3;
            int address = gpr[rs] + simm14_a16;
            int k = 3 - ((address >> 2) & 3);
            u32 *p = lle::mmu::Addr< u32 >(address & ~15);
            if ((vt & 32) != 0)
            {
                for (int j = k; j < 4; ++j)
                {
                    *p++ = *((u32 *)(&vpr[m][j][i]));
                }
            }
            else
            {
                for (int j = k; j < 4; ++j)
                {
                    *p++ = *((u32 *)(&vpr[m][i][j]));
                }
            }
        }

        // LSU:SVRQ
        void do$SVR_Q(int vt, int rs, int simm14_a16)
        {
            int m = (vt >> 2) & 7;
            int i = (vt >> 0) & 3;
            int address = gpr[rs] + simm14_a16;
            int k = 4 - ((address >> 2) & 3);
            u32 *p = lle::mmu::Addr< u32 >(address);
            if ((vt & 32) != 0)
            {
                for (int j = 0; j < k; ++j)
                {
                    *p++ = *((u32 *)(&vpr[m][j][i]));
                }
            }
            else
            {
                for (int j = 0; j < k; ++j)
                {
                    *p++ = *((u32 *)(&vpr[m][i][j]));
                }
            }
        }

        __forceinline u32 &lo()
        {
            return (reinterpret_cast< u32 * > (&hilo))[0];
        }
        __forceinline u32 &hi()
        {
            return (reinterpret_cast< u32 * > (&hilo))[1];
        }

        __forceinline u32 lo() const
        {
            return (reinterpret_cast< u32 const * > (&hilo))[0];
        }
        __forceinline u32 hi() const
        {
            return (reinterpret_cast< u32 const * > (&hilo))[1];
        }

        __forceinline void do$MFHI(u32 rd)
        {
            if (rd != 0)
            {
                gpr[rd] = (u32) (hilo >> 32);
            }
        }

        __forceinline void do$MTHI(u32 rs)
        {
            hi() = gpr[rs];
        }

        __forceinline void do$MFLO(u32 rd)
        {
            if (rd != 0)
            {
                gpr[rd] = (u32) hilo;
            }
        }

        __forceinline void do$MTLO(u32 rs)
        {
            lo() = gpr[rs];
        }

        __forceinline void do$MULT(u32 rs, u32 rt)
        {
            hilo = (u64) (((s64)(s32) gpr[rs]) * ((s64)(s32) gpr[rt]));
        }

        __forceinline void do$MULTU(u32 rs, u32 rt)
        {
            hilo = ((u64) gpr[rs]) * ((u64) gpr[rt]);
        }

        __forceinline void do$DIV(u32 rs, u32 rt)
        {
            if (gpr[rt]) //TODO : in a perfect emulation world that check is useless
            {
                lo() = (u32) (((s32) gpr[rs]) / ((s32) gpr[rt]));
                hi() = (u32) (((s32) gpr[rs]) % ((s32) gpr[rt]));
            }
            else
            {
                errorf(cpu, "DIV : WARNING! an unexpected zero division is detected");
            }
        }

        __forceinline void do$DIVU(u32 rs, u32 rt)
        {
            if (gpr[rt]) //TODO : in a perfect emulation world that check is useless
            {
                lo() = ((u32) gpr[rs]) / ((u32) gpr[rt]);
                hi() = ((u32) gpr[rs]) % ((s32) gpr[rt]);
            }
            else
            {
                errorf(cpu, "DIVU : WARNING! an unexpected zero division is detected");
            }
        }

        __forceinline void do$MADD(u32 rs, u32 rt)
        {
            hilo += (u64) (((s64)(s32) gpr[rs]) * ((s64)(s32) gpr[rt]));
        }

        __forceinline void do$MADDU(u32 rs, u32 rt)
        {
            hilo += (u64) (((u64) gpr[rs]) * ((u64) gpr[rt]));
        }

        __forceinline void do$MSUB(u32 rs, u32 rt)
        {
            hilo -= (u64) (((s64)(s32) gpr[rs]) * ((s64)(s32) gpr[rt]));
        }

        __forceinline void do$MSUBU(u32 rs, u32 rt)
        {
            hilo -= ((u64) gpr[rs]) * ((u64) gpr[rt]);
        }

        //////////////////////////////////////////////////////////////////

        static bool const CHECK_ALIGNMENT = true;

        __forceinline void do$LB(u32 rt, u32 rs, s32 simm16)
        {
            if (rt != 0)
            {
                gpr[rt] = (u32) (s32) *lle::mmu::Addr< s8 >(gpr[rs] + simm16);
            }
        }

        __forceinline void do$LBU(u32 rt, u32 rs, s32 simm16)
        {
            if (rt != 0)
            {
                gpr[rt] = (u32) *lle::mmu::Addr< u8 >(gpr[rs] + simm16);
            }
        }

        __forceinline void do$LH(u32 rt, u32 rs, s32 simm16)
        {
            u32 address = gpr[rs] + simm16;
            if (rt != 0)
            {
                gpr[rt] = (u32) (s32) *lle::mmu::Addr< s16 >(address);
            }
        }

        __forceinline void do$LHU(u32 rt, u32 rs, s32 simm16)
        {
            u32 address = gpr[rs] + simm16;
            if (rt != 0)
            {
                gpr[rt] = (u32) *lle::mmu::Addr< u16 >(address);
            }
        }

        __forceinline void do$LWL(u32 rt, u32 rs, s32 simm16)
        {
            static u32 const lwl_mask[4]  = { 0xffffff, 0xffff, 0xff, 0 };
            static u32 const lwl_shift[4] = { 24, 16, 8, 0 };
            if (rt != 0)
            {
                u32 address = gpr[rs] + simm16;
                u32 offset = address & 0x3;
                u32 data = *lle::mmu::Addr< u32 >(address & 0xfffffffc);
                gpr[rt] = (data << lwl_shift[offset]) | (gpr[rt] & lwl_mask[offset]);
            }
        }

        __forceinline void do$LW(u32 rt, u32 rs, s32 simm16)
        {
            u32 address = gpr[rs] + simm16;
            if (rt != 0)
            {
                gpr[rt] = *lle::mmu::Addr< u32 >(address);
            }
        }

        __forceinline void do$LWR(u32 rt, u32 rs, s32 simm16)
        {
            static u32 const lwr_mask[4]  = { 0, 0xff000000, 0xffff0000, 0xffffff00 };
            static u32 const lwr_shift[4] = { 0, 8, 16, 24 };
            if (rt != 0)
            {
                u32 address = gpr[rs] + simm16;
                u32 offset = address & 0x3;
                u32 data = *lle::mmu::Addr< u32 >(address & 0xfffffffc);
                gpr[rt] = (data >> lwr_shift[offset]) | (gpr[rt] & lwr_mask[offset]);
            }
        }

        __forceinline void do$SB(u32 rt, u32 rs, u32 simm16)
        {
            *lle::mmu::Addr< u8 >(gpr[rs] + simm16) = (u8) gpr[rt];
        }

        __forceinline void do$SH(u32 rt, u32 rs, u32 simm16)
        {
            u32 address = gpr[rs] + simm16;
            *lle::mmu::Addr< u16 >(address) = (u16) gpr[rt];
        }

        __forceinline void do$SWL(u32 rt, u32 rs, s32 simm16)
        {
            static u32 const swl_mask[4]  = { 0xffffff00, 0xffff0000, 0xff000000, 0 };
            static u32 const swl_shift[4] = { 24, 16, 8, 0 };
            u32 address = gpr[rs] + simm16;
            u32 offset = address & 0x3;
            address &= 0xfffffffc;
            *lle::mmu::Addr< u32 >(address) = (gpr[rt] >> swl_shift[offset]) | (*lle::mmu::Addr< u32 >(address) & swl_mask[offset]);
        }

        __forceinline void do$SW(u32 rt, u32 rs, u32 simm16)
        {
            u32 address = gpr[rs] + simm16;
            *lle::mmu::Addr< u32 >(address) = gpr[rt];
        }

        __forceinline void do$SWR(u32 rt, u32 rs, s32 simm16)
        {
            static u32 const swl_mask[4]  = { 0, 0xff, 0xffff, 0xffffff };
            static u32 const swl_shift[4] = { 0, 8, 16, 24 };
            u32 address = gpr[rs] + simm16;
            u32 offset = address & 0x3;
            address &= 0xfffffffc;
            *lle::mmu::Addr< u32 >( address) = (gpr[rt] << swl_shift[offset]) | (*lle::mmu::Addr< u32 >(address) & swl_mask[offset]);
        }

        __forceinline void do$LL(u32 rt, u32 rs, s32 simm16)
        {
            u32 address = gpr[rs] + simm16;
            if (rt != 0)
            {
                gpr[rt] = (u32) *lle::mmu::Addr< u32 >(address);
            }
            // llbit = 1;
        }

        __forceinline void do$SC(u32 rt, u32 rs, u32 simm16)
        {
            u32 address = gpr[rs] + simm16;
            *lle::mmu::Addr< u32 >( address) = gpr[rt];
            gpr[rt] = 1; // = ll_bit;
        }

        __forceinline void do$LWC1(u32 ft, u32 rs, u32 simm16)
        {
            u32 address = gpr[rs] + simm16;
            fpr[ft] = *lle::mmu::Addr< f32 >(address);
        }

        __forceinline void do$SWC1(u32 ft, u32 rs, u32 simm16)
        {
            u32 address = gpr[rs] + simm16;
            *lle::mmu::Addr< f32 >(address) = fpr[ft];
        }

        ///////////////////////////////////////////////////////////////////////////////

        __forceinline static u32 branch_target(u32 npc, s32 simm16)
        {
            return npc + (simm16 << 2);
        }

        __forceinline static u32 jump_target(u32 npc, u32 uimm26)
        {
            return (npc & 0xf0000000) | (uimm26 << 2);
        }

        __forceinline u32 FetchOpcode()
        {
            npc = pc + 4;

            u32 opcode = *lle::mmu::Addr< u32 >(pc);

            // by default, the next instruction to emulate is at the next address
            pc = npc;

            return opcode;
        }

        __forceinline u32 FetchDelayslotOpcode()
        {
            u32 opcode = *lle::mmu::Addr< u32 >(pc);

            // by default, the next instruction to emulate is at the next address
            pc += 4;

            return opcode;
        }

        __forceinline void NextPC()
        {
            pc = npc;
            npc = pc + 4;
        }

        __forceinline bool do$JR(u32 rs)
        {
            npc = gpr[rs];
            return true;
        }

        __forceinline bool do$JRA()
        {
            npc = gpr[31];
            return true;
        }

        __forceinline bool do$JRALR(u32 rs)
        {
            gpr[31] = pc + 4;
            npc = gpr[rs];
            return true;
        }

        __forceinline bool do$JALR(u32 rd, u32 rs)
        {
            if (rd != 0)
            {
                gpr[rd] = pc + 4;
            }
            npc = gpr[rs];
            return true;
        }

        __forceinline bool do$BLTZ(u32 rs, s32 simm16)
        {
            npc = (s32(gpr[rs]) < 0) ? branch_target(pc, simm16) : (pc + 4);
            return true;
        }

        __forceinline bool do$BGEZ(u32 rs, s32 simm16)
        {
            npc = (s32(gpr[rs]) >= 0) ? branch_target(pc, simm16) : (pc + 4);
            return true;
        }

        __forceinline bool do$BLTZL(u32 rs, s32 simm16)
        {
            if (s32(gpr[rs]) < 0)
            {
                npc = branch_target(pc, simm16);
                return true;
            }
            else
            {
                pc += 4;
            }
            return false;
        }

        __forceinline bool do$BGEZL(u32 rs, s32 simm16)
        {
            if (s32(gpr[rs]) >= 0)
            {
                npc = branch_target(pc, simm16);
                return true;
            }
            else
            {
                pc += 4;
            }
            return false;
        }

        __forceinline bool do$BLTZAL(u32 rs, u32 simm16)
        {
            u32 target = pc + 4;
            bool t = (s32(gpr[rs]) < 0);
            gpr[31] = target;
            npc = t ? branch_target(pc, simm16) : target;
            return true;
        }

        __forceinline bool do$BGEZAL(u32 rs, u32 simm16)
        {
            u32 target = pc + 4;
            bool t = (s32(gpr[rs]) >= 0);
            gpr[31] = target;
            npc = t ? branch_target(pc, simm16) : target;
            return true;
        }

        __forceinline bool do$BLTZALL(u32 rs, s32 simm16)
        {
            bool t = (s32(gpr[rs]) < 0);
            gpr[31] = pc + 4;
            if (t)
            {
                npc = branch_target(pc, simm16);
            }
            else
            {
                pc += 4;
            }
            return t;
        }

        __forceinline bool do$BGEZALL(u32 rs, s32 simm16)
        {
            bool t = (s32(gpr[rs]) >= 0);
            gpr[31] = pc + 4;
            if (t)
            {
                npc = branch_target(pc, simm16);
            }
            else
            {
                pc += 4;
            }
            return t;
        }

        __forceinline bool do$J(u32 uimm26)
        {
            npc = jump_target(pc, uimm26);
            if (npc == pc - 4)
            {
                //Processor.log.info("Pausing emulator - jump to self (death loop)");
                //Emulator.PauseEmuWithStatus(Emulator.EMU_STATUS_JUMPSELF);
            }
            return true;
        }

        __forceinline bool do$JAL(u32 uimm26)
        {
            gpr[31] = pc + 4;
            npc = jump_target(pc, uimm26);
            return true;
        }

        __forceinline bool do$BEQ(u32 rs, u32 rt, s32 simm16)
        {
            npc = (gpr[rs] == gpr[rt]) ? branch_target(pc, simm16) : (pc + 4);
            return true;
        }

        __forceinline bool do$BNE(u32 rs, u32 rt, u32 simm16)
        {
            npc = (gpr[rs] != gpr[rt]) ? branch_target(pc, simm16) : (pc + 4);
            return true;
        }

        __forceinline bool do$BLEZ(u32 rs, u32 simm16)
        {
            npc = (s32(gpr[rs]) <= 0) ? branch_target(pc, simm16) : (pc + 4);
            return true;
        }

        __forceinline bool do$BGTZ(u32 rs, u32 simm16)
        {
            npc = (s32(gpr[rs]) > 0) ? branch_target(pc, simm16) : (pc + 4);
            return true;
        }

        __forceinline bool do$BEQL(u32 rs, u32 rt, s32 simm16)
        {
            if (gpr[rs] == gpr[rt])
            {
                npc = branch_target(pc, simm16);
                return true;
            }
            else
            {
                pc += 4;
            }
            return false;
        }

        __forceinline bool do$BNEL(u32 rs, u32 rt, s32 simm16)
        {
            if (gpr[rs] != gpr[rt])
            {
                npc = branch_target(pc, simm16);
                return true;
            }
            else
            {
                pc += 4;
            }
            return false;
        }

        __forceinline bool do$BLEZL(u32 rs, s32 simm16)
        {
            if (s32(gpr[rs]) <= 0)
            {
                npc = branch_target(pc, simm16);
                return true;
            }
            else
            {
                pc += 4;
            }
            return false;
        }

        __forceinline bool do$BGTZL(u32 rs, s32 simm16)
        {
            if (s32(gpr[rs]) > 0)
            {
                npc = branch_target(pc, simm16);
                return true;
            }
            else
            {
                pc += 4;
            }
            return false;
        }

        __forceinline bool do$BC1F(s32 simm16)
        {
            npc = ((fcr31 & (1 << 23)) == 0) ? branch_target(pc, simm16) : (pc + 4);
            return true;
        }

        __forceinline bool do$BC1T(s32 simm16)
        {
            npc = ((fcr31 & (1 << 23)) != 0) ? branch_target(pc, simm16) : (pc + 4);
            return true;
        }

        __forceinline bool do$BC1FL(s32 simm16)
        {
            if ((fcr31 & (1 << 23)) == 0)
            {
                npc = branch_target(pc, simm16);
                return true;
            }
            else
            {
                pc += 4;
            }
            return false;
        }

        __forceinline bool do$BC1TL(s32 simm16)
        {
            if ((fcr31 & (1 << 23)) != 0)
            {
                npc = branch_target(pc, simm16);
                return true;
            }
            else
            {
                pc += 4;
            }
            return false;
        }

        //////////////////////////////////////////////////////////////////////////

        __forceinline bool do$BEQ(u32 rs, u32 rt, s32 simm16, bool &t)
        {
            (void)simm16;
            t = gpr[rs] == gpr[rt];
            return true;
        }

        __forceinline bool do$BNE(u32 rs, u32 rt, u32 simm16, bool &t)
        {
            (void)simm16;
            t = gpr[rs] != gpr[rt];
            return true;
        }

        __forceinline bool do$BLTZ(u32 rs, s32 simm16, bool &t)
        {
            (void)simm16;
            t = s32(gpr[rs]) < 0;
            return true;
        }

        __forceinline bool do$BGEZ(u32 rs, s32 simm16, bool &t)
        {
            (void)simm16;
            t = s32(gpr[rs]) >= 0;
            return true;
        }

        __forceinline bool do$BLTZL(u32 rs, s32 simm16, bool &t)
        {
            (void)simm16;
            t = s32(gpr[rs]) < 0;
            return t;
        }

        __forceinline bool do$BGEZL(u32 rs, s32 simm16, bool &t)
        {
            (void)simm16;
            t = s32(gpr[rs]) >= 0;
            return t;
        }

        __forceinline bool do$BLEZ(u32 rs, u32 simm16, bool &t)
        {
            (void)simm16;
            t = s32(gpr[rs]) <= 0;
            return true;
        }

        __forceinline bool do$BGTZ(u32 rs, u32 simm16, bool &t)
        {
            (void)simm16;
            t = s32(gpr[rs]) > 0;
            return true;
        }

        __forceinline bool do$BEQL(u32 rs, u32 rt, s32 simm16, bool &t)
        {
            (void)simm16;
            t = gpr[rs] == gpr[rt];
            return t;
        }

        __forceinline bool do$BNEL(u32 rs, u32 rt, s32 simm16, bool &t)
        {
            (void)simm16;
            t = gpr[rs] != gpr[rt];
            return t;
        }

        __forceinline bool do$BLEZL(u32 rs, s32 simm16, bool &t)
        {
            (void)simm16;
            t = s32(gpr[rs]) <= 0;
            return t;
        }

        __forceinline bool do$BGTZL(u32 rs, s32 simm16, bool &t)
        {
            (void)simm16;
            t = s32(gpr[rs]) > 0;
            return t;
        }

        __forceinline bool do$BC1F(s32 simm16, bool &t)
        {
            (void)simm16;
            t = (fcr31 & (1 << 23)) == 0;
            return true;
        }

        __forceinline bool do$BC1T(s32 simm16, bool &t)
        {
            (void)simm16;
            t = (fcr31 & (1 << 23)) != 0;
            return true;
        }

        __forceinline bool do$BC1FL(s32 simm16, bool &t)
        {
            (void)simm16;
            t = (fcr31 & (1 << 23)) == 0;
            return t;
        }

        __forceinline bool do$BC1TL(s32 simm16, bool &t)
        {
            (void)simm16;
            t = (fcr31 & (1 << 23)) != 0;
            return t;
        }


        Allegrex::Context();

        void Reset();

        void do$UNK(char const *reason) { warnf(cpu, "%s", reason); }

        void Interpret();

        void InterpretDebug();

#ifndef BUILDING_SPECIFIC_GAME_EMULATOR
        __forceinline bool InterpretAutogeneratedCode() { return false; }
#else
        bool InterpretAutogeneratedCode();
#endif

        void InterpretDelayslot();

        void do$SYSCALL(u32 code);

        void Breakpoint();

        void RunThread() {}

        void Step();

        static void CountInstructions();

        void SetTrampoline(u32 address);

        void CrossInterpret_(u32 address);

        static void Syscall(Context * that, u32 code);

        static u64  Recompile(Context * that, u32 address);

        static void CrossInterpret(Context * that, u32 address);

        static void Trace(Context * that, u32 address);
    };
}


enum AllegrexGpr
{
    ALLEGREX_ZR = 0,
    ALLEGREX_AT = 1,
    ALLEGREX_V0 = 2,
    ALLEGREX_V1 = 3,
    ALLEGREX_A0 = 4,
    ALLEGREX_A1 = 5,
    ALLEGREX_A2 = 6,
    ALLEGREX_A3 = 7,
    ALLEGREX_T0 = 8,  ALLEGREX_A4 = ALLEGREX_T0,
    ALLEGREX_T1 = 9,  ALLEGREX_A5 = ALLEGREX_T1,
    ALLEGREX_T2 = 10, ALLEGREX_A6 = ALLEGREX_T2,
    ALLEGREX_T3 = 11, ALLEGREX_A7 = ALLEGREX_T3,
    ALLEGREX_T4 = 12,
    ALLEGREX_T5 = 13,
    ALLEGREX_T6 = 14,
    ALLEGREX_T7 = 15,
    ALLEGREX_S0 = 16,
    ALLEGREX_S1 = 17,
    ALLEGREX_S2 = 18,
    ALLEGREX_S3 = 19,
    ALLEGREX_S4 = 20,
    ALLEGREX_S5 = 21,
    ALLEGREX_S6 = 22,
    ALLEGREX_S7 = 23,
    ALLEGREX_T8 = 24,
    ALLEGREX_T9 = 25,
    ALLEGREX_K0 = 26,
    ALLEGREX_K1 = 27,
    ALLEGREX_GP = 28,
    ALLEGREX_SP = 29,
    ALLEGREX_FP = 30, ALLEGREX_S8 = ALLEGREX_FP,
    ALLEGREX_RA = 31
};

enum AllegrexFpr
{
    ALLEGREX_F0  =  0,
    ALLEGREX_F1  =  1,
    ALLEGREX_F2  =  2,
    ALLEGREX_F3  =  3,
    ALLEGREX_F4  =  4,
    ALLEGREX_F5  =  5,
    ALLEGREX_F6  =  6,
    ALLEGREX_F7  =  7,
    ALLEGREX_F8  =  8,
    ALLEGREX_F9  =  9,
    ALLEGREX_F10 = 10,
    ALLEGREX_F11 = 11,
    ALLEGREX_F12 = 12,
    ALLEGREX_F13 = 13,
    ALLEGREX_F14 = 14,
    ALLEGREX_F15 = 15,
    ALLEGREX_F16 = 16,
    ALLEGREX_F17 = 17,
    ALLEGREX_F18 = 18,
    ALLEGREX_F19 = 19,
    ALLEGREX_F20 = 20,
    ALLEGREX_F21 = 21,
    ALLEGREX_F22 = 22,
    ALLEGREX_F23 = 23,
    ALLEGREX_F24 = 24,
    ALLEGREX_F25 = 25,
    ALLEGREX_F26 = 26,
    ALLEGREX_F27 = 27,
    ALLEGREX_F28 = 28,
    ALLEGREX_F29 = 29,
    ALLEGREX_F30 = 30,
    ALLEGREX_F31 = 31
};
