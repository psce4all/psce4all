/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

static inline u32 __any_ones(u32 x)
{
    x -= ((x >> 1) & 0x55555555);
    x  = ((x >> 2) & 0x33333333) + ((x >> 0) & 0x33333333);
    x  = ((x >> 4) + x) & 0x0f0f0f0f;
    x += ((x >> 8));
    x += ((x >> 16));
    return x & 0x3f;
}

static inline u32 __any_avg(u32 a, u32 b)
{
    s32 x = s32(a), y = s32(b);
    return (x&y)+((x^y)>>1);
}

static inline u32 __any_rotr(u32 _rt, u32 _sa)
{
    return (_rt >> _sa)|(_rt << (32-_sa));
}

static inline u32 __any_rotrv(u32 _rt, u32 _rs)
{
    u32 _sa = _rs & 31;
    return __any_rotr(_rt, _sa);
}

static inline u32 __any_clz(u32 _rs)
{
    _rs |= (_rs >>  1);
    _rs |= (_rs >>  2);
    _rs |= (_rs >>  4);
    _rs |= (_rs >>  8);
    _rs |= (_rs >> 16);
    return 32 - __any_ones(_rs);
}

static inline u32 __any_clo(u32 _rs)
{
    return __any_clz(~_rs);
}

static inline u32 __any_min(u32 _rs, u32 _rt)
{
    s32 x = s32(_rs), y = s32(_rt);
    return (x < y) ? x : y;
}

static inline u32 __any_max(u32 _rs, u32 _rt)
{
    s32 x = s32(_rs), y = s32(_rt);
    return (x > y) ? x : y;
}

static inline u32 __any_wsbh(u32 _rt)
{
    u32 x = _rt;
    return ((x & 0x00ff00ff) << 8)|((x & 0xff00ff00) >> 8);
}

static inline u32 __any_wsbw(u32 _rt)
{
    return __any_rotr(__any_wsbh(_rt), 16);
}

static inline u32 __any_bitrev(u32 _rt)
{
    u32 x = __any_wsbw(_rt);
    return
        ((x & 0x01010101) << 7)|
        ((x & 0x02020202) << 6)|
        ((x & 0x04040404) << 5)|
        ((x & 0x08080808) << 4)|
        ((x & 0x10101010) >> 4)|
        ((x & 0x20202020) >> 5)|
        ((x & 0x40404040) >> 6)|
        ((x & 0x80808080) >> 7);
}

static inline u32 __any_ext(u32 _rs, u32 pos, u32 len)
{
    return (_rs >> pos) & ~(~0 << len);
}

static inline u32 __any_ins(u32 _rt, u32 _rs, u32 pos, u32 len)
{
    u32 x = ~(~0 << len) << pos;
    return (_rt & ~x) | ((_rs << pos) & x);
}

static inline s64 __any_mult(u32 x, u32 y)
{
    return ((s64) x) * ((s32) y);
}

static inline u64 __any_multu(u32 x, u32 y)
{
    return ((u64) x) * ((u32) y);
}

static inline s64 __any_madd(u32 x, u32 y, u64 hilo)
{
    return ((s64) hilo) + ((s64) x) * ((s32) y);
}

static inline u64 __any_maddu(u32 x, u32 y, u64 hilo)
{
    return ((u64) hilo) + ((u64) x) * ((u32) y);
}

static inline s64 __any_msub(u32 x, u32 y, u64 hilo)
{
    return ((s64) hilo) - ((s64) x) * ((s32) y);
}

static inline u64 __any_msubu(u32 x, u32 y, u64 hilo)
{
    return ((u64) hilo) - ((u64) x) * ((u32) y);
}

static inline f32 __any_vsbn(f32 x, int y)
{
    return (y > 0) ? x * f32(1 << y) : x / f32(1 << -y);
}

#undef __host_rotr
#define __host_rotr(_rt, _sa) __any_rotr(_rt, _sa)

#undef __host_rotrv
#define __host_rotrv(_rt, _rs) __any_rotrv(_rt, _rs)

#undef __host_clz
#define __host_clz(_rs) __any_clz(_rs)

#undef __host_clo
#define __host_clo(_rs) __any_clo(_rs)

#undef __host_min
#define __host_min(_rs, _rt) __any_min(_rs, _rt)

#undef __host_max
#define __host_max(_rs, _rt) __any_max(_rs, _rt)

#undef __host_wsbh
#define __host_wsbh(_rt) __any_wsbh(_rt)

#undef __host_wsbw
#define __host_wsbw(_rt) __any_wsbw(_rt)

#undef __host_bitrev
#define __host_bitrev(_rt) __any_bitrev(_rt)

#undef __host_ext
#define __host_ext(_rs, pos, len) __any_ext(_rs, pos, len)

