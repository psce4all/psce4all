/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#define MINIMAL_EMU_LOG
#define MINIMAL_LLE_MMU

#include "pspe4all.pch.h"

#include "emu.log.h"
#include "lle.mmu.h"
#include "dbg.svr.h"

void __forceinline vfstderrf(wchar_t const fmt[], va_list args) { fputc('\n', stderr); vfwprintf(stderr, fmt, args); }
void __forceinline vfstderrf(char    const fmt[], va_list args) { fputc('\n', stderr); vfprintf(stderr, fmt, args); }
void __forceinline fstderrf(wchar_t const fmt[], ...) { va_list args; va_start(args, fmt); vfstderrf(fmt, args); va_end(args); }
void __forceinline fstderrf(char    const fmt[], ...) { va_list args; va_start(args, fmt); vfstderrf(fmt, args); va_end(args); }
