//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_hpremote_prx_sceHprm_h__
#define hle_hpremote_prx_sceHprm_h__

namespace hle
{
    namespace sceHprm //@hle:library-start{sceHprm|sceHP_Remote_Driver|hpremote.prx}
    {
        //@hle:function{1910B327|sceHprm|sceHprmPeekCurrentKey|gg|int sceHprmPeekCurrentKey(u32 * key)}
        extern int  sceHprmPeekCurrentKey(u32 $a0);
        //@hle:function{208DB1BD|sceHprm|sceHprmIsRemoteExist|g|int sceHprmIsRemoteExist(void)}
        extern int  sceHprmIsRemoteExist();
        //@hle:function{219C58F1|sceHprm|sceHprmIsMicrophoneExist|g|int sceHprmIsMicrophoneExist(void)}
        extern int  sceHprmIsMicrophoneExist();
        //@hle:function{2BCEC83E|sceHprm|sceHprmPeekLatch|gg|int sceHprmPeekLatch(u32 * latch)}
        extern int  sceHprmPeekLatch(u32 $a0);
        //@hle:function{3953DE6B|sceHprm|sceHprm_3953DE6B|g|??? sceHprm_3953DE6B()}
        extern int  sceHprm_3953DE6B();
        //@hle:function{396FD885|sceHprm|sceHprm_396FD885|g|??? sceHprm_396FD885()}
        extern int  sceHprm_396FD885();
        //@hle:function{40D2F9F0|sceHprm|sceHprmReadLatch|gg|int sceHprmReadLatch(u32 * latch)}
        extern int  sceHprmReadLatch(u32 $a0);
        //@hle:function{444ED0B7|sceHprm|sceHprmUnregitserCallback|g|??? sceHprmUnregitserCallback()}
        extern int  sceHprmUnregitserCallback();
        //@hle:function{71B5FB67|sceHprm|sceHprmGetHpDetect|g|??? sceHprmGetHpDetect()}
        extern int  sceHprmGetHpDetect();
        //@hle:function{7E69EDA4|sceHprm|sceHprmIsHeadphoneExist|g|int sceHprmIsHeadphoneExist(void)}
        extern int  sceHprmIsHeadphoneExist();
        //@hle:function{C7154136|sceHprm|sceHprmRegisterCallback|g|??? sceHprmRegisterCallback()}
        extern int  sceHprmRegisterCallback();
        //@hle:function{FD7DE6CD|sceHprm|sceHprm_FD7DE6CD|g|??? sceHprm_FD7DE6CD()}
        extern int  sceHprm_FD7DE6CD();
    } //@hle:library-end{sceHprm|sceHP_Remote_Driver|hpremote.prx}
}
#endif