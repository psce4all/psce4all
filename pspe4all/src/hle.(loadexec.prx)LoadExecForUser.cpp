//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(loadexec.prx)LoadExecForUser.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace LoadExecForUser //@hle:library-start{LoadExecForUser|sceLoadExec|loadexec.prx}
    {

        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }
        //@hle:function{BD2F1094|LoadExecForUser|sceKernelLoadExec|ggg|int sceKernelLoadExec(const char * file, const SceKernelLoadExecParam * param)}
        int  sceKernelLoadExec(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{05572A5F|LoadExecForUser|sceKernelExitGame|g|int sceKernelExitGame(void)}
        int  sceKernelExitGame()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2AC9954B|LoadExecForUser|sceKernelExitGameWithStatus|gg|int sceKernelExitGameWithStatus(int status)}
        int  sceKernelExitGameWithStatus(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4AC57943|LoadExecForUser|sceKernelRegisterExitCallback|gg|int sceKernelRegisterExitCallback(SceUID cbid)}
        int  sceKernelRegisterExitCallback(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{362A956B|LoadExecForUser|LoadExecForUser_362A956B|g|??? LoadExecForUser_362A956B()}
        int  LoadExecForUser_362A956B()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8ADA38D3|LoadExecForUser|LoadExecForUser_8ADA38D3|g|??? LoadExecForUser_8ADA38D3()}
        int  LoadExecForUser_8ADA38D3()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D1FB50DC|LoadExecForUser|LoadExecForUser_D1FB50DC|g|??? LoadExecForUser_D1FB50DC()}
        int  LoadExecForUser_D1FB50DC()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{LoadExecForUser|sceLoadExec|loadexec.prx}
}

extern "C" bool __cdecl LoadExecForUser$Init() { return hle::LoadExecForUser::Init(); }
extern "C" bool __cdecl LoadExecForUser$Fini() { return hle::LoadExecForUser::Fini(); }
extern "C" void __cdecl LoadExecForUser_BD2F1094(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::LoadExecForUser::sceKernelLoadExec                                >(c); } //@hle:syscall{BD2F1094|LoadExecForUser|sceKernelLoadExec|ggg|int sceKernelLoadExec(const char * file, const SceKernelLoadExecParam * param)}
extern "C" void __cdecl LoadExecForUser_05572A5F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::LoadExecForUser::sceKernelExitGame                                >(c); } //@hle:syscall{05572A5F|LoadExecForUser|sceKernelExitGame|g|int sceKernelExitGame(void)}
extern "C" void __cdecl LoadExecForUser_2AC9954B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::LoadExecForUser::sceKernelExitGameWithStatus                      >(c); } //@hle:syscall{2AC9954B|LoadExecForUser|sceKernelExitGameWithStatus|gg|int sceKernelExitGameWithStatus(int status)}
extern "C" void __cdecl LoadExecForUser_4AC57943(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::LoadExecForUser::sceKernelRegisterExitCallback                    >(c); } //@hle:syscall{4AC57943|LoadExecForUser|sceKernelRegisterExitCallback|gg|int sceKernelRegisterExitCallback(SceUID cbid)}
extern "C" void __cdecl LoadExecForUser_362A956B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::LoadExecForUser::LoadExecForUser_362A956B                         >(c); } //@hle:syscall{362A956B|LoadExecForUser|LoadExecForUser_362A956B|g|??? LoadExecForUser_362A956B()}
extern "C" void __cdecl LoadExecForUser_8ADA38D3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::LoadExecForUser::LoadExecForUser_8ADA38D3                         >(c); } //@hle:syscall{8ADA38D3|LoadExecForUser|LoadExecForUser_8ADA38D3|g|??? LoadExecForUser_8ADA38D3()}
extern "C" void __cdecl LoadExecForUser_D1FB50DC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::LoadExecForUser::LoadExecForUser_D1FB50DC                         >(c); } //@hle:syscall{D1FB50DC|LoadExecForUser|LoadExecForUser_D1FB50DC|g|??? LoadExecForUser_D1FB50DC()}