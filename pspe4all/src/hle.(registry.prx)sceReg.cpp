//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(registry.prx)sceReg.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceReg //@hle:library-start{sceReg|sceRegistry_Service|registry.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{0CAE832B|sceReg|sceRegCloseCategory|gg|int sceRegCloseCategory(REGHANDLE hd)}
        int  sceRegCloseCategory(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0D69BF40|sceReg|sceRegFlushCategory|gg|int sceRegFlushCategory(REGHANDLE hd)}
        int  sceRegFlushCategory(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{17768E14|sceReg|sceRegSetKeyValue|ggggg|int sceRegSetKeyValue(REGHANDLE hd, const char * name, const void * buf, SceSize size)}
        int  sceRegSetKeyValue(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1D8A762E|sceReg|sceRegOpenCategory|ggggg|int sceRegOpenCategory(REGHANDLE h, const char * name, int mode, REGHANDLE * hd)}
        int  sceRegOpenCategory(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{28A8E98A|sceReg|sceRegGetKeyValue|ggggg|int sceRegGetKeyValue(REGHANDLE hd, REGHANDLE hk, void * buf, SceSize size)}
        int  sceRegGetKeyValue(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2C0DB9DD|sceReg|sceRegGetKeysNum|ggg|int sceRegGetKeysNum(REGHANDLE hd, int * num)}
        int  sceRegGetKeysNum(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2D211135|sceReg|sceRegGetKeys|gggg|int sceRegGetKeys(REGHANDLE hd, char * buf, int num)}
        int  sceRegGetKeys(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{30BE0259|sceReg|sceRegGetKeyValueByName|ggggg|int sceRegGetKeyValueByName(REGHANDLE hd, const char * name, void * buf, SceSize size)}
        int  sceRegGetKeyValueByName(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3615BC87|sceReg|sceRegRemoveKey|g|??? sceRegRemoveKey()}
        int  sceRegRemoveKey()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{39461B4D|sceReg|sceRegFlushRegistry|gg|int sceRegFlushRegistry(REGHANDLE h)}
        int  sceRegFlushRegistry(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4CA16893|sceReg|sceRegRemoveCategory|ggg|int sceRegRemoveCategory(REGHANDLE h, const char * name)}
        int  sceRegRemoveCategory(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{57641A81|sceReg|sceRegCreateKey|ggggg|int sceRegCreateKey(REGHANDLE hd, const char * name, int type, SceSize size)}
        int  sceRegCreateKey(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{835ECE6F|sceReg|sceReg_835ECE6F|g|??? sceReg_835ECE6F()}
        int  sceReg_835ECE6F()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{92E41280|sceReg|sceRegOpenRegistry|gggg|int sceRegOpenRegistry(struct RegParam * reg, int mode, REGHANDLE * h)}
        int  sceRegOpenRegistry(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9B25EDF1|sceReg|sceRegExit|g|??? sceRegExit()}
        int  sceRegExit()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BE8C1263|sceReg|sceReg_BE8C1263|g|??? sceReg_BE8C1263()}
        int  sceReg_BE8C1263()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C5768D02|sceReg|sceRegGetKeyInfoByName|ggggg|int sceRegGetKeyInfoByName(REGHANDLE hd, const char * name, unsigned int * type, SceSize * size)}
        int  sceRegGetKeyInfoByName(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D4475AA8|sceReg|sceRegGetKeyInfo|gggggg|int sceRegGetKeyInfo(REGHANDLE hd, const char * name, REGHANDLE * hk, unsigned int * type, SceSize * size)}
        int  sceRegGetKeyInfo(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DEDA92BF|sceReg|sceRegRemoveRegistry|gg|int sceRegRemoveRegistry(struct RegParam * reg)}
        int  sceRegRemoveRegistry(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FA8A5739|sceReg|sceRegCloseRegistry|gg|int sceRegCloseRegistry(REGHANDLE h)}
        int  sceRegCloseRegistry(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceReg|sceRegistry_Service|registry.prx}
}

extern "C" bool __cdecl sceReg$Init() { return hle::sceReg::Init(); }
extern "C" bool __cdecl sceReg$Fini() { return hle::sceReg::Fini(); }
extern "C" void __cdecl sceReg_0CAE832B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceReg::sceRegCloseCategory                              >(c); } //@hle:syscall{0CAE832B|sceReg|sceRegCloseCategory|gg|int sceRegCloseCategory(REGHANDLE hd)}
extern "C" void __cdecl sceReg_0D69BF40(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceReg::sceRegFlushCategory                              >(c); } //@hle:syscall{0D69BF40|sceReg|sceRegFlushCategory|gg|int sceRegFlushCategory(REGHANDLE hd)}
extern "C" void __cdecl sceReg_17768E14(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceReg::sceRegSetKeyValue                                >(c); } //@hle:syscall{17768E14|sceReg|sceRegSetKeyValue|ggggg|int sceRegSetKeyValue(REGHANDLE hd, const char * name, const void * buf, SceSize size)}
extern "C" void __cdecl sceReg_1D8A762E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceReg::sceRegOpenCategory                               >(c); } //@hle:syscall{1D8A762E|sceReg|sceRegOpenCategory|ggggg|int sceRegOpenCategory(REGHANDLE h, const char * name, int mode, REGHANDLE * hd)}
extern "C" void __cdecl sceReg_28A8E98A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceReg::sceRegGetKeyValue                                >(c); } //@hle:syscall{28A8E98A|sceReg|sceRegGetKeyValue|ggggg|int sceRegGetKeyValue(REGHANDLE hd, REGHANDLE hk, void * buf, SceSize size)}
extern "C" void __cdecl sceReg_2C0DB9DD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceReg::sceRegGetKeysNum                                 >(c); } //@hle:syscall{2C0DB9DD|sceReg|sceRegGetKeysNum|ggg|int sceRegGetKeysNum(REGHANDLE hd, int * num)}
extern "C" void __cdecl sceReg_2D211135(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceReg::sceRegGetKeys                                    >(c); } //@hle:syscall{2D211135|sceReg|sceRegGetKeys|gggg|int sceRegGetKeys(REGHANDLE hd, char * buf, int num)}
extern "C" void __cdecl sceReg_30BE0259(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceReg::sceRegGetKeyValueByName                          >(c); } //@hle:syscall{30BE0259|sceReg|sceRegGetKeyValueByName|ggggg|int sceRegGetKeyValueByName(REGHANDLE hd, const char * name, void * buf, SceSize size)}
extern "C" void __cdecl sceReg_3615BC87(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceReg::sceRegRemoveKey                                  >(c); } //@hle:syscall{3615BC87|sceReg|sceRegRemoveKey|g|??? sceRegRemoveKey()}
extern "C" void __cdecl sceReg_39461B4D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceReg::sceRegFlushRegistry                              >(c); } //@hle:syscall{39461B4D|sceReg|sceRegFlushRegistry|gg|int sceRegFlushRegistry(REGHANDLE h)}
extern "C" void __cdecl sceReg_4CA16893(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceReg::sceRegRemoveCategory                             >(c); } //@hle:syscall{4CA16893|sceReg|sceRegRemoveCategory|ggg|int sceRegRemoveCategory(REGHANDLE h, const char * name)}
extern "C" void __cdecl sceReg_57641A81(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceReg::sceRegCreateKey                                  >(c); } //@hle:syscall{57641A81|sceReg|sceRegCreateKey|ggggg|int sceRegCreateKey(REGHANDLE hd, const char * name, int type, SceSize size)}
extern "C" void __cdecl sceReg_835ECE6F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceReg::sceReg_835ECE6F                                  >(c); } //@hle:syscall{835ECE6F|sceReg|sceReg_835ECE6F|g|??? sceReg_835ECE6F()}
extern "C" void __cdecl sceReg_92E41280(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceReg::sceRegOpenRegistry                               >(c); } //@hle:syscall{92E41280|sceReg|sceRegOpenRegistry|gggg|int sceRegOpenRegistry(struct RegParam * reg, int mode, REGHANDLE * h)}
extern "C" void __cdecl sceReg_9B25EDF1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceReg::sceRegExit                                       >(c); } //@hle:syscall{9B25EDF1|sceReg|sceRegExit|g|??? sceRegExit()}
extern "C" void __cdecl sceReg_BE8C1263(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceReg::sceReg_BE8C1263                                  >(c); } //@hle:syscall{BE8C1263|sceReg|sceReg_BE8C1263|g|??? sceReg_BE8C1263()}
extern "C" void __cdecl sceReg_C5768D02(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceReg::sceRegGetKeyInfoByName                           >(c); } //@hle:syscall{C5768D02|sceReg|sceRegGetKeyInfoByName|ggggg|int sceRegGetKeyInfoByName(REGHANDLE hd, const char * name, unsigned int * type, SceSize * size)}
extern "C" void __cdecl sceReg_D4475AA8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::sceReg::sceRegGetKeyInfo                                 >(c); } //@hle:syscall{D4475AA8|sceReg|sceRegGetKeyInfo|gggggg|int sceRegGetKeyInfo(REGHANDLE hd, const char * name, REGHANDLE * hk, unsigned int * type, SceSize * size)}
extern "C" void __cdecl sceReg_DEDA92BF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceReg::sceRegRemoveRegistry                             >(c); } //@hle:syscall{DEDA92BF|sceReg|sceRegRemoveRegistry|gg|int sceRegRemoveRegistry(struct RegParam * reg)}
extern "C" void __cdecl sceReg_FA8A5739(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceReg::sceRegCloseRegistry                              >(c); } //@hle:syscall{FA8A5739|sceReg|sceRegCloseRegistry|gg|int sceRegCloseRegistry(REGHANDLE h)}