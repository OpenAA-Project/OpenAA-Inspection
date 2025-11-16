#include "LEDControl16GTester.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LEDControl16GTester w;
	w.show();
	return a.exec();
}
