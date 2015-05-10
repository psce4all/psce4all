/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#define hle_kd_ThreadMan_h__

#define MAX_THREAD_PRIORITY     127
#define MIN_THREAD_STACKSIZE    0x200
#define THREAD_KSTACKSIZE       0x800

namespace hle
{
    namespace kd
    {
        struct Thread;
        struct Delay;
    }
}

#include "hle.kd.ThreadMan.IntrSoft2.h"
#include "hle.kd.ThreadMan.ThreadQueue.h"
#include "hle.kd.ThreadMan.WaitQueue.h"
#include "hle.kd.ThreadMan.Timer.h"
#include "hle.kd.ThreadMan.Callback.h"
#include "hle.kd.ThreadMan.EventHandler.h"
#include "hle.kd.ThreadMan.EventFlag.h"
#include "hle.kd.ThreadMan.Semaphore.h"
#include "hle.kd.ThreadMan.MsgBox.h"
#include "hle.kd.ThreadMan.MsgPipe.h"
#include "hle.kd.ThreadMan.Fpl.h"
#include "hle.kd.ThreadMan.Vpl.h"
#include "hle.kd.ThreadMan.ThreadContext.h"
#include "hle.kd.ThreadMan.Thread.h"
#include "hle.kd.ThreadMan.Scheduler.h"
