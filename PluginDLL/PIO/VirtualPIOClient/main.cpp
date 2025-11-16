#include "VirtualPIOClient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QString	AccessMemoryName=/**/"VirtualPIO";
	QString	ServerIPName	="localhost";
	int		ServerPort=28200;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='N' || *argv[i]=='n'){
			char	*fp=argv[i]+1;
			AccessMemoryName	=fp;
		}
		if(*argv[i]=='I' || *argv[i]=='i'){
			ServerIPName=QString(argv[i]+1);
		}
		if(*argv[i]=='P' || *argv[i]=='p'){
			QString	PortName=QString(argv[i]+1);
			ServerPort	=PortName.toInt();
		}
	}

	VirtualPIOClient w(ServerIPName,ServerPort,AccessMemoryName);
	w.show();
	return a.exec();
}
