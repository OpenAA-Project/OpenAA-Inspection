#include <QApplication>
#include "LearningServer.h"
#include "XLearningServer.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XFilterManager.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XDirectComm.h"
#include "XPieceArchitect.h"
#include "XDatabase.h"
#include "SingleExecute.h"
#include "Regulus64System.h"
#include "LearningSettingDialog.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}


int main(int argc, char *argv[])
{
	int		PortNumber=13444;
	QString	AbsPath;
	QString	UserPath;
	bool	DupOK=true;
	QString	GlobalParmaFileName;
	QString	CommParmaFileName;
	bool	StopForDebug=false;
	bool	Setting=false;
	bool	StartRun=false;
	bool	StartMinimizedly=false;

	QApplication a(argc, argv);

	for(int i=0;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if(strnicmp(argv[i],"StopForDebug",12)==0){
			StopForDebug=true;
		}
		else if(strnicmp(argv[i],"Setting",7)==0){
			Setting=true;
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
		else if(stricmp(argv[i],"Run")==0){
			StartRun=true;
		}
		else if(stricmp(argv[i],"minimize")==0){
			StartMinimizedly=true;
		}
	}
	if(StopForDebug==true){
		QMessageBox::information(NULL,"Stop","Please push OK button to go",QMessageBox::Ok);
	}
	QFileInfo	FInfo(argv[0]);
	if(DupOK==false && SingleExecute(FInfo.fileName())==false){
		KillDupProcess(FInfo.fileName());
		//return 100;
	}


	if(AbsPath.isEmpty()==false){
		QCoreApplication::addLibraryPath (AbsPath);
	}
	else{
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());
	}

	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	int	LanguageCode=FRegistry.LoadRegInt("Language",0);

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);
	QString tMsg;
	Layers->Initial(tMsg ,false);

	if(GlobalParmaFileName.isEmpty()==false){
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	}
	if(CommParmaFileName.isEmpty()==false){
		Layers->GetParamComm()->SetDefaultFileName(CommParmaFileName);
	}		
	//SeqMessagerParamData=new SeqMessagerParam(Layers);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	Layers->SetLanguageCode();

	if(Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath())==false){
		QMessageBox Q("Load error"
					, "Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}

	qRegisterMetaType<int64>(/**/"int64");


	RootNameListContainer	AlgorithmRootNameList;
	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList,true);
	Layers->LoadShrinkingPackContainer();

	ServerBaseData=new ServerBase(Layers);
	if(ServerBaseData->LoadDefault()==false){
		*ServerBaseData->GetParamGlobal()=*Layers->GetParamGlobal();
	}
	if(Setting==true){
		LearningSettingDialog	D(Layers,ServerBaseData->GetParamGlobal());
		D.exec();
	}

	QString	Msg;
	Layers->InitialDatabaseLoader(Msg);
	LocalDatabaseBasicClass	*KDatabase=new LocalDatabaseBasicClass(Layers->GetDatabaseLoader(false)
																	,ServerBaseData->GetParamGlobal()->LocalDatabase_FileName
																	,ServerBaseData->GetParamGlobal()->LocalDatabase_HostName
																	,ServerBaseData->GetParamGlobal()->LocalDatabase_Port
																	,ServerBaseData->GetParamGlobal()->TransDatabaseIP
																	,ServerBaseData->GetParamGlobal()->TransDatabasePort);
	
	if(KDatabase->IsExistDatabase()==false){

		QString  msg=QString(/**/"Not exist Database file! :(")
					+ServerBaseData->GetParamGlobal()->LocalDatabase_HostName
					+QString(") ")
					+ServerBaseData->GetParamGlobal()->LocalDatabase_FileName;
			
		int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Ok);
		LearningSettingDialog	D(Layers,ServerBaseData->GetParamGlobal());	
		D.exec();
		return(4);
	}

	if(Layers->OpenDatabase(*KDatabase)==false){
		QMessageBox Q( /**/"Error"
					, /**/"Could not open database", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		LearningSettingDialog	D(Layers,ServerBaseData->GetParamGlobal());	
		D.exec();
		return(2);
	}
	Layers->LoadLevelFolderContainerFromDB();
	Layers->InitialAlgorithmLibrary();

	LearningServer w(Layers,StartRun);
	Layers->SetMainForm((GUIFormBase *)&w);
	if(StartMinimizedly==false){
		w.show();
	}
	else{
		w.showMinimized();
	}
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	Layers->CloseInformed();

	return a.exec();
}


