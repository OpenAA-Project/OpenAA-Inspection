#include "NetworkSIOServer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	int	PortNumber=28210;
	int	ComPort	=1;

	for(int i=1;i<argc;i++){
		if(strnicmp(argv[i],"COM",3)==0){
			char	*fp=argv[i]+3;
			QString	s(fp);
			bool	ok;
			ComPort	=s.toInt(&ok);
			if(ok==false){
				ComPort=1;
			}
		}
		if(strnicmp(argv[i],"P",1)==0){
			char	*fp=argv[i]+1;
			QString	s(fp);
			bool	ok;
			PortNumber	=s.toInt(&ok);
			if(ok==false){
				PortNumber=28210;
			}
		}
	}

	NetworkSIOServer w(ComPort,PortNumber);
	w.show();
	return a.exec();
}
