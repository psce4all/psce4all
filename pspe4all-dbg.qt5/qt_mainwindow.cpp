/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_mainwindow.h"
#include "qt_instruction.h"
#include "qt_instructionsmodel.h"
#include "qt_webview.h"

//#include <QWebSettings>

qt_MainWindow::qt_MainWindow(QWidget *parent, std::shared_ptr< qt_Instructions > instructions)
    : QMainWindow(parent)
    , instructions_(instructions)
{
    setFont(QFont("Monospace", 8));

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

    backwardItemDelegate_ = new qt_JumpDisplayDelegate(false, this);
    forwardItemDelegate_ = new qt_JumpDisplayDelegate(true, this);

    instructionsView_ = new qt_InstructionsView(this);
    instructionsView_->setObjectName(QStringLiteral("InstructionsView"));
    instructionsView_->treeView()->setItemDelegateForColumn(qt_InstructionsModel::IMC_BACKWARD_JUMP, backwardItemDelegate_);
    instructionsView_->treeView()->setItemDelegateForColumn(qt_InstructionsModel::IMC_FORWARD_JUMP, forwardItemDelegate_);

    addDockWidget(Qt::TopDockWidgetArea, instructionsView_);

    memoryView_ = new qt_MemoryView(tr("Memory"), this);
    memoryView_->setObjectName(QStringLiteral("MemoryView"));
    addDockWidget(Qt::TopDockWidgetArea, memoryView_);

    logView_ = new qt_LogView(this);
    logView_->setObjectName(QStringLiteral("LogView"));
    addDockWidget(Qt::BottomDockWidgetArea, logView_);

    instructionReferenceView_ = new qt_InstructionReferenceView(this);
    instructionReferenceView_->setObjectName(QStringLiteral("InstructionReferenceView"));
    addDockWidget(Qt::TopDockWidgetArea, instructionReferenceView_);

    //qt_WebView * webView = new qt_WebView(tr("Markdown Test"), this);
    //webView->setObjectName(QStringLiteral("MarkdownTest"));
    //addDockWidget(Qt::TopDockWidgetArea, webView);
    //QFile file("markdown.md");
    //if (file.open(QIODevice::ReadOnly))
    //{
    //    webView->webView()->settings()->setUserStyleSheetUrl(QUrl::fromLocalFile("./assets/markdown.css"));
    //    webView->setMarkdownDocument(QString::fromUtf8(file.readAll()));
    //}

    tabifyDockWidget(instructionReferenceView_, memoryView_);
    //tabifyDockWidget(instructionReferenceView_, webView);

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

    instructionsViewAction_ = instructionsView_->toggleViewAction();
    instructionsViewAction_->setText(tr("&Instructions"));
    instructionsViewAction_->setShortcut(Qt::ALT + Qt::Key_I);

    memoryViewAction_ = memoryView_->toggleViewAction();
    memoryViewAction_->setText(tr("&Memory"));
    memoryViewAction_->setShortcut(Qt::ALT + Qt::Key_M);

    logViewAction_ = logView_->toggleViewAction();
    logViewAction_->setText(tr("&Log"));
    logViewAction_->setShortcut(Qt::ALT + Qt::Key_L);

    instructionReferenceViewAction_ = instructionReferenceView_->toggleViewAction();
    instructionReferenceViewAction_->setText(tr("instruction &Reference"));
    instructionReferenceViewAction_->setShortcut(Qt::ALT + Qt::Key_R);
}

void qt_MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAction_);

    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(instructionsViewAction_);
    viewMenu->addAction(memoryViewAction_);
    viewMenu->addAction(logViewAction_);
    viewMenu->addSeparator();
    viewMenu->addAction(instructionReferenceViewAction_);
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
            else
            {
                textView->setDocumentFont(QFont("Consolas", 8));
            }
        }
        else if (auto treeView = qobject_cast< qt_TreeView * >(child))
        {
            if (!treeView->objectName().isEmpty())
            {
                treeView->setDocumentFont(settings_->value(treeView->objectName() + ".font", treeView->documentFont()).value<QFont>());
            }
            else
            {
                treeView->setDocumentFont(QFont("Consolas", 8));
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
        else if (auto treeView = qobject_cast< qt_TreeView * >(child))
        {
            if (!treeView->objectName().isEmpty())
            {
                settings_->setValue(treeView->objectName() + ".font", treeView->documentFont());
            }
        }
    }
}

void qt_MainWindow::setStatusText(const QString &text)
{
    statusLabel_->setText(text);
}

void qt_MainWindow::updateAllViews()
{
    auto model = new qt_InstructionsModel(this, instructions_);
    instructionsView_->setModel(model);
    forwardItemDelegate_->update(model->getInstructions(), 60);
    backwardItemDelegate_->update(model->getInstructions(), 60);
}
