#include "EditParamIntegrationMaster.h"
#include <QApplication>
#include "XShowVersion.h"
#include "XFileRegistry.h"
#include "XParamIntegrationMaster.h"
#include "XGUI.h"

int	LanguageCode;

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "EditParameter.lng";
}

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
   a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	if(AbsPath.isEmpty()==false){
		QCoreApplication::addLibraryPath (AbsPath);
	}
	else{
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());
	}
	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	EntryPointToFuncGlobal->GUISetEditMode(true);
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	QString	ErrorMsg;
	DWORD	ErrorCode=0;

	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	LanguageCode=FRegistry.LoadRegInt("Language",0);
	Layers->SetLanguageCode(LanguageCode);

	Layers->InitialFilterBank();

	ParamIntegrationMaster Param(Layers);
    EditParamIntegrationMaster w(Layers,&Param);

    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	Layers->CloseInformed();
    return a.exec();
}
