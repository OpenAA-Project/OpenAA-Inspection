#include "LotBinder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LotBinder w;
	w.show();
	return a.exec();
}
