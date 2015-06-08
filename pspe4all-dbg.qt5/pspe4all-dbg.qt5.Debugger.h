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

            virtual void run() override;

        public slots:
            void onAboutToQuit();
            void onStepIn();
            void onStepOver();
            void onStepOut();
            void enableStepping();
            void disableStepping();

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

            qt_MainWindow         * mainWindow;
            DEBUG_EVENT             debugEvent;
            DWORD                   continueStatus;
            State                   state;
            QThreadPool             threadpool;
            bool                    result;

            bool PeekForState(State resultType, State waitingType);
            bool WaitForState(State resultType);
            void WakeForState(State neededType);
        };
    }
}
