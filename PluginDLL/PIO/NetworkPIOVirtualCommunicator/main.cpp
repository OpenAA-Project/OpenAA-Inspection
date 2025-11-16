#include "NetworkPIOVirtualCommunicator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	int		ID				=0;
	QString	ServerIPName	="localhost";
	int		ServerPort=18830;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='D' || *argv[i]=='d'){
			ID=QString(argv[i]+1).toInt();
		}
		if(*argv[i]=='I' || *argv[i]=='i'){
			ServerIPName=QString(argv[i]+1);
		}
		if(*argv[i]=='P' || *argv[i]=='p'){
			QString	PortName=QString(argv[i]+1);
			ServerPort	=PortName.toInt();
		}
	}

	NetworkPIOVirtualCommunicator w;
	w.Initial(ID,ServerIPName,ServerPort,16,16);
	w.show();
	return a.exec();
}
