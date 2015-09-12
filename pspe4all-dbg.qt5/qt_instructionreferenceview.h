/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "qt_textview.h"

#include <QColumnView>

class qt_InstructionReferenceView : public qt_TextView
{
    Q_OBJECT

    QComboBox *comboBox4arch_;
    QListView *listView4insn_;

public:
    qt_InstructionReferenceView(QWidget *parent = 0);

public slots:
    void onArchitectureSelection(int);
    void onInstructionSelection(const QModelIndex & index);
};