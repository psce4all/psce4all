/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "qt_memoryviewer.h"
#include "qt_logview.h"

class qt_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    qt_MainWindow(QWidget *parent = 0);
    ~qt_MainWindow();

    QAction * actionContinue() { return actionContinue_; }
    QAction * actionStop()     { return actionStop_; }
    QAction * actionStepInto()   { return actionStepInto_; }
    QAction * actionStepOver() { return actionStepOver_; }
    QAction * actionStepOut()  { return actionStepOut_; }

    qt_LogView    * logView() { return logView_; }

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private:
    void createWidgets();
    void createActions();
    void createMenus();
    void loadSettings();
    void saveSettings();

public slots:
    void setStatusText(const QString &text);

private:
    QAction         *quitAction_;

    QAction         *actionContinue_;
    QAction         *actionStop_;
    QAction         *actionStepInto_;
    QAction         *actionStepOver_;
    QAction         *actionStepOut_;

    QAction         *instructionsViewAction_;
    QAction         *memoryViewAction_;
    QAction         *logViewAction_;

    QDockWidget     *instructionsViewDock_;
    QWidget         *instructionsViewWidget_;

    QDockWidget     *memoryViewDock_;
    qt_MemoryViewer *memoryViewWidget_;

    qt_LogView      *logView_;

    QMenuBar        *menuBar_;
    QToolBar        *mainToolBar_;
    QLabel          *statusLabel_;
    QProgressBar    *statusProgressBar_;
    QStatusBar      *statusBar_;

    QSettings       *settings_;
};
