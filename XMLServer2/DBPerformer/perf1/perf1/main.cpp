#include <QApplication>
#include "perf1.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	perf1 w;
	w.show();
	return a.exec();
}
