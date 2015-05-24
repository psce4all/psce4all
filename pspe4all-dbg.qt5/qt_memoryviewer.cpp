#include "stdafx.h"
#include "types.h"
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
