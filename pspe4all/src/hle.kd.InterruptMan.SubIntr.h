/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifndef hle_kd_InterruptMan_h__
#error you must include "hle.kd.InterruptMan.h" instead
#endif

namespace hle
{
    namespace kd
    {
        /// KernelSubIntr ///////////////////////////////////////////////////////////

        struct SubIntr
        {
            /**/               SubIntr(Intr * intr);
            virtual           ~SubIntr();

            void               Trigger();
            virtual void       Execute();

            Intr             * m_intr;
            bool               m_enabled;

            int                Enable();
            int                Disable();
        };
    }

    typedef kd::SubIntr KernelSubIntr;
}
