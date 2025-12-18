/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\InspectionEditor\main.cpp
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
#include "InspectionEditorResource.h"
#include "XApplication.h"
#include "BootupLogoForm.h"
#include "ClosingForm.h"

#include "XGUI.h"
#include <stdio.h>
#include <QInputDialog>
#include "XExecuteInspect.h"
#include "XDatabase.h"
#include "IDatabaseMessageDialog.h"
#include "XGeneralDialog.h"
#include "SelectWorkerForm.h"

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
	C[Filename]		Load Comm-Param file to set [Filename]
	W[WorkerID]		Set [WorkerID]
	U[GUI.dat]		Set default GUI.dat file name
	P[FileName]		Load Pixel file for Master Image
	M[MasterID]		Load MasterData from database
	B[Level]		Set BootingLevel[Level]
	DT				Disallocate Target buffer
	DM				Disallocate Master buffer
	ET				Enable allocate Target buffer
	EM				Enable allocate Master buffer
	Single			Single Execution
	EP				Edit password
	LogOut			Set LogOut mode
	L[FileName]		LogFileName
	YAddMenu		Add system menu
	Revision		Show Revision on command line
	NDM				No database message
	SetNumThreads[n]	Set num threads
	-R				Remove useless GUI components
	BootSmall[PageCount]	Boot with small image size parameter
	ID:(id name)	Set ID name to control main window
	-K				No allocation OpenMP stack
	Style[style]	style=windows, windowsvista, fusion, or macintosh
	StopForDebug	Stop for Debug at first
