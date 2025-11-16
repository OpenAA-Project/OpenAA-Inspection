#include "Maintainer.h"
#include <QApplication>
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QString	SettingFileName=/**/"Maintainer.dat";

	for(int i=0;i<argc;i++){
		if(*argv[i]=='S'){
			SettingFileName=QString(argv[i]+1);
		}
	}

	QApplication a(argc, argv);
	Maintainer w(SettingFileName);
	w.show();
	return a.exec();
}
