/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_gotolinewidget.h"

#include <QCompleter>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringListModel>
#include <QTextBlock>
#include <QPlainTextEdit>

qt_GotoLineWidget::qt_GotoLineWidget(QPlainTextEdit *textEdit, QWidget *parent)
    : QWidget(parent)
    , textEdit_(textEdit)
{
    QLabel *goLabel = new QLabel(tr("Go to line:"), this);

    completionModel_ = new QStringListModel(this);

    QIntValidator *validator = new QIntValidator(this);
    validator->setBottom(1);

    lineEdit_ = new QLineEdit(this);
    lineEdit_->setCompleter(new QCompleter(completionModel_, this));
    lineEdit_->setValidator(validator);

    connect(lineEdit_, SIGNAL(textChanged(const QString &)), this, SLOT(indicateStatus()));
    connect(lineEdit_, SIGNAL(returnPressed()), this, SLOT(go()));

    QPushButton *goButton = new QPushButton(tr("&Go"), this);
    connect(goButton, SIGNAL(clicked()), this, SLOT(go()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(4, 0, 4, 4);
    layout->addWidget(goLabel);
    layout->addWidget(lineEdit_);
    layout->addWidget(goButton);

    normalPalette_   = lineEdit_->palette();
    notFoundPalette_ = lineEdit_->palette();
    notFoundPalette_.setColor(QPalette::Base, QColor(255, 192, 192));
}

void qt_GotoLineWidget::activate()
{
    show();
    lineEdit_->selectAll();
    lineEdit_->setFocus();
}

void qt_GotoLineWidget::deactivate()
{
    if (!isVisible())
    {
        return;
    }

    textEdit()->setFocus();
    hide();
}

void qt_GotoLineWidget::go()
{
    QTextBlock block;

    if (textEdit()->document())
    {
        block = textEdit()->document()->findBlockByNumber(lineEdit_->text().toInt() - 1);
    }

    if (block.isValid())
    {
        QTextCursor cursor(block);
        textEdit()->setTextCursor(cursor);
        textEdit()->ensureCursorVisible();

        indicateStatus(true);

        deactivate();
    }
    else
    {
        indicateStatus(false);
    }

    rememberCompletion();
}

void qt_GotoLineWidget::indicateStatus(bool success)
{
    lineEdit_->setPalette(success ? normalPalette_ : notFoundPalette_);
}

void qt_GotoLineWidget::rememberCompletion()
{
    QStringList list = completionModel_->stringList();
    if (!list.contains(lineEdit_->text(), lineEdit_->completer()->caseSensitivity()))
    {
        list.append(lineEdit_->text());
        completionModel_->setStringList(list);
    }
}
