//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(libatrac3plus.prx)sceAtrac3plus.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceAtrac3plus //@hle:library-start{sceAtrac3plus|sceATRAC3plus_Library|libatrac3plus.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{780F88D1|sceAtrac3plus|sceAtracGetAtracID|gg|int sceAtracGetAtracID(unsigned int codec_type)}
        int  sceAtracGetAtracID(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{61EB33F5|sceAtrac3plus|sceAtracReleaseAtracID|gg|int sceAtracReleaseAtracID(int atrac_id)}
        int  sceAtracReleaseAtracID(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{132F1ECA|sceAtrac3plus|sceAtracReinit|ggg|int sceAtracReinit(int at3_entry, int at3plus_entry)}
        int  sceAtracReinit(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0E2A73AB|sceAtrac3plus|sceAtracSetData|gggg|int sceAtracSetData(int atrac_id, unsigned char * buffer_address, unsigned int buffer_size)}
        int  sceAtracSetData(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{3F6E26B5|sceAtrac3plus|sceAtracSetHalfwayBuffer|ggggg|int sceAtracSetHalfwayBuffer(int atrac_id, unsigned char * buffer_address, unsigned int read_bytes, unsigned int buffer_size)}
        int  sceAtracSetHalfwayBuffer(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7A20E7AF|sceAtrac3plus|sceAtracSetDataAndGetID|ggg|int sceAtracSetDataAndGetID(unsigned char * buffer_address, unsigned int buffer_size)}
        int  sceAtracSetDataAndGetID(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{0FAE370E|sceAtrac3plus|sceAtracSetHalfwayBufferAndGetID|gggg|int sceAtracSetHalfwayBufferAndGetID(unsigned char * buffer_address, unsigned int read_bytes, unsigned int buffer_size)}
        int  sceAtracSetHalfwayBufferAndGetID(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6A8C3CD5|sceAtrac3plus|sceAtracDecodeData|gggggg|int sceAtracDecodeData(int atrac_id, short * sample_buffer, unsigned int * sample_count, unsigned int * finish_flag, int * remaining_frames)}
        int  sceAtracDecodeData(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5D268707|sceAtrac3plus|sceAtracGetStreamDataInfo|ggggg|int sceAtracGetStreamDataInfo(int atrac_id, unsigned char * * buffer_address, unsigned int writable_bytes, unsigned int read_position)}
        int  sceAtracGetStreamDataInfo(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7DB31251|sceAtrac3plus|sceAtracAddStreamData|ggg|int sceAtracAddStreamData(int atrac_id, unsigned int bytes)}
        int  sceAtracAddStreamData(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{83E85EA0|sceAtrac3plus|sceAtracGetSecondBufferInfo|gggg|int sceAtracGetSecondBufferInfo(int atrac_id, unsigned int * position, unsigned int * bytes)}
        int  sceAtracGetSecondBufferInfo(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{83BF7AFD|sceAtrac3plus|sceAtracSetSecondBuffer|gggg|int sceAtracSetSecondBuffer(int atrac_id, unsigned char * second_buffer_address, unsigned int second_buffer_size)}
        int  sceAtracSetSecondBuffer(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{ECA32A99|sceAtrac3plus|sceAtracIsSecondBufferNeeded|gg|int sceAtracIsSecondBufferNeeded(int atrac_id)}
        int  sceAtracIsSecondBufferNeeded(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9AE849A7|sceAtrac3plus|sceAtracGetRemainFrame|ggg|int sceAtracGetRemainFrame(int atrac_id, int * remaining_frames)}
        int  sceAtracGetRemainFrame(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{31668BAA|sceAtrac3plus|sceAtracGetChannel|ggg|int sceAtracGetChannel(int atrac_id, int * channel)}
        int  sceAtracGetChannel(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B3B5D042|sceAtrac3plus|sceAtracGetOutputChannel|ggg|int sceAtracGetOutputChannel(int atrac_id, int * channel)}
        int  sceAtracGetOutputChannel(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D6A5F2F7|sceAtrac3plus|sceAtracGetMaxSample|ggg|int sceAtracGetMaxSample(int atrac_id, int * max_sample)}
        int  sceAtracGetMaxSample(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{36FAABFB|sceAtrac3plus|sceAtracGetNextSample|ggg|int sceAtracGetNextSample(int atrac_id, int * next_sample)}
        int  sceAtracGetNextSample(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A2BBA8BE|sceAtrac3plus|sceAtracGetSoundSample|ggggg|int sceAtracGetSoundSample(int atrac_id, int * end_sample, int * loop_start_sample, int * loop_end_sample)}
        int  sceAtracGetSoundSample(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E23E3A35|sceAtrac3plus|sceAtracGetNextDecodePosition|ggg|int sceAtracGetNextDecodePosition(int atrac_id, unsigned int * sample_position)}
        int  sceAtracGetNextDecodePosition(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A554A158|sceAtrac3plus|sceAtracGetBitrate|ggg|int sceAtracGetBitrate(int atrac_id, int * bitrate)}
        int  sceAtracGetBitrate(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{FAA4F89B|sceAtrac3plus|sceAtracGetLoopStatus|gggg|int sceAtracGetLoopStatus(int atrac_id, int * loop_number, unsigned int loop_status)}
        int  sceAtracGetLoopStatus(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{868120B5|sceAtrac3plus|sceAtracSetLoopNum|ggg|int sceAtracSetLoopNum(int atrac_id, int loop_number)}
        int  sceAtracSetLoopNum(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2DD3E298|sceAtrac3plus|sceAtracGetBufferInfoForResetting|gggg|int sceAtracGetBufferInfoForResetting(int atrac_id, unsigned int samples, SceAtracBufferInfo * info)}
        int  sceAtracGetBufferInfoForResetting(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{644E5607|sceAtrac3plus|sceAtracResetPlayPosition|ggggg|int sceAtracResetPlayPosition(int atrac_id, unsigned int sample, unsigned int first_buffer_write_byte, unsigned int second_buffer_write_byte)}
        int  sceAtracResetPlayPosition(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E88F759B|sceAtrac3plus|sceAtracGetInternalErrorInfo|ggg|int sceAtracGetInternalErrorInfo(int atrac_id, int * result)}
        int  sceAtracGetInternalErrorInfo(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5622B7C1|sceAtrac3plus|sceAtracSetAA3DataAndGetID|g|??? sceAtracSetAA3DataAndGetID()}
        int  sceAtracSetAA3DataAndGetID()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5CF9D852|sceAtrac3plus|sceAtracSetMOutHalfwayBuffer|g|??? sceAtracSetMOutHalfwayBuffer()}
        int  sceAtracSetMOutHalfwayBuffer()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5DD66588|sceAtrac3plus|sceAtracSetAA3HalfwayBufferAndGetID|g|??? sceAtracSetAA3HalfwayBufferAndGetID()}
        int  sceAtracSetAA3HalfwayBufferAndGetID()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CA3CA3D2|sceAtrac3plus|sceAtracGetBufferInfoForReseting|g|??? sceAtracGetBufferInfoForReseting()}
        int  sceAtracGetBufferInfoForReseting()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D1F59FDB|sceAtrac3plus|sceAtracStartEntry|g|??? sceAtracStartEntry()}
        int  sceAtracStartEntry()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D5C28CC0|sceAtrac3plus|sceAtracEndEntry|g|??? sceAtracEndEntry()}
        int  sceAtracEndEntry()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9CD7DE03|sceAtrac3plus|sceAtracSetMOutHalfwayBufferAndGetID|g|??? sceAtracSetMOutHalfwayBufferAndGetID()}
        int  sceAtracSetMOutHalfwayBufferAndGetID()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceAtrac3plus|sceATRAC3plus_Library|libatrac3plus.prx}
}

extern "C" bool __cdecl sceAtrac3plus$Init() { return hle::sceAtrac3plus::Init(); }
extern "C" bool __cdecl sceAtrac3plus$Fini() { return hle::sceAtrac3plus::Fini(); }
extern "C" void __cdecl sceAtrac3plus_780F88D1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceAtrac3plus::sceAtracGetAtracID                               >(c); } //@hle:syscall{780F88D1|sceAtrac3plus|sceAtracGetAtracID|gg|int sceAtracGetAtracID(unsigned int codec_type)}
extern "C" void __cdecl sceAtrac3plus_61EB33F5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceAtrac3plus::sceAtracReleaseAtracID                           >(c); } //@hle:syscall{61EB33F5|sceAtrac3plus|sceAtracReleaseAtracID|gg|int sceAtracReleaseAtracID(int atrac_id)}
extern "C" void __cdecl sceAtrac3plus_132F1ECA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracReinit                                   >(c); } //@hle:syscall{132F1ECA|sceAtrac3plus|sceAtracReinit|ggg|int sceAtracReinit(int at3_entry, int at3plus_entry)}
extern "C" void __cdecl sceAtrac3plus_0E2A73AB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAtrac3plus::sceAtracSetData                                  >(c); } //@hle:syscall{0E2A73AB|sceAtrac3plus|sceAtracSetData|gggg|int sceAtracSetData(int atrac_id, unsigned char * buffer_address, unsigned int buffer_size)}
extern "C" void __cdecl sceAtrac3plus_3F6E26B5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceAtrac3plus::sceAtracSetHalfwayBuffer                         >(c); } //@hle:syscall{3F6E26B5|sceAtrac3plus|sceAtracSetHalfwayBuffer|ggggg|int sceAtracSetHalfwayBuffer(int atrac_id, unsigned char * buffer_address, unsigned int read_bytes, unsigned int buffer_size)}
extern "C" void __cdecl sceAtrac3plus_7A20E7AF(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracSetDataAndGetID                          >(c); } //@hle:syscall{7A20E7AF|sceAtrac3plus|sceAtracSetDataAndGetID|ggg|int sceAtracSetDataAndGetID(unsigned char * buffer_address, unsigned int buffer_size)}
extern "C" void __cdecl sceAtrac3plus_0FAE370E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAtrac3plus::sceAtracSetHalfwayBufferAndGetID                 >(c); } //@hle:syscall{0FAE370E|sceAtrac3plus|sceAtracSetHalfwayBufferAndGetID|gggg|int sceAtracSetHalfwayBufferAndGetID(unsigned char * buffer_address, unsigned int read_bytes, unsigned int buffer_size)}
extern "C" void __cdecl sceAtrac3plus_6A8C3CD5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::sceAtrac3plus::sceAtracDecodeData                               >(c); } //@hle:syscall{6A8C3CD5|sceAtrac3plus|sceAtracDecodeData|gggggg|int sceAtracDecodeData(int atrac_id, short * sample_buffer, unsigned int * sample_count, unsigned int * finish_flag, int * remaining_frames)}
extern "C" void __cdecl sceAtrac3plus_5D268707(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceAtrac3plus::sceAtracGetStreamDataInfo                        >(c); } //@hle:syscall{5D268707|sceAtrac3plus|sceAtracGetStreamDataInfo|ggggg|int sceAtracGetStreamDataInfo(int atrac_id, unsigned char * * buffer_address, unsigned int writable_bytes, unsigned int read_position)}
extern "C" void __cdecl sceAtrac3plus_7DB31251(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracAddStreamData                            >(c); } //@hle:syscall{7DB31251|sceAtrac3plus|sceAtracAddStreamData|ggg|int sceAtracAddStreamData(int atrac_id, unsigned int bytes)}
extern "C" void __cdecl sceAtrac3plus_83E85EA0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAtrac3plus::sceAtracGetSecondBufferInfo                      >(c); } //@hle:syscall{83E85EA0|sceAtrac3plus|sceAtracGetSecondBufferInfo|gggg|int sceAtracGetSecondBufferInfo(int atrac_id, unsigned int * position, unsigned int * bytes)}
extern "C" void __cdecl sceAtrac3plus_83BF7AFD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAtrac3plus::sceAtracSetSecondBuffer                          >(c); } //@hle:syscall{83BF7AFD|sceAtrac3plus|sceAtracSetSecondBuffer|gggg|int sceAtracSetSecondBuffer(int atrac_id, unsigned char * second_buffer_address, unsigned int second_buffer_size)}
extern "C" void __cdecl sceAtrac3plus_ECA32A99(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceAtrac3plus::sceAtracIsSecondBufferNeeded                     >(c); } //@hle:syscall{ECA32A99|sceAtrac3plus|sceAtracIsSecondBufferNeeded|gg|int sceAtracIsSecondBufferNeeded(int atrac_id)}
extern "C" void __cdecl sceAtrac3plus_9AE849A7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracGetRemainFrame                           >(c); } //@hle:syscall{9AE849A7|sceAtrac3plus|sceAtracGetRemainFrame|ggg|int sceAtracGetRemainFrame(int atrac_id, int * remaining_frames)}
extern "C" void __cdecl sceAtrac3plus_31668BAA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracGetChannel                               >(c); } //@hle:syscall{31668BAA|sceAtrac3plus|sceAtracGetChannel|ggg|int sceAtracGetChannel(int atrac_id, int * channel)}
extern "C" void __cdecl sceAtrac3plus_B3B5D042(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracGetOutputChannel                         >(c); } //@hle:syscall{B3B5D042|sceAtrac3plus|sceAtracGetOutputChannel|ggg|int sceAtracGetOutputChannel(int atrac_id, int * channel)}
extern "C" void __cdecl sceAtrac3plus_D6A5F2F7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracGetMaxSample                             >(c); } //@hle:syscall{D6A5F2F7|sceAtrac3plus|sceAtracGetMaxSample|ggg|int sceAtracGetMaxSample(int atrac_id, int * max_sample)}
extern "C" void __cdecl sceAtrac3plus_36FAABFB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracGetNextSample                            >(c); } //@hle:syscall{36FAABFB|sceAtrac3plus|sceAtracGetNextSample|ggg|int sceAtracGetNextSample(int atrac_id, int * next_sample)}
extern "C" void __cdecl sceAtrac3plus_A2BBA8BE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceAtrac3plus::sceAtracGetSoundSample                           >(c); } //@hle:syscall{A2BBA8BE|sceAtrac3plus|sceAtracGetSoundSample|ggggg|int sceAtracGetSoundSample(int atrac_id, int * end_sample, int * loop_start_sample, int * loop_end_sample)}
extern "C" void __cdecl sceAtrac3plus_E23E3A35(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracGetNextDecodePosition                    >(c); } //@hle:syscall{E23E3A35|sceAtrac3plus|sceAtracGetNextDecodePosition|ggg|int sceAtracGetNextDecodePosition(int atrac_id, unsigned int * sample_position)}
extern "C" void __cdecl sceAtrac3plus_A554A158(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracGetBitrate                               >(c); } //@hle:syscall{A554A158|sceAtrac3plus|sceAtracGetBitrate|ggg|int sceAtracGetBitrate(int atrac_id, int * bitrate)}
extern "C" void __cdecl sceAtrac3plus_FAA4F89B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAtrac3plus::sceAtracGetLoopStatus                            >(c); } //@hle:syscall{FAA4F89B|sceAtrac3plus|sceAtracGetLoopStatus|gggg|int sceAtracGetLoopStatus(int atrac_id, int * loop_number, unsigned int loop_status)}
extern "C" void __cdecl sceAtrac3plus_868120B5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracSetLoopNum                               >(c); } //@hle:syscall{868120B5|sceAtrac3plus|sceAtracSetLoopNum|ggg|int sceAtracSetLoopNum(int atrac_id, int loop_number)}
extern "C" void __cdecl sceAtrac3plus_2DD3E298(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAtrac3plus::sceAtracGetBufferInfoForResetting                >(c); } //@hle:syscall{2DD3E298|sceAtrac3plus|sceAtracGetBufferInfoForResetting|gggg|int sceAtracGetBufferInfoForResetting(int atrac_id, unsigned int samples, SceAtracBufferInfo * info)}
extern "C" void __cdecl sceAtrac3plus_644E5607(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceAtrac3plus::sceAtracResetPlayPosition                        >(c); } //@hle:syscall{644E5607|sceAtrac3plus|sceAtracResetPlayPosition|ggggg|int sceAtracResetPlayPosition(int atrac_id, unsigned int sample, unsigned int first_buffer_write_byte, unsigned int second_buffer_write_byte)}
extern "C" void __cdecl sceAtrac3plus_E88F759B(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAtrac3plus::sceAtracGetInternalErrorInfo                     >(c); } //@hle:syscall{E88F759B|sceAtrac3plus|sceAtracGetInternalErrorInfo|ggg|int sceAtracGetInternalErrorInfo(int atrac_id, int * result)}
extern "C" void __cdecl sceAtrac3plus_5622B7C1(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAtrac3plus::sceAtracSetAA3DataAndGetID                       >(c); } //@hle:syscall{5622B7C1|sceAtrac3plus|sceAtracSetAA3DataAndGetID|g|??? sceAtracSetAA3DataAndGetID()}
extern "C" void __cdecl sceAtrac3plus_5CF9D852(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAtrac3plus::sceAtracSetMOutHalfwayBuffer                     >(c); } //@hle:syscall{5CF9D852|sceAtrac3plus|sceAtracSetMOutHalfwayBuffer|g|??? sceAtracSetMOutHalfwayBuffer()}
extern "C" void __cdecl sceAtrac3plus_5DD66588(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAtrac3plus::sceAtracSetAA3HalfwayBufferAndGetID              >(c); } //@hle:syscall{5DD66588|sceAtrac3plus|sceAtracSetAA3HalfwayBufferAndGetID|g|??? sceAtracSetAA3HalfwayBufferAndGetID()}
extern "C" void __cdecl sceAtrac3plus_CA3CA3D2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAtrac3plus::sceAtracGetBufferInfoForReseting                 >(c); } //@hle:syscall{CA3CA3D2|sceAtrac3plus|sceAtracGetBufferInfoForReseting|g|??? sceAtracGetBufferInfoForReseting()}
extern "C" void __cdecl sceAtrac3plus_D1F59FDB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAtrac3plus::sceAtracStartEntry                               >(c); } //@hle:syscall{D1F59FDB|sceAtrac3plus|sceAtracStartEntry|g|??? sceAtracStartEntry()}
extern "C" void __cdecl sceAtrac3plus_D5C28CC0(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAtrac3plus::sceAtracEndEntry                                 >(c); } //@hle:syscall{D5C28CC0|sceAtrac3plus|sceAtracEndEntry|g|??? sceAtracEndEntry()}
extern "C" void __cdecl sceAtrac3plus_9CD7DE03(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAtrac3plus::sceAtracSetMOutHalfwayBufferAndGetID             >(c); } //@hle:syscall{9CD7DE03|sceAtrac3plus|sceAtracSetMOutHalfwayBufferAndGetID|g|??? sceAtracSetMOutHalfwayBufferAndGetID()}