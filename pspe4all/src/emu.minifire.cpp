/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

// THIS IS A TEMPORARY STUFF UNTIL TRUE THREADMANAGER WORKS

// Working demos            |    Real     | Interpreter-like |   Full
//                          | Interpreter |     Dynarec      |  Dynarec
//--------------------------+-------------+------------------+----------
// - minifire.pbp           |     yes     |       yes        |    yes**
// - helloworldpsp.pbp      |     yes     |       yes        |    yes**
// - compilerPref.pbp*      |    cross    |       yes        |     no**
//
// * : special version for pspe4all which can be used as a benchmark with jpcsp, ppsspp, etc. without pad input and screen output.
// **: due to last changes, full dynarec mode may not work as focus is mainly upon interpreter-like mode now.

#include "hal.dbg.h"
#include "hal.npa.h"
#include "hal.AsyncFile.h"
#include "lle.mmu.h"
#include "hle.kd.h"
#include "emu.log.h"
#include "emu.h"
#include "emu.minifire.h"

#include <winnt.h>

#include <map>

hle::kd::Module   * main_module = 0;
hal::AsyncFile<>  * async_file  = 0;
hal::AsyncFile<>  * asm_file;

/*
Below is test code to be checked and removed in near future (shadow)
*/
void LoadModule(wchar_t const * filename)
{
    FILE * pFile;
    if ((pFile = _wfsopen(filename, L"rb", _SH_DENYNO)) != NULL)
    {
        u32 magic;
        /*size_t readSize =*/ fread(&magic, 4, 1, pFile);
        if (magic == 'FLE\x7F' || magic == 'PBP\x00')
        {
            SceKernelLoadExecParam parameters;
            memset(&parameters, 0, sizeof(SceKernelLoadExecParam));

            long size;
            fseek(pFile, 0, SEEK_END);
            size = ftell(pFile);
            rewind(pFile);
            u8 * buf = new u8[(int)size + 0x01000000];
            fread(buf, 1, size, pFile);
            fclose(pFile);

            if (memcmp(buf, "\0PBP", 4) == 0)
            {
                debugf(kd, "hleLoadExec File is pbp");
            }

            main_module = hle::kd::LoadModule(buf, 0);

            delete[] buf;

            //debugf(hle, "LoadedExec loaded");
        }
        fclose(pFile);
    }
}

CCpu Cpu;

static Allegrex::Context$base cross_context[2];

void CCpu::Initialize(wchar_t const filename[])
{
    debugf(emu, "pspe4all-emu: CPU initializing...");

    hle::syscalls::Init();

    LoadModule(filename);

    Context::Reset();
    Context::gpr[ALLEGREX_SP] = 0x09FFC000;
    Context::gpr[ALLEGREX_GP] = main_module->m_gp_value;
    Context::pc               = main_module->m_entry_addr;

    memcpy(&cross_context[0], (Allegrex::Context$base *)this, sizeof(cross_context[0]));
}

void CCpu::Terminate()
{
    hle::syscalls::Fini();
}

void CCpu::Step()
{
    Interpret();
}

void CCpu::Interpret()
{
    Context::Interpret();
}

static hal::npa::Event cpu_event1("CPU Interpreter");
static hal::npa::Event cpu_event2("CPU Waiting");

void CCpu::Run()
{
    if (!::GetCurrentUmsThread())
    {
        UmsScheduler::Run();
    }
    else
    {
        if (!USE_REAL_INTERPRETER)
        {
            auto execute = reinterpret_cast< void (*)(Allegrex::Context *) >(Allegrex::icache.thread_code.GetCode());

            hal::npa::StartEvent(cpu_event1);
            execute(this);
            hal::npa::StopEvent(cpu_event1);
        }
        else
        {
            do
            {
                switch (Cpu.syscall.code)
                {
                    case DoNothing:
                    {
                        __npa_Event(cpu_event1)
                        {
                            do Cpu.Step(); while (Cpu.syscall.code == DoNothing);
                        }
                        break;
                    }
                    case DoLeave:
                    {
                        return;
                    }
                    default:
                    {
                        __npa_Event(cpu_event2)
                        {
                            ::WaitForSingleObject(Cpu.syscall.event[1], INFINITE);
                        }
                        ::ResetEvent(Cpu.syscall.event[1]);
                    }
                }
            }
            while (true);
        }
    }
}

