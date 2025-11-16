#include "MakeLockStarKey.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MakeLockStarKey w;
	w.show();
	return a.exec();
}
