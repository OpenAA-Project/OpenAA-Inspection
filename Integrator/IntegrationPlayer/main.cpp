/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\IntegrationPlayer\main.cpp
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
#include "IntegrationPlayer.h"
#include "BootupLogoForm.h"

//#include "InspectionPlayerResource.h"
#include "XGUI.h"
#include "XDataInExe.h"
#include "XDataInExe.h"
#include <stdio.h>
#include <ThreadSequence.h>
#include <QInputDialog>
#include "XSequenceLocalExecuter.h"
#include "XExecuteIntegrationPlayer.h"
#include "XDatabase.h"
#include "IDatabaseMessageDialog.h"
#include "XGeneralDialog.h"
#include "SelectWorkerForm.h"
#include "XDataInLayerCommander.h"
#include "PasswordDropper.h"
#include "XPassword.h"
#include "hasplib.h"
#include "XForWindows.h"
#include "SingleExecute.h"
#include "XShowVersion.h"
#include "XLightClass.h"
#include "ErrorMessageDialog.h"
#include "XPassword.h"
#include "IntegrationLib.h"
#include "XParamIntegrationMaster.h"
#include "XIntegrationBase.h"
#include "XStatusController.h"
#include "XLogOut.h"
#include "NoComponentDialog.h"
#include "Regulus64System.h"
#include "XIntegrationComm.h"
#include <omp.h>

