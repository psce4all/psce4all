#include "dbg.svr.h"

#define BOOLIFY(x) !!(x)

bool const dbg::svr::InterruptBreakpoint::EnableBreakpoint()
{
#if 0
    SIZE_T ulBytes = 0;
    bool bSuccess = BOOLIFY(ReadProcessMemory(m_hProcess, (LPCVOID)m_dwAddress, &m_originalByte, sizeof(unsigned char), &ulBytes));
    if (bSuccess && ulBytes == sizeof(unsigned char))
    {
        bSuccess = BOOLIFY(WriteProcessMemory(m_hProcess, (LPVOID)m_dwAddress, &m_breakpointOpcode, sizeof(unsigned char), &ulBytes));
        return bSuccess && (ulBytes == sizeof(unsigned char));
    }
    else
    {
        debugf(dbg, "Could not read from address %p. Error = %X", m_dwAddress, ::GetLastError());
    }
#else
    if (size_t(m_dwAddress) - JITASM_MEMORY_ADDRESS < size_t(JITASM_MEMORY_SIZE))
    {
        if (*((u8 *)m_dwAddress) == 0xCC) // int3
        {
            if (*((u16 *)(m_dwAddress - 2)) == 0x0175) // jnz $+1 (skip int3)
            {
                *((u8 *)(m_dwAddress - 1)) = 0x00; // jnz $+0 (execute int3)
                return true;
            }
        }
    }
    else
    {
        debugf(dbg, "Could not read from address %p", m_dwAddress);
    }
#endif
    return false;
}

bool const dbg::svr::InterruptBreakpoint::DisableBreakpoint()
{
#if 0
    SIZE_T ulBytes = 0;
    const bool bSuccess = BOOLIFY(WriteProcessMemory(m_hProcess, (LPVOID)m_dwAddress, &m_originalByte, sizeof(unsigned char), &ulBytes));
    if (bSuccess && ulBytes == sizeof(unsigned char))
    {
        return true;
    }
    errorf(dbg, "Could not write back original opcode to address %p. Error = %X", m_dwAddress, ::GetLastError());
#else
    if (size_t(m_dwAddress) - JITASM_MEMORY_ADDRESS < size_t(JITASM_MEMORY_SIZE))
    {
        if (*((u8 *)m_dwAddress) == 0xCC) // int3
        {
            if (*((u16 *)(m_dwAddress - 2)) == 0x0075) // jnz $+0 (execute int3)
            {
                *((u8 *)(m_dwAddress - 1)) = 0x01; // jnz $+1 (skip int3)
                return true;
            }
        }
    }
    else
    {
        debugf(dbg, "Could not write back original opcode to address %p.", m_dwAddress);
    }
#endif
    return false;
}

