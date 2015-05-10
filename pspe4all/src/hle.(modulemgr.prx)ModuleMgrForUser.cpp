//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(modulemgr.prx)ModuleMgrForUser.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace ModuleMgrForUser //@hle:library-start{ModuleMgrForUser|sceModuleManager|modulemgr.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{977DE386|ModuleMgrForUser|sceKernelLoadModule|gggg|SceUID sceKernelLoadModule(const char * path, int flags, const SceKernelLMOption * opt)}
        int  sceKernelLoadModule(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{710F61B5|ModuleMgrForUser|sceKernelLoadModuleMs|gggg|SceUID sceKernelLoadModuleMs(const char * path, int flags, SceKernelLMOption * option)}
        int  sceKernelLoadModuleMs(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F9275D98|ModuleMgrForUser|sceKernelLoadModuleBufferUsbWlan|ggggg|SceUID sceKernelLoadModuleBufferUsbWlan(SceSize bufsize, void * buf, int flags, SceKernelLMOption * option)}
        int  sceKernelLoadModuleBufferUsbWlan(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B7F46618|ModuleMgrForUser|sceKernelLoadModuleByID|gggg|SceUID sceKernelLoadModuleByID(SceUID fid, int flags, const SceKernelLMOption * opt)}
        int  sceKernelLoadModuleByID(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{50F0C1EC|ModuleMgrForUser|sceKernelStartModule|gggggg|int sceKernelStartModule(SceUID modid, SceSize args, void * argp, int * status, SceKernelSMOption * option)}
        int  sceKernelStartModule(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D1FF982A|ModuleMgrForUser|sceKernelStopModule|gggggg|int sceKernelStopModule(SceUID modid, SceSize args, void * argp, int * status, SceKernelSMOption * option)}
        int  sceKernelStopModule(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2E0911AA|ModuleMgrForUser|sceKernelUnloadModule|gg|int sceKernelUnloadModule(SceUID modid)}
        int  sceKernelUnloadModule(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D675EBB8|ModuleMgrForUser|sceKernelSelfStopUnloadModule|gggg|int sceKernelSelfStopUnloadModule(int status, SceSize argsize, void * argp)}
        int  sceKernelSelfStopUnloadModule(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CC1D3699|ModuleMgrForUser|sceKernelStopUnloadSelfModule|ggggg|int sceKernelStopUnloadSelfModule(SceSize args, void * argp, int * status, SceKernelSMOption * option)}
        int  sceKernelStopUnloadSelfModule(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{748CBED9|ModuleMgrForUser|sceKernelQueryModuleInfo|ggg|int sceKernelQueryModuleInfo(SceUID modid, SceKernelModuleInfo * info)}
        int  sceKernelQueryModuleInfo(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F0A26395|ModuleMgrForUser|sceKernelGetModuleId|g|SceUID sceKernelGetModuleId(void)}
        int  sceKernelGetModuleId()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D8B73127|ModuleMgrForUser|sceKernelGetModuleIdByAddress|gg|SceUID sceKernelGetModuleIdByAddress(const void * base)}
        int  sceKernelGetModuleIdByAddress(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D2FBC957|ModuleMgrForUser|sceKernelGetModuleGPByAddress|gg|SceUID sceKernelGetModuleGPByAddress(int gp)}
        int  sceKernelGetModuleGPByAddress(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{644395E2|ModuleMgrForUser|sceKernelGetModuleIdList|gggg|int sceKernelGetModuleIdList(SceUID * readbuf, int readbufsize, int * idcount)}
        int  sceKernelGetModuleIdList(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1196472E|ModuleMgrForUser|ModuleMgrForUser_1196472E|g|??? ModuleMgrForUser_1196472E()}
        int  ModuleMgrForUser_1196472E()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{24EC0641|ModuleMgrForUser|ModuleMgrForUser_24EC0641|g|??? ModuleMgrForUser_24EC0641()}
        int  ModuleMgrForUser_24EC0641()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8F2DF740|ModuleMgrForUser|ModuleMgrForUser_8F2DF740|g|??? ModuleMgrForUser_8F2DF740()}
        int  ModuleMgrForUser_8F2DF740()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E4C4211C|ModuleMgrForUser|ModuleMgrForUser_E4C4211C|g|??? ModuleMgrForUser_E4C4211C()}
        int  ModuleMgrForUser_E4C4211C()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F2D8D1B4|ModuleMgrForUser|ModuleMgrForUser_F2D8D1B4|g|??? ModuleMgrForUser_F2D8D1B4()}
        int  ModuleMgrForUser_F2D8D1B4()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FBE27467|ModuleMgrForUser|ModuleMgrForUser_FBE27467|g|??? ModuleMgrForUser_FBE27467()}
        int  ModuleMgrForUser_FBE27467()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FEF27DC1|ModuleMgrForUser|ModuleMgrForUser_FEF27DC1|g|??? ModuleMgrForUser_FEF27DC1()}
        int  ModuleMgrForUser_FEF27DC1()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{ModuleMgrForUser|sceModuleManager|modulemgr.prx}
}

