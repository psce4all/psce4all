//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_utility_prx_sceUtility_h__
#define hle_utility_prx_sceUtility_h__

namespace hle
{
    namespace sceUtility //@hle:library-start{sceUtility|sceUtility_Driver|utility.prx}
    {
        //@hle:function{0251B134|sceUtility|sceUtility_0251B134|g|??? sceUtility_0251B134()}
        extern int  sceUtility_0251B134();
        //@hle:function{05AFB9E4|sceUtility|sceUtilityHtmlViewerUpdate|g|??? sceUtilityHtmlViewerUpdate()}
        extern int  sceUtilityHtmlViewerUpdate();
        //@hle:function{06A48659|sceUtility|sceUtility_06A48659|g|??? sceUtility_06A48659()}
        extern int  sceUtility_06A48659();
        //@hle:function{0D5BC6D2|sceUtility|sceUtilityLoadUsbModule|g|??? sceUtilityLoadUsbModule()}
        extern int  sceUtilityLoadUsbModule();
        //@hle:function{0F3EEAAC|sceUtility|sceUtility_0F3EEAAC|g|??? sceUtility_0F3EEAAC()}
        extern int  sceUtility_0F3EEAAC();
        //@hle:function{1281DA8E|sceUtility|sceUtilityInstallInitStart|g|??? sceUtilityInstallInitStart()}
        extern int  sceUtilityInstallInitStart();
        //@hle:function{147F7C85|sceUtility|sceUtility_147F7C85|g|??? sceUtility_147F7C85()}
        extern int  sceUtility_147F7C85();
        //@hle:function{149A7895|sceUtility|sceUtility_149A7895|g|??? sceUtility_149A7895()}
        extern int  sceUtility_149A7895();
        //@hle:function{1579A159|sceUtility|sceUtilityLoadNetModule|gg|int sceUtilityLoadNetModule(int module)}
        extern int  sceUtilityLoadNetModule(u32 $a0);
        //@hle:function{16A1A8D8|sceUtility|sceUtility_16A1A8D8|g|??? sceUtility_16A1A8D8()}
        extern int  sceUtility_16A1A8D8();
        //@hle:function{16D02AF0|sceUtility|sceUtility_16D02AF0|g|??? sceUtility_16D02AF0()}
        extern int  sceUtility_16D02AF0();
        //@hle:function{28D35634|sceUtility|sceUtility_28D35634|g|??? sceUtility_28D35634()}
        extern int  sceUtility_28D35634();
        //@hle:function{2995D020|sceUtility|sceUtility_2995D020|g|??? sceUtility_2995D020()}
        extern int  sceUtility_2995D020();
        //@hle:function{2A2B3DE0|sceUtility|sceUtilityLoadModule|g|??? sceUtilityLoadModule()}
        extern int  sceUtilityLoadModule();
        //@hle:function{2AD8E239|sceUtility|sceUtilityMsgDialogInitStart|gg|int sceUtilityMsgDialogInitStart(SceUtilityMsgDialogParams * params)}
        extern int  sceUtilityMsgDialogInitStart(u32 $a0);
        //@hle:function{2B96173B|sceUtility|sceUtility_2B96173B|g|??? sceUtility_2B96173B()}
        extern int  sceUtility_2B96173B();
        //@hle:function{34B78343|sceUtility|sceUtilityGetSystemParamString|gggg|int sceUtilityGetSystemParamString(int id, char * str, int len)}
        extern int  sceUtilityGetSystemParamString(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{3AAD51DC|sceUtility|sceUtility_3AAD51DC|g|??? sceUtility_3AAD51DC()}
        extern int  sceUtility_3AAD51DC();
        //@hle:function{3AD50AE7|sceUtility|sceNetplayDialogInitStart|g|??? sceNetplayDialogInitStart()}
        extern int  sceNetplayDialogInitStart();
        //@hle:function{3DFAEBA9|sceUtility|sceUtilityOskShutdownStart|g|int sceUtilityOskShutdownStart(void)}
        extern int  sceUtilityOskShutdownStart();
        //@hle:function{417BED54|sceUtility|sceNetplayDialogUpdate|g|??? sceNetplayDialogUpdate()}
        extern int  sceNetplayDialogUpdate();
        //@hle:function{41E30674|sceUtility|sceUtilitySetSystemParamString|ggg|int sceUtilitySetSystemParamString(int id, const char * str)}
        extern int  sceUtilitySetSystemParamString(u32 $a0, u32 $a1);
        //@hle:function{42071A83|sceUtility|sceUtility_42071A83|g|??? sceUtility_42071A83()}
        extern int  sceUtility_42071A83();
        //@hle:function{434D4B3A|sceUtility|sceUtilityGetNetParam|gggg|int sceUtilityGetNetParam(int conf, int param, netData * data)}
        extern int  sceUtilityGetNetParam(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{45C18506|sceUtility|sceUtilitySetSystemParamInt|ggg|int sceUtilitySetSystemParamInt(int id, int value)}
        extern int  sceUtilitySetSystemParamInt(u32 $a0, u32 $a1);
        //@hle:function{4928BD96|sceUtility|sceUtilityMsgDialogAbort|g|??? sceUtilityMsgDialogAbort()}
        extern int  sceUtilityMsgDialogAbort();
        //@hle:function{4A833BA4|sceUtility|sceUtility_4A833BA4|g|??? sceUtility_4A833BA4()}
        extern int  sceUtility_4A833BA4();
        //@hle:function{4B0A8FE5|sceUtility|sceUtility_4B0A8FE5|g|??? sceUtility_4B0A8FE5()}
        extern int  sceUtility_4B0A8FE5();
        //@hle:function{4B85C861|sceUtility|sceUtilityOskUpdate|gg|int sceUtilityOskUpdate(int n)}
        extern int  sceUtilityOskUpdate(u32 $a0);
        //@hle:function{4DB1E739|sceUtility|sceUtilityNetconfInitStart|gg|int sceUtilityNetconfInitStart(pspUtilityNetconfData * data)}
        extern int  sceUtilityNetconfInitStart(u32 $a0);
        //@hle:function{4FED24D8|sceUtility|sceUtilityGetNetParamLatestID|g|??? sceUtilityGetNetParamLatestID()}
        extern int  sceUtilityGetNetParamLatestID();
        //@hle:function{50C4CD57|sceUtility|sceUtilitySavedataInitStart|gg|int sceUtilitySavedataInitStart(SceUtilitySavedataParam * params)}
        extern int  sceUtilitySavedataInitStart(u32 $a0);
        //@hle:function{54A5C62F|sceUtility|sceUtility_54A5C62F|g|??? sceUtility_54A5C62F()}
        extern int  sceUtility_54A5C62F();
        //@hle:function{5EEE6548|sceUtility|sceUtilityCheckNetParam|gg|int sceUtilityCheckNetParam(int id)}
        extern int  sceUtilityCheckNetParam(u32 $a0);
        //@hle:function{5EF1C24A|sceUtility|sceUtilityInstallShutdownStart|g|??? sceUtilityInstallShutdownStart()}
        extern int  sceUtilityInstallShutdownStart();
        //@hle:function{6332AA39|sceUtility|sceUtilityNetconfGetStatus|g|int sceUtilityNetconfGetStatus(void)}
        extern int  sceUtilityNetconfGetStatus();
        //@hle:function{64D50C56|sceUtility|sceUtilityUnloadNetModule|gg|int sceUtilityUnloadNetModule(int module)}
        extern int  sceUtilityUnloadNetModule(u32 $a0);
        //@hle:function{67AF3428|sceUtility|sceUtilityMsgDialogShutdownStart|0|void sceUtilityMsgDialogShutdownStart(void)}
        extern void sceUtilityMsgDialogShutdownStart();
        //@hle:function{6F56F9CF|sceUtility|sceUtility_6F56F9CF|g|??? sceUtility_6F56F9CF()}
        extern int  sceUtility_6F56F9CF();
        //@hle:function{70267ADF|sceUtility|sceUtility_70267ADF|g|??? sceUtility_70267ADF()}
        extern int  sceUtility_70267ADF();
        //@hle:function{7853182D|sceUtility|sceUtilityGameSharingUpdate|g|??? sceUtilityGameSharingUpdate()}
        extern int  sceUtilityGameSharingUpdate();
        //@hle:function{81C44706|sceUtility|sceUtility_81C44706|g|??? sceUtility_81C44706()}
        extern int  sceUtility_81C44706();
        //@hle:function{8326AB05|sceUtility|sceUtility_8326AB05|g|??? sceUtility_8326AB05()}
        extern int  sceUtility_8326AB05();
        //@hle:function{86A03A27|sceUtility|sceUtility_86A03A27|g|??? sceUtility_86A03A27()}
        extern int  sceUtility_86A03A27();
        //@hle:function{86ABDB1B|sceUtility|sceUtility_86ABDB1B|g|??? sceUtility_86ABDB1B()}
        extern int  sceUtility_86ABDB1B();
        //@hle:function{8874DBE0|sceUtility|sceUtilitySavedataGetStatus|g|int sceUtilitySavedataGetStatus(void)}
        extern int  sceUtilitySavedataGetStatus();
        //@hle:function{88BC7406|sceUtility|sceUtility_88BC7406|g|??? sceUtility_88BC7406()}
        extern int  sceUtility_88BC7406();
        //@hle:function{89317C8F|sceUtility|sceUtility_89317C8F|g|??? sceUtility_89317C8F()}
        extern int  sceUtility_89317C8F();
        //@hle:function{91E70E35|sceUtility|sceUtilityNetconfUpdate|gg|int sceUtilityNetconfUpdate(int unknown)}
        extern int  sceUtilityNetconfUpdate(u32 $a0);
        //@hle:function{943CBA46|sceUtility|sceUtility_943CBA46|g|??? sceUtility_943CBA46()}
        extern int  sceUtility_943CBA46();
        //@hle:function{946963F3|sceUtility|sceUtilityGameSharingGetStatus|g|??? sceUtilityGameSharingGetStatus()}
        extern int  sceUtilityGameSharingGetStatus();
        //@hle:function{95FC253B|sceUtility|sceUtilityMsgDialogUpdate|0g|void sceUtilityMsgDialogUpdate(int n)}
        extern void sceUtilityMsgDialogUpdate(u32 $a0);
        //@hle:function{9790B33C|sceUtility|sceUtilitySavedataShutdownStart|g|int sceUtilitySavedataShutdownStart(void)}
        extern int  sceUtilitySavedataShutdownStart();
        //@hle:function{9A1C91D7|sceUtility|sceUtilityMsgDialogGetStatus|g|int sceUtilityMsgDialogGetStatus(void)}
        extern int  sceUtilityMsgDialogGetStatus();
        //@hle:function{A03D29BA|sceUtility|sceUtilityInstallUpdate|g|??? sceUtilityInstallUpdate()}
        extern int  sceUtilityInstallUpdate();
        //@hle:function{A084E056|sceUtility|sceUtility_A084E056|g|??? sceUtility_A084E056()}
        extern int  sceUtility_A084E056();
        //@hle:function{A50E5B30|sceUtility|sceUtility_A50E5B30|g|??? sceUtility_A50E5B30()}
        extern int  sceUtility_A50E5B30();
        //@hle:function{A5DA2406|sceUtility|sceUtilityGetSystemParamInt|ggg|int sceUtilityGetSystemParamInt(int id, int * value)}
        extern int  sceUtilityGetSystemParamInt(u32 $a0, u32 $a1);
        //@hle:function{AB083EA9|sceUtility|sceUtility_AB083EA9|g|??? sceUtility_AB083EA9()}
        extern int  sceUtility_AB083EA9();
        //@hle:function{B0FB7FF5|sceUtility|sceUtility_B0FB7FF5|g|??? sceUtility_B0FB7FF5()}
        extern int  sceUtility_B0FB7FF5();
        //@hle:function{B62A4061|sceUtility|sceUtility_B62A4061|g|??? sceUtility_B62A4061()}
        extern int  sceUtility_B62A4061();
        //@hle:function{B6CEE597|sceUtility|sceNetplayDialogGetStatus|g|??? sceNetplayDialogGetStatus()}
        extern int  sceNetplayDialogGetStatus();
        //@hle:function{B8592D5F|sceUtility|sceUtility_B8592D5F|g|??? sceUtility_B8592D5F()}
        extern int  sceUtility_B8592D5F();
        //@hle:function{BC6B6296|sceUtility|sceNetplayDialogShutdownStart|g|??? sceNetplayDialogShutdownStart()}
        extern int  sceNetplayDialogShutdownStart();
        //@hle:function{BDA7D894|sceUtility|sceUtilityHtmlViewerGetStatus|g|??? sceUtilityHtmlViewerGetStatus()}
        extern int  sceUtilityHtmlViewerGetStatus();
        //@hle:function{C4700FA3|sceUtility|sceUtilityInstallGetStatus|g|??? sceUtilityInstallGetStatus()}
        extern int  sceUtilityInstallGetStatus();
        //@hle:function{C492F751|sceUtility|sceUtilityGameSharingInitStart|g|??? sceUtilityGameSharingInitStart()}
        extern int  sceUtilityGameSharingInitStart();
        //@hle:function{C629AF26|sceUtility|sceUtilityLoadAvModule|g|??? sceUtilityLoadAvModule()}
        extern int  sceUtilityLoadAvModule();
        //@hle:function{CDC3AA41|sceUtility|sceUtilityHtmlViewerInitStart|g|??? sceUtilityHtmlViewerInitStart()}
        extern int  sceUtilityHtmlViewerInitStart();
        //@hle:function{D17A0573|sceUtility|sceUtility_D17A0573|g|??? sceUtility_D17A0573()}
        extern int  sceUtility_D17A0573();
        //@hle:function{D4B95FFB|sceUtility|sceUtilitySavedataUpdate|0g|void sceUtilitySavedataUpdate(int unknown)}
        extern void sceUtilitySavedataUpdate(u32 $a0);
        //@hle:function{D81957B7|sceUtility|sceUtility_D81957B7|g|??? sceUtility_D81957B7()}
        extern int  sceUtility_D81957B7();
        //@hle:function{D852CDCE|sceUtility|sceUtility_D852CDCE|g|??? sceUtility_D852CDCE()}
        extern int  sceUtility_D852CDCE();
        //@hle:function{DA97F1AA|sceUtility|sceUtility_DA97F1AA|g|??? sceUtility_DA97F1AA()}
        extern int  sceUtility_DA97F1AA();
        //@hle:function{DDE5389D|sceUtility|sceUtility_DDE5389D|g|??? sceUtility_DDE5389D()}
        extern int  sceUtility_DDE5389D();
        //@hle:function{E19C97D6|sceUtility|sceUtility_E19C97D6|g|??? sceUtility_E19C97D6()}
        extern int  sceUtility_E19C97D6();
        //@hle:function{E49BFE92|sceUtility|sceUtilityUnloadModule|g|??? sceUtilityUnloadModule()}
        extern int  sceUtilityUnloadModule();
        //@hle:function{E7B778D8|sceUtility|sceUtility_E7B778D8|g|??? sceUtility_E7B778D8()}
        extern int  sceUtility_E7B778D8();
        //@hle:function{ECE1D3E5|sceUtility|sceUtility_ECE1D3E5|g|??? sceUtility_ECE1D3E5()}
        extern int  sceUtility_ECE1D3E5();
        //@hle:function{ED0FAD38|sceUtility|sceUtility_ED0FAD38|g|??? sceUtility_ED0FAD38()}
        extern int  sceUtility_ED0FAD38();
        //@hle:function{EF3582B2|sceUtility|sceUtility_EF3582B2|g|??? sceUtility_EF3582B2()}
        extern int  sceUtility_EF3582B2();
        //@hle:function{EFC6F80F|sceUtility|sceUtilityGameSharingShutdownStart|g|??? sceUtilityGameSharingShutdownStart()}
        extern int  sceUtilityGameSharingShutdownStart();
        //@hle:function{F3F76017|sceUtility|sceUtilityOskGetStatus|g|int sceUtilityOskGetStatus(void)}
        extern int  sceUtilityOskGetStatus();
        //@hle:function{F3FBC572|sceUtility|sceUtility_F3FBC572|g|??? sceUtility_F3FBC572()}
        extern int  sceUtility_F3FBC572();
        //@hle:function{F5CE1134|sceUtility|sceUtilityHtmlViewerShutdownStart|g|??? sceUtilityHtmlViewerShutdownStart()}
        extern int  sceUtilityHtmlViewerShutdownStart();
        //@hle:function{F6269B82|sceUtility|sceUtilityOskInitStart|gg|int sceUtilityOskInitStart(SceUtilityOskParams * params)}
        extern int  sceUtilityOskInitStart(u32 $a0);
        //@hle:function{F64910F0|sceUtility|sceUtilityUnloadUsbModule|g|??? sceUtilityUnloadUsbModule()}
        extern int  sceUtilityUnloadUsbModule();
        //@hle:function{F7D8D092|sceUtility|sceUtilityUnloadAvModule|g|??? sceUtilityUnloadAvModule()}
        extern int  sceUtilityUnloadAvModule();
        //@hle:function{F88155F6|sceUtility|sceUtilityNetconfShutdownStart|g|int sceUtilityNetconfShutdownStart(void)}
        extern int  sceUtilityNetconfShutdownStart();
        //@hle:function{F9E0008C|sceUtility|sceUtility_F9E0008C|g|??? sceUtility_F9E0008C()}
        extern int  sceUtility_F9E0008C();
    } //@hle:library-end{sceUtility|sceUtility_Driver|utility.prx}
}
#endif