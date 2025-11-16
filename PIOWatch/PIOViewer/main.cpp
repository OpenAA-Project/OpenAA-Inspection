#include "PIOViewer.h"
#include <QApplication>
#include "XGUI.h"
#include "XSequence.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include "XPIOButton.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

PIOClassPack		*PIOPack=NULL;
int32				xErrorCode;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);
	QString		AbsPath;
	QString		UserPath;
	QString		StartDLL;
	bool		StartOnDLL=false;

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
		if(*argv[i]=='D' || *argv[i]=='d'){
			char	*fp=argv[i]+1;
			if(*fp!=0){
				StartDLL	=fp;
			}
			StartOnDLL=true;
		}
	}

	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	QString	ErrorMsg;
	DWORD	ErrorCode;

	Layers->SetLanguageCode();

	PIOPack=new PIOClassPack(Layers);
	PIOPack->SearchAddDLL(xErrorCode,false);

	PIOViewer w(Layers,StartOnDLL,StartDLL);

	w.show();
	Layers->CloseInformed();
	return a.exec();
}
