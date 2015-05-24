#ifndef QT_MEMORYVIEWER_H
#define QT_MEMORYVIEWER_H

#include <QWidget>
#include "ui_qt_memoryviewer.h"

class qt_MemoryViewer : public QWidget
{
    Q_OBJECT

  public:
    qt_MemoryViewer(QWidget *parent = 0);
    ~qt_MemoryViewer();
	 void updateMemoryViewer();
	
  private:
	  Ui::memoryform ui;
	  
};

#endif // QT_MEMORYVIEWER_H