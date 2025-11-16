/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\InspectionPlayer\InspectionPlayer\main.cpp
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
#include "InspectionPlayer.h"
#include "BootupLogoForm.h"
#include "ClosingForm.h"

#include "InspectionPlayerResource.h"
#include "XGUI.h"
#include <stdio.h>
#include <QLineEdit>
#include <QInputDialog>
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspect.h"
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
#include "XStatusController.h"
#include "IntegrationLib.h"
#include "XIntegrationBase.h"
#include "XParamIntegrationMaster.h"
#include "XLogOut.h"
#include "XGeneralFunc.h"
#include "NoComponentDialog.h"
#include "Regulus64System.h"
#include "XGeneralStocker.h"
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
	NoCamDevice		Not initialize nor use local camera
	LogOut			Set LogOut mode
	L[FileName]		LogFileName
	YAddMenu		Add system menu
	Revision		Show Revision on command line
	NDM				No database message
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
	QString	CommParmaFileName;
	int		NumThreads=16;
	int		WorkerID=-1;
	QString	PixFileName;
	bool	NoCamDevice=false;
	int		MasterID=-1;
	int		BootingLevel=0;
	bool	WorkerIDEnabled=false;
	QString	AbsPath;
	bool3	DisallocateTarget=none3;
	bool3	DisallocateMaster=none3;
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
	QString	IdentificationName;
	bool	NoAllocOpenMPStack=false;
	QString	Style = "windowsvista";
	bool	StopForDebug=false;
	QString	UserPath;

	QString	GUIFileName=/**/"InspectionPlayer.gui";
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
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
			PartsReEntrantMode=true;
		}
		else if((*argv[i]=='C' || *argv[i]=='c') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			CommParmaFileName=fp;
		}
		else if((*argv[i]=='P' || *argv[i]=='p') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			PixFileName=fp;
		}
		else if((*argv[i]=='M' || *argv[i]=='m') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&MasterID);
		}
		else if((*argv[i]=='B' || *argv[i]=='b') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&BootingLevel);
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
		else if(strcmp(argv[i],/**/"NoCamDevice")==0){
			NoCamDevice=true;
		}
		else if(strcmp(argv[i],/**/"NoSequence")==0){
			NoSequence=true;
		}
		else if(strcmp(argv[i],/**/"LogOut")==0){
			LogOutMode=true;
		}
		else if(stricmp(argv[i],/**/"-K")==0){
			NoAllocOpenMPStack=true;
		}
		else if((*argv[i]=='D' || *argv[i]=='d') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(*fp=='T' || *fp=='t')
				DisallocateTarget=true3;
			else if(*fp=='M' || *fp=='m')
				DisallocateMaster=true3;
		}
		else if((*argv[i]=='E' || *argv[i]=='e') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(*fp=='T' || *fp=='t')
				DisallocateTarget=false3;
			else if(*fp=='M' || *fp=='m')
				DisallocateMaster=false3;
			else if(*fp=='P' || *fp=='p'){
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

	QFileInfo	FInfo(argv[0]);
	if(DupOK==false && SingleExecute(FInfo.fileName())==false){
		KillDupProcess(FInfo.fileName());
		//return 100;
	}
#ifdef _MSC_VER
#ifdef __INTEL_COMPILER
	if(NoAllocOpenMPStack==false){
		kmp_set_stacksize_s(64000000);
	}
#endif
#endif

    InspectionPlayer w;
	/*
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	*/
	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	QApplication::setStyle(Style);

	BootupLogoForm	LogoForm(NULL);
	LogoForm.show();
	QCoreApplication::processEvents();

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	EntryPointToFuncGlobal->NoCamDevice=NoCamDevice;
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

	if(Layers->GetParamComm()->GetConnectedPCNumb()!=0){
		Layers->GetParamComm()->EnabledComm=true;
	}

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
	Layers->GetGeneralStocker()->CreateExcludedList(EList);
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

	if(Layers->OpenDatabase(*KDatabase)==false){
			QMessageBox::warning (NULL, /**/"Error"
									, /**/"Could not open database");
			return(2);
	}
	Layers->LoadLevelFolderContainerFromDB();

	ParamIntegrationMaster	ParamIntegrationMasterData(Layers);
	ParamIntegrationMasterData.LoadDefault(Layers->GetUserPath());
	IntegrationBase	*IBase=new IntegrationBase(Layers,&ParamIntegrationMasterData);
	IBase->Initialize();
	Layers->SetIntegrationBase(IBase);

	/*
		QString RetVolumeNameBuffer;
		int32	VolumeSerialNumber;		// ?リュ??のシリアル番号
		int32	MaximumComponentLength;	// フ?イル名の最大の長さ
		int32	FileSystemFlags;			// フ?イルシステ?のオプション
		QString	FileSystemNameBuffer;		// フ?イルシステ?名を格?するバッフ?

		MtGetVolumeInformation(
			"e:\\",				// ル?トディレクトリ
			RetVolumeNameBuffer,     // ?リュ??名バッフ?
			VolumeSerialNumber,		// ?リュ??のシリアル番号
			MaximumComponentLength,	// フ?イル名の最大の長さ
			FileSystemFlags,			// フ?イルシステ?のオプション
			FileSystemNameBuffer		// フ?イルシステ?名を格?するバッフ?
		);
*/
	if(NoDatabaseMessage==false){
		Layers->InitialAlgorithmBlob();
	}
	Layers->InitialAlgorithmLibrary();
	if(G->InitialAdditionalFieldFromGUI(Layers->GetDatabase(),ErrorMsg)==false){
		QString  msg=QString(/**/"Database Error");
		QMessageBox Q(msg
					, ErrorMsg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	if(Layers->GetGeneralStocker()->InitialAdditionalFieldFromGUI(Layers->GetDatabase(),ErrorMsg)==false){
		QString  msg=QString(/**/"Database Error");
		QMessageBox Q(msg
					, ErrorMsg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}

	if(BootingLevel==0 && EntryPointToFuncGlobal->IsMasterPC()==true){
		Layers->LoadOutlineOffsetForDatabase();
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
		MainForm->SetSingleExecution(QString("InspectionPlayer-")+GUIFileName);
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
			QMessageBox::warning(NULL,"Double boot","Now executing another same InspectionPlayer.exe. Please close all InspectionPlayer.exe from Task-Manager" ,QMessageBox::Ok);
			return 11;
		}
	}


	SeqControlParam	*SeqControlParamData=new SeqControlParam(Layers);
	
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
	Layers->ReadBaseSettingFiles(true);
	int	CameraCount=-1;
	ExecuteInspect	*ExeIns=new ExecuteInspect(MainForm,EntryPointToFuncGlobal,SeqControlParamData);
	EntryPointToFuncGlobal->SetExecuteInspect(ExeIns);
	ExeIns->Initial();
	if(EntryPointToFuncGlobal->NoCamDevice==false){
		if(ExeIns->IsLocalCamera()==true){
			CameraCount=ExeIns->GetCameraCount();
	
			if(CameraCount>0){
				Layers->GetParamGlobal()->TotalCameraNumb=CameraCount;
				Layers->Reallocate(-1,CameraCount,-1);
			}

			int32 ErrorCode;
			if(ExeIns->InitialCamera(ErrorCode)==false){
				if(EntryPointToFuncGlobal->IsMasterPC()==true){
					LogoForm.close();
					QString  msg=QString(/**/"Camera Error Code=")
								+QString::number(ErrorCode,16);
					QMessageBox::warning (NULL, /**/"Error", msg);
					return(2);
				}
				else{
					int	globalPage=Layers->GetGlobalPageFromLocal(0);
					CmdCameraErrorOccursMsg	Mq(Layers,/**/"ANY",/**/"ANY",globalPage);
					Mq.SendFromSlaveToMaster(globalPage ,0);				
				}
			}
			if(ExeIns->LoadDefault()==false){
				if(ExeIns->LoadDefaultOldVer()==false){
					LogoForm.close();
					QMessageBox::warning (NULL, "Alert"
											, "カメラ設定が正常に読み込めませんでした");
					LogoForm.show();
				}
			}

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
	Layers->SetMainForm(MainForm);
	if(DefaultGUI_DotFileNameMode==true){
		Layers->GetParamGUI()->SetDefaultFileName(DefaultGUI_DotFileName);
	}
	//Layers->GetParamGUI()->LoadDefault();
	if(MainForm!=NULL){
		Layers->SetGUIInstancePack(G->GetGUIInstanceRoot());
		G->GetGUIInstanceRoot()->ShowAll(MainForm,Layers,Layers->GetParamGUI(),false);
	}
	ExeIns->InitialPrepare();
	ExeIns->Prepare();
	ExeIns->AfterPrepare();

	//Layers->InitialArrangementDLL();

	G->GetGUIInstanceRoot()->GetFirstForm()->SetName(/**/"InspectionPlayer");
	Layers->SetMainForm(MainForm);
	Layers->LoadGUILanguage(Layers->GetParamGlobal()->GUILanguageFileName);
	
#ifdef _MSC_VER
	if(_CrtCheckMemory()==false)
		return(-1);
#endif

	Layers->GetParamGUI()->LoadDefault(Layers->GetUserPath());


	Layers->InitialLight(true);
	//G->GetGUIInstanceRoot()->GetFirstForm()->SetName(/**/"InspectionPlayer");

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

	G->InitialMultiComputer(G->GetGUIInstanceRoot()->GetFirstForm());

	if(EntryPointToFuncGlobal->IsMasterPC()==true){

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


	ExeIns->start();
	Layers->InitialFinalize(G->GetGUIInstanceRoot()->GetFirstForm());
#ifdef _MSC_VER
	if(_CrtCheckMemory()==false)
		return(-1);
#endif

	//QMessageBox::warning (NULL, "Test1", "Test1");

	//G->GetGUIInstanceRoot()->GetFirstForm()->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	if(BootingLevel==0 && EntryPointToFuncGlobal->IsMasterPC()==true){
		Layers->BroadcastMachineID();
	}
//#ifdef _MSC_VER
//	if(_CrtCheckMemory()==false)
//		return(-1);
//#endif

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
	B->connect(B,SIGNAL(SignalClose(GUIFormBase	*)),ExeIns,SLOT(Exit(GUIFormBase *)));
	Layers->ExecuteLogoInGUIForm(B ,/**/"",/**/"");

	if(EntryPointToFuncGlobal->IsMasterPC()==true){
		Layers->GetPasswordHolder()->SetDefaultFile(GUIFileName);
		Layers->GetPasswordHolder()->LoadDefaultFile();
		Layers->GetPasswordHolder()->SetupOnlyPassword(*G->GetGUIInstanceRoot());
	}
	if(BootingLevel==0){
		NPListPack<ErrorInfoList>	ErrorPages;
		Layers->CheckSlave(ErrorPages);
		if(ErrorPages.GetNumber()!=0){
			LogoForm.close();
			ErrorMessageDialog	E(ErrorPages);
			E.exec();
			for(ErrorInfoList *c=ErrorPages.GetFirst();c!=NULL;c=c->GetNext()){
				if(c->ReqReboot==true){
					return(8);
				}
			}
		}
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


	if(PixFileName.isEmpty()==false){
		Layers->LoadMasterImage(PixFileName);
	}
	if(MasterID>=0){
		bool CriticalErrorOccured;
		QString ErrorMessageOfFalse;
		if(Layers->SQLLoadMasterData(MasterID,-1,true,CriticalErrorOccured,ErrorMessageOfFalse)==true){
			ExecuteInitialAfterEditInfo EInfo;
			EInfo.CalledInLoadMaster=true;
			Layers->ExecuteInitialAfterEdit(EInfo);
			GUIFormBase	*B=G->GetGUIInstanceRoot()->GetFirstForm();
			B->BroadcastDirectly(GUIFormBase::_BC_BuildForShow,0);
		}
	}
	if(EntryPointToFuncGlobal->IsMasterPC()==true){
		if(checkBootupPassword(Layers, "InspectionEditor","Password.dat")==false){
			return -2;
		}
	}

	MainForm->ReflectAlignment();
	if(G!=NULL && G->GetGUIInstanceRoot()!=NULL && MainForm!=NULL){
		G->GetGUIInstanceRoot()->ReadyParam(MainForm);
		ExeIns->ReadyParam();
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
	Layers->GetOperationLoggerData()->PutLogStart("InspectionPlayer");

	if(IdentificationName.isEmpty()==false){
		MainForm->StartIdentificationServer(IdentificationName);
	}
	Layers->LoadShadowChildrenDLL();
	G->InitialIntegration();
	Layers->LoadRegulationDefault();

	G->AfterStartSequence();
	ExeIns->AfterStartSequence();
	IBase->InitialForLocalHost();
	
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

	if(Seq!=NULL){
		ClosingForm		CL;
		CL.setWindowTitle(Seq->GetTitle());
		CL.show();
		CL.update();
	}


	Layers->GetOperationLoggerData()->PutLogClose();
	Layers->SetOnTerminating(true);

	ExeIns->CamRelease();


	//MainGUIFormBase	*MainBase=dynamic_cast<MainGUIFormBase *>(G->GetGUIInstanceRoot()->GetFirstForm());
	//if(MainBase!=NULL){
	//	MainBase->OutputPosition();
	//}
	Layers->CloseDatabase();
	delete	KDatabase;

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
	return ret;

	ExeIns->terminate();
	ExeIns->wait(1000);
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

	//return ret;

	delete	G;
	if(PWForm!=NULL){
		delete	PWForm;
	}

}
