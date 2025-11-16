#pragma once

#include "cameramvsgige_global.h"
#include <QList>
#include <QRgb>
#include <QDialog>
#include "XCameraHandle.h"
#include "XCameraCommon.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "MvCamera.h"
#include "MvCameraControl.h"


class CamBufferStack
{
public:
	BYTE	*Data;
	int		XLen,YLen;
	enum MvGvspPixelType	PixelFormat;
	int		FrameSize;

	CamBufferStack();
	~CamBufferStack();

	bool	ChangeInfo(int XLen ,int YLen);
	CamBufferStack	&operator=(const CamBufferStack &src);
};
#define	MaxCountCamBufferStack		10


class  CameraMVSGigE :public CameraHandle
{
    char                    m_chPixelFormat[1024];
    int                     m_nDeviceCombo;

    bool                    m_bOpenDevice;                        // ch:是否打开设备 | en:Whether to open device
    bool                    m_bStartGrabbing;                     // ch:是否开始抓图 | en:Whether to start grabbing

    MV_CC_DEVICE_INFO	    stDevInfo;
    MV_CC_DEVICE_INFO_LIST  m_stDevList;         
    MV_FRAME_OUT_INFO_EX    m_stImageInfo;

	CamBufferStack		*CamBuffDim[MaxCountCamBufferStack];
	volatile	int		CamBuffWPoint;
	volatile	int		CamBuffRPoint;
	volatile	int		CamBuffStockedCount;
	BYTE	*RGBBuff;
	int		XLen,YLen;
	QMutex	MutexImageSize;

public:
    int	        Version;
	QString		IPAddress;
	QString		UserName;
	int			DevNo;

	float		ExposureTime;
	float		Gain;
	float		FrameRate;
	bool		bSoftWareTriggerCheck;
    int			TriggerMode;                       // ch:触发模式 | en:Trigger Mode
    int			TriggerSource;                     // ch:触发源 | en:Trigger Source

	bool		ContinuousON;
	int			CurrentNumber;
	CMvCamera	Cam;


    CameraMVSGigE(int CamNo ,const QString &ParamStr,LayersBase *base);
    ~CameraMVSGigE(void);

    bool    Initial(void);

    bool	ChangeInfo(int XLen ,int YLen);
    void	CaptureImage(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo);
    bool	IsCaptured(void);

    bool    SetLineCount(int YLen);
    bool    ShowSetting(void);

    bool    PrepareCapture();
    bool    StartCapture();
    bool    SetAutoRepeat(bool b);
    bool    HaltCapture();
    bool    GetStatus(CameraScanInfo *Info);
    bool	StartCaptureContinuously(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info);
    void	GetImage(ImageBuffer *Buff[3] ,int LayerNumb);

    void    TransmitDirectly(GUIDirectMessage *packet);
    void    SpecifiedDirectly(SpecifiedBroadcaster *v);

    virtual	bool	Save(QIODevice *f)  override;
    virtual	bool	Load(QIODevice *f)  override;

	bool	GetIntValue	 (const char* strKey ,int64 &CurrentValue ,int64 &MaxValue ,int64 &MinValue);
	bool	GetfloatValue(const char* strKey ,float &CurrentValue ,float &MaxValue ,float &MinValue);
	bool	GetBoolValue (const char* strKey ,bool &CurrentValue );

    int SetTriggerMode();                // ch:设置触发模式 | en:Set Trigger Mode
    int GetTriggerMode();
    int GetExposureTime();               // ch:设置曝光时间 | en:Set Exposure Time
    int SetExposureTime(); 
    int GetGain();                       // ch:设置增益 | en:Set Gain
    int SetGain();
    int GetFrameRate();                  // ch:设置帧率 | en:Set Frame Rate
    int SetFrameRate();
    int GetTriggerSource();              // ch:设置触发源 | en:Set Trigger Source
    int SetTriggerSource();
    int GetPixelFormat();                // ch:获取像素格式 | en:Get Pixel Format
};
