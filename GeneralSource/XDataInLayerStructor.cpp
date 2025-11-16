/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataInLayerStructor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------
#include "XTypeDef.h"
#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <QReadWriteLock>
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
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "SelectPasteForm.h"
#include "XTransferInterface.h"
#include "XTransfer.h"
#include "XCriticalFunc.h"
#include "XDatabaseLoader.h"
#include "XPieceArchitect.h"
#include "OnProcessingForm.h"
#include "XCrossObj.h"
#include "XDirectComm.h"
#include "XLightInterfaceDLL.h"
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
#include "XDisplayImagePacket.h"
#include "XServiceForLayers.h"
#include "XGUI.h"
#include "XSyncGUI.h"
#include "XStatusController.h"
#include "XLearningRegist.h"
#include "XImageProcess.h"
#include "ShowLoadingDLLForm.h"
#include "XLotInformation.h"
#include "XHistgramByParam.h"
#include "XDateTime.h"
#include "AlertDialog.h"
#include "XShareMasterData.h"
#include "XCSV.h"
#include "XPrinterManager.h"
#include "XPointer.h"
#include "XImageExpand.h"
#include "LensWindowForm.h"
#include "XIntegrationComm.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"
#include "XResize.h"
#include "XResultAnalizer.h"
#include "XDirectCommPacket.h"
#include "XDataInLayerToDisplayImage.h"
#include "ThreadSequence.h"
#include "XDataInLayerCmdLocal.h"
#include "XFilterInstance.h"
#include "XCameraClass.h"
#include "XAuthenticationInside.h"
#include "XResult.h"
#include "XWriteResultThread.h"
#include "XLibraryType.h"
#include "XArrangementFromFile.h"
#include "XLogOut.h"
#include "XParamDatabase.h"
#include "XImageStocker.h"
#include "XLanguageStockerLoader.h"
#include "XShadowTree.h"
#include "XFileThread.h"
#include "XLevel.h"
#include "XEntryPoint.h"

LayersBase::LayersBase(const QString& _TypeName, LayersBase* ParentLayer)
	:AuthenticationInComponent(this)
	,ShadowTree(-1,ParentLayer)
	, TypeName(_TypeName)
	, OnTerminating(false)
	, EntryPoint(ParentLayer->GetEntryPoint())
	, TopView(256, 256, QImage::Format_RGB32)
	, UndoDataStocker(this), RedoDataStocker(this)
	, ChangingDataStructure(QReadWriteLock::Recursive)
	, SystemResultContainer(this)
{
	ReadyOK					=false;
	Parent 					= NULL;
	GuiInitializerData 		= NULL;
	GUIInstancePackData 	= NULL;
	InstShowLoadingDLLForm 	= NULL;
	ShadowNumber			=-1;
	CurrentShadowNumber		=-1;
	ReturnCode				=0;
    FastBoot				=false;
    StartThreadWriteMode	=false;
	#pragma omp parallel                             
	{             
		NumThreads=omp_get_num_threads();
	}
	LibType 			= new LibTypeListContainer();
	InstalledLibType	= new LibTypeListContainer();
	ResultHistryData	= new ResultHistryContainer(this);
	ArrangementDLLStock = new ArrangementDLLBase(this);
	LogCreater 			= new LogOutClass("");
	ResultInspectionPointerStocker = new ResultInspectionPointerStock();

	OnChanging 			= false;
	MilisecExecuteFilter= 0;
	InsideLearningEditor= false;
	ResultThread 		= NULL;
	FRegistry 			= new FileRegistry(ParentLayer->GetFRegistry()->GetFileName());
	int	LanguageCode 	= GetFRegistry()->LoadRegInt("Language", 0);
	LanguagePackageData = new LanguagePackage();
	LoadLanguageSolution(ParentLayer->GetLocalLanguageSolutionFileName());
	LanguagePackageData->SetLanguage(LanguageCode);
	ParamGlobalData 	= new ParamGlobal(this);
	ParamCommData 		= new ParamComm(this);
	ParamCommData->Mastered = true;
	UseDynamicMasking 	= false;

	ParamGUIData 			= NULL;
	RCmdBase 				= NULL;
	GlobalOffset 			= NULL;
	AllocatedBufferInfoCount=0;
	BufferInfoListDim		=NULL;
	SendingData 			= NULL;
	GlobalPageNumb 			= 0;
	CurrentLevel			=NULL;
	EnableFilter			=true;
	EnableProcess			=true;

	RIntegrationCmdBase = NULL;
	IntegrationSendingData = NULL;

	DefaultArrangeMode = false;
	RootDBase = NULL;
	OriginalRootDBase = true;
	CurrentStrategicNumber = 0;
	CurrentStrategicNumberForSeq = 0;
	CurrentStrategicNumberForCalc = 0;
	StopCommSender = false;
	MasterCode = -1;
	PageData = NULL;
	PageDataPhase = NULL;
	DrawPageIndex = NULL;
	CurrentPhase = 0;
	//AllocatedPageNumb		=0;
	AllocatedPhaseNumb = 0;
	//MachineID				=0;
	RegTime = XDateTime::currentDateTime();
	WorkerID = -1;
	Version = RegulusVersion;
	LoadedVersion = RegulusVersion;
	LastEditTime = RegTime;
	StartInspectionTime = RegTime;
	CategoryID = -1;
	_CurrentInspectID = 0;
	_LastInspectID = 0;
	InspectionRemark = 0;
	LotInfo = NULL;
	ExecuterDim = NULL;
	AllocExecuterDim = 0;
	CurrentCalcPoint = 0;
	CurrentDrawPoint = 0;
	LastCurrentCalcPoint = 0;
	AlgoDLLContPointer = new AlgorithmDLLContainer(this);
	LogicDLLBase = new LogicDLLBaseClass(this);;
	ResultDLLBase = new ResultDLLBaseClass(this);
	SequenceInstance = NULL;
	InspectionTimeMilisec = 0;
	DBLoader = NULL;
	MasterType = 0;		//0:MasterData 1:PieceData
	PieceStock = NULL;
	BootingLevel = 0;
	OnProcessing = NULL;
	ErrorOccurs = 0;
	AckFlag = NULL;
	AllocatedAckFlag = 0;
	DirectCommBase = NULL;
	ProcessingReEntrant = 0;
	LightBase = NULL;
	ForceChangedInspectID = false;
	EventPriority = 0;

	MTransfer					=NULL;
	MainWidget					=NULL;
	LocalParamStocker			=NULL;
	AppPointer					=(QApplication*)QCoreApplication::instance();
	ShouldWriteResult			=true;
	FilterBank					=NULL;
	OutlineOffsetWriter			=NULL;
	LogoStockerInstance			=NULL;
	AnyData						=NULL;
	GeneralStockerData			=NULL;
	ErrorContainer				=NULL;
	LatchedInspectionNumber		=0;
	InsideReEntrant				=0;
	ResultWrittenID				=0;
	PasswordHolder				=NULL;
	SyncGUIData					=NULL;
	StatusControllerData		=NULL;
	LearningRegisterData		=NULL;

	RCmdDirectCommBase			=NULL;
	LearningRegData				=NULL;
	TmpHidingProcessingForm		=false;
	ListOfQImageStockerData		=NULL;

	MachineID					=-1;
	MachineIDFromMaster			=MachineID;
	CurrentScanPhaseNumber		=0;
	CurrentLibFolderID			=-1;
	DataOfShareMasterContainer	=NULL;
	MainThread					=QThread::currentThreadId();
	PasteListMatrixContainerBase=NULL;
	OperationLoggerData			=NULL;
	PrinterClassPackData		=NULL;
	ShrinkingPackContainerInstance=NULL;
	LensWindow					=NULL;
	ZoneWindow					=NULL;
	CurrentZoneWindowComponent	=NULL;
	ResultFromAlgorithm			=0;
	IntegrationBaseData			=NULL;
	ResizeData 					=NULL;
	ResultAnalizerDLLPack		=NULL;
	ResultAnalizerItemBasePack 	=NULL;
	ViewRefreshCounter			=0;
	ThresholdLevelParentID		=0;
	ThresholdLevelID			=0;
	AuthenticationInst			=NULL;
	FileThreadListContainerInst	=new FileThreadListContainer(this);
	EditPasswordMode			=false;
	LevelFolderContainerInst	=new LevelFolderContainer(this);
	
	EnableLoopOnIdle	=true;
	PossibleToUpdateDisplay		=true;
}
LayersBase::~LayersBase(void)
{
	//	if(_CrtCheckMemory()==false)
	//		ErrorOccurs++;

	OnTerminating = true;

	ReleaseAll();

	MainThread = NULL;
	AppPointer = NULL;
	GuiInitializerData = NULL;
	GUIInstancePackData = NULL;
	
	if(FileThreadListContainerInst!=NULL){
		FileThreadListContainerInst->SetTerminate(true);
		FileThreadListContainerInst->wait(20000);
		delete	FileThreadListContainerInst;
		FileThreadListContainerInst=NULL;
	}
}

