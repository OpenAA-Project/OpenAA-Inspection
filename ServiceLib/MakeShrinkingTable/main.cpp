#include "MakeShrinkingTable.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MakeShrinkingTable w;
	w.show();
	return a.exec();
}
