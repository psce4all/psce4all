/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QtConcurrent/QtConcurrent>

#include "qt_mainwindow.h"
#include "qt_instruction.h"

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

            static Debugger * application() { return static_cast<Debugger *>(qApp); }

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
            virtual void       OnNewGuestInstruction(u32 address, size_t address_x86_64, size_t size_x86_64) override;
			virtual void       OnCurrentGuestInstruction(u32 address) override;
		
		private:
            qt_MainWindow                     *mainWindow_;
            HANDLE                             hProcSyncEvent_;
            std::shared_ptr< qt_Instructions > instructions_;
			std::shared_ptr< u32 >             pc_;
		};
    }
}
