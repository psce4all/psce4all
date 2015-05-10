//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_loadexec_prx_LoadExecForUser_h__
#define hle_loadexec_prx_LoadExecForUser_h__

namespace hle
{
    namespace LoadExecForUser //@hle:library-start{LoadExecForUser|sceLoadExec|loadexec.prx}
    {
        //@hle:function{BD2F1094|LoadExecForUser|sceKernelLoadExec|ggg|int sceKernelLoadExec(const char * file, const SceKernelLoadExecParam * param)}
        extern int  sceKernelLoadExec(u32 $a0, u32 $a1);
        //@hle:function{05572A5F|LoadExecForUser|sceKernelExitGame|g|int sceKernelExitGame(void)}
        extern int  sceKernelExitGame();
        //@hle:function{2AC9954B|LoadExecForUser|sceKernelExitGameWithStatus|gg|int sceKernelExitGameWithStatus(int status)}
        extern int  sceKernelExitGameWithStatus(u32 $a0);
        //@hle:function{4AC57943|LoadExecForUser|sceKernelRegisterExitCallback|gg|int sceKernelRegisterExitCallback(SceUID cbid)}
        extern int  sceKernelRegisterExitCallback(u32 $a0);
        //@hle:function{362A956B|LoadExecForUser|LoadExecForUser_362A956B|g|??? LoadExecForUser_362A956B()}
        extern int  LoadExecForUser_362A956B();
        //@hle:function{8ADA38D3|LoadExecForUser|LoadExecForUser_8ADA38D3|g|??? LoadExecForUser_8ADA38D3()}
        extern int  LoadExecForUser_8ADA38D3();
        //@hle:function{D1FB50DC|LoadExecForUser|LoadExecForUser_D1FB50DC|g|??? LoadExecForUser_D1FB50DC()}
        extern int  LoadExecForUser_D1FB50DC();
    } //@hle:library-end{LoadExecForUser|sceLoadExec|loadexec.prx}
}
#endif