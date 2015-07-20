/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QtConcurrent/QtConcurrent>

#include "qt_mainwindow.h"

namespace dbg
{
    namespace qt5
    {
        struct Debugger final : QApplication, dbg::svr::Debugger
        {
            Q_OBJECT

        public:
            Debugger() = delete;
            Debugger(int &argc, char **argv, int flags = ApplicationFlags);
            Debugger(const Debugger &copy) = delete;
            Debugger &operator=(const Debugger &copy) = delete;

            ~Debugger() = default;

            int exec(DWORD pid);

            bool const attachToProcess(DWORD pid);

        signals:
            void enableStepping();
            void disableStepping();
            void log(const QString&);

        public slots:
            void onAboutToQuit();
            void onContinue();
            void onStop();
            void onStepOver();
            void onStepInto();
            void onStepOut();
            void onEnableStepping();
            void onDisableStepping();
            void onLog(const QString &);

        protected:
            static DWORD WINAPI run(LPVOID lpParameters);

            virtual bool const DebuggerLoop() override;
            virtual bool const Continue(const bool bIsStepping) override;
            virtual bool const WaitForContinue() override;
            virtual void       OutputDebugStringA(char const message[]) override;
            virtual void       OutputDebugStringW(wchar_t const message[]) override;

        private:
            qt_MainWindow * m_qMainWindow;
            HANDLE          m_hProcSyncEvent;
        };
    }
}
