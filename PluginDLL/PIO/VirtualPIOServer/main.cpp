#include "VirtualPIOServer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	int	PortNumber=28200;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='P' || *argv[i]=='p'){
			char	*fp=argv[i]+1;
			QString	s(fp);
			bool	ok;
			PortNumber	=s.toInt(&ok);
			if(ok==false){
				PortNumber=28200;
			}
		}
	}

	VirtualPIOServer w(PortNumber);
	w.show();
	return a.exec();
}
