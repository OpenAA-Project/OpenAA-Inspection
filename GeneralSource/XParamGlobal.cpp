/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XParamGlobal.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "ServiceLibResource.h"
#include<QIODevice>
#include"XParamGlobal.h"
#include"XGeneralFunc.h"
#include"swap.h"
#include "XNetworkDrive.h"
#include "XDataInLayer.h"

StrategicListContainer	&StrategicListContainer::operator=(const StrategicListContainer &src)
{
	RemoveAll();
	for(StrategicList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		StrategicList	*b=new StrategicList();
		*b=*a;
		AppendList(b);
	}
	return *this;
}


PageDirection::PageDirection(void)
{
	ReverseX=false;
	ReverseY=false;
	YDelay	=0;
}

PageDirection	&PageDirection::operator=(const PageDirection &src)
{
	ReverseX=src.ReverseX;
	ReverseY=src.ReverseY;
	YDelay	=src.YDelay;
	return *this;
}
bool	PageDirection::Save(QIODevice *f)
{
	if(::Save(f,ReverseX)==false){
		return false;
	}
	if(::Save(f,ReverseY)==false){
		return false;
	}
	if(::Save(f,YDelay)==false){
		return false;
	}
	return true;
}
bool	PageDirection::Load(QIODevice *f)
{
	if(::Load(f,ReverseX)==false){
		return false;
	}
	if(::Load(f,ReverseY)==false){
		return false;
	}
	if(::Load(f,YDelay)==false){
		return false;
	}
	return true;
}

RemoteTransferList &RemoteTransferList::operator=(const RemoteTransferList &src)
{
	Name		=src.Name;
	IPAddress	=src.IPAddress;
	Port		=src.Port;
	return *this;
}
bool	RemoteTransferList::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f, Ver		) ==false)		return false;
	if(::Save(f, Name		) == false)		return false;
	if(::Save(f, IPAddress	) == false)		return false;
	if(::Save(f, Port		) == false)		return false;
	return true;
}
bool	RemoteTransferList::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f, Ver		) == false)		return false;
	if(::Load(f, Name		) == false)		return false;
	if(::Load(f, IPAddress	) == false)		return false;
	if(::Load(f, Port		) == false)		return false;
	return true;
}

//--------------------------------------------------------------------

bool	ShadowParameter::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f, Ver		) ==false)		return false;

	if(::Save(f, ShadowGlobalFileName		) ==false)		return false;
	if(::Save(f, ShadowGUIFileName			) ==false)		return false;
	if(::Save(f, ShadowParamFileName		) ==false)		return false;
	if(::Save(f, ShadowControlDLLFileName	) ==false)		return false;
	return true;
}
bool	ShadowParameter::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f, Ver		) == false)		return false;

	if(::Load(f, ShadowGlobalFileName		) ==false)		return false;
	if(::Load(f, ShadowGUIFileName			) ==false)		return false;
	if(::Load(f, ShadowParamFileName		) ==false)		return false;
	if(::Load(f, ShadowControlDLLFileName	) ==false)		return false;
	return true;
}

bool	ShadowParameter::operator==(const ShadowParameter &src)	const
{
	if(ShadowGlobalFileName		==src.ShadowGlobalFileName		
	&& ShadowGUIFileName		==src.ShadowGUIFileName				
	&& ShadowParamFileName		==src.ShadowParamFileName		
	&& ShadowControlDLLFileName	==src.ShadowControlDLLFileName	)
		return true;
	return false;
}

bool	ShadowParameter::operator!=(const ShadowParameter &src)	const
{
	return !operator==(src);
}
ShadowParameter &ShadowParameter::operator=(const ShadowParameter &src)
{
	ShadowGlobalFileName	=src.ShadowGlobalFileName		;
	ShadowGUIFileName		=src.ShadowGUIFileName			;
	ShadowParamFileName		=src.ShadowParamFileName		;
	ShadowControlDLLFileName=src.ShadowControlDLLFileName	;
	return *this;
}


ShadowParameter	*ShadowParameterContainer::Create(void)
{
	return new ShadowParameter();
}

bool	ShadowParameterContainer::operator==(const ShadowParameterContainer &src)	const
{
	for(ShadowParameter *d=GetFirst();d!=NULL;d=d->GetNext()){
		for(ShadowParameter *s=src.GetFirst();s!=NULL;s=s->GetNext()){
			if(*d!=*s){
				return false;
			}
		}
	}
	for(ShadowParameter *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		for(ShadowParameter *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(*d!=*s){
				return false;
			}
		}
	}
	return true;
}
bool	ShadowParameterContainer::operator!=(const ShadowParameterContainer &src)	const
{
	return !operator==(src);
}

//--------------------------------------------------------------------
ParamGlobalEachPage::ParamGlobalEachPage(void)
{
	UseEachPage			=false;
	DotPerLine			=5000;
	MaxLines			=5000;
	LayerNumb			=1;
	MaximumDotPerLine	=16384;
	MaximumMaxLines		=65535;
	NGCacheNumb			=32;
	ResolutionXNano		=20000;
	ResolutionYNano		=20000;

	SetParam(&UseEachPage			,/**/"PageLocal" ,/**/"UseEachPage"			,LangLibSolver.GetString(XParamGlobal_LS,LID_168)/*"Use params for each page"*/		);
	SetParam(&DotPerLine			,/**/"PageLocal" ,/**/"DotPerLine"			,LangLibSolver.GetString(XParamGlobal_LS,LID_170)/*"Horizontal dots in Image"*/		,0,1000000);
	SetParam(&MaxLines				,/**/"PageLocal" ,/**/"MaxLines"			,LangLibSolver.GetString(XParamGlobal_LS,LID_171)/*"Vertical dots in Image"*/		,0,1000000);
	SetParam(&LayerNumb				,/**/"PageLocal" ,/**/"LayerNumb"			,LangLibSolver.GetString(XParamGlobal_LS,LID_173)/*"Layer counts"*/					,1,1000);
	SetParam(&MaximumDotPerLine		,/**/"PageLocal" ,/**/"MaximumDotPerLine"	,LangLibSolver.GetString(XParamGlobal_LS,LID_174)/*"Maximum X pixels"*/				,-1,99999999	,ParamEnableInLoadOnMaster);
	SetParam(&MaximumMaxLines		,/**/"PageLocal" ,/**/"MaximumMaxLines"		,LangLibSolver.GetString(XParamGlobal_LS,LID_176)/*"Maximum Y pixels"*/				,-1,99999999	,ParamEnableInLoadOnMaster);
	SetParam(&NGCacheNumb			,/**/"PageLocal" ,/**/"NGCacheNumb"			,LangLibSolver.GetString(XParamGlobal_LS,LID_177)/*"NG Cache-counts in buffer"*/	,0,1000000);
	SetParam(&ResolutionXNano		,/**/"PageLocal" ,/**/"ResolutionXNano"		,LangLibSolver.GetString(XParamGlobal_LS,LID_179)/*"X resolution(nano meter)"*/		,0);
	SetParam(&ResolutionYNano		,/**/"PageLocal" ,/**/"ResolutionYNano"		,LangLibSolver.GetString(XParamGlobal_LS,LID_180)/*"Y resolution(nano meter)"*/		,0);
}



//--------------------------------------------------------------------

