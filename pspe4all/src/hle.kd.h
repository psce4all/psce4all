/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "emu.log.h"

namespace emu
{
    namespace log
    {
        extern SubCategory kd;
    }
}

#include "hal.hmm.h"
#include "hal.LinkedList.h"
#include "hle.sce.h"
#include "hle.kd.Object.h"
#include "hle.kd.SysMem.h"
#include "hle.kd.InterruptMan.h"
#include "hle.kd.ThreadMan.h"
#include "hle.kd.LoadExecForUser.h"
#include "hle.kd.ModuleMgr.h"
#include "hle.kd.ElfLoader.h"
#if 0
#include "kernel_Syscall.h"
#include "kernel_ModuleMgr.h"
#include "kernel_Display.h"
#include "kernel_IoFileMgr.h"
#include "kernel_Audio.h"
#include "kernel_Ge.h"
#endif

namespace hle
{
    namespace kd
    {
        bool Reboot();
        bool ShutDown();
    }
}
