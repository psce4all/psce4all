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

#include <QtWidgets>

void __forceinline vfstderrf(wchar_t const fmt[], va_list args) { wchar_t tmp[4096]; int len = swprintf(tmp, L"[TID:%04X]", ::GetCurrentThreadId()); vswprintf(tmp + len, fmt, args); qDebug() << tmp; }
void __forceinline vfstderrf(char    const fmt[], va_list args) { char tmp[4096]; int len = sprintf(tmp, "[TID:%04X]", ::GetCurrentThreadId()); vsprintf(tmp + len, fmt, args); qDebug() << tmp; }
void __forceinline fstderrf(wchar_t const fmt[], ...) { va_list args; va_start(args, fmt); vfstderrf(fmt, args); va_end(args); }
void __forceinline fstderrf(char    const fmt[], ...) { va_list args; va_start(args, fmt); vfstderrf(fmt, args); va_end(args); }
