/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "ui_qt_mainwindow.h"

class qt_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    qt_MainWindow(QWidget *parent = 0);
    ~qt_MainWindow();

private:
    Ui::main_window ui;
};
