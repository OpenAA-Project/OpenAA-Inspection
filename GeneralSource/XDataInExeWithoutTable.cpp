/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataInExe.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XGeneralFunc.h"
#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <stdlib.h>
#include <QTimer>
#include <QThread>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XAlert.h"
#include "XPointer.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "XCriticalFunc.h"
#include "XDatabaseLoader.h"
#include "XPieceArchitect.h"
#include "XCrossObj.h"
#include "XDirectComm.h"
#include "XLightClass.h"
#include "ServiceLibResource.h"
#include "XGUIFormBase.h"
#include "XFilterManager.h"
#include "XErrorCode.h"
#include "XFileRegistry.h"
#include "XOutlineOffset.h"
#include "XLogo.h"
#include "XAnyData.h"
#include <QMessageBox>
#include "XDirectComm.h"
#include "XGeneralStocker.h"
#include "XLearningRule.h"
#include "XPassword.h"
#include "XServiceForLayers.h"
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include "XSyncGUI.h"
#include "XStatusController.h"
#include "XLearningRegist.h"
#include "XImageProcess.h"
#include "XLotInformation.h"
#include "XHistgramByParam.h"
#include "XDateTime.h"
#include "XShareMasterData.h"
#include "XResultAnalizer.h"

#include "XGUI.h"
#include "XDataInExe.h"
#include "XGeneralFunc.h"
#include "XExecuteInspectBase.h"
#include "XDirectComm.h"
#include "XImageExpand.h"
#include "XResize.h"
#include "XAuthenticationInside.h"
#include "XResult.h"
#include "XWriteResultThread.h"
#include "XLibraryType.h"
#include "XArrangementFromFile.h"
#include "XLogOut.h"
#include "XParamDatabase.h"
#include "XImageStocker.h"
#include "XShadowTree.h"
#include "XFileThread.h"
#include "XLevel.h"

