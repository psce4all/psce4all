//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(mediaman.prx)sceUmdUser.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceUmdUser //@hle:library-start{sceUmdUser|sceUmd_driver|mediaman.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{20628E6F|sceUmdUser|sceUmdGetErrorStat|g|??? sceUmdGetErrorStat()}
        int  sceUmdGetErrorStat()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{340B7686|sceUmdUser|sceUmdGetDiscInfo|g|??? sceUmdGetDiscInfo()}
        int  sceUmdGetDiscInfo()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{46EBB729|sceUmdUser|sceUmdCheckMedium|gg|int sceUmdCheckMedium(int a)}
        int  sceUmdCheckMedium(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4A9E5E29|sceUmdUser|sceUmdWaitDriveStatCB|g|??? sceUmdWaitDriveStatCB()}
        int  sceUmdWaitDriveStatCB()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{56202973|sceUmdUser|sceUmdWaitDriveStatWithTimer|g|??? sceUmdWaitDriveStatWithTimer()}
        int  sceUmdWaitDriveStatWithTimer()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6AF9B50A|sceUmdUser|sceUmdCancelWaitDriveStat|g|??? sceUmdCancelWaitDriveStat()}
        int  sceUmdCancelWaitDriveStat()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6B4A146C|sceUmdUser|sceUmdGetDriveStat|g|??? sceUmdGetDriveStat()}
        int  sceUmdGetDriveStat()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{87533940|sceUmdUser|sceUmdReplaceProhibit|g|??? sceUmdReplaceProhibit()}
        int  sceUmdReplaceProhibit()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8EF08FCE|sceUmdUser|sceUmdWaitDriveStat|gg|int sceUmdWaitDriveStat(int stat)}
        int  sceUmdWaitDriveStat(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AEE7404D|sceUmdUser|sceUmdRegisterUMDCallBack|gg|int sceUmdRegisterUMDCallBack(int cbid)}
        int  sceUmdRegisterUMDCallBack(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BD2BDE07|sceUmdUser|sceUmdUnRegisterUMDCallBack|g|??? sceUmdUnRegisterUMDCallBack()}
        int  sceUmdUnRegisterUMDCallBack()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C6183D47|sceUmdUser|sceUmdActivate|ggg|int sceUmdActivate(int unit, const char * drive)}
        int  sceUmdActivate(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CBE9F02A|sceUmdUser|sceUmdReplacePermit|g|??? sceUmdReplacePermit()}
        int  sceUmdReplacePermit()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E83742BA|sceUmdUser|sceUmdDeactivate|g|??? sceUmdDeactivate()}
        int  sceUmdDeactivate()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceUmdUser|sceUmd_driver|mediaman.prx}
}

extern "C" bool __cdecl sceUmdUser$Init() { return hle::sceUmdUser::Init(); }
extern "C" bool __cdecl sceUmdUser$Fini() { return hle::sceUmdUser::Fini(); }
extern "C" void __cdecl sceUmdUser_20628E6F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdGetErrorStat                               >(c); } //@hle:syscall{20628E6F|sceUmdUser|sceUmdGetErrorStat|g|??? sceUmdGetErrorStat()}
extern "C" void __cdecl sceUmdUser_340B7686(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdGetDiscInfo                                >(c); } //@hle:syscall{340B7686|sceUmdUser|sceUmdGetDiscInfo|g|??? sceUmdGetDiscInfo()}
extern "C" void __cdecl sceUmdUser_46EBB729(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceUmdUser::sceUmdCheckMedium                                >(c); } //@hle:syscall{46EBB729|sceUmdUser|sceUmdCheckMedium|gg|int sceUmdCheckMedium(int a)}
extern "C" void __cdecl sceUmdUser_4A9E5E29(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdWaitDriveStatCB                            >(c); } //@hle:syscall{4A9E5E29|sceUmdUser|sceUmdWaitDriveStatCB|g|??? sceUmdWaitDriveStatCB()}
extern "C" void __cdecl sceUmdUser_56202973(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdWaitDriveStatWithTimer                     >(c); } //@hle:syscall{56202973|sceUmdUser|sceUmdWaitDriveStatWithTimer|g|??? sceUmdWaitDriveStatWithTimer()}
extern "C" void __cdecl sceUmdUser_6AF9B50A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdCancelWaitDriveStat                        >(c); } //@hle:syscall{6AF9B50A|sceUmdUser|sceUmdCancelWaitDriveStat|g|??? sceUmdCancelWaitDriveStat()}
extern "C" void __cdecl sceUmdUser_6B4A146C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdGetDriveStat                               >(c); } //@hle:syscall{6B4A146C|sceUmdUser|sceUmdGetDriveStat|g|??? sceUmdGetDriveStat()}
extern "C" void __cdecl sceUmdUser_87533940(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdReplaceProhibit                            >(c); } //@hle:syscall{87533940|sceUmdUser|sceUmdReplaceProhibit|g|??? sceUmdReplaceProhibit()}
extern "C" void __cdecl sceUmdUser_8EF08FCE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceUmdUser::sceUmdWaitDriveStat                              >(c); } //@hle:syscall{8EF08FCE|sceUmdUser|sceUmdWaitDriveStat|gg|int sceUmdWaitDriveStat(int stat)}
extern "C" void __cdecl sceUmdUser_AEE7404D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceUmdUser::sceUmdRegisterUMDCallBack                        >(c); } //@hle:syscall{AEE7404D|sceUmdUser|sceUmdRegisterUMDCallBack|gg|int sceUmdRegisterUMDCallBack(int cbid)}
extern "C" void __cdecl sceUmdUser_BD2BDE07(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdUnRegisterUMDCallBack                      >(c); } //@hle:syscall{BD2BDE07|sceUmdUser|sceUmdUnRegisterUMDCallBack|g|??? sceUmdUnRegisterUMDCallBack()}
extern "C" void __cdecl sceUmdUser_C6183D47(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceUmdUser::sceUmdActivate                                   >(c); } //@hle:syscall{C6183D47|sceUmdUser|sceUmdActivate|ggg|int sceUmdActivate(int unit, const char * drive)}
extern "C" void __cdecl sceUmdUser_CBE9F02A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdReplacePermit                              >(c); } //@hle:syscall{CBE9F02A|sceUmdUser|sceUmdReplacePermit|g|??? sceUmdReplacePermit()}
extern "C" void __cdecl sceUmdUser_E83742BA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceUmdUser::sceUmdDeactivate                                 >(c); } //@hle:syscall{E83742BA|sceUmdUser|sceUmdDeactivate|g|??? sceUmdDeactivate()}