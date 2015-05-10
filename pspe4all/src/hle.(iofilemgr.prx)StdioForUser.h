//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_iofilemgr_prx_StdioForUser_h__
#define hle_iofilemgr_prx_StdioForUser_h__

namespace hle
{
    namespace StdioForUser //@hle:library-start{StdioForUser|sceIOFileManager|iofilemgr.prx}
    {
        //@hle:function{A6BAB2E9|StdioForUser|sceKernelStdout|g|SceUID sceKernelStdout(void)}
        extern int  sceKernelStdout();
        //@hle:function{F78BA90A|StdioForUser|sceKernelStderr|g|SceUID sceKernelStderr(void)}
        extern int  sceKernelStderr();
        //@hle:function{172D316E|StdioForUser|sceKernelStdin|g|SceUID sceKernelStdin(void)}
        extern int  sceKernelStdin();
        //@hle:function{924ABA61|StdioForUser|sceKernelStdioOpen|g|??? sceKernelStdioOpen()}
        extern int  sceKernelStdioOpen();
        //@hle:function{9D061C19|StdioForUser|sceKernelStdioClose|g|??? sceKernelStdioClose()}
        extern int  sceKernelStdioClose();
        //@hle:function{0CBB0571|StdioForUser|sceKernelStdioLseek|g|??? sceKernelStdioLseek()}
        extern int  sceKernelStdioLseek();
        //@hle:function{3054D478|StdioForUser|sceKernelStdioRead|g|??? sceKernelStdioRead()}
        extern int  sceKernelStdioRead();
        //@hle:function{A3B931DB|StdioForUser|sceKernelStdioWrite|g|??? sceKernelStdioWrite()}
        extern int  sceKernelStdioWrite();
        //@hle:function{A46785C9|StdioForUser|sceKernelStdioSendChar|g|??? sceKernelStdioSendChar()}
        extern int  sceKernelStdioSendChar();
        //@hle:function{432D8F5C|StdioForUser|sceKernelRegisterStdoutPipe|g|??? sceKernelRegisterStdoutPipe()}
        extern int  sceKernelRegisterStdoutPipe();
        //@hle:function{6F797E03|StdioForUser|sceKernelRegisterStderrPipe|g|??? sceKernelRegisterStderrPipe()}
        extern int  sceKernelRegisterStderrPipe();
    } //@hle:library-end{StdioForUser|sceIOFileManager|iofilemgr.prx}
}
#endif