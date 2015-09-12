/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QFrame>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>
#include <QDockWidget>

#include "qt_memoryscrollbar.h"
#include "qt_memoryspinbox.h"
//#include "qt_hexedit.h"
#include "qt_hexwidget.h"

class qt_MemoryView : public QDockWidget
{
    Q_OBJECT

    QVBoxLayout                 *verticalLayout_;
    QHBoxLayout                 *horizontalLayout_;
    QLabel                      *memoryAddressGotoLabel_;
    qt_MemorySpinBox            *memoryAddressGotoSpinbox_;
    QComboBox                   *memoryAddressRangeCombobox_;
    //qt_HexEdit                  *memoryWidget_;
    qt_HexWidget                *memoryWidget_;

    bool                         doNotProceed_;

public:
    qt_MemoryView(const QString &title, QWidget *parent = 0);
    ~qt_MemoryView();
    void updateMemoryView();

public slots:
    void changeAddressRange(int);
    void changeAddress(int);
    void updateAddressGotoSpinboxValue();
};
