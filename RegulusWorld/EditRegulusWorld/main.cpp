/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RegulusWorld\EditRegulusWorld\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#define _SDEBUG


#ifdef _SDEBUG
#define	NOMINMAX
#include <Windows.h>
#include "LeakChecker.h"
#pragma comment(lib, /**/"LeakChecker")
#endif

#include "XMacro.h"
//#include "InspectionEditorResource.h"
#include "XApplication.h"
#include "BootupLogoForm.h"
#include "ClosingForm.h"

#include "XGUI.h"
#include <stdio.h>
#include <QInputDialog>
//#include "XExecuteInspect.h"
#include "XDatabase.h"
//#include "IDatabaseMessageDialog.h"
#include "XGeneralDialog.h"
#include "SelectWorkerForm.h"

#ifdef _MSC_VER
#include "hasplib.h"
#include "sentinellib.h"
#endif

#include "SingleExecute.h"
#include "PasswordDropper.h"
#include "XPassword.h"
#include "XShowVersion.h"
#include <omp.h>
#include "XCrossObj.h"
#include "XStatusController.h"
#include "IntegrationLib.h"
#include "XIntegrationBase.h"
#include "XLogOut.h"
#include "XGeneralFunc.h"
#include "Regulus64System.h"
#include "XRegulusWorld.h"

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
	T[Port]			Set Transfer-Port number to [Port]
	S[Filename]		Load Global-Param file to set [Filename]
	W[WorkerID]		Set [WorkerID]
	U[GUI.dat]		Set default GUI.dat file name
	P[FileName]		Load Pixel file for Master Image
	Single			Single Execution
	EP				Edit password
	LogOut			Set LogOut mode
	L[FileName]		LogFileName
	YAddMenu		Add system menu
	Revision		Show Revision on command line
	SetNumThreads[n]	Set num threads
	-R				Remove useless GUI components
	ID:(id name)	Set ID name to control main window
	-K				No allocation OpenMP stack
	Style[style]	style=windows, windowsvista, fusion, or macintosh
	StopForDebug	Stop for Debug at first
*/

static	bool HaspCheck(QString strKey)
{
#ifdef _MSC_VER
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
#else
	return true;
#endif
}

#ifdef HASP_ENABLE
static	bool SentinelCheck(QString strKey)
{
	QStringList RetList;
	Sentinellib _Sentinel;

	if (false == _Sentinel.SentinelExecute(RetList))
		return false;

	for (int Cnt = 0; Cnt < (RetList.count() / 2); Cnt++)
		if (strKey == RetList.at(Cnt * 2 + 1))
			if (QDate::currentDate() <= QDate::fromString(RetList.at(Cnt * 2), /**/"yyyyMMdd"))
				return true;

	return false;
}
#endif

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return /**/"InspectionGeneral.lng";
}

