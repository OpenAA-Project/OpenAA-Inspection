#include "ContecNC3D.h"
#include <QApplication>

char *DeviceName ="SMC000" ;

int main(int argc, char *argv[])
{
	for(int i=1;i<argc;i++){
		if((*argv[i]=='D' || *argv[i]=='d')){
			char	*fp=argv[i]+1;
			DeviceName	=fp;
		}
	}

	QApplication a(argc, argv);
	ContecNC3D w(DeviceName);
	w.show();
	return a.exec();
}
