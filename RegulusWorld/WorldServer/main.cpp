#include "WorldServer.h"
#include <QtWidgets/QApplication>
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

    QApplication a(argc, argv);
    WorldServer w;
    w.show();
    return a.exec();
}
