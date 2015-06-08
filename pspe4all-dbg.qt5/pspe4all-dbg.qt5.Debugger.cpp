/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "pspe4all-dbg.qt5.Debugger.h"
#include "qt_mainwindow.h"

#include <synchapi.h>
#pragma comment(lib, "synchronization.lib")

namespace dbg
{
    namespace qt5
    {
        Debugger::Debugger(int &argc, char **argv, int flags) : QApplication(argc, argv, flags)
        {
            state = NoEvent_State;

            QRunnable::setAutoDelete(false);

            threadpool.setExpiryTimeout(-1); // disable the expiry mechanism
            threadpool.setMaxThreadCount(0);
            threadpool.reserveThread();

            connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));
        }

        Debugger::~Debugger()
        {
        }

        bool Debugger::attachToProcess(DWORD pid)
        {
            debugEvent.dwProcessId = pid;
            state = AttachToProcessNeeded_State;

            threadpool.start(this);

            // wait for the result
            if (result = WaitForState(AttachToProcessResult_State))
            {
                WakeForState(WaitForDebugEventNeeded_State);
            }

            return result;
        }

        bool Debugger::continueDebugEvent()
        {
            result = PeekForState(WaitForDebugEventResult_State, WaitForDebugEventNeeded_State);
            if (result)
            {
                WakeForState(ContinueDebugEventNeeded_State);

                // wait for the result
                if (result = WaitForState(ContinueDebugEventResult_State))
                {
                    WakeForState(WaitForDebugEventNeeded_State);
                }
            }

            return result;
        }

        void Debugger::onAboutToQuit()
        {
            threadpool.releaseThread();

            WakeForState(NoEvent_State);
        }

        void Debugger::onStepIn()
        {
            if (!continueDebugEvent())
            {
                errorf(dbg, "Debugger::onStepIn() failure");
            }
        }

        void Debugger::onStepOver()
        {
            if (!continueDebugEvent())
            {
                errorf(dbg, "Debugger::onStepOver() failure");
            }
        }

        void Debugger::onStepOut()
        {
            if (!continueDebugEvent())
            {
                errorf(dbg, "Debugger::onStepOut() failure");
            }
        }

        void Debugger::enableStepping()
        {
            mainWindow->actionStepIn()->setEnabled(true);
            mainWindow->actionStepOver()->setEnabled(true);
            mainWindow->actionStepOut()->setEnabled(true);
        }

        void Debugger::disableStepping()
        {
            mainWindow->actionStepIn()->setDisabled(true);
            mainWindow->actionStepOver()->setDisabled(true);
            mainWindow->actionStepOut()->setDisabled(true);
        }

        void Debugger::run()
        {
            while (bContinue)
            {
                switch ((State volatile)state)
                {
                case NoEvent_State:
                    return;

                case AttachToProcessNeeded_State:
                    debugf(dbg, "Debugger::AttachToProcess(%u):", debugEvent.dwProcessId);
                    result = dbg::svr::Debugger::AttachToProcess(debugEvent.dwProcessId);
                    debugf(dbg, "Result = %d", int(result));
                    if (result)
                    {
                        WakeForState(AttachToProcessResult_State);
                    }
                    break;

                case AttachToProcessResult_State:
                    WaitForState(WaitForDebugEventNeeded_State);
                    break;

                case WaitForDebugEventNeeded_State:
                    QTimer::singleShot(0, Qt::PreciseTimer, this, SLOT(disableStepping()));
                    debugf(dbg, "Debugger::WaitForDebugEvent():", debugEvent.dwDebugEventCode, debugEvent.dwProcessId, debugEvent.dwThreadId);
                    continueStatus = DBG_CONTINUE;
                    result = dbg::svr::Debugger::WaitForDebugEvent(debugEvent, 333, continueStatus);
                    if (result)
                    {
                        debugf(dbg, "Result = %d, Code = %u, Process = %04X, Thread = %04X", int(result), debugEvent.dwDebugEventCode, debugEvent.dwProcessId, debugEvent.dwThreadId);
                        bool callContinueDebugEvent =
                            debugEvent.dwDebugEventCode != EXCEPTION_DEBUG_EVENT ||
                            debugEvent.u.Exception.ExceptionRecord.ExceptionCode != EXCEPTION_BREAKPOINT ||
                            !bSeenInitialBreakpoint;
                        if (dbg::svr::Debugger::HandleDebugEvent(debugEvent, continueStatus))
                        {
                            if (callContinueDebugEvent)
                            {
                                debugf(dbg, "Debugger::ContinueDebugEvent(Code = %u, Process = %04X, Thread = %04X):", debugEvent.dwDebugEventCode, debugEvent.dwProcessId, debugEvent.dwThreadId);
                                result = dbg::svr::Debugger::ContinueDebugEvent(debugEvent, continueStatus);
                                debugf(dbg, "Result = %d", int(result));
                                if (!result)
                                {
                                    errorf(dbg, "Debugger::ContinueDebugEvent() failure");
                                    return;
                                }
                                break;
                            }
                            QTimer::singleShot(0, Qt::PreciseTimer, this, SLOT(enableStepping()));
                            WakeForState(ContinueDebugEventResult_State);
                        }
                        else
                        {
                            errorf(dbg, "Debugger::HandleDebugEvent() failure");
                            return;
                        }
                    }
                    else
                    {
                        DWORD ErrCode = ::GetLastError();
                        if (ErrCode != ERROR_SEM_TIMEOUT)
                        {
                            debugf(dbg, "Result = %d, ErrorCode = %d", result, ErrCode);
                            return;
                        }
                    }
                    break;

                case WaitForDebugEventResult_State:
                    WaitForState(ContinueDebugEventNeeded_State);
                    break;

                case ContinueDebugEventNeeded_State:
                    debugf(dbg, "Debugger::ContinueDebugEvent(Code = %u, Process = %04X, Thread = %04X):", debugEvent.dwDebugEventCode, debugEvent.dwProcessId, debugEvent.dwThreadId);
                    result = dbg::svr::Debugger::ContinueDebugEvent(debugEvent, continueStatus);
                    debugf(dbg, "Result = %d", int(result));
                    if (result)
                    {
                        WakeForState(ContinueDebugEventResult_State);
                    }
                    break;

                case ContinueDebugEventResult_State:
                    WaitForState(WaitForDebugEventNeeded_State);
                    break;
                }
            }
        }

        bool Debugger::PeekForState(State resultType, State waitingType)
        {
            ::WaitOnAddress(&state, &waitingType, sizeof(waitingType), 0);
            return state == resultType;
        }

        bool Debugger::WaitForState(State resultType)
        {
            auto actualType = resultType;
            do
            {
                if (actualType != NoEvent_State)
                {
                    ::WaitOnAddress(&state, &actualType, sizeof(actualType), INFINITE);
                }
                else
                {
                    return false;
                }
            }
            while ((actualType = state) != resultType);
            return true;
        }

        void Debugger::WakeForState(State neededType)
        {
            state = neededType;
            ::WakeByAddressSingle(&state);
        }

        int Debugger::exec(DWORD pid)
        {
            int result = -1;

            qt_MainWindow MainWindow;

            mainWindow = &MainWindow;

            if (attachToProcess(pid))
            {
                mainWindow->actionStepIn()->setDisabled(true);
                mainWindow->actionStepOver()->setDisabled(true);
                mainWindow->actionStepOut()->setDisabled(true);

                MainWindow.show();

                result = QApplication::exec();
            }

            return result;
        }

    }
}