ParamGlobal::ParamGlobal(LayersBase *base)
:ServiceForLayers(base)
{
	DataVersion			=1;

	PageLocalData		=NULL;
	CountOfPageLocal	=0;
	AllocatedCounfOfPageLocal	=0;

	DotPerLine			=5000;
	MaxLines			=5000;
	LayerNumb			=1;
	PageNumb			=3;
	PhaseNumb			=1;
	TotalCameraNumb		=3;
	MaxInspectMilisec	=300000;
	MaximumDotPerLine	=16384;
	MaximumMaxLines		=65535;
	NGCacheNumb			=32;
	IODLL_FileName		=/**/"PluginDLL/PIODLL";
	IOSomething			=/**/"";
	RotatedAngleRadian	=0.0;
	ResolutionXNano		=20000;
	ResolutionYNano		=20000;
	CameraDLL_FileName		=/**/"PluginDLL/DummyCamera.dll";
	CameraSetting_FileName	=/**/"Camera.dat";
	CameraParameter			=/**/"";
	CameraAllocation		=/**/"";
	CameraDLL_FileName2		=/**/"";
	CameraSetting_FileName2	=/**/"";
	CameraParameter2		=/**/"";
	CameraAllocation2		=/**/"";
	CameraDLL_FileName3		=/**/"";
	CameraSetting_FileName3	=/**/"";
	CameraAllocation3		=/**/"";
	CameraParameter3		=/**/"";
	CameraDLL_FileName4		=/**/"";
	CameraSetting_FileName4	=/**/"";
	CameraAllocation4		=/**/"";
	CameraParameter4		=/**/"";

	Sequence_FileName		=/**/"Sequence.dat";
	IODefine_FileName		=/**/"IODef.dat";
	LocalDatabase_FileName	=/**/"D:/Data/Regulus64.fdb";
	DatabaseDDL_FileName	=/**/"Regulus64Local.DDL";
	LocalDatabase_Port		=3051;
	LocalDatabase_HostName	=/**/"localhost";
	LayerDefaultFileName	=/**/"LayerAttr.dat";
	ShadowTreeDefFileName	=/**/"";
	CameraResolutionBit		=8;
	ResultDLLFileName		=/**/"ResultXMLV3.dll";
	ImageLeftsideRight		=false;
	TransterPortNumber		=18666;
	TransterPortCount		=4;
	TransterWaitingMilisec	=4000;
	MaxNGCountsPerCam		=5000;
	ImageFilePath			=/**/"Z:";
	ArrangementDLLPath		=/**/"PluginDLL";
	MaxHistoryCounts		=100;
	NetworkDrive1			=/**/"Z";
	NetworkDrive2			=/**/"";
	NetworkDrive3			=/**/"";
	NetworkDrive4			=/**/"";
	NetworkDrivePath1		=/**/"//unit_a/data";
	NetworkDrivePath2		=/**/"";
	NetworkDrivePath3		=/**/"";
	NetworkDrivePath4		=/**/"";
	CaptureInBackground		=false;
	LightDLLFileName		=/**/"PluginDLL/Light.dll";
	LightSettingFileName	=/**/"Light.dat";
	LightParamStr			=/**/"";
	ChangeThresholdFromPartsOrigin	=true;
	AllocateMasterBuff		=true;
	AllocatedCountMasterBuff=1;
	AllocateBackGroundBuff		=false;
	AllocatedCountBackGroundBuff=0;
	AllocateTargetBuff		=true;
	AllocateTargetTRBuff	=false;
	AllocateGrayBuff		=true;
	AllocViewTargetBuffer	=false;
	AllocBitBuffer			=false;
	AllocTrialTargetBuffer	=false;
	DefaultImageArrange		=1;
	TopOfID					=0;
	AlgorithmDefFile		=/**/"AlgorithmList.dat";
	OutputResult			=true;
	NGMarkRadius			=8;
	MaxNGImageNumbPerPage	=200;
	MaxNGImageForHaltPerCam	=10000;
	LogoListFileName		=/**/"/Regulus64v5/LogoList.dat";
	OutputLogMode			=false;
	BufferedProcessing		=false;
	CalcSingleThread		=false;
	KeepFilteredImage		=true;
	MaxWaitingCommMilisec	=500;
	DrawResultDetail		=false;
	DrawResultDetailLevel	=0;
	DebugLevel				=0;
	ErrorLogFile			=/**/"/Regulus64v5/ErrorLog.txt";
	ReDrawByInspection		=true;
	GUIExcludedListFile		=/**/"GUIExcludedList.dat";
	AllocRawTargetBuffForNGImage	=false;
	GeneralStockerFileName	=/**/"ConfigStocker.dat";
	AdoptRateLForAvr		=0.7;
	AdoptRateHForAvr		=0.7;
	SyncGUIFileName			=/**/"";
	SyncGUIPort				=19566;
	FilterDLLPath			=/**/"Filter";
	FilterDefFile			=/**/"ConfigFilter.dat";
	CommentFileName			=/**/"CommentDef.dat";
	MinLearningSize			=256;
	MaxLearningSize			=1000;
	MakeHistgramData		=true;
	WaitMilisecAfterScan	=0;
	ShrinkDotUncoveredArea	=5;
	ViewProcessingWindow	=true;
	AdoptRawForResultImage	=true;
	OutputNGCause			=true;
	MaxUndoCount			=10;
	WaitmilisecForDelayedView	=300;
	NGColorTranparency		=100;
	InitialLightON			=true;
	NoLoadSaveMasterImage	=false;
	IsLoadedMasterImageSuccessful	=true;
	RetryTimeToCycleFinish	=10000;
	FileNameOfShareMasterData	=/**/"ShareMasterData.dat";
	ResultNGCircleWidth		=1;
	ConfirmResult			=false;
	CameraSoftBuffer		=0;
	DrawBlueNGMark			=true;
	OMPResultCompress		=true;
	OMPResultCompressNum	=4;
	MaxStackCompressCount	=100;
	AutoIncreaseStrategicNumberInSlave	=true;
	TransDatabaseIP			=/**/"";
	TransDatabasePort		=16050;
	RetryLoadIfFails		=true;
	WaitingMilisecForRetryLoading	=5000;
	CountToRetryLoading		=15;
	ImageFileCachePort		=0;
	WaitMilisecForConnect	=1000;
	SwapOutSizeMegaByte		=16000;
	UnitName				=/**/"mm";
	UnitSquareName			=/**/"mm2";
	//TransformUnitPerPixel	=0.02;
	TransformUnitToNano		=1000000.0;		//mm=1000,000nm
	SmallNumberFigure		=3;
	AutoIncrementScanPhaseNumber	=false;
	UnconditionalCaptureBackground	=false;
	AllocCamTargetBuffer			=false;
	ModeCompressNGImage				=true;
	MaxLotDeliveryCount				=1;
	OperationLogFolder				=LangLibSolver.GetString(XParamGlobal_LS,LID_8)/*"OperationLog"*/;
	OperationLogDaysToKeep			=30;
	CameraSoftBufferType			=0;	//0:Allocated 1:Target 2:Master
	CountOfNGImageForPrepararion	=20;
	ShowToBindNGForReviewArea		=false;
	ZoomMin							=0.001;
	ZoomMax							=10;
	OutputOnlyPhase					=-1;
	ResultAnalizerDLLPath			=/**/"ResultAnalizer";
	ResultAnalizerFileName			=/**/"ResultAnalizerDef.dat";
	BindResultOfAllPhases			=true;
	UseScanPhaseNumber				=true;
	CommonTargetBetweenPhases		=false;
	IdleLoopMiliSec					=100;
	ModeToShowLoadingDLLWindow		=true;
	StandardWriteResult				=true;
	ResultCodeInScanning			=1;
	CommonOperationInAllPhases		=false;
	MaxFatThin						=50;
	AddInspectID					=1;
	FileNameControlPointsForPages	=/**/"ControlPointsForPages.dat";
	UseExecuteCaptured				=false;
	GUILanguageFileName				=/**/"GUILanguage.GLN";
	MixMasterForIntegration			=true;
	RegulationFileName				=/**/"Regulation.dat";
	UseSystemResultStocker			=false;

	ModePageExecutePostProcessing		=0;

	ModePhaseExecuteInitialAfterEdit	=-1;
	ModePhaseExecuteStartByInspection	=-1;
	ModePhaseExecuteCaptured			=-1;
	ModePhaseExecutePreAlignment		=-1;
	ModePhaseExecuteAlignment			=-1;
	ModePhaseExecutePreProcessing		=-1;
	ModePhaseExecuteProcessing			=-1;
	ModePhaseExecuteProcessingRevived	=-1;
	ModePhaseExecutePostProcessing		=-1;
	ModePhaseExecutePreScanning			=-1;
	ModePhaseExecuteScanning			=-1;
	ModePhaseExecutePostScanning		=-1;
	ModePhaseExecuteManageResult		=-1;
	ModePhaseOutputResult				=-1;
	ModePhaseAdaptChangingThreshold		=-1;

	IntegrationParamFileName		=/**/"ParamIntegrationMaster.dat";

	Layer0Color	=Qt::white;
	Layer1Color	=Qt::white;
	Layer2Color	=Qt::white;
	Layer3Color	=Qt::white;
	Layer4Color	=Qt::white;
	Layer5Color	=Qt::white;
	Layer6Color	=Qt::white;
	Layer7Color	=Qt::white;
	EnableToColorizeFor3Layers=true;

	GraphLayer0Color	=Qt::green;
	GraphLayer1Color	=Qt::yellow;
	GraphLayer2Color	=Qt::blue;
	GraphLayer3Color	=Qt::cyan;
	GraphLayer4Color	=Qt::darkGreen;
	GraphLayer5Color	=Qt::darkYellow;
	GraphLayer6Color	=Qt::darkBlue;
	GraphLayer7Color	=Qt::darkCyan;

	HistgramGraphColor	=Qt::green;
	HistgramThreshColor	=Qt::red;
	NGCircleColor		=Qt::red;
	MeassurementColor	=Qt::yellow;

	Layer0String	=/**/"LY0";
	Layer1String	=/**/"LY1";
	Layer2String	=/**/"LY2";
	Layer3String	=/**/"LY3";
	Layer4String	=/**/"LY4";
	Layer5String	=/**/"LY5";
	Layer6String	=/**/"LY6";
	Layer7String	=/**/"LY7";

	Phase0String	=/**/"Ph0";
	Phase1String	=/**/"Ph1";
	Phase2String	=/**/"Ph2";
	Phase3String	=/**/"Ph3";
	Phase4String	=/**/"Ph4";
	Phase5String	=/**/"Ph5";
	Phase6String	=/**/"Ph6";
	Phase7String	=/**/"Ph7";

	GeneralStockerFileName1	=/**/"PluginDLL/General.dll";
	GeneralStockerFileName2	=/**/"";
	GeneralStockerFileName3	=/**/"";
	GeneralStockerFileName4	=/**/"";

	SetParam(&CountOfPageLocal				,/**/"Global" ,/**/"CountOfPageLocal"		,LangLibSolver.GetString(XParamGlobal_LS,LID_182)/*"Count of page local"*/		,0,1000000);
	SetParam(&DotPerLine					,/**/"Global" ,/**/"DotPerLine"				,LangLibSolver.GetString(XParamGlobal_LS,LID_166)/*"Horizontal dots in Image"*/					,0,1000000);
	SetParam(&MaxLines						,/**/"Global" ,/**/"MaxLines"				,LangLibSolver.GetString(XParamGlobal_LS,LID_169)/*"Vertical dots in Image"*/					,0,1000000);
	SetParam(&LayerNumb						,/**/"Global" ,/**/"LayerNumb"				,LangLibSolver.GetString(XParamGlobal_LS,LID_172)/*"Layer counts"*/								,1,1000);
	SetParam(&PageNumb						,/**/"Global" ,/**/"PageNumb"				,LangLibSolver.GetString(XParamGlobal_LS,LID_175)/*"Page counts"*/								,1,1000		,ParamEnableInLoadOnMaster);
	SetParam(&PhaseNumb						,/**/"Global" ,/**/"PhaseNumb"				,LangLibSolver.GetString(XParamGlobal_LS,LID_4015)/*"Phase counts"*/								,1,1000		,ParamEnableInLoadOnMaster);
	SetParam(&MaximumDotPerLine				,/**/"Global" ,/**/"MaximumDotPerLine"		,LangLibSolver.GetString(XParamGlobal_LS,LID_183)/*"Maximum X pixels"*/								,-1,99999999	,ParamEnableInLoadOnMaster);
	SetParam(&MaximumMaxLines				,/**/"Global" ,/**/"MaximumMaxLines"		,LangLibSolver.GetString(XParamGlobal_LS,LID_185)/*"Maximum Y pixels"*/								,-1,99999999	,ParamEnableInLoadOnMaster);
	SetParam(&TotalCameraNumb				,/**/"Global" ,/**/"TotalCameraNumb"		,LangLibSolver.GetString(XParamGlobal_LS,LID_178)/*"Total Camera number in system"*/			,1,1000		,ParamEnableInLoadOnMaster | ParamEnableInLoadOnSlave);
	SetParam(&MaxInspectMilisec				,/**/"Timing" ,/**/"MaxInspectSec"			,LangLibSolver.GetString(XParamGlobal_LS,LID_181)/*"Maximum inspection mili-second"*/			,0,3600*24*1000);
	SetParam(&CaptureInBackground			,/**/"Timing" ,/**/"CaptureInBackground"	,LangLibSolver.GetString(XParamGlobal_LS,LID_184)/*"Start capture as soon as prior capture"*/);
	SetParam(&NGCacheNumb					,/**/"Result" ,/**/"NGCacheNumb"			,LangLibSolver.GetString(XParamGlobal_LS,LID_187)/*"NG Cache-counts in buffer"*/				,0,1000000);
	SetParam(&ResolutionXNano				,/**/"Global" ,/**/"ResolutionXNano"		,LangLibSolver.GetString(XParamGlobal_LS,LID_190)/*"X resolution(nano meter)"*/					,0);
	SetParam(&ResolutionYNano				,/**/"Global" ,/**/"ResolutionYNano"		,LangLibSolver.GetString(XParamGlobal_LS,LID_193)/*"Y resolution(nano meter)"*/					,0);
	SetParam(&CameraResolutionBit			,/**/"Global" ,/**/"CameraResolutionBit"	,LangLibSolver.GetString(XParamGlobal_LS,LID_196)/*"Resolution Bits of Camera"*/				,8,8);
	SetParam(&WaitMilisecForConnect			,/**/"Global" ,/**/"WaitMilisecForConnect"	,LangLibSolver.GetString(XParamGlobal_LS,LID_40)/*"Waiting time (milisec) for connection to slave"*/				,0,100000);

	SetParamFileName(&BootupGUIFile			,/**/"Bootup" ,/**/"BootupGUIFile"			,LangLibSolver.GetString(XParamGlobal_LS,LID_38)/*"Bootup GUI file name (Real arguments are higher)"*/	,0);
	SetParam(&BootupParam					,/**/"Bootup" ,/**/"BootupParam"			,LangLibSolver.GetString(XParamGlobal_LS,LID_110)/*"Bootup Parameter (Real arguments are higher)"*/		,0);
	SetParamPath(&DefaultWorkingFolder		,/**/"Bootup" ,/**/"DefaultWorkingFolder"	,LangLibSolver.GetString(XParamGlobal_LS,LID_111)/*"Bootup Working directory (Real arguments are higher)"*/	,0);

	SetParam(&CommonOperationInAllPhases	,/**/"Operation" ,/**/"CommonOperationInAllPhases"	,LangLibSolver.GetString(XParamGlobal_LS,LID_112)/*"Common operation for all phases"*/);

	SetParamFileName(&IODLL_FileName		,/**/"PlugIn"	,/**/"IODLL_FileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_199)/*"FileName without ext for I/O DLL"*/		,0);
	SetParamFileName(&IOSomething			,/**/"PlugIn"	,/**/"IOSomething"			,LangLibSolver.GetString(XParamGlobal_LS,LID_41)/*"Something for parameter in PIO"*/		,0);
	SetParamFileName(&CameraDLL_FileName	,/**/"PlugIn"	,/**/"CameraDLL_FileName"	,LangLibSolver.GetString(XParamGlobal_LS,LID_202)/*"Camera DLL filename without ext"*/			,0);
	SetParamFileName(&CameraSetting_FileName,/**/"File"		,/**/"CameraSetting_FileName"	,LangLibSolver.GetString(XParamGlobal_LS,LID_205)/*"Camera-Setting file name"*/					,0);
	SetParamFileName(&CameraAllocation		,/**/"PlugIn"	,/**/"CameraAllocation"		,LangLibSolver.GetString(XParamGlobal_LS,LID_42)/*"Camera number(0,1,...)"*/			,0);
	SetParamFileName(&CameraParameter		,/**/"PlugIn"	,/**/"CameraParameter"		,LangLibSolver.GetString(XParamGlobal_LS,LID_74)/*"Camera parameter for Cam1"*/			,0);
	SetParamFileName(&CameraDLL_FileName2	,/**/"PlugIn"	,/**/"CameraDLL_FileName2"		,LangLibSolver.GetString(XParamGlobal_LS,LID_43)/*"2nd Camera DLL filename without ext"*/			,0);
	SetParamFileName(&CameraSetting_FileName2,/**/"File"	,/**/"CameraSetting_FileName2"	,LangLibSolver.GetString(XParamGlobal_LS,LID_44)/*"2nd Camera-Setting file name"*/					,0);
	SetParamFileName(&CameraAllocation2		,/**/"PlugIn"	,/**/"CameraAllocation2"			,LangLibSolver.GetString(XParamGlobal_LS,LID_45)/*"2nd Camera number(0,1,...)"*/			,0);
	SetParamFileName(&CameraParameter2		,/**/"PlugIn"	,/**/"CameraParameter2"		,LangLibSolver.GetString(XParamGlobal_LS,LID_75)/*"Camera parameter for Cam2"*/			,0);
	SetParamFileName(&CameraDLL_FileName3	,/**/"PlugIn"	,/**/"CameraDLL_FileName3"		,LangLibSolver.GetString(XParamGlobal_LS,LID_46)/*"3rd Camera DLL filename without ext"*/			,0);
	SetParamFileName(&CameraSetting_FileName3,/**/"File"	,/**/"CameraSetting_FileName3"	,LangLibSolver.GetString(XParamGlobal_LS,LID_47)/*"3rdCamera-Setting file name"*/					,0);
	SetParamFileName(&CameraAllocation3		,/**/"PlugIn"	,/**/"CameraAllocation3"			,LangLibSolver.GetString(XParamGlobal_LS,LID_48)/*"3rd Camera number(0,1,...)"*/			,0);
	SetParamFileName(&CameraParameter3		,/**/"PlugIn"	,/**/"CameraParameter3"		,LangLibSolver.GetString(XParamGlobal_LS,LID_76)/*"Camera parameter for Cam3"*/			,0);
	SetParamFileName(&CameraDLL_FileName4	,/**/"PlugIn"	,/**/"CameraDLL_FileName4"		,LangLibSolver.GetString(XParamGlobal_LS,LID_49)/*"4th Camera DLL filename without ext"*/			,0);
	SetParamFileName(&CameraSetting_FileName4,/**/"File"	,/**/"CameraSetting_FileName4"	,LangLibSolver.GetString(XParamGlobal_LS,LID_54)/*"4th Camera-Setting file name"*/					,0);
	SetParamFileName(&CameraAllocation4		,/**/"PlugIn"	,/**/"CameraAllocation4"			,LangLibSolver.GetString(XParamGlobal_LS,LID_56)/*"4th Camera number(0,1,...)"*/			,0);
	SetParamFileName(&CameraParameter4		,/**/"PlugIn"	,/**/"CameraParameter4"		,LangLibSolver.GetString(XParamGlobal_LS,LID_77)/*"Camera parameter for Cam4"*/			,0);
	SetParamFileName(&Sequence_FileName		,/**/"File"	,/**/"Sequence_FileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_208)/*"Sequence control file name"*/				,0);
	SetParamFileName(&IODefine_FileName		,/**/"File"	,/**/"IODefine_FileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_211)/*"I/O definition file name"*/					,0);
	SetParamFileName(&LocalDatabase_FileName,/**/"File" ,/**/"LocalDatabase_FileName"	,LangLibSolver.GetString(XParamGlobal_LS,LID_214)/*"Local database file name with path"*/		,0);
	SetParam(&LocalDatabase_Port			,/**/"File" ,/**/"LocalDatabase_Port"		,LangLibSolver.GetString(XParamGlobal_LS,LID_4016)/*"Local database Port number"*/		,1000,65535);
	SetParamFileName(&DatabaseDDL_FileName	,/**/"File" ,/**/"DatabaseDDL_FileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_217)/*"DDL file name for database structure"*/		,0);
	SetParamFileName(&FilterDefFile			,/**/"File" ,/**/"FilterDefFile"		,LangLibSolver.GetString(XParamGlobal_LS,LID_4017)/*"Definition file for Filter"*/		,0);

	SetParam(&LocalDatabase_HostName		,/**/"File" ,/**/"LocalDatabase_HostName"	,LangLibSolver.GetString(XParamGlobal_LS,LID_220)/*"Local Database host name"*/					,0);
	SetParam(&TransDatabaseIP				,/**/"File" ,/**/"TransDatabaseIP"			,LangLibSolver.GetString(XParamGlobal_LS,LID_9)/*"Trans Database host name / IP"*/			,0);
	SetParam(&TransDatabasePort				,/**/"File" ,/**/"TransDatabasePort"		,LangLibSolver.GetString(XParamGlobal_LS,LID_12)/*"Trans Database host Port(Default 16050)"*/	,0);

	SetParamFileName(&LayerDefaultFileName	,/**/"File" ,/**/"LayerDefaultFileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_223)/*"Default File Name of Layer"*/				,0);
	SetParamFileName(&ShadowTreeDefFileName	,/**/"File" ,/**/"ShadowTreeDefFileName"	,LangLibSolver.GetString(XParamGlobal_LS,LID_113)/*"Shadow definition file name for Root"*/		,0);
	//SetParamPath(&ResultDLLPathName			,/**/"File" ,/**/"ResultDLLPathName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_226)/*"ResultDLL Path name"*/						,0);
	SetParamFileName(&ResultDLLFileName		,/**/"File" ,/**/"ResultDLLFileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_16)/*"ResultDLL File name"*/						,0);
	SetParamPath(&ImageFilePath				,/**/"File" ,/**/"ImageFilePath"			,LangLibSolver.GetString(XParamGlobal_LS,LID_229)/*"Image File Path name"*/						,0);
	SetParam(&ImageFileCachePort			,/**/"File" ,/**/"ImageFileCachePort"		,LangLibSolver.GetString(XParamGlobal_LS,LID_17)/*"Port number of Image File Cache(TransFile) . "*/			,0,65535,0x80);
	SetParamPath(&ArrangementDLLPath		,/**/"File" ,/**/"ArrangementDLLPath"		,LangLibSolver.GetString(XParamGlobal_LS,LID_232)/*"Path of Arrangement DLL"*/					,0);
	SetParamPath(&FilterDLLPath				,/**/"File" ,/**/"FilterDLLPath"			,LangLibSolver.GetString(XParamGlobal_LS,LID_4018)/*"Path of Filter DLL"*/					,0);	
	SetParamPath(&FileNameOfShareMasterData	,/**/"File"	,/**/"FileNameOfShareMasterData",LangLibSolver.GetString(XParamGlobal_LS,LID_18)/*"File name to share master data"*/	,0);
	SetParam(&RetryLoadIfFails				,/**/"File"	,/**/"RetryLoadIfFails"			,LangLibSolver.GetString(XParamGlobal_LS,LID_19)/*"Retry loading if it fails"*/	);
	SetParam(&CountToRetryLoading			,/**/"File"	,/**/"CountToRetryLoading"		,LangLibSolver.GetString(XParamGlobal_LS,LID_20)/*"Maximum count to retry loading"*/	);
	SetParam(&WaitingMilisecForRetryLoading	,/**/"File"	,/**/"WaitingMilisecForRetryLoading"	,LangLibSolver.GetString(XParamGlobal_LS,LID_114)/*"Waiting milisec for Retry loading"*/	);
	SetParam(&ImageLeftsideRight			,/**/"Global" ,/**/"ImageLeftsideRight"		,LangLibSolver.GetString(XParamGlobal_LS,LID_235)/*"Flap image from leftside to right"*/);
	SetParam(&TransterPortNumber			,/**/"Transfer" ,/**/"TransterPortNumber"	,LangLibSolver.GetString(XParamGlobal_LS,LID_238)/*"Port Number for transfering"*/				,0);
	SetParam(&TransterPortCount				,/**/"Transfer" ,/**/"TransterPortCount"	,LangLibSolver.GetString(XParamGlobal_LS,LID_115)/*"Port count for transfering"*/, 0);
	SetParam(&TransterWaitingMilisec		,/**/"Transfer",/**/"TransterWaitingMilisec",LangLibSolver.GetString(XParamGlobal_LS,LID_116)/*"Waiting for milisec to transfer"*/, 0);
	SetParam(&ChangeThresholdFromPartsOrigin,/**/"Global" ,/**/"ChangeThresholdFromPartsOrigin"	,LangLibSolver.GetString(XParamGlobal_LS,LID_50)/*"Whether changing threshold from parts-origin items"*/	,0);
	SetParam(&DefaultImageArrange			,/**/"Global" ,/**/"DefaultImageArrange"	,LangLibSolver.GetString(XParamGlobal_LS,LID_51)/*"Default arangement method 1:X-Tile 2:Y-Tile"*/	,1,2);
	SetParam(&TopOfID						,/**/"Global" ,/**/"TopOfID"				,LangLibSolver.GetString(XParamGlobal_LS,LID_52)/*"Default ID for start"*/	,0,0x7FFFFFFF,ParamEnableInWeakest);
	SetParam(&DataVersion					,/**/"Global" ,/**/"DataVersion"	,LangLibSolver.GetString(XParamGlobal_LS,LID_53)/*"Data version"*/	,0);
	SetParam(&MaxNGCountsPerCam				,/**/"Result" ,/**/"MaxNGCountsPerCam"		,LangLibSolver.GetString(XParamGlobal_LS,LID_241)/*"Max NG Counts per Camera unit"*/);
	SetParam(&MaxNGImageForHaltPerCam		,/**/"Result" ,/**/"MaxNGImageForHaltPerCam"	,LangLibSolver.GetString(XParamGlobal_LS,LID_3980)/*"Max NG-Image Counts for Halt per camera"*/);
	SetParam(&MaxHistoryCounts				,/**/"Result" ,/**/"MaxHistoryCounts"		,LangLibSolver.GetString(XParamGlobal_LS,LID_244)/*"Max NG history counts on list"*/			,0,1000000);
	SetParam(&OutputResult					,/**/"Result" ,/**/"OutputResult"			,LangLibSolver.GetString(XParamGlobal_LS,LID_55)/*"Write inspection result"*/	);
	SetParam(&StandardWriteResult			,/**/"Result" ,/**/"StandardWriteResult"	,LangLibSolver.GetString(XParamGlobal_LS,LID_117)/*"Standard write-result mode in background"*/	);
	SetParam(&NGMarkRadius					,/**/"Result" ,/**/"NGMarkRadius"			,LangLibSolver.GetString(XParamGlobal_LS,LID_57)/*"Circle radius of NG Mark"*/	);
	SetParam(&MaxNGImageNumbPerPage			,/**/"Result" ,/**/"MaxNGImageNumbPerPage"	,LangLibSolver.GetString(XParamGlobal_LS,LID_59)/*"Maximum NG Image count per a camera"*/	);
	SetParam(&DrawResultDetail				,/**/"Result" ,/**/"DrawResultDetail"		,LangLibSolver.GetString(XParamGlobal_LS,LID_3982)/*"Mode DrawResult on Detail"*/	);
	SetParam(&DrawResultDetailLevel			,/**/"Result" ,/**/"DrawResultDetailLevel"	,LangLibSolver.GetString(XParamGlobal_LS,LID_3984)/*"Detail Level on DrawResult. 0:Most detail 1:easier"*/	);
	SetParam(&ModeCompressNGImage			,/**/"Result" ,/**/"ModeCompressNGImage"	,LangLibSolver.GetString(XParamGlobal_LS,LID_58)/*"Compress/Save NG images"*/);
	SetParam(&MaxStackCompressCount			,/**/"Result" ,/**/"MaxStackCompressCount"	,LangLibSolver.GetString(XParamGlobal_LS,LID_118)/*"Maximum count of stack of NG compress."*/);
	SetParam(&OutputNGCause					,/**/"Result" ,/**/"OutputNGCause"			,LangLibSolver.GetString(XParamGlobal_LS,LID_4019)/*"Mode : Output NGList"*/	);
	SetParam(&NGColorTranparency			,/**/"Result" ,/**/"NGColorTranparency"		,LangLibSolver.GetString(XParamGlobal_LS,LID_21)/*"Transparent level for NGColor"*/	);
	SetParam(&ResultNGCircleWidth			,/**/"Result" ,/**/"ResultNGCircleWidth"	,LangLibSolver.GetString(XParamGlobal_LS,LID_22)/*"Width of Red NG circle"*/			,0,30);
	SetParam(&DrawBlueNGMark				,/**/"Result" ,/**/"DrawBlueNGMark"			,LangLibSolver.GetString(XParamGlobal_LS,LID_23)/*"Blue NG circle"*/					);
	SetParam(&ConfirmResult					,/**/"Result" ,/**/"ConfirmResult"			,LangLibSolver.GetString(XParamGlobal_LS,LID_24)/*"Repeatable call confirmation for slave PC if calc finishes."*/			,0);
	SetParam(&OMPResultCompress				,/**/"Result" ,/**/"OMPResultCompress"		,LangLibSolver.GetString(XParamGlobal_LS,LID_25)/*"OpenMP usage in Compressing NG images."*/);
	SetParam(&OMPResultCompressNum			,/**/"Result" ,/**/"OMPResultCompressNum"	,LangLibSolver.GetString(XParamGlobal_LS,LID_78)/*"OpenMP usage count in Compressing NG images."*/);
	SetParam(&CountOfNGImageForPrepararion	,/**/"Result" ,/**/"CountOfNGImageForPrepararion"	,LangLibSolver.GetString(XParamGlobal_LS,LID_79)/*"Count of NGImage for prepararion"*/);
	SetParam(&ShowToBindNGForReviewArea		,/**/"Result" ,/**/"ShowToBindNGForReviewArea"		,LangLibSolver.GetString(XParamGlobal_LS,LID_80)/*"Show to bind multiple NG for ReviewArea"*/);
	SetParam(&ResultCodeInScanning			,/**/"Result" ,/**/"ResultCodeInScanning"	,LangLibSolver.GetString(XParamGlobal_LS,LID_119)/*"Result code in Scanning (0:NoResult , 1:OK 2:NG)"*/,0);
	SetParam(&UseSystemResultStocker		,/**/"Result" ,/**/"UseSystemResultStocker"	,LangLibSolver.GetString(XParamGlobal_LS,LID_186)/*"Use system result stocker"*/);
	SetParam(&AutoIncreaseStrategicNumberInSlave,/**/"Execute" ,/**/"AutoIncreaseStrategicNumberInSlave"		,LangLibSolver.GetString(XParamGlobal_LS,LID_26)/*"Increase Strategic number in slavePC automatically"*/);
	SetParam(&AutoIncrementScanPhaseNumber	,/**/"Execute" ,/**/"AutoIncrementScanPhaseNumber"		,LangLibSolver.GetString(XParamGlobal_LS,LID_60)/*"Auto Increment of ScanPhaseNumber"*/);
	SetParam(&AddInspectID					,/**/"Execute" ,/**/"AddInspectID"				,LangLibSolver.GetString(XParamGlobal_LS,LID_120)/*"Incremental number for InspectionID (normally 1)"*/);
	SetParam(&OutputOnlyPhase				,/**/"Execute" ,/**/"OutputOnlyPhase"		,LangLibSolver.GetString(XParamGlobal_LS,LID_121)/*"Output result only in phase number (-1: every phase)"*/);
	SetParam(&BindResultOfAllPhases			,/**/"Execute" ,/**/"BindResultOfAllPhases"	,LangLibSolver.GetString(XParamGlobal_LS,LID_122)/*"Output result after binding all phase"*/);
	
	SetParam(&ResultAnalizerDLLPath			,/**/"ResultAnalizer" ,/**/"ResultAnalizerDLLPath"		,LangLibSolver.GetString(XParamGlobal_LS,LID_123)/*"Relative path for ResultAnalizer"*/);
	SetParam(&ResultAnalizerFileName		,/**/"ResultAnalizer" ,/**/"ResultAnalizerFileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_124)/*"Default file name for ResultAnalizer"*/);

	SetParamPath(&NetworkDrive1				,/**/"NetDrive" ,/**/"NetworkDrive1"		,LangLibSolver.GetString(XParamGlobal_LS,LID_247)/*"Network Drive1 for initialization"*/);
	SetParamPath(&NetworkDrivePath1			,/**/"NetDrive" ,/**/"NetworkDrivePath1"	,LangLibSolver.GetString(XParamGlobal_LS,LID_250)/*"Network Drive1 path for initialization"*/);
	SetParamPath(&NetworkDrive2				,/**/"NetDrive" ,/**/"NetworkDrive2"		,LangLibSolver.GetString(XParamGlobal_LS,LID_253)/*"Network Drive2 for initialization"*/);
	SetParamPath(&NetworkDrivePath2			,/**/"NetDrive" ,/**/"NetworkDrivePath2"	,LangLibSolver.GetString(XParamGlobal_LS,LID_256)/*"Network Drive2 path for initialization"*/);
	SetParamPath(&NetworkDrive3				,/**/"NetDrive" ,/**/"NetworkDrive3"		,LangLibSolver.GetString(XParamGlobal_LS,LID_259)/*"Network Drive3 for initialization"*/);
	SetParamPath(&NetworkDrivePath3			,/**/"NetDrive" ,/**/"NetworkDrivePath3"	,LangLibSolver.GetString(XParamGlobal_LS,LID_262)/*"Network Drive3 path for initialization"*/);
	SetParamPath(&NetworkDrive4				,/**/"NetDrive" ,/**/"NetworkDrive4"		,LangLibSolver.GetString(XParamGlobal_LS,LID_265)/*"Network Drive4 for initialization"*/);
	SetParamPath(&NetworkDrivePath4			,/**/"NetDrive" ,/**/"NetworkDrivePath4"	,LangLibSolver.GetString(XParamGlobal_LS,LID_268)/*"Network Drive4 path for initialization"*/);
	SetParamFileName(&LightDLLFileName		,/**/"Light"	,/**/"LightDLLFileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_271)/*"Light DLL file name"*/						,0);
	SetParamFileName(&LightSettingFileName	,/**/"Light"	,/**/"LightSettingFileName"	,LangLibSolver.GetString(XParamGlobal_LS,LID_274)/*"configuration file name for light"*/		,0);
	SetParam(&LightParamStr					,/**/"Light"	,/**/"LightParamStr"		,LangLibSolver.GetString(XParamGlobal_LS,LID_27)/*"Initial Parameter for Light "*/		,0);
	SetParam(&InitialLightON				,/**/"Light"	,/**/"InitialLightON"		,LangLibSolver.GetString(XParamGlobal_LS,LID_28)/*"Initial Light ON"*/		,0);
	SetParamFileName(&LightDLLFileName2		,/**/"Light"	,/**/"LightDLLFileName2"	,LangLibSolver.GetString(XParamGlobal_LS,LID_29)/*"2nd Light DLL file name"*/				,0);
	SetParam(&LightParamStr2				,/**/"Light"	,/**/"LightParamStr2"		,LangLibSolver.GetString(XParamGlobal_LS,LID_30)/*"2nd Initial Parameter for Light "*/		,0);
	SetParamFileName(&LightDLLFileName3		,/**/"Light"	,/**/"LightDLLFileName3"	,LangLibSolver.GetString(XParamGlobal_LS,LID_31)/*"3rd Light DLL file name"*/				,0);
	SetParam(&LightParamStr3				,/**/"Light"	,/**/"LightParamStr3"		,LangLibSolver.GetString(XParamGlobal_LS,LID_32)/*"3rd Initial Parameter for Light "*/		,0);
	SetParamFileName(&LightDLLFileName4		,/**/"Light"	,/**/"LightDLLFileName4"	,LangLibSolver.GetString(XParamGlobal_LS,LID_33)/*"4th Light DLL file name"*/				,0);
	SetParam(&LightParamStr4				,/**/"Light"	,/**/"LightParamStr4"		,LangLibSolver.GetString(XParamGlobal_LS,LID_34)/*"4th Initial Parameter for Light "*/		,0);

	SetParamFileName(&PrinterDLLFileName	,/**/"Printer"	,/**/"PrinterDLLFileName"	,LangLibSolver.GetString(XParamGlobal_LS,LID_81)/*"Printer DLL file name"*/					,0);
	SetParamFileName(&PrinterSettingFileName,/**/"Printer"	,/**/"PrinterSettingFileName",LangLibSolver.GetString(XParamGlobal_LS,LID_83)/*"configuration file name for Printer"*/		,0);
	SetParam(&PrinterParamStr				,/**/"Printer"	,/**/"PrinterParamStr"		,LangLibSolver.GetString(XParamGlobal_LS,LID_85)/*"Initial Parameter for Printer "*/			,0);
	SetParamFileName(&PrinterDLLFileName2	,/**/"Printer"	,/**/"PrinterDLLFileName2"	,LangLibSolver.GetString(XParamGlobal_LS,LID_87)/*"2nd Printer DLL file name"*/				,0);
	SetParam(&PrinterParamStr2				,/**/"Printer"	,/**/"PrinterParamStr2"		,LangLibSolver.GetString(XParamGlobal_LS,LID_89)/*"2nd Initial Parameter for Printer "*/		,0);
	SetParamFileName(&PrinterDLLFileName3	,/**/"Printer"	,/**/"PrinterDLLFileName3"	,LangLibSolver.GetString(XParamGlobal_LS,LID_91)/*"3rd Printer DLL file name"*/				,0);
	SetParam(&PrinterParamStr3				,/**/"Printer"	,/**/"PrinterParamStr3"		,LangLibSolver.GetString(XParamGlobal_LS,LID_93)/*"3rd Initial Parameter for Printer "*/		,0);
	SetParamFileName(&PrinterDLLFileName4	,/**/"Printer"	,/**/"PrinterDLLFileName4"	,LangLibSolver.GetString(XParamGlobal_LS,LID_95)/*"4th Printer DLL file name"*/				,0);
	SetParam(&PrinterParamStr4				,/**/"Printer"	,/**/"PrinterParamStr4"		,LangLibSolver.GetString(XParamGlobal_LS,LID_97)/*"4th Initial Parameter for Printer "*/		,0);

	SetParam(&AllocateMasterBuff			,/**/"System"	,/**/"AllocateMasterBuff"	,LangLibSolver.GetString(XParamGlobal_LS,LID_61)/*"When MasterBuff is allocated ,True"*/	,0);
	SetParam(&AllocatedCountMasterBuff		,/**/"System"	,/**/"AllocatedCountMasterBuff"		,LangLibSolver.GetString(XParamGlobal_LS,LID_125)/*"Allocateed count of MasterBuff (0:No Master Buff)"*/	,0,1000);
	SetParam(&AllocateBackGroundBuff		,/**/"System"	,/**/"AllocateBackGroundBuff"		,"When BackGroundBuff is allocated ,True"	,0);
	SetParam(&AllocatedCountBackGroundBuff	,/**/"System"	,/**/"AllocatedCountBackGroundBuff"	,"Allocateed count of BackGroundBuff (0:No Master Buff)"	,0,1000);
	SetParam(&AllocateTargetBuff			,/**/"System"	,/**/"AllocateTargetBuff"	,LangLibSolver.GetString(XParamGlobal_LS,LID_63)/*"When TargetBuff is allocated ,True"*/	,0);
	SetParam(&AllocateTargetTRBuff			,/**/"System"	,/**/"AllocateTargetTRBuff"			,LangLibSolver.GetString(XParamGlobal_LS,LID_126)/*"When Transpositional TargetBuff is allocated ,True"*/	,0);
	SetParam(&CommonTargetBetweenPhases		,/**/"System"	,/**/"CommonTargetBetweenPhases"	,LangLibSolver.GetString(XParamGlobal_LS,LID_127)/*"Target buffer is common between all phases"*/,0);
	SetParam(&AllocateGrayBuff				,/**/"System"	,/**/"AllocateGrayBuff"				,LangLibSolver.GetString(XParamGlobal_LS,LID_65)/*"When GrayBuff is allocated ,True"*/	,0);
	SetParam(&AllocRawTargetBuffForNGImage	,/**/"System"	,/**/"AllocRawTargetBuffForNGImage"	,LangLibSolver.GetString(XParamGlobal_LS,LID_3986)/*"When Raw buffer for NG Image is allocated ,True"*/	,0);
	SetParam(&AllocViewTargetBuffer			,/**/"System"	,/**/"AllocViewTargetBuffer"		,LangLibSolver.GetString(XParamGlobal_LS,LID_4020)/*"When delayed view is allocated ,True"*/	,0);
	SetParam(&AllocCamTargetBuffer			,/**/"System"	,/**/"AllocCamTargetBuffer"			,LangLibSolver.GetString(XParamGlobal_LS,LID_62)/*"Allocate camera image buffer"*/	,0);
	SetParam(&AllocBitBuffer				,/**/"System"	,/**/"AllocBitBuffer"				,LangLibSolver.GetString(XParamGlobal_LS,LID_99)/*"Allocate bit buffer"*/	,0);
	SetParam(&AllocTrialTargetBuffer		,/**/"System"	,/**/"AllocTrialTargetBuffer"		,LangLibSolver.GetString(XParamGlobal_LS,LID_128)/*"Allocate TrialTargetBuff"*/	,0);
	SetParam(&AdoptRawForResultImage		,/**/"System"	,/**/"AdoptRawForResultImage"			,LangLibSolver.GetString(XParamGlobal_LS,LID_4021)/*"True when Raw buffer is available and Raw image is adopted for NG image"*/	,0);
	SetParam(&MaxUndoCount					,/**/"System"	,/**/"MaxUndoCount"			,LangLibSolver.GetString(XParamGlobal_LS,LID_4022)/*"Maximum Undo count"*/	,0);
	SetParam(&MaxFatThin					,/**/"System"	,/**/"MaxFatThin"			,LangLibSolver.GetString(XParamGlobal_LS,LID_129)/*"Maximum Thin/Fat width"*/	,0,1000);
	SetParam(&SwapOutSizeMegaByte			,/**/"Setting"	,/**/"SwapOutSizeMegaByte"				,LangLibSolver.GetString(XParamGlobal_LS,LID_64)/*"Memory size to swap out (MByte)"*/);
	SetParamFileName(&AlgorithmDefFile		,/**/"File"		,/**/"AlgorithmDefFile"		,LangLibSolver.GetString(XParamGlobal_LS,LID_66)/*"Algorithm Def file name"*/	,0);
	SetParamFileName(&LogoListFileName		,/**/"File"		,/**/"LogoListFileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_68)/*"File name for Logo-List"*/	,0);
	SetParamFileName(&CommentFileName		,/**/"File"		,/**/"CommentFileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_4023)/*"Comment definition file name"*/	,0);
	SetParamFileName(&FileNameControlPointsForPages	,/**/"File"	,/**/"FileNameControlPointsForPages"	,LangLibSolver.GetString(XParamGlobal_LS,LID_130)/*"File name to ControlPointsForPages"*/	,0);
	SetParam(&BufferedProcessing			, /**/"Timing" ,/**/"BufferedProcessing"		,LangLibSolver.GetString(XParamGlobal_LS,LID_82)/*"Output OK in strategic process till end before end of calc"*/);
	SetParam(&WaitMilisecAfterScan			, /**/"Timing" ,/**/"WaitMilisecAfterScan"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4024)/*"Shortest calculation time for CycleTime (ms)"*/);
	SetParam(&WaitmilisecForDelayedView		, /**/"Timing" ,/**/"WaitmilisecForDelayedView"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4025)/*"Delayed mili seconds for view"*/);
	SetParam(&UnconditionalCaptureBackground, /**/"Timing" ,/**/"UnconditionalCaptureBackground"	,LangLibSolver.GetString(XParamGlobal_LS,LID_67)/*"Unconditional Capture mode in Background"*/);
	SetParam(&IdleLoopMiliSec				, /**/"Timing" ,/**/"IdleLoopMiliSec"					,LangLibSolver.GetString(XParamGlobal_LS,LID_131)/*"IdleLoop timer interval (mili second)"*/);
	SetParam(&CalcSingleThread				, /**/"System"	,/**/"CalcSingleThread"		,LangLibSolver.GetString(XParamGlobal_LS,LID_84)/*"True if single thread calculation is executed"*/	,-1);
	SetParam(&KeepFilteredImage				, /**/"System" ,/**/"KeepFilteredImage"			,LangLibSolver.GetString(XParamGlobal_LS,LID_86)/*"Keep filtered image?"*/);
	SetParam(&MaxWaitingCommMilisec			, /**/"System" ,/**/"MaxWaitingCommMilisec"	,LangLibSolver.GetString(XParamGlobal_LS,LID_88)/*"Maximum wait-milisecond for comm(LAN)?"*/);
	SetParam(&RetryTimeToCycleFinish		, /**/"System" ,/**/"RetryTimeToCycleFinish",LangLibSolver.GetString(XParamGlobal_LS,LID_35)/*"Waiting time to retry to make sure if Cycle finishes or not"*/);
	SetParam(&DebugLevel					,/**/"System"	,/**/"DebugLevel"			,LangLibSolver.GetString(XParamGlobal_LS,LID_3988)/*"Debug(Logging)level. Bit0:Each layer Bit1:Each item Bit2:Controller Bit4:DrawResult"*/);
	//SetParam(&ErrorLogFile					,/**/"File"		,/**/"ErrorLogFile"			,LangLibSolver.GetString(XParamGlobal_LS,LID_3990)/*"File name with parh of Error Log"*/);
	//SetParam(&OutputLogMode					,/**/"File"		,/**/"OutputLogMode"			,LangLibSolver.GetString(XParamGlobal_LS,LID_4026)/*"Mode of Log-output"*/);
	SetParam(&ErrorLogFile					,/**/"Log"		,/**/"ErrorLogFile"			,LangLibSolver.GetString(XParamGlobal_LS,LID_3990)/*"File name with parh of Error Log"*/);
	SetParam(&OutputLogMode					,/**/"Log"		,/**/"OutputLogMode"			,LangLibSolver.GetString(XParamGlobal_LS,LID_4026)/*"Mode of Log-output"*/);
	SetParam(&ReDrawByInspection			,/**/"Optimize"	,/**/"ReDrawByInspection"	,LangLibSolver.GetString(XParamGlobal_LS,LID_3992)/*"Draw after every inspection"*/);
	SetParam(&GUIExcludedListFile			,/**/"File"		,/**/"GUIExcludedListFile"	,LangLibSolver.GetString(XParamGlobal_LS,LID_3994)/*"File name of Excluded GUI DLL File list"*/);
	SetParam(&NoLoadSaveMasterImage			,/**/"File"		,/**/"NoLoadSaveMasterImage"	,LangLibSolver.GetString(XParamGlobal_LS,LID_36)/*"No load and save MasterImage"*/);
	SetParam(&GUILanguageFileName			,/**/"File"		,/**/"GUILanguageFileName"	,LangLibSolver.GetString(XParamGlobal_LS,LID_132)/*"GUI Language file name"*/);
	SetParam(&RegulationFileName			,/**/"File"		,/**/"RegulationFileName"	,LangLibSolver.GetString(XParamGlobal_LS,LID_188)/*"Regulstion file name to load/save as default filename"*/);

	SetParam(&AdoptRateLForAvr				,/**/"Global"	,/**/"AdoptRateLForAvr"	,LangLibSolver.GetString(XParamGlobal_LS,LID_3996)/*"Adopted Rate for Low side for Average"*/);
	SetParam(&AdoptRateHForAvr				,/**/"Global"	,/**/"AdoptRateHForAvr"	,LangLibSolver.GetString(XParamGlobal_LS,LID_3998)/*"Adopted Rate for High side for Average"*/);
	SetParam(&ShrinkDotUncoveredArea		,/**/"Global"														,/**/"ShrinkDotUncoveredArea"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4027)/*"Shrink Dot for UncoveredArea"*/);
	SetParamFileName(&SyncGUIFileName		,/**/"System"	,/**/"SyncGUIFileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_4028)/*"Infomation file for Synclonization between Masters"*/	,0);
	SetParam(&SyncGUIPort					,/**/"System"	,/**/"SyncGUIPort"			,LangLibSolver.GetString(XParamGlobal_LS,LID_4029)/*"Own Port number for Synclonization between Masters"*/	,0);
	SetParam(&ViewProcessingWindow			,/**/"Global"	,/**/"ViewProcessingWindow"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4030)/*"Mode to View ProcessingWindow"*/);
	SetParam(&CameraSoftBuffer				,/**/"Global"	,/**/"CameraSoftBuffer"		,LangLibSolver.GetString(XParamGlobal_LS,LID_37)/*"Count of soft buffer to capture image"*/);
	SetParam(&CameraSoftBufferType			,/**/"Global"	,/**/"CameraSoftBufferType"	,LangLibSolver.GetString(XParamGlobal_LS,LID_101)/*"0:Allocated in memory  1:Target buffer  2:Master buffer"*/,0,3		,ParamEnableInLoadOnMaster);
	SetParam(&ZoomMin						,/**/"Image"	,/**/"ZoomMin"				,LangLibSolver.GetString(XParamGlobal_LS,LID_103)/*"Minimum zoom rate"*/,0.00000001,1000.0);
	SetParam(&ZoomMax						,/**/"Image"	,/**/"ZoomMax"				,LangLibSolver.GetString(XParamGlobal_LS,LID_105)/*"Maximum zoom rate"*/,0.00000001,1000.0);

	SetParam(&Layer0Color	, /**/"Color" ,/**/"Layer0Color",LangLibSolver.GetString(XParamGlobal_LS,LID_277)/*"Layer0 Color in single view(Brightness color)"*/);
	SetParam(&Layer1Color	, /**/"Color" ,/**/"Layer1Color",LangLibSolver.GetString(XParamGlobal_LS,LID_280)/*"Layer1 Color in single view(Brightness color)"*/);
	SetParam(&Layer2Color	, /**/"Color" ,/**/"Layer2Color",LangLibSolver.GetString(XParamGlobal_LS,LID_283)/*"Layer2 Color in single view(Brightness color)"*/);
	SetParam(&Layer3Color	, /**/"Color" ,/**/"Layer3Color",LangLibSolver.GetString(XParamGlobal_LS,LID_286)/*"Layer3 Color in single view(Brightness color)"*/);
	SetParam(&Layer4Color	, /**/"Color" ,/**/"Layer4Color",LangLibSolver.GetString(XParamGlobal_LS,LID_289)/*"Layer4 Color in single view(Brightness color)"*/);
	SetParam(&Layer5Color	, /**/"Color" ,/**/"Layer5Color",LangLibSolver.GetString(XParamGlobal_LS,LID_292)/*"Layer5 Color in single view(Brightness color)"*/);
	SetParam(&Layer6Color	, /**/"Color" ,/**/"Layer6Color",LangLibSolver.GetString(XParamGlobal_LS,LID_295)/*"Layer6 Color in single view(Brightness color)"*/);
	SetParam(&Layer7Color	, /**/"Color" ,/**/"Layer7Color",LangLibSolver.GetString(XParamGlobal_LS,LID_298)/*"Layer7 Color in single view(Brightness color)"*/);
	SetParam(&EnableToColorizeFor3Layers	, /**/"Color" ,/**/"EnableToColorizeFor3Layers",LangLibSolver.GetString(XParamGlobal_LS,LID_301)/*"Enable color show in 3 layers combination"*/);

	SetParam(&GraphLayer0Color	, /**/"OtherColor" ,/**/"GraphLayer0Color",LangLibSolver.GetString(XParamGlobal_LS,LID_304)/*"Layer0 color for something"*/);
	SetParam(&GraphLayer1Color	, /**/"OtherColor" ,/**/"GraphLayer1Color",LangLibSolver.GetString(XParamGlobal_LS,LID_307)/*"Layer1 color for something"*/);
	SetParam(&GraphLayer2Color	, /**/"OtherColor" ,/**/"GraphLayer2Color",LangLibSolver.GetString(XParamGlobal_LS,LID_310)/*"Layer2 color for something"*/);
	SetParam(&GraphLayer3Color	, /**/"OtherColor" ,/**/"GraphLayer3Color",LangLibSolver.GetString(XParamGlobal_LS,LID_313)/*"Layer3 color for something"*/);
	SetParam(&GraphLayer4Color	, /**/"OtherColor" ,/**/"GraphLayer4Color",LangLibSolver.GetString(XParamGlobal_LS,LID_316)/*"Layer4 color for something"*/);
	SetParam(&GraphLayer5Color	, /**/"OtherColor" ,/**/"GraphLayer5Color",LangLibSolver.GetString(XParamGlobal_LS,LID_319)/*"Layer5 color for something"*/);
	SetParam(&GraphLayer6Color	, /**/"OtherColor" ,/**/"GraphLayer6Color",LangLibSolver.GetString(XParamGlobal_LS,LID_322)/*"Layer6 color for something"*/);
	SetParam(&GraphLayer7Color	, /**/"OtherColor" ,/**/"GraphLayer7Color",LangLibSolver.GetString(XParamGlobal_LS,LID_325)/*"Layer7 color for something"*/);

	SetParam(&HistgramGraphColor	, /**/"OtherColor" ,/**/"HistgramGraphColor"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4031)/*"General Histgram bar color"*/);
	SetParam(&HistgramThreshColor	, /**/"OtherColor" ,/**/"HistgramThreshColor"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4032)/*"General histgram threshold color"*/);
	SetParam(&NGCircleColor			, /**/"OtherColor" ,/**/"NGCircleColor"			,LangLibSolver.GetString(XParamGlobal_LS,LID_69)/*"NG circle color"*/);
	SetParam(&MeassurementColor		, /**/"OtherColor" ,/**/"MeassurementColor"		,LangLibSolver.GetString(XParamGlobal_LS,LID_106)/*"Meassurement color (Arrow and text color)"*/);

	SetParam(&Layer0String	,/**/"LayerName"	,/**/"Layer0String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_90)/*"Layer 0 Name"*/	);
	SetParam(&Layer1String	,/**/"LayerName"	,/**/"Layer1String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_92)/*"Layer 1 Name"*/	);
	SetParam(&Layer2String	,/**/"LayerName"	,/**/"Layer2String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_94)/*"Layer 2 Name"*/	);
	SetParam(&Layer3String	,/**/"LayerName"	,/**/"Layer3String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_96)/*"Layer 3 Name"*/	);
	SetParam(&Layer4String	,/**/"LayerName"	,/**/"Layer4String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_98)/*"Layer 4 Name"*/	);
	SetParam(&Layer5String	,/**/"LayerName"	,/**/"Layer5String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_100)/*"Layer 5 Name"*/	);
	SetParam(&Layer6String	,/**/"LayerName"	,/**/"Layer6String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_102)/*"Layer 6 Name"*/	);
	SetParam(&Layer7String	,/**/"LayerName"	,/**/"Layer7String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_104)/*"Layer 7 Name"*/	);

	SetParam(&Phase0String	,/**/"PhaseName"	,/**/"Phase0String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4033)/*"Layer 0 Name"*/);
	SetParam(&Phase1String	,/**/"PhaseName"	,/**/"Phase1String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4034)/*"Layer 1 Name"*/);
	SetParam(&Phase2String	,/**/"PhaseName"	,/**/"Phase2String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4035)/*"Layer 2 Name"*/);
	SetParam(&Phase3String	,/**/"PhaseName"	,/**/"Phase3String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4036)/*"Layer 3 Name"*/);
	SetParam(&Phase4String	,/**/"PhaseName"	,/**/"Phase4String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4037)/*"Layer 4 Name"*/);
	SetParam(&Phase5String	,/**/"PhaseName"	,/**/"Phase5String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4038)/*"Layer 5 Name"*/);
	SetParam(&Phase6String	,/**/"PhaseName"	,/**/"Phase6String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4039)/*"Layer 6 Name"*/);
	SetParam(&Phase7String	,/**/"PhaseName"	,/**/"Phase7String"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4040)/*"Layer 7 Name"*/);

	SetParamFileName(&GeneralStockerFileName	,/**/"GeneralStocker" ,/**/"GeneralStockerFileName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_4000)/*"Configuration file name for GeneralStocker"*/		,-1);
	SetParamFileName(&GeneralStockerFileName1	,/**/"GeneralStocker" ,/**/"GeneralStockerFileName1"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4002)/*"File name 1 for GeneralStocker"*/		,-1);
	SetParamFileName(&GeneralStockerFileName2	,/**/"GeneralStocker" ,/**/"GeneralStockerFileName2"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4004)/*"File name 2 for GeneralStocker"*/		,-1);
	SetParamFileName(&GeneralStockerFileName3	,/**/"GeneralStocker" ,/**/"GeneralStockerFileName3"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4006)/*"File name 3 for GeneralStocker"*/		,-1);
	SetParamFileName(&GeneralStockerFileName4	,/**/"GeneralStocker" ,/**/"GeneralStockerFileName4"	,LangLibSolver.GetString(XParamGlobal_LS,LID_4008)/*"File name 4 for GeneralStocker"*/		,-1);

	SetParam(&UnitName							, /**/"Unit"		,/**/"UnitName"						,LangLibSolver.GetString(XParamGlobal_LS,LID_70)/*"Unit name"*/);
	SetParam(&UnitSquareName					, /**/"Unit"		,/**/"UnitSquareName"				,LangLibSolver.GetString(XParamGlobal_LS,LID_71)/*"Unit square name"*/);
	//SetParam(&TransformUnitPerPixel				, /**/"Unit"		,/**/"TransformUnitPerPixel"		,LangLibSolver.GetString(XParamGlobal_LS,LID_72)/*"Transform Unit/Pixel"*/);
	SetParam(&TransformUnitToNano				, /**/"Unit"		,/**/"TransformUnitToNano"			,LangLibSolver.GetString(XParamGlobal_LS,LID_133)/*"Unit(mm) =XXXX nm"*/);
	SetParam(&SmallNumberFigure					, /**/"Unit"		,/**/"SmallNumberFigure"			,LangLibSolver.GetString(XParamGlobal_LS,LID_73)/*"Small number figure in unit"*/);

	SetParam(&MinLearningSize					,/**/"Learning"		,/**/"MinLearningSize"				,LangLibSolver.GetString(XParamGlobal_LS,LID_4041)/*"Minimum window size of Learning"*/);
	SetParam(&MaxLearningSize					,/**/"Learning"		,/**/"MaxLearningSize"				,LangLibSolver.GetString(XParamGlobal_LS,LID_4042)/*"Maximum window size of Learning"*/);
	SetParam(&MakeHistgramData					,/**/"System"		,/**/"MakeHistgramData"				,LangLibSolver.GetString(XParamGlobal_LS,LID_4043)/*"If check, histgram data is created in each item"*/);
	SetParam(&MaxLotDeliveryCount				,/**/"System"		,/**/"MaxLotDeliveryCount"			,LangLibSolver.GetString(XParamGlobal_LS,LID_107)/*"Max Lot-Delivery count"*/);
	SetParam(&ModeToShowLoadingDLLWindow		,/**/"System"		,/**/"ModeToShowLoadingDLLWindow"	,LangLibSolver.GetString(XParamGlobal_LS,LID_134)/*"Mode to show loading-DLL Window"*/);
	SetParam(&UseExecuteCaptured				,/**/"System"		,/**/"UseExecuteCaptured"			,LangLibSolver.GetString(XParamGlobal_LS,LID_135)/*"Use ExecuteCaptured"*/);

	SetParam(&OperationLogFolder				,/**/"Log"			,/**/"OperationLogFolder"			,LangLibSolver.GetString(XParamGlobal_LS,LID_108)/*"Log folder for Operation log"*/);
	SetParam(&OperationLogDaysToKeep			,/**/"Log"			,/**/"OperationLogDaysToKeep"		,LangLibSolver.GetString(XParamGlobal_LS,LID_109)/*"Days to keep Operation log"*/);

	SetParam(&ModePageExecutePostProcessing		,/**/"Page"			,/**/"ModePageExecutePostProcessing",LangLibSolver.GetString(XParamGlobal_LS,LID_189)/*"0:Follow as order	,-1:Calc all pages in final ScanNumber"*/);

	SetParam(&ModePhaseExecuteInitialAfterEdit	,/**/"Phase"		,/**/"ModePhaseExecuteInitialAfterEdit"	,LangLibSolver.GetString(XParamGlobal_LS,LID_136)/*"ExecuteInitialAfterEdit	-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecuteStartByInspection	,/**/"Phase"		,/**/"ModePhaseExecuteStartByInspection",LangLibSolver.GetString(XParamGlobal_LS,LID_137)/*"ExecuteStartByInspection	-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecuteCaptured			,/**/"Phase"		,/**/"ModePhaseExecuteCaptured"			,LangLibSolver.GetString(XParamGlobal_LS,LID_138)/*"ExecuteCaptured			-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecutePreAlignment		,/**/"Phase"		,/**/"ModePhaseExecutePreAlignment"		,LangLibSolver.GetString(XParamGlobal_LS,LID_139)/*"ExecutePreAlignment		-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecuteAlignment			,/**/"Phase"		,/**/"ModePhaseExecuteAlignment"		,LangLibSolver.GetString(XParamGlobal_LS,LID_140)/*"ExecuteAlignment			-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecutePreProcessing		,/**/"Phase"		,/**/"ModePhaseExecutePreProcessing"	,LangLibSolver.GetString(XParamGlobal_LS,LID_141)/*"ExecutePreProcessing		-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecuteProcessing		,/**/"Phase"		,/**/"ModePhaseExecuteProcessing"		,LangLibSolver.GetString(XParamGlobal_LS,LID_142)/*"ExecuteProcessing			-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecuteProcessingRevived	,/**/"Phase"		,/**/"ModePhaseExecuteProcessingRevived",LangLibSolver.GetString(XParamGlobal_LS,LID_143)/*"ExecuteProcessingRevived	-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecutePostProcessing	,/**/"Phase"		,/**/"ModePhaseExecutePostProcessing"	,LangLibSolver.GetString(XParamGlobal_LS,LID_144)/*"ExecutePostProcessing		-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecutePreScanning		,/**/"Phase"		,/**/"ModePhaseExecutePreScanning"		,LangLibSolver.GetString(XParamGlobal_LS,LID_145)/*"ExecutePreScanning		-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecuteScanning			,/**/"Phase"		,/**/"ModePhaseExecuteScanning"			,LangLibSolver.GetString(XParamGlobal_LS,LID_146)/*"ExecuteScanning			-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecutePostScanning		,/**/"Phase"		,/**/"ModePhaseExecutePostScanning"		,LangLibSolver.GetString(XParamGlobal_LS,LID_147)/*"ExecutePostScanning		-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseExecuteManageResult		,/**/"Phase"		,/**/"ModePhaseExecuteManageResult"		,LangLibSolver.GetString(XParamGlobal_LS,LID_148)/*"ExecuteManageResult		-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseOutputResult				,/**/"Phase"		,/**/"ModePhaseOutputResult"			,LangLibSolver.GetString(XParamGlobal_LS,LID_149)/*"ModePhaseOutputResult	-3:One of phases ,-2:All phases,-1:Follow scan-phase,0-:1 phase"*/);
	SetParam(&ModePhaseAdaptChangingThreshold	,/**/"Phase"		,/**/"ModePhaseAdaptChangingThreshold"	,LangLibSolver.GetString(XParamGlobal_LS,LID_150)/*"AdaptChangingThreshold	-2:Adapt all phases , -1:Current phase	,0-:Adapt only 1 phase"*/);
	
	SetParam(&IntegrationParamFileName			,/**/"Integration"	,/**/"IntegrationParamFileName"			,LangLibSolver.GetString(XParamGlobal_LS,LID_151)/*"Integration param file name (ParamIntegrationMaster.dat)"*/);
	SetParam(&MixMasterForIntegration			,/**/"Integration"	,/**/"MixMasterForIntegration"			,LangLibSolver.GetString(XParamGlobal_LS,LID_191)/*"Use mixed Master image for integration"*/);
	

	SetCategoryLanguage(/**/"Global"		,LangLibSolver.GetString(XParamGlobal_LS,LID_0)/*"Global"*/);
	SetCategoryLanguage(/**/"Timing"		,LangLibSolver.GetString(XParamGlobal_LS,LID_1)/*"Timing"*/);
	SetCategoryLanguage(/**/"Result"		,LangLibSolver.GetString(XParamGlobal_LS,LID_2)/*"Result"*/);
	SetCategoryLanguage(/**/"Bootup"		,LangLibSolver.GetString(XParamGlobal_LS,LID_3)/*"Bootup"*/);
	SetCategoryLanguage(/**/"Operation"		,LangLibSolver.GetString(XParamGlobal_LS,LID_4)/*"Operation"*/);
	SetCategoryLanguage(/**/"PlugIn"		,LangLibSolver.GetString(XParamGlobal_LS,LID_5)/*"PlugIn"*/);
	SetCategoryLanguage(/**/"File"			,LangLibSolver.GetString(XParamGlobal_LS,LID_6)/*"File"*/);
	SetCategoryLanguage(/**/"Transfer"		,LangLibSolver.GetString(XParamGlobal_LS,LID_7)/*"Transfer"*/);
	SetCategoryLanguage(/**/"Execute"		,LangLibSolver.GetString(XParamGlobal_LS,LID_10)/*"Execute"*/);
	SetCategoryLanguage(/**/"ResultAnalizer",LangLibSolver.GetString(XParamGlobal_LS,LID_11)/*"ResultAnalizer"*/);
	SetCategoryLanguage(/**/"NetDrive"		,LangLibSolver.GetString(XParamGlobal_LS,LID_14)/*"NetDrive"*/);
	SetCategoryLanguage(/**/"Printer"		,LangLibSolver.GetString(XParamGlobal_LS,LID_15)/*"Printer"*/);
	SetCategoryLanguage(/**/"System"		,LangLibSolver.GetString(XParamGlobal_LS,LID_72)/*"System"*/);
	SetCategoryLanguage(/**/"Light"			,LangLibSolver.GetString(XParamGlobal_LS,LID_154)/*"Light"*/);
	SetCategoryLanguage(/**/"Log"			,LangLibSolver.GetString(XParamGlobal_LS,LID_155)/*"Log"*/);
	SetCategoryLanguage(/**/"Optimize"		,LangLibSolver.GetString(XParamGlobal_LS,LID_156)/*"Optimize"*/);
	SetCategoryLanguage(/**/"Image"			,LangLibSolver.GetString(XParamGlobal_LS,LID_157)/*"Image"*/);
	SetCategoryLanguage(/**/"Color"			,LangLibSolver.GetString(XParamGlobal_LS,LID_158)/*"Color"*/);
	SetCategoryLanguage(/**/"OtherColor"	,LangLibSolver.GetString(XParamGlobal_LS,LID_159)/*"OtherColor"*/);
	SetCategoryLanguage(/**/"LayerName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_160)/*"LayerName"*/);
	SetCategoryLanguage(/**/"PhaseName"		,LangLibSolver.GetString(XParamGlobal_LS,LID_161)/*"PhaseName"*/);
	SetCategoryLanguage(/**/"GeneralStocker",LangLibSolver.GetString(XParamGlobal_LS,LID_162)/*"GeneralStocker"*/);
	SetCategoryLanguage(/**/"Unit"			,LangLibSolver.GetString(XParamGlobal_LS,LID_163)/*"Unit"*/);
	SetCategoryLanguage(/**/"Learning"		,LangLibSolver.GetString(XParamGlobal_LS,LID_164)/*"Learning"*/);
	SetCategoryLanguage(/**/"Phase"			,LangLibSolver.GetString(XParamGlobal_LS,LID_165)/*"Phase"*/);
	SetCategoryLanguage(/**/"Integration"	,LangLibSolver.GetString(XParamGlobal_LS,LID_167)/*"Integration"*/);


	MaxScanStrategy	=1;	
	StrategyDim		=NULL;
	StrategyDimAllocNumb=0;

	CalcStrategyDim		=NULL;
	CalcStrategyDimAllocNumb=0;

	CamAllocInPagesDim	=NULL;
	CamAllocInPagesDimNumb=0;

	PDirData=NULL;
	PDirDataAllocNumb=0;

	ScanNumberInPhaseDim=NULL;
	ScanNumberInPhaseDimNumb=0;

	RemoteTransferListDim	=new RemoteTransferList[MaxRemoteTransferListDimNumb];
	RemoteTransferListDimNumb=0;
}

ParamGlobal::~ParamGlobal(void)
{
	if(StrategyDim!=NULL){
		delete	[]StrategyDim;
	}
	StrategyDim=NULL;

	if(CalcStrategyDim!=NULL){
		delete	[]CalcStrategyDim;
	}
	CalcStrategyDim=NULL;

	if(CamAllocInPagesDim!=NULL){
		delete	[]CamAllocInPagesDim;
	}
	CamAllocInPagesDim=NULL;

	if(PDirData!=NULL){
		delete	[]PDirData;
		PDirData=NULL;
	}
	PDirDataAllocNumb=0;

	if(ScanNumberInPhaseDim!=NULL){
		delete	[]ScanNumberInPhaseDim;
		ScanNumberInPhaseDim=NULL;
	}
	ScanNumberInPhaseDimNumb=0;

	if(RemoteTransferListDim!=NULL){
		delete	[]RemoteTransferListDim;
		RemoteTransferListDim=NULL;
	}
	RemoteTransferListDimNumb=0;

	if(PageLocalData!=NULL){
		delete	[]PageLocalData;
		PageLocalData=NULL;
		AllocatedCounfOfPageLocal=0;
	}
}

void	ParamGlobal::ReallocPageLocal(int AllocPageNumb)
{
	if(CountOfPageLocal!=AllocPageNumb){
		ParamGlobalEachPage	*iPageLocalData=new ParamGlobalEachPage[AllocPageNumb];
		for(int page=0;page<AllocPageNumb && page<CountOfPageLocal;page++){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			PageLocalData[page].SaveParam(&Buff,-1);
			Buff.seek(0);
			iPageLocalData[page].LoadParam(&Buff,-1);
		}
		if(PageLocalData!=NULL){
			delete	[]PageLocalData;
			PageLocalData=NULL;
		}
		CountOfPageLocal			=AllocPageNumb;
		AllocatedCounfOfPageLocal	=AllocPageNumb;
		PageLocalData=iPageLocalData;
	}
}

bool	ParamGlobal::IsValid(int page ,int layer)	const
{
	if(0<=page && page<PageNumb){
		if(page<CountOfPageLocal
		&& PageLocalData[page].UseEachPage==true){
			if(0<=layer && layer<PageLocalData[page].LayerNumb){
				return true;
			}
			return false;
		}
		else{
			if(0<=layer && layer<LayerNumb){
				return true;
			}
			return false;
		}
	}
	return false;
}

bool	ParamGlobal::WriteEnableToDefaultFile(void)
{
	if(GetLayersBase()->GetBootingLevel()==0 && GetLayersBase()->GetMasterType()==0){
		return true;
	}
	else{
		return false;
	}
}

int32	ParamGlobal::GetStrategyCode(int page ,int layer)
{	
	if(StrategyDim!=NULL){
		int	n=page*LayerNumb+layer;
		if(n<StrategyDimAllocNumb){
			return(StrategyDim[n]);
		}
		ReallocStrategy();
		return(StrategyDim[n]);
	}
	return(0);
}
void	ParamGlobal::SetStrategyCode(int page ,int layer ,int strategycode)
{
	if(StrategyDim!=NULL){
		int	n=page*LayerNumb+layer;
		if(n<StrategyDimAllocNumb){
			StrategyDim[n]=strategycode;
		}
		else{
			ReallocStrategy();
			StrategyDim[n]=strategycode;
		}
	}
	else{
		ReallocStrategy();
		int	n=page*LayerNumb+layer;
		StrategyDim[n]=strategycode;
	}
}

int32	ParamGlobal::GetCalcStrategyCode(int page ,int layer)
{	
	if(CalcStrategyDim!=NULL){
		int	n=page*LayerNumb+layer;
		if(n<CalcStrategyDimAllocNumb){
			return(CalcStrategyDim[n]);
		}
		ReallocStrategy();
		return(CalcStrategyDim[n]);
	}
	return(0);
}
void	ParamGlobal::SetCalcStrategyCode(int page ,int layer ,int strategycode)
{
	if(CalcStrategyDim!=NULL){
		int	n=page*LayerNumb+layer;
		if(n<CalcStrategyDimAllocNumb){
			CalcStrategyDim[n]=strategycode;
		}
		else{
			ReallocStrategy();
			CalcStrategyDim[n]=strategycode;
		}
	}
	else{
		ReallocStrategy();
		int	n=page*LayerNumb+layer;
		CalcStrategyDim[n]=strategycode;
	}
}

void	ParamGlobal::ReallocStrategy(void)
{
	if(StrategyDim!=NULL){
		int	n=PageNumb*LayerNumb;
		if(StrategyDimAllocNumb!=n){
			int32	*D=new int32[n];
			memset(D,0,sizeof(int32)*n);
			memcpy(D,StrategyDim,sizeof(int32)*min(n,StrategyDimAllocNumb));
			delete	[]StrategyDim;
			StrategyDim=D;
			StrategyDimAllocNumb=n;
		}
	}
	else{
		int	n=PageNumb*LayerNumb;
		StrategyDim=new int32[n];
		StrategyDimAllocNumb=n;
		memset(StrategyDim,0,sizeof(int32)*n);
	}
	if(CalcStrategyDim!=NULL){
		int	n=PageNumb*LayerNumb;
		if(CalcStrategyDimAllocNumb!=n){
			int32	*D=new int32[n];
			memset(D,0,sizeof(int32)*n);
			memcpy(D,CalcStrategyDim,sizeof(int32)*min(n,CalcStrategyDimAllocNumb));
			delete	[]CalcStrategyDim;
			CalcStrategyDim=D;
			CalcStrategyDimAllocNumb=n;
		}
	}
	else{
		int	n=PageNumb*LayerNumb;
		CalcStrategyDim=new int32[n];
		CalcStrategyDimAllocNumb=n;
		memset(CalcStrategyDim,0,sizeof(int32)*n);
	}
}

bool	ParamGlobal::SaveParam(QIODevice *f ,int EnableCondition)
{
	DataVersion=9;
	if(ParamBase::SaveParam(f,EnableCondition)==false){
		return false;
	}
	if(SaveStrategy(f ,EnableCondition)==false){
		return false;
	}
	if(SaveCameraAlloc(f ,EnableCondition)==false){
		return false;
	}
	if(SavePageDir(f ,EnableCondition)==false){
		return false;
	}
	if(SaveScanPhase(f ,EnableCondition)==false){
		return false;
	}
	QStringList	tThresholdLevelText;
	if(::Save(f,tThresholdLevelText)==false){
		return false;
	}
	if(::Save(f,MasterBuffNames)==false){
		return false;
	}
	if(::Save(f,PhaseNames)==false){
		return false;
	}
	for(int i=0;i<CountOfPageLocal;i++){
		if(PageLocalData[i].SaveParam(f,EnableCondition)==false){
			return false;
		}
	}

	return true;
}

bool	ParamGlobal::SaveStrategy(QIODevice *f ,int EnableCondition)
{
	if(EnableCondition==ParamEnableDefault
	|| EnableCondition==ParamEnableInAll){
		if(f->write((const char *)&MaxScanStrategy,sizeof(MaxScanStrategy))!=sizeof(MaxScanStrategy)){
			return(false);
		}
		bool	StrategyDimExist;
		if(StrategyDim!=NULL){
			StrategyDimExist=true;
			if(f->write((const char *)&StrategyDimExist,sizeof(StrategyDimExist))!=sizeof(StrategyDimExist)){
				return(false);
			}
			if(f->write((const char *)&StrategyDimAllocNumb,sizeof(StrategyDimAllocNumb))!=sizeof(StrategyDimAllocNumb)){
				return(false);
			}
			if(f->write((const char *)StrategyDim,sizeof(int32)*StrategyDimAllocNumb)!=sizeof(int32)*StrategyDimAllocNumb){
				return(false);
			}
		}
		else{
			StrategyDimExist=false;
			if(f->write((const char *)&StrategyDimExist,sizeof(StrategyDimExist))!=sizeof(StrategyDimExist)){
				return(false);
			}
		}
		bool	CalcStrategyDimExist;
		if(CalcStrategyDim!=NULL){
			CalcStrategyDimExist=true;
			if(f->write((const char *)&CalcStrategyDimExist,sizeof(CalcStrategyDimExist))!=sizeof(CalcStrategyDimExist)){
				return(false);
			}
			if(f->write((const char *)&CalcStrategyDimAllocNumb,sizeof(CalcStrategyDimAllocNumb))!=sizeof(CalcStrategyDimAllocNumb)){
				return(false);
			}
			if(f->write((const char *)CalcStrategyDim,sizeof(int32)*CalcStrategyDimAllocNumb)!=sizeof(int32)*CalcStrategyDimAllocNumb){
				return(false);
			}
		}
		else{
			CalcStrategyDimExist=false;
			if(f->write((const char *)&CalcStrategyDimExist,sizeof(CalcStrategyDimExist))!=sizeof(CalcStrategyDimExist)){
				return(false);
			}
		}
	}
	return true;
}

bool	ParamGlobal::SaveCameraAlloc(QIODevice *f ,int EnableCondition)
{
	if(EnableCondition==ParamEnableDefault
	|| EnableCondition==ParamEnableInAll){
		bool	CamAllocInPagesDimExist;
		if(CamAllocInPagesDim!=NULL){
			CamAllocInPagesDimExist=true;
			if(f->write((const char *)&CamAllocInPagesDimExist,sizeof(CamAllocInPagesDimExist))!=sizeof(CamAllocInPagesDimExist)){
				return(false);
			}
			if(f->write((const char *)&CamAllocInPagesDimNumb,sizeof(CamAllocInPagesDimNumb))!=sizeof(CamAllocInPagesDimNumb)){
				return(false);
			}
			if(f->write((const char *)CamAllocInPagesDim,sizeof(int32)*CamAllocInPagesDimNumb)!=sizeof(int32)*CamAllocInPagesDimNumb){
				return(false);
			}
		}
		else{
			CamAllocInPagesDimExist=false;
			if(f->write((const char *)&CamAllocInPagesDimExist,sizeof(CamAllocInPagesDimExist))!=sizeof(CamAllocInPagesDimExist)){
				return(false);
			}
		}
		if(::Save(f,FilterBankFileNames)==false){
			return false;
		}
	}
	return true;
}
bool	ParamGlobal::SavePageDir(QIODevice *f ,int EnableCondition)
{
	if(EnableCondition==ParamEnableDefault
	|| EnableCondition==ParamEnableInAll){
		if(::Save(f,PDirDataAllocNumb)==false){
			return false;
		}
		for(int page=0;page<PDirDataAllocNumb;page++){
			if(PDirData[page].Save(f)==false){
				return false;
			}
		}
	}
			
	return true;
}
bool	ParamGlobal::LoadPageDir(QIODevice *f ,int EnableCondition)
{
	if(EnableCondition==ParamEnableDefault
	|| EnableCondition==ParamEnableInAll){
		GetLayersBase()->LockWChangingDataStructure();
		if(DataVersion>=3){
			if(PDirData!=NULL){
				delete	[]PDirData;
				PDirData=NULL;
			}
			int32	iPDirDataAllocNumb;
			if(::Load(f,iPDirDataAllocNumb)==false){
				GetLayersBase()->UnlockChangingDataStructure();
				return false;
			}
			PDirDataAllocNumb=PageNumb;
			if(PDirDataAllocNumb>0){
				PDirData=new PageDirection[PDirDataAllocNumb];
				for(int page=0;page<PDirDataAllocNumb && page<iPDirDataAllocNumb;page++){
					if(PDirData[page].Load(f)==false){
						GetLayersBase()->UnlockChangingDataStructure();
						return false;
					}
				}
				for(int page=PDirDataAllocNumb;page<iPDirDataAllocNumb;page++){
					PageDirection	Dummy;
					if(Dummy.Load(f)==false){
						GetLayersBase()->UnlockChangingDataStructure();
						return false;
					}
				}

			}
		}
		GetLayersBase()->UnlockChangingDataStructure();
	}
	else{
		if(DataVersion>=3){
			int32	iPDirDataAllocNumb;
			if(::Load(f,iPDirDataAllocNumb)==false){
				return false;
			}
			for(int page=0;page<iPDirDataAllocNumb;page++){
				PageDirection	Dummy;
				if(Dummy.Load(f)==false){
					return false;
				}

			}
		}
	}

	return(true);
}
bool	ParamGlobal::LoadParam(QIODevice *f ,int EnableCondition)
{
	if(ParamBase::LoadParam(f,EnableCondition)==false){
		return(false);
	}
	if(LoadStrategy(f ,EnableCondition)==false){
		return(false);
	}
	if(LoadCameraAlloc(f ,EnableCondition)==false){
		return(false);
	}
	if(LoadPageDir(f ,EnableCondition)==false){
		return false;
	}
	if(DataVersion>=4){
		if(LoadScanPhase(f ,EnableCondition)==false){
			return false;
		}
	}
	if(DataVersion>=6){
		if(EnableCondition==ParamEnableDefault
		|| EnableCondition==ParamEnableInAll
		|| EnableCondition==ParamEnableInTransfer){
			QStringList	tThresholdLevelText;
			if(::Load(f,tThresholdLevelText)==false){
				return false;
			}
		}
		else{
			QStringList	tThresholdLevelText;
			if(::Load(f,tThresholdLevelText)==false){
				return false;
			}
		}
	}
	if(DataVersion>=7){
		if(::Load(f,MasterBuffNames)==false){
			return false;
		}
	}
	if(DataVersion>=8){
		if(::Load(f,PhaseNames)==false){
			return false;
		}
	}
	if(DataVersion>=9){
		if(PageLocalData!=NULL){
			delete	[]PageLocalData;
			PageLocalData=NULL;
		}
		AllocatedCounfOfPageLocal=CountOfPageLocal;
		PageLocalData=new ParamGlobalEachPage[AllocatedCounfOfPageLocal];
		for(int i=0;i<CountOfPageLocal;i++){
			if(PageLocalData[i].LoadParam(f,EnableCondition)==false){
				return false;
			}
		}
	}

	QFile	File(ShadowTreeDefFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(ShadowParameterData.Load(&File)==false){
			return false;
		}
	}
	return true;
}

bool	ParamGlobal::LoadStrategy(QIODevice *f ,int EnableCondition)
{
	if(EnableCondition==ParamEnableDefault
	|| EnableCondition==ParamEnableInAll){
		if(f->read((char *)&MaxScanStrategy,sizeof(MaxScanStrategy))!=sizeof(MaxScanStrategy)){
			return(false);
		}
		bool	StrategyDimExist;
		if(f->read((char *)&StrategyDimExist,sizeof(StrategyDimExist))!=sizeof(StrategyDimExist)){
			return(false);
		}
		if(StrategyDimExist==true){
			int32	iStrategyDimAllocNumb;
			if(f->read((char *)&iStrategyDimAllocNumb,sizeof(iStrategyDimAllocNumb))!=sizeof(iStrategyDimAllocNumb)){
				return(false);
			}
			if(StrategyDimAllocNumb!=iStrategyDimAllocNumb){
				StrategyDimAllocNumb=iStrategyDimAllocNumb;
				if(StrategyDim!=NULL){
					//_CrtCheckMemory();
					delete	[]StrategyDim;
					//_CrtCheckMemory();
				}
				StrategyDim=new int32[StrategyDimAllocNumb];
				memset(StrategyDim,0,sizeof(int32)*StrategyDimAllocNumb);
			}
			if(f->read((char *)StrategyDim,sizeof(int32)*StrategyDimAllocNumb)!=sizeof(int32)*StrategyDimAllocNumb){
				return(false);
			}
		}
		else{
			if(StrategyDim!=NULL){
				delete	[]StrategyDim;
			}
			StrategyDim=NULL;
			StrategyDimAllocNumb=0;
		}

		if(DataVersion>=5){
			bool	CalcStrategyDimExist;
			if(f->read((char *)&CalcStrategyDimExist,sizeof(CalcStrategyDimExist))!=sizeof(CalcStrategyDimExist)){
				return(false);
			}
			if(CalcStrategyDimExist==true){
				int32	iCalcStrategyDimAllocNumb;
				if(f->read((char *)&iCalcStrategyDimAllocNumb,sizeof(iCalcStrategyDimAllocNumb))!=sizeof(iCalcStrategyDimAllocNumb)){
					return(false);
				}
				if(CalcStrategyDimAllocNumb!=iCalcStrategyDimAllocNumb){
					CalcStrategyDimAllocNumb=iCalcStrategyDimAllocNumb;
					if(CalcStrategyDim!=NULL){
						//_CrtCheckMemory();
						delete	[]CalcStrategyDim;
						//_CrtCheckMemory();
					}
					CalcStrategyDim=new int32[CalcStrategyDimAllocNumb];
					memset(CalcStrategyDim,0,sizeof(int32)*CalcStrategyDimAllocNumb);
				}
				if(f->read((char *)CalcStrategyDim,sizeof(int32)*CalcStrategyDimAllocNumb)!=sizeof(int32)*CalcStrategyDimAllocNumb){
					return(false);
				}
			}
			else{
				if(CalcStrategyDim!=NULL){
					delete	[]CalcStrategyDim;
				}
				CalcStrategyDim=NULL;
				CalcStrategyDimAllocNumb=0;
			}
		}
		else{
			if(StrategyDim==NULL){
				if(CalcStrategyDim!=NULL){
					delete	[]CalcStrategyDim;
					CalcStrategyDim=NULL;
					CalcStrategyDimAllocNumb=0;
				}
			}
			else{
				CalcStrategyDimAllocNumb=StrategyDimAllocNumb;
				if(CalcStrategyDim!=NULL){
					delete	[]CalcStrategyDim;
					CalcStrategyDim=NULL;
				}
				int32	*D=new int32[CalcStrategyDimAllocNumb];
				memset(D,0,sizeof(int32)*CalcStrategyDimAllocNumb);
				CalcStrategyDim=D;
				memcpy(CalcStrategyDim,StrategyDim,sizeof(int32)*CalcStrategyDimAllocNumb);
			}
		}
	}
	else{
		int32	iMaxScanStrategy;
		if(f->read((char *)&iMaxScanStrategy,sizeof(iMaxScanStrategy))!=sizeof(iMaxScanStrategy)){
			return(false);
		}
		bool	StrategyDimExist;
		if(f->read((char *)&StrategyDimExist,sizeof(StrategyDimExist))!=sizeof(StrategyDimExist)){
			return(false);
		}
		if(StrategyDimExist==true){
			int32	iStrategyDimAllocNumb;
			if(f->read((char *)&iStrategyDimAllocNumb,sizeof(iStrategyDimAllocNumb))!=sizeof(iStrategyDimAllocNumb)){
				return(false);
			}
			int32	*iStrategyDim=new int32[iStrategyDimAllocNumb];

			if(f->read((char *)iStrategyDim,sizeof(int32)*iStrategyDimAllocNumb)!=sizeof(int32)*iStrategyDimAllocNumb){
				return(false);
			}
			delete	[]iStrategyDim;
		}

		if(DataVersion>=5){
			bool	CalcStrategyDimExist;
			if(f->read((char *)&CalcStrategyDimExist,sizeof(CalcStrategyDimExist))!=sizeof(CalcStrategyDimExist)){
				return(false);
			}
			if(CalcStrategyDimExist==true){
				int32	iCalcStrategyDimAllocNumb;
				if(f->read((char *)&iCalcStrategyDimAllocNumb,sizeof(iCalcStrategyDimAllocNumb))!=sizeof(iCalcStrategyDimAllocNumb)){
					return(false);
				}
				int32	*iCalcStrategyDim=new int32[iCalcStrategyDimAllocNumb];

				if(f->read((char *)iCalcStrategyDim,sizeof(int32)*iCalcStrategyDimAllocNumb)!=sizeof(int32)*iCalcStrategyDimAllocNumb){
					return(false);
				}
				delete	[]iCalcStrategyDim;
			}
		}
	}
	return true;
}

bool	ParamGlobal::LoadCameraAlloc(QIODevice *f ,int EnableCondition)
{
	if(EnableCondition==ParamEnableDefault
	|| EnableCondition==ParamEnableInAll){
		bool	CamAllocInPagesDimExist;
		if(f->read((char *)&CamAllocInPagesDimExist,sizeof(CamAllocInPagesDimExist))!=sizeof(CamAllocInPagesDimExist)){
			return(false);
		}
		if(CamAllocInPagesDimExist==true){
			int32	iCamAllocInPagesDimNumb;
			if(f->read((char *)&iCamAllocInPagesDimNumb,sizeof(iCamAllocInPagesDimNumb))!=sizeof(iCamAllocInPagesDimNumb)){
				return(false);
			}
			if(iCamAllocInPagesDimNumb<PageNumb){
				iCamAllocInPagesDimNumb=PageNumb;
			}
			if(CamAllocInPagesDimNumb!=iCamAllocInPagesDimNumb){
				CamAllocInPagesDimNumb=iCamAllocInPagesDimNumb;
				if(CamAllocInPagesDim!=NULL){
					delete	[]CamAllocInPagesDim;
				}
				CamAllocInPagesDim=new int32[CamAllocInPagesDimNumb];
				memset(CamAllocInPagesDim,0,sizeof(int32)*CamAllocInPagesDimNumb);
			}
			if(f->read((char *)CamAllocInPagesDim,sizeof(int32)*CamAllocInPagesDimNumb)!=sizeof(int32)*CamAllocInPagesDimNumb){
				return(false);
			}
		}
		else{
			if(CamAllocInPagesDim!=NULL){
				delete	[]CamAllocInPagesDim;
			}
			CamAllocInPagesDim=NULL;
			CamAllocInPagesDimNumb=0;
		}
		if(DataVersion>=2){
			if(::Load(f,FilterBankFileNames)==false){
				return false;
			}
		}
	}
	else{
		bool	CamAllocInPagesDimExist;
		if(f->read((char *)&CamAllocInPagesDimExist,sizeof(CamAllocInPagesDimExist))!=sizeof(CamAllocInPagesDimExist)){
			return(false);
		}
		if(CamAllocInPagesDimExist==true){
			int32	iCamAllocInPagesDimNumb;
			if(f->read((char *)&iCamAllocInPagesDimNumb,sizeof(iCamAllocInPagesDimNumb))!=sizeof(iCamAllocInPagesDimNumb)){
				return(false);
			}
			if(iCamAllocInPagesDimNumb<PageNumb){
				iCamAllocInPagesDimNumb=PageNumb;
			}
			int32	*iCamAllocInPagesDim=new int32[iCamAllocInPagesDimNumb];

			if(f->read((char *)iCamAllocInPagesDim,sizeof(int32)*iCamAllocInPagesDimNumb)!=sizeof(int32)*iCamAllocInPagesDimNumb){
				delete	[]iCamAllocInPagesDim;
				return(false);
			}
			delete	[]iCamAllocInPagesDim;
		}

		if(DataVersion>=2){
			QStringList	iFilterBankFileNames;
			if(::Load(f,iFilterBankFileNames)==false){
				return false;
			}
		}
	}
	return true;
}



void	ParamGlobal::ReallocCamAllocInPages(void)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(CamAllocInPagesDim!=NULL){
			if(CamAllocInPagesDimNumb!=PageNumb){
				int32	*D=new int32[PageNumb];
				memset(D,0,sizeof(int32)*PageNumb);
				memcpy(D,CamAllocInPagesDim,sizeof(int32)*min(CamAllocInPagesDimNumb,PageNumb));
				delete	[]CamAllocInPagesDim;
				CamAllocInPagesDim=D;
				CamAllocInPagesDimNumb=PageNumb;
				for(int k=0;k<CamAllocInPagesDimNumb;k++){
					if(CamAllocInPagesDim[k]<0){
						for(int i=0;i<TotalCameraNumb;i++){
							bool	Found=false;
							for(int t=0;t<CamAllocInPagesDimNumb;t++){
								if(i==CamAllocInPagesDim[t]){
									Found=true;
									break;
								}
							}
							if(Found==false){
								CamAllocInPagesDim[k]=i;
								break;
							}
						}
					}
				}
			}
		}
		else{
			CamAllocInPagesDim=new int32[PageNumb];
			memset(CamAllocInPagesDim,0,sizeof(int32)*PageNumb);
			CamAllocInPagesDimNumb=PageNumb;
			if(PageNumb==TotalCameraNumb){
				for(int i=0;i<PageNumb;i++){
					SetCameraNo(i,i);
				}
			}
			else{
				memset(CamAllocInPagesDim,0,sizeof(int32)*CamAllocInPagesDimNumb);
			}
		}
	}
}
int32	ParamGlobal::GetCameraNo(int page)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(CamAllocInPagesDim==NULL){
			ReallocCamAllocInPages();
		}
		if(CamAllocInPagesDim!=NULL){
			if(CamAllocInPagesDimNumb>page){
				if(0<=CamAllocInPagesDim[page] && CamAllocInPagesDim[page]<TotalCameraNumb){
					return(CamAllocInPagesDim[page]);
				}
				return page;
			}
		}
		return(-1);
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetCameraNo(page);
	}
}
void	ParamGlobal::SetCameraNo(int page ,int32 CamNo)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(TotalCameraNumb<=CamNo){
			CamNo=TotalCameraNumb-1;
		}

		if(CamAllocInPagesDim!=NULL){
			if(CamAllocInPagesDimNumb>page){
				CamAllocInPagesDim[page]=CamNo;
			}
			else{
				int32	*tCamAllocInPagesDim=new int32[CamAllocInPagesDimNumb];
				for(int i=0;i<CamAllocInPagesDimNumb;i++){
					tCamAllocInPagesDim[i]=CamAllocInPagesDim[i];
				}
				delete	[]CamAllocInPagesDim;
				CamAllocInPagesDim=new int32[max(PageNumb,CamNo+1)];
				memset(CamAllocInPagesDim,0,sizeof(int32)*max(PageNumb,CamNo+1));
				for(int i=0;i<CamAllocInPagesDimNumb;i++){
					CamAllocInPagesDim[i]=tCamAllocInPagesDim[i];
				}
				CamAllocInPagesDimNumb=max(PageNumb,CamNo+1);
				CamAllocInPagesDim[page]=CamNo;
				delete	[]tCamAllocInPagesDim;
			}
		}
	}
}
bool	ParamGlobal::GetPageListFromCameraNo(int CamNo ,IntList &PageList)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		bool	Ret=false;
		PageList.RemoveAll();
		if(CamAllocInPagesDim==NULL){
			ReallocCamAllocInPages();
		}
		for(int page=0;page<GetPageNumb();page++){
			if(CamAllocInPagesDim[page]==CamNo){
				PageList.Add(page);
				Ret=true;
			}
		}
		return Ret;
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetPageListFromCameraNo(CamNo ,PageList);
	}
}
int		ParamGlobal::GetDotPerLineInCamera(int32 CamNo)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		IntList PageList;
		if(GetPageListFromCameraNo(CamNo ,PageList)==true){
			int	iDotPerLine=0;
			for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
				int	Page=c->GetValue();
				DataInPage	*Dp=GetLayersBase()->GetPageData(Page);
				iDotPerLine=max(iDotPerLine,Dp->GetDotPerLine());
			}
			return iDotPerLine;
		}
		return DotPerLine;
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetDotPerLineInCamera(CamNo);
	}
}
int		ParamGlobal::GetMaxLinesInCamera(int32 CamNo)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		IntList PageList;
		if(GetPageListFromCameraNo(CamNo ,PageList)==true){
			int	iMaxLines=0;
			for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
				int	Page=c->GetValue();
				DataInPage	*Dp=GetLayersBase()->GetPageData(Page);
				iMaxLines=max(iMaxLines,Dp->GetMaxLines());
			}
			return iMaxLines;
		}
		return MaxLines;
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetMaxLinesInCamera(CamNo);
	}
}
void	ParamGlobal::ReallocScanPhase(void)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(ScanNumberInPhaseDim!=NULL){
			if(ScanNumberInPhaseDimNumb!=PhaseNumb){
				int32	*D=new int32[PhaseNumb];
				memset(D,0,sizeof(int32)*PhaseNumb);
				memcpy(D,ScanNumberInPhaseDim,sizeof(int32)*min(ScanNumberInPhaseDimNumb,PhaseNumb));
				delete	[]ScanNumberInPhaseDim;
				ScanNumberInPhaseDim=D;
				ScanNumberInPhaseDimNumb=PhaseNumb;
			}
		}
		else{
			ScanNumberInPhaseDim=new int32[PhaseNumb];
			ScanNumberInPhaseDimNumb=PhaseNumb;
			for(int i=0;i<PhaseNumb;i++){
				ScanNumberInPhaseDim[i]=i;
			}
		}
	}
}


int		ParamGlobal::GetScanPhaseCount(void)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(ScanNumberInPhaseDim==NULL){
			ReallocScanPhase();
		}
		IntList	PCounts;
		for(int phase=0;phase<ScanNumberInPhaseDimNumb && phase<GetPhaseNumb();phase++){
			if(PCounts.IsInclude(ScanNumberInPhaseDim[phase])==false){
				PCounts.Add(ScanNumberInPhaseDim[phase]);
			}
		}
		return PCounts.GetCount();
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetScanPhaseCount();
	}
}
int		ParamGlobal::GetScanNumberInPhase(int phase)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(ScanNumberInPhaseDim==NULL){
			ReallocScanPhase();
		}
		if(0<=phase && phase<ScanNumberInPhaseDimNumb && phase<GetPhaseNumb()){
			return ScanNumberInPhaseDim[phase];
		}
		return 0;
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetScanNumberInPhase(phase);
	}
}
void	ParamGlobal::GetPhaseNumber(IntList &PNumber ,int PhaseScanNumber)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(UseScanPhaseNumber==true){
			if(ScanNumberInPhaseDim==NULL){
				ReallocScanPhase();
			}
			for(int phase=0;phase<ScanNumberInPhaseDimNumb && phase<GetPhaseNumb();phase++){
				if(ScanNumberInPhaseDim[phase]==PhaseScanNumber){
					PNumber.Add(phase);
				}
			}
		}
		else{
			PNumber.Add(GetLayersBase()->GetCurrentPhase());
		}
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetPhaseNumber(PNumber,PhaseScanNumber);
	}
}
void	ParamGlobal::GetScanPhaseFromPhase(int phase ,int &RetScanPhaseNumbers)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(ScanNumberInPhaseDim==NULL){
			ReallocScanPhase();
		}
		if(0<=phase && phase<GetPhaseNumb() && phase<ScanNumberInPhaseDimNumb){
			RetScanPhaseNumbers=ScanNumberInPhaseDim[phase];
		}
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetScanPhaseFromPhase(phase,RetScanPhaseNumbers);
	}
}
void	ParamGlobal::SetScanPhaseNumber(int phase , int ScanNumber)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(ScanNumberInPhaseDim==NULL){
			ReallocScanPhase();
		}
		if(0<=phase && phase<ScanNumberInPhaseDimNumb){
			ScanNumberInPhaseDim[phase]=ScanNumber;
		}
	}
}
bool	ParamGlobal::SaveScanPhase(QIODevice *f ,int EnableCondition)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		if(EnableCondition==0 || EnableCondition==-1 || EnableCondition==1){
			if(ScanNumberInPhaseDim==NULL){
				ReallocScanPhase();
			}
			if(::Save(f,ScanNumberInPhaseDimNumb)==false){
				return false;
			}
			for(int phase=0;phase<ScanNumberInPhaseDimNumb;phase++){
				if(::Save(f,ScanNumberInPhaseDim[phase])==false){
					return false;
				}
			}
		}
		return true;
	}
	return true;
}

