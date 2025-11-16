#include <QApplication>
#include "xmldb_local.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XMLDB_Local w;
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
