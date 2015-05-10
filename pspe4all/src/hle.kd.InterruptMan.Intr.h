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
        /// KernelIntr //////////////////////////////////////////////////////////////

        struct IntrQueue : hal::LinkedList< Intr >
        {
        };

        struct Intr : IntrQueue::Node
        {
            enum
            {
                INTR_UART_ALL       = 0x00,
                INTR_SPI_ALL        = 0x01,
                INTR_TIM_PERI_ALL   = 0x02,
                INTR_USB_ALL        = 0x03,
                INTR_GPIO           = 0x04,
                INTR_ATA            = 0x05,
                INTR_SPOCK          = 0x06,
                INTR_SMS1           = 0x07,
                INTR_SMS2           = 0x08,
                INTR_MG             = 0x09,
                INTR_AUDIO1         = 0x0A,
                INTR_AUDIO2         = 0x0B,
                INTR_IIC            = 0x0C,
                INTR_KEY            = 0x0D,
                INTR_SIRCS          = 0x0E,
                INTR_TIM0_SYS       = 0x0F,
                INTR_TIM1_SYS       = 0x10,
                INTR_TIM2_SYS       = 0x11,
                INTR_TIM3_SYS       = 0x12,
                INTR_COUNT          = 0x13,
                INTR_EMC_SM         = 0x14,
                INTR_DMAC128        = 0x15,
                INTR_DMAC_SC1       = 0x16,
                INTR_DMAC_SC2       = 0x17,
                INTR_KIRK           = 0x18,
                INTR_GE             = 0x19,
                INTR_USB_MAIN       = 0x1A,
                INTR_VSYNC          = 0x1E,
                INTR_SYS_REG        = 0x1F,
                INTR_UART1          = 0x20,
                INTR_UART2          = 0x21,
                INTR_UART3          = 0x22,
                INTR_UART4          = 0x23,
                INTR_UART5          = 0x24,
                INTR_UART6          = 0x25,
                INTR_SPI1           = 0x28,
                INTR_SPI2           = 0x29,
                INTR_SPI3           = 0x2A,
                INTR_SPI4           = 0x2B,
                INTR_SPI5           = 0x2C,
                INTR_SPI6           = 0x2D,
                INTR_TIM1_PERI      = 0x30,
                INTR_TIM2_PERI      = 0x31,
                INTR_TIM3_PERI      = 0x32,
                INTR_TIM4_PERI      = 0x33,
                INTR_USB_RESUME     = 0x38,
                INTR_USB_CON        = 0x39,
                INTR_USB_DISCON     = 0x3A,
                INTR_USB_READY      = 0x3B,
                INTR_SMS1_CON       = 0x3C,
                INTR_SMS1_DISCON    = 0x3D,
                INTR_SMS2_CON       = 0x3E,
                INTR_SMS2_DISCON    = 0x3F,
                INTR_SOFT1          = 0x40,
                INTR_SOFT2          = 0x41,
                INTR_CPUTIMER       = 0x43,

                INTR_MAX
            };

            /**/                    Intr();
            virtual                ~Intr();

            bool                    m_enabled;

            int                     Enable();
            int                     Disable();
            bool                    IsEnabled();

            static Intr           * m_intr[INTR_MAX];
            static IntrQueue        m_intr_queue;
            bool                    m_triggered;

            void                    Trigger();
            virtual void            Execute();

            static bool             Register(int i, Intr *intr);
            static bool             Release(int i);

            int                     m_subintr_max;
            SubIntr               * m_subintr[32];

            static bool             m_ie;

            static int              Suspend();
            static void             Resume(int ie);

            static int              m_intr_context;

            static int              IsIntrContext();
        };
    }

    typedef kd::Intr      KernelIntr;
    typedef kd::IntrQueue KernelIntrQueue;
}
