/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "qt_textview.h"

class qt_LogView : public qt_TextView
{
    Q_OBJECT

public:
    qt_LogView(QWidget *parent = 0);

public slots:
    void log(const QString &text);
};