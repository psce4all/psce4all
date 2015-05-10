/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "emu.h"
#include "emu.log.h"
#include "hal.hmm.h"
#include "hal.dbg.h"
#include "hal.npa.h"


void ForceLinkWithStartupCleanup()
{
}

emu::StartupCleanup::StartupCleanup()
{
    hal::hmm::Startup();
    hal::dbg::Startup();
    hal::npa::Startup();
    emu::log::Startup();
}

emu::StartupCleanup::~StartupCleanup()
{
    emu::log::Cleanup();
    hal::npa::Cleanup();
    hal::dbg::Cleanup();
    hal::hmm::Cleanup();
}

#pragma warning(disable:4073)
#pragma init_seg(lib)
emu::StartupCleanup startup_cleanup;