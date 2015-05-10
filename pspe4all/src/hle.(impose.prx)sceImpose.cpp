//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(impose.prx)sceImpose.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceImpose //@hle:library-start{sceImpose|sceImpose_Driver|impose.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{0F341BE4|sceImpose|sceImposeGetHomePopup|g|??? sceImposeGetHomePopup()}
        int  sceImposeGetHomePopup()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{24FD7BCF|sceImpose|sceImposeGetLanguageMode|g|??? sceImposeGetLanguageMode()}
        int  sceImposeGetLanguageMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{36AA6E91|sceImpose|sceImposeSetLanguageMode|g|??? sceImposeSetLanguageMode()}
        int  sceImposeSetLanguageMode()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{381BD9E7|sceImpose|sceImposeHomeButton|g|??? sceImposeHomeButton()}
        int  sceImposeHomeButton()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5595A71A|sceImpose|sceImposeSetHomePopup|g|??? sceImposeSetHomePopup()}
        int  sceImposeSetHomePopup()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{72189C48|sceImpose|sceImposeSetUMDPopup|g|??? sceImposeSetUMDPopup()}
        int  sceImposeSetUMDPopup()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8C943191|sceImpose|sceImposeGetBatteryIconStatus|g|??? sceImposeGetBatteryIconStatus()}
        int  sceImposeGetBatteryIconStatus()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8F6E3518|sceImpose|sceImposeGetBacklightOffTime|g|??? sceImposeGetBacklightOffTime()}
        int  sceImposeGetBacklightOffTime()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{967F6D4A|sceImpose|sceImposeSetBacklightOffTime|g|??? sceImposeSetBacklightOffTime()}
        int  sceImposeSetBacklightOffTime()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9BA61B49|sceImpose|sceImpose_9BA61B49|g|??? sceImpose_9BA61B49()}
        int  sceImpose_9BA61B49()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A9884B00|sceImpose|sceImpose_A9884B00|g|??? sceImpose_A9884B00()}
        int  sceImpose_A9884B00()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BB3F5DEC|sceImpose|sceImpose_BB3F5DEC|g|??? sceImpose_BB3F5DEC()}
        int  sceImpose_BB3F5DEC()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E0887BC8|sceImpose|sceImposeGetUMDPopup|g|??? sceImposeGetUMDPopup()}
        int  sceImposeGetUMDPopup()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FCD44963|sceImpose|sceImpose_FCD44963|g|??? sceImpose_FCD44963()}
        int  sceImpose_FCD44963()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FF1A2F07|sceImpose|sceImpose_FF1A2F07|g|??? sceImpose_FF1A2F07()}
        int  sceImpose_FF1A2F07()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceImpose|sceImpose_Driver|impose.prx}
}

extern "C" bool __cdecl sceImpose$Init() { return hle::sceImpose::Init(); }
extern "C" bool __cdecl sceImpose$Fini() { return hle::sceImpose::Fini(); }
extern "C" void __cdecl sceImpose_0F341BE4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeGetHomePopup                            >(c); } //@hle:syscall{0F341BE4|sceImpose|sceImposeGetHomePopup|g|??? sceImposeGetHomePopup()}
extern "C" void __cdecl sceImpose_24FD7BCF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeGetLanguageMode                         >(c); } //@hle:syscall{24FD7BCF|sceImpose|sceImposeGetLanguageMode|g|??? sceImposeGetLanguageMode()}
extern "C" void __cdecl sceImpose_36AA6E91(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeSetLanguageMode                         >(c); } //@hle:syscall{36AA6E91|sceImpose|sceImposeSetLanguageMode|g|??? sceImposeSetLanguageMode()}
extern "C" void __cdecl sceImpose_381BD9E7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeHomeButton                              >(c); } //@hle:syscall{381BD9E7|sceImpose|sceImposeHomeButton|g|??? sceImposeHomeButton()}
extern "C" void __cdecl sceImpose_5595A71A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeSetHomePopup                            >(c); } //@hle:syscall{5595A71A|sceImpose|sceImposeSetHomePopup|g|??? sceImposeSetHomePopup()}
extern "C" void __cdecl sceImpose_72189C48(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeSetUMDPopup                             >(c); } //@hle:syscall{72189C48|sceImpose|sceImposeSetUMDPopup|g|??? sceImposeSetUMDPopup()}
extern "C" void __cdecl sceImpose_8C943191(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeGetBatteryIconStatus                    >(c); } //@hle:syscall{8C943191|sceImpose|sceImposeGetBatteryIconStatus|g|??? sceImposeGetBatteryIconStatus()}
extern "C" void __cdecl sceImpose_8F6E3518(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeGetBacklightOffTime                     >(c); } //@hle:syscall{8F6E3518|sceImpose|sceImposeGetBacklightOffTime|g|??? sceImposeGetBacklightOffTime()}
extern "C" void __cdecl sceImpose_967F6D4A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeSetBacklightOffTime                     >(c); } //@hle:syscall{967F6D4A|sceImpose|sceImposeSetBacklightOffTime|g|??? sceImposeSetBacklightOffTime()}
extern "C" void __cdecl sceImpose_9BA61B49(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImpose_9BA61B49                               >(c); } //@hle:syscall{9BA61B49|sceImpose|sceImpose_9BA61B49|g|??? sceImpose_9BA61B49()}
extern "C" void __cdecl sceImpose_A9884B00(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImpose_A9884B00                               >(c); } //@hle:syscall{A9884B00|sceImpose|sceImpose_A9884B00|g|??? sceImpose_A9884B00()}
extern "C" void __cdecl sceImpose_BB3F5DEC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImpose_BB3F5DEC                               >(c); } //@hle:syscall{BB3F5DEC|sceImpose|sceImpose_BB3F5DEC|g|??? sceImpose_BB3F5DEC()}
extern "C" void __cdecl sceImpose_E0887BC8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImposeGetUMDPopup                             >(c); } //@hle:syscall{E0887BC8|sceImpose|sceImposeGetUMDPopup|g|??? sceImposeGetUMDPopup()}
extern "C" void __cdecl sceImpose_FCD44963(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImpose_FCD44963                               >(c); } //@hle:syscall{FCD44963|sceImpose|sceImpose_FCD44963|g|??? sceImpose_FCD44963()}
extern "C" void __cdecl sceImpose_FF1A2F07(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceImpose::sceImpose_FF1A2F07                               >(c); } //@hle:syscall{FF1A2F07|sceImpose|sceImpose_FF1A2F07|g|??? sceImpose_FF1A2F07()}