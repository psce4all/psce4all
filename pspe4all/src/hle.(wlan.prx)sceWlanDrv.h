//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_wlan_prx_sceWlanDrv_h__
#define hle_wlan_prx_sceWlanDrv_h__

namespace hle
{
    namespace sceWlanDrv //@hle:library-start{sceWlanDrv|sceWlan_Driver|wlan.prx}
    {
        //@hle:function{0C622081|sceWlanDrv|sceWlanGetEtherAddr|gg|int sceWlanGetEtherAddr(char * etherAddr)}
        extern int  sceWlanGetEtherAddr(u32 $a0);
        //@hle:function{93440B11|sceWlanDrv|sceWlanDevIsPowerOn|g|int sceWlanDevIsPowerOn(void)}
        extern int  sceWlanDevIsPowerOn();
        //@hle:function{D7763699|sceWlanDrv|sceWlanGetSwitchState|g|int sceWlanGetSwitchState(void)}
        extern int  sceWlanGetSwitchState();
    } //@hle:library-end{sceWlanDrv|sceWlan_Driver|wlan.prx}
}
#endif