#include "ScreenLock.h"
#include <QApplication>
#include "XShowVersion.h"

bool	CloseAfterPassword=false;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int		BreakTime=60;
	QString Password="abc";
	QString title=/**/"";

 	for(int i=1;i<argc;i++){
		if(*argv[i]=='B' || *argv[i]=='b'){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&BreakTime);
		}
		if((*argv[i]=='P' || *argv[i]=='p')){
			char	*fp=argv[i]+1;
			Password=QString(fp);
		}
		if((*argv[i]=='T' || *argv[i]=='t')){
			char	*fp=argv[i]+1;
			title=QString(fp);
		}
		if((*argv[i]=='C' || *argv[i]=='c')){
			CloseAfterPassword=true;
		}
	}

	QApplication a(argc, argv);
	ScreenLock 	w(Password , title ,BreakTime);
	//w.showMaximized();
	w.show();
	return a.exec();
}
