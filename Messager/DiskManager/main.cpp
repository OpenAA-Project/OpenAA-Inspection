#include "XMacro.h"
#include "DiskManager.h"
#include <QApplication>
#include <QDir>
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "SingleExecute.h"
#include "XGUI.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}


QString	LogHeaderFileName="MessagerLog.txt";

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;
	int		PortNumber=13444;
	QString	AbsPath;
	QString	UserPath;
	bool	DupOK=true;
	QString	GlobalParmaFileName;
	QString	CommParmaFileName;

	QApplication a(argc, argv);

	for(int i=0;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
		}
		else if((*argv[i]=='C' || *argv[i]=='c') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			CommParmaFileName=fp;
		}
		else if(stricmp(argv[i],"Single")==0){
			DupOK=false;
		}
		else if((*argv[i]=='L' || *argv[i]=='l') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			LogHeaderFileName=fp;
		}
		else if((*argv[i]=='T' || *argv[i]=='t') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&PortNumber);
		}
	}
	QFileInfo	FInfo(argv[0]);
	if(DupOK==false && SingleExecute(FInfo.fileName())==false){
		KillDupProcess(FInfo.fileName());
		//return 100;
	}

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	if(GlobalParmaFileName.isEmpty()==false){
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	}
	if(CommParmaFileName.isEmpty()==false){
		Layers->GetParamComm()->SetDefaultFileName(CommParmaFileName);
	}		
	//SeqMessagerParamData=new SeqMessagerParam(Layers);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());

	DiskManager w(PortNumber);
	Layers->SetMainForm((GUIFormBase *)&w);

	w.show();
	return a.exec();
}
