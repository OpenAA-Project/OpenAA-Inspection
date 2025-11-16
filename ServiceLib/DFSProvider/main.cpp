#include "DFSProvider.h"
#include <QApplication>
#include "XShowVersion.h"
#include "XForWindows.h"
#include <QDir>

QString	DefaultSettingFileName="DFSProvider.dat";
QString	ProviderName;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QString		IPAddress="localhost";
	int			Port	=DFSProviderPort;
	QString		AbsPath;

	for(int i=0;i<10;i++){
		if(::MtGetComputerName(ProviderName)==true)
			break;
	}
	for(int i=1;i<argc;i++){
		if(*argv[i]=='I' || *argv[i]=='i'){
			char	*fp=argv[i]+1;
			IPAddress=QString(fp);
		}
		else if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if(*argv[i]=='P' || *argv[i]=='p'){
			char	*fp=argv[i]+1;
			QString	Var(fp);
			Port=Var.toInt();
		}
		else if(*argv[i]=='N' || *argv[i]=='n'){
			char	*fp=argv[i]+1;
			ProviderName=QString(fp);
		}
	}

	QApplication a(argc, argv);
	DFSProvider w(IPAddress ,Port);
	w.show();
	return a.exec();
}
