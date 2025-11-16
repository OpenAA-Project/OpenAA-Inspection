#include "ContecNC4D.h"
#include <QApplication>

char *SMCDeviceName ="SMC001" ;
char *PIODeviceName ="DIO000" ;

int main(int argc, char *argv[])
{
	for(int i=1;i<argc;i++){
		if((*argv[i]=='D' || *argv[i]=='d')){
			char	*fp=argv[i]+1;
			SMCDeviceName	=fp;
		}
		if((*argv[i]=='P' || *argv[i]=='p')){
			char	*fp=argv[i]+1;
			PIODeviceName	=fp;
		}
	}

	QApplication a(argc, argv);
	ContecNC4D w(SMCDeviceName ,PIODeviceName);
	w.show();
	return a.exec();
}
