//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_registry_prx_sceReg_h__
#define hle_registry_prx_sceReg_h__

namespace hle
{
    namespace sceReg //@hle:library-start{sceReg|sceRegistry_Service|registry.prx}
    {
        //@hle:function{0CAE832B|sceReg|sceRegCloseCategory|gg|int sceRegCloseCategory(REGHANDLE hd)}
        extern int  sceRegCloseCategory(u32 $a0);
        //@hle:function{0D69BF40|sceReg|sceRegFlushCategory|gg|int sceRegFlushCategory(REGHANDLE hd)}
        extern int  sceRegFlushCategory(u32 $a0);
        //@hle:function{17768E14|sceReg|sceRegSetKeyValue|ggggg|int sceRegSetKeyValue(REGHANDLE hd, const char * name, const void * buf, SceSize size)}
        extern int  sceRegSetKeyValue(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{1D8A762E|sceReg|sceRegOpenCategory|ggggg|int sceRegOpenCategory(REGHANDLE h, const char * name, int mode, REGHANDLE * hd)}
        extern int  sceRegOpenCategory(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{28A8E98A|sceReg|sceRegGetKeyValue|ggggg|int sceRegGetKeyValue(REGHANDLE hd, REGHANDLE hk, void * buf, SceSize size)}
        extern int  sceRegGetKeyValue(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{2C0DB9DD|sceReg|sceRegGetKeysNum|ggg|int sceRegGetKeysNum(REGHANDLE hd, int * num)}
        extern int  sceRegGetKeysNum(u32 $a0, u32 $a1);
        //@hle:function{2D211135|sceReg|sceRegGetKeys|gggg|int sceRegGetKeys(REGHANDLE hd, char * buf, int num)}
        extern int  sceRegGetKeys(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{30BE0259|sceReg|sceRegGetKeyValueByName|ggggg|int sceRegGetKeyValueByName(REGHANDLE hd, const char * name, void * buf, SceSize size)}
        extern int  sceRegGetKeyValueByName(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{3615BC87|sceReg|sceRegRemoveKey|g|??? sceRegRemoveKey()}
        extern int  sceRegRemoveKey();
        //@hle:function{39461B4D|sceReg|sceRegFlushRegistry|gg|int sceRegFlushRegistry(REGHANDLE h)}
        extern int  sceRegFlushRegistry(u32 $a0);
        //@hle:function{4CA16893|sceReg|sceRegRemoveCategory|ggg|int sceRegRemoveCategory(REGHANDLE h, const char * name)}
        extern int  sceRegRemoveCategory(u32 $a0, u32 $a1);
        //@hle:function{57641A81|sceReg|sceRegCreateKey|ggggg|int sceRegCreateKey(REGHANDLE hd, const char * name, int type, SceSize size)}
        extern int  sceRegCreateKey(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{835ECE6F|sceReg|sceReg_835ECE6F|g|??? sceReg_835ECE6F()}
        extern int  sceReg_835ECE6F();
        //@hle:function{92E41280|sceReg|sceRegOpenRegistry|gggg|int sceRegOpenRegistry(struct RegParam * reg, int mode, REGHANDLE * h)}
        extern int  sceRegOpenRegistry(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{9B25EDF1|sceReg|sceRegExit|g|??? sceRegExit()}
        extern int  sceRegExit();
        //@hle:function{BE8C1263|sceReg|sceReg_BE8C1263|g|??? sceReg_BE8C1263()}
        extern int  sceReg_BE8C1263();
        //@hle:function{C5768D02|sceReg|sceRegGetKeyInfoByName|ggggg|int sceRegGetKeyInfoByName(REGHANDLE hd, const char * name, unsigned int * type, SceSize * size)}
        extern int  sceRegGetKeyInfoByName(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{D4475AA8|sceReg|sceRegGetKeyInfo|gggggg|int sceRegGetKeyInfo(REGHANDLE hd, const char * name, REGHANDLE * hk, unsigned int * type, SceSize * size)}
        extern int  sceRegGetKeyInfo(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{DEDA92BF|sceReg|sceRegRemoveRegistry|gg|int sceRegRemoveRegistry(struct RegParam * reg)}
        extern int  sceRegRemoveRegistry(u32 $a0);
        //@hle:function{FA8A5739|sceReg|sceRegCloseRegistry|gg|int sceRegCloseRegistry(REGHANDLE h)}
        extern int  sceRegCloseRegistry(u32 $a0);
    } //@hle:library-end{sceReg|sceRegistry_Service|registry.prx}
}
#endif