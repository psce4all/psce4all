/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#if 0 // 1 for WIN8, 0 for WIN7 or later
#define DCACHE_MEMORY_ADDRESS 0x000000007FFF0000ULL // 4   Gbyte: [07FFF0000,18FFF0000[
#define ICACHE_MEMORY_ADDRESS 0x0000000000000000ULL // 2   Gbyte: [000000000,080000000[
#define JITASM_MEMORY_ADDRESS 0x0000000000040000ULL // 127 Mbyte: [000040000,007F40000[ fits a gap in ICACHE_MEMORY_ADDRESS range
#define JITASM_MEMORY_SIZE    127*1024*1024
#else
#define DCACHE_MEMORY_ADDRESS 0x000000007FFF0000ULL // 4   Gbyte: [07FFF0000,18FFF0000[
#define ICACHE_MEMORY_ADDRESS 0x000000008FFF0000ULL // 2   Gbyte: [08FFF0000,10FFF0000[ fits a gap in DCACHE_MEMORY_ADDRESS range
#define JITASM_MEMORY_ADDRESS 0x000000009FFF0000ULL // 512 Mbyte: [09FFF0000,0BFFF0000[ fits a gap in both DCACHE_MEMORY_ADDRESS and ICACHE_MEMORY_ADDRESS ranges
#define JITASM_MEMORY_SIZE    512*1024*1024
#endif

static void * const lle_mmu$dcache = (void *)DCACHE_MEMORY_ADDRESS;
static void * const lle_mmu$icache = (void *)ICACHE_MEMORY_ADDRESS;

using p32u64 = u64 __based(lle_mmu$dcache) * __ptr32 __uptr;
using p32s64 = s64 __based(lle_mmu$dcache)* __ptr32 __uptr;

using p32u32 = u32 __based(lle_mmu$dcache)* __ptr32 __uptr;
using p32s32 = s32 __based(lle_mmu$dcache)* __ptr32 __uptr;

using p32u16 = u16 __based(lle_mmu$dcache)* __ptr32 __uptr;
using p32s16 = s16 __based(lle_mmu$dcache)* __ptr32 __uptr;

using p32u8 = u8 __based(lle_mmu$dcache)* __ptr32 __uptr;
using p32s8 = s8 __based(lle_mmu$dcache)* __ptr32 __uptr;

using p32f64 = f64 __based(lle_mmu$dcache)* __ptr32 __uptr;
using p32f32 = f32 __based(lle_mmu$dcache)* __ptr32 __uptr;

template< typename T > using p32 = T __based(lle_mmu$dcache) * __ptr32 __uptr;

template< typename T > using p32dcache = T __based(lle_mmu$dcache) * __ptr32 __uptr;
template< typename T > using p32icache = T __based(lle_mmu$icache) * __ptr32 __uptr;

extern HANDLE lle_jitasm$heap;

#include "emu.h"

namespace lle
{
    namespace mmu
    {
        template< typename T > static __forceinline T * Addr(u32 address) { return &((T &)(*((p32< T >)(address)))); }

        struct Interface : emu::Interface
        {
            /* interface v 1.0 */
        };
    }
}

#if !defined(EMU_EXPORTS)
extern "C" __declspec(dllimport) lle::mmu::Interface * lle_mmu$GetInterface(long version);
#else
extern "C" __declspec(dllexport) lle::mmu::Interface * lle_mmu$GetInterface(long version);
#endif
