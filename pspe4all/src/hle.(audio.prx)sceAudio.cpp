//////////////////////////////////////////////////////////////////
//// This file is auto-generated from pspe4all-nidgen version 0.3
//////////////////////////////////////////////////////////////////
#include "hle.(audio.prx)sceAudio.h"
#include "hle.syscalls.FunctionWrappers.h"

#include "lle.cpu(Allegrex).Context.h"

namespace hle
{
    namespace sceAudio //@hle:library-start{sceAudio|sceAudio_Driver|audio.prx}
    {
        bool Init()
        {
            return true;
        }
        bool Fini()
        {
            return true;
        }

        //@hle:function{5EC81C55|sceAudio|sceAudioChReserve|gggg|int sceAudioChReserve(int channel, int sample_count, int format)}
        int  sceAudioChReserve(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6FC46853|sceAudio|sceAudioChRelease|gg|int sceAudioChRelease(int channel)}
        int  sceAudioChRelease(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{8C1009B2|sceAudio|sceAudioOutput|gggg|int sceAudioOutput(int channel, int volume, void * sample_buffer)}
        int  sceAudioOutput(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{136CAF51|sceAudio|sceAudioOutputBlocking|gggg|int sceAudioOutputBlocking(int channel, int volume, void * sample_buffer)}
        int  sceAudioOutputBlocking(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E2D56B2D|sceAudio|sceAudioOutputPanned|ggggg|int sceAudioOutputPanned(int channel, int left_volume, int right_volume, void * sample_buffer)}
        int  sceAudioOutputPanned(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{13F592BC|sceAudio|sceAudioOutputPannedBlocking|ggggg|int sceAudioOutputPannedBlocking(int channel, int left_volume, int right_volume, void * sample_buffer)}
        int  sceAudioOutputPannedBlocking(u32 $a0, u32 $a1, u32 $a2, u32 $a3)
        {
            (void)($a0, $a1, $a2, $a3);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B7E1D8E7|sceAudio|sceAudioChangeChannelVolume|gggg|int sceAudioChangeChannelVolume(int channel, int left_volume, int right_volume)}
        int  sceAudioChangeChannelVolume(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{95FD0C2D|sceAudio|sceAudioChangeChannelConfig|ggg|int sceAudioChangeChannelConfig(int channel, int format)}
        int  sceAudioChangeChannelConfig(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{CB2E439E|sceAudio|sceAudioSetChannelDataLen|ggg|int sceAudioSetChannelDataLen(int channel, int samplecount)}
        int  sceAudioSetChannelDataLen(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E9D97901|sceAudio|sceAudioGetChannelRestLen|gg|int sceAudioGetChannelRestLen(int channel)}
        int  sceAudioGetChannelRestLen(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{B011922F|sceAudio|sceAudioGetChannelRestLength|gg|int sceAudioGetChannelRestLength(int channel)}
        int  sceAudioGetChannelRestLength(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{38553111|sceAudio|sceAudioSRCChReserve|gggg|int sceAudioSRCChReserve(int sample_count, int frequency, int channel_count)}
        int  sceAudioSRCChReserve(u32 $a0, u32 $a1, u32 $a2)
        {
            (void)($a0, $a1, $a2);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{5C37C0AE|sceAudio|sceAudioSRCChRelease|g|int sceAudioSRCChRelease(void)}
        int  sceAudioSRCChRelease()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E0727056|sceAudio|sceAudioSRCOutputBlocking|ggg|int sceAudioSRCOutputBlocking(int volume, void * sample_buffer)}
        int  sceAudioSRCOutputBlocking(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{01562BA3|sceAudio|sceAudioOutput2Reserve|gg|int sceAudioOutput2Reserve(int sample_count)}
        int  sceAudioOutput2Reserve(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{43196845|sceAudio|sceAudioOutput2Release|g|int sceAudioOutput2Release(void)}
        int  sceAudioOutput2Release()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{2D53F36E|sceAudio|sceAudioOutput2OutputBlocking|ggg|int sceAudioOutput2OutputBlocking(int volume, void * sample_buffer)}
        int  sceAudioOutput2OutputBlocking(u32 $a0, u32 $a1)
        {
            (void)($a0, $a1);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{63F2889C|sceAudio|sceAudioOutput2ChangeLength|gg|int sceAudioOutput2ChangeLength(int sample_count)}
        int  sceAudioOutput2ChangeLength(u32 $a0)
        {
            (void)($a0);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{647CEF33|sceAudio|sceAudioOutput2GetRestSample|g|int sceAudioOutput2GetRestSample(void)}
        int  sceAudioOutput2GetRestSample()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{41EFADE7|sceAudio|sceAudioOneshotOutput|ggggggg|int sceAudioOneshotOutput(int channel, int sample_count, int format, int left_volume, int right_volume, void * sample_buffer)}
        int  sceAudioOneshotOutput(u32 $a0, u32 $a1, u32 $a2, u32 $a3, u32 $a4, u32 $a5)
        {
            (void)($a0, $a1, $a2, $a3, $a4, $a5);
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{7DE61688|sceAudio|sceAudioInputInit|g|??? sceAudioInputInit()}
        int  sceAudioInputInit()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{E926D3FB|sceAudio|sceAudioInputInitEx|g|??? sceAudioInputInitEx()}
        int  sceAudioInputInitEx()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{6D4BEC68|sceAudio|sceAudioInput|g|??? sceAudioInput()}
        int  sceAudioInput()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{086E5895|sceAudio|sceAudioInputBlocking|g|??? sceAudioInputBlocking()}
        int  sceAudioInputBlocking()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A633048E|sceAudio|sceAudioPollInputEnd|g|??? sceAudioPollInputEnd()}
        int  sceAudioPollInputEnd()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{87B2E651|sceAudio|sceAudioWaitInputEnd|g|??? sceAudioWaitInputEnd()}
        int  sceAudioWaitInputEnd()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
        //@hle:function{A708C6A6|sceAudio|sceAudioGetInputLength|g|??? sceAudioGetInputLength()}
        int  sceAudioGetInputLength()
        {
            int $v0;
            $v0 = 0;
            return $v0;
        }
    } //@hle:library-end{sceAudio|sceAudio_Driver|audio.prx}
}

extern "C" bool __cdecl sceAudio$Init() { return hle::sceAudio::Init(); }
extern "C" bool __cdecl sceAudio$Fini() { return hle::sceAudio::Fini(); }
extern "C" void __cdecl sceAudio_5EC81C55(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAudio::sceAudioChReserve                                >(c); } //@hle:syscall{5EC81C55|sceAudio|sceAudioChReserve|gggg|int sceAudioChReserve(int channel, int sample_count, int format)}
extern "C" void __cdecl sceAudio_6FC46853(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceAudio::sceAudioChRelease                                >(c); } //@hle:syscall{6FC46853|sceAudio|sceAudioChRelease|gg|int sceAudioChRelease(int channel)}
extern "C" void __cdecl sceAudio_8C1009B2(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAudio::sceAudioOutput                                   >(c); } //@hle:syscall{8C1009B2|sceAudio|sceAudioOutput|gggg|int sceAudioOutput(int channel, int volume, void * sample_buffer)}
extern "C" void __cdecl sceAudio_136CAF51(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAudio::sceAudioOutputBlocking                           >(c); } //@hle:syscall{136CAF51|sceAudio|sceAudioOutputBlocking|gggg|int sceAudioOutputBlocking(int channel, int volume, void * sample_buffer)}
extern "C" void __cdecl sceAudio_E2D56B2D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceAudio::sceAudioOutputPanned                             >(c); } //@hle:syscall{E2D56B2D|sceAudio|sceAudioOutputPanned|ggggg|int sceAudioOutputPanned(int channel, int left_volume, int right_volume, void * sample_buffer)}
extern "C" void __cdecl sceAudio_13F592BC(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggg           < hle::sceAudio::sceAudioOutputPannedBlocking                     >(c); } //@hle:syscall{13F592BC|sceAudio|sceAudioOutputPannedBlocking|ggggg|int sceAudioOutputPannedBlocking(int channel, int left_volume, int right_volume, void * sample_buffer)}
extern "C" void __cdecl sceAudio_B7E1D8E7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAudio::sceAudioChangeChannelVolume                      >(c); } //@hle:syscall{B7E1D8E7|sceAudio|sceAudioChangeChannelVolume|gggg|int sceAudioChangeChannelVolume(int channel, int left_volume, int right_volume)}
extern "C" void __cdecl sceAudio_95FD0C2D(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAudio::sceAudioChangeChannelConfig                      >(c); } //@hle:syscall{95FD0C2D|sceAudio|sceAudioChangeChannelConfig|ggg|int sceAudioChangeChannelConfig(int channel, int format)}
extern "C" void __cdecl sceAudio_CB2E439E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAudio::sceAudioSetChannelDataLen                        >(c); } //@hle:syscall{CB2E439E|sceAudio|sceAudioSetChannelDataLen|ggg|int sceAudioSetChannelDataLen(int channel, int samplecount)}
extern "C" void __cdecl sceAudio_E9D97901(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceAudio::sceAudioGetChannelRestLen                        >(c); } //@hle:syscall{E9D97901|sceAudio|sceAudioGetChannelRestLen|gg|int sceAudioGetChannelRestLen(int channel)}
extern "C" void __cdecl sceAudio_B011922F(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceAudio::sceAudioGetChannelRestLength                     >(c); } //@hle:syscall{B011922F|sceAudio|sceAudioGetChannelRestLength|gg|int sceAudioGetChannelRestLength(int channel)}
extern "C" void __cdecl sceAudio_38553111(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gggg            < hle::sceAudio::sceAudioSRCChReserve                             >(c); } //@hle:syscall{38553111|sceAudio|sceAudioSRCChReserve|gggg|int sceAudioSRCChReserve(int sample_count, int frequency, int channel_count)}
extern "C" void __cdecl sceAudio_5C37C0AE(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioSRCChRelease                             >(c); } //@hle:syscall{5C37C0AE|sceAudio|sceAudioSRCChRelease|g|int sceAudioSRCChRelease(void)}
extern "C" void __cdecl sceAudio_E0727056(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAudio::sceAudioSRCOutputBlocking                        >(c); } //@hle:syscall{E0727056|sceAudio|sceAudioSRCOutputBlocking|ggg|int sceAudioSRCOutputBlocking(int volume, void * sample_buffer)}
extern "C" void __cdecl sceAudio_01562BA3(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceAudio::sceAudioOutput2Reserve                           >(c); } //@hle:syscall{01562BA3|sceAudio|sceAudioOutput2Reserve|gg|int sceAudioOutput2Reserve(int sample_count)}
extern "C" void __cdecl sceAudio_43196845(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioOutput2Release                           >(c); } //@hle:syscall{43196845|sceAudio|sceAudioOutput2Release|g|int sceAudioOutput2Release(void)}
extern "C" void __cdecl sceAudio_2D53F36E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggg             < hle::sceAudio::sceAudioOutput2OutputBlocking                    >(c); } //@hle:syscall{2D53F36E|sceAudio|sceAudioOutput2OutputBlocking|ggg|int sceAudioOutput2OutputBlocking(int volume, void * sample_buffer)}
extern "C" void __cdecl sceAudio_63F2889C(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$gg              < hle::sceAudio::sceAudioOutput2ChangeLength                      >(c); } //@hle:syscall{63F2889C|sceAudio|sceAudioOutput2ChangeLength|gg|int sceAudioOutput2ChangeLength(int sample_count)}
extern "C" void __cdecl sceAudio_647CEF33(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioOutput2GetRestSample                     >(c); } //@hle:syscall{647CEF33|sceAudio|sceAudioOutput2GetRestSample|g|int sceAudioOutput2GetRestSample(void)}
extern "C" void __cdecl sceAudio_41EFADE7(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$ggggggg         < hle::sceAudio::sceAudioOneshotOutput                            >(c); } //@hle:syscall{41EFADE7|sceAudio|sceAudioOneshotOutput|ggggggg|int sceAudioOneshotOutput(int channel, int sample_count, int format, int left_volume, int right_volume, void * sample_buffer)}
extern "C" void __cdecl sceAudio_7DE61688(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioInputInit                                >(c); } //@hle:syscall{7DE61688|sceAudio|sceAudioInputInit|g|??? sceAudioInputInit()}
extern "C" void __cdecl sceAudio_E926D3FB(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioInputInitEx                              >(c); } //@hle:syscall{E926D3FB|sceAudio|sceAudioInputInitEx|g|??? sceAudioInputInitEx()}
extern "C" void __cdecl sceAudio_6D4BEC68(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioInput                                    >(c); } //@hle:syscall{6D4BEC68|sceAudio|sceAudioInput|g|??? sceAudioInput()}
extern "C" void __cdecl sceAudio_086E5895(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioInputBlocking                            >(c); } //@hle:syscall{086E5895|sceAudio|sceAudioInputBlocking|g|??? sceAudioInputBlocking()}
extern "C" void __cdecl sceAudio_A633048E(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioPollInputEnd                             >(c); } //@hle:syscall{A633048E|sceAudio|sceAudioPollInputEnd|g|??? sceAudioPollInputEnd()}
extern "C" void __cdecl sceAudio_87B2E651(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioWaitInputEnd                             >(c); } //@hle:syscall{87B2E651|sceAudio|sceAudioWaitInputEnd|g|??? sceAudioWaitInputEnd()}
extern "C" void __cdecl sceAudio_A708C6A6(Allegrex::Context & c) { hle::syscalls::FunctionWrapper$g               < hle::sceAudio::sceAudioGetInputLength                           >(c); } //@hle:syscall{A708C6A6|sceAudio|sceAudioGetInputLength|g|??? sceAudioGetInputLength()}