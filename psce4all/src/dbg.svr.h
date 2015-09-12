/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <thread>

#include <stdio.h>
#include <tchar.h>

#ifdef UNICODE
#define DBGHELP_TRANSLATE_TCHAR
#endif

#include <dbghelp.h>
#include <psapi.h>

#include "emu.log.h"
#include "lle.mmu.h"
#include "hal.Observable.h"

namespace dbg
{
    namespace svr
    {
        struct SafeHandle
        {
        public:
            SafeHandle() : m_handle{ INVALID_HANDLE_VALUE }
            {
            }

            SafeHandle(HANDLE handle) : m_handle{ handle }
            {
            }

            SafeHandle(SafeHandle const &copy) = delete;
            SafeHandle &operator=(SafeHandle const &copy) = delete;

            SafeHandle(SafeHandle &&obj)
            {
                m_handle = obj.m_handle;
                obj.m_handle = INVALID_HANDLE_VALUE;
            }

            SafeHandle &operator=(SafeHandle &&obj)
            {
                m_handle = obj.m_handle;
                obj.m_handle = INVALID_HANDLE_VALUE;
                return *this;
            }

            SafeHandle &operator=(HANDLE const handle)
            {
                m_handle = handle;
                return *this;
            }

            ~SafeHandle()
            {
                if (IsValid())
                {
                    (void)CloseHandle(m_handle);
                }
            }

            bool const IsValid() const
            {
                return (m_handle != INVALID_HANDLE_VALUE) || (m_handle != nullptr);
            }

            HANDLE operator()() const
            {
                return m_handle;
            }

        private:
            HANDLE m_handle;
        };

        struct Breakpoint
        {
        public:
            enum eType
            {
                Hardware  = 1,
                Software  = 2,
                Interrupt = 3
            };

            Breakpoint() = delete;
            Breakpoint(Breakpoint const &copy) = delete;
            Breakpoint(HANDLE const hProcess, DWORD_PTR const dwAddress, eType const eBreakpointType)
                : m_hProcess{ hProcess }
                , m_dwAddress{ dwAddress }
                , m_eType{ eBreakpointType }
                , m_eState{ Breakpoint::Disabled }
            {
            }

            virtual ~Breakpoint() = default;

            Breakpoint &operator=(Breakpoint const &copy) = delete;

            eType const Type() const
            {
                return m_eType;
            }

            DWORD_PTR const Address() const
            {
                return m_dwAddress;
            }

            bool const IsEnabled() const
            {
                return m_eState == Breakpoint::Enabled;
            }

            bool const Enable()
            {
                if (EnableBreakpoint())
                {
                    m_eState = Breakpoint::Enabled;
                    return true;
                }
                return false;
            }

            bool const Disable()
            {
                if (DisableBreakpoint())
                {
                    m_eState = Breakpoint::Disabled;
                    return true;
                }
                return false;
            }

            bool operator==(Breakpoint const &rhs) const
            {
                return (m_eType == rhs.m_eType) && (m_dwAddress == rhs.m_dwAddress);
            }

            bool operator!=(Breakpoint const &rhs) const
            {
                return !(*this == rhs);
            }

        private:
            enum eState
            {
                Disabled = 0,
                Enabled  = 1
            };

            virtual const bool EnableBreakpoint()  = 0;
            virtual const bool DisableBreakpoint() = 0;

            eType  m_eType;
            eState m_eState;

        protected:
            HANDLE    m_hProcess;
            DWORD_PTR m_dwAddress;
        };

        class InterruptBreakpoint final : public Breakpoint
        {
        public:
            InterruptBreakpoint() = delete;
            InterruptBreakpoint(const HANDLE hProcess, const DWORD_PTR dwAddress)
                : Breakpoint(hProcess, dwAddress, Breakpoint::Interrupt)
                , m_originalByte{ 0 }
            {
            }

            InterruptBreakpoint(const InterruptBreakpoint &copy) = delete;
            InterruptBreakpoint &operator=(const InterruptBreakpoint &copy) = delete;

            ~InterruptBreakpoint() = default;

            bool const EnableBreakpoint();

            bool const DisableBreakpoint();

            void ChangeAddress(DWORD_PTR const dwNewAddress)
            {
                m_dwAddress = dwNewAddress;
            }

        private:
            static unsigned char const m_breakpointOpcode = 0xCC;
            unsigned char              m_originalByte;
        };

        enum DebugEvents
        {
            Exception     = EXCEPTION_DEBUG_EVENT,
            StartThread   = CREATE_THREAD_DEBUG_EVENT,
            StartProcess  = CREATE_PROCESS_DEBUG_EVENT,
            ExitThread    = EXIT_THREAD_DEBUG_EVENT,
            ExitProcess   = EXIT_PROCESS_DEBUG_EVENT,
            LoadDll       = LOAD_DLL_DEBUG_EVENT,
            UnloadDll     = UNLOAD_DLL_DEBUG_EVENT,
            DebugString   = OUTPUT_DEBUG_STRING_EVENT,
            RipEvent      = RIP_EVENT,
        };

        struct Debugger;

        struct DebugEventHandler final : hal::Observable < DebugEvents, void, const DEBUG_EVENT & >
        {
        public:
            DebugEventHandler() = delete;
            DebugEventHandler(Debugger *pDebugger)
                : m_pDebugger{ pDebugger }
            {
                Initialize();
            }

            DebugEventHandler(DebugEventHandler const &copy) = delete;
            DebugEventHandler &operator=(DebugEventHandler const &copy) = delete;

            ~DebugEventHandler() = default;

            DWORD const ContinueStatus() const
            {
                return m_dwContinueStatus;
            }

