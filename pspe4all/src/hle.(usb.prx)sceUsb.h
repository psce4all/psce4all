//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_usb_prx_sceUsb_h__
#define hle_usb_prx_sceUsb_h__

namespace hle
{
    namespace sceUsb //@hle:library-start{sceUsb|sceUSB_Driver|usb.prx}
    {
        //@hle:function{112CC951|sceUsb|sceUsbGetDrvState|gg|int sceUsbGetDrvState(const char * driverName)}
        extern int  sceUsbGetDrvState(u32 $a0);
        //@hle:function{1C360735|sceUsb|sceUsbWaitCancel|g|??? sceUsbWaitCancel()}
        extern int  sceUsbWaitCancel();
        //@hle:function{4E537366|sceUsb|sceUsbGetDrvList|g|??? sceUsbGetDrvList()}
        extern int  sceUsbGetDrvList();
        //@hle:function{586DB82C|sceUsb|sceUsbActivate|gg|int sceUsbActivate(u32 pid)}
        extern int  sceUsbActivate(u32 $a0);
        //@hle:function{5BE0E002|sceUsb|sceUsbWaitState|g|??? sceUsbWaitState()}
        extern int  sceUsbWaitState();
        //@hle:function{616F2B61|sceUsb|sceUsbWaitStateCB|g|??? sceUsbWaitStateCB()}
        extern int  sceUsbWaitStateCB();
        //@hle:function{89DE0DC5|sceUsb|sceUsb_89DE0DC5|g|??? sceUsb_89DE0DC5()}
        extern int  sceUsb_89DE0DC5();
        //@hle:function{8BFC3DE8|sceUsb|sceUsb_8BFC3DE8|g|??? sceUsb_8BFC3DE8()}
        extern int  sceUsb_8BFC3DE8();
        //@hle:function{AE5DE6AF|sceUsb|sceUsbStart|gggg|int sceUsbStart(const char * driverName, int size, void * args)}
        extern int  sceUsbStart(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{C21645A4|sceUsb|sceUsbGetState|g|int sceUsbGetState(void)}
        extern int  sceUsbGetState();
        //@hle:function{C2464FA0|sceUsb|sceUsbStop|gggg|int sceUsbStop(const char * driverName, int size, void * args)}
        extern int  sceUsbStop(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{C572A9C8|sceUsb|sceUsbDeactivate|gg|int sceUsbDeactivate(u32 pid)}
        extern int  sceUsbDeactivate(u32 $a0);
        //@hle:function{E20B23A6|sceUsb|sceUsbActivateWithCharging|g|??? sceUsbActivateWithCharging()}
        extern int  sceUsbActivateWithCharging();
    } //@hle:library-end{sceUsb|sceUSB_Driver|usb.prx}
}
#endif