bool	ParamGlobal::LoadScanPhase(QIODevice *f ,int EnableCondition)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		int32	tScanNumberInPhaseDimNumb;

		if(EnableCondition==ParamEnableDefault
		|| EnableCondition==ParamEnableInAll
		|| EnableCondition==ParamEnableInTransfer){
			if(::Load(f,tScanNumberInPhaseDimNumb)==false){
				return false;
			}
			tScanNumberInPhaseDimNumb=Clipping(tScanNumberInPhaseDimNumb,0,1000);
			if(ScanNumberInPhaseDimNumb>=tScanNumberInPhaseDimNumb){
				ScanNumberInPhaseDimNumb=tScanNumberInPhaseDimNumb;
				for(int phase=0;phase<ScanNumberInPhaseDimNumb;phase++){
					if(::Load(f,ScanNumberInPhaseDim[phase])==false){
						return false;
					}
					if(ScanNumberInPhaseDim[phase]<0 || ScanNumberInPhaseDim[phase]>=PhaseNumb){
						ScanNumberInPhaseDim[phase]=phase;
					}
				}
			}
			else{
				if(ScanNumberInPhaseDim!=NULL){
					delete	[]ScanNumberInPhaseDim;
				}
				ScanNumberInPhaseDimNumb=tScanNumberInPhaseDimNumb;
				ScanNumberInPhaseDim=new int32[ScanNumberInPhaseDimNumb];
				for(int phase=0;phase<ScanNumberInPhaseDimNumb;phase++){
					if(::Load(f,ScanNumberInPhaseDim[phase])==false){
						return false;
					}
					if(ScanNumberInPhaseDim[phase]<0 || ScanNumberInPhaseDim[phase]>=PhaseNumb){
						ScanNumberInPhaseDim[phase]=phase;
					}
				}
			}
			ReallocScanPhase();
		}
		else{
			if(::Load(f,tScanNumberInPhaseDimNumb)==false){
				return false;
			}
			for(int phase=0;phase<tScanNumberInPhaseDimNumb;phase++){
				int32	tmp;
				if(::Load(f,tmp)==false){
					return false;
				}
			}
		}
		return true;
	}
	return true;
}
int		ParamGlobal::GetScanNumberInPhaseDimNumb(void)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		return ScanNumberInPhaseDimNumb;
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetScanNumberInPhaseDimNumb();
	}
}

