#include "stdafx.h"
#include "pspe4alldbgqt5.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	pspe4alldbgqt5 w;
	w.show();
	return a.exec();
}