int main(int argc, char *argv[])
{
	MainApplication *a=new MainApplication(argc, argv);

	bool	PartsReEntrantMode=false;
	QString	GlobalParmaFileName;
	QString	GUIFileName="EditRegulusWorld.gui";
	int		WorkerID=-1;
	int		NumThreads=16;
	bool	WorkerIDEnabled=false;
	bool	LogOutMode=false;
	char	LogFileName[256]=/**/"C:/LogOut.txt";
	QString	AbsPath;
	bool	DupOK=true;
	bool	EditPasswordMode=false;
	bool	AddSystemMenu=false;
	bool	DefaultGUI_DotFileNameMode=false;
	bool	RemoveUselessGUI=false;
	QString	DefaultGUI_DotFileName= "GUI.dat";
	QString	BootPassword;
	QString	IdentificationName;
	bool	NoAllocOpenMPStack=false;
	QString	Style = "windowsvista";
	bool	StopForDebug=false;
	QString	UserPath;

	if(CheckExeVersion(argc, argv)==false)
		return 1;

#ifdef HASP_ENABLE
	if (HaspCheck("k38fj306") == false) {
		if (HaspCheck("je8398hw") == false) {
			Hasplib* hasplib = new Hasplib();
			if (hasplib->HaspCheck(1) == false) {
				if (hasplib->HaspCheck(0) == false) {
					QMessageBox::critical(NULL, "Hasp Error", "Mismatch Hasp code", QMessageBox::Ok);
					delete hasplib;
					return 0;
				}
			}
			delete hasplib;
		}
	}
#endif


	/*
#if 0
//	if(SentinelCheck("k38fj306")==false){
	if(SentinelCheck("12345678")==false){
//	if(SentinelCheck("87654321")==false){
//	if(SentinelCheck("zzzzzzzz")==false){
//	if(SentinelCheck("aaaaaaaa")==false){
//		QMessageBox::critical ( NULL, "Hasp Error", "Mismatch Hasp code", QMessageBox::Ok);
		return 0;
	}
#endif

#ifdef _SDEBUG
	LeakCheckerStart();
#endif
*/


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
		else if(stricmp(argv[i],"Single")==0){
			DupOK=false;
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
		else if(strnicmp(argv[i],"StopForDebug",12)==0){
			StopForDebug=true;
		}
		else if (strnicmp(argv[i], "Style", 5) == 0) {
			char* fp = &argv[i][5];
			Style = QString::fromLocal8Bit(fp);
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
		else if((*argv[i]=='E' || *argv[i]=='e') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(*fp=='P' || *fp=='p'){
				EditPasswordMode=true;
				BootPassword=QString(fp+1);
			}
		}
		else if(strcmp(argv[i],/**/"LogOut")==0){
			LogOutMode=true;
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
		else if(stricmp(argv[i],/**/"-K")==0){
			NoAllocOpenMPStack=true;
		}
	}
	if(StopForDebug==true){
		QMessageBox::information(NULL,"Stop","Please push OK button to go",QMessageBox::Ok);
	}
	{
		QFileInfo	FInfo(argv[0]);
		if(DupOK==false && SingleExecute(FInfo.fileName())==false){
			return 100;
		}
	}

#ifdef _MSC_VER
#ifdef __INTEL_COMPILER
	if (NoAllocOpenMPStack == false) {
		kmp_set_stacksize_s(32000000);
	}
#endif
#endif


    //InspectionEditor w;
    //w.show();
	//a.connect(QCoreApplication::instance(), SIGNAL(lastWindowClosed()), &a, SLOT(QuitProcess()));

	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	QApplication::setStyle(Style);

	BootupLogoForm	*LogoForm=new BootupLogoForm(NULL);
	LogoForm->show();
	QCoreApplication::processEvents();

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	#ifdef _MSC_VER
	_heapchk();
	#endif
	if(PartsReEntrantMode==true)
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);

	if(Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath())==false){
		QMessageBox Q("Load error"
					, "Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}

	Layers->GetParamGlobal()->AllocateTargetBuff=false;
	Layers->GetParamGlobal()->AllocateMasterBuff=false;

	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	RegulusWorld	*WorldBase=new RegulusWorld(Layers);
	Layers->GetAnyData()->AppendList(WorldBase);

	DWORD	ErrorCode=0;
	{
		QString	ErrorMsg;
		if(G->Initial(Layers,ErrorCode ,ErrorMsg,false)==false || ErrorCode!=0){
			QString  msg=QString(/**/"GUI Error: ")
				+QString::number(ErrorCode);
			QMessageBox Q(msg
						, ErrorMsg, QMessageBox::Critical
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(1);
		}
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

	{
		QString Msg;
		if(G->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
			QMessageBox Q( /**/"Error"
						, Msg, QMessageBox::Critical
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(1);
		}
		if(WorldBase->InitialLoadParam()==false){
			QMessageBox Q( /**/"Error"
						, /**/"Initial error", QMessageBox::Critical
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(1);
		}
	}
	Layers->LoadAttrDefault();
	if(LogOutMode==true){
		Layers->GetLogCreater()->Initial(LogFileName);
	}

	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList);
	Layers->ReadLogicSettingFiles(true);

	WorldBase->InitialAlgorithm(AlgorithmPathList);

	Layers->LoadLevelFolderContainerFromDB();
	Layers->InitialAlgorithmLibrary();

	GUIFormBase	*MainForm=NULL;
	{
		QFile	file(GUIFileName);
		if(file.open(QIODevice::ReadOnly)==true){
			Layers->SetGUIFileName(GUIFileName);
			G->GetGUIInstanceRoot()->CloseAll();
			QString ErrorMsg;
			if(G->GetGUIInstanceRoot()->LoadInstances(&file,ErrorMsg)==false){
				QMessageBox::critical ( NULL, /**/"Loading Error", ErrorMsg, QMessageBox::Ok);
				return(3);
			}
			file.close();
			if(RemoveUselessGUI==true){
				G->RemoveUselessGUI();
			}

			RootNameListContainer LackOfAlgorithm;
			if(Layers->CheckInstalledAlgorithm(AlgorithmRootNameList,LackOfAlgorithm)==false){
				RootNameList	*v=LackOfAlgorithm.GetFirst();
				QString	msg=QString(/**/"Lack of Algorithm");
				ErrorMsg= QString("Root(")+v->DLLRoot+QString(/**/") Name(")+v->DLLName+QString(/**/")");
				QMessageBox::critical ( NULL, msg, ErrorMsg, QMessageBox::Ok);
				return(3);
			}
			Layers->SetLanguageCode(false,true,true);
			Layers->InitialAllocExecuterDim();
			Layers->InitialResult();
			MainForm=G->GetGUIInstanceRoot()->CreateMainForm(Layers,GUIInstancePack::_Center,AddSystemMenu);
			//G->GetGUIInstanceRoot()->ShowAll(Layers,GUIInstancePack::_Center,AddSystemMenu);
		}
		else{
			Layers->SetLanguageCode();
			QString	Msg=QString(/**/"Can't load GUI file(")+GUIFileName +QString(/**/")");
			QMessageBox::critical ( NULL, /**/"Loading Error", Msg, QMessageBox::Ok);
			return(4);
		}
	}
	if(MainForm!=NULL){
		Layers->SetGUIInstancePack(G->GetGUIInstanceRoot());
		Layers->SetMainForm(G->GetGUIInstanceRoot()->GetFirstForm());
		G->GetGUIInstanceRoot()->ShowAll(MainForm	,Layers
										,Layers->GetParamGUI());
	}
	//Layers->InitialArrangementDLL();
	AlgorithmRootNameList.RemoveAll();

	G->GetGUIInstanceRoot()->GetFirstForm()->SetName(/**/"EditRegulusWorld");
	LogoForm->show();
	QCoreApplication::processEvents();
	

	if(DefaultGUI_DotFileNameMode==true){
		Layers->GetParamGUI()->SetDefaultFileName(DefaultGUI_DotFileName);
	}
	Layers->GetParamGUI()->LoadDefault(Layers->GetUserPath());
	//G->GetGUIInstanceRoot()->GetFirstForm()->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);

	if(WorkerIDEnabled==false){
		SelectWorkerForm	*DW=new SelectWorkerForm(Layers);
		LogoForm->close();
		GeneralDialog	DWorker(NULL,DW,Layers->GetMainWidget());
		Layers->CloseInformed();
		DWorker.exec();
		LogoForm->show();
		//QCoreApplication::processEvents();
		Layers->SetWorkerID	(DW->SelectWorkerID		);
		Layers->SetWorkerName	(DW->SelectWorkerName	);
	}
	else{
		Layers->SQLSetWorker(WorkerID);
	}
	Layers->InitialFinalize(G->GetGUIInstanceRoot()->GetFirstForm());
	//G->GetGUIInstanceRoot()->GetFirstForm()->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	//omp_set_max_active_levels(2);

	Layers->InitialFilterBank();
	Layers->InitialResultAnalizer();

	Layers->BroadcastMachineID();
	Layers->InitialAfterParamLoaded();

	ExecuteInitialAfterEditInfo EInfo;
	Layers->ExecuteInitialAfterEdit(EInfo);
	Layers->GetParamGlobal()->InitializeNetworkDrive();
	GUIFormBase	*B=G->GetGUIInstanceRoot()->GetFirstForm();
	B->BroadcastDirectly(GUIFormBase::_BC_BuildForShow,0);
	Layers->ExecuteLogoInGUIForm(B ,/**/"",/**/"");

	Layers->GetPasswordHolder()->SetDefaultFile(GUIFileName);
	Layers->GetPasswordHolder()->LoadDefaultFile();

	MainForm->ReflectAlignment();
	if(G!=NULL && G->GetGUIInstanceRoot()!=NULL && MainForm!=NULL){
		G->GetGUIInstanceRoot()->ReadyParam(MainForm);
	}

	if(EditPasswordMode==true){
		Layers->SetEditPasswordMode(true);
		Layers->CloseInformed();
		LogoForm->close();
		QString Password=QInputDialog::getText ( NULL, /**/"Input Boot-Password", "Boot-Password"
												, QLineEdit::Password);
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
	else{
		Layers->GetPasswordHolder()->SetupOnlyPassword(*G->GetGUIInstanceRoot());
	}

	Layers->DeliverOutlineOffset();
	if(EntryPointToFuncGlobal->IsMasterPC()==true){
		Layers->DeliverAllCommsForDirectComm(50000);
	}
	else{
		Layers->OpenCommsForDirectComm();
	}
	Layers->LoadFilterDef();
	if(Layers->GetStatusController()!=NULL){
		Layers->GetStatusController()->InstallFilter();
	}

	Layers->CloseInformed();
	LogoForm->close();
	delete	LogoForm;

	if(checkBootupPassword(Layers, "EditRegulusWorld","Password.dat")==false)
		return -2;

	G->GetGUIInstanceRoot()->AfterPrepare();

	Layers->GetOperationLoggerData()->PutLogStart("EditRegulusWorld");

	if(IdentificationName.isEmpty()==false){
		MainGUIFormBase *m=dynamic_cast<MainGUIFormBase *>(MainForm);
		if(m!=NULL){
			m->StartIdentificationServer(IdentificationName);
		}
	}
	G->InitialIntegration();
	Layers->LoadRegulationDefault();
	Layers->LoadShadowChildrenDLL();


	int	ret=false;
	if(Layers->GetOnTerminating()==false){
		Layers->StartReady();
		ret=a->exec();
	}

	ClosingForm		CL;
	CL.setWindowTitle(/**/"Editor");
	CL.show();
	CL.update();

	Layers->GetOperationLoggerData()->PutLogClose();
	Layers->SetOnTerminating(true);

	MainGUIFormBase	*MainBase=dynamic_cast<MainGUIFormBase *>(G->GetGUIInstanceRoot()->GetFirstForm());
	if(MainBase!=NULL){
		MainBase->OutputPosition();
	}
	Layers->CloseDatabase();

	//delete	Layers;

	GlobalParmaFileName.clear();
	
	//delete	Layers;

	delete	G;
	//_heapchk();

	if(PWForm!=NULL){
		delete	PWForm;
	}

	//delete	a;

	//__kmp_cleanup_user_locks();
	return ret;

}