QColor	ParamGlobal::GetOneLayerColor(int Layer)
{
	switch(Layer%8){
		case 0:	return Layer0Color;
		case 1:	return Layer1Color;
		case 2:	return Layer2Color;
		case 3:	return Layer3Color;
		case 4:	return Layer4Color;
		case 5:	return Layer5Color;
		case 6:	return Layer6Color;
		case 7:	return Layer7Color;
	}
	return Qt::black;
}
QColor	ParamGlobal::GetOneGraphLayerColor(int Layer)
{
	switch(Layer%8){
		case 0:	return GraphLayer0Color;
		case 1:	return GraphLayer1Color;
		case 2:	return GraphLayer2Color;
		case 3:	return GraphLayer3Color;
		case 4:	return GraphLayer4Color;
		case 5:	return GraphLayer5Color;
		case 6:	return GraphLayer6Color;
		case 7:	return GraphLayer7Color;
	}
	return Qt::black;
}

QString	ParamGlobal::GetLayerName(int layer)
{
	switch(layer%8){
		case 0:	return Layer0String;
		case 1:	return Layer1String;
		case 2:	return Layer2String;
		case 3:	return Layer3String;
		case 4:	return Layer4String;
		case 5:	return Layer5String;
		case 6:	return Layer6String;
		case 7:	return Layer7String;
	}
	return /**/"";
}
QString	ParamGlobal::GetPhaseString(int phase)
{
	if(phase<8){
		switch(phase){
			case 0:	return Phase0String;
			case 1:	return Phase1String;
			case 2:	return Phase2String;
			case 3:	return Phase3String;
			case 4:	return Phase4String;
			case 5:	return Phase5String;
			case 6:	return Phase6String;
			case 7:	return Phase7String;
		}
	}
	else{
		int	n=phase-8;
		if(0<=n && n<PhaseNames.count()){
			return PhaseNames[n];
		}
	}
	return /**/"";
}
void	ParamGlobal::SetPhaseString(int phase ,QString &str)
{
	if(phase<8){
		switch(phase){
			case 0:	Phase0String=str;	break;
			case 1:	Phase1String=str;	break;
			case 2:	Phase2String=str;	break;
			case 3:	Phase3String=str;	break;
			case 4:	Phase4String=str;	break;
			case 5:	Phase5String=str;	break;
			case 6:	Phase6String=str;	break;
			case 7:	Phase7String=str;	break;
		}
	}
	else{
		int	n=phase-8;
		while(PhaseNames.count()<=n){
			PhaseNames.append(/**/"");
		}
		PhaseNames[n]=str;
	}
}

