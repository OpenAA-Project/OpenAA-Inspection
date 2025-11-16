/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RegulusWorld\RobotRegulusWorld\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#define	_SDEBUG

#ifdef _SDEBUG
#define	NOMINMAX
#include <Windows.h>
#include "LeakChecker.h"
#pragma comment(lib, "LeakChecker")
#endif

#include "XMacro.h"
#include <QApplication>
#include "BootupLogoForm.h"
#include "ClosingForm.h"

//#include "InspectionPlayerResource.h"
#include "XGUI.h"
#include <stdio.h>
#include <QLineEdit>
#include <QInputDialog>
#include <ThreadSequence.h>
//#include "XExecuteInspectFast.h"
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "XDataInLayerCommander.h"
#include "PasswordDropper.h"
#include "XPassword.h"
#include "hasplib.h"
#include "XForWindows.h"
#include "SelectWorkerForm.h"
#include "SingleExecute.h"
#include "XShowVersion.h"
#include "ErrorMessageDialog.h"
#include "XPassword.h"
#include "XStatusController.h"
#include "XLogOut.h"
#include "XGeneralFunc.h"
#include "NoComponentDialog.h"
#include "Regulus64System.h"
#include "XRegulusWorld.h"
#include <omp.h>

int	XDbg;

#ifdef HASP_ENABLE
static	bool HaspCheck(QString strKey)
{
	QStringList RetList;
	Hasplib Hasp;
	if(Hasp.HaspExecute(RetList)==false)
		return false;
	for(int Cnt=0;Cnt<RetList.count();Cnt++){
		if(RetList.at(Cnt)==strKey){
			if(QDate::currentDate()<=QDate::fromString(RetList.at(Cnt-1),/**/"yyyyMMdd"))
				return true;
		}
	}
	return false;
}
#endif

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return /**/"InspectionGeneral.lng";
}


/*
	Commandline option

	A[Path]			Set current path to [Path]
	Q[Path]			Set user path
					if PATH C:/Users/<USER>/AppData/Roaming/<APPNAME> doesn't exist, use CurrentPath 
	G[Filename]		Set GUI file to [Filename]
	S[Filename]		Load Global-Param file to set [Filename]
	W[WorkerID]		Set [WorkerID]
	U[GUI.dat]		Set default GUI.dat file name
	Single			Single Execution
	LogOut			Set LogOut mode
	L[FileName]		LogFileName
	YAddMenu		Add system menu
	Revision		Show Revision on command line
	Duplicate		Enable multiple boot
	SetNumThreads[n]	Set num threads
	-R				Remove useless GUI components
	ID:(id name)	Set ID name to control main window
	-K				No allocation OpenMP stack
	Style[style]	style=windows, windowsvista, fusion, or macintosh
	StopForDebug	Stop for Debug at first
*/

