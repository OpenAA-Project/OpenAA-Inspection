#include <QApplication>
#include "XMacro.h"
#include "Messager.h"
#include <QDir>
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "MessagerSeq.h"
#include "SingleExecute.h"
#include "XGUI.h"
#include "XShowVersion.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

/*
	Commandline option

	A[Path]			Set current path to [Path]
	Q[Path]			Set user path
					if PATH C:/Users/<USER>/AppData/Roaming/<APPNAME> doesn't exist, use CurrentPath 
	S[Filename]		Load Global-Param file to set [Filename]
	C[Filename]		Load Comm-Param file to set [Filename]
	Single			Single Execution
	QON				Sequence start
	QOFF			Not execute sequence
	L[FileName]		LogFileName
	T[Port]			Port Numver

	システムビット	P1		１にするとポップアップを閉じる

*/

QString	LogHeaderFileName=/**/"MessagerLog.txt";
bool	ExecuteSequence=true;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QString	GlobalParmaFileName=/**/"Global.dat";
	QString	CommParmaFileName;
	QString	AbsPath;
	QString	UserPath;
	bool	DupOK=true;
	int		PortNumber=13444;

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
		else if(stricmp(argv[i],"Single")==0){
			DupOK=false;
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
		}
		else if((*argv[i]=='C' || *argv[i]=='c') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			CommParmaFileName=fp;
		}
		else if((*argv[i]=='L' || *argv[i]=='l') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			LogHeaderFileName=fp;
		}
		else if((*argv[i]=='T' || *argv[i]=='t') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&PortNumber);
		}
		else if(stricmp(argv[i],"QON")==0){
			ExecuteSequence=true;
		}
		else if(stricmp(argv[i],"QOFF")==0){
			ExecuteSequence=false;
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

	SeqMessagerParamData=new SeqMessagerParam(Layers);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());

	Messager w(Layers,PortNumber);
	Layers->SetMainForm((GUIFormBase *)&w);
	
	w.show();
	return a.exec();
}
