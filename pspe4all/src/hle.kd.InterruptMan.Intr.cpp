/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

int                hle::kd::Intr::m_intr_context = 0;
hle::kd::Intr    * hle::kd::Intr::m_intr[hle::kd::Intr::INTR_MAX] = { 0, };
hle::kd::IntrQueue hle::kd::Intr::m_intr_queue;
bool               hle::kd::Intr::m_ie = true;

hle::kd::Intr::Intr()
:   m_enabled(false)
,   m_triggered(false)
,   m_subintr_max(0)
{
    ::memset(m_subintr, 0, sizeof(hle::kd::SubIntr*)*32);
}

hle::kd::Intr::~Intr()
{
}

int hle::kd::Intr::Enable()
{
    m_enabled = true;
    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Intr::Disable()
{
    m_enabled = false;
    return SCE_KERNEL_ERROR_OK;
}

bool hle::kd::Intr::IsEnabled()
{
    return m_enabled;
}

bool hle::kd::Intr::Register(int i, hle::kd::Intr *intr)
{
    if (!m_intr[i])
    {
        m_intr[i] = intr;
        return true;
    }
    return false;
}

bool hle::kd::Intr::Release(int i)
{
    if (m_intr[i])
    {
        m_intr[i] = 0;
        return true;
    }
    return false;
}

void hle::kd::Intr::Trigger()
{
    m_intr_context++;
    if (m_enabled && m_ie)
    {
        if (m_triggered)
        {
            this->RemoveFromList();
            m_triggered = false;
        }
        Execute();
    }
    else if (!m_triggered)
    {
        m_triggered = true;
        m_intr_queue.Append(this);
    }
    m_intr_context--;
}

void hle::kd::Intr::Execute() // to overload
{
    for (int i = 0; i < m_subintr_max; ++i)
    {
        hle::kd::SubIntr * subintr = m_subintr[i];
        if (subintr)
        {
            subintr->Trigger();
        }
    }
}

int hle::kd::Intr::IsIntrContext()
{
    return m_intr_context;
}

int hle::kd::Intr::Suspend()
{
    // get old state
    int result = m_ie;

    // suspend immediate interrupt execution
    m_ie = false;

    // return old state
    return result;
}

void hle::kd::Intr::Resume(int allowed)
{
    m_ie = 0 != allowed;

    // resume all waiting interrupts if allowed
    if (allowed)
    {
        while (hle::kd::Intr * that = m_intr_queue.First())
        {
            that->Trigger();
        }
    }
}