int main(int argc, char *argv[])
{

#ifdef _SDEBUG
	LeakCheckerStart();
#endif

	if(CheckExeVersion(argc, argv)==false)
		return 1;
	
	QApplication a(argc, argv);
	
	bool	LogOutMode=false;
	char	LogFileName[256]=/**/"C:/LogOut.txt";
	bool	PartsReEntrantMode=false;
	QString	GlobalParmaFileName;
	int		NumThreads=16;
	int		WorkerID=-1;
	bool	WorkerIDEnabled=false;
	QString	AbsPath;
	bool	DupOK=true;
	bool	AddSystemMenu=false;
	bool	DefaultGUI_DotFileNameMode=false;
	QString	DefaultGUI_DotFileName=/**/"GUI.dat";
	bool	EditPasswordMode=false;
	QString	BootPassword;
	bool	EnableDuplicate=false;
	bool	RemoveUselessGUI=false;
	QString	IdentificationName;
	bool	NoAllocOpenMPStack=false;
	QString	Style = "windowsvista";
	bool	StopForDebug=false;
	QString	UserPath;

	QString	GUIFileName=/**/"RobotRegulusWorld.gui";


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

		else if(stricmp(argv[i],/**/"Single")==0){
			DupOK=false;
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
			PartsReEntrantMode=true;
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

	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	if(PartsReEntrantMode==true){
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	}

	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if(strnicmp(argv[i],"SetNumThreads",13)==0){
			char	*fp=&argv[i][13];
			NumThreads=1;
			sscanf(fp,/**/"%d",&NumThreads);
			#ifdef _MSC_VER
			omp_set_num_threads(NumThreads);
			#endif
		}
		else if(strnicmp(argv[i],"ID:",3)==0){
			char	*fp=&argv[i][3];
			IdentificationName=fp;
		}
		else if (strnicmp(argv[i], "Style", 5) == 0) {
			char* fp = &argv[i][5];
			Style = QString::fromLocal8Bit(fp);
		}
		else if(stricmp(argv[i],/**/"Duplicate")==0){
			EnableDuplicate=true;
		}
		else if(stricmp(argv[i],/**/"Single")==0){
			DupOK=false;
		}
		else if((*argv[i]=='G' || *argv[i]=='g') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GUIFileName=fp;
		}
		else if((*argv[i]=='W' || *argv[i]=='w') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(sscanf(fp,/**/"%d",&WorkerID)==1){
				WorkerIDEnabled=true;
			}
		}
		else if((*argv[i]=='U' || *argv[i]=='u') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			DefaultGUI_DotFileName=fp;
			DefaultGUI_DotFileNameMode=true;
		}
		else if(strcmp(argv[i],/**/"LogOut")==0){
			LogOutMode=true;
		}
		else if(stricmp(argv[i],/**/"-K")==0){
			NoAllocOpenMPStack=true;
		}
		else if((*argv[i]=='E' || *argv[i]=='e') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(*fp=='P' || *fp=='p'){
				EditPasswordMode=true;
				BootPassword=QString(fp+1);
			}
		}
		else if((*argv[i]=='l' || *argv[i]=='L') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			strncpy(LogFileName,fp,sizeof(LogFileName));
		}
		else if(stricmp(argv[i],/**/"YAddMenu")==0){
			AddSystemMenu=true;
		}
		else if(stricmp(argv[i],/**/"-R")==0){
			RemoveUselessGUI=true;
		}
	}
	#ifdef _MSC_VER
	if(NoAllocOpenMPStack==false){
		kmp_set_stacksize_s(64000000);
	}
	#endif

	QApplication::setStyle(Style);

	BootupLogoForm	LogoForm(NULL);
	LogoForm.show();
	QCoreApplication::processEvents();

	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	RegulusWorld	*WorldBase=new RegulusWorld(Layers);
	Layers->GetAnyData()->AppendList(WorldBase);
	Layers->GetParamGlobal()->AllocateTargetBuff=false;
	Layers->GetParamGlobal()->AllocateMasterBuff=false;

	if(Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath())==false){
		QMessageBox Q(/**/"Load error"
					, /**/"Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}
	WorldBase->InitialLoadParam();

	Layers->SetModeInspectionPlayer(true);
	WorldBase->InitialLoadDevice();

	DWORD	ErrorCode=0;
	QString	ErrorMsg;
	if(G->Initial(Layers,ErrorCode ,ErrorMsg,false)==false || ErrorCode!=0){
		QString  msg=QString(/**/"GUI Error: ")
			+QString::number(ErrorCode);
		QMessageBox Q(ErrorMsg
					, msg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	Layers->LoadGUILanguage(Layers->GetParamGlobal()->GUILanguageFileName);

	Layers->SetGUIFileName(GUIFileName);
	RootNameListContainer	AlgorithmRootNameList;
	QFile	gfile(GUIFileName);
	if(gfile.open(QIODevice::ReadOnly)==true){
		if(G->GetGUIInstanceRoot()->LoadOnlyAlgorithm(&gfile)==true){
			AlgorithmRootNameList=G->GetGUIInstanceRoot()->AlgorithmList;
		}
		gfile.close();
	}
	if(Layers->GetStatusController()!=NULL){
		Layers->GetStatusController()->LoadDef();
	}

	QString Msg;
	if(G->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
		QMessageBox Q(/**/"Error"
					, Msg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	Layers->LoadAttrDefault();
	if(LogOutMode==true)
		Layers->GetLogCreater()->Initial(LogFileName);

	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList);
	Layers->ReadLogicSettingFiles(true);

	if(Layers->GetParamComm()->GetConnectedPCNumb()!=0){
		Layers->GetParamComm()->EnabledComm=true;
	}

	Layers->LoadLevelFolderContainerFromDB();
	Layers->InitialAlgorithmLibrary();

	MainGUIFormBase	*MainForm=NULL;
	QFile	file(GUIFileName);
	if(file.open(QIODevice::ReadOnly)==true){
		Layers->SetGUIFileName(GUIFileName);
		G->GetGUIInstanceRoot()->CloseAll();
		QString ErrorMsg;
		if(G->GetGUIInstanceRoot()->LoadInstances(&file,ErrorMsg)==false){
			QMessageBox::critical ( NULL, /**/"Loading Error", ErrorMsg, QMessageBox::Ok);
			return(3);
		}
		if(RemoveUselessGUI==true){
			G->RemoveUselessGUI();
		}
		RootNameListContainer LackOfAlgorithm;
		if(Layers->CheckInstalledAlgorithm(AlgorithmRootNameList,LackOfAlgorithm)==false){
			RootNameList	*v=LackOfAlgorithm.GetFirst();
			QString	msg=QString(/**/"Lack of Algorithn : Root(")+v->DLLRoot+QString(/**/") Name(")+v->DLLName+QString(/**/")");
			QMessageBox::critical ( NULL, msg, ErrorMsg, QMessageBox::Ok);
			return(3);
		}
		Layers->SetLanguageCode(false,true,true);
		Layers->InitialAllocExecuterDim();
		Layers->InitialResult();
		MainForm=(MainGUIFormBase *)G->GetGUIInstanceRoot()->CreateMainForm(Layers,GUIInstancePack::_Center,AddSystemMenu);
		//G->GetGUIInstanceRoot()->ShowAll(Layers,GUIInstancePack::_Center,AddSystemMenu);
	}
	else{
		Layers->SetLanguageCode();
		QString	Msg=QString(/**/"Can't load GUI file(")+GUIFileName +QString(/**/")");
		QMessageBox::critical ( NULL, /**/"Loading Error", Msg, QMessageBox::Ok);
		return(4);
	}
	AlgorithmRootNameList.RemoveAll();
	if(EntryPointToFuncGlobal->IsMasterPC()==true){
		MainForm->SetSingleExecution(QString("RobotRegulusWorld-")+GUIFileName);
		if(EnableDuplicate==false && MainForm->CheckDoubleBoot()==true){
			Layers->CloseInformed();
			LogoForm.close();
			/*
			QMessageBox::StandardButton	RetButton=QMessageBox::warning(NULL,"Double boot","Do you close previous program?" ,QMessageBox::Yes | QMessageBox::No);
			if(RetButton==QMessageBox::Yes){
				MainForm->RequirePrebootedSoftwareToTerminate();
			}
			else{
				QApplication::quit();
				return 50;
			}
			*/
			QMessageBox::warning(NULL,"Double boot","Now executing another same RobotRegulusWorld.exe. Please close all RobotRegulusWorld.exe from Task-Manager" ,QMessageBox::Ok);
			return 11;
		}
	}

	Layers->ReadBaseSettingFiles(true);

	Layers->SetMainForm(MainForm);
	if(DefaultGUI_DotFileNameMode==true){
		Layers->GetParamGUI()->SetDefaultFileName(DefaultGUI_DotFileName);
	}
	//Layers->GetParamGUI()->LoadDefault();
	if(MainForm!=NULL){
		Layers->SetGUIInstancePack(G->GetGUIInstanceRoot());
		G->GetGUIInstanceRoot()->ShowAll(MainForm,Layers,Layers->GetParamGUI(),false);
	}

	//Layers->InitialArrangementDLL();

	G->GetGUIInstanceRoot()->GetFirstForm()->SetName(/**/"RobotRegulusWorld");
	Layers->SetMainForm(MainForm);

#ifdef _MSC_VER
	if(_CrtCheckMemory()==false)
		return(-1);
#endif

	Layers->GetParamGUI()->LoadDefault(Layers->GetUserPath());

	G->InitialMultiComputer(G->GetGUIInstanceRoot()->GetFirstForm());

	if(EntryPointToFuncGlobal->IsMasterPC()==true){

#ifdef HASP_ENABLE
	/*
		if(HaspCheck("je8398hw")==false){
			Hasplib *hasplib = new Hasplib();
			if(hasplib->HaspCheck(0)==false){
				QMessageBox::critical ( NULL, "Hasp Error", "Mismatch Hasp code", QMessageBox::Ok);
				delete hasplib;
				return 0;
			}
			delete hasplib;
		}
	*/

	Layers->SetApplicationCode(/**/"je8398hw");
	if(Layers->AddInitialHasp(/**/"SentinelHasp")==false){
		QMessageBox::critical(NULL,/**/"Error"
						, /**/"No Security library");
		return(10);
	}
	if(Layers->IsAuthenticationPassed(NULL)==false){
		QMessageBox::critical ( NULL, "Hasp Error", "Mismatch Hasp code", QMessageBox::Ok);
		return 10;
	}
#endif
	}

	if(WorkerIDEnabled==false){
		SelectWorkerForm	*DW=new SelectWorkerForm(Layers);
		if(EntryPointToFuncGlobal->IsMasterPC()==true){
			LogoForm.close();
			GeneralDialog	DWorker(NULL,DW,Layers->GetMainWidget());
			Layers->CloseInformed();
			DWorker.exec();
			LogoForm.show();
			Layers->SetWorkerID	(DW->SelectWorkerID	);
			Layers->SetWorkerName	(DW->SelectWorkerName);
		}
	}
	else{
		Layers->SQLSetWorker(WorkerID);
	}


	Layers->InitialFinalize(G->GetGUIInstanceRoot()->GetFirstForm());
#ifdef _MSC_VER
	if(_CrtCheckMemory()==false)
		return(-1);
#endif

	Layers->BroadcastMachineID();

	//Layers->ReadAllSettingFiles(true);
	Layers->ReadOtherSettingFiles(true);
	Layers->InitialAfterParamLoaded();
//#ifdef _MSC_VER
//	if(_CrtCheckMemory()==false)
//		return(-1);
//#endif

	Layers->InitialFilterBank();
	Layers->InitialResultAnalizer();
	Layers->InitialSyncGUI();
	Layers->InitialPrinter();
	//QMessageBox::warning (NULL, "Test", "Test");
	//GSleep(3000);
//#ifdef _MSC_VER
//	if(_CrtCheckMemory()==false)
//		return(-1);
//#endif
		ExecuteInitialAfterEditInfo EInfo;
		Layers->ExecuteInitialAfterEdit(EInfo);
	//}

	GUIFormBase	*B=G->GetGUIInstanceRoot()->GetFirstForm();
	B->BroadcastDirectly(GUIFormBase::_BC_BuildForShow,0);

	Layers->ExecuteLogoInGUIForm(B ,/**/"",/**/"");

	if(EntryPointToFuncGlobal->IsMasterPC()==true){
		Layers->GetPasswordHolder()->SetDefaultFile(GUIFileName);
		Layers->GetPasswordHolder()->LoadDefaultFile();
		Layers->GetPasswordHolder()->SetupOnlyPassword(*G->GetGUIInstanceRoot());
	}

	Layers->DeliverOutlineOffset();
	Layers->OpenCommsForDirectComm();
	if(EntryPointToFuncGlobal->IsMasterPC()==true){
		Layers->DeliverAllCommsForDirectComm(5000);
	}
	else{
		Layers->OpenCommsForDirectComm();
	}
	Layers->LoadFilterDef();
	Layers->CloseInformed();
	LogoForm.close();

	if(EntryPointToFuncGlobal->IsMasterPC()==true){
		if(checkBootupPassword(Layers, "RobotRegulusWorld","Password.dat")==false){
			return -2;
		}
	}

	MainForm->ReflectAlignment();
	if(G!=NULL && G->GetGUIInstanceRoot()!=NULL && MainForm!=NULL){
		G->GetGUIInstanceRoot()->ReadyParam(MainForm);
		MainForm->ReflectSize();
	}
	if(EditPasswordMode==true){
		Layers->SetEditPasswordMode(true);
		Layers->CloseInformed();
		LogoForm.close();
		QString Password=QInputDialog::getText ( NULL, /**/"Input Boot-Password", "Boot-Password", QLineEdit::Password);
		if(BootPassword.isEmpty()==true){
			if(Layers->GetPasswordHolder()->IsPasswordExists(Password)==false)
				return 10;
		}
		else{
			if(BootPassword!=Password){
				return 10;
			}
		}
	}

	PasswordDropper	*PWForm=NULL;
	if(EditPasswordMode==true){
		PWForm=new PasswordDropper(Layers);
		PWForm->GUIPack=G->GetGUIInstanceRoot();
		PWForm->show();
	}
	//else{
	//	Layers->GetPasswordHolder()->SetupOnlyPassword(*G->GetGUIInstanceRoot());
	//}
	if(Layers->GetStatusController()!=NULL){
		Layers->GetStatusController()->InstallFilter();
	}
	Layers->PrepareResult();
	Layers->GetOperationLoggerData()->PutLogStart("RobotRegulusWorld");

	if(IdentificationName.isEmpty()==false){
		MainForm->StartIdentificationServer(IdentificationName);
	}
	Layers->LoadShadowChildrenDLL();
	G->InitialIntegration();
	Layers->LoadRegulationDefault();

	G->AfterStartSequence();

	ComponentListContainer NoComponentList;
	if(Layers->CheckDependencyDLL(NoComponentList)==false){
		NoComponentDialog	D(NoComponentList);
		D.exec();
	}

	int	ret=false;
	if(Layers->GetOnTerminating()==false){
		Layers->StartReady();
		ret=a.exec();
	}

	Layers->GetOperationLoggerData()->PutLogClose();
	Layers->SetOnTerminating(true);

	//MainGUIFormBase	*MainBase=dynamic_cast<MainGUIFormBase *>(G->GetGUIInstanceRoot()->GetFirstForm());
	//if(MainBase!=NULL){
	//	MainBase->OutputPosition();
	//}
	Layers->CloseDatabase();

	return ret;

	//return ret;

	delete	G;
	if(PWForm!=NULL){
		delete	PWForm;
	}

}