void	ParamGlobal::InitializeNetworkDrive(void)
{
	if(NetworkDrive1.length()!=0 && NetworkDrivePath1.length()!=0){
		char	NetworkDriveBuff[100];
		QString2Char(NetworkDrive1,NetworkDriveBuff,sizeof(NetworkDriveBuff));
		if(CreateNetworkDrive(false
							,NetworkDriveBuff[0]-'A'
							,NetworkDrivePath1
							,/**/""
							,/**/"")==true){
			GSleep(5000);
		}
	}
	if(NetworkDrive2.length()!=0 && NetworkDrivePath2.length()!=0){
		char	NetworkDriveBuff[100];
		QString2Char(NetworkDrive2,NetworkDriveBuff,sizeof(NetworkDriveBuff));
		if(CreateNetworkDrive(false
							,NetworkDriveBuff[0]-'A'
							,NetworkDrivePath2
							,/**/""
							,/**/"")==true){
			GSleep(5000);
		}
	}
	if(NetworkDrive3.length()!=0 && NetworkDrivePath3.length()!=0){
		char	NetworkDriveBuff[100];
		QString2Char(NetworkDrive3,NetworkDriveBuff,sizeof(NetworkDriveBuff));
		if(CreateNetworkDrive(false
							,NetworkDriveBuff[0]-'A'
							,NetworkDrivePath3
							,/**/""
							,/**/"")==true){
			GSleep(5000);
		}
	}
	if(NetworkDrive4.length()!=0 && NetworkDrivePath4.length()!=0){
		char	NetworkDriveBuff[100];
		QString2Char(NetworkDrive4,NetworkDriveBuff,sizeof(NetworkDriveBuff));
		if(CreateNetworkDrive(false
							,NetworkDriveBuff[0]-'A'
							,NetworkDrivePath4
							,/**/""
							,/**/"")==true){
			GSleep(5000);
		}
	}
}

