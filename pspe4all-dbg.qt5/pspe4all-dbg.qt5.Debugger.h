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
        struct Debugger : QApplication, dbg::svr::Debugger, QRunnable
        {
            Q_OBJECT
        public:

            Debugger(int &argc, char **argv, int flags = ApplicationFlags);

            ~Debugger();

            bool attachToProcess(DWORD pid);
            bool continueDebugEvent();

            int exec(DWORD pid);

        public slots:
            void onAboutToQuit();
            void onContinue();
            void onStop();
            void onStepOver();
            void onStepIn();
            void onStepOut();
            void enableStepping();
            void disableStepping();

        protected:
            virtual void run() override;

            virtual DWORD OnExceptionEvent(DWORD ThreadId, EXCEPTION_DEBUG_INFO const & Info) override;

        private:
            enum State
            {
                NoEvent_State,
                AttachToProcessNeeded_State,
                AttachToProcessResult_State,
                WaitForDebugEventNeeded_State,
                WaitForDebugEventResult_State,
                ContinueDebugEventNeeded_State,
                ContinueDebugEventResult_State
            };

            enum StepMode
            {
                None_StepMode,
                Continue_StepMode,  // F5
                Stop_StepMode,      // Shift+F5
                StepOver_StepMode,  // F10
                StepIn_StepMode,    // F11
                StepOut_StepMode    // Shift+F11
            };

            enum StepAction
            {
                None_StepAction,

            };

            qt_MainWindow         * mainWindow;
            DEBUG_EVENT             debugEvent;
            DWORD                   continueStatus;
            State                   state;
            u8                    * stepping;
            StepMode                stepMode;
            QThreadPool             threadpool;
            QMap< u32, u32 * >      breakpoints;
            bool                    result;

            bool PeekForState(State resultType, State waitingType);
            bool WaitForState(State resultType);
            void WakeForState(State neededType);
        };
    }
}
