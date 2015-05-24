/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "ui_qt_memoryviewer.h"

class qt_MemoryViewer : public QWidget
{
    Q_OBJECT

public:
    qt_MemoryViewer(QWidget *parent = 0);
    ~qt_MemoryViewer();
    void updateMemoryViewer();

private:
    Ui::memory_viewer ui;
};
