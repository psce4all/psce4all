//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(iofilemgr.prx)StdioForUser.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace StdioForUser //@hle:library-start{StdioForUser|sceIOFileManager|iofilemgr.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{A6BAB2E9|StdioForUser|sceKernelStdout|g|SceUID sceKernelStdout(void)}
        int  sceKernelStdout()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F78BA90A|StdioForUser|sceKernelStderr|g|SceUID sceKernelStderr(void)}
        int  sceKernelStderr()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{172D316E|StdioForUser|sceKernelStdin|g|SceUID sceKernelStdin(void)}
        int  sceKernelStdin()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{924ABA61|StdioForUser|sceKernelStdioOpen|g|??? sceKernelStdioOpen()}
        int  sceKernelStdioOpen()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9D061C19|StdioForUser|sceKernelStdioClose|g|??? sceKernelStdioClose()}
        int  sceKernelStdioClose()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0CBB0571|StdioForUser|sceKernelStdioLseek|g|??? sceKernelStdioLseek()}
        int  sceKernelStdioLseek()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3054D478|StdioForUser|sceKernelStdioRead|g|??? sceKernelStdioRead()}
        int  sceKernelStdioRead()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A3B931DB|StdioForUser|sceKernelStdioWrite|g|??? sceKernelStdioWrite()}
        int  sceKernelStdioWrite()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A46785C9|StdioForUser|sceKernelStdioSendChar|g|??? sceKernelStdioSendChar()}
        int  sceKernelStdioSendChar()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{432D8F5C|StdioForUser|sceKernelRegisterStdoutPipe|g|??? sceKernelRegisterStdoutPipe()}
        int  sceKernelRegisterStdoutPipe()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6F797E03|StdioForUser|sceKernelRegisterStderrPipe|g|??? sceKernelRegisterStderrPipe()}
        int  sceKernelRegisterStderrPipe()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{StdioForUser|sceIOFileManager|iofilemgr.prx}
}

extern "C" bool __cdecl StdioForUser$Init() { return hle::StdioForUser::Init(); }
extern "C" bool __cdecl StdioForUser$Fini() { return hle::StdioForUser::Fini(); }
extern "C" void __cdecl StdioForUser_A6BAB2E9(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelStdout                                  >(c); } //@hle:syscall{A6BAB2E9|StdioForUser|sceKernelStdout|g|SceUID sceKernelStdout(void)}
extern "C" void __cdecl StdioForUser_F78BA90A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelStderr                                  >(c); } //@hle:syscall{F78BA90A|StdioForUser|sceKernelStderr|g|SceUID sceKernelStderr(void)}
extern "C" void __cdecl StdioForUser_172D316E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelStdin                                   >(c); } //@hle:syscall{172D316E|StdioForUser|sceKernelStdin|g|SceUID sceKernelStdin(void)}
extern "C" void __cdecl StdioForUser_924ABA61(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelStdioOpen                               >(c); } //@hle:syscall{924ABA61|StdioForUser|sceKernelStdioOpen|g|??? sceKernelStdioOpen()}
extern "C" void __cdecl StdioForUser_9D061C19(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelStdioClose                              >(c); } //@hle:syscall{9D061C19|StdioForUser|sceKernelStdioClose|g|??? sceKernelStdioClose()}
extern "C" void __cdecl StdioForUser_0CBB0571(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelStdioLseek                              >(c); } //@hle:syscall{0CBB0571|StdioForUser|sceKernelStdioLseek|g|??? sceKernelStdioLseek()}
extern "C" void __cdecl StdioForUser_3054D478(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelStdioRead                               >(c); } //@hle:syscall{3054D478|StdioForUser|sceKernelStdioRead|g|??? sceKernelStdioRead()}
extern "C" void __cdecl StdioForUser_A3B931DB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelStdioWrite                              >(c); } //@hle:syscall{A3B931DB|StdioForUser|sceKernelStdioWrite|g|??? sceKernelStdioWrite()}
extern "C" void __cdecl StdioForUser_A46785C9(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelStdioSendChar                           >(c); } //@hle:syscall{A46785C9|StdioForUser|sceKernelStdioSendChar|g|??? sceKernelStdioSendChar()}
extern "C" void __cdecl StdioForUser_432D8F5C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelRegisterStdoutPipe                      >(c); } //@hle:syscall{432D8F5C|StdioForUser|sceKernelRegisterStdoutPipe|g|??? sceKernelRegisterStdoutPipe()}
extern "C" void __cdecl StdioForUser_6F797E03(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::StdioForUser::sceKernelRegisterStderrPipe                      >(c); } //@hle:syscall{6F797E03|StdioForUser|sceKernelRegisterStderrPipe|g|??? sceKernelRegisterStderrPipe()}