/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
#include <QLocalServer>
#include <QLocalSocket>

#define Version_CameraMVSGigE   4

class ShowCameraDialog;


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
    Q_OBJECT

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

	QLocalServer    LocalServer;
	QLocalSocket    *LocalSocket;

public:
    int	        Version;
	QString		IPAddress;
	QString		UserName;
	int			DevNo;

    int         ExposureAuto;
    int         ExposureMode;
	float		ExposureTime;
	float		Gain;
	float		FrameRate;
	bool		bSoftWareTriggerCheck;
    int		    TriggerMode;                       // ch:触发模式 | en:Trigger Mode
    int			TriggerSource;                     // ch:触发源 | en:Trigger Source
    unsigned int    BinningHMode;
    unsigned int    BinningVMode;
    unsigned int    DecimationH ;
    unsigned int    DecimationV ;

    bool    ReverseX;
    bool    ReverseY;

    bool    AOIMode;
    unsigned int     AOIOffsetX;
    unsigned int     AOIOffsetY;
    unsigned int     AOIWidth;
    unsigned int     AOIHeight;
	bool    BlackLevelEnable;
	int     BlackLevel      ;
    int     WhiteBalance    ;

    int     BalanceRatioR               ;
    int     BalanceRatioG               ;
    int     BalanceRatioB               ;
    int     BalanceColorTemperatureMode ;

	int			CurrentNumber;
	CMvCamera	Cam;


    CameraMVSGigE(int CamNo ,const QString &ParamStr,LayersBase *base);
    ~CameraMVSGigE(void);

    bool    Initial(void);
    void    Release(void);
	bool	RecoverFromError(void);

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

	bool	SetUserSelect(int n);   //n=1:User1 ,n=2:User2 ,n=3:User3

    virtual	bool	Save(QIODevice *f)  override;
    virtual	bool	Load(QIODevice *f)  override;

	bool	GetIntValue	 (const char* strKey ,int64 &CurrentValue ,int64 &MaxValue ,int64 &MinValue);
    bool	GetIntValue	 (const char* strKey ,int   &CurrentValue ,int   &MaxValue ,int   &MinValue);
	bool	GetfloatValue(const char* strKey ,float &CurrentValue ,float &MaxValue ,float &MinValue);
	bool	GetBoolValue (const char* strKey ,bool &CurrentValue );
    bool	GetEnumValue (const char* strKey ,int &CurrentValue ,int EnumData[64],int &EnumCount);
    bool	GetEnumSymblic (const char* strKey ,int EnumValue ,QString &Str);

    bool    SetTriggerMode(bool b)  override;   // ch:设置触发模式 | en:Set Trigger Mode
    bool    GetTriggerMode(void)    override;
    int GetExposureTime();               // ch:设置曝光时间 | en:Set Exposure Time
    int SetExposure(); 
    int GetGain();                       // ch:设置增益 | en:Set Gain
    int SetGain();
    int GetFrameRate();                  // ch:设置帧率 | en:Set Frame Rate
    int SetFrameRate();
    int GetTriggerSource();              // ch:设置触发源 | en:Set Trigger Source
    int SetTriggerSource();
    int GetPixelFormat();                // ch:获取像素格式 | en:Get Pixel Format

    int     SetWhiteBalance();

    bool    SetBinningDecimation(void);
    bool    SetReverse(void);
    bool    SetAOI(void);
    bool    SetBlackLevel(void);

    bool    GetResolution(int &Width ,int &Height);

    bool    GetLine0(void);
	bool	SetLine1(bool b);

    bool    Set(ShowCameraDialog &D);

	virtual	bool	ShowInfoNumber(QByteArray &RetInfo);
	virtual	bool	SetInfoNumber(QByteArray &Info);

private slots:
	void    SlotNewConnection();
    void    SlotReadLocalSocket();
};