void CCpu::StartThread()
{
    Allegrex::icache.Start();

    if (TRACE_ALLEGREX_INSTRUCTION)
    {
        asm_file = new hal::AsyncFile < > ;
        if (INTERPRETER_LIKE)
        {
            asm_file->Open(L"allegrex_flow.fast.txt");
        }
        else
        {
            asm_file->Open(L"allegrex_flow.full.txt");
        }

        if (CROSS_INTERPRETER)
        {
            async_file = new hal::AsyncFile < > ;
            async_file->Open(L"cross_interpreter.txt");
        }
    }

    syscall.event[0] = ::CreateEvent(0, TRUE, FALSE, 0);
    syscall.event[1] = ::CreateEvent(0, TRUE, FALSE, 0);

    QueueWorker(this)->Start();
    StartRunnable(this);
}

void CCpu::StopThread()
{
    syscall.Leave(DoLeave);
    Join();

    ::CloseHandle(syscall.event[0]);
    ::CloseHandle(syscall.event[1]);

    if (CROSS_INTERPRETER)
    {
        delete async_file;
    }

    if (TRACE_ALLEGREX_INSTRUCTION)
    {
        delete asm_file;
    }

    Allegrex::icache.Stop();
}

static inline u32 rd(u32 opcode) { return ((((u32)opcode) >> 11) & 31); }
static inline u32 rt(u32 opcode) { return ((((u32)opcode) >> 16) & 31); }
static inline u32 rs(u32 opcode) { return ((((u32)opcode) >> 21) & 31); }

void lle::cpu::Context::Trace(Context * that, u32 address)
{
    static std::set< u32 > addresses;
    static u32 last_address = 0;
    static u32 last_opcode = 0;
    static u64 last_info = 0ULL;

    if (last_opcode && (last_info & IS_BCU))
    {
        char line[1024];
        auto length = int(0);
        if (last_info & (HAS_RS_AS_INPUT | HAS_RT_AS_INPUT | HAS_RA_AS_OUTPUT | HAS_RA_AS_INPUT))
        {
            length += sprintf(line, " --->");
            if (last_info & HAS_RS_AS_INPUT)
            {
                length += sprintf(line + length, " rs:%08X", that->gpr[rs(last_opcode)]);
            }
            if (last_info & HAS_RT_AS_INPUT)
            {
                length += sprintf(line + length, " rt:%08X", that->gpr[rt(last_opcode)]);
            }
            if (last_info & (HAS_RA_AS_OUTPUT | HAS_RA_AS_INPUT))
            {
                length += sprintf(line + length, " ra:%08X", that->gpr[31]);
            }
            asm_file->Write(line, strlen(line));
        }
        last_opcode = 0;
    }

    if (addresses.find(address) == addresses.end())
    {
        char line[1024];
        sprintf(line, "\r\n%08X - ", address);
        auto opcode = *p32u32(address);
        last_info = lle::cpu::Disassemble(address, opcode, line + sizeof("\r\nXXXXXXXX - ") - 1);
        asm_file->Write(line, strlen(line));
        addresses.insert(address);
        last_address = address;
        last_opcode = opcode;
    }
}

static u32 cross_interpreter_last_pc = 0;
static bool cross_interpreter_syscall = false;

void lle::cpu::Context::CrossInterpret(Context * that, u32 address)
{
    that->CrossInterpret_(address);
}

