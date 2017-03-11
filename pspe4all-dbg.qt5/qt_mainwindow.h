/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "qt_instruction.h"
#include "qt_instructionsview.h"
#include "qt_memoryview.h"
#include "qt_logview.h"
#include "qt_instructionreferenceview.h"
#include "qt_jumpdisplaydelegate.h"

class qt_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    qt_MainWindow(QWidget * parent, std::shared_ptr< qt_Instructions > instructions);
    ~qt_MainWindow();

    QAction * actionContinue() { return actionContinue_; }
    QAction * actionStop()     { return actionStop_; }
    QAction * actionStepInto() { return actionStepInto_; }
    QAction * actionStepOver() { return actionStepOver_; }
    QAction * actionStepOut()  { return actionStepOut_; }

    qt_LogView * logView() { return logView_; }

    void updateAllViews();

protected:
    virtual void closeEvent(QCloseEvent * event) override;

private:
    void createWidgets();
    void createActions();
    void createMenus();
    void loadSettings();
    void saveSettings();

public slots:
    void setStatusText(QString const & text);

private:
    QAction                           * quitAction_;

    QAction                           * actionContinue_;
    QAction                           * actionStop_;
    QAction                           * actionStepInto_;
    QAction                           * actionStepOver_;
    QAction                           * actionStepOut_;

    QAction                           * instructionsViewAction_;
    QAction                           * memoryViewAction_;
    QAction                           * logViewAction_;
    QAction                           * instructionReferenceViewAction_;

    qt_InstructionsView               * instructionsView_;
    qt_MemoryView                     * memoryView_;
    qt_LogView                        * logView_;
    qt_InstructionReferenceView       * instructionReferenceView_;

    qt_JumpDisplayDelegate            * backwardItemDelegate_;
    qt_JumpDisplayDelegate            * forwardItemDelegate_;

    QMenuBar                          * menuBar_;
    QToolBar                          * mainToolBar_;
    QLabel                            * statusLabel_;
    QProgressBar                      * statusProgressBar_;
    QStatusBar                        * statusBar_;

    QSettings                         * settings_;
    std::shared_ptr< qt_Instructions >  instructions_;
};
