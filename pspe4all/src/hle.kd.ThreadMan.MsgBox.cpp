/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

char const * hle::kd::MsgBox::m_object_type = "KernelMsgBox";

void hle::kd::MsgBox::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}
