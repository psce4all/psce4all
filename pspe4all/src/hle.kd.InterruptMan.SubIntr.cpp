/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

hle::kd::SubIntr::SubIntr(Intr *intr)
:   m_enabled(false)
,   m_intr(intr)
{
}

hle::kd::SubIntr::~SubIntr()
{
}

void hle::kd::SubIntr::Trigger()
{
    if (m_enabled)
    {
        Execute();
    }
}

void hle::kd::SubIntr::Execute()
{
}

int hle::kd::SubIntr::Enable()
{
    m_enabled = true;
    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::SubIntr::Disable()
{
    m_enabled = false;
    return SCE_KERNEL_ERROR_OK;
}