int	XDbg;

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
	T[Port]			Set Transfer-Port number to [Port]
	S[Filename]		Load Global-Param file to set [Filename]
	C[Filename]		Load Comm-Param file to set [Filename]
	W[WorkerID]		Set [WorkerID]
	U[GUI.dat]		Set default GUI.dat file name
	Single			Single Execution
	LogOut			Set LogOut mode
	L[FileName]		LogFileName
	YAddMenu		Add system menu
	Revision		Show Revision on command line
	NDM				No database message
	Duplicate		Enable multiple boot
	-R				Remove useless GUI components
	NoSequence		No need Sequence file
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
	QString	CommParmaFileName;
	int		WorkerID=-1;
	bool	WorkerIDEnabled=false;
	QString	AbsPath;
	bool	DupOK=true;
	bool	AddSystemMenu=false;
	bool	NoDatabaseMessage=false;
	bool	DefaultGUI_DotFileNameMode=false;
	QString	DefaultGUI_DotFileName=/**/"GUI.dat";
	bool	EditPasswordMode=false;
	QString	BootPassword;
	bool	EnableDuplicate=false;
	bool	NoSequence=false;
	bool	RemoveUselessGUI=false;
	bool	StopForDebug=false;
	QString	UserPath;

	QString	GUIFileName=/**/"InspectionPlayer.gui";
	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if(stricmp(argv[i],/**/"Duplicate")==0){
			EnableDuplicate=true;
		}
		else if(stricmp(argv[i],/**/"Single")==0){
			DupOK=false;
		}
		else if(strnicmp(argv[i],"StopForDebug",12)==0){
			StopForDebug=true;
		}
		else if((*argv[i]=='G' || *argv[i]=='g') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GUIFileName=fp;
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
			PartsReEntrantMode=true;
		}
		else if((*argv[i]=='C' || *argv[i]=='c') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			CommParmaFileName=fp;
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
		else if(strcmp(argv[i],/**/"NoSequence")==0){
			NoSequence=true;
		}
		else if(strcmp(argv[i],/**/"LogOut")==0){
			LogOutMode=true;
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
		else if(stricmp(argv[i],/**/"NDM")==0){
			NoDatabaseMessage=true;
		}
		else if(stricmp(argv[i],/**/"-R")==0){
			RemoveUselessGUI=true;
		}
	}

	if(StopForDebug==true){
		QMessageBox::information(NULL,"Stop","Please push OK button to go",QMessageBox::Ok);
	}
	//QMessageBox::warning(NULL,"Test"
	//				,"1234567890abcdefghijklmnopqrstuvwxyz‚ ‚¢‚¤‚¦‚¨1234567890abcdefghijklmnopqrstuvwxyz\n1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz"
	//				,QMessageBox::Ok);

	QFileInfo	FInfo(argv[0]);
	if(DupOK==false && SingleExecute(FInfo.fileName())==false){
		KillDupProcess(FInfo.fileName());
		//return 100;
	}
	kmp_set_stacksize_s(64000000);

    IntegrationPlayer w;
	/*
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	*/
	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	BootupLogoForm	LogoForm(NULL);
	LogoForm.show();
	QCoreApplication::processEvents();

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	if(PartsReEntrantMode==true){
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	}
	if(CommParmaFileName.isEmpty()==false){
		Layers->GetParamComm()->SetDefaultFileName(CommParmaFileName);
	}

	if(Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath())==false){
		QMessageBox Q(/**/"Load error"
					, /**/"Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	Layers->SetModeInspectionPlayer(true);

	ParamIntegrationMaster	ParamIntegrationMasterData(Layers);
	ParamIntegrationMasterData.LoadDefault(Layers->GetUserPath());

	if(ParamIntegrationMasterData.IntegrationSlaveMode==false){
		Layers->GetParamGlobal()->AllocateTargetBuff=false;
		Layers->GetParamGlobal()->AllocateMasterBuff=false;
	}
	if(Layers->GetStatusController()!=NULL){
		Layers->GetStatusController()->LoadDef();
	}

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

	QString	Msg;
	if(G->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
		QMessageBox Q(/**/"Error"
					, Msg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList);
	Layers->ReadLogicSettingFiles(true);

	LocalDatabaseBasicClass	*KDatabase=new LocalDatabaseBasicClass(Layers->GetDatabaseLoader(false)
																, Layers->GetParamGlobal()->LocalDatabase_FileName
																, Layers->GetParamGlobal()->LocalDatabase_HostName
																, Layers->GetParamGlobal()->LocalDatabase_Port
																, Layers->GetParamGlobal()->TransDatabaseIP
																, Layers->GetParamGlobal()->TransDatabasePort);
	if(KDatabase->IsExistDatabase()==false){
		QString  msg=QString(/**/"Not exist Database file! Create database?");
		int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
		if(ret==QMessageBox::No){
			return(4);
		}
		if(KDatabase->CreateDatabase()==false){
			QMessageBox Q( /**/"Error"
					, /**/"Could not create database", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(1);
		}
	}
	ExcludedListPack	EList;
	Layers->MakeAlgorithmBlobList(EList);
	G->CreateExcludedList(EList);
	if(KDatabase->LoadFromDDL(Layers->GetParamGlobal()->DatabaseDDL_FileName)==true){
		if(KDatabase->Check(&EList)==false){
			IDatabaseMessageDialog	M(Layers->GetMainWidget());
			if(NoDatabaseMessage==false){
				if(M.SetMessages(KDatabase->GetMessageList())==true){
					M.exec();
				}
			}
			KDatabase->Change(&EList);
			if(NoDatabaseMessage==false){
				if(M.SetMessages(KDatabase->GetMessageList())==true){
					M.exec();
				}
			}
		}
	}
	if(NoDatabaseMessage==false){
		KDatabase->LoadFromDDL(Layers->GetParamGlobal()->DatabaseDDL_FileName);
	}
	if(Layers->OpenDatabase(*KDatabase)==false){
			QMessageBox::warning (NULL, /**/"Error"
									, /**/"Could not open database");
			return(2);
	}
	Layers->LoadLevelFolderContainerFromDB();

	IntegrationBase	*IBase=new IntegrationBase(Layers,&ParamIntegrationMasterData);
	IBase->Initialize();
	Layers->SetIntegrationBase(IBase);
	if(NoDatabaseMessage==false){
		Layers->InitialAlgorithmBlob();
	}
	Layers->InitialAlgorithmLibrary();

	//G->InitialIntegration();

	Layers->LoadAttrDefault();
	if(LogOutMode==true)
		Layers->GetLogCreater()->Initial(LogFileName);

	if(Layers->GetParamComm()->GetConnectedPCNumb()!=0){
		Layers->GetParamComm()->EnabledComm=true;
	}

	if(G->InitialAdditionalFieldFromGUI(Layers->GetDatabase(),ErrorMsg)==false){
		QString  msg=QString(/**/"Database Error");
		QMessageBox Q(msg
					, ErrorMsg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}

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
		Layers->SetLanguageCode();
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

	SeqControlParam	*SeqControlParamData=new SeqControlParam(&w,Layers);
	
	//Layers->SetMainForm(MainForm);
	ThreadSequence	*Seq=NULL;
	if(NoSequence==false){
		if(EntryPointToFuncGlobal->IsMasterPC()==true){
			Seq=new ThreadSequence(Layers,MainForm);
			Layers->SetSequenceInstance(Seq);

			Seq->SetFunction(SeqControlParamData
							,_XSeqLocalInit
							,_SetDataSpecialOperand
							,_GetDataSpecialOperand
							,_SetDataSpecialBitOperand
							,_GetDataSpecialBitOperand
							,_SetDataSpecialStringOperand
							,_GetDataSpecialStringOperand
							,_SetDataSpecialFloatOperand
							,_GetDataSpecialFloatOperand
							);
		}
	}

	ExecuteIntegrationPlayer	*ExeIns=new ExecuteIntegrationPlayer(&w,EntryPointToFuncGlobal);
	ExeIns->Initial();

	Layers->SetMainForm(MainForm);
	if(DefaultGUI_DotFileNameMode==true){
		Layers->GetParamGUI()->SetDefaultFileName(DefaultGUI_DotFileName);
	}
	if(MainForm!=NULL){
		Layers->SetGUIInstancePack(G->GetGUIInstanceRoot());
		G->GetGUIInstanceRoot()->ShowAll(MainForm,Layers,Layers->GetParamGUI(),false);
	}
	ExeIns->InitialPrepare();
	ExeIns->Prepare();
	ExeIns->AfterPrepare();

	for(GUIInstancePack *L=G->GUIInstanceRoot.GetFirst();L!=NULL;L=L->GetNext()){
		for(GUIItemInstance *s=L->NPListPack<GUIItemInstance>::GetFirst();s!=NULL;s=s->GetNext()){
			IntegratorRelation	*d=dynamic_cast<IntegratorRelation *>(s->GetForm());
			if(d!=NULL){
				d->SetParamPointer(&ParamIntegrationMasterData);
			}
		}
	}

	G->GetGUIInstanceRoot()->GetFirstForm()->SetName(/**/"IntegrationPlayer");
	Layers->SetMainForm(MainForm);
	
	#ifdef _MSC_VER
	if(_CrtCheckMemory()==false){
		return(-1);
	}
	#endif

	Layers->GetParamGUI()->LoadDefault(Layers->GetUserPath());
	Layers->InitialLight(true);

	if(EntryPointToFuncGlobal->IsMasterPC()==true && Seq!=NULL){
		QString	ErrorLine;
		if(Seq->LoadStartSequenceFile(G->GetGUIInstanceRoot()->GetFirstForm()
				,Layers->GetParamGlobal()->Sequence_FileName
				,Layers->GetParamGlobal()->IODLL_FileName
				,Layers->GetParamGlobal()->IODefine_FileName
				,ErrorLine
				,Layers->GetParamGlobal()->IOSomething
				)==false){
			QString  msg=QString(/**/"Sequence Error:Line ")
						+ErrorLine;
			QMessageBox Q( /**/"Error"
						, msg, QMessageBox::Critical
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(1);
		}
		G->GetGUIInstanceRoot()->GetFirstForm()->setWindowTitle(Seq->GetTitle());
		Seq->start();
	}

	/*	
#ifdef HASP_ENABLE
		if(HaspCheck("je8398hw")==false){
			Hasplib *hasplib = new Hasplib();
			if(hasplib->HaspCheck(0)==false){
				QMessageBox::critical ( NULL, "Hasp Error", "Mismatch Hasp code", QMessageBox::Ok);
				delete hasplib;
				return 0;
			}
			delete hasplib;
		}
#endif
		*/

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


	ExeIns->start();
	Layers->InitialFinalize(G->GetGUIInstanceRoot()->GetFirstForm());
	#ifdef _MSC_VER
		if(_CrtCheckMemory()==false){
			return(-1);
		}
	#endif
	
	//_heapchk();

	//G->GetGUIInstanceRoot()->GetFirstForm()->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	Layers->ReadAllSettingFiles(true);
	Layers->InitialAfterParamLoaded();

	Layers->InitialPrinter();
	//QMessageBox::warning (NULL, "Test", "Test");
	//GSleep(3000);
		ExecuteInitialAfterEditInfo EInfo;
		Layers->ExecuteInitialAfterEdit(EInfo);
	//}

	GUIFormBase	*B=G->GetGUIInstanceRoot()->GetFirstForm();
	B->BroadcastDirectly(GUIFormBase::_BC_BuildForShow,0);
	B->connect(B,SIGNAL(SignalClose(GUIFormBase	*)),ExeIns,SLOT(Exit(GUIFormBase *)));
	Layers->ExecuteLogoInGUIForm(B ,/**/"",/**/"");

	if(EntryPointToFuncGlobal->IsMasterPC()==true){
		Layers->GetPasswordHolder()->SetDefaultFile(GUIFileName);
		Layers->GetPasswordHolder()->LoadDefaultFile();
		Layers->GetPasswordHolder()->SetupOnlyPassword(*G->GetGUIInstanceRoot());
	}

	Layers->CloseInformed();
	LogoForm.close();

	if(MainForm!=NULL){
		G->GetGUIInstanceRoot()->ReadyParam(MainForm);
		ExeIns->ReadyParam();
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
	//_heapchk();

	PasswordDropper	*PWForm=NULL;
	if(EditPasswordMode==true){
		PWForm=new PasswordDropper(Layers);
		PWForm->GUIPack=G->GetGUIInstanceRoot();
		PWForm->show();
	}
	if(Layers->GetStatusController()!=NULL){
		Layers->GetStatusController()->InstallFilter();
	}
	//_heapchk();
	Layers->LoadShadowChildrenDLL();
	G->InitialIntegration();
	IBase->InitialForLocalHost();
	ComponentListContainer NoComponentList;
	if(Layers->CheckDependencyDLL(NoComponentList)==false){
		NoComponentDialog	D(NoComponentList);
		D.exec();
	}

	Layers->GetOperationLoggerData()->PutLogStart("IntegrationPlayer");
    int	ret=a.exec();
	Layers->GetOperationLoggerData()->PutLogClose();

	MainGUIFormBase	*MainBase=dynamic_cast<MainGUIFormBase *>(G->GetGUIInstanceRoot()->GetFirstForm());
	if(MainBase!=NULL){
		MainBase->OutputPosition();
	}

	if(Seq!=NULL){
		Seq->SetTerminateFlag();
		for(time_t t=time(NULL);time(NULL)-t<60;){
			if(Seq->IsAliveMode()==false){
				break;
			}
		}
		Seq->wait(5000);
		if(Seq!=NULL && Seq->isFinished()==false){
			Seq->terminate();
			Seq->wait(1000);
		}
	}
	//return ret;

	delete	IBase;
	Layers->CloseOne();

	//ExeIns->terminate();
	//ExeIns->wait(1000);
	delete	ExeIns;

	if(Seq!=NULL){
		delete	Seq;
		Seq=NULL;
	}
	if(EntryPointToFuncGlobal->IsMasterPC()==true){
		if(Layers->GetLightBase()!=NULL){
			Layers->GetLightBase()->LightOff();
		}
	}

	return ret;

	//delete	KDatabase;
	delete	G;
	
	#ifdef _MSC_VER
	_CrtCheckMemory();
	#endif

}
