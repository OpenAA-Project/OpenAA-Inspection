#include "Haspviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HaspViewer w;
	w.show();
	return a.exec();
}