LayersBase::LayersBase(EntryPointBase *pEntryPoint,bool _StartThreadWriteMode)
:AuthenticationInComponent(this)
,ShadowTree(-1,this)
,Parent(NULL)
,ChangingDataStructure(QReadWriteLock::Recursive)
,TopView(256,256,QImage::Format_RGB32)
,EntryPoint(pEntryPoint)
,OnTerminating(false)
,UndoDataStocker(this)
,RedoDataStocker(this)
,SystemResultContainer(this)
{
	ReadyOK					=false;
	GuiInitializerData		=NULL;
	GUIInstancePackData		=NULL;
	InstShowLoadingDLLForm	=NULL;
	ShadowNumber			=-1;
	CurrentShadowNumber		=-1;
	ReturnCode				=0;
    FastBoot				=false;
    StartThreadWriteMode	=_StartThreadWriteMode;
	#pragma omp parallel                             
	{             
		NumThreads=omp_get_num_threads();
	}
	LibType					=new LibTypeListContainer();
	InstalledLibType		=new LibTypeListContainer();
	ResultHistryData		=new ResultHistryContainer(this);
	ArrangementDLLStock		=new ArrangementDLLBase(this);
	LogCreater				=new LogOutClass("C:/LogFile.txt");
	ResultInspectionPointerStocker	=new ResultInspectionPointerStock();
	
	OnChanging				=false;
	MilisecExecuteFilter	=0;
	InsideLearningEditor	=false;
	QString	CurPath			=QDir::currentPath();
	FRegistry				=new FileRegistry(CurPath+QString("/MachineInfo.dat"));
	int	LanguageCode=GetFRegistry()->LoadRegInt("Language",0);
	LanguagePackageData		=new LanguagePackage();
	LoadLanguageSolution(GetLanguageSolutionFileName());
	LanguagePackageData->SetLanguage(LanguageCode);
	LangLibSolver.SetLanguage(GetLanguagePackageData(),LanguageCode);
	UseDynamicMasking		=false;

	ParamGlobalData			=new ParamGlobal(this);
	ParamCommData			=new ParamComm	(this);
	ParamGUIData			=new ParamGUI	();
	AllocatedBufferInfoCount=0;
	BufferInfoListDim		=NULL;
	RCmdBase				=new NPListPack<ReceiverList>;
	GlobalOffset			=NULL;
	SendingData				=NULL;
	GlobalPageNumb			=0;
	CurrentLevel			=NULL;
	EnableFilter			=true;
	EnableProcess			=true;

	RIntegrationCmdBase		=new NPListPack<ReceiverList>;;
	IntegrationSendingData	=NULL;

	DefaultArrangeMode		=false;
	RootDBase				=NULL;
	OriginalRootDBase		=true;
	CurrentStrategicNumber	=0;
	CurrentStrategicNumberForSeq	=0;
	CurrentStrategicNumberForCalc	=0;
	CurrentStrategicNumberInExe		=0;
	StopCommSender			=false;
	MasterCode				= -1;
	PageData				=NULL;
	PageDataPhase			=NULL;
	DrawPageIndex			=NULL;
	CurrentPhase			=0;
	//AllocatedPageNumb		=0;
	AllocatedPhaseNumb		=0;
	//MachineID				=0;
	RegTime					=XDateTime::currentDateTime();
	WorkerID				= -1;
	Version					=RegulusVersion;
	LoadedVersion			=RegulusVersion;
	LastEditTime			=RegTime;
	StartInspectionTime		=RegTime;
	CategoryID				= -1;
	_CurrentInspectID		=0;
	_LastInspectID			=0;
	InspectionRemark		=0;
	LotInfo					=new LotBase(this);
	ExecuterDim				=NULL;
	AllocExecuterDim		=0;
	CurrentCalcPoint		=0;
	CurrentDrawPoint		=0;
	LastCurrentCalcPoint	=0;
	AlgoDLLContPointer		=new AlgorithmDLLContainer(this);
	LogicDLLBase			=new LogicDLLBaseClass(this);
	ResultDLLBase			=new ResultDLLBaseClass(this);
	SequenceInstance		=NULL;
	InspectionTimeMilisec	=0;
	DBLoader				=NULL;
	MasterType				=0;		//0:MasterData 1:PieceData
	PieceStock				=new PieceStocker(this);
	BootingLevel			=0;
	OnProcessing			=NULL;
	ErrorOccurs				=0;
	AckFlag					=NULL;
	AllocatedAckFlag		=0;
	AckFilterID				=-1;
	DirectCommBase			=NULL;
	ProcessingReEntrant		=0;
	LightBase				=NULL;
	ForceChangedInspectID	=false;
	LanguageCode			=0;
	MTransfer				=NULL;
	MainWidget				=NULL;

	LocalParamStocker		=new ParamDatabase("LocalData.dat");
	AppPointer	=(QApplication *)QCoreApplication::instance();
	ShouldWriteResult		=true;
	FilterBank				=std::make_shared<FilterBankBase>(this);
	OutlineOffsetWriter		=new OutlineOffsetInBlob(this);
	LogoStockerInstance		=std::make_shared<LogoStocker>();
	AnyData					=new AnyDataContainer();
	GeneralStockerData		=new GeneralStockerContainer(this);
	ErrorContainer			=new ErrorCodeListContainer();
	LatchedInspectionNumber	=0;
	InsideReEntrant			=0;
	ResultWrittenID			=0;
	PasswordHolder			=std::make_shared<PasswordManager>(this);
	SyncGUIData				=std::make_shared<SyncGUIPack>(this);
	StatusControllerData	=new StatusController(this);
	LearningRegisterData	=new LearningRegister(this);
	EventPriority			=0;

	RCmdDirectCommBase		=new NPListPack<DirectCommReceiverList>; 
	LearningRegData			=new LearningRegListContainer();
	TmpHidingProcessingForm	=false;
	ListOfQImageStockerData	=new ListOfQImageStocker();

	MachineID				=FRegistry->LoadRegInt("MachineID",0);
	MachineIDFromMaster		=MachineID;
	CurrentScanPhaseNumber	=0;
	DataOfShareMasterContainer		=new ShareMasterContainer(this);
	MainThread						=QThread::currentThreadId();
	PasteListMatrixContainerBase	=new PasteListMatrixContainer();
	OperationLoggerData				=std::make_shared<OperationLogger>(this);
	PrinterClassPackData			=NULL;
	ShrinkingPackContainerInstance	=NULL;
	ModeInspectionPlayer		=false;
	LensWindow					=NULL;
	ZoneWindow					=NULL;
	CurrentZoneWindowComponent	=NULL;
	ResultFromAlgorithm			=0;
	IntegrationBaseData			=NULL;
	ResizeData					=new WidgetGeometry();
	ResultAnalizerDLLPack		=new ResultAnalizerDLLContainer(this);
	ResultAnalizerItemBasePack	=new ResultAnalizerItemBaseContainer(this);	
	ResultThread				=new WriteResultThread(this,StartThreadWriteMode);
	ViewRefreshCounter			=0;
	ThresholdLevelParentID		=0;
	ThresholdLevelID			=0;
	CurrentLibFolderID			=-1;
	AuthenticationInst			=std::make_shared<AuthenticationInside>(this);
	FileThreadListContainerInst	=new FileThreadListContainer(this);
	EditPasswordMode			=false;
	LevelFolderContainerInst	=new LevelFolderContainer(this);
	
	EnableLoopOnIdle	=true;
	PossibleToUpdateDisplay		=true;
}

