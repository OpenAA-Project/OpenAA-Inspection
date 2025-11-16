#include <QApplication>
#include "EditStatusComment.h"

#include "XGUI.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

LayersBase	*Layers;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);

	QString	AbsPath;
	QString	UserPath;

	for(int i=0;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
	}

	EditStatusComment w;
	w.show();

    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	if(AbsPath.isEmpty()==false){
		QCoreApplication::addLibraryPath (AbsPath);
	}
	else{
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());
	}
	EntryPointBase	*e	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(e);
	e->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	Layers->SetCurrentPath(QDir::currentPath());
	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	//Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	QString	ErrorMsg;
	DWORD	ErrorCode;

	Layers->SetLanguageCode();

	return a.exec();
}
