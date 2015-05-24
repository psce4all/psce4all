#ifndef PSPE4ALLDBGQT5_H
#define PSPE4ALLDBGQT5_H

#include <QtWidgets/QMainWindow>
#include "ui_pspe4alldbgqt5.h"

class pspe4alldbgqt5 : public QMainWindow
{
	Q_OBJECT

public:
	pspe4alldbgqt5(QWidget *parent = 0);
	~pspe4alldbgqt5();

private:
	Ui::pspe4alldbgqt5Class ui;
};

#endif // PSPE4ALLDBGQT5_H
