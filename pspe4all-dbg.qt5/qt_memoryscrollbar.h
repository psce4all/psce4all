#ifndef QT_MEMORYSCROLLBAR_H
#define QT_MEMORYSCROLLBAR_H

#include <QWidget>
#include <QScrollBar>

class qt_MemoryScrollbar : public QScrollBar
{
	Q_OBJECT

public:
	qt_MemoryScrollbar(QWidget *parent = 0);
	qt_MemoryScrollbar(Qt::Orientation orientation, QWidget *parent = 0);
	~qt_MemoryScrollbar();

public slots:
    void changeRange(int min, int max);
	
};

#endif // QT4_MEMORYSCROLLBAR_H
