#ifdef _SDEBUG
#define	NOMINMAX
#include <Windows.h>
#include "LeakChecker.h"
#pragma comment(lib, /**/"LeakChecker")
#endif

#include "PQSystemExecutor.h"
#include <QtWidgets/QApplication>

#include "XMacro.h"
#include "XApplication.h"

#include "XGUI.h"
#include <stdio.h>
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "SelectWorkerForm.h"
#include "SingleExecute.h"
#include "XPassword.h"
#include "XShowVersion.h"
#include <omp.h>
#include "XPassword.h"
#include "XCrossObj.h"
#include "XStatusController.h"
#include "XLogOut.h"
#include "IntegrationLib.h"
#include "XParamIntegrationMaster.h"
#include "XIntegrationBase.h"
#include "Regulus64System.h"

void	MainApplication::QuitProcess()
{
	//GUIInitialData->GetGUIInstanceRoot()->RemoveAll();
	//EntryPointToFuncGlobal->GetLayersBase()->Release();
}

/*
	Commandline option

	A[Path]			Set current path to [Path]
	Q[Path]			Set user path
					if PATH C:/Users/<USER>/AppData/Roaming/<APPNAME> doesn't exist, use CurrentPath 
	G[Filename]		Set GUI file to [Filename]
	S[Filename]		Load Global-Param file to set [Filename]
	NDM				No database message
	Style[style]	style=windows, windowsvista, fusion, or macintosh
	StopForDebug	Stop for Debug at first
*/

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return /**/"PQSystem.lng";
}

int main(int argc, char *argv[])
{
	MainApplication *a=new MainApplication(argc, argv);

	QString	GlobalParmaFileName;
	QString	AbsPath;
	QString	UserPath;
	QString	Style = "windowsvista";
	bool	StopForDebug=false;

	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QString	GUIFileName=/**/"InspecionPrintSlave.gui";
 	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
		else if(strnicmp(argv[i],"StopForDebug",12)==0){
			StopForDebug=true;
		}
		else if (strnicmp(argv[i], "Style", 5) == 0) {
			char* fp = &argv[i][5];
			Style = QString::fromLocal8Bit(fp);
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
		}
		else if((*argv[i]=='G' || *argv[i]=='g') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GUIFileName=fp;
		}
	}
	if(StopForDebug==true){
		QMessageBox::information(NULL,"Stop","Please push OK button to go",QMessageBox::Ok);
	}

	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	QApplication::setStyle(Style);

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBasePQSystem	*Layers	=new LayersBasePQSystem(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	QString	Msg;
	Layers->InitialDatabaseLoader(Msg);

	Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	if(Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath())==false){
		QMessageBox Q("Load error"
					, "Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}

	Layers->SetModeInspectionPlayer(true);

	ParamIntegrationMaster	ParamIntegrationMasterData(Layers);
	ParamIntegrationMasterData.LoadDefault(Layers->GetUserPath());

	DWORD	ErrorCode=0;
	Layers->LoadAttrDefault();

	RootNameListContainer	AlgorithmRootNameList;
	QFile	gfile(GUIFileName);
	if(gfile.open(QIODevice::ReadOnly)==true){
		if(G->GetGUIInstanceRoot()->LoadOnlyAlgorithm(&gfile)==true){
			AlgorithmRootNameList=G->GetGUIInstanceRoot()->AlgorithmList;
		}
		gfile.close();
	}
	if(G->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
		QMessageBox Q(/**/"Error"
					, Msg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	QStringList	AlgorithmPathList;
	QDir::setCurrent(Layers->GetSystemPath());
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList,true);
	Layers->ReadLogicSettingFiles(true);
	LocalDatabaseBasicClass	*KDatabase=new LocalDatabaseBasicClass(Layers->GetDatabaseLoader(false)
																	,Layers->GetParamGlobal()->LocalDatabase_FileName
																	,Layers->GetParamGlobal()->LocalDatabase_HostName
																	,Layers->GetParamGlobal()->LocalDatabase_Port
																	,Layers->GetParamGlobal()->TransDatabaseIP
																	,Layers->GetParamGlobal()->TransDatabasePort);
	
	if(KDatabase->IsExistDatabase()==false){
		QString  msg=QString(/**/"Not exist Database file! Create database?");
		int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
		if(ret==QMessageBox::No){
			return(4);
		}
		if(KDatabase->CreateDatabase()==false){
			QMessageBox Q( /**/"Error" , /**/"Could not create database", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(1);
		}
	}

	if(Layers->OpenDatabase(*KDatabase)==false){
		QMessageBox Q( /**/"Error"
					, /**/"Could not open database", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(2);
	}
	Layers->LoadLevelFolderContainerFromDB();
	
	IntegrationBase	*IBase=new IntegrationBase(Layers,&ParamIntegrationMasterData);
	IBase->Initialize();
	Layers->SetIntegrationBase(IBase);
	G->InitialIntegration();

	Layers->InitialAlgorithmBlob();
	Layers->InitialAlgorithmLibrary();
	//Layers->LoadOutlineOffsetForDatabase();

	RootNameListContainer LackOfAlgorithm;
  	if(Layers->CheckInstalledAlgorithm(AlgorithmRootNameList,LackOfAlgorithm)==false){
		RootNameList	*v=LackOfAlgorithm.GetFirst();
		QString	msg=QString(/**/"Lack of Algorithm");
		QString ErrorMsg= QString("Root(")+v->DLLRoot+QString(/**/") Name(")+v->DLLName+QString(/**/")");
		QMessageBox::critical ( NULL, msg, ErrorMsg, QMessageBox::Ok);
		return(3);
	}
	Layers->SetLanguageCode(true,true,true);
	Layers->InitialAllocExecuterDim();
	Layers->InitialResult();
	Layers->GetParamPQSystem()->LoadDefault(Layers->GetUserPath());

	AlgorithmRootNameList.RemoveAll();
	Layers->SQLSetWorker(1);

	Layers->InitialLight(false);
	//Layers->InitialFilterBank();
	Layers->InitialResultAnalizer();
	//Layers->BroadcastMachineID();

	Layers->ReadAllSettingFiles(true);
	Layers->InitialAfterParamLoaded();
	//Layers->DeliverOutlineOffset();
	//Layers->DeliverAllCommsForDirectComm(50000);
	//Layers->LoadFilterDef();
	//if(Layers->GetStatusController()!=NULL){
	//	Layers->GetStatusController()->InstallFilter();
	//}
	Layers->CloseInformed();

	int	ret=false;
	PQSystemExecutor *w=new PQSystemExecutor(Layers);
	if(Layers->GetOnTerminating()==false){
		w->LoadDLL(/**/"PQSystem");
		w->show();
		ret=a->exec();
	}

	Layers->SetOnTerminating(true);

	Layers->CloseDatabase();
	delete	KDatabase;

	//delete	Layers;
	delete	G;
	//_heapchk();

	GlobalParmaFileName.clear();
	
	//delete	Layers;
	//_heapchk();

	return ret;


}
