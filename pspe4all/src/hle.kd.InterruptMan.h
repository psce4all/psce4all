/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#define hle_kd_InterruptMan_h__

namespace hle
{
    namespace kd
    {
        struct Intr;
        struct SubIntr;
    }
}

#include "hle.kd.InterruptMan.Intr.h"
#include "hle.kd.InterruptMan.SubIntr.h"

static __forceinline int  hleKernelCpuSuspendIntr()
{
    return hle::kd::Intr::Suspend();
}
static __forceinline void hleKernelCpuResumeIntr(int intr)
{
    hle::kd::Intr::Resume(intr);
}
static __forceinline int  hleKernelIsIntrContext()
{
    return hle::kd::Intr::IsIntrContext();
}

struct SceKernelCpuSuspendIntrScope
{
    SceKernelCpuSuspendIntrScope()
    {
        Suspend();
    }
    ~SceKernelCpuSuspendIntrScope()
    {
        Resume();
    }

    operator int const () const
    {
        return intr;
    }

    __forceinline void Resume()
    {
        hleKernelCpuResumeIntr(intr);
    }
    __forceinline void Suspend()
    {
        intr = hleKernelCpuSuspendIntr();
    }

private:
    int intr;
};
