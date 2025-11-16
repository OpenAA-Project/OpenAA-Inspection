#include "NetworkSIOTestClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NetworkSIOTestClient w;
	w.show();
	return a.exec();
}