void dbg::svr::DebugEventHandler::Initialize()
{
    Register(DebugEvents::StartThread, [&](const DEBUG_EVENT &dbgEvent)
    {
        auto &info = dbgEvent.u.CreateThread;
        debugf(dbg, "DebugEvents::CreateThread: Handle: %p, TLS base: %p, Start address: %p",
                    info.hThread, info.lpThreadLocalBase, info.lpStartAddress);
        SetContinueStatus(DBG_CONTINUE);
    });

    Register(DebugEvents::StartProcess, [&](const DEBUG_EVENT &dbgEvent)
    {
        auto &info = dbgEvent.u.CreateProcessInfo;
        debugf(dbg, "DebugEvents::CreateProcess: Handle (image file): %p, Handle (process): %p, Handle (main thread): %p, Image base address: %p, Debug info file offset: %X, Debug info size: %X, TLS base: %p, Start address: %p.",
                    info.hFile, info.hProcess, info.hThread, info.lpBaseOfImage,
                    info.dwDebugInfoFileOffset, info.nDebugInfoSize, info.lpThreadLocalBase,
                    info.lpStartAddress);

        char strName[MAX_PATH] = { 0 };
        (void)::GetFinalPathNameByHandleA(info.hFile, strName, sizeof(strName), FILE_NAME_NORMALIZED);

        m_pDebugger->m_hProcess = info.hProcess;
        m_pDebugger->m_hFile = info.hFile;
        m_pDebugger->m_pStepPoint = std::unique_ptr<InterruptBreakpoint>(new InterruptBreakpoint(info.hProcess, 0));

        SetContinueStatus(DBG_CONTINUE);
    });

    Register(DebugEvents::ExitThread, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugEvents::ExitThread: Thread %X exited with code %X.",
                    dbgEvent.dwThreadId, dbgEvent.u.ExitThread.dwExitCode);
        SetContinueStatus(DBG_CONTINUE);
    });

    Register(DebugEvents::ExitProcess, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugEvents::ExitProcess: Process %X exited with code %X.",
                    dbgEvent.dwProcessId, dbgEvent.u.ExitProcess.dwExitCode);
        SetContinueStatus(DBG_CONTINUE);
    });

    Register(DebugEvents::LoadDll, [&](const DEBUG_EVENT &dbgEvent)
    {
        auto &info = dbgEvent.u.LoadDll;
        debugf(dbg, "DebugEvents::LoadDll: Handle: %p, Base address: %p, Debug info file offset: %X, Debug info size: %X.",
                    info.hFile, info.lpBaseOfDll, info.dwDebugInfoFileOffset,
                    info.nDebugInfoSize);
        char strName[MAX_PATH] = { 0 };
        (void)GetFinalPathNameByHandleA(info.hFile, strName, sizeof(strName), FILE_NAME_NORMALIZED);
        debugf(dbg, "DebugEvents::LoadDll: Name: %s.", strName);
        m_dwContinueStatus = DBG_CONTINUE;
    });

    Register(DebugEvents::UnloadDll, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugEvents::UnloadDll: Dll at %p has unloaded.", dbgEvent.u.UnloadDll.lpBaseOfDll);
        SetContinueStatus(DBG_CONTINUE);
    });

    Register(DebugEvents::DebugString, [&](const DEBUG_EVENT &dbgEvent)
    {
        auto &info = dbgEvent.u.DebugString;
        auto pBuffer = std::unique_ptr<char[]>(new char[info.nDebugStringLength]);
        SIZE_T ulBytesRead = 0;

        const bool bSuccess = BOOLIFY(ReadProcessMemory(m_pDebugger->m_hProcess(), info.lpDebugStringData, pBuffer.get(), info.nDebugStringLength, &ulBytesRead));
        if (bSuccess)
        {
            if (info.fUnicode)
            {
                m_pDebugger->OutputDebugStringW((wchar_t *)pBuffer.get());
            }
            else
            {
                m_pDebugger->OutputDebugStringA(pBuffer.get());
            }
        }
        else
        {
            errorf(dbg, "DebugEvents::DebugString: Could not read debug string. Error = %X", ::GetLastError());
        }

        SetContinueStatus(DBG_CONTINUE);
    });

    Register(DebugEvents::RipEvent, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugEvents::RipEvent.");
        SetContinueStatus(DBG_CONTINUE);
    });

    Register(DebugEvents::Exception, [&](const DEBUG_EVENT &dbgEvent)
    {
        auto &exception = dbgEvent.u.Exception;
        debugf(dbg, "DebugEvents::Exception: First chance exception: %X, Exception code: %X, Exception flags: %X, Exception address: %p, Number parameters (associated with exception): %X",
                    exception.dwFirstChance, exception.ExceptionRecord.ExceptionCode,
                    exception.ExceptionRecord.ExceptionFlags, exception.ExceptionRecord.ExceptionAddress,
                    exception.ExceptionRecord.NumberParameters);
                    m_pDebugger->m_pExceptionHandler->Notify((DebugExceptions)dbgEvent.u.Exception.ExceptionRecord.ExceptionCode, dbgEvent);
        SetContinueStatus(m_pDebugger->m_pExceptionHandler->ContinueStatus());
    });
}