bool	ParamGlobal::CheckAndRefer(ParamGlobal &MasterSrcParam)
{
	if(DotPerLine!=MasterSrcParam.DotPerLine){
		DotPerLine=MasterSrcParam.DotPerLine;
		return false;
	}
	if(MaxLines!=MasterSrcParam.MaxLines){
		MaxLines=MasterSrcParam.MaxLines;
		return false;
	}
	/*
	if(PageNumb!=MasterSrcParam.PageNumb){
		PageNumb=MasterSrcParam.PageNumb;
		return false;
	}
	*/
	if(LayerNumb!=MasterSrcParam.LayerNumb){
		LayerNumb=MasterSrcParam.LayerNumb;
		return false;
	}
	if(TotalCameraNumb!=MasterSrcParam.TotalCameraNumb){
		TotalCameraNumb=MasterSrcParam.TotalCameraNumb;
		return false;
	}
	if(MaxInspectMilisec!=MasterSrcParam.MaxInspectMilisec){
		MaxInspectMilisec=MasterSrcParam.MaxInspectMilisec;
		return true;
	}
	if(NGCacheNumb!=MasterSrcParam.NGCacheNumb){
		NGCacheNumb=MasterSrcParam.NGCacheNumb;
		return false;
	}
	if(ResolutionXNano!=MasterSrcParam.ResolutionXNano){
		ResolutionXNano=MasterSrcParam.ResolutionXNano;
		return true;
	}
	if(ResolutionYNano!=MasterSrcParam.ResolutionYNano){
		ResolutionYNano=MasterSrcParam.ResolutionYNano;
		return true;
	}
	if(CameraResolutionBit!=MasterSrcParam.CameraResolutionBit){
		CameraResolutionBit=MasterSrcParam.CameraResolutionBit;
		return true;
	}
	if(MaxNGCountsPerCam!=MasterSrcParam.MaxNGCountsPerCam){
		MaxNGCountsPerCam=MasterSrcParam.MaxNGCountsPerCam;
		return true;
	}
	if(MaxHistoryCounts!=MasterSrcParam.MaxHistoryCounts){
		MaxHistoryCounts=MasterSrcParam.MaxHistoryCounts;
		return true;
	}
	if(CaptureInBackground!=MasterSrcParam.CaptureInBackground){
		CaptureInBackground=MasterSrcParam.CaptureInBackground;
		return true;
	}
	if(AllocateMasterBuff!=MasterSrcParam.AllocateMasterBuff){
		AllocateMasterBuff=MasterSrcParam.AllocateMasterBuff;
		return false;
	}
	if(AllocatedCountMasterBuff!=MasterSrcParam.AllocatedCountMasterBuff){
		AllocatedCountMasterBuff=MasterSrcParam.AllocatedCountMasterBuff;
		return false;
	}
	if(AllocateTargetBuff!=MasterSrcParam.AllocateTargetBuff){
		AllocateTargetBuff=MasterSrcParam.AllocateTargetBuff;
		return false;
	}
	if(TopOfID!=MasterSrcParam.TopOfID){
		TopOfID=MasterSrcParam.TopOfID;
		return true;
	}
	if(NGMarkRadius!=MasterSrcParam.NGMarkRadius){
		NGMarkRadius=MasterSrcParam.NGMarkRadius;
		return true;
	}
	if(MaxNGImageNumbPerPage!=MasterSrcParam.MaxNGImageNumbPerPage){
		MaxNGImageNumbPerPage=MasterSrcParam.MaxNGImageNumbPerPage;
		return true;
	}
	if(MaxWaitingCommMilisec!=MasterSrcParam.MaxWaitingCommMilisec){
		MaxWaitingCommMilisec=MasterSrcParam.MaxWaitingCommMilisec;
		return true;
	}
	if(BufferedProcessing!=MasterSrcParam.BufferedProcessing){
		BufferedProcessing=MasterSrcParam.BufferedProcessing;
		return true;
	}
	if(CalcSingleThread!=MasterSrcParam.CalcSingleThread){
		CalcSingleThread=MasterSrcParam.CalcSingleThread;
		return true;
	}
	return true;
}

