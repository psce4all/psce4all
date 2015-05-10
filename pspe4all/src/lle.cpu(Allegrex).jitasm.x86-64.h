// jitasm version adapted pspe4all needs

// Copyright (c) 2009-2011, Hikaru Inoue, Akihiro Yamasaki,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
//      copyright notice, this list of conditions and the following
//      disclaimer in the documentation and/or other materials provided
//      with the distribution.
//    * The names of the contributors may not be used to endorse or promote
//      products derived from this software without specific prior written
//      permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef __allegrex_jit_x86_64_h__
#define __allegrex_jit_x86_64_h__

#include <string>
#include <deque>
#include <vector>
#include <map>
#include <algorithm>
#include <string.h>

#include <windows.h>

#include <mmintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <intrin.h>

#define JITASM_ATTRIBUTE_WEAK __declspec(selectany)

#pragma warning( push )
#pragma warning( disable : 4127 )   // conditional expression is constant.
#pragma warning( disable : 4201 )   // nonstandard extension used : nameless struct/union

#define ASSERT(e) if (!(e)) __debugbreak();
#ifdef ASSERT
#   define JITASM_ASSERT ASSERT
#else
#   include <assert.h>
#   define JITASM_ASSERT assert
#endif

#   include <stdio.h>
#   include "emu.log.h"
namespace emu
{
    namespace log
    {
        extern SubCategory cpu;
    }
}
//#define JITASM_DEBUG_DUMP
#ifdef JITASM_DEBUG_DUMP
#   define JITASM_TRACE jitasm::detail::Trace
#else
#   define JITASM_TRACE __noop
#endif

namespace Allegrex
{
    namespace jitasm
    {

        typedef signed char         sint8;
        typedef signed short        sint16;
        typedef signed int          sint32;
        typedef unsigned char       uint8;
        typedef unsigned short      uint16;
        typedef unsigned int        uint32;
        typedef signed __int64      sint64;
        typedef unsigned __int64    uint64;

        template<typename T> inline void avoid_unused_warn(const T&)
        {
        }

        namespace detail
        {
            inline long interlocked_increment(long *addend)
            {
                return _InterlockedIncrement(addend);
            }
            inline long interlocked_decrement(long *addend)
            {
                return _InterlockedDecrement(addend);
            }
            inline long interlocked_exchange(long *target, long value)
            {
                return _InterlockedExchange(target, value);
            }
        }   // namespace detail

        /// Physical register ID
        enum PhysicalRegID
        {
            INVALID=0x0FFFFFFF,
            EAX=0, ECX, EDX, EBX, ESP, EBP, ESI, EDI, R8D, R9D, R10D, R11D, R12D, R13D, R14D, R15D,
            AL=0, CL, DL, BL, AH, CH, DH, BH, R8B, R9B, R10B, R11B, R12B, R13B, R14B, R15B,
            AX=0, CX, DX, BX, SP, BP, SI, DI, R8W, R9W, R10W, R11W, R12W, R13W, R14W, R15W,
            RAX=0, RCX, RDX, RBX, RSP, RBP, RSI, RDI, R8, R9, R10, R11, R12, R13, R14, R15,
            ST0=0, ST1, ST2, ST3, ST4, ST5, ST6, ST7,
            MM0=0, MM1, MM2, MM3, MM4, MM5, MM6, MM7,
            XMM0=0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7, XMM8, XMM9, XMM10, XMM11, XMM12, XMM13, XMM14, XMM15,
            YMM0=0, YMM1, YMM2, YMM3, YMM4, YMM5, YMM6, YMM7, YMM8, YMM9, YMM10, YMM11, YMM12, YMM13, YMM14, YMM15,
            EIP=0,
            RIP=0,
        };

        enum AllegrexRegID
        {
            $ZR=0, $AT, $V0, $V1, $A0, $A1, $A2, $A3, $T0, $T1, $T2, $T3, $T4, $T5, $T6, $T7, $S0, $S1, $S2, $S3, $S4, $S5, $S6, $S7, $T8, $T9, $K0, $K1, $GP, $SP, $S8, $RA
        };

        enum
        {
            /** \var NUM_OF_PHYSICAL_REG
            * Number of physical register
            */
            /** \var SIZE_OF_GP_REG
            * Size of general-purpose register
            */
            NUM_OF_PHYSICAL_REG = 16,
            SIZE_OF_GP_REG = 8
        };

        /// Register type
        enum RegType
        {
            R_TYPE_GP,              ///< General purpose register
            R_TYPE_MMX,             ///< MMX register
            R_TYPE_XMM,             ///< XMM register
            R_TYPE_YMM,             ///< YMM register
            R_TYPE_FPU,             ///< FPU register
            R_TYPE_IP,              ///< instruction pointer register
            R_TYPE_SYMBOLIC_GP,     ///< Symbolic general purpose register
            R_TYPE_SYMBOLIC_MMX,    ///< Symbolic MMX register
            R_TYPE_SYMBOLIC_XMM,    ///< Symbolic XMM register
            R_TYPE_SYMBOLIC_YMM,    ///< Symbolic YMM register
            R_TYPE_ALLEGREX_GPR,
            R_TYPE_ALLEGREX_FPR,
            R_TYPE_ALLEGREX_VPR
        };

        /// Register identifier
        struct RegID
        {
            unsigned type : 4;  // RegType
            unsigned id : 28;       ///< PhysicalRegID or symbolic register id

            bool operator==(const RegID& rhs) const
            {
                return type == rhs.type && id == rhs.id;
            }
            bool operator!=(const RegID& rhs) const
            {
                return !(*this == rhs);
            }
            bool operator<(const RegID& rhs) const
            {
                return type != rhs.type ? type < rhs.type : id < rhs.id;
            }
            bool IsInvalid() const
            {
                return type == R_TYPE_GP && id == INVALID;
            }
            bool IsSymbolic() const
            {
                return type == R_TYPE_SYMBOLIC_GP || type == R_TYPE_SYMBOLIC_MMX || type == R_TYPE_SYMBOLIC_XMM || type == R_TYPE_SYMBOLIC_YMM;
            }
            bool IsAllegrex() const
            {
                return type == R_TYPE_ALLEGREX_GPR || type == R_TYPE_ALLEGREX_FPR || type == R_TYPE_ALLEGREX_VPR;
            }
            RegType GetType() const
            {
                return static_cast<RegType>(type);
            }

            static RegID Invalid()
            {
                RegID reg;
                reg.type = R_TYPE_GP;
                reg.id = INVALID;
                return reg;
            }
            static RegID CreatePhysicalRegID(RegType type_, PhysicalRegID id_)
            {
                RegID reg;
                reg.type = type_;
                reg.id = id_;
                return reg;
            }
            static RegID CreateSymbolicRegID(RegType type_)
            {
                static long s_id = 0;
                RegID reg;
                reg.type = type_;
                reg.id = static_cast<unsigned>(detail::interlocked_increment(&s_id));
                return reg;
            }
            static RegID CreateAllegrexRegID(RegType type_, unsigned id_)
            {
                RegID reg;
                reg.type = type_;
                reg.id = id_;
                return reg;
            }
            static RegID DuplicateRegID(const RegID& rhs)
            {
                RegID reg;
                reg.type = rhs.type;
                reg.id = rhs.id;
                return reg;
            }
        };

        /// Operand type
        enum OpdType
        {
            O_TYPE_NONE,
            O_TYPE_REG,
            O_TYPE_MEM,
            O_TYPE_IMM,
            O_TYPE_TYPE_MASK        = 0x03,

            O_TYPE_DUMMY    = 1 << 2,   ///< The operand which has this flag is not encoded. This is for register allocator.
            O_TYPE_READ     = 1 << 3,   ///< The operand is used for reading.
            O_TYPE_WRITE    = 1 << 4    ///< The operand is used for writing.
        };

        /// Operand size
        enum OpdSize
        {
            O_SIZE_8,
            O_SIZE_16,
            O_SIZE_32,
            O_SIZE_64,
            O_SIZE_80,
            O_SIZE_128,
            O_SIZE_224,
            O_SIZE_256,
            O_SIZE_864,
            O_SIZE_4096
        };

        namespace detail
        {
#pragma pack(push, 1)

            /// Operand base class
            struct Opd
            {
                uint8 opdtype_; // OpdType
                uint8 opdsize_; // OpdSize

                union
                {
                    // REG
                    struct
                    {
                        RegID reg_;
                        uint32 reg_assignable_;
                    };
                    // MEM
                    struct
                    {
                        RegID   base_;
                        RegID   index_;
                        sint64  scale_;
                        sint64  disp_;
                        uint8   base_size_  : 4;        // OpdSize
                        uint8   index_size_ : 4;    // OpdSize
                    };
                    // IMM
                    sint64 imm_;
                };

                /// NONE
                Opd() : opdtype_(O_TYPE_NONE)
                {
                }
                /// REG
                Opd(OpdSize opdsize, const RegID& reg, uint32 reg_assignable = 0xFFFFFFFF) : opdtype_(O_TYPE_REG), opdsize_(static_cast<uint8>(opdsize)), reg_(reg), reg_assignable_(reg_assignable)
                {
                }
                /// MEM
                Opd(OpdSize opdsize, OpdSize base_size, OpdSize index_size, const RegID& base, const RegID& index, sint64 scale, sint64 disp)
                    : opdtype_(O_TYPE_MEM), opdsize_(static_cast<uint8>(opdsize)), base_(base), index_(index), scale_(scale), disp_(disp), base_size_(static_cast<uint8>(base_size)), index_size_(static_cast<uint8>(index_size))
                {
                }
            protected:
                /// IMM
                explicit Opd(OpdSize opdsize, sint64 imm) : opdtype_(O_TYPE_IMM), opdsize_(static_cast<uint8>(opdsize)), imm_(imm)
                {
                }

            public:
                bool    IsNone() const
                {
                    return (opdtype_ & O_TYPE_TYPE_MASK) == O_TYPE_NONE;
                }
                bool    IsReg() const
                {
                    return (opdtype_ & O_TYPE_TYPE_MASK) == O_TYPE_REG;
                }
                bool    IsGpReg() const
                {
                    return IsReg() && (reg_.type == R_TYPE_GP || reg_.type == R_TYPE_SYMBOLIC_GP);
                }
                bool    IsFpuReg() const
                {
                    return IsReg() && reg_.type == R_TYPE_FPU;
                }
                bool    IsMmxReg() const
                {
                    return IsReg() && (reg_.type == R_TYPE_MMX || reg_.type == R_TYPE_SYMBOLIC_MMX);
                }
                bool    IsXmmReg() const
                {
                    return IsReg() && (reg_.type == R_TYPE_XMM || reg_.type == R_TYPE_SYMBOLIC_XMM);
                }
                bool    IsYmmReg() const
                {
                    return IsReg() && (reg_.type == R_TYPE_YMM || reg_.type == R_TYPE_SYMBOLIC_YMM);
                }
                bool    IsRip() const
                {
                    return IsReg() && reg_.type == R_TYPE_IP;
                }
                bool    IsMem() const
                {
                    return (opdtype_ & O_TYPE_TYPE_MASK) == O_TYPE_MEM;
                }
                bool    IsImm() const
                {
                    return (opdtype_ & O_TYPE_TYPE_MASK) == O_TYPE_IMM;
                }
                bool    IsDummy() const
                {
                    return (opdtype_ & O_TYPE_DUMMY) != 0;
                }
                bool    IsRead() const
                {
                    return (opdtype_ & O_TYPE_READ) != 0;
                }
                bool    IsWrite() const
                {
                    return (opdtype_ & O_TYPE_WRITE) != 0;
                }

                OpdType GetType() const
                {
                    return static_cast<OpdType>(opdtype_);
                }
                OpdSize GetSize() const
                {
                    return static_cast<OpdSize>(opdsize_);
                }
                OpdSize GetAddressBaseSize() const
                {
                    return static_cast<OpdSize>(base_size_);
                }
                OpdSize GetAddressIndexSize() const
                {
                    return static_cast<OpdSize>(index_size_);
                }
                RegID   GetReg() const
                {
                    JITASM_ASSERT(IsReg()); return reg_;
                }
                RegID   GetBase() const
                {
                    JITASM_ASSERT(IsMem()); return base_;
                }
                RegID   GetIndex() const
                {
                    JITASM_ASSERT(IsMem()); return index_;
                }
                sint64  GetScale() const
                {
                    JITASM_ASSERT(IsMem()); return scale_;
                }
                sint64  GetDisp() const
                {
                    JITASM_ASSERT(IsMem()); return disp_;
                }
                sint64  GetImm() const
                {
                    JITASM_ASSERT(IsImm()); return imm_;
                }

                bool operator==(const Opd& rhs) const
                {
                    if ((opdtype_ & O_TYPE_TYPE_MASK) != (rhs.opdtype_ & O_TYPE_TYPE_MASK) || opdsize_ != rhs.opdsize_)
                    {
                        return false;
                    }
                    if (IsReg())
                    {
                        return reg_ == rhs.reg_ && reg_assignable_ == rhs.reg_assignable_;
                    }
                    if (IsMem())
                    {
                        return base_ == rhs.base_ && index_ == rhs.index_ && scale_ == rhs.scale_ && disp_ == rhs.disp_ && base_size_ == rhs.base_size_ && index_size_ == rhs.index_size_;
                    }
                    if (IsImm())
                    {
                        return imm_ == rhs.imm_;
                    }
                    return true;
                }
                bool operator!=(const Opd& rhs) const
                {
                    return !(*this == rhs);
                }
            };

#pragma pack(pop)

            /// Add O_TYPE_DUMMY to the specified operand
            inline Opd Dummy(const Opd& opd)
            {
                Opd o(opd);
                o.opdtype_ = static_cast<OpdType>(static_cast<int>(o.opdtype_) | O_TYPE_DUMMY);
                return o;
            }

            /// Add O_TYPE_DUMMY to the specified operand and constraint of register assignment
            inline Opd Dummy(const Opd& opd, const Opd& constraint)
            {
                JITASM_ASSERT(opd.IsReg() && (opd.opdtype_ & O_TYPE_TYPE_MASK) == (constraint.opdtype_ & O_TYPE_TYPE_MASK) && !constraint.GetReg().IsSymbolic());
                Opd o(opd);
                o.opdtype_ = static_cast<OpdType>(static_cast<int>(o.opdtype_ & O_TYPE_TYPE_MASK) | O_TYPE_DUMMY);
                o.reg_assignable_ = (1 << constraint.reg_.id);
                return o;
            }

            /// Add O_TYPE_READ to the specified operand
            inline Opd R(const Opd& opd)
            {
                Opd o(opd);
                o.opdtype_ = static_cast<OpdType>(static_cast<int>(o.opdtype_ & O_TYPE_TYPE_MASK) | O_TYPE_READ);
                return o;
            }

            /// Add O_TYPE_WRITE to the specified operand
            inline Opd W(const Opd& opd)
            {
                Opd o(opd);
                o.opdtype_ = static_cast<OpdType>(static_cast<int>(o.opdtype_ & O_TYPE_TYPE_MASK) | O_TYPE_WRITE);
                return o;
            }

            /// Add O_TYPE_READ | O_TYPE_WRITE to the specified operand
            inline Opd RW(const Opd& opd)
            {
                Opd o(opd);
                o.opdtype_ = static_cast<OpdType>(static_cast<int>(o.opdtype_ & O_TYPE_TYPE_MASK) | O_TYPE_READ | O_TYPE_WRITE);
                return o;
            }

            template<int Size> inline OpdSize ToOpdSize();
            template<> inline OpdSize ToOpdSize<8>()
            {
                return O_SIZE_8;
            }
            template<> inline OpdSize ToOpdSize<16>()
            {
                return O_SIZE_16;
            }
            template<> inline OpdSize ToOpdSize<32>()
            {
                return O_SIZE_32;
            }
            template<> inline OpdSize ToOpdSize<64>()
            {
                return O_SIZE_64;
            }
            template<> inline OpdSize ToOpdSize<80>()
            {
                return O_SIZE_80;
            }
            template<> inline OpdSize ToOpdSize<128>()
            {
                return O_SIZE_128;
            }
            template<> inline OpdSize ToOpdSize<224>()
            {
                return O_SIZE_224;
            }
            template<> inline OpdSize ToOpdSize<256>()
            {
                return O_SIZE_256;
            }
            template<> inline OpdSize ToOpdSize<864>()
            {
                return O_SIZE_864;
            }
            template<> inline OpdSize ToOpdSize<4096>()
            {
                return O_SIZE_4096;
            }

            template<int Size>
            struct OpdT : Opd
            {
                /// NONE
                OpdT() : Opd()
                {
                }
                /// REG
                explicit OpdT(const RegID& reg, uint32 reg_assignable = 0xFFFFFFFF) : Opd(ToOpdSize<Size>(), reg, reg_assignable)
                {
                }
                /// MEM
                OpdT(OpdSize base_size, OpdSize index_size, const RegID& base, const RegID& index, sint64 scale, sint64 disp)
                    : Opd(ToOpdSize<Size>(), base_size, index_size, base, index, scale, disp)
                {
                }
            protected:
                /// IMM
                OpdT(sint64 imm) : Opd(ToOpdSize<Size>(), imm)
                {
                }
            };

        }   // namespace detail

        typedef detail::OpdT<8>     Opd8;
        typedef detail::OpdT<16>    Opd16;
        typedef detail::OpdT<32>    Opd32;
        typedef detail::OpdT<64>    Opd64;
        typedef detail::OpdT<80>    Opd80;
        typedef detail::OpdT<128>   Opd128;
        typedef detail::OpdT<224>   Opd224;     // FPU environment
        typedef detail::OpdT<256>   Opd256;
        typedef detail::OpdT<864>   Opd864;     // FPU state
        typedef detail::OpdT<4096>  Opd4096;    // FPU, MMX, XMM, MXCSR state

        /// 8bit general purpose register
        struct Reg8 : Opd8
        {
            Reg8() : Opd8(RegID::CreateSymbolicRegID(R_TYPE_SYMBOLIC_GP), 0xFFFFFF0F)
            {
            }
            explicit Reg8(PhysicalRegID id) : Opd8(RegID::CreatePhysicalRegID(R_TYPE_GP, id))
            {
            }
            explicit Reg8(AllegrexRegID id) : Opd8(RegID::CreateAllegrexRegID(R_TYPE_ALLEGREX_GPR, id))
            {
            }
        };
        /// 16bit general purpose register
        struct Reg16 : Opd16
        {
            Reg16() : Opd16(RegID::CreateSymbolicRegID(R_TYPE_SYMBOLIC_GP))
            {
            }
            explicit Reg16(PhysicalRegID id) : Opd16(RegID::CreatePhysicalRegID(R_TYPE_GP, id))
            {
            }
            explicit Reg16(AllegrexRegID id) : Opd16(RegID::CreateAllegrexRegID(R_TYPE_ALLEGREX_GPR, id))
            {
            }
        };
        /// 32bit general purpose register
        struct Reg32 : Opd32
        {
            Reg32() : Opd32(RegID::CreateSymbolicRegID(R_TYPE_SYMBOLIC_GP))
            {
            }
            explicit Reg32(PhysicalRegID id) : Opd32(RegID::CreatePhysicalRegID(R_TYPE_GP, id))
            {
            }
            explicit Reg32(AllegrexRegID id) : Opd32(RegID::CreateAllegrexRegID(R_TYPE_ALLEGREX_GPR, id))
            {
            }
            explicit operator Reg8() const
            {
                switch (GetReg().GetType())
                {
                    case R_TYPE_GP:
                        return Reg8(PhysicalRegID(GetReg().id <= R8 ? GetReg().id : GetReg().id - R8 + R8B));
                    case R_TYPE_ALLEGREX_GPR:
                        return Reg8(AllegrexRegID(GetReg().id));
                    default:
                        break;
                }
                return Reg8();
            }
            explicit operator Reg16() const
            {
                switch (GetReg().GetType())
                {
                    case R_TYPE_GP:
                        return Reg16(PhysicalRegID(GetReg().id <= R8 ? GetReg().id : GetReg().id - R8 + R8W));
                    case R_TYPE_ALLEGREX_GPR:
                        return Reg16(AllegrexRegID(GetReg().id));
                    default:
                        break;
                }
                return Reg16();
            }
        };
        struct Gpr : Reg32
        {
            explicit Gpr(unsigned id) : Reg32(Allegrex::jitasm::AllegrexRegID(id))
            {
            }
        };

        /// 64bit general purpose register
        struct Reg64 : Opd64
        {
            Reg64() : Opd64(RegID::CreateSymbolicRegID(R_TYPE_SYMBOLIC_GP))
            {
            }
            explicit Reg64(PhysicalRegID id) : Opd64(RegID::CreatePhysicalRegID(R_TYPE_GP, id))
            {
            }
            explicit Reg64(AllegrexRegID id) : Opd64(RegID::CreateAllegrexRegID(R_TYPE_ALLEGREX_GPR, id))
            {
            }
            explicit Reg64(Gpr reg) : Opd64(RegID::CreateAllegrexRegID(R_TYPE_ALLEGREX_GPR, reg.reg_.id))
            {
            }
        };
        typedef Reg64 Reg;
        /// FPU register
        struct FpuReg : Opd80
        {
            explicit FpuReg(PhysicalRegID id) : Opd80(RegID::CreatePhysicalRegID(R_TYPE_FPU, id))
            {
            }
        };
        /// MMX register
        struct MmxReg : Opd64
        {
            MmxReg() : Opd64(RegID::CreateSymbolicRegID(R_TYPE_SYMBOLIC_MMX))
            {
            }
            explicit MmxReg(PhysicalRegID id) : Opd64(RegID::CreatePhysicalRegID(R_TYPE_MMX, id))
            {
            }
        };
        /// XMM register
        struct XmmReg : Opd128
        {
            XmmReg() : Opd128(RegID::CreateSymbolicRegID(R_TYPE_SYMBOLIC_XMM))
            {
            }
            explicit XmmReg(PhysicalRegID id) : Opd128(RegID::CreatePhysicalRegID(R_TYPE_XMM, id))
            {
            }
        };
        /// YMM register
        struct YmmReg : Opd256
        {
            YmmReg() : Opd256(RegID::CreateSymbolicRegID(R_TYPE_SYMBOLIC_YMM))
            {
            }
            explicit YmmReg(PhysicalRegID id) : Opd256(RegID::CreatePhysicalRegID(R_TYPE_YMM, id))
            {
            }
        };
        /// 64bit general purpose register
        struct Rip64 : Opd64
        {
            Rip64() : Opd64(RegID::CreatePhysicalRegID(R_TYPE_IP, RIP))
            {
            }
        };

        struct FpuReg_st0 : FpuReg
        {
            FpuReg_st0() : FpuReg(ST0)
            {
            }
        };

        template<class OpdN, class U, class S>
        struct ImmT : OpdN
        {
            ImmT(U imm) : OpdN((S)imm)
            {
            }
        };
        typedef ImmT<Opd8, uint8, sint8>    Imm8;   ///< 1 byte immediate
        typedef ImmT<Opd16, uint16, sint16> Imm16;  ///< 2 byte immediate
        typedef ImmT<Opd32, uint32, sint32> Imm32;  ///< 4 byte immediate
        typedef ImmT<Opd64, uint64, sint64> Imm64;  ///< 8 byte immediate

        namespace detail
        {
            inline bool IsInt8(sint64 n)
            {
                return (sint8)n == n;
            }
            inline bool IsInt16(sint64 n)
            {
                return (sint16)n == n;
            }
            inline bool IsInt32(sint64 n)
            {
                return (sint32)n == n;
            }
            inline Opd ImmXor8(const Imm16& imm)
            {
                return IsInt8(imm.GetImm()) ? (Opd)Imm8((sint8)imm.GetImm()) : (Opd)imm;
            }
            inline Opd ImmXor8(const Imm32& imm)
            {
                return IsInt8(imm.GetImm()) ? (Opd)Imm8((sint8)imm.GetImm()) : (Opd)imm;
            }
            inline Opd ImmXor8(const Imm64& imm)
            {
                return IsInt8(imm.GetImm()) ? (Opd)Imm8((sint8)imm.GetImm()) : (Opd)imm;
            }
        }   // namespace detail

        /// 32bit address (base, displacement)
        struct Addr32
        {
            RegID reg_;
            sint64 disp_;
            Addr32(const Reg32& obj) : reg_(obj.reg_), disp_(0)
            {
            }   // implicit
            Addr32(const RegID& reg, sint64 disp) : reg_(reg), disp_(disp)
            {
            }
        };
        inline Addr32 operator+(const Reg32& lhs, sint64 rhs)
        {
            return Addr32(lhs.reg_, rhs);
        }
        inline Addr32 operator+(sint64 lhs, const Reg32& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32 operator-(const Reg32& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr32 operator+(const Addr32& lhs, sint64 rhs)
        {
            return Addr32(lhs.reg_, lhs.disp_ + rhs);
        }
        inline Addr32 operator+(sint64 lhs, const Addr32& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32 operator-(const Addr32& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr32 operator+(const Reg32& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr32 operator+(const void* lhs, const Reg32& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 32bit address (base, index, displacement)
        struct Addr32BI
        {
            RegID base_;
            RegID index_;
            sint64 disp_;
            Addr32BI(const RegID& base, const RegID& index, sint64 disp) : base_(base), index_(index), disp_(disp)
            {
            }
        };
        inline Addr32BI operator+(const Addr32& lhs, const Addr32& rhs)
        {
            return Addr32BI(rhs.reg_, lhs.reg_, lhs.disp_ + rhs.disp_);
        }
        inline Addr32BI operator+(const Addr32BI& lhs, sint64 rhs)
        {
            return Addr32BI(lhs.base_, lhs.index_, lhs.disp_ + rhs);
        }
        inline Addr32BI operator+(sint64 lhs, const Addr32BI& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32BI operator-(const Addr32BI& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr32BI operator+(const Addr32BI& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr32BI operator+(const void* lhs, const Addr32BI& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 32bit address (index, scale, displacement)
        struct Addr32SI
        {
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            Addr32SI(const RegID& index, sint64 scale, sint64 disp) : index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline Addr32SI operator*(const Reg32& lhs, sint64 rhs)
        {
            return Addr32SI(lhs.reg_, rhs, 0);
        }
        inline Addr32SI operator*(sint64 lhs, const Reg32& rhs)
        {
            return rhs * lhs;
        }
        inline Addr32SI operator*(const Addr32SI& lhs, sint64 rhs)
        {
            return Addr32SI(lhs.index_, lhs.scale_ * rhs, lhs.disp_);
        }
        inline Addr32SI operator*(sint64 lhs, const Addr32SI& rhs)
        {
            return rhs * lhs;
        }
        inline Addr32SI operator+(const Addr32SI& lhs, sint64 rhs)
        {
            return Addr32SI(lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline Addr32SI operator+(sint64 lhs, const Addr32SI& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32SI operator-(const Addr32SI& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr32SI operator+(const Addr32SI& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr32SI operator+(const void* lhs, const Addr32SI& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 32bit address (base, index, scale, displacement)
        struct Addr32SIB
        {
            RegID base_;
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            Addr32SIB(const RegID& base, const RegID& index, sint64 scale, sint64 disp) : base_(base), index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline Addr32SIB operator+(const Addr32& lhs, const Addr32SI& rhs)
        {
            return Addr32SIB(lhs.reg_, rhs.index_, rhs.scale_, lhs.disp_ + rhs.disp_);
        }
        inline Addr32SIB operator+(const Addr32SI& lhs, const Addr32& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32SIB operator+(const Addr32SIB& lhs, sint64 rhs)
        {
            return Addr32SIB(lhs.base_, lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline Addr32SIB operator+(sint64 lhs, const Addr32SIB& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32SIB operator-(const Addr32SIB& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr32SIB operator+(const Addr32SIB& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr32SIB operator+(const void* lhs, const Addr32SIB& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// Address (xmm index, scale, displacement)
        struct AddrXmmSI
        {
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            AddrXmmSI(const RegID& index, sint64 scale, sint64 disp) : index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline AddrXmmSI operator*(const XmmReg& lhs, sint64 rhs)
        {
            return AddrXmmSI(lhs.reg_, rhs, 0);
        }
        inline AddrXmmSI operator*(sint64 lhs, const XmmReg& rhs)
        {
            return rhs * lhs;
        }
        inline AddrXmmSI operator*(const AddrXmmSI& lhs, sint64 rhs)
        {
            return AddrXmmSI(lhs.index_, lhs.scale_ * rhs, lhs.disp_);
        }
        inline AddrXmmSI operator*(sint64 lhs, const AddrXmmSI& rhs)
        {
            return rhs * lhs;
        }
        inline AddrXmmSI operator+(const AddrXmmSI& lhs, sint64 rhs)
        {
            return AddrXmmSI(lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline AddrXmmSI operator+(sint64 lhs, const AddrXmmSI& rhs)
        {
            return rhs + lhs;
        }
        inline AddrXmmSI operator-(const AddrXmmSI& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline AddrXmmSI operator+(const AddrXmmSI& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline AddrXmmSI operator+(const void* lhs, const AddrXmmSI& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 32bit address (base, xmm index, scale, displacement)
        struct Addr32XmmSIB
        {
            RegID base_;
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            Addr32XmmSIB(const RegID& base, const RegID& index, sint64 scale, sint64 disp) : base_(base), index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline Addr32XmmSIB operator+(const Addr32& lhs, const AddrXmmSI& rhs)
        {
            return Addr32XmmSIB(lhs.reg_, rhs.index_, rhs.scale_, lhs.disp_ + rhs.disp_);
        }
        inline Addr32XmmSIB operator+(const AddrXmmSI& lhs, const Addr32& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32XmmSIB operator+(const Addr32XmmSIB& lhs, sint64 rhs)
        {
            return Addr32XmmSIB(lhs.base_, lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline Addr32XmmSIB operator+(sint64 lhs, const Addr32XmmSIB& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32XmmSIB operator-(const Addr32XmmSIB& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr32XmmSIB operator+(const Addr32XmmSIB& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr32XmmSIB operator+(const void* lhs, const Addr32XmmSIB& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// Address (ymm index, scale, displacement)
        struct AddrYmmSI
        {
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            AddrYmmSI(const RegID& index, sint64 scale, sint64 disp) : index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline AddrYmmSI operator*(const YmmReg& lhs, sint64 rhs)
        {
            return AddrYmmSI(lhs.reg_, rhs, 0);
        }
        inline AddrYmmSI operator*(sint64 lhs, const YmmReg& rhs)
        {
            return rhs * lhs;
        }
        inline AddrYmmSI operator*(const AddrYmmSI& lhs, sint64 rhs)
        {
            return AddrYmmSI(lhs.index_, lhs.scale_ * rhs, lhs.disp_);
        }
        inline AddrYmmSI operator*(sint64 lhs, const AddrYmmSI& rhs)
        {
            return rhs * lhs;
        }
        inline AddrYmmSI operator+(const AddrYmmSI& lhs, sint64 rhs)
        {
            return AddrYmmSI(lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline AddrYmmSI operator+(sint64 lhs, const AddrYmmSI& rhs)
        {
            return rhs + lhs;
        }
        inline AddrYmmSI operator-(const AddrYmmSI& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline AddrYmmSI operator+(const AddrYmmSI& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline AddrYmmSI operator+(const void* lhs, const AddrYmmSI& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 32bit address (base, ymm index, scale, displacement)
        struct Addr32YmmSIB
        {
            RegID base_;
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            Addr32YmmSIB(const RegID& base, const RegID& index, sint64 scale, sint64 disp) : base_(base), index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline Addr32YmmSIB operator+(const Addr32& lhs, const AddrYmmSI& rhs)
        {
            return Addr32YmmSIB(lhs.reg_, rhs.index_, rhs.scale_, lhs.disp_ + rhs.disp_);
        }
        inline Addr32YmmSIB operator+(const AddrYmmSI& lhs, const Addr32& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32YmmSIB operator+(const Addr32YmmSIB& lhs, sint64 rhs)
        {
            return Addr32YmmSIB(lhs.base_, lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline Addr32YmmSIB operator+(sint64 lhs, const Addr32YmmSIB& rhs)
        {
            return rhs + lhs;
        }
        inline Addr32YmmSIB operator-(const Addr32YmmSIB& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr32YmmSIB operator+(const Addr32YmmSIB& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr32YmmSIB operator+(const void* lhs, const Addr32YmmSIB& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 64bit address (base, displacement)
        struct Addr64
        {
            RegID reg_;
            sint64 disp_;
            Addr64(const Reg64& obj) : reg_(obj.reg_), disp_(0)
            {
            }
            Addr64(const Gpr& obj) : reg_(obj.reg_), disp_(0)
            {
            }
            Addr64(const RegID& reg, sint64 disp) : reg_(reg), disp_(disp)
            {
            }
        };
        inline Addr64 operator+(const Reg64& lhs, sint64 rhs)
        {
            return Addr64(lhs.reg_, rhs);
        }
        inline Addr64 operator+(sint64 lhs, const Reg64& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64 operator-(const Reg64& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr64 operator+(const Addr64& lhs, sint64 rhs)
        {
            return Addr64(lhs.reg_, lhs.disp_ + rhs);
        }
        inline Addr64 operator+(sint64 lhs, const Addr64& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64 operator-(const Addr64& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr64 operator+(const Reg64& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr64 operator+(const void* lhs, const Reg64& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 64bit address (base, index, displacement)
        struct Addr64BI
        {
            RegID base_;
            RegID index_;
            sint64 disp_;
            Addr64BI(const RegID& base, const RegID& index, sint64 disp) : base_(base), index_(index), disp_(disp)
            {
            }
        };
        inline Addr64BI operator+(const Addr64& lhs, const Addr64& rhs)
        {
            return Addr64BI(rhs.reg_, lhs.reg_, lhs.disp_ + rhs.disp_);
        }
        inline Addr64BI operator+(const Addr64BI& lhs, sint64 rhs)
        {
            return Addr64BI(lhs.base_, lhs.index_, lhs.disp_ + rhs);
        }
        inline Addr64BI operator+(sint64 lhs, const Addr64BI& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64BI operator-(const Addr64BI& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr64BI operator+(const Addr64BI& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr64BI operator+(const void* lhs, const Addr64BI& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 64bit address (index, scale, displacement)
        struct Addr64SI
        {
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            Addr64SI(const RegID& index, sint64 scale, sint64 disp) : index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline Addr64SI operator*(const Reg64& lhs, sint64 rhs)
        {
            return Addr64SI(lhs.reg_, rhs, 0);
        }
        inline Addr64SI operator*(sint64 lhs, const Reg64& rhs)
        {
            return rhs * lhs;
        }
        inline Addr64SI operator*(const Addr64SI& lhs, sint64 rhs)
        {
            return Addr64SI(lhs.index_, lhs.scale_ * rhs, lhs.disp_);
        }
        inline Addr64SI operator*(sint64 lhs, const Addr64SI& rhs)
        {
            return rhs * lhs;
        }
        inline Addr64SI operator+(const Addr64SI& lhs, sint64 rhs)
        {
            return Addr64SI(lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline Addr64SI operator+(sint64 lhs, const Addr64SI& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64SI operator-(const Addr64SI& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr64SI operator+(const Addr64SI& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr64SI operator+(const void* lhs, const Addr64SI& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 64bit address (base, index, scale, displacement)
        struct Addr64SIB
        {
            RegID base_;
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            Addr64SIB(const RegID& base, const RegID& index, sint64 scale, sint64 disp) : base_(base), index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline Addr64SIB operator+(const Addr64& lhs, const Addr64SI& rhs)
        {
            return Addr64SIB(lhs.reg_, rhs.index_, rhs.scale_, lhs.disp_ + rhs.disp_);
        }
        inline Addr64SIB operator+(const Addr64SI& lhs, const Addr64& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64SIB operator+(const Addr64SIB& lhs, sint64 rhs)
        {
            return Addr64SIB(lhs.base_, lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline Addr64SIB operator+(sint64 lhs, const Addr64SIB& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64SIB operator-(const Addr64SIB& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr64SIB operator+(const Addr64SIB& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr64SIB operator+(const void* lhs, const Addr64SIB& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 64bit address (base, xmm index, scale, displacement)
        struct Addr64XmmSIB
        {
            RegID base_;
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            Addr64XmmSIB(const RegID& base, const RegID& index, sint64 scale, sint64 disp) : base_(base), index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline Addr64XmmSIB operator+(const Addr64& lhs, const AddrXmmSI& rhs)
        {
            return Addr64XmmSIB(lhs.reg_, rhs.index_, rhs.scale_, lhs.disp_ + rhs.disp_);
        }
        inline Addr64XmmSIB operator+(const AddrXmmSI& lhs, const Addr64& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64XmmSIB operator+(const Addr64XmmSIB& lhs, sint64 rhs)
        {
            return Addr64XmmSIB(lhs.base_, lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline Addr64XmmSIB operator+(sint64 lhs, const Addr64XmmSIB& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64XmmSIB operator-(const Addr64XmmSIB& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr64XmmSIB operator+(const Addr64XmmSIB& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr64XmmSIB operator+(const void* lhs, const Addr64XmmSIB& rhs)
        {
            return rhs + sint64(lhs);
        }

        /// 64bit address (base, ymm index, scale, displacement)
        struct Addr64YmmSIB
        {
            RegID base_;
            RegID index_;
            sint64 scale_;
            sint64 disp_;
            Addr64YmmSIB(const RegID& base, const RegID& index, sint64 scale, sint64 disp) : base_(base), index_(index), scale_(scale), disp_(disp)
            {
            }
        };
        inline Addr64YmmSIB operator+(const Addr64& lhs, const AddrYmmSI& rhs)
        {
            return Addr64YmmSIB(lhs.reg_, rhs.index_, rhs.scale_, lhs.disp_ + rhs.disp_);
        }
        inline Addr64YmmSIB operator+(const AddrYmmSI& lhs, const Addr64& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64YmmSIB operator+(const Addr64YmmSIB& lhs, sint64 rhs)
        {
            return Addr64YmmSIB(lhs.base_, lhs.index_, lhs.scale_, lhs.disp_ + rhs);
        }
        inline Addr64YmmSIB operator+(sint64 lhs, const Addr64YmmSIB& rhs)
        {
            return rhs + lhs;
        }
        inline Addr64YmmSIB operator-(const Addr64YmmSIB& lhs, sint64 rhs)
        {
            return lhs + -rhs;
        }
        inline Addr64YmmSIB operator+(const Addr64YmmSIB& lhs, const void* rhs)
        {
            return lhs + sint64(rhs);
        }
        inline Addr64YmmSIB operator+(const void* lhs, const Addr64YmmSIB& rhs)
        {
            return rhs + sint64(lhs);
        }

        typedef Addr64      Addr;
        typedef Addr64BI    AddrBI;
        typedef Addr64SI    AddrSI;
        typedef Addr64SIB   AddrSIB;

        template<class OpdN>
        struct MemT : OpdN
        {
            MemT(OpdSize base_size, OpdSize index_size, const RegID& base, const RegID& index, sint64 scale, sint64 disp) : OpdN(base_size, index_size, base, index, scale, disp)
            {
            }

            MemT operator[](int disp) const
            {
                return MemT(O_SIZE_64, O_SIZE_64, this->base_, this->index_, this->scale_, this->disp_ + sint64(disp));
            }
            MemT operator[](unsigned int disp) const
            {
                return MemT(O_SIZE_64, O_SIZE_64, this->base_, this->index_, this->scale_, this->disp_ + sint64(disp));
            }
            MemT operator[](intptr_t disp) const
            {
                return MemT(O_SIZE_64, O_SIZE_64, this->base_, this->index_, this->scale_, this->disp_ + sint64(disp));
            }
            MemT operator[](uintptr_t disp) const
            {
                return MemT(O_SIZE_64, O_SIZE_64, this->base_, this->index_, this->scale_, this->disp_ + sint64(disp));
            }
            MemT operator[](const Addr32& obj) const
            {
                return MemT(O_SIZE_32, O_SIZE_32, obj.reg_, this->index_, this->scale_, this->disp_ + obj.disp_);
            }
            MemT operator[](const Addr32BI& obj) const
            {
                return MemT(O_SIZE_32, O_SIZE_32, obj.base_, obj.index_, this->scale_, this->disp_ + obj.disp_);
            }
            MemT operator[](const Addr32SI& obj) const
            {
                return MemT(O_SIZE_32, O_SIZE_32, this->base_, obj.index_, obj.scale_, this->disp_ + obj.disp_);
            }
            MemT operator[](const Addr32SIB& obj) const
            {
                return MemT(O_SIZE_32, O_SIZE_32, obj.base_, obj.index_, obj.scale_, this->disp_ + obj.disp_);
            }

            // 64bit-Addressing
            MemT operator[](const Addr64& obj) const
            {
                return MemT(O_SIZE_64, O_SIZE_64, this->base_, obj.reg_, this->scale_, this->disp_ + obj.disp_);
            }
            MemT operator[](const Addr64BI& obj) const
            {
                return MemT(O_SIZE_64, O_SIZE_64, obj.base_, obj.index_, this->scale_, this->disp_ + obj.disp_);
            }
            MemT operator[](const Addr64SI& obj) const
            {
                return MemT(O_SIZE_64, O_SIZE_64, this->base_, obj.index_, obj.scale_, this->disp_ + obj.disp_);
            }
            MemT operator[](const Addr64SIB& obj) const
            {
                return MemT(O_SIZE_64, O_SIZE_64, obj.base_, obj.index_, obj.scale_, this->disp_ + obj.disp_);
            }

        };

        typedef MemT<Opd8>      Mem8;
        typedef MemT<Opd16>     Mem16;
        typedef MemT<Opd32>     Mem32;
        typedef MemT<Opd64>     Mem64;
        typedef MemT<Opd80>     Mem80;
        typedef MemT<Opd128>    Mem128;
        typedef MemT<Opd224>    Mem224;     // FPU environment
        typedef MemT<Opd256>    Mem256;
        typedef MemT<Opd864>    Mem864;     // FPU state
        typedef MemT<Opd4096>   Mem4096;    // FPU, MMX, XMM, MXCSR state

        template<class OpdN, OpdSize IndexSize>
        struct VecMemT : OpdN
        {
            VecMemT(OpdSize base_size, const RegID& base, const RegID& index, sint64 scale, sint64 disp) : OpdN(base_size, IndexSize, base, index, scale, disp)
            {
            }
        };
        typedef VecMemT<Opd32, O_SIZE_128>  Mem32vxd;
        typedef VecMemT<Opd32, O_SIZE_256>  Mem32vyd;
        typedef VecMemT<Opd32, O_SIZE_128>  Mem64vxd;
        typedef VecMemT<Opd32, O_SIZE_256>  Mem64vyd;
        typedef VecMemT<Opd64, O_SIZE_128>  Mem32vxq;
        typedef VecMemT<Opd64, O_SIZE_256>  Mem32vyq;
        typedef VecMemT<Opd64, O_SIZE_128>  Mem64vxq;
        typedef VecMemT<Opd64, O_SIZE_256>  Mem64vyq;

        struct MemOffset64
        {
            sint64 offset_;
            explicit MemOffset64(sint64 offset) : offset_(offset)
            {
            }
            sint64 GetOffset() const
            {
                return offset_;
            }
        };

        template<typename OpdN>
        struct AddressingPtr
        {
            // 32bit-Addressing
            MemT<OpdN> operator[](const Addr32& obj)
            {
                return MemT<OpdN>(O_SIZE_32, O_SIZE_32, obj.reg_, RegID::Invalid(), 0, obj.disp_);
            }

            MemT<OpdN> operator[](const Addr32BI& obj)
            {
                return MemT<OpdN>(O_SIZE_32, O_SIZE_32, obj.base_, obj.index_, 0, obj.disp_);
            }
            MemT<OpdN> operator[](const Addr32SI& obj)
            {
                return MemT<OpdN>(O_SIZE_32, O_SIZE_32, RegID::Invalid(), obj.index_, obj.scale_, obj.disp_);
            }
            MemT<OpdN> operator[](const Addr32SIB& obj)
            {
                return MemT<OpdN>(O_SIZE_32, O_SIZE_32, obj.base_, obj.index_, obj.scale_, obj.disp_);
            }
            VecMemT<OpdN, O_SIZE_128> operator[](const Addr32XmmSIB& obj)
            {
                return VecMemT<OpdN, O_SIZE_128>(O_SIZE_32, obj.base_, obj.index_, obj.scale_, obj.disp_);
            }
            VecMemT<OpdN, O_SIZE_256> operator[](const Addr32YmmSIB& obj)
            {
                return VecMemT<OpdN, O_SIZE_256>(O_SIZE_32, obj.base_, obj.index_, obj.scale_, obj.disp_);
            }

            // 64bit-Addressing
            MemT<OpdN> operator[](const Addr64& obj)
            {
                return MemT<OpdN>(O_SIZE_64, O_SIZE_64, obj.reg_, RegID::Invalid(), 0, obj.disp_);
            }
            MemT<OpdN> operator[](const Addr64BI& obj)
            {
                return MemT<OpdN>(O_SIZE_64, O_SIZE_64, obj.base_, obj.index_, 0, obj.disp_);
            }
            MemT<OpdN> operator[](const Addr64SI& obj)
            {
                return MemT<OpdN>(O_SIZE_64, O_SIZE_64, RegID::Invalid(), obj.index_, obj.scale_, obj.disp_);
            }
            MemT<OpdN> operator[](const Addr64SIB& obj)
            {
                return MemT<OpdN>(O_SIZE_64, O_SIZE_64, obj.base_, obj.index_, obj.scale_, obj.disp_);
            }
            MemOffset64 operator[](sint64 offset)
            {
                return MemOffset64(offset);
            }
            MemOffset64 operator[](uint64 offset)
            {
                return MemOffset64((sint64)offset);
            }
            VecMemT<OpdN, O_SIZE_128> operator[](const Addr64XmmSIB& obj)
            {
                return VecMemT<OpdN, O_SIZE_128>(O_SIZE_64, obj.base_, obj.index_, obj.scale_, obj.disp_);
            }
            VecMemT<OpdN, O_SIZE_256> operator[](const Addr64YmmSIB& obj)
            {
                return VecMemT<OpdN, O_SIZE_256>(O_SIZE_64, obj.base_, obj.index_, obj.scale_, obj.disp_);
            }

            MemT<OpdN> operator[](sint32 disp)
            {
                return MemT<OpdN>(O_SIZE_64, O_SIZE_64, RegID::Invalid(), RegID::Invalid(), 0, disp);
            }
            MemT<OpdN> operator[](uint32 disp)
            {
                return MemT<OpdN>(O_SIZE_64, O_SIZE_64, RegID::Invalid(), RegID::Invalid(), 0, (sint32)disp);
            }

            //MemOffset64 operator[](const void* ptr)
            //{
            //    return MemOffset64((sint64)ptr);
            //}
        };

        /// Instruction ID
        enum InstrID
        {
            I_ADC, I_ADD, I_AND,
            I_BSF, I_BSR, I_BSWAP, I_BT, I_BTC, I_BTR, I_BTS,
            I_CALL, I_CBW, I_CLC, I_CLD, I_CLI, I_CLTS, I_CMC, I_CMOVCC, I_CMP, I_CMPS_B, I_CMPS_W, I_CMPS_D, I_CMPS_Q, I_CMPXCHG,
            I_CMPXCHG8B, I_CMPXCHG16B, I_CPUID, I_CWD, I_CDQ, I_CQO,
            I_DEC, I_DIV,
            I_ENTER,
            I_HLT,
            I_IDIV, I_IMUL, I_IN, I_INC, I_INS_B, I_INS_W, I_INS_D, I_INVD, I_INVLPG, I_INT3, I_INTN, I_INTO, I_IRET, I_IRETD, I_IRETQ,
            I_JMP, I_JCC,
            I_LAR, I_LEA, I_LEAVE, I_LLDT, I_LMSW, I_LSL, I_LTR, I_LODS_B, I_LODS_W, I_LODS_D, I_LODS_Q, I_LOOP,
            I_MOV, I_MOVBE, I_MOVS_B, I_MOVS_W, I_MOVS_D, I_MOVS_Q, I_MOVZX, I_MOVSX, I_MOVSXD, I_MUL,
            I_NEG, I_NOP, I_NOT,
            I_OR, I_OUT, I_OUTS_B, I_OUTS_W, I_OUTS_D,
            I_POP, I_POPAD, I_POPF, I_POPFD, I_POPFQ, I_PUSH, I_PUSHAD, I_PUSHF, I_PUSHFD, I_PUSHFQ,
            I_RDMSR, I_RDPMC, I_RDTSC, I_RET, I_RCL, I_RCR, I_ROL, I_ROR, I_RSM,
            I_SAR, I_SHL, I_SHR, I_SBB, I_SCAS_B, I_SCAS_W, I_SCAS_D, I_SCAS_Q, I_SETCC, I_SHLD, I_SHRD, I_SGDT, I_SIDT, I_SLDT, I_SMSW, I_STC, I_STD, I_STI,
            I_STOS_B, I_STOS_W, I_STOS_D, I_STOS_Q, I_SUB, I_SWAPGS, I_SYSCALL, I_SYSENTER, I_SYSEXIT, I_SYSRET,
            I_TEST,
            I_UD2,
            I_VERR, I_VERW,
            I_WAIT, I_WBINVD, I_WRMSR,
            I_XADD, I_XCHG, I_XGETBV, I_XLATB, I_XOR,

            I_F2XM1, I_FABS, I_FADD, I_FADDP, I_FIADD,
            I_FBLD, I_FBSTP, I_FCHS, I_FCLEX, I_FNCLEX, I_FCMOVCC, I_FCOM, I_FCOMP, I_FCOMPP, I_FCOMI, I_FCOMIP, I_FCOS,
            I_FDECSTP, I_FDIV, I_FDIVP, I_FIDIV, I_FDIVR, I_FDIVRP, I_FIDIVR,
            I_FFREE,
            I_FICOM, I_FICOMP, I_FILD, I_FINCSTP, I_FINIT, I_FNINIT, I_FIST, I_FISTP,
            I_FLD, I_FLD1, I_FLDCW, I_FLDENV, I_FLDL2E, I_FLDL2T, I_FLDLG2, I_FLDLN2, I_FLDPI, I_FLDZ,
            I_FMUL, I_FMULP, I_FIMUL,
            I_FNOP,
            I_FPATAN, I_FPREM, I_FPREM1, I_FPTAN,
            I_FRNDINT, I_FRSTOR,
            I_FSAVE, I_FNSAVE, I_FSCALE, I_FSIN, I_FSINCOS, I_FSQRT, I_FST, I_FSTP, I_FSTCW, I_FNSTCW, I_FSTENV, I_FNSTENV, I_FSTSW, I_FNSTSW,
            I_FSUB, I_FSUBP, I_FISUB, I_FSUBR, I_FSUBRP, I_FISUBR,
            I_FTST,
            I_FUCOM, I_FUCOMP, I_FUCOMPP, I_FUCOMI, I_FUCOMIP,
            I_FXAM, I_FXCH, I_FXRSTOR, I_FXSAVE, I_FXTRACT,
            I_FYL2X, I_FYL2XP1,

            I_ADDPS, I_ADDSS, I_ADDPD, I_ADDSD, I_ADDSUBPS, I_ADDSUBPD, I_ANDPS, I_ANDPD, I_ANDNPS, I_ANDNPD,
            I_BLENDPS, I_BLENDPD, I_BLENDVPS, I_BLENDVPD,
            I_CLFLUSH, I_CMPPS, I_CMPSS, I_CMPPD, I_CMPSD, I_COMISS, I_COMISD, I_CRC32,
            I_CVTDQ2PD, I_CVTDQ2PS, I_CVTPD2DQ, I_CVTPD2PI, I_CVTPD2PS, I_CVTPI2PD, I_CVTPI2PS, I_CVTPS2DQ, I_CVTPS2PD, I_CVTPS2PI, I_CVTSD2SI,
            I_CVTSD2SS, I_CVTSI2SD, I_CVTSI2SS, I_CVTSS2SD, I_CVTSS2SI, I_CVTTPD2DQ, I_CVTTPD2PI, I_CVTTPS2DQ, I_CVTTPS2PI, I_CVTTSD2SI, I_CVTTSS2SI,
            I_DIVPS, I_DIVSS, I_DIVPD, I_DIVSD, I_DPPS, I_DPPD,
            I_EMMS, I_EXTRACTPS,
            I_FISTTP,
            I_HADDPS, I_HADDPD, I_HSUBPS, I_HSUBPD,
            I_INSERTPS,
            I_LDDQU, I_LDMXCSR, I_LFENCE,
            I_MASKMOVDQU, I_MASKMOVQ, I_MAXPS, I_MAXSS, I_MAXPD, I_MAXSD, I_MFENCE, I_MINPS, I_MINSS, I_MINPD, I_MINSD, I_MONITOR,
            I_MOVAPD, I_MOVAPS, I_MOVD, I_MOVDDUP, I_MOVDQA, I_MOVDQU, I_MOVDQ2Q, I_MOVHLPS, I_MOVLHPS, I_MOVHPS, I_MOVHPD, I_MOVLPS, I_MOVLPD,
            I_MOVMSKPS, I_MOVMSKPD, I_MOVNTDQ, I_MOVNTDQA, I_MOVNTI, I_MOVNTPD, I_MOVNTPS, I_MOVNTQ, I_MOVQ, I_MOVQ2DQ, I_MOVSD, I_MOVSS,
            I_MOVSHDUP, I_MOVSLDUP, I_MOVUPS, I_MOVUPD, I_MPSADBW, I_MULPS, I_MULSS, I_MULPD, I_MULSD, I_MWAIT,
            I_ORPS, I_ORPD,
            I_PABSB, I_PABSD, I_PABSW, I_PACKSSDW, I_PACKSSWB, I_PACKUSDW, I_PACKUSWB, I_PADDB, I_PADDD, I_PADDQ, I_PADDSB, I_PADDSW, I_PADDUSB,
            I_PADDUSW, I_PADDW, I_PALIGNR, I_PAND, I_PANDN, I_PAUSE, I_PAVGB, I_PAVGW,
            I_PBLENDVB, I_PBLENDW,
            I_PCMPEQB, I_PCMPEQW, I_PCMPEQD, I_PCMPEQQ, I_PCMPESTRI, I_PCMPESTRM, I_PCMPISTRI, I_PCMPISTRM, I_PCMPGTB, I_PCMPGTW, I_PCMPGTD, I_PCMPGTQ,
            I_PEXTRB, I_PEXTRW, I_PEXTRD, I_PEXTRQ,
            I_PHADDW, I_PHADDD, I_PHADDSW, I_PHMINPOSUW, I_PHSUBW, I_PHSUBD, I_PHSUBSW,
            I_PINSRB, I_PINSRW, I_PINSRD, I_PINSRQ,
            I_PMADDUBSW, I_PMADDWD, I_PMAXSB, I_PMAXSW, I_PMAXSD, I_PMAXUB, I_PMAXUW, I_PMAXUD, I_PMINSB, I_PMINSW, I_PMINSD, I_PMINUB, I_PMINUW,
            I_PMINUD, I_PMOVMSKB, I_PMOVSXBW, I_PMOVSXBD, I_PMOVSXBQ, I_PMOVSXWD, I_PMOVSXWQ, I_PMOVSXDQ, I_PMOVZXBW, I_PMOVZXBD, I_PMOVZXBQ, I_PMOVZXWD,
            I_PMOVZXWQ, I_PMOVZXDQ, I_PMULDQ, I_PMULHRSW, I_PMULHUW, I_PMULHW, I_PMULLW, I_PMULLD, I_PMULUDQ,
            I_POPCNT, I_POR,
            I_PREFETCH,
            I_PSADBW, I_PSHUFB, I_PSHUFD, I_PSHUFHW, I_PSHUFLW, I_PSHUFW, I_PSIGNB, I_PSIGNW, I_PSIGND, I_PSLLW, I_PSLLD, I_PSLLQ, I_PSLLDQ, I_PSRAW,
            I_PSRAD, I_PSRLW, I_PSRLD, I_PSRLQ, I_PSRLDQ, I_PSUBB, I_PSUBW, I_PSUBD, I_PSUBQ, I_PSUBSB, I_PSUBSW, I_PSUBUSB, I_PSUBUSW,
            I_PTEST,
            I_PUNPCKHBW, I_PUNPCKHWD, I_PUNPCKHDQ, I_PUNPCKHQDQ, I_PUNPCKLBW, I_PUNPCKLWD, I_PUNPCKLDQ, I_PUNPCKLQDQ,
            I_PXOR,
            I_RCPPS, I_RCPSS, I_ROUNDPS, I_ROUNDPD, I_ROUNDSS, I_ROUNDSD, I_RSQRTPS, I_RSQRTSS,
            I_SFENCE, I_SHUFPS, I_SHUFPD, I_SQRTPS, I_SQRTSS, I_SQRTPD, I_SQRTSD, I_STMXCSR, I_SUBPS, I_SUBSS, I_SUBPD, I_SUBSD,
            I_UCOMISS, I_UCOMISD, I_UNPCKHPS, I_UNPCKHPD, I_UNPCKLPS, I_UNPCKLPD,
            I_XORPS, I_XORPD,

            I_VBROADCASTSS, I_VBROADCASTSD, I_VBROADCASTF128,
            I_VEXTRACTF128,
            I_VINSERTF128,
            I_VMASKMOVPS, I_VMASKMOVPD,
            I_VPERMILPD, I_VPERMILPS, I_VPERM2F128,
            I_VTESTPS, I_VTESTPD,
            I_VZEROALL, I_VZEROUPPER,

            I_AESENC, I_AESENCLAST, I_AESDEC, I_AESDECLAST, I_AESIMC, I_AESKEYGENASSIST,
            I_PCLMULQDQ,

            // FMA
            I_VFMADD132PD, I_VFMADD213PD, I_VFMADD231PD, I_VFMADD132PS, I_VFMADD213PS, I_VFMADD231PS,
            I_VFMADD132SD, I_VFMADD213SD, I_VFMADD231SD, I_VFMADD132SS, I_VFMADD213SS, I_VFMADD231SS,
            I_VFMADDSUB132PD, I_VFMADDSUB213PD, I_VFMADDSUB231PD, I_VFMADDSUB132PS, I_VFMADDSUB213PS, I_VFMADDSUB231PS,
            I_VFMSUBADD132PD, I_VFMSUBADD213PD, I_VFMSUBADD231PD, I_VFMSUBADD132PS, I_VFMSUBADD213PS, I_VFMSUBADD231PS,
            I_VFMSUB132PD, I_VFMSUB213PD, I_VFMSUB231PD, I_VFMSUB132PS, I_VFMSUB213PS, I_VFMSUB231PS,
            I_VFMSUB132SD, I_VFMSUB213SD, I_VFMSUB231SD, I_VFMSUB132SS, I_VFMSUB213SS, I_VFMSUB231SS,
            I_VFNMADD132PD, I_VFNMADD213PD, I_VFNMADD231PD, I_VFNMADD132PS, I_VFNMADD213PS, I_VFNMADD231PS,
            I_VFNMADD132SD, I_VFNMADD213SD, I_VFNMADD231SD, I_VFNMADD132SS, I_VFNMADD213SS, I_VFNMADD231SS,
            I_VFNMSUB132PD, I_VFNMSUB213PD, I_VFNMSUB231PD, I_VFNMSUB132PS, I_VFNMSUB213PS, I_VFNMSUB231PS,
            I_VFNMSUB132SD, I_VFNMSUB213SD, I_VFNMSUB231SD, I_VFNMSUB132SS, I_VFNMSUB213SS, I_VFNMSUB231SS,

            // F16C
            I_RDFSBASE, I_RDGSBASE, I_RDRAND, I_WRFSBASE, I_WRGSBASE, I_VCVTPH2PS, I_VCVTPS2PH,

            // BMI
            I_ANDN, I_BEXTR, I_BLSI, I_BLSMSK, I_BLSR, I_BZHI, I_LZCNT, I_MULX, I_PDEP, I_PEXT, I_RORX, I_SARX, I_SHLX, I_SHRX, I_TZCNT, I_INVPCID,

            // XOP
            I_VFRCZPD, I_VFRCZPS, I_VFRCZSD, I_VFRCZSS,
            I_VPCMOV, I_VPCOMB, I_VPCOMD, I_VPCOMQ, I_VPCOMUB, I_VPCOMUD, I_VPCOMUQ, I_VPCOMUW, I_VPCOMW, I_VPERMIL2PD, I_VPERMIL2PS,
            I_VPHADDBD, I_VPHADDBQ, I_VPHADDBW, I_VPHADDDQ, I_VPHADDUBD, I_VPHADDUBQ, I_VPHADDUBW, I_VPHADDUDQ, I_VPHADDUWD, I_VPHADDUWQ,
            I_VPHADDWD, I_VPHADDWQ, I_VPHSUBBW, I_VPHSUBDQ, I_VPHSUBWD,
            I_VPMACSDD, I_VPMACSDQH, I_VPMACSDQL, I_VPMACSSDD, I_VPMACSSDQH, I_VPMACSSDQL, I_VPMACSSWD, I_VPMACSSWW, I_VPMACSWD, I_VPMACSWW,
            I_VPMADCSSWD, I_VPMADCSWD,
            I_VPPERM, I_VPROTB, I_VPROTD, I_VPROTQ, I_VPROTW, I_VPSHAB, I_VPSHAD, I_VPSHAQ, I_VPSHAW, I_VPSHLB, I_VPSHLD, I_VPSHLQ, I_VPSHLW,

            // FMA4
            I_VFMADDPD, I_VFMADDPS, I_VFMADDSD, I_VFMADDSS,
            I_VFMADDSUBPD, I_VFMADDSUBPS,
            I_VFMSUBADDPD, I_VFMSUBADDPS,
            I_VFMSUBPD, I_VFMSUBPS, I_VFMSUBSD, I_VFMSUBSS,
            I_VFNMADDPD, I_VFNMADDPS, I_VFNMADDSD, I_VFNMADDSS,
            I_VFNMSUBPD, I_VFNMSUBPS, I_VFNMSUBSD, I_VFNMSUBSS,

            // AVX2
            I_VBROADCASTI128, I_VPBROADCASTB, I_VPBROADCASTW, I_VPBROADCASTD, I_VPBROADCASTQ,
            I_PBLENDD, I_VPERMD, I_VPERMQ, I_VPERMPS, I_VPERMPD, I_VPERM2I128,
            I_VEXTRACTI128, I_VINSERTI128, I_VMASKMOVD, I_VMASKMOVQ, I_VPSLLVD, I_VPSLLVQ, I_VPSRAVD, I_VPSRLVD, I_VPSRLVQ,
            I_VGATHERDPS, I_VGATHERQPS, I_VGATHERDPD, I_VGATHERQPD, I_VPGATHERDD, I_VPGATHERQD, I_VPGATHERDQ, I_VPGATHERQQ,

            // jitasm compiler instructions
            I_COMPILER_DECLARE_REG_ARG,     ///< Declare register argument
            I_COMPILER_DECLARE_STACK_ARG,   ///< Declare stack argument
            I_COMPILER_DECLARE_RESULT_REG,  ///< Declare result register (eax/rax/xmm0)
            I_COMPILER_PROLOG,              ///< Function prolog
            I_COMPILER_EPILOG,              ///< Function epilog

            I_ALIGN,
            I_NULL,
            I_SOURCE,

            I_GEN,
            I_SAME,
            I_KILL,

            // constants pool
            I_DB,
            I_DW,
            I_DD,
            I_DQ,
        };

        enum JumpCondition
        {
            JCC_O, JCC_NO, JCC_B, JCC_AE, JCC_E, JCC_NE, JCC_BE, JCC_A, JCC_S, JCC_NS, JCC_P, JCC_NP, JCC_L, JCC_GE, JCC_LE, JCC_G,
            JCC_CXZ, JCC_ECXZ, JCC_RCXZ,
        };

        enum EncodingFlags
        {
            E_SPECIAL               = 1 << 0,
            E_OPERAND_SIZE_PREFIX   = 1 << 1,   ///< Operand-size override prefix
            E_REP_PREFIX            = 1 << 2,   ///< REP prefix
            E_REXW_PREFIX           = 1 << 3,   ///< REX.W
            E_MANDATORY_PREFIX_66   = 1 << 4,   ///< Mandatory prefix 66
            E_MANDATORY_PREFIX_F2   = 1 << 5,   ///< Mandatory prefix F2
            E_MANDATORY_PREFIX_F3   = 1 << 6,   ///< Mandatory prefix F3
            E_VEX                   = 1 << 7,
            E_XOP                   = 1 << 8,
            E_VEX_L                 = 1 << 9,
            E_VEX_W                 = 1 << 10,
            E_VEX_MMMMM_SHIFT       = 11,
            E_VEX_MMMMM_MASK        = 0x1F << E_VEX_MMMMM_SHIFT,
            E_VEX_0F                = 1 << E_VEX_MMMMM_SHIFT,
            E_VEX_0F38              = 2 << E_VEX_MMMMM_SHIFT,
            E_VEX_0F3A              = 3 << E_VEX_MMMMM_SHIFT,
            E_XOP_M00011            = 3 << E_VEX_MMMMM_SHIFT,
            E_XOP_M01000            = 8 << E_VEX_MMMMM_SHIFT,
            E_XOP_M01001            = 9 << E_VEX_MMMMM_SHIFT,
            E_VEX_PP_SHIFT          = 16,
            E_VEX_PP_MASK           = 0x3 << E_VEX_PP_SHIFT,
            E_VEX_66                = 1 << E_VEX_PP_SHIFT,
            E_VEX_F3                = 2 << E_VEX_PP_SHIFT,
            E_VEX_F2                = 3 << E_VEX_PP_SHIFT,
            E_XOP_P00               = 0 << E_VEX_PP_SHIFT,
            E_XOP_P01               = 1 << E_VEX_PP_SHIFT,

            E_NO_BREAK              = 1 << 31,

            E_VEX_128       = E_VEX,
            E_VEX_256       = E_VEX | E_VEX_L,
            E_VEX_LIG       = E_VEX,
            E_VEX_LZ        = E_VEX,
            E_VEX_66_0F     = E_VEX_66 | E_VEX_0F,
            E_VEX_66_0F38   = E_VEX_66 | E_VEX_0F38,
            E_VEX_66_0F3A   = E_VEX_66 | E_VEX_0F3A,
            E_VEX_F2_0F     = E_VEX_F2 | E_VEX_0F,
            E_VEX_F2_0F38   = E_VEX_F2 | E_VEX_0F38,
            E_VEX_F2_0F3A   = E_VEX_F2 | E_VEX_0F3A,
            E_VEX_F3_0F     = E_VEX_F3 | E_VEX_0F,
            E_VEX_F3_0F38   = E_VEX_F3 | E_VEX_0F38,
            E_VEX_F3_0F3A   = E_VEX_F3 | E_VEX_0F3A,
            E_VEX_W0        = 0,
            E_VEX_W1        = E_VEX_W,
            E_VEX_WIG       = 0,
            E_XOP_128       = E_XOP,
            E_XOP_256       = E_XOP | E_VEX_L,
            E_XOP_W0        = 0,
            E_XOP_W1        = E_VEX_W,


            // Aliases
            E_VEX_128_0F_WIG = E_VEX_128 | E_VEX_0F | E_VEX_WIG,
            E_VEX_256_0F_WIG = E_VEX_256 | E_VEX_0F | E_VEX_WIG,
            E_VEX_128_66_0F_WIG = E_VEX_128 | E_VEX_66_0F | E_VEX_WIG,
            E_VEX_256_66_0F_WIG = E_VEX_256 | E_VEX_66_0F | E_VEX_WIG,
            E_VEX_128_66_0F38_WIG = E_VEX_128 | E_VEX_66_0F38 | E_VEX_WIG,
            E_VEX_256_66_0F38_WIG = E_VEX_256 | E_VEX_66_0F38 | E_VEX_WIG,
            E_VEX_128_66_0F38_W0 = E_VEX_128 | E_VEX_66_0F38 | E_VEX_W0,
            E_VEX_256_66_0F38_W0 = E_VEX_256 | E_VEX_66_0F38 | E_VEX_W0,
            E_VEX_128_66_0F38_W1 = E_VEX_128 | E_VEX_66_0F38 | E_VEX_W1,
            E_VEX_256_66_0F38_W1 = E_VEX_256 | E_VEX_66_0F38 | E_VEX_W1,
            E_VEX_128_66_0F3A_W0 = E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0,
            E_VEX_256_66_0F3A_W0 = E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0,
        };

        /// Instruction
        struct Instr
        {
            static const size_t MAX_OPERAND_COUNT = 6;

            InstrID id_;                            ///< Instruction ID
            uint32  opcode_;                        ///< Opcode
            uint32  encoding_flag_;                 ///< EncodingFlags
            detail::Opd opd_[MAX_OPERAND_COUNT];    ///< Operands

            Instr(InstrID id, uint32 opcode, uint32 encoding_flag, const detail::Opd& opd1 = detail::Opd(), const detail::Opd& opd2 = detail::Opd(), const detail::Opd& opd3 = detail::Opd(), const detail::Opd& opd4 = detail::Opd(), const detail::Opd& opd5 = detail::Opd(), const detail::Opd& opd6 = detail::Opd())
                : id_(id), opcode_(opcode), encoding_flag_(encoding_flag)
            {
                opd_[0] = opd1, opd_[1] = opd2, opd_[2] = opd3, opd_[3] = opd4, opd_[4] = opd5, opd_[5] = opd6;
            }

            InstrID GetID() const
            {
                return id_;
            }
            const detail::Opd& GetOpd(size_t index) const
            {
                return opd_[index];
            }
            detail::Opd& GetOpd(size_t index)
            {
                return opd_[index];
            }

#if 0
            Instr(InstrID id, const detail::Opd& opd1 = detail::Opd(), const detail::Opd& opd2 = detail::Opd(), const detail::Opd& opd3 = detail::Opd(), const detail::Opd& opd4 = detail::Opd(), const detail::Opd& opd5 = detail::Opd(), const detail::Opd& opd6 = detail::Opd());
#endif
        };

        /// Assembler backend
        struct Backend
        {
            uint8*                       pbuff_;
            size_t                       buffsize_;
            size_t                       size_;
            std::multimap< size_t, u32 > sources_;

            Backend(void* pbuff = NULL, size_t buffsize = 0) : pbuff_((uint8*)pbuff), buffsize_(buffsize), size_(0)
            {
                memset(pbuff, 0xCC, buffsize);  // INT3
            }

            std::vector< u32 > GetSources(size_t offset)
            {
                std::vector< u32 > sources;
                auto r = sources_.equal_range(offset);
                for (auto i = r.first; i != r.second; ++i)
                {
                    sources.push_back(i->second);
                }
                return sources;
            }

            size_t GetSize() const
            {
                return size_;
            }

            void PutBytes(void* p, size_t n)
            {
                uint8* pb = (uint8*)p;
                while (n--)
                {
                    if (pbuff_)
                    {
                        if (size_ == buffsize_) JITASM_ASSERT(0);
                        pbuff_[size_] = *pb++;
                    }
                    size_++;
                }
            }
            void db(uint64 b)
            {
                PutBytes(&b, 1);
            }
            void dw(uint64 w)
            {
                PutBytes(&w, 2);
            }
            void dd(uint64 d)
            {
                PutBytes(&d, 4);
            }
            void dq(uint64 q)
            {
                PutBytes(&q, 8);
            }

            uint8 GetWRXB(int w, const detail::Opd& reg, const detail::Opd& r_m)
            {
                uint8 wrxb = w ? 8 : 0;
                if (reg.IsReg())
                {
                    if (!reg.GetReg().IsInvalid() && reg.GetReg().id >= R8) wrxb |= 4;
                }
                if (r_m.IsReg())
                {
                    if (r_m.GetReg().id >= R8) wrxb |= 1;
                }
                if (r_m.IsMem())
                {
                    if (!r_m.GetIndex().IsInvalid() && r_m.GetIndex().id >= R8) wrxb |= 2;
                    if (!r_m.GetBase().IsInvalid() && uint32(r_m.GetBase().id - R8) < (RIP-R8)) wrxb |= 1;
                }
                return wrxb;
            }

            void EncodePrefixes(uint32 flag, const detail::Opd& reg, const detail::Opd& r_m, const detail::Opd& vex)
            {
                if (flag & (E_VEX | E_XOP))
                {
                    // Encode VEX prefix
                    if (r_m.IsMem() && r_m.GetAddressBaseSize() != O_SIZE_64) db(0x67);
                    uint8 vvvv = vex.IsReg() ? 0xF - (uint8)vex.GetReg().id : 0xF;
                    uint8 mmmmm = (flag & E_VEX_MMMMM_MASK) >> E_VEX_MMMMM_SHIFT;
                    uint8 pp = static_cast<uint8>((flag & E_VEX_PP_MASK) >> E_VEX_PP_SHIFT);
                    uint8 wrxb = GetWRXB(flag & E_VEX_W, reg, r_m);
                    if (flag & E_XOP)
                    {
                        db(0x8F);
                        db((~wrxb & 7) << 5 | mmmmm);
                        db((wrxb & 8) << 4 | vvvv << 3 | (flag & E_VEX_L ? 4 : 0) | pp);
                    }
                    else if (wrxb & 0xB || (flag & E_VEX_MMMMM_MASK) == E_VEX_0F38 || (flag & E_VEX_MMMMM_MASK) == E_VEX_0F3A)
                    {
                        db(0xC4);
                        db((~wrxb & 7) << 5 | mmmmm);
                        db((wrxb & 8) << 4 | vvvv << 3 | (flag & E_VEX_L ? 4 : 0) | pp);
                    }
                    else
                    {
                        db(0xC5);
                        db((~wrxb & 4) << 5 | vvvv << 3 | (flag & E_VEX_L ? 4 : 0) | pp);
                    }
                }
                else
                {
                    uint8 wrxb = GetWRXB(flag & E_REXW_PREFIX, reg, r_m);
                    if (wrxb)
                    {
                        // Encode REX prefix
                        JITASM_ASSERT(!reg.IsReg() || reg.GetSize() != O_SIZE_8 || reg.GetReg().id < AH || reg.GetReg().id >= R8B); // AH, BH, CH, or DH may not be used with REX.
                        JITASM_ASSERT(!r_m.IsReg() || r_m.GetSize() != O_SIZE_8 || r_m.GetReg().id < AH || r_m.GetReg().id >= R8B); // AH, BH, CH, or DH may not be used with REX.

                        if (flag & E_REP_PREFIX) db(0xF3);
                        if (r_m.IsMem() && r_m.GetAddressBaseSize() != O_SIZE_64) db(0x67);
                        if (flag & E_OPERAND_SIZE_PREFIX) db(0x66);

                        if (flag & E_MANDATORY_PREFIX_66) db(0x66);
                        else if (flag & E_MANDATORY_PREFIX_F2) db(0xF2);
                        else if (flag & E_MANDATORY_PREFIX_F3) db(0xF3);

                        db(0x40 | wrxb);
                    }
                    else
                    {
                        if (flag & E_MANDATORY_PREFIX_66) db(0x66);
                        else if (flag & E_MANDATORY_PREFIX_F2) db(0xF2);
                        else if (flag & E_MANDATORY_PREFIX_F3) db(0xF3);

                        if (flag & E_REP_PREFIX) db(0xF3);
                        if (r_m.IsMem() && r_m.GetAddressBaseSize() != O_SIZE_64) db(0x67);
                        if (flag & E_OPERAND_SIZE_PREFIX) db(0x66);
                    }
                }
            }

            void EncodeModRM(uint8 reg, const detail::Opd& r_m)
            {
                reg &= 0x7;

                if (r_m.IsReg())
                {
                    db(0xC0 | (reg << 3) | (r_m.GetReg().id & 0x7));
                }
                else if (r_m.IsMem())
                {
                    int base = r_m.GetBase().id; if (base != INVALID) base &= 0x7;
                    int index = r_m.GetIndex().id; if (index != INVALID) index &= 0x7;

                    if (base == INVALID && index == INVALID)
                    {
                        db(reg << 3 | 4);
                        db(0x25);
                        dd(r_m.GetDisp());
                    }
                    else if (r_m.GetBase().type == R_TYPE_IP)
                    {
                        db(0 << 6 | reg << 3 | 5);
                        dd(r_m.GetDisp());
                    }
                    else
                    {
                        JITASM_ASSERT(base != ESP || index != ESP);
                        JITASM_ASSERT(index != ESP || r_m.GetScale() == 0);

                        if (index == ESP)
                        {
                            index = base;
                            base = ESP;
                        }
                        bool sib = index != INVALID || r_m.GetScale() || base == ESP;

                        // ModR/M
                        uint8 mod = 0;
                        if (r_m.GetDisp() == 0 || (sib && base == INVALID)) mod = base != EBP ? 0 : 1;
                        else if (detail::IsInt8(r_m.GetDisp())) mod = 1;
                        else if (detail::IsInt32(r_m.GetDisp())) mod = 2;
                        else JITASM_ASSERT(0);
                        db(mod << 6 | reg << 3 | (sib ? 4 : base));

                        // SIB
                        if (sib)
                        {
                            uint8 ss = 0;
                            if (r_m.GetScale() == 0) ss = 0;
                            else if (r_m.GetScale() == 2) ss = 1;
                            else if (r_m.GetScale() == 4) ss = 2;
                            else if (r_m.GetScale() == 8) ss = 3;
                            else JITASM_ASSERT(0);
                            if (index != INVALID && base != INVALID)
                            {
                                db(ss << 6 | index << 3 | base);
                            }
                            else if (base != INVALID)
                            {
                                db(ss << 6 | 4 << 3 | base);
                            }
                            else if (index != INVALID)
                            {
                                db(ss << 6 | index << 3 | 5);
                            }
                            else
                            {
                                JITASM_ASSERT(0);
                            }
                        }
                        // Displacement
                        if (mod == 0 && sib && base == INVALID) dd(r_m.GetDisp());
                        if (mod == 1) db(r_m.GetDisp());
                        if (mod == 2) dd(r_m.GetDisp());
                    }
                }
                else
                {
                    JITASM_ASSERT(0);
                }
            }

            void EncodeOpcode(uint32 opcode)
            {
                if (opcode & 0xFF000000) db((opcode >> 24) & 0xFF);
                if (opcode & 0xFFFF0000) db((opcode >> 16) & 0xFF);
                if (opcode & 0xFFFFFF00) db((opcode >> 8)  & 0xFF);
                db(opcode & 0xFF);
            }

            void EncodeImm(const detail::Opd& imm)
            {
                const OpdSize size = imm.GetSize();
                if (size == O_SIZE_8) db(imm.GetImm());
                else if (size == O_SIZE_16) dw(imm.GetImm());
                else if (size == O_SIZE_32) dd(imm.GetImm());
                else if (size == O_SIZE_64) dq(imm.GetImm());
                else JITASM_ASSERT(0);
            }

            void EncodeSource(const detail::Opd& imm)
            {
                sources_.insert(std::make_pair(size_, u32(imm.GetImm())));
            }

            void EncodeMultiNop(const detail::Opd& imm)
            {
                size_t align = 1ULL << size_t(imm.GetImm());
                size_t bytes = ((size_ + align - 1) & size_t(-intptr_t(align))) - size_;
                switch (bytes)
                {
                    case  0: break;
                    case  1: PutBytes("\x90", 1); break;
                    case  2: PutBytes("\x66\x90", 2); break;
                    case  3: PutBytes("\x0f\x1f\x00", 3); break;
                    case  4: PutBytes("\x0f\x1f\x40\x00", 4); break;
                    case  5: PutBytes("\x0f\x1f\x44\x00\x00", 5); break;
                    case  6: PutBytes("\x66\x0f\x1f\x44\x00\x00", 6); break;
                    case  7: PutBytes("\x0f\x1f\x80\x00\x00\x00\x00", 7); break;
                    case  8: PutBytes("\x0f\x1f\x84\x00\x00\x00\x00\x00", 8); break;
                    case  9: PutBytes("\x66\x0f\x1f\x84\x00\x00\x00\x00\x00", 9); break;
                    case 10:
                    more_10: PutBytes("\x66\x2e\x0f\x1f\x84\x00\x00\x00\x00\x00", 10); break;
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15: PutBytes("\x66\x66\x66\x66\x66", bytes - 10); goto more_10;
                    default: JITASM_ASSERT(0);
                }
            }

            void Encode(const Instr& instr)
            {
                uint32 opcode = instr.opcode_;

                const detail::Opd& opd1 = instr.GetOpd(0).IsDummy() ? detail::Opd() : instr.GetOpd(0);  JITASM_ASSERT(!(opd1.IsReg() && opd1.GetReg().IsSymbolic()));
                const detail::Opd& opd2 = instr.GetOpd(1).IsDummy() ? detail::Opd() : instr.GetOpd(1);  JITASM_ASSERT(!(opd2.IsReg() && opd2.GetReg().IsSymbolic()));
                const detail::Opd& opd3 = instr.GetOpd(2).IsDummy() ? detail::Opd() : instr.GetOpd(2);  JITASM_ASSERT(!(opd3.IsReg() && opd3.GetReg().IsSymbolic()));
                const detail::Opd& opd4 = instr.GetOpd(3).IsDummy() ? detail::Opd() : instr.GetOpd(3);  JITASM_ASSERT(!(opd4.IsReg() && opd4.GetReg().IsSymbolic()));

                // +rb, +rw, +rd, +ro
                if (opd1.IsReg() && (opd2.IsNone() || opd2.IsImm()))
                {
                    opcode += opd1.GetReg().id & 0x7;
                }

                if ((opd1.IsImm() || opd1.IsReg()) && (opd2.IsReg() || opd2.IsMem()))
                {   // ModR/M
                    const detail::Opd& reg = opd1;
                    const detail::Opd& r_m = opd2;
                    const detail::Opd& vex = opd3;
                    EncodePrefixes(instr.encoding_flag_, reg, r_m, vex);
                    EncodeOpcode(opcode);
                    EncodeModRM((uint8)(reg.IsImm() ? reg.GetImm() : reg.GetReg().id), r_m);

                    // /is4
                    if (opd4.IsReg())
                    {
                        EncodeImm(Imm8(static_cast<uint8>(opd4.GetReg().id << 4)));
                    }
                }
                else
                {
                    const detail::Opd& reg = detail::Opd();
                    const detail::Opd& r_m = opd1.IsReg() ? opd1 : detail::Opd();
                    const detail::Opd& vex = detail::Opd();
                    EncodePrefixes(instr.encoding_flag_, reg, r_m, vex);
                    EncodeOpcode(opcode);
                }

                if (opd1.IsImm() && !opd2.IsReg() && !opd2.IsMem()) EncodeImm(opd1);
                if (opd2.IsImm())   EncodeImm(opd2);
                if (opd3.IsImm())   EncodeImm(opd3);
                if (opd4.IsImm())   EncodeImm(opd4);
            }

            void EncodeALU(const Instr& instr, uint32 opcode)
            {
                const detail::Opd& opd0 = instr.GetOpd(0);
                const detail::Opd& opd1 = instr.GetOpd(1);

                if (opd0.IsMem())
                {
                    if (opd1.IsMem() && opd0.GetSize() == O_SIZE_32)
                    {
                        PhysicalRegID tmp_id = EAX; // Defaulted to AL/AX/EAX

                        const detail::Opd& opd2 = instr.GetOpd(2);

                        if (opd2.IsReg() && opd2.reg_.type == R_TYPE_GP)
                        {
                            tmp_id = PhysicalRegID(opd2.reg_.id);
                        }

                        Encode(Instr(I_MOV, 0x8B, instr.encoding_flag_, W(Reg32(tmp_id)), R(opd0)));
                        Encode(Instr(instr.id_, instr.opcode_, instr.encoding_flag_, R(Reg32(tmp_id)), opd1.IsWrite() ? RW(opd1) : R(opd1)));
                        return;
                    }
                    else if (!(instr.opcode_&2))
                    {
                        Encode(Instr(instr.id_, instr.opcode_|2, instr.encoding_flag_, opd1.IsWrite() ? RW(opd1) : R(opd1), R(opd0)));
                        return;
                    }
                }
                else
                {
                    const detail::Opd& reg = instr.GetOpd(1);
                    const detail::Opd& imm = instr.GetOpd(2);
                    if (instr.GetOpd(0).IsImm() && imm.IsImm())
                    {
                        if (!imm.GetImm() && (instr.id_ == I_ADD || instr.id_ == I_SUB || instr.id_ == I_OR || instr.id_ == I_XOR))
                        {
                            return;
                        }

                        if (reg.IsReg() && (reg.GetReg().id == EAX && (reg.GetSize() == O_SIZE_8 || !detail::IsInt8(imm.GetImm()))))
                        {
                            opcode |= (reg.GetSize() == O_SIZE_8 ? 0 : 1);
                            Encode(Instr(instr.GetID(), opcode, instr.encoding_flag_, reg, imm));
                            return;
                        }
                    }
                }
                Encode(instr);
            }

            void EncodeJMP(const Instr& instr)
            {
                const detail::Opd& imm = instr.GetOpd(0);
                if (instr.GetID() == I_JMP)
                {
                    Encode(Instr(instr.GetID(), imm.GetSize() == O_SIZE_8 ? 0xEB : 0xE9, instr.encoding_flag_, imm));
                }
                else if (instr.GetID() == I_JCC)
                {
                    uint32 tttn = instr.opcode_;
                    if (tttn == JCC_ECXZ)       Encode(Instr(instr.GetID(), 0x67E3, instr.encoding_flag_, imm));
                    else if (tttn == JCC_RCXZ)  Encode(Instr(instr.GetID(), 0xE3, instr.encoding_flag_, imm));
                    else Encode(Instr(instr.GetID(), (imm.GetSize() == O_SIZE_8 ? 0x70 : 0x0F80) | tttn, instr.encoding_flag_, imm));
                }
                else if (instr.GetID() == I_LOOP)
                {
                    Encode(Instr(instr.GetID(), instr.opcode_, instr.encoding_flag_, imm));
                }
                else
                {
                    JITASM_ASSERT(0);
                }
            }

            void EncodeMOV(const Instr& instr)
            {
                // we don't encode "mov opd0, opd1" if both opd0 and opd1 are the same register
                const detail::Opd& opd0 = instr.GetOpd(0);
                const detail::Opd& opd1 = instr.GetOpd(1);
                if (instr.id_ != I_MOV || opd0 != opd1)
                {
                    if (opd0.IsMem())
                    {
                        if (opd1.IsImm())
                        {
                            switch (instr.opcode_)
                            {
                                case 0xB0:case 0xB1:case 0xB2:case 0xB3:case 0xB4:case 0xB5:case 0xB6:case 0xB7:
                                    Encode(Instr(instr.GetID(), 0xC6, instr.encoding_flag_, Imm8(0), opd0, opd1));
                                    return;
                                case 0xB8:case 0xB9:case 0xBA:case 0xBB:case 0xBC:case 0xBD:case 0xBE:case 0xBF:
                                    Encode(Instr(instr.GetID(), 0xC7, instr.encoding_flag_, Imm8(0), opd0, opd1));
                                    return;
                                default:
                                    break;
                            }
                        }
                        else if (opd1.IsMem())
                        {
                            auto & opdr = opd1.IsRead()  ? opd1 : opd0;
                            auto & opdw = opd0.IsWrite() ? opd0 : opd1;

                            InstrID movM2R = I_ADC;
                            InstrID movR2M = I_ADC;
                            UINT32  opcM2R = 0, opcR2M = 0;
                            UINT32  encM2R = 0, encR2M = 0;

                            switch (instr.id_)
                            {
                                case I_MOV:
                                {
                                    movM2R = I_MOV;
                                    opcM2R = 0x8A + !(opd1.GetSize() == O_SIZE_8);
                                    encM2R = opdr.GetSize() == O_SIZE_16 ? E_OPERAND_SIZE_PREFIX : 0;
                                    movR2M = I_MOV;
                                    opcR2M = 0x88 + !(opd1.GetSize() == O_SIZE_8);
                                    encR2M = opdw.GetSize() == O_SIZE_16 ? E_OPERAND_SIZE_PREFIX : 0;
                                    break;
                                }
                                case I_MOVZX:
                                {
                                    movM2R = I_MOVZX;
                                    opcM2R = 0x0FB6 + !(opd1.GetSize() == O_SIZE_8);
                                    encM2R = 0;
                                    movR2M = I_MOV;
                                    opcR2M = 0x89;
                                    encR2M = opdw.GetSize() == O_SIZE_16 ? E_OPERAND_SIZE_PREFIX : 0;
                                    break;
                                }
                                case I_MOVSX:
                                {
                                    movM2R = I_MOVSX;
                                    opcM2R = 0x0FBE + !(opd1.GetSize() == O_SIZE_8);
                                    encM2R = 0;
                                    movR2M = I_MOV;
                                    opcR2M = 0x89;
                                    encR2M = opdw.GetSize() == O_SIZE_16 ? E_OPERAND_SIZE_PREFIX : 0;
                                    break;
                                }
                            }

                            PhysicalRegID tmp_id = EAX; // Defaulted to AL/AX/EAX

                            const detail::Opd& opd2 = instr.GetOpd(2);

                            if (opd2.IsReg() && opd2.reg_.type == R_TYPE_GP)
                            {
                                tmp_id = PhysicalRegID(opd2.reg_.id);
                            }

                            Encode(Instr(movM2R, opcM2R, encM2R, W(Reg32(tmp_id)), opdr));
                            Encode(Instr(movR2M, opcR2M, encR2M, R(Reg32(tmp_id)), opdw));

                            return;
                        }
                        else if (instr.opcode_ == 0x8B)
                        {
                            Encode(Instr(I_MOV, 0x89, instr.encoding_flag_, opd1, opd0));
                            return;
                        }
                    }
                    Encode(instr);
                }
            }

            void EncodeTEST(const Instr& instr)
            {
                const detail::Opd& reg = instr.GetOpd(1);
                const detail::Opd& imm = instr.GetOpd(2);
                if (instr.GetOpd(0).IsImm() && reg.IsReg() && imm.IsImm() && reg.GetReg().id == EAX)
                {
                    uint32 opcode = 0xA8 | (reg.GetSize() == O_SIZE_8 ? 0 : 1);
                    Encode(Instr(instr.GetID(), opcode, instr.encoding_flag_, reg, imm));
                }
                else
                {
                    Encode(instr);
                }
            }

            void EncodeXCHG(const Instr& instr)
            {
                const detail::Opd& dst = instr.GetOpd(0);
                const detail::Opd& src = instr.GetOpd(1);
                if (dst != src)
                {
                    if (dst.IsReg() && src.IsReg())
                    {
                        if (dst.GetReg().id == EAX)
                        {
                            Encode(Instr(instr.GetID(), 0x90, instr.encoding_flag_, src));
                            return;
                        }
                        if (src.GetReg().id == EAX)
                        {
                            Encode(Instr(instr.GetID(), 0x90, instr.encoding_flag_, dst));
                            return;
                        }
                    }
                    Encode(instr);
                }
            }

            void Assemble(const Instr& instr)
            {
                switch (instr.GetID())
                {
                    case I_ADD:     EncodeALU(instr, 0x04); break;
                    case I_OR:      EncodeALU(instr, 0x0C); break;
                    case I_ADC:     EncodeALU(instr, 0x14); break;
                    case I_SBB:     EncodeALU(instr, 0x1C); break;
                    case I_AND:     EncodeALU(instr, 0x24); break;
                    case I_SUB:     EncodeALU(instr, 0x2C); break;
                    case I_XOR:     EncodeALU(instr, 0x34); break;
                    case I_CMP:     EncodeALU(instr, 0x3C); break;
                    case I_JMP:     EncodeJMP(instr); break;
                    case I_JCC:     EncodeJMP(instr); break;
                    case I_LOOP:    EncodeJMP(instr); break;
                    case I_MOV:     EncodeMOV(instr); break;
                    case I_MOVZX:   EncodeMOV(instr); break;
                    case I_MOVSX:   EncodeMOV(instr); break;
                    case I_TEST:    EncodeTEST(instr); break;
                    case I_XCHG:    EncodeXCHG(instr); break;
                    case I_ALIGN:   EncodeMultiNop(instr.GetOpd(0)); break;
                    case I_NULL:    break;
                    case I_SOURCE:  EncodeSource(instr.GetOpd(0)); break;
                    case I_GEN:     break;
                    case I_SAME:    break;
                    case I_KILL:    break;
                    case I_DB:      EncodeImm(instr.GetOpd(0)); break;
                    case I_DW:      EncodeImm(instr.GetOpd(0)); break;
                    case I_DD:      EncodeImm(instr.GetOpd(0)); break;
                    case I_DQ:      EncodeImm(instr.GetOpd(0)); break;
                    default:        Encode(instr); break;
                }
            }

            static size_t GetInstrCodeSize(const Instr& instr)
            {
                Backend backend;
                backend.Assemble(instr);
                return backend.GetSize();
            }
        };

        namespace detail
        {
            /// Counting 1-Bits
            inline uint32 Count1Bits(uint32 x)
            {
                x = x - ((x >> 1) & 0x55555555);
                x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
                x = (x + (x >> 4)) & 0x0F0F0F0F;
                x = x + (x >> 8);
                x = x + (x >> 16);
                return x & 0x0000003F;
            }

            /// The bit position of the first bit 1.
            inline uint32 bit_scan_forward(uint32 x)
            {
                JITASM_ASSERT(x != 0);
                unsigned long index;
                _BitScanForward(&index, x);
                return index;
            }

            /// The bit position of the last bit 1.
            inline uint32 bit_scan_reverse(uint32 x)
            {
                JITASM_ASSERT(x != 0);
                unsigned long index;
                _BitScanReverse(&index, x);
                return index;
            }

            /// Prior iterator
            template<class It> It prior(const It &it)
            {
                It i = it;
                return --i;
            }

            /// Next iterator
            template<class It> It next(const It &it)
            {
                It i = it;
                return ++i;
            }

            /// Iterator range
            template<class T, class It = typename T::iterator> struct Range : std::pair<It, It>
            {
                typedef It Iterator;
                Range() : std::pair<It, It>()
                {
                }
                Range(const It& f, const It& s) : std::pair<It, It>(f, s)
                {
                }
                Range(T& container) : std::pair<It, It>(container.begin(), container.end())
                {
                }
                bool empty() const
                {
                    return this->first == this->second;
                }
                size_t size() const
                {
                    return std::distance(this->first, this->second);
                }
            };

            /// Const iterator range
            template<class T> struct ConstRange : Range<T, typename T::const_iterator>
            {
                ConstRange() : Range<T, typename T::const_iterator>()
                {
                }
                ConstRange(const typename T::const_iterator& f, const typename T::const_iterator& s) : Range<T, typename T::const_iterator>(f, s)
                {
                }
                ConstRange(const T& container) : Range<T, typename T::const_iterator>(container.begin(), container.end())
                {
                }
            };

            inline void append_num(std::string& str, size_t num)
            {
                if (num >= 10)
                    append_num(str, num / 10);
                str.append(1, static_cast<char>('0' + num % 10));
            }

#if defined(JITASM_DEBUG_DUMP)
            /// Debug trace
            inline void Trace(const char *format, ...)
            {
#   if 0
                char szBuf[256];
                va_list args;
                va_start(args, format);
                _vsnprintf_s(szBuf, sizeof(szBuf) / sizeof(char), format, args);
                va_end(args);
                ::OutputDebugStringA(szBuf);
#   else
                va_list args;
                va_start(args, format);
                forcefv(cpu, format, args);
                va_end(args);
#   endif
            }
#endif

            /// Executable code buffer
            class CodeBuffer
            {
                void  * pbuff_;
                size_t  codesize_;
                size_t  buffsize_;

            public:
                CodeBuffer() : pbuff_(NULL), codesize_(0), buffsize_(0)
                {
                }
                ~CodeBuffer()
                {
                    Reset(0);
                }

                void * GetPointer() const
                {
                    return pbuff_;
                }
                size_t GetCodeSize() const
                {
                    return codesize_;
                }
                size_t GetBufferSize() const
                {
                    return buffsize_;
                }

                bool Reset(size_t codesize)
                {
                    if (pbuff_)
                    {
                        if (lle_jitasm$heap) ::RtlFreeHeap(lle_jitasm$heap, 0, pbuff_);
                        pbuff_ = NULL;
                        codesize_ = 0;
                        buffsize_ = 0;
                    }
                    if (codesize)
                    {
                        void * pbuff = ::RtlAllocateHeap(lle_jitasm$heap, 0, codesize);
                        if (!pbuff)
                        {
                            JITASM_ASSERT(0);
                            return false;
                        }
                        buffsize_ = codesize;

                        pbuff_ = pbuff;
                        codesize_ = codesize;
                    }
                    return true;
                }
            };

            /// Stack manager
            /**
            * <b>Stack layout</b>
            * \verbatim
            * +-----------------------+
            * | Caller return address |
            * +=======================+========
            * |       ebp (rbp)       |
            * +-----------------------+ <-- ebp (rbp)
            * |  Saved gp registers   |
            * +-----------------------+
            * | Padding for alignment |
            * +-----------------------+ <-- Stack base
            * |    Spill slots and    |
            * |    local variable     |
            * +-----------------------+ <-- esp (rsp)
            * \endverbatim
            */
            class StackManager
            {
            private:
                Addr stack_base_;
                uint32 stack_size_;

            public:
                StackManager() : stack_base_(RegID::CreatePhysicalRegID(R_TYPE_GP, EBX), 0), stack_size_(0)
                {
                }

                /// Get allocated stack size
                uint32 GetSize() const
                {
                    return (stack_size_ + 15) / 16 * 16; /* 16 bytes aligned*/
                }

                /// Get stack base
                Addr GetStackBase() const
                {
                    return stack_base_;
                }

                /// Set stack base
                void SetStackBase(const Addr& stack_base)
                {
                    stack_base_ = stack_base;
                }

                /// Allocate stack
                Addr Alloc(uint32 size, uint32 alignment)
                {
                    stack_size_ = (stack_size_ + alignment - 1) / alignment * alignment;
                    stack_size_ += size;
                    return stack_base_ - stack_size_;
                }
            };

            /// Spin lock
            class SpinLock
            {
                long lock_;
            public:
                SpinLock() : lock_(0)
                {
                }
                void Lock()
                {
                    while (interlocked_exchange(&lock_, 1));
                }
                void Unlock()
                {
                    interlocked_exchange(&lock_, 0);
                }
            };

            template<class Ty>
            class ScopedLock
            {
                Ty& lock_;
                ScopedLock<Ty>& operator=(const ScopedLock<Ty>&);
            public:
                ScopedLock(Ty& lock) : lock_(lock)
                {
                    lock.Lock();
                }
                ~ScopedLock()
                {
                    lock_.Unlock();
                }
            };
        }   // namespace detail

        // compiler prototype declaration
        struct Frontend;
        namespace compiler
        {
            void Compile(Frontend& f);
        }

        /// jitasm frontend
        struct Frontend
        {
            typedef jitasm::Addr    Addr;
            typedef jitasm::Reg     Reg;
            typedef jitasm::Reg8    Reg8;
            typedef jitasm::Reg16   Reg16;
            typedef jitasm::Reg32   Reg32;
            typedef jitasm::Reg64   Reg64;
            typedef jitasm::MmxReg  MmxReg;
            typedef jitasm::XmmReg  XmmReg;
            typedef jitasm::YmmReg  YmmReg;

            static Reg8         al, cl, dl, bl, ah, ch, dh, bh;
            static Reg16        ax, cx, dx, bx, sp, bp, si, di;
            static Reg32        eax, ecx, edx, ebx, esp, ebp, esi, edi;
            static FpuReg_st0   st0;
            static FpuReg       st1, st2, st3, st4, st5, st6, st7;
            static MmxReg       mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
            static XmmReg       xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7;
            static YmmReg       ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;
            static Reg8         r8b, r9b, r10b, r11b, r12b, r13b, r14b, r15b;
            static Reg16        r8w, r9w, r10w, r11w, r12w, r13w, r14w, r15w;
            static Reg32        r8d, r9d, r10d, r11d, r12d, r13d, r14d, r15d;
            static Reg64        rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15;
            static XmmReg       xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15;
            static YmmReg       ymm8, ymm9, ymm10, ymm11, ymm12, ymm13, ymm14, ymm15;
            static Rip64        rip;

            typedef AddressingPtr<Opd8>     BytePtr;
            typedef AddressingPtr<Opd16>    WordPtr;
            typedef AddressingPtr<Opd32>    DwordPtr;
            typedef AddressingPtr<Opd64>    QwordPtr;
            typedef AddressingPtr<Opd64>    MmwordPtr;
            typedef AddressingPtr<Opd128>   XmmwordPtr;
            typedef AddressingPtr<Opd256>   YmmwordPtr;
            typedef AddressingPtr<Opd32>    Real4Ptr;
            typedef AddressingPtr<Opd64>    Real8Ptr;
            typedef AddressingPtr<Opd80>    Real10Ptr;
            typedef AddressingPtr<Opd16>    M2bytePtr;
            typedef AddressingPtr<Opd224>   M28bytePtr;
            typedef AddressingPtr<Opd864>   M108bytePtr;
            typedef AddressingPtr<Opd4096>  M512bytePtr;

            AddressingPtr<Opd8>     byte_ptr;
            AddressingPtr<Opd16>    word_ptr;
            AddressingPtr<Opd32>    dword_ptr;
            AddressingPtr<Opd64>    qword_ptr;
            AddressingPtr<Opd64>    mmword_ptr;
            AddressingPtr<Opd128>   xmmword_ptr;
            AddressingPtr<Opd256>   ymmword_ptr;
            AddressingPtr<Opd32>    real4_ptr;
            AddressingPtr<Opd64>    real8_ptr;
            AddressingPtr<Opd80>    real10_ptr;
            AddressingPtr<Opd16>    m2byte_ptr;
            AddressingPtr<Opd224>   m28byte_ptr;
            AddressingPtr<Opd864>   m108byte_ptr;
            AddressingPtr<Opd4096>  m512byte_ptr;

            static Reg              zax, zcx, zdx, zbx, zsp, zbp, zsi, zdi;
            AddressingPtr<Opd64>    ptr;

            typedef std::vector<Instr>                              InstrList;
            typedef std::set< size_t >                              IndexList;
            typedef std::map< size_t, std::pair< size_t, size_t > > LinkList;

            InstrList               instrs_;
            bool                    assembled_;
            detail::CodeBuffer      codebuff_;
            detail::SpinLock        codelock_;
            detail::StackManager    stack_manager_;
            IndexList               indices_;
            LinkList                links_;

        private:
            template<typename OpdN>
            struct RipPtr : AddressingPtr<OpdN>
            {
                MemT<OpdN> operator[](u32 label_name)
                {
                    MemT<OpdN> result(O_SIZE_64, O_SIZE_64, RegID::CreatePhysicalRegID(R_TYPE_IP, RIP), RegID::Invalid(), 0, 0);
                    switch (result.GetSize())
                    {
                        case O_SIZE_8:    return result[((Frontend*)((char*)this - offsetof(Frontend, byte_rip_ptr)))->GetLabelID(label_name)];
                        case O_SIZE_16:   return result[((Frontend*)((char*)this - offsetof(Frontend, word_rip_ptr)))->GetLabelID(label_name)];
                        case O_SIZE_32:   return result[((Frontend*)((char*)this - offsetof(Frontend, dword_rip_ptr)))->GetLabelID(label_name)];
                        case O_SIZE_64:   return result[((Frontend*)((char*)this - offsetof(Frontend, qword_rip_ptr)))->GetLabelID(label_name)];
                        case O_SIZE_128:  return result[((Frontend*)((char*)this - offsetof(Frontend, xmmword_rip_ptr)))->GetLabelID(label_name)];
                        case O_SIZE_256:  return result[((Frontend*)((char*)this - offsetof(Frontend, ymmword_rip_ptr)))->GetLabelID(label_name)];
                    }
                    return result;
                }
            };

        public:
            RipPtr<Opd8>        byte_rip_ptr;
            RipPtr<Opd16>       word_rip_ptr;
            RipPtr<Opd32>       dword_rip_ptr;
            RipPtr<Opd64>       qword_rip_ptr;
            RipPtr<Opd128>      xmmword_rip_ptr;
            RipPtr<Opd256>      ymmword_rip_ptr;

            struct Label
            {
                u32         name;
                size_t      instr_number;
                explicit Label(u32 name_) : name(name_), instr_number(0)
                {
                }
            };
            typedef std::deque<Label> LabelList;
            LabelList   labels_;


            Frontend() : assembled_(false)
            {
            }
            virtual ~Frontend()
            {
            }

            virtual void InternalMain() = 0;

            /// Declare variable of the function argument on register
            void DeclareRegArg(const detail::Opd& var, const detail::Opd& arg, const detail::Opd& spill_slot = detail::Opd())
            {
                JITASM_ASSERT(var.IsReg() && arg.IsReg());
                // Insert special instruction after Prolog
                InstrList::iterator it = instrs_.begin();
                if (!instrs_.empty() && instrs_[0].GetID() == I_COMPILER_PROLOG) ++it;
                // The arg is passed as register constraint of the var.
                instrs_.insert(it, Instr(I_COMPILER_DECLARE_REG_ARG, 0, E_SPECIAL, Dummy(W(var), arg), spill_slot));
            }

            /// Declare variable of the function argument on stack
            void DeclareStackArg(const detail::Opd& var, const detail::Opd& arg)
            {
                JITASM_ASSERT(var.IsReg() && arg.IsMem());
                // Insert special instruction after Prolog
                InstrList::iterator it = instrs_.begin();
                if (!instrs_.empty() && instrs_[0].GetID() == I_COMPILER_PROLOG) ++it;
                instrs_.insert(it, Instr(I_COMPILER_DECLARE_STACK_ARG, 0, E_SPECIAL, W(var), R(arg)));
            }

            /// Declare variable of the function result on register
            void DeclareResultReg(const detail::Opd& var)
            {
                JITASM_ASSERT(var.IsReg());
                // The result register is passed as register constraint of the var.
                if (var.IsGpReg())
                {
                    AppendInstr(I_COMPILER_DECLARE_RESULT_REG, 0, E_SPECIAL, Dummy(R(var), zax));
                }
                else if (var.IsMmxReg())
                {
                    AppendInstr(I_COMPILER_DECLARE_RESULT_REG, 0, E_SPECIAL, Dummy(R(var), mm0));
                }
                else if (var.IsXmmReg())
                {
                    AppendInstr(I_COMPILER_DECLARE_RESULT_REG, 0, E_SPECIAL, Dummy(R(var), xmm0));
                }
            }

            /// Function prolog
            void Prolog()
            {
                AppendInstr(I_COMPILER_PROLOG, 0, E_SPECIAL);
            }

            /// Function epilog
            void Epilog()
            {
                AppendInstr(I_COMPILER_EPILOG, 0, E_SPECIAL);
            }

            static bool IsJump(InstrID id)
            {
                return id == I_JMP || id == I_JCC || id == I_LOOP;
            }

            static bool HasRIP(const detail::Opd& opd)
            {
                return opd.IsMem() && (opd.GetBase().type == R_TYPE_IP);
            }

            size_t GetJumpTo(const Instr& instr) const
            {
                size_t label_id = (size_t)instr.GetOpd(0).GetImm();
                JITASM_ASSERT(labels_[label_id].instr_number != (size_t)-1);    // invalid label
                return label_id != size_t(-1) ? labels_[label_id].instr_number : 0;
            }

            void ResolveJumpAndRIP();

            /// Assemble
            void Assemble();

            /// Get assembled code
            void * GetCode()
            {
                if (!assembled_)
                {
                    Assemble();
                }
                return (void *)((char *)codebuff_.GetPointer());
            }

            /// Get total size of machine code
            size_t GetCodeSize() const
            {
                return codebuff_.GetCodeSize();
            }

            void AppendInstr(InstrID id, uint32 opcode, uint32 encoding_flag, const detail::Opd& opd1 = detail::Opd(), const detail::Opd& opd2 = detail::Opd(), const detail::Opd& opd3 = detail::Opd(), const detail::Opd& opd4 = detail::Opd(), const detail::Opd& opd5 = detail::Opd(), const detail::Opd& opd6 = detail::Opd())
            {
                instrs_.push_back(Instr(id, opcode, encoding_flag, opd1, opd2, opd3, opd4, opd5, opd6));
            }

            void AppendJmp(size_t label_id, bool special = false)
            {
                AppendInstr(I_JMP, 0, special ? E_SPECIAL : 0, Imm64(label_id));
            }

            void AppendJcc(JumpCondition jcc, size_t label_id)
            {
                AppendInstr(I_JCC, jcc, 0, Imm64(label_id));
            }

            /// Change label id of jump instruction
            static void ChangeLabelID(Instr& instr, size_t label_id)
            {
                JITASM_ASSERT(IsJump(instr.id_) && instr.GetOpd(0).IsImm());
                instr.GetOpd(0).imm_ = label_id;
            }

            size_t NewLabelID(u32 label_name)
            {
                labels_.push_back(Label(label_name));
                return labels_.size() - 1;
            }

            size_t CheckLabelID(u32 label_name)
            {
                for (size_t i = 0; i < labels_.size(); i++)
                {
                    if (labels_[i].name == label_name)
                    {
                        return i;
                    }
                }
                return (size_t)-1;
            }

            size_t GetLabelID(u32 label_name)
            {
                for (size_t i = 0; i < labels_.size(); i++)
                {
                    if (labels_[i].name == label_name)
                    {
                        return i;
                    }
                }
                return NewLabelID(label_name);
            }

            /// Label
            void L(u32 label_name)
            {
                labels_[GetLabelID(label_name)].instr_number = instrs_.size();
            }

            /// Alignment
            void align(const Imm8& imm = 4)
            {
                AppendInstr(I_ALIGN, 0, E_SPECIAL, imm);
            }

            void source(u32 label_name)
            {
                AppendInstr(I_SOURCE, 0, 0, Imm32(label_name));
            }

            /// Data
            void db(const Imm8& imm)
            {
                AppendInstr(I_DB, 0, E_SPECIAL, imm);
            }

            void dw(const Imm16& imm)
            {
                AppendInstr(I_DW, 0, E_SPECIAL, imm);
            }

            void dd(const Imm32& imm)
            {
                AppendInstr(I_DD, 0, E_SPECIAL, imm);
            }

            void dq(const Imm64& imm)
            {
                AppendInstr(I_DQ, 0, E_SPECIAL, imm);
            }

            // General-Purpose Instructions
            void adc(const Reg8& dst, const Imm8& imm)
            {
                AppendInstr(I_ADC, 0x80, 0, Imm8(2), RW(dst), imm);
            }
            void adc(const Mem8& dst, const Imm8& imm)
            {
                AppendInstr(I_ADC, 0x80, 0, Imm8(2), RW(dst), imm);
            }
            void adc(const Reg16& dst, const Imm16& imm)
            {
                AppendInstr(I_ADC, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst), detail::ImmXor8(imm));
            }
            void adc(const Mem16& dst, const Imm16& imm)
            {
                AppendInstr(I_ADC, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst), detail::ImmXor8(imm));
            }
            void adc(const Reg32& dst, const Imm32& imm)
            {
                AppendInstr(I_ADC, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(2), RW(dst), detail::ImmXor8(imm));
            }
            void adc(const Mem32& dst, const Imm32& imm)
            {
                AppendInstr(I_ADC, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(2), RW(dst), detail::ImmXor8(imm));
            }
            void adc(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_ADC, 0x10, 0, R(src), RW(dst));
            }
            void adc(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_ADC, 0x10, 0, R(src), RW(dst));
            }
            void adc(const Reg8& dst, const Mem8& src)
            {
                AppendInstr(I_ADC, 0x12, 0, RW(dst), R(src));
            }
            void adc(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_ADC, 0x11, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void adc(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_ADC, 0x11, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void adc(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_ADC, 0x13, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void adc(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_ADC, 0x11, 0, R(src), RW(dst));
            }
            void adc(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_ADC, 0x11, 0, R(src), RW(dst));
            }
            void adc(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_ADC, 0x13, 0, RW(dst), R(src));
            }
            void adc(const Reg64& dst, const Imm32& imm)
            {
                AppendInstr(I_ADC, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(2), RW(dst), detail::ImmXor8(imm));
            }
            void adc(const Mem64& dst, const Imm32& imm)
            {
                AppendInstr(I_ADC, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(2), RW(dst), detail::ImmXor8(imm));
            }
            void adc(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_ADC, 0x11, E_REXW_PREFIX, R(src), RW(dst));
            }
            void adc(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_ADC, 0x11, E_REXW_PREFIX, R(src), RW(dst));
            }
            void adc(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_ADC, 0x13, E_REXW_PREFIX, RW(dst), R(src));
            }
            void add(const Reg8& dst, const Imm8& imm)
            {
                AppendInstr(I_ADD, 0x80, 0, Imm8(0), RW(dst), imm);
            }
            void add(const Mem8& dst, const Imm8& imm)
            {
                AppendInstr(I_ADD, 0x80, 0, Imm8(0), RW(dst), imm);
            }
            void add(const Reg16& dst, const Imm16& imm)
            {
                AppendInstr(I_ADD, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst), detail::ImmXor8(imm));
            }
            void add(const Mem16& dst, const Imm16& imm)
            {
                AppendInstr(I_ADD, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst), detail::ImmXor8(imm));
            }
            void add(const Reg32& dst, const Imm32& imm)
            {
                AppendInstr(I_ADD, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(0), RW(dst), detail::ImmXor8(imm));
            }
            void add(const Mem32& dst, const Imm32& imm)
            {
                AppendInstr(I_ADD, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(0), RW(dst), detail::ImmXor8(imm));
            }
            void add(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_ADD, 0x00, 0, R(src), RW(dst));
            }
            void add(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_ADD, 0x00, 0, R(src), RW(dst));
            }
            void add(const Reg8& dst, const Mem8& src)
            {
                AppendInstr(I_ADD, 0x02, 0, RW(dst), R(src));
            }
            void add(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_ADD, 0x01, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void add(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_ADD, 0x01, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void add(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_ADD, 0x03, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void add(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_ADD, 0x01, 0, R(src), RW(dst));
            }
            void add(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_ADD, 0x01, 0, R(src), RW(dst));
            }
            void add(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_ADD, 0x03, 0, RW(dst), R(src));
            }
            void add(const Reg64& dst, const Imm32& imm)
            {
                AppendInstr(I_ADD, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(0), RW(dst), detail::ImmXor8(imm));
            }
            void add(const Mem64& dst, const Imm32& imm)
            {
                AppendInstr(I_ADD, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(0), RW(dst), detail::ImmXor8(imm));
            }
            void add(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_ADD, 0x01, E_REXW_PREFIX, R(src), RW(dst));
            }
            void add(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_ADD, 0x01, E_REXW_PREFIX, R(src), RW(dst));
            }
            void add(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_ADD, 0x03, E_REXW_PREFIX, RW(dst), R(src));
            }
            void and(const Reg8& dst, const Imm8& imm)
            {
                AppendInstr(I_AND, 0x80, 0, Imm8(4), RW(dst), imm);
            }
            void and(const Mem8& dst, const Imm8& imm)
            {
                AppendInstr(I_AND, 0x80, 0, Imm8(4), RW(dst), imm);
            }
            void and(const Reg16& dst, const Imm16& imm)
            {
                AppendInstr(I_AND, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(4), RW(dst), detail::ImmXor8(imm));
            }
            void and(const Mem16& dst, const Imm16& imm)
            {
                AppendInstr(I_AND, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(4), RW(dst), detail::ImmXor8(imm));
            }
            void and(const Reg32& dst, const Imm32& imm)
            {
                AppendInstr(I_AND, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(4), RW(dst), detail::ImmXor8(imm));
            }
            void and(const Mem32& dst, const Imm32& imm)
            {
                AppendInstr(I_AND, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(4), RW(dst), detail::ImmXor8(imm));
            }
            void and(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_AND, 0x20, 0, R(src), RW(dst));
            }
            void and(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_AND, 0x20, 0, R(src), RW(dst));
            }
            void and(const Reg8& dst, const Mem8& src)
            {
                AppendInstr(I_AND, 0x22, 0, RW(dst), R(src));
            }
            void and(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_AND, 0x21, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void and(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_AND, 0x21, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void and(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_AND, 0x23, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void and(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_AND, 0x21, 0, R(src), RW(dst));
            }
            void and(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_AND, 0x21, 0, R(src), RW(dst));
            }
            void and(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_AND, 0x23, 0, RW(dst), R(src));
            }
            void and(const Reg64& dst, const Imm32& imm)
            {
                AppendInstr(I_AND, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(4), RW(dst), detail::ImmXor8(imm));
            }
            void and(const Mem64& dst, const Imm32& imm)
            {
                AppendInstr(I_AND, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(4), RW(dst), detail::ImmXor8(imm));
            }
            void and(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_AND, 0x21, E_REXW_PREFIX, R(src), RW(dst));
            }
            void and(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_AND, 0x21, E_REXW_PREFIX, R(src), RW(dst));
            }
            void and(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_AND, 0x23, E_REXW_PREFIX, RW(dst), R(src));
            }
            void bsf(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_BSF, 0x0FBC, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void bsf(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_BSF, 0x0FBC, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void bsf(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_BSF, 0x0FBC, 0, W(dst), R(src));
            }
            void bsf(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_BSF, 0x0FBC, 0, W(dst), R(src));
            }
            void bsf(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_BSF, 0x0FBC, E_REXW_PREFIX, W(dst), R(src));
            }
            void bsf(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_BSF, 0x0FBC, E_REXW_PREFIX, W(dst), R(src));
            }
            void bsr(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_BSR, 0x0FBD, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void bsr(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_BSR, 0x0FBD, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void bsr(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_BSR, 0x0FBD, 0, W(dst), R(src));
            }
            void bsr(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_BSR, 0x0FBD, 0, W(dst), R(src));
            }
            void bsr(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_BSR, 0x0FBD, E_REXW_PREFIX, W(dst), R(src));
            }
            void bsr(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_BSR, 0x0FBD, E_REXW_PREFIX, W(dst), R(src));
            }
            void bswap(const Reg32& dst)
            {
                AppendInstr(I_BSWAP, 0x0FC8, 0, RW(dst));
            }
            void bswap(const Reg64& dst)
            {
                AppendInstr(I_BSWAP, 0x0FC8, E_REXW_PREFIX, RW(dst));
            }
            void bt(const Reg16& bitbase, const Reg16& bitoffset)
            {
                AppendInstr(I_BT, 0x0FA3, E_OPERAND_SIZE_PREFIX, R(bitoffset), R(bitbase));
            }
            void bt(const Mem16& bitbase, const Reg16& bitoffset)
            {
                AppendInstr(I_BT, 0x0FA3, E_OPERAND_SIZE_PREFIX, R(bitoffset), R(bitbase));
            }
            void bt(const Reg32& bitbase, const Reg32& bitoffset)
            {
                AppendInstr(I_BT, 0x0FA3, 0, R(bitoffset), R(bitbase));
            }
            void bt(const Mem32& bitbase, const Reg32& bitoffset)
            {
                AppendInstr(I_BT, 0x0FA3, 0, R(bitoffset), R(bitbase));
            }
            void bt(const Reg16& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BT, 0x0FBA, E_OPERAND_SIZE_PREFIX, Imm8(4), R(bitbase), bitoffset);
            }
            void bt(const Mem16& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BT, 0x0FBA, E_OPERAND_SIZE_PREFIX, Imm8(4), R(bitbase), bitoffset);
            }
            void bt(const Reg32& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BT, 0x0FBA, 0, Imm8(4), R(bitbase), bitoffset);
            }
            void bt(const Mem32& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BT, 0x0FBA, 0, Imm8(4), R(bitbase), bitoffset);
            }
            void bt(const Reg64& bitbase, const Reg64& bitoffset)
            {
                AppendInstr(I_BT, 0x0FA3, E_REXW_PREFIX, R(bitoffset), R(bitbase));
            }
            void bt(const Mem64& bitbase, const Reg64& bitoffset)
            {
                AppendInstr(I_BT, 0x0FA3, E_REXW_PREFIX, R(bitoffset), R(bitbase));
            }
            void bt(const Reg64& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BT, 0x0FBA, E_REXW_PREFIX, Imm8(4), R(bitbase), bitoffset);
            }
            void bt(const Mem64& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BT, 0x0FBA, E_REXW_PREFIX, Imm8(4), R(bitbase), bitoffset);
            }
            void btc(const Reg16& bitbase, const Reg16& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBB, E_OPERAND_SIZE_PREFIX, R(bitoffset), RW(bitbase));
            }
            void btc(const Mem16& bitbase, const Reg16& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBB, E_OPERAND_SIZE_PREFIX, R(bitoffset), RW(bitbase));
            }
            void btc(const Reg32& bitbase, const Reg32& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBB, 0, R(bitoffset), RW(bitbase));
            }
            void btc(const Mem32& bitbase, const Reg32& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBB, 0, R(bitoffset), RW(bitbase));
            }
            void btc(const Reg16& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBA, E_OPERAND_SIZE_PREFIX, Imm8(7), RW(bitbase), bitoffset);
            }
            void btc(const Mem16& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBA, E_OPERAND_SIZE_PREFIX, Imm8(7), RW(bitbase), bitoffset);
            }
            void btc(const Reg32& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBA, 0, Imm8(7), RW(bitbase), bitoffset);
            }
            void btc(const Mem32& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBA, 0, Imm8(7), RW(bitbase), bitoffset);
            }
            void btc(const Reg64& bitbase, const Reg64& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBB, E_REXW_PREFIX, R(bitoffset), RW(bitbase));
            }
            void btc(const Mem64& bitbase, const Reg64& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBB, E_REXW_PREFIX, R(bitoffset), RW(bitbase));
            }
            void btc(const Reg64& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBA, E_REXW_PREFIX, Imm8(7), RW(bitbase), bitoffset);
            }
            void btc(const Mem64& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTC, 0x0FBA, E_REXW_PREFIX, Imm8(7), RW(bitbase), bitoffset);
            }
            void btr(const Reg16& bitbase, const Reg16& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FB3, E_OPERAND_SIZE_PREFIX, R(bitoffset), RW(bitbase));
            }
            void btr(const Mem16& bitbase, const Reg16& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FB3, E_OPERAND_SIZE_PREFIX, R(bitoffset), RW(bitbase));
            }
            void btr(const Reg32& bitbase, const Reg32& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FB3, 0, R(bitoffset), RW(bitbase));
            }
            void btr(const Mem32& bitbase, const Reg32& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FB3, 0, R(bitoffset), RW(bitbase));
            }
            void btr(const Reg16& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FBA, E_OPERAND_SIZE_PREFIX, Imm8(6), RW(bitbase), bitoffset);
            }
            void btr(const Mem16& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FBA, E_OPERAND_SIZE_PREFIX, Imm8(6), RW(bitbase), bitoffset);
            }
            void btr(const Reg32& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FBA, 0, Imm8(6), RW(bitbase), bitoffset);
            }
            void btr(const Mem32& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FBA, 0, Imm8(6), RW(bitbase), bitoffset);
            }
            void btr(const Reg64& bitbase, const Reg64& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FB3, E_REXW_PREFIX, R(bitoffset), RW(bitbase));
            }
            void btr(const Mem64& bitbase, const Reg64& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FB3, E_REXW_PREFIX, R(bitoffset), RW(bitbase));
            }
            void btr(const Reg64& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FBA, E_REXW_PREFIX, Imm8(6), RW(bitbase), bitoffset);
            }
            void btr(const Mem64& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTR, 0x0FBA, E_REXW_PREFIX, Imm8(6), RW(bitbase), bitoffset);
            }
            void bts(const Reg16& bitbase, const Reg16& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FAB, E_OPERAND_SIZE_PREFIX, R(bitoffset), RW(bitbase));
            }
            void bts(const Mem16& bitbase, const Reg16& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FAB, E_OPERAND_SIZE_PREFIX, R(bitoffset), RW(bitbase));
            }
            void bts(const Reg32& bitbase, const Reg32& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FAB, 0, R(bitoffset), RW(bitbase));
            }
            void bts(const Mem32& bitbase, const Reg32& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FAB, 0, R(bitoffset), RW(bitbase));
            }
            void bts(const Reg16& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FBA, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(bitbase), bitoffset);
            }
            void bts(const Mem16& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FBA, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(bitbase), bitoffset);
            }
            void bts(const Reg32& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FBA, 0, Imm8(5), RW(bitbase), bitoffset);
            }
            void bts(const Mem32& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FBA, 0, Imm8(5), RW(bitbase), bitoffset);
            }
            void bts(const Reg64& bitbase, const Reg64& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FAB, E_REXW_PREFIX, R(bitoffset), RW(bitbase));
            }
            void bts(const Mem64& bitbase, const Reg64& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FAB, E_REXW_PREFIX, R(bitoffset), RW(bitbase));
            }
            void bts(const Reg64& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FBA, E_REXW_PREFIX, Imm8(5), RW(bitbase), bitoffset);
            }
            void bts(const Mem64& bitbase, const Imm8& bitoffset)
            {
                AppendInstr(I_BTS, 0x0FBA, E_REXW_PREFIX, Imm8(5), RW(bitbase), bitoffset);
            }
            void call(const Reg64& dst, bool no_break = false)
            {
                AppendInstr(I_CALL, 0xFF, no_break ? E_NO_BREAK : 0, Imm8(2), R(dst));
            }
            void call(const Mem64& dst, bool no_break = false)
            {
                AppendInstr(I_CALL, 0xFF, no_break ? E_NO_BREAK : 0, Imm8(2), R(dst));
            }
            void jmp(const Reg64& dst)
            {
                AppendInstr(I_CALL, 0xFF, E_SPECIAL, Imm8(4), R(dst));
            }
            void jmp(const Mem64& dst)
            {
                AppendInstr(I_CALL, 0xFF, E_SPECIAL, Imm8(4), R(dst));
            }
            void cbw()
            {
                AppendInstr(I_CBW, 0x98, E_OPERAND_SIZE_PREFIX, Dummy(RW(eax)));
            }
            void cwde()
            {
                AppendInstr(I_CBW, 0x98, 0, Dummy(RW(eax)));
            }
            void cdqe()
            {
                AppendInstr(I_CBW, 0x98, E_REXW_PREFIX, Dummy(RW(eax)));
            }
            void clc()
            {
                AppendInstr(I_CLC, 0xF8, 0);
            }
            void cld()
            {
                AppendInstr(I_CLD, 0xFC, 0);
            }
            void cli()
            {
                AppendInstr(I_CLI, 0xFA, 0);
            }
            void clts()
            {
                AppendInstr(I_CLTS, 0x0F06, 0);
            }
            void cmc()
            {
                AppendInstr(I_CMC, 0xF5, 0);
            }
            void cmova(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F47, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmova(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F47, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovae(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F43, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovae(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F43, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovb(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F42, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovb(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F42, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovbe(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F46, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovbe(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F46, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovc(const Reg16& dst, const Reg16& src)
            {
                cmovb(dst, src);
            }
            void cmovc(const Reg16& dst, const Mem16& src)
            {
                cmovb(dst, src);
            }
            void cmove(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F44, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmove(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F44, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovg(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4F, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovg(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4F, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovge(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4D, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovge(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4D, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovl(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4C, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovl(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4C, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovle(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4E, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovle(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4E, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovna(const Reg16& dst, const Reg16& src)
            {
                cmovbe(dst, src);
            }
            void cmovna(const Reg16& dst, const Mem16& src)
            {
                cmovbe(dst, src);
            }
            void cmovnae(const Reg16& dst, const Reg16& src)
            {
                cmovb(dst, src);
            }
            void cmovnae(const Reg16& dst, const Mem16& src)
            {
                cmovb(dst, src);
            }
            void cmovnb(const Reg16& dst, const Reg16& src)
            {
                cmovae(dst, src);
            }
            void cmovnb(const Reg16& dst, const Mem16& src)
            {
                cmovae(dst, src);
            }
            void cmovnbe(const Reg16& dst, const Reg16& src)
            {
                cmova(dst, src);
            }
            void cmovnbe(const Reg16& dst, const Mem16& src)
            {
                cmova(dst, src);
            }
            void cmovnc(const Reg16& dst, const Reg16& src)
            {
                cmovae(dst, src);
            }
            void cmovnc(const Reg16& dst, const Mem16& src)
            {
                cmovae(dst, src);
            }
            void cmovne(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F45, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovne(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F45, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovng(const Reg16& dst, const Reg16& src)
            {
                cmovle(dst, src);
            }
            void cmovng(const Reg16& dst, const Mem16& src)
            {
                cmovle(dst, src);
            }
            void cmovnge(const Reg16& dst, const Reg16& src)
            {
                cmovl(dst, src);
            }
            void cmovnge(const Reg16& dst, const Mem16& src)
            {
                cmovl(dst, src);
            }
            void cmovnl(const Reg16& dst, const Reg16& src)
            {
                cmovge(dst, src);
            }
            void cmovnl(const Reg16& dst, const Mem16& src)
            {
                cmovge(dst, src);
            }
            void cmovnle(const Reg16& dst, const Reg16& src)
            {
                cmovg(dst, src);
            }
            void cmovnle(const Reg16& dst, const Mem16& src)
            {
                cmovg(dst, src);
            }
            void cmovno(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F41, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovno(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F41, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovnp(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4B, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovnp(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4B, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovns(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F49, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovns(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F49, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovnz(const Reg16& dst, const Reg16& src)
            {
                cmovne(dst, src);
            }
            void cmovnz(const Reg16& dst, const Mem16& src)
            {
                cmovne(dst, src);
            }
            void cmovo(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F40, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovo(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F40, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovp(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4A, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovp(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4A, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovpe(const Reg16& dst, const Reg16& src)
            {
                cmovp(dst, src);
            }
            void cmovpe(const Reg16& dst, const Mem16& src)
            {
                cmovp(dst, src);
            }
            void cmovpo(const Reg16& dst, const Reg16& src)
            {
                cmovnp(dst, src);
            }
            void cmovpo(const Reg16& dst, const Mem16& src)
            {
                cmovnp(dst, src);
            }
            void cmovs(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F48, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovs(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_CMOVCC, 0x0F48, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void cmovz(const Reg16& dst, const Reg16& src)
            {
                cmove(dst, src);
            }
            void cmovz(const Reg16& dst, const Mem16& src)
            {
                cmove(dst, src);
            }
            void cmova(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F47, 0, RW(dst), R(src));
            }
            void cmova(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F47, 0, RW(dst), R(src));
            }
            void cmovae(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F43, 0, RW(dst), R(src));
            }
            void cmovae(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F43, 0, RW(dst), R(src));
            }
            void cmovb(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F42, 0, RW(dst), R(src));
            }
            void cmovb(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F42, 0, RW(dst), R(src));
            }
            void cmovbe(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F46, 0, RW(dst), R(src));
            }
            void cmovbe(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F46, 0, RW(dst), R(src));
            }
            void cmovc(const Reg32& dst, const Reg32& src)
            {
                cmovb(dst, src);
            }
            void cmovc(const Reg32& dst, const Mem32& src)
            {
                cmovb(dst, src);
            }
            void cmove(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F44, 0, RW(dst), R(src));
            }
            void cmove(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F44, 0, RW(dst), R(src));
            }
            void cmovg(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4F, 0, RW(dst), R(src));
            }
            void cmovg(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4F, 0, RW(dst), R(src));
            }
            void cmovge(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4D, 0, RW(dst), R(src));
            }
            void cmovge(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4D, 0, RW(dst), R(src));
            }
            void cmovl(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4C, 0, RW(dst), R(src));
            }
            void cmovl(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4C, 0, RW(dst), R(src));
            }
            void cmovle(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4E, 0, RW(dst), R(src));
            }
            void cmovle(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4E, 0, RW(dst), R(src));
            }
            void cmovna(const Reg32& dst, const Reg32& src)
            {
                cmovbe(dst, src);
            }
            void cmovna(const Reg32& dst, const Mem32& src)
            {
                cmovbe(dst, src);
            }
            void cmovnae(const Reg32& dst, const Reg32& src)
            {
                cmovb(dst, src);
            }
            void cmovnae(const Reg32& dst, const Mem32& src)
            {
                cmovb(dst, src);
            }
            void cmovnb(const Reg32& dst, const Reg32& src)
            {
                cmovae(dst, src);
            }
            void cmovnb(const Reg32& dst, const Mem32& src)
            {
                cmovae(dst, src);
            }
            void cmovnbe(const Reg32& dst, const Reg32& src)
            {
                cmova(dst, src);
            }
            void cmovnbe(const Reg32& dst, const Mem32& src)
            {
                cmova(dst, src);
            }
            void cmovnc(const Reg32& dst, const Reg32& src)
            {
                cmovae(dst, src);
            }
            void cmovnc(const Reg32& dst, const Mem32& src)
            {
                cmovae(dst, src);
            }
            void cmovne(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F45, 0, RW(dst), R(src));
            }
            void cmovne(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F45, 0, RW(dst), R(src));
            }
            void cmovng(const Reg32& dst, const Reg32& src)
            {
                cmovle(dst, src);
            }
            void cmovng(const Reg32& dst, const Mem32& src)
            {
                cmovle(dst, src);
            }
            void cmovnge(const Reg32& dst, const Reg32& src)
            {
                cmovl(dst, src);
            }
            void cmovnge(const Reg32& dst, const Mem32& src)
            {
                cmovl(dst, src);
            }
            void cmovnl(const Reg32& dst, const Reg32& src)
            {
                cmovge(dst, src);
            }
            void cmovnl(const Reg32& dst, const Mem32& src)
            {
                cmovge(dst, src);
            }
            void cmovnle(const Reg32& dst, const Reg32& src)
            {
                cmovg(dst, src);
            }
            void cmovnle(const Reg32& dst, const Mem32& src)
            {
                cmovg(dst, src);
            }
            void cmovno(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F41, 0, RW(dst), R(src));
            }
            void cmovno(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F41, 0, RW(dst), R(src));
            }
            void cmovnp(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4B, 0, RW(dst), R(src));
            }
            void cmovnp(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4B, 0, RW(dst), R(src));
            }
            void cmovns(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F49, 0, RW(dst), R(src));
            }
            void cmovns(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F49, 0, RW(dst), R(src));
            }
            void cmovnz(const Reg32& dst, const Reg32& src)
            {
                cmovne(dst, src);
            }
            void cmovnz(const Reg32& dst, const Mem32& src)
            {
                cmovne(dst, src);
            }
            void cmovo(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F40, 0, RW(dst), R(src));
            }
            void cmovo(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F40, 0, RW(dst), R(src));
            }
            void cmovp(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4A, 0, RW(dst), R(src));
            }
            void cmovp(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4A, 0, RW(dst), R(src));
            }
            void cmovpe(const Reg32& dst, const Reg32& src)
            {
                cmovp(dst, src);
            }
            void cmovpe(const Reg32& dst, const Mem32& src)
            {
                cmovp(dst, src);
            }
            void cmovpo(const Reg32& dst, const Reg32& src)
            {
                cmovnp(dst, src);
            }
            void cmovpo(const Reg32& dst, const Mem32& src)
            {
                cmovnp(dst, src);
            }
            void cmovs(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F48, 0, RW(dst), R(src));
            }
            void cmovs(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CMOVCC, 0x0F48, 0, RW(dst), R(src));
            }
            void cmovz(const Reg32& dst, const Reg32& src)
            {
                cmove(dst, src);
            }
            void cmovz(const Reg32& dst, const Mem32& src)
            {
                cmove(dst, src);
            }
            void cmova(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F47, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmova(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F47, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovae(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F43, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovae(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F43, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovb(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F42, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovb(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F42, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovbe(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F46, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovbe(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F46, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovc(const Reg64& dst, const Reg64& src)
            {
                cmovb(dst, src);
            }
            void cmovc(const Reg64& dst, const Mem64& src)
            {
                cmovb(dst, src);
            }
            void cmove(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F44, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmove(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F44, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovg(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4F, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovg(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4F, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovge(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4D, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovge(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4D, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovl(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4C, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovl(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4C, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovle(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4E, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovle(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4E, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovna(const Reg64& dst, const Reg64& src)
            {
                cmovbe(dst, src);
            }
            void cmovna(const Reg64& dst, const Mem64& src)
            {
                cmovbe(dst, src);
            }
            void cmovnae(const Reg64& dst, const Reg64& src)
            {
                cmovb(dst, src);
            }
            void cmovnae(const Reg64& dst, const Mem64& src)
            {
                cmovb(dst, src);
            }
            void cmovnb(const Reg64& dst, const Reg64& src)
            {
                cmovae(dst, src);
            }
            void cmovnb(const Reg64& dst, const Mem64& src)
            {
                cmovae(dst, src);
            }
            void cmovnbe(const Reg64& dst, const Reg64& src)
            {
                cmova(dst, src);
            }
            void cmovnbe(const Reg64& dst, const Mem64& src)
            {
                cmova(dst, src);
            }
            void cmovnc(const Reg64& dst, const Reg64& src)
            {
                cmovae(dst, src);
            }
            void cmovnc(const Reg64& dst, const Mem64& src)
            {
                cmovae(dst, src);
            }
            void cmovne(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F45, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovne(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F45, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovng(const Reg64& dst, const Reg64& src)
            {
                cmovle(dst, src);
            }
            void cmovng(const Reg64& dst, const Mem64& src)
            {
                cmovle(dst, src);
            }
            void cmovnge(const Reg64& dst, const Reg64& src)
            {
                cmovl(dst, src);
            }
            void cmovnge(const Reg64& dst, const Mem64& src)
            {
                cmovl(dst, src);
            }
            void cmovnl(const Reg64& dst, const Reg64& src)
            {
                cmovge(dst, src);
            }
            void cmovnl(const Reg64& dst, const Mem64& src)
            {
                cmovge(dst, src);
            }
            void cmovnle(const Reg64& dst, const Reg64& src)
            {
                cmovg(dst, src);
            }
            void cmovnle(const Reg64& dst, const Mem64& src)
            {
                cmovg(dst, src);
            }
            void cmovno(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F41, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovno(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F41, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovnp(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4B, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovnp(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4B, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovns(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F49, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovns(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F49, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovnz(const Reg64& dst, const Reg64& src)
            {
                cmovne(dst, src);
            }
            void cmovnz(const Reg64& dst, const Mem64& src)
            {
                cmovne(dst, src);
            }
            void cmovo(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F40, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovo(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F40, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovp(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4A, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovp(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F4A, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovpe(const Reg64& dst, const Reg64& src)
            {
                cmovp(dst, src);
            }
            void cmovpe(const Reg64& dst, const Mem64& src)
            {
                cmovp(dst, src);
            }
            void cmovpo(const Reg64& dst, const Reg64& src)
            {
                cmovnp(dst, src);
            }
            void cmovpo(const Reg64& dst, const Mem64& src)
            {
                cmovnp(dst, src);
            }
            void cmovs(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F48, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovs(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CMOVCC, 0x0F48, E_REXW_PREFIX, RW(dst), R(src));
            }
            void cmovz(const Reg64& dst, const Reg64& src)
            {
                cmove(dst, src);
            }
            void cmovz(const Reg64& dst, const Mem64& src)
            {
                cmove(dst, src);
            }
            void cmp(const Reg8& lhs, const Imm8& imm)
            {
                AppendInstr(I_CMP, 0x80, 0, Imm8(7), R(lhs), imm);
            }
            void cmp(const Mem8& lhs, const Imm8& imm)
            {
                AppendInstr(I_CMP, 0x80, 0, Imm8(7), R(lhs), imm);
            }
            void cmp(const Reg16& lhs, const Imm16& imm)
            {
                AppendInstr(I_CMP, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(7), R(lhs), detail::ImmXor8(imm));
            }
            void cmp(const Mem16& lhs, const Imm16& imm)
            {
                AppendInstr(I_CMP, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(7), R(lhs), detail::ImmXor8(imm));
            }
            void cmp(const Reg32& lhs, const Imm32& imm)
            {
                AppendInstr(I_CMP, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(7), R(lhs), detail::ImmXor8(imm));
            }
            void cmp(const Mem32& lhs, const Imm32& imm)
            {
                AppendInstr(I_CMP, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(7), R(lhs), detail::ImmXor8(imm));
            }
            void cmp(const Reg8& lhs, const Reg8& rhs)
            {
                AppendInstr(I_CMP, 0x38, 0, R(rhs), R(lhs));
            }
            void cmp(const Mem8& lhs, const Reg8& rhs)
            {
                AppendInstr(I_CMP, 0x38, 0, R(rhs), R(lhs));
            }
            void cmp(const Reg8& lhs, const Mem8& rhs)
            {
                AppendInstr(I_CMP, 0x3A, 0, R(lhs), R(rhs));
            }
            void cmp(const Reg16& lhs, const Reg16& rhs)
            {
                AppendInstr(I_CMP, 0x39, E_OPERAND_SIZE_PREFIX, R(rhs), R(lhs));
            }
            void cmp(const Mem16& lhs, const Reg16& rhs)
            {
                AppendInstr(I_CMP, 0x39, E_OPERAND_SIZE_PREFIX, R(rhs), R(lhs));
            }
            void cmp(const Reg16& lhs, const Mem16& rhs)
            {
                AppendInstr(I_CMP, 0x3B, E_OPERAND_SIZE_PREFIX, R(lhs), R(rhs));
            }
            void cmp(const Reg32& lhs, const Reg32& rhs)
            {
                AppendInstr(I_CMP, 0x39, 0, R(rhs), R(lhs));
            }
            void cmp(const Mem32& lhs, const Reg32& rhs)
            {
                AppendInstr(I_CMP, 0x39, 0, R(rhs), R(lhs));
            }
            void cmp(const Reg32& lhs, const Mem32& rhs)
            {
                AppendInstr(I_CMP, 0x3B, 0, R(lhs), R(rhs));
            }
            void cmp(const Reg64& lhs, const Imm32& imm)
            {
                AppendInstr(I_CMP, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(7), R(lhs), detail::ImmXor8(imm));
            }
            void cmp(const Mem64& lhs, const Imm32& imm)
            {
                AppendInstr(I_CMP, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(7), R(lhs), detail::ImmXor8(imm));
            }
            void cmp(const Reg64& lhs, const Reg64& rhs)
            {
                AppendInstr(I_CMP, 0x39, E_REXW_PREFIX, R(rhs), R(lhs));
            }
            void cmp(const Mem64& lhs, const Reg64& rhs)
            {
                AppendInstr(I_CMP, 0x39, E_REXW_PREFIX, R(rhs), R(lhs));
            }
            void cmp(const Reg64& lhs, const Mem64& rhs)
            {
                AppendInstr(I_CMP, 0x3B, E_REXW_PREFIX, R(lhs), R(rhs));
            }
            void cmpsb()
            {
                AppendInstr(I_CMPS_B, 0xA6, 0, Dummy(RW(edi)), Dummy(RW(esi)));
            }
            void cmpsw()
            {
                AppendInstr(I_CMPS_W, 0xA7, E_OPERAND_SIZE_PREFIX, Dummy(RW(edi)), Dummy(RW(esi)));
            }
            void cmpsd()
            {
                AppendInstr(I_CMPS_D, 0xA7, 0, Dummy(RW(edi)), Dummy(RW(esi)));
            }
            void cmpsq()
            {
                AppendInstr(I_CMPS_Q, 0xA7, E_REXW_PREFIX, Dummy(RW(rdi)), Dummy(RW(rsi)));
            }
            void cmpxchg(const Reg8& dst, const Reg8& src, const Reg8& cmpx)
            {
                AppendInstr(I_CMPXCHG, 0x0FB0, 0, R(src), RW(dst), Dummy(RW(cmpx), al));
            }
            void cmpxchg(const Mem8& dst, const Reg8& src, const Reg8& cmpx)
            {
                AppendInstr(I_CMPXCHG, 0x0FB0, 0, R(src), RW(dst), Dummy(RW(cmpx), al));
            }
            void cmpxchg(const Reg16& dst, const Reg16& src, const Reg16& cmpx)
            {
                AppendInstr(I_CMPXCHG, 0x0FB1, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), Dummy(RW(cmpx), ax));
            }
            void cmpxchg(const Mem16& dst, const Reg16& src, const Reg16& cmpx)
            {
                AppendInstr(I_CMPXCHG, 0x0FB1, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), Dummy(RW(cmpx), ax));
            }
            void cmpxchg(const Reg32& dst, const Reg32& src, const Reg32& cmpx)
            {
                AppendInstr(I_CMPXCHG, 0x0FB1, 0, R(src), RW(dst), Dummy(RW(cmpx), eax));
            }
            void cmpxchg(const Mem32& dst, const Reg32& src, const Reg32& cmpx)
            {
                AppendInstr(I_CMPXCHG, 0x0FB1, 0, R(src), RW(dst), Dummy(RW(cmpx), eax));
            }
            void cmpxchg(const Reg64& dst, const Reg64& src, const Reg64& cmpx)
            {
                AppendInstr(I_CMPXCHG, 0x0FB1, E_REXW_PREFIX, R(src), RW(dst), Dummy(RW(cmpx), rax));
            }
            void cmpxchg(const Mem64& dst, const Reg64& src, const Reg64& cmpx)
            {
                AppendInstr(I_CMPXCHG, 0x0FB1, E_REXW_PREFIX, R(src), RW(dst), Dummy(RW(cmpx), rax));
            }
            void cmpxchg8b(const Mem64& dst)
            {
                AppendInstr(I_CMPXCHG8B, 0x0FC7, 0, Imm8(1), RW(dst), Dummy(RW(edx)), Dummy(RW(eax)), Dummy(R(ecx)), Dummy(R(ebx)));
            }
            void cmpxchg16b(const Mem128& dst)
            {
                AppendInstr(I_CMPXCHG16B, 0x0FC7, E_REXW_PREFIX, Imm8(1), RW(dst), Dummy(RW(rdx)), Dummy(RW(rax)), Dummy(R(rcx)), Dummy(R(rbx)));
            }
            void cpuid()
            {
                AppendInstr(I_CPUID, 0x0FA2, 0, Dummy(RW(eax)), Dummy(RW(ecx)), Dummy(W(ebx)), Dummy(W(edx)));
            }
            void cwd()
            {
                AppendInstr(I_CWD, 0x99, E_OPERAND_SIZE_PREFIX, Dummy(W(dx)), Dummy(R(ax)));
            }
            void cdq()
            {
                AppendInstr(I_CDQ, 0x99, 0, Dummy(W(edx)), Dummy(R(eax)));
            }
            void cqo()
            {
                AppendInstr(I_CQO, 0x99, E_REXW_PREFIX, Dummy(W(rdx)), Dummy(R(rax)));
            }
            void dec(const Reg8& dst)
            {
                AppendInstr(I_DEC, 0xFE, 0, Imm8(1), RW(dst));
            }
            void dec(const Mem8& dst)
            {
                AppendInstr(I_DEC, 0xFE, 0, Imm8(1), RW(dst));
            }
            void dec(const Mem16& dst)
            {
                AppendInstr(I_DEC, 0xFF, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst));
            }
            void dec(const Mem32& dst)
            {
                AppendInstr(I_DEC, 0xFF, 0, Imm8(1), RW(dst));
            }
            void dec(const Reg16& dst)
            {
                AppendInstr(I_DEC, 0xFF, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst));
            }
            void dec(const Reg32& dst)
            {
                AppendInstr(I_DEC, 0xFF, 0, Imm8(1), RW(dst));
            }
            void dec(const Reg64& dst)
            {
                AppendInstr(I_DEC, 0xFF, E_REXW_PREFIX, Imm8(1), RW(dst));
            }
            void dec(const Mem64& dst)
            {
                AppendInstr(I_DEC, 0xFF, E_REXW_PREFIX, Imm8(1), RW(dst));
            }
            void div(const Reg8& src)
            {
                AppendInstr(I_DIV, 0xF6, 0, Imm8(6), R(src), Dummy(RW(ax)));
            }
            void div(const Mem8& src)
            {
                AppendInstr(I_DIV, 0xF6, 0, Imm8(6), R(src), Dummy(RW(ax)));
            }
            void div(const Reg16& src)
            {
                AppendInstr(I_DIV, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(6), R(src), Dummy(RW(ax)), Dummy(RW(dx)));
            }
            void div(const Mem16& src)
            {
                AppendInstr(I_DIV, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(6), R(src), Dummy(RW(ax)), Dummy(RW(dx)));
            }
            void div(const Reg32& src)
            {
                AppendInstr(I_DIV, 0xF7, 0, Imm8(6), R(src), Dummy(RW(eax)), Dummy(RW(edx)));
            }
            void div(const Mem32& src)
            {
                AppendInstr(I_DIV, 0xF7, 0, Imm8(6), R(src), Dummy(RW(eax)), Dummy(RW(edx)));
            }
            void div(const Reg64& src)
            {
                AppendInstr(I_DIV, 0xF7, E_REXW_PREFIX, Imm8(6), R(src), Dummy(RW(rax)), Dummy(RW(rdx)));
            }
            void div(const Mem64& src)
            {
                AppendInstr(I_DIV, 0xF7, E_REXW_PREFIX, Imm8(6), R(src), Dummy(RW(rax)), Dummy(RW(rdx)));
            }
            void enter(const Imm16& imm16, const Imm8& imm8)
            {
                AppendInstr(I_ENTER, 0xC8, 0, imm16, imm8, Dummy(RW(esp)), Dummy(RW(ebp)));
            }
            void hlt()
            {
                AppendInstr(I_HLT, 0xF4, 0);
            }
            void idiv(const Reg8& src)
            {
                AppendInstr(I_IDIV, 0xF6, 0, Imm8(7), R(src), Dummy(RW(ax)));
            }
            void idiv(const Mem8& src)
            {
                AppendInstr(I_IDIV, 0xF6, 0, Imm8(7), R(src), Dummy(RW(ax)));
            }
            void idiv(const Reg16& src)
            {
                AppendInstr(I_IDIV, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(7), R(src), Dummy(RW(ax)), Dummy(RW(dx)));
            }
            void idiv(const Mem16& src)
            {
                AppendInstr(I_IDIV, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(7), R(src), Dummy(RW(ax)), Dummy(RW(dx)));
            }
            void idiv(const Reg32& src)
            {
                AppendInstr(I_IDIV, 0xF7, 0, Imm8(7), R(src), Dummy(RW(eax)), Dummy(RW(edx)));
            }
            void idiv(const Mem32& src)
            {
                AppendInstr(I_IDIV, 0xF7, 0, Imm8(7), R(src), Dummy(RW(eax)), Dummy(RW(edx)));
            }
            void idiv(const Reg64& src)
            {
                AppendInstr(I_IDIV, 0xF7, E_REXW_PREFIX, Imm8(7), R(src), Dummy(RW(rax)), Dummy(RW(rdx)));
            }
            void idiv(const Mem64& src)
            {
                AppendInstr(I_IDIV, 0xF7, E_REXW_PREFIX, Imm8(7), R(src), Dummy(RW(rax)), Dummy(RW(rdx)));
            }
            void imul(const Reg8& src)
            {
                AppendInstr(I_IMUL, 0xF6, 0, Imm8(5), R(src), Dummy(RW(ax)));
            }
            void imul(const Mem8& src)
            {
                AppendInstr(I_IMUL, 0xF6, 0, Imm8(5), R(src), Dummy(RW(ax)));
            }
            void imul(const Reg16& src)
            {
                AppendInstr(I_IMUL, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(5), R(src), Dummy(RW(ax)), Dummy(W(dx)));
            }
            void imul(const Mem16& src)
            {
                AppendInstr(I_IMUL, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(5), R(src), Dummy(RW(ax)), Dummy(W(dx)));
            }
            void imul(const Reg32& src)
            {
                AppendInstr(I_IMUL, 0xF7, 0, Imm8(5), R(src), Dummy(RW(eax)), Dummy(W(edx)));
            }
            void imul(const Mem32& src)
            {
                AppendInstr(I_IMUL, 0xF7, 0, Imm8(5), R(src), Dummy(RW(eax)), Dummy(W(edx)));
            }
            void imul(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_IMUL, 0x0FAF, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void imul(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_IMUL, 0x0FAF, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void imul(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_IMUL, 0x0FAF, 0, RW(dst), R(src));
            }
            void imul(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_IMUL, 0x0FAF, 0, RW(dst), R(src));
            }
            void imul(const Reg16& dst, const Reg16& src, const Imm16& imm)
            {
                AppendInstr(I_IMUL, detail::IsInt8(imm.GetImm()) ? 0x6B : 0x69, E_OPERAND_SIZE_PREFIX, W(dst), R(src), detail::ImmXor8(imm));
            }
            void imul(const Reg16& dst, const Mem16& src, const Imm16& imm)
            {
                AppendInstr(I_IMUL, detail::IsInt8(imm.GetImm()) ? 0x6B : 0x69, E_OPERAND_SIZE_PREFIX, W(dst), R(src), detail::ImmXor8(imm));
            }
            void imul(const Reg32& dst, const Reg32& src, const Imm32& imm)
            {
                AppendInstr(I_IMUL, detail::IsInt8(imm.GetImm()) ? 0x6B : 0x69, 0, W(dst), R(src), detail::ImmXor8(imm));
            }
            void imul(const Reg32& dst, const Mem32& src, const Imm32& imm)
            {
                AppendInstr(I_IMUL, detail::IsInt8(imm.GetImm()) ? 0x6B : 0x69, 0, W(dst), R(src), detail::ImmXor8(imm));
            }
            void imul(const Reg16& dst, const Imm16& imm)
            {
                imul(dst, dst, imm);
            }
            void imul(const Reg32& dst, const Imm32& imm)
            {
                imul(dst, dst, imm);
            }
            void imul(const Reg64& src)
            {
                AppendInstr(I_IMUL, 0xF7, E_REXW_PREFIX, Imm8(5), R(src), Dummy(RW(rax)), Dummy(W(rdx)));
            }
            void imul(const Mem64& src)
            {
                AppendInstr(I_IMUL, 0xF7, E_REXW_PREFIX, Imm8(5), R(src), Dummy(RW(rax)), Dummy(W(rdx)));
            }
            void imul(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_IMUL, 0x0FAF, E_REXW_PREFIX, RW(dst), R(src));
            }
            void imul(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_IMUL, 0x0FAF, E_REXW_PREFIX, RW(dst), R(src));
            }
            void imul(const Reg64& dst, const Reg64& src, const Imm32& imm)
            {
                AppendInstr(I_IMUL, detail::IsInt8(imm.GetImm()) ? 0x6B : 0x69, E_REXW_PREFIX, W(dst), R(src), detail::ImmXor8(imm));
            }
            void imul(const Reg64& dst, const Mem64& src, const Imm32& imm)
            {
                AppendInstr(I_IMUL, detail::IsInt8(imm.GetImm()) ? 0x6B : 0x69, E_REXW_PREFIX, W(dst), R(src), detail::ImmXor8(imm));
            }
            void imul(const Reg64& dst, const Imm32& imm)
            {
                imul(dst, dst, imm);
            }
            void in(const Reg8& dst, const Imm8& src)
            {
                AppendInstr(I_IN, 0xE4, 0, src, Dummy(W(dst), al));
            }
            void in(const Reg16& dst, const Imm8& src)
            {
                AppendInstr(I_IN, 0xE5, E_OPERAND_SIZE_PREFIX, src, Dummy(W(dst), ax));
            }
            void in(const Reg32& dst, const Imm8& src)
            {
                AppendInstr(I_IN, 0xE5, 0, src, Dummy(W(dst), eax));
            }
            void in(const Reg8& dst, const Reg16& src)
            {
                AppendInstr(I_IN, 0xEC, 0, Dummy(R(src), dx), Dummy(W(dst), al));
            }
            void in(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_IN, 0xED, E_OPERAND_SIZE_PREFIX, Dummy(R(src), dx), Dummy(W(dst), ax));
            }
            void in(const Reg32& dst, const Reg16& src)
            {
                AppendInstr(I_IN, 0xED, 0, Dummy(R(src), dx), Dummy(W(dst), eax));
            }
            void inc(const Reg8& dst)
            {
                AppendInstr(I_INC, 0xFE, 0, Imm8(0), RW(dst));
            }
            void inc(const Mem8& dst)
            {
                AppendInstr(I_INC, 0xFE, 0, Imm8(0), RW(dst));
            }
            void inc(const Mem16& dst)
            {
                AppendInstr(I_INC, 0xFF, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst));
            }
            void inc(const Mem32& dst)
            {
                AppendInstr(I_INC, 0xFF, 0, Imm8(0), RW(dst));
            }
            void inc(const Reg16& dst)
            {
                AppendInstr(I_INC, 0xFF, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst));
            }
            void inc(const Reg32& dst)
            {
                AppendInstr(I_INC, 0xFF, 0, Imm8(0), RW(dst));
            }
            void inc(const Reg64& dst)
            {
                AppendInstr(I_INC, 0xFF, E_REXW_PREFIX, Imm8(0), RW(dst));
            }
            void inc(const Mem64& dst)
            {
                AppendInstr(I_INC, 0xFF, E_REXW_PREFIX, Imm8(0), RW(dst));
            }
            void insb(const Reg& dst, const Reg16& src)
            {
                AppendInstr(I_INS_B, 0x6C, 0, Dummy(R(src), dx), Dummy(RW(dst), edi));
            }
            void insw(const Reg& dst, const Reg16& src)
            {
                AppendInstr(I_INS_W, 0x6D, E_OPERAND_SIZE_PREFIX, Dummy(R(src), dx), Dummy(RW(dst), edi));
            }
            void insd(const Reg& dst, const Reg16& src)
            {
                AppendInstr(I_INS_D, 0x6D, 0, Dummy(R(src), dx), Dummy(RW(dst), edi));
            }
            void rep_insb(const Reg& dst, const Reg16& src, const Reg& count)
            {
                AppendInstr(I_INS_B, 0x6C, E_REP_PREFIX, Dummy(R(src), dx), Dummy(RW(dst), edi), Dummy(RW(count), ecx));
            }
            void rep_insw(const Reg& dst, const Reg16& src, const Reg& count)
            {
                AppendInstr(I_INS_W, 0x6D, E_REP_PREFIX | E_OPERAND_SIZE_PREFIX, Dummy(R(src), dx), Dummy(RW(dst), edi), Dummy(RW(count), ecx));
            }
            void rep_insd(const Reg& dst, const Reg16& src, const Reg& count)
            {
                AppendInstr(I_INS_D, 0x6D, E_REP_PREFIX, Dummy(R(src), dx), Dummy(RW(dst), edi), Dummy(RW(count), ecx));
            }
            void int3()
            {
                AppendInstr(I_INT3, 0xCC, 0);
            }
            void intn(const Imm8& n)
            {
                AppendInstr(I_INTN, 0xCD, 0, n);
            }
            void invd()
            {
                AppendInstr(I_INVD, 0x0F08, 0);
            }
            template<class Ty> void invlpg(const MemT<Ty>& dst)
            {
                AppendInstr(I_INVLPG, 0x0F01, 0, Imm8(7), R(dst));
            }
            void iret()
            {
                AppendInstr(I_IRET, 0xCF, E_OPERAND_SIZE_PREFIX);
            }
            void iretd()
            {
                AppendInstr(I_IRETD, 0xCF, 0);
            }
            void iretq()
            {
                AppendInstr(I_IRETQ, 0xCF, E_REXW_PREFIX);
            }
            void jmp(u32 label_name)
            {
                AppendJmp(GetLabelID(label_name));
            }
            void jmp(u32 label_target, bool special)
            {
                AppendJmp(GetLabelID(label_target), true);
            }
            void jcc(JumpCondition cc, u32 label_name)
            {
                AppendJcc(cc, GetLabelID(label_name));
                AppendInstr(I_JMP, 0, 0, Imm8(0));
            }
            void ja(u32 label_name)
            {
                AppendJcc(JCC_A, GetLabelID(label_name));
            }
            void jae(u32 label_name)
            {
                AppendJcc(JCC_AE, GetLabelID(label_name));
            }
            void jb(u32 label_name)
            {
                AppendJcc(JCC_B, GetLabelID(label_name));
            }
            void jbe(u32 label_name)
            {
                AppendJcc(JCC_BE, GetLabelID(label_name));
            }
            void jc(u32 label_name)
            {
                jb(label_name);
            }
            void jecxz(u32 label_name)
            {
                AppendJcc(JCC_ECXZ, GetLabelID(label_name));
            }   // short jump only
            void jrcxz(u32 label_name)
            {
                AppendJcc(JCC_RCXZ, GetLabelID(label_name));
            }   // short jump only
            void je(u32 label_name)
            {
                AppendJcc(JCC_E, GetLabelID(label_name));
            }
            void jg(u32 label_name)
            {
                AppendJcc(JCC_G, GetLabelID(label_name));
            }
            void jge(u32 label_name)
            {
                AppendJcc(JCC_GE, GetLabelID(label_name));
            }
            void jl(u32 label_name)
            {
                AppendJcc(JCC_L, GetLabelID(label_name));
            }
            void jle(u32 label_name)
            {
                AppendJcc(JCC_LE, GetLabelID(label_name));
            }
            void jna(u32 label_name)
            {
                jbe(label_name);
            }
            void jnae(u32 label_name)
            {
                jb(label_name);
            }
            void jnb(u32 label_name)
            {
                jae(label_name);
            }
            void jnbe(u32 label_name)
            {
                ja(label_name);
            }
            void jnc(u32 label_name)
            {
                jae(label_name);
            }
            void jne(u32 label_name)
            {
                AppendJcc(JCC_NE, GetLabelID(label_name));
            }
            void jng(u32 label_name)
            {
                jle(label_name);
            }
            void jnge(u32 label_name)
            {
                jl(label_name);
            }
            void jnl(u32 label_name)
            {
                jge(label_name);
            }
            void jnle(u32 label_name)
            {
                jg(label_name);
            }
            void jno(u32 label_name)
            {
                AppendJcc(JCC_NO, GetLabelID(label_name));
            }
            void jnp(u32 label_name)
            {
                AppendJcc(JCC_NP, GetLabelID(label_name));
            }
            void jns(u32 label_name)
            {
                AppendJcc(JCC_NS, GetLabelID(label_name));
            }
            void jnz(u32 label_name)
            {
                jne(label_name);
            }
            void jo(u32 label_name)
            {
                AppendJcc(JCC_O, GetLabelID(label_name));
            }
            void jp(u32 label_name)
            {
                AppendJcc(JCC_P, GetLabelID(label_name));
            }
            void jpe(u32 label_name)
            {
                jp(label_name);
            }
            void jpo(u32 label_name)
            {
                jnp(label_name);
            }
            void js(u32 label_name)
            {
                AppendJcc(JCC_S, GetLabelID(label_name));
            }
            void jz(u32 label_name)
            {
                je(label_name);
            }
            void lar(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_LAR, 0x0F02, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void lar(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_LAR, 0x0F02, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void lar(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_LAR, 0x0F02, 0, W(dst), R(src));
            }
            void lar(const Reg32& dst, const Mem16& src)
            {
                AppendInstr(I_LAR, 0x0F02, 0, W(dst), R(src));
            }
            void lar(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_LAR, 0x0F02, E_REXW_PREFIX, W(dst), R(src));
            }
            void lar(const Reg64& dst, const Mem16& src)
            {
                AppendInstr(I_LAR, 0x0F02, E_REXW_PREFIX, W(dst), R(src));
            }
            template<class Ty> void lea(const Reg16& dst, const MemT<Ty>& src)
            {
                AppendInstr(I_LEA, 0x8D, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            template<class Ty> void lea(const Reg32& dst, const MemT<Ty>& src)
            {
                AppendInstr(I_LEA, 0x8D, 0, W(dst), R(src));
            }
            template<class Ty> void lea(const Reg64& dst, const MemT<Ty>& src)
            {
                AppendInstr(I_LEA, 0x8D, E_REXW_PREFIX, W(dst), R(src));
            }
            void leave()
            {
                AppendInstr(I_LEAVE, 0xC9, 0, Dummy(W(esp)), Dummy(RW(ebp)));
            }
            //lgdt
            //lidt
            void lldt(const Reg16& src)
            {
                AppendInstr(I_LLDT, 0x0F00, 0, Imm8(2), R(src));
            }
            void lldt(const Mem16& src)
            {
                AppendInstr(I_LLDT, 0x0F00, 0, Imm8(2), R(src));
            }
            void lmsw(const Reg16& src)
            {
                AppendInstr(I_LMSW, 0x0F01, 0, Imm8(6), R(src));
            }
            void lmsw(const Mem16& src)
            {
                AppendInstr(I_LMSW, 0x0F01, 0, Imm8(6), R(src));
            }
            void lodsb(const Reg8& dst, const Reg& src)
            {
                AppendInstr(I_LODS_B, 0xAC, 0, Dummy(W(dst), al), Dummy(RW(src), zsi));
            }
            void lodsw(const Reg16& dst, const Reg& src)
            {
                AppendInstr(I_LODS_W, 0xAD, E_OPERAND_SIZE_PREFIX, Dummy(W(dst), ax), Dummy(RW(src), zsi));
            }
            void lodsd(const Reg32& dst, const Reg& src)
            {
                AppendInstr(I_LODS_D, 0xAD, 0, Dummy(W(dst), eax), Dummy(RW(src), zsi));
            }
            void lodsq(const Reg64& dst, const Reg& src)
            {
                AppendInstr(I_LODS_Q, 0xAD, E_REXW_PREFIX, Dummy(W(dst), rax), Dummy(RW(src), rsi));
            }
            void rep_lodsb(const Reg8& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_LODS_B, 0xAC, E_REP_PREFIX, Dummy(RW(dst), al), Dummy(RW(src), zsi), Dummy(RW(count), zcx));
            }                           // dst is RW because of ecx == 0
            void rep_lodsw(const Reg16& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_LODS_W, 0xAD, E_REP_PREFIX | E_OPERAND_SIZE_PREFIX, Dummy(RW(dst), ax), Dummy(RW(src), zsi), Dummy(RW(count), zcx));
            }   // dst is RW because of ecx == 0
            void rep_lodsd(const Reg32& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_LODS_D, 0xAD, E_REP_PREFIX, Dummy(RW(dst), eax), Dummy(RW(src), zsi), Dummy(RW(count), zcx));
            }                           // dst is RW because of ecx == 0
            void rep_lodsq(const Reg64& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_LODS_Q, 0xAD, E_REP_PREFIX | E_REXW_PREFIX, Dummy(RW(dst), rax), Dummy(RW(src), rsi), Dummy(RW(count), rcx));
            }           // dst is RW because of ecx == 0
            void loop(u32 label_name)
            {
                AppendInstr(I_LOOP, 0xE2, 0, Imm64(GetLabelID(label_name)), Dummy(RW(zcx)));
            }   // short jump only
            void loope(u32 label_name)
            {
                AppendInstr(I_LOOP, 0xE1, 0, Imm64(GetLabelID(label_name)), Dummy(RW(zcx)));
            }   // short jump only
            void loopne(u32 label_name)
            {
                AppendInstr(I_LOOP, 0xE0, 0, Imm64(GetLabelID(label_name)), Dummy(RW(zcx)));
            }   // short jump only
            void lsl(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_LSL, 0x0F03, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void lsl(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_LSL, 0x0F03, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void lsl(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_LSL, 0x0F03, 0, RW(dst), R(src));
            }
            void lsl(const Reg32& dst, const Mem16& src)
            {
                AppendInstr(I_LSL, 0x0F03, 0, RW(dst), R(src));
            }
            void lsl(const Reg64& dst, const Reg32& src)
            {
                AppendInstr(I_LSL, 0x0F03, E_REXW_PREFIX, RW(dst), R(src));
            }
            void lsl(const Reg64& dst, const Mem16& src)
            {
                AppendInstr(I_LSL, 0x0F03, E_REXW_PREFIX, RW(dst), R(src));
            }
            void ltr(const Reg16& src)
            {
                AppendInstr(I_LTR, 0x0F00, 0, Imm8(3), R(src));
            }
            void ltr(const Mem16& src)
            {
                AppendInstr(I_LTR, 0x0F00, 0, Imm8(3), R(src));
            }
            void mov(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_MOV, 0x8A, 0, W(dst), R(src));
            }
            void mov(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_MOV, 0x88, 0, R(src), W(dst));
            }
            void mov(const Mem8& dst, const Gpr& src) // special case for Allegrex
            {
                AppendInstr(I_MOV, 0x88, 0, R(src), W(dst));
            }
            void mov(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_MOV, 0x8B, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void mov(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_MOV, 0x89, E_OPERAND_SIZE_PREFIX, R(src), W(dst));
            }
            void mov(const Mem16& dst, const Gpr& src) // special case for Allegrex
            {
                AppendInstr(I_MOV, 0x89, E_OPERAND_SIZE_PREFIX, R(src), W(dst));
            }
            void mov(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_MOV, 0x8B, 0, W(dst), R(src));
            }
            void mov(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_MOV, 0x89, 0, R(src), W(dst));
            }
            void mov(const Reg8& dst, const Mem8& src)
            {
                AppendInstr(I_MOV, 0x8A, 0, W(dst), R(src));
            }
            void mov(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_MOV, 0x8B, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void mov(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_MOV, 0x8B, 0, W(dst), R(src));
            }
            void mov(const Reg8& dst, const Imm8& imm)
            {
                AppendInstr(I_MOV, 0xB0, 0, W(dst), imm);
            }
            void mov(const Reg16& dst, const Imm16& imm)
            {
                AppendInstr(I_MOV, 0xB8, E_OPERAND_SIZE_PREFIX, W(dst), imm);
            }
            void mov(const Reg32& dst, const Imm32& imm)
            {
                AppendInstr(I_MOV, 0xB8, 0, W(dst), imm);
            }
            void mov(const Mem8& dst, const Imm8& imm)
            {
                AppendInstr(I_MOV, 0xC6, 0, Imm8(0), W(dst), imm);
            }
            void mov(const Mem16& dst, const Imm16& imm)
            {
                AppendInstr(I_MOV, 0xC7, E_OPERAND_SIZE_PREFIX, Imm8(0), W(dst), imm);
            }
            void mov(const Mem32& dst, const Imm32& imm)
            {
                AppendInstr(I_MOV, 0xC7, 0, Imm8(0), W(dst), imm);
            }
            void mov(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_MOV, 0x8B, E_REXW_PREFIX, W(dst), R(src));
            }
            void mov(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_MOV, 0x89, E_REXW_PREFIX, R(src), W(dst));
            }
            void mov(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_MOV, 0x8B, E_REXW_PREFIX, W(dst), R(src));
            }
            void mov(const Reg64& dst, const Imm64& imm)
            {
                detail::IsInt32(imm.GetImm()) ? AppendInstr(I_MOV, 0xC7, E_REXW_PREFIX, Imm8(0), W(dst), Imm32((sint32)imm.GetImm())) : AppendInstr(I_MOV, 0xB8, E_REXW_PREFIX, W(dst), imm);
            }
            void mov(const Mem64& dst, const Imm32& imm)
            {
                AppendInstr(I_MOV, 0xC7, E_REXW_PREFIX, Imm8(0), W(dst), imm);
            }
            void mov(const Reg64& dst, const MemOffset64& src)
            {
                AppendInstr(I_MOV, 0xA1, E_REXW_PREFIX, Imm64(src.GetOffset()), Dummy(W(dst), rax));
            }
            void mov(const MemOffset64& dst, const Reg64& src)
            {
                AppendInstr(I_MOV, 0xA3, E_REXW_PREFIX, Imm64(dst.GetOffset()), Dummy(R(src), rax));
            }
            void movbe(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_MOVBE, 0x0F38F0, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void movbe(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_MOVBE, 0x0F38F0, 0, W(dst), R(src));
            }
            void movbe(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_MOVBE, 0x0F38F1, E_OPERAND_SIZE_PREFIX, R(src), W(dst));
            }
            void movbe(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_MOVBE, 0x0F38F1, 0, R(src), W(dst));
            }
            void movbe(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_MOVBE, 0x0F38F0, E_REXW_PREFIX, W(dst), R(src));
            }
            void movbe(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_MOVBE, 0x0F38F1, E_REXW_PREFIX, R(src), W(dst));
            }
            void movsb(const Reg& dst, const Reg& src)
            {
                AppendInstr(I_MOVS_B, 0xA4, 0, Dummy(RW(dst), zdi), Dummy(RW(src), zsi));
            }
            void movsw(const Reg& dst, const Reg& src)
            {
                AppendInstr(I_MOVS_W, 0xA5, E_OPERAND_SIZE_PREFIX, Dummy(RW(dst), zdi), Dummy(RW(src), zsi));
            }
            void movsd(const Reg& dst, const Reg& src)
            {
                AppendInstr(I_MOVS_D, 0xA5, 0, Dummy(RW(dst), zdi), Dummy(RW(src), zsi));
            }
            void movsq(const Reg& dst, const Reg& src)
            {
                AppendInstr(I_MOVS_Q, 0xA5, E_REXW_PREFIX, Dummy(RW(dst), rdi), Dummy(RW(src), rsi));
            }
            void rep_movsb()
            {
                rep_movsb(zdi, zsi, zcx);
            }
            void rep_movsw()
            {
                rep_movsw(zdi, zsi, zcx);
            }
            void rep_movsd()
            {
                rep_movsd(zdi, zsi, zcx);
            }
            void rep_movsb(const Reg& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_MOVS_B, 0xA4, E_REP_PREFIX, Dummy(RW(dst), zdi), Dummy(RW(src), zsi), Dummy(RW(count), ecx));
            }
            void rep_movsw(const Reg& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_MOVS_W, 0xA5, E_REP_PREFIX | E_OPERAND_SIZE_PREFIX, Dummy(RW(dst), zdi), Dummy(RW(src), zsi), Dummy(RW(count), ecx));
            }
            void rep_movsd(const Reg& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_MOVS_D, 0xA5, E_REP_PREFIX, Dummy(RW(dst), zdi), Dummy(RW(src), zsi), Dummy(RW(count), ecx));
            }
            void rep_movsq()
            {
                rep_movsq(rdi, rsi, rcx);
            }
            void rep_movsq(const Reg64& dst, const Reg64& src, const Reg64& count)
            {
                AppendInstr(I_MOVS_Q, 0xA5, E_REP_PREFIX | E_REXW_PREFIX, Dummy(RW(dst), rdi), Dummy(RW(src), rsi), Dummy(RW(count), rcx));
            }
            void movsx(const Reg16& dst, const Reg8& src)
            {
                AppendInstr(I_MOVSX, 0x0FBE, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void movsx(const Reg16& dst, const Mem8& src)
            {
                AppendInstr(I_MOVSX, 0x0FBE, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void movsx(const Reg32& dst, const Reg8& src)
            {
                AppendInstr(I_MOVSX, 0x0FBE, 0, W(dst), R(src));
            }
            void movsx(const Reg32& dst, const Mem8& src)
            {
                AppendInstr(I_MOVSX, 0x0FBE, 0, W(dst), R(src));
            }
            void movsx(const Reg32& dst, const Reg16& src)
            {
                AppendInstr(I_MOVSX, 0x0FBF, 0, W(dst), R(src));
            }
            void movsx(const Reg32& dst, const Mem16& src)
            {
                AppendInstr(I_MOVSX, 0x0FBF, 0, W(dst), R(src));
            }
            void movsx(const Reg64& dst, const Reg8& src)
            {
                AppendInstr(I_MOVSX, 0x0FBE, E_REXW_PREFIX, W(dst), R(src));
            }
            void movsx(const Reg64& dst, const Mem8& src)
            {
                AppendInstr(I_MOVSX, 0x0FBE, E_REXW_PREFIX, W(dst), R(src));
            }
            void movsx(const Reg64& dst, const Reg16& src)
            {
                AppendInstr(I_MOVSX, 0x0FBF, E_REXW_PREFIX, W(dst), R(src));
            }
            void movsx(const Reg64& dst, const Mem16& src)
            {
                AppendInstr(I_MOVSX, 0x0FBF, E_REXW_PREFIX, W(dst), R(src));
            }
            void movsxd(const Reg64& dst, const Reg32& src)
            {
                AppendInstr(I_MOVSXD, 0x63, E_REXW_PREFIX, W(dst), R(src));
            }
            void movsxd(const Reg64& dst, const Mem32& src)
            {
                AppendInstr(I_MOVSXD, 0x63, E_REXW_PREFIX, W(dst), R(src));
            }
            void movzx(const Reg16& dst, const Reg8& src)
            {
                AppendInstr(I_MOVZX, 0x0FB6, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void movzx(const Reg16& dst, const Mem8& src)
            {
                AppendInstr(I_MOVZX, 0x0FB6, E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void movzx(const Reg32& dst, const Reg8& src)
            {
                AppendInstr(I_MOVZX, 0x0FB6, 0, W(dst), R(src));
            }
            void movzx(const Reg32& dst, const Mem8& src)
            {
                AppendInstr(I_MOVZX, 0x0FB6, 0, W(dst), R(src));
            }
            void movzx(const Reg32& dst, const Reg16& src)
            {
                AppendInstr(I_MOVZX, 0x0FB7, 0, W(dst), R(src));
            }
            void movzx(const Reg32& dst, const Mem16& src)
            {
                AppendInstr(I_MOVZX, 0x0FB7, 0, W(dst), R(src));
            }
            void movzx(const Reg64& dst, const Reg8& src)
            {
                AppendInstr(I_MOVZX, 0x0FB6, E_REXW_PREFIX, W(dst), R(src));
            }
            void movzx(const Reg64& dst, const Mem8& src)
            {
                AppendInstr(I_MOVZX, 0x0FB6, E_REXW_PREFIX, W(dst), R(src));
            }
            void movzx(const Reg64& dst, const Reg16& src)
            {
                AppendInstr(I_MOVZX, 0x0FB7, E_REXW_PREFIX, W(dst), R(src));
            }
            void movzx(const Reg64& dst, const Mem16& src)
            {
                AppendInstr(I_MOVZX, 0x0FB7, E_REXW_PREFIX, W(dst), R(src));
            }
            void mul(const Reg8& src)
            {
                AppendInstr(I_MUL, 0xF6, 0, Imm8(4), R(src), Dummy(RW(ax)));
            }
            void mul(const Mem8& src)
            {
                AppendInstr(I_MUL, 0xF6, 0, Imm8(4), R(src), Dummy(RW(ax)));
            }
            void mul(const Reg16& src)
            {
                AppendInstr(I_MUL, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(4), R(src), Dummy(RW(ax)), Dummy(W(dx)));
            }
            void mul(const Mem16& src)
            {
                AppendInstr(I_MUL, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(4), R(src), Dummy(RW(ax)), Dummy(W(dx)));
            }
            void mul(const Reg32& src)
            {
                AppendInstr(I_MUL, 0xF7, 0, Imm8(4), R(src), Dummy(RW(eax)), Dummy(W(edx)));
            }
            void mul(const Mem32& src)
            {
                AppendInstr(I_MUL, 0xF7, 0, Imm8(4), R(src), Dummy(RW(eax)), Dummy(W(edx)));
            }
            void mul(const Reg64& src)
            {
                AppendInstr(I_MUL, 0xF7, E_REXW_PREFIX, Imm8(4), R(src), Dummy(RW(rax)), Dummy(W(rdx)));
            }
            void mul(const Mem64& src)
            {
                AppendInstr(I_MUL, 0xF7, E_REXW_PREFIX, Imm8(4), R(src), Dummy(RW(rax)), Dummy(W(rdx)));
            }
            void neg(const Reg8& dst)
            {
                AppendInstr(I_NEG, 0xF6, 0, Imm8(3), RW(dst));
            }
            void neg(const Mem8& dst)
            {
                AppendInstr(I_NEG, 0xF6, 0, Imm8(3), RW(dst));
            }
            void neg(const Reg16& dst)
            {
                AppendInstr(I_NEG, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst));
            }
            void neg(const Mem16& dst)
            {
                AppendInstr(I_NEG, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst));
            }
            void neg(const Reg32& dst)
            {
                AppendInstr(I_NEG, 0xF7, 0, Imm8(3), RW(dst));
            }
            void neg(const Mem32& dst)
            {
                AppendInstr(I_NEG, 0xF7, 0, Imm8(3), RW(dst));
            }
            void neg(const Reg64& dst)
            {
                AppendInstr(I_NEG, 0xF7, E_REXW_PREFIX, Imm8(3), RW(dst));
            }
            void neg(const Mem64& dst)
            {
                AppendInstr(I_NEG, 0xF7, E_REXW_PREFIX, Imm8(3), RW(dst));
            }
            void nop()
            {
                AppendInstr(I_NOP, 0x90, 0);
            }
            void not(const Reg8& dst)
            {
                AppendInstr(I_NOT, 0xF6, 0, Imm8(2), RW(dst));
            }
            void not(const Mem8& dst)
            {
                AppendInstr(I_NOT, 0xF6, 0, Imm8(2), RW(dst));
            }
            void not(const Reg16& dst)
            {
                AppendInstr(I_NOT, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst));
            }
            void not(const Mem16& dst)
            {
                AppendInstr(I_NOT, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst));
            }
            void not(const Reg32& dst)
            {
                AppendInstr(I_NOT, 0xF7, 0, Imm8(2), RW(dst));
            }
            void not(const Mem32& dst)
            {
                AppendInstr(I_NOT, 0xF7, 0, Imm8(2), RW(dst));
            }
            void not(const Reg64& dst)
            {
                AppendInstr(I_NOT, 0xF7, E_REXW_PREFIX, Imm8(2), RW(dst));
            }
            void not(const Mem64& dst)
            {
                AppendInstr(I_NOT, 0xF7, E_REXW_PREFIX, Imm8(2), RW(dst));
            }
            void or(const Reg8& dst, const Imm8& imm)
            {
                AppendInstr(I_OR, 0x80, 0, Imm8(1), RW(dst), imm);
            }
            void or(const Mem8& dst, const Imm8& imm)
            {
                AppendInstr(I_OR, 0x80, 0, Imm8(1), RW(dst), imm);
            }
            void or(const Reg16& dst, const Imm16& imm)
            {
                AppendInstr(I_OR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst), detail::ImmXor8(imm));
            }
            void or(const Mem16& dst, const Imm16& imm)
            {
                AppendInstr(I_OR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst), detail::ImmXor8(imm));
            }
            void or(const Reg32& dst, const Imm32& imm)
            {
                AppendInstr(I_OR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(1), RW(dst), detail::ImmXor8(imm));
            }
            void or(const Mem32& dst, const Imm32& imm)
            {
                AppendInstr(I_OR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(1), RW(dst), detail::ImmXor8(imm));
            }
            void or(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_OR, 0x08, 0, R(src), RW(dst));
            }
            void or(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_OR, 0x08, 0, R(src), RW(dst));
            }
            void or(const Reg8& dst, const Mem8& src)
            {
                AppendInstr(I_OR, 0x0A, 0, RW(dst), R(src));
            }
            void or(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_OR, 0x09, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void or(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_OR, 0x09, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void or(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_OR, 0x0B, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void or(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_OR, 0x09, 0, R(src), RW(dst));
            }
            void or(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_OR, 0x09, 0, R(src), RW(dst));
            }
            void or(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_OR, 0x0B, 0, RW(dst), R(src));
            }
            void or(const Reg64& dst, const Imm32& imm)
            {
                AppendInstr(I_OR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(1), RW(dst), detail::ImmXor8(imm));
            }
            void or(const Mem64& dst, const Imm32& imm)
            {
                AppendInstr(I_OR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(1), RW(dst), detail::ImmXor8(imm));
            }
            void or(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_OR, 0x09, E_REXW_PREFIX, R(src), RW(dst));
            }
            void or(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_OR, 0x09, E_REXW_PREFIX, R(src), RW(dst));
            }
            void or(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_OR, 0x0B, E_REXW_PREFIX, RW(dst), R(src));
            }
            void out(const Imm8& dst, const Reg8& src)
            {
                AppendInstr(I_OUT, 0xE6, 0, dst, Dummy(R(src), al));
            }
            void out(const Imm8& dst, const Reg16& src)
            {
                AppendInstr(I_OUT, 0xE7, E_OPERAND_SIZE_PREFIX, dst, Dummy(R(src), ax));
            }
            void out(const Imm8& dst, const Reg32& src)
            {
                AppendInstr(I_OUT, 0xE7, 0, dst, Dummy(R(src), eax));
            }
            void out(const Reg16& dst, const Reg8& src)
            {
                AppendInstr(I_OUT, 0xEE, 0, Dummy(R(dst), dx), Dummy(R(src), al));
            }
            void out(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_OUT, 0xEF, E_OPERAND_SIZE_PREFIX, Dummy(R(dst), dx), Dummy(R(src), ax));
            }
            void out(const Reg16& dst, const Reg32& src)
            {
                AppendInstr(I_OUT, 0xEF, 0, Dummy(R(dst), dx), Dummy(R(src), eax));
            }
            void outsb(const Reg16& dst, const Reg& src)
            {
                AppendInstr(I_OUTS_B, 0x6E, 0, Dummy(RW(src), esi), Dummy(R(dst), dx));
            }
            void outsw(const Reg16& dst, const Reg& src)
            {
                AppendInstr(I_OUTS_W, 0x6F, E_OPERAND_SIZE_PREFIX, Dummy(RW(src), esi), Dummy(R(dst), dx));
            }
            void outsd(const Reg16& dst, const Reg& src)
            {
                AppendInstr(I_OUTS_D, 0x6F, 0, Dummy(RW(src), esi), Dummy(R(dst), dx));
            }
            void rep_outsb(const Reg16& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_OUTS_B, 0x6E, E_REP_PREFIX, Dummy(RW(src), esi), Dummy(R(dst), dx), Dummy(RW(count), ecx));
            }
            void rep_outsw(const Reg16& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_OUTS_W, 0x6F, E_REP_PREFIX | E_OPERAND_SIZE_PREFIX, Dummy(RW(src), esi), Dummy(R(dst), dx), Dummy(RW(count), ecx));
            }
            void rep_outsd(const Reg16& dst, const Reg& src, const Reg& count)
            {
                AppendInstr(I_OUTS_D, 0x6F, E_REP_PREFIX, Dummy(RW(src), esi), Dummy(R(dst), dx), Dummy(RW(count), ecx));
            }
            void pop(const Reg16& dst)
            {
                AppendInstr(I_POP, 0x58, E_OPERAND_SIZE_PREFIX, W(dst));
            }
            void pop(const Mem16& dst)
            {
                AppendInstr(I_POP, 0x8F, E_OPERAND_SIZE_PREFIX, Imm8(0), W(dst));
            }
            void pop(const Reg64& dst)
            {
                AppendInstr(I_POP, 0x58, 0, W(dst), Dummy(RW(esp)));
            }
            void pop(const Mem64& dst)
            {
                AppendInstr(I_POP, 0x8F, 0, Imm8(0), W(dst), Dummy(RW(esp)));
            }
            void popf()
            {
                AppendInstr(I_POPF, 0x9D, E_OPERAND_SIZE_PREFIX, Dummy(RW(esp)));
            }
            void popfq()
            {
                AppendInstr(I_POPFQ, 0x9D, 0, Dummy(RW(esp)));
            }
            void push(const Reg16& src)
            {
                AppendInstr(I_PUSH, 0x50, E_OPERAND_SIZE_PREFIX, R(src), Dummy(RW(esp)));
            }
            void push(const Mem16& src)
            {
                AppendInstr(I_PUSH, 0xFF, E_OPERAND_SIZE_PREFIX, Imm8(6), R(src), Dummy(RW(esp)));
            }
            void push(const Reg64& src)
            {
                AppendInstr(I_PUSH, 0x50, 0, R(src), Dummy(RW(esp)));
            }
            void push(const Mem64& src)
            {
                AppendInstr(I_PUSH, 0xFF, 0, Imm8(6), R(src), Dummy(RW(esp)));
            }
            void push(const Imm32& imm)
            {
                AppendInstr(I_PUSH, detail::IsInt8(imm.GetImm()) ? 0x6A : 0x68, 0, detail::ImmXor8(imm), Dummy(RW(esp)));
            }
            void pushf()
            {
                AppendInstr(I_PUSHF, 0x9C, E_OPERAND_SIZE_PREFIX, Dummy(RW(esp)));
            }
            void pushfq()
            {
                AppendInstr(I_PUSHFQ, 0x9C, 0, Dummy(RW(esp)));
            }
            void rcl(const Reg8& dst, const Reg8& shift)
            {
                AppendInstr(I_RCL, 0xD2, 0, Imm8(2), RW(dst), Dummy(R(shift), cl));
            }
            void rcl(const Mem8& dst, const Reg8& shift)
            {
                AppendInstr(I_RCL, 0xD2, 0, Imm8(2), RW(dst), Dummy(R(shift), cl));
            }
            void rcl(const Reg8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCL, 0xD0, 0, Imm8(2), RW(dst)) : AppendInstr(I_RCL, 0xC0, 0, Imm8(2), RW(dst), shift);
            }
            void rcl(const Mem8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCL, 0xD0, 0, Imm8(2), RW(dst)) : AppendInstr(I_RCL, 0xC0, 0, Imm8(2), RW(dst), shift);
            }
            void rcr(const Reg8& dst, const Reg8& shift)
            {
                AppendInstr(I_RCR, 0xD2, 0, Imm8(3), RW(dst), Dummy(R(shift), cl));
            }
            void rcr(const Mem8& dst, const Reg8& shift)
            {
                AppendInstr(I_RCR, 0xD2, 0, Imm8(3), RW(dst), Dummy(R(shift), cl));
            }
            void rcr(const Reg8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCR, 0xD0, 0, Imm8(3), RW(dst)) : AppendInstr(I_RCR, 0xC0, 0, Imm8(3), RW(dst), shift);
            }
            void rcr(const Mem8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCR, 0xD0, 0, Imm8(3), RW(dst)) : AppendInstr(I_RCR, 0xC0, 0, Imm8(3), RW(dst), shift);
            }
            void rol(const Reg8& dst, const Reg8& shift)
            {
                AppendInstr(I_ROL, 0xD2, 0, Imm8(0), RW(dst), Dummy(R(shift), cl));
            }
            void rol(const Mem8& dst, const Reg8& shift)
            {
                AppendInstr(I_ROL, 0xD2, 0, Imm8(0), RW(dst), Dummy(R(shift), cl));
            }
            void rol(const Reg8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROL, 0xD0, 0, Imm8(0), RW(dst)) : AppendInstr(I_ROL, 0xC0, 0, Imm8(0), RW(dst), shift);
            }
            void rol(const Mem8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROL, 0xD0, 0, Imm8(0), RW(dst)) : AppendInstr(I_ROL, 0xC0, 0, Imm8(0), RW(dst), shift);
            }
            void ror(const Reg8& dst, const Reg8& shift)
            {
                AppendInstr(I_ROR, 0xD2, 0, Imm8(1), RW(dst), Dummy(R(shift), cl));
            }
            void ror(const Mem8& dst, const Reg8& shift)
            {
                AppendInstr(I_ROR, 0xD2, 0, Imm8(1), RW(dst), Dummy(R(shift), cl));
            }
            void ror(const Reg8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROR, 0xD0, 0, Imm8(1), RW(dst)) : AppendInstr(I_ROR, 0xC0, 0, Imm8(1), RW(dst), shift);
            }
            void ror(const Mem8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROR, 0xD0, 0, Imm8(1), RW(dst)) : AppendInstr(I_ROR, 0xC0, 0, Imm8(1), RW(dst), shift);
            }
            void rcl(const Reg16& dst, const Reg8& shift)
            {
                AppendInstr(I_RCL, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst), Dummy(R(shift), cl));
            }
            void rcl(const Mem16& dst, const Reg8& shift)
            {
                AppendInstr(I_RCL, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst), Dummy(R(shift), cl));
            }
            void rcl(const Reg16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCL, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst)) : AppendInstr(I_RCL, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst), shift);
            }
            void rcl(const Mem16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCL, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst)) : AppendInstr(I_RCL, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(2), RW(dst), shift);
            }
            void rcr(const Reg16& dst, const Reg8& shift)
            {
                AppendInstr(I_RCR, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst), Dummy(R(shift), cl));
            }
            void rcr(const Mem16& dst, const Reg8& shift)
            {
                AppendInstr(I_RCR, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst), Dummy(R(shift), cl));
            }
            void rcr(const Reg16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCR, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst)) : AppendInstr(I_RCR, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst), shift);
            }
            void rcr(const Mem16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCR, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst)) : AppendInstr(I_RCR, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst), shift);
            }
            void rol(const Reg16& dst, const Reg8& shift)
            {
                AppendInstr(I_ROL, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst), Dummy(R(shift), cl));
            }
            void rol(const Mem16& dst, const Reg8& shift)
            {
                AppendInstr(I_ROL, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst), Dummy(R(shift), cl));
            }
            void rol(const Reg16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROL, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst)) : AppendInstr(I_ROL, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst), shift);
            }
            void rol(const Mem16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROL, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst)) : AppendInstr(I_ROL, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(0), RW(dst), shift);
            }
            void ror(const Reg16& dst, const Reg8& shift)
            {
                AppendInstr(I_ROR, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst), Dummy(R(shift), cl));
            }
            void ror(const Mem16& dst, const Reg8& shift)
            {
                AppendInstr(I_ROR, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst), Dummy(R(shift), cl));
            }
            void ror(const Reg16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROR, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst)) : AppendInstr(I_ROR, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst), shift);
            }
            void ror(const Mem16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROR, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst)) : AppendInstr(I_ROR, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(1), RW(dst), shift);
            }
            void rcl(const Reg32& dst, const Reg8& shift)
            {
                AppendInstr(I_RCL, 0xD3, 0, Imm8(2), RW(dst), Dummy(R(shift), cl));
            }
            void rcl(const Mem32& dst, const Reg8& shift)
            {
                AppendInstr(I_RCL, 0xD3, 0, Imm8(2), RW(dst), Dummy(R(shift), cl));
            }
            void rcl(const Reg32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCL, 0xD1, 0, Imm8(2), RW(dst)) : AppendInstr(I_RCL, 0xC1, 0, Imm8(2), RW(dst), shift);
            }
            void rcl(const Mem32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCL, 0xD1, 0, Imm8(2), RW(dst)) : AppendInstr(I_RCL, 0xC1, 0, Imm8(2), RW(dst), shift);
            }
            void rcr(const Reg32& dst, const Reg8& shift)
            {
                AppendInstr(I_RCR, 0xD3, 0, Imm8(3), RW(dst), Dummy(R(shift), cl));
            }
            void rcr(const Mem32& dst, const Reg8& shift)
            {
                AppendInstr(I_RCR, 0xD3, 0, Imm8(3), RW(dst), Dummy(R(shift), cl));
            }
            void rcr(const Reg32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCR, 0xD1, 0, Imm8(3), RW(dst)) : AppendInstr(I_RCR, 0xC1, 0, Imm8(3), RW(dst), shift);
            }
            void rcr(const Mem32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCR, 0xD1, 0, Imm8(3), RW(dst)) : AppendInstr(I_RCR, 0xC1, 0, Imm8(3), RW(dst), shift);
            }
            void rol(const Reg32& dst, const Reg8& shift)
            {
                AppendInstr(I_ROL, 0xD3, 0, Imm8(0), RW(dst), Dummy(R(shift), cl));
            }
            void rol(const Mem32& dst, const Reg8& shift)
            {
                AppendInstr(I_ROL, 0xD3, 0, Imm8(0), RW(dst), Dummy(R(shift), cl));
            }
            void rol(const Reg32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROL, 0xD1, 0, Imm8(0), RW(dst)) : AppendInstr(I_ROL, 0xC1, 0, Imm8(0), RW(dst), shift);
            }
            void rol(const Mem32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROL, 0xD1, 0, Imm8(0), RW(dst)) : AppendInstr(I_ROL, 0xC1, 0, Imm8(0), RW(dst), shift);
            }
            void ror(const Reg32& dst, const Reg8& shift)
            {
                AppendInstr(I_ROR, 0xD3, 0, Imm8(1), RW(dst), Dummy(R(shift), cl));
            }
            void ror(const Mem32& dst, const Reg8& shift)
            {
                AppendInstr(I_ROR, 0xD3, 0, Imm8(1), RW(dst), Dummy(R(shift), cl));
            }
            void ror(const Reg32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROR, 0xD1, 0, Imm8(1), RW(dst)) : AppendInstr(I_ROR, 0xC1, 0, Imm8(1), RW(dst), shift);
            }
            void ror(const Mem32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROR, 0xD1, 0, Imm8(1), RW(dst)) : AppendInstr(I_ROR, 0xC1, 0, Imm8(1), RW(dst), shift);
            }
            void rcl(const Reg64& dst, const Reg8& shift)
            {
                AppendInstr(I_RCL, 0xD3, E_REXW_PREFIX, Imm8(2), RW(dst), Dummy(R(shift), cl));
            }
            void rcl(const Mem64& dst, const Reg8& shift)
            {
                AppendInstr(I_RCL, 0xD3, E_REXW_PREFIX, Imm8(2), RW(dst), Dummy(R(shift), cl));
            }
            void rcl(const Reg64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCL, 0xD1, E_REXW_PREFIX, Imm8(2), RW(dst)) : AppendInstr(I_RCL, 0xC1, E_REXW_PREFIX, Imm8(2), RW(dst), shift);
            }
            void rcl(const Mem64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCL, 0xD1, E_REXW_PREFIX, Imm8(2), RW(dst)) : AppendInstr(I_RCL, 0xC1, E_REXW_PREFIX, Imm8(2), RW(dst), shift);
            }
            void rcr(const Reg64& dst, const Reg8& shift)
            {
                AppendInstr(I_RCR, 0xD3, E_REXW_PREFIX, Imm8(3), RW(dst), Dummy(R(shift), cl));
            }
            void rcr(const Mem64& dst, const Reg8& shift)
            {
                AppendInstr(I_RCR, 0xD3, E_REXW_PREFIX, Imm8(3), RW(dst), Dummy(R(shift), cl));
            }
            void rcr(const Reg64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCR, 0xD1, E_REXW_PREFIX, Imm8(3), RW(dst)) : AppendInstr(I_RCR, 0xC1, E_REXW_PREFIX, Imm8(3), RW(dst), shift);
            }
            void rcr(const Mem64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_RCR, 0xD1, E_REXW_PREFIX, Imm8(3), RW(dst)) : AppendInstr(I_RCR, 0xC1, E_REXW_PREFIX, Imm8(3), RW(dst), shift);
            }
            void rol(const Reg64& dst, const Reg8& shift)
            {
                AppendInstr(I_ROL, 0xD3, E_REXW_PREFIX, Imm8(0), RW(dst), Dummy(R(shift), cl));
            }
            void rol(const Mem64& dst, const Reg8& shift)
            {
                AppendInstr(I_ROL, 0xD3, E_REXW_PREFIX, Imm8(0), RW(dst), Dummy(R(shift), cl));
            }
            void rol(const Reg64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROL, 0xD1, E_REXW_PREFIX, Imm8(0), RW(dst)) : AppendInstr(I_ROL, 0xC1, E_REXW_PREFIX, Imm8(0), RW(dst), shift);
            }
            void rol(const Mem64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROL, 0xD1, E_REXW_PREFIX, Imm8(0), RW(dst)) : AppendInstr(I_ROL, 0xC1, E_REXW_PREFIX, Imm8(0), RW(dst), shift);
            }
            void ror(const Reg64& dst, const Reg8& shift)
            {
                AppendInstr(I_ROR, 0xD3, E_REXW_PREFIX, Imm8(1), RW(dst), Dummy(R(shift), cl));
            }
            void ror(const Mem64& dst, const Reg8& shift)
            {
                AppendInstr(I_ROR, 0xD3, E_REXW_PREFIX, Imm8(1), RW(dst), Dummy(R(shift), cl));
            }
            void ror(const Reg64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROR, 0xD1, E_REXW_PREFIX, Imm8(1), RW(dst)) : AppendInstr(I_ROR, 0xC1, E_REXW_PREFIX, Imm8(1), RW(dst), shift);
            }
            void ror(const Mem64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_ROR, 0xD1, E_REXW_PREFIX, Imm8(1), RW(dst)) : AppendInstr(I_ROR, 0xC1, E_REXW_PREFIX, Imm8(1), RW(dst), shift);
            }
            void rdmsr()
            {
                AppendInstr(I_RDMSR, 0x0F32, 0, Dummy(R(ecx)), Dummy(W(edx)), Dummy(W(eax)));
            }
            void rdpmc()
            {
                AppendInstr(I_RDMSR, 0x0F33, 0, Dummy(R(ecx)), Dummy(W(edx)), Dummy(W(eax)));
            }
            void rdtsc()
            {
                AppendInstr(I_RDPMC, 0x0F31, 0, Dummy(W(edx)), Dummy(W(eax)), Dummy(W(ecx)));
            }
            void ret()
            {
                AppendInstr(I_RET, 0xC3, 0, Dummy(RW(esp)));
            }
            void ret(const Imm16& imm)
            {
                AppendInstr(I_RET, 0xC2, 0, imm, Dummy(RW(esp)));
            }
            void rsm()
            {
                AppendInstr(I_RSM, 0x0FAA, 0);
            }
            void sal(const Reg8& dst, const Reg8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Mem8& dst, const Reg8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Reg8& dst, const Imm8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Mem8& dst, const Imm8& shift)
            {
                shl(dst, shift);
            }
            void sar(const Reg8& dst, const Reg8& shift)
            {
                AppendInstr(I_SAR, 0xD2, 0, Imm8(7), RW(dst), Dummy(R(shift), cl));
            }
            void sar(const Mem8& dst, const Reg8& shift)
            {
                AppendInstr(I_SAR, 0xD2, 0, Imm8(7), RW(dst), Dummy(R(shift), cl));
            }
            void sar(const Reg8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SAR, 0xD0, 0, Imm8(7), RW(dst)) : AppendInstr(I_SAR, 0xC0, 0, Imm8(7), RW(dst), shift);
            }
            void sar(const Mem8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SAR, 0xD0, 0, Imm8(7), RW(dst)) : AppendInstr(I_SAR, 0xC0, 0, Imm8(7), RW(dst), shift);
            }
            void shl(const Reg8& dst, const Reg8& shift)
            {
                AppendInstr(I_SHL, 0xD2, 0, Imm8(4), RW(dst), Dummy(R(shift), cl));
            }
            void shl(const Mem8& dst, const Reg8& shift)
            {
                AppendInstr(I_SHL, 0xD2, 0, Imm8(4), RW(dst), Dummy(R(shift), cl));
            }
            void shl(const Reg8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHL, 0xD0, 0, Imm8(4), RW(dst)) : AppendInstr(I_SHL, 0xC0, 0, Imm8(4), RW(dst), shift);
            }
            void shl(const Mem8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHL, 0xD0, 0, Imm8(4), RW(dst)) : AppendInstr(I_SHL, 0xC0, 0, Imm8(4), RW(dst), shift);
            }
            void shr(const Reg8& dst, const Reg8& shift)
            {
                AppendInstr(I_SHR, 0xD2, 0, Imm8(5), RW(dst), Dummy(R(shift), cl));
            }
            void shr(const Mem8& dst, const Reg8& shift)
            {
                AppendInstr(I_SHR, 0xD2, 0, Imm8(5), RW(dst), Dummy(R(shift), cl));
            }
            void shr(const Reg8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHR, 0xD0, 0, Imm8(5), RW(dst)) : AppendInstr(I_SHR, 0xC0, 0, Imm8(5), RW(dst), shift);
            }
            void shr(const Mem8& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHR, 0xD0, 0, Imm8(5), RW(dst)) : AppendInstr(I_SHR, 0xC0, 0, Imm8(5), RW(dst), shift);
            }
            void sal(const Reg16& dst, const Reg8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Mem16& dst, const Reg8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Reg16& dst, const Imm8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Mem16& dst, const Imm8& shift)
            {
                shl(dst, shift);
            }
            void sar(const Reg16& dst, const Reg8& shift)
            {
                AppendInstr(I_SAR, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(7), RW(dst), Dummy(R(shift), cl));
            }
            void sar(const Mem16& dst, const Reg8& shift)
            {
                AppendInstr(I_SAR, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(7), RW(dst), Dummy(R(shift), cl));
            }
            void sar(const Reg16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SAR, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(7), RW(dst)) : AppendInstr(I_SAR, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(7), RW(dst), shift);
            }
            void sar(const Mem16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SAR, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(7), RW(dst)) : AppendInstr(I_SAR, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(7), RW(dst), shift);
            }
            void shl(const Reg16& dst, const Reg8& shift)
            {
                AppendInstr(I_SHL, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(4), RW(dst), Dummy(R(shift), cl));
            }
            void shl(const Mem16& dst, const Reg8& shift)
            {
                AppendInstr(I_SHL, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(4), RW(dst), Dummy(R(shift), cl));
            }
            void shl(const Reg16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHL, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(4), RW(dst)) : AppendInstr(I_SHL, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(4), RW(dst), shift);
            }
            void shl(const Mem16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHL, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(4), RW(dst)) : AppendInstr(I_SHL, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(4), RW(dst), shift);
            }
            void shr(const Reg16& dst, const Reg8& shift)
            {
                AppendInstr(I_SHR, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(dst), Dummy(R(shift), cl));
            }
            void shr(const Mem16& dst, const Reg8& shift)
            {
                AppendInstr(I_SHR, 0xD3, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(dst), Dummy(R(shift), cl));
            }
            void shr(const Reg16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHR, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(dst)) : AppendInstr(I_SHR, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(dst), shift);
            }
            void shr(const Mem16& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHR, 0xD1, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(dst)) : AppendInstr(I_SHR, 0xC1, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(dst), shift);
            }
            void sal(const Reg32& dst, const Reg8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Mem32& dst, const Reg8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Reg32& dst, const Imm8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Mem32& dst, const Imm8& shift)
            {
                shl(dst, shift);
            }
            void sar(const Reg32& dst, const Reg8& shift)
            {
                AppendInstr(I_SAR, 0xD3, 0, Imm8(7), RW(dst), Dummy(R(shift), cl));
            }
            void sar(const Mem32& dst, const Reg8& shift)
            {
                AppendInstr(I_SAR, 0xD3, 0, Imm8(7), RW(dst), Dummy(R(shift), cl));
            }
            void sar(const Reg32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SAR, 0xD1, 0, Imm8(7), RW(dst)) : AppendInstr(I_SAR, 0xC1, 0, Imm8(7), RW(dst), shift);
            }
            void sar(const Mem32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SAR, 0xD1, 0, Imm8(7), RW(dst)) : AppendInstr(I_SAR, 0xC1, 0, Imm8(7), RW(dst), shift);
            }
            void shl(const Reg32& dst, const Reg8& shift)
            {
                AppendInstr(I_SHL, 0xD3, 0, Imm8(4), RW(dst), Dummy(R(shift), cl));
            }
            void shl(const Mem32& dst, const Reg8& shift)
            {
                AppendInstr(I_SHL, 0xD3, 0, Imm8(4), RW(dst), Dummy(R(shift), cl));
            }
            void shl(const Reg32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHL, 0xD1, 0, Imm8(4), RW(dst)) : AppendInstr(I_SHL, 0xC1, 0, Imm8(4), RW(dst), shift);
            }
            void shl(const Mem32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHL, 0xD1, 0, Imm8(4), RW(dst)) : AppendInstr(I_SHL, 0xC1, 0, Imm8(4), RW(dst), shift);
            }
            void shr(const Reg32& dst, const Reg8& shift)
            {
                AppendInstr(I_SHR, 0xD3, 0, Imm8(5), RW(dst), Dummy(R(shift), cl));
            }
            void shr(const Mem32& dst, const Reg8& shift)
            {
                AppendInstr(I_SHR, 0xD3, 0, Imm8(5), RW(dst), Dummy(R(shift), cl));
            }
            void shr(const Reg32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHR, 0xD1, 0, Imm8(5), RW(dst)) : AppendInstr(I_SHR, 0xC1, 0, Imm8(5), RW(dst), shift);
            }
            void shr(const Mem32& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHR, 0xD1, 0, Imm8(5), RW(dst)) : AppendInstr(I_SHR, 0xC1, 0, Imm8(5), RW(dst), shift);
            }
            void sal(const Reg64& dst, const Reg8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Mem64& dst, const Reg8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Reg64& dst, const Imm8& shift)
            {
                shl(dst, shift);
            }
            void sal(const Mem64& dst, const Imm8& shift)
            {
                shl(dst, shift);
            }
            void sar(const Reg64& dst, const Reg8& shift)
            {
                AppendInstr(I_SAR, 0xD3, E_REXW_PREFIX, Imm8(7), RW(dst), Dummy(R(shift), cl));
            }
            void sar(const Mem64& dst, const Reg8& shift)
            {
                AppendInstr(I_SAR, 0xD3, E_REXW_PREFIX, Imm8(7), RW(dst), Dummy(R(shift), cl));
            }
            void sar(const Reg64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SAR, 0xD1, E_REXW_PREFIX, Imm8(7), RW(dst)) : AppendInstr(I_SAR, 0xC1, E_REXW_PREFIX, Imm8(7), RW(dst), shift);
            }
            void sar(const Mem64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SAR, 0xD1, E_REXW_PREFIX, Imm8(7), RW(dst)) : AppendInstr(I_SAR, 0xC1, E_REXW_PREFIX, Imm8(7), RW(dst), shift);
            }
            void shl(const Reg64& dst, const Reg8& shift)
            {
                AppendInstr(I_SHL, 0xD3, E_REXW_PREFIX, Imm8(4), RW(dst), Dummy(R(shift), cl));
            }
            void shl(const Mem64& dst, const Reg8& shift)
            {
                AppendInstr(I_SHL, 0xD3, E_REXW_PREFIX, Imm8(4), RW(dst), Dummy(R(shift), cl));
            }
            void shl(const Reg64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHL, 0xD1, E_REXW_PREFIX, Imm8(4), RW(dst)) : AppendInstr(I_SHL, 0xC1, E_REXW_PREFIX, Imm8(4), RW(dst), shift);
            }
            void shl(const Mem64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHL, 0xD1, E_REXW_PREFIX, Imm8(4), RW(dst)) : AppendInstr(I_SHL, 0xC1, E_REXW_PREFIX, Imm8(4), RW(dst), shift);
            }
            void shr(const Reg64& dst, const Reg8& shift)
            {
                AppendInstr(I_SHR, 0xD3, E_REXW_PREFIX, Imm8(5), RW(dst), Dummy(R(shift), cl));
            }
            void shr(const Mem64& dst, const Reg8& shift)
            {
                AppendInstr(I_SHR, 0xD3, E_REXW_PREFIX, Imm8(5), RW(dst), Dummy(R(shift), cl));
            }
            void shr(const Reg64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHR, 0xD1, E_REXW_PREFIX, Imm8(5), RW(dst)) : AppendInstr(I_SHR, 0xC1, E_REXW_PREFIX, Imm8(5), RW(dst), shift);
            }
            void shr(const Mem64& dst, const Imm8& shift)
            {
                shift.GetImm() == 1 ? AppendInstr(I_SHR, 0xD1, E_REXW_PREFIX, Imm8(5), RW(dst)) : AppendInstr(I_SHR, 0xC1, E_REXW_PREFIX, Imm8(5), RW(dst), shift);
            }
            void sbb(const Reg8& dst, const Imm8& imm)
            {
                AppendInstr(I_SBB, 0x80, 0, Imm8(3), RW(dst), imm);
            }
            void sbb(const Mem8& dst, const Imm8& imm)
            {
                AppendInstr(I_SBB, 0x80, 0, Imm8(3), RW(dst), imm);
            }
            void sbb(const Reg16& dst, const Imm16& imm)
            {
                AppendInstr(I_SBB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst), detail::ImmXor8(imm));
            }
            void sbb(const Mem16& dst, const Imm16& imm)
            {
                AppendInstr(I_SBB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(3), RW(dst), detail::ImmXor8(imm));
            }
            void sbb(const Reg32& dst, const Imm32& imm)
            {
                AppendInstr(I_SBB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(3), RW(dst), detail::ImmXor8(imm));
            }
            void sbb(const Mem32& dst, const Imm32& imm)
            {
                AppendInstr(I_SBB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(3), RW(dst), detail::ImmXor8(imm));
            }
            void sbb(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_SBB, 0x18, 0, R(src), RW(dst));
            }
            void sbb(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_SBB, 0x18, 0, R(src), RW(dst));
            }
            void sbb(const Reg8& dst, const Mem8& src)
            {
                AppendInstr(I_SBB, 0x1A, 0, RW(dst), R(src));
            }
            void sbb(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_SBB, 0x19, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void sbb(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_SBB, 0x19, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void sbb(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_SBB, 0x1B, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void sbb(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_SBB, 0x19, 0, R(src), RW(dst));
            }
            void sbb(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_SBB, 0x19, 0, R(src), RW(dst));
            }
            void sbb(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_SBB, 0x1B, 0, RW(dst), R(src));
            }
            void sbb(const Reg64& dst, const Imm32& imm)
            {
                AppendInstr(I_SBB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(3), RW(dst), detail::ImmXor8(imm));
            }
            void sbb(const Mem64& dst, const Imm32& imm)
            {
                AppendInstr(I_SBB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(3), RW(dst), detail::ImmXor8(imm));
            }
            void sbb(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_SBB, 0x19, E_REXW_PREFIX, R(src), RW(dst));
            }
            void sbb(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_SBB, 0x19, E_REXW_PREFIX, R(src), RW(dst));
            }
            void sbb(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_SBB, 0x1B, E_REXW_PREFIX, RW(dst), R(src));
            }
            void scasb()
            {
                AppendInstr(I_SCAS_B, 0xAE, 0, Dummy(R(al)), Dummy(RW(edi)));
            }
            void scasw()
            {
                AppendInstr(I_SCAS_W, 0xAF, E_OPERAND_SIZE_PREFIX, Dummy(R(ax)), Dummy(RW(edi)));
            }
            void scasd()
            {
                AppendInstr(I_SCAS_D, 0xAF, 0, Dummy(R(eax)), Dummy(RW(edi)));
            }
            void scasq()
            {
                AppendInstr(I_SCAS_Q, 0xAF, E_REXW_PREFIX, Dummy(R(rax)), Dummy(RW(rdi)));
            }
            void seta(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F97, 0, Imm8(0), W(dst));
            }
            void seta(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F97, 0, Imm8(0), W(dst));
            }
            void setae(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F93, 0, Imm8(0), W(dst));
            }
            void setae(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F93, 0, Imm8(0), W(dst));
            }
            void setb(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F92, 0, Imm8(0), W(dst));
            }
            void setb(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F92, 0, Imm8(0), W(dst));
            }
            void setbe(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F96, 0, Imm8(0), W(dst));
            }
            void setbe(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F96, 0, Imm8(0), W(dst));
            }
            void setc(const Reg8& dst)
            {
                setb(dst);
            }
            void setc(const Mem8& dst)
            {
                setb(dst);
            }
            void sete(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F94, 0, Imm8(0), W(dst));
            }
            void sete(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F94, 0, Imm8(0), W(dst));
            }
            void setg(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9F, 0, Imm8(0), W(dst));
            }
            void setg(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9F, 0, Imm8(0), W(dst));
            }
            void setge(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9D, 0, Imm8(0), W(dst));
            }
            void setge(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9D, 0, Imm8(0), W(dst));
            }
            void setl(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9C, 0, Imm8(0), W(dst));
            }
            void setl(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9C, 0, Imm8(0), W(dst));
            }
            void setle(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9E, 0, Imm8(0), W(dst));
            }
            void setle(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9E, 0, Imm8(0), W(dst));
            }
            void setna(const Reg8& dst)
            {
                setbe(dst);
            }
            void setna(const Mem8& dst)
            {
                setbe(dst);
            }
            void setnae(const Reg8& dst)
            {
                setb(dst);
            }
            void setnae(const Mem8& dst)
            {
                setb(dst);
            }
            void setnb(const Reg8& dst)
            {
                setae(dst);
            }
            void setnb(const Mem8& dst)
            {
                setae(dst);
            }
            void setnbe(const Reg8& dst)
            {
                seta(dst);
            }
            void setnbe(const Mem8& dst)
            {
                seta(dst);
            }
            void setnc(const Reg8& dst)
            {
                setae(dst);
            }
            void setnc(const Mem8& dst)
            {
                setae(dst);
            }
            void setne(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F95, 0, Imm8(0), W(dst));
            }
            void setne(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F95, 0, Imm8(0), W(dst));
            }
            void setng(const Reg8& dst)
            {
                setle(dst);
            }
            void setng(const Mem8& dst)
            {
                setle(dst);
            }
            void setnge(const Reg8& dst)
            {
                setl(dst);
            }
            void setnge(const Mem8& dst)
            {
                setl(dst);
            }
            void setnl(const Reg8& dst)
            {
                setge(dst);
            }
            void setnl(const Mem8& dst)
            {
                setge(dst);
            }
            void setnle(const Reg8& dst)
            {
                setg(dst);
            }
            void setnle(const Mem8& dst)
            {
                setg(dst);
            }
            void setno(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F91, 0, Imm8(0), W(dst));
            }
            void setno(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F91, 0, Imm8(0), W(dst));
            }
            void setnp(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9B, 0, Imm8(0), W(dst));
            }
            void setnp(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9B, 0, Imm8(0), W(dst));
            }
            void setns(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F99, 0, Imm8(0), W(dst));
            }
            void setns(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F99, 0, Imm8(0), W(dst));
            }
            void setnz(const Reg8& dst)
            {
                setne(dst);
            }
            void setnz(const Mem8& dst)
            {
                setne(dst);
            }
            void seto(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F90, 0, Imm8(0), W(dst));
            }
            void seto(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F90, 0, Imm8(0), W(dst));
            }
            void setp(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9A, 0, Imm8(0), W(dst));
            }
            void setp(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F9A, 0, Imm8(0), W(dst));
            }
            void setpe(const Reg8& dst)
            {
                setp(dst);
            }
            void setpe(const Mem8& dst)
            {
                setp(dst);
            }
            void setpo(const Reg8& dst)
            {
                setnp(dst);
            }
            void setpo(const Mem8& dst)
            {
                setnp(dst);
            }
            void sets(const Reg8& dst)
            {
                AppendInstr(I_SETCC, 0x0F98, 0, Imm8(0), W(dst));
            }
            void sets(const Mem8& dst)
            {
                AppendInstr(I_SETCC, 0x0F98, 0, Imm8(0), W(dst));
            }
            void setz(const Reg8& dst)
            {
                sete(dst);
            }
            void setz(const Mem8& dst)
            {
                sete(dst);
            }
            void shld(const Reg16& dst, const Reg16& src, const Imm8& place)
            {
                AppendInstr(I_SHLD, 0x0FA4, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), place);
            }
            void shld(const Mem16& dst, const Reg16& src, const Imm8& place)
            {
                AppendInstr(I_SHLD, 0x0FA4, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), place);
            }
            void shld(const Reg16& dst, const Reg16& src, const Reg8& place)
            {
                AppendInstr(I_SHLD, 0x0FA5, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shld(const Mem16& dst, const Reg16& src, const Reg8& place)
            {
                AppendInstr(I_SHLD, 0x0FA5, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shld(const Reg32& dst, const Reg32& src, const Imm8& place)
            {
                AppendInstr(I_SHLD, 0x0FA4, 0, R(src), RW(dst), place);
            }
            void shld(const Mem32& dst, const Reg32& src, const Imm8& place)
            {
                AppendInstr(I_SHLD, 0x0FA4, 0, R(src), RW(dst), place);
            }
            void shld(const Reg32& dst, const Reg32& src, const Reg8& place)
            {
                AppendInstr(I_SHLD, 0x0FA5, 0, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shld(const Mem32& dst, const Reg32& src, const Reg8& place)
            {
                AppendInstr(I_SHLD, 0x0FA5, 0, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shld(const Reg64& dst, const Reg64& src, const Imm8& place)
            {
                AppendInstr(I_SHLD, 0x0FA4, E_REXW_PREFIX, R(src), RW(dst), place);
            }
            void shld(const Mem64& dst, const Reg64& src, const Imm8& place)
            {
                AppendInstr(I_SHLD, 0x0FA4, E_REXW_PREFIX, R(src), RW(dst), place);
            }
            void shld(const Reg64& dst, const Reg64& src, const Reg8& place)
            {
                AppendInstr(I_SHLD, 0x0FA5, E_REXW_PREFIX, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shld(const Mem64& dst, const Reg64& src, const Reg8& place)
            {
                AppendInstr(I_SHLD, 0x0FA5, E_REXW_PREFIX, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shrd(const Reg16& dst, const Reg16& src, const Imm8& place)
            {
                AppendInstr(I_SHRD, 0x0FAC, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), place);
            }
            void shrd(const Mem16& dst, const Reg16& src, const Imm8& place)
            {
                AppendInstr(I_SHRD, 0x0FAC, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), place);
            }
            void shrd(const Reg16& dst, const Reg16& src, const Reg8& place)
            {
                AppendInstr(I_SHRD, 0x0FAD, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shrd(const Mem16& dst, const Reg16& src, const Reg8& place)
            {
                AppendInstr(I_SHRD, 0x0FAD, E_OPERAND_SIZE_PREFIX, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shrd(const Reg32& dst, const Reg32& src, const Imm8& place)
            {
                AppendInstr(I_SHRD, 0x0FAC, 0, R(src), RW(dst), place);
            }
            void shrd(const Mem32& dst, const Reg32& src, const Imm8& place)
            {
                AppendInstr(I_SHRD, 0x0FAC, 0, R(src), RW(dst), place);
            }
            void shrd(const Reg32& dst, const Reg32& src, const Reg8& place)
            {
                AppendInstr(I_SHRD, 0x0FAD, 0, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shrd(const Mem32& dst, const Reg32& src, const Reg8& place)
            {
                AppendInstr(I_SHRD, 0x0FAD, 0, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shrd(const Reg64& dst, const Reg64& src, const Imm8& place)
            {
                AppendInstr(I_SHRD, 0x0FAC, E_REXW_PREFIX, R(src), RW(dst), place);
            }
            void shrd(const Mem64& dst, const Reg64& src, const Imm8& place)
            {
                AppendInstr(I_SHRD, 0x0FAC, E_REXW_PREFIX, R(src), RW(dst), place);
            }
            void shrd(const Reg64& dst, const Reg64& src, const Reg8& place)
            {
                AppendInstr(I_SHRD, 0x0FAD, E_REXW_PREFIX, R(src), RW(dst), Dummy(R(place), cl));
            }
            void shrd(const Mem64& dst, const Reg64& src, const Reg8& place)
            {
                AppendInstr(I_SHRD, 0x0FAD, E_REXW_PREFIX, R(src), RW(dst), Dummy(R(place), cl));
            }
            template<class Ty> void sgdt(const MemT<Ty>& dst)
            {
                AppendInstr(I_SGDT, 0x0F01, 0, Imm8(0), W(dst));
            }
            template<class Ty> void sidt(const MemT<Ty>& dst)
            {
                AppendInstr(I_SIDT, 0x0F01, 0, Imm8(1), W(dst));
            }
            void sldt(const Reg16& dst)
            {
                AppendInstr(I_SLDT, 0x0F00, E_OPERAND_SIZE_PREFIX, Imm8(0), W(dst));
            }
            void sldt(const Mem16& dst)
            {
                AppendInstr(I_SLDT, 0x0F00, 0, Imm8(0), W(dst));
            }
            void sldt(const Reg64& dst)
            {
                AppendInstr(I_SLDT, 0x0F00, E_REXW_PREFIX, Imm8(0), W(dst));
            }
            void smsw(const Reg16& dst)
            {
                AppendInstr(I_SMSW, 0x0F01, E_OPERAND_SIZE_PREFIX, Imm8(4), W(dst));
            }
            void smsw(const Mem16& dst)
            {
                AppendInstr(I_SMSW, 0x0F01, 0, Imm8(4), W(dst));
            }
            void smsw(const Reg64& dst)
            {
                AppendInstr(I_SMSW, 0x0F01, E_REXW_PREFIX, Imm8(4), W(dst));
            }
            void stc()
            {
                AppendInstr(I_STC, 0xF9, 0);
            }
            void std()
            {
                AppendInstr(I_STD, 0xFD, 0);
            }
            void sti()
            {
                AppendInstr(I_STI, 0xFB, 0);
            }
            void stosb(const Reg& dst, const Reg8& src)
            {
                AppendInstr(I_STOS_B, 0xAA, 0, Dummy(R(src), al), Dummy(RW(dst), zdi));
            }
            void stosw(const Reg& dst, const Reg16& src)
            {
                AppendInstr(I_STOS_W, 0xAB, E_OPERAND_SIZE_PREFIX, Dummy(R(src), ax), Dummy(RW(dst), zdi));
            }
            void stosd(const Reg& dst, const Reg32& src)
            {
                AppendInstr(I_STOS_D, 0xAB, 0, Dummy(R(src), eax), Dummy(RW(dst), zdi));
            }
            void stosq(const Reg& dst, const Reg64& src)
            {
                AppendInstr(I_STOS_Q, 0xAB, E_REXW_PREFIX, Dummy(R(src), rax), Dummy(RW(dst), zdi));
            }
            void rep_stosb(const Reg& dst, const Reg8& src, const Reg& count)
            {
                AppendInstr(I_STOS_B, 0xAA, E_REP_PREFIX, Dummy(R(src), al), Dummy(RW(dst), zdi), Dummy(RW(count), zcx));
            }
            void rep_stosw(const Reg& dst, const Reg16& src, const Reg& count)
            {
                AppendInstr(I_STOS_W, 0xAB, E_REP_PREFIX | E_OPERAND_SIZE_PREFIX, Dummy(R(src), ax), Dummy(RW(dst), zdi), Dummy(RW(count), zcx));
            }
            void rep_stosd(const Reg& dst, const Reg32& src, const Reg& count)
            {
                AppendInstr(I_STOS_D, 0xAB, E_REP_PREFIX, Dummy(R(src), eax), Dummy(RW(dst), zdi), Dummy(RW(count), zcx));
            }
            void rep_stosq(const Reg& dst, const Reg64& src, const Reg& count)
            {
                AppendInstr(I_STOS_Q, 0xAB, E_REP_PREFIX | E_REXW_PREFIX, Dummy(R(src), rax), Dummy(RW(dst), zdi), Dummy(RW(count), zcx));
            }
            void sub(const Reg8& dst, const Imm8& imm)
            {
                AppendInstr(I_SUB, 0x80, 0, Imm8(5), RW(dst), imm);
            }
            void sub(const Mem8& dst, const Imm8& imm)
            {
                AppendInstr(I_SUB, 0x80, 0, Imm8(5), RW(dst), imm);
            }
            void sub(const Reg16& dst, const Imm16& imm)
            {
                AppendInstr(I_SUB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(dst), detail::ImmXor8(imm));
            }
            void sub(const Mem16& dst, const Imm16& imm)
            {
                AppendInstr(I_SUB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(5), RW(dst), detail::ImmXor8(imm));
            }
            void sub(const Reg32& dst, const Imm32& imm)
            {
                AppendInstr(I_SUB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(5), RW(dst), detail::ImmXor8(imm));
            }
            void sub(const Mem32& dst, const Imm32& imm)
            {
                AppendInstr(I_SUB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(5), RW(dst), detail::ImmXor8(imm));
            }
            void sub(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_SUB, 0x28, 0, R(src), RW(dst));
            }
            void sub(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_SUB, 0x28, 0, R(src), RW(dst));
            }
            void sub(const Reg8& dst, const Mem8& src)
            {
                AppendInstr(I_SUB, 0x2A, 0, RW(dst), R(src));
            }
            void sub(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_SUB, 0x29, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void sub(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_SUB, 0x29, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void sub(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_SUB, 0x2B, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void sub(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_SUB, 0x29, 0, R(src), RW(dst));
            }
            void sub(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_SUB, 0x29, 0, R(src), RW(dst));
            }
            void sub(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_SUB, 0x2B, 0, RW(dst), R(src));
            }
            void sub(const Reg64& dst, const Imm32& imm)
            {
                AppendInstr(I_SUB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(5), RW(dst), detail::ImmXor8(imm));
            }
            void sub(const Mem64& dst, const Imm32& imm)
            {
                AppendInstr(I_SUB, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(5), RW(dst), detail::ImmXor8(imm));
            }
            void sub(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_SUB, 0x29, E_REXW_PREFIX, R(src), RW(dst));
            }
            void sub(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_SUB, 0x29, E_REXW_PREFIX, R(src), RW(dst));
            }
            void sub(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_SUB, 0x2B, E_REXW_PREFIX, RW(dst), R(src));
            }
            void swapgs()
            {
                AppendInstr(I_SWAPGS, 0x0F01F8, 0);
            }   // 0F 01 /7
            void syscall()
            {
                AppendInstr(I_SYSCALL, 0x0F05, 0);
            }
            void sysret()
            {
                AppendInstr(I_SYSRET, 0x0F07, 0);
            }
            void test(const Reg8& src1, const Imm8& src2)
            {
                AppendInstr(I_TEST, 0xF6, 0, Imm8(0), R(src1), R(src2));
            }
            void test(const Mem8& src1, const Imm8& src2)
            {
                AppendInstr(I_TEST, 0xF6, 0, Imm8(0), R(src1), R(src2));
            }
            void test(const Reg16& src1, const Imm16& src2)
            {
                AppendInstr(I_TEST, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(0), R(src1), R(src2));
            }
            void test(const Mem16& src1, const Imm16& src2)
            {
                AppendInstr(I_TEST, 0xF7, E_OPERAND_SIZE_PREFIX, Imm8(0), R(src1), R(src2));
            }
            void test(const Reg32& src1, const Imm32& src2)
            {
                AppendInstr(I_TEST, 0xF7, 0, Imm8(0), R(src1), R(src2));
            }
            void test(const Mem32& src1, const Imm32& src2)
            {
                AppendInstr(I_TEST, 0xF7, 0, Imm8(0), R(src1), R(src2));
            }
            void test(const Reg8& src1, const Reg8& src2)
            {
                AppendInstr(I_TEST, 0x84, 0, R(src1), R(src2));
            }
            void test(const Mem8& src1, const Reg8& src2)
            {
                AppendInstr(I_TEST, 0x84, 0, R(src2), R(src1));
            }
            void test(const Reg16& src1, const Reg16& src2)
            {
                AppendInstr(I_TEST, 0x85, E_OPERAND_SIZE_PREFIX, R(src1), R(src2));
            }
            void test(const Mem16& src1, const Reg16& src2)
            {
                AppendInstr(I_TEST, 0x85, E_OPERAND_SIZE_PREFIX, R(src2), R(src1));
            }
            void test(const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_TEST, 0x85, 0, R(src1), R(src2));
            }
            void test(const Mem32& src1, const Reg32& src2)
            {
                AppendInstr(I_TEST, 0x85, 0, R(src2), R(src1));
            }
            void test(const Reg64& src1, const Imm32& src2)
            {
                AppendInstr(I_TEST, 0xF7, E_REXW_PREFIX, Imm8(0), R(src1), R(src2));
            }
            void test(const Mem64& src1, const Imm32& src2)
            {
                AppendInstr(I_TEST, 0xF7, E_REXW_PREFIX, Imm8(0), R(src1), R(src2));
            }
            void test(const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_TEST, 0x85, E_REXW_PREFIX, R(src1), R(src2));
            }
            void test(const Mem64& src1, const Reg64& src2)
            {
                AppendInstr(I_TEST, 0x85, E_REXW_PREFIX, R(src2), R(src1));
            }
            void ud2()
            {
                AppendInstr(I_UD2, 0x0F0B, 0);
            }
            void verr(const Reg16& src)
            {
                AppendInstr(I_VERR, 0x0F00, 0, Imm8(4), R(src));
            }
            void verr(const Mem16& src)
            {
                AppendInstr(I_VERR, 0x0F00, 0, Imm8(4), R(src));
            }
            void verw(const Reg16& src)
            {
                AppendInstr(I_VERW, 0x0F00, 0, Imm8(5), R(src));
            }
            void verw(const Mem16& src)
            {
                AppendInstr(I_VERW, 0x0F00, 0, Imm8(5), R(src));
            }
            void wait()
            {
                AppendInstr(I_WAIT, 0x9B, 0);
            }
            void wbinvd()
            {
                AppendInstr(I_WBINVD, 0x0F09, 0);
            }
            void wrmsr()
            {
                AppendInstr(I_WRMSR, 0x0F30, 0, Dummy(R(ecx)), Dummy(R(edx)), Dummy(R(eax)));
            }
            void xadd(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_XADD, 0x0FC0, 0, RW(src), RW(dst));
            }
            void xadd(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_XADD, 0x0FC0, 0, RW(src), RW(dst));
            }
            void xadd(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_XADD, 0x0FC1, E_OPERAND_SIZE_PREFIX, RW(src), RW(dst));
            }
            void xadd(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_XADD, 0x0FC1, E_OPERAND_SIZE_PREFIX, RW(src), RW(dst));
            }
            void xadd(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_XADD, 0x0FC1, 0, RW(src), RW(dst));
            }
            void xadd(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_XADD, 0x0FC1, 0, RW(src), RW(dst));
            }
            void xadd(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_XADD, 0x0FC1, E_REXW_PREFIX, RW(src), RW(dst));
            }
            void xadd(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_XADD, 0x0FC1, E_REXW_PREFIX, RW(src), RW(dst));
            }
            void xchg(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_XCHG, 0x86, 0, RW(dst), RW(src));
            }
            void xchg(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_XCHG, 0x86, 0, RW(src), RW(dst));
            }
            void xchg(const Reg8& dst, const Mem8& src)
            {
                AppendInstr(I_XCHG, 0x86, 0, RW(dst), RW(src));
            }
            void xchg(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_XCHG, 0x87, E_OPERAND_SIZE_PREFIX, RW(dst), RW(src));
            }
            void xchg(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_XCHG, 0x87, E_OPERAND_SIZE_PREFIX, RW(src), RW(dst));
            }
            void xchg(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_XCHG, 0x87, E_OPERAND_SIZE_PREFIX, RW(dst), RW(src));
            }
            void xchg(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_XCHG, 0x87, 0, RW(dst), RW(src));
            }
            void xchg(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_XCHG, 0x87, 0, RW(src), RW(dst));
            }
            void xchg(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_XCHG, 0x87, 0, RW(dst), RW(src));
            }
            void xchg(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_XCHG, 0x87, E_REXW_PREFIX, RW(dst), RW(src));
            }
            void xchg(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_XCHG, 0x87, E_REXW_PREFIX, RW(src), RW(dst));
            }
            void xchg(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_XCHG, 0x87, E_REXW_PREFIX, RW(dst), RW(src));
            }
            void xgetbv()
            {
                AppendInstr(I_XGETBV, 0x0F01D0, 0, Dummy(R(ecx)), Dummy(W(edx)), Dummy(W(eax)));
            }
            void xlatb()
            {
                AppendInstr(I_XLATB, 0xD7, 0, Dummy(RW(al)), Dummy(R(ebx)));
            }
            void xor(const Reg8& dst, const Imm8& imm)
            {
                AppendInstr(I_XOR, 0x80, 0, Imm8(6), RW(dst), imm);
            }
            void xor(const Mem8& dst, const Imm8& imm)
            {
                AppendInstr(I_XOR, 0x80, 0, Imm8(6), RW(dst), imm);
            }
            void xor(const Reg16& dst, const Imm16& imm)
            {
                AppendInstr(I_XOR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(6), RW(dst), detail::ImmXor8(imm));
            }
            void xor(const Mem16& dst, const Imm16& imm)
            {
                AppendInstr(I_XOR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_OPERAND_SIZE_PREFIX, Imm8(6), RW(dst), detail::ImmXor8(imm));
            }
            void xor(const Reg32& dst, const Imm32& imm)
            {
                AppendInstr(I_XOR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(6), RW(dst), detail::ImmXor8(imm));
            }
            void xor(const Mem32& dst, const Imm32& imm)
            {
                AppendInstr(I_XOR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, 0, Imm8(6), RW(dst), detail::ImmXor8(imm));
            }
            void xor(const Reg8& dst, const Reg8& src)
            {
                AppendInstr(I_XOR, 0x30, 0, R(src), RW(dst));
            }
            void xor(const Mem8& dst, const Reg8& src)
            {
                AppendInstr(I_XOR, 0x30, 0, R(src), RW(dst));
            }
            void xor(const Reg8& dst, const Mem8& src)
            {
                AppendInstr(I_XOR, 0x32, 0, RW(dst), R(src));
            }
            void xor(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_XOR, 0x31, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void xor(const Mem16& dst, const Reg16& src)
            {
                AppendInstr(I_XOR, 0x31, E_OPERAND_SIZE_PREFIX, R(src), RW(dst));
            }
            void xor(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_XOR, 0x33, E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void xor(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_XOR, 0x31, 0, R(src), RW(dst));
            }
            void xor(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_XOR, 0x31, 0, R(src), RW(dst));
            }
            void xor(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_XOR, 0x33, 0, RW(dst), R(src));
            }
            void xor(const Reg64& dst, const Imm32& imm)
            {
                AppendInstr(I_XOR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(6), RW(dst), detail::ImmXor8(imm));
            }
            void xor(const Mem64& dst, const Imm32& imm)
            {
                AppendInstr(I_XOR, detail::IsInt8(imm.GetImm()) ? 0x83 : 0x81, E_REXW_PREFIX, Imm8(6), RW(dst), detail::ImmXor8(imm));
            }
            void xor(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_XOR, 0x31, E_REXW_PREFIX, R(src), RW(dst));
            }
            void xor(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_XOR, 0x31, E_REXW_PREFIX, R(src), RW(dst));
            }
            void xor(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_XOR, 0x33, E_REXW_PREFIX, RW(dst), R(src));
            }

            // x87 Floating-Point Instructions
            void f2xm1()
            {
                AppendInstr(I_F2XM1, 0xD9F0, 0);
            }
            void fabs()
            {
                AppendInstr(I_FABS, 0xD9E1, 0);
            }
            void fadd(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FADD, 0xD8C0, 0, src); avoid_unused_warn(dst);
            }
            void fadd(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FADD, 0xDCC0, 0, dst); avoid_unused_warn(src);
            }
            void fadd(const Mem32& dst)
            {
                AppendInstr(I_FADD, 0xD8, 0, Imm8(0), dst);
            }
            void fadd(const Mem64& dst)
            {
                AppendInstr(I_FADD, 0xDC, 0, Imm8(0), dst);
            }
            void faddp()
            {
                AppendInstr(I_FADDP, 0xDEC1, 0);
            }
            void faddp(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FADDP, 0xDEC0, 0, dst);  avoid_unused_warn(src);
            }
            void fiadd(const Mem16& dst)
            {
                AppendInstr(I_FIADD, 0xDE, 0, Imm8(0), dst);
            }
            void fiadd(const Mem32& dst)
            {
                AppendInstr(I_FIADD, 0xDA, 0, Imm8(0), dst);
            }
            void fbld(const Mem80& dst)
            {
                AppendInstr(I_FBLD, 0xDF, 0, Imm8(4), dst);
            }
            void fbstp(const Mem80& dst)
            {
                AppendInstr(I_FBSTP, 0xDF, 0, Imm8(6), dst);
            }
            void fchs()
            {
                AppendInstr(I_FCHS, 0xD9E0, 0);
            }
            void fclex()
            {
                AppendInstr(I_FCLEX, 0x9BDBE2, 0);
            }
            void fnclex()
            {
                AppendInstr(I_FNCLEX, 0xDBE2, 0);
            }
            void fcmovb(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCMOVCC, 0xDAC0, 0, src); avoid_unused_warn(dst);
            }
            void fcmovbe(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCMOVCC, 0xDAD0, 0, src); avoid_unused_warn(dst);
            }
            void fcmove(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCMOVCC, 0xDAC8, 0, src); avoid_unused_warn(dst);
            }
            void fcmovnb(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCMOVCC, 0xDBC0, 0, src); avoid_unused_warn(dst);
            }
            void fcmovnbe(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCMOVCC, 0xDBD0, 0, src); avoid_unused_warn(dst);
            }
            void fcmovne(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCMOVCC, 0xDBC8, 0, src); avoid_unused_warn(dst);
            }
            void fcmovnu(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCMOVCC, 0xDBD8, 0, src); avoid_unused_warn(dst);
            }
            void fcmovu(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCMOVCC, 0xDAD8, 0, src); avoid_unused_warn(dst);
            }
            void fcom()
            {
                AppendInstr(I_FCOM, 0xD8D1, 0);
            }
            void fcom(const FpuReg& dst)
            {
                AppendInstr(I_FCOM, 0xD8D0, 0, dst);
            }
            void fcom(const Mem32& dst)
            {
                AppendInstr(I_FCOM, 0xD8, 0, Imm8(2), dst);
            }
            void fcom(const Mem64& dst)
            {
                AppendInstr(I_FCOM, 0xDC, 0, Imm8(2), dst);
            }
            void fcomp()
            {
                AppendInstr(I_FCOMP, 0xD8D9, 0);
            }
            void fcomp(const FpuReg& dst)
            {
                AppendInstr(I_FCOMP, 0xD8D8, 0, dst);
            }
            void fcomp(const Mem32& dst)
            {
                AppendInstr(I_FCOMP, 0xD8, 0, Imm8(3), dst);
            }
            void fcomp(const Mem64& dst)
            {
                AppendInstr(I_FCOMP, 0xDC, 0, Imm8(3), dst);
            }
            void fcompp()
            {
                AppendInstr(I_FCOMPP, 0xDED9, 0);
            }
            void fcomi(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCOMI, 0xDBF0, 0, src); avoid_unused_warn(dst);
            }
            void fcomip(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FCOMIP, 0xDFF0, 0, src); avoid_unused_warn(dst);
            }
            void fcos()
            {
                AppendInstr(I_FCOS, 0xD9FF, 0);
            }
            void fdecstp()
            {
                AppendInstr(I_FDECSTP, 0xD9F6, 0);
            }
            void fdiv(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FDIV, 0xD8F0, 0, src); avoid_unused_warn(dst);
            }
            void fdiv(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FDIV, 0xDCF8, 0, dst); avoid_unused_warn(src);
            }
            void fdiv(const Mem32& dst)
            {
                AppendInstr(I_FDIV, 0xD8, 0, Imm8(6), dst);
            }
            void fdiv(const Mem64& dst)
            {
                AppendInstr(I_FDIV, 0xDC, 0, Imm8(6), dst);
            }
            void fdivp()
            {
                AppendInstr(I_FDIVP, 0xDEF9, 0);
            }
            void fdivp(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FDIVP, 0xDEF8, 0, dst); avoid_unused_warn(src);
            }
            void fidiv(const Mem16& dst)
            {
                AppendInstr(I_FIDIV, 0xDE, 0, Imm8(6), dst);
            }
            void fidiv(const Mem32& dst)
            {
                AppendInstr(I_FIDIV, 0xDA, 0, Imm8(6), dst);
            }
            void fdivr(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FDIVR, 0xD8F8, 0, src); avoid_unused_warn(dst);
            }
            void fdivr(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FDIVR, 0xDCF0, 0, dst); avoid_unused_warn(src);
            }
            void fdivr(const Mem32& dst)
            {
                AppendInstr(I_FDIVR, 0xD8, 0, Imm8(7), dst);
            }
            void fdivr(const Mem64& dst)
            {
                AppendInstr(I_FDIVR, 0xDC, 0, Imm8(7), dst);
            }
            void fdivrp()
            {
                AppendInstr(I_FDIVRP, 0xDEF1, 0);
            }
            void fdivrp(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FDIVRP, 0xDEF0, 0, dst); avoid_unused_warn(src);
            }
            void fidivr(const Mem16& dst)
            {
                AppendInstr(I_FIDIVR, 0xDE, 0, Imm8(7), dst);
            }
            void fidivr(const Mem32& dst)
            {
                AppendInstr(I_FIDIVR, 0xDA, 0, Imm8(7), dst);
            }
            void ffree(const FpuReg& dst)
            {
                AppendInstr(I_FFREE, 0xDDC0, 0, dst);
            }
            void ficom(const Mem16& dst)
            {
                AppendInstr(I_FICOM, 0xDE, 0, Imm8(2), dst);
            }
            void ficom(const Mem32& dst)
            {
                AppendInstr(I_FICOM, 0xDA, 0, Imm8(2), dst);
            }
            void ficomp(const Mem16& dst)
            {
                AppendInstr(I_FICOMP, 0xDE, 0, Imm8(3), dst);
            }
            void ficomp(const Mem32& dst)
            {
                AppendInstr(I_FICOMP, 0xDA, 0, Imm8(3), dst);
            }
            void fild(const Mem16& dst)
            {
                AppendInstr(I_FILD, 0xDF, 0, Imm8(0), dst);
            }
            void fild(const Mem32& dst)
            {
                AppendInstr(I_FILD, 0xDB, 0, Imm8(0), dst);
            }
            void fild(const Mem64& dst)
            {
                AppendInstr(I_FILD, 0xDF, 0, Imm8(5), dst);
            }
            void fincstp()
            {
                AppendInstr(I_FINCSTP, 0xD9F7, 0);
            }
            void finit()
            {
                AppendInstr(I_FINIT, 0x9BDBE3, 0);
            }
            void fninit()
            {
                AppendInstr(I_FNINIT, 0xDBE3, 0);
            }
            void fist(const Mem16& dst)
            {
                AppendInstr(I_FIST, 0xDF, 0, Imm8(2), dst);
            }
            void fist(const Mem32& dst)
            {
                AppendInstr(I_FIST, 0xDB, 0, Imm8(2), dst);
            }
            void fistp(const Mem16& dst)
            {
                AppendInstr(I_FISTP, 0xDF, 0, Imm8(3), dst);
            }
            void fistp(const Mem32& dst)
            {
                AppendInstr(I_FISTP, 0xDB, 0, Imm8(3), dst);
            }
            void fistp(const Mem64& dst)
            {
                AppendInstr(I_FISTP, 0xDF, 0, Imm8(7), dst);
            }
            void fisttp(const Mem16& dst)
            {
                AppendInstr(I_FISTP, 0xDF, 0, Imm8(1), dst);
            }
            void fisttp(const Mem32& dst)
            {
                AppendInstr(I_FISTP, 0xDB, 0, Imm8(1), dst);
            }
            void fisttp(const Mem64& dst)
            {
                AppendInstr(I_FISTP, 0xDD, 0, Imm8(1), dst);
            }
            void fld(const Mem32& src)
            {
                AppendInstr(I_FLD, 0xD9, 0, Imm8(0), src);
            }
            void fld(const Mem64& src)
            {
                AppendInstr(I_FLD, 0xDD, 0, Imm8(0), src);
            }
            void fld(const Mem80& src)
            {
                AppendInstr(I_FLD, 0xDB, 0, Imm8(5), src);
            }
            void fld(const FpuReg& src)
            {
                AppendInstr(I_FLD, 0xD9C0, 0, src);
            }
            void fld1()
            {
                AppendInstr(I_FLD1, 0xD9E8, 0);
            }
            void fldcw(const Mem16& src)
            {
                AppendInstr(I_FLDCW, 0xD9, 0, Imm8(5), src);
            }
            void fldenv(const Mem224& src)
            {
                AppendInstr(I_FLDENV, 0xD9, 0, Imm8(4), src);
            }
            void fldl2e()
            {
                AppendInstr(I_FLDL2E, 0xD9EA, 0);
            }
            void fldl2t()
            {
                AppendInstr(I_FLDL2T, 0xD9E9, 0);
            }
            void fldlg2()
            {
                AppendInstr(I_FLDLG2, 0xD9EC, 0);
            }
            void fldln2()
            {
                AppendInstr(I_FLDLN2, 0xD9ED, 0);
            }
            void fldpi()
            {
                AppendInstr(I_FLDPI, 0xD9EB, 0);
            }
            void fldz()
            {
                AppendInstr(I_FLDZ, 0xD9EE, 0);
            }
            void fmul(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FMUL, 0xD8C8, 0, src); avoid_unused_warn(dst);
            }
            void fmul(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FMUL, 0xDCC8, 0, dst); avoid_unused_warn(src);
            }
            void fmul(const Mem32& dst)
            {
                AppendInstr(I_FMUL, 0xD8, 0, Imm8(1), dst);
            }
            void fmul(const Mem64& dst)
            {
                AppendInstr(I_FMUL, 0xDC, 0, Imm8(1), dst);
            }
            void fmulp()
            {
                AppendInstr(I_FMULP, 0xDEC9, 0);
            }
            void fmulp(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FMULP, 0xDEC8, 0, dst); avoid_unused_warn(src);
            }
            void fimul(const Mem16& dst)
            {
                AppendInstr(I_FIMUL, 0xDE, 0, Imm8(1), dst);
            }
            void fimul(const Mem32& dst)
            {
                AppendInstr(I_FIMUL, 0xDA, 0, Imm8(1), dst);
            }
            void fnop()
            {
                AppendInstr(I_FNOP, 0xD9D0, 0);
            }
            void fpatan()
            {
                AppendInstr(I_FPATAN, 0xD9F3, 0);
            }
            void fprem()
            {
                AppendInstr(I_FPREM, 0xD9F8, 0);
            }
            void fprem1()
            {
                AppendInstr(I_FPREM1, 0xD9F5, 0);
            }
            void fptan()
            {
                AppendInstr(I_FPTAN, 0xD9F2, 0);
            }
            void frndint()
            {
                AppendInstr(I_FRNDINT, 0xD9FC, 0);
            }
            void frstor(const Mem864& src)
            {
                AppendInstr(I_FRSTOR, 0xDD, 0, Imm8(4), src);
            }
            void fsave(const Mem864& dst)
            {
                AppendInstr(I_FSAVE, 0x9BDD, 0, Imm8(6), dst);
            }
            void fnsave(const Mem864& dst)
            {
                AppendInstr(I_FNSAVE, 0xDD, 0, Imm8(6), dst);
            }
            void fscale()
            {
                AppendInstr(I_FSCALE, 0xD9FD, 0);
            }
            void fsin()
            {
                AppendInstr(I_FSIN, 0xD9FE, 0);
            }
            void fsincos()
            {
                AppendInstr(I_FSINCOS, 0xD9FB, 0);
            }
            void fsqrt()
            {
                AppendInstr(I_FSQRT, 0xD9FA, 0);
            }
            void fst(const Mem32& dst)
            {
                AppendInstr(I_FST, 0xD9, 0, Imm8(2), dst);
            }
            void fst(const Mem64& dst)
            {
                AppendInstr(I_FST, 0xDD, 0, Imm8(2), dst);
            }
            void fst(const FpuReg& dst)
            {
                AppendInstr(I_FST, 0xDDD0, 0, dst);
            }
            void fstp(const FpuReg& dst)
            {
                AppendInstr(I_FSTP, 0xDDD8, 0, dst);
            }
            void fstp(const Mem32& dst)
            {
                AppendInstr(I_FSTP, 0xD9, 0, Imm8(3), dst);
            }
            void fstp(const Mem64& dst)
            {
                AppendInstr(I_FSTP, 0xDD, 0, Imm8(3), dst);
            }
            void fstp(const Mem80& dst)
            {
                AppendInstr(I_FSTP, 0xDB, 0, Imm8(7), dst);
            }
            void fstcw(const Mem16& dst)
            {
                AppendInstr(I_FSTCW, 0x9BD9, 0, Imm8(7), dst);
            }
            void fnstcw(const Mem16& dst)
            {
                AppendInstr(I_FNSTCW, 0xD9, 0, Imm8(7), dst);
            }
            void fstenv(const Mem224& dst)
            {
                AppendInstr(I_FSTENV, 0x9BD9, 0, Imm8(6), dst);
            }
            void fnstenv(const Mem224& dst)
            {
                AppendInstr(I_FNSTENV, 0xD9, 0, Imm8(6), dst);
            }
            void fstsw(const Mem16& dst)
            {
                AppendInstr(I_FSTSW, 0x9BDD, 0, Imm8(7), dst);
            }
            void fstsw(const Reg16& dst)
            {
                AppendInstr(I_FSTSW, 0x9BDFE0, 0, Dummy(W(dst), ax));
            }
            void fnstsw(const Mem16& dst)
            {
                AppendInstr(I_FNSTSW, 0xDD, 0, Imm8(7), dst);
            }
            void fnstsw(const Reg16& dst)
            {
                AppendInstr(I_FNSTSW, 0xDFE0, 0, Dummy(W(dst), ax));
            }
            void fsub(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FSUB, 0xD8E0, 0, src); avoid_unused_warn(dst);
            }
            void fsub(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FSUB, 0xDCE8, 0, dst); avoid_unused_warn(src);
            }
            void fsub(const Mem32& dst)
            {
                AppendInstr(I_FSUB, 0xD8, 0, Imm8(4), dst);
            }
            void fsub(const Mem64& dst)
            {
                AppendInstr(I_FSUB, 0xDC, 0, Imm8(4), dst);
            }
            void fsubp()
            {
                AppendInstr(I_FSUBP, 0xDEE9, 0);
            }
            void fsubp(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FSUBP, 0xDEE8, 0, dst); avoid_unused_warn(src);
            }
            void fisub(const Mem16& dst)
            {
                AppendInstr(I_FISUB, 0xDE, 0, Imm8(4), dst);
            }
            void fisub(const Mem32& dst)
            {
                AppendInstr(I_FISUB, 0xDA, 0, Imm8(4), dst);
            }
            void fsubr(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FSUBR, 0xD8E8, 0, src); avoid_unused_warn(dst);
            }
            void fsubr(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FSUBR, 0xDCE0, 0, dst); avoid_unused_warn(src);
            }
            void fsubr(const Mem32& dst)
            {
                AppendInstr(I_FSUBR, 0xD8, 0, Imm8(5), dst);
            }
            void fsubr(const Mem64& dst)
            {
                AppendInstr(I_FSUBR, 0xDC, 0, Imm8(5), dst);
            }
            void fsubrp()
            {
                AppendInstr(I_FSUBRP, 0xDEE1, 0);
            }
            void fsubrp(const FpuReg& dst, const FpuReg_st0& src)
            {
                AppendInstr(I_FSUBRP, 0xDEE0, 0, dst); avoid_unused_warn(src);
            }
            void fisubr(const Mem16& dst)
            {
                AppendInstr(I_FISUBR, 0xDE, 0, Imm8(5), dst);
            }
            void fisubr(const Mem32& dst)
            {
                AppendInstr(I_FISUBR, 0xDA, 0, Imm8(5), dst);
            }
            void ftst()
            {
                AppendInstr(I_FTST, 0xD9E4, 0);
            }
            void fucom()
            {
                AppendInstr(I_FUCOM, 0xDDE1, 0);
            }
            void fucom(const FpuReg& dst)
            {
                AppendInstr(I_FUCOM, 0xDDE0, 0, dst);
            }
            void fucomp()
            {
                AppendInstr(I_FUCOMP, 0xDDE9, 0);
            }
            void fucomp(const FpuReg& dst)
            {
                AppendInstr(I_FUCOMP, 0xDDE8, 0, dst);
            }
            void fucompp()
            {
                AppendInstr(I_FUCOMPP, 0xDAE9, 0);
            }
            void fucomi(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FUCOMI, 0xDBE8, 0, src); avoid_unused_warn(dst);
            }
            void fucomip(const FpuReg_st0& dst, const FpuReg& src)
            {
                AppendInstr(I_FUCOMIP, 0xDFE8, 0, src); avoid_unused_warn(dst);
            }
            void fwait()
            {
                wait();
            }
            void fxam()
            {
                AppendInstr(I_FXAM, 0xD9E5, 0);
            }
            void fxch()
            {
                AppendInstr(I_FXCH, 0xD9C9, 0);
            }
            void fxch(const FpuReg& dst)
            {
                AppendInstr(I_FXCH, 0xD9C8, 0, dst);
            }
            void fxrstor(const Mem4096& src)
            {
                AppendInstr(I_FXRSTOR, 0x0FAE, 0, Imm8(1), src);
            }
            void fxsave(const Mem4096& dst)
            {
                AppendInstr(I_FXSAVE, 0x0FAE, 0, Imm8(0), dst);
            }
            void fxtract()
            {
                AppendInstr(I_FXTRACT, 0xD9F4, 0);
            }
            void fyl2x()
            {
                AppendInstr(I_FYL2X, 0xD9F1, 0);
            }
            void fyl2xp1()
            {
                AppendInstr(I_FYL2XP1, 0xD9F9, 0);
            }

            // MMX
            void emms()
            {
                AppendInstr(I_EMMS, 0x0F77, 0);
            }
            void movd(const MmxReg& dst, const Reg32& src)
            {
                AppendInstr(I_MOVD, 0x0F6E, 0, W(dst), R(src));
            }
            void movd(const MmxReg& dst, const Mem32& src)
            {
                AppendInstr(I_MOVD, 0x0F6E, 0, W(dst), R(src));
            }
            void movd(const Reg32& dst, const MmxReg& src)
            {
                AppendInstr(I_MOVD, 0x0F7E, 0, R(src), W(dst));
            }
            void movd(const Mem32& dst, const MmxReg& src)
            {
                AppendInstr(I_MOVD, 0x0F7E, 0, R(src), W(dst));
            }
            void movd(const MmxReg& dst, const Reg64& src)
            {
                AppendInstr(I_MOVD, 0x0F6E, E_REXW_PREFIX, W(dst), R(src));
            }
            void movd(const Reg64& dst, const MmxReg& src)
            {
                AppendInstr(I_MOVD, 0x0F7E, E_REXW_PREFIX, R(src), W(dst));
            }
            void movq(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVQ, 0x0F6F, 0, W(dst), R(src));
            }
            void movq(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_MOVQ, 0x0F7F, 0, R(src), W(dst));
            }
            void movq(const Mem64& dst, const MmxReg& src)
            {
                AppendInstr(I_MOVQ, 0x0F7F, 0, R(src), W(dst));
            }
            void movq(const MmxReg& dst, const Reg64& src)
            {
                movd(dst, src);
            }
            void movq(const Reg64& dst, const MmxReg& src)
            {
                movd(dst, src);
            }
            void packsswb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PACKSSWB, 0x0F63, 0, RW(dst), R(src));
            }
            void packsswb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PACKSSWB, 0x0F63, 0, RW(dst), R(src));
            }
            void packssdw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PACKSSDW, 0x0F6B, 0, RW(dst), R(src));
            }
            void packssdw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PACKSSDW, 0x0F6B, 0, RW(dst), R(src));
            }
            void packuswb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PACKUSWB, 0x0F67, 0, RW(dst), R(src));
            }
            void packuswb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PACKUSWB, 0x0F67, 0, RW(dst), R(src));
            }
            void paddb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PADDB, 0x0FFC, 0, RW(dst), R(src));
            }
            void paddb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PADDB, 0x0FFC, 0, RW(dst), R(src));
            }
            void paddw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PADDW, 0x0FFD, 0, RW(dst), R(src));
            }
            void paddw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PADDW, 0x0FFD, 0, RW(dst), R(src));
            }
            void paddd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PADDD, 0x0FFE, 0, RW(dst), R(src));
            }
            void paddd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PADDD, 0x0FFE, 0, RW(dst), R(src));
            }
            void paddsb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PADDSB, 0x0FEC, 0, RW(dst), R(src));
            }
            void paddsb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PADDSB, 0x0FEC, 0, RW(dst), R(src));
            }
            void paddsw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PADDSW, 0x0FED, 0, RW(dst), R(src));
            }
            void paddsw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PADDSW, 0x0FED, 0, RW(dst), R(src));
            }
            void paddusb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PADDUSB, 0x0FDC, 0, RW(dst), R(src));
            }
            void paddusb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PADDUSB, 0x0FDC, 0, RW(dst), R(src));
            }
            void paddusw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PADDUSW, 0x0FDD, 0, RW(dst), R(src));
            }
            void paddusw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PADDUSW, 0x0FDD, 0, RW(dst), R(src));
            }
            void pand(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PAND, 0x0FDB, 0, RW(dst), R(src));
            }
            void pand(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PAND, 0x0FDB, 0, RW(dst), R(src));
            }
            void pandn(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PANDN, 0x0FDF, 0, RW(dst), R(src));
            }
            void pandn(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PANDN, 0x0FDF, 0, RW(dst), R(src));
            }
            void pcmpeqb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PCMPEQB, 0x0F74, 0, RW(dst), R(src));
            }
            void pcmpeqb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PCMPEQB, 0x0F74, 0, RW(dst), R(src));
            }
            void pcmpeqw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PCMPEQW, 0x0F75, 0, RW(dst), R(src));
            }
            void pcmpeqw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PCMPEQW, 0x0F75, 0, RW(dst), R(src));
            }
            void pcmpeqd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PCMPEQD, 0x0F76, 0, RW(dst), R(src));
            }
            void pcmpeqd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PCMPEQD, 0x0F76, 0, RW(dst), R(src));
            }
            void pcmpgtb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PCMPGTB, 0x0F64, 0, RW(dst), R(src));
            }
            void pcmpgtb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PCMPGTB, 0x0F64, 0, RW(dst), R(src));
            }
            void pcmpgtw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PCMPGTW, 0x0F65, 0, RW(dst), R(src));
            }
            void pcmpgtw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PCMPGTW, 0x0F65, 0, RW(dst), R(src));
            }
            void pcmpgtd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PCMPGTD, 0x0F66, 0, RW(dst), R(src));
            }
            void pcmpgtd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PCMPGTD, 0x0F66, 0, RW(dst), R(src));
            }
            void pmaddwd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMADDWD, 0x0FF5, 0, RW(dst), R(src));
            }
            void pmaddwd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMADDWD, 0x0FF5, 0, RW(dst), R(src));
            }
            void pmulhw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMULHW, 0x0FE5, 0, RW(dst), R(src));
            }
            void pmulhw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMULHW, 0x0FE5, 0, RW(dst), R(src));
            }
            void pmullw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMULLW, 0x0FD5, 0, RW(dst), R(src));
            }
            void pmullw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMULLW, 0x0FD5, 0, RW(dst), R(src));
            }
            void por(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_POR, 0x0FEB, 0, RW(dst), R(src));
            }
            void por(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_POR, 0x0FEB, 0, RW(dst), R(src));
            }
            void psllw(const MmxReg& dst, const MmxReg& count)
            {
                AppendInstr(I_PSLLW, 0x0FF1, 0, RW(dst), R(count));
            }
            void psllw(const MmxReg& dst, const Mem64& count)
            {
                AppendInstr(I_PSLLW, 0x0FF1, 0, RW(dst), R(count));
            }
            void psllw(const MmxReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSLLW, 0x0F71, 0, Imm8(6), RW(dst), count);
            }
            void pslld(const MmxReg& dst, const MmxReg& count)
            {
                AppendInstr(I_PSLLD, 0x0FF2, 0, RW(dst), R(count));
            }
            void pslld(const MmxReg& dst, const Mem64& count)
            {
                AppendInstr(I_PSLLD, 0x0FF2, 0, RW(dst), R(count));
            }
            void pslld(const MmxReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSLLD, 0x0F72, 0, Imm8(6), RW(dst), count);
            }
            void psllq(const MmxReg& dst, const MmxReg& count)
            {
                AppendInstr(I_PSLLQ, 0x0FF3, 0, RW(dst), R(count));
            }
            void psllq(const MmxReg& dst, const Mem64& count)
            {
                AppendInstr(I_PSLLQ, 0x0FF3, 0, RW(dst), R(count));
            }
            void psllq(const MmxReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSLLQ, 0x0F73, 0, Imm8(6), RW(dst), count);
            }
            void psraw(const MmxReg& dst, const MmxReg& count)
            {
                AppendInstr(I_PSRAW, 0x0FE1, 0, RW(dst), R(count));
            }
            void psraw(const MmxReg& dst, const Mem64& count)
            {
                AppendInstr(I_PSRAW, 0x0FE1, 0, RW(dst), R(count));
            }
            void psraw(const MmxReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRAW, 0x0F71, 0, Imm8(4), RW(dst), count);
            }
            void psrad(const MmxReg& dst, const MmxReg& count)
            {
                AppendInstr(I_PSRAD, 0x0FE2, 0, RW(dst), R(count));
            }
            void psrad(const MmxReg& dst, const Mem64& count)
            {
                AppendInstr(I_PSRAD, 0x0FE2, 0, RW(dst), R(count));
            }
            void psrad(const MmxReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRAD, 0x0F72, 0, Imm8(4), RW(dst), count);
            }
            void psrlw(const MmxReg& dst, const MmxReg& count)
            {
                AppendInstr(I_PSRLW, 0x0FD1, 0, RW(dst), R(count));
            }
            void psrlw(const MmxReg& dst, const Mem64& count)
            {
                AppendInstr(I_PSRLW, 0x0FD1, 0, RW(dst), R(count));
            }
            void psrlw(const MmxReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRLW, 0x0F71, 0, Imm8(2), RW(dst), count);
            }
            void psrld(const MmxReg& dst, const MmxReg& count)
            {
                AppendInstr(I_PSRLD, 0x0FD2, 0, RW(dst), R(count));
            }
            void psrld(const MmxReg& dst, const Mem64& count)
            {
                AppendInstr(I_PSRLD, 0x0FD2, 0, RW(dst), R(count));
            }
            void psrld(const MmxReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRLD, 0x0F72, 0, Imm8(2), RW(dst), count);
            }
            void psrlq(const MmxReg& dst, const MmxReg& count)
            {
                AppendInstr(I_PSRLQ, 0x0FD3, 0, RW(dst), R(count));
            }
            void psrlq(const MmxReg& dst, const Mem64& count)
            {
                AppendInstr(I_PSRLQ, 0x0FD3, 0, RW(dst), R(count));
            }
            void psrlq(const MmxReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRLQ, 0x0F73, 0, Imm8(2), RW(dst), count);
            }
            void psubb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSUBB, 0x0FF8, 0, RW(dst), R(src));
            }
            void psubb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSUBB, 0x0FF8, 0, RW(dst), R(src));
            }
            void psubw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSUBW, 0x0FF9, 0, RW(dst), R(src));
            }
            void psubw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSUBW, 0x0FF9, 0, RW(dst), R(src));
            }
            void psubd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSUBD, 0x0FFA, 0, RW(dst), R(src));
            }
            void psubd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSUBD, 0x0FFA, 0, RW(dst), R(src));
            }
            void psubsb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSUBSB, 0x0FE8, 0, RW(dst), R(src));
            }
            void psubsb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSUBSB, 0x0FE8, 0, RW(dst), R(src));
            }
            void psubsw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSUBSW, 0x0FE9, 0, RW(dst), R(src));
            }
            void psubsw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSUBSW, 0x0FE9, 0, RW(dst), R(src));
            }
            void psubusb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSUBUSB, 0x0FD8, 0, RW(dst), R(src));
            }
            void psubusb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSUBUSB, 0x0FD8, 0, RW(dst), R(src));
            }
            void psubusw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSUBUSW, 0x0FD9, 0, RW(dst), R(src));
            }
            void psubusw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSUBUSW, 0x0FD9, 0, RW(dst), R(src));
            }
            void punpckhbw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PUNPCKHBW, 0x0F68, 0, RW(dst), R(src));
            }
            void punpckhbw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PUNPCKHBW, 0x0F68, 0, RW(dst), R(src));
            }
            void punpckhwd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PUNPCKHWD, 0x0F69, 0, RW(dst), R(src));
            }
            void punpckhwd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PUNPCKHWD, 0x0F69, 0, RW(dst), R(src));
            }
            void punpckhdq(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PUNPCKHDQ, 0x0F6A, 0, RW(dst), R(src));
            }
            void punpckhdq(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PUNPCKHDQ, 0x0F6A, 0, RW(dst), R(src));
            }
            void punpcklbw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PUNPCKLBW, 0x0F60, 0, RW(dst), R(src));
            }
            void punpcklbw(const MmxReg& dst, const Mem32& src)
            {
                AppendInstr(I_PUNPCKLBW, 0x0F60, 0, RW(dst), R(src));
            }
            void punpcklwd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PUNPCKLWD, 0x0F61, 0, RW(dst), R(src));
            }
            void punpcklwd(const MmxReg& dst, const Mem32& src)
            {
                AppendInstr(I_PUNPCKLWD, 0x0F61, 0, RW(dst), R(src));
            }
            void punpckldq(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PUNPCKLDQ, 0x0F62, 0, RW(dst), R(src));
            }
            void punpckldq(const MmxReg& dst, const Mem32& src)
            {
                AppendInstr(I_PUNPCKLDQ, 0x0F62, 0, RW(dst), R(src));
            }
            void pxor(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PXOR, 0x0FEF, 0, RW(dst), R(src));
            }
            void pxor(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PXOR, 0x0FEF, 0, RW(dst), R(src));
            }

            // MMX2
            void pavgb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PAVGB, 0x0FE0, 0, RW(dst), R(src));
            }
            void pavgb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PAVGB, 0x0FE0, 0, RW(dst), R(src));
            }
            void pavgw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PAVGW, 0x0FE3, 0, RW(dst), R(src));
            }
            void pavgw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PAVGW, 0x0FE3, 0, RW(dst), R(src));
            }
            void pextrw(const Reg32& dst, const MmxReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRW, 0x0FC5, 0, W(dst), R(src), i);
            }
            void pextrw(const Reg64& dst, const MmxReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRW, 0x0FC5, E_REXW_PREFIX, W(dst), R(src), i);
            }
            void pinsrw(const MmxReg& dst, const Reg32& src, const Imm8& i)
            {
                AppendInstr(I_PINSRW, 0x0FC4, 0, RW(dst), R(src), i);
            }
            void pinsrw(const MmxReg& dst, const Mem16& src, const Imm8& i)
            {
                AppendInstr(I_PINSRW, 0x0FC4, 0, RW(dst), R(src), i);
            }
            void pinsrw(const MmxReg& dst, const Reg64& src, const Imm8& i)
            {
                AppendInstr(I_PINSRW, 0x0FC4, E_REXW_PREFIX, RW(dst), R(src), i);
            }
            void pmaxsw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMAXSW, 0x0FEE, 0, RW(dst), R(src));
            }
            void pmaxsw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMAXSW, 0x0FEE, 0, RW(dst), R(src));
            }
            void pmaxub(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMAXUB, 0x0FDE, 0, RW(dst), R(src));
            }
            void pmaxub(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMAXUB, 0x0FDE, 0, RW(dst), R(src));
            }
            void pminsw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMINSW, 0x0FEA, 0, RW(dst), R(src));
            }
            void pminsw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMINSW, 0x0FEA, 0, RW(dst), R(src));
            }
            void pminub(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMINUB, 0x0FDA, 0, RW(dst), R(src));
            }
            void pminub(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMINUB, 0x0FDA, 0, RW(dst), R(src));
            }
            void pmovmskb(const Reg32& dst, const MmxReg& src)
            {
                AppendInstr(I_PMOVMSKB, 0x0FD7, 0, W(dst), R(src));
            }
            void pmovmskb(const Reg64& dst, const MmxReg& src)
            {
                AppendInstr(I_PMOVMSKB, 0x0FD7, E_REXW_PREFIX, W(dst), R(src));
            }
            void pmulhuw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMULHUW, 0x0FE4, 0, RW(dst), R(src));
            }
            void pmulhuw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMULHUW, 0x0FE4, 0, RW(dst), R(src));
            }
            void psadbw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSADBW, 0x0FF6, 0, RW(dst), R(src));
            }
            void psadbw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSADBW, 0x0FF6, 0, RW(dst), R(src));
            }
            void pshufw(const MmxReg& dst, const MmxReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFW, 0x0F70, 0, RW(dst), R(src), order);
            }
            void pshufw(const MmxReg& dst, const Mem64& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFW, 0x0F70, 0, RW(dst), R(src), order);
            }

            // SSE
            void addps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ADDPS, 0x0F58, 0, RW(dst), R(src));
            }
            void addps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ADDPS, 0x0F58, 0, RW(dst), R(src));
            }
            void addss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ADDSS, 0x0F58, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void addss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_ADDSS, 0x0F58, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void andps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ANDPS, 0x0F54, 0, RW(dst), R(src));
            }
            void andps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ANDPS, 0x0F54, 0, RW(dst), R(src));
            }
            void andnps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ANDNPS, 0x0F55, 0, RW(dst), R(src));
            }
            void andnps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ANDNPS, 0x0F55, 0, RW(dst), R(src));
            }
            void cmpps(const XmmReg& dst, const XmmReg& src, const Imm8& opd3)
            {
                AppendInstr(I_CMPPS, 0x0FC2, 0, RW(dst), R(src), opd3);
            }
            void cmpps(const XmmReg& dst, const Mem128& src, const Imm8& opd3)
            {
                AppendInstr(I_CMPPS, 0x0FC2, 0, RW(dst), R(src), opd3);
            }
            void cmpeqps(const XmmReg& dst, const XmmReg& src)
            {
                cmpps(dst, src, 0);
            }
            void cmpeqps(const XmmReg& dst, const Mem128& src)
            {
                cmpps(dst, src, 0);
            }
            void cmpltps(const XmmReg& dst, const XmmReg& src)
            {
                cmpps(dst, src, 1);
            }
            void cmpltps(const XmmReg& dst, const Mem128& src)
            {
                cmpps(dst, src, 1);
            }
            void cmpleps(const XmmReg& dst, const XmmReg& src)
            {
                cmpps(dst, src, 2);
            }
            void cmpleps(const XmmReg& dst, const Mem128& src)
            {
                cmpps(dst, src, 2);
            }
            void cmpunordps(const XmmReg& dst, const XmmReg& src)
            {
                cmpps(dst, src, 3);
            }
            void cmpunordps(const XmmReg& dst, const Mem128& src)
            {
                cmpps(dst, src, 3);
            }
            void cmpneqps(const XmmReg& dst, const XmmReg& src)
            {
                cmpps(dst, src, 4);
            }
            void cmpneqps(const XmmReg& dst, const Mem128& src)
            {
                cmpps(dst, src, 4);
            }
            void cmpnltps(const XmmReg& dst, const XmmReg& src)
            {
                cmpps(dst, src, 5);
            }
            void cmpnltps(const XmmReg& dst, const Mem128& src)
            {
                cmpps(dst, src, 5);
            }
            void cmpnleps(const XmmReg& dst, const XmmReg& src)
            {
                cmpps(dst, src, 6);
            }
            void cmpnleps(const XmmReg& dst, const Mem128& src)
            {
                cmpps(dst, src, 6);
            }
            void cmpordps(const XmmReg& dst, const XmmReg& src)
            {
                cmpps(dst, src, 7);
            }
            void cmpordps(const XmmReg& dst, const Mem128& src)
            {
                cmpps(dst, src, 7);
            }
            void cmpss(const XmmReg& dst, const XmmReg& src, const Imm8& opd3)
            {
                AppendInstr(I_CMPSS, 0x0FC2, E_MANDATORY_PREFIX_F3, RW(dst), R(src), opd3);
            }
            void cmpss(const XmmReg& dst, const Mem32& src, const Imm8& opd3)
            {
                AppendInstr(I_CMPSS, 0x0FC2, E_MANDATORY_PREFIX_F3, RW(dst), R(src), opd3);
            }
            void cmpeqss(const XmmReg& dst, const XmmReg& src)
            {
                cmpss(dst, src, 0);
            }
            void cmpeqss(const XmmReg& dst, const Mem32& src)
            {
                cmpss(dst, src, 0);
            }
            void cmpltss(const XmmReg& dst, const XmmReg& src)
            {
                cmpss(dst, src, 1);
            }
            void cmpltss(const XmmReg& dst, const Mem32& src)
            {
                cmpss(dst, src, 1);
            }
            void cmpless(const XmmReg& dst, const XmmReg& src)
            {
                cmpss(dst, src, 2);
            }
            void cmpless(const XmmReg& dst, const Mem32& src)
            {
                cmpss(dst, src, 2);
            }
            void cmpunordss(const XmmReg& dst, const XmmReg& src)
            {
                cmpss(dst, src, 3);
            }
            void cmpunordss(const XmmReg& dst, const Mem32& src)
            {
                cmpss(dst, src, 3);
            }
            void cmpneqss(const XmmReg& dst, const XmmReg& src)
            {
                cmpss(dst, src, 4);
            }
            void cmpneqss(const XmmReg& dst, const Mem32& src)
            {
                cmpss(dst, src, 4);
            }
            void cmpnltss(const XmmReg& dst, const XmmReg& src)
            {
                cmpss(dst, src, 5);
            }
            void cmpnltss(const XmmReg& dst, const Mem32& src)
            {
                cmpss(dst, src, 5);
            }
            void cmpnless(const XmmReg& dst, const XmmReg& src)
            {
                cmpss(dst, src, 6);
            }
            void cmpnless(const XmmReg& dst, const Mem32& src)
            {
                cmpss(dst, src, 6);
            }
            void cmpordss(const XmmReg& dst, const XmmReg& src)
            {
                cmpss(dst, src, 7);
            }
            void cmpordss(const XmmReg& dst, const Mem32& src)
            {
                cmpss(dst, src, 7);
            }
            void comiss(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_COMISS, 0x0F2F, 0, R(src1), R(src2));
            }
            void comiss(const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_COMISS, 0x0F2F, 0, R(src1), R(src2));
            }
            void cvtpi2ps(const XmmReg& dst, const MmxReg& src)
            {
                AppendInstr(I_CVTPI2PS, 0x0F2A, 0, RW(dst), R(src));
            }
            void cvtpi2ps(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTPI2PS, 0x0F2A, 0, RW(dst), R(src));
            }
            void cvtps2pi(const MmxReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPS2PI, 0x0F2D, 0, W(dst), R(src));
            }
            void cvtps2pi(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTPS2PI, 0x0F2D, 0, W(dst), R(src));
            }
            void cvtsi2ss(const XmmReg& dst, const Reg32& src)
            {
                AppendInstr(I_CVTSI2SS, 0x0F2A, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void cvtsi2ss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_CVTSI2SS, 0x0F2A, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void cvtss2si(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSS2SI, 0x0F2D, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void cvtss2si(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CVTSS2SI, 0x0F2D, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void cvttps2pi(const MmxReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTPS2PI, 0x0F2C, 0, W(dst), R(src));
            }
            void cvttps2pi(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTTPS2PI, 0x0F2C, 0, W(dst), R(src));
            }
            void cvttss2si(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTSS2SI, 0x0F2C, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void cvttss2si(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CVTTSS2SI, 0x0F2C, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void cvtsi2ss(const XmmReg& dst, const Reg64& src)
            {
                AppendInstr(I_CVTSI2SS, 0x0F2A, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, RW(dst), R(src));
            }
            void cvtsi2ss(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTSI2SS, 0x0F2A, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, RW(dst), R(src));
            }
            void cvtss2si(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSS2SI, 0x0F2D, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }
            void cvtss2si(const Reg64& dst, const Mem32& src)
            {
                AppendInstr(I_CVTSS2SI, 0x0F2D, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }
            void cvttss2si(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTSS2SI, 0x0F2C, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }
            void cvttss2si(const Reg64& dst, const Mem32& src)
            {
                AppendInstr(I_CVTTSS2SI, 0x0F2C, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }
            void divps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_DIVPS, 0x0F5E, 0, RW(dst), R(src));
            }
            void divps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_DIVPS, 0x0F5E, 0, RW(dst), R(src));
            }
            void divss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_DIVSS, 0x0F5E, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void divss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_DIVSS, 0x0F5E, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void ldmxcsr(const Mem32& src)
            {
                AppendInstr(I_LDMXCSR, 0x0FAE, 0, Imm8(2), R(src));
            }
            void maskmovq(const MmxReg& src, const MmxReg& mask, const Reg& dstptr)
            {
                AppendInstr(I_MASKMOVQ, 0x0FF7, 0, R(src), R(mask), Dummy(R(dstptr), zdi));
            }
            void maxps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MAXPS, 0x0F5F, 0, RW(dst), R(src));
            }
            void maxps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MAXPS, 0x0F5F, 0, RW(dst), R(src));
            }
            void maxss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MAXSS, 0x0F5F, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void maxss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_MAXSS, 0x0F5F, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void minps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MINPS, 0x0F5D, 0, RW(dst), R(src));
            }
            void minps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MINPS, 0x0F5D, 0, RW(dst), R(src));
            }
            void minss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MINSS, 0x0F5D, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void minss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_MINSS, 0x0F5D, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void movaps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVAPS, 0x0F28, 0, W(dst), R(src));
            }
            void movaps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVAPS, 0x0F28, 0, W(dst), R(src));
            }
            void movaps(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVAPS, 0x0F29, 0, R(src), W(dst));
            }
            void movhlps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVHLPS, 0x0F12, 0, RW(dst), R(src));
            }
            void movhps(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVHPS, 0x0F16, 0, RW(dst), R(src));
            }
            void movhps(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVHPS, 0x0F17, 0, R(src), W(dst));
            }
            void movlhps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVLHPS, 0x0F16, 0, RW(dst), R(src));
            }
            void movlps(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVLPS, 0x0F12, 0, RW(dst), R(src));
            }
            void movlps(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVLPS, 0x0F13, 0, R(src), W(dst));
            }
            void movmskps(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVMSKPS, 0x0F50, 0, W(dst), R(src));
            }
            void movmskps(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVMSKPS, 0x0F50, E_REXW_PREFIX, W(dst), R(src));
            }
            void movntps(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVNTPS, 0x0F2B, 0, R(src), W(dst));
            }
            void movntq(const Mem64& dst, const MmxReg& src)
            {
                AppendInstr(I_MOVNTQ, 0x0FE7, 0, R(src), W(dst));
            }
            void movss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSS, 0x0F10, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void movss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_MOVSS, 0x0F10, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void movss(const Mem32& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSS, 0x0F11, E_MANDATORY_PREFIX_F3, R(src), W(dst));
            }
            void movups(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVUPS, 0x0F10, 0, W(dst), R(src));
            }
            void movups(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVUPS, 0x0F10, 0, W(dst), R(src));
            }
            void movups(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVUPS, 0x0F11, 0, R(src), W(dst));
            }
            void mulps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MULPS, 0x0F59, 0, RW(dst), R(src));
            }
            void mulps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MULPS, 0x0F59, 0, RW(dst), R(src));
            }
            void mulss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MULSS, 0x0F59, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void mulss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_MULSS, 0x0F59, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void orps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ORPS, 0x0F56, 0, RW(dst), R(src));
            }
            void orps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ORPS, 0x0F56, 0, RW(dst), R(src));
            }
            void prefetcht0(const Mem8& mem)
            {
                AppendInstr(I_PREFETCH, 0x0F18, 0, Imm8(1), R(mem));
            }
            void prefetcht1(const Mem8& mem)
            {
                AppendInstr(I_PREFETCH, 0x0F18, 0, Imm8(2), R(mem));
            }
            void prefetcht2(const Mem8& mem)
            {
                AppendInstr(I_PREFETCH, 0x0F18, 0, Imm8(3), R(mem));
            }
            void prefetchnta(const Mem8& mem)
            {
                AppendInstr(I_PREFETCH, 0x0F18, 0, Imm8(0), R(mem));
            }
            void rcpps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_RCPPS, 0x0F53, 0, W(dst), R(src));
            }
            void rcpps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_RCPPS, 0x0F53, 0, W(dst), R(src));
            }
            void rcpss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_RCPSS, 0x0F53, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void rcpss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_RCPSS, 0x0F53, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void rsqrtps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_RSQRTPS, 0x0F52, 0, W(dst), R(src));
            }
            void rsqrtps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_RSQRTPS, 0x0F52, 0, W(dst), R(src));
            }
            void rsqrtss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_RSQRTSS, 0x0F52, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void rsqrtss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_RSQRTSS, 0x0F52, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void sfence()
            {
                AppendInstr(I_SFENCE, 0x0FAEF8, 0);
            }
            void shufps(const XmmReg& dst, const XmmReg& src, const Imm8& sel)
            {
                AppendInstr(I_SHUFPS, 0x0FC6, 0, RW(dst), R(src), sel);
            }
            void shufps(const XmmReg& dst, const Mem128& src, const Imm8& sel)
            {
                AppendInstr(I_SHUFPS, 0x0FC6, 0, RW(dst), R(src), sel);
            }
            void sqrtps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SQRTPS, 0x0F51, 0, W(dst), R(src));
            }
            void sqrtps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_SQRTPS, 0x0F51, 0, W(dst), R(src));
            }
            void sqrtss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SQRTSS, 0x0F51, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void sqrtss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_SQRTSS, 0x0F51, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void stmxcsr(const Mem32& dst)
            {
                AppendInstr(I_STMXCSR, 0x0FAE, 0, Imm8(3), W(dst));
            }
            void subps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SUBPS, 0x0F5C, 0, RW(dst), R(src));
            }
            void subps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_SUBPS, 0x0F5C, 0, RW(dst), R(src));
            }
            void subss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SUBSS, 0x0F5C, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void subss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_SUBSS, 0x0F5C, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void ucomiss(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_UCOMISS, 0x0F2E, 0, R(src1), R(src2));
            }
            void ucomiss(const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_UCOMISS, 0x0F2E, 0, R(src1), R(src2));
            }
            void unpckhps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_UNPCKHPS, 0x0F15, 0, RW(dst), R(src));
            }
            void unpckhps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_UNPCKHPS, 0x0F15, 0, RW(dst), R(src));
            }
            void unpcklps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_UNPCKLPS, 0x0F14, 0, RW(dst), R(src));
            }
            void unpcklps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_UNPCKLPS, 0x0F14, 0, RW(dst), R(src));
            }
            void xorps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_XORPS, 0x0F57, 0, RW(dst), R(src));
            }
            void xorps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_XORPS, 0x0F57, 0, RW(dst), R(src));
            }

            // SSE2
            void addpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ADDPD, 0x0F58, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void addpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ADDPD, 0x0F58, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void addsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ADDSD, 0x0F58, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void addsd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_ADDSD, 0x0F58, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void andpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ANDPD, 0x0F54, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void andpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ANDPD, 0x0F54, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void andnpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ANDNPD, 0x0F55, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void andnpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ANDNPD, 0x0F55, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void clflush(const Mem8& src)
            {
                AppendInstr(I_CLFLUSH, 0x0FAE, 0, Imm8(7), R(src));
            }
            void cmppd(const XmmReg& dst, const XmmReg& src, const Imm8& opd3)
            {
                AppendInstr(I_CMPPD, 0x0FC2, E_MANDATORY_PREFIX_66, RW(dst), R(src), opd3);
            }
            void cmppd(const XmmReg& dst, const Mem128& src, const Imm8& opd3)
            {
                AppendInstr(I_CMPPD, 0x0FC2, E_MANDATORY_PREFIX_66, RW(dst), R(src), opd3);
            }
            void cmpeqpd(const XmmReg& dst, const XmmReg& src)
            {
                cmppd(dst, src, 0);
            }
            void cmpeqpd(const XmmReg& dst, const Mem128& src)
            {
                cmppd(dst, src, 0);
            }
            void cmpltpd(const XmmReg& dst, const XmmReg& src)
            {
                cmppd(dst, src, 1);
            }
            void cmpltpd(const XmmReg& dst, const Mem128& src)
            {
                cmppd(dst, src, 1);
            }
            void cmplepd(const XmmReg& dst, const XmmReg& src)
            {
                cmppd(dst, src, 2);
            }
            void cmplepd(const XmmReg& dst, const Mem128& src)
            {
                cmppd(dst, src, 2);
            }
            void cmpunordpd(const XmmReg& dst, const XmmReg& src)
            {
                cmppd(dst, src, 3);
            }
            void cmpunordpd(const XmmReg& dst, const Mem128& src)
            {
                cmppd(dst, src, 3);
            }
            void cmpneqpd(const XmmReg& dst, const XmmReg& src)
            {
                cmppd(dst, src, 4);
            }
            void cmpneqpd(const XmmReg& dst, const Mem128& src)
            {
                cmppd(dst, src, 4);
            }
            void cmpnltpd(const XmmReg& dst, const XmmReg& src)
            {
                cmppd(dst, src, 5);
            }
            void cmpnltpd(const XmmReg& dst, const Mem128& src)
            {
                cmppd(dst, src, 5);
            }
            void cmpnlepd(const XmmReg& dst, const XmmReg& src)
            {
                cmppd(dst, src, 6);
            }
            void cmpnlepd(const XmmReg& dst, const Mem128& src)
            {
                cmppd(dst, src, 6);
            }
            void cmpordpd(const XmmReg& dst, const XmmReg& src)
            {
                cmppd(dst, src, 7);
            }
            void cmpordpd(const XmmReg& dst, const Mem128& src)
            {
                cmppd(dst, src, 7);
            }
            void cmpsd(const XmmReg& dst, const XmmReg& src, const Imm8& opd3)
            {
                AppendInstr(I_CMPSD, 0x0FC2, E_MANDATORY_PREFIX_F2, RW(dst), R(src), opd3);
            }
            void cmpsd(const XmmReg& dst, const Mem64& src, const Imm8& opd3)
            {
                AppendInstr(I_CMPSD, 0x0FC2, E_MANDATORY_PREFIX_F2, RW(dst), R(src), opd3);
            }
            void cmpeqsd(const XmmReg& dst, const XmmReg& src)
            {
                cmpsd(dst, src, 0);
            }
            void cmpeqsd(const XmmReg& dst, const Mem64& src)
            {
                cmpsd(dst, src, 0);
            }
            void cmpltsd(const XmmReg& dst, const XmmReg& src)
            {
                cmpsd(dst, src, 1);
            }
            void cmpltsd(const XmmReg& dst, const Mem64& src)
            {
                cmpsd(dst, src, 1);
            }
            void cmplesd(const XmmReg& dst, const XmmReg& src)
            {
                cmpsd(dst, src, 2);
            }
            void cmplesd(const XmmReg& dst, const Mem64& src)
            {
                cmpsd(dst, src, 2);
            }
            void cmpunordsd(const XmmReg& dst, const XmmReg& src)
            {
                cmpsd(dst, src, 3);
            }
            void cmpunordsd(const XmmReg& dst, const Mem64& src)
            {
                cmpsd(dst, src, 3);
            }
            void cmpneqsd(const XmmReg& dst, const XmmReg& src)
            {
                cmpsd(dst, src, 4);
            }
            void cmpneqsd(const XmmReg& dst, const Mem64& src)
            {
                cmpsd(dst, src, 4);
            }
            void cmpnltsd(const XmmReg& dst, const XmmReg& src)
            {
                cmpsd(dst, src, 5);
            }
            void cmpnltsd(const XmmReg& dst, const Mem64& src)
            {
                cmpsd(dst, src, 5);
            }
            void cmpnlesd(const XmmReg& dst, const XmmReg& src)
            {
                cmpsd(dst, src, 6);
            }
            void cmpnlesd(const XmmReg& dst, const Mem64& src)
            {
                cmpsd(dst, src, 6);
            }
            void cmpordsd(const XmmReg& dst, const XmmReg& src)
            {
                cmpsd(dst, src, 7);
            }
            void cmpordsd(const XmmReg& dst, const Mem64& src)
            {
                cmpsd(dst, src, 7);
            }
            void comisd(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_COMISD, 0x0F2F, E_MANDATORY_PREFIX_66, R(src1), R(src2));
            }
            void comisd(const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_COMISD, 0x0F2F, E_MANDATORY_PREFIX_66, R(src1), R(src2));
            }
            void cvtdq2pd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTDQ2PD, 0x0FE6, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void cvtdq2pd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTDQ2PD, 0x0FE6, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void cvtpd2dq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPD2DQ, 0x0FE6, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void cvtpd2dq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTPD2DQ, 0x0FE6, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void cvtpd2pi(const MmxReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPD2PI, 0x0F2D, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvtpd2pi(const MmxReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTPD2PI, 0x0F2D, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvtpd2ps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPD2PS, 0x0F5A, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvtpd2ps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTPD2PS, 0x0F5A, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvtpi2pd(const XmmReg& dst, const MmxReg& src)
            {
                AppendInstr(I_CVTPI2PD, 0x0F2A, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvtpi2pd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTPI2PD, 0x0F2A, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvtps2dq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPS2DQ, 0x0F5B, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvtps2dq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTPS2DQ, 0x0F5B, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvtdq2ps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTDQ2PS, 0x0F5B, 0, W(dst), R(src));
            }
            void cvtdq2ps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTDQ2PS, 0x0F5B, 0, W(dst), R(src));
            }
            void cvtps2pd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPS2PD, 0x0F5A, 0, W(dst), R(src));
            }
            void cvtps2pd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTPS2PD, 0x0F5A, 0, W(dst), R(src));
            }
            void cvtsd2si(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSD2SI, 0x0F2D, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void cvtsd2si(const Reg32& dst, const Mem64& src)
            {
                AppendInstr(I_CVTSD2SI, 0x0F2D, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void cvtsd2si(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSD2SI, 0x0F2D, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, W(dst), R(src));
            }
            void cvtsd2si(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CVTSD2SI, 0x0F2D, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, W(dst), R(src));
            }
            void cvtsd2ss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSD2SS, 0x0F5A, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void cvtsd2ss(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTSD2SS, 0x0F5A, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void cvtsi2sd(const XmmReg& dst, const Reg32& src)
            {
                AppendInstr(I_CVTSI2SD, 0x0F2A, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void cvtsi2sd(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_CVTSI2SD, 0x0F2A, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void cvtsi2sd(const XmmReg& dst, const Reg64& src)
            {
                AppendInstr(I_CVTSI2SD, 0x0F2A, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, RW(dst), R(src));
            }
            void cvtsi2sd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTSI2SD, 0x0F2A, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, RW(dst), R(src));
            }
            void cvtss2sd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSS2SD, 0x0F5A, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void cvtss2sd(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_CVTSS2SD, 0x0F5A, E_MANDATORY_PREFIX_F3, RW(dst), R(src));
            }
            void cvttpd2dq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTPD2DQ, 0x0FE6, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvttpd2dq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTTPD2DQ, 0x0FE6, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvttpd2pi(const MmxReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTPD2PI, 0x0F2C, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvttpd2pi(const MmxReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTTPD2PI, 0x0F2C, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void cvttps2dq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTPS2DQ, 0x0F5B, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void cvttps2dq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTTPS2DQ, 0x0F5B, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void cvttsd2si(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTSD2SI, 0x0F2C, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void cvttsd2si(const Reg32& dst, const Mem64& src)
            {
                AppendInstr(I_CVTTSD2SI, 0x0F2C, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void cvttsd2si(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTSD2SI, 0x0F2C, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, W(dst), R(src));
            }
            void cvttsd2si(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CVTTSD2SI, 0x0F2C, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, W(dst), R(src));
            }
            void divpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_DIVPD, 0x0F5E, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void divpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_DIVPD, 0x0F5E, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void divsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_DIVSD, 0x0F5E, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void divsd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_DIVSD, 0x0F5E, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void lfence()
            {
                AppendInstr(I_LFENCE, 0x0FAEE8, 0);
            }
            void maskmovdqu(const XmmReg& src, const XmmReg& mask, const Reg& dstptr)
            {
                AppendInstr(I_MASKMOVDQU, 0x0FF7, E_MANDATORY_PREFIX_66, R(src), R(mask), Dummy(R(dstptr), zdi));
            }
            void maxpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MAXPD, 0x0F5F, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void maxpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MAXPD, 0x0F5F, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void maxsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MAXSD, 0x0F5F, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void maxsd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MAXSD, 0x0F5F, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void mfence()
            {
                AppendInstr(I_MFENCE, 0x0FAEF0, 0);
            }
            void minpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MINPD, 0x0F5D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void minpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MINPD, 0x0F5D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void minsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MINSD, 0x0F5D, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void minsd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MINSD, 0x0F5D, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void movapd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVAPD, 0x0F28, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void movapd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVAPD, 0x0F28, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void movapd(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVAPD, 0x0F29, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void movd(const XmmReg& dst, const Reg32& src)
            {
                AppendInstr(I_MOVD, 0x0F6E, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void movd(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_MOVD, 0x0F6E, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void movd(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVD, 0x0F7E, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void movd(const Mem32& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVD, 0x0F7E, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void movd(const XmmReg& dst, const Reg64& src)
            {
                AppendInstr(I_MOVD, 0x0F6E, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, W(dst), R(src));
            }
            void movd(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVD, 0x0F7E, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, R(src), W(dst));
            }
            void movdqa(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDQA, 0x0F6F, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void movdqa(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVDQA, 0x0F6F, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void movdqa(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDQA, 0x0F7F, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void movdqu(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDQU, 0x0F6F, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void movdqu(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVDQU, 0x0F6F, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void movdqu(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDQU, 0x0F7F, E_MANDATORY_PREFIX_F3, R(src), W(dst));
            }
            void movdq2q(const MmxReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDQ2Q, 0x0FD6, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void movhpd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVHPD, 0x0F16, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void movhpd(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVHPD, 0x0F17, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void movlpd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVLPD, 0x0F12, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void movlpd(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVLPD, 0x0F13, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void movmskpd(const Reg32& dst, XmmReg& src)
            {
                AppendInstr(I_MOVMSKPD, 0x0F50, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void movmskpd(const Reg64& dst, XmmReg& src)
            {
                AppendInstr(I_MOVMSKPD, 0x0F50, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, W(dst), R(src));
            }
            void movntdq(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVNTDQ, 0x0FE7, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void movnti(const Mem32& dst, const Reg32& src)
            {
                AppendInstr(I_MOVNTI, 0x0FC3, 0, R(src), W(dst));
            }
            void movnti(const Mem64& dst, const Reg64& src)
            {
                AppendInstr(I_MOVNTI, 0x0FC3, E_REXW_PREFIX, R(src), W(dst));
            }
            void movntpd(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVNTPD, 0x0F2B, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void movq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVQ, 0x0F7E, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void movq(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVQ, 0x0F7E, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void movq(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVQ, 0x0FD6, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void movq(const XmmReg& dst, const Reg64& src)
            {
                movd(dst, src);
            }
            void movq(const Reg64& dst, const XmmReg& src)
            {
                movd(dst, src);
            }
            void movq2dq(const XmmReg& dst, const MmxReg& src)
            {
                AppendInstr(I_MOVQ2DQ, 0x0FD6, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void movsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSD, 0x0F10, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }   // 64~127bits are unchanged
            void movsd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVSD, 0x0F10, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void movsd(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSD, 0x0F11, E_MANDATORY_PREFIX_F2, R(src), W(dst));
            }
            void movupd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVUPD, 0x0F10, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void movupd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVUPD, 0x0F10, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void movupd(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVUPD, 0x0F11, E_MANDATORY_PREFIX_66, R(src), W(dst));
            }
            void mulpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MULPD, 0x0F59, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void mulpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MULPD, 0x0F59, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void mulsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MULSD, 0x0F59, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void mulsd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MULSD, 0x0F59, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void orpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ORPD, 0x0F56, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void orpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ORPD, 0x0F56, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void packsswb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PACKSSWB, 0x0F63, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void packsswb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PACKSSWB, 0x0F63, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void packssdw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PACKSSDW, 0x0F6B, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void packssdw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PACKSSDW, 0x0F6B, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void packuswb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PACKUSWB, 0x0F67, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void packuswb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PACKUSWB, 0x0F67, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PADDB, 0x0FFC, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PADDB, 0x0FFC, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PADDW, 0x0FFD, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PADDW, 0x0FFD, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PADDD, 0x0FFE, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PADDD, 0x0FFE, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddq(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PADDQ, 0x0FD4, 0, RW(dst), R(src));
            }
            void paddq(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PADDQ, 0x0FD4, 0, RW(dst), R(src));
            }
            void paddq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PADDQ, 0x0FD4, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PADDQ, 0x0FD4, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddsb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PADDSB, 0x0FEC, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddsb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PADDSB, 0x0FEC, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PADDSW, 0x0FED, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PADDSW, 0x0FED, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddusb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PADDUSB, 0x0FDC, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddusb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PADDUSB, 0x0FDC, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddusw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PADDUSW, 0x0FDD, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void paddusw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PADDUSW, 0x0FDD, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pand(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PAND, 0x0FDB, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pand(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PAND, 0x0FDB, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pandn(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PANDN, 0x0FDF, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pandn(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PANDN, 0x0FDF, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pause()
            {
                AppendInstr(I_PAUSE, 0xF390, 0);
            }
            void pavgb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PAVGB, 0x0FE0, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pavgb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PAVGB, 0x0FE0, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pavgw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PAVGW, 0x0FE3, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pavgw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PAVGW, 0x0FE3, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpeqb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PCMPEQB, 0x0F74, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpeqb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PCMPEQB, 0x0F74, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpeqw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PCMPEQW, 0x0F75, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpeqw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PCMPEQW, 0x0F75, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpeqd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PCMPEQD, 0x0F76, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpeqd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PCMPEQD, 0x0F76, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpgtb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PCMPGTB, 0x0F64, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpgtb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PCMPGTB, 0x0F64, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpgtw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PCMPGTW, 0x0F65, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpgtw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PCMPGTW, 0x0F65, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpgtd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PCMPGTD, 0x0F66, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpgtd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PCMPGTD, 0x0F66, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pextrw(const Reg32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRW, 0x0FC5, E_MANDATORY_PREFIX_66, W(dst), R(src), i);
            }
            void pextrw(const Reg64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRW, 0x0FC5, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, W(dst), R(src), i);
            }
            void pinsrw(const XmmReg& dst, const Reg32& src, const Imm8& i)
            {
                AppendInstr(I_PINSRW, 0x0FC4, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void pinsrw(const XmmReg& dst, const Mem16& src, const Imm8& i)
            {
                AppendInstr(I_PINSRW, 0x0FC4, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void pinsrw(const XmmReg& dst, const Reg64& src, const Imm8& i)
            {
                AppendInstr(I_PINSRW, 0x0FC4, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, RW(dst), R(src), i);
            }
            void pmaddwd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMADDWD, 0x0FF5, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaddwd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMADDWD, 0x0FF5, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMAXSW, 0x0FEE, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMAXSW, 0x0FEE, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxub(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMAXUB, 0x0FDE, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxub(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMAXUB, 0x0FDE, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMINSW, 0x0FEA, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMINSW, 0x0FEA, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminub(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMINUB, 0x0FDA, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminub(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMINUB, 0x0FDA, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmovmskb(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVMSKB, 0x0FD7, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovmskb(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVMSKB, 0x0FD7, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, W(dst), R(src));
            }
            void pmulhuw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMULHUW, 0x0FE4, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmulhuw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMULHUW, 0x0FE4, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmulhw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMULHW, 0x0FE5, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmulhw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMULHW, 0x0FE5, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmullw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMULLW, 0x0FD5, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmullw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMULLW, 0x0FD5, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmuludq(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMULUDQ, 0x0FF4, 0, RW(dst), R(src));
            }
            void pmuludq(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMULUDQ, 0x0FF4, 0, RW(dst), R(src));
            }
            void pmuludq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMULUDQ, 0x0FF4, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmuludq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMULUDQ, 0x0FF4, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void por(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_POR, 0x0FEB, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void por(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_POR, 0x0FEB, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psadbw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSADBW, 0x0FF6, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psadbw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSADBW, 0x0FF6, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pshufd(const XmmReg& dst, const XmmReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFD, 0x0F70, E_MANDATORY_PREFIX_66, W(dst), R(src), order);
            }
            void pshufd(const XmmReg& dst, const Mem128& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFD, 0x0F70, E_MANDATORY_PREFIX_66, W(dst), R(src), order);
            }
            void pshufhw(const XmmReg& dst, const XmmReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFHW, 0x0F70, E_MANDATORY_PREFIX_F3, W(dst), R(src), order);
            }
            void pshufhw(const XmmReg& dst, const Mem128& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFHW, 0x0F70, E_MANDATORY_PREFIX_F3, W(dst), R(src), order);
            }
            void pshuflw(const XmmReg& dst, const XmmReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFLW, 0x0F70, E_MANDATORY_PREFIX_F2, W(dst), R(src), order);
            }
            void pshuflw(const XmmReg& dst, const Mem128& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFLW, 0x0F70, E_MANDATORY_PREFIX_F2, W(dst), R(src), order);
            }
            void psllw(const XmmReg& dst, const XmmReg& count)
            {
                AppendInstr(I_PSLLW, 0x0FF1, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psllw(const XmmReg& dst, const Mem128& count)
            {
                AppendInstr(I_PSLLW, 0x0FF1, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psllw(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSLLW, 0x0F71, E_MANDATORY_PREFIX_66, Imm8(6), RW(dst), count);
            }
            void pslld(const XmmReg& dst, const XmmReg& count)
            {
                AppendInstr(I_PSLLD, 0x0FF2, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void pslld(const XmmReg& dst, const Mem128& count)
            {
                AppendInstr(I_PSLLD, 0x0FF2, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void pslld(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSLLD, 0x0F72, E_MANDATORY_PREFIX_66, Imm8(6), RW(dst), count);
            }
            void psllq(const XmmReg& dst, const XmmReg& count)
            {
                AppendInstr(I_PSLLQ, 0x0FF3, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psllq(const XmmReg& dst, const Mem128& count)
            {
                AppendInstr(I_PSLLQ, 0x0FF3, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psllq(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSLLQ, 0x0F73, E_MANDATORY_PREFIX_66, Imm8(6), RW(dst), count);
            }
            void pslldq(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSLLDQ, 0x0F73, E_MANDATORY_PREFIX_66, Imm8(7), RW(dst), count);
            }
            void psraw(const XmmReg& dst, const XmmReg& count)
            {
                AppendInstr(I_PSRAW, 0x0FE1, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psraw(const XmmReg& dst, const Mem128& count)
            {
                AppendInstr(I_PSRAW, 0x0FE1, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psraw(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRAW, 0x0F71, E_MANDATORY_PREFIX_66, Imm8(4), RW(dst), count);
            }
            void psrad(const XmmReg& dst, const XmmReg& count)
            {
                AppendInstr(I_PSRAD, 0x0FE2, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psrad(const XmmReg& dst, const Mem128& count)
            {
                AppendInstr(I_PSRAD, 0x0FE2, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psrad(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRAD, 0x0F72, E_MANDATORY_PREFIX_66, Imm8(4), RW(dst), count);
            }
            void psrlw(const XmmReg& dst, const XmmReg& count)
            {
                AppendInstr(I_PSRLW, 0x0FD1, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psrlw(const XmmReg& dst, const Mem128& count)
            {
                AppendInstr(I_PSRLW, 0x0FD1, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psrlw(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRLW, 0x0F71, E_MANDATORY_PREFIX_66, Imm8(2), RW(dst), count);
            }
            void psrld(const XmmReg& dst, const XmmReg& count)
            {
                AppendInstr(I_PSRLD, 0x0FD2, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psrld(const XmmReg& dst, const Mem128& count)
            {
                AppendInstr(I_PSRLD, 0x0FD2, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psrld(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRLD, 0x0F72, E_MANDATORY_PREFIX_66, Imm8(2), RW(dst), count);
            }
            void psrlq(const XmmReg& dst, const XmmReg& count)
            {
                AppendInstr(I_PSRLQ, 0x0FD3, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psrlq(const XmmReg& dst, const Mem128& count)
            {
                AppendInstr(I_PSRLQ, 0x0FD3, E_MANDATORY_PREFIX_66, RW(dst), R(count));
            }
            void psrlq(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRLQ, 0x0F73, E_MANDATORY_PREFIX_66, Imm8(2), RW(dst), count);
            }
            void psrldq(const XmmReg& dst, const Imm8& count)
            {
                AppendInstr(I_PSRLDQ, 0x0F73, E_MANDATORY_PREFIX_66, Imm8(3), RW(dst), count);
            }
            void psubb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSUBB, 0x0FF8, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSUBB, 0x0FF8, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSUBW, 0x0FF9, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSUBW, 0x0FF9, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSUBD, 0x0FFA, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSUBD, 0x0FFA, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubq(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSUBQ, 0x0FFB, 0, RW(dst), R(src));
            }
            void psubq(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSUBQ, 0x0FFB, 0, RW(dst), R(src));
            }
            void psubq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSUBQ, 0x0FFB, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSUBQ, 0x0FFB, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubsb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSUBSB, 0x0FE8, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubsb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSUBSB, 0x0FE8, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSUBSW, 0x0FE9, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSUBSW, 0x0FE9, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubusb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSUBUSB, 0x0FD8, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubusb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSUBUSB, 0x0FD8, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubusw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSUBUSW, 0x0FD9, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psubusw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSUBUSW, 0x0FD9, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckhbw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PUNPCKHBW, 0x0F68, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckhbw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PUNPCKHBW, 0x0F68, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckhwd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PUNPCKHWD, 0x0F69, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckhwd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PUNPCKHWD, 0x0F69, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckhdq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PUNPCKHDQ, 0x0F6A, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckhdq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PUNPCKHDQ, 0x0F6A, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckhqdq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PUNPCKHQDQ, 0x0F6D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckhqdq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PUNPCKHQDQ, 0x0F6D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpcklbw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PUNPCKLBW, 0x0F60, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpcklbw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PUNPCKLBW, 0x0F60, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpcklwd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PUNPCKLWD, 0x0F61, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpcklwd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PUNPCKLWD, 0x0F61, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckldq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PUNPCKLDQ, 0x0F62, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpckldq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PUNPCKLDQ, 0x0F62, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpcklqdq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PUNPCKLQDQ, 0x0F6C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void punpcklqdq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PUNPCKLQDQ, 0x0F6C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pxor(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PXOR, 0x0FEF, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pxor(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PXOR, 0x0FEF, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void shufpd(const XmmReg& dst, const XmmReg& src, const Imm8& sel)
            {
                AppendInstr(I_SHUFPD, 0x0FC6, E_MANDATORY_PREFIX_66, RW(dst), R(src), sel);
            }
            void shufpd(const XmmReg& dst, const Mem128& src, const Imm8& sel)
            {
                AppendInstr(I_SHUFPD, 0x0FC6, E_MANDATORY_PREFIX_66, RW(dst), R(src), sel);
            }
            void sqrtpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SQRTPD, 0x0F51, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void sqrtpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_SQRTPD, 0x0F51, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void sqrtsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SQRTSD, 0x0F51, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void sqrtsd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_SQRTSD, 0x0F51, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void subpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SUBPD, 0x0F5C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void subpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_SUBPD, 0x0F5C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void subsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SUBSD, 0x0F5C, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void subsd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_SUBSD, 0x0F5C, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void ucomisd(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_UCOMISD, 0x0F2E, E_MANDATORY_PREFIX_66, R(src1), R(src2));
            }
            void ucomisd(const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_UCOMISD, 0x0F2E, E_MANDATORY_PREFIX_66, R(src1), R(src2));
            }
            void unpckhpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_UNPCKHPD, 0x0F15, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void unpckhpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_UNPCKHPD, 0x0F15, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void unpcklpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_UNPCKLPD, 0x0F14, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void unpcklpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_UNPCKLPD, 0x0F14, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void xorpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_XORPD, 0x0F57, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void xorpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_XORPD, 0x0F57, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }

            // SSE3
            void addsubps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ADDSUBPS, 0x0FD0, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void addsubps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ADDSUBPS, 0x0FD0, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void addsubpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_ADDSUBPD, 0x0FD0, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void addsubpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_ADDSUBPD, 0x0FD0, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void haddps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_HADDPS, 0x0F7C, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void haddps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_HADDPS, 0x0F7C, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void haddpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_HADDPD, 0x0F7C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void haddpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_HADDPD, 0x0F7C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void hsubps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_HSUBPS, 0x0F7D, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void hsubps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_HSUBPS, 0x0F7D, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void hsubpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_HSUBPD, 0x0F7D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void hsubpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_HSUBPD, 0x0F7D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void lddqu(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_LDDQU, 0x0FF0, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void monitor()
            {
                AppendInstr(I_MONITOR, 0x0F01C8, 0);
            }
            void movddup(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDDUP, 0x0F12, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void movddup(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVDDUP, 0x0F12, E_MANDATORY_PREFIX_F2, W(dst), R(src));
            }
            void movshdup(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSHDUP, 0x0F16, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void movshdup(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVSHDUP, 0x0F16, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void movsldup(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSLDUP, 0x0F12, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void movsldup(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVSLDUP, 0x0F12, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void mwait()
            {
                AppendInstr(I_MWAIT, 0x0F01C9, 0);
            }

            // SSSE3
            void pabsb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PABSB, 0x0F381C, 0, RW(dst), R(src));
            }
            void pabsb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PABSB, 0x0F381C, 0, RW(dst), R(src));
            }
            void pabsb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PABSB, 0x0F381C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pabsb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PABSB, 0x0F381C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pabsw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PABSW, 0x0F381D, 0, RW(dst), R(src));
            }
            void pabsw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PABSW, 0x0F381D, 0, RW(dst), R(src));
            }
            void pabsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PABSW, 0x0F381D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pabsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PABSW, 0x0F381D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pabsd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PABSD, 0x0F381E, 0, RW(dst), R(src));
            }
            void pabsd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PABSD, 0x0F381E, 0, RW(dst), R(src));
            }
            void pabsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PABSD, 0x0F381E, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pabsd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PABSD, 0x0F381E, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void palignr(const MmxReg& dst, const MmxReg& src, const Imm8& n)
            {
                AppendInstr(I_PALIGNR, 0x0F3A0F, 0, RW(dst), R(src), n);
            }
            void palignr(const MmxReg& dst, const Mem64& src, const Imm8& n)
            {
                AppendInstr(I_PALIGNR, 0x0F3A0F, 0, RW(dst), R(src), n);
            }
            void palignr(const XmmReg& dst, const XmmReg& src, const Imm8& n)
            {
                AppendInstr(I_PALIGNR, 0x0F3A0F, E_MANDATORY_PREFIX_66, RW(dst), R(src), n);
            }
            void palignr(const XmmReg& dst, const Mem128& src, const Imm8& n)
            {
                AppendInstr(I_PALIGNR, 0x0F3A0F, E_MANDATORY_PREFIX_66, RW(dst), R(src), n);
            }
            void phaddw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PHADDW, 0x0F3801, 0, RW(dst), R(src));
            }
            void phaddw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PHADDW, 0x0F3801, 0, RW(dst), R(src));
            }
            void phaddw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PHADDW, 0x0F3801, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phaddw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PHADDW, 0x0F3801, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phaddd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PHADDD, 0x0F3802, 0, RW(dst), R(src));
            }
            void phaddd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PHADDD, 0x0F3802, 0, RW(dst), R(src));
            }
            void phaddd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PHADDD, 0x0F3802, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phaddd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PHADDD, 0x0F3802, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phaddsw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PHADDSW, 0x0F3803, 0, RW(dst), R(src));
            }
            void phaddsw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PHADDSW, 0x0F3803, 0, RW(dst), R(src));
            }
            void phaddsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PHADDSW, 0x0F3803, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phaddsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PHADDSW, 0x0F3803, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phsubw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PHSUBW, 0x0F3805, 0, RW(dst), R(src));
            }
            void phsubw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PHSUBW, 0x0F3805, 0, RW(dst), R(src));
            }
            void phsubw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PHSUBW, 0x0F3805, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phsubw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PHSUBW, 0x0F3805, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phsubd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PHSUBD, 0x0F3806, 0, RW(dst), R(src));
            }
            void phsubd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PHSUBD, 0x0F3806, 0, RW(dst), R(src));
            }
            void phsubd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PHSUBD, 0x0F3806, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phsubd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PHSUBD, 0x0F3806, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phsubsw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PHSUBSW, 0x0F3807, 0, RW(dst), R(src));
            }
            void phsubsw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PHSUBSW, 0x0F3807, 0, RW(dst), R(src));
            }
            void phsubsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PHSUBSW, 0x0F3807, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phsubsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PHSUBSW, 0x0F3807, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaddubsw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMADDUBSW, 0x0F3804, 0, RW(dst), R(src));
            }
            void pmaddubsw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMADDUBSW, 0x0F3804, 0, RW(dst), R(src));
            }
            void pmaddubsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMADDUBSW, 0x0F3804, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaddubsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMADDUBSW, 0x0F3804, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmulhrsw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PMULHRSW, 0x0F380B, 0, RW(dst), R(src));
            }
            void pmulhrsw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMULHRSW, 0x0F380B, 0, RW(dst), R(src));
            }
            void pmulhrsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMULHRSW, 0x0F380B, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmulhrsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMULHRSW, 0x0F380B, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pshufb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSHUFB, 0x0F3800, 0, RW(dst), R(src));
            }
            void pshufb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSHUFB, 0x0F3800, 0, RW(dst), R(src));
            }
            void pshufb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSHUFB, 0x0F3800, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pshufb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSHUFB, 0x0F3800, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psignb(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSIGNB, 0x0F3808, 0, RW(dst), R(src));
            }
            void psignb(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSIGNB, 0x0F3808, 0, RW(dst), R(src));
            }
            void psignb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSIGNB, 0x0F3808, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psignb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSIGNB, 0x0F3808, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psignw(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSIGNW, 0x0F3809, 0, RW(dst), R(src));
            }
            void psignw(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSIGNW, 0x0F3809, 0, RW(dst), R(src));
            }
            void psignw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSIGNW, 0x0F3809, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psignw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSIGNW, 0x0F3809, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psignd(const MmxReg& dst, const MmxReg& src)
            {
                AppendInstr(I_PSIGND, 0x0F380A, 0, RW(dst), R(src));
            }
            void psignd(const MmxReg& dst, const Mem64& src)
            {
                AppendInstr(I_PSIGND, 0x0F380A, 0, RW(dst), R(src));
            }
            void psignd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PSIGND, 0x0F380A, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void psignd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PSIGND, 0x0F380A, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }

            // SSE4.1
            void blendps(const XmmReg& dst, const XmmReg& src, const Imm8& mask)
            {
                AppendInstr(I_BLENDPS, 0x0F3A0C, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void blendps(const XmmReg& dst, const Mem128& src, const Imm8& mask)
            {
                AppendInstr(I_BLENDPS, 0x0F3A0C, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void blendpd(const XmmReg& dst, const XmmReg& src, const Imm8& mask)
            {
                AppendInstr(I_BLENDPD, 0x0F3A0D, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void blendpd(const XmmReg& dst, const Mem128& src, const Imm8& mask)
            {
                AppendInstr(I_BLENDPD, 0x0F3A0D, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void blendvps(const XmmReg& dst, const XmmReg& src, const XmmReg& mask)
            {
                AppendInstr(I_BLENDVPS, 0x0F3814, E_MANDATORY_PREFIX_66, RW(dst), R(src), Dummy(R(mask), xmm0));
            }
            void blendvps(const XmmReg& dst, const Mem128& src, const XmmReg& mask)
            {
                AppendInstr(I_BLENDVPS, 0x0F3814, E_MANDATORY_PREFIX_66, RW(dst), R(src), Dummy(R(mask), xmm0));
            }
            void blendvpd(const XmmReg& dst, const XmmReg& src, const XmmReg& mask)
            {
                AppendInstr(I_BLENDVPD, 0x0F3815, E_MANDATORY_PREFIX_66, RW(dst), R(src), Dummy(R(mask), xmm0));
            }
            void blendvpd(const XmmReg& dst, const Mem128& src, const XmmReg& mask)
            {
                AppendInstr(I_BLENDVPD, 0x0F3815, E_MANDATORY_PREFIX_66, RW(dst), R(src), Dummy(R(mask), xmm0));
            }
            void dpps(const XmmReg& dst, const XmmReg& src, const Imm8& mask)
            {
                AppendInstr(I_DPPS, 0x0F3A40, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void dpps(const XmmReg& dst, const Mem128& src, const Imm8& mask)
            {
                AppendInstr(I_DPPS, 0x0F3A40, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void dppd(const XmmReg& dst, const XmmReg& src, const Imm8& mask)
            {
                AppendInstr(I_DPPD, 0x0F3A41, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void dppd(const XmmReg& dst, const Mem128& src, const Imm8& mask)
            {
                AppendInstr(I_DPPD, 0x0F3A41, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void extractps(const Reg32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_EXTRACTPS, 0x0F3A17, E_MANDATORY_PREFIX_66, R(src), W(dst), i);
            }
            void extractps(const Mem32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_EXTRACTPS, 0x0F3A17, E_MANDATORY_PREFIX_66, R(src), W(dst), i);
            }
            void extractps(const Reg64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_EXTRACTPS, 0x0F3A17, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, R(src), W(dst), i);
            }
            void insertps(const XmmReg& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_INSERTPS, 0x0F3A21, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void insertps(const XmmReg& dst, const Mem32& src, const Imm8& i)
            {
                AppendInstr(I_INSERTPS, 0x0F3A21, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void movntdqa(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVNTDQA, 0x0F382A, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void mpsadbw(const XmmReg& dst, const XmmReg& src, const Imm8& offsets)
            {
                AppendInstr(I_MPSADBW, 0x0F3A42, E_MANDATORY_PREFIX_66, RW(dst), R(src), offsets);
            }
            void mpsadbw(const XmmReg& dst, const Mem128& src, const Imm8& offsets)
            {
                AppendInstr(I_MPSADBW, 0x0F3A42, E_MANDATORY_PREFIX_66, RW(dst), R(src), offsets);
            }
            void packusdw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PACKUSDW, 0x0F382B, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void packusdw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PACKUSDW, 0x0F382B, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pblendvb(const XmmReg& dst, const XmmReg& src, const XmmReg& mask)
            {
                AppendInstr(I_PBLENDVB, 0x0F3810, E_MANDATORY_PREFIX_66, RW(dst), R(src), Dummy(R(mask), xmm0));
            }
            void pblendvb(const XmmReg& dst, const Mem128& src, const XmmReg& mask)
            {
                AppendInstr(I_PBLENDVB, 0x0F3810, E_MANDATORY_PREFIX_66, RW(dst), R(src), Dummy(R(mask), xmm0));
            }
            void pblendw(const XmmReg& dst, const XmmReg& src, const Imm8& mask)
            {
                AppendInstr(I_PBLENDW, 0x0F3A0E, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void pblendw(const XmmReg& dst, const Mem128& src, const Imm8& mask)
            {
                AppendInstr(I_PBLENDW, 0x0F3A0E, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void pcmpeqq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PCMPEQQ, 0x0F3829, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpeqq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PCMPEQQ, 0x0F3829, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pextrb(const Reg32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRB, 0x0F3A14, E_MANDATORY_PREFIX_66, R(src), W(dst), i);
            }
            void pextrb(const Mem8& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRB, 0x0F3A14, E_MANDATORY_PREFIX_66, R(src), W(dst), i);
            }
            void pextrw(const Mem16& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRW, 0x0F3A15, E_MANDATORY_PREFIX_66, R(src), W(dst), i);
            }
            void pextrd(const Reg32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRD, 0x0F3A16, E_MANDATORY_PREFIX_66, R(src), W(dst), i);
            }
            void pextrd(const Mem32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRD, 0x0F3A16, E_MANDATORY_PREFIX_66, R(src), W(dst), i);
            }
            void pextrb(const Reg64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRB, 0x0F3A14, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, R(src), W(dst), i);
            }
            void pextrd(const Reg64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRD, 0x0F3A16, E_MANDATORY_PREFIX_66, R(src), W(dst), i);
            }
            void pextrq(const Reg64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRQ, 0x0F3A16, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, R(src), W(dst), i);
            }
            void pextrq(const Mem64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRQ, 0x0F3A16, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, R(src), W(dst), i);
            }
            void phminposuw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PHMINPOSUW, 0x0F3841, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void phminposuw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PHMINPOSUW, 0x0F3841, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pinsrb(const XmmReg& dst, const Reg32& src, const Imm8& i)
            {
                AppendInstr(I_PINSRB, 0x0F3A20, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void pinsrb(const XmmReg& dst, const Mem8& src, const Imm8& i)
            {
                AppendInstr(I_PINSRB, 0x0F3A20, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void pinsrd(const XmmReg& dst, const Reg32& src, const Imm8& i)
            {
                AppendInstr(I_PINSRD, 0x0F3A22, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void pinsrd(const XmmReg& dst, const Mem32& src, const Imm8& i)
            {
                AppendInstr(I_PINSRD, 0x0F3A22, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void pinsrb(const XmmReg& dst, const Reg64& src, const Imm8& i)
            {
                AppendInstr(I_PINSRB, 0x0F3A20, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void pinsrd(const XmmReg& dst, const Reg64& src, const Imm8& i)
            {
                AppendInstr(I_PINSRD, 0x0F3A22, E_MANDATORY_PREFIX_66, RW(dst), R(src), i);
            }
            void pinsrq(const XmmReg& dst, const Reg64& src, const Imm8& i)
            {
                AppendInstr(I_PINSRQ, 0x0F3A22, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, RW(dst), R(src), i);
            }
            void pinsrq(const XmmReg& dst, const Mem64& src, const Imm8& i)
            {
                AppendInstr(I_PINSRQ, 0x0F3A22, E_MANDATORY_PREFIX_66 | E_REXW_PREFIX, RW(dst), R(src), i);
            }
            void pmaxsb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMAXSB, 0x0F383C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxsb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMAXSB, 0x0F383C, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMAXSD, 0x0F383D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxsd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMAXSD, 0x0F383D, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxuw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMAXUW, 0x0F383E, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxuw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMAXUW, 0x0F383E, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxud(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMAXUD, 0x0F383F, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmaxud(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMAXUD, 0x0F383F, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminsb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMINSB, 0x0F3838, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminsb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMINSB, 0x0F3838, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMINSD, 0x0F3839, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminsd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMINSD, 0x0F3839, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminuw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMINUW, 0x0F383A, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminuw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMINUW, 0x0F383A, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminud(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMINUD, 0x0F383B, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pminud(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMINUD, 0x0F383B, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmovsxbw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXBW, 0x0F3820, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxbw(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVSXBW, 0x0F3820, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxbd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXBD, 0x0F3821, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxbd(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVSXBD, 0x0F3821, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxbq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXBQ, 0x0F3822, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxbq(const XmmReg& dst, const Mem16& src)
            {
                AppendInstr(I_PMOVSXBQ, 0x0F3822, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxwd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXWD, 0x0F3823, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxwd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVSXWD, 0x0F3823, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxwq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXWQ, 0x0F3824, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxwq(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVSXWQ, 0x0F3824, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxdq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXDQ, 0x0F3825, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovsxdq(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVSXDQ, 0x0F3825, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxbw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXBW, 0x0F3830, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxbw(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVZXBW, 0x0F3830, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxbd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXBD, 0x0F3831, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxbd(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVZXBD, 0x0F3831, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxbq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXBQ, 0x0F3832, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxbq(const XmmReg& dst, const Mem16& src)
            {
                AppendInstr(I_PMOVZXBQ, 0x0F3832, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxwd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXWD, 0x0F3833, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxwd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVZXWD, 0x0F3833, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxwq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXWQ, 0x0F3834, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxwq(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVZXWQ, 0x0F3834, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxdq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXDQ, 0x0F3835, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmovzxdq(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVZXDQ, 0x0F3835, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void pmuldq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMULDQ, 0x0F3828, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmuldq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMULDQ, 0x0F3828, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmulld(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMULLD, 0x0F3840, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pmulld(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PMULLD, 0x0F3840, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void ptest(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PTEST, 0x0F3817, E_MANDATORY_PREFIX_66, R(src1), R(src2));
            }
            void ptest(const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PTEST, 0x0F3817, E_MANDATORY_PREFIX_66, R(src1), R(src2));
            }
            void roundps(const XmmReg& dst, const XmmReg& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPS, 0x0F3A08, E_MANDATORY_PREFIX_66, W(dst), R(src), mode);
            }
            void roundps(const XmmReg& dst, const Mem128& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPS, 0x0F3A08, E_MANDATORY_PREFIX_66, W(dst), R(src), mode);
            }
            void roundpd(const XmmReg& dst, const XmmReg& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPD, 0x0F3A09, E_MANDATORY_PREFIX_66, W(dst), R(src), mode);
            }
            void roundpd(const XmmReg& dst, const Mem128& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPD, 0x0F3A09, E_MANDATORY_PREFIX_66, W(dst), R(src), mode);
            }
            void roundss(const XmmReg& dst, const XmmReg& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDSS, 0x0F3A0A, E_MANDATORY_PREFIX_66, RW(dst), R(src), mode);
            }
            void roundss(const XmmReg& dst, const Mem32& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDSS, 0x0F3A0A, E_MANDATORY_PREFIX_66, RW(dst), R(src), mode);
            }
            void roundsd(const XmmReg& dst, const XmmReg& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDSD, 0x0F3A0B, E_MANDATORY_PREFIX_66, RW(dst), R(src), mode);
            }
            void roundsd(const XmmReg& dst, const Mem64& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDSD, 0x0F3A0B, E_MANDATORY_PREFIX_66, RW(dst), R(src), mode);
            }

            // SSE4.2
            void crc32(const Reg32& dst, const Reg8& src)
            {
                AppendInstr(I_CRC32, 0x0F38F0, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void crc32(const Reg32& dst, const Mem8& src)
            {
                AppendInstr(I_CRC32, 0x0F38F0, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void crc32(const Reg32& dst, const Reg16& src)
            {
                AppendInstr(I_CRC32, 0x0F38F1, E_MANDATORY_PREFIX_F2 | E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void crc32(const Reg32& dst, const Mem16& src)
            {
                AppendInstr(I_CRC32, 0x0F38F1, E_MANDATORY_PREFIX_F2 | E_OPERAND_SIZE_PREFIX, RW(dst), R(src));
            }
            void crc32(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_CRC32, 0x0F38F1, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void crc32(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CRC32, 0x0F38F1, E_MANDATORY_PREFIX_F2, RW(dst), R(src));
            }
            void crc32(const Reg64& dst, const Reg8& src)
            {
                AppendInstr(I_CRC32, 0x0F38F0, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, RW(dst), R(src));
            }
            void crc32(const Reg64& dst, const Mem8& src)
            {
                AppendInstr(I_CRC32, 0x0F38F0, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, RW(dst), R(src));
            }
            void crc32(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_CRC32, 0x0F38F1, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, RW(dst), R(src));
            }
            void crc32(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CRC32, 0x0F38F1, E_MANDATORY_PREFIX_F2 | E_REXW_PREFIX, RW(dst), R(src));
            }
            void pcmpestri(const Reg& result, const XmmReg& src1, const Reg& len1, const XmmReg& src2, const Reg& len2, const Imm8& mode)
            {
                AppendInstr(I_PCMPESTRI, 0x0F3A61, E_MANDATORY_PREFIX_66, R(src1), R(src2), mode, Dummy(W(result), ecx), Dummy(R(len1), eax), Dummy(R(len2), edx));
            }
            void pcmpestri(const Reg& result, const XmmReg& src1, const Reg& len1, const Mem128& src2, const Reg& len2, const Imm8& mode)
            {
                AppendInstr(I_PCMPESTRI, 0x0F3A61, E_MANDATORY_PREFIX_66, R(src1), R(src2), mode, Dummy(W(result), ecx), Dummy(R(len1), eax), Dummy(R(len2), edx));
            }
            void pcmpestrm(const XmmReg& result, const XmmReg& src1, const Reg& len1, const XmmReg& src2, const Reg& len2, const Imm8& mode)
            {
                AppendInstr(I_PCMPESTRM, 0x0F3A60, E_MANDATORY_PREFIX_66, R(src1), R(src2), mode, Dummy(W(result), xmm0), Dummy(R(len1), eax), Dummy(R(len2), edx));
            }
            void pcmpestrm(const XmmReg& result, const XmmReg& src1, const Reg& len1, const Mem128& src2, const Reg& len2, const Imm8& mode)
            {
                AppendInstr(I_PCMPESTRM, 0x0F3A60, E_MANDATORY_PREFIX_66, R(src1), R(src2), mode, Dummy(W(result), xmm0), Dummy(R(len1), eax), Dummy(R(len2), edx));
            }
            void pcmpistri(const Reg& result, const XmmReg& src1, const XmmReg& src2, const Imm8& mode)
            {
                AppendInstr(I_PCMPISTRI, 0x0F3A63, E_MANDATORY_PREFIX_66, R(src1), R(src2), mode, Dummy(W(result), ecx));
            }
            void pcmpistri(const Reg& result, const XmmReg& src1, const Mem128& src2, const Imm8& mode)
            {
                AppendInstr(I_PCMPISTRI, 0x0F3A63, E_MANDATORY_PREFIX_66, R(src1), R(src2), mode, Dummy(W(result), ecx));
            }
            void pcmpistrm(const XmmReg& result, const XmmReg& src1, const XmmReg& src2, const Imm8& mode)
            {
                AppendInstr(I_PCMPISTRM, 0x0F3A62, E_MANDATORY_PREFIX_66, R(src1), R(src2), mode, Dummy(W(result), xmm0));
            }
            void pcmpistrm(const XmmReg& result, const XmmReg& src1, const Mem128& src2, const Imm8& mode)
            {
                AppendInstr(I_PCMPISTRM, 0x0F3A62, E_MANDATORY_PREFIX_66, R(src1), R(src2), mode, Dummy(W(result), xmm0));
            }
            void pcmpgtq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PCMPGTQ, 0x0F3837, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void pcmpgtq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PCMPGTQ, 0x0F3837, E_MANDATORY_PREFIX_66, RW(dst), R(src));
            }
            void popcnt(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_POPCNT, 0x0FB8, E_MANDATORY_PREFIX_F3 | E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void popcnt(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_POPCNT, 0x0FB8, E_MANDATORY_PREFIX_F3 | E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void popcnt(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_POPCNT, 0x0FB8, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void popcnt(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_POPCNT, 0x0FB8, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void popcnt(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_POPCNT, 0x0FB8, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }
            void popcnt(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_POPCNT, 0x0FB8, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }

            // AVX
            void vaddpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ADDPD, 0x58, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ADDPD, 0x58, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ADDPD, 0x58, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ADDPD, 0x58, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ADDPS, 0x58, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ADDPS, 0x58, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ADDPS, 0x58, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ADDPS, 0x58, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ADDSD, 0x58, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vaddsd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_ADDSD, 0x58, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vaddss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ADDSS, 0x58, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vaddss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_ADDSS, 0x58, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vaddsubpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ADDSUBPD, 0xD0, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddsubpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ADDSUBPD, 0xD0, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddsubpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ADDSUBPD, 0xD0, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddsubpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ADDSUBPD, 0xD0, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vaddsubps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ADDSUBPS, 0xD0, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vaddsubps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ADDSUBPS, 0xD0, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vaddsubps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ADDSUBPS, 0xD0, E_VEX_256 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vaddsubps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ADDSUBPS, 0xD0, E_VEX_256 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void aesenc(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_AESENC, 0x0F38DC, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void aesenc(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_AESENC, 0x0F38DC, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void vaesenc(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_AESENC, 0xDC, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vaesenc(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_AESENC, 0xDC, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void aesenclast(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_AESENCLAST, 0x0F38DD, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void aesenclast(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_AESENCLAST, 0x0F38DD, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void vaesenclast(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_AESENCLAST, 0xDD, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vaesenclast(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_AESENCLAST, 0xDD, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void aesdec(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_AESDEC, 0x0F38DE, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void aesdec(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_AESDEC, 0x0F38DE, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void vaesdec(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_AESDEC, 0xDE, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vaesdec(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_AESDEC, 0xDE, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void aesdeclast(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_AESDECLAST, 0x0F38DF, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void aesdeclast(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_AESDECLAST, 0x0F38DF, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void vaesdeclast(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_AESDECLAST, 0xDF, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vaesdeclast(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_AESDECLAST, 0xDF, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void aesimc(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_AESIMC, 0x0F38DB, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void aesimc(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_AESIMC, 0x0F38DB, E_MANDATORY_PREFIX_66, W(dst), R(src));
            }
            void vaesimc(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_AESIMC, 0xDB, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vaesimc(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_AESIMC, 0xDB, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void aeskeygenassist(const XmmReg& dst, const XmmReg& src, const Imm8& imm)
            {
                AppendInstr(I_AESKEYGENASSIST, 0x0F3ADF, E_MANDATORY_PREFIX_66, W(dst), R(src), imm);
            }
            void aeskeygenassist(const XmmReg& dst, const Mem128& src, const Imm8& imm)
            {
                AppendInstr(I_AESKEYGENASSIST, 0x0F3ADF, E_MANDATORY_PREFIX_66, W(dst), R(src), imm);
            }
            void vaeskeygenassist(const XmmReg& dst, const XmmReg& src, const Imm8& imm)
            {
                AppendInstr(I_AESKEYGENASSIST, 0xDF, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src), imm);
            }
            void vaeskeygenassist(const XmmReg& dst, const Mem128& src, const Imm8& imm)
            {
                AppendInstr(I_AESKEYGENASSIST, 0xDF, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src), imm);
            }
            void vandpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ANDPD, 0x54, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ANDPD, 0x54, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ANDPD, 0x54, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ANDPD, 0x54, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ANDPS, 0x54, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ANDPS, 0x54, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ANDPS, 0x54, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ANDPS, 0x54, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandnpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ANDNPD, 0x55, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandnpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ANDNPD, 0x55, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandnpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ANDNPD, 0x55, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandnpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ANDNPD, 0x55, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandnps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ANDNPS, 0x55, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandnps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ANDNPS, 0x55, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandnps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ANDNPS, 0x55, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vandnps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ANDNPS, 0x55, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vblendpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_BLENDPD, 0x0D, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vblendpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& mask)
            {
                AppendInstr(I_BLENDPD, 0x0D, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vblendpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_BLENDPD, 0x0D, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vblendpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& mask)
            {
                AppendInstr(I_BLENDPD, 0x0D, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vblendps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_BLENDPS, 0x0C, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vblendps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& mask)
            {
                AppendInstr(I_BLENDPS, 0x0C, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vblendps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_BLENDPS, 0x0C, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vblendps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& mask)
            {
                AppendInstr(I_BLENDPS, 0x0C, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vblendvpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const XmmReg& mask)
            {
                AppendInstr(I_BLENDVPD, 0x4B, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), R(mask));
            }
            void vblendvpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const XmmReg& mask)
            {
                AppendInstr(I_BLENDVPD, 0x4B, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), R(mask));
            }
            void vblendvpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const YmmReg& mask)
            {
                AppendInstr(I_BLENDVPD, 0x4B, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), R(mask));
            }
            void vblendvpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const YmmReg& mask)
            {
                AppendInstr(I_BLENDVPD, 0x4B, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), R(mask));
            }
            void vblendvps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const XmmReg& mask)
            {
                AppendInstr(I_BLENDVPS, 0x4A, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), R(mask));
            }
            void vblendvps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const XmmReg& mask)
            {
                AppendInstr(I_BLENDVPS, 0x4A, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), R(mask));
            }
            void vblendvps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const YmmReg& mask)
            {
                AppendInstr(I_BLENDVPS, 0x4A, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), R(mask));
            }
            void vblendvps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const YmmReg& mask)
            {
                AppendInstr(I_BLENDVPS, 0x4A, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), R(mask));
            }
            void vbroadcastss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_VBROADCASTSS, 0x18, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vbroadcastss(const YmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_VBROADCASTSS, 0x18, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vbroadcastsd(const YmmReg& dst, const Mem64 src)
            {
                AppendInstr(I_VBROADCASTSD, 0x19, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vbroadcastf128(const YmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_VBROADCASTF128, 0x1A, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vcmppd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPPD, 0xC2, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1), imm);
            }
            void vcmppd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPPD, 0xC2, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1), imm);
            }
            void vcmppd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPPD, 0xC2, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1), imm);
            }
            void vcmppd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPPD, 0xC2, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1), imm);
            }
            void vcmpps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPPS, 0xC2, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1), imm);
            }
            void vcmpps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPPS, 0xC2, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1), imm);
            }
            void vcmpps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPPS, 0xC2, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1), imm);
            }
            void vcmpps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPPS, 0xC2, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1), imm);
            }
            void vcmpsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPSD, 0xC2, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1), imm);
            }
            void vcmpsd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPSD, 0xC2, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1), imm);
            }
            void vcmpss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPSS, 0xC2, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1), imm);
            }
            void vcmpss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2, const Imm8& imm)
            {
                AppendInstr(I_CMPSS, 0xC2, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1), imm);
            }
            void vcomisd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_COMISD, 0x2F, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vcomisd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_COMISD, 0x2F, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vcomiss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_COMISS, 0x2F, E_VEX_LIG | E_VEX_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vcomiss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_COMISS, 0x2F, E_VEX_LIG | E_VEX_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vcvtdq2pd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTDQ2PD, 0xE6, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src));
            }
            void vcvtdq2pd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTDQ2PD, 0xE6, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src));
            }
            void vcvtdq2pd(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTDQ2PD, 0xE6, E_VEX_256 | E_VEX_F3_0F, W(dst), R(src));
            }
            void vcvtdq2pd(const YmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTDQ2PD, 0xE6, E_VEX_256 | E_VEX_F3_0F, W(dst), R(src));
            }
            void vcvtdq2ps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTDQ2PS, 0x5B, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vcvtdq2ps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTDQ2PS, 0x5B, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vcvtdq2ps(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_CVTDQ2PS, 0x5B, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vcvtdq2ps(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_CVTDQ2PS, 0x5B, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vcvtpd2dq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPD2DQ, 0xE6, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src));
            }
            void vcvtpd2dq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTPD2DQ, 0xE6, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src));
            }
            void vcvtpd2dq(const XmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_CVTPD2DQ, 0xE6, E_VEX_256 | E_VEX_F2_0F, W(dst), R(src));
            }
            void vcvtpd2dq(const XmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_CVTPD2DQ, 0xE6, E_VEX_256 | E_VEX_F2_0F, W(dst), R(src));
            }
            void vcvtpd2ps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPD2PS, 0x5A, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vcvtpd2ps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTPD2PS, 0x5A, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vcvtpd2ps(const XmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_CVTPD2PS, 0x5A, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vcvtpd2ps(const XmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_CVTPD2PS, 0x5A, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vcvtps2dq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPS2DQ, 0x5B, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vcvtps2dq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTPS2DQ, 0x5B, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vcvtps2dq(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_CVTPS2DQ, 0x5B, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vcvtps2dq(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_CVTPS2DQ, 0x5B, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vcvtps2pd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPS2PD, 0x5A, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vcvtps2pd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_CVTPS2PD, 0x5A, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vcvtps2pd(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTPS2PD, 0x5A, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vcvtps2pd(const YmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTPS2PD, 0x5A, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vcvtsd2si(const Reg32 dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSD2SI, 0x2D, E_VEX_128 | E_VEX_F2_0F | E_VEX_W0, W(dst), R(src));
            }
            void vcvtsd2si(const Reg32 dst, const Mem64& src)
            {
                AppendInstr(I_CVTSD2SI, 0x2D, E_VEX_128 | E_VEX_F2_0F | E_VEX_W0, W(dst), R(src));
            }
            void vcvtsd2si(const Reg64 dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSD2SI, 0x2D, E_VEX_128 | E_VEX_F2_0F | E_VEX_W1, W(dst), R(src));
            }
            void vcvtsd2si(const Reg64 dst, const Mem64& src)
            {
                AppendInstr(I_CVTSD2SI, 0x2D, E_VEX_128 | E_VEX_F2_0F | E_VEX_W1, W(dst), R(src));
            }
            void vcvtsd2ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_CVTSD2SS, 0x5A, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vcvtsd2ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_CVTSD2SS, 0x5A, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vcvtsi2sd(const XmmReg& dst, const XmmReg& src1, const Reg32& src2)
            {
                AppendInstr(I_CVTSI2SD, 0x2A, E_VEX_128 | E_VEX_F2_0F | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void vcvtsi2sd(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_CVTSI2SD, 0x2A, E_VEX_128 | E_VEX_F2_0F | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void vcvtsi2sd(const XmmReg& dst, const XmmReg& src1, const Reg64& src2)
            {
                AppendInstr(I_CVTSI2SD, 0x2A, E_VEX_128 | E_VEX_F2_0F | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void vcvtsi2sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_CVTSI2SD, 0x2A, E_VEX_128 | E_VEX_F2_0F | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void vcvtsi2ss(const XmmReg& dst, const XmmReg& src1, const Reg32& src2)
            {
                AppendInstr(I_CVTSI2SS, 0x2A, E_VEX_128 | E_VEX_F3_0F | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void vcvtsi2ss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_CVTSI2SS, 0x2A, E_VEX_128 | E_VEX_F3_0F | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void vcvtsi2ss(const XmmReg& dst, const XmmReg& src1, const Reg64& src2)
            {
                AppendInstr(I_CVTSI2SS, 0x2A, E_VEX_128 | E_VEX_F3_0F | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void vcvtsi2ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_CVTSI2SS, 0x2A, E_VEX_128 | E_VEX_F3_0F | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void vcvtss2sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_CVTSS2SD, 0x5A, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vcvtss2sd(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_CVTSS2SD, 0x5A, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vcvtss2si(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSS2SI, 0x2D, E_VEX_128 | E_VEX_F3_0F | E_VEX_W0, W(dst), R(src));
            }
            void vcvtss2si(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CVTSS2SI, 0x2D, E_VEX_128 | E_VEX_F3_0F | E_VEX_W0, W(dst), R(src));
            }
            void vcvtss2si(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSS2SI, 0x2D, E_VEX_128 | E_VEX_F3_0F | E_VEX_W1, W(dst), R(src));
            }
            void vcvtss2si(const Reg64& dst, const Mem32& src)
            {
                AppendInstr(I_CVTSS2SI, 0x2D, E_VEX_128 | E_VEX_F3_0F | E_VEX_W1, W(dst), R(src));
            }
            void vcvttpd2dq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTPD2DQ, 0xE6, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vcvttpd2dq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTTPD2DQ, 0xE6, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vcvttpd2dq(const XmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_CVTTPD2DQ, 0xE6, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vcvttpd2dq(const XmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_CVTTPD2DQ, 0xE6, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vcvttps2dq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTTPS2DQ, 0x5B, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src));
            }
            void vcvttps2dq(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_CVTTPS2DQ, 0x5B, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src));
            }
            void vcvttps2dq(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_CVTTPS2DQ, 0x5B, E_VEX_256 | E_VEX_F3_0F, W(dst), R(src));
            }
            void vcvttps2dq(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_CVTTPS2DQ, 0x5B, E_VEX_256 | E_VEX_F3_0F, W(dst), R(src));
            }
            void vcvttsd2si(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSD2SI, 0x2C, E_VEX_128 | E_VEX_F2_0F | E_VEX_W0, W(dst), R(src));
            }
            void vcvttsd2si(const Reg32& dst, const Mem64& src)
            {
                AppendInstr(I_CVTSD2SI, 0x2C, E_VEX_128 | E_VEX_F2_0F | E_VEX_W0, W(dst), R(src));
            }
            void vcvttsd2si(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSD2SI, 0x2C, E_VEX_128 | E_VEX_F2_0F | E_VEX_W1, W(dst), R(src));
            }
            void vcvttsd2si(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_CVTSD2SI, 0x2C, E_VEX_128 | E_VEX_F2_0F | E_VEX_W1, W(dst), R(src));
            }
            void vcvttss2si(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSS2SI, 0x2C, E_VEX_128 | E_VEX_F3_0F | E_VEX_W0, W(dst), R(src));
            }
            void vcvttss2si(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_CVTSS2SI, 0x2C, E_VEX_128 | E_VEX_F3_0F | E_VEX_W0, W(dst), R(src));
            }
            void vcvttss2si(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_CVTSS2SI, 0x2C, E_VEX_128 | E_VEX_F3_0F | E_VEX_W1, W(dst), R(src));
            }
            void vcvttss2si(const Reg64& dst, const Mem32& src)
            {
                AppendInstr(I_CVTSS2SI, 0x2C, E_VEX_128 | E_VEX_F3_0F | E_VEX_W1, W(dst), R(src));
            }
            void vdivpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_DIVPD, 0x5E, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vdivpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_DIVPD, 0x5E, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vdivpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_DIVPD, 0x5E, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vdivpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_DIVPD, 0x5E, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vdivps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_DIVPS, 0x5E, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vdivps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_DIVPS, 0x5E, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vdivps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_DIVPS, 0x5E, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vdivps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_DIVPS, 0x5E, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vdivsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_DIVSD, 0x5E, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vdivsd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_DIVSD, 0x5E, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vdivss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_DIVSS, 0x5E, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vdivss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_DIVSS, 0x5E, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vdppd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_DPPD, 0x41, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vdppd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& mask)
            {
                AppendInstr(I_DPPD, 0x41, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vdpps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_DPPS, 0x40, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vdpps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& mask)
            {
                AppendInstr(I_DPPS, 0x40, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vdpps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_DPPS, 0x40, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vdpps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& mask)
            {
                AppendInstr(I_DPPS, 0x40, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vextractf128(const XmmReg& dst, const YmmReg& src, const Imm8& i)
            {
                AppendInstr(I_VEXTRACTF128, 0x19, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, R(src), W(dst), i);
            }
            void vextractf128(const Mem128& dst, const YmmReg& src, const Imm8& i)
            {
                AppendInstr(I_VEXTRACTF128, 0x19, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, R(src), W(dst), i);
            }
            void vextractps(const Reg32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_EXTRACTPS, 0x17, E_VEX_128 | E_VEX_66_0F3A, R(src), W(dst), i);
            }
            void vextractps(const Mem32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_EXTRACTPS, 0x17, E_VEX_128 | E_VEX_66_0F3A, R(src), W(dst), i);
            }
            void vhaddpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_HADDPD, 0x7C, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vhaddpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_HADDPD, 0x7C, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vhaddpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_HADDPD, 0x7C, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vhaddpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_HADDPD, 0x7C, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vhaddps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_HADDPD, 0x7C, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vhaddps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_HADDPD, 0x7C, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vhaddps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_HADDPD, 0x7C, E_VEX_256 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vhaddps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_HADDPD, 0x7C, E_VEX_256 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vhsubpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_HSUBPD, 0x7D, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vhsubpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_HSUBPD, 0x7D, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vhsubpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_HSUBPD, 0x7D, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vhsubpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_HSUBPD, 0x7D, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vhsubps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_HSUBPD, 0x7D, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vhsubps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_HSUBPD, 0x7D, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vhsubps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_HSUBPD, 0x7D, E_VEX_256 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vhsubps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_HSUBPD, 0x7D, E_VEX_256 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vinsertf128(const YmmReg& dst, const YmmReg& src1, const XmmReg& src2, const Imm8& i)
            {
                AppendInstr(I_VINSERTF128, 0x18, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), i);
            }
            void vinsertf128(const YmmReg& dst, const YmmReg& src1, const Mem128& src2, const Imm8& i)
            {
                AppendInstr(I_VINSERTF128, 0x18, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), i);
            }
            void vinsertps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& i)
            {
                AppendInstr(I_INSERTPS, 0x21, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), i);
            }
            void vinsertps(const XmmReg& dst, const XmmReg& src1, const Mem32& src2, const Imm8& i)
            {
                AppendInstr(I_INSERTPS, 0x21, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), i);
            }
            void vlddqu(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_LDDQU, 0xF0, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src));
            }
            void vlddqu(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_LDDQU, 0xF0, E_VEX_256 | E_VEX_F2_0F, W(dst), R(src));
            }
            void vldmxcsr(const Mem32& src)
            {
                AppendInstr(I_LDMXCSR, 0xAE, E_VEX_LZ | E_VEX_0F | E_VEX_WIG, Imm8(2), R(src));
            }
            void vmaskmovdqu(const XmmReg& src, const XmmReg& mask, const Reg& dstptr)
            {
                AppendInstr(I_MASKMOVDQU, 0xF7, E_VEX_128_66_0F_WIG, R(src), R(mask), Dummy(R(dstptr), zdi));
            }
            void vmaskmovps(const XmmReg& dst, const XmmReg& mask, const Mem128& src)
            {
                AppendInstr(I_VMASKMOVPS, 0x2C, E_VEX_128_66_0F38_W0, W(dst), R(src), R(mask));
            }
            void vmaskmovps(const YmmReg& dst, const YmmReg& mask, const Mem256& src)
            {
                AppendInstr(I_VMASKMOVPS, 0x2C, E_VEX_256_66_0F38_W0, W(dst), R(src), R(mask));
            }
            void vmaskmovpd(const XmmReg& dst, const XmmReg& mask, const Mem128& src)
            {
                AppendInstr(I_VMASKMOVPD, 0x2D, E_VEX_128_66_0F38_W0, W(dst), R(src), R(mask));
            }
            void vmaskmovpd(const YmmReg& dst, const YmmReg& mask, const Mem256& src)
            {
                AppendInstr(I_VMASKMOVPD, 0x2D, E_VEX_256_66_0F38_W0, W(dst), R(src), R(mask));
            }
            void vmaskmovps(const Mem128& dst, const XmmReg& mask, const XmmReg& src)
            {
                AppendInstr(I_VMASKMOVPS, 0x2E, E_VEX_128_66_0F38_W0, R(src), W(dst), R(mask));
            }
            void vmaskmovps(const Mem256& dst, const YmmReg& mask, const YmmReg& src)
            {
                AppendInstr(I_VMASKMOVPS, 0x2E, E_VEX_256_66_0F38_W0, R(src), W(dst), R(mask));
            }
            void vmaskmovpd(const Mem128& dst, const XmmReg& mask, const XmmReg& src)
            {
                AppendInstr(I_VMASKMOVPD, 0x2F, E_VEX_128_66_0F38_W0, R(src), W(dst), R(mask));
            }
            void vmaskmovpd(const Mem256& dst, const YmmReg& mask, const YmmReg& src)
            {
                AppendInstr(I_VMASKMOVPD, 0x2F, E_VEX_256_66_0F38_W0, R(src), W(dst), R(mask));
            }
            void vmaxpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MAXPD, 0x5F, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmaxpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_MAXPD, 0x5F, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmaxpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_MAXPD, 0x5F, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmaxpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_MAXPD, 0x5F, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmaxps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MAXPS, 0x5F, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmaxps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_MAXPS, 0x5F, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmaxps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_MAXPS, 0x5F, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmaxps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_MAXPS, 0x5F, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmaxsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MAXSD, 0x5F, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vmaxsd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_MAXSD, 0x5F, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vmaxss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MAXSS, 0x5F, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vmaxss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_MAXSS, 0x5F, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vminpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MINPD, 0x5D, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vminpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_MINPD, 0x5D, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vminpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_MINPD, 0x5D, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vminpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_MINPD, 0x5D, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vminps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MINPS, 0x5D, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vminps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_MINPS, 0x5D, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vminps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_MINPS, 0x5D, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vminps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_MINPS, 0x5D, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vminsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MINSD, 0x5D, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vminsd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_MINSD, 0x5D, E_VEX_128 | E_VEX_F2_0F, W(dst), R(src2), R(src1));
            }
            void vminss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MINSS, 0x5D, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vminss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_MINSS, 0x5D, E_VEX_128 | E_VEX_F3_0F, W(dst), R(src2), R(src1));
            }
            void vmovapd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVAPD, 0x28, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vmovapd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVAPD, 0x28, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vmovapd(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVAPD, 0x29, E_VEX_128_66_0F_WIG, R(src), W(dst));
            }
            void vmovapd(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVAPD, 0x28, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vmovapd(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVAPD, 0x28, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vmovapd(const Mem256& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVAPD, 0x29, E_VEX_256_66_0F_WIG, R(src), W(dst));
            }
            void vmovaps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVAPS, 0x28, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vmovaps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVAPS, 0x28, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vmovaps(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVAPS, 0x29, E_VEX_128_0F_WIG, R(src), W(dst));
            }
            void vmovaps(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVAPS, 0x28, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vmovaps(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVAPS, 0x28, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vmovaps(const Mem256& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVAPS, 0x29, E_VEX_256_0F_WIG, R(src), W(dst));
            }
            void vmovd(const XmmReg& dst, const Reg32& src)
            {
                AppendInstr(I_MOVD, 0x6E, E_VEX_128 | E_VEX_66_0F | E_VEX_W0, W(dst), R(src));
            }
            void vmovd(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_MOVD, 0x6E, E_VEX_128 | E_VEX_66_0F | E_VEX_W0, W(dst), R(src));
            }
            void vmovd(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVD, 0x7E, E_VEX_128 | E_VEX_66_0F | E_VEX_W0, R(src), W(dst));
            }
            void vmovd(const Mem32& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVD, 0x7E, E_VEX_128 | E_VEX_66_0F | E_VEX_W0, R(src), W(dst));
            }
            void vmovq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVQ, 0x7E, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovq(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVQ, 0x7E, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovq(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVQ, 0xD6, E_VEX_128_66_0F_WIG, R(src), W(dst));
            }
            void vmovq(const XmmReg& dst, const Reg64& src)
            {
                AppendInstr(I_MOVQ, 0x6E, E_VEX_128 | E_VEX_66_0F | E_VEX_W1, W(dst), R(src));
            }
            void vmovq(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVQ, 0x7E, E_VEX_128 | E_VEX_66_0F | E_VEX_W1, R(src), W(dst));
            }
            void vmovddup(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDDUP, 0x12, E_VEX_128 | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovddup(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVDDUP, 0x12, E_VEX_128 | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovddup(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVDDUP, 0x12, E_VEX_256 | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovddup(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVDDUP, 0x12, E_VEX_256 | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovdqa(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDQA, 0x6F, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vmovdqa(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVDQA, 0x6F, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vmovdqa(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDQA, 0x7F, E_VEX_128_66_0F_WIG, R(src), W(dst));
            }
            void vmovdqa(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVDQA, 0x6F, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vmovdqa(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVDQA, 0x6F, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vmovdqa(const Mem256& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVDQA, 0x7F, E_VEX_256_66_0F_WIG, R(src), W(dst));
            }
            void vmovdqu(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDQU, 0x6F, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovdqu(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVDQU, 0x6F, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovdqu(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVDQU, 0x7F, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, R(src), W(dst));
            }
            void vmovdqu(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVDQU, 0x6F, E_VEX_256 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovdqu(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVDQU, 0x6F, E_VEX_256 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovdqu(const Mem256& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVDQU, 0x7F, E_VEX_256 | E_VEX_F3_0F | E_VEX_WIG, R(src), W(dst));
            }
            void vmovhlps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MOVHLPS, 0x12, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmovhpd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_MOVHPD, 0x16, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmovhpd(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVHPD, 0x17, E_VEX_128_66_0F_WIG, R(src), W(dst));
            }
            void vmovhps(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_MOVHPS, 0x16, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmovhps(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVHPS, 0x17, E_VEX_128_0F_WIG, R(src), W(dst));
            }
            void vmovlhps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MOVHLPS, 0x16, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmovlpd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_MOVLPD, 0x12, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmovlpd(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVLPD, 0x13, E_VEX_128_66_0F_WIG, R(src), W(dst));
            }
            void vmovlps(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_MOVLPS, 0x12, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmovlps(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVLPS, 0x13, E_VEX_128_0F_WIG, R(src), W(dst));
            }
            void vmovmskpd(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVMSKPD, 0x50, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vmovmskpd(const Reg32& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVMSKPD, 0x50, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vmovmskpd(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVMSKPD, 0x50, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vmovmskpd(const Reg64& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVMSKPD, 0x50, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vmovmskps(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVMSKPS, 0x50, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vmovmskps(const Reg32& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVMSKPS, 0x50, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vmovmskps(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVMSKPS, 0x50, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vmovmskps(const Reg64& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVMSKPS, 0x50, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vmovntdq(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVNTDQ, 0xE7, E_VEX_128_66_0F_WIG, R(src), W(dst));
            }
            void vmovntdq(const Mem256& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVNTDQ, 0xE7, E_VEX_256_66_0F_WIG, R(src), W(dst));
            }
            void vmovntdqa(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVNTDQA, 0x2A, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vmovntpd(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVNTPD, 0x2B, E_VEX_128_66_0F_WIG, R(src), W(dst));
            }
            void vmovntpd(const Mem256& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVNTPD, 0x2B, E_VEX_256_66_0F_WIG, R(src), W(dst));
            }
            void vmovntps(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVNTPS, 0x2B, E_VEX_128_0F_WIG, R(src), W(dst));
            }
            void vmovntps(const Mem256& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVNTPS, 0x2B, E_VEX_256_0F_WIG, R(src), W(dst));
            }
            void vmovsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MOVSD, 0x10, E_VEX_LIG | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vmovsd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_MOVSD, 0x10, E_VEX_LIG | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovsd(const Mem64& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSD, 0x11, E_VEX_LIG | E_VEX_F2_0F | E_VEX_WIG, R(src), W(dst));
            }
            void vmovshdup(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSHDUP, 0x16, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovshdup(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVSHDUP, 0x16, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovshdup(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVSHDUP, 0x16, E_VEX_256 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovshdup(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVSHDUP, 0x16, E_VEX_256 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovsldup(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSLDUP, 0x12, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovsldup(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVSLDUP, 0x12, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovsldup(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVSLDUP, 0x12, E_VEX_256 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovsldup(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVSLDUP, 0x12, E_VEX_256 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MOVSS, 0x10, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vmovss(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_MOVSS, 0x10, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src));
            }
            void vmovss(const Mem32& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVSS, 0x11, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, R(src), W(dst));
            }
            void vmovupd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVUPD, 0x10, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vmovupd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVUPD, 0x10, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vmovupd(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVUPD, 0x11, E_VEX_128_66_0F_WIG, R(src), W(dst));
            }
            void vmovupd(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVUPD, 0x10, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vmovupd(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVUPD, 0x10, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vmovupd(const Mem256& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVUPD, 0x11, E_VEX_256_66_0F_WIG, R(src), W(dst));
            }
            void vmovups(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVUPS, 0x10, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vmovups(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_MOVUPS, 0x10, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vmovups(const Mem128& dst, const XmmReg& src)
            {
                AppendInstr(I_MOVUPS, 0x11, E_VEX_128_0F_WIG, R(src), W(dst));
            }
            void vmovups(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVUPS, 0x10, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vmovups(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVUPS, 0x10, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vmovups(const Mem256& dst, const YmmReg& src)
            {
                AppendInstr(I_MOVUPS, 0x11, E_VEX_256_0F_WIG, R(src), W(dst));
            }
            void vmpsadbw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& i)
            {
                AppendInstr(I_MPSADBW, 0x42, E_VEX_128 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src2), R(src1), i);
            }
            void vmpsadbw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& i)
            {
                AppendInstr(I_MPSADBW, 0x42, E_VEX_128 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src2), R(src1), i);
            }
            void vmulpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MULPD, 0x59, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmulpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_MULPD, 0x59, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmulpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_MULPD, 0x59, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmulpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_MULPD, 0x59, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmulps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MULPS, 0x59, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmulps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_MULPS, 0x59, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmulps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_MULPS, 0x59, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmulps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_MULPS, 0x59, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vmulsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MULSD, 0x59, E_VEX_LIG | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vmulsd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_MULSD, 0x59, E_VEX_LIG | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vmulss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_MULSS, 0x59, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vmulss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_MULSS, 0x59, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vorpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ORPD, 0x56, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vorpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ORPD, 0x56, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vorpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ORPD, 0x56, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vorpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ORPD, 0x56, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vorps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_ORPS, 0x56, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vorps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_ORPS, 0x56, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vorps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_ORPS, 0x56, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vorps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_ORPS, 0x56, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpabsb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PABSB, 0x1C, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsb(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PABSB, 0x1C, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PABSW, 0x1D, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PABSW, 0x1D, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PABSD, 0x1E, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PABSD, 0x1E, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpacksswb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PACKSSWB, 0x63, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpacksswb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PACKSSWB, 0x63, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackssdw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PACKSSDW, 0x6B, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackssdw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PACKSSDW, 0x6B, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackuswb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PACKUSWB, 0x67, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackuswb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PACKUSWB, 0x67, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackusdw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PACKUSDW, 0x2B, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpackusdw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PACKUSDW, 0x2B, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PADDB, 0xFC, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PADDB, 0xFC, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PADDW, 0xFD, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PADDW, 0xFD, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PADDD, 0xFE, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PADDD, 0xFE, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PADDQ, 0xD4, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PADDQ, 0xD4, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddsb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PADDSB, 0xEC, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddsb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PADDSB, 0xEC, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddsw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PADDSW, 0xED, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddsw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PADDSW, 0xED, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddusb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PADDUSB, 0xDC, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddusb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PADDUSB, 0xDC, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddusw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PADDUSW, 0xDD, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddusw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PADDUSW, 0xDD, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpalignr(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& i)
            {
                AppendInstr(I_PALIGNR, 0x0F, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), i);
            }
            void vpalignr(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& i)
            {
                AppendInstr(I_PALIGNR, 0x0F, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), i);
            }
            void vpand(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PAND, 0xDB, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpand(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PAND, 0xDB, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpandn(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PANDN, 0xDF, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpandn(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PANDN, 0xDF, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpavgb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PAVGB, 0xE0, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpavgb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PAVGB, 0xE0, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpavgw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PAVGW, 0xE3, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpavgw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PAVGW, 0xE3, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpblendvb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const XmmReg& mask)
            {
                AppendInstr(I_PBLENDVB, 0x4C, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src2), R(src1), R(mask));
            }
            void vpblendvb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const XmmReg& mask)
            {
                AppendInstr(I_PBLENDVB, 0x4C, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src2), R(src1), R(mask));
            }
            void vpblendw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_PBLENDW, 0x0E, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vpblendw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& mask)
            {
                AppendInstr(I_PBLENDW, 0x0E, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void pclmulqdq(const XmmReg& dst, const XmmReg& src, const Imm8& mask)
            {
                AppendInstr(I_PCLMULQDQ, 0x0F3A44, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void pclmulqdq(const XmmReg& dst, const Mem128& src, const Imm8& mask)
            {
                AppendInstr(I_PCLMULQDQ, 0x0F3A44, E_MANDATORY_PREFIX_66, RW(dst), R(src), mask);
            }
            void vpclmulqdq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_PCLMULQDQ, 0x44, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vpclmulqdq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& mask)
            {
                AppendInstr(I_PCLMULQDQ, 0x44, E_VEX_128 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vpcmpeqb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PCMPEQB, 0x74, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PCMPEQB, 0x74, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PCMPEQW, 0x75, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PCMPEQW, 0x75, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PCMPEQD, 0x76, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PCMPEQD, 0x76, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PCMPEQQ, 0x29, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PCMPEQQ, 0x29, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PCMPGTB, 0x64, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PCMPGTB, 0x64, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PCMPGTW, 0x65, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PCMPGTW, 0x65, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PCMPGTD, 0x66, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PCMPGTD, 0x66, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PCMPGTQ, 0x37, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PCMPGTQ, 0x37, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpestri(const Reg& result, const XmmReg& src1, const Reg& len1, const XmmReg& src2, const Reg& len2, const Imm8& mode)
            {
                AppendInstr(I_PCMPESTRI, 0x61, E_VEX_128 | E_VEX_66_0F3A, R(src1), R(src2), mode, Dummy(W(result), ecx), Dummy(R(len1), eax), Dummy(R(len2), edx));
            }
            void vpcmpestri(const Reg& result, const XmmReg& src1, const Reg& len1, const Mem128& src2, const Reg& len2, const Imm8& mode)
            {
                AppendInstr(I_PCMPESTRI, 0x61, E_VEX_128 | E_VEX_66_0F3A, R(src1), R(src2), mode, Dummy(W(result), ecx), Dummy(R(len1), eax), Dummy(R(len2), edx));
            }
            void vpcmpestrm(const XmmReg& result, const XmmReg& src1, const Reg& len1, const XmmReg& src2, const Reg& len2, const Imm8& mode)
            {
                AppendInstr(I_PCMPESTRM, 0x60, E_VEX_128 | E_VEX_66_0F3A, R(src1), R(src2), mode, Dummy(W(result), xmm0), Dummy(R(len1), eax), Dummy(R(len2), edx));
            }
            void vpcmpestrm(const XmmReg& result, const XmmReg& src1, const Reg& len1, const Mem128& src2, const Reg& len2, const Imm8& mode)
            {
                AppendInstr(I_PCMPESTRM, 0x60, E_VEX_128 | E_VEX_66_0F3A, R(src1), R(src2), mode, Dummy(W(result), xmm0), Dummy(R(len1), eax), Dummy(R(len2), edx));
            }
            void vpcmpistri(const Reg& result, const XmmReg& src1, const XmmReg& src2, const Imm8& mode)
            {
                AppendInstr(I_PCMPISTRI, 0x63, E_VEX_128 | E_VEX_66_0F3A, R(src1), R(src2), mode, Dummy(W(result), ecx));
            }
            void vpcmpistri(const Reg& result, const XmmReg& src1, const Mem128& src2, const Imm8& mode)
            {
                AppendInstr(I_PCMPISTRI, 0x63, E_VEX_128 | E_VEX_66_0F3A, R(src1), R(src2), mode, Dummy(W(result), ecx));
            }
            void vpcmpistrm(const XmmReg& result, const XmmReg& src1, const XmmReg& src2, const Imm8& mode)
            {
                AppendInstr(I_PCMPISTRM, 0x62, E_VEX_128 | E_VEX_66_0F3A, R(src1), R(src2), mode, Dummy(W(result), xmm0));
            }
            void vpcmpistrm(const XmmReg& result, const XmmReg& src1, const Mem128& src2, const Imm8& mode)
            {
                AppendInstr(I_PCMPISTRM, 0x62, E_VEX_128 | E_VEX_66_0F3A, R(src1), R(src2), mode, Dummy(W(result), xmm0));
            }
            void vpermilpd(const XmmReg& dst, const XmmReg& src, const XmmReg& ctrl)
            {
                AppendInstr(I_VPERMILPD, 0x0D, E_VEX_128_66_0F38_W0, W(dst), R(ctrl), R(src));
            }
            void vpermilpd(const XmmReg& dst, const XmmReg& src, const Mem128& ctrl)
            {
                AppendInstr(I_VPERMILPD, 0x0D, E_VEX_128_66_0F38_W0, W(dst), R(ctrl), R(src));
            }
            void vpermilpd(const YmmReg& dst, const YmmReg& src, const YmmReg& ctrl)
            {
                AppendInstr(I_VPERMILPD, 0x0D, E_VEX_256_66_0F38_W0, W(dst), R(ctrl), R(src));
            }
            void vpermilpd(const YmmReg& dst, const YmmReg& src, const Mem256& ctrl)
            {
                AppendInstr(I_VPERMILPD, 0x0D, E_VEX_256_66_0F38_W0, W(dst), R(ctrl), R(src));
            }
            void vpermilpd(const XmmReg& dst, const XmmReg& src, const Imm8& ctrl)
            {
                AppendInstr(I_VPERMILPD, 0x05, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src), ctrl);
            }
            void vpermilpd(const XmmReg& dst, const Mem128& src, const Imm8& ctrl)
            {
                AppendInstr(I_VPERMILPD, 0x05, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src), ctrl);
            }
            void vpermilpd(const YmmReg& dst, const YmmReg& src, const Imm8& ctrl)
            {
                AppendInstr(I_VPERMILPD, 0x05, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src), ctrl);
            }
            void vpermilpd(const YmmReg& dst, const Mem256& src, const Imm8& ctrl)
            {
                AppendInstr(I_VPERMILPD, 0x05, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src), ctrl);
            }
            void vpermilps(const XmmReg& dst, const XmmReg& src, const XmmReg& ctrl)
            {
                AppendInstr(I_VPERMILPS, 0x0C, E_VEX_128_66_0F38_W0, W(dst), R(ctrl), R(src));
            }
            void vpermilps(const XmmReg& dst, const XmmReg& src, const Mem128& ctrl)
            {
                AppendInstr(I_VPERMILPS, 0x0C, E_VEX_128_66_0F38_W0, W(dst), R(ctrl), R(src));
            }
            void vpermilps(const YmmReg& dst, const YmmReg& src, const YmmReg& ctrl)
            {
                AppendInstr(I_VPERMILPS, 0x0C, E_VEX_256_66_0F38_W0, W(dst), R(ctrl), R(src));
            }
            void vpermilps(const YmmReg& dst, const YmmReg& src, const Mem256& ctrl)
            {
                AppendInstr(I_VPERMILPS, 0x0C, E_VEX_256_66_0F38_W0, W(dst), R(ctrl), R(src));
            }
            void vpermilps(const XmmReg& dst, const XmmReg& src, const Imm8& ctrl)
            {
                AppendInstr(I_VPERMILPS, 0x04, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src), ctrl);
            }
            void vpermilps(const XmmReg& dst, const Mem128& src, const Imm8& ctrl)
            {
                AppendInstr(I_VPERMILPS, 0x04, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src), ctrl);
            }
            void vpermilps(const YmmReg& dst, const YmmReg& src, const Imm8& ctrl)
            {
                AppendInstr(I_VPERMILPS, 0x04, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src), ctrl);
            }
            void vpermilps(const YmmReg& dst, const Mem256& src, const Imm8& ctrl)
            {
                AppendInstr(I_VPERMILPS, 0x04, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src), ctrl);
            }
            void vperm2f128(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& ctrl)
            {
                AppendInstr(I_VPERM2F128, 0x06, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src2), R(src1), ctrl);
            }
            void vperm2f128(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& ctrl)
            {
                AppendInstr(I_VPERM2F128, 0x06, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src2), R(src1), ctrl);
            }
            void vpextrb(const Reg32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRB, 0x14, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, R(src), W(dst), i);
            }
            void vpextrb(const Mem8& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRB, 0x14, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, R(src), W(dst), i);
            }
            void vpextrw(const Reg32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRW, 0xC5, E_VEX_128 | E_VEX_66_0F | E_VEX_W0, W(dst), R(src), i);
            }
            void vpextrw(const Mem16& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRW, 0x15, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, R(src), W(dst), i);
            }
            void vpextrd(const Reg32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRD, 0x16, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, R(src), W(dst), i);
            }
            void vpextrd(const Mem32& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRD, 0x16, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, R(src), W(dst), i);
            }
            void vpextrb(const Reg64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRB, 0x14, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, R(src), W(dst), i);
            }
            void vpextrw(const Reg64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRW, 0xC5, E_VEX_128 | E_VEX_66_0F | E_VEX_W0, W(dst), R(src), i);
            }
            void vpextrd(const Reg64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRD, 0x16, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, R(src), W(dst), i);
            }
            void vpextrq(const Reg64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRQ, 0x16, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W1, R(src), W(dst), i);
            }
            void vpextrq(const Mem64& dst, const XmmReg& src, const Imm8& i)
            {
                AppendInstr(I_PEXTRQ, 0x16, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W1, R(src), W(dst), i);
            }
            void vphaddw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PHADDW, 0x01, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PHADDW, 0x01, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PHADDD, 0x02, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PHADDD, 0x02, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddsw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PHADDSW, 0x03, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddsw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PHADDSW, 0x03, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphminposuw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PHMINPOSUW, 0x41, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vphminposuw(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_PHMINPOSUW, 0x41, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vphsubw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PHSUBW, 0x05, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PHSUBW, 0x05, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PHSUBD, 0x06, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PHSUBD, 0x06, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubsw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PHSUBSW, 0x07, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubsw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PHSUBSW, 0x07, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpinsrb(const XmmReg& dst, const XmmReg& src, const Reg32& val, const Imm8& i)
            {
                AppendInstr(I_PINSRB, 0x20, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(val), R(src), i);
            }
            void vpinsrb(const XmmReg& dst, const XmmReg& src, const Mem8& val, const Imm8& i)
            {
                AppendInstr(I_PINSRB, 0x20, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(val), R(src), i);
            }
            void vpinsrw(const XmmReg& dst, const XmmReg& src, const Reg32& val, const Imm8& i)
            {
                AppendInstr(I_PINSRW, 0xC4, E_VEX_128 | E_VEX_66_0F | E_VEX_W0, W(dst), R(val), R(src), i);
            }
            void vpinsrw(const XmmReg& dst, const XmmReg& src, const Mem16& val, const Imm8& i)
            {
                AppendInstr(I_PINSRW, 0xC4, E_VEX_128 | E_VEX_66_0F | E_VEX_W0, W(dst), R(val), R(src), i);
            }
            void vpinsrd(const XmmReg& dst, const XmmReg& src, const Reg32& val, const Imm8& i)
            {
                AppendInstr(I_PINSRD, 0x22, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(val), R(src), i);
            }
            void vpinsrd(const XmmReg& dst, const XmmReg& src, const Mem32& val, const Imm8& i)
            {
                AppendInstr(I_PINSRD, 0x22, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(val), R(src), i);
            }
            void vpinsrb(const XmmReg& dst, const XmmReg& src, const Reg64& val, const Imm8& i)
            {
                AppendInstr(I_PINSRB, 0x20, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(val), R(src), i);
            }
            void vpinsrw(const XmmReg& dst, const XmmReg& src, const Reg64& val, const Imm8& i)
            {
                AppendInstr(I_PINSRW, 0xC4, E_VEX_128 | E_VEX_66_0F | E_VEX_W0, W(dst), R(val), R(src), i);
            }
            void vpinsrd(const XmmReg& dst, const XmmReg& src, const Reg64& val, const Imm8& i)
            {
                AppendInstr(I_PINSRD, 0x22, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(val), R(src), i);
            }
            void vpinsrq(const XmmReg& dst, const XmmReg& src, const Reg64& val, const Imm8& i)
            {
                AppendInstr(I_PINSRQ, 0x22, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W1, W(dst), R(val), R(src), i);
            }
            void vpinsrq(const XmmReg& dst, const XmmReg& src, const Mem64& val, const Imm8& i)
            {
                AppendInstr(I_PINSRQ, 0x22, E_VEX_128 | E_VEX_66_0F3A | E_VEX_W1, W(dst), R(val), R(src), i);
            }
            void vpmaddwd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMADDWD, 0xF5, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaddwd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMADDWD, 0xF5, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaddubsw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMADDUBSW, 0x04, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaddubsw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMADDUBSW, 0x04, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMAXSB, 0x3C, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMAXSB, 0x3C, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMAXSW, 0xEE, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMAXSW, 0xEE, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMAXSD, 0x3D, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMAXSD, 0x3D, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxub(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMAXUB, 0xDE, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxub(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMAXUB, 0xDE, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxuw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMAXUW, 0x3E, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxuw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMAXUW, 0x3E, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxud(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMAXUD, 0x3F, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxud(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMAXUD, 0x3F, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMINSB, 0x38, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMINSB, 0x38, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMINSW, 0xEA, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMINSW, 0xEA, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMINSD, 0x39, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMINSD, 0x39, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminub(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMINUB, 0xDA, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpminub(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMINUB, 0xDA, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpminuw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMINUW, 0x3A, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminuw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMINUW, 0x3A, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminud(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMINUD, 0x3B, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminud(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMINUD, 0x3B, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmovmskb(const Reg32& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVMSKB, 0xD7, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vpmovmskb(const Reg64& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVMSKB, 0xD7, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vpmovsxbw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXBW, 0x20, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbw(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVSXBW, 0x20, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXBD, 0x21, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbd(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVSXBD, 0x21, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXBQ, 0x22, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbq(const XmmReg& dst, const Mem16& src)
            {
                AppendInstr(I_PMOVSXBQ, 0x22, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxwd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXWD, 0x23, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxwd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVSXWD, 0x23, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxwq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXWQ, 0x24, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxwq(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVSXWQ, 0x24, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxdq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXDQ, 0x25, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxdq(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVSXDQ, 0x25, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXBW, 0x30, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbw(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVZXBW, 0x30, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXBD, 0x31, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbd(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVZXBD, 0x31, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXBQ, 0x32, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbq(const XmmReg& dst, const Mem16& src)
            {
                AppendInstr(I_PMOVZXBQ, 0x32, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxwd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXWD, 0x33, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxwd(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVZXWD, 0x33, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxwq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXWQ, 0x34, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxwq(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVZXWQ, 0x34, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxdq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXDQ, 0x35, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxdq(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVZXDQ, 0x35, E_VEX_128_66_0F38_WIG, W(dst), R(src));
            }
            void vpmulhuw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMULHUW, 0xE4, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhuw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMULHUW, 0xE4, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhrsw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMULHRSW, 0x0B, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhrsw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMULHRSW, 0x0B, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMULHW, 0xE5, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMULHW, 0xE5, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmullw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMULLW, 0xD5, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmullw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMULLW, 0xD5, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulld(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMULLD, 0x40, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulld(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMULLD, 0x40, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmuludq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMULUDQ, 0xF4, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmuludq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMULUDQ, 0xF4, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmuldq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PMULDQ, 0x28, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmuldq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PMULDQ, 0x28, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpor(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_POR, 0xEB, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpor(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_POR, 0xEB, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsadbw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSADBW, 0xF6, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsadbw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSADBW, 0xF6, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpshufb(const XmmReg& dst, const XmmReg& src, const XmmReg& order)
            {
                AppendInstr(I_PSHUFB, 0x00, E_VEX_128_66_0F38_WIG, W(dst), R(order), R(src));
            }
            void vpshufb(const XmmReg& dst, const XmmReg& src, const Mem128& order)
            {
                AppendInstr(I_PSHUFB, 0x00, E_VEX_128_66_0F38_WIG, W(dst), R(order), R(src));
            }
            void vpshufd(const XmmReg& dst, const XmmReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFD, 0x70, E_VEX_128_66_0F_WIG, W(dst), R(src), order);
            }
            void vpshufd(const XmmReg& dst, const Mem128& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFD, 0x70, E_VEX_128_66_0F_WIG, W(dst), R(src), order);
            }
            void vpshufhw(const XmmReg& dst, const XmmReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFHW, 0x70, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src), order);
            }
            void vpshufhw(const XmmReg& dst, const Mem128& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFHW, 0x70, E_VEX_128 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src), order);
            }
            void vpshuflw(const XmmReg& dst, const XmmReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFLW, 0x70, E_VEX_128 | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src), order);
            }
            void vpshuflw(const XmmReg& dst, const Mem128& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFLW, 0x70, E_VEX_128 | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src), order);
            }
            void vpsignb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSIGNB, 0x08, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSIGNB, 0x08, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSIGNW, 0x09, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSIGNW, 0x09, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSIGND, 0x0A, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSIGND, 0x0A, E_VEX_128_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsllw(const XmmReg& dst, const XmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSLLW, 0xF1, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsllw(const XmmReg& dst, const XmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSLLW, 0xF1, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsllw(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSLLW, 0x71, E_VEX_128_66_0F_WIG, Imm8(6), R(src), W(dst), count);
            }
            void vpslld(const XmmReg& dst, const XmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSLLD, 0xF2, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpslld(const XmmReg& dst, const XmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSLLD, 0xF2, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpslld(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSLLD, 0x72, E_VEX_128_66_0F_WIG, Imm8(6), R(src), W(dst), count);
            }
            void vpsllq(const XmmReg& dst, const XmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSLLQ, 0xF3, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsllq(const XmmReg& dst, const XmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSLLQ, 0xF3, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsllq(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSLLQ, 0x73, E_VEX_128_66_0F_WIG, Imm8(6), R(src), W(dst), count);
            }
            void vpslldq(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSLLDQ, 0x73, E_VEX_128_66_0F_WIG, Imm8(7), R(src), W(dst), count);
            }
            void vpsraw(const XmmReg& dst, const XmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRAW, 0xE1, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsraw(const XmmReg& dst, const XmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRAW, 0xE1, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsraw(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRAW, 0x71, E_VEX_128_66_0F_WIG, Imm8(4), R(src), W(dst), count);
            }
            void vpsrad(const XmmReg& dst, const XmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRAD, 0xE2, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrad(const XmmReg& dst, const XmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRAD, 0xE2, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrad(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRAD, 0x72, E_VEX_128_66_0F_WIG, Imm8(4), R(src), W(dst), count);
            }
            void vpsrlw(const XmmReg& dst, const XmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRLW, 0xD1, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrlw(const XmmReg& dst, const XmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRLW, 0xD1, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrlw(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRLW, 0x71, E_VEX_128_66_0F_WIG, Imm8(2), R(src), W(dst), count);
            }
            void vpsrld(const XmmReg& dst, const XmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRLD, 0xD2, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrld(const XmmReg& dst, const XmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRLD, 0xD2, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrld(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRLD, 0x72, E_VEX_128_66_0F_WIG, Imm8(2), R(src), W(dst), count);
            }
            void vpsrlq(const XmmReg& dst, const XmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRLQ, 0xD3, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrlq(const XmmReg& dst, const XmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRLQ, 0xD3, E_VEX_128_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrlq(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRLQ, 0x73, E_VEX_128_66_0F_WIG, Imm8(2), R(src), W(dst), count);
            }
            void vpsrldq(const XmmReg& dst, const XmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRLDQ, 0x73, E_VEX_128_66_0F_WIG, Imm8(3), R(src), W(dst), count);
            }
            void vptest(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PTEST, 0x17, E_VEX_128_66_0F38_WIG, R(src1), R(src2));
            }
            void vptest(const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PTEST, 0x17, E_VEX_128_66_0F38_WIG, R(src1), R(src2));
            }
            void vptest(const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PTEST, 0x17, E_VEX_256_66_0F38_WIG, R(src1), R(src2));
            }
            void vptest(const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PTEST, 0x17, E_VEX_256_66_0F38_WIG, R(src1), R(src2));
            }
            void vtestps(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VTESTPS, 0x0E, E_VEX_128_66_0F38_W0, R(src1), R(src2));
            }
            void vtestps(const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VTESTPS, 0x0E, E_VEX_128_66_0F38_W0, R(src1), R(src2));
            }
            void vtestps(const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VTESTPS, 0x0E, E_VEX_256_66_0F38_W0, R(src1), R(src2));
            }
            void vtestps(const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VTESTPS, 0x0E, E_VEX_256_66_0F38_W0, R(src1), R(src2));
            }
            void vtestpd(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VTESTPD, 0x0F, E_VEX_128_66_0F38_W0, R(src1), R(src2));
            }
            void vtestpd(const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VTESTPD, 0x0F, E_VEX_128_66_0F38_W0, R(src1), R(src2));
            }
            void vtestpd(const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VTESTPD, 0x0F, E_VEX_256_66_0F38_W0, R(src1), R(src2));
            }
            void vtestpd(const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VTESTPD, 0x0F, E_VEX_256_66_0F38_W0, R(src1), R(src2));
            }
            void vpsubb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSUBB, 0xF8, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSUBB, 0xF8, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSUBW, 0xF9, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSUBW, 0xF9, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSUBD, 0xFA, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSUBD, 0xFA, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSUBQ, 0xFB, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSUBQ, 0xFB, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubsb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSUBSB, 0xE8, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubsb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSUBSB, 0xE8, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubsw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSUBSW, 0xE9, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubsw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSUBSW, 0xE9, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubusb(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSUBUSB, 0xD8, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubusb(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSUBUSB, 0xD8, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubusw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PSUBUSW, 0xD9, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubusw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PSUBUSW, 0xD9, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhbw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PUNPCKHBW, 0x68, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhbw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PUNPCKHBW, 0x68, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhwd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PUNPCKHWD, 0x69, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhwd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PUNPCKHWD, 0x69, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhdq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PUNPCKHDQ, 0x6A, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhdq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PUNPCKHDQ, 0x6A, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhqdq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PUNPCKHQDQ, 0x6D, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhqdq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PUNPCKHQDQ, 0x6D, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklbw(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PUNPCKLBW, 0x60, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklbw(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PUNPCKLBW, 0x60, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklwd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PUNPCKLWD, 0x61, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklwd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PUNPCKLWD, 0x61, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckldq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PUNPCKLDQ, 0x62, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckldq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PUNPCKLDQ, 0x62, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklqdq(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PUNPCKLQDQ, 0x6C, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklqdq(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PUNPCKLQDQ, 0x6C, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpxor(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_PXOR, 0xEF, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpxor(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_PXOR, 0xEF, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vrcpps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_RCPPS, 0x53, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vrcpps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_RCPPS, 0x53, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vrcpps(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_RCPPS, 0x53, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vrcpps(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_RCPPS, 0x53, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vrcpss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_RCPSS, 0x53, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vrcpss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_RCPSS, 0x53, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vrsqrtps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_RSQRTPS, 0x52, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vrsqrtps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_RSQRTPS, 0x52, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vrsqrtps(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_RSQRTPS, 0x52, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vrsqrtps(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_RSQRTPS, 0x52, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vrsqrtss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_RSQRTSS, 0x52, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vrsqrtss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_RSQRTSS, 0x52, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vroundpd(const XmmReg& dst, const XmmReg& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPD, 0x09, E_VEX_128 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src), mode);
            }
            void vroundpd(const XmmReg& dst, const Mem128& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPD, 0x09, E_VEX_128 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src), mode);
            }
            void vroundpd(const YmmReg& dst, const YmmReg& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPD, 0x09, E_VEX_256 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src), mode);
            }
            void vroundpd(const YmmReg& dst, const Mem256& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPD, 0x09, E_VEX_256 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src), mode);
            }
            void vroundps(const XmmReg& dst, const XmmReg& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPS, 0x08, E_VEX_128 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src), mode);
            }
            void vroundps(const XmmReg& dst, const Mem128& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPS, 0x08, E_VEX_128 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src), mode);
            }
            void vroundps(const YmmReg& dst, const YmmReg& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPS, 0x08, E_VEX_256 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src), mode);
            }
            void vroundps(const YmmReg& dst, const Mem256& src, const Imm8& mode)
            {
                AppendInstr(I_ROUNDPS, 0x08, E_VEX_256 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src), mode);
            }
            void vroundsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& mode)
            {
                AppendInstr(I_ROUNDSD, 0x0B, E_VEX_LIG | E_VEX_66_0F3A | E_VEX_WIG, RW(dst), R(src2), R(src1), mode);
            }
            void vroundsd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2, const Imm8& mode)
            {
                AppendInstr(I_ROUNDSD, 0x0B, E_VEX_LIG | E_VEX_66_0F3A | E_VEX_WIG, RW(dst), R(src2), R(src1), mode);
            }
            void vroundss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& mode)
            {
                AppendInstr(I_ROUNDSS, 0x0A, E_VEX_LIG | E_VEX_66_0F3A | E_VEX_WIG, RW(dst), R(src2), R(src1), mode);
            }
            void vroundss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2, const Imm8& mode)
            {
                AppendInstr(I_ROUNDSS, 0x0A, E_VEX_LIG | E_VEX_66_0F3A | E_VEX_WIG, RW(dst), R(src2), R(src1), mode);
            }
            void vshufpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& sel)
            {
                AppendInstr(I_SHUFPD, 0xC6, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1), sel);
            }
            void vshufpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& sel)
            {
                AppendInstr(I_SHUFPD, 0xC6, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1), sel);
            }
            void vshufpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& sel)
            {
                AppendInstr(I_SHUFPD, 0xC6, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1), sel);
            }
            void vshufpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& sel)
            {
                AppendInstr(I_SHUFPD, 0xC6, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1), sel);
            }
            void vshufps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& sel)
            {
                AppendInstr(I_SHUFPS, 0xC6, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1), sel);
            }
            void vshufps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& sel)
            {
                AppendInstr(I_SHUFPS, 0xC6, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1), sel);
            }
            void vshufps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& sel)
            {
                AppendInstr(I_SHUFPS, 0xC6, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1), sel);
            }
            void vshufps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& sel)
            {
                AppendInstr(I_SHUFPS, 0xC6, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1), sel);
            }
            void vsqrtpd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SQRTPD, 0x51, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vsqrtpd(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_SQRTPD, 0x51, E_VEX_128_66_0F_WIG, W(dst), R(src));
            }
            void vsqrtpd(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_SQRTPD, 0x51, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vsqrtpd(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_SQRTPD, 0x51, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vsqrtps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_SQRTPS, 0x51, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vsqrtps(const XmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_SQRTPS, 0x51, E_VEX_128_0F_WIG, W(dst), R(src));
            }
            void vsqrtps(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_SQRTPS, 0x51, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vsqrtps(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_SQRTPS, 0x51, E_VEX_256_0F_WIG, W(dst), R(src));
            }
            void vsqrtsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_SQRTSD, 0x51, E_VEX_LIG | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vsqrtsd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_SQRTSD, 0x51, E_VEX_LIG | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vsqrtss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_SQRTSS, 0x51, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vsqrtss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_SQRTSS, 0x51, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vstmxcsr(const Mem32& dst)
            {
                AppendInstr(I_STMXCSR, 0xAE, E_VEX_LZ | E_VEX_0F | E_VEX_WIG, Imm8(3), W(dst));
            }
            void vsubpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_SUBPD, 0x5C, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vsubpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_SUBPD, 0x5C, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vsubpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_SUBPD, 0x5C, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vsubpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_SUBPD, 0x5C, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vsubps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_SUBPS, 0x5C, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vsubps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_SUBPS, 0x5C, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vsubps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_SUBPS, 0x5C, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vsubps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_SUBPS, 0x5C, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vsubsd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_SUBSD, 0x5C, E_VEX_LIG | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vsubsd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_SUBSD, 0x5C, E_VEX_LIG | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vsubss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_SUBSS, 0x5C, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vsubss(const XmmReg& dst, const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_SUBSS, 0x5C, E_VEX_LIG | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src2), R(src1));
            }
            void vucomisd(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_UCOMISD, 0x2E, E_VEX_LIG | E_VEX_66_0F | E_VEX_WIG, R(src1), R(src2));
            }
            void vucomisd(const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_UCOMISD, 0x2E, E_VEX_LIG | E_VEX_66_0F | E_VEX_WIG, R(src1), R(src2));
            }
            void vucomiss(const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_UCOMISS, 0x2E, E_VEX_LIG | E_VEX_0F | E_VEX_WIG, R(src1), R(src2));
            }
            void vucomiss(const XmmReg& src1, const Mem32& src2)
            {
                AppendInstr(I_UCOMISS, 0x2E, E_VEX_LIG | E_VEX_0F | E_VEX_WIG, R(src1), R(src2));
            }
            void vunpckhpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_UNPCKHPD, 0x15, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpckhpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_UNPCKHPD, 0x15, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpckhpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_UNPCKHPD, 0x15, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpckhpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_UNPCKHPD, 0x15, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpckhps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_UNPCKHPS, 0x15, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpckhps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_UNPCKHPS, 0x15, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpckhps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_UNPCKHPS, 0x15, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpckhps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_UNPCKHPS, 0x15, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpcklpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_UNPCKLPD, 0x14, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpcklpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_UNPCKLPD, 0x14, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpcklpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_UNPCKLPD, 0x14, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpcklpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_UNPCKLPD, 0x14, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpcklps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_UNPCKLPS, 0x14, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpcklps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_UNPCKLPS, 0x14, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpcklps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_UNPCKLPS, 0x14, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vunpcklps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_UNPCKLPS, 0x14, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vxorpd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_XORPD, 0x57, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vxorpd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_XORPD, 0x57, E_VEX_128_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vxorpd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_XORPD, 0x57, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vxorpd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_XORPD, 0x57, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vxorps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_XORPS, 0x57, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vxorps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_XORPS, 0x57, E_VEX_128_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vxorps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_XORPS, 0x57, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vxorps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_XORPS, 0x57, E_VEX_256_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vzeroall()
            {
                AppendInstr(I_VZEROUPPER, 0x77, E_VEX_256_0F_WIG);
            }
            void vzeroupper()
            {
                AppendInstr(I_VZEROUPPER, 0x77, E_VEX_128_0F_WIG);
            }

            // FMA
            void vfmadd132pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD132PD, 0x98, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd132pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADD132PD, 0x98, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd132pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADD132PD, 0x98, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd132pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADD132PD, 0x98, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd213pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD213PD, 0xA8, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd213pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADD213PD, 0xA8, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd213pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADD213PD, 0xA8, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd213pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADD213PD, 0xA8, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd231pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD231PD, 0xB8, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd231pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADD231PD, 0xB8, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd231pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADD231PD, 0xB8, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd231pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADD231PD, 0xB8, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd132ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD132PS, 0x98, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd132ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADD132PS, 0x98, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd132ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADD132PS, 0x98, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd132ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADD132PS, 0x98, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd213ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD213PS, 0xA8, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd213ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADD213PS, 0xA8, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd213ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADD213PS, 0xA8, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd213ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADD213PS, 0xA8, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd231ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD231PS, 0xB8, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd231ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADD231PS, 0xB8, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd231ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADD231PS, 0xB8, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd231ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADD231PS, 0xB8, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd132sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD132SD, 0x99, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd132sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMADD132SD, 0x99, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd213sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD213SD, 0xA9, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd213sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMADD213SD, 0xA9, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd231sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD231SD, 0xB9, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd231sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMADD231SD, 0xB9, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmadd132ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD132SS, 0x99, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd132ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMADD132SS, 0x99, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd213ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD213SS, 0xA9, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd213ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMADD213SS, 0xA9, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd231ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADD231SS, 0xB9, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmadd231ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMADD231SS, 0xB9, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub132pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB132PD, 0x96, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub132pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADDSUB132PD, 0x96, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub132pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB132PD, 0x96, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub132pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADDSUB132PD, 0x96, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub213pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB213PD, 0xA6, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub213pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADDSUB213PD, 0xA6, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub213pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB213PD, 0xA6, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub213pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADDSUB213PD, 0xA6, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub231pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB231PD, 0xB6, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub231pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADDSUB231PD, 0xB6, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub231pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB231PD, 0xB6, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub231pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADDSUB231PD, 0xB6, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub132ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB132PS, 0x96, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub132ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADDSUB132PS, 0x96, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub132ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB132PS, 0x96, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub132ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADDSUB132PS, 0x96, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub213ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB213PS, 0xA6, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub213ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADDSUB213PS, 0xA6, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub213ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB213PS, 0xA6, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub213ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADDSUB213PS, 0xA6, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub231ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB231PS, 0xB6, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub231ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMADDSUB231PS, 0xB6, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub231ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMADDSUB231PS, 0xB6, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmaddsub231ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMADDSUB231PS, 0xB6, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd132pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD132PD, 0x97, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd132pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUBADD132PD, 0x97, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd132pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD132PD, 0x97, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd132pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUBADD132PD, 0x97, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd213pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD213PD, 0xA7, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd213pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUBADD213PD, 0xA7, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd213pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD213PD, 0xA7, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd213pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUBADD213PD, 0xA7, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd231pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD231PD, 0xB7, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd231pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUBADD231PD, 0xB7, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd231pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD231PD, 0xB7, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd231pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUBADD231PD, 0xB7, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd132ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD132PS, 0x97, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd132ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUBADD132PS, 0x97, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd132ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD132PS, 0x97, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd132ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUBADD132PS, 0x97, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd213ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD213PS, 0xA7, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd213ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUBADD213PS, 0xA7, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd213ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD213PS, 0xA7, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd213ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUBADD213PS, 0xA7, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd231ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD231PS, 0xB7, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd231ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUBADD231PS, 0xB7, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd231ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUBADD231PS, 0xB7, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsubadd231ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUBADD231PS, 0xB7, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub132pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB132PD, 0x9A, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub132pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUB132PD, 0x9A, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub132pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUB132PD, 0x9A, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub132pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUB132PD, 0x9A, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub213pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB213PD, 0xAA, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub213pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUB213PD, 0xAA, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub213pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUB213PD, 0xAA, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub213pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUB213PD, 0xAA, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub231pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB231PD, 0xBA, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub231pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUB231PD, 0xBA, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub231pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUB231PD, 0xBA, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub231pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUB231PD, 0xBA, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub132ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB132PS, 0x9A, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub132ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUB132PS, 0x9A, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub132ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUB132PS, 0x9A, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub132ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUB132PS, 0x9A, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub213ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB213PS, 0xAA, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub213ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUB213PS, 0xAA, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub213ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUB213PS, 0xAA, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub213ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUB213PS, 0xAA, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub231ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB231PS, 0xBA, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub231ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFMSUB231PS, 0xBA, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub231ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFMSUB231PS, 0xBA, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub231ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFMSUB231PS, 0xBA, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub132sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB132SD, 0x9B, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub132sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMSUB132SD, 0x9B, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub213sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB213SD, 0xAB, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub213sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMSUB213SD, 0xAB, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub231sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB231SD, 0xBB, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub231sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMSUB231SD, 0xBB, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfmsub132ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB132SS, 0x9B, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub132ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMSUB132SS, 0x9B, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub213ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB213SS, 0xAB, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub213ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMSUB213SS, 0xAB, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub231ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFMSUB231SS, 0xBB, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfmsub231ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFMSUB231SS, 0xBB, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD132PD, 0x9C, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMADD132PD, 0x9C, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMADD132PD, 0x9C, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMADD132PD, 0x9C, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD213PD, 0xAC, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMADD213PD, 0xAC, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMADD213PD, 0xAC, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMADD213PD, 0xAC, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD231PD, 0xBC, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMADD231PD, 0xBC, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMADD231PD, 0xBC, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMADD231PD, 0xBC, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD132PS, 0x9C, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMADD132PS, 0x9C, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMADD132PS, 0x9C, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMADD132PS, 0x9C, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD213PS, 0xAC, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMADD213PS, 0xAC, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMADD213PS, 0xAC, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMADD213PS, 0xAC, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD231PS, 0xBC, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMADD231PS, 0xBC, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMADD231PS, 0xBC, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMADD231PS, 0xBC, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD132SD, 0x9D, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMADD132SD, 0x9D, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD213SD, 0xAD, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMADD213SD, 0xAD, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD231SD, 0xBD, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMADD231SD, 0xBD, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD132SS, 0x9D, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd132ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMADD132SS, 0x9D, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD213SS, 0xAD, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd213ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMADD213SS, 0xAD, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMADD231SS, 0xBD, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmadd231ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMADD231SS, 0xBD, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB132PD, 0x9E, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMSUB132PD, 0x9E, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMSUB132PD, 0x9E, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMSUB132PD, 0x9E, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB213PD, 0xAE, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMSUB213PD, 0xAE, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMSUB213PD, 0xAE, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMSUB213PD, 0xAE, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231pd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB231PD, 0xBE, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231pd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMSUB231PD, 0xBE, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231pd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMSUB231PD, 0xBE, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231pd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMSUB231PD, 0xBE, E_VEX_256_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB132PS, 0x9E, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMSUB132PS, 0x9E, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMSUB132PS, 0x9E, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMSUB132PS, 0x9E, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB213PS, 0xAE, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMSUB213PS, 0xAE, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMSUB213PS, 0xAE, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMSUB213PS, 0xAE, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231ps(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB231PS, 0xBE, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231ps(const XmmReg& dst, const XmmReg& src1, const Mem128& src2)
            {
                AppendInstr(I_VFNMSUB231PS, 0xBE, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231ps(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_VFNMSUB231PS, 0xBE, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231ps(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_VFNMSUB231PS, 0xBE, E_VEX_256_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB132SD, 0x9F, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMSUB132SD, 0x9F, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB213SD, 0xAF, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMSUB213SD, 0xAF, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231sd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB231SD, 0xBF, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231sd(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMSUB231SD, 0xBF, E_VEX_128_66_0F38_W1, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB132SS, 0x9F, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub132ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMSUB132SS, 0x9F, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB213SS, 0xAF, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub213ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMSUB213SS, 0xAF, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231ss(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2)
            {
                AppendInstr(I_VFNMSUB231SS, 0xBF, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }
            void vfnmsub231ss(const XmmReg& dst, const XmmReg& src1, const Mem64& src2)
            {
                AppendInstr(I_VFNMSUB231SS, 0xBF, E_VEX_128_66_0F38_W0, RW(dst), R(src2), R(src1));
            }

            // F16C
            void rdfsbase(const Reg32& dst)
            {
                AppendInstr(I_RDFSBASE, 0x0FAE, E_MANDATORY_PREFIX_F3, Imm8(0), W(dst));
            }
            void rdfsbase(const Reg64& dst)
            {
                AppendInstr(I_RDFSBASE, 0x0FAE, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, Imm8(0), W(dst));
            }
            void rdgsbase(const Reg32& dst)
            {
                AppendInstr(I_RDGSBASE, 0x0FAE, E_MANDATORY_PREFIX_F3, Imm8(1), W(dst));
            }
            void rdgsbase(const Reg64& dst)
            {
                AppendInstr(I_RDGSBASE, 0x0FAE, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, Imm8(1), W(dst));
            }
            void rdrand(const Reg16& dst)
            {
                AppendInstr(I_RDRAND, 0x0FC7, E_OPERAND_SIZE_PREFIX, Imm8(6), W(dst));
            }
            void rdrand(const Reg32& dst)
            {
                AppendInstr(I_RDRAND, 0x0FC7, 0, Imm8(6), W(dst));
            }
            void rdrand(const Reg64& dst)
            {
                AppendInstr(I_RDRAND, 0x0FC7, E_REXW_PREFIX, Imm8(6), W(dst));
            }
            void wrfsbase(const Reg32& src)
            {
                AppendInstr(I_WRFSBASE, 0x0FAE, E_MANDATORY_PREFIX_F3, Imm8(2), R(src));
            }
            void wrfsbase(const Reg64& src)
            {
                AppendInstr(I_WRFSBASE, 0x0FAE, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, Imm8(2), R(src));
            }
            void wrgsbase(const Reg32& src)
            {
                AppendInstr(I_WRGSBASE, 0x0FAE, E_MANDATORY_PREFIX_F3, Imm8(3), R(src));
            }
            void wrgsbase(const Reg64& src)
            {
                AppendInstr(I_WRGSBASE, 0x0FAE, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, Imm8(3), R(src));
            }
            void vcvtph2ps(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VCVTPH2PS, 0x13, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vcvtph2ps(const YmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_VCVTPH2PS, 0x13, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vcvtph2ps(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VCVTPH2PS, 0x13, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vcvtph2ps(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_VCVTPH2PS, 0x13, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vcvtps2ph(const XmmReg& dst, const YmmReg& src, const Imm8& rc)
            {
                AppendInstr(I_VCVTPS2PH, 0x1D, E_VEX_256_66_0F3A_W0, R(src), W(dst), rc);
            }
            void vcvtps2ph(const Mem128& dst, const YmmReg& src, const Imm8& rc)
            {
                AppendInstr(I_VCVTPS2PH, 0x1D, E_VEX_256_66_0F3A_W0, R(src), W(dst), rc);
            }
            void vcvtps2ph(const XmmReg& dst, const XmmReg& src, const Imm8& rc)
            {
                AppendInstr(I_VCVTPS2PH, 0x1D, E_VEX_128_66_0F3A_W0, R(src), W(dst), rc);
            }
            void vcvtps2ph(const Mem64& dst, const XmmReg& src, const Imm8& rc)
            {
                AppendInstr(I_VCVTPS2PH, 0x1D, E_VEX_128_66_0F3A_W0, R(src), W(dst), rc);
            }

            // BMI2
            void andn(const Reg32& dst, const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_ANDN, 0xF2, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void andn(const Reg32& dst, const Reg32& src1, const Mem32& src2)
            {
                AppendInstr(I_ANDN, 0xF2, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void andn(const Reg64& dst, const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_ANDN, 0xF2, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void andn(const Reg64& dst, const Reg64& src1, const Mem64& src2)
            {
                AppendInstr(I_ANDN, 0xF2, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void bextr(const Reg32& dst, const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_BEXTR, 0xF7, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void bextr(const Reg32& dst, const Mem32& src1, const Reg32& src2)
            {
                AppendInstr(I_BEXTR, 0xF7, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void bextr(const Reg64& dst, const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_BEXTR, 0xF7, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void bextr(const Reg64& dst, const Mem64& src1, const Reg64& src2)
            {
                AppendInstr(I_BEXTR, 0xF7, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void blsi(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_BLSI, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, Imm8(3), R(src), W(dst));
            }
            void blsi(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_BLSI, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, Imm8(3), R(src), W(dst));
            }
            void blsi(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_BLSI, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, Imm8(3), R(src), W(dst));
            }
            void blsi(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_BLSI, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, Imm8(3), R(src), W(dst));
            }
            void blsmsk(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_BLSMSK, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, Imm8(2), R(src), W(dst));
            }
            void blsmsk(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_BLSMSK, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, Imm8(2), R(src), W(dst));
            }
            void blsmsk(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_BLSMSK, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, Imm8(2), R(src), W(dst));
            }
            void blsmsk(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_BLSMSK, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, Imm8(2), R(src), W(dst));
            }
            void blsr(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_BLSR, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, Imm8(1), R(src), W(dst));
            }
            void blsr(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_BLSR, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, Imm8(1), R(src), W(dst));
            }
            void blsr(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_BLSR, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, Imm8(1), R(src), W(dst));
            }
            void blsr(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_BLSR, 0xF3, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, Imm8(1), R(src), W(dst));
            }
            void bzhi(const Reg32& dst, const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_BZHI, 0xF5, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void bzhi(const Reg32& dst, const Mem32& src1, const Reg32& src2)
            {
                AppendInstr(I_BZHI, 0xF5, E_VEX_LZ | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void bzhi(const Reg64& dst, const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_BZHI, 0xF5, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void bzhi(const Reg64& dst, const Mem64& src1, const Reg64& src2)
            {
                AppendInstr(I_BZHI, 0xF5, E_VEX_LZ | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void lzcnt(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_LZCNT, 0x0FBD, E_MANDATORY_PREFIX_F3 | E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void lzcnt(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_LZCNT, 0x0FBD, E_MANDATORY_PREFIX_F3 | E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void lzcnt(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_LZCNT, 0x0FBD, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void lzcnt(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_LZCNT, 0x0FBD, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void lzcnt(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_LZCNT, 0x0FBD, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }
            void lzcnt(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_LZCNT, 0x0FBD, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }
            void mulx(const Reg32& dst1, const Reg32& dst2, const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_MULX, 0xF6, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W0, W(dst1), R(src2), W(dst2), Dummy(R(src1), edx));
            }
            void mulx(const Reg32& dst1, const Reg32& dst2, const Reg32& src1, const Mem32& src2)
            {
                AppendInstr(I_MULX, 0xF6, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W0, W(dst1), R(src2), W(dst2), Dummy(R(src1), edx));
            }
            void mulx(const Reg64& dst1, const Reg64& dst2, const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_MULX, 0xF6, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W1, W(dst1), R(src2), W(dst2), Dummy(R(src1), rdx));
            }
            void mulx(const Reg64& dst1, const Reg64& dst2, const Reg64& src1, const Mem64& src2)
            {
                AppendInstr(I_MULX, 0xF6, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W1, W(dst1), R(src2), W(dst2), Dummy(R(src1), rdx));
            }
            void pdep(const Reg32& dst, const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_PDEP, 0xF5, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void pdep(const Reg32& dst, const Reg32& src1, const Mem32& src2)
            {
                AppendInstr(I_PDEP, 0xF5, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void pdep(const Reg64& dst, const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_PDEP, 0xF5, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void pdep(const Reg64& dst, const Reg64& src1, const Mem64& src2)
            {
                AppendInstr(I_PDEP, 0xF5, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void pext(const Reg32& dst, const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_PEXT, 0xF5, E_VEX_LZ | E_VEX_F3 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void pext(const Reg32& dst, const Reg32& src1, const Mem32& src2)
            {
                AppendInstr(I_PEXT, 0xF5, E_VEX_LZ | E_VEX_F3 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src2), R(src1));
            }
            void pext(const Reg64& dst, const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_PEXT, 0xF5, E_VEX_LZ | E_VEX_F3 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void pext(const Reg64& dst, const Reg64& src1, const Mem64& src2)
            {
                AppendInstr(I_PEXT, 0xF5, E_VEX_LZ | E_VEX_F3 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src2), R(src1));
            }
            void rorx(const Reg32& dst, const Reg32& src, const Imm8& shift)
            {
                AppendInstr(I_RORX, 0xF0, E_VEX_LZ | E_VEX_F2 | E_VEX_0F3A | E_VEX_W0, W(dst), R(src), shift);
            }
            void rorx(const Reg32& dst, const Mem32& src, const Imm8& shift)
            {
                AppendInstr(I_RORX, 0xF0, E_VEX_LZ | E_VEX_F2 | E_VEX_0F3A | E_VEX_W0, W(dst), R(src), shift);
            }
            void rorx(const Reg64& dst, const Reg64& src, const Imm8& shift)
            {
                AppendInstr(I_RORX, 0xF0, E_VEX_LZ | E_VEX_F2 | E_VEX_0F3A | E_VEX_W1, W(dst), R(src), shift);
            }
            void rorx(const Reg64& dst, const Mem64& src, const Imm8& shift)
            {
                AppendInstr(I_RORX, 0xF0, E_VEX_LZ | E_VEX_F2 | E_VEX_0F3A | E_VEX_W1, W(dst), R(src), shift);
            }
            void sarx(const Reg32& dst, const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_SARX, 0xF7, E_VEX_LZ | E_VEX_F3 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void sarx(const Reg32& dst, const Mem32& src1, const Reg32& src2)
            {
                AppendInstr(I_SARX, 0xF7, E_VEX_LZ | E_VEX_F3 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void sarx(const Reg64& dst, const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_SARX, 0xF7, E_VEX_LZ | E_VEX_F3 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void sarx(const Reg64& dst, const Mem64& src1, const Reg64& src2)
            {
                AppendInstr(I_SARX, 0xF7, E_VEX_LZ | E_VEX_F3 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void shlx(const Reg32& dst, const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_SHLX, 0xF7, E_VEX_LZ | E_VEX_66 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void shlx(const Reg32& dst, const Mem32& src1, const Reg32& src2)
            {
                AppendInstr(I_SHLX, 0xF7, E_VEX_LZ | E_VEX_66 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void shlx(const Reg64& dst, const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_SHLX, 0xF7, E_VEX_LZ | E_VEX_66 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void shlx(const Reg64& dst, const Mem64& src1, const Reg64& src2)
            {
                AppendInstr(I_SHLX, 0xF7, E_VEX_LZ | E_VEX_66 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void shrx(const Reg32& dst, const Reg32& src1, const Reg32& src2)
            {
                AppendInstr(I_SHRX, 0xF7, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void shrx(const Reg32& dst, const Mem32& src1, const Reg32& src2)
            {
                AppendInstr(I_SHRX, 0xF7, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W0, W(dst), R(src1), R(src2));
            }
            void shrx(const Reg64& dst, const Reg64& src1, const Reg64& src2)
            {
                AppendInstr(I_SHRX, 0xF7, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void shrx(const Reg64& dst, const Mem64& src1, const Reg64& src2)
            {
                AppendInstr(I_SHRX, 0xF7, E_VEX_LZ | E_VEX_F2 | E_VEX_0F38 | E_VEX_W1, W(dst), R(src1), R(src2));
            }
            void tzcnt(const Reg16& dst, const Reg16& src)
            {
                AppendInstr(I_TZCNT, 0x0FBC, E_MANDATORY_PREFIX_F3 | E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void tzcnt(const Reg16& dst, const Mem16& src)
            {
                AppendInstr(I_TZCNT, 0x0FBC, E_MANDATORY_PREFIX_F3 | E_OPERAND_SIZE_PREFIX, W(dst), R(src));
            }
            void tzcnt(const Reg32& dst, const Reg32& src)
            {
                AppendInstr(I_TZCNT, 0x0FBC, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void tzcnt(const Reg32& dst, const Mem32& src)
            {
                AppendInstr(I_TZCNT, 0x0FBC, E_MANDATORY_PREFIX_F3, W(dst), R(src));
            }
            void tzcnt(const Reg64& dst, const Reg64& src)
            {
                AppendInstr(I_TZCNT, 0x0FBC, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }
            void tzcnt(const Reg64& dst, const Mem64& src)
            {
                AppendInstr(I_TZCNT, 0x0FBC, E_MANDATORY_PREFIX_F3 | E_REXW_PREFIX, W(dst), R(src));
            }
            void invpcid(const Reg64& type, const Mem128& desc)
            {
                AppendInstr(I_INVPCID, 0x0F3882, E_MANDATORY_PREFIX_66, W(type), R(desc));
            }

            // AVX2
            void vbroadcastss(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VBROADCASTSS, 0x18, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vbroadcastss(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VBROADCASTSS, 0x18, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vbroadcastsd(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VBROADCASTSD, 0x19, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vbroadcasti128(const YmmReg& dst, const Mem128& src)
            {
                AppendInstr(I_VBROADCASTI128, 0x5A, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vextracti128(const XmmReg& dst, const YmmReg& src, const Imm8& offset)
            {
                AppendInstr(I_VEXTRACTI128, 0x39, E_VEX_256_66_0F3A_W0, R(src), W(dst), offset);
            }
            void vextracti128(const Mem128& dst, const YmmReg& src, const Imm8& offset)
            {
                AppendInstr(I_VEXTRACTI128, 0x39, E_VEX_256_66_0F3A_W0, R(src), W(dst), offset);
            }
            void vgatherdps(const XmmReg& dst, const Mem32vxd& src, const XmmReg& mask)
            {
                AppendInstr(I_VGATHERDPS, 0x92, E_VEX_128_66_0F38_W0, RW(dst), R(src), R(mask));
            }
            void vgatherdps(const YmmReg& dst, const Mem32vyd& src, const YmmReg& mask)
            {
                AppendInstr(I_VGATHERDPS, 0x92, E_VEX_256_66_0F38_W0, RW(dst), R(src), R(mask));
            }
            void vgatherqps(const XmmReg& dst, const Mem64vxd& src, const XmmReg& mask)
            {
                AppendInstr(I_VGATHERQPS, 0x93, E_VEX_128_66_0F38_W0, RW(dst), R(src), R(mask));
            }
            void vgatherqps(const XmmReg& dst, const Mem64vyd& src, const XmmReg& mask)
            {
                AppendInstr(I_VGATHERQPS, 0x93, E_VEX_256_66_0F38_W0, RW(dst), R(src), R(mask));
            }
            void vgatherdpd(const XmmReg& dst, const Mem32vxq& src, const XmmReg& mask)
            {
                AppendInstr(I_VGATHERDPD, 0x92, E_VEX_128_66_0F38_W1, RW(dst), R(src), R(mask));
            }
            void vgatherdpd(const YmmReg& dst, const Mem32vxq& src, const YmmReg& mask)
            {
                AppendInstr(I_VGATHERDPD, 0x92, E_VEX_256_66_0F38_W1, RW(dst), R(src), R(mask));
            }
            void vgatherqpd(const XmmReg& dst, const Mem64vxq& src, const XmmReg& mask)
            {
                AppendInstr(I_VGATHERQPD, 0x93, E_VEX_128_66_0F38_W1, RW(dst), R(src), R(mask));
            }
            void vgatherqpd(const YmmReg& dst, const Mem64vyq& src, const YmmReg& mask)
            {
                AppendInstr(I_VGATHERQPD, 0x93, E_VEX_256_66_0F38_W1, RW(dst), R(src), R(mask));
            }
            void vinserti128(const YmmReg& dst, const YmmReg& src1, const XmmReg& src2, const Imm8& offset)
            {
                AppendInstr(I_VINSERTI128, 0x38, E_VEX_256_66_0F3A_W0, W(dst), R(src2), R(src1), offset);
            }
            void vinserti128(const YmmReg& dst, const YmmReg& src1, const Mem128& src2, const Imm8& offset)
            {
                AppendInstr(I_VINSERTI128, 0x38, E_VEX_256_66_0F3A_W0, W(dst), R(src2), R(src1), offset);
            }
            void vmovntdqa(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_MOVNTDQA, 0x2A, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vmpsadbw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& i)
            {
                AppendInstr(I_MPSADBW, 0x42, E_VEX_256 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src2), R(src1), i);
            }
            void vmpsadbw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& i)
            {
                AppendInstr(I_MPSADBW, 0x42, E_VEX_256 | E_VEX_66_0F3A | E_VEX_WIG, W(dst), R(src2), R(src1), i);
            }
            void vpabsb(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_PABSB, 0x1C, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsb(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_PABSB, 0x1C, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsw(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_PABSW, 0x1D, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsw(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_PABSW, 0x1D, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsd(const YmmReg& dst, const YmmReg& src)
            {
                AppendInstr(I_PABSD, 0x1E, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpabsd(const YmmReg& dst, const Mem256& src)
            {
                AppendInstr(I_PABSD, 0x1E, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpacksswb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PACKSSWB, 0x63, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpacksswb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PACKSSWB, 0x63, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackssdw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PACKSSDW, 0x6B, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackssdw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PACKSSDW, 0x6B, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackuswb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PACKUSWB, 0x67, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackuswb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PACKUSWB, 0x67, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpackusdw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PACKUSDW, 0x2B, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpackusdw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PACKUSDW, 0x2B, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PADDB, 0xFC, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PADDB, 0xFC, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PADDW, 0xFD, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PADDW, 0xFD, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PADDD, 0xFE, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PADDD, 0xFE, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PADDQ, 0xD4, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PADDQ, 0xD4, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddsb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PADDSB, 0xEC, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddsb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PADDSB, 0xEC, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddsw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PADDSW, 0xED, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddsw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PADDSW, 0xED, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddusb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PADDUSB, 0xDC, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddusb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PADDUSB, 0xDC, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddusw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PADDUSW, 0xDD, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpaddusw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PADDUSW, 0xDD, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpalignr(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& i)
            {
                AppendInstr(I_PALIGNR, 0x0F, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), i);
            }
            void vpalignr(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& i)
            {
                AppendInstr(I_PALIGNR, 0x0F, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), i);
            }
            void vpand(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PAND, 0xDB, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpand(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PAND, 0xDB, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpandn(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PANDN, 0xDF, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpandn(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PANDN, 0xDF, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpavgb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PAVGB, 0xE0, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpavgb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PAVGB, 0xE0, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpavgw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PAVGW, 0xE3, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpavgw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PAVGW, 0xE3, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpblendvb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const YmmReg& mask)
            {
                AppendInstr(I_PBLENDVB, 0x4C, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src2), R(src1), R(mask));
            }
            void vpblendvb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const YmmReg& mask)
            {
                AppendInstr(I_PBLENDVB, 0x4C, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W0, W(dst), R(src2), R(src1), R(mask));
            }
            void vpblendw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_PBLENDW, 0x0E, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vpblendw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& mask)
            {
                AppendInstr(I_PBLENDW, 0x0E, E_VEX_256 | E_VEX_66_0F3A, W(dst), R(src2), R(src1), mask);
            }
            void vpblendd(const XmmReg& dst, const XmmReg& src1, const XmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_PBLENDD, 0x02, E_VEX_128_66_0F3A_W0, W(dst), R(src2), R(src1), mask);
            }
            void vpblendd(const XmmReg& dst, const XmmReg& src1, const Mem128& src2, const Imm8& mask)
            {
                AppendInstr(I_PBLENDD, 0x02, E_VEX_128_66_0F3A_W0, W(dst), R(src2), R(src1), mask);
            }
            void vpblendd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& mask)
            {
                AppendInstr(I_PBLENDD, 0x02, E_VEX_256_66_0F3A_W0, W(dst), R(src2), R(src1), mask);
            }
            void vpblendd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& mask)
            {
                AppendInstr(I_PBLENDD, 0x02, E_VEX_256_66_0F3A_W0, W(dst), R(src2), R(src1), mask);
            }
            void vpbroadcastb(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VPBROADCASTB, 0x78, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastb(const XmmReg& dst, const Mem8& src)
            {
                AppendInstr(I_VPBROADCASTB, 0x78, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastb(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VPBROADCASTB, 0x78, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastb(const YmmReg& dst, const Mem8& src)
            {
                AppendInstr(I_VPBROADCASTB, 0x78, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastw(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VPBROADCASTW, 0x79, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastw(const XmmReg& dst, const Mem16& src)
            {
                AppendInstr(I_VPBROADCASTW, 0x79, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastw(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VPBROADCASTW, 0x79, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastw(const YmmReg& dst, const Mem16& src)
            {
                AppendInstr(I_VPBROADCASTW, 0x79, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastd(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VPBROADCASTD, 0x58, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastd(const XmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_VPBROADCASTD, 0x58, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastd(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VPBROADCASTD, 0x58, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastd(const YmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_VPBROADCASTD, 0x58, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastq(const XmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VPBROADCASTQ, 0x59, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastq(const XmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_VPBROADCASTQ, 0x59, E_VEX_128_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastq(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_VPBROADCASTQ, 0x59, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vpbroadcastq(const YmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_VPBROADCASTQ, 0x59, E_VEX_256_66_0F38_W0, W(dst), R(src));
            }
            void vpcmpeqb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PCMPEQB, 0x74, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PCMPEQB, 0x74, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PCMPEQW, 0x75, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PCMPEQW, 0x75, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PCMPEQD, 0x76, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PCMPEQD, 0x76, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PCMPEQQ, 0x29, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpeqq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PCMPEQQ, 0x29, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PCMPGTB, 0x64, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PCMPGTB, 0x64, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PCMPGTW, 0x65, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PCMPGTW, 0x65, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PCMPGTD, 0x66, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PCMPGTD, 0x66, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PCMPGTQ, 0x37, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpcmpgtq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PCMPGTQ, 0x37, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpermd(const YmmReg& dst, const YmmReg& offsets, const YmmReg& src)
            {
                AppendInstr(I_VPERMD, 0x36, E_VEX_256_66_0F38_W0, W(dst), R(src), R(offsets));
            }
            void vpermd(const YmmReg& dst, const YmmReg& offsets, const Mem256& src)
            {
                AppendInstr(I_VPERMD, 0x36, E_VEX_256_66_0F38_W0, W(dst), R(src), R(offsets));
            }
            void vpermq(const YmmReg& dst, const YmmReg& src, const Imm8& control)
            {
                AppendInstr(I_VPERMQ, 0x00, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W1, W(dst), R(src), control);
            }
            void vpermq(const YmmReg& dst, const Mem256& src, const Imm8& control)
            {
                AppendInstr(I_VPERMQ, 0x00, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W1, W(dst), R(src), control);
            }
            void vpermps(const YmmReg& dst, const YmmReg& offsets, const YmmReg& src)
            {
                AppendInstr(I_VPERMPS, 0x16, E_VEX_256_66_0F38_W0, W(dst), R(src), R(offsets));
            }
            void vpermps(const YmmReg& dst, const YmmReg& offsets, const Mem256& src)
            {
                AppendInstr(I_VPERMPS, 0x16, E_VEX_256_66_0F38_W0, W(dst), R(src), R(offsets));
            }
            void vpermpd(const YmmReg& dst, const YmmReg& src, const Imm8& control)
            {
                AppendInstr(I_VPERMPD, 0x01, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W1, W(dst), R(src), control);
            }
            void vpermpd(const YmmReg& dst, const Mem256& src, const Imm8& control)
            {
                AppendInstr(I_VPERMPD, 0x01, E_VEX_256 | E_VEX_66_0F3A | E_VEX_W1, W(dst), R(src), control);
            }
            void vperm2i128(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2, const Imm8& control)
            {
                AppendInstr(I_VPERM2I128, 0x46, E_VEX_256_66_0F3A_W0, W(dst), R(src2), R(src1), control);
            }
            void vperm2i128(const YmmReg& dst, const YmmReg& src1, const Mem256& src2, const Imm8& control)
            {
                AppendInstr(I_VPERM2I128, 0x46, E_VEX_256_66_0F3A_W0, W(dst), R(src2), R(src1), control);
            }
            void vpgatherdd(const XmmReg& dst, const Mem32vxd& src, const XmmReg& mask)
            {
                AppendInstr(I_VPGATHERDD, 0x90, E_VEX_128_66_0F38_W0, RW(dst), R(src), R(mask));
            }
            void vpgatherdd(const YmmReg& dst, const Mem32vyd& src, const YmmReg& mask)
            {
                AppendInstr(I_VPGATHERDD, 0x90, E_VEX_256_66_0F38_W0, RW(dst), R(src), R(mask));
            }
            void vpgatherqd(const XmmReg& dst, const Mem64vxd& src, const XmmReg& mask)
            {
                AppendInstr(I_VPGATHERQD, 0x91, E_VEX_128_66_0F38_W0, RW(dst), R(src), R(mask));
            }
            void vpgatherqd(const XmmReg& dst, const Mem64vyd& src, const XmmReg& mask)
            {
                AppendInstr(I_VPGATHERQD, 0x91, E_VEX_256_66_0F38_W0, RW(dst), R(src), R(mask));
            }
            void vpgatherdq(const XmmReg& dst, const Mem32vxq& src, const XmmReg& mask)
            {
                AppendInstr(I_VPGATHERDQ, 0x90, E_VEX_128_66_0F38_W1, RW(dst), R(src), R(mask));
            }
            void vpgatherdq(const YmmReg& dst, const Mem32vxq& src, const YmmReg& mask)
            {
                AppendInstr(I_VPGATHERDQ, 0x90, E_VEX_256_66_0F38_W1, RW(dst), R(src), R(mask));
            }
            void vpgatherqq(const XmmReg& dst, const Mem64vxq& src, const XmmReg& mask)
            {
                AppendInstr(I_VPGATHERQQ, 0x91, E_VEX_128_66_0F38_W1, RW(dst), R(src), R(mask));
            }
            void vpgatherqq(const YmmReg& dst, const Mem64vyq& src, const YmmReg& mask)
            {
                AppendInstr(I_VPGATHERQQ, 0x91, E_VEX_256_66_0F38_W1, RW(dst), R(src), R(mask));
            }
            void vphaddw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PHADDW, 0x01, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PHADDW, 0x01, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PHADDD, 0x02, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PHADDD, 0x02, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddsw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PHADDSW, 0x03, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphaddsw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PHADDSW, 0x03, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PHSUBW, 0x05, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PHSUBW, 0x05, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PHSUBD, 0x06, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PHSUBD, 0x06, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubsw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PHSUBSW, 0x07, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vphsubsw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PHSUBSW, 0x07, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaddwd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMADDWD, 0xF5, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaddwd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMADDWD, 0xF5, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaddubsw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMADDUBSW, 0x04, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaddubsw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMADDUBSW, 0x04, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaskmovd(const XmmReg& dst, const XmmReg& mask, const Mem128& src)
            {
                AppendInstr(I_VMASKMOVD, 0x8C, E_VEX_128_66_0F38_W0, W(dst), R(src), R(mask));
            }
            void vpmaskmovd(const YmmReg& dst, const YmmReg& mask, const Mem256& src)
            {
                AppendInstr(I_VMASKMOVD, 0x8C, E_VEX_256_66_0F38_W0, W(dst), R(src), R(mask));
            }
            void vpmaskmovq(const XmmReg& dst, const XmmReg& mask, const Mem128& src)
            {
                AppendInstr(I_VMASKMOVQ, 0x8C, E_VEX_128_66_0F38_W1, W(dst), R(src), R(mask));
            }
            void vpmaskmovq(const YmmReg& dst, const YmmReg& mask, const Mem256& src)
            {
                AppendInstr(I_VMASKMOVQ, 0x8C, E_VEX_256_66_0F38_W1, W(dst), R(src), R(mask));
            }
            void vpmaskmovd(const Mem128& dst, const XmmReg& mask, const XmmReg& src)
            {
                AppendInstr(I_VMASKMOVD, 0x8E, E_VEX_128_66_0F38_W0, R(src), W(dst), R(mask));
            }
            void vpmaskmovd(const Mem256& dst, const YmmReg& mask, const YmmReg& src)
            {
                AppendInstr(I_VMASKMOVD, 0x8E, E_VEX_256_66_0F38_W0, R(src), W(dst), R(mask));
            }
            void vpmaskmovq(const Mem128& dst, const XmmReg& mask, const XmmReg& src)
            {
                AppendInstr(I_VMASKMOVQ, 0x8E, E_VEX_128_66_0F38_W1, R(src), W(dst), R(mask));
            }
            void vpmaskmovq(const Mem256& dst, const YmmReg& mask, const YmmReg& src)
            {
                AppendInstr(I_VMASKMOVQ, 0x8E, E_VEX_256_66_0F38_W1, R(src), W(dst), R(mask));
            }
            void vpmaxsb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMAXSB, 0x3C, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMAXSB, 0x3C, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMAXSW, 0xEE, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMAXSW, 0xEE, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMAXSD, 0x3D, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxsd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMAXSD, 0x3D, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxub(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMAXUB, 0xDE, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxub(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMAXUB, 0xDE, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxuw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMAXUW, 0x3E, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxuw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMAXUW, 0x3E, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxud(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMAXUD, 0x3F, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmaxud(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMAXUD, 0x3F, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMINSB, 0x38, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMINSB, 0x38, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMINSW, 0xEA, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMINSW, 0xEA, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMINSD, 0x39, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminsd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMINSD, 0x39, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminub(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMINUB, 0xDA, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpminub(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMINUB, 0xDA, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpminuw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMINUW, 0x3A, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminuw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMINUW, 0x3A, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminud(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMINUD, 0x3B, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpminud(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMINUD, 0x3B, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmovmskb(const Reg32& dst, const YmmReg& src)
            {
                AppendInstr(I_PMOVMSKB, 0xD7, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vpmovmskb(const Reg64& dst, const YmmReg& src)
            {
                AppendInstr(I_PMOVMSKB, 0xD7, E_VEX_256_66_0F_WIG, W(dst), R(src));
            }
            void vpmovsxbw(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXBW, 0x20, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbw(const YmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVSXBW, 0x20, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbd(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXBD, 0x21, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbd(const YmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVSXBD, 0x21, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbq(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXBQ, 0x22, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxbq(const YmmReg& dst, const Mem16& src)
            {
                AppendInstr(I_PMOVSXBQ, 0x22, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxwd(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXWD, 0x23, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxwd(const YmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVSXWD, 0x23, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxwq(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXWQ, 0x24, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxwq(const YmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVSXWQ, 0x24, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxdq(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVSXDQ, 0x25, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovsxdq(const YmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVSXDQ, 0x25, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbw(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXBW, 0x30, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbw(const YmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVZXBW, 0x30, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbd(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXBD, 0x31, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbd(const YmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVZXBD, 0x31, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbq(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXBQ, 0x32, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxbq(const YmmReg& dst, const Mem16& src)
            {
                AppendInstr(I_PMOVZXBQ, 0x32, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxwd(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXWD, 0x33, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxwd(const YmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVZXWD, 0x33, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxwq(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXWQ, 0x34, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxwq(const YmmReg& dst, const Mem32& src)
            {
                AppendInstr(I_PMOVZXWQ, 0x34, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxdq(const YmmReg& dst, const XmmReg& src)
            {
                AppendInstr(I_PMOVZXDQ, 0x35, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmovzxdq(const YmmReg& dst, const Mem64& src)
            {
                AppendInstr(I_PMOVZXDQ, 0x35, E_VEX_256_66_0F38_WIG, W(dst), R(src));
            }
            void vpmulhuw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMULHUW, 0xE4, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhuw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMULHUW, 0xE4, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhrsw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMULHRSW, 0x0B, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhrsw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMULHRSW, 0x0B, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMULHW, 0xE5, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulhw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMULHW, 0xE5, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmullw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMULLW, 0xD5, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmullw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMULLW, 0xD5, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulld(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMULLD, 0x40, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmulld(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMULLD, 0x40, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmuludq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMULUDQ, 0xF4, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmuludq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMULUDQ, 0xF4, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpmuldq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PMULDQ, 0x28, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpmuldq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PMULDQ, 0x28, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpor(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_POR, 0xEB, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpor(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_POR, 0xEB, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsadbw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSADBW, 0xF6, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsadbw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSADBW, 0xF6, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpshufb(const YmmReg& dst, const YmmReg& src, const YmmReg& order)
            {
                AppendInstr(I_PSHUFB, 0x00, E_VEX_256_66_0F38_WIG, W(dst), R(order), R(src));
            }
            void vpshufb(const YmmReg& dst, const YmmReg& src, const Mem256& order)
            {
                AppendInstr(I_PSHUFB, 0x00, E_VEX_256_66_0F38_WIG, W(dst), R(order), R(src));
            }
            void vpshufd(const YmmReg& dst, const YmmReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFD, 0x70, E_VEX_256_66_0F_WIG, W(dst), R(src), order);
            }
            void vpshufd(const YmmReg& dst, const Mem256& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFD, 0x70, E_VEX_256_66_0F_WIG, W(dst), R(src), order);
            }
            void vpshufhw(const YmmReg& dst, const YmmReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFHW, 0x70, E_VEX_256 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src), order);
            }
            void vpshufhw(const YmmReg& dst, const Mem256& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFHW, 0x70, E_VEX_256 | E_VEX_F3_0F | E_VEX_WIG, W(dst), R(src), order);
            }
            void vpshuflw(const YmmReg& dst, const YmmReg& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFLW, 0x70, E_VEX_256 | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src), order);
            }
            void vpshuflw(const YmmReg& dst, const Mem256& src, const Imm8& order)
            {
                AppendInstr(I_PSHUFLW, 0x70, E_VEX_256 | E_VEX_F2_0F | E_VEX_WIG, W(dst), R(src), order);
            }
            void vpsignb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSIGNB, 0x08, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSIGNB, 0x08, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSIGNW, 0x09, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSIGNW, 0x09, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSIGND, 0x0A, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsignd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSIGND, 0x0A, E_VEX_256_66_0F38_WIG, W(dst), R(src2), R(src1));
            }
            void vpsllw(const YmmReg& dst, const YmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSLLW, 0xF1, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsllw(const YmmReg& dst, const YmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSLLW, 0xF1, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsllw(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSLLW, 0x71, E_VEX_256_66_0F_WIG, Imm8(6), R(src), W(dst), count);
            }
            void vpslld(const YmmReg& dst, const YmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSLLD, 0xF2, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpslld(const YmmReg& dst, const YmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSLLD, 0xF2, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpslld(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSLLD, 0x72, E_VEX_256_66_0F_WIG, Imm8(6), R(src), W(dst), count);
            }
            void vpsllq(const YmmReg& dst, const YmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSLLQ, 0xF3, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsllq(const YmmReg& dst, const YmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSLLQ, 0xF3, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsllq(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSLLQ, 0x73, E_VEX_256_66_0F_WIG, Imm8(6), R(src), W(dst), count);
            }
            void vpslldq(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSLLDQ, 0x73, E_VEX_256_66_0F_WIG, Imm8(7), R(src), W(dst), count);
            }
            void vpsllvd(const XmmReg& dst, const XmmReg& count, const XmmReg& src)
            {
                AppendInstr(I_VPSLLVD, 0x47, E_VEX_128_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsllvd(const XmmReg& dst, const XmmReg& count, const Mem128& src)
            {
                AppendInstr(I_VPSLLVD, 0x47, E_VEX_128_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsllvd(const YmmReg& dst, const YmmReg& count, const YmmReg& src)
            {
                AppendInstr(I_VPSLLVD, 0x47, E_VEX_256_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsllvd(const YmmReg& dst, const YmmReg& count, const Mem256& src)
            {
                AppendInstr(I_VPSLLVD, 0x47, E_VEX_256_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsllvq(const XmmReg& dst, const XmmReg& count, const XmmReg& src)
            {
                AppendInstr(I_VPSLLVQ, 0x47, E_VEX_128_66_0F38_W1, W(dst), R(src), R(count));
            }
            void vpsllvq(const XmmReg& dst, const XmmReg& count, const Mem128& src)
            {
                AppendInstr(I_VPSLLVQ, 0x47, E_VEX_128_66_0F38_W1, W(dst), R(src), R(count));
            }
            void vpsllvq(const YmmReg& dst, const YmmReg& count, const YmmReg& src)
            {
                AppendInstr(I_VPSLLVQ, 0x47, E_VEX_256_66_0F38_W1, W(dst), R(src), R(count));
            }
            void vpsllvq(const YmmReg& dst, const YmmReg& count, const Mem256& src)
            {
                AppendInstr(I_VPSLLVQ, 0x47, E_VEX_256_66_0F38_W1, W(dst), R(src), R(count));
            }
            void vpsraw(const YmmReg& dst, const YmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRAW, 0xE1, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsraw(const YmmReg& dst, const YmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRAW, 0xE1, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsraw(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRAW, 0x71, E_VEX_256_66_0F_WIG, Imm8(4), R(src), W(dst), count);
            }
            void vpsrad(const YmmReg& dst, const YmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRAD, 0xE2, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrad(const YmmReg& dst, const YmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRAD, 0xE2, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrad(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRAD, 0x72, E_VEX_256_66_0F_WIG, Imm8(4), R(src), W(dst), count);
            }
            void vpsravd(const XmmReg& dst, const XmmReg& count, const XmmReg& src)
            {
                AppendInstr(I_VPSRAVD, 0x46, E_VEX_128_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsravd(const XmmReg& dst, const XmmReg& count, const Mem128& src)
            {
                AppendInstr(I_VPSRAVD, 0x46, E_VEX_128_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsravd(const YmmReg& dst, const YmmReg& count, const YmmReg& src)
            {
                AppendInstr(I_VPSRAVD, 0x46, E_VEX_256_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsravd(const YmmReg& dst, const YmmReg& count, const Mem256& src)
            {
                AppendInstr(I_VPSRAVD, 0x46, E_VEX_256_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsrlw(const YmmReg& dst, const YmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRLW, 0xD1, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrlw(const YmmReg& dst, const YmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRLW, 0xD1, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrlw(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRLW, 0x71, E_VEX_256_66_0F_WIG, Imm8(2), R(src), W(dst), count);
            }
            void vpsrld(const YmmReg& dst, const YmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRLD, 0xD2, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrld(const YmmReg& dst, const YmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRLD, 0xD2, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrld(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRLD, 0x72, E_VEX_256_66_0F_WIG, Imm8(2), R(src), W(dst), count);
            }
            void vpsrlq(const YmmReg& dst, const YmmReg& src, const XmmReg& count)
            {
                AppendInstr(I_PSRLQ, 0xD3, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrlq(const YmmReg& dst, const YmmReg& src, const Mem128& count)
            {
                AppendInstr(I_PSRLQ, 0xD3, E_VEX_256_66_0F_WIG, W(dst), R(count), R(src));
            }
            void vpsrlq(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRLQ, 0x73, E_VEX_256_66_0F_WIG, Imm8(2), R(src), W(dst), count);
            }
            void vpsrldq(const YmmReg& dst, const YmmReg& src, const Imm8& count)
            {
                AppendInstr(I_PSRLDQ, 0x73, E_VEX_256_66_0F_WIG, Imm8(3), R(src), W(dst), count);
            }
            void vpsrlvd(const XmmReg& dst, const XmmReg& count, const XmmReg& src)
            {
                AppendInstr(I_VPSRLVD, 0x45, E_VEX_128_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsrlvd(const XmmReg& dst, const XmmReg& count, const Mem128& src)
            {
                AppendInstr(I_VPSRLVD, 0x45, E_VEX_128_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsrlvd(const YmmReg& dst, const YmmReg& count, const YmmReg& src)
            {
                AppendInstr(I_VPSRLVD, 0x45, E_VEX_256_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsrlvd(const YmmReg& dst, const YmmReg& count, const Mem256& src)
            {
                AppendInstr(I_VPSRLVD, 0x45, E_VEX_256_66_0F38_W0, W(dst), R(src), R(count));
            }
            void vpsrlvq(const XmmReg& dst, const XmmReg& count, const XmmReg& src)
            {
                AppendInstr(I_VPSRLVQ, 0x45, E_VEX_128_66_0F38_W1, W(dst), R(src), R(count));
            }
            void vpsrlvq(const XmmReg& dst, const XmmReg& count, const Mem128& src)
            {
                AppendInstr(I_VPSRLVQ, 0x45, E_VEX_128_66_0F38_W1, W(dst), R(src), R(count));
            }
            void vpsrlvq(const YmmReg& dst, const YmmReg& count, const YmmReg& src)
            {
                AppendInstr(I_VPSRLVQ, 0x45, E_VEX_256_66_0F38_W1, W(dst), R(src), R(count));
            }
            void vpsrlvq(const YmmReg& dst, const YmmReg& count, const Mem256& src)
            {
                AppendInstr(I_VPSRLVQ, 0x45, E_VEX_256_66_0F38_W1, W(dst), R(src), R(count));
            }
            void vpsubb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSUBB, 0xF8, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSUBB, 0xF8, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSUBW, 0xF9, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSUBW, 0xF9, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSUBD, 0xFA, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSUBD, 0xFA, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSUBQ, 0xFB, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSUBQ, 0xFB, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubsb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSUBSB, 0xE8, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubsb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSUBSB, 0xE8, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubsw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSUBSW, 0xE9, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubsw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSUBSW, 0xE9, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubusb(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSUBUSB, 0xD8, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubusb(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSUBUSB, 0xD8, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubusw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PSUBUSW, 0xD9, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpsubusw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PSUBUSW, 0xD9, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhbw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PUNPCKHBW, 0x68, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhbw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PUNPCKHBW, 0x68, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhwd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PUNPCKHWD, 0x69, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhwd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PUNPCKHWD, 0x69, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhdq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PUNPCKHDQ, 0x6A, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhdq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PUNPCKHDQ, 0x6A, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhqdq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PUNPCKHQDQ, 0x6D, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckhqdq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PUNPCKHQDQ, 0x6D, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklbw(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PUNPCKLBW, 0x60, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklbw(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PUNPCKLBW, 0x60, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklwd(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PUNPCKLWD, 0x61, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklwd(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PUNPCKLWD, 0x61, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckldq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PUNPCKLDQ, 0x62, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpckldq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PUNPCKLDQ, 0x62, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklqdq(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PUNPCKLQDQ, 0x6C, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpunpcklqdq(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PUNPCKLQDQ, 0x6C, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpxor(const YmmReg& dst, const YmmReg& src1, const YmmReg& src2)
            {
                AppendInstr(I_PXOR, 0xEF, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
            void vpxor(const YmmReg& dst, const YmmReg& src1, const Mem256& src2)
            {
                AppendInstr(I_PXOR, 0xEF, E_VEX_256_66_0F_WIG, W(dst), R(src2), R(src1));
            }
        };

        namespace compiler
        {
            struct BitVector : std::vector<uint32>
            {
                size_t size_bit() const
                {
                    return size() * 32;
                }

                bool get_bit(size_t idx) const
                {
                    const size_t i = idx / 32;
                    return i < size() && (at(i) & (1 << (idx % 32))) != 0;
                }

                void set_bit(size_t idx, bool b)
                {
                    const size_t i = idx / 32;
                    const uint32 mask = (1 << (idx % 32));
                    if (i >= size()) resize(i + 1);
                    if (b)  at(i) |= mask;
                    else    at(i) &= ~mask;
                }

                bool is_equal(const BitVector& rhs) const
                {
                    const size_t min_size = size() < rhs.size() ? size() : rhs.size();
                    for (size_t i = 0; i < min_size; ++i)
                    {
                        if (at(i) != rhs[i]) return false;
                    }

                    const BitVector& larger = size() < rhs.size() ? rhs : *this;
                    for (size_t i = min_size; i < larger.size(); ++i)
                    {
                        if (larger[i] != 0) return false;
                    }

                    return true;
                }

                size_t count_bit() const
                {
                    size_t count = 0;
                    for (size_t i = 0; i < size(); ++i)
                    {
                        count += detail::Count1Bits(at(i));
                    }
                    return count;
                }

                void get_bit_indexes(std::vector<size_t>& indexes) const
                {
                    indexes.clear();
                    for (size_t i = 0; i < size(); ++i)
                    {
                        uint32 m = at(i);
                        while (m != 0)
                        {
                            uint32 index = detail::bit_scan_forward(m);
                            indexes.push_back(static_cast<uint32>(i * 32) + index);
                            m &= ~(1 << index);
                        }
                    }
                }

                template<class Fn>
                void query_bit_indexes(Fn& fn) const
                {
                    for (size_t i = 0; i < size(); ++i)
                    {
                        uint32 m = at(i);
                        while (m != 0)
                        {
                            uint32 index = detail::bit_scan_forward(m);
                            fn(i * 32 + index);
                            m &= ~(1 << index);
                        }
                    }
                }

                void set_union(const BitVector& rhs)
                {
                    if (size() < rhs.size()) resize(rhs.size());
                    for (size_t i = 0; i < rhs.size(); ++i)
                    {
                        at(i) |= rhs[i];
                    }
                }

                void set_subtract(const BitVector& rhs)
                {
                    const size_t min_size = size() < rhs.size() ? size() : rhs.size();
                    for (size_t i = 0; i < min_size; ++i)
                    {
                        at(i) &= ~rhs[i];
                    }
                }
            };

            template<class T, size_t N>
            class FixedArray
            {
            private:
                T data_[N];
                size_t size_;

            public:
                FixedArray() : size_(0)
                {
                }
                bool empty() const
                {
                    return size_ == 0;
                }
                size_t size() const
                {
                    return size_;
                }
                void clear()
                {
                    size_ = 0;
                }

                void push_back(const T& v)
                {
                    data_[size_++] = v;
                }
                void pop_back()
                {
                    --size_;
                }

                const T& operator[](size_t i) const
                {
                    return data_[i];
                }
                T& operator[](size_t i)
                {
                    return data_[i];
                }

                const T& back() const
                {
                    return data_[size_ - 1];
                }
                T& back()
                {
                    return data_[size_ - 1];
                }
            };

            /// Register family
            inline size_t GetRegFamily(RegType type)
            {
                switch (type)
                {
                    case R_TYPE_GP:             return 0;
                    case R_TYPE_MMX:            return 1;
                    case R_TYPE_XMM:            return 2;
                    case R_TYPE_YMM:            return 2;
                    case R_TYPE_SYMBOLIC_GP:    return 0;
                    case R_TYPE_SYMBOLIC_MMX:   return 1;
                    case R_TYPE_SYMBOLIC_XMM:   return 2;
                    case R_TYPE_SYMBOLIC_YMM:   return 2;
                    case R_TYPE_FPU:
                    default:
                        JITASM_ASSERT(0);
                        return 0x7FFFFFFF;
                }
            }

            inline std::string GetRegName(RegType type, size_t reg_idx)
            {
                const static std::string s_gp_reg_name[] = { "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" };
                std::string name;
                if (type == R_TYPE_GP)
                {
                    return s_gp_reg_name[reg_idx];
                }
                else if (type == R_TYPE_MMX)
                {
                    name.assign("mm");
                }
                else if (type == R_TYPE_XMM)
                {
                    name.assign("xmm");
                }
                else if (type == R_TYPE_YMM)
                {
                    name.assign("ymm");
                }
                else if (type == R_TYPE_SYMBOLIC_GP)
                {
                    name.assign("gpsym"); reg_idx -= NUM_OF_PHYSICAL_REG;
                }
                else if (type == R_TYPE_SYMBOLIC_MMX)
                {
                    name.assign("mmsym"); reg_idx -= NUM_OF_PHYSICAL_REG;
                }
                else if (type == R_TYPE_SYMBOLIC_XMM)
                {
                    name.assign("xmmsym"); reg_idx -= NUM_OF_PHYSICAL_REG;
                }
                else if (type == R_TYPE_SYMBOLIC_YMM)
                {
                    name.assign("ymmsym"); reg_idx -= NUM_OF_PHYSICAL_REG;
                }
                detail::append_num(name, reg_idx);
                return name;
            }

            /// Variable attribute
            struct VarAttribute
            {
                unsigned size : 7;  // OpdSize
                unsigned spill : 1; // bool
                Addr stack_slot;
                VarAttribute() : size(0), spill(0/*false*/), stack_slot(RegID::Invalid(), 0)
                {
                }
            };

            /// Variable manager
            class VariableManager
            {
            private:
                std::vector<VarAttribute> attributes_[3];   // GP, MMX, XMM/YMM

            public:
                std::vector<VarAttribute>& GetAttributes(size_t reg_family)
                {
                    return attributes_[reg_family];
                }
                const std::vector<VarAttribute>& GetAttributes(size_t reg_family) const
                {
                    return attributes_[reg_family];
                }

                /// Get variable size
                OpdSize GetVarSize(size_t reg_family, int var) const
                {
                    return static_cast<OpdSize>(attributes_[reg_family][var].size);
                }

                /// Update variable size
                void UpdateVarSize(RegType reg_type, int var, OpdSize size)
                {
                    const size_t reg_family = GetRegFamily(reg_type);
                    if (static_cast<size_t>(var) >= attributes_[reg_family].size())
                    {
                        attributes_[reg_family].resize(var + 1);
                    }

                    if (attributes_[reg_family][var].size < static_cast<unsigned>(size))
                    {
                        attributes_[reg_family][var].size = static_cast<unsigned>(size);
                    }
                }

                /// Get stack slot for spill register
                Addr GetSpillSlot(size_t reg_family, int var) const
                {
                    return attributes_[reg_family][var].stack_slot;
                }

                /// Set stack slot for spill register
                void SetSpillSlot(RegType reg_type, int var, const Addr& stack_slot)
                {
                    const size_t reg_family = GetRegFamily(reg_type);
                    if (static_cast<size_t>(var) >= attributes_[reg_family].size())
                    {
                        attributes_[reg_family].resize(var + 1);
                    }
                    attributes_[reg_family][var].stack_slot = stack_slot;
                }

                /// Allocate stack of spill slots
                void AllocSpillSlots(detail::StackManager& stack_manager)
                {
                    // YMM
                    for (size_t i = 0; i < attributes_[2].size(); ++i)
                    {
                        if (attributes_[2][i].spill && attributes_[2][i].size == O_SIZE_256 && attributes_[2][i].stack_slot.reg_.IsInvalid())
                        {
                            attributes_[2][i].stack_slot = stack_manager.Alloc(256 / 8, 16);
                        }
                    }

                    // XMM
                    for (size_t i = 0; i < attributes_[2].size(); ++i)
                    {
                        if (attributes_[2][i].spill && attributes_[2][i].size == O_SIZE_128 && attributes_[2][i].stack_slot.reg_.IsInvalid())
                        {
                            attributes_[2][i].stack_slot = stack_manager.Alloc(128 / 8, 16);
                        }
                    }

                    // MMX
                    for (size_t i = 0; i < attributes_[1].size(); ++i)
                    {
                        if (attributes_[1][i].spill && attributes_[1][i].stack_slot.reg_.IsInvalid())
                        {
                            attributes_[1][i].stack_slot = stack_manager.Alloc(64 / 8, 8);
                        }
                    }

                    // GP
                    for (size_t i = 0; i < attributes_[0].size(); ++i)
                    {
                        if (attributes_[0][i].spill && attributes_[0][i].stack_slot.reg_.IsInvalid())
                        {
                            attributes_[0][i].stack_slot = stack_manager.Alloc(64 / 8, 8);
                        }
                    }
                }
            };

            /// Register use point
            struct RegUsePoint
            {
                size_t instr_idx;       ///< Instruction index offset from basic block start point
                OpdType type;           ///< Operand type
                uint32 reg_assignable;  ///< Register assignment constraint

                RegUsePoint(size_t idx, OpdType t, uint32 assignable) : instr_idx(idx), type(t), reg_assignable(assignable)
                {
                }

                bool operator<(const RegUsePoint& rhs) const
                {
                    if (instr_idx == rhs.instr_idx)
                    {
                        // R < RW < W
                        const int lhs_type = (type & O_TYPE_READ ? -1 : 0) + (type & O_TYPE_WRITE ? 1 : 0);
                        const int rhs_type = (rhs.type & O_TYPE_READ ? -1 : 0) + (rhs.type & O_TYPE_WRITE ? 1 : 0);
                        return lhs_type < rhs_type;
                    }
                    return instr_idx < rhs.instr_idx;
                }
            };

            /// Variable lifetime
            struct Lifetime
            {
                typedef detail::Range< std::vector<RegUsePoint> >       RegUsePointRange;
                typedef detail::ConstRange< std::vector<RegUsePoint> >  ConstRegUsePointRange;

                struct Interval
                {
                    size_t instr_idx_offset;                ///< Instruction index offset from basic block start point
                    BitVector liveness;                     ///< The set of live variables
                    BitVector use;                          ///< The set of used variables in this interval
                    BitVector spill;                        ///< The set of spilled variables
                    std::vector<uint32> reg_assignables;    ///< The constraints of register allocation
                    std::vector<int> assignment_table;      ///< Register assignment table

                    Interval(size_t instr_idx, const std::vector<uint32>& assignables) : instr_idx_offset(instr_idx), reg_assignables(assignables)
                    {
                    }
                    Interval(size_t instr_idx, const BitVector& l, const BitVector& s, const std::vector<uint32>& assignables) : instr_idx_offset(instr_idx), liveness(l), spill(s), reg_assignables(assignables)
                    {
                    }

                    void UpdateUse(size_t var, RegUsePointRange& range, const Interval *next_interval)
                    {
                        // step range
                        while (!range.empty() && range.first->instr_idx < instr_idx_offset)
                        {
                            ++range.first;
                        }

                        // check if variables used in this interval
                        const bool used = !range.empty() && (!next_interval || range.first->instr_idx < next_interval->instr_idx_offset);
                        use.set_bit(var, used);
                    }

                    void Dump(bool dump_assigned_reg) const
                    {
                        std::vector<char> liveness_str;
                        for (size_t v = 0; v < liveness.size_bit(); ++v)
                        {
                            if (liveness.get_bit(v))
                            {
                                const bool used = use.get_bit(v);
                                char c;
                                if (spill.get_bit(v))
                                {
                                    c = used ? 'S' : 's';
                                }
                                else if (dump_assigned_reg)
                                {
                                    int reg = assignment_table[v];
                                    c = static_cast<char>(reg < 0xA ? '0' + reg : 'A' + reg);
                                }
                                else
                                {
                                    c = used ? 'R' : 'r';
                                }
                                liveness_str.push_back(c);
                            }
                            else
                            {
                                liveness_str.push_back('.');
                            }
                        }
                        liveness_str.push_back('\0');
                        JITASM_TRACE("[%03d] %s", instr_idx_offset, &liveness_str[0]);
                    }
                };

                // 0 ~ NUM_OF_PHYSICAL_REG-1 : Physical register
                // NUM_OF_PHYSICAL_REG ~     : Symbolic register
                std::vector< std::vector<RegUsePoint> > use_points;
                BitVector gen;                          ///< The set of variables used before any assignment
                BitVector kill;                         ///< The set of variables assigned a value before any use
                BitVector live_in;                      ///< The set of live variables at the start of this block
                BitVector live_out;                     ///< The set of live variables at the end of this block
                bool dirty_live_out;                    ///< The dirty flag of live_out
                std::vector<Interval> intervals;        ///< Lifetime intervals

                static const int SpillCost_Read = 2;
                static const int SpillCost_Write = 3;

                Lifetime() : use_points(NUM_OF_PHYSICAL_REG), dirty_live_out(true)
                {
                }

                /// Add register use point
                void AddUsePoint(size_t instr_idx, const RegID& reg, OpdType opd_type, OpdSize opd_size, uint32 reg_assignable)
                {
                    if (use_points.size() <= static_cast<size_t>(reg.id))
                    {
                        use_points.resize(reg.id + 1);
                    }

                    // add read attribute when writing to 8/16bit register because it is partial write
                    if ((opd_type & O_TYPE_WRITE) && (opd_size == O_SIZE_8 || opd_size == O_SIZE_16))
                    {
                        opd_type = static_cast<OpdType>(static_cast<int>(opd_type) | O_TYPE_READ);
                    }

                    RegUsePoint use_point(instr_idx, opd_type, reg_assignable);
                    std::vector<RegUsePoint>::reverse_iterator it = use_points[reg.id].rbegin();
                    while (it != use_points[reg.id].rend() && use_point < *it)
                    {
                        ++it;
                    }
                    use_points[reg.id].insert(it.base(), use_point);
                }

                void GetSpillCost(int freq, std::vector<int>& spill_cost) const
                {
                    if (spill_cost.size() < use_points.size())
                    {
                        spill_cost.resize(use_points.size());   // expand
                    }
                    for (size_t i = 0; i < use_points.size(); ++i)
                    {
                        int cost = 0;
                        for (std::vector<RegUsePoint>::const_iterator it = use_points[i].begin(); it != use_points[i].end(); ++it)
                        {
                            if (it->type & O_TYPE_READ)  cost += SpillCost_Read;
                            if (it->type & O_TYPE_WRITE) cost += SpillCost_Write;
                        }
                        spill_cost[i] += cost * freq;
                    }
                }

                void BuildIntervals()
                {
                    // initialize use_points ranges
                    std::vector<RegUsePointRange> use_points_ranges;
                    use_points_ranges.reserve(use_points.size());
                    for (size_t i = 0; i < use_points.size(); ++i)
                    {
                        use_points_ranges.push_back(RegUsePointRange(use_points[i]));
                    }

                    // build interval
                    BitVector *last_liveness = NULL;
                    std::vector<uint32> reg_assignables;
                    bool last_reg_constraints = false;
                    bool last_stack_vars = false;
                    const size_t num_of_variables = live_in.size_bit() < use_points.size() ? use_points.size() : live_in.size_bit();
                    size_t instr_idx = 0;
                    size_t end_count;
                    do
                    {
                        BitVector liveness = live_in;
                        BitVector stack_vars;
                        end_count = 0;
                        reg_assignables.clear();
                        size_t min_instr_idx = (size_t)-1;
                        for (size_t i = 0; i < use_points_ranges.size(); ++i)
                        {
                            if (use_points_ranges[i].empty())
                            {
                                liveness.set_bit(i, live_out.get_bit(i));
                                ++end_count;
                            }
                            else
                            {
                                if (use_points_ranges[i].first->instr_idx < min_instr_idx)
                                {
                                    min_instr_idx = use_points_ranges[i].first->instr_idx;
                                }

                                if (use_points_ranges[i].first->instr_idx == instr_idx)
                                {
                                    for (; !use_points_ranges[i].empty() && use_points_ranges[i].first->instr_idx == instr_idx; ++use_points_ranges[i].first)
                                    {
                                        // Check the constraints of register allocation
                                        if (use_points_ranges[i].first->reg_assignable != 0xFFFFFFFF)
                                        {
                                            reg_assignables.resize(num_of_variables, 0xFFFFFFFF);
                                            reg_assignables[i] &= use_points_ranges[i].first->reg_assignable;
                                        }

                                        // Check the stack variable
                                        if (use_points_ranges[i].first->type & O_TYPE_MEM)
                                        {
                                            stack_vars.set_bit(i, true);
                                        }
                                    }
                                    liveness.set_bit(i, true);
                                }
                                else if (use_points_ranges[i].first->type & O_TYPE_READ)
                                {
                                    liveness.set_bit(i, true);
                                }
                                else if (use_points_ranges[i].first->type & O_TYPE_WRITE)
                                {
                                    liveness.set_bit(i, false);
                                }
                                else
                                {
                                    JITASM_ASSERT(0);
                                }
                            }
                        }

                        // Split interval in the following case:
                        // - The liveness is changed.
                        // - Current or last instruction has any constraints of register allocation.
                        // - Last instruction is I_COMPILER_DECLARE_STACK_ARG
                        if (!reg_assignables.empty() || last_reg_constraints || last_stack_vars || !last_liveness || !last_liveness->is_equal(liveness))
                        {
                            intervals.push_back(Interval(instr_idx, liveness, stack_vars, reg_assignables));
                            last_liveness = &intervals.back().liveness;
                        }

                        last_reg_constraints = !reg_assignables.empty();
                        last_stack_vars = !stack_vars.empty();
                        instr_idx = min_instr_idx == instr_idx ? instr_idx + 1 : min_instr_idx;
                    }
                    while (end_count < use_points_ranges.size());

                    // check use
                    for (size_t v = 0; v < use_points.size(); ++v)
                    {
                        RegUsePointRange range(use_points[v]);
                        for (size_t i = 0; i < intervals.size(); ++i)
                        {
                            const Interval *next_interval  = i + 1 < intervals.size() ? &intervals[i + 1] : NULL;
                            intervals[i].UpdateUse(v, range, next_interval);
                        }
                    }
                }

                /// Split interval
                void SplitInterval(size_t instr_idx, size_t interval_idx)
                {
                    std::vector<Interval>::iterator it = intervals.insert(intervals.begin() + interval_idx + 1, intervals[interval_idx]);
                    it->instr_idx_offset = instr_idx;

                    // update use
                    for (size_t v = 0; v < use_points.size(); ++v)
                    {
                        RegUsePointRange range(use_points[v]);
                        for (size_t i = interval_idx; i < interval_idx + 2; ++i)
                        {
                            const Interval *next_interval  = i + 1 < intervals.size() ? &intervals[i + 1] : NULL;
                            intervals[i].UpdateUse(v, range, next_interval);
                        }
                    }
                }

                struct LessCost
                {
                    const std::vector<int> *cost_;
                    LessCost(const std::vector<int> *cost) : cost_(cost)
                    {
                    }
                    int get_cost(size_t i) const
                    {
                        return i < cost_->size() ? cost_->at(i) : 0;
                    }
                    bool operator()(size_t lhs, size_t rhs) const
                    {
                        return get_cost(lhs) < get_cost(rhs);
                    }
                };

                /// Spill identification
                void SpillIdentification(uint32 available_reg_count, const std::vector<int>& total_spill_cost, int freq, const Interval *last_interval, std::vector<VarAttribute>& var_attrs)
                {
                    // initialize use_points ranges
                    std::vector<RegUsePointRange> interval_use_points;
                    interval_use_points.reserve(use_points.size());
                    for (size_t i = 0; i < use_points.size(); ++i)
                    {
                        interval_use_points.push_back(RegUsePointRange(use_points[i]));
                    }

                    std::vector<size_t> live_vars;
                    std::vector<int> cur_spill_cost;
                    for (size_t interval_idx = 0; interval_idx < intervals.size(); ++interval_idx)
                    {
                        const Interval *prior_interval = interval_idx > 0 ? &intervals[interval_idx - 1] : last_interval;
                        Interval *cur_interval = &intervals[interval_idx];

                        if (cur_interval->liveness.count_bit() > available_reg_count)
                        {
                            cur_interval->liveness.get_bit_indexes(live_vars);

                            const size_t max_var = live_vars.back();
                            if (var_attrs.size() < max_var + 1)
                            {
                                var_attrs.resize(max_var + 1);      // expand var_attrs
                            }

                            cur_spill_cost.resize(max_var + 1);
                            for (size_t i = 0; i < live_vars.size(); ++i)
                            {
                                const size_t var = live_vars[i];

                                // step interval_use_points
                                if (var < interval_use_points.size())
                                {
                                    while (!interval_use_points[var].empty() && interval_use_points[var].first->instr_idx < cur_interval->instr_idx_offset)
                                    {
                                        ++interval_use_points[var].first;
                                    }
                                }

                                // calculate spill cost of this interval
                                if (cur_interval->use.get_bit(var) && (interval_use_points[var].first->type & O_TYPE_MEM))
                                {
                                    // special low spill cost if this variable on stack (function arguemnt)
                                    cur_spill_cost[var] = -1;
                                }
                                else if (cur_interval->use.get_bit(var) && interval_use_points[var].first->instr_idx == cur_interval->instr_idx_offset)
                                {
                                    // special high spill cost if this variable is used at first instruction of this interval
                                    // because it must not be spilled.
                                    cur_spill_cost[var] = 0x7FFFFFFF;
                                }
                                else
                                {
                                    cur_spill_cost[var] = total_spill_cost[var];
                                    if (prior_interval && !prior_interval->spill.get_bit(var))
                                    {
                                        cur_spill_cost[var] += (SpillCost_Read + SpillCost_Write) * freq;
                                    }
                                }
                            }

                            // Spill from the smallest cost
                            std::sort(live_vars.begin(), live_vars.end(), LessCost(&cur_spill_cost));

                            // Mark spilled variable.
                            // Split interval if spilled variable is used in this interval.
                            // Find first instruction index using the spilled variable.
                            size_t split_interval_instr = (size_t)-1;
                            for (size_t i = 0; i < live_vars.size(); ++i)
                            {
                                const size_t var = live_vars[i];
                                const bool stack_var = (cur_spill_cost[var] < 0);       // It may be function argument on stack
                                const bool spill = (i + available_reg_count < live_vars.size() || stack_var);
                                cur_interval->spill.set_bit(var, spill);
                                if (spill)
                                {
                                    var_attrs[var].spill = 1;
                                }
                                if (stack_var)
                                {
                                    // Split at next of using stack variable
                                    if (interval_use_points[var].first->instr_idx + 1 < split_interval_instr)
                                    {
                                        split_interval_instr = interval_use_points[var].first->instr_idx + 1;
                                    }
                                }
                                else if (spill && cur_interval->use.get_bit(var))
                                {
                                    // Split if spilled variable is used in this interval.
                                    if (interval_use_points[var].first->instr_idx < split_interval_instr)
                                    {
                                        split_interval_instr = interval_use_points[var].first->instr_idx;
                                    }
                                }
                            }

                            if (split_interval_instr != (size_t)-1)
                            {
                                SplitInterval(split_interval_instr, interval_idx);
                            }
                        }
                    }
                }

                struct LessAssignOrder
                {
                    Interval *interval;
                    const Interval *prior_interval;
                    LessAssignOrder(Interval *cur, const Interval *prior) : interval(cur), prior_interval(prior)
                    {
                    }
                    bool has_constraints(size_t v) const
                    {
                        return v < interval->reg_assignables.size() ? interval->reg_assignables[v] != 0xFFFFFFFF : false;
                    }
                    uint32 num_of_assignable(size_t v) const
                    {
                        return v < interval->reg_assignables.size() ? detail::Count1Bits(interval->reg_assignables[v]) : 32;
                    }
                    bool operator()(size_t lhs, size_t rhs) const
                    {
                        // is there any register constraints or not
                        const bool lhs_has_constraints = has_constraints(lhs);
                        const bool rhs_has_constraints = has_constraints(rhs);
                        if (lhs_has_constraints != rhs_has_constraints)
                        {
                            return lhs_has_constraints;
                        }

                        if (lhs_has_constraints)
                        {
                            // is the register which has constraints used in this interval or not
                            const bool lhs_used = interval->use.get_bit(lhs);
                            const bool rhs_used = interval->use.get_bit(rhs);
                            if (lhs_used != rhs_used)
                            {
                                return lhs_used;
                            }

                            // compare number of assignable registers
                            const uint32 lhs_num_of_assignable = num_of_assignable(lhs);
                            const uint32 rhs_num_of_assignable = num_of_assignable(rhs);
                            if (lhs_num_of_assignable != rhs_num_of_assignable)
                            {
                                return lhs_num_of_assignable < rhs_num_of_assignable;
                            }
                        }

                        // physical register or symbolic register
                        const int lhs_sym_reg = (lhs < NUM_OF_PHYSICAL_REG ? 0 : 1);
                        const int rhs_sym_reg = (rhs < NUM_OF_PHYSICAL_REG ? 0 : 1);
                        if (lhs_sym_reg != rhs_sym_reg)
                        {
                            return lhs_sym_reg < rhs_sym_reg;
                        }

                        if (prior_interval)
                        {
                            // is the variable assigned register in prior interval or not
                            const bool lhs_prior_reg = !prior_interval->spill.get_bit(lhs) && prior_interval->liveness.get_bit(lhs);
                            const bool rhs_prior_reg = !prior_interval->spill.get_bit(rhs) && prior_interval->liveness.get_bit(rhs);
                            if (lhs_prior_reg != rhs_prior_reg)
                            {
                                return lhs_prior_reg;
                            }
                        }

                        // compare register id
                        return lhs < rhs;
                    }
                };

                /// Assign register in basic block
                /**
                * \param[in] available_reg  Available physical register mask
                * \param[in] last_interval  Last Interval as the hint of assignment
                * \return Used physical register mask
                */
                uint32 AssignRegister(uint32 available_reg, const Interval *last_interval)
                {
                    uint32 used_reg = 0;
                    std::vector<size_t> live_vars;
                    for (size_t interval_idx = 0; interval_idx < intervals.size(); ++interval_idx)
                    {
                        const Interval *prior_interval = interval_idx > 0 ? &intervals[interval_idx - 1] : last_interval;
                        Interval *cur_interval = &intervals[interval_idx];

                        // enum variables to assign register
                        live_vars.clear();
                        for (size_t i = 0; i < cur_interval->liveness.size(); ++i)
                        {
                            uint32 s = i < cur_interval->spill.size() ? cur_interval->spill[i] : 0;
                            uint32 l = cur_interval->liveness[i] & ~s;
                            while (l != 0)
                            {
                                uint32 index = detail::bit_scan_forward(l);
                                live_vars.push_back(static_cast<uint32>(i * 32) + index);
                                l &= ~(1 << index);
                            }
                        }

                        if (!live_vars.empty())
                        {
                            cur_interval->assignment_table.resize(live_vars.back() + 1, -1);

                            // sort into assignment order
                            std::sort(live_vars.begin(), live_vars.end(), LessAssignOrder(cur_interval, prior_interval));
                        }

                        // Assign register
                        uint32 cur_avail = available_reg;
                        const size_t num_of_live_vars = live_vars.size();
                        for (size_t i = 0; i < live_vars.size(); ++i)
                        {
                            const size_t var = live_vars[i];
                            const bool first_try = (i < num_of_live_vars);  // Try to assign for the first time
                            const uint32 reg_assignable = first_try && var < cur_interval->reg_assignables.size() ? cur_interval->reg_assignables[var] : 0xFFFFFFFF;    // Ignore constraint if it is retried
                            JITASM_ASSERT((cur_avail & reg_assignable) != 0);
                            int assigned_reg = -1;
                            if (var < NUM_OF_PHYSICAL_REG && first_try)
                            {
                                // Physical register
                                if (cur_avail & reg_assignable & (1 << var))
                                {
                                    assigned_reg = static_cast<int>(var);
                                }
                                else if (((1 << var) & available_reg) && !cur_interval->use.get_bit(var))
                                {
                                    // Try to assign another physical register if it is not used in this interval. But assign later.
                                    live_vars.push_back(var);
                                }
                                else if (reg_assignable != 0xFFFFFFFF && (cur_avail & reg_assignable) && cur_interval->use.get_bit(var))
                                {
                                    // This physical register violates the register constraint.
                                    // Assign another physical register which satisfy the constraint.
                                    assigned_reg = detail::bit_scan_forward(cur_avail & reg_assignable);
                                }
                                else
                                {
                                    // This may be out of assignment register (ESP, EBP and so on...)
                                    JITASM_ASSERT(((1 << var) & available_reg) == 0);       // false assignment!?
                                    assigned_reg = static_cast<int>(var);
                                }
                            }
                            else
                            {
                                // Symbolic register or retried physical register
                                const int last_assigned = prior_interval && var < prior_interval->assignment_table.size() ? prior_interval->assignment_table[var] : -1;
                                if (last_assigned != -1 && (cur_avail & reg_assignable & (1 << last_assigned)))
                                {
                                    // select last assigned register
                                    assigned_reg = last_assigned;
                                }
                                else if (cur_avail & reg_assignable)
                                {
                                    assigned_reg = detail::bit_scan_forward(cur_avail & reg_assignable);
                                }
                                else if (reg_assignable != 0xFFFFFFFF && !cur_interval->use.get_bit(var))
                                {
                                    // Try to assign register ignoring constraint if it is not used in this interval. But assign later.
                                    live_vars.push_back(var);
                                }
                                else
                                {
                                    JITASM_ASSERT(0);
                                }
                            }

                            if (assigned_reg >= 0)
                            {
                                cur_interval->assignment_table[var] = assigned_reg;
                                cur_avail &= ~(1 << assigned_reg);
                            }
                        }

                        used_reg |= ~cur_avail & available_reg;
                    }

                    return used_reg;
                }

                void DumpIntervals(size_t block_id, bool dump_assigned_reg) const
                {
                    avoid_unused_warn(block_id);
                    JITASM_TRACE("---- Block%d ----", block_id);
                    for (size_t i = 0; i < intervals.size(); ++i)
                    {
                        intervals[i].Dump(dump_assigned_reg);
                    }
                }
            };

            /// Basic block
            struct BasicBlock
            {
                BasicBlock *successor[2];
                std::vector<BasicBlock *> predecessor;
                size_t instr_begin;                 ///< Begin instruction index of the basic block (inclusive)
                size_t instr_end;                   ///< End instruction index of the basic block (exclusive)
                size_t depth;                       ///< Depth-first order of Control flow
                BasicBlock *dfs_parent;             ///< Depth-first search tree parent
                BasicBlock *immediate_dominator;    ///< Immediate dominator
                size_t loop_depth;                  ///< Loop nesting depth
                Lifetime lifetime[3];               ///< Variable lifetime (0: GP, 1: MMX, 2: XMM/YMM)

                BasicBlock(size_t instr_begin_, size_t instr_end_, BasicBlock *successor0 = NULL, BasicBlock *successor1 = NULL) : instr_begin(instr_begin_), instr_end(instr_end_), depth((size_t)-1), dfs_parent(NULL), immediate_dominator(NULL), loop_depth(0)
                {
                    successor[0] = successor0;
                    successor[1] = successor1;
                }

                bool operator<(const BasicBlock& rhs) const
                {
                    return instr_begin < rhs.instr_begin;
                }

                /// Remove predecessor
                void RemovePredecessor(BasicBlock *block)
                {
                    std::vector<BasicBlock *>::iterator it = std::find(predecessor.begin(), predecessor.end(), block);
                    if (it != predecessor.end())
                    {
                        predecessor.erase(it);
                    }
                }

                /// Replace predecessor
                bool ReplacePredecessor(BasicBlock *old_pred, BasicBlock *new_pred)
                {
                    std::vector<BasicBlock *>::iterator it = std::find(predecessor.begin(), predecessor.end(), old_pred);
                    if (it != predecessor.end())
                    {
                        *it = new_pred;
                        return true;
                    }
                    return false;
                }

                /// Check if the specified block is dominator of this block
                bool IsDominated(BasicBlock *block) const
                {
                    if (block == this)
                    {
                        return true;
                    }
                    return immediate_dominator ? immediate_dominator->IsDominated(block) : false;
                }

                /// Get estimated frequency of basic block
                int GetFrequency() const
                {
                    const static int freq[] = { 1, 100, 10000, 40000, 160000, 640000 };
                    return freq[loop_depth < sizeof(freq) / sizeof(int) ? loop_depth : sizeof(freq) / sizeof(int) - 1];
                }

                /// Get variable lifetime
                Lifetime& GetLifetime(RegType type)
                {
                    return lifetime[GetRegFamily(type)];
                }
                /// Get variable lifetime
                const Lifetime& GetLifetime(RegType type) const
                {
                    return lifetime[GetRegFamily(type)];
                }

                struct less
                {
                    bool operator()(BasicBlock *lhs, BasicBlock *rhs)
                    {
                        return lhs->instr_begin < rhs->instr_begin;
                    }
                    bool operator()(BasicBlock *lhs, size_t rhs)
                    {
                        return lhs->instr_begin < rhs;
                    }
                    bool operator()(size_t lhs, BasicBlock *rhs)
                    {
                        return lhs < rhs->instr_begin;
                    }
                };
            };

            /**
            * The Lengauer-Tarjan algorithm
            */
            class DominatorFinder
            {
            private:
                std::vector<size_t> sdom_;          // semidominator
                std::vector<size_t> ancestor_;
                std::vector<size_t> best_;

                void Link(size_t v, size_t w)
                {
                    ancestor_[w] = v;
                }

                size_t Eval(size_t v)
                {
                    if (ancestor_[v] == 0) return v;
                    Compress(v);
                    return best_[v];
                }

                void Compress(size_t v)
                {
                    size_t a = ancestor_[v];
                    if (ancestor_[a] == 0)
                        return;

                    Compress(a);

                    if (sdom_[best_[v]] > sdom_[best_[a]])
                        best_[v] = best_[a];

                    ancestor_[v] = ancestor_[a];
                }

            public:
                void operator()(std::deque<BasicBlock *>& depth_first_blocks)
                {
                    const size_t num_of_nodes = depth_first_blocks.size();
                    if (num_of_nodes == 0) return;

                    // initialize
                    sdom_.resize(num_of_nodes);         // semidominator
                    ancestor_.clear();
                    ancestor_.resize(num_of_nodes);
                    best_.resize(num_of_nodes);
                    std::vector< std::vector<size_t> > bucket(num_of_nodes);
                    std::vector<size_t> dom(num_of_nodes);
                    for (size_t i = 0; i < num_of_nodes; ++i)
                    {
                        sdom_[i] = i;
                        best_[i] = i;
                    }

                    for (size_t w = num_of_nodes - 1; w > 0; --w)
                    {
                        BasicBlock *wb = depth_first_blocks[w];
                        size_t p = wb->dfs_parent->depth;

                        // Compute the semidominator
                        for (std::vector<BasicBlock *>::iterator v = wb->predecessor.begin(); v != wb->predecessor.end(); ++v)
                        {
                            if ((*v)->depth != (size_t)-1)
                            {   // skip out of DFS tree
                                size_t u = Eval((*v)->depth);
                                if (sdom_[u] < sdom_[w])
                                    sdom_[w] = sdom_[u];
                            }
                        }
                        bucket[sdom_[w]].push_back(w);
                        Link(p, w);

                        // Implicity compute immediate dominator
                        for (std::vector<size_t>::iterator v = bucket[p].begin(); v != bucket[p].end(); ++v)
                        {
                            size_t u = Eval(*v);
                            dom[*v] = sdom_[u] < sdom_[*v] ? u : p;
                        }
                        bucket[p].clear();
                    }

                    // Explicity compute immediate dominator
                    for (size_t w = 1; w < num_of_nodes; ++w)
                    {
                        if (dom[w] != sdom_[w])
                            dom[w] = dom[dom[w]];
                        depth_first_blocks[w]->immediate_dominator = depth_first_blocks[dom[w]];
                    }
                    depth_first_blocks[0]->immediate_dominator = NULL;
                }
            };

            /// Control flow graph
            class ControlFlowGraph
            {
            public:
                typedef std::deque<BasicBlock *> BlockList;

            private:
                BlockList blocks_;
                BlockList depth_first_blocks_;

                void MakeDepthFirstBlocks(BasicBlock *block)
                {
                    block->depth = 0;   // mark "visited"
                    for (size_t i = 0; i < 2; ++i)
                    {
                        BasicBlock *s = block->successor[i];
                        if (s && s->depth != 0)
                        {
                            s->dfs_parent = block;
                            MakeDepthFirstBlocks(s);
                        }
                    }
                    depth_first_blocks_.push_front(block);
                }

                struct sort_backedge
                {
                    bool operator()(const std::pair<size_t, size_t>& lhs, const std::pair<size_t, size_t>& rhs) const
                    {
                        if (lhs.second < rhs.second) return true;                       // smaller depth loop header first
                        if (lhs.second == rhs.second) return lhs.first > rhs.first;     // larger depth of end of loop first if same loop header
                        return false;
                    }
                };

                void DetectLoops()
                {
                    // Make dominator tree
                    DominatorFinder dom_finder;
                    dom_finder(depth_first_blocks_);

                    // Identify backedges
                    std::vector< std::pair<size_t, size_t> > backedges;
                    for (size_t i = 0; i < depth_first_blocks_.size(); ++i)
                    {
                        BasicBlock *block = depth_first_blocks_[i];
                        for (size_t j = 0; j < 2; ++j)
                        {
                            if (block->successor[j] && block->depth >= block->successor[j]->depth)
                            {       // retreating edge
                                if (block->IsDominated(block->successor[j]))
                                {
                                    backedges.push_back(std::make_pair(block->depth, block->successor[j]->depth));
                                }
                            }
                        }
                    }

                    // Merge loops with the same loop header
                    std::sort(backedges.begin(), backedges.end(), sort_backedge());
                    if (backedges.size() >= 2)
                    {
                        std::vector< std::pair<size_t, size_t> >::iterator it = backedges.begin() + 1;
                        while (it != backedges.end())
                        {
                            if (detail::prior(it)->second == it->second)
                            {
                                // erase backedge of smaller loop
                                it = backedges.erase(it);
                            }
                            else
                            {
                                ++it;
                            }
                        }
                    }

                    // Set loop depth
                    for (std::vector< std::pair<size_t, size_t> >::iterator it = backedges.begin(); it != backedges.end(); ++it)
                    {
                        for (size_t i = it->second; i <= it->first; ++i)
                        {
                            depth_first_blocks_[i]->loop_depth++;
                        }
                    }
                }

                BlockList::iterator initialize(size_t num_of_instructions)
                {
                    clear();
                    blocks_.resize(num_of_instructions > 0 ? 2 : 1);
                    BasicBlock *enter_block = new BasicBlock(0, num_of_instructions);
                    blocks_[0] = enter_block;
                    if (num_of_instructions > 0)
                    {
                        // exit block
                        BasicBlock *exit_block = new BasicBlock(num_of_instructions, num_of_instructions);
                        blocks_[1] = exit_block;
                        enter_block->successor[0] = exit_block;
                        exit_block->predecessor.push_back(enter_block);
                    }
                    return blocks_.begin();
                }

                /// Split basic block
                BlockList::iterator split(BlockList::iterator target_block_it, size_t instr_idx)
                {
                    BasicBlock *target_block = *target_block_it;
                    if (target_block->instr_begin == instr_idx)
                        return target_block_it;

                    BasicBlock *new_block = new BasicBlock(instr_idx, target_block->instr_end);
                    new_block->successor[0] = target_block->successor[0];
                    new_block->successor[1] = target_block->successor[1];
                    new_block->predecessor.push_back(target_block);
                    target_block->successor[0] = new_block;
                    target_block->successor[1] = NULL;
                    target_block->instr_end = instr_idx;

                    // replace predecessor of successors
                    if (new_block->successor[0]) new_block->successor[0]->ReplacePredecessor(target_block, new_block);
                    if (new_block->successor[1]) new_block->successor[1]->ReplacePredecessor(target_block, new_block);

                    return blocks_.insert(detail::next(target_block_it), new_block);
                }

            public:
                ~ControlFlowGraph()
                {
                    clear();
                }

                BlockList::iterator get_block(size_t instr_idx)
                {
                    BlockList::iterator it = std::upper_bound(blocks_.begin(), blocks_.end(), instr_idx, BasicBlock::less());
                    return it != blocks_.begin() ? --it : blocks_.end();
                }

                BlockList::iterator get_exit_block()
                {
                    return detail::prior(blocks_.end());
                }

                size_t size()
                {
                    return blocks_.size();
                }

                void clear()
                {
                    for (BlockList::iterator it = blocks_.begin(); it != blocks_.end(); ++it)
                    {
                        delete *it;
                    }
                    blocks_.clear();
                    depth_first_blocks_.clear();
                }

                BlockList::iterator begin()
                {
                    return blocks_.begin();
                }
                BlockList::iterator end()
                {
                    return blocks_.end();
                }
                BlockList::const_iterator begin() const
                {
                    return blocks_.begin();
                }
                BlockList::const_iterator end() const
                {
                    return blocks_.end();
                }
                BlockList::iterator dfs_begin()
                {
                    return depth_first_blocks_.begin();
                }
                BlockList::iterator dfs_end()
                {
                    return depth_first_blocks_.end();
                }

                void DumpDot() const
                {
                    JITASM_TRACE("digraph CFG {");
                    JITASM_TRACE("\tnode[shape=box];");
                    for (BlockList::const_iterator it = blocks_.begin(); it != blocks_.end(); ++it)
                    {
                        BasicBlock *block = *it;
                        std::string live_in = "live in:";
                        std::string live_out = "live out:";
                        for (size_t reg_family = 0; reg_family < 3; ++reg_family)
                        {
                            for (size_t i = 0; i < block->lifetime[reg_family].live_in.size_bit(); ++i)
                            {
                                if (block->lifetime[reg_family].live_in.get_bit(i))
                                {
                                    live_in.append(" ");
                                    live_in.append(GetRegName(static_cast<RegType>(reg_family + (i < NUM_OF_PHYSICAL_REG ? R_TYPE_GP : R_TYPE_SYMBOLIC_GP)), i));
                                }
                            }
                            for (size_t i = 0; i < block->lifetime[reg_family].live_out.size_bit(); ++i)
                            {
                                if (block->lifetime[reg_family].live_out.get_bit(i))
                                {
                                    live_out.append(" ");
                                    live_out.append(GetRegName(static_cast<RegType>(reg_family + (i < NUM_OF_PHYSICAL_REG ? R_TYPE_GP : R_TYPE_SYMBOLIC_GP)), i));
                                }
                            }
                        }
                        JITASM_TRACE("\tnode%d[label=\"Block%d\\ninstruction %d - %d\\nloop depth %d\\n%s\\n%s\"];", block->instr_begin, block->depth, block->instr_begin, block->instr_end - 1, block->loop_depth, live_in.c_str(), live_out.c_str());
                        int constraint = 0; avoid_unused_warn(constraint);
                        if (block->successor[0]) JITASM_TRACE("\t\"node%d\" -> \"node%d\" [constraint=%s];", block->instr_begin, block->successor[0]->instr_begin, constraint == 0 ? "true" : "false");
                        if (block->successor[1]) JITASM_TRACE("\t\"node%d\" -> \"node%d\" [constraint=%s];", block->instr_begin, block->successor[1]->instr_begin, constraint == 0 ? "true" : "false");
                        //if (block->dfs_parent) JITASM_TRACE("\t\"node%d\" -> \"node%d\" [color=\"#ff0000\"];", block->instr_begin, block->dfs_parent->instr_begin);
                        //if (block->immediate_dominator) JITASM_TRACE("\t\"node%d\" -> \"node%d\" [constraint=false, color=\"#0000ff\"];", block->instr_begin, block->immediate_dominator->instr_begin);
                        //for (size_t i = 0; i < block->predecessor.size(); ++i) {
                        //  JITASM_TRACE("\t\"node%d\" -> \"node%d\" [constraint=false, color=\"#808080\"];", block->instr_begin, block->predecessor[i]->instr_begin);
                        //}
                    }
                    JITASM_TRACE("}");
                }

                /// Build control flow graph from instruction list
                void Build(const Frontend& f);

                /// Build dummy control flow graph which has enter and exit blocks.
                void BuildDummy(const Frontend& f)
                {
                    BasicBlock *enter_block = *initialize(f.instrs_.size());
                    BasicBlock *exit_block = enter_block->successor[0];

                    enter_block->depth = 0;
                    depth_first_blocks_.push_back(enter_block);
                    if (exit_block)
                    {
                        exit_block->depth = 1;
                        exit_block->dfs_parent = enter_block;
                        exit_block->immediate_dominator = enter_block;
                        depth_first_blocks_.push_back(exit_block);
                    }
                }
            };

            /// Prepare compile
            /**
            * - Re-number symbolic register ID.
            * - Check if register allocation is needed or not.
            * - Look over physical register use.
            *
            * \param[in,out]  instrs                    Instruction list
            * \param[out]     modified_physical_reg Modified physical register mask
            * \param[out]     need_reg_alloc            Register allocation is needed or not
            * \return There is any compile process if it is true.
            */
            inline bool PrepareCompile(Frontend::InstrList& instrs, uint32(&modified_physical_reg)[3], bool(&need_reg_alloc)[3])
            {
                struct RegIDMap
                {
                    int next_id_;
                    std::map<int, int> id_map_;
                    RegIDMap() : next_id_(NUM_OF_PHYSICAL_REG)
                    {
                    }
                    int GetNormalizedID(int id)
                    {
                        std::map<int, int>::iterator it = id_map_.find(id);
                        if (it != id_map_.end())
                        {
                            return it->second;
                        }
                        int new_id = next_id_++;
                        id_map_.insert(std::pair<int, int>(id, new_id));
                        return new_id;
                    }
                };
                RegIDMap reg_id_map[3];     // GP, MMX, XMM/YMM
                modified_physical_reg[0] = modified_physical_reg[1] = modified_physical_reg[2] = 0;
                need_reg_alloc[0] = need_reg_alloc[1] = need_reg_alloc[2] = false;
                bool compile_process = false;

                for (Frontend::InstrList::iterator it = instrs.begin(); it != instrs.end(); ++it)
                {
                    const InstrID instr_id = it->GetID();
                    if (instr_id == I_COMPILER_DECLARE_REG_ARG || instr_id == I_COMPILER_DECLARE_STACK_ARG || instr_id == I_COMPILER_DECLARE_RESULT_REG || instr_id == I_COMPILER_PROLOG || instr_id == I_COMPILER_EPILOG)
                    {
                        compile_process = true;
                    }

                    for (size_t i = 0; i < Instr::MAX_OPERAND_COUNT; ++i)
                    {
                        detail::Opd& opd = it->GetOpd(i);
                        if (opd.IsReg() && !opd.IsFpuReg() && !opd.IsRip())
                        {
                            const RegID& reg = opd.GetReg();
                            const size_t reg_family = GetRegFamily(reg.GetType());
                            if (reg.IsSymbolic())
                            {
                                opd.reg_.id = reg_id_map[reg_family].GetNormalizedID(reg.id);
                            }
                            else if (reg.IsAllegrex())
                            {
                                //need_reg_alloc[0] = true;
                            }
                            else
                            {
                                if (opd.IsWrite())
                                {
                                    // This physical register is modified
                                    modified_physical_reg[reg_family] |= (1 << reg.id);
                                }

                                if ((opd.reg_assignable_ & (1 << reg.id)) == 0)
                                {
                                    // Specified physical register does not fit the instruction.
                                    // Let's try to assign optimal physical register by register allocation.
                                    need_reg_alloc[reg_family] = true;
                                }
                            }
                        }
                        else if (opd.IsMem())
                        {
                            const RegID& base = opd.GetBase();
                            if (base.IsSymbolic())
                            {
                                opd.base_.id = reg_id_map[0].GetNormalizedID(base.id);
                            }
                            else if (base.IsAllegrex())
                            {
                                //need_reg_alloc[0] = true;
                            }

                            const RegID& index = opd.GetIndex();
                            if (index.IsSymbolic())
                            {
                                opd.index_.id = reg_id_map[GetRegFamily(index.GetType())].GetNormalizedID(index.id);
                            }
                            else if (index.IsAllegrex())
                            {
                                //need_reg_alloc[0] = true;
                            }
                        }
                    }
                }

                for (size_t i = 0; i < 3; ++i)
                {
                    if (!need_reg_alloc[i] && reg_id_map[i].next_id_ > NUM_OF_PHYSICAL_REG)
                    {
                        need_reg_alloc[i] = true;
                    }
                }

                return compile_process || need_reg_alloc[0] || need_reg_alloc[1] || need_reg_alloc[2];
            }

            /// Check the instruction if it break register dependence
            inline bool IsBreakDependenceInstr(const Instr& instr)
            {
                // Instructions
                // SUB, SBB, XOR, PXOR, XORPS, XORPD, PANDN, PSUBxx, PCMPxx
                const InstrID id = instr.GetID();
                if (id == I_SUB || id == I_SBB || id == I_XOR || id == I_PXOR || id == I_XORPS || id == I_XORPD || id == I_PANDN ||
                    id == I_PSUBB || id == I_PSUBW || id == I_PSUBD || id == I_PSUBQ || id == I_PSUBSB || id == I_PSUBSW || id == I_PSUBUSB || id == I_PSUBUSW ||
                    id == I_PCMPEQB || id == I_PCMPEQW || id == I_PCMPEQD || id == I_PCMPEQQ || id == I_PCMPGTB || id == I_PCMPGTW || id == I_PCMPGTD || id == I_PCMPGTQ)
                {
                    // source and destination operands are the same register.
                    // 8bit or 16bit register cannot break dependence.
                    const detail::Opd& opd0 = instr.GetOpd(0);
                    const detail::Opd& opd1 = instr.GetOpd(1);
                    const OpdSize opdsize = opd0.GetSize();
                    if (opd0 == opd1 && opd0.IsReg() && opdsize != O_SIZE_8 && opdsize != O_SIZE_16)
                    {
                        return true;
                    }
                }
                return false;
            }

            /// Live Variable Analysis
            inline void LiveVariableAnalysis(const Frontend& f, ControlFlowGraph& cfg, VariableManager& var_manager)
            {
                std::vector<BasicBlock *> update_target;
                update_target.reserve(cfg.size());

                for (ControlFlowGraph::BlockList::iterator it = cfg.begin(); it != cfg.end(); ++it)
                {
                    BasicBlock *block = *it;
                    // Scanning instructions of basic block and make register lifetime table
                    for (size_t i = block->instr_begin; i != block->instr_end; ++i)
                    {
                        const size_t instr_offset = i - block->instr_begin;
                        const Instr& instr = f.instrs_[i];
                        if (instr.GetID() == I_COMPILER_DECLARE_REG_ARG)
                        {
                            // Declare function argument on register
                            const detail::Opd& opd0 = instr.GetOpd(0);
                            const RegID& reg = opd0.GetReg();
                            // Avoid passing operand size 8 or 16 to AddUsePoint
                            // because they are treated as partial access register and cause miss assignment of register.
                            OpdSize opd_size = opd0.GetSize();
                            if (opd_size == O_SIZE_8 || opd_size == O_SIZE_16)
                            {
                                opd_size = O_SIZE_32;
                            }
                            const detail::Opd& opd1 = instr.GetOpd(1);
                            block->GetLifetime(reg.GetType()).AddUsePoint(instr_offset, reg, opd0.GetType(), opd_size, opd0.reg_assignable_);
                            if (opd1.IsMem())
                            {
                                var_manager.SetSpillSlot(reg.GetType(), reg.id, Addr(opd1.GetBase(), opd1.GetDisp()));
                            }
                        }
                        else if (instr.GetID() == I_COMPILER_DECLARE_STACK_ARG)
                        {
                            // Declare function argument on stack
                            // The register variable starts "spill" state by O_TYPE_MEM of AddUsePoint
                            const detail::Opd& opd0 = instr.GetOpd(0);  // Register variable.
                            const RegID& reg = opd0.GetReg();
                            // Avoid passing operand size 8 or 16 to AddUsePoint
                            // because they are treated as partial access register and cause miss assignment of register.
                            OpdSize opd_size = opd0.GetSize();
                            if (opd_size == O_SIZE_8 || opd_size == O_SIZE_16)
                            {
                                opd_size = O_SIZE_32;
                            }
                            const detail::Opd& opd1 = instr.GetOpd(1);  // Argument
                            block->GetLifetime(reg.GetType()).AddUsePoint(instr_offset, reg, static_cast<OpdType>(O_TYPE_MEM | O_TYPE_WRITE), opd_size, opd0.reg_assignable_);
                            var_manager.SetSpillSlot(reg.GetType(), reg.id, Addr(opd1.GetBase(), opd1.GetDisp()));
                        }
                        else if (instr.GetID() == I_COMPILER_DECLARE_RESULT_REG)
                        {
                            // Declare function result on register
                            const detail::Opd& opd0 = instr.GetOpd(0);
                            const RegID& reg = opd0.GetReg();
                            block->GetLifetime(reg.GetType()).AddUsePoint(instr_offset, reg, opd0.GetType(), opd0.GetSize(), opd0.reg_assignable_);
                        }
                        else if (IsBreakDependenceInstr(instr))
                        {
                            // Add only 1 use point if the instruction that break register dependence
                            const detail::Opd& opd = instr.GetOpd(0);
                            const RegID& reg = opd.GetReg();
                            block->GetLifetime(reg.GetType()).AddUsePoint(instr_offset, reg, static_cast<OpdType>(O_TYPE_REG | O_TYPE_WRITE), opd.GetSize(), opd.reg_assignable_);
                            var_manager.UpdateVarSize(reg.GetType(), reg.id, opd.GetSize());
                        }
                        else if (instr.GetID() == I_PUSHAD || instr.GetID() == I_POPAD)
                        {
                            // Add use point of pushad/popad
                            const OpdType type = static_cast<OpdType>(O_TYPE_REG | (instr.GetID() == I_PUSHAD ? O_TYPE_READ : O_TYPE_WRITE));
                            block->GetLifetime(R_TYPE_GP).AddUsePoint(instr_offset, RegID::CreatePhysicalRegID(R_TYPE_GP, EAX), type, O_SIZE_32, 0xFFFFFFFF);
                            block->GetLifetime(R_TYPE_GP).AddUsePoint(instr_offset, RegID::CreatePhysicalRegID(R_TYPE_GP, ECX), type, O_SIZE_32, 0xFFFFFFFF);
                            block->GetLifetime(R_TYPE_GP).AddUsePoint(instr_offset, RegID::CreatePhysicalRegID(R_TYPE_GP, EDX), type, O_SIZE_32, 0xFFFFFFFF);
                            block->GetLifetime(R_TYPE_GP).AddUsePoint(instr_offset, RegID::CreatePhysicalRegID(R_TYPE_GP, EBX), type, O_SIZE_32, 0xFFFFFFFF);
                            block->GetLifetime(R_TYPE_GP).AddUsePoint(instr_offset, RegID::CreatePhysicalRegID(R_TYPE_GP, EBP), type, O_SIZE_32, 0xFFFFFFFF);
                            block->GetLifetime(R_TYPE_GP).AddUsePoint(instr_offset, RegID::CreatePhysicalRegID(R_TYPE_GP, ESI), type, O_SIZE_32, 0xFFFFFFFF);
                            block->GetLifetime(R_TYPE_GP).AddUsePoint(instr_offset, RegID::CreatePhysicalRegID(R_TYPE_GP, EDI), type, O_SIZE_32, 0xFFFFFFFF);
                            block->GetLifetime(R_TYPE_GP).AddUsePoint(instr_offset, RegID::CreatePhysicalRegID(R_TYPE_GP, ESP), static_cast<OpdType>(O_TYPE_REG | O_TYPE_READ | O_TYPE_WRITE), O_SIZE_32, 0xFFFFFFFF);
                        }
                        else if (instr.GetID() == I_VZEROALL || instr.GetID() == I_VZEROUPPER)
                        {
                            // Add use point of vzeroall/vzeroupper
                            const OpdType type = static_cast<OpdType>(O_TYPE_REG | (instr.GetID() == I_VZEROALL ? O_TYPE_WRITE : O_TYPE_READ | O_TYPE_WRITE));
                            for (int j = 0; j < NUM_OF_PHYSICAL_REG; ++j)
                            {
                                block->GetLifetime(R_TYPE_YMM).AddUsePoint(instr_offset, RegID::CreatePhysicalRegID(R_TYPE_YMM, static_cast<PhysicalRegID>(YMM0 + j)), type, O_SIZE_256, 0xFFFFFFFF);
                            }
                        }
                        else
                        {
                            // Add each use point of all operands
                            for (size_t j = 0; j < Instr::MAX_OPERAND_COUNT; ++j)
                            {
                                const detail::Opd& opd = instr.GetOpd(j);
                                if (opd.IsGpReg() || opd.IsMmxReg() || opd.IsXmmReg() || opd.IsYmmReg())
                                {
                                    // Register operand
                                    const RegID& reg = opd.GetReg();
                                    block->GetLifetime(reg.GetType()).AddUsePoint(instr_offset, reg, opd.GetType(), opd.GetSize(), opd.reg_assignable_);
                                    var_manager.UpdateVarSize(reg.GetType(), reg.id, opd.GetSize());
                                }
                                else if (opd.IsMem())
                                {
                                    // Memory operand
                                    const RegID& base = opd.GetBase();
                                    if (!base.IsInvalid())
                                    {
                                        block->GetLifetime(R_TYPE_GP).AddUsePoint(instr_offset, base, static_cast<OpdType>(O_TYPE_REG | O_TYPE_READ), opd.GetAddressBaseSize(), 0xFFFFFFFF);
                                        var_manager.UpdateVarSize(R_TYPE_GP, base.id, opd.GetAddressBaseSize());
                                    }
                                    const RegID& index = opd.GetIndex();
                                    if (!index.IsInvalid())
                                    {
                                        block->GetLifetime(index.GetType()).AddUsePoint(instr_offset, index, static_cast<OpdType>(O_TYPE_REG | O_TYPE_READ), opd.GetAddressIndexSize(), 0xFFFFFFFF);
                                        var_manager.UpdateVarSize(index.GetType(), index.id, opd.GetAddressIndexSize());
                                    }
                                }
                            }
                        }
                    }

                    // Make GEN and KILL set
                    for (size_t reg_family = 0; reg_family < 3; ++reg_family)
                    {
                        Lifetime& lifetime = block->lifetime[reg_family];
                        const size_t num_of_used_reg = lifetime.use_points.size();
                        for (size_t i = 0; i < num_of_used_reg; ++i)
                        {
                            if (!lifetime.use_points[i].empty())
                            {
                                OpdType type = lifetime.use_points[i][0].type;
                                if (type & O_TYPE_READ)
                                {
                                    lifetime.gen.set_bit(i, true);  // GEN
                                }
                                else
                                {
                                    JITASM_ASSERT(type & O_TYPE_WRITE);
                                    lifetime.kill.set_bit(i, true); // KILL
                                }
                            }
                        }
                    }

                    update_target.push_back(block);
                }

                while (!update_target.empty())
                {
                    BasicBlock *block = update_target.back();
                    update_target.pop_back();
                    for (size_t reg_family = 0; reg_family < 3; ++reg_family)
                    {
                        Lifetime& lifetime = block->lifetime[reg_family];
                        if (lifetime.dirty_live_out)
                        {
                            // live_out is the union of the live_in of the successors
                            for (size_t i = 0; i < 2; ++i)
                            {
                                if (block->successor[i])
                                {
                                    lifetime.live_out.set_union(block->successor[i]->lifetime[reg_family].live_in);
                                }
                            }
                            lifetime.dirty_live_out = false;

                            // live_in = gen OR (live_out - kill)
                            BitVector new_live_in = lifetime.live_out;
                            new_live_in.set_subtract(lifetime.kill);
                            new_live_in.set_union(lifetime.gen);

                            if (!lifetime.live_in.is_equal(new_live_in))
                            {
                                lifetime.live_in.swap(new_live_in);

                                for (size_t i = 0; i < block->predecessor.size(); ++i)
                                {
                                    block->predecessor[i]->lifetime[reg_family].dirty_live_out = true;
                                    update_target.push_back(block->predecessor[i]);
                                }
                            }
                        }
                    }
                }
            }

            /// Linear scan register allocation
            /**
            * \param[in,out] cfg            Control flow graph and additional information
            * \param[in]     reg_family Register family
            * \param[in]     available_reg  Available physical register mask
            * \param[out]    var_attrs      Variable attributes
            * \return   Used physical register mask
            */
            inline uint32 LinearScanRegisterAlloc(ControlFlowGraph& cfg, size_t reg_family, uint32 available_reg, std::vector<VarAttribute>& var_attrs)
            {
                const uint32 available_reg_count = detail::Count1Bits(available_reg);

                std::vector<int> total_spill_cost;
                for (ControlFlowGraph::BlockList::iterator block = cfg.begin(); block != cfg.end(); ++block)
                {
                    (*block)->lifetime[reg_family].BuildIntervals();
                    (*block)->lifetime[reg_family].GetSpillCost((*block)->GetFrequency(), total_spill_cost);
                }

                uint32 used_reg = 0;
                const Lifetime::Interval *last_interval = NULL;
                size_t last_loop_depth = 0;
                for (ControlFlowGraph::BlockList::iterator block = cfg.dfs_begin(); block != cfg.dfs_end(); ++block)
                {
                    Lifetime& lifetime = (*block)->lifetime[reg_family];
                    const size_t loop_depth = (*block)->loop_depth;

                    // Spill identification
                    lifetime.SpillIdentification(available_reg_count, total_spill_cost, (*block)->GetFrequency(), last_loop_depth == loop_depth ? last_interval : NULL, var_attrs);

                    // Register assignment
                    used_reg |= lifetime.AssignRegister(available_reg, last_interval);

#ifdef JITASM_DEBUG_DUMP
                    lifetime.DumpIntervals((*block)->depth, true);
#endif
                    if (!lifetime.intervals.empty())
                    {
                        last_interval = &lifetime.intervals.back();
                        last_loop_depth = loop_depth;
                    }
                }

                return used_reg;
            }

            /// General purpose register operator
            struct GpRegOperator
            {
                Frontend *f_;
                const VariableManager *var_manager_;

                GpRegOperator(Frontend *f, const VariableManager *var_manager) : f_(f), var_manager_(var_manager)
                {
                }

                void Move(PhysicalRegID dst_reg, PhysicalRegID src_reg, OpdSize /*size*/)
                {
                    f_->mov(Reg(dst_reg), Reg(src_reg));
                }

                void Swap(PhysicalRegID reg1, PhysicalRegID reg2, OpdSize /*size*/)
                {
                    f_->xchg(Reg(reg1), Reg(reg2));
                }

                void Load(PhysicalRegID dst_reg, int var)
                {
                    f_->mov(Reg(dst_reg), f_->ptr[var_manager_->GetSpillSlot(0, var)]);
                }

                void Store(int var, PhysicalRegID src_reg)
                {
                    f_->mov(f_->ptr[var_manager_->GetSpillSlot(0, var)], Reg(src_reg));
                }
            };

            /// MMX register operator
            struct MmxRegOperator
            {
                Frontend *f_;
                const VariableManager *var_manager_;

                MmxRegOperator(Frontend *f, const VariableManager *var_manager) : f_(f), var_manager_(var_manager)
                {
                }

                void Move(PhysicalRegID dst_reg, PhysicalRegID src_reg, OpdSize /*size*/)
                {
                    f_->movq(MmxReg(dst_reg), MmxReg(src_reg));
                }

                void Swap(PhysicalRegID reg1, PhysicalRegID reg2, OpdSize /*size*/)
                {
                    f_->pxor(MmxReg(reg1), MmxReg(reg2));
                    f_->pxor(MmxReg(reg2), MmxReg(reg1));
                    f_->pxor(MmxReg(reg1), MmxReg(reg2));
                }

                void Load(PhysicalRegID dst_reg, int var)
                {
                    f_->movq(MmxReg(dst_reg), f_->mmword_ptr[var_manager_->GetSpillSlot(1, var)]);
                }

                void Store(int var, PhysicalRegID src_reg)
                {
                    f_->movq(f_->mmword_ptr[var_manager_->GetSpillSlot(1, var)], MmxReg(src_reg));
                }
            };

            /// XMM/YMM register operator
            struct XmmRegOperator
            {
                Frontend *f_;
                const VariableManager *var_manager_;

                XmmRegOperator(Frontend *f, const VariableManager *var_manager) : f_(f), var_manager_(var_manager)
                {
                }

                void Move(PhysicalRegID dst_reg, PhysicalRegID src_reg, OpdSize size)
                {
                    if (size == O_SIZE_128)
                    {
                        f_->movaps(XmmReg(dst_reg), XmmReg(src_reg));
                    }
                    else if (size == O_SIZE_256)
                    {
                        f_->vmovaps(YmmReg(dst_reg), YmmReg(src_reg));
                    }
                    else
                    {
                        JITASM_ASSERT(0);
                    }
                }

                void Swap(PhysicalRegID reg1, PhysicalRegID reg2, OpdSize size)
                {
                    if (size == O_SIZE_128)
                    {
                        f_->xorps(XmmReg(reg1), XmmReg(reg2));
                        f_->xorps(XmmReg(reg2), XmmReg(reg1));
                        f_->xorps(XmmReg(reg1), XmmReg(reg2));
                    }
                    else if (size == O_SIZE_256)
                    {
                        f_->vxorps(YmmReg(reg1), YmmReg(reg1), YmmReg(reg2));
                        f_->vxorps(YmmReg(reg2), YmmReg(reg1), YmmReg(reg2));
                        f_->vxorps(YmmReg(reg1), YmmReg(reg1), YmmReg(reg2));
                    }
                    else
                    {
                        JITASM_ASSERT(0);
                    }
                }

                void Load(PhysicalRegID dst_reg, int var)
                {
                    const OpdSize size = var_manager_->GetVarSize(2, var);
                    if (size == O_SIZE_128)
                    {
                        f_->movaps(XmmReg(dst_reg), f_->xmmword_ptr[var_manager_->GetSpillSlot(2, var)]);
                    }
                    else if (size == O_SIZE_256)
                    {
                        f_->vmovaps(YmmReg(dst_reg), f_->ymmword_ptr[var_manager_->GetSpillSlot(2, var)]);
                    }
                    else
                    {
                        JITASM_ASSERT(0);
                    }
                }

                void Store(int var, PhysicalRegID src_reg)
                {
                    const OpdSize size = var_manager_->GetVarSize(2, var);
                    if (size == O_SIZE_128)
                    {
                        f_->movaps(f_->xmmword_ptr[var_manager_->GetSpillSlot(2, var)], XmmReg(src_reg));
                    }
                    else if (size == O_SIZE_256)
                    {
                        f_->vmovaps(f_->ymmword_ptr[var_manager_->GetSpillSlot(2, var)], YmmReg(src_reg));
                    }
                    else
                    {
                        JITASM_ASSERT(0);
                    }
                }
            };

            /// Strongly connected components finder
            /**
            * Tarjan's algorithm
            */
            class SCCFinder
            {
            private:
                struct Node
                {
                    int index;
                    int lowlink;
                    Node() : index(-1)
                    {
                    }
                };
                Node nodes_[NUM_OF_PHYSICAL_REG];
                int *successors_;
                int index;
                FixedArray<int, NUM_OF_PHYSICAL_REG> scc_;

                /// Is v in scc_?
                bool IsInsideSCC(int v) const
                {
                    for (size_t i = 0; i < scc_.size(); ++i)
                    {
                        if (scc_[i] == v)
                        {
                            return true;
                        }
                    }
                    return false;
                }

                template<class Fn> void Find(int v, Fn& fn)
                {
                    nodes_[v].index = index;
                    nodes_[v].lowlink = index;
                    ++index;
                    scc_.push_back(v);
                    const int w = successors_[v];
                    if (w != -1)
                    {
                        if (nodes_[w].index == -1)
                        {
                            // successor w has not been visited yet
                            Find(w, fn);
                            if (nodes_[w].lowlink < nodes_[v].lowlink)
                            {
                                nodes_[v].lowlink = nodes_[w].lowlink;
                            }
                        }
                        else if (IsInsideSCC(w))
                        {
                            // successor w is in scc_
                            if (nodes_[w].index < nodes_[v].lowlink)
                            {
                                nodes_[v].lowlink = nodes_[w].index;
                            }
                        }
                    }
                    if (nodes_[v].lowlink == nodes_[v].index && !scc_.empty())
                    {
                        // v is the root of scc_
                        size_t i = 0;
                        while (scc_[i] != v)
                        {
                            ++i;
                        }
                        fn(&scc_[i], scc_.size() - i);
                        while (i < scc_.size())
                        {
                            scc_.pop_back();
                        }
                    }
                }

            public:
                SCCFinder(int *successors) : successors_(successors), index(0)
                {
                }

                template<class Fn> void operator()(Fn fn)
                {
                    for (int v = 0; v < NUM_OF_PHYSICAL_REG; ++v)
                    {
                        if (successors_[v] != -1 && nodes_[v].index == -1)
                        {
                            Find(v, fn);
                        }
                    }
                }
            };

            struct Operations
            {
                int move[NUM_OF_PHYSICAL_REG];
                int load[NUM_OF_PHYSICAL_REG];
                int store[NUM_OF_PHYSICAL_REG];
                OpdSize size[NUM_OF_PHYSICAL_REG];
                std::pair<const Lifetime::Interval *, const Lifetime::Interval *> interval;
                const std::vector<VarAttribute> *var_attrs;

                Operations(const Lifetime::Interval *first, const Lifetime::Interval *second, const std::vector<VarAttribute> *vattrs) : interval(first, second), var_attrs(vattrs)
                {
                    for (size_t i = 0; i < NUM_OF_PHYSICAL_REG; ++i)
                    {
                        move[i] = load[i] = store[i] = -1;
                    }
                }

                void operator()(size_t var)
                {
                    if (interval.first->assignment_table.size())
                    {
                        if (interval.second->liveness.get_bit(var))
                        {
                            const bool first_spill = interval.first->spill.get_bit(var);
                            const bool second_spill = interval.second->spill.get_bit(var);
                            if (!first_spill)
                            {
                                const int first_reg = interval.first->assignment_table[var];
                                if (!second_spill)
                                {
                                    // register -> register
                                    move[first_reg] = interval.second->assignment_table[var];
                                    size[first_reg] = static_cast<OpdSize>(var_attrs->at(var).size);
                                }
                                else
                                {
                                    // register -> stack
                                    store[first_reg] = static_cast<int>(var);
                                }
                            }
                            else
                            {
                                if (!second_spill)
                                {
                                    // stack -> register
                                    load[interval.second->assignment_table[var]] = static_cast<int>(var);
                                }
                                else
                                {
                                    // stack -> stack
                                    // do nothing
                                }
                            }
                        }
                    }
                }
            };


            template<class RegOp>
            struct MoveGenerator
            {
                int *moves_;
                OpdSize *sizes_;
                RegOp *reg_operator_;
                MoveGenerator(int *moves, OpdSize *sizes, RegOp *reg_operator) : moves_(moves), sizes_(sizes), reg_operator_(reg_operator)
                {
                }
                void operator()(const int *scc, size_t count)
                {
                    if (count > 1)
                    {
                        for (size_t i = 0; i < count - 1; ++i)
                        {
                            const int r = scc[i];
                            JITASM_ASSERT(r != moves_[r] && moves_[r] != -1);
                            reg_operator_->Swap(static_cast<PhysicalRegID>(moves_[r]), static_cast<PhysicalRegID>(r), sizes_[r]);
                            JITASM_TRACE("Swap%d %d <-> %d", sizes_[r], moves_[r], r);
                        }
                    }
                    else if (moves_[scc[0]] != scc[0] && moves_[scc[0]] != -1)
                    {
                        const int r = scc[0];
                        reg_operator_->Move(static_cast<PhysicalRegID>(moves_[r]), static_cast<PhysicalRegID>(r), sizes_[r]);
                        JITASM_TRACE("Move%d %d -> %d", sizes_[r], r, moves_[r]);
                    }
                }
            };

            /// Generate inter-interval instructions
            /**
            * - Move register
            * - Load from stack slot
            * - Store to stack slot
            */
            template<class RegOp>
            inline void GenerateInterIntervalInstr(const Lifetime::Interval& first_interval, const Lifetime::Interval& second_interval, const std::vector<VarAttribute>& var_attrs, RegOp reg_operator)
            {
#ifdef JITASM_DEBUG_DUMP
                first_interval.Dump(true);
#endif

                Operations ops(&first_interval, &second_interval, &var_attrs);
                first_interval.liveness.query_bit_indexes(ops);

                // Store instructions
                for (size_t r = 0; r < NUM_OF_PHYSICAL_REG; ++r)
                {
                    if (ops.store[r] != -1)
                    {
                        reg_operator.Store(ops.store[r], static_cast<PhysicalRegID>(r));
                        JITASM_TRACE("Store %d (physical reg %d)", ops.store[r], r);
                    }
                }

                // Move instructions
                SCCFinder scc_finder(ops.move);
                scc_finder(MoveGenerator<RegOp>(ops.move, ops.size, &reg_operator));

                // Load instructions
                for (size_t r = 0; r < NUM_OF_PHYSICAL_REG; ++r)
                {
                    if (ops.load[r] != -1)
                    {
                        reg_operator.Load(static_cast<PhysicalRegID>(r), ops.load[r]);
                        JITASM_TRACE("Load %d (physical reg %d)", ops.load[r], r);
                    }
                }

#ifdef JITASM_DEBUG_DUMP
                second_interval.Dump(true);
#endif
            }

            /// Generate inter-block instructions
            inline void GenerateInterBlockInstr(const BasicBlock *first_block, const BasicBlock *second_block, Frontend& f, const VariableManager& var_manager)
            {
                if (!first_block->lifetime[0].intervals.empty() && !second_block->lifetime[0].intervals.empty())
                {
                    JITASM_TRACE("---- General purpose register ----");
                    GenerateInterIntervalInstr(first_block->lifetime[0].intervals.back(), second_block->lifetime[0].intervals.front(), var_manager.GetAttributes(0), GpRegOperator(&f, &var_manager));
                }
                if (!first_block->lifetime[1].intervals.empty() && !second_block->lifetime[1].intervals.empty())
                {
                    JITASM_TRACE("---- MMX register ----");
                    GenerateInterIntervalInstr(first_block->lifetime[1].intervals.back(), second_block->lifetime[1].intervals.front(), var_manager.GetAttributes(1), MmxRegOperator(&f, &var_manager));
                }
                if (!first_block->lifetime[2].intervals.empty() && !second_block->lifetime[2].intervals.empty())
                {
                    JITASM_TRACE("---- XMM/YMM register ----");
                    GenerateInterIntervalInstr(first_block->lifetime[2].intervals.back(), second_block->lifetime[2].intervals.front(), var_manager.GetAttributes(2), XmmRegOperator(&f, &var_manager));
                }
            }

            /// Generate prolog instructions
            inline void GenerateProlog(Frontend& f, const uint32(&preserved_reg)[3], const Addr& preserved_reg_stack)
            {
                avoid_unused_warn(preserved_reg_stack);

                // Save & Make frame pointer
                f.push(f.zbp);
                f.mov(f.zbp, f.zsp);

                size_t stack_size = f.stack_manager_.GetSize();

                // Save general-purpose registers
                size_t num_of_preserved_gp_reg = 0;
                for (uint32 reg_mask = preserved_reg[0]; reg_mask != 0; ++num_of_preserved_gp_reg)
                {
                    uint32 reg_id = detail::bit_scan_forward(reg_mask);
                    f.push(Reg(static_cast<PhysicalRegID>(reg_id)));
                    reg_mask &= ~(1 << reg_id);
                }

                // Stack base
                if (stack_size > 0)
                {
                    if (num_of_preserved_gp_reg & 1)
                    {
                        // Copy with alignment
                        f.lea(f.rbx, f.ptr[f.rsp - 8]);
                        stack_size += 8;    // padding for keep alignment
                    }
                    else
                    {
                        f.mov(f.rbx, f.rsp);
                    }
                }

                // Move stack pointer
                if (stack_size > 0)
                {
                    f.sub(f.zsp, static_cast<uint32>(stack_size));
                }

                // Save xmm registers
                uint32 xmm_reg_mask = preserved_reg[2];
                for (size_t i = 0; xmm_reg_mask != 0; ++i)
                {
                    uint32 reg_id = detail::bit_scan_forward(xmm_reg_mask);
                    f.movaps(f.xmmword_ptr[preserved_reg_stack + 16 * i], XmmReg(static_cast<PhysicalRegID>(reg_id)));
                    xmm_reg_mask &= ~(1 << reg_id);
                }
            }

            /// Generate epilog instructions
            inline void GenerateEpilog(Frontend& f, const uint32(&preserved_reg)[3], const Addr& preserved_reg_stack)
            {
                avoid_unused_warn(preserved_reg_stack);

                size_t stack_size = f.stack_manager_.GetSize();
                const size_t num_of_preserved_gp_reg = detail::Count1Bits(preserved_reg[0]);

                // Restore xmm registers
                // Push the register id and index by saved order
                FixedArray<uint32, 16> regs;
                for (uint32 reg_mask = preserved_reg[2]; reg_mask != 0;)
                {
                    uint32 reg_id = detail::bit_scan_forward(reg_mask);
                    regs.push_back(reg_id);
                    reg_mask &= ~(1 << reg_id);
                }

                // Insert restore instruction by inverse order
                while (!regs.empty())
                {
                    f.movaps(XmmReg(static_cast<PhysicalRegID>(regs.back())), f.xmmword_ptr[preserved_reg_stack + 16 * (regs.size() - 1)]);
                    regs.pop_back();
                }

                // Move stack pointer
                if (stack_size > 0)
                {
                    if (num_of_preserved_gp_reg & 1)
                    {
                        stack_size += 8;    // padding for keep alignment
                    }
                    f.add(f.zsp, static_cast<uint32>(stack_size));
                }

                // Restore general-purpose registers
                for (uint32 reg_mask = preserved_reg[0]; reg_mask != 0;)
                {
                    uint32 reg_id = detail::bit_scan_reverse(reg_mask);
                    f.pop(Reg(static_cast<PhysicalRegID>(reg_id)));
                    reg_mask &= ~(1 << reg_id);
                }

                // Restore frame pointer
                f.pop(f.zbp);

                f.ret();
            }

            struct OrderedLabel
            {
                size_t id;
                size_t instr_idx;
                OrderedLabel(size_t id_, size_t instr_idx_) : id(id_), instr_idx(instr_idx_)
                {
                }
                bool operator<(const OrderedLabel& rhs) const
                {
                    return instr_idx < rhs.instr_idx;
                }
            };

            bool RewriteInstructions(Frontend& f, size_t beg, size_t end);

            void RewriteInstructions(Frontend& f, const ControlFlowGraph& cfg);

            /// Compile
            void Compile(Frontend& f);

        }   // namespace compiler
    }   // namespace jitasm
} // namespace Allegrex

#pragma warning( pop )
#endif // __allegrex_jit_x86_64_h__
