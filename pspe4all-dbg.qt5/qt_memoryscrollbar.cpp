#include "stdafx.h"
#include "qt_memoryscrollbar.h"

qt_MemoryScrollbar::qt_MemoryScrollbar(QWidget *parent)
	: QScrollBar(parent)
{

}
qt_MemoryScrollbar::qt_MemoryScrollbar(Qt::Orientation orientation, QWidget *parent)
   : QScrollBar(orientation, parent)
{

}
qt_MemoryScrollbar::~qt_MemoryScrollbar()
{

}
void qt_MemoryScrollbar::changeRange(int min, int max)
{
  QScrollBar::setRange(min, max);
}