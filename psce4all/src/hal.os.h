/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "emu.h"

#define CRITICALSECTION_USE_WIN32_CRITICALSECTION 1
#define CRITICALSECTION_USE_RECURSIVE_BENAPHORE   (!CRITICALSECTION_USE_WIN32_CRITICALSECTION)

#include "hal.Atomic.h"
#include "hal.IntrusivePointer.h"
#include "hal.MPSCQueue.h"
#include "hal.os.win32.h"
#include "hal.os.CriticalSection.h"
#include "hal.os.Thread.h"
#include "hal.os.CommandQueue.h"
