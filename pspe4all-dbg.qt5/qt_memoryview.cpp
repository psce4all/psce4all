/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_memoryview.h"

qt_MemoryView::qt_MemoryView(const QString &title, QWidget *parent)
    : QDockWidget(title, parent), doNotProceed_(false)
{
    QWidget *widget = new QWidget(this);

    memoryAddressGotoSpinbox_ = new qt_MemorySpinBox(this);
    memoryAddressGotoSpinbox_->setObjectName(QStringLiteral("MemoryAddressGotoSpinbox"));
    memoryAddressGotoSpinbox_->setMinimumSize(QSize(130, 0));
    memoryAddressGotoSpinbox_->setMaximumSize(QSize(100, 16777215));
    memoryAddressGotoSpinbox_->setAccelerated(true);
    memoryAddressGotoSpinbox_->setMinimum(-2147483647);
    memoryAddressGotoSpinbox_->setMaximum(2147483647);

    memoryAddressGotoLabel_ = new QLabel(this);
    memoryAddressGotoLabel_->setObjectName(QStringLiteral("MemoryAddressGotoLabel"));
    memoryAddressGotoLabel_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    memoryAddressGotoLabel_->setBuddy(memoryAddressGotoSpinbox_);

    memoryAddressRangeCombobox_ = new QComboBox(this);
    memoryAddressRangeCombobox_->setObjectName(QStringLiteral("MemoryAddressRangeCombobox"));
    memoryAddressRangeCombobox_->setMaximumSize(QSize(16777215, 16777215));

    //memoryWidget_ = new qt_HexEdit(this);
    memoryWidget_ = new qt_HexWidget(this);
    memoryWidget_->setObjectName(QStringLiteral("MemoryWidget"));

    horizontalLayout_ = new QHBoxLayout(this);
    horizontalLayout_->setObjectName(QStringLiteral("HorizontalLayout"));
    horizontalLayout_->addWidget(memoryAddressGotoLabel_);
    horizontalLayout_->addWidget(memoryAddressGotoSpinbox_);
    horizontalLayout_->addWidget(memoryAddressRangeCombobox_);

    verticalLayout_ = new QVBoxLayout(widget);
    verticalLayout_->setObjectName(QStringLiteral("VerticalLayout"));
    verticalLayout_->setContentsMargins(0, 0, 0, 0);
    verticalLayout_->addLayout(horizontalLayout_);
    verticalLayout_->addWidget(memoryWidget_);

    setWidget(widget);

    memoryAddressGotoLabel_->setText(QApplication::translate("MemoryView", "Address:", 0));
    memoryAddressRangeCombobox_->clear();
    memoryAddressRangeCombobox_->insertItems(0, QStringList()
                                                << QApplication::translate("MemoryView", "08800000-0BFFFFFF : user main memory", 0)
                                                << QApplication::translate("MemoryView", "08000000-087FFFFF : kernel main ram", 0)
                                                << QApplication::translate("MemoryView", "04000000-047FFFFF : video ram", 0)
                                                << QApplication::translate("MemoryView", "00010000-00013FFF : scratch pad", 0)
                                            );

    QObject::connect(memoryAddressRangeCombobox_, SIGNAL(currentIndexChanged(int)), this, SLOT(changeAddressRange(int)));
    QObject::connect(memoryAddressGotoSpinbox_, SIGNAL(valueChanged(int)), this, SLOT(changeAddress(int)));
    QObject::connect(memoryWidget_->verticalScrollBar(), SIGNAL(sliderMoved(int)), this, SLOT(updateAddressGotoSpinboxValue()));

    changeAddressRange(0);
    changeAddress(0x08800000);
}

qt_MemoryView::~qt_MemoryView()
{
}

void qt_MemoryView::updateMemoryView()
{
    memoryWidget_->update();
}

void qt_MemoryView::changeAddressRange(int choice)
{
    int start, end;
    switch (choice)
    {
    case 0:
        start = 0x08800000;
        end = 0x0C000000;
        break;
    case 1:
        start = 0x08000000;
        end = 0x08800000;
        break;
    case 2:
        start = 0x04000000;
        end = 0x04400000;
        break;
    case 3:
        start = 0x00010000;
        end = 0x00014000;
        break;
    default:
        return;
    }
    
    memoryWidget_->setData(QByteArray::fromRawData(p32< char >(start), end - start));
    memoryWidget_->setAddressOffset(start);
    memoryAddressGotoSpinbox_->setRange(start, end);
}

void qt_MemoryView::changeAddress(int address)
{
    memoryWidget_->setAddressOffset(address);
}

void qt_MemoryView::updateAddressGotoSpinboxValue()
{
}
