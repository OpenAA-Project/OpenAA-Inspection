#include <QApplication>
#include "PIODevicer.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PIODevicer w;
	w.show();
	return a.exec();
}
