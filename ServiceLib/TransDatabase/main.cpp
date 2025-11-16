#include "TransDatabase.h"
#include <QApplication>
#include "XShowVersion.h"
#include "Regulus64Version.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XEntryPoint.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}
int	LanguageCode;

QString		LoadedFileName;
int			KeepingDay=5;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int	SlaveCount=4;
	int	LanguageCode=0;
	int		AccessPort=16050;
	bool	LogMode=false;

 	for(int i=1;i<argc;i++){
		if(*argv[i]=='P' || *argv[i]=='p'){
			AccessPort=QString(argv[i]+1).toInt();
		}
		if(*argv[i]=='K' || *argv[i]=='k'){
			KeepingDay=QString(argv[i]+1).toInt();
		}
		if(*argv[i]=='L' || *argv[i]=='l'){
			LogMode=true;
		}
	}
	GSleep(1000);

	QApplication a(argc, argv);
	EntryPointToFuncGlobal->GUISetEditMode(true);
	TransDatabase w(LogMode,AccessPort);
	w.show();
	return a.exec();
}