void lle::cpu::Context::CrossInterpret_(u32 address)
{
    if (0) tracef(cpu, "<<<%08X>>>", u32(((uintptr_t*)__returnaddressptr())[6+8]));

    bool must_compare = 0 == (address & 1);

    address &= u32(-2);

    if (cross_interpreter_syscall)
    {
        this->npc = address;
        this->pc = address;
        memcpy(&cross_context[0], (Allegrex::Context$base *)this, sizeof(cross_context[0]));
        cross_interpreter_syscall = false;
    }
    else
    {
        this->npc = cross_context[0].npc;
        this->pc = cross_context[0].pc;
    }

    Trace(this, address);

    if (must_compare)
    {
        if (memcmp(cross_context[0].gpr + 1, Context::gpr + 1, sizeof(u32[31])))
        {
            char       buffer[1024];
            static u32 count = 0;
            size_t     length        = ::_snprintf(buffer, 1024,
                                                   "[%6d - #%08X after #%08X]:"
                                                   "\r\n\t$zr:[%08X %08X] $at:[%08X %08X] $v0:[%08X %08X] $v1:[%08X %08X]"
                                                   "\r\n\t$a0:[%08X %08X] $a1:[%08X %08X] $a2:[%08X %08X] $a3:[%08X %08X]"
                                                   "\r\n\t$t0:[%08X %08X] $t1:[%08X %08X] $t2:[%08X %08X] $t3:[%08X %08X]"
                                                   "\r\n\t$t4:[%08X %08X] $t5:[%08X %08X] $t6:[%08X %08X] $t7:[%08X %08X]"
                                                   "\r\n\t$s0:[%08X %08X] $s1:[%08X %08X] $s2:[%08X %08X] $s3:[%08X %08X]"
                                                   "\r\n\t$s4:[%08X %08X] $s5:[%08X %08X] $s6:[%08X %08X] $s7:[%08X %08X]"
                                                   "\r\n\t$t8:[%08X %08X] $t9:[%08X %08X] $k0:[%08X %08X] $k1:[%08X %08X]"
                                                   "\r\n\t$gp:[%08X %08X] $sp:[%08X %08X] $fp:[%08X %08X] $ra:[%08X %08X]\r\n",
                                                   ++count,
                                                   address,
                                                   cross_interpreter_last_pc,
                                                   gpr[+0], cross_context[0].gpr[+0], gpr[+1], cross_context[0].gpr[+1], gpr[+2], cross_context[0].gpr[+2], gpr[+3], cross_context[0].gpr[+3],
                                                   gpr[+4], cross_context[0].gpr[+4], gpr[+5], cross_context[0].gpr[+5], gpr[+6], cross_context[0].gpr[+6], gpr[+7], cross_context[0].gpr[+7],
                                                   gpr[+8], cross_context[0].gpr[+8], gpr[+9], cross_context[0].gpr[+9], gpr[10], cross_context[0].gpr[10], gpr[11], cross_context[0].gpr[11],
                                                   gpr[12], cross_context[0].gpr[12], gpr[13], cross_context[0].gpr[13], gpr[14], cross_context[0].gpr[14], gpr[15], cross_context[0].gpr[15],
                                                   gpr[16], cross_context[0].gpr[16], gpr[17], cross_context[0].gpr[17], gpr[18], cross_context[0].gpr[18], gpr[19], cross_context[0].gpr[19],
                                                   gpr[20], cross_context[0].gpr[20], gpr[21], cross_context[0].gpr[21], gpr[22], cross_context[0].gpr[22], gpr[23], cross_context[0].gpr[23],
                                                   gpr[24], cross_context[0].gpr[24], gpr[25], cross_context[0].gpr[25], gpr[26], cross_context[0].gpr[26], gpr[27], cross_context[0].gpr[27],
                                                   gpr[28], cross_context[0].gpr[28], gpr[29], cross_context[0].gpr[29], gpr[30], cross_context[0].gpr[30], gpr[31], cross_context[0].gpr[31]);
            async_file->Write(buffer, length);

            __debugbreak();
        }

        if (memcmp(cross_context[0].fpr, Context::fpr, sizeof(f32[32])))
        {
            char       buffer[1024];
            static u32 count = 0;
            size_t     length = ::_snprintf(buffer, 1024,
                                            "[%6d - #%08X after #%08X]:"
                                            "\r\n\t$f0 :[%08X %08X] $f1 :[%08X %08X] $f2 :[%08X %08X] $f3 :[%08X %08X]"
                                            "\r\n\t$f4 :[%08X %08X] $f5 :[%08X %08X] $f6 :[%08X %08X] $f7 :[%08X %08X]"
                                            "\r\n\t$f8 :[%08X %08X] $f9 :[%08X %08X] $f10:[%08X %08X] $f11:[%08X %08X]"
                                            "\r\n\t$f12:[%08X %08X] $f13:[%08X %08X] $f14:[%08X %08X] $f15:[%08X %08X]"
                                            "\r\n\t$f16:[%08X %08X] $f17:[%08X %08X] $f18:[%08X %08X] $f19:[%08X %08X]"
                                            "\r\n\t$f20:[%08X %08X] $f21:[%08X %08X] $f22:[%08X %08X] $f23:[%08X %08X]"
                                            "\r\n\t$f24:[%08X %08X] $f25:[%08X %08X] $f26:[%08X %08X] $f27:[%08X %08X]"
                                            "\r\n\t$f28:[%08X %08X] $f29:[%08X %08X] $f30:[%08X %08X] $f31:[%08X %08X]\r\n",
                                            ++count,
                                            address,
                                            cross_interpreter_last_pc,
                                            fpr[+0], cross_context[0].fpr[+0], fpr[+1], cross_context[0].fpr[+1], fpr[+2], cross_context[0].fpr[+2], fpr[+3], cross_context[0].fpr[+3],
                                            fpr[+4], cross_context[0].fpr[+4], fpr[+5], cross_context[0].fpr[+5], fpr[+6], cross_context[0].fpr[+6], fpr[+7], cross_context[0].fpr[+7],
                                            fpr[+8], cross_context[0].fpr[+8], fpr[+9], cross_context[0].fpr[+9], fpr[10], cross_context[0].fpr[10], fpr[11], cross_context[0].fpr[11],
                                            fpr[12], cross_context[0].fpr[12], fpr[13], cross_context[0].fpr[13], fpr[14], cross_context[0].fpr[14], fpr[15], cross_context[0].fpr[15],
                                            fpr[16], cross_context[0].fpr[16], fpr[17], cross_context[0].fpr[17], fpr[18], cross_context[0].fpr[18], fpr[19], cross_context[0].fpr[19],
                                            fpr[20], cross_context[0].fpr[20], fpr[21], cross_context[0].fpr[21], fpr[22], cross_context[0].fpr[22], fpr[23], cross_context[0].fpr[23],
                                            fpr[24], cross_context[0].fpr[24], fpr[25], cross_context[0].fpr[25], fpr[26], cross_context[0].fpr[26], fpr[27], cross_context[0].fpr[27],
                                            fpr[28], cross_context[0].fpr[28], fpr[29], cross_context[0].fpr[29], fpr[30], cross_context[0].fpr[30], fpr[31], cross_context[0].fpr[31]);
            async_file->Write(buffer, length);

            __debugbreak();
        }

        cross_interpreter_last_pc = address;
    }

    memcpy(&cross_context[1], (Allegrex::Context$base *)this, sizeof(cross_context[1]));

    Cpu.Step();

    memcpy(&cross_context[0], (Allegrex::Context$base *)this, sizeof(cross_context[0]));
    memcpy((Allegrex::Context$base *)this, &cross_context[1], sizeof(cross_context[1]));
}

