#include <QtCore/QCoreApplication>
#include <QTcpSocket>
#include <string.h>
#include <stdio.h>
#include "XGeneralFunc.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString	IPAddress=/**/"localhost";
	int		PortNo=36755;

	for(int i=0;i<argc;i++){
		if(strnicmp(argv[i],"-A",2)==0
		|| strnicmp(argv[i],"/A",2)==0){
			char	*fp=argv[i]+2;
			IPAddress=QString(fp);
		}
		if(strnicmp(argv[i],"-P",2)==0
		|| strnicmp(argv[i],"/P",2)==0){
			char	*fp=argv[i]+2;
			sscanf(fp,"%d",&PortNo);
		}
	}

	QTcpSocket	Sock(NULL);
	Sock.connectToHost(IPAddress,PortNo);
	Sock.waitForConnected(3000);
	if(Sock.state()==QAbstractSocket::ConnectedState){
		if(Sock.open(QIODevice::ReadWrite | QIODevice::Unbuffered)==true){
			Sock.write("CloseOne\n",8);
			Sock.flush();

			GSleep(1000);
			Sock.disconnectFromHost();
		}
	}

	return 0;
}
