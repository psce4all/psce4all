/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

class qt_MemorySpinBox : public QSpinBox
{
  Q_OBJECT

public:
  qt_MemorySpinBox(QWidget *parent = 0);
  ~qt_MemorySpinBox();

  QValidator::State validate(QString &input, int &pos) const;

protected:
  QString textFromValue(int value) const;
  int valueFromText(const QString &text) const;
};
