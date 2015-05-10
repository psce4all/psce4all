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
        /// KernelIntrSoft2 /////////////////////////////////////////////////////////

        struct IntrSoft2 : Intr /*, EmulatorEvent*/
        {
            /**/  IntrSoft2()
            {
                Intr::Register(INTR_SOFT2, this);
                this->Enable();
            }
            /**/ ~IntrSoft2()
            {
                this->Disable();
                Intr::Release(INTR_SOFT2);
            }

            bool  Handle()
            {
                Trigger();
                return true;
            }

            void  Execute()
            {
            }
        };
    }

    typedef kd::IntrSoft2 KernelIntrSoft2;
}
