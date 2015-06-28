/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_mainwindow.h"

qt_MainWindow::qt_MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setDockNestingEnabled(true);
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);

    createWidgets();
    createActions();
    createMenus();

    settings_ = new QSettings("psce4all", "pspe4all.dbg.qt5", this);

    loadSettings();
}

qt_MainWindow::~qt_MainWindow()
{

}

void qt_MainWindow::createWidgets()
{
    statusLabel_ = new QLabel(this);
    statusLabel_->setMargin(3);

    statusProgressBar_ = new QProgressBar(this);
    statusProgressBar_->setTextVisible(false);
    statusProgressBar_->setRange(0, 0);

    statusBar()->addPermanentWidget(statusLabel_, 1);
    statusBar()->addPermanentWidget(statusProgressBar_, 0);

    instructionsViewDock_ = new QDockWidget(tr("Instructions"), this);
    instructionsViewDock_->setObjectName(QStringLiteral("InstructionsViewDock"));
    instructionsViewWidget_ = new QWidget(this);
    instructionsViewWidget_->setObjectName(QStringLiteral("InstructionsView"));
    instructionsViewDock_->setWidget(instructionsViewWidget_);
    addDockWidget(Qt::TopDockWidgetArea, instructionsViewDock_);

    memoryViewDock_ = new QDockWidget(tr("Memory"), this);
    memoryViewDock_->setObjectName(QStringLiteral("MemoryViewDock"));
    memoryViewWidget_ = new qt_MemoryViewer();
    memoryViewWidget_->setObjectName(QStringLiteral("MemoryView"));
    memoryViewDock_->setWidget(memoryViewWidget_);
    addDockWidget(Qt::TopDockWidgetArea, memoryViewDock_);

    logView_ = new qt_LogView(this);
    logView_->setObjectName(QStringLiteral("LogView"));
    addDockWidget(Qt::BottomDockWidgetArea, logView_);

    mainToolBar_ = new QToolBar(this);
    mainToolBar_->setObjectName(QStringLiteral("MainToolBar"));
    addToolBar(Qt::TopToolBarArea, mainToolBar_);
}

void qt_MainWindow::createActions()
{
    quitAction_ = new QAction(tr("&Quit"), this);
    quitAction_->setShortcuts(QKeySequence::Quit);
    connect(quitAction_, SIGNAL(triggered()), this, SLOT(close()));

    actionContinue_ = new QAction(this);
    actionContinue_->setObjectName(QStringLiteral("ActionContinue"));
    QIcon icon0;
    icon0.addFile(QStringLiteral(":/pspe4alldbgqt5/res/PlayIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionContinue_->setIcon(icon0);
    actionContinue_->setShortcut(Qt::Key_F5);
    connect(actionContinue_, SIGNAL(triggered()), qApp, SLOT(onContinue()));

    actionStop_ = new QAction(this);
    actionStop_->setObjectName(QStringLiteral("ActionStop"));
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/pspe4alldbgqt5/res/PauseIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionStop_->setIcon(icon1);
    actionStop_->setShortcut(Qt::SHIFT + Qt::Key_F5);
    connect(actionStop_, SIGNAL(triggered()), qApp, SLOT(onStop()));

    actionStepInto_ = new QAction(this);
    actionStepInto_->setObjectName(QStringLiteral("ActionStepInto"));
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/pspe4alldbgqt5/res/StepIntoIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionStepInto_->setIcon(icon2);
    actionStepInto_->setShortcut(Qt::Key_F11);
    connect(actionStepInto_, SIGNAL(triggered()), qApp, SLOT(onStepInto()));

    actionStepOver_ = new QAction(this);
    actionStepOver_->setObjectName(QStringLiteral("ActionStepOver"));
    QIcon icon3;
    icon3.addFile(QStringLiteral(":/pspe4alldbgqt5/res/StepOverIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionStepOver_->setIcon(icon3);
    actionStepOver_->setShortcut(Qt::Key_F10);
    connect(actionStepOver_, SIGNAL(triggered()), qApp, SLOT(onStepOver()));

    actionStepOut_ = new QAction(this);
    actionStepOut_->setObjectName(QStringLiteral("ActionStepOut"));
    QIcon icon4;
    icon4.addFile(QStringLiteral(":/pspe4alldbgqt5/res/StepOutIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionStepOut_->setIcon(icon4);
    actionStepOut_->setShortcut(Qt::SHIFT + Qt::Key_F11);
    connect(actionStepOut_, SIGNAL(triggered()), qApp, SLOT(onStepOut()));

    mainToolBar_->addAction(actionContinue_);
    mainToolBar_->addAction(actionStop_);
    mainToolBar_->addSeparator();
    mainToolBar_->addAction(actionStepInto_);
    mainToolBar_->addAction(actionStepOver_);
    mainToolBar_->addAction(actionStepOut_);

    instructionsViewAction_ = instructionsViewDock_->toggleViewAction();
    instructionsViewAction_->setText(tr("&Instructions"));
    instructionsViewAction_->setShortcut(Qt::ALT + Qt::Key_I);

    memoryViewAction_ = memoryViewDock_->toggleViewAction();
    memoryViewAction_->setText(tr("&Memory"));
    memoryViewAction_->setShortcut(Qt::ALT + Qt::Key_M);

    logViewAction_ = logView_->toggleViewAction();
    logViewAction_->setText(tr("&Log"));
    logViewAction_->setShortcut(Qt::ALT + Qt::Key_L);
}

void qt_MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAction_);

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(instructionsViewAction_);
    viewMenu->addAction(memoryViewAction_);
    viewMenu->addAction(logViewAction_);
}

void qt_MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    QMainWindow::closeEvent(event);
}

void qt_MainWindow::loadSettings()
{
    if (parent() == nullptr)
    {
        restoreGeometry(settings_->value("geometry", saveGeometry()).toByteArray());
    }
    restoreState(settings_->value("windowState", saveState()).toByteArray());

    foreach(QObject *child, children())
    {
        if (auto textView = qobject_cast< qt_TextView * >(child))
        {
            if (!textView->objectName().isEmpty())
            {
                textView->setDocumentFont(settings_->value(textView->objectName() + ".font", textView->documentFont()).value<QFont>());
            }
        }
    }
}

void qt_MainWindow::saveSettings()
{
    if (parent() == nullptr)
    {
        settings_->setValue("geometry", saveGeometry());
    }
    settings_->setValue("windowState", saveState());

    foreach(QObject *child, children())
    {
        if (auto textView = qobject_cast< qt_TextView * >(child))
        {
            if (!textView->objectName().isEmpty())
            {
                settings_->setValue(textView->objectName() + ".font", textView->documentFont());
            }
        }
    }
}

void qt_MainWindow::setStatusText(const QString &text)
{
    statusLabel_->setText(text);
}