bool TimeToSecondsSince1970(PLARGE_INTEGER Time, PULONG SecondsSince1970)
{
    LARGE_INTEGER IntTime;

    IntTime.QuadPart = Time->QuadPart - 0x019db1ded53e8000i64/*TICKSTO1970*/;
    IntTime.QuadPart = IntTime.QuadPart / 10000000/*TICKSPERSEC*/;

    if (IntTime.u.HighPart != 0)
    {
        return false;
    }

    *SecondsSince1970 = IntTime.u.LowPart;

    return true;
}

void lle::cpu::Context::do$SYSCALL(u32 code)
{
    static hal::AsyncFile<> iofile[4];
    static u32 uid = 0x100;
    static std::map< u32, u32 > entry;
    static std::map< u32, u32 > heap;
    if (code & 0x80000000)
    {
        if (CROSS_INTERPRETER)
        {
            cross_interpreter_syscall = true;
            return;
        }
        else
        {
            code = code - 0x80000000;
        }
    }
    switch (code)
    {
    case 0x00000000: // sceKernelMaxFreeMemSize
        if (true)
        {
            forcef(hle, "!!!sceKernelMaxFreeMemSize");
            gpr[2] = 16 * 1024 * 1024;
            forcef(hle, "!!!sceKernelMaxFreeMemSize -> %d", gpr[2]);
        }
        break;

    case 0x00000007: // sceKernelAllocPartitionMemory
        if (true)
        {
            static u32 heap_top = 0x0C000000;
            forcef(hle, "!!!sceKernelAllocPartitionMemory(%d)", gpr[7]);
            heap_top -= gpr[7];
            heap[++uid] = heap_top;
            gpr[2] = uid;
            forcef(hle, "!!!sceKernelAllocPartitionMemory -> %d", gpr[2]);
        }
        break;

    case 0x00000008: // sceKernelFreePartitionMemory
        if (true)
        {
            forcef(hle, "!!!sceKernelFreePartitionMemory(%d)", gpr[4]);
            heap[gpr[4]] = 0;
            gpr[2] = 0;
            forcef(hle, "!!!sceKernelFreePartitionMemory -> %d", gpr[2]);
        }
        break;

    case 0x00000009: // sceKernelGetBlockHeadAddr
        if (true)
        {
            forcef(hle, "!!!sceKernelGetBlockHeadAddr(%d)", gpr[4]);
            gpr[2] = heap[gpr[4]];
            forcef(hle, "!!!sceKernelGetBlockHeadAddr -> 0x%08X", gpr[2]);
        }
        break;

    case 0x00000819: // sceKernelLibcTime
        if (true)
        {
            forcef(hle, "!!!sceKernelLibcTime");
            FILETIME ft;
            GetSystemTimeAsFileTime(&ft);
            ULONG seconds = 0;
            TimeToSecondsSince1970((PLARGE_INTEGER)&ft, &seconds);
            if (gpr[4])
            {
                *p32u32(gpr[4]) = u32(seconds);
            }
            gpr[2] = u32(seconds);
            forcef(hle, "!!!sceKernelLibcTime -> %u", gpr[2]);
        }
        break;

    case 0x00004000:
    case 0x0000206D: // sceKernelCreateThread
        if (true)
        {
            auto pc = gpr[5];
            forcef(hle, "!!!sceKernelCreateThread(pc:0x%08X)", pc);
            entry[++uid] = pc;
            gpr[2] = uid;
            forcef(hle, "!!!sceKernelCreateThread -> thid:%d", gpr[2]);
        }
        break;

    case 0x00004002:
    case 0x0000206F: // sceKernelStartThread
        if (true)
        {
            auto pc = entry[int(gpr[4])];
            forcef(hle, "!!!sceKernelStartThread(thid:%d)", gpr[4]);
            SetTrampoline(pc);
            gpr[2] = 0;
            gpr[4] = 0;
            gpr[5] = 0;
            forcef(hle, "!!!sceKernelStartThread -> jump to pc:0x%08X", pc);
        }
        break;

    case 0x00002071: // sceKernelExitThread
        if (true)
        {
            forcef(hle, "!!!sceKernelExitThread");
        }
        break;

    case 0x000020BF: // sceKernelUtilsMt19937Init
        if (true)
        {
            //forcef(hle, "!!!sceKernelUtilsMt19937Init");
            srand(gpr[4]);
            gpr[2] = 0;
            //forcef(hle, "!!!sceKernelUtilsMt19937Init -> %d", gpr[2]);
        }
        break;

    case 0x000020C0: // sceKernelUtilsMt19937UInt
        if (true)
        {
            //forcef(hle, "!!!sceKernelUtilsMt19937UInt");
            gpr[2] = (u32)rand() * (u32)rand();
            //forcef(hle, "!!!sceKernelUtilsMt19937UInt -> %d", gpr[2]);
        }
        break;

    case 0x00002150: // sceCtrlPeekBufferPositive
        if (true)
        {
            //debugf(emu, "pspe4all-emu: syscall 0x02150 [sceCtrlPeekBufferPositive]");
            u32 i;
            u32 addr = gpr[4];
            for (i = 0; i < gpr[5]; ++i)
            {
                *lle::mmu::Addr< u32 >(addr) = 0;
                *lle::mmu::Addr< u32 >(addr + 4) = 0;
                *lle::mmu::Addr< u8  >(addr + 8) = 0;
                *lle::mmu::Addr< u8  >(addr + 9) = 0;
                addr += 16;
            }
            gpr[2] = i;
        }
        break;

    case 0x0000401B: // sceKernelSleepThreadCB
        if (true)
        {
            //forcef(hle, "!!!sceKernelSleepThreadCB");
            gpr[2] = 0;
            //forcef(hle, "!!!sceKernelSleepThreadCB -> %u", gpr[2]);
        }
        break;

    case 0x00004055: // sceKernelGetSystemTime
        if (true)
        {
            //forcef(hle, "!!!sceKernelGetSystemTime");
            u32 addr = gpr[4];
            FILETIME ft;
            ::GetSystemTimeAsFileTime(&ft);
            *lle::mmu::Addr< u64 >(addr) = (*((u64 *)&ft) / 10ULL);
            gpr[2] = SCE_KERNEL_ERROR_OK;
            //forcef(hle, "!!!sceKernelGetSystemTime-> %u", gpr[2]);
        }
        break;

    case 0x00004057: // sceKernelGetSystemTimeLow
        if (true)
        {
            //forcef(hle, "!!!sceKernelGetSystemTimeLow");
            FILETIME ft;
            ::GetSystemTimeAsFileTime(&ft);
            auto time = *((u64 *)&ft);
            gpr[2] = u32(time / 10ULL);
            //forcef(hle, "!!!sceKernelGetSystemTimeLow -> %u", gpr[2]);
        }
        break;


    case 0x00004073: // sceKernelCreateCallback
        if (true)
        {
            forcef(hle, "!!!sceKernelCreateCallback");
            gpr[2] = 0;
            forcef(hle, "!!!sceKernelCreateCallback -> %u", gpr[2]);
        }
        break;

    case 0x00006002: // sceKernelStdin
        if (true)
        {
            forcef(hle, "!!!sceKernelStdin");
            iofile[0].Open(L"stdin.txt");
            gpr[2] = 0;
            forcef(hle, "!!!sceKernelStdin -> 0x%08X", gpr[2]);
        }
        break;

    case 0x00006000: // sceKernelStdout
        if (true)
        {
            forcef(hle, "!!!sceKernelStdout");
            iofile[1].Open(L"stdout.txt");
            gpr[2] = 1;
            forcef(hle, "!!!sceKernelStdout -> 0x%08X", gpr[2]);
        }
        break;

    case 0x00006001: // sceKernelStderr
        if (true)
        {
            forcef(hle, "!!!sceKernelStderr");
            iofile[2].Open(L"stderr.txt");
            gpr[2] = 2;
            forcef(hle, "!!!sceKernelStderr -> 0x%08X", gpr[2]);
        }
        break;

    case 0x0000640E: // sceIoOpen
        if (true)
        {
            forcef(hle, "!!!sceIoOpen");
            iofile[3].Open(L"output.txt");
            gpr[2] = 3;
            forcef(hle, "!!!sceIoOpen -> 0x%08X", gpr[2]);
        }
        break;

    case 0x0000640F: // sceIoClose
        if (true)
        {
            forcef(hle, "!!!sceIoClose");
            iofile[3].Close();
            gpr[2] = 0;
            forcef(hle, "!!!sceIoClose -> 0x%08X", gpr[2]);
        }
        break;

    case 0x00006414: // sceIoWrite
        if (true)
        {
            static int count = 1;
            forcef(hle, "!!!sceIoWrite(%d, 0x%08X, %d) - %d", gpr[4], gpr[5], gpr[6], count++);
            iofile[gpr[4]].Write(lle::mmu::Addr< const char >(gpr[5]), size_t(gpr[6]));
            gpr[2] = gpr[6];
            forcef(hle, "!!!sceIoWrite -> %d", gpr[2]);
        }
        break;

    case 0x00008007: // sceKernelSelfStopUnloadModule
        if (true)
        {
            forcef(hle, "!!!sceKernelSelfStopUnloadModule");
            gpr[2] = 0;
            forcef(hle, "!!!sceKernelSelfStopUnloadModule -> %d", gpr[2]);
        }
        break;

    case 0x0000A001: // sceKernelExitGame
    case 0x000020EB:
        if (true)
        {
            forcef(hle, "!!!sceKernelExitGame");

        }
        break;

    case 0x0000A003: // sceKernelRegisterExitCallback
        if (true)
        {
            forcef(hle, "!!!sceKernelRegisterExitCallback");
            gpr[2] = 0;
            forcef(hle, "!!!sceKernelRegisterExitCallback -> %u", gpr[2]);
        }
        break;

    case 0x00012000:
    case 0x0000213A: // sceSetDisplayMode
        if (true)
        {
            //debugf(emu, "pspe4all-emu: syscall 0x0213A [sceSetDisplayMode] : %d %d %d", Cpu.gpr[4], Cpu.gpr[5],Cpu.gpr[6]);
            Cpu.syscall.Enter(CCpu::DoSceSetDisplayMode);
            gpr[2] = 0;
            /*  Cpu.gpr[2] = Video.sceSetDisplayMode(
            Cpu.gpr[4], Cpu.gpr[5], Cpu.gpr[6]);*/ //TODO
            hal::npa::StopEvent(cpu_event1);
            ::WaitForSingleObject(Cpu.syscall.event[1], INFINITE);
            ::ResetEvent(Cpu.syscall.event[1]);
            hal::npa::StartEvent(cpu_event1);
        }
        break;

    case 0x00012003:
    case 0x0000213F: // sceDisplaySetFrameBuf
        if (true)
        {
            //debugf(emu, "pspe4all-emu: syscall 0x0213F [sceDisplaySetFrameBuf] : 0x%08X %d %d", Cpu.gpr[4], Cpu.gpr[5], Cpu.gpr[6]);
            Cpu.syscall.Enter(CCpu::DoSceDisplaySetFrameBuf);
            gpr[2] = 0;
            /*  Cpu.gpr[2] = Video.sceDisplaySetFrameBuf(
            Cpu.gpr[4], Cpu.gpr[5],
            (PspDisplayPixelFormat)Cpu.gpr[6],
            (PspDisplaySetBufSync)Cpu.gpr[7]);*/  //TODO
            hal::npa::StopEvent(cpu_event1);
            ::WaitForSingleObject(Cpu.syscall.event[1], INFINITE);
            ::ResetEvent(Cpu.syscall.event[1]);
            hal::npa::StartEvent(cpu_event1);
        }
        break;

    case 0x0001200C:
    case 0x00002147: // sceDisplayWaitVblankStart
        if (true)
        {
            //debugf(emu, "pspe4all-emu: syscall 0x02147 [sceDisplayWaitVblankStart]");
            Cpu.syscall.Enter(CCpu::DoSceDisplayWaitVblankStart);
            gpr[2] = 0;
            hal::npa::StopEvent(cpu_event1);
            ::WaitForSingleObject(Cpu.syscall.event[1], INFINITE);
            ::ResetEvent(Cpu.syscall.event[1]);
            hal::npa::StartEvent(cpu_event1);
        }
        break;

    case 0x00014000: // sceCtrlSetSamplingMode
        if (true)
        {
            //forcef(hle, "!!!sceCtrlSetSamplingMode");
            gpr[2] = 0;
            //forcef(hle, "!!!sceCtrlSetSamplingMode -> %d", gpr[2]);
        }
        break;

    case 0x00014002: // sceCtrlSetSamplingCycle
        if (true)
        {
            //forcef(hle, "!!!sceCtrlSetSamplingCycle");
            gpr[2] = 0;
            //forcef(hle, "!!!sceCtrlSetSamplingCycle -> %d", gpr[2]);
        }
        break;

    case 0x00014008: // sceCtrlReadBufferPositive
        if (true)
        {
            //debugf(emu, "pspe4all-emu: syscall 0x02150 [sceCtrlPeekBufferPositive]");
            u32 i;
            u32 addr = gpr[4];
            for (i = 0; i < gpr[5]; ++i)
            {
                *p32u32(addr) = 0;
                *p32u32(addr + 4) = 0;
                *p32u8(addr + 8) = 0;
                *p32u8(addr + 9) = 0;
                addr += 16;
            }
            gpr[2] = i;
        }
        break;

    case 0x00018002: // scePowerRegisterCallback
        if (true)
        {
            //forcef(hle, "!!!scePowerRegisterCallback");
            gpr[2] = 0;
            //forcef(hle, "!!!scePowerRegisterCallback -> %d", gpr[2]);
        }
        break;

    case 0x00018038: // scePowerGetCpuClockFrequencyInt
        if (true)
        {
            forcef(hle, "!!!scePowerGetCpuClockFrequencyInt");
            gpr[2] = 222;
            forcef(hle, "!!!scePowerGetCpuClockFrequencyInt -> %d", gpr[2]);
        }
        break;

    case 0xFFFFFFFF:
        if (true)
        {
            if (CROSS_INTERPRETER)
            {
                memcpy((Allegrex::Context$base *)this, &cross_context[0], sizeof(cross_context[0]));
                break;
            }
        }

    default:
        if (true)
        {
            forcef(hle, "!!!SYSCALL 0x%08X", code);
            //assert(0);
            gpr[2] = 0;
            forcef(hle, "!!!SYSCALL 0x%08X -> %d", code, gpr[2]);
        }
        break;
    }
}

__noinline void lle::cpu::Context::SetTrampoline(u32 address)
{
    pc = address;
    if (return_address) *return_address = u64(trampoline_address);
}

__noinline void lle::cpu::Context::Syscall(Context * that, u32 code)
{
    if (CCpu::DoLeave != Cpu.syscall.code && code != 0x0000A001)
    {
        that->do$SYSCALL(code);
    }
    else
    {
        if (that->return_address) *that->return_address = u64(that->exit_address);
    }
}
