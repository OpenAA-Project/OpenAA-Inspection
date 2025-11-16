#include <QApplication>
#include "logintegratorfrontend.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LogIntegratorFrontEnd w;
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