LayersBase::LayersBase(const LayersBase *_Parent,bool _StartThreadWriteMode)
:AuthenticationInComponent(this)
,ShadowTree(-1,this)
,Parent(_Parent)
,ChangingDataStructure(QReadWriteLock::Recursive)
,TopView(256,256,QImage::Format_RGB32)
,EntryPoint(((LayersBase *)_Parent)->GetEntryPoint())
,OnTerminating(false)
,UndoDataStocker(this)
,RedoDataStocker(this)
,SystemResultContainer(this)
{
	ReadyOK					=false;
	GuiInitializerData		=NULL;
	GUIInstancePackData		=NULL;
	InstShowLoadingDLLForm	=NULL;
	ShadowNumber			=-1;
	CurrentShadowNumber		=-1;
	ReturnCode				=0;
    FastBoot				=false;
    StartThreadWriteMode	=_StartThreadWriteMode;
	#pragma omp parallel                             
	{             
		NumThreads=omp_get_num_threads();
	}
	LibType					=new LibTypeListContainer();
	InstalledLibType		=new LibTypeListContainer();
	ResultHistryData		=new ResultHistryContainer(this);
	ArrangementDLLStock		=new ArrangementDLLBase(this);
	LogCreater				=new LogOutClass("C:/LogFile.txt");
	ResultInspectionPointerStocker	=new ResultInspectionPointerStock();
	
	OnChanging				=false;
	MilisecExecuteFilter	=0;
	InsideLearningEditor	=false;
	QString	CurPath			=QDir::currentPath();
	FRegistry				=new FileRegistry(CurPath+QString("/MachineInfo.dat"));
	int	LanguageCode=GetFRegistry()->LoadRegInt("Language",0);
	LanguagePackageData		=((LayersBase *)Parent)->GetLanguagePackageDataPointer();
	//LoadLanguageSolution(GetLanguageSolutionFileName());
	LanguagePackageData->SetLanguage(LanguageCode);
	LangLibSolver.SetLanguage(GetLanguagePackageData(),LanguageCode);
	UseDynamicMasking		=false;

	ParamGlobalData			=new ParamGlobal(this);
	ParamCommData			=new ParamComm	(this);
	ParamGUIData			=new ParamGUI	();
	AllocatedBufferInfoCount=0;
	BufferInfoListDim		=NULL;
	RCmdBase				=new NPListPack<ReceiverList>;
	GlobalOffset			=NULL;
	SendingData				=NULL;
	GlobalPageNumb			=0;
	CurrentLevel			=NULL;
	EnableFilter			=true;
	EnableProcess			=true;

	RIntegrationCmdBase		=new NPListPack<ReceiverList>;;
	IntegrationSendingData	=NULL;

	DefaultArrangeMode		=false;
	RootDBase				=NULL;
	CurrentStrategicNumber	=0;
	CurrentStrategicNumberForSeq	=0;
	CurrentStrategicNumberForCalc	=0;
	CurrentStrategicNumberInExe		=0;
	StopCommSender			=false;
	MasterCode				= -1;
	PageData				=NULL;
	PageDataPhase			=NULL;
	DrawPageIndex			=NULL;
	CurrentPhase			=0;
	//AllocatedPageNumb		=0;
	AllocatedPhaseNumb		=0;
	//MachineID				=0;
	RegTime					=XDateTime::currentDateTime();
	WorkerID				= -1;
	Version					=RegulusVersion;
	LoadedVersion			=RegulusVersion;
	LastEditTime			=RegTime;
	StartInspectionTime		=RegTime;
	CategoryID				= -1;
	_CurrentInspectID		=0;
	_LastInspectID			=0;
	InspectionRemark		=0;
	LotInfo					=new LotBase(this);
	ExecuterDim				=NULL;
	AllocExecuterDim		=0;
	CurrentCalcPoint		=0;
	CurrentDrawPoint		=0;
	LastCurrentCalcPoint	=0;
	AlgoDLLContPointer		=new AlgorithmDLLContainer(this);
	LogicDLLBase			=new LogicDLLBaseClass(this);
	ResultDLLBase			=new ResultDLLBaseClass(this);
	SequenceInstance		=NULL;
	InspectionTimeMilisec	=0;
	DBLoader				=NULL;
	MasterType				=0;		//0:MasterData 1:PieceData
	PieceStock				=new PieceStocker(this);
	BootingLevel			=0;
	OnProcessing			=NULL;
	ErrorOccurs				=0;
	AckFlag					=NULL;
	AllocatedAckFlag		=0;
	AckFilterID				=-1;
	DirectCommBase			=NULL;
	ProcessingReEntrant		=0;
	LightBase				=NULL;
	ForceChangedInspectID	=false;
	LanguageCode			=0;
	MTransfer				=NULL;
	MainWidget				=NULL;
	LocalParamStocker		=new ParamDatabase("LocalData.dat");
	AppPointer	=(QApplication *)QCoreApplication::instance();
	ShouldWriteResult		=true;
	FilterBank				=std::make_shared<FilterBankBase>(this);
	OutlineOffsetWriter		=new OutlineOffsetInBlob(this);
	LogoStockerInstance		=std::make_shared<LogoStocker>();
	AnyData					=new AnyDataContainer();
	GeneralStockerData		=new GeneralStockerContainer(this);
	ErrorContainer			=new ErrorCodeListContainer();
	LatchedInspectionNumber	=0;
	InsideReEntrant			=0;
	ResultWrittenID			=0;
	PasswordHolder			=std::make_shared<PasswordManager>(this);
	SyncGUIData				=std::make_shared<SyncGUIPack>(this);
	StatusControllerData	=new StatusController(this);
	LearningRegisterData	=new LearningRegister(this);
	EventPriority			=0;

	RCmdDirectCommBase		=new NPListPack<DirectCommReceiverList>; 
	LearningRegData			=new LearningRegListContainer();
	TmpHidingProcessingForm	=false;
	ListOfQImageStockerData	=new ListOfQImageStocker();

	MachineID				=FRegistry->LoadRegInt("MachineID",0);
	MachineIDFromMaster		=MachineID;
	CurrentScanPhaseNumber	=0;
	DataOfShareMasterContainer		=new ShareMasterContainer(this);
	MainThread						=QThread::currentThreadId();
	PasteListMatrixContainerBase	=new PasteListMatrixContainer();
	OperationLoggerData				=std::make_shared<OperationLogger>(this);
	PrinterClassPackData			=NULL;
	ShrinkingPackContainerInstance	=NULL;
	ModeInspectionPlayer		=false;
	LensWindow					=NULL;
	ZoneWindow					=NULL;
	CurrentZoneWindowComponent	=NULL;
	ResultFromAlgorithm			=0;
	IntegrationBaseData			=NULL;
	ResizeData					=new WidgetGeometry();
	ResultAnalizerDLLPack		=new ResultAnalizerDLLContainer(this);
	ResultAnalizerItemBasePack	=new ResultAnalizerItemBaseContainer(this);	
	ResultThread				=new WriteResultThread(this,StartThreadWriteMode);
	ViewRefreshCounter			=0;
	ThresholdLevelParentID		=0;
	ThresholdLevelID			=0;
	CurrentLibFolderID			=-1;
	AuthenticationInst			=std::make_shared<AuthenticationInside>(this);
	FileThreadListContainerInst	=new FileThreadListContainer(this);
	EditPasswordMode			=false;
	LevelFolderContainerInst	=new LevelFolderContainer(this);
	
	EnableLoopOnIdle	=true;
	PossibleToUpdateDisplay		=true;
}

