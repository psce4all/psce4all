//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_audio_prx_sceAudio_h__
#define hle_audio_prx_sceAudio_h__

namespace hle
{
    namespace sceAudio //@hle:library-start{sceAudio|sceAudio_Driver|audio.prx}
    {
        //@hle:function{5EC81C55|sceAudio|sceAudioChReserve|gggg|int sceAudioChReserve(int channel, int sample_count, int format)}
        extern int  sceAudioChReserve(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{6FC46853|sceAudio|sceAudioChRelease|gg|int sceAudioChRelease(int channel)}
        extern int  sceAudioChRelease(u32 $a0);
        //@hle:function{8C1009B2|sceAudio|sceAudioOutput|gggg|int sceAudioOutput(int channel, int volume, void * sample_buffer)}
        extern int  sceAudioOutput(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{136CAF51|sceAudio|sceAudioOutputBlocking|gggg|int sceAudioOutputBlocking(int channel, int volume, void * sample_buffer)}
        extern int  sceAudioOutputBlocking(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{E2D56B2D|sceAudio|sceAudioOutputPanned|ggggg|int sceAudioOutputPanned(int channel, int left_volume, int right_volume, void * sample_buffer)}
        extern int  sceAudioOutputPanned(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{13F592BC|sceAudio|sceAudioOutputPannedBlocking|ggggg|int sceAudioOutputPannedBlocking(int channel, int left_volume, int right_volume, void * sample_buffer)}
        extern int  sceAudioOutputPannedBlocking(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{B7E1D8E7|sceAudio|sceAudioChangeChannelVolume|gggg|int sceAudioChangeChannelVolume(int channel, int left_volume, int right_volume)}
        extern int  sceAudioChangeChannelVolume(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{95FD0C2D|sceAudio|sceAudioChangeChannelConfig|ggg|int sceAudioChangeChannelConfig(int channel, int format)}
        extern int  sceAudioChangeChannelConfig(u32 $a0, u32 $a1);
        //@hle:function{CB2E439E|sceAudio|sceAudioSetChannelDataLen|ggg|int sceAudioSetChannelDataLen(int channel, int samplecount)}
        extern int  sceAudioSetChannelDataLen(u32 $a0, u32 $a1);
        //@hle:function{E9D97901|sceAudio|sceAudioGetChannelRestLen|gg|int sceAudioGetChannelRestLen(int channel)}
        extern int  sceAudioGetChannelRestLen(u32 $a0);
        //@hle:function{B011922F|sceAudio|sceAudioGetChannelRestLength|gg|int sceAudioGetChannelRestLength(int channel)}
        extern int  sceAudioGetChannelRestLength(u32 $a0);
        //@hle:function{38553111|sceAudio|sceAudioSRCChReserve|gggg|int sceAudioSRCChReserve(int sample_count, int frequency, int channel_count)}
        extern int  sceAudioSRCChReserve(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{5C37C0AE|sceAudio|sceAudioSRCChRelease|g|int sceAudioSRCChRelease(void)}
        extern int  sceAudioSRCChRelease();
        //@hle:function{E0727056|sceAudio|sceAudioSRCOutputBlocking|ggg|int sceAudioSRCOutputBlocking(int volume, void * sample_buffer)}
        extern int  sceAudioSRCOutputBlocking(u32 $a0, u32 $a1);
        //@hle:function{01562BA3|sceAudio|sceAudioOutput2Reserve|gg|int sceAudioOutput2Reserve(int sample_count)}
        extern int  sceAudioOutput2Reserve(u32 $a0);
        //@hle:function{43196845|sceAudio|sceAudioOutput2Release|g|int sceAudioOutput2Release(void)}
        extern int  sceAudioOutput2Release();
        //@hle:function{2D53F36E|sceAudio|sceAudioOutput2OutputBlocking|ggg|int sceAudioOutput2OutputBlocking(int volume, void * sample_buffer)}
        extern int  sceAudioOutput2OutputBlocking(u32 $a0, u32 $a1);
        //@hle:function{63F2889C|sceAudio|sceAudioOutput2ChangeLength|gg|int sceAudioOutput2ChangeLength(int sample_count)}
        extern int  sceAudioOutput2ChangeLength(u32 $a0);
        //@hle:function{647CEF33|sceAudio|sceAudioOutput2GetRestSample|g|int sceAudioOutput2GetRestSample(void)}
        extern int  sceAudioOutput2GetRestSample();
        //@hle:function{41EFADE7|sceAudio|sceAudioOneshotOutput|ggggggg|int sceAudioOneshotOutput(int channel, int sample_count, int format, int left_volume, int right_volume, void * sample_buffer)}
        extern int  sceAudioOneshotOutput(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{7DE61688|sceAudio|sceAudioInputInit|g|??? sceAudioInputInit()}
        extern int  sceAudioInputInit();
        //@hle:function{E926D3FB|sceAudio|sceAudioInputInitEx|g|??? sceAudioInputInitEx()}
        extern int  sceAudioInputInitEx();
        //@hle:function{6D4BEC68|sceAudio|sceAudioInput|g|??? sceAudioInput()}
        extern int  sceAudioInput();
        //@hle:function{086E5895|sceAudio|sceAudioInputBlocking|g|??? sceAudioInputBlocking()}
        extern int  sceAudioInputBlocking();
        //@hle:function{A633048E|sceAudio|sceAudioPollInputEnd|g|??? sceAudioPollInputEnd()}
        extern int  sceAudioPollInputEnd();
        //@hle:function{87B2E651|sceAudio|sceAudioWaitInputEnd|g|??? sceAudioWaitInputEnd()}
        extern int  sceAudioWaitInputEnd();
        //@hle:function{A708C6A6|sceAudio|sceAudioGetInputLength|g|??? sceAudioGetInputLength()}
        extern int  sceAudioGetInputLength();
    } //@hle:library-end{sceAudio|sceAudio_Driver|audio.prx}
}
#endif