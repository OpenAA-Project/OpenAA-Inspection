/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XExecuteInspect.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XExecuteInspectH
#define XExecuteInspectH

#include <QThread>
#include <QReadWriteLock>
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"
#include "XServiceForLayers.h"
#include "XResult.h"

class	SeqControlParam;
class	CmdCaptureBegins;
class	GUIFormBase;

//CameraClass		*ExecuteInspect::GetCamera(int n)	{	return Cam[n];	}
class ResultInspection;

class ThreadOutputResult : public QThread,public ServiceForLayers
{
	QMutex				MutexOutput;
	ResultInspection	*Res;
	volatile	bool	Terminated;
	volatile	bool	InspectionStart;
	volatile	bool	EndOfInspection;
	DWORD		StartMilisec;
	ResultPkNgPacket	ResultPacket;
	int					ResultMode;
	DWORD				AddedMilisec;
	bool				ThreadMode;
	DWORD				ExecutedTime;
public:
	ThreadOutputResult(QObject *obj ,LayersBase *Base);
	~ThreadOutputResult(void);

	void	StartThreadMode(bool ThreadMode);
	virtual	void	run()	override;
	void	Terminate(void);

	void	SetStart(ResultInspection *R ,DWORD _AddedMilisec);
	void	SetOutput(int RMode ,ResultPkNgPacket &P);

private:
	void	Execute(void);
};

class ExecuteInspectFast : public ExecuteInspectBase
{
	Q_OBJECT
		char	*DefaultCameraFileName;

	int		AllocatedPage;
	enum	__Result
	{
		_OK			=1
		,_NG		=2
		,_Nothing	=3
	}Result;
	int64		NGCounts;
	int32		NGImageCount;
	bool		TimeOutBreak;
	bool		MaxErrorBreak;
	int32		ExecuterID;

	PageAndLayerFlagListContainer	CurrentCapturedPageLayer;
	QMutex				ChangingCameraInfo;
	volatile	bool	NowOnWorking;
	volatile	int		SignalCounter;

	ThreadOutputResult	ThreadOutputResultInst;

public:
	bool		TriggeredCapture;
	int			StackedCountInAutoMode;
	ResultInspection	*ResultInspectionToAccessInSlotAutomodeStart;
public:
	ExecuteInspectFast(QObject *parent ,EntryPointBase *_EntryPoint ,SeqControlParam *SeqParam);
	~ExecuteInspectFast(void);

	virtual	void	Initial(void);
	virtual	void	Release(void);
	virtual	void	CamRelease(void);

	virtual	bool	InitialCamera(int32 &ErrorCode)	override;
	virtual	bool	ChangeCameraInfo(CameraReqInfoAnyData *anydata=NULL)	override;
	virtual	bool	CheckCameraDLL(void)			override;
	virtual	bool	LoadDefault(void)				override;
	virtual	bool	LoadDefaultOldVer(void);
	virtual	bool	SaveDefault(void)				override;
	virtual	bool	Load(QIODevice *file)			override;
	virtual	bool	Save(QIODevice *file)			override;
	virtual	bool	IsLocalCamera(void)				override;

	virtual	int		GetAllocatedCameraCount(void)		override;
	virtual	CameraClass		*GetCamera(int n)			override;
	virtual	int		GetCameraDim(CameraClass *CamDim[])	override;
	virtual	void	SetCameraDim(CameraClass *CamDim[])	override;	

	//これらは外部からの操作
	virtual	void	GoInspect(void)					override;
	virtual	void	GoInspectWithoutCapture(void)	override;
	virtual	void	GoMasterCaptureOnly(void)		override;
	virtual	void	GoTargetCaptureOnly(void)		override;
	virtual	void	GoGray(void)					override;
	virtual	void	CamShowSetting(int CamNo)		override;
	virtual	bool	LoadCameraSetting(QIODevice *f)					override;
	virtual	void	ChangeLot(void)					override;
	virtual	void	ClearCameraBuffer(void)			override;

	bool	CapturePrepare(void);
	bool	CaptureStart(void);
	bool	CaptureHalt(void);

	int		GetCameraCount(void);
	static	ExecuteInspectFast	*StaticInstance		;
	volatile	bool	GoSlotAutomodeStart;
	void	EmitCalcDone(ResultInspection &Res,int tCurrentScanPhaseNumber ,int32 nStrategicNumber);
	void	EmitScanDone(ResultInspection &Res,int tCurrentScanPhaseNumber ,int32 nStrategicNumber);

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)		override;
	void	SetScanInfo(int ScanNumber ,bool ScanMastered);
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	override;
protected:
	virtual	void run()	override;

	CameraClass				**Cam;
	int						AllocatedCamNumb;
	
	int32		CameraErrorCode;
	bool		StatusCameraHalt;

public:
	SeqControlParam *SeqParam;
private:

	bool	CheckCamera(int32 &ErrorCode);
	int		CaptureGetState(void);
		//全てのカメラのビットＯＲ
		//	戻り値：	ビット０	１：撮影準備中
		//				ビット１	１：トリガー待機中
		//				ビット２	１：ＤＭＡ転送中
		//				ビット３	１：オーバーランエラー発生
		//				ビット４	１：その他エラー発生
	bool	CaptureGetMasterImage(int CStrategic,ListPhasePageLayerPack &CapturedList);
	bool	CaptureGetTargetImage(ListPhasePageLayerPack &CapturedList);
	void	OccurCamError(int CamStatus);
	void	ExecuteHalt(void);
	void				TestMP(void);
	QString	MakeCamDefaultName(void);
	void	SetCaptured(int CStrategic);
	void	FinishInspection(ResultInspection *Res,int32 nStrategicNumber);
	void	FinishScanning	(ResultInspection *Res,int32 nStrategicNumber);
	void	PreFinishInspection	(ResultInspection *Res,int32 nStrategicNumber);
	void	PreFinishScanning	(ResultInspection *Res,int32 nStrategicNumber);
signals:
 	void	SignalAutomodeStart();
	void	SignalCaptureHalt();
	void	SignalInspectionRefresh(LayersBase *base,int64 InspectionID);
	void	SignalInspectionOnTheWay(int64 InspectionID);
	void	SignalRunByEveryInspection(LayersBase *base,int64 InspectionID);
	void	SignalScanningRefresh(int64 InspectionID);
	void	SignalOccurError(int CamStatus);
private slots:
	void	SlotCaptureHalt();
	void	SlotInspectionRefresh(LayersBase *base,int64 InspectionID);
	void	SlotInspectionOnTheWay(int64 InspectionID);
	void	SlotRunByEveryInspection(LayersBase *base,int64 InspectionID);
	void	SlotScanningRefresh(int64 InspectionID);
	void	SlotOccurError(int CamStatus);
public slots:
	void	Exit(GUIFormBase *);
};


#endif
