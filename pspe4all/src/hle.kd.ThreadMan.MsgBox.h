/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifndef hle_kd_ThreadMan_h__
#error you must include "hle.kd.ThreadMan.h" instead
#endif

namespace hle
{
    namespace kd
    {
        /// KernelMsgBox ////////////////////////////////////////////////////////////

        struct MsgBox : WaitQueue
        {
            declare_kernel_type(MsgBox, WaitQueue);

            MsgBox() : WaitQueue("TODO:KernelMsgBox", 0)
            { /*TODO*/
            }
        };
    }

    typedef kd::MsgBox KernelMsgBox;
}
