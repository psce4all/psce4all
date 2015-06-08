/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_mainwindow.h"

qt_MainWindow::qt_MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(actionStepIn(), SIGNAL(triggered()), qApp, SLOT(onStepIn()));
    connect(actionStepOver(), SIGNAL(triggered()), qApp, SLOT(onStepOver()));
    connect(actionStepOut(), SIGNAL(triggered()), qApp, SLOT(onStepOut()));
}

qt_MainWindow::~qt_MainWindow()
{

}
