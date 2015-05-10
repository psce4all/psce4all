//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(sysmem.prx)UtilsForUser.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace UtilsForUser //@hle:library-start{UtilsForUser|sceSystemMemoryManager|sysmem.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{79D1C3FA|UtilsForUser|sceKernelDcacheWritebackAll|0|void sceKernelDcacheWritebackAll(void)}
        void sceKernelDcacheWritebackAll()
        {
        }
        //@hle:function{B435DEC5|UtilsForUser|sceKernelDcacheWritebackInvalidateAll|0|void sceKernelDcacheWritebackInvalidateAll(void)}
        void sceKernelDcacheWritebackInvalidateAll()
        {
        }
        //@hle:function{3EE30821|UtilsForUser|sceKernelDcacheWritebackRange|0gg|void sceKernelDcacheWritebackRange(const void * addr, unsigned int size)}
        void sceKernelDcacheWritebackRange(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
        }
        //@hle:function{34B9FA9E|UtilsForUser|sceKernelDcacheWritebackInvalidateRange|0gg|void sceKernelDcacheWritebackInvalidateRange(const void * addr, unsigned int size)}
        void sceKernelDcacheWritebackInvalidateRange(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
        }
        //@hle:function{BFA98062|UtilsForUser|sceKernelDcacheInvalidateRange|0gg|void sceKernelDcacheInvalidateRange(const void * addr, unsigned int size)}
        void sceKernelDcacheInvalidateRange(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
        }
        //@hle:function{80001C4C|UtilsForUser|sceKernelDcacheProbe|gg|int sceKernelDcacheProbe(void * addr)}
        int  sceKernelDcacheProbe(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{77DFF087|UtilsForUser|sceKernelDcacheProbeRange|ggg|int sceKernelDcacheProbeRange(void * addr, unsigned int size)}
        int  sceKernelDcacheProbeRange(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{16641D70|UtilsForUser|sceKernelDcacheReadTag|g|??? sceKernelDcacheReadTag()}
        int  sceKernelDcacheReadTag()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{920F104A|UtilsForUser|sceKernelIcacheInvalidateAll|0|void sceKernelIcacheInvalidateAll(void)}
        void sceKernelIcacheInvalidateAll()
        {
        }
        //@hle:function{C2DF770E|UtilsForUser|sceKernelIcacheInvalidateRange|0gg|void sceKernelIcacheInvalidateRange(const void * addr, unsigned int size)}
        void sceKernelIcacheInvalidateRange(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
        }
        //@hle:function{4FD31C9D|UtilsForUser|sceKernelIcacheProbe|gg|int sceKernelIcacheProbe(const void * addr)}
        int  sceKernelIcacheProbe(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FB05FAD0|UtilsForUser|sceKernelIcacheReadTag|g|??? sceKernelIcacheReadTag()}
        int  sceKernelIcacheReadTag()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{C8186A58|UtilsForUser|sceKernelUtilsMd5Digest|gggg|int sceKernelUtilsMd5Digest(const unsigned char * data, unsigned int size, unsigned char * digest)}
        int  sceKernelUtilsMd5Digest(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9E5C5086|UtilsForUser|sceKernelUtilsMd5BlockInit|gg|int sceKernelUtilsMd5BlockInit(SceKernelUtilsMd5Context * ctx)}
        int  sceKernelUtilsMd5BlockInit(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{61E1E525|UtilsForUser|sceKernelUtilsMd5BlockUpdate|gggg|int sceKernelUtilsMd5BlockUpdate(SceKernelUtilsMd5Context * ctx, const unsigned char * data, u32 size)}
        int  sceKernelUtilsMd5BlockUpdate(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B8D24E78|UtilsForUser|sceKernelUtilsMd5BlockResult|ggg|int sceKernelUtilsMd5BlockResult(SceKernelUtilsMd5Context * ctx, unsigned char * digest)}
        int  sceKernelUtilsMd5BlockResult(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{840259F1|UtilsForUser|sceKernelUtilsSha1Digest|gggg|int sceKernelUtilsSha1Digest(const unsigned char * data, unsigned int size, unsigned char * digest)}
        int  sceKernelUtilsSha1Digest(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F8FCD5BA|UtilsForUser|sceKernelUtilsSha1BlockInit|gg|int sceKernelUtilsSha1BlockInit(SceKernelUtilsSha1Context * ctx)}
        int  sceKernelUtilsSha1BlockInit(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{346F6DA8|UtilsForUser|sceKernelUtilsSha1BlockUpdate|gggg|int sceKernelUtilsSha1BlockUpdate(SceKernelUtilsSha1Context * ctx, const unsigned char * data, unsigned int size)}
        int  sceKernelUtilsSha1BlockUpdate(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{585F1C09|UtilsForUser|sceKernelUtilsSha1BlockResult|ggg|int sceKernelUtilsSha1BlockResult(SceKernelUtilsSha1Context * ctx, unsigned char * digest)}
        int  sceKernelUtilsSha1BlockResult(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E860E75E|UtilsForUser|sceKernelUtilsMt19937Init|ggg|int sceKernelUtilsMt19937Init(SceKernelUtilsMt19937Context * ctx, unsigned int seed)}
        int  sceKernelUtilsMt19937Init(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{06FB8A63|UtilsForUser|sceKernelUtilsMt19937UInt|gg|unsigned int sceKernelUtilsMt19937UInt(SceKernelUtilsMt19937Context * ctx)}
        int  sceKernelUtilsMt19937UInt(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{37FB5C42|UtilsForUser|sceKernelGetGPI|g|unsigned char sceKernelGetGPI(void)}
        int  sceKernelGetGPI()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6AD345D7|UtilsForUser|sceKernelSetGPO|0g|void sceKernelSetGPO(unsigned char gpo)}
        void sceKernelSetGPO(u32 $a0)
        {
            (void)($a0);
        }
        //@hle:function{91E4F6A7|UtilsForUser|sceKernelLibcClock|g|clock_t sceKernelLibcClock(void)}
        int  sceKernelLibcClock()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{27CC57F0|UtilsForUser|sceKernelLibcTime|gg|time_t sceKernelLibcTime(time_t * t)}
        int  sceKernelLibcTime(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{71EC4271|UtilsForUser|sceKernelLibcGettimeofday|ggg|int sceKernelLibcGettimeofday(struct timeval * tp, struct timezone * tzp)}
        int  sceKernelLibcGettimeofday(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{87E81561|UtilsForUser|sceKernelPutUserLog|g|??? sceKernelPutUserLog()}
        int  sceKernelPutUserLog()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{004D4DEE|UtilsForUser|UtilsForUser_004D4DEE|g|??? UtilsForUser_004D4DEE()}
        int  UtilsForUser_004D4DEE()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{157A383A|UtilsForUser|UtilsForUser_157A383A|g|??? UtilsForUser_157A383A()}
        int  UtilsForUser_157A383A()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{1B0592A3|UtilsForUser|UtilsForUser_1B0592A3|g|??? UtilsForUser_1B0592A3()}
        int  UtilsForUser_1B0592A3()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{39F49610|UtilsForUser|UtilsForUser_39F49610|g|??? UtilsForUser_39F49610()}
        int  UtilsForUser_39F49610()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3FD3D324|UtilsForUser|UtilsForUser_3FD3D324|g|??? UtilsForUser_3FD3D324()}
        int  UtilsForUser_3FD3D324()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{43C9A8DB|UtilsForUser|UtilsForUser_43C9A8DB|g|??? UtilsForUser_43C9A8DB()}
        int  UtilsForUser_43C9A8DB()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{515B4FAF|UtilsForUser|UtilsForUser_515B4FAF|g|??? UtilsForUser_515B4FAF()}
        int  UtilsForUser_515B4FAF()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5C7F2B1A|UtilsForUser|UtilsForUser_5C7F2B1A|g|??? UtilsForUser_5C7F2B1A()}
        int  UtilsForUser_5C7F2B1A()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6231A71D|UtilsForUser|UtilsForUser_6231A71D|g|??? UtilsForUser_6231A71D()}
        int  UtilsForUser_6231A71D()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7333E539|UtilsForUser|UtilsForUser_7333E539|g|??? UtilsForUser_7333E539()}
        int  UtilsForUser_7333E539()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{740DF7F0|UtilsForUser|UtilsForUser_740DF7F0|g|??? UtilsForUser_740DF7F0()}
        int  UtilsForUser_740DF7F0()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{99134C3F|UtilsForUser|UtilsForUser_99134C3F|g|??? UtilsForUser_99134C3F()}
        int  UtilsForUser_99134C3F()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AF3766BB|UtilsForUser|UtilsForUser_AF3766BB|g|??? UtilsForUser_AF3766BB()}
        int  UtilsForUser_AF3766BB()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B83A1E76|UtilsForUser|UtilsForUser_B83A1E76|g|??? UtilsForUser_B83A1E76()}
        int  UtilsForUser_B83A1E76()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{DBBE9A46|UtilsForUser|UtilsForUser_DBBE9A46|g|??? UtilsForUser_DBBE9A46()}
        int  UtilsForUser_DBBE9A46()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F0155BCA|UtilsForUser|UtilsForUser_F0155BCA|g|??? UtilsForUser_F0155BCA()}
        int  UtilsForUser_F0155BCA()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{UtilsForUser|sceSystemMemoryManager|sysmem.prx}
}

extern "C" bool __cdecl UtilsForUser$Init() { return hle::UtilsForUser::Init(); }
extern "C" bool __cdecl UtilsForUser$Fini() { return hle::UtilsForUser::Fini(); }
extern "C" void __cdecl UtilsForUser_79D1C3FA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0               < hle::UtilsForUser::sceKernelDcacheWritebackAll                      >(c); } //@hle:syscall{79D1C3FA|UtilsForUser|sceKernelDcacheWritebackAll|0|void sceKernelDcacheWritebackAll(void)}
extern "C" void __cdecl UtilsForUser_B435DEC5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0               < hle::UtilsForUser::sceKernelDcacheWritebackInvalidateAll            >(c); } //@hle:syscall{B435DEC5|UtilsForUser|sceKernelDcacheWritebackInvalidateAll|0|void sceKernelDcacheWritebackInvalidateAll(void)}
extern "C" void __cdecl UtilsForUser_3EE30821(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0gg             < hle::UtilsForUser::sceKernelDcacheWritebackRange                    >(c); } //@hle:syscall{3EE30821|UtilsForUser|sceKernelDcacheWritebackRange|0gg|void sceKernelDcacheWritebackRange(const void * addr, unsigned int size)}
extern "C" void __cdecl UtilsForUser_34B9FA9E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0gg             < hle::UtilsForUser::sceKernelDcacheWritebackInvalidateRange          >(c); } //@hle:syscall{34B9FA9E|UtilsForUser|sceKernelDcacheWritebackInvalidateRange|0gg|void sceKernelDcacheWritebackInvalidateRange(const void * addr, unsigned int size)}
extern "C" void __cdecl UtilsForUser_BFA98062(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0gg             < hle::UtilsForUser::sceKernelDcacheInvalidateRange                   >(c); } //@hle:syscall{BFA98062|UtilsForUser|sceKernelDcacheInvalidateRange|0gg|void sceKernelDcacheInvalidateRange(const void * addr, unsigned int size)}
extern "C" void __cdecl UtilsForUser_80001C4C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::UtilsForUser::sceKernelDcacheProbe                             >(c); } //@hle:syscall{80001C4C|UtilsForUser|sceKernelDcacheProbe|gg|int sceKernelDcacheProbe(void * addr)}
extern "C" void __cdecl UtilsForUser_77DFF087(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::UtilsForUser::sceKernelDcacheProbeRange                        >(c); } //@hle:syscall{77DFF087|UtilsForUser|sceKernelDcacheProbeRange|ggg|int sceKernelDcacheProbeRange(void * addr, unsigned int size)}
extern "C" void __cdecl UtilsForUser_16641D70(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::sceKernelDcacheReadTag                           >(c); } //@hle:syscall{16641D70|UtilsForUser|sceKernelDcacheReadTag|g|??? sceKernelDcacheReadTag()}
extern "C" void __cdecl UtilsForUser_920F104A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0               < hle::UtilsForUser::sceKernelIcacheInvalidateAll                     >(c); } //@hle:syscall{920F104A|UtilsForUser|sceKernelIcacheInvalidateAll|0|void sceKernelIcacheInvalidateAll(void)}
extern "C" void __cdecl UtilsForUser_C2DF770E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0gg             < hle::UtilsForUser::sceKernelIcacheInvalidateRange                   >(c); } //@hle:syscall{C2DF770E|UtilsForUser|sceKernelIcacheInvalidateRange|0gg|void sceKernelIcacheInvalidateRange(const void * addr, unsigned int size)}
extern "C" void __cdecl UtilsForUser_4FD31C9D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::UtilsForUser::sceKernelIcacheProbe                             >(c); } //@hle:syscall{4FD31C9D|UtilsForUser|sceKernelIcacheProbe|gg|int sceKernelIcacheProbe(const void * addr)}
extern "C" void __cdecl UtilsForUser_FB05FAD0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::sceKernelIcacheReadTag                           >(c); } //@hle:syscall{FB05FAD0|UtilsForUser|sceKernelIcacheReadTag|g|??? sceKernelIcacheReadTag()}
extern "C" void __cdecl UtilsForUser_C8186A58(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::UtilsForUser::sceKernelUtilsMd5Digest                          >(c); } //@hle:syscall{C8186A58|UtilsForUser|sceKernelUtilsMd5Digest|gggg|int sceKernelUtilsMd5Digest(const unsigned char * data, unsigned int size, unsigned char * digest)}
extern "C" void __cdecl UtilsForUser_9E5C5086(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::UtilsForUser::sceKernelUtilsMd5BlockInit                       >(c); } //@hle:syscall{9E5C5086|UtilsForUser|sceKernelUtilsMd5BlockInit|gg|int sceKernelUtilsMd5BlockInit(SceKernelUtilsMd5Context * ctx)}
extern "C" void __cdecl UtilsForUser_61E1E525(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::UtilsForUser::sceKernelUtilsMd5BlockUpdate                     >(c); } //@hle:syscall{61E1E525|UtilsForUser|sceKernelUtilsMd5BlockUpdate|gggg|int sceKernelUtilsMd5BlockUpdate(SceKernelUtilsMd5Context * ctx, const unsigned char * data, u32 size)}
extern "C" void __cdecl UtilsForUser_B8D24E78(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::UtilsForUser::sceKernelUtilsMd5BlockResult                     >(c); } //@hle:syscall{B8D24E78|UtilsForUser|sceKernelUtilsMd5BlockResult|ggg|int sceKernelUtilsMd5BlockResult(SceKernelUtilsMd5Context * ctx, unsigned char * digest)}
extern "C" void __cdecl UtilsForUser_840259F1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::UtilsForUser::sceKernelUtilsSha1Digest                         >(c); } //@hle:syscall{840259F1|UtilsForUser|sceKernelUtilsSha1Digest|gggg|int sceKernelUtilsSha1Digest(const unsigned char * data, unsigned int size, unsigned char * digest)}
extern "C" void __cdecl UtilsForUser_F8FCD5BA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::UtilsForUser::sceKernelUtilsSha1BlockInit                      >(c); } //@hle:syscall{F8FCD5BA|UtilsForUser|sceKernelUtilsSha1BlockInit|gg|int sceKernelUtilsSha1BlockInit(SceKernelUtilsSha1Context * ctx)}
extern "C" void __cdecl UtilsForUser_346F6DA8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::UtilsForUser::sceKernelUtilsSha1BlockUpdate                    >(c); } //@hle:syscall{346F6DA8|UtilsForUser|sceKernelUtilsSha1BlockUpdate|gggg|int sceKernelUtilsSha1BlockUpdate(SceKernelUtilsSha1Context * ctx, const unsigned char * data, unsigned int size)}
extern "C" void __cdecl UtilsForUser_585F1C09(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::UtilsForUser::sceKernelUtilsSha1BlockResult                    >(c); } //@hle:syscall{585F1C09|UtilsForUser|sceKernelUtilsSha1BlockResult|ggg|int sceKernelUtilsSha1BlockResult(SceKernelUtilsSha1Context * ctx, unsigned char * digest)}
extern "C" void __cdecl UtilsForUser_E860E75E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::UtilsForUser::sceKernelUtilsMt19937Init                        >(c); } //@hle:syscall{E860E75E|UtilsForUser|sceKernelUtilsMt19937Init|ggg|int sceKernelUtilsMt19937Init(SceKernelUtilsMt19937Context * ctx, unsigned int seed)}
extern "C" void __cdecl UtilsForUser_06FB8A63(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::UtilsForUser::sceKernelUtilsMt19937UInt                        >(c); } //@hle:syscall{06FB8A63|UtilsForUser|sceKernelUtilsMt19937UInt|gg|unsigned int sceKernelUtilsMt19937UInt(SceKernelUtilsMt19937Context * ctx)}
extern "C" void __cdecl UtilsForUser_37FB5C42(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::sceKernelGetGPI                                  >(c); } //@hle:syscall{37FB5C42|UtilsForUser|sceKernelGetGPI|g|unsigned char sceKernelGetGPI(void)}
extern "C" void __cdecl UtilsForUser_6AD345D7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$0g              < hle::UtilsForUser::sceKernelSetGPO                                  >(c); } //@hle:syscall{6AD345D7|UtilsForUser|sceKernelSetGPO|0g|void sceKernelSetGPO(unsigned char gpo)}
extern "C" void __cdecl UtilsForUser_91E4F6A7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::sceKernelLibcClock                               >(c); } //@hle:syscall{91E4F6A7|UtilsForUser|sceKernelLibcClock|g|clock_t sceKernelLibcClock(void)}
extern "C" void __cdecl UtilsForUser_27CC57F0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::UtilsForUser::sceKernelLibcTime                                >(c); } //@hle:syscall{27CC57F0|UtilsForUser|sceKernelLibcTime|gg|time_t sceKernelLibcTime(time_t * t)}
extern "C" void __cdecl UtilsForUser_71EC4271(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::UtilsForUser::sceKernelLibcGettimeofday                        >(c); } //@hle:syscall{71EC4271|UtilsForUser|sceKernelLibcGettimeofday|ggg|int sceKernelLibcGettimeofday(struct timeval * tp, struct timezone * tzp)}
extern "C" void __cdecl UtilsForUser_87E81561(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::sceKernelPutUserLog                              >(c); } //@hle:syscall{87E81561|UtilsForUser|sceKernelPutUserLog|g|??? sceKernelPutUserLog()}
extern "C" void __cdecl UtilsForUser_004D4DEE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_004D4DEE                            >(c); } //@hle:syscall{004D4DEE|UtilsForUser|UtilsForUser_004D4DEE|g|??? UtilsForUser_004D4DEE()}
extern "C" void __cdecl UtilsForUser_157A383A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_157A383A                            >(c); } //@hle:syscall{157A383A|UtilsForUser|UtilsForUser_157A383A|g|??? UtilsForUser_157A383A()}
extern "C" void __cdecl UtilsForUser_1B0592A3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_1B0592A3                            >(c); } //@hle:syscall{1B0592A3|UtilsForUser|UtilsForUser_1B0592A3|g|??? UtilsForUser_1B0592A3()}
extern "C" void __cdecl UtilsForUser_39F49610(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_39F49610                            >(c); } //@hle:syscall{39F49610|UtilsForUser|UtilsForUser_39F49610|g|??? UtilsForUser_39F49610()}
extern "C" void __cdecl UtilsForUser_3FD3D324(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_3FD3D324                            >(c); } //@hle:syscall{3FD3D324|UtilsForUser|UtilsForUser_3FD3D324|g|??? UtilsForUser_3FD3D324()}
extern "C" void __cdecl UtilsForUser_43C9A8DB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_43C9A8DB                            >(c); } //@hle:syscall{43C9A8DB|UtilsForUser|UtilsForUser_43C9A8DB|g|??? UtilsForUser_43C9A8DB()}
extern "C" void __cdecl UtilsForUser_515B4FAF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_515B4FAF                            >(c); } //@hle:syscall{515B4FAF|UtilsForUser|UtilsForUser_515B4FAF|g|??? UtilsForUser_515B4FAF()}
extern "C" void __cdecl UtilsForUser_5C7F2B1A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_5C7F2B1A                            >(c); } //@hle:syscall{5C7F2B1A|UtilsForUser|UtilsForUser_5C7F2B1A|g|??? UtilsForUser_5C7F2B1A()}
extern "C" void __cdecl UtilsForUser_6231A71D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_6231A71D                            >(c); } //@hle:syscall{6231A71D|UtilsForUser|UtilsForUser_6231A71D|g|??? UtilsForUser_6231A71D()}
extern "C" void __cdecl UtilsForUser_7333E539(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_7333E539                            >(c); } //@hle:syscall{7333E539|UtilsForUser|UtilsForUser_7333E539|g|??? UtilsForUser_7333E539()}
extern "C" void __cdecl UtilsForUser_740DF7F0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_740DF7F0                            >(c); } //@hle:syscall{740DF7F0|UtilsForUser|UtilsForUser_740DF7F0|g|??? UtilsForUser_740DF7F0()}
extern "C" void __cdecl UtilsForUser_99134C3F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_99134C3F                            >(c); } //@hle:syscall{99134C3F|UtilsForUser|UtilsForUser_99134C3F|g|??? UtilsForUser_99134C3F()}
extern "C" void __cdecl UtilsForUser_AF3766BB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_AF3766BB                            >(c); } //@hle:syscall{AF3766BB|UtilsForUser|UtilsForUser_AF3766BB|g|??? UtilsForUser_AF3766BB()}
extern "C" void __cdecl UtilsForUser_B83A1E76(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_B83A1E76                            >(c); } //@hle:syscall{B83A1E76|UtilsForUser|UtilsForUser_B83A1E76|g|??? UtilsForUser_B83A1E76()}
extern "C" void __cdecl UtilsForUser_DBBE9A46(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_DBBE9A46                            >(c); } //@hle:syscall{DBBE9A46|UtilsForUser|UtilsForUser_DBBE9A46|g|??? UtilsForUser_DBBE9A46()}
extern "C" void __cdecl UtilsForUser_F0155BCA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::UtilsForUser::UtilsForUser_F0155BCA                            >(c); } //@hle:syscall{F0155BCA|UtilsForUser|UtilsForUser_F0155BCA|g|??? UtilsForUser_F0155BCA()}