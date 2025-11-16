/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XExecuteInspectBase.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XExecuteInspectOpenH
#define XExecuteInspectOpenH

#include <QThread>
#include <QReadWriteLock>
#include "XTypeDef.h"
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"
#include "XStatistic.h"
#include "XShadowTree.h"

class	SeqControlParam;
class	SeqLocalParam;
class	CameraClass;
class	ThreadSequence;
class	GUIInstancePack;
class	EntryPointBase;
class	CameraReqInfoAnyData;

class	CallBackFunctionList : public NPList<CallBackFunctionList>
{
public:
	GUIFormBase	*GBase;
	void	(*CallBackFunc)(GUIFormBase *f);

	CallBackFunctionList(void){	GBase=NULL;	CallBackFunc=NULL;	}
};

class	CallBackFunctionContainer : public NPListPack<CallBackFunctionList>
{
public:
	CallBackFunctionContainer(void){}

	void	ExecuteFunc(void);
};

class ExecuteInspectBase : public QThread , public ServiceForLayers
{
	Q_OBJECT
		
	EntryPointBase		*EntryPointBaseData;
	SeqLocalParam		*LocalParam;
	IntList				CameraStates;

protected:
	CallBackFunctionContainer	FuncContainerInCaptureOnlyMaster	;
	CallBackFunctionContainer	FuncContainerInCaptureOnlyTarget	;
	CallBackFunctionContainer	FuncContainerInCaptureInspect		;
	CallBackFunctionContainer	FuncContainerInCaptureContinuously	;
	StackForAverage				TimeStocker;
public:
	enum	ExecuteInspectState{
			_EI_IDLE			=0
			,_EI_Prepare		=1
			,_EI_StartCamera	=2
			,_EI_OnCapturing	=3
			,_EI_OnCalc			=4
			,_EI_OnTransmit		=5
			,_EI_OnResult		=6
	};

	enum	MotionMode{
			_CaptureNone					=0
			,_CaptureOnlyMaster				=1
			,_CaptureOnlyTarget				=2
			,_CaptureInspect				=3
			,_CaptureGray					=4
			,_CaptureInspectWithoutCapture	=5
			,_CaptureContinuously			=6
	};
	enum	AutoRepeatMode{
			 _NoAutoRepeat					=0
			,_AutoCaptureOnlyMaster			=1
			,_AutoCaptureOnlyTarget			=2
			,_AutoCaptureInspect			=3
			,_AutoCaptureGray				=4
			,_CaptureMasterContinuously		=5
			,_CaptureTargetContinuously		=6
			,_CaptureRawTargetContinuously	=7
			,_CaptureCamTargetContinuously	=8
	};
	enum	TypeOfCapture{
			_Master			=0
			,_Target		=1
	};
private:
	AutoRepeatMode	AutoRepeatFlag;
	bool		HaltMode;
	bool		PermitToRun;

	TypeOfCapture	CurrentTypeOfCapture;
	TypeOfCapture	CurrentCaptureSource;
	int		IdleLoopCounter;
	QString		LastCamFileName;
public:
	NPListPack<LayersBasePointerList>	ShadowLayersBasePointer;

public:
	explicit    ExecuteInspectBase(QObject *parent ,EntryPointBase *_EntryPointBaseData ,SeqLocalParam *_SeqParam);
	virtual	~ExecuteInspectBase(void);

	virtual void	InitialPrepare(void);
	virtual void	Prepare(void)		;
	virtual void	AfterPrepare(void)	;
	virtual void	ReadyParam(void)	;
	virtual void	AfterStartSequence(void);

	virtual	bool	IsLocalCamera(void)			=0;

	virtual	ExecuteInspectState	GetState(void)	;
	virtual	MotionMode			GetMode(void)	;

	virtual	void	SetState(ExecuteInspectBase::ExecuteInspectState b)	;
	virtual	void	SetMode (ExecuteInspectBase::MotionMode b)	;


	virtual	SeqLocalParam		*GetSeqParam(void){		return LocalParam;	}
	virtual	bool	LoadDefault(void)			=0;
	virtual	bool	SaveDefault(void)			=0;
	virtual	bool	Load(QIODevice *f)			=0;
	virtual	bool	Save(QIODevice *f)			=0;
	
	virtual	bool	InitialCamera(int32 &ErrorCode)		{	return true;	}
	virtual	bool	ChangeCameraInfo(CameraReqInfoAnyData *anydata=NULL){	return true;	}
	virtual	bool	CheckCameraDLL(void)				{	return true;	}
	void	StartAllCamera(void);
	void	FinishCapture(int PageNo);
	bool	IsAllFinished(void);

	virtual	int			GetAllocatedCameraCount(void);
	virtual	CameraClass		*GetCamera(int n)			=0;
	virtual	int		GetCameraDim(CameraClass *CamDim[])	{	return 0;	}
	virtual	void	SetCameraDim(CameraClass *CamDim[])	{}

