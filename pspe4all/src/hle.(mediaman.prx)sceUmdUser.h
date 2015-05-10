//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_mediaman_prx_sceUmdUser_h__
#define hle_mediaman_prx_sceUmdUser_h__

namespace hle
{
    namespace sceUmdUser //@hle:library-start{sceUmdUser|sceUmd_driver|mediaman.prx}
    {
        //@hle:function{20628E6F|sceUmdUser|sceUmdGetErrorStat|g|??? sceUmdGetErrorStat()}
        extern int  sceUmdGetErrorStat();
        //@hle:function{340B7686|sceUmdUser|sceUmdGetDiscInfo|g|??? sceUmdGetDiscInfo()}
        extern int  sceUmdGetDiscInfo();
        //@hle:function{46EBB729|sceUmdUser|sceUmdCheckMedium|gg|int sceUmdCheckMedium(int a)}
        extern int  sceUmdCheckMedium(u32 $a0);
        //@hle:function{4A9E5E29|sceUmdUser|sceUmdWaitDriveStatCB|g|??? sceUmdWaitDriveStatCB()}
        extern int  sceUmdWaitDriveStatCB();
        //@hle:function{56202973|sceUmdUser|sceUmdWaitDriveStatWithTimer|g|??? sceUmdWaitDriveStatWithTimer()}
        extern int  sceUmdWaitDriveStatWithTimer();
        //@hle:function{6AF9B50A|sceUmdUser|sceUmdCancelWaitDriveStat|g|??? sceUmdCancelWaitDriveStat()}
        extern int  sceUmdCancelWaitDriveStat();
        //@hle:function{6B4A146C|sceUmdUser|sceUmdGetDriveStat|g|??? sceUmdGetDriveStat()}
        extern int  sceUmdGetDriveStat();
        //@hle:function{87533940|sceUmdUser|sceUmdReplaceProhibit|g|??? sceUmdReplaceProhibit()}
        extern int  sceUmdReplaceProhibit();
        //@hle:function{8EF08FCE|sceUmdUser|sceUmdWaitDriveStat|gg|int sceUmdWaitDriveStat(int stat)}
        extern int  sceUmdWaitDriveStat(u32 $a0);
        //@hle:function{AEE7404D|sceUmdUser|sceUmdRegisterUMDCallBack|gg|int sceUmdRegisterUMDCallBack(int cbid)}
        extern int  sceUmdRegisterUMDCallBack(u32 $a0);
        //@hle:function{BD2BDE07|sceUmdUser|sceUmdUnRegisterUMDCallBack|g|??? sceUmdUnRegisterUMDCallBack()}
        extern int  sceUmdUnRegisterUMDCallBack();
        //@hle:function{C6183D47|sceUmdUser|sceUmdActivate|ggg|int sceUmdActivate(int unit, const char * drive)}
        extern int  sceUmdActivate(u32 $a0, u32 $a1);
        //@hle:function{CBE9F02A|sceUmdUser|sceUmdReplacePermit|g|??? sceUmdReplacePermit()}
        extern int  sceUmdReplacePermit();
        //@hle:function{E83742BA|sceUmdUser|sceUmdDeactivate|g|??? sceUmdDeactivate()}
        extern int  sceUmdDeactivate();
    } //@hle:library-end{sceUmdUser|sceUmd_driver|mediaman.prx}
}
#endif