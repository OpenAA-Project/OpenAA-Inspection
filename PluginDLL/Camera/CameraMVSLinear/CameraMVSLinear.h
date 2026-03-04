#pragma once

#include "cameramvslinear_global.h"

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
#define	MaxCountCamBufferStack		2


class  CameraMVSLinear :public CameraHandle
{
    Q_OBJECT

    QString                 ParamStr;
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

    int         ExposureAuto;
    int         ExposureMode;
	float		ExposureTime;
	float		Gain;
	float		GainR;
    float		GainG;
    float		GainB;
	float		FrameRate;
    bool		LineTriggerMode;   
    int			LineTriggerSource; 
    bool        FrameTriggerMode;   
    int			FrameTriggerSource; 
    unsigned int    BinningHMode;
    unsigned int    BinningVMode;
    unsigned int    DecimationH ;
    unsigned int    DecimationV ;

    bool    ReverseX;
    bool    ReverseTDIY;

    bool    AOIMode;
    unsigned int     AOIOffsetX;
    unsigned int     AOIWidth;


	int			CurrentNumber;
	CMvCamera	Cam;


    CameraMVSLinear(int CamNo ,const QString &ParamStr,LayersBase *base);
    ~CameraMVSLinear(void);

    bool    Initial(void);

    virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines) override;
    bool	ChangeInfo(int XLen ,int YLen);
    bool    ReqSystemChange(CameraReqSystemChangeInfo &caminfo);
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
    bool	SetIntValue	 (const char* strKey ,int64 &CurrentValue);
    bool	GetIntValue	 (const char* strKey ,int   &CurrentValue ,int   &MaxValue ,int   &MinValue);
	bool	GetfloatValue(const char* strKey ,float &CurrentValue ,float &MaxValue ,float &MinValue);
	bool	GetBoolValue (const char* strKey ,bool &CurrentValue );
    bool	GetEnumValue (const char* strKey ,int &CurrentValue ,int EnumData[64],int &EnumCount);
    bool	GetEnumSymblic (const char* strKey ,int EnumValue ,QString &Str);

    bool    SetEnumValueByString(IN const char* strKey, IN const char* sValue);

    bool    SetTriggerMode(bool b)  override;   // ch:设置触发模式 | en:Set Trigger Mode
    bool    GetTriggerMode(void)    override;

    bool    SetLineTriggerMode(bool b)  ;
    bool    GetLineTriggerMode(void)    ;
    bool    SetFrameTriggerMode(bool b) ;
    bool    GetFrameTriggerMode(void)   ;

    int GetExposureTime();               // ch:设置曝光时间 | en:Set Exposure Time
    int SetExposure(); 
    bool    GetGain(float &fGainR,float &fGainG,float &fGainB);
    bool    SetRGBGain();
    int GetFrameRate();                  // ch:设置帧率 | en:Set Frame Rate
    int SetFrameRate();
    int GetPixelFormat();                // ch:获取像素格式 | en:Get Pixel Format

    bool    SetBinningDecimation(void);
    bool    SetReverse(void);
    bool    SetAOI(void);

    bool    GetResolution(int &Width ,int &Height);

    bool    GetLine0(void);
	bool	SetLine1(bool b);

};