#undef __host_ins
#define __host_ins(_rt, _rs, pos, len) __any_ins(_rt, _rs, pos, len)

#undef __host_mult
#define __host_mult(x, y) __any_mult(x, y)

#undef __host_multu
#define __host_multu(x, y) __any_multu(x, y)

#undef __host_madd
#define __host_madd(x, y, hilo) __any_madd(x, y, hilo)

#undef __host_maddu
#define __host_maddu(x, y, hilo) __any_maddu(x, y, hilo)

#undef __host_msub
#define __host_msub(x, y, hilo) __any_msub(x, y, hilo)

#undef __host_msubu
#define __host_msubu(x, y) __any_msubu(x, y)

#undef __host_vsbn
#define __host_vsbn(x, y) __any_vsbn(x, y)

#if defined(__arch_x86__) && defined(__msvc__)

#include <intrin.h>
#include <xmmintrin.h>
#include <smmintrin.h>

#pragma intrinsic(__emul)
#pragma intrinsic(__emulu)
#pragma intrinsic(_BitScanReverse)

static __forceinline u32 __msvc_lzcnt(u32 rt)
{
    DWORD rd;
    _BitScanReverse(&rd, rt);
    return (rd^31);
}

static __forceinline u32 __msvc_rotr(u32 rt, u32 sa) { return _rotr(rt, sa); }
static __forceinline u32 __msvc_rotrv(u32 rt, u32 rs) { return __msvc_rotr(rt, rs & 31); }
static __forceinline u32 __msvc_clz(u32 rt) { return (rt) ? __msvc_lzcnt(rt) : 32; }
static __forceinline u32 __msvc_clo(u32 rt) { return __msvc_clz(~rt); }
static __forceinline u32 __msvc_wsbw(u32 rt) { return _byteswap_ulong(rt); }
static __forceinline u32 __msvc_wsbh(u32 rt) { return  _rotr(__msvc_wsbw(rt), 16); }
static __forceinline u32 __msvc_bitrev(u32 rt)
{
    rt = ((rt >> 1) & 0x55555555) | ((rt & 0x55555555) << 1);
    rt = ((rt >> 2) & 0x33333333) | ((rt & 0x33333333) << 2);
    rt = ((rt >> 4) & 0x0F0F0F0F) | ((rt & 0x0F0F0F0F) << 4);
    rt = ((rt >> 8) & 0x00FF00FF) | ((rt & 0x00FF00FF) << 8);
    rt = ( rt >> 16             ) | ( rt               << 16);
    return rt;
}
static __forceinline s64 __msvc_mult(u32 x, u32 y) { return __emul(s32(x), s32(y)); }
static __forceinline u64 __msvc_multu(u32 x, u32 y) { return __emulu(u32(x), u32(y)); }
static __forceinline s64 __msvc_madd(u32 x, u32 y, u64 hilo) { return ((s64) hilo) + __msvc_mult(x, y); }
static __forceinline u64 __msvc_maddu(u32 x, u32 y, u64 hilo) { return ((u64) hilo) + __msvc_multu(x, y); }
static __forceinline s64 __msvc_msub(u32 x, u32 y, u64 hilo) { return ((s64) hilo) - __msvc_mult(x, y); }
static __forceinline u64 __msvc_msubu(u32 x, u32 y, u64 hilo) { return ((u64) hilo) - __msvc_multu(x, y); }

#undef __host_rotr
#define __host_rotr(_rt, _sa) __msvc_rotr(_rt, _sa)

#undef __host_rotrv
#define __host_rotrv(_rt, _rs) __msvc_rotrv(_rt, _rs)

#undef __host_clz
#define __host_clz(_rs) __msvc_clz(_rs)

#undef __host_clo
#define __host_clo(_rs) __msvc_clo(_rs)

#undef __host_wsbh
#define __host_wsbh(_rt) __msvc_wsbh(_rt)

#undef __host_wsbw
#define __host_wsbw(_rt) __msvc_wsbw(_rt)

#undef __host_bitrev
#define __host_bitrev(_rt) __msvc_bitrev(_rt)

#undef __host_mult
#define __host_mult(x, y) __msvc_mult(x, y)

#undef __host_multu
#define __host_multu(x, y) __msvc_multu(x, y)

#undef __host_madd
#define __host_madd(x, y, hilo) __msvc_madd(x, y, hilo)

#undef __host_maddu
#define __host_maddu(x, y, hilo) __msvc_maddu(x, y, hilo)

#undef __host_msub
#define __host_msub(x, y, hilo) __msvc_msub(x, y, hilo)

#undef __host_msubu
#define __host_msubu(x, y) __msvc_msubu(x, y)

#endif
