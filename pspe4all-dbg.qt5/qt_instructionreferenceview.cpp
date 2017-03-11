/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_instructionreferenceview.h"

qt_InstructionReferenceView::qt_InstructionReferenceView(QWidget *parent)
    : qt_TextView(tr("Instruction Reference"), parent)
{
    QStringList architectures;
    QStandardItemModel *model = new QStandardItemModel(this);

    architectures << "X86-64" << "ALLEGREX" << "MIPS32";

    bool ok = false;

    foreach (auto & architecture, architectures)
    {
        QFile file("assets/instructions/" + architecture + ".txt");
        if (file.open(QIODevice::ReadOnly))
        {
            QString contents(QString::fromUtf8(file.readAll()));
            QStringList instructions = contents.split(QChar('\f'), QString::SkipEmptyParts);
            if (instructions.size())
            {
                QStandardItem *architectureItem = new QStandardItem(architecture);
                architectureItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                ok = true;

                foreach (auto & instruction, instructions)
                {
                    QStringList fields = instruction.split(QChar('\t'), QString::KeepEmptyParts);

                    if (fields.size() == 2)
                    {
                        QStandardItem *mnemonicItem = new QStandardItem(fields.at(0));
                        mnemonicItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren);
                        mnemonicItem->setData(fields.at(1), 257);
                        architectureItem->appendRow(mnemonicItem);
                    }
                }

                model->appendRow(architectureItem);
            }

            file.close();
        }
    }

    if (ok)
    {
        comboBox4arch_ = new QComboBox(this);
        comboBox4arch_->setModel(model);
        comboBox4arch_->setMaximumWidth(132);
        comboBox4arch_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
        connect(comboBox4arch_, static_cast< void (QComboBox::*)(int) >(&QComboBox::activated), this, &qt_InstructionReferenceView::onArchitectureSelection);

        listView4insn_ = new QListView(this);
        listView4insn_->setResizeMode(QListView::Adjust);
        listView4insn_->setMaximumWidth(132);
        listView4insn_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        connect(listView4insn_, &QListView::activated, this, &qt_InstructionReferenceView::onInstructionSelection);

        onArchitectureSelection(0);

        QWidget * widget = new QWidget(this);
        QVBoxLayout * verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("VerticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->addWidget(comboBox4arch_);
        verticalLayout->addWidget(listView4insn_);

        QSplitter * splitter = new QSplitter(this);
        splitter->setObjectName(QStringLiteral("Splitter"));
        splitter->addWidget(widget);
        splitter->addWidget(qt_TextView::widget());
        splitter->setCollapsible(1, false);
        splitter->setStretchFactor(0, 0);
        splitter->setStretchFactor(1, 1);

        setWidget(splitter);
    }
    else
    {
        setWidget(new QLabel("No Instruction Set Architectures available", this));
    }
}

void qt_InstructionReferenceView::onArchitectureSelection(int row)
{
    auto model = comboBox4arch_->model();
    auto index = model->index(row, 0);
    if (index.isValid())
    {
        listView4insn_->setModel(model);
        listView4insn_->setRootIndex(index);
    }
    else
    {
        listView4insn_->setModel(0);
    }
}

void qt_InstructionReferenceView::onInstructionSelection(const QModelIndex & index)
{
    QString text = index.data(257).toString();
    if (text.startsWith("-R:"))
    {
        QString name = text.mid(3);
        QModelIndexList list = index.model()->match(index, Qt::DisplayRole, name);
        if (list.size())
        {
            textEdit()->setPlainText(list.first().data(257).toString());
        }
        else
        {
            textEdit()->setPlainText(QString("Unknown reference to %1").arg(name));
        }
    }
    else
    {
        textEdit()->setPlainText(text);
    }
}
