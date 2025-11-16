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
#include "RepairGUIMain.h"
#include <QDate>

#include "XGUI.h"
#include "XDataInExe.h"
#include "XDataInExe.h"
#include <stdio.h>
#include <ThreadSequence.h>
#include "XSequenceRepairLocal.h"
#include "XExecuteInspectBase.h"
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "SelectWorkerForm.h"
#include "XDataInLayerCommander.h"
#include "hasplib.h"
#include "XForWindows.h"
#include "SingleExecute.h"
#include "XShowVersion.h"
#include "XExecuteInspectForReview.h"
#include "XExecuteInspectBase.h"
#include "XPassword.h"
#include "PasswordDropper.h"
#include "XStatusController.h"
#include "XLogOut.h"
#include "Regulus64System.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

int	XDbg;
ExecuteInspectForReview	*ExeIns;


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

/*
	Commandline option

	A[Path]			Set current path to [Path]
	G[Filename]		Set GUI file to [Filename]
	S[Filename]		Load Global-Param file to set [Filename]
	W[WorkerID]		Set [WorkerID]
	Single			Single Execution
	LogOut			Set LogOut mode
	L[FileName]		LogFileName
	YAddMenu		Add system menu
	Revision		Show Revision on command line
	NDM				No database message
	NOPASSWORD		No Password usage
	EP				Edit password
	NDS			No sequence execution
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef _SDEBUG
	LeakCheckerStart();
#endif
	if(CheckExeVersion(argc, argv)==false){
		QMessageBox::critical(NULL, "CheckExeVersion error", "This version is mismatch.");
		return 1;
	}
	/*
#ifdef HASP_ENABLE
	if(HaspCheck("je8398hw")==false){
		if(HaspCheck("k38fj306")==false){	//EditPC
			QMessageBox::critical ( NULL, "Hasp Error", "Mismatch Hasp code", QMessageBox::Ok);
			return 0;
		}
	}
#endif
	*/

	//// リミット時間
	//QDate limitDate = QDate(2013, 2, 1);// 年月日で指定、この時になると起動不可となる

	//// リミット超過判定(ただし、windowsの時刻をいじった場合は回避される？)
	//QDate date = QDate::currentDate();
	//if(date>=limitDate){
	//	QMessageBox::critical(NULL, "Date is over", "This software is active until 2013/02/01.");
	//	return EXIT_SUCCESS;
	//}

	bool	LogOutMode=false;
	char	LogFileName[256]=/**/"C:/LogOut.txt";
	bool	PartsReEntrantMode=false;
	bool	NoCamDevice=false;
	QString	GlobalParmaFileName;
	int		WorkerID=-1;
	bool	WorkerIDEnabled=false;
	QString	AbsPath;
	bool3	DisallocateTarget=none3;
	bool3	DisallocateMaster=none3;
	bool	DupOK=true;
	bool	AddSystemMenu=false;
	bool	NoDatabaseMessage=false;
	bool	NoNeedSequence	=false;
	bool	UsePassword=true;
	QString SequenceFileName;
	QString CommFileName;
	bool	EditPasswordMode=false;

	QString	GUIFileName=/**/"RepairStation.gui";
	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if(stricmp(argv[i],"Single")==0){
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
		else if((*argv[i]=='W' || *argv[i]=='w') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(sscanf(fp,/**/"%d",&WorkerID)==1){
				WorkerIDEnabled=true;
			}
		}
		else if(stricmp(argv[i],/**/"NoCamDevice")==0){
			NoCamDevice=true;
		}
		else if(stricmp(argv[i],/**/"NoPassword")==0){
			UsePassword=false;
		}
		else if(stricmp(argv[i],/**/"LogOut")==0){
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
		else if(stricmp(argv[i],/**/"NDS")==0){
			NoNeedSequence=true;
		}
		else if(*argv[i]=='M' || *argv[i]=='m'){
			SequenceFileName = (argv[i]+1);
		}
		else if(*argv[i]=='C' || *argv[i]=='c'){
			CommFileName = (argv[i]+1);
		}
		else if((*argv[i]=='E' || *argv[i]=='e') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(*fp=='P' || *fp=='p'){
				EditPasswordMode=true;
			}
		}
	}

	QFileInfo	FInfo(argv[0]);
	if(DupOK==false && SingleExecute(FInfo.fileName())==false){
		KillDupProcess(FInfo.fileName());
		//return 100;
	}
	if(DupOK==false){
		KillPreviousDupProcess();
	}

    RepairGUIMain w;
	/*
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	*/
	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	QCoreApplication::processEvents();

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	EntryPointToFuncGlobal->NoCamDevice=NoCamDevice;
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	if(PartsReEntrantMode==true){
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	}

	Layers->SetCurrentPath(QDir::currentPath());
	if(Layers->GetParamGlobal()->LoadDefault()==false){
		QMessageBox Q("Load error"
					, "Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}
	if(CommFileName.isNull()==false){
		ParamComm *comm = Layers->GetParamComm();
		QString filename_old = comm->GetDefaultFileName();
		comm->SetDefaultFileName(CommFileName);
		qDebug() << comm->GetSavedFileName();
	}
	ParamComm *comm = Layers->GetParamComm();
	QString filename_old;

	Layers->GetParamComm()->LoadDefault();

	Layers->GetParamGlobal()->AllocateTargetBuff=false;
	Layers->GetParamGlobal()->AllocateMasterBuff=false;
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
	RootNameListContainer	AlgorithmRootNameList;
	QFile	gfile(GUIFileName);
	if(gfile.open(QIODevice::ReadOnly)==true){
		if(G->GetGUIInstanceRoot()->LoadOnlyAlgorithm(&gfile)==true){
			AlgorithmRootNameList=G->GetGUIInstanceRoot()->AlgorithmList;
		}
		gfile.close();
	}
	Layers->SetLanguageCode();

	QString Msg;
	if(G->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
		QMessageBox Q(/**/"Error"
					, Msg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	//Layers->LoadDefault();
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
	if(KDatabase->LoadFromDDL(Layers->GetParamGlobal()->DatabaseDDL_FileName)==true){
		KDatabase->Check(&EList);
	}
	if(Layers->OpenDatabase(*KDatabase)==false){
			QMessageBox::warning (NULL, /**/"Error"
									, /**/"Could not open database");
			return(2);
	}
	Layers->LoadLevelFolderContainerFromDB();


	/*
		QString RetVolumeNameBuffer;
		int32	VolumeSerialNumber;		// ボリュームのシリアル番号
		int32	MaximumComponentLength;	// ファイル名の最大の長さ
		int32	FileSystemFlags;			// ファイルシステムのオプション
		QString	FileSystemNameBuffer;		// ファイルシステム名を格納するバッファ

		MtGetVolumeInformation(
			"e:\\",				// ルートディレクトリ
			RetVolumeNameBuffer,     // ボリューム名バッファ
			VolumeSerialNumber,		// ボリュームのシリアル番号
			MaximumComponentLength,	// ファイル名の最大の長さ
			FileSystemFlags,			// ファイルシステムのオプション
			FileSystemNameBuffer		// ファイルシステム名を格納するバッファ
		);
*/

	Layers->InitialAlgorithmBlob();
	Layers->InitialAlgorithmLibrary();
	QString errMsg;
	if(G->InitialAdditionalFieldFromGUI(Layers->GetDatabase(), errMsg)==false){
		QMessageBox::critical(NULL, /**/"GUI Initial Error", errMsg);
		return (-1);
	}

	GUIFormBase	*MainForm=NULL;
	QFile	file(GUIFileName);
	if(file.open(QIODevice::ReadOnly)==true){
		Layers->SetGUIFileName(GUIFileName);
		G->GetGUIInstanceRoot()->CloseAll();
		QString ErrorMsg;
		if(G->GetGUIInstanceRoot()->LoadInstances(&file,ErrorMsg)==false){
			QMessageBox::critical ( NULL, /**/"Loading Error", ErrorMsg, QMessageBox::Ok);
			return(3);
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
		MainForm=G->GetGUIInstanceRoot()->CreateMainForm(Layers,GUIInstancePack::_Center,AddSystemMenu);
		//G->GetGUIInstanceRoot()->ShowAll(Layers,GUIInstancePack::_Center,AddSystemMenu);
	}
	else{
		Layers->SetLanguageCode();
		QString	Msg=QString(/**/"Can't load GUI file(")+GUIFileName +QString(/**/")");
		QMessageBox::critical ( NULL, /**/"Loading Error", Msg, QMessageBox::Ok);
		return(4);
	}

	if(SequenceFileName.isNull()==false){
		Layers->GetParamGlobal()->Sequence_FileName = SequenceFileName;
	}

	SeqControlParam	*SeqControlParamData=new SeqControlParam(Layers);
	Layers->SetMainForm(MainForm);
	ThreadSequence	*Seq=NULL;
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
						,_GetDataSpecialFloatOperand);
	}
	EntryPointToFuncGlobal->SetExecuteInspect(ExeIns);
	ExeIns=new ExecuteInspectForReview(MainForm,EntryPointToFuncGlobal,SeqControlParamData);

	Layers->InitialLight(true);
	if(MainForm!=NULL){
		Layers->SetGUIInstancePack(G->GetGUIInstanceRoot());
		G->GetGUIInstanceRoot()->ShowAll(MainForm	,Layers
																,Layers->GetParamGUI());
	}
	ExeIns->InitialPrepare();
	ExeIns->Prepare();
	ExeIns->AfterPrepare();

	Layers->InitialArrangementDLL();
	
	#ifdef _MSC_VER
	if(_CrtCheckMemory()==false){
		return(-1);
	}
	#endif
	Layers->GetParamGUI()->LoadDefault();

	G->GetGUIInstanceRoot()->GetFirstForm()->SetName(/**/"ReviewPlayer");

	if(NoNeedSequence==false){
		if(EntryPointToFuncGlobal->IsMasterPC()==true && Seq!=NULL){
			QString	ErrorLine;
			if(Layers->GetParamGlobal()->Sequence_FileName.isEmpty()==false
			&& Seq->LoadStartSequenceFile(G->GetGUIInstanceRoot()->GetFirstForm()
					,Layers->GetParamGlobal()->Sequence_FileName
					,Layers->GetParamGlobal()->IODLL_FileName
					,Layers->GetParamGlobal()->IODefine_FileName
					,ErrorLine
					,Layers->GetParamGlobal()->IOSomething)==false){
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
	}

	G->InitialMultiComputer(G->GetGUIInstanceRoot()->GetFirstForm());

	if(WorkerIDEnabled==false){
		SelectWorkerForm	*DW=new SelectWorkerForm(Layers);
		if(EntryPointToFuncGlobal->IsMasterPC()==true){
			GeneralDialog	DWorker(NULL,DW,Layers->GetMainWidget());
			DWorker.exec();
			Layers->SetWorkerID	(DW->SelectWorkerID	);
			Layers->SetWorkerName	(DW->SelectWorkerName);
		}
	}
	else{
		Layers->SQLSetWorker(WorkerID);
	}

	Layers->InitialFinalize(G->GetGUIInstanceRoot()->GetFirstForm());
	#ifdef _MSC_VER
		if(_CrtCheckMemory()==false){
			return(-1);
		}
	#endif

	Layers->LoadOutlineOffsetForDatabase();
	Layers->ReadAllSettingFiles(true);
	Layers->InitialAfterParamLoaded();

	GUIFormBase	*B=G->GetGUIInstanceRoot()->GetFirstForm();
	B->BroadcastDirectly(GUIFormBase::_BC_BuildForShow,0);
	Layers->ExecuteLogoInGUIForm(B ,/**/"",/**/"");
	Layers->CloseInformed();

	Layers->GetPasswordHolder()->SetDefaultFile(GUIFileName);
	Layers->GetPasswordHolder()->LoadDefaultFile();
	PasswordDropper	*PWForm=NULL;
	if(EditPasswordMode==true){
		Layers->SetEditPasswordMode(true);
		PWForm=new PasswordDropper(Layers);
		PWForm->GUIPack=G->GetGUIInstanceRoot();
		PWForm->show();
	}
	else{
		Layers->GetPasswordHolder()->SetupOnlyPassword(*G->GetGUIInstanceRoot());
	}
	if(Layers->GetStatusController()!=NULL){
		Layers->GetStatusController()->InstallFilter();
	}

	if(UsePassword==true){
		if(checkBootupPassword(Layers, "RepairGUIMain","Password.dat")==false)
			return -2;
	}
	Layers->GetOperationLoggerData()->PutLogStart("RepairGUIMain");
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

		delete	Seq;
		Seq=NULL;
	}
	if(PWForm!=NULL){
		delete	PWForm;
	}
	//return ret;

	//delete	KDatabase;
	delete	G;
	
	#ifdef _MSC_VER
	_CrtCheckMemory();
	#endif

}
