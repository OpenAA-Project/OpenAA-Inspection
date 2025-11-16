#include "Booter.h"
#include <QApplication>
#include <QDir>
#include "XShowVersion.h"
#include "XGUI.h"
#include "XLightClass.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include <QString>

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int	OperationalPort=17900;
	int	LanguageCode=0;
	QString	AbsPath;
	QString	SettingFile="BooterParameter.dat";
	//EntryPointToFuncGlobal	=MakeEntryPointForGlobal();

 	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		if((*argv[i]=='P' || *argv[i]=='p')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&OperationalPort);
		}
		if((*argv[i]=='L' || *argv[i]=='l')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&LanguageCode);
		}
		if((*argv[i]=='S' || *argv[i]=='s')){
			char	*fp=argv[i]+1;
			SettingFile=QString(fp);
		}
	}

	QApplication a(argc, argv);
	Booter w(SettingFile,OperationalPort);
	
	w.show();
	return a.exec();
}
