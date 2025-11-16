#pragma once

#include <QThread>
#include <QReadWriteLock>
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"
#include "XServiceForLayers.h"
#include "XResult.h"

class	SeqLocalParam;
class	CmdCaptureBegins;
class	GUIFormBase;
class	ResultInspection;


class RWExecuteCamera : public ExecuteInspectBase
{
	Q_OBJECT
	char	*DefaultCameraFileName;

	int32		ExecuterID;

	PageAndLayerFlagListContainer	CurrentCapturedPageLayer;
	QMutex				ChangingCameraInfo;
	volatile	bool	NowOnWorking;
	volatile	int		SignalCounter;

public:
	bool		TriggeredCapture;
	int			StackedCountInAutoMode;
public:
	RWExecuteCamera(QObject *parent ,EntryPointBase *_EntryPoint ,SeqLocalParam *SeqParam);
	~RWExecuteCamera(void);

	virtual	void	Initial(void);
	virtual	void	Release(void);
	virtual	void	CamRelease(void);

	virtual	bool	InitialCamera(int32 &ErrorCode)	override;
	virtual	bool	ChangeCameraInfo(CameraReqInfoAnyData *anydata=NULL)	override;
	virtual	bool	CheckCameraDLL(void)			override;
	virtual	bool	LoadDefault(void)				override;
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
	static	RWExecuteCamera	*StaticInstance		;
	volatile	bool	GoSlotAutomodeStart;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)		override;
	void	SetScanInfo(int ScanNumber ,bool ScanMastered);
	virtual	void	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	override;
protected:
	virtual	void run()	override;

	CameraClass				**Cam;
	int						AllocatedCamNumb;
	
	int32		CameraErrorCode;
	bool		StatusCameraHalt;

	void	EmitCalcDone(ResultInspection &Res,int tCurrentScanPhaseNumber ,int32 nStrategicNumber);

public:

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

	void	FinishInspection(ResultInspection *Res,int32 nStrategicNumber);
	void	PreFinishInspection	(ResultInspection *Res,int32 nStrategicNumber);
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
	void	SlotOccurError(int CamStatus);
public slots:
	void	Exit(GUIFormBase *);
};