void	ParamGlobal::CopyStrategyFrom(ParamGlobal &src)
{
	if(&src==this){
		return;
	}
	QBuffer	F;
	F.open(QIODevice::ReadWrite);
	src.SaveStrategy(&F);
	src.SaveCameraAlloc(&F);
	F.seek(0);
	LoadStrategy(&F);
	LoadCameraAlloc(&F);
}
int		ParamGlobal::GetMaxScanStrategy(void)
{	
	if(GetLayersBase()->GetShadowLevel()==0){
		return(MaxScanStrategy);
	}
	else{
		return GetTreeTopLayersBase()->GetParamGlobal()->GetMaxScanStrategy();
	}
}
void	ParamGlobal::GetStrategy(int strategycode ,StrategicListContainer &SList)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		for(int page=0;page<PageNumb;page++){
			int	n=page*LayerNumb;
			if(n<StrategyDimAllocNumb){
				for(int L=0;L<LayerNumb;L++){
					if(StrategyDim[n+L]==strategycode){
						StrategicList	*s=new StrategicList();
						s->Page=page;
						s->Layer=L;
						SList.AppendList(s);
					}
				}
			}
		}
	}
	else{
		GetTreeTopLayersBase()->GetParamGlobal()->GetStrategy(strategycode ,SList);
	}
}

void	ParamGlobal::GetStrategyPage (int strategycode ,IntList &PageList)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		for(int page=0;page<PageNumb;page++){
			for(int layer=0;layer<LayerNumb;layer++){
				int	n=page*LayerNumb+layer;
				if(n<StrategyDimAllocNumb){
					if(StrategyDim[n]==strategycode){
						PageList.Add(page);
						goto	PNext;
					}
				}
			}
	PNext:;
		}
	}
	else{
		GetTreeTopLayersBase()->GetParamGlobal()->GetStrategyPage(strategycode ,PageList);
	}
}

void	ParamGlobal::GetStrategyLayer(int strategycode ,int page ,IntList &LayerList)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		for(int layer=0;layer<LayerNumb;layer++){
			int	n=page*LayerNumb+layer;
			if(n<StrategyDimAllocNumb){
				if(StrategyDim[n]==strategycode){
					LayerList.Add(layer);
				}
			}
		}
	}
	else{
		GetTreeTopLayersBase()->GetParamGlobal()->GetStrategyLayer(strategycode ,page,LayerList);
	}
}

void	ParamGlobal::GetCalcStrategy(int strategycode ,StrategicListContainer &SList)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		for(int page=0;page<PageNumb;page++){
			int	n=page*LayerNumb;
			if(n<CalcStrategyDimAllocNumb){
				for(int L=0;L<LayerNumb;L++){
					if(CalcStrategyDim[n+L]==strategycode){
						StrategicList	*s=new StrategicList();
						s->Page=page;
						s->Layer=L;
						SList.AppendList(s);
					}
				}
			}
		}
	}
	else{
		GetTreeTopLayersBase()->GetParamGlobal()->GetCalcStrategy(strategycode ,SList);
	}
}

void	ParamGlobal::GetCalcStrategyPage (int strategycode ,IntList &PageList)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		for(int page=0;page<PageNumb;page++){
			for(int layer=0;layer<LayerNumb;layer++){
				int	n=page*LayerNumb+layer;
				if(n<CalcStrategyDimAllocNumb){
					if(CalcStrategyDim[n]==strategycode){
						PageList.Add(page);
						goto	PNext;
					}
				}
			}
	PNext:;
		}
	}
	else{
		GetTreeTopLayersBase()->GetParamGlobal()->GetCalcStrategyPage(strategycode ,PageList);
	}
}

void	ParamGlobal::GetCalcStrategyLayer(int strategycode ,int page ,IntList &LayerList)
{
	if(GetLayersBase()->GetShadowLevel()==0){
		for(int layer=0;layer<LayerNumb;layer++){
			int	n=page*LayerNumb+layer;
			if(n<CalcStrategyDimAllocNumb){
				if(CalcStrategyDim[n]==strategycode){
					LayerList.Add(layer);
				}
			}
		}
	}
	else{
		GetTreeTopLayersBase()->GetParamGlobal()->GetCalcStrategyLayer(strategycode ,page,LayerList);
	}
}


void	ParamGlobal::GetPageDir(int page ,bool &XDirReverse ,bool &YDirReverse)
{
	if(PDirData==NULL || PDirDataAllocNumb!=GetPageNumb()){
		ReallocPageDir();
	}
	XDirReverse=PDirData[page].ReverseX;
	YDirReverse=PDirData[page].ReverseY;
}
void	ParamGlobal::SetPageDir(int page ,bool  XDirReverse ,bool  YDirReverse)
{
	if(PDirData==NULL || PDirDataAllocNumb!=GetPageNumb()){
		ReallocPageDir();
	}
	PDirData[page].ReverseX=XDirReverse;
	PDirData[page].ReverseY=YDirReverse;
}
bool	ParamGlobal::GetPageXDir(int page)
{
	if(PDirData==NULL || PDirDataAllocNumb!=GetPageNumb()){
		ReallocPageDir();
	}
	return PDirData[page].ReverseX;
}
bool	ParamGlobal::GetPageYDir(int page)
{
	if(PDirData==NULL || PDirDataAllocNumb!=GetPageNumb()){
		ReallocPageDir();
	}
	return PDirData[page].ReverseY;
}
int		ParamGlobal::GetPageYDelay(int page)
{
	if(PDirData==NULL || PDirDataAllocNumb!=GetPageNumb()){
		ReallocPageDir();
	}
	return PDirData[page].YDelay;
}

void	ParamGlobal::SetPageXDir(int page ,bool Rev)
{
	if(PDirData==NULL || PDirDataAllocNumb!=GetPageNumb()){
		ReallocPageDir();
	}
	PDirData[page].ReverseX=Rev;
}
void	ParamGlobal::SetPageYDir(int page ,bool Rev)
{
	if(PDirData==NULL || PDirDataAllocNumb!=GetPageNumb()){
		ReallocPageDir();
	}
	PDirData[page].ReverseY=Rev;
}

void	ParamGlobal::SetPageYDelay(int page ,int ydelay)
{
	if(PDirData==NULL || PDirDataAllocNumb!=GetPageNumb()){
		ReallocPageDir();
	}
	PDirData[page].YDelay=ydelay;
}

void	ParamGlobal::ReallocPageDir(void)
{
	GetLayersBase()->LockWChangingDataStructure();
	if(PDirDataAllocNumb!=GetPageNumb()){
		PageDirection	*TmpPDirData=new PageDirection[GetPageNumb()];
		if(PDirDataAllocNumb!=0 && PDirData!=NULL){
			for(int i=0;i<PDirDataAllocNumb && i<GetPageNumb();i++){
				TmpPDirData[i]=PDirData[i];
			}
			delete	[]PDirData;
			PDirData=NULL;
			PDirDataAllocNumb=0;
		}
		PDirData=TmpPDirData;
		PDirDataAllocNumb=GetPageNumb();
	}
	GetLayersBase()->UnlockChangingDataStructure();
}

void	ParamGlobal::CopyPageDirFrom(ParamGlobal &src)
{
	if(&src==this){
		return;
	}
	GetLayersBase()->LockWChangingDataStructure();
	if(PDirDataAllocNumb!=GetPageNumb()){
		PageDirection	*TmpPDirData=new PageDirection[GetPageNumb()];
		if(PDirDataAllocNumb!=0 && PDirData!=NULL){
			for(int i=0;i<PDirDataAllocNumb && i<GetPageNumb();i++){
				PDirData[i]=TmpPDirData[i];
			}
			delete	[]PDirData;
			PDirData=NULL;
			PDirDataAllocNumb=0;
		}
		PDirData=TmpPDirData;
		PDirDataAllocNumb=GetPageNumb();
	}
	GetLayersBase()->UnlockChangingDataStructure();
	for(int i=0;i<PDirDataAllocNumb;i++){
		PDirData[i]=src.PDirData[i];
	}
}

//----------- RemoteTransfer -------------

int		ParamGlobal::GetRemoteTransferCount(void)
{
	return RemoteTransferListDimNumb;
}
RemoteTransferList *ParamGlobal::GetRemoteTransfer(int n)
{
	if(0<=n && n< RemoteTransferListDimNumb){
		return &RemoteTransferListDim[n];
	}
	return NULL;
}
void	ParamGlobal::AddRemoteTransfer(RemoteTransferList &n)
{
	if(RemoteTransferListDimNumb< MaxRemoteTransferListDimNumb){
		RemoteTransferListDim[RemoteTransferListDimNumb]=n;
		RemoteTransferListDimNumb++;
	}
}
void	ParamGlobal::RemoveRemoteTransfer(int n)
{
	if(0 <= n && n < RemoteTransferListDimNumb) {
		for(int i=n;i< RemoteTransferListDimNumb-1;i++){
			RemoteTransferListDim[i]=RemoteTransferListDim[i+1];
		}
		RemoteTransferListDimNumb--;
	}
}
bool	ParamGlobal::SaveRemoteTransfer(QIODevice *f, int EnableCondition)
{
	if(::Save(f, RemoteTransferListDimNumb)==false)
		return false;
	for(int i=0;i< RemoteTransferListDimNumb;i++){
		if(RemoteTransferListDim[i].Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ParamGlobal::LoadRemoteTransfer(QIODevice *f, int EnableCondition)
{
	if(::Load(f, RemoteTransferListDimNumb) == false)
		return false;
	if(RemoteTransferListDimNumb>=MaxRemoteTransferListDimNumb){
		delete	[]RemoteTransferListDim;
		RemoteTransferListDim=new RemoteTransferList[RemoteTransferListDimNumb+MaxRemoteTransferListDimNumb];
	}
	for(int i=0;i<RemoteTransferListDimNumb;i++) {
		if(RemoteTransferListDim[i].Load(f) == false) {
			return false;
		}
	}
	return true;
}

//----------- Unit-------------
bool	ParamGlobal::IsUnitMode(void)
{
	if(UnitName.isEmpty()==true || ResolutionXNano==0 || TransformUnitToNano==0)
		return false;
	return true;
}
	
double	ParamGlobal::TransformPixelDistanceToUnit(int Page,double PixelX1,double PixelY1 ,double PixelX2,double PixelY2)
{
	return TransformPixelDistanceToUnit(Page,PixelX2-PixelX1,PixelY2-PixelY1);
}
double	ParamGlobal::TransformUnitDistanceToPixel(int Page,double UnitX1 ,double UnitY1  ,double UnitX2 ,double UnitY2)
{
	return TransformUnitDistanceToPixel(Page,UnitX2-UnitX1,UnitY2-UnitY1);
}
	
double	ParamGlobal::TransformPixelDistanceToUnit(int Page,double PixelXLen,double PixelYLen)
{
	double	Len=hypot(PixelXLen,PixelYLen);
	if(Len==0.0){
		return 0.0;
	}
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		double	Px=PixelXLen/Len;
		double	Py=PixelYLen/Len;
		double	Ux=PixelXLen*Px*ResolutionXNano/TransformUnitToNano;
		double	Uy=PixelYLen*Py*ResolutionYNano/TransformUnitToNano;
		return hypot(Ux,Uy);
	}
	double	Px=PixelXLen/Len;
	double	Py=PixelYLen/Len;
	double	Ux=PixelXLen*Px*PageLocalData[Page].ResolutionXNano/TransformUnitToNano;
	double	Uy=PixelYLen*Py*PageLocalData[Page].ResolutionYNano/TransformUnitToNano;
	return hypot(Ux,Uy);
}

double	ParamGlobal::TransformUnitDistanceToPixel(int Page,double UnitXLen ,double UnitYLen)
{
	double	Len=hypot(UnitXLen,UnitYLen);
	if(Len==0.0){
		return 0.0;
	}
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		double	Ux=UnitXLen/Len;
		double	Uy=UnitYLen/Len;
		double	Px=UnitXLen*Ux/ResolutionXNano*TransformUnitToNano;
		double	Py=UnitYLen*Uy/ResolutionYNano*TransformUnitToNano;
		return hypot(Px,Py);
	}
	double	Ux=UnitXLen/Len;
	double	Uy=UnitYLen/Len;
	double	Px=UnitXLen*Ux/PageLocalData[Page].ResolutionXNano*TransformUnitToNano;
	double	Py=UnitYLen*Uy/PageLocalData[Page].ResolutionYNano*TransformUnitToNano;
	return hypot(Px,Py);
}

double	ParamGlobal::TransformPixelToUnit(int Page,double pixel)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		int	AvrResolutionNano=(ResolutionXNano+ResolutionYNano)/2;
		return pixel*AvrResolutionNano/TransformUnitToNano;
	}
	int	AvrResolutionNano=(PageLocalData[Page].ResolutionXNano+PageLocalData[Page].ResolutionYNano)/2;
	return pixel*AvrResolutionNano/TransformUnitToNano;
}

