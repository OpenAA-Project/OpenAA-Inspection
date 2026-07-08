/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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
#include <stdio.h>
#include <ThreadSequence.h>
#include "XSequenceRepairLocal.h"
#include "XExecuteInspectBase.h"
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "SelectWorkerForm.h"
#include "XDataInLayerCommander.h"
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
#include "XOpenAA.h"
#include "XMainGUIFormBase.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

int	XDbg;
ExecuteInspectForReview	*ExeIns;

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
	NDS				No sequence execution
*/

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false){
		QMessageBox::critical(NULL, "CheckExeVersion error", "This version is mismatch.");
		return 1;
	}
	char	TBuff[256];
	strcpy(TBuff,"-platformpluginpath");
	argv[argc] = TBuff;
	argc++;

	char	CurrentBuff[256];
	strcpy(CurrentBuff,(char *)QDir::currentPath().toStdString().c_str());
	argv[argc] = CurrentBuff;	
	argc++;
	
	QCoreApplication::addLibraryPath(CurrentBuff);
    QApplication a(argc, argv);

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
	QString	UserPath;
	bool	RemoveUselessGUI=false;
	bool	StopForDebug=false;

	QString	GUIFileName=/**/"RepairStation.gui";

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
		else if(stricmp(argv[i],/**/"NoCamDevice")==0){
			NoCamDevice=true;
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
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal,::GetUserPath(UserPath));
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	EntryPointToFuncGlobal->NoCamDevice=NoCamDevice;
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	if(PartsReEntrantMode==true){
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	}

	for(int i=1;i<argc;i++){
		if((*argv[i]=='G' || *argv[i]=='g') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GUIFileName=fp;
		}
		else if((*argv[i]=='W' || *argv[i]=='w') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(sscanf(fp,/**/"%d",&WorkerID)==1){
				WorkerIDEnabled=true;
			}
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
		else if(stricmp(argv[i],/**/"-R")==0){
			RemoveUselessGUI=true;
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

	Layers->SetCurrentPath(QDir::currentPath());
	if(Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath())==false){
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

	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());

	Layers->GetParamGlobal()->AllocateTargetBuff=false;
	Layers->GetParamGlobal()->AllocateMasterBuff=false;
	if(Layers->GetStatusController()!=NULL){
		Layers->GetStatusController()->LoadDef();
	}
	GUIInstancePack	*GPack=G->GetGUIInstanceRoot();
	RootNameListContainer	GUIRootNameList;
	QFile	GGfile(GUIFileName);
	if(GGfile.open(QIODevice::ReadOnly)==true){
		Layers->SetGUIFileName(GUIFileName);
		GPack->CloseAll();
		QString ErrorMsg;
		if(GPack->LoadInstances(&GGfile,false,ErrorMsg)==false){
			QMessageBox::critical ( NULL, /**/"Loading Error", ErrorMsg, QMessageBox::Ok);
			return(3);
		}
		GPack->GetEntryGUI(GUIRootNameList);
	}

	DWORD	ErrorCode=0;
	QString	ErrorMsg;
	if(G->Initial(Layers,ErrorCode ,ErrorMsg,false,&GUIRootNameList)==false || ErrorCode!=0){
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

	Layers->InitialAlgorithmBlob();
	Layers->InitialAlgorithmLibrary();
	QString errMsg;
	if(G->InitialAdditionalFieldFromGUI(Layers->GetDatabase(), errMsg)==false){
		QMessageBox::critical(NULL, /**/"GUI Initial Error", errMsg);
		return (-1);
	}

	QString StrSystemPath = Layers->GetSystemPath();
	if(StrSystemPath.isEmpty()==false){
		QDir::setCurrent(StrSystemPath);
	}
	GUIFormBase	*MainForm=NULL;
	QFile	file(GUIFileName);
	if(file.open(QIODevice::ReadOnly)==true){
		Layers->SetGUIFileName(GUIFileName);
		G->GetGUIInstanceRoot()->CloseAll();
		QString ErrorMsg;
		if(G->GetGUIInstanceRoot()->LoadInstances(&file,true,ErrorMsg)==false){
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
	Layers->GetParamGUI()->LoadDefault(Layers->GetUserPath());

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