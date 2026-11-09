#pragma once

#include "camerahikrobotgige_global.h"
#include "XTypeDef.h"
#include <QIODevice>
#include <QThread>
#include <QPixmap>
#include <QMutex>
#include "XMainSchemeMemory.h"
#include "XServiceForLayers.h"
#include "XCameraHandle.h"
#include "MvCamera.h"
#include "XCameraCommon.h"

class GUIDirectMessage;

class CamBufferStack
{
public:
	bool	Adopted;
	BYTE	*Data;
	int		XLen,YLen;
	enum MvGvspPixelType	PixelFormat;
	int		FrameSize;
	int		Number;
	double	Distance;
	float	CurrentPos[6];

	CamBufferStack();
	~CamBufferStack();

	bool	ChangeInfo(int XLen ,int YLen);
	CamBufferStack	&operator=(const CamBufferStack &src);
};
#define	MaxCountCamBufferStack		1200
//#define	MaxCountCapturedBufferStack	20

class CameraHIKRobotGigE :public CameraHandle
{
	Q_OBJECT

	int	Version;
	MV_CC_DEVICE_INFO_LIST  m_stDevList; 
	QString				UserName;
	int					DevNo;
	MV_CC_DEVICE_INFO	stDevInfo;
	char				m_chPixelFormat[MV_MAX_SYMBOLIC_LEN];

	CamBufferStack		*CamBuffDim[MaxCountCamBufferStack];
	QMutex				MutexCounter;
	volatile	int		CamBuffWPoint;
	volatile	int		CamBuffRPoint;
	volatile	int		CamBuffStockedCount;
	BYTE	*RGBBuff;
	int		XLen,YLen;
	QMutex	MutexImageSize;

	//CamBufferStack		*CapturedBuffDim[MaxCountCapturedBufferStack];
	//volatile	int		CapturedBuffWPoint;
	//volatile	int		CapturedBuffRPoint;
	IntList		CapturedRList;
	QMutex		MutexRList;
	bool		CaptureOneMode;
public:
	QString		IPAddress;
	float		ExposureTime;
	float		Gain;
	float		FrameRate;
    bool		TriggerMode;                       //
	int			TriggerSource;                     //0:Source Software 1;Line0	2::Line2
	int			TriggerEdge;						//0:Rising 1:Falling 2:Level High 3:Level Low 4:Any
	//bool		CaptureOne;
	bool		ContinuousON;
	int			CurrentNumber;
	double		CurrentDistance;
	CMvCamera	Cam;
	qint64		CapturedCount;
	volatile	bool	LockCapture;

    CameraHIKRobotGigE(int CamNo,LayersBase *Base);
	~CameraHIKRobotGigE(void);

	bool	Initial(int AllocCount,const QString &IPAddress);

	bool	ChangeInfo(int XLen ,int YLen);

	bool	Save(QIODevice *f)	override;
	bool	Load(QIODevice *f)	override;

	bool	StartCapture(void);
	bool	IsCaptured(void);
	bool	GetImage(ImageBuffer *Buff[3] ,int LayerNumb);
	bool	StartCaptureContinuously(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info);

	void	TransmitDirectly(GUIDirectMessage *packet);

	void	CaptureImage(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo);

    bool	SetTriggerMode(bool b)	override;	// ch:设置触发模式 | en:Set Trigger Mode
    bool	GetTriggerMode(void)	override;
	int		SetTriggerModeOff();

    int GetExposureTime();               // ch:设置曝光时间 | en:Set Exposure Time
    int SetExposureTime(); 
    int GetGain();                       // ch:设置增益 | en:Set Gain
    int SetGain();
    int GetFrameRate();                  // ch:设置帧率 | en:Set Frame Rate
    int SetFrameRate();
    int GetTriggerSource();              // ch:设置触发源 | en:Set Trigger Source
    int SetTriggerSource();
    int GetPixelFormat();                // ch:获取像素格式 | en:Get Pixel Format

	bool	GetIntValue	 (const char* strKey ,int64 &CurrentValue ,int64 &MaxValue ,int64 &MinValue);
	bool	GetfloatValue(const char* strKey ,float &CurrentValue ,float &MaxValue ,float &MinValue);
	bool	GetBoolValue (const char* strKey ,bool &CurrentValue );

	CamBufferStack		*GetCamBuffDim(int Index)	{	return CamBuffDim[Index];	}
	bool	ImageToTarget(int TargetPhase ,int TargetPage,int Index);

	void	GetImage(CamBufferStack *p,ImageBuffer *Buff[3] ,int LayerNumb);


signals:
	void	SignalCapturedImage(int CurrentCamBuffPoint);
};
