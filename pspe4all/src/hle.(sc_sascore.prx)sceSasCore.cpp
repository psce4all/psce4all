//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(sc_sascore.prx)sceSasCore.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceSasCore //@hle:library-start{sceSasCore|sceSAScore|sc_sascore.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{42778A9F|sceSasCore|__sceSasInit|gggggg|int __sceSasInit(void * core, unsigned int grain, int max_voices, int output_mode, int sample_rate)}
        int  __sceSasInit(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A3589D81|sceSasCore|__sceSasCore|ggg|int __sceSasCore(void * core, short * sample_buffer)}
        int  __sceSasCore(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{50A14DFC|sceSasCore|__sceSasCoreWithMix|ggggg|int __sceSasCoreWithMix(void * core, short * sample_buffer, int left_volume, int right_volume)}
        int  __sceSasCoreWithMix(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{76F01ACA|sceSasCore|__sceSasSetKeyOn|ggg|int __sceSasSetKeyOn(void * core, int voice)}
        int  __sceSasSetKeyOn(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A0CF2FA4|sceSasCore|__sceSasSetKeyOff|ggg|int __sceSasSetKeyOff(void * core, int voice)}
        int  __sceSasSetKeyOff(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{787D04D5|sceSasCore|__sceSasSetPause|gggg|int __sceSasSetPause(void * core, int voice, unsigned int pause_flags)}
        int  __sceSasSetPause(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2C8E6AB3|sceSasCore|__sceSasGetPauseFlag|gg|int __sceSasGetPauseFlag(void * core)}
        int  __sceSasGetPauseFlag(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{440CA7D8|sceSasCore|__sceSasSetVolume|ggggggg|int __sceSasSetVolume(void * core, int voice, int left_dry_volume, int right_dry_volume, int wet_left_volume, int right_wet_volume)}
        int  __sceSasSetVolume(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{AD84D37F|sceSasCore|__sceSasSetPitch|gggg|int __sceSasSetPitch(void * core, int voice, int pitch)}
        int  __sceSasSetPitch(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{99944089|sceSasCore|__sceSasSetVoice|gggggg|int __sceSasSetVoice(void * core, int voice, void const * vag_buffer, unsigned int size, int loop_flag)}
        int  __sceSasSetVoice(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B7660A23|sceSasCore|__sceSasSetNoise|gggg|int __sceSasSetNoise(void * core, int voice, unsigned int clock)}
        int  __sceSasSetNoise(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D5EBBBCD|sceSasCore|__sceSasSetSteepWave|gggg|int __sceSasSetSteepWave(void * core, int voice, int percent)}
        int  __sceSasSetSteepWave(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A232CBE6|sceSasCore|__sceSasSetTrianglarWave|gggg|int __sceSasSetTrianglarWave(void * core, int voice, int percent)}
        int  __sceSasSetTrianglarWave(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E1CD9561|sceSasCore|__sceSasSetVoicePCM|gggggg|int __sceSasSetVoicePCM(void * core, int voice, void const * pcm_buffer, unsigned int size, int loop_size)}
        int  __sceSasSetVoicePCM(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4)
        {
            (void)($a0, $a1, $a2, $a3, $a4);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{019B25EB|sceSasCore|__sceSasSetADSR|gggggggg|int __sceSasSetADSR(void * core, int voice, int flags, unsigned int a, unsigned int d, unsigned int s, unsigned int r)}
        int  __sceSasSetADSR(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5, u32 $a6)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5, $a6);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{9EC3676A|sceSasCore|__sceSasSetADSRmode|gggggggg|int __sceSasSetADSRmode(void * core, int voice, int flags, int a, int d, int s, int r)}
        int  __sceSasSetADSRmode(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5, u32 $a6)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5, $a6);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5F9529F6|sceSasCore|__sceSasSetSL|gggg|int __sceSasSetSL(void * core, int voice, int sl)}
        int  __sceSasSetSL(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CBCD4F79|sceSasCore|__sceSasSetSimpleADSR|ggggg|int __sceSasSetSimpleADSR(void * core, int voice, int adsr1, int adsr2)}
        int  __sceSasSetSimpleADSR(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{68A46B95|sceSasCore|__sceSasGetEndFlag|gg|unsigned int __sceSasGetEndFlag(void * core)}
        int  __sceSasGetEndFlag(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{74AE582A|sceSasCore|__sceSasGetEnvelopeHeight|ggg|int __sceSasGetEnvelopeHeight(void * core, int voice)}
        int  __sceSasGetEnvelopeHeight(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{07F58C24|sceSasCore|__sceSasGetAllEnvelopeHeights|ggg|int __sceSasGetAllEnvelopeHeights(void * core, int * buffer)}
        int  __sceSasGetAllEnvelopeHeights(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D1E0A01E|sceSasCore|__sceSasSetGrain|ggg|int __sceSasSetGrain(void * core, unsigned int grain)}
        int  __sceSasSetGrain(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{BD11B7C2|sceSasCore|__sceSasGetGrain|gg|int __sceSasGetGrain(void * core)}
        int  __sceSasGetGrain(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E855BF76|sceSasCore|__sceSasSetOutputmode|ggg|int __sceSasSetOutputmode(void * core, int outputmode)}
        int  __sceSasSetOutputmode(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E175EF66|sceSasCore|__sceSasGetOutputmode|gg|int __sceSasGetOutputmode(void * core)}
        int  __sceSasGetOutputmode(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{33D4AB37|sceSasCore|__sceSasRevType|ggg|int __sceSasRevType(void * core, int effect_type)}
        int  __sceSasRevType(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{267A6DD2|sceSasCore|__sceSasRevParam|gggg|int __sceSasRevParam(void * core, int delay_time, int feedback_level)}
        int  __sceSasRevParam(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{D5A229C9|sceSasCore|__sceSasRevEVOL|gggg|int __sceSasRevEVOL(void * core, int left_channel_effect_volume, int right_channel_effect_volume)}
        int  __sceSasRevEVOL(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F983B186|sceSasCore|__sceSasRevVON|gggg|int __sceSasRevVON(void * core, int dry_on_off, int wet_on_off)}
        int  __sceSasRevVON(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{4AA9EAD6|sceSasCore|__sceSasSetVoiceATRAC3|gggg|__sceSasSetVoiceATRAC3(void * core, int voice, void * atrac3_context)}
        int  __sceSasSetVoiceATRAC3(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7497EA85|sceSasCore|__sceSasConcatenateATRAC3|ggggg|int __sceSasConcatenateATRAC3(void * core, int voice, void * optional_atrac3_buffer, unsigned int size)}
        int  __sceSasConcatenateATRAC3(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{F6107F00|sceSasCore|__sceSasUnsetATRAC3|ggg|int __sceSasUnsetATRAC3(void * core, int voice)}
        int  __sceSasUnsetATRAC3(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceSasCore|sceSAScore|sc_sascore.prx}
}

extern "C" bool __cdecl sceSasCore$Init() { return hle::sceSasCore::Init(); }
extern "C" bool __cdecl sceSasCore$Fini() { return hle::sceSasCore::Fini(); }
extern "C" void __cdecl sceSasCore_42778A9F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::sceSasCore::__sceSasInit                                     >(c); } //@hle:syscall{42778A9F|sceSasCore|__sceSasInit|gggggg|int __sceSasInit(void * core, unsigned int grain, int max_voices, int output_mode, int sample_rate)}
extern "C" void __cdecl sceSasCore_A3589D81(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSasCore::__sceSasCore                                     >(c); } //@hle:syscall{A3589D81|sceSasCore|__sceSasCore|ggg|int __sceSasCore(void * core, short * sample_buffer)}
extern "C" void __cdecl sceSasCore_50A14DFC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceSasCore::__sceSasCoreWithMix                              >(c); } //@hle:syscall{50A14DFC|sceSasCore|__sceSasCoreWithMix|ggggg|int __sceSasCoreWithMix(void * core, short * sample_buffer, int left_volume, int right_volume)}
extern "C" void __cdecl sceSasCore_76F01ACA(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSasCore::__sceSasSetKeyOn                                 >(c); } //@hle:syscall{76F01ACA|sceSasCore|__sceSasSetKeyOn|ggg|int __sceSasSetKeyOn(void * core, int voice)}
extern "C" void __cdecl sceSasCore_A0CF2FA4(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSasCore::__sceSasSetKeyOff                                >(c); } //@hle:syscall{A0CF2FA4|sceSasCore|__sceSasSetKeyOff|ggg|int __sceSasSetKeyOff(void * core, int voice)}
extern "C" void __cdecl sceSasCore_787D04D5(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasSetPause                                 >(c); } //@hle:syscall{787D04D5|sceSasCore|__sceSasSetPause|gggg|int __sceSasSetPause(void * core, int voice, unsigned int pause_flags)}
extern "C" void __cdecl sceSasCore_2C8E6AB3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceSasCore::__sceSasGetPauseFlag                             >(c); } //@hle:syscall{2C8E6AB3|sceSasCore|__sceSasGetPauseFlag|gg|int __sceSasGetPauseFlag(void * core)}
extern "C" void __cdecl sceSasCore_440CA7D8(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::sceSasCore::__sceSasSetVolume                                >(c); } //@hle:syscall{440CA7D8|sceSasCore|__sceSasSetVolume|ggggggg|int __sceSasSetVolume(void * core, int voice, int left_dry_volume, int right_dry_volume, int wet_left_volume, int right_wet_volume)}
extern "C" void __cdecl sceSasCore_AD84D37F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasSetPitch                                 >(c); } //@hle:syscall{AD84D37F|sceSasCore|__sceSasSetPitch|gggg|int __sceSasSetPitch(void * core, int voice, int pitch)}
extern "C" void __cdecl sceSasCore_99944089(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::sceSasCore::__sceSasSetVoice                                 >(c); } //@hle:syscall{99944089|sceSasCore|__sceSasSetVoice|gggggg|int __sceSasSetVoice(void * core, int voice, void const * vag_buffer, unsigned int size, int loop_flag)}
extern "C" void __cdecl sceSasCore_B7660A23(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasSetNoise                                 >(c); } //@hle:syscall{B7660A23|sceSasCore|__sceSasSetNoise|gggg|int __sceSasSetNoise(void * core, int voice, unsigned int clock)}
extern "C" void __cdecl sceSasCore_D5EBBBCD(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasSetSteepWave                             >(c); } //@hle:syscall{D5EBBBCD|sceSasCore|__sceSasSetSteepWave|gggg|int __sceSasSetSteepWave(void * core, int voice, int percent)}
extern "C" void __cdecl sceSasCore_A232CBE6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasSetTrianglarWave                         >(c); } //@hle:syscall{A232CBE6|sceSasCore|__sceSasSetTrianglarWave|gggg|int __sceSasSetTrianglarWave(void * core, int voice, int percent)}
extern "C" void __cdecl sceSasCore_E1CD9561(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggg          < hle::sceSasCore::__sceSasSetVoicePCM                              >(c); } //@hle:syscall{E1CD9561|sceSasCore|__sceSasSetVoicePCM|gggggg|int __sceSasSetVoicePCM(void * core, int voice, void const * pcm_buffer, unsigned int size, int loop_size)}
extern "C" void __cdecl sceSasCore_019B25EB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggggg        < hle::sceSasCore::__sceSasSetADSR                                  >(c); } //@hle:syscall{019B25EB|sceSasCore|__sceSasSetADSR|gggggggg|int __sceSasSetADSR(void * core, int voice, int flags, unsigned int a, unsigned int d, unsigned int s, unsigned int r)}
extern "C" void __cdecl sceSasCore_9EC3676A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggggggg        < hle::sceSasCore::__sceSasSetADSRmode                              >(c); } //@hle:syscall{9EC3676A|sceSasCore|__sceSasSetADSRmode|gggggggg|int __sceSasSetADSRmode(void * core, int voice, int flags, int a, int d, int s, int r)}
extern "C" void __cdecl sceSasCore_5F9529F6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasSetSL                                    >(c); } //@hle:syscall{5F9529F6|sceSasCore|__sceSasSetSL|gggg|int __sceSasSetSL(void * core, int voice, int sl)}
extern "C" void __cdecl sceSasCore_CBCD4F79(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceSasCore::__sceSasSetSimpleADSR                            >(c); } //@hle:syscall{CBCD4F79|sceSasCore|__sceSasSetSimpleADSR|ggggg|int __sceSasSetSimpleADSR(void * core, int voice, int adsr1, int adsr2)}
extern "C" void __cdecl sceSasCore_68A46B95(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceSasCore::__sceSasGetEndFlag                               >(c); } //@hle:syscall{68A46B95|sceSasCore|__sceSasGetEndFlag|gg|unsigned int __sceSasGetEndFlag(void * core)}
extern "C" void __cdecl sceSasCore_74AE582A(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSasCore::__sceSasGetEnvelopeHeight                        >(c); } //@hle:syscall{74AE582A|sceSasCore|__sceSasGetEnvelopeHeight|ggg|int __sceSasGetEnvelopeHeight(void * core, int voice)}
extern "C" void __cdecl sceSasCore_07F58C24(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSasCore::__sceSasGetAllEnvelopeHeights                    >(c); } //@hle:syscall{07F58C24|sceSasCore|__sceSasGetAllEnvelopeHeights|ggg|int __sceSasGetAllEnvelopeHeights(void * core, int * buffer)}
extern "C" void __cdecl sceSasCore_D1E0A01E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSasCore::__sceSasSetGrain                                 >(c); } //@hle:syscall{D1E0A01E|sceSasCore|__sceSasSetGrain|ggg|int __sceSasSetGrain(void * core, unsigned int grain)}
extern "C" void __cdecl sceSasCore_BD11B7C2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceSasCore::__sceSasGetGrain                                 >(c); } //@hle:syscall{BD11B7C2|sceSasCore|__sceSasGetGrain|gg|int __sceSasGetGrain(void * core)}
extern "C" void __cdecl sceSasCore_E855BF76(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSasCore::__sceSasSetOutputmode                            >(c); } //@hle:syscall{E855BF76|sceSasCore|__sceSasSetOutputmode|ggg|int __sceSasSetOutputmode(void * core, int outputmode)}
extern "C" void __cdecl sceSasCore_E175EF66(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceSasCore::__sceSasGetOutputmode                            >(c); } //@hle:syscall{E175EF66|sceSasCore|__sceSasGetOutputmode|gg|int __sceSasGetOutputmode(void * core)}
extern "C" void __cdecl sceSasCore_33D4AB37(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSasCore::__sceSasRevType                                  >(c); } //@hle:syscall{33D4AB37|sceSasCore|__sceSasRevType|ggg|int __sceSasRevType(void * core, int effect_type)}
extern "C" void __cdecl sceSasCore_267A6DD2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasRevParam                                 >(c); } //@hle:syscall{267A6DD2|sceSasCore|__sceSasRevParam|gggg|int __sceSasRevParam(void * core, int delay_time, int feedback_level)}
extern "C" void __cdecl sceSasCore_D5A229C9(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasRevEVOL                                  >(c); } //@hle:syscall{D5A229C9|sceSasCore|__sceSasRevEVOL|gggg|int __sceSasRevEVOL(void * core, int left_channel_effect_volume, int right_channel_effect_volume)}
extern "C" void __cdecl sceSasCore_F983B186(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasRevVON                                   >(c); } //@hle:syscall{F983B186|sceSasCore|__sceSasRevVON|gggg|int __sceSasRevVON(void * core, int dry_on_off, int wet_on_off)}
extern "C" void __cdecl sceSasCore_4AA9EAD6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceSasCore::__sceSasSetVoiceATRAC3                           >(c); } //@hle:syscall{4AA9EAD6|sceSasCore|__sceSasSetVoiceATRAC3|gggg|__sceSasSetVoiceATRAC3(void * core, int voice, void * atrac3_context)}
extern "C" void __cdecl sceSasCore_7497EA85(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceSasCore::__sceSasConcatenateATRAC3                        >(c); } //@hle:syscall{7497EA85|sceSasCore|__sceSasConcatenateATRAC3|ggggg|int __sceSasConcatenateATRAC3(void * core, int voice, void * optional_atrac3_buffer, unsigned int size)}
extern "C" void __cdecl sceSasCore_F6107F00(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceSasCore::__sceSasUnsetATRAC3                              >(c); } //@hle:syscall{F6107F00|sceSasCore|__sceSasUnsetATRAC3|ggg|int __sceSasUnsetATRAC3(void * core, int voice)}