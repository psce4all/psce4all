/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "pspe4all-dbg.qt5.Debugger.h"
#include "qt_mainwindow.h"
#include "qt_instructionsmodel.h"

#include <synchapi.h>
#pragma comment(lib, "synchronization.lib")

namespace dbg
{
    namespace qt5
    {
        Debugger::Debugger(int &argc, char **argv, int flags)
            : QApplication(argc, argv, flags)
            , instructions_(new qt_Instructions)
			, pc_(new u32)
        {
            connect(qApp, &QCoreApplication::aboutToQuit, this, &Debugger::onAboutToQuit);

            connect(this, &Debugger::log, this, &Debugger::onLog, Qt::BlockingQueuedConnection);
            connect(this, &Debugger::enableStepping, this, &Debugger::onEnableStepping, Qt::BlockingQueuedConnection);
            connect(this, &Debugger::disableStepping, this, &Debugger::onDisableStepping, Qt::BlockingQueuedConnection);
        }

        void Debugger::onAboutToQuit()
        {
            dbg::svr::Debugger::Continue();
            QThread::msleep(100);
        }

        void Debugger::onContinue()
        {
            dbg::svr::Debugger::Continue();
        }

        void Debugger::onStop()
        {
            dbg::svr::Debugger::Stop();
        }

        void Debugger::onStepOver()
        {
            dbg::svr::Debugger::StepOver();
        }

        void Debugger::onStepInto()
        {
            dbg::svr::Debugger::StepInto();
        }

        void Debugger::onStepOut()
        {
            dbg::svr::Debugger::StepOut();
        }

        DWORD WINAPI Debugger::run(LPVOID lpParameters)
        {
            Debugger *pDebugger = (Debugger *)lpParameters;

            return pDebugger->Start();
        }

        int Debugger::exec(DWORD pid)
        {
            int result = -1;

            char procsync_name[256];
            snprintf(procsync_name, 255, "pspe4all-dbg-%u", pid);

            hProcSyncEvent_ = ::OpenEventA(EVENT_MODIFY_STATE, FALSE, procsync_name);
            if (hProcSyncEvent_)
            {
                qt_MainWindow MainWindow(nullptr, instructions_, pc_);

                mainWindow_ = &MainWindow;

                if (attachToProcess(pid))
                {
                    onEnableStepping();

                    MainWindow.show();

                    result = QApplication::exec();
                }

                ::CloseHandle(hProcSyncEvent_);
            }

            return result;
        }

        bool const Debugger::attachToProcess(DWORD pid)
        {
            m_dwProcessId = pid;

            DWORD dwThreadId = 0;

            HANDLE hDebugThread = ::CreateThread(nullptr, 0, run, this, 0, &dwThreadId);

            if (hDebugThread == nullptr)
            {
                errorf(dbg, "Could not run the debugger thread. Error = %X", ::GetLastError());

                return false;
            }

            return true;
        }

        bool const Debugger::DebuggerLoop()
        {
            ::SetEvent(hProcSyncEvent_);

            return dbg::svr::Debugger::DebuggerLoop();
        }

        bool const Debugger::Continue(const bool bIsStepping)
        {
            return dbg::svr::Debugger::Continue(bIsStepping);
        }

        bool const Debugger::WaitForContinue()
        {
            emit enableStepping();

            auto result = dbg::svr::Debugger::WaitForContinue();

            emit disableStepping();

            return result;
        }

        void Debugger::onEnableStepping()
        {
            mainWindow_->setStatusText("Press F5 to continue, F10 to step over, F11 to step into, Shift+F11 to step out.");
            mainWindow_->actionContinue()->setEnabled(true);
            mainWindow_->actionStop()->setEnabled(false);
            mainWindow_->actionStepInto()->setEnabled(true);
            mainWindow_->actionStepOver()->setEnabled(true);
            mainWindow_->actionStepOut()->setEnabled(true);
            mainWindow_->updateAllViews();
        }

        void Debugger::onDisableStepping()
        {
            mainWindow_->setStatusText("Press Shift+F5 to stop.");
            mainWindow_->actionContinue()->setEnabled(false);
            mainWindow_->actionStop()->setEnabled(true);
            mainWindow_->actionStepInto()->setEnabled(false);
            mainWindow_->actionStepOver()->setEnabled(false);
            mainWindow_->actionStepOut()->setEnabled(false);
        }

        void Debugger::onLog(const QString &text)
        {
            mainWindow_->logView()->log(text);
        }

        void Debugger::OutputDebugStringA(char const message[])
        {
            emit log(QString(message));
        }

        void Debugger::OutputDebugStringW(wchar_t const message[])
        {
            emit log(QString::fromWCharArray(message));
        }

        void Debugger::OnNewGuestInstruction(u32 address, size_t address_x86_64, size_t size_x86_64)
        {
            static auto hint = instructions_->end();
            auto data = *p32u32(address);
            hint = instructions_->emplace_hint(hint, std::move(address), qt_Instruction{ address, data, 4, address_x86_64, size_x86_64 });
        }

		void Debugger::OnCurrentGuestInstruction(u32 address)
		{
			*pc_ = address;
		}
	}
}
