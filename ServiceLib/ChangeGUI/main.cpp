#include "ChangeGUI.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChangeGUI w;
	w.show();
	return a.exec();
}
