#ifndef QT_MEMORYSPINBOX_H_
#define QT_MEMORYSPINBOX_H_

#include <QSpinBox>

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

#endif /* Qt_MEMORYSPINBOX_H_ */
