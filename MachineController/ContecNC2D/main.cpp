#include "ContecNC2D.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ContecNC2D w;
	w.show();
	return a.exec();
}