	//Ç±ÇÍÇÁÇÕäOïîÇ©ÇÁÇÃëÄçÏ
	virtual	void	GoInspect(void)					=0;
	virtual	void	GoInspectWithoutCapture(void)	=0;
	virtual	void	GoMasterCaptureOnly(void)		=0;
	virtual	void	GoTargetCaptureOnly(void)		=0;
	virtual	void	GoGray(void)					=0;
	virtual	void	GoHalt(void)				{	HaltMode=true;		}
	virtual	void	ClearHaltMode(void)			{	HaltMode=false;		}
	virtual	void	CamShowSetting(int CamNo)	=0;
	virtual	bool	LoadCameraSetting(const QString &CamFileName);
	virtual	bool	SaveCameraSetting(const QString &CamFileName);
	virtual	bool	LoadCameraSetting(QIODevice *f);
	virtual	bool	SaveCameraSetting(QIODevice *f);

	virtual	bool	GetHaltMode(void)			{	return HaltMode;	}

	virtual	void	StopCycle(void)				{	PermitToRun=false;	}
	virtual	void	StartCycle(void)			{	PermitToRun=true;	}
	virtual	bool	GetPermitToRun(void)		{	return PermitToRun;	}

	TypeOfCapture	GetCurrentTypeOfCapture(void){	return CurrentTypeOfCapture;	}
	void			SetCurrentTypeOfCapture(TypeOfCapture s){	CurrentTypeOfCapture=s;	}
	TypeOfCapture	GetCurrentCaptureSource(void){	return CurrentCaptureSource;	}
	void			SetCurrentCaptureSource(TypeOfCapture s){	CurrentCaptureSource=s;	}
	virtual	void	ChangeLot(void){}
	virtual	void	ClearCameraBuffer(void){}

	void	SetAutoRepeat(AutoRepeatMode mode);
	AutoRepeatMode	GetAutoRepeat(void){	return AutoRepeatFlag;	}

	void	ImageReverse(int page,ImageBuffer *Buff[] ,int BuffDimCount);
	void	ImageYDelay(int page,ImageBuffer *Buff[] ,int BuffDimCount);

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v){}

	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	ReallocXYPixelsPage(int Phase ,int Page ,int NewDotPerLine ,int NewMaxLines);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);

	LayersBase			*GetLayersBase(void)		;
	EntryPointBase		*GetEntryPoint(void)		;
	ParamGlobal			*GetParamGlobal(void)		;
	ParamComm			*GetParamComm(void)			;
	ThreadSequence		*GetThreadSequence(void)	;
	GUIInstancePack		*GetGUIInstancePack(void)	;

	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	virtual	bool	Reallocate(int newPhaseNumb		);
	virtual	bool	RemovePhase(int RemovedPhaseCode);	//can not remove phase0

	// These callback function is called in thread
	void	AddCallbackInCaptureOnlyMaster	(GUIFormBase	*GBase ,void (*CallBackFunc)(GUIFormBase *f));
	void	AddCallbackInCaptureOnlyTarget	(GUIFormBase	*GBase ,void (*CallBackFunc)(GUIFormBase *f));
	void	AddCallbackInCaptureInspect		(GUIFormBase	*GBase ,void (*CallBackFunc)(GUIFormBase *f));
	void	AddCallbackInCaptureContinuously(GUIFormBase	*GBase ,void (*CallBackFunc)(GUIFormBase *f));

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID);
	virtual	ExeResult	ExecuteStartByInspection(int ExeID);
	virtual	ExeResult	ExecuteCaptured			(int ExeID,ListPhasePageLayerPack &CapturedList);
	virtual	ExeResult	ExecutePreAlignment		(int ExeID);
	virtual	ExeResult	ExecuteAlignment		(int ExeID);
	virtual	ExeResult	ExecutePreProcessing	(int ExeID);
	virtual	ExeResult	ExecuteProcessing		(int ExeID);
	virtual	ExeResult	ExecuteProcessingRevived(int ExeID);
	virtual	ExeResult	ExecutePostProcessing	(int ExeID);
	virtual	ExeResult	ExecutePreScanning		(int ExeID);
	virtual	ExeResult	ExecuteScanning			(int ExeID);
	virtual	ExeResult	ExecutePostScanning		(int ExeID);
	virtual	ExeResult	ExecuteManageResult		(int ExeID);

	int		GetIdleLoopCounter(void)	{	return IdleLoopCounter;	}
	void	PushOnIdle(void)			{	IdleLoopCounter++;		}

	void	EmitSignalCaptured(int CStrategic);
	void	EmitSignalTargetImageCaptured(void);
	void	EmitSignalMasterImageCaptured(void);
protected:
	QReadWriteLock			MutexStateMode;
	volatile	ExecuteInspectState		CurrentState;
	volatile	MotionMode				CurrentMode;

signals:
	void	SignalCaptured(int);
	void	SignalTargetImageCaptured();
	void	SignalMasterImageCaptured();
};

class	SpecifiedBroadcasterAutoModeStart : public SpecifiedBroadcaster
{
public:
	SpecifiedBroadcasterAutoModeStart(void){}
};

class	SpecifiedBroadcasterAutoModeEnd : public SpecifiedBroadcaster
{
public:
	SpecifiedBroadcasterAutoModeEnd(void){}
};

class	CmdReqInspectionRefresh: public SpecifiedBroadcaster
{
public:
	int64	InspectionID;
	CmdReqInspectionRefresh(void){	InspectionID=-1;	}
};

#endif

