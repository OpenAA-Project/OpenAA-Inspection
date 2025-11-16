#include "DFSExplorer.h"
#include <QApplication>
#include "XShowVersion.h"
#include <QDir>

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QString		IPAddress="localhost";
	int			Port	=DFSClientPort;
	QString		AbsPath;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='I' || *argv[i]=='i'){
			char	*fp=argv[i]+1;
			IPAddress=QString(fp);
		}
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if(*argv[i]=='P' || *argv[i]=='p'){
			char	*fp=argv[i]+1;
			QString	Var(fp);
			Port=Var.toInt();
		}
	}

	QApplication a(argc, argv);

	DFSExplorer w(IPAddress ,Port);
	w.show();
	return a.exec();
}
