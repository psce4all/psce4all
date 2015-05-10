//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(usb.prx)sceUsb.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceUsb //@hle:library-start{sceUsb|sceUSB_Driver|usb.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{112CC951|sceUsb|sceUsbGetDrvState|gg|int sceUsbGetDrvState(const char * driverName)}
        int  sceUsbGetDrvState(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1C360735|sceUsb|sceUsbWaitCancel|g|??? sceUsbWaitCancel()}
        int  sceUsbWaitCancel()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4E537366|sceUsb|sceUsbGetDrvList|g|??? sceUsbGetDrvList()}
        int  sceUsbGetDrvList()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{586DB82C|sceUsb|sceUsbActivate|gg|int sceUsbActivate(u32 pid)}
        int  sceUsbActivate(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5BE0E002|sceUsb|sceUsbWaitState|g|??? sceUsbWaitState()}
        int  sceUsbWaitState()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{616F2B61|sceUsb|sceUsbWaitStateCB|g|??? sceUsbWaitStateCB()}
        int  sceUsbWaitStateCB()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{89DE0DC5|sceUsb|sceUsb_89DE0DC5|g|??? sceUsb_89DE0DC5()}
        int  sceUsb_89DE0DC5()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8BFC3DE8|sceUsb|sceUsb_8BFC3DE8|g|??? sceUsb_8BFC3DE8()}
        int  sceUsb_8BFC3DE8()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AE5DE6AF|sceUsb|sceUsbStart|gggg|int sceUsbStart(const char * driverName, int size, void * args)}
        int  sceUsbStart(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C21645A4|sceUsb|sceUsbGetState|g|int sceUsbGetState(void)}
        int  sceUsbGetState()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C2464FA0|sceUsb|sceUsbStop|gggg|int sceUsbStop(const char * driverName, int size, void * args)}
        int  sceUsbStop(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C572A9C8|sceUsb|sceUsbDeactivate|gg|int sceUsbDeactivate(u32 pid)}
        int  sceUsbDeactivate(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E20B23A6|sceUsb|sceUsbActivateWithCharging|g|??? sceUsbActivateWithCharging()}
        int  sceUsbActivateWithCharging()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceUsb|sceUSB_Driver|usb.prx}
}

extern "C" bool __cdecl sceUsb$Init() { return hle::sceUsb::Init(); }
extern "C" bool __cdecl sceUsb$Fini() { return hle::sceUsb::Fini(); }
extern "C" void __cdecl sceUsb_112CC951(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceUsb::sceUsbGetDrvState                                >(c); } //@hle:syscall{112CC951|sceUsb|sceUsbGetDrvState|gg|int sceUsbGetDrvState(const char * driverName)}
extern "C" void __cdecl sceUsb_1C360735(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUsb::sceUsbWaitCancel                                 >(c); } //@hle:syscall{1C360735|sceUsb|sceUsbWaitCancel|g|??? sceUsbWaitCancel()}
extern "C" void __cdecl sceUsb_4E537366(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUsb::sceUsbGetDrvList                                 >(c); } //@hle:syscall{4E537366|sceUsb|sceUsbGetDrvList|g|??? sceUsbGetDrvList()}
extern "C" void __cdecl sceUsb_586DB82C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceUsb::sceUsbActivate                                   >(c); } //@hle:syscall{586DB82C|sceUsb|sceUsbActivate|gg|int sceUsbActivate(u32 pid)}
extern "C" void __cdecl sceUsb_5BE0E002(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUsb::sceUsbWaitState                                  >(c); } //@hle:syscall{5BE0E002|sceUsb|sceUsbWaitState|g|??? sceUsbWaitState()}
extern "C" void __cdecl sceUsb_616F2B61(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUsb::sceUsbWaitStateCB                                >(c); } //@hle:syscall{616F2B61|sceUsb|sceUsbWaitStateCB|g|??? sceUsbWaitStateCB()}
extern "C" void __cdecl sceUsb_89DE0DC5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUsb::sceUsb_89DE0DC5                                  >(c); } //@hle:syscall{89DE0DC5|sceUsb|sceUsb_89DE0DC5|g|??? sceUsb_89DE0DC5()}
extern "C" void __cdecl sceUsb_8BFC3DE8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUsb::sceUsb_8BFC3DE8                                  >(c); } //@hle:syscall{8BFC3DE8|sceUsb|sceUsb_8BFC3DE8|g|??? sceUsb_8BFC3DE8()}
extern "C" void __cdecl sceUsb_AE5DE6AF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceUsb::sceUsbStart                                      >(c); } //@hle:syscall{AE5DE6AF|sceUsb|sceUsbStart|gggg|int sceUsbStart(const char * driverName, int size, void * args)}
extern "C" void __cdecl sceUsb_C21645A4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUsb::sceUsbGetState                                   >(c); } //@hle:syscall{C21645A4|sceUsb|sceUsbGetState|g|int sceUsbGetState(void)}
extern "C" void __cdecl sceUsb_C2464FA0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceUsb::sceUsbStop                                       >(c); } //@hle:syscall{C2464FA0|sceUsb|sceUsbStop|gggg|int sceUsbStop(const char * driverName, int size, void * args)}
extern "C" void __cdecl sceUsb_C572A9C8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceUsb::sceUsbDeactivate                                 >(c); } //@hle:syscall{C572A9C8|sceUsb|sceUsbDeactivate|gg|int sceUsbDeactivate(u32 pid)}
extern "C" void __cdecl sceUsb_E20B23A6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUsb::sceUsbActivateWithCharging                       >(c); } //@hle:syscall{E20B23A6|sceUsb|sceUsbActivateWithCharging|g|??? sceUsbActivateWithCharging()}