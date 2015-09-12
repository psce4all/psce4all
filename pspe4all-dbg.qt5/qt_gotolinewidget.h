/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QStringListModel>
#include <QPlainTextEdit>

class qt_GotoLineWidget : public QWidget
{
    Q_OBJECT

public:
    qt_GotoLineWidget(QPlainTextEdit *textEdit, QWidget *parent = nullptr);

    QPlainTextEdit *textEdit() const { return textEdit_; }

public slots:
    void activate();
    void deactivate();

private slots:
    void go();
    void indicateStatus(bool success = true);
    void rememberCompletion();

private:
    QPlainTextEdit   *textEdit_;
    QLineEdit        *lineEdit_;
    QStringListModel *completionModel_;
    QPalette          normalPalette_;
    QPalette          notFoundPalette_;
};
