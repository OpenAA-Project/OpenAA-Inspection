#include <QApplication>
#include "ClearCacheAndStress.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ClearCacheAndStress w;
	w.show();
	return a.exec();
}
