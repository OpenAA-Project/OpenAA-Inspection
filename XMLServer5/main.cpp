#include "XMLServer5.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XMLServer5 w;
	w.show();
	return a.exec();
}
