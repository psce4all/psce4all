//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#ifndef hle_sc_sascore_prx_sceSasCore_h__
#define hle_sc_sascore_prx_sceSasCore_h__

namespace hle
{
    namespace sceSasCore //@hle:library-start{sceSasCore|sceSAScore|sc_sascore.prx}
    {
        //@hle:function{42778A9F|sceSasCore|__sceSasInit|gggggg|int __sceSasInit(void * core, unsigned int grain, int max_voices, int output_mode, int sample_rate)}
        extern int  __sceSasInit(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{A3589D81|sceSasCore|__sceSasCore|ggg|int __sceSasCore(void * core, short * sample_buffer)}
        extern int  __sceSasCore(u32 $a0, u32 $a1);
        //@hle:function{50A14DFC|sceSasCore|__sceSasCoreWithMix|ggggg|int __sceSasCoreWithMix(void * core, short * sample_buffer, int left_volume, int right_volume)}
        extern int  __sceSasCoreWithMix(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{76F01ACA|sceSasCore|__sceSasSetKeyOn|ggg|int __sceSasSetKeyOn(void * core, int voice)}
        extern int  __sceSasSetKeyOn(u32 $a0, u32 $a1);
        //@hle:function{A0CF2FA4|sceSasCore|__sceSasSetKeyOff|ggg|int __sceSasSetKeyOff(void * core, int voice)}
        extern int  __sceSasSetKeyOff(u32 $a0, u32 $a1);
        //@hle:function{787D04D5|sceSasCore|__sceSasSetPause|gggg|int __sceSasSetPause(void * core, int voice, unsigned int pause_flags)}
        extern int  __sceSasSetPause(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{2C8E6AB3|sceSasCore|__sceSasGetPauseFlag|gg|int __sceSasGetPauseFlag(void * core)}
        extern int  __sceSasGetPauseFlag(u32 $a0);
        //@hle:function{440CA7D8|sceSasCore|__sceSasSetVolume|ggggggg|int __sceSasSetVolume(void * core, int voice, int left_dry_volume, int right_dry_volume, int wet_left_volume, int right_wet_volume)}
        extern int  __sceSasSetVolume(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5);
        //@hle:function{AD84D37F|sceSasCore|__sceSasSetPitch|gggg|int __sceSasSetPitch(void * core, int voice, int pitch)}
        extern int  __sceSasSetPitch(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{99944089|sceSasCore|__sceSasSetVoice|gggggg|int __sceSasSetVoice(void * core, int voice, void const * vag_buffer, unsigned int size, int loop_flag)}
        extern int  __sceSasSetVoice(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{B7660A23|sceSasCore|__sceSasSetNoise|gggg|int __sceSasSetNoise(void * core, int voice, unsigned int clock)}
        extern int  __sceSasSetNoise(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{D5EBBBCD|sceSasCore|__sceSasSetSteepWave|gggg|int __sceSasSetSteepWave(void * core, int voice, int percent)}
        extern int  __sceSasSetSteepWave(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{A232CBE6|sceSasCore|__sceSasSetTrianglarWave|gggg|int __sceSasSetTrianglarWave(void * core, int voice, int percent)}
        extern int  __sceSasSetTrianglarWave(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{E1CD9561|sceSasCore|__sceSasSetVoicePCM|gggggg|int __sceSasSetVoicePCM(void * core, int voice, void const * pcm_buffer, unsigned int size, int loop_size)}
        extern int  __sceSasSetVoicePCM(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4);
        //@hle:function{019B25EB|sceSasCore|__sceSasSetADSR|gggggggg|int __sceSasSetADSR(void * core, int voice, int flags, unsigned int a, unsigned int d, unsigned int s, unsigned int r)}
        extern int  __sceSasSetADSR(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5, u32 $a6);
        //@hle:function{9EC3676A|sceSasCore|__sceSasSetADSRmode|gggggggg|int __sceSasSetADSRmode(void * core, int voice, int flags, int a, int d, int s, int r)}
        extern int  __sceSasSetADSRmode(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5, u32 $a6);
        //@hle:function{5F9529F6|sceSasCore|__sceSasSetSL|gggg|int __sceSasSetSL(void * core, int voice, int sl)}
        extern int  __sceSasSetSL(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{CBCD4F79|sceSasCore|__sceSasSetSimpleADSR|ggggg|int __sceSasSetSimpleADSR(void * core, int voice, int adsr1, int adsr2)}
        extern int  __sceSasSetSimpleADSR(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{68A46B95|sceSasCore|__sceSasGetEndFlag|gg|unsigned int __sceSasGetEndFlag(void * core)}
        extern int  __sceSasGetEndFlag(u32 $a0);
        //@hle:function{74AE582A|sceSasCore|__sceSasGetEnvelopeHeight|ggg|int __sceSasGetEnvelopeHeight(void * core, int voice)}
        extern int  __sceSasGetEnvelopeHeight(u32 $a0, u32 $a1);
        //@hle:function{07F58C24|sceSasCore|__sceSasGetAllEnvelopeHeights|ggg|int __sceSasGetAllEnvelopeHeights(void * core, int * buffer)}
        extern int  __sceSasGetAllEnvelopeHeights(u32 $a0, u32 $a1);
        //@hle:function{D1E0A01E|sceSasCore|__sceSasSetGrain|ggg|int __sceSasSetGrain(void * core, unsigned int grain)}
        extern int  __sceSasSetGrain(u32 $a0, u32 $a1);
        //@hle:function{BD11B7C2|sceSasCore|__sceSasGetGrain|gg|int __sceSasGetGrain(void * core)}
        extern int  __sceSasGetGrain(u32 $a0);
        //@hle:function{E855BF76|sceSasCore|__sceSasSetOutputmode|ggg|int __sceSasSetOutputmode(void * core, int outputmode)}
        extern int  __sceSasSetOutputmode(u32 $a0, u32 $a1);
        //@hle:function{E175EF66|sceSasCore|__sceSasGetOutputmode|gg|int __sceSasGetOutputmode(void * core)}
        extern int  __sceSasGetOutputmode(u32 $a0);
        //@hle:function{33D4AB37|sceSasCore|__sceSasRevType|ggg|int __sceSasRevType(void * core, int effect_type)}
        extern int  __sceSasRevType(u32 $a0, u32 $a1);
        //@hle:function{267A6DD2|sceSasCore|__sceSasRevParam|gggg|int __sceSasRevParam(void * core, int delay_time, int feedback_level)}
        extern int  __sceSasRevParam(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{D5A229C9|sceSasCore|__sceSasRevEVOL|gggg|int __sceSasRevEVOL(void * core, int left_channel_effect_volume, int right_channel_effect_volume)}
        extern int  __sceSasRevEVOL(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{F983B186|sceSasCore|__sceSasRevVON|gggg|int __sceSasRevVON(void * core, int dry_on_off, int wet_on_off)}
        extern int  __sceSasRevVON(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{4AA9EAD6|sceSasCore|__sceSasSetVoiceATRAC3|gggg|__sceSasSetVoiceATRAC3(void * core, int voice, void * atrac3_context)}
        extern int  __sceSasSetVoiceATRAC3(u32 $a0, u32 $a1, u32 $a2);
        //@hle:function{7497EA85|sceSasCore|__sceSasConcatenateATRAC3|ggggg|int __sceSasConcatenateATRAC3(void * core, int voice, void * optional_atrac3_buffer, unsigned int size)}
        extern int  __sceSasConcatenateATRAC3(u32 $a0, u32 $a1, u32 $a2, u32 $a3);
        //@hle:function{F6107F00|sceSasCore|__sceSasUnsetATRAC3|ggg|int __sceSasUnsetATRAC3(void * core, int voice)}
        extern int  __sceSasUnsetATRAC3(u32 $a0, u32 $a1);
    } //@hle:library-end{sceSasCore|sceSAScore|sc_sascore.prx}
}
#endif