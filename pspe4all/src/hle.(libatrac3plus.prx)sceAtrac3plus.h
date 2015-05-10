//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_libatrac3plus_prx_sceAtrac3plus_h__
#define hle_libatrac3plus_prx_sceAtrac3plus_h__

namespace hle
{
    namespace sceAtrac3plus //@hle:library-start{sceAtrac3plus|sceATRAC3plus_Library|libatrac3plus.prx}
    {
        //@hle:function{780F88D1|sceAtrac3plus|sceAtracGetAtracID|gg|int sceAtracGetAtracID(unsigned int codec_type)}
        extern int  sceAtracGetAtracID(u32 $a0);
        //@hle:function{61EB33F5|sceAtrac3plus|sceAtracReleaseAtracID|gg|int sceAtracReleaseAtracID(int atrac_id)}
        extern int  sceAtracReleaseAtracID(u32 $a0);
        //@hle:function{132F1ECA|sceAtrac3plus|sceAtracReinit|ggg|int sceAtracReinit(int at3_entry, int at3plus_entry)}
        extern int  sceAtracReinit(u32 $a0, u32 $a1);
        //@hle:function{0E2A73AB|sceAtrac3plus|sceAtracSetData|gggg|int sceAtracSetData(int atrac_id, unsigned char * buffer_address, unsigned int buffer_size)}
        extern int  sceAtracSetData(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{3F6E26B5|sceAtrac3plus|sceAtracSetHalfwayBuffer|ggggg|int sceAtracSetHalfwayBuffer(int atrac_id, unsigned char * buffer_address, unsigned int read_bytes, unsigned int buffer_size)}
        extern int  sceAtracSetHalfwayBuffer(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{7A20E7AF|sceAtrac3plus|sceAtracSetDataAndGetID|ggg|int sceAtracSetDataAndGetID(unsigned char * buffer_address, unsigned int buffer_size)}
        extern int  sceAtracSetDataAndGetID(u32 $a0, u32 $a1);
        //@hle:function{0FAE370E|sceAtrac3plus|sceAtracSetHalfwayBufferAndGetID|gggg|int sceAtracSetHalfwayBufferAndGetID(unsigned char * buffer_address, unsigned int read_bytes, unsigned int buffer_size)}
        extern int  sceAtracSetHalfwayBufferAndGetID(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{6A8C3CD5|sceAtrac3plus|sceAtracDecodeData|gggggg|int sceAtracDecodeData(int atrac_id, short * sample_buffer, unsigned int * sample_count, unsigned int * finish_flag, int * remaining_frames)}
        extern int  sceAtracDecodeData(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{5D268707|sceAtrac3plus|sceAtracGetStreamDataInfo|ggggg|int sceAtracGetStreamDataInfo(int atrac_id, unsigned char * * buffer_address, unsigned int writable_bytes, unsigned int read_position)}
        extern int  sceAtracGetStreamDataInfo(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{7DB31251|sceAtrac3plus|sceAtracAddStreamData|ggg|int sceAtracAddStreamData(int atrac_id, unsigned int bytes)}
        extern int  sceAtracAddStreamData(u32 $a0, u32 $a1);
        //@hle:function{83E85EA0|sceAtrac3plus|sceAtracGetSecondBufferInfo|gggg|int sceAtracGetSecondBufferInfo(int atrac_id, unsigned int * position, unsigned int * bytes)}
        extern int  sceAtracGetSecondBufferInfo(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{83BF7AFD|sceAtrac3plus|sceAtracSetSecondBuffer|gggg|int sceAtracSetSecondBuffer(int atrac_id, unsigned char * second_buffer_address, unsigned int second_buffer_size)}
        extern int  sceAtracSetSecondBuffer(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{ECA32A99|sceAtrac3plus|sceAtracIsSecondBufferNeeded|gg|int sceAtracIsSecondBufferNeeded(int atrac_id)}
        extern int  sceAtracIsSecondBufferNeeded(u32 $a0);
        //@hle:function{9AE849A7|sceAtrac3plus|sceAtracGetRemainFrame|ggg|int sceAtracGetRemainFrame(int atrac_id, int * remaining_frames)}
        extern int  sceAtracGetRemainFrame(u32 $a0, u32 $a1);
        //@hle:function{31668BAA|sceAtrac3plus|sceAtracGetChannel|ggg|int sceAtracGetChannel(int atrac_id, int * channel)}
        extern int  sceAtracGetChannel(u32 $a0, u32 $a1);
        //@hle:function{B3B5D042|sceAtrac3plus|sceAtracGetOutputChannel|ggg|int sceAtracGetOutputChannel(int atrac_id, int * channel)}
        extern int  sceAtracGetOutputChannel(u32 $a0, u32 $a1);
        //@hle:function{D6A5F2F7|sceAtrac3plus|sceAtracGetMaxSample|ggg|int sceAtracGetMaxSample(int atrac_id, int * max_sample)}
        extern int  sceAtracGetMaxSample(u32 $a0, u32 $a1);
        //@hle:function{36FAABFB|sceAtrac3plus|sceAtracGetNextSample|ggg|int sceAtracGetNextSample(int atrac_id, int * next_sample)}
        extern int  sceAtracGetNextSample(u32 $a0, u32 $a1);
        //@hle:function{A2BBA8BE|sceAtrac3plus|sceAtracGetSoundSample|ggggg|int sceAtracGetSoundSample(int atrac_id, int * end_sample, int * loop_start_sample, int * loop_end_sample)}
        extern int  sceAtracGetSoundSample(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{E23E3A35|sceAtrac3plus|sceAtracGetNextDecodePosition|ggg|int sceAtracGetNextDecodePosition(int atrac_id, unsigned int * sample_position)}
        extern int  sceAtracGetNextDecodePosition(u32 $a0, u32 $a1);
        //@hle:function{A554A158|sceAtrac3plus|sceAtracGetBitrate|ggg|int sceAtracGetBitrate(int atrac_id, int * bitrate)}
        extern int  sceAtracGetBitrate(u32 $a0, u32 $a1);
        //@hle:function{FAA4F89B|sceAtrac3plus|sceAtracGetLoopStatus|gggg|int sceAtracGetLoopStatus(int atrac_id, int * loop_number, unsigned int loop_status)}
        extern int  sceAtracGetLoopStatus(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{868120B5|sceAtrac3plus|sceAtracSetLoopNum|ggg|int sceAtracSetLoopNum(int atrac_id, int loop_number)}
        extern int  sceAtracSetLoopNum(u32 $a0, u32 $a1);
        //@hle:function{2DD3E298|sceAtrac3plus|sceAtracGetBufferInfoForResetting|gggg|int sceAtracGetBufferInfoForResetting(int atrac_id, unsigned int samples, SceAtracBufferInfo * info)}
        extern int  sceAtracGetBufferInfoForResetting(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{644E5607|sceAtrac3plus|sceAtracResetPlayPosition|ggggg|int sceAtracResetPlayPosition(int atrac_id, unsigned int sample, unsigned int first_buffer_write_byte, unsigned int second_buffer_write_byte)}
        extern int  sceAtracResetPlayPosition(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{E88F759B|sceAtrac3plus|sceAtracGetInternalErrorInfo|ggg|int sceAtracGetInternalErrorInfo(int atrac_id, int * result)}
        extern int  sceAtracGetInternalErrorInfo(u32 $a0, u32 $a1);
        //@hle:function{5622B7C1|sceAtrac3plus|sceAtracSetAA3DataAndGetID|g|??? sceAtracSetAA3DataAndGetID()}
        extern int  sceAtracSetAA3DataAndGetID();
        //@hle:function{5CF9D852|sceAtrac3plus|sceAtracSetMOutHalfwayBuffer|g|??? sceAtracSetMOutHalfwayBuffer()}
        extern int  sceAtracSetMOutHalfwayBuffer();
        //@hle:function{5DD66588|sceAtrac3plus|sceAtracSetAA3HalfwayBufferAndGetID|g|??? sceAtracSetAA3HalfwayBufferAndGetID()}
        extern int  sceAtracSetAA3HalfwayBufferAndGetID();
        //@hle:function{CA3CA3D2|sceAtrac3plus|sceAtracGetBufferInfoForReseting|g|??? sceAtracGetBufferInfoForReseting()}
        extern int  sceAtracGetBufferInfoForReseting();
        //@hle:function{D1F59FDB|sceAtrac3plus|sceAtracStartEntry|g|??? sceAtracStartEntry()}
        extern int  sceAtracStartEntry();
        //@hle:function{D5C28CC0|sceAtrac3plus|sceAtracEndEntry|g|??? sceAtracEndEntry()}
        extern int  sceAtracEndEntry();
        //@hle:function{9CD7DE03|sceAtrac3plus|sceAtracSetMOutHalfwayBufferAndGetID|g|??? sceAtracSetMOutHalfwayBufferAndGetID()}
        extern int  sceAtracSetMOutHalfwayBufferAndGetID();
    } //@hle:library-end{sceAtrac3plus|sceATRAC3plus_Library|libatrac3plus.prx}
}
#endif