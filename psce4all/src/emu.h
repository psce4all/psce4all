/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

extern "C" void AtomicChangeEmulatorState(long volatile * address, long value);

namespace emu
{
    struct StartupCleanup
    {
        /**/ StartupCleanup();

        /**/~StartupCleanup();
    };

    struct EmulatorState
    {
        enum
        {
            EmuPausing,
            EmuLoading,
            EmuRunning,
            EmuLeaving,

            EmuMaxStates  = 256,
            EmuStateMask  = 255,
        };

        __forceinline long RawState() const
        {
            return m_state;
        }
        __forceinline long State() const
        {
            return m_state & EmuStateMask;
        }
        __forceinline bool IsStateUnchanged(long & new_state)
        {
            long old_state = new_state, value = m_state; new_state = value; return value == old_state;
        }

        __forceinline void Pause()
        {
            AtomicChangeEmulatorState(&m_state, EmuPausing);
        }
        __forceinline void Run()
        {
            AtomicChangeEmulatorState(&m_state, EmuRunning);
        }
        __forceinline void Leave()
        {
            AtomicChangeEmulatorState(&m_state, EmuLeaving);
        }
        __forceinline void Load()
        {
            AtomicChangeEmulatorState(&m_state, EmuLoading);
        }

        __forceinline bool IsPausing() const
        {
            return (m_state & EmuStateMask) == EmuPausing;
        }
        __forceinline bool IsRunning() const
        {
            return (m_state & EmuStateMask) == EmuRunning;
        }
        __forceinline bool IsLeaving() const
        {
            return (m_state & EmuStateMask) == EmuLeaving;
        }
        __forceinline bool IsLoading() const
        {
            return (m_state & EmuStateMask) == EmuLoading;
        }

        __forceinline void TriggerEvent()
        {
            _InterlockedExchangeAdd(&m_state, EmuMaxStates);
        }

        EmulatorState() : m_state(EmuPausing)
        {
        }

    private:
        volatile long m_state;
    };

    struct Interface
    {
        static const long version_major = 1;
        static const long version_minor = 0;
        static const long version       = (version_major<<8)|(version_minor);

        /**/     Interface() {}
        virtual ~Interface() {}

        /* interface v 1.0 */
        long (* GetVersion_)(Interface *); __forceinline long GetVersion() { return GetVersion_(this); }

        virtual bool DllProcessAttach() = 0;
        virtual void DllProcessDetach() = 0;

        long State() const
        {
            return m_current_state.State();
        }

        long RawState() const
        {
            return m_current_state.RawState();
        }

        bool IsStateUnchanged(long & state)
        {
            return m_current_state.IsStateUnchanged(state);
        }

        void Resume()
        {
            m_current_state.Run();
        }

        void Pause()
        {
            m_current_state.Pause();
        }

        void Leave()
        {
            m_current_state.Leave();
        }

        bool IsRunning()
        {
            return m_current_state.IsRunning();
        }
        bool IsPausing()
        {
            return m_current_state.IsPausing();
        }
        bool IsLeaving()
        {
            return m_current_state.IsLeaving();
        }

        bool Start()
        {
            if (m_needs_start)
            {
                Resume();
                m_needs_start = false;
                m_needs_load = false;
                return true;
            };
            return false;
        }

        void Load()
        {
            m_needs_load = true;
        }

        void Reschedule();

        void ExecutePendingEvents();

        EmulatorState m_current_state;

        volatile bool m_needs_load;
        volatile bool m_needs_start;
        volatile bool m_loaded_game;
    };

    namespace sysinfo
    {
        wchar_t const * WindowsName();
        wchar_t const * WindowsArch();
        long            WindowsBits();
        bool            IsWow64();
        wchar_t const * UserName();
        wchar_t const * HomePath();
        wchar_t const * WorkPath();
        wchar_t const * TempPath();
    }
}

#if !defined(EMU_EXPORTS)
extern "C" __declspec(dllimport) emu::Interface * emu$GetInterface(long version);
#else
extern "C" __declspec(dllexport) emu::Interface * emu$GetInterface(long version);
#endif

extern emu::Interface * emulator;