EntryPointForGlobal::~EntryPointForGlobal(void)
{
	if(DirectCommBase!=NULL){
		delete	DirectCommBase;
		DirectCommBase=NULL;
	}
}

void	EntryPointForGlobal::WaitReadyReadAll(int milisec)
{
	if(GetLayersBase()!=NULL && GetLayersBase()->GetGuiInitializer()!=NULL){
		GetLayersBase()->GetGuiInitializer()->WaitReadyReadAll(milisec);
	}
}


void	EntryPointForGlobal::SetLanguageCode(int LanguageCode)
{
	if(GetLayersBase()->GetGuiInitializer()!=NULL){
		for(GUIInstancePack *c=GetLayersBase()->GetGuiInitializer()->GUIInstanceRoot.GetFirst();c!=NULL;c=c->GetNext()){
			for(GUIItemInstance *d=c->NPListPack<GUIItemInstance>::GetFirst();d!=NULL;d=d->GetNext()){
				if(d->DLLAccess!=NULL){
					d->DLLAccess->SetLanguageCode(LanguageCode);
				}
			}
		}
	}
}

GUIFormBase	*EntryPointForGlobal::ShowOtherGUI(GUIFormBase *ChainedParent
											,const QString &GUIFileName 
											,LayersBase *LayersBasePointer ,bool EditMode)
{
	GUIInstancePack	*NowPack=new GUIInstancePack(LayersBasePointer,GetLayersBase()->GetGuiInitializer());
	GetLayersBase()->GetGuiInitializer()->GUIInstanceRoot.AppendList(NowPack);
	QFile	file(GUIFileName);
	GUIFormBase	*f=NULL;
	if(file.open(QIODevice::ReadOnly)==true){
		QString ErrorMsg;
		if(NowPack->LoadInstances(&file ,ErrorMsg)==true){
			f=NowPack->CreateMainForm(LayersBasePointer ,GUIInstancePack::_Center);
			LayersBasePointer->SetGUIInstancePack(NowPack);
			LayersBasePointer->SetMainForm(NowPack->GetFirstForm());

			NowPack->ShowAll(f,LayersBasePointer ,LayersBasePointer->GetParamGUI(),EditMode);
			f->SetChainedParent(ChainedParent);
			f->Set(GetLayersBase()->GetGuiInitializer(),NowPack);
			((MainGUIFormBase *)f)->CloseCompletely=true;

			QIODevice	*Dev=ChainedParent->GetChainedDevice();
			f->LoadAll(Dev);
			delete	Dev;
		}
	}
	return f;
}

int		EntryPointForGlobal::GetDirectCommIDFromGlobalPage(int globalPageTo)
{
	return GetLayersBase()->GetDirectCommBase()->GetCommIDFromGlobalPage(globalPageTo);
}
