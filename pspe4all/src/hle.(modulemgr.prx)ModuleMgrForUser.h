//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_modulemgr_prx_ModuleMgrForUser_h__
#define hle_modulemgr_prx_ModuleMgrForUser_h__

namespace hle
{
    namespace ModuleMgrForUser //@hle:library-start{ModuleMgrForUser|sceModuleManager|modulemgr.prx}
    {
        //@hle:function{977DE386|ModuleMgrForUser|sceKernelLoadModule|gggg|SceUID sceKernelLoadModule(const char * path, int flags, const SceKernelLMOption * opt)}
        extern int  sceKernelLoadModule(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{710F61B5|ModuleMgrForUser|sceKernelLoadModuleMs|gggg|SceUID sceKernelLoadModuleMs(const char * path, int flags, SceKernelLMOption * option)}
        extern int  sceKernelLoadModuleMs(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{F9275D98|ModuleMgrForUser|sceKernelLoadModuleBufferUsbWlan|ggggg|SceUID sceKernelLoadModuleBufferUsbWlan(SceSize bufsize, void * buf, int flags, SceKernelLMOption * option)}
        extern int  sceKernelLoadModuleBufferUsbWlan(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{B7F46618|ModuleMgrForUser|sceKernelLoadModuleByID|gggg|SceUID sceKernelLoadModuleByID(SceUID fid, int flags, const SceKernelLMOption * opt)}
        extern int  sceKernelLoadModuleByID(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{50F0C1EC|ModuleMgrForUser|sceKernelStartModule|gggggg|int sceKernelStartModule(SceUID modid, SceSize args, void * argp, int * status, SceKernelSMOption * option)}
        extern int  sceKernelStartModule(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{D1FF982A|ModuleMgrForUser|sceKernelStopModule|gggggg|int sceKernelStopModule(SceUID modid, SceSize args, void * argp, int * status, SceKernelSMOption * option)}
        extern int  sceKernelStopModule(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{2E0911AA|ModuleMgrForUser|sceKernelUnloadModule|gg|int sceKernelUnloadModule(SceUID modid)}
        extern int  sceKernelUnloadModule(u32 $a0);
        //@hle:function{D675EBB8|ModuleMgrForUser|sceKernelSelfStopUnloadModule|gggg|int sceKernelSelfStopUnloadModule(int status, SceSize argsize, void * argp)}
        extern int  sceKernelSelfStopUnloadModule(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{CC1D3699|ModuleMgrForUser|sceKernelStopUnloadSelfModule|ggggg|int sceKernelStopUnloadSelfModule(SceSize args, void * argp, int * status, SceKernelSMOption * option)}
        extern int  sceKernelStopUnloadSelfModule(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{748CBED9|ModuleMgrForUser|sceKernelQueryModuleInfo|ggg|int sceKernelQueryModuleInfo(SceUID modid, SceKernelModuleInfo * info)}
        extern int  sceKernelQueryModuleInfo(u32 $a0, u32 $a1);
        //@hle:function{F0A26395|ModuleMgrForUser|sceKernelGetModuleId|g|SceUID sceKernelGetModuleId(void)}
        extern int  sceKernelGetModuleId();
        //@hle:function{D8B73127|ModuleMgrForUser|sceKernelGetModuleIdByAddress|gg|SceUID sceKernelGetModuleIdByAddress(const void * base)}
        extern int  sceKernelGetModuleIdByAddress(u32 $a0);
        //@hle:function{D2FBC957|ModuleMgrForUser|sceKernelGetModuleGPByAddress|gg|SceUID sceKernelGetModuleGPByAddress(int gp)}
        extern int  sceKernelGetModuleGPByAddress(u32 $a0);
        //@hle:function{644395E2|ModuleMgrForUser|sceKernelGetModuleIdList|gggg|int sceKernelGetModuleIdList(SceUID * readbuf, int readbufsize, int * idcount)}
        extern int  sceKernelGetModuleIdList(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{1196472E|ModuleMgrForUser|ModuleMgrForUser_1196472E|g|??? ModuleMgrForUser_1196472E()}
        extern int  ModuleMgrForUser_1196472E();
        //@hle:function{24EC0641|ModuleMgrForUser|ModuleMgrForUser_24EC0641|g|??? ModuleMgrForUser_24EC0641()}
        extern int  ModuleMgrForUser_24EC0641();
        //@hle:function{8F2DF740|ModuleMgrForUser|ModuleMgrForUser_8F2DF740|g|??? ModuleMgrForUser_8F2DF740()}
        extern int  ModuleMgrForUser_8F2DF740();
        //@hle:function{E4C4211C|ModuleMgrForUser|ModuleMgrForUser_E4C4211C|g|??? ModuleMgrForUser_E4C4211C()}
        extern int  ModuleMgrForUser_E4C4211C();
        //@hle:function{F2D8D1B4|ModuleMgrForUser|ModuleMgrForUser_F2D8D1B4|g|??? ModuleMgrForUser_F2D8D1B4()}
        extern int  ModuleMgrForUser_F2D8D1B4();
        //@hle:function{FBE27467|ModuleMgrForUser|ModuleMgrForUser_FBE27467|g|??? ModuleMgrForUser_FBE27467()}
        extern int  ModuleMgrForUser_FBE27467();
        //@hle:function{FEF27DC1|ModuleMgrForUser|ModuleMgrForUser_FEF27DC1|g|??? ModuleMgrForUser_FEF27DC1()}
        extern int  ModuleMgrForUser_FEF27DC1();
    } //@hle:library-end{ModuleMgrForUser|sceModuleManager|modulemgr.prx}
}
#endif