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
            connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));

            connect(this, SIGNAL(log(QString)), this, SLOT(onLog(QString)), Qt::BlockingQueuedConnection);
            connect(this, SIGNAL(enableStepping()), this, SLOT(onEnableStepping()), Qt::BlockingQueuedConnection);
            connect(this, SIGNAL(disableStepping()), this, SLOT(onDisableStepping()), Qt::BlockingQueuedConnection);
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

            qt_MainWindow MainWindow;

            m_qMainWindow = &MainWindow;

            if (attachToProcess(pid))
            {
                onEnableStepping();

                MainWindow.show();

                result = QApplication::exec();
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
            return dbg::svr::Debugger::DebuggerLoop();
        }

        bool const Debugger::Continue(const bool bIsStepping)
        {
            return dbg::svr::Debugger::Continue(bIsStepping);
        }

        bool const Debugger::WaitForContinue()
        {
            //QTimer::singleShot(0, Qt::PreciseTimer, this, SLOT(onEnableStepping()));
            emit enableStepping();

            auto result = dbg::svr::Debugger::WaitForContinue();

            //QTimer::singleShot(0, Qt::PreciseTimer, this, SLOT(onDisableStepping()));
            emit disableStepping();

            return result;
        }

        void Debugger::onEnableStepping()
        {
            m_qMainWindow->setStatusText("Press F5 to continue, F10 to step over, F11 to step into, Shift+F11 to step out.");
            m_qMainWindow->actionContinue()->setEnabled(true);
            m_qMainWindow->actionStop()->setEnabled(false);
            m_qMainWindow->actionStepInto()->setEnabled(true);
            m_qMainWindow->actionStepOver()->setEnabled(true);
            m_qMainWindow->actionStepOut()->setEnabled(true);
        }

        void Debugger::onDisableStepping()
        {
            m_qMainWindow->setStatusText("Press Shift+F5 to stop.");
            m_qMainWindow->actionContinue()->setEnabled(false);
            m_qMainWindow->actionStop()->setEnabled(true);
            m_qMainWindow->actionStepInto()->setEnabled(false);
            m_qMainWindow->actionStepOver()->setEnabled(false);
            m_qMainWindow->actionStepOut()->setEnabled(false);
        }

        void Debugger::onLog(const QString &text)
        {
            m_qMainWindow->logView()->log(text);
        }

        void Debugger::OutputDebugStringA(char const message[])
        {
            emit log(QString(message));
        }

        void Debugger::OutputDebugStringW(wchar_t const message[])
        {
            emit log(QString::fromWCharArray(message));
        }
    }
}
