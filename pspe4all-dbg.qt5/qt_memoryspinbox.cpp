#include "stdafx.h"
#include "qt_memoryspinbox.h"
#include "QMessageBox"

qt_MemorySpinBox::qt_MemorySpinBox(QWidget *parent)
: QSpinBox(parent)
{
}

qt_MemorySpinBox::~qt_MemorySpinBox()
{
}

QValidator::State qt_MemorySpinBox::validate(QString &input, int &pos) const
{
  if (isxdigit(input[pos].cell()))
  {
    if (input.size() < 8)
      return QValidator::Intermediate;
    else if (input.size() == 8)
      return QValidator::Acceptable;
  }
  return QValidator::Invalid;
}

QString qt_MemorySpinBox::textFromValue(int value) const
{
  return QString("%1").arg((unsigned int)value, 8, 16, QChar('0')).toUpper();
}

int qt_MemorySpinBox::valueFromText(const QString &text) const
{
  return text.toInt(0, 16);
}
