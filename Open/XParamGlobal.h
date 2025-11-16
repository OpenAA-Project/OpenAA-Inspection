/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XParamGlobal.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPARAMGLOBAL_H)
#define	XPARAMGLOBAL_H

#include "XParamBase.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "NListComp.h"
#include "XTypeDef.h"

class	ParamComm;

const	int		GUICommPort=10300;


class	CameraAllocationSlave
{
public:
	int	SlavePC;	

	CameraAllocationSlave(void){	SlavePC=0;	}
	CameraAllocationSlave(const CameraAllocationSlave &src){	SlavePC=src.SlavePC;	}
};

class	StrategicList : public NPList<StrategicList>
{
public:
	int32	Page;
	int32	Layer;

	StrategicList(void){	Page=Layer=0;	}
	StrategicList(const StrategicList &src)
	{
		Page	=src.Page;
		Layer	=src.Layer;
	}

	StrategicList	&operator=(const StrategicList &src)
	{
		Page	=src.Page;
		Layer	=src.Layer;
		return *this;
	}
};

class	StrategicListContainer : public NPListPack<StrategicList>
{
public:
	StrategicListContainer(void){}

	StrategicListContainer	&operator=(const StrategicListContainer &src);
};

class	PageDirection
{
public:
	bool	ReverseX;
	bool	ReverseY;
	int32	YDelay;

	PageDirection(void);