*/


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
	char	TBuff[256];
	strcpy(TBuff,"-platformpluginpath");
	argv[argc] = TBuff;
	argc++;

	char	CurrentBuff[256];
	strcpy(CurrentBuff,(char *)QDir::currentPath().toStdString().c_str());
	argv[argc] = CurrentBuff;	
	argc++;

	MainApplication *a=new MainApplication(argc, argv);

	bool	PartsReEntrantMode=false;
	QString	GlobalParmaFileName;
	QString	CommParmaFileName;
	QString	GUIFileName="InspectionEditor.gui";
	int		WorkerID=-1;
	QString	PixFileName;
	int		MasterID=-1;
	int		NumThreads=16;
	int		BootingLevel=0;
	bool	WorkerIDEnabled=false;
	bool	LogOutMode=false;
	char	LogFileName[256]=/**/"C:/LogOut.txt";
	bool3	DisallocateTarget=none3;
	bool3	DisallocateMaster=none3;
	QString	AbsPath;
	bool	DupOK=true;
	bool	EditPasswordMode=false;
	bool	AddSystemMenu=false;
	bool	NoDatabaseMessage=false;
	bool	DefaultGUI_DotFileNameMode=false;
	bool	RemoveUselessGUI=false;
	int		BootSmall=-1;
	QString	DefaultGUI_DotFileName= "GUI.dat";
	QString	BootPassword;
	QString	IdentificationName;
	bool	NoAllocOpenMPStack=false;
	QString	Style = "windowsvista";
	bool	StopForDebug=false;
	QString	UserPath;

	if(CheckExeVersion(argc, argv)==false)
		return 1;


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
		else if((*argv[i]=='P' || *argv[i]=='p') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			PixFileName=fp;
		}
		else if((*argv[i]=='M' || *argv[i]=='m') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&MasterID);
		}
		else if(strnicmp(argv[i],/**/"BootSmall",9)==0){
			char	*fp=&argv[i][9];
			BootSmall=1;
			sscanf(fp,/**/"%d",&BootSmall);
		}
		else if((*argv[i]=='B' || *argv[i]=='b') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&BootingLevel);
		}
		else if((*argv[i]=='D' || *argv[i]=='d') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(*fp=='T' || *fp=='t'){
				DisallocateTarget=true3;
			}
			else if(*fp=='M' || *fp=='m'){
				DisallocateMaster=true3;
			}
		}
		else if((*argv[i]=='E' || *argv[i]=='e') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(*fp=='T' || *fp=='t'){
				DisallocateTarget=false3;
			}
			else if(*fp=='M' || *fp=='m'){
				DisallocateMaster=false3;
			}
			else if(*fp=='P' || *fp=='p'){
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
		else if(stricmp(argv[i],/**/"NDM")==0){
			NoDatabaseMessage=true;
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
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	#ifdef _MSC_VER
	_heapchk();
	#endif
	if(PartsReEntrantMode==true)
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	if(CommParmaFileName.isEmpty()==false){
		Layers->GetParamComm()->SetDefaultFileName(CommParmaFileName);
	}

	if(Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath())==false){
		QMessageBox Q("Load error"
					, "Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}
	if(BootSmall>=1){
		Layers->GetParamGlobal()->DotPerLine=100;
		Layers->GetParamGlobal()->MaxLines=100;
		Layers->GetParamGlobal()->PageNumb=BootSmall;
	}
	if(DisallocateTarget==true3)
		Layers->GetParamGlobal()->AllocateTargetBuff=false;
	else
	if(DisallocateTarget==false3)
		Layers->GetParamGlobal()->AllocateTargetBuff=true;
	if(DisallocateMaster==true3)
		Layers->GetParamGlobal()->AllocateMasterBuff=false;
	else
	if(DisallocateMaster==false3)
		Layers->GetParamGlobal()->AllocateMasterBuff=true;

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
	}
	Layers->SetBootingLevel(BootingLevel);
	Layers->SetMasterType(BootingLevel);
	Layers->LoadAttrDefault();
	if(LogOutMode==true)
		Layers->GetLogCreater()->Initial(LogFileName);

	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList);
	
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
	ExcludedListPack	*EList=new ExcludedListPack();
	Layers->MakeAlgorithmBlobList(*EList);
	G->CreateExcludedList(*EList);

	if(NoDatabaseMessage==false){
		if(KDatabase->LoadFromDDL(Layers->GetParamGlobal()->DatabaseDDL_FileName)==true){
			if(KDatabase->Check(EList)==false){
				IDatabaseMessageDialog	M(Layers->GetMainWidget());
				if(M.SetMessages(KDatabase->GetMessageList())==true){
					M.exec();
				}
				KDatabase->Change(EList);
				if(M.SetMessages(KDatabase->GetMessageList())==true){
					M.exec();
				}
			}
		}
	}
	delete	EList;

	if(Layers->OpenDatabase(*KDatabase)==false){
		QMessageBox Q( /**/"Error"
					, /**/"Could not open database", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(2);
	}
	Layers->LoadLevelFolderContainerFromDB();
	
	ParamIntegrationMaster	ParamIntegrationMasterData(Layers);
	ParamIntegrationMasterData.LoadDefault(Layers->GetUserPath());
	IntegrationBase	*IBase=new IntegrationBase(Layers,&ParamIntegrationMasterData);
	IBase->Initialize();
	Layers->SetIntegrationBase(IBase);

	if(NoDatabaseMessage==false){
		Layers->InitialAlgorithmBlob();
	}
	Layers->InitialAlgorithmLibrary();
	{
		QString	ErrorMsg;
		if(G->InitialAdditionalFieldFromGUI(Layers->GetDatabase(),ErrorMsg)==false){
			QString  msg=QString(/**/"Database Error");
			QMessageBox Q(msg
						, ErrorMsg, QMessageBox::Critical
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(1);
		}
	}
	if(BootingLevel==0 && EntryPointToFuncGlobal->IsMasterPC()==true){
		Layers->LoadOutlineOffsetForDatabase();
	}

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
	for(GUIInstancePack *L=G->GUIInstanceRoot.GetFirst();L!=NULL;L=L->GetNext()){
		for(GUIItemInstance *s=L->NPListPack<GUIItemInstance>::GetFirst();s!=NULL;s=s->GetNext()){
			IntegratorRelation	*d=dynamic_cast<IntegratorRelation *>(s->GetForm());
			if(d!=NULL){
				d->SetParamPointer(&ParamIntegrationMasterData);
			}
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

	G->GetGUIInstanceRoot()->GetFirstForm()->SetName(/**/"InspectionEditor");
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
	if(PixFileName.isEmpty()==false){
		Layers->LoadMasterImage(PixFileName);
		/*
		QFile	F(PixFileName);
		if(F.open(QIODevice::ReadOnly)==true){
			Layers->LoadImages(&F);
		}
		*/
	}

	//Layers->InitialLight(false);
	Layers->InitialFilterBank();
	Layers->InitialResultAnalizer();

	if(BootingLevel==0 && EntryPointToFuncGlobal->IsMasterPC()==true){
		Layers->BroadcastMachineID();
	}

	Layers->ReadAllSettingFiles(true,BootSmall);
	Layers->InitialAfterParamLoaded();

	if(MasterID>=0){
		bool CriticalErrorOccured;
		QString ErrorMessageOfFalse;
		Layers->SQLLoadMasterData(MasterID,-1,true,CriticalErrorOccured,ErrorMessageOfFalse);
	}

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

	if(EditPasswordMode==true
	&& BootPassword.isEmpty()==false){
		Layers->SetEditPasswordMode(true);
		Layers->CloseInformed();
		LogoForm->close();
		QString Password=QInputDialog::getText ( NULL, /**/"Input Boot-Password", "Boot-Password"
												, QLineEdit::Password);
		if(Layers->GetPasswordHolder()->IsPasswordExists(Password)==false){
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

	if(checkBootupPassword(Layers, "InspectionEditor","Password.dat")==false)
		return -2;

	G->GetGUIInstanceRoot()->AfterPrepare();

	Layers->GetOperationLoggerData()->PutLogStart("InspectionEditor");

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
	delete	KDatabase;

	//delete	Layers;

	if(PixFileName.isEmpty()==false){
		QFileInfo	FInfo(PixFileName);
		if(FInfo.suffix().toUpper()==/**/"TMP"){
			QDir	PixFile(Layers->GetUserPath());
			PixFile.remove(PixFileName);
		}
	}
	if(GlobalParmaFileName.isEmpty()==false){
		QFileInfo	FInfo(GlobalParmaFileName);
		if(FInfo.suffix().toUpper()==/**/"TMP"){
			QDir	PixFile(Layers->GetUserPath());
			PixFile.remove(GlobalParmaFileName);
		}
	}

	PixFileName.clear();
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
