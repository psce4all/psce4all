/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

class qt_MemoryScrollbar : public QScrollBar
{
    Q_OBJECT

public:
    qt_MemoryScrollbar(QWidget *parent = 0);
    qt_MemoryScrollbar(Qt::Orientation orientation, QWidget *parent = 0);
    ~qt_MemoryScrollbar();

public slots:
    void changeRange(int min, int max);

};
