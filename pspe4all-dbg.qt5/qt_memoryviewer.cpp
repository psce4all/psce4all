/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_memoryviewer.h"

qt_MemoryViewer::qt_MemoryViewer(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

qt_MemoryViewer::~qt_MemoryViewer()
{
}
void qt_MemoryViewer::updateMemoryViewer()
{
    ui.memory_widget->update();
}
