#include <QApplication>
#include "ReportDisk.h"
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);
	ReportDisk w;
	w.show();
	return a.exec();
}
