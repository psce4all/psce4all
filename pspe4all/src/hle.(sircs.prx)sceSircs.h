//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_sircs_prx_sceSircs_h__
#define hle_sircs_prx_sceSircs_h__

namespace hle
{
    namespace sceSircs //@hle:library-start{sceSircs|sceSIRCS_IrDA_Driver|sircs.prx}
    {
        //@hle:function{71EEF62D|sceSircs|sceSircsSend|ggg|int sceSircsSend(struct sircs_data * sd, int count)}
        extern int  sceSircsSend(u32 $a0, u32 $a1);
        //@hle:function{83381633|sceSircs|sceSircsReceive|g|??? sceSircsReceive()}
        extern int  sceSircsReceive();
    } //@hle:library-end{sceSircs|sceSIRCS_IrDA_Driver|sircs.prx}
}
#endif