void dbg::svr::DebugExceptionHandler::Initialize()
{
    Register(DebugExceptions::AccessViolation, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::AccessViolation: Received access violation");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::DataTypeMisalignment, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::DataTypeMisalignment: Received datatype misalignment");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::SoftBreakpoint, [&](const DEBUG_EVENT &dbgEvent)
    {
        if (!m_pDebugger->m_bSeenInitialBreakpoint)
        {
            m_pDebugger->m_bSeenInitialBreakpoint = true;
            SetContinueStatus(DBG_CONTINUE);
        }
        else
        {
            auto &exceptionRecord = dbgEvent.u.Exception.ExceptionRecord;
            const DWORD_PTR dwExceptionAddress = (DWORD_PTR)exceptionRecord.ExceptionAddress;
            debugf(dbg, "DebugExceptions::SoftBreakpoint: Received breakpoint at address %p.", dwExceptionAddress);

            m_pDebugger->m_dwExecutingThreadId = dbgEvent.dwThreadId;
            CONTEXT ctx = m_pDebugger->GetExecutingContext();
            auto rip = ctx.Rip;
            if (size_t(rip) - JITASM_MEMORY_ADDRESS < size_t(JITASM_MEMORY_SIZE))
            {
                auto icache_pc = (u32 *)ctx.Rdx;
                //auto jitasm_ip = (u32 *)Context.Rbp;
                m_pDebugger->m_eStepMode = (Debugger::StepMode *)ctx.Rdi;
				m_pDebugger->OnCurrentGuestInstruction(u32(size_t(icache_pc) - ICACHE_MEMORY_ADDRESS));

                if (*((u8 *)rip) == 0xCC)
                {
                    switch (*((u16 *)(rip - 2)))
                    {
                    case 0x0075: // user breakpoint
						{
							Breakpoint *pBreakpoint = m_pDebugger->FindBreakpoint(dwExceptionAddress);
							if (pBreakpoint != nullptr)
							{
								if (pBreakpoint->Disable())
								{
									ctx.Rip++;
									if (m_pDebugger->SetExecutingContext(ctx))
									{
										debugf(dbg, "<<<<<<<<<<<<<< breakpoint at 0x%08X... >>>>>>>>>>>>>>>", (size_t(icache_pc) - ICACHE_MEMORY_ADDRESS));
										(void)m_pDebugger->WaitForContinue();
									}
									SetContinueStatus(DBG_CONTINUE);
									return;
								}
								else
								{
									errorf(dbg, "DebugExceptions::SoftBreakpoint: Could not remove breakpoint at address %p.", dwExceptionAddress);
								}
							}
						}
						break;

                    case 0x0175: // single-step
                        ctx.Rip++;
                        if (m_pDebugger->SetExecutingContext(ctx))
                        {
                            debugf(dbg, "<<<<<<<<<<<<<< stepping at 0x%08X... >>>>>>>>>>>>>>>", (size_t(icache_pc) - ICACHE_MEMORY_ADDRESS));
                            (void)m_pDebugger->WaitForContinue();
                        }
                        SetContinueStatus(DBG_CONTINUE);
                        return;
                    }
                }
            }

            SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
        }
    });

    Register(DebugExceptions::HardBreakpoint, [&](const DEBUG_EVENT &dbgEvent)
    {
        auto &exceptionRecord = dbgEvent.u.Exception.ExceptionRecord;
        const DWORD_PTR dwExceptionAddress = (DWORD_PTR)exceptionRecord.ExceptionAddress;
        debugf(dbg, "DebugExceptions::HardBreakpoint: Received step at address %p", dwExceptionAddress);
        if (m_pDebugger->m_bIsStepping)
        {
            debugf(dbg, "Press c to continue, s to step into, o to step over.");
            m_pDebugger->m_dwExecutingThreadId = dbgEvent.dwThreadId;
            CONTEXT ctx = m_pDebugger->GetExecutingContext();
            if (m_pDebugger->SetExecutingContext(ctx))
            {
                (void)m_pDebugger->WaitForContinue();
            }
        }
        if (m_pDebugger->m_pLastBreakpoint != m_pDebugger->m_pStepPoint.get() && !m_pDebugger->m_pLastBreakpoint->IsEnabled())
        {
            (void)m_pDebugger->m_pLastBreakpoint->Enable();
        }

        SetContinueStatus(DBG_CONTINUE);
    });

    Register(DebugExceptions::ArrayBoundsExceeded, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::ArrayBoundsExceeded: Received array bounds exceeded");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::FltDenormal, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::FltDenormal: Received floating point denormal");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::FltDivideByZero, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::FltDivideByZero: Received floating point divide by zero");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::FltInexactResult, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::FltInexactResult: Received floating point inexact result");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::FltInvalidOperation, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::FltInvalidOperation: Received floating point invalid operation");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::FltOverflow, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::FltOverflow: Received floating point overflow");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::FltStackCheck, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::FltStackCheck: Received floating point stack check");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::FltUnderflow, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::FltUnderflow: Received floating point underflow");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::IntDivideByZero, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::IntDivideByZero: Received integer divide by zero");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::IntOverflow, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::IntOverflow: Received integer overflow");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::PrivilegedInstruction, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::PrivilegedInstruction: Received privileged instruction");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::PageError, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::PageError: Received page error");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::IllegalInstruction, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "Received illegal instruction");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::NoncontinuableException, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "Received non-continuable exception");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::StackOverflow, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "Received stack overflow");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::InvalidDisposition, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "Received invalid disposition");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::GuardPage, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "Received guard page");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::InvalidHandle, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "Received invalid handle");
        SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
    });

    Register(DebugExceptions::SetThreadName, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::SetThreadName: Received set thread name");
        auto &exceptionRecord = dbgEvent.u.Exception.ExceptionRecord;
        if (exceptionRecord.ExceptionInformation[0] == 0x1000)
        {
            auto thread_name = (char const *)exceptionRecord.ExceptionInformation[1];
            auto thread_id = exceptionRecord.ExceptionInformation[2];

            SetContinueStatus(DBG_CONTINUE);
        }
        else
        {
            SetContinueStatus(DBG_EXCEPTION_NOT_HANDLED);
        }
    });

    Register(DebugExceptions::GuestInstruction, [&](const DEBUG_EVENT &dbgEvent)
    {
        debugf(dbg, "DebugExceptions::GuestInstruction: Received Allegrex instruction");
        auto &exceptionRecord = dbgEvent.u.Exception.ExceptionRecord;
        m_pDebugger->OnNewGuestInstruction(u32(exceptionRecord.ExceptionInformation[0]), size_t(exceptionRecord.ExceptionInformation[2]), size_t(exceptionRecord.ExceptionInformation[3]));
        SetContinueStatus(DBG_CONTINUE);
    });
}

