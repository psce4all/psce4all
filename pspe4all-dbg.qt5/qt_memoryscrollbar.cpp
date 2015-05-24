/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

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