void    LayersBase::Release(void)
{
	if (LogicDLLBase != NULL) {
		delete	LogicDLLBase;
		LogicDLLBase = NULL;
	}
	if (ResultDLLBase != NULL) {
		delete	ResultDLLBase;
		ResultDLLBase = NULL;
	}

	if (PageDataPhase != NULL) {
		for (int i = 0; i < AllocatedPhaseNumb; i++) {
			PageDataPhase[i]->Release();
		}
		delete[]PageDataPhase;
		PageDataPhase = NULL;
	}
	PageData = NULL;

	if (DrawPageIndex != NULL) {
		delete[]DrawPageIndex;
		DrawPageIndex = NULL;
	}
}
void    LayersBase::ReleaseLogger(void)
{
	if(ShadowNumber<0){
		if (OperationLoggerData){
			OperationLoggerData->Uninstall();
			OperationLoggerData.reset();
		}
	}
}
void    LayersBase::ReleaseBeforeReleasingGUI(void)
{
	static	bool	ModeCheckHeap = false;

	if (MainWidget != NULL) {
		disconnect(MainWidget, SLOT(SlotCommand(int)));
		disconnect(MainWidget, SLOT(SlotWroteSlave(XDateTime)));
		disconnect(MainWidget, SLOT(SlotChangeLotInfo(int)));
	}
	for (int phase = 0; phase < AllocatedPhaseNumb; phase++) {
		for (int page = 0; page < GetPageNumb(); page++) {
			GetPageDataPhase(phase)->GetPageData(page)->ReleaseInside();
		}
	}
	if (LensWindow != NULL) {
		delete	LensWindow;
		LensWindow = NULL;
	}

	if (ParamGUIData != NULL) {
		delete	ParamGUIData;
		ParamGUIData = NULL;
	}
	if(ShadowNumber<0){
		if (OperationLoggerData) {
			OperationLoggerData.reset();
		}
	}

	//delete	PacketWritternResult;
	PacketWritternResult = NULL;

	if (RCmdBase != NULL) {
		ReceiverList* r;
		while ((r = RCmdBase->GetFirst()) != NULL) {
			if (r->Point != NULL) {
				GUICmdPacketBase* Point = r->Point;
				if (RemovePacket(Point) == false) {
					RCmdBase->RemoveList(r);
					if (Point->GetGlobalPage() >= 0) {
						delete	Point;
					}
					delete	r;
				}
				else {
					if (Point->GlobalPage >= 0) {
						delete	Point;
					}
				}
			}
		}
		delete	RCmdBase;
		RCmdBase = NULL;
	}
	if (RCmdDirectCommBase != NULL) {
		DirectCommReceiverList* r;
		while ((r = RCmdDirectCommBase->GetFirst()) != NULL) {
			DirectCommPacketBase* Point = r->Point;
			if (r->Point != NULL) {
				if (RemoveDirectCommPacket(Point) == false) {
					RCmdDirectCommBase->RemoveList(r);
					if (Point->GetGlobalPageFrom() >= 0) {
						delete	Point;
					}
					delete	r;
				}
				else {
					if (Point->GetGlobalPageFrom() >= 0) {
						delete	Point;
					}
				}
			}
		}
		delete	RCmdDirectCommBase;
		RCmdDirectCommBase = NULL;
	}
	if (RIntegrationCmdBase != NULL) {
		ReceiverList* r;
		if (ModeCheckHeap == true){
			#ifdef _MSC_VER
			_heapchk();
			#endif
		}

		while ((r = RIntegrationCmdBase->GetFirst()) != NULL) {
			if (r->IntegrationPoint != NULL) {
				IntegrationCmdPacketBase* Point = r->IntegrationPoint;
				if (RemoveIntegrationPacket(Point) == false) {
					RIntegrationCmdBase->RemoveList(r);
					if (Point->GetSlaveNo() >= 0) {
						delete	Point;
					}
					delete	r;
				}
				else {
					if (Point->GetSlaveNo() >= 0) {
						delete	Point;
					}
				}
			}
		}
		delete	RIntegrationCmdBase;
		RIntegrationCmdBase = NULL;
	}
	if(ShadowNumber<0){
		if (ListOfQImageStockerData != NULL) {
			delete	ListOfQImageStockerData;
		}
	}
	ListOfQImageStockerData = NULL;

	GUICmdContainer.RemoveAll();
	DirectCmdContainer.RemoveAll();
	IntegrationCmdContainer.RemoveAll();
}
void    LayersBase::ReleaseAll(void)
{
	static	bool	ModeCheckHeap = false;

	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}
	UndoDataStocker.RemoveAll();
	RedoDataStocker.RemoveAll();
	CreateAlgorithmPointer();

	if(ShadowNumber<0){
		if (LibType != NULL) {
			delete	LibType;
		}
	}
	LibType = NULL;

	if (ResultHistryData != NULL) {
		delete	ResultHistryData;
		ResultHistryData = NULL;
	}
	if (ArrangementDLLStock != NULL) {
		delete	ArrangementDLLStock;
		ArrangementDLLStock = NULL;
	}
	if(ShadowNumber<0){
		if (LogCreater != NULL) {
			delete	LogCreater;
		}
	}
	LogCreater = NULL;

	if (ResultInspectionPointerStocker != NULL) {
		delete	ResultInspectionPointerStocker;
		ResultInspectionPointerStocker = NULL;
	}

	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if (ResultThread != NULL) {
		//ResultThread.terminate();
		ResultThread->SetCmdFinish(true);
		ResultThread->wait(5000);
		//if(ResultDLLBase!=NULL)
		//	ResultDLLBase->Release();
		delete	ResultThread;
		ResultThread = NULL;
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if (MainWidget != NULL) {
		MainWidget->deleteLater();
		MainWidget = NULL;
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}


	GUICmdContainer.RemoveAll();

	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if (PageDataPhase != NULL) {
		for (int i = 0; i < AllocatedPhaseNumb; i++) {
			PageDataPhase[i]->Release();
		}
		delete[]PageDataPhase;
		PageDataPhase = NULL;
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	PageData = NULL;

	if (Parent == NULL) {
		if (ShrinkingPackContainerInstance) {
			ShrinkingPackContainerInstance.reset();
		}
	}

	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if (DrawPageIndex != NULL) {
		delete[]DrawPageIndex;
		DrawPageIndex = NULL;
	}

	if (MTransfer != NULL) {
		delete	MTransfer;
		MTransfer = NULL;
	}

	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if(ShadowNumber<0){
		if (ErrorContainer != NULL) {
			delete	ErrorContainer;
		}
	}
	ErrorContainer = NULL;

	//AllocatedPageNumb=0;
	if (LogicDLLBase != NULL) {
		delete	LogicDLLBase;
		LogicDLLBase = NULL;
	}

	if (ResultDLLBase != NULL) {
		delete	ResultDLLBase;
		ResultDLLBase = NULL;
	}

	if (PieceStock != NULL) {
		delete	PieceStock;
		PieceStock = NULL;
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	//CloseDatabase();
	if (DBLoader) {
		DatabaseRelease();
		DBLoader.reset();
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if (ExecuterDim != NULL) {
		for (int i = 0; i < AllocExecuterDim; i++) {
			delete	ExecuterDim[i];
		}
		delete[]ExecuterDim;
		ExecuterDim = NULL;
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if (ParamGlobalData != NULL) {
		delete	ParamGlobalData;
		ParamGlobalData = NULL;
	}
	if (ParamCommData != NULL) {
		delete	ParamCommData;
		ParamCommData = NULL;
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if (AckFlag != NULL) {
		delete[]AckFlag;
		AckFlag = NULL;
	}
	if (LightBase != NULL) {
		delete	LightBase;
		LightBase = NULL;
	}
	if(ShadowNumber<0){
		if (LocalParamStocker != NULL) {
			delete	LocalParamStocker;
		}
	}
	LocalParamStocker = NULL;

	if (OnProcessing != NULL) {
		delete	OnProcessing;
		OnProcessing = NULL;
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if(ShadowNumber<0){
		FilterBank.reset();
	}

	if(ShadowNumber<0){
		if (OutlineOffsetWriter != NULL) {
			delete	OutlineOffsetWriter;
		}
	}
	OutlineOffsetWriter = NULL;

	if(ShadowNumber<0){
		if (LogoStockerInstance) {
			LogoStockerInstance.reset();
		}
	}

	if(ShadowNumber<0){
		if (AnyData != NULL) {
			delete	AnyData;
		}
	}
	AnyData = NULL;

	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if(ShadowNumber<0){
		if (GeneralStockerData != NULL) {
			delete	GeneralStockerData;
		}
	}
	GeneralStockerData = NULL;

	if (LearningRegData != NULL) {
		delete	LearningRegData;
		LearningRegData = NULL;
	}
	if (GlobalOffset != NULL) {
		delete[]GlobalOffset;
		GlobalOffset = NULL;
	}
	if (SendingData != NULL) {
		delete[]SendingData;
		SendingData = NULL;
	}
	if (IntegrationSendingData != NULL) {
		delete[]IntegrationSendingData;
		IntegrationSendingData = NULL;
	}
	if(ShadowNumber<0){
		if (PasswordHolder) {
			PasswordHolder.reset();
		}
	}

	if(ShadowNumber<0){
		if (SyncGUIData) {
			SyncGUIData.reset();
		}
	}

	if(ShadowNumber<0){
		if (StatusControllerData != NULL) {
			delete	StatusControllerData;
		}
	}
	StatusControllerData = NULL;

	if(ShadowNumber<0){
		if (AlgoDLLContPointer != NULL) {
			delete	AlgoDLLContPointer;
		}
	}
	AlgoDLLContPointer = NULL;

	if (LearningRegisterData != NULL) {
		delete	LearningRegisterData;
		LearningRegisterData = NULL;
	}
	if (LotInfo != NULL) {
		delete	LotInfo;
		LotInfo = NULL;
	}
	if (InstShowLoadingDLLForm != NULL) {
		delete	InstShowLoadingDLLForm;
		InstShowLoadingDLLForm = NULL;
	}
	if (Parent == NULL) {
		if (LanguagePackageData != NULL) {
			delete	LanguagePackageData;
			LanguagePackageData = NULL;
		}
	}
	else {
		LanguagePackageData = NULL;
	}

	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	if(ShadowNumber<0){
		if (DataOfShareMasterContainer != NULL) {
			delete	DataOfShareMasterContainer;
		}
	}
	DataOfShareMasterContainer = NULL;

	//delete	RootDBase;
	if(ShadowNumber<0){
		if (PasteListMatrixContainerBase != NULL) {
			delete	PasteListMatrixContainerBase;
		}
	}
	PasteListMatrixContainerBase = NULL;

	if (PrinterClassPackData != NULL) {
		delete	PrinterClassPackData;
		PrinterClassPackData = NULL;
	}
	if(ShadowNumber<0){
		if (FRegistry != NULL) {
			delete	FRegistry;
		}
	}
	FRegistry = NULL;

	/*
	DirectCommBase is allocated in XGUIExe.cpp as global param, and released in global
	if(DirectCommBase!=NULL){
		delete	DirectCommBase;
		DirectCommBase=NULL;
	}
	*/
	if (IntegrationBaseData != NULL) {
		delete	IntegrationBaseData;
		IntegrationBaseData = NULL;
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}
	if(BufferInfoListDim!=NULL){
		delete	[]BufferInfoListDim;
		BufferInfoListDim=NULL;
	}

	CurrentLevel=NULL;

	if (ZoneWindow != NULL) {
		delete	ZoneWindow;
		ZoneWindow = NULL;
	}
	if (ResizeData != NULL) {
		delete	ResizeData;
		ResizeData = NULL;
	}
	if(ShadowNumber<0){
		if (ResultAnalizerDLLPack != NULL) {
			delete	ResultAnalizerDLLPack;
		}
	}
	ResultAnalizerDLLPack = NULL;

	if (ResultAnalizerItemBasePack != NULL) {
		delete	ResultAnalizerItemBasePack;
		ResultAnalizerItemBasePack = NULL;
	}
	if (ModeCheckHeap == true){
		#ifdef _MSC_VER
		_heapchk();
		#endif
	}

	ReleaseBook();
	CurrentZoneWindowComponent = NULL;
}