static bool EnableDebugPrivilege(bool Enable)
{
    bool Success = false;
    HANDLE hToken = NULL;
    DWORD ec = 0;
    for (;;)
    {
        if (!::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
        {
            break;
        }
        TOKEN_PRIVILEGES tp;
        tp.PrivilegeCount = 1;
        if (!::LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
        {
            break;
        }
        tp.Privileges[0].Attributes = Enable ? SE_PRIVILEGE_ENABLED : 0;
        if (!::AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
        {
            break;
        }
        Success = true;
        break;
    }

    if (hToken != NULL)
    {
        ::CloseHandle(hToken);
    }
    return Success;
}

dbg::svr::Debugger::Debugger()
    : m_bIsActive{ false }
    , m_dwProcessId{ 0 }
    , m_bKillOnExit{ true }
    , m_hProcess{ INVALID_HANDLE_VALUE }
    , m_pLastBreakpoint{ nullptr }
    , m_dwExecutingThreadId{ 0 }
    , m_bIsStepping{ false }
    , m_eStepMode{ nullptr }
{
    m_pEventHandler = std::unique_ptr<DebugEventHandler>(new DebugEventHandler(this));
    m_pExceptionHandler = std::unique_ptr<DebugExceptionHandler>(new DebugExceptionHandler(this));
    m_hContinueEvent = ::CreateEvent(nullptr, false, false, nullptr/*L"Continue event"*/);

    EnableDebugPrivilege(true);
}


bool const dbg::svr::Debugger::AttachToProcess(DWORD pid)
{
    m_bIsActive = BOOLIFY(::DebugActiveProcess(pid));
    if (m_bIsActive)
    {
        m_dwProcessId = pid;
        bool const bIsSuccess = BOOLIFY(::DebugSetProcessKillOnExit(m_bKillOnExit));
        if (!bIsSuccess)
        {
            errorf(dbg, "Could not set process kill on exit policy. Error = %X", ::GetLastError());
        }
        return DebuggerLoop();
    }
    else
    {
        errorf(dbg, "Could not debug process %X. Error = %X", m_dwProcessId, ::GetLastError());
    }

    return false;
}

bool const dbg::svr::Debugger::Detach()
{
    m_bIsActive = BOOLIFY(::DebugActiveProcessStop(m_dwProcessId));
    if (!m_bIsActive)
    {
        errorf(dbg, "Could not stop debugging process %X. Error = %X", m_dwProcessId, ::GetLastError());
    }

    return m_bIsActive;
}

bool const dbg::svr::Debugger::Start()
{
    m_bIsActive = BOOLIFY(::DebugActiveProcess(m_dwProcessId));
    if (m_bIsActive)
    {
        bool const bIsSuccess = BOOLIFY(::DebugSetProcessKillOnExit(m_bKillOnExit));
        if (!bIsSuccess)
        {
            errorf(dbg, "Could not set process kill on exit policy. Error = %X", ::GetLastError());
        }
        return DebuggerLoop();
    }
    else
    {
        errorf(dbg, "Could not debug process %X. Error = %X", m_dwProcessId, ::GetLastError());
    }

    return false;
}

bool const dbg::svr::Debugger::AddBreakpoint(DWORD_PTR const dwAddress)
{
    bool bSuccess = false;

    std::unique_ptr<InterruptBreakpoint> pNewBreakpoint(new InterruptBreakpoint(m_hProcess(), dwAddress));
    if (pNewBreakpoint->EnableBreakpoint())
    {
        m_cBreakpoints.emplace_back(std::move(pNewBreakpoint));
        bSuccess = true;
    }

    return bSuccess;
}

bool const dbg::svr::Debugger::RemoveBreakpoint(DWORD_PTR const dwAddress)
{
    bool bSuccess = false;

    auto breakpoint = std::find_if(m_cBreakpoints.begin(), m_cBreakpoints.end(), [=](const std::unique_ptr<Breakpoint> &breakpoint)
    {
        return breakpoint->Address() == dwAddress;
    });
    if (breakpoint != m_cBreakpoints.end())
    {
        (void)(*breakpoint)->Disable();
        m_cBreakpoints.remove(*breakpoint);
        bSuccess = true;
    }

    return bSuccess;
}

dbg::svr::Breakpoint * dbg::svr::Debugger::FindBreakpoint(DWORD_PTR const dwAddress)
{
    auto breakpoint = std::find_if(m_cBreakpoints.begin(), m_cBreakpoints.end(), [=](const std::unique_ptr<Breakpoint> &breakpoint)
    {
        return breakpoint->Address() == dwAddress;
    });
    if (breakpoint != m_cBreakpoints.end())
    {
        return breakpoint->get();
    }
    if (m_pStepPoint->Address() == dwAddress)
    {
        return m_pStepPoint.get();
    }

    return nullptr;
}

bool const dbg::svr::Debugger::StepOver()
{
    if (m_eStepMode)
    {
        *m_eStepMode = StepOverMode;

        (void)Continue(true);
    }

    return true;
}

bool const dbg::svr::Debugger::StepInto()
{
    if (m_eStepMode)
    {
        *m_eStepMode = StepIntoMode;

        (void)Continue(true);
    }

    return true;
}

bool const dbg::svr::Debugger::StepOut()
{
    if (m_eStepMode)
    {
        *m_eStepMode = StepOutMode;

        (void)Continue(true);
    }

    return true;
}

bool const dbg::svr::Debugger::Continue()
{
    if (m_eStepMode)
    {
        *m_eStepMode = ContinueMode;

        return Continue(false);
    }

    return false;
}

bool const dbg::svr::Debugger::Stop()
{
    if (m_eStepMode)
    {
        *m_eStepMode = StopMode;

        return Continue(false);
    }

    return false;
}

bool const dbg::svr::Debugger::Continue(const bool bIsStepping)
{
    m_bIsStepping = bIsStepping;

    return BOOLIFY(::SetEvent(m_hContinueEvent()));
}

bool const dbg::svr::Debugger::SetExecutingContext(CONTEXT const &ctx)
{
    bool bSuccess = false;
    SafeHandle hThread = OpenCurrentThread();
    if (hThread.IsValid())
    {
        bSuccess = BOOLIFY(SetThreadContext(hThread(), &ctx));
    }

    memcpy(&m_lastContext, &ctx, sizeof(CONTEXT));

    return bSuccess;
}

CONTEXT const dbg::svr::Debugger::GetExecutingContext()
{
    CONTEXT ctx = { 0 };
    ctx.ContextFlags = CONTEXT_ALL;
    SafeHandle hThread = OpenCurrentThread();
    if (hThread.IsValid())
    {
        bool bSuccess = BOOLIFY(GetThreadContext(hThread(), &ctx));
        if (!bSuccess)
        {
            errorf(dbg, "Could not get context for thread %X. Error = %X", m_dwExecutingThreadId, GetLastError());
        }
    }

    memcpy(&m_lastContext, &ctx, sizeof(CONTEXT));

    return ctx;
}

dbg::svr::SafeHandle dbg::svr::Debugger::OpenCurrentThread()
{
    SafeHandle handle = ::OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT, FALSE, m_dwExecutingThreadId);
    return handle;
}

bool const dbg::svr::Debugger::WaitForContinue()
{
    return (::WaitForSingleObject(m_hContinueEvent(), INFINITE) == WAIT_OBJECT_0);
}

bool const dbg::svr::Debugger::DebuggerLoop()
{
    DEBUG_EVENT dbgEvent = { 0 };
    DWORD dwContinueStatus = 0;
    bool bSuccess = false;

    while (m_bIsActive)
    {
        bSuccess = BOOLIFY(::WaitForDebugEvent(&dbgEvent, INFINITE));
        if (!bSuccess)
        {
            errorf(dbg, "WaitForDebugEvent returned failure. Error = %X", ::GetLastError());
            return false;
        }

        m_pEventHandler->Notify((DebugEvents)dbgEvent.dwDebugEventCode, dbgEvent);
        dwContinueStatus = m_pEventHandler->ContinueStatus();

        bSuccess = BOOLIFY(::ContinueDebugEvent(dbgEvent.dwProcessId, dbgEvent.dwThreadId, dwContinueStatus));
        if (!bSuccess)
        {
            errorf(dbg, "ContinueDebugEvent returned failure. Error = %X", ::GetLastError());
            return false;
        }
    }

    return true;
}

void dbg::svr::Debugger::OutputDebugStringA(char const message[])
{
    debugf("DebugEvents::DebugString:  %s", message);
}

void dbg::svr::Debugger::OutputDebugStringW(wchar_t const message[])
{
    debugf(L"DebugEvents::DebugString:  %s", message);
}

void dbg::svr::Debugger::OnNewGuestInstruction(u32 /*address*/, size_t /*address_x86_64*/, size_t /*size_x86_64*/)
{
}

void dbg::svr::Debugger::OnCurrentGuestInstruction(u32 /*address*/)
{
}