extern "C" bool __cdecl ModuleMgrForUser$Init() { return hle::ModuleMgrForUser::Init(); }
extern "C" bool __cdecl ModuleMgrForUser$Fini() { return hle::ModuleMgrForUser::Fini(); }
extern "C" void __cdecl ModuleMgrForUser_977DE386(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ModuleMgrForUser::sceKernelLoadModule                              >(c); } //@hle:syscall{977DE386|ModuleMgrForUser|sceKernelLoadModule|gggg|SceUID sceKernelLoadModule(const char * path, int flags, const SceKernelLMOption * opt)}
extern "C" void __cdecl ModuleMgrForUser_710F61B5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ModuleMgrForUser::sceKernelLoadModuleMs                            >(c); } //@hle:syscall{710F61B5|ModuleMgrForUser|sceKernelLoadModuleMs|gggg|SceUID sceKernelLoadModuleMs(const char * path, int flags, SceKernelLMOption * option)}
extern "C" void __cdecl ModuleMgrForUser_F9275D98(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::ModuleMgrForUser::sceKernelLoadModuleBufferUsbWlan                 >(c); } //@hle:syscall{F9275D98|ModuleMgrForUser|sceKernelLoadModuleBufferUsbWlan|ggggg|SceUID sceKernelLoadModuleBufferUsbWlan(SceSize bufsize, void * buf, int flags, SceKernelLMOption * option)}
extern "C" void __cdecl ModuleMgrForUser_B7F46618(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ModuleMgrForUser::sceKernelLoadModuleByID                          >(c); } //@hle:syscall{B7F46618|ModuleMgrForUser|sceKernelLoadModuleByID|gggg|SceUID sceKernelLoadModuleByID(SceUID fid, int flags, const SceKernelLMOption * opt)}
extern "C" void __cdecl ModuleMgrForUser_50F0C1EC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ModuleMgrForUser::sceKernelStartModule                             >(c); } //@hle:syscall{50F0C1EC|ModuleMgrForUser|sceKernelStartModule|gggggg|int sceKernelStartModule(SceUID modid, SceSize args, void * argp, int * status, SceKernelSMOption * option)}
extern "C" void __cdecl ModuleMgrForUser_D1FF982A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::ModuleMgrForUser::sceKernelStopModule                              >(c); } //@hle:syscall{D1FF982A|ModuleMgrForUser|sceKernelStopModule|gggggg|int sceKernelStopModule(SceUID modid, SceSize args, void * argp, int * status, SceKernelSMOption * option)}
extern "C" void __cdecl ModuleMgrForUser_2E0911AA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ModuleMgrForUser::sceKernelUnloadModule                            >(c); } //@hle:syscall{2E0911AA|ModuleMgrForUser|sceKernelUnloadModule|gg|int sceKernelUnloadModule(SceUID modid)}
extern "C" void __cdecl ModuleMgrForUser_D675EBB8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ModuleMgrForUser::sceKernelSelfStopUnloadModule                    >(c); } //@hle:syscall{D675EBB8|ModuleMgrForUser|sceKernelSelfStopUnloadModule|gggg|int sceKernelSelfStopUnloadModule(int status, SceSize argsize, void * argp)}
extern "C" void __cdecl ModuleMgrForUser_CC1D3699(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::ModuleMgrForUser::sceKernelStopUnloadSelfModule                    >(c); } //@hle:syscall{CC1D3699|ModuleMgrForUser|sceKernelStopUnloadSelfModule|ggggg|int sceKernelStopUnloadSelfModule(SceSize args, void * argp, int * status, SceKernelSMOption * option)}
extern "C" void __cdecl ModuleMgrForUser_748CBED9(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::ModuleMgrForUser::sceKernelQueryModuleInfo                         >(c); } //@hle:syscall{748CBED9|ModuleMgrForUser|sceKernelQueryModuleInfo|ggg|int sceKernelQueryModuleInfo(SceUID modid, SceKernelModuleInfo * info)}
extern "C" void __cdecl ModuleMgrForUser_F0A26395(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ModuleMgrForUser::sceKernelGetModuleId                             >(c); } //@hle:syscall{F0A26395|ModuleMgrForUser|sceKernelGetModuleId|g|SceUID sceKernelGetModuleId(void)}
extern "C" void __cdecl ModuleMgrForUser_D8B73127(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ModuleMgrForUser::sceKernelGetModuleIdByAddress                    >(c); } //@hle:syscall{D8B73127|ModuleMgrForUser|sceKernelGetModuleIdByAddress|gg|SceUID sceKernelGetModuleIdByAddress(const void * base)}
extern "C" void __cdecl ModuleMgrForUser_D2FBC957(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::ModuleMgrForUser::sceKernelGetModuleGPByAddress                    >(c); } //@hle:syscall{D2FBC957|ModuleMgrForUser|sceKernelGetModuleGPByAddress|gg|SceUID sceKernelGetModuleGPByAddress(int gp)}
extern "C" void __cdecl ModuleMgrForUser_644395E2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::ModuleMgrForUser::sceKernelGetModuleIdList                         >(c); } //@hle:syscall{644395E2|ModuleMgrForUser|sceKernelGetModuleIdList|gggg|int sceKernelGetModuleIdList(SceUID * readbuf, int readbufsize, int * idcount)}
extern "C" void __cdecl ModuleMgrForUser_1196472E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ModuleMgrForUser::ModuleMgrForUser_1196472E                        >(c); } //@hle:syscall{1196472E|ModuleMgrForUser|ModuleMgrForUser_1196472E|g|??? ModuleMgrForUser_1196472E()}
extern "C" void __cdecl ModuleMgrForUser_24EC0641(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ModuleMgrForUser::ModuleMgrForUser_24EC0641                        >(c); } //@hle:syscall{24EC0641|ModuleMgrForUser|ModuleMgrForUser_24EC0641|g|??? ModuleMgrForUser_24EC0641()}
extern "C" void __cdecl ModuleMgrForUser_8F2DF740(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ModuleMgrForUser::ModuleMgrForUser_8F2DF740                        >(c); } //@hle:syscall{8F2DF740|ModuleMgrForUser|ModuleMgrForUser_8F2DF740|g|??? ModuleMgrForUser_8F2DF740()}
extern "C" void __cdecl ModuleMgrForUser_E4C4211C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ModuleMgrForUser::ModuleMgrForUser_E4C4211C                        >(c); } //@hle:syscall{E4C4211C|ModuleMgrForUser|ModuleMgrForUser_E4C4211C|g|??? ModuleMgrForUser_E4C4211C()}
extern "C" void __cdecl ModuleMgrForUser_F2D8D1B4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ModuleMgrForUser::ModuleMgrForUser_F2D8D1B4                        >(c); } //@hle:syscall{F2D8D1B4|ModuleMgrForUser|ModuleMgrForUser_F2D8D1B4|g|??? ModuleMgrForUser_F2D8D1B4()}
extern "C" void __cdecl ModuleMgrForUser_FBE27467(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ModuleMgrForUser::ModuleMgrForUser_FBE27467                        >(c); } //@hle:syscall{FBE27467|ModuleMgrForUser|ModuleMgrForUser_FBE27467|g|??? ModuleMgrForUser_FBE27467()}
extern "C" void __cdecl ModuleMgrForUser_FEF27DC1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::ModuleMgrForUser::ModuleMgrForUser_FEF27DC1                        >(c); } //@hle:syscall{FEF27DC1|ModuleMgrForUser|ModuleMgrForUser_FEF27DC1|g|??? ModuleMgrForUser_FEF27DC1()}