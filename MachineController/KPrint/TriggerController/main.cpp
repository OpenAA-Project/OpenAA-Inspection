#include "TriggerController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TriggerController w;
	w.show();
	return a.exec();
}