	PageDirection	&operator=(const PageDirection &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class RemoteTransferList
{
public:
	QString		Name;
	QString		IPAddress;
	int			Port;

	RemoteTransferList()	{	Port =-1;	}
	~RemoteTransferList()	{}

	RemoteTransferList	&operator=(const RemoteTransferList &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class ShadowParameter : public NPListSaveLoad<ShadowParameter>
{
public:
	QString	ShadowGlobalFileName;
	QString	ShadowGUIFileName;
	QString	ShadowParamFileName;
	QString	ShadowControlDLLFileName;

	ShadowParameter(void){}
	~ShadowParameter(void){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	bool	operator==(const ShadowParameter &src)	const;
	bool	operator!=(const ShadowParameter &src)	const;
	ShadowParameter &operator=(const ShadowParameter &src);
};

class ShadowParameterContainer : public NPListPackSaveLoad<ShadowParameter>
{
public:
	ShadowParameterContainer(void){}

	virtual	ShadowParameter	*Create(void)	override;
	bool	operator==(const ShadowParameterContainer &src)	const;
	bool	operator!=(const ShadowParameterContainer &src)	const;
};

#define	MaxRemoteTransferListDimNumb	1000

class	ParamGlobalEachPage : public ParamBase
{
public:
	bool	UseEachPage;
	int32	DotPerLine;
	int32	MaxLines;
	int32	LayerNumb;
	int32	MaximumDotPerLine;
	int32	MaximumMaxLines  ;
	int32	NGCacheNumb;
	int32	ResolutionXNano;
	int32	ResolutionYNano;

	ParamGlobalEachPage(void);

	virtual	QString	GetDataText(void)			override{	return(/**/"");	};
	virtual	QString	GetDefaultFileName(void)	override{	return(/**/"");	}

};

class	ParamGlobal : public ParamBase ,public ServiceForLayers
{
public:
	ParamGlobalEachPage	*PageLocalData;
	int32				CountOfPageLocal;
	int32				AllocatedCounfOfPageLocal;

	int32	DotPerLine;
	int32	MaxLines;
	int32	LayerNumb;
	int32	PageNumb;
	int32	PhaseNumb;
	int32	TotalCameraNumb;
	int32	MaxInspectMilisec;
	int32	MaximumDotPerLine;
	int32	MaximumMaxLines  ;
	int32	NGCacheNumb;
	QString	IODLL_FileName;
	QString	IOSomething;
	int32	ResolutionXNano;
	int32	ResolutionYNano;
	double	RotatedAngleRadian;			//Hiddden parameter in EditParameter  Radian
	QString	CameraDLL_FileName;
	QString	CameraSetting_FileName;
	QString	CameraAllocation;
	QString	CameraParameter;
	QString	CameraDLL_FileName2;
	QString	CameraSetting_FileName2;
	QString	CameraAllocation2;
	QString	CameraParameter2;
	QString	CameraDLL_FileName3;
	QString	CameraSetting_FileName3;
	QString	CameraAllocation3;
	QString	CameraParameter3;
	QString	CameraDLL_FileName4;
	QString	CameraSetting_FileName4;
	QString	CameraAllocation4;
	QString	CameraParameter4;
	QString	Sequence_FileName;
	QString	IODefine_FileName;
	QString	LocalDatabase_FileName;
	int32	LocalDatabase_Port;
	QString	DatabaseDDL_FileName;
	QString	LocalDatabase_HostName;
	QString	LayerDefaultFileName;
	QString	ShadowTreeDefFileName;
	int32	CameraResolutionBit;
	//QString	ResultDLLPathName;
	QString	ResultDLLFileName;
	bool	ImageLeftsideRight;
	int32	TransterPortNumber;
	int32	TransterPortCount;
	int32	TransterWaitingMilisec;
	int32	MaxNGCountsPerCam;
	int32	MaxNGImageForHaltPerCam;
	QString	ImageFilePath;
	int		ImageFileCachePort;
	QString	ArrangementDLLPath;
	int32	MaxHistoryCounts;
	QString	NetworkDrive1;
	QString	NetworkDrive2;
	QString	NetworkDrive3;
	QString	NetworkDrive4;
	QString	NetworkDrivePath1;
	QString	NetworkDrivePath2;
	QString	NetworkDrivePath3;
	QString	NetworkDrivePath4;
	bool	CaptureInBackground;
	QString	LightDLLFileName;
	QString	LightSettingFileName;
	QString	LightParamStr;
	QString	LightDLLFileName2;
	QString	LightParamStr2;
	QString	LightDLLFileName3;
	QString	LightParamStr3;
	QString	LightDLLFileName4;
	QString	LightParamStr4;
	bool	ChangeThresholdFromPartsOrigin;
	bool	AllocateMasterBuff;
	int32	AllocatedCountMasterBuff;
	bool	AllocateBackGroundBuff;
	int32	AllocatedCountBackGroundBuff;
	bool	AllocateTargetBuff;
	bool	AllocateTargetTRBuff;
	bool	AllocateGrayBuff;
	bool	AllocRawTargetBuffForNGImage;
	bool	AllocViewTargetBuffer;
	bool	AllocBitBuffer;
	bool	AllocTrialTargetBuffer;
	int32	DefaultImageArrange;
	int32	TopOfID;
	QString	AlgorithmDefFile;
	int32	DataVersion;
	int32	NGMarkRadius;
	int32	MaxNGImageNumbPerPage;
	QString	LogoListFileName;
	int32	MaxWaitingCommMilisec;
	bool	BufferedProcessing;
	bool	CalcSingleThread;
	bool	KeepFilteredImage;
	QString	GeneralStockerFileName1;
	QString	GeneralStockerFileName2;
	QString	GeneralStockerFileName3;
	QString	GeneralStockerFileName4;
	bool	DrawResultDetail;
	int32	DrawResultDetailLevel;
	int		DebugLevel;	//0:NoDebug
	QString	ErrorLogFile;
	bool	OutputLogMode;
	bool	ReDrawByInspection;
	QString	GUIExcludedListFile;
	QString	GeneralStockerFileName;
	double	AdoptRateLForAvr;
	double	AdoptRateHForAvr;
	QString	SyncGUIFileName;
	int		SyncGUIPort;
	QString	FilterDLLPath;
	QString	FilterDefFile;
	QString	CommentFileName;
	int		MinLearningSize;
	int		MaxLearningSize;
	bool	MakeHistgramData;
	int		WaitMilisecAfterScan;
	int32	ShrinkDotUncoveredArea;
	bool	ViewProcessingWindow;
	bool	AdoptRawForResultImage;
	bool	OutputNGCause;
	int32	MaxUndoCount;
	int32	WaitmilisecForDelayedView;
	int		NGColorTranparency;
	bool	InitialLightON;
	bool	NoLoadSaveMasterImage;
	bool	IsLoadedMasterImageSuccessful;
	int32	RetryTimeToCycleFinish;
	QString	FileNameOfShareMasterData;
	int32	ResultNGCircleWidth;
	bool	ConfirmResult;
	int		CameraSoftBuffer;
	bool	DrawBlueNGMark;
	bool	OMPResultCompress;
	int		OMPResultCompressNum;
	int		MaxStackCompressCount;
	bool	AutoIncreaseStrategicNumberInSlave;
	QString	TransDatabaseIP;
	int		TransDatabasePort;
	bool	RetryLoadIfFails;
	int		CountToRetryLoading;
	int32	WaitingMilisecForRetryLoading;
	int		WaitMilisecForConnect;
	int		SwapOutSizeMegaByte;
	QString	UnitName;
	QString	UnitSquareName;
	//double	TransformUnitPerPixel;
	double	TransformUnitToNano;
	int		SmallNumberFigure;
	bool	AutoIncrementScanPhaseNumber;
	bool	UnconditionalCaptureBackground;
	bool	AllocCamTargetBuffer;
	bool	ModeCompressNGImage;
	int		MaxLotDeliveryCount;
	QString	OperationLogFolder;
	int		OperationLogDaysToKeep;
	QString	PrinterDLLFileName;
	QString	PrinterSettingFileName;
	QString	PrinterParamStr;
	QString	PrinterDLLFileName2;
	QString	PrinterParamStr2;
	QString	PrinterDLLFileName3;
	QString	PrinterParamStr3;
	QString	PrinterDLLFileName4;
	QString	PrinterParamStr4;
	int32	CameraSoftBufferType;	//0:Allocated 1:Target 2:Master
	int32	CountOfNGImageForPrepararion;
	bool	ShowToBindNGForReviewArea;
	double	ZoomMin;
	double	ZoomMax;
	int32	OutputOnlyPhase;	//-1:Output in every phase
	QString	ResultAnalizerDLLPath;
	QString	ResultAnalizerFileName;
	bool	BindResultOfAllPhases;
	bool	UseScanPhaseNumber;
	bool	CommonTargetBetweenPhases;
	int32	IdleLoopMiliSec;
	bool	ModeToShowLoadingDLLWindow;
	bool	StandardWriteResult;
	int		ResultCodeInScanning;
	bool	CommonOperationInAllPhases;
	int32	MaxFatThin;
	int32	AddInspectID;		//Normally 1
	QString	FileNameControlPointsForPages;
	bool	UseExecuteCaptured;
	QString	GUILanguageFileName;
	bool	MixMasterForIntegration;
	QString	RegulationFileName;
	bool	UseSystemResultStocker;

	QString	BootupGUIFile;
	QString	BootupParam;
	QString	DefaultWorkingFolder;

	QColor	Layer0Color;
	QColor	Layer1Color;
	QColor	Layer2Color;
	QColor	Layer3Color;
	QColor	Layer4Color;
	QColor	Layer5Color;
	QColor	Layer6Color;
	QColor	Layer7Color;
	bool	EnableToColorizeFor3Layers;
	bool	OutputResult;

	QColor	GraphLayer0Color;
	QColor	GraphLayer1Color;
	QColor	GraphLayer2Color;
	QColor	GraphLayer3Color;
	QColor	GraphLayer4Color;
	QColor	GraphLayer5Color;
	QColor	GraphLayer6Color;
	QColor	GraphLayer7Color;

	QString	Layer0String;
	QString	Layer1String;
	QString	Layer2String;
	QString	Layer3String;
	QString	Layer4String;
	QString	Layer5String;
	QString	Layer6String;
	QString	Layer7String;

	QString	Phase0String;
	QString	Phase1String;
	QString	Phase2String;
	QString	Phase3String;
	QString	Phase4String;
	QString	Phase5String;
	QString	Phase6String;
	QString	Phase7String;
	QStringList	PhaseNames;	//PhaseNames[0]=Phase8String

	QColor	HistgramGraphColor;
	QColor	HistgramThreshColor;
	QColor	NGCircleColor;
	QColor	MeassurementColor;

	int32	ModePageExecutePostProcessing		;	//0:Follow as order	,-1:Calc all pages in final ScanNumber

	int32	ModePhaseExecuteInitialAfterEdit	;	//-2:Execute all , -1:Follow ScanPhase ,0-:Execute only 1 phase
	int32	ModePhaseExecuteStartByInspection	;
	int32	ModePhaseExecuteCaptured			;
	int32	ModePhaseExecutePreAlignment		;
	int32	ModePhaseExecuteAlignment			;
	int32	ModePhaseExecutePreProcessing		;
	int32	ModePhaseExecuteProcessing			;
	int32	ModePhaseExecuteProcessingRevived	;
	int32	ModePhaseExecutePostProcessing		;
	int32	ModePhaseExecutePreScanning			;
	int32	ModePhaseExecuteScanning			;
	int32	ModePhaseExecutePostScanning		;
	int32	ModePhaseExecuteManageResult		;
	int32	ModePhaseOutputResult				;	//Check compress , output result
	int32	ModePhaseAdaptChangingThreshold		;	//-2:Adapt all phases , -1:Current phase	,0-:Adapt only 1 phase

	QString	IntegrationParamFileName;
	QStringList	MasterBuffNames;

	explicit	ParamGlobal(LayersBase *base);
	~ParamGlobal(void);

	virtual	QString	GetDataText(void)			override{	return("Global Data");	};
	virtual	QString	GetDefaultFileName(void)	override{	return("Global.dat");	}
	virtual	bool	WriteEnableToDefaultFile(void)	override;

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1)	override;

	void	InitializeNetworkDrive(void);
	bool	CheckAndRefer(ParamGlobal &MasterSrcParam);

	void	ReallocPageLocal(int AllocPageNumb);
	bool	IsValid(int page ,int layer)		const;

	//----------- Allocation of camera in each page --------------
	void	ReallocCamAllocInPages(void);
	int32	GetCameraNo(int globalPage);
	void	SetCameraNo(int globalPage ,int32 CamNo);	//if CamNo==-1, no camera allocated
	bool	GetPageListFromCameraNo(int CamNo ,IntList &PageList);
	bool	SaveCameraAlloc(QIODevice *f ,int EnableCondition=-1);
	bool	LoadCameraAlloc(QIODevice *f ,int EnableCondition=-1);

	int		GetDotPerLineInCamera(int32 CamNo);
	int		GetMaxLinesInCamera(int32 CamNo);

	//----------- Strategy Code in Layer-Page Matrix --------------
	void	SetMaxScanStrategy(int n){	MaxScanStrategy=n;	}
	int		GetMaxScanStrategy(void);
	int		GetStrategyCode(int page ,int layer);
	void	SetStrategyCode(int page ,int layer ,int strategycode);
	void	ReallocStrategy(void);
	void	GetStrategy(int strategycode ,StrategicListContainer &SList);
	void	GetStrategyPage (int strategycode ,IntList &PageList);
	void	GetStrategyLayer(int strategycode ,int page ,IntList &LayerList);

	int		GetCalcStrategyCode(int page ,int layer);
	void	SetCalcStrategyCode(int page ,int layer ,int strategycode);
	void	GetCalcStrategy(int strategycode ,StrategicListContainer &SList);
	void	GetCalcStrategyPage (int strategycode ,IntList &PageList);
	void	GetCalcStrategyLayer(int strategycode ,int page ,IntList &LayerList);

	bool	SaveStrategy(QIODevice *f ,int EnableCondition=-1);
	bool	LoadStrategy(QIODevice *f ,int EnableCondition=-1);
	void	CopyStrategyFrom(ParamGlobal &src);

	//----------- Direction in each page --------------
	void	GetPageDir(int page ,bool &XDirReverse ,bool &YDirReverse);
	void	SetPageDir(int page ,bool  XDirReverse ,bool  YDirReverse);
	bool	GetPageXDir(int page);
	bool	GetPageYDir(int page);
	int		GetPageYDelay(int page);
	void	SetPageXDir(int page ,bool Rev);
	void	SetPageYDir(int page ,bool Rev);
	void	SetPageYDelay(int page ,int ydelay);
	void	ReallocPageDir(void);
	bool	SavePageDir(QIODevice *f ,int EnableCondition=-1);
	bool	LoadPageDir(QIODevice *f ,int EnableCondition=-1);
	void	CopyPageDirFrom(ParamGlobal &src);

	//----------- Strategy Code in Layer-Page Matrix --------------

	QColor	GetOneLayerColor(int Layer);
	QColor	GetOneGraphLayerColor(int Layer);
	QString	GetLayerName(int layer);
	QString	GetPhaseString(int phase);
	void	SetPhaseString(int phase ,QString &Str);

	//----------- Filter bank DLL file names--------------
	QStringList		FilterBankFileNames;


	//----------- ScanPhase--------------
	void	ReallocScanPhase(void);
	int		GetScanPhaseCount(void);
	int		GetScanNumberInPhase(int phase);
	void	SetScanPhaseNumber(int phase , int ScanNumber);
	void	GetPhaseNumber(IntList &PNumber ,int PhaseScanNumber);
	void	GetScanPhaseFromPhase(int phase ,int &RetScanPhaseNumbers);
	bool	SaveScanPhase(QIODevice *f ,int EnableCondition=-1);
	bool	LoadScanPhase(QIODevice *f ,int EnableCondition=-1);

	int		GetScanNumberInPhaseDimNumb(void);

	//----------- Remote transfer --------------
	int		GetRemoteTransferCount(void);
	RemoteTransferList	*GetRemoteTransfer(int n);
	void	AddRemoteTransfer(RemoteTransferList &n);
	void	RemoveRemoteTransfer(int n);
	bool	SaveRemoteTransfer(QIODevice *f, int EnableCondition=-1);
	bool	LoadRemoteTransfer(QIODevice *f, int EnableCondition=-1);

	//----------- Unit-------------
	bool	IsUnitMode(void);

	double	TransformPixelDistanceToUnit(int Page,double PixelX1,double PixelY1 ,double PixelX2,double PixelY2);
	double	TransformUnitDistanceToPixel(int Page,double UnitX1 ,double UnitY1  ,double UnitX2 ,double UnitY2);
	double	TransformPixelDistanceToUnit(int Page,double PixelXLen,double PixelYLen);
	double	TransformUnitDistanceToPixel(int Page,double UnitXLen ,double UnitYLen);

	double	TransformPixelToUnit	(int Page,double pixel);
	double	TransformUnitToPixel	(int Page,double unit);
	QString	TransformPixelToUnitStr	(int Page,double pixel);
	QString	GetUnitStr(double unit);
	double	TransformPixelToUnitSquare(int Page,double pixel);
	double	TransformUnitToPixelSquare(int Page,double unit);
	QString	TransformPixelToUnitSquareStr(int Page,double pixel);
	QString	GetUnitSquareStr(double unit);

	double	TransformPixelToUnitX(int Page,double pixel);
	double	TransformPixelToUnitY(int Page,double pixel);
	double	TransformUnitToPixelX(int Page,double unit);
	double	TransformUnitToPixelY(int Page,double unit);

private:
	int32	MaxScanStrategy;
	int32	*StrategyDim;
	int32	StrategyDimAllocNumb;
	int32	*CalcStrategyDim;
	int32	CalcStrategyDimAllocNumb;

	int32	*CamAllocInPagesDim;
	int32	CamAllocInPagesDimNumb;

	PageDirection	*PDirData;
	int32			PDirDataAllocNumb;

	int32	*ScanNumberInPhaseDim;
	int32	ScanNumberInPhaseDimNumb;

	RemoteTransferList	*RemoteTransferListDim;
	int32				RemoteTransferListDimNumb;

public:
	ShadowParameterContainer	ShadowParameterData;
};

//======================================================================
class	ConnectionInfo
{
private:
	int32			*GlobalCameraNo;
	int32			GlobalCameraNoNumb;
public:
	int32	PartnerID;
	QString	IPAddress;
	int32	CameraNumb;

	ConnectionInfo(void);
	ConnectionInfo(const ConnectionInfo &src){	PartnerID=src.PartnerID;	IPAddress=src.IPAddress;	CameraNumb=src.CameraNumb;	GlobalCameraNoNumb=0;	GlobalCameraNo=NULL;	}
	~ConnectionInfo(void);

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition);
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition);
	ConnectionInfo	&operator=(ConnectionInfo &src);

	void			ReallocGlobalCameraNo(void);
	int32			GetGlobalCameraNo(int localCamNo);
	void			SetGlobalCameraNo(int localCamNo, int globalCameraNo);
	int				GetPortNo(void);
};

class	ParamComm : public ParamBase ,public ServiceForLayers
{
public:
	int32	ConnectedPCNumb;
	bool	Mastered;
	int32	ThisComputerID;
	bool	EnabledComm;

	explicit	ParamComm(LayersBase *base);
	~ParamComm(void);

	virtual	QString	GetDataText(void)			override{	return("Comm Data");	};
	virtual	QString	GetDefaultFileName(void)	override{	return DefaultFileName.isEmpty() ? "Comm.dat" : DefaultFileName;	}
	virtual	bool	WriteEnableToDefaultFile(void)override;

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1)	override;

	void	ReallocConnection(void);
	int		GetConnectedPCNumb(void){	return ConnectedPCNumb;	}

	ConnectionInfo	*GetConnection(int n);
	bool	IsMastered(void)	{	return Mastered;	}

	int				GetCommIDFromPage		(ParamGlobal &ParamGlobalData ,int page);
	int				GetLocalPageFromGlobal	(ParamGlobal &ParamGlobalData ,int globalPage);
	int				GetGlobalPageFromLocal	(ParamGlobal &ParamGlobalData ,int localPage);
	ConnectionInfo	*GetConnectionFromPage	(ParamGlobal &ParamGlobalData ,int localPage);
	bool			ImageBufferNecessary(void);
	int				GetLocalCameraNumb(int computerID);

private:
	ConnectionInfo	*Connection;
	int32			ConnectionNumb;

};


inline	bool	ParamComm::ImageBufferNecessary(void)
{
	if(Mastered==false || ConnectedPCNumb==0)
		return(true);
	return(false);
}


#endif
