#include "TransFileServer.h"
#include <QApplication>
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int	SlaveCount=4;
	int	LanguageCode=0;
	int		AccessPort=15700;
	QString	CachePath="d:\\Data";
	bool	LogMode=false;

 	for(int i=1;i<argc;i++){
		if(*argv[i]=='P' || *argv[i]=='p'){
			AccessPort=QString(argv[i]+1).toInt();
		}
		if(*argv[i]=='C' || *argv[i]=='c'){
			CachePath=QString(argv[i]+1);
		}
		if(*argv[i]=='L' || *argv[i]=='l'){
			LogMode=true;
		}
	}

	QApplication a(argc, argv);
	TransFileServer w(LogMode,AccessPort,CachePath);
	w.show();
	return a.exec();
}