double	ParamGlobal::TransformUnitToPixel(int Page,double unit)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		int	AvrResolutionNano=(ResolutionXNano+ResolutionYNano)/2;
		return unit/AvrResolutionNano*TransformUnitToNano;
	}
	int	AvrResolutionNano=(PageLocalData[Page].ResolutionXNano+PageLocalData[Page].ResolutionYNano)/2;
	return unit/AvrResolutionNano*TransformUnitToNano;
}
double	ParamGlobal::TransformPixelToUnitX(int Page,double pixel)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		return pixel*ResolutionXNano/TransformUnitToNano;
	}
	return pixel*PageLocalData[Page].ResolutionXNano/TransformUnitToNano;
}
double	ParamGlobal::TransformPixelToUnitY(int Page,double pixel)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		return pixel*ResolutionYNano/TransformUnitToNano;
	}
	return pixel*PageLocalData[Page].ResolutionYNano/TransformUnitToNano;
}
double	ParamGlobal::TransformUnitToPixelX(int Page,double unit)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		return unit/ResolutionXNano*TransformUnitToNano;
	}
	return unit/PageLocalData[Page].ResolutionXNano*TransformUnitToNano;
}
double	ParamGlobal::TransformUnitToPixelY(int Page,double unit)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		return unit/ResolutionYNano*TransformUnitToNano;
	}
	return unit/PageLocalData[Page].ResolutionYNano*TransformUnitToNano;
}

QString	ParamGlobal::TransformPixelToUnitStr(int Page,double pixel)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		int	AvrResolutionNano=(ResolutionXNano+ResolutionYNano)/2;
		return GetUnitStr(pixel*AvrResolutionNano/TransformUnitToNano);
	}
	if(Page<0)
		Page=0;
	int	AvrResolutionNano=(PageLocalData[Page].ResolutionXNano+PageLocalData[Page].ResolutionYNano)/2;
	return GetUnitStr(pixel*AvrResolutionNano/TransformUnitToNano);
}

QString	ParamGlobal::GetUnitStr(double unit)
{
	return QString::number(unit,'f',SmallNumberFigure)+QString(' ')+UnitName;
}

double	ParamGlobal::TransformPixelToUnitSquare(int Page,double pixel)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		double	ux=ResolutionXNano/TransformUnitToNano;
		double	uy=ResolutionYNano/TransformUnitToNano;
		return pixel*ux*uy;
	}
	double	ux=PageLocalData[Page].ResolutionXNano/TransformUnitToNano;
	double	uy=PageLocalData[Page].ResolutionYNano/TransformUnitToNano;
	return pixel*ux*uy;
}	
double	ParamGlobal::TransformUnitToPixelSquare(int Page,double unit)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		double	ux=ResolutionXNano/TransformUnitToNano;
		double	uy=ResolutionYNano/TransformUnitToNano;
		return unit/(ux*uy);
	}
	double	ux=PageLocalData[Page].ResolutionXNano/TransformUnitToNano;
	double	uy=PageLocalData[Page].ResolutionYNano/TransformUnitToNano;
	return unit/(ux*uy);
}
QString	ParamGlobal::TransformPixelToUnitSquareStr(int Page,double pixel)
{
	if(CountOfPageLocal<=Page || PageLocalData==NULL){
		double	ux=ResolutionXNano/TransformUnitToNano;
		double	uy=ResolutionYNano/TransformUnitToNano;
		return GetUnitSquareStr(pixel*ux*uy);
	}
	double	ux=PageLocalData[Page].ResolutionXNano/TransformUnitToNano;
	double	uy=PageLocalData[Page].ResolutionYNano/TransformUnitToNano;
	return GetUnitSquareStr(pixel*ux*uy);
}


QString	ParamGlobal::GetUnitSquareStr(double unit)
{
	return QString::number(unit,'f',SmallNumberFigure)+QString(' ')+UnitSquareName;
}

//================================================================================

ConnectionInfo::ConnectionInfo(void)
{	
	GlobalCameraNo	=NULL;
	GlobalCameraNoNumb=0;
	PartnerID=0;	
	CameraNumb		=1;
}
ConnectionInfo::~ConnectionInfo(void)
{
	if(GlobalCameraNo!=NULL){
		delete	[]GlobalCameraNo;
	}
	GlobalCameraNo=NULL;
}

ConnectionInfo	&ConnectionInfo::operator=(ConnectionInfo &src)
{
	if(this!=&src){
		PartnerID	=src.PartnerID;
		IPAddress	=src.IPAddress;
		CameraNumb	=src.CameraNumb;

		if(GlobalCameraNo!=NULL){
			delete	[]GlobalCameraNo;
		}
		GlobalCameraNo=new int32[CameraNumb];
		if(src.GlobalCameraNo!=NULL){
			for(int i=0;i<CameraNumb;i++){
				GlobalCameraNo[i]=src.GlobalCameraNo[i];
			}
		}
		GlobalCameraNoNumb=CameraNumb;
	}
	return *this;
}

bool	ConnectionInfo::SaveParam(QIODevice *f,int EnableCondition)
{
	if(EnableCondition==0 || EnableCondition==-1){
		if(f->write((const char *)&PartnerID,sizeof(PartnerID))!=sizeof(PartnerID)){
			return(false);
		}
		if(f->write((const char *)&CameraNumb,sizeof(CameraNumb))!=sizeof(CameraNumb)){
			return(false);
		}
		if(::Save(f,IPAddress)==false){
			return(false);
		}
		bool	GlobalCameraNoExist;
		if(GlobalCameraNo!=NULL){
			GlobalCameraNoExist=true;
			if(f->write((const char *)&GlobalCameraNoExist,sizeof(GlobalCameraNoExist))!=sizeof(GlobalCameraNoExist)){
				return(false);
			}
			if(f->write((const char *)&GlobalCameraNoNumb,sizeof(GlobalCameraNoNumb))!=sizeof(GlobalCameraNoNumb)){
				return(false);
			}
			if(f->write((const char *)GlobalCameraNo,sizeof(GlobalCameraNo[0])*GlobalCameraNoNumb)!=sizeof(GlobalCameraNo[0])*GlobalCameraNoNumb){
				return(false);
			}
		}
		else{
			GlobalCameraNoExist=false;
			if(f->write((const char *)&GlobalCameraNoExist,sizeof(GlobalCameraNoExist))!=sizeof(GlobalCameraNoExist)){
				return(false);
			}
		}
	}
	return(true);
}
bool	ConnectionInfo::LoadParam(QIODevice *f,int EnableCondition)
{
	if(EnableCondition==0 || EnableCondition==-1){
		if(f->read((char *)&PartnerID,sizeof(PartnerID))!=sizeof(PartnerID)){
			return(false);
		}
		if(f->read((char *)&CameraNumb,sizeof(CameraNumb))!=sizeof(CameraNumb)){
			return(false);
		}
		if(::Load(f,IPAddress)==false){
			return(false);
		}
		bool	GlobalCameraNoExist;
		if(f->read((char *)&GlobalCameraNoExist,sizeof(GlobalCameraNoExist))!=sizeof(GlobalCameraNoExist)){
			return(false);
		}
		if(GlobalCameraNo!=NULL){
			delete	[]GlobalCameraNo;
		}
		GlobalCameraNo=NULL;
		if(GlobalCameraNoExist==true){
			if(f->read((char *)&GlobalCameraNoNumb,sizeof(GlobalCameraNoNumb))!=sizeof(GlobalCameraNoNumb)){
				return(false);
			}
			GlobalCameraNo=new int32[GlobalCameraNoNumb];
			if(f->read((char *)GlobalCameraNo,sizeof(GlobalCameraNo[0])*GlobalCameraNoNumb)!=sizeof(GlobalCameraNo[0])*GlobalCameraNoNumb){
				return(false);
			}
		}
	}
	return(true);
}
void	ConnectionInfo::ReallocGlobalCameraNo(void)
{
	if(GlobalCameraNo!=NULL){
		if(GlobalCameraNoNumb!=CameraNumb){
			int32	*D=new int32[CameraNumb];
			for(int i=0;i<CameraNumb;i++){
				D[i]=i;
			}
			for(int i=0;i<min(GlobalCameraNoNumb,CameraNumb);i++){
				D[i]=GlobalCameraNo[i];
			}
			delete	[]GlobalCameraNo;
			GlobalCameraNo=D;
			GlobalCameraNoNumb=CameraNumb;
		}
	}
	else{
		GlobalCameraNo=new int32[CameraNumb];
		for(int i=0;i<CameraNumb;i++){
			GlobalCameraNo[i]=i;
		}
		GlobalCameraNoNumb=CameraNumb;
	}
}
int32		ConnectionInfo::GetGlobalCameraNo(int localCamNo)
{
	if(GlobalCameraNo==NULL){
		ReallocGlobalCameraNo();
	}
	if(GlobalCameraNo!=NULL){
		if(GlobalCameraNoNumb>localCamNo){
			return(GlobalCameraNo[localCamNo]);
		}
		else{
			ReallocGlobalCameraNo();
			if(GlobalCameraNoNumb>localCamNo){
				return(GlobalCameraNo[localCamNo]);
			}
			return(GlobalCameraNo[GlobalCameraNoNumb-1]+localCamNo-(GlobalCameraNoNumb-1));
		}
	}
	return(0);
}
void		ConnectionInfo::SetGlobalCameraNo(int localCamNo, int globalCameraNo)
{
	if(GlobalCameraNo!=NULL){
		if(GlobalCameraNoNumb>localCamNo){
			GlobalCameraNo[localCamNo]=globalCameraNo;
		}
	}
}
int		ConnectionInfo::GetPortNo(void)
{
	QString	PortStr=IPAddress.section(':',1,1);
	if(PortStr.isEmpty()==true){
		return GUICommPort;
	}
	else{
		return IPAddress.section(':',0,0),PortStr.toInt();
	}
}

ParamComm::ParamComm(LayersBase *base)
:ServiceForLayers(base)
{
	ConnectedPCNumb=0;
	Mastered		=true;
	ThisComputerID	=0;
	EnabledComm		=false;

	SetParam(&ConnectedPCNumb	, /**/"Comm" ,/**/"ConnectedPCNumb"	,LangLibSolver.GetString(XParamGlobal_LS,LID_336)/*"Connected computer number"*/);
	SetParam(&Mastered			, /**/"Comm" ,/**/"Mastered"		,LangLibSolver.GetString(XParamGlobal_LS,LID_339)/*"Master computer"*/			);
	SetParam(&ThisComputerID	, /**/"Comm" ,/**/"SlaveID"			,LangLibSolver.GetString(XParamGlobal_LS,LID_342)/*"Connected computer number"*/);

	Connection		=NULL;
	ConnectionNumb	=0;
}
ParamComm::~ParamComm(void)
{
	if(Connection!=NULL){
		delete	[]Connection;
	}
	Connection=NULL;
}

bool	ParamComm::WriteEnableToDefaultFile(void)
{
	if(GetLayersBase()->GetBootingLevel()==0 && GetLayersBase()->GetMasterType()==0){
		return true;
	}
	else{
		return false;
	}
}


bool	ParamComm::SaveParam(QIODevice *f,int EnableCondition)
{
	if(ParamBase::SaveParam(f,EnableCondition)==false){
		return(false);
	}

	if(EnableCondition==0 || EnableCondition==-1){
		bool	ConnectionExist;
		if(Connection!=NULL){
			ConnectionExist=true;
			if(f->write((const char *)&ConnectionExist,sizeof(ConnectionExist))!=sizeof(ConnectionExist)){
				return(false);
			}
			if(f->write((const char *)&ConnectionNumb,sizeof(ConnectionNumb))!=sizeof(ConnectionNumb)){
				return(false);
			}
			for(int i=0;i<ConnectionNumb;i++){
				if(Connection[i].SaveParam(f,EnableCondition)==false){
					return(false);
				}
			}
		}
		else{
			ConnectionExist=false;
			if(f->write((const char *)&ConnectionExist,sizeof(ConnectionExist))!=sizeof(ConnectionExist)){
				return(false);
			}
		}
	}
			
	return(true);
}
bool	ParamComm::LoadParam(QIODevice *f,int EnableCondition)
{
	if(ParamBase::LoadParam(f,EnableCondition)==false){
		return(false);
	}
	if(EnableCondition==0 || EnableCondition==-1){
		bool	ConnectionExist;
		if(f->read((char *)&ConnectionExist,sizeof(ConnectionExist))!=sizeof(ConnectionExist)){
			return(false);
		}
		if(Connection!=NULL){
			delete	[]Connection;
		}
		Connection=NULL;
		if(ConnectionExist==true){
			if(f->read((char *)&ConnectionNumb,sizeof(ConnectionNumb))!=sizeof(ConnectionNumb)){
				return(false);
			}
			Connection=new ConnectionInfo[ConnectionNumb];
			for(int i=0;i<ConnectionNumb;i++){
				if(Connection[i].LoadParam(f,EnableCondition)==false){
					return(false);
				}
			}
		}
	}
	return(true);
}


void	ParamComm::ReallocConnection(void)
{
	if(Connection!=NULL){
		if(ConnectionNumb!=ConnectedPCNumb){
			ConnectionInfo	*D=new ConnectionInfo[ConnectedPCNumb];
			for(int i=0;i<ConnectedPCNumb;i++){
				D[i].PartnerID=i;
			}
			for(int i=0;i<min(ConnectedPCNumb,ConnectionNumb);i++){
				D[i]=Connection[i];
			}
			delete	[]Connection;
			Connection=D;
			ConnectionNumb=ConnectedPCNumb;
		}
	}
	else{
		Connection=new ConnectionInfo[ConnectedPCNumb];
		ConnectionNumb=ConnectedPCNumb;
	}
}

ConnectionInfo	*ParamComm::GetConnection(int n)
{
	if(Connection==NULL){
		ReallocConnection();
	}
	if(Connection!=NULL){
		if(ConnectionNumb>n){
			return(&Connection[n]);
		}
		else{
			ReallocConnection();
			if(ConnectionNumb>n){
				return(&Connection[n]);
			}
			return(NULL);
		}
	}
	return(NULL);
}

int	ParamComm::GetCommIDFromPage(ParamGlobal &ParamGlobalData ,int page)
{
	int	gcam=ParamGlobalData.GetCameraNo(page);
	return gcam;
}

ConnectionInfo	*ParamComm::GetConnectionFromPage	(ParamGlobal &ParamGlobalData ,int localPage)
{
	for(int i=0;i<ConnectedPCNumb;i++){
		ConnectionInfo	*p=GetConnection(i);
		if(p==NULL){
			continue;
		}
		for(int j=0;j<p->CameraNumb;j++){
			//if(p->GetGlobalCameraNo(j)==gcam){
			if(p->GetGlobalCameraNo(j)==localPage){
				return(p);
			}
		}
	}
	return(NULL);
}

int	ParamComm::GetLocalPageFromGlobal(ParamGlobal &ParamGlobalData ,int globalPage)
{
	if(Mastered==true){
		return(globalPage);
	}
	ConnectionInfo	*p=GetConnection(0);
	if(p==NULL){
		return(-1);
	}

	if(ParamGlobalData.GetMaxScanStrategy()<=1){
		for(int j=0;j<p->CameraNumb;j++){
			int	gcam=p->GetGlobalCameraNo(j);
			if(globalPage==gcam){
				return(j);
			}
		}
		for(int j=0;j<p->CameraNumb;j++){
			int	gcam=p->GetGlobalCameraNo(0);
			if(gcam+GetPageNumb()>globalPage){
				return globalPage-gcam;
			}
		}
	}
	else{
		for(int j=0;j<p->CameraNumb;j++){
			int	gcam=p->GetGlobalCameraNo(0);
			for(int i=0;i<ParamGlobalData.GetMaxScanStrategy();i++){
				if(globalPage==(gcam+i)){
					return(i);
				}
			}
		}
		for(int j=0;j<p->CameraNumb;j++){
			int	gcam=p->GetGlobalCameraNo(0);
			if(gcam+GetPageNumb()>globalPage){
				return globalPage-gcam;
			}
		}
	}

	return(-1);
}
int	ParamComm::GetGlobalPageFromLocal(ParamGlobal &ParamGlobalData ,int localPage)
{
	if(Mastered==true){
		return(localPage);
	}

	if(ParamGlobalData.GetMaxScanStrategy()<=1){
		ConnectionInfo	*p=GetConnection(0);
		if(p==NULL){
			return(-1);
		}
		return p->GetGlobalCameraNo(localPage);
	}
	else{
		ConnectionInfo	*p=GetConnection(0);
		if(p==NULL){
			return(-1);
		}
		int	c=p->GetGlobalCameraNo(0);
		return c+localPage;
	}
}

int	ParamComm::GetLocalCameraNumb(int)	//computerID)
{
	if(Mastered==true){
		if(ConnectedPCNumb==0){
			return GetLayersBase()->GetParamGlobal()->TotalCameraNumb;
		}
	}
	else{
		int	MaxD=0;
		int	L=GetLayersBase()->GetParamGlobal()->GetMaxScanStrategy();
		if(L>1){
			for(int s=0;s<L;s++){
				IntList	PageList;
				GetLayersBase()->GetParamGlobal()->GetStrategyPage (s,PageList);
				int	d=PageList.GetCount();
				if(MaxD<d){
					MaxD=d;
				}
			}
			return MaxD;
		}
		else{
			return GetLayersBase()->GetParamGlobal()->GetPageNumb();
		}
	}
	return(1);
}
