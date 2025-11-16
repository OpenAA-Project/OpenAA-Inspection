#include "DelayExe.h"
#include <QApplication>
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);

	if(argc>=2){
		int	WaitingTime;
		QString	ExeFileName;
		char	*fp1=argv[1];
		sscanf(fp1,/**/"%d",&WaitingTime);

		ExeFileName=QString(argv[2]);
		for(int i=3;i<argc;i++){
			ExeFileName+=QString(" ");
			ExeFileName+=QString(argv[i]);
		}

		DelayExe w(ExeFileName,WaitingTime);
		w.show();
		return a.exec();
	}
}