        private:
            void Initialize();
            void SetContinueStatus(DWORD const dwContinueStatus)
            {
                m_dwContinueStatus = dwContinueStatus;
            }

            Debugger * const m_pDebugger;
            DWORD            m_dwContinueStatus;
        };

        enum DebugExceptions
        {
            AccessViolation         = EXCEPTION_ACCESS_VIOLATION,
            DataTypeMisalignment    = EXCEPTION_DATATYPE_MISALIGNMENT,
            SoftBreakpoint          = EXCEPTION_BREAKPOINT,
            HardBreakpoint          = EXCEPTION_SINGLE_STEP,
            ArrayBoundsExceeded     = EXCEPTION_ARRAY_BOUNDS_EXCEEDED,
            FltDenormal             = EXCEPTION_FLT_DENORMAL_OPERAND,
            FltDivideByZero         = EXCEPTION_FLT_DIVIDE_BY_ZERO,
            FltInexactResult        = EXCEPTION_FLT_INEXACT_RESULT,
            FltInvalidOperation     = EXCEPTION_FLT_INVALID_OPERATION,
            FltOverflow             = EXCEPTION_FLT_OVERFLOW,
            FltStackCheck           = EXCEPTION_FLT_STACK_CHECK,
            FltUnderflow            = EXCEPTION_FLT_UNDERFLOW,
            IntDivideByZero         = EXCEPTION_INT_DIVIDE_BY_ZERO,
            IntOverflow             = EXCEPTION_INT_OVERFLOW,
            PrivilegedInstruction   = EXCEPTION_PRIV_INSTRUCTION,
            PageError               = EXCEPTION_IN_PAGE_ERROR,
            IllegalInstruction      = EXCEPTION_ILLEGAL_INSTRUCTION,
            NoncontinuableException = EXCEPTION_NONCONTINUABLE_EXCEPTION,
            StackOverflow           = EXCEPTION_STACK_OVERFLOW,
            InvalidDisposition      = EXCEPTION_INVALID_DISPOSITION,
            GuardPage               = EXCEPTION_GUARD_PAGE,
            InvalidHandle           = EXCEPTION_INVALID_HANDLE,
            SetThreadName           = 0x406D1388,
            AllegrexInstruction     = 0x414CA449,
        };

        struct DebugExceptionHandler final : hal::Observable < DebugExceptions, void, const DEBUG_EVENT & >
        {
        public:
            DebugExceptionHandler() = delete;
            DebugExceptionHandler(Debugger *pDebugger)
                : m_pDebugger{ pDebugger }
            {
                Initialize();
            }

            ~DebugExceptionHandler() = default;

            const DWORD ContinueStatus() const
            {
                return m_dwContinueStatus;
            }

        private:
            void Initialize();

            void SetContinueStatus(const DWORD dwContinueStatus)
            {
                m_dwContinueStatus = dwContinueStatus;
            }

            Debugger * const m_pDebugger;
            DWORD            m_dwContinueStatus;
        };

        struct Debugger
        {
            friend struct DebugEventHandler;
            friend struct DebugExceptionHandler;

        public:
            enum StepMode : u64
            {
                ContinueMode = 0x0000000000000002ULL,  // F5
                StopMode     = 0x0100000000000000ULL,  // Shift+F5
                StepOverMode = 0x0200010000000000ULL,  // F10
                StepIntoMode = 0x0300000000000000ULL,  // F11
                StepOutMode  = 0x0401000000000001ULL   // Shift+F11
            };

            Debugger();

            Debugger(Debugger const &copy) = delete;
            Debugger &operator=(Debugger const &copy) = delete;

            ~Debugger() = default;

            bool const    AttachToProcess(DWORD pid);
            bool const    Detach();

            bool const    Start();
            bool const    Stop();
            bool const    StepInto();
            bool const    StepOver();
            bool const    StepOut();
            bool const    Continue();

            bool const    SetExecutingContext(CONTEXT const &ctx);

            CONTEXT const GetExecutingContext();

            bool const volatile IsActive() const
            {
                return m_bIsActive;
            }

            bool const    AddBreakpoint(DWORD_PTR const dwAddress);
            bool const    RemoveBreakpoint(DWORD_PTR const dwAddress);
            Breakpoint  * FindBreakpoint(DWORD_PTR const dwAddress);

            const HANDLE Handle() const
            {
                return m_hProcess();
            }

        protected:
            volatile bool m_bIsActive;
            bool          m_bKillOnExit;
            DWORD         m_dwProcessId;
            SafeHandle    m_hProcess;
            SafeHandle    m_hFile;
            SafeHandle    m_hContinueEvent;

            Breakpoint  * m_pLastBreakpoint;
            DWORD         m_dwExecutingThreadId;
            CONTEXT       m_lastContext;
            volatile bool m_bIsStepping;
            StepMode    * m_eStepMode;
            bool          m_bSeenInitialBreakpoint;

            virtual bool const DebuggerLoop();
            virtual bool const Continue(const bool bIsStepping);
            virtual bool const WaitForContinue();
            virtual void       OutputDebugStringA(char const message[]);
            virtual void       OutputDebugStringW(wchar_t const message[]);
            virtual void       OnAllegrexInstruction(u32 address, size_t address_x86_64, size_t size_x86_64);

            SafeHandle         OpenCurrentThread();

            std::unique_ptr < DebugEventHandler              > m_pEventHandler;
            std::unique_ptr < DebugExceptionHandler          > m_pExceptionHandler;
            std::unique_ptr < InterruptBreakpoint            > m_pStepPoint;
            std::list       < std::unique_ptr < Breakpoint > > m_cBreakpoints;
        };
    }
}