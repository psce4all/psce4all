//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_sysmem_prx_UtilsForUser_h__
#define hle_sysmem_prx_UtilsForUser_h__

namespace hle
{
    namespace UtilsForUser //@hle:library-start{UtilsForUser|sceSystemMemoryManager|sysmem.prx}
    {
        //@hle:function{79D1C3FA|UtilsForUser|sceKernelDcacheWritebackAll|0|void sceKernelDcacheWritebackAll(void)}
        extern void sceKernelDcacheWritebackAll();
        //@hle:function{B435DEC5|UtilsForUser|sceKernelDcacheWritebackInvalidateAll|0|void sceKernelDcacheWritebackInvalidateAll(void)}
        extern void sceKernelDcacheWritebackInvalidateAll();
        //@hle:function{3EE30821|UtilsForUser|sceKernelDcacheWritebackRange|0gg|void sceKernelDcacheWritebackRange(const void * addr, unsigned int size)}
        extern void sceKernelDcacheWritebackRange(u32 $a0, u32 $a1);
        //@hle:function{34B9FA9E|UtilsForUser|sceKernelDcacheWritebackInvalidateRange|0gg|void sceKernelDcacheWritebackInvalidateRange(const void * addr, unsigned int size)}
        extern void sceKernelDcacheWritebackInvalidateRange(u32 $a0, u32 $a1);
        //@hle:function{BFA98062|UtilsForUser|sceKernelDcacheInvalidateRange|0gg|void sceKernelDcacheInvalidateRange(const void * addr, unsigned int size)}
        extern void sceKernelDcacheInvalidateRange(u32 $a0, u32 $a1);
        //@hle:function{80001C4C|UtilsForUser|sceKernelDcacheProbe|gg|int sceKernelDcacheProbe(void * addr)}
        extern int  sceKernelDcacheProbe(u32 $a0);
        //@hle:function{77DFF087|UtilsForUser|sceKernelDcacheProbeRange|ggg|int sceKernelDcacheProbeRange(void * addr, unsigned int size)}
        extern int  sceKernelDcacheProbeRange(u32 $a0, u32 $a1);
        //@hle:function{16641D70|UtilsForUser|sceKernelDcacheReadTag|g|??? sceKernelDcacheReadTag()}
        extern int  sceKernelDcacheReadTag();
        //@hle:function{920F104A|UtilsForUser|sceKernelIcacheInvalidateAll|0|void sceKernelIcacheInvalidateAll(void)}
        extern void sceKernelIcacheInvalidateAll();
        //@hle:function{C2DF770E|UtilsForUser|sceKernelIcacheInvalidateRange|0gg|void sceKernelIcacheInvalidateRange(const void * addr, unsigned int size)}
        extern void sceKernelIcacheInvalidateRange(u32 $a0, u32 $a1);
        //@hle:function{4FD31C9D|UtilsForUser|sceKernelIcacheProbe|gg|int sceKernelIcacheProbe(const void * addr)}
        extern int  sceKernelIcacheProbe(u32 $a0);
        //@hle:function{FB05FAD0|UtilsForUser|sceKernelIcacheReadTag|g|??? sceKernelIcacheReadTag()}
        extern int  sceKernelIcacheReadTag();
        //@hle:function{C8186A58|UtilsForUser|sceKernelUtilsMd5Digest|gggg|int sceKernelUtilsMd5Digest(const unsigned char * data, unsigned int size, unsigned char * digest)}
        extern int  sceKernelUtilsMd5Digest(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{9E5C5086|UtilsForUser|sceKernelUtilsMd5BlockInit|gg|int sceKernelUtilsMd5BlockInit(SceKernelUtilsMd5Context * ctx)}
        extern int  sceKernelUtilsMd5BlockInit(u32 $a0);
        //@hle:function{61E1E525|UtilsForUser|sceKernelUtilsMd5BlockUpdate|gggg|int sceKernelUtilsMd5BlockUpdate(SceKernelUtilsMd5Context * ctx, const unsigned char * data, u32 size)}
        extern int  sceKernelUtilsMd5BlockUpdate(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{B8D24E78|UtilsForUser|sceKernelUtilsMd5BlockResult|ggg|int sceKernelUtilsMd5BlockResult(SceKernelUtilsMd5Context * ctx, unsigned char * digest)}
        extern int  sceKernelUtilsMd5BlockResult(u32 $a0, u32 $a1);
        //@hle:function{840259F1|UtilsForUser|sceKernelUtilsSha1Digest|gggg|int sceKernelUtilsSha1Digest(const unsigned char * data, unsigned int size, unsigned char * digest)}
        extern int  sceKernelUtilsSha1Digest(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{F8FCD5BA|UtilsForUser|sceKernelUtilsSha1BlockInit|gg|int sceKernelUtilsSha1BlockInit(SceKernelUtilsSha1Context * ctx)}
        extern int  sceKernelUtilsSha1BlockInit(u32 $a0);
        //@hle:function{346F6DA8|UtilsForUser|sceKernelUtilsSha1BlockUpdate|gggg|int sceKernelUtilsSha1BlockUpdate(SceKernelUtilsSha1Context * ctx, const unsigned char * data, unsigned int size)}
        extern int  sceKernelUtilsSha1BlockUpdate(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{585F1C09|UtilsForUser|sceKernelUtilsSha1BlockResult|ggg|int sceKernelUtilsSha1BlockResult(SceKernelUtilsSha1Context * ctx, unsigned char * digest)}
        extern int  sceKernelUtilsSha1BlockResult(u32 $a0, u32 $a1);
        //@hle:function{E860E75E|UtilsForUser|sceKernelUtilsMt19937Init|ggg|int sceKernelUtilsMt19937Init(SceKernelUtilsMt19937Context * ctx, unsigned int seed)}
        extern int  sceKernelUtilsMt19937Init(u32 $a0, u32 $a1);
        //@hle:function{06FB8A63|UtilsForUser|sceKernelUtilsMt19937UInt|gg|unsigned int sceKernelUtilsMt19937UInt(SceKernelUtilsMt19937Context * ctx)}
        extern int  sceKernelUtilsMt19937UInt(u32 $a0);
        //@hle:function{37FB5C42|UtilsForUser|sceKernelGetGPI|g|unsigned char sceKernelGetGPI(void)}
        extern int  sceKernelGetGPI();
        //@hle:function{6AD345D7|UtilsForUser|sceKernelSetGPO|0g|void sceKernelSetGPO(unsigned char gpo)}
        extern void sceKernelSetGPO(u32 $a0);
        //@hle:function{91E4F6A7|UtilsForUser|sceKernelLibcClock|g|clock_t sceKernelLibcClock(void)}
        extern int  sceKernelLibcClock();
        //@hle:function{27CC57F0|UtilsForUser|sceKernelLibcTime|gg|time_t sceKernelLibcTime(time_t * t)}
        extern int  sceKernelLibcTime(u32 $a0);
        //@hle:function{71EC4271|UtilsForUser|sceKernelLibcGettimeofday|ggg|int sceKernelLibcGettimeofday(struct timeval * tp, struct timezone * tzp)}
        extern int  sceKernelLibcGettimeofday(u32 $a0, u32 $a1);
        //@hle:function{87E81561|UtilsForUser|sceKernelPutUserLog|g|??? sceKernelPutUserLog()}
        extern int  sceKernelPutUserLog();
        //@hle:function{004D4DEE|UtilsForUser|UtilsForUser_004D4DEE|g|??? UtilsForUser_004D4DEE()}
        extern int  UtilsForUser_004D4DEE();
        //@hle:function{157A383A|UtilsForUser|UtilsForUser_157A383A|g|??? UtilsForUser_157A383A()}
        extern int  UtilsForUser_157A383A();
        //@hle:function{1B0592A3|UtilsForUser|UtilsForUser_1B0592A3|g|??? UtilsForUser_1B0592A3()}
        extern int  UtilsForUser_1B0592A3();
        //@hle:function{39F49610|UtilsForUser|UtilsForUser_39F49610|g|??? UtilsForUser_39F49610()}
        extern int  UtilsForUser_39F49610();
        //@hle:function{3FD3D324|UtilsForUser|UtilsForUser_3FD3D324|g|??? UtilsForUser_3FD3D324()}
        extern int  UtilsForUser_3FD3D324();
        //@hle:function{43C9A8DB|UtilsForUser|UtilsForUser_43C9A8DB|g|??? UtilsForUser_43C9A8DB()}
        extern int  UtilsForUser_43C9A8DB();
        //@hle:function{515B4FAF|UtilsForUser|UtilsForUser_515B4FAF|g|??? UtilsForUser_515B4FAF()}
        extern int  UtilsForUser_515B4FAF();
        //@hle:function{5C7F2B1A|UtilsForUser|UtilsForUser_5C7F2B1A|g|??? UtilsForUser_5C7F2B1A()}
        extern int  UtilsForUser_5C7F2B1A();
        //@hle:function{6231A71D|UtilsForUser|UtilsForUser_6231A71D|g|??? UtilsForUser_6231A71D()}
        extern int  UtilsForUser_6231A71D();
        //@hle:function{7333E539|UtilsForUser|UtilsForUser_7333E539|g|??? UtilsForUser_7333E539()}
        extern int  UtilsForUser_7333E539();
        //@hle:function{740DF7F0|UtilsForUser|UtilsForUser_740DF7F0|g|??? UtilsForUser_740DF7F0()}
        extern int  UtilsForUser_740DF7F0();
        //@hle:function{99134C3F|UtilsForUser|UtilsForUser_99134C3F|g|??? UtilsForUser_99134C3F()}
        extern int  UtilsForUser_99134C3F();
        //@hle:function{AF3766BB|UtilsForUser|UtilsForUser_AF3766BB|g|??? UtilsForUser_AF3766BB()}
        extern int  UtilsForUser_AF3766BB();
        //@hle:function{B83A1E76|UtilsForUser|UtilsForUser_B83A1E76|g|??? UtilsForUser_B83A1E76()}
        extern int  UtilsForUser_B83A1E76();
        //@hle:function{DBBE9A46|UtilsForUser|UtilsForUser_DBBE9A46|g|??? UtilsForUser_DBBE9A46()}
        extern int  UtilsForUser_DBBE9A46();
        //@hle:function{F0155BCA|UtilsForUser|UtilsForUser_F0155BCA|g|??? UtilsForUser_F0155BCA()}
        extern int  UtilsForUser_F0155BCA();
    } //@hle:library-end{UtilsForUser|sceSystemMemoryManager|sysmem.prx}
}
#endif