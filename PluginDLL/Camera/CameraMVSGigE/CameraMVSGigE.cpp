#include "CameraMVSGigE.h"
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"
#include "ShowCameraDialog.h"

static  void    FuncCameraOutput(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);



CamBufferStack::CamBufferStack()
{
    Data=NULL;
    XLen=0;
    YLen=0;
}
CamBufferStack::~CamBufferStack()
{
    if(Data!=NULL){
        delete  []Data;
        Data=NULL;
    }
    XLen=0;
    YLen=0;
}

bool	CamBufferStack::ChangeInfo(int _XLen ,int _YLen)
{
    if(XLen!=_XLen || YLen!=_YLen){
        if(Data!=NULL){
            delete  []Data;
        }
        XLen=_XLen;
        YLen=_YLen;
        Data=new BYTE[XLen*YLen*4+100];
    }
    return true; 
}
CamBufferStack	&CamBufferStack::operator=(const CamBufferStack &src)
{
    ChangeInfo(src.XLen ,src.YLen);
    memcpy(Data,src.Data,XLen*YLen*4+100);
    PixelFormat =src.PixelFormat;
    FrameSize   =src.FrameSize;
    return *this;
}


CameraMVSGigE::CameraMVSGigE(int CamNo ,const QString &ParamStr,LayersBase *base)
	:CameraHandle(CamNo,base)
{
	TriggerMode				= MV_TRIGGER_MODE_OFF;
	bSoftWareTriggerCheck	= true;
	TriggerSource			= MV_TRIGGER_SOURCE_SOFTWARE;

    CamBuffWPoint   =0;
    CamBuffRPoint   =0;
    CamBuffStockedCount=0;
    for(int i=0;i<MaxCountCamBufferStack;i++){
        CamBuffDim[i]=new CamBufferStack();
    }
    RGBBuff =NULL;
    XLen    =0;
    YLen    =0;
}
CameraMVSGigE::~CameraMVSGigE(void)
{
	Cam.Close();
    for(int i=0;i<MaxCountCamBufferStack;i++){
        delete  CamBuffDim[i];
        CamBuffDim[i]=NULL;
    }
}

bool    CameraMVSGigE::Initial(void)
{
	Version=CMvCamera::GetSDKVersion();

	DevNo=-1;
	
	int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE, &m_stDevList);
	if (MV_OK != nRet){
		return false;
	}

	// ch:将值加入到信息列表框中并显示出来 | en:Add value to the information list box and display
	for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++){
		MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
		if (NULL == pDeviceInfo)
		{
		    continue;
		}

		char strUserName[256] = {0};
		if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
		{
		    int nIp1 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
		    int nIp2 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
		    int nIp3 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
		    int nIp4 = (m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

		    if (strcmp("", (const char *)(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName)) != 0)
		    {
				memset(strUserName,0,256);
				sprintf_s(strUserName, 256, "%s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName,
					pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
		        UserName=strUserName;
		    }
		    else
		    {
		        memset(strUserName,0,256);
		        sprintf_s(strUserName, 256, "%s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
		            pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
		        UserName=strUserName;
		    }
			char strBuff[256];
		    sprintf_s(strBuff, 256, "%d.%d.%d.%d", nIp1, nIp2, nIp3, nIp4);
			if(IPAddress.isEmpty()==true){
				IPAddress=strBuff;
				DevNo=i;
				break;
			}
			else if(IPAddress==IPAddress){
				DevNo=i;
				break;
			}
		}
	}
	if(DevNo<0){
		return false;
	}
    GSleep(500);

	int	Ret=Cam.Open(m_stDevList.pDeviceInfo[DevNo]);
    if (MV_OK != Ret){
        return false;
    }

    int	QlyRet=Cam.SetBayerCvtQuality(1);
    if (MV_OK != QlyRet){
        return false;
    }

    int TrRet = SetTriggerMode();
    if (MV_OK != TrRet){
        return false;
    }
    if (m_stDevList.pDeviceInfo[DevNo]->nTLayerType == MV_GIGE_DEVICE){
        unsigned int nPacketSize = 0;
        nRet = Cam.GetOptimalPacketSize(&nPacketSize);
        if (nRet == MV_OK){
            nRet = Cam.SetIntValue("GevSCPSPacketSize",nPacketSize);
            if(nRet != MV_OK){
                return false;
            }
        }
        else{
            return false;
        }
    }
    int RegRet = Cam.RegisterImageCallBack(FuncCameraOutput, this);
    if (MV_OK != RegRet){
        return false;
    }

	Cam.GetDeviceInfo(&stDevInfo);

	return true;
}
static  void    FuncCameraOutput(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
{
    CameraMVSGigE  *Handle=(CameraMVSGigE *)pUser;
    Handle->CaptureImage(pData,pFrameInfo);
}

void	CameraMVSGigE::CaptureImage(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo)
{
    if(CamBuffDim[CamBuffWPoint]->Data!=NULL){
        MutexImageSize.lock();
        memcpy(CamBuffDim[CamBuffWPoint]->Data,pData,pFrameInfo->nFrameLen);
        CamBuffDim[CamBuffWPoint]->FrameSize=pFrameInfo->nFrameLen;
        CamBuffDim[CamBuffWPoint]->PixelFormat=pFrameInfo->enPixelType;

        CamBuffWPoint++;
        if(CamBuffWPoint>=MaxCountCamBufferStack){
            CamBuffWPoint=0;
        }
        CamBuffStockedCount++;
        if(CamBuffStockedCount>=MaxCountCamBufferStack){
            CamBuffStockedCount=MaxCountCamBufferStack;
        }
        MutexImageSize.unlock();
    }
}

bool	CameraMVSGigE::IsCaptured(void)
{
    MutexImageSize.lock();
    bool    Ret=(CamBuffStockedCount!=0)?true:false;
    MutexImageSize.unlock();
    return Ret;
}

bool	CameraMVSGigE::ChangeInfo(int _XLen ,int _YLen)
{
    MutexImageSize.lock();
    for(int i=0;i<MaxCountCamBufferStack;i++){
        CamBuffDim[i]->ChangeInfo(_XLen ,_YLen);
    }

    if(RGBBuff!=NULL){
        delete  []RGBBuff;
    }
    RGBBuff=new BYTE[_XLen*_YLen*4];
    XLen=_XLen;
    YLen=_YLen;
    MutexImageSize.unlock();

    return true;
}
bool    CameraMVSGigE::SetLineCount(int _YLen)
{
    ChangeInfo(XLen ,_YLen);
}
bool    CameraMVSGigE::ShowSetting(void)
{
	ShowCameraDialog	D(this);
	if(D.exec()==true){
        ExposureTime=D.ExposureTime;
        Gain        =D.Gain;
        SetExposureTime();
        SetGain();
		return true;
	}
	return false;
}

bool    CameraMVSGigE::PrepareCapture()
{
}
bool    CameraMVSGigE::StartCapture()
{
    return Cam.StartGrabbing();
}
bool    CameraMVSGigE::SetAutoRepeat(bool b)
{
    return true;
}
bool    CameraMVSGigE::HaltCapture()
{
    return true;
}

bool    CameraMVSGigE::GetStatus(CameraScanInfo *Info)
{
    return true;
}
bool	CameraMVSGigE::StartCaptureContinuously(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
{
    if(CamBuffStockedCount==0){
        return false;
    }

    GetImage(Buff ,BufferDimCounts);

    return true;
}
void	CameraMVSGigE::GetImage(ImageBuffer *Buff[3] ,int LayerNumb)
{
    //CamBufferStack		*p=CamBuffDim[CamBuffRPoint];
    CamBufferStack		*p=CamBuffDim[CamBuffRPoint];
               
    MV_CC_PIXEL_CONVERT_PARAM_EX stConvertParam = {0};
       
    MutexImageSize.lock();

    if(LayerNumb==3){
        stConvertParam.nWidth   = p->XLen;                 //ch:图像宽 | en:image width
        stConvertParam.nHeight  = p->YLen;               //ch:图像高 | en:image height
        stConvertParam.pSrcData = p->Data;                         //ch:输入数据缓存 | en:input data buffer
	    stConvertParam.nSrcDataLen = p->FrameSize;         //ch:输入数据大小 | en:input data size
        stConvertParam.enSrcPixelType = p->PixelFormat;    //ch:输入像素格式 | en:input pixel format
        stConvertParam.enDstPixelType = PixelType_Gvsp_RGB8_Packed;                         //ch:输出像素格式 | en:output pixel format
        stConvertParam.pDstBuffer = RGBBuff;                               //ch:输出数据缓存 | en:output data buffer
        stConvertParam.nDstBufferSize = XLen*YLen*4;                       //ch:输出缓存大小 | en:output buffer size

        int Ret=Cam.ConvertPixelType(&stConvertParam);
        if(Ret==MV_OK){
            BYTE    *s=RGBBuff;
            if(LayerNumb>=3){
                for(int y=0;y<YLen;y++){
                    BYTE    *dR=Buff[0]->GetY(y);
                    BYTE    *dG=Buff[1]->GetY(y);
                    BYTE    *dB=Buff[2]->GetY(y);
                    for(int x=0;x<XLen;x++){
                        *dR=*(s+0);
                        *dG=*(s+1);
                        *dB=*(s+2);
                        s+=3;
                        dR++;
                        dG++;
                        dB++;
                    }
                }
            }
        }
    }
    else if(LayerNumb==1){
        stConvertParam.nWidth   = p->XLen;                 //ch:图像宽 | en:image width
        stConvertParam.nHeight  = p->YLen;               //ch:图像高 | en:image height
        stConvertParam.pSrcData = p->Data;                         //ch:输入数据缓存 | en:input data buffer
        stConvertParam.nSrcDataLen = p->FrameSize;         //ch:输入数据大小 | en:input data size
        stConvertParam.enSrcPixelType = p->PixelFormat;    //ch:输入像素格式 | en:input pixel format
        stConvertParam.enDstPixelType = PixelType_Gvsp_Mono8;                         //ch:输出像素格式 | en:output pixel format
        stConvertParam.pDstBuffer = RGBBuff;                               //ch:输出数据缓存 | en:output data buffer
        stConvertParam.nDstBufferSize = XLen*YLen;                       //ch:输出缓存大小 | en:output buffer size
        int Ret=Cam.ConvertPixelType(&stConvertParam);
        if(Ret==MV_OK){
            BYTE    *s=RGBBuff;
            BYTE    *dR;
            for(int y=0;y<YLen;y++){
                dR=Buff[0]->GetY(y);
                for(int x=0;x<XLen;x++){
                    *dR=*s;
                    s++;
                    dR++;
                }
            }
        }
	}
    CamBuffRPoint++;
    if(CamBuffRPoint>=MaxCountCamBufferStack){
        CamBuffRPoint=0;
    }
    CamBuffStockedCount--;
    if(CamBuffStockedCount<0)
        CamBuffStockedCount=0;

    MutexImageSize.unlock();
}

void    CameraMVSGigE::TransmitDirectly(GUIDirectMessage *packet)
{
}
void    CameraMVSGigE::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
}

bool	CameraMVSGigE::Save(QIODevice *f)
{
	if(::Save(f,ExposureTime)==false)	        return false;
	if(::Save(f,Gain)==false)			        return false;
    if(::Save(f,FrameRate)==false)			    return false;
    if(::Save(f,bSoftWareTriggerCheck)==false)	return false;
    if(::Save(f,TriggerMode)==false)			return false;
    if(::Save(f,TriggerSource)==false)			return false;

	return true;
}
bool	CameraMVSGigE::Load(QIODevice *f)
{
	if(::Load(f,ExposureTime)==false)	return false;
	if(::Load(f,Gain)==false)			return false;
    if(::Load(f,FrameRate)==false)			    return false;
    if(::Load(f,bSoftWareTriggerCheck)==false)	return false;
    if(::Load(f,TriggerMode)==false)			return false;
    if(::Load(f,TriggerSource)==false)			return false;

    SetTriggerMode();
    SetExposureTime();
    SetGain();
    SetFrameRate();
    SetTriggerSource();

	return true;
}

// ch:获取触发模式 | en:Get Trigger Mode
int CameraMVSGigE::GetTriggerMode()
{
    MVCC_ENUMVALUE stEnumValue = {0};

    int nRet = Cam.GetEnumValue("TriggerMode", &stEnumValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    TriggerMode = stEnumValue.nCurValue;

    return MV_OK;
}

// ch:设置触发模式 | en:Set Trigger Mode
int CameraMVSGigE::SetTriggerMode()
{
    return Cam.SetEnumValue("TriggerMode", TriggerMode);
}

// ch:获取曝光时间 | en:Get Exposure Time
int CameraMVSGigE::GetExposureTime()
{
    MVCC_FLOATVALUE stFloatValue = {0};

    int nRet = Cam.GetFloatValue("ExposureTime", &stFloatValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    ExposureTime= stFloatValue.fCurValue;

    return MV_OK;
}

// ch:设置曝光时间 | en:Set Exposure Time
int CameraMVSGigE::SetExposureTime()
{
    Cam.SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);

    return Cam.SetFloatValue("ExposureTime", (float)ExposureTime);
}

// ch:获取增益 | en:Get Gain
int CameraMVSGigE::GetGain()
{
    MVCC_FLOATVALUE stFloatValue = {0};

    int nRet = Cam.GetFloatValue("Gain", &stFloatValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }
    Gain = stFloatValue.fCurValue;

    return MV_OK;
}

// ch:设置增益 | en:Set Gain
int CameraMVSGigE::SetGain()
{
    // ch:设置增益前先把自动增益关闭，失败无需返回
    //en:Set Gain after Auto Gain is turned off, this failure does not need to return
    Cam.SetEnumValue("GainAuto", 0);

    return Cam.SetFloatValue("Gain", (float)Gain);
}

// ch:获取帧率 | en:Get Frame Rate
int CameraMVSGigE::GetFrameRate()
{
    MVCC_FLOATVALUE stFloatValue = {0};

    int nRet = Cam.GetFloatValue("ResultingFrameRate", &stFloatValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }
    FrameRate = stFloatValue.fCurValue;

    return MV_OK;
}

// ch:设置帧率 | en:Set Frame Rate
int CameraMVSGigE::SetFrameRate()
{
    int nRet = Cam.SetBoolValue("AcquisitionFrameRateEnable", true);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    return Cam.SetFloatValue("AcquisitionFrameRate", (float)FrameRate);
}

// ch:获取触发源 | en:Get Trigger Source
int CameraMVSGigE::GetTriggerSource()
{
    MVCC_ENUMVALUE stEnumValue = {0};

    int nRet = Cam.GetEnumValue("TriggerSource", &stEnumValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    if ((unsigned int)MV_TRIGGER_SOURCE_SOFTWARE == stEnumValue.nCurValue)
    {
        bSoftWareTriggerCheck = true;
    }
    else
    {
        bSoftWareTriggerCheck = false;
    }

    return MV_OK;
}

// ch:设置触发源 | en:Set Trigger Source
int CameraMVSGigE::SetTriggerSource()
{
    int nRet = MV_OK;
    if (bSoftWareTriggerCheck==true)
    {
        TriggerSource = MV_TRIGGER_SOURCE_SOFTWARE;
        nRet = Cam.SetEnumValue("TriggerSource", TriggerSource);
        if (MV_OK != nRet)
        {
            return nRet;
        }
    }
    else
    {
        TriggerSource = MV_TRIGGER_SOURCE_LINE0;
        nRet = Cam.SetEnumValue("TriggerSource", TriggerSource);
        if (MV_OK != nRet)
        {
            return nRet;
        }
    }

    return nRet;
}

// 该接口只展示GetEnumEntrySymbolic接口的使用方法
int CameraMVSGigE::GetPixelFormat()
{
    MVCC_ENUMVALUE stEnumValue = {0};
    MVCC_ENUMENTRY stPixelFormatInfo = {0};

    int nRet = Cam.GetEnumValue("PixelFormat", &stEnumValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    stPixelFormatInfo.nValue = stEnumValue.nCurValue;
    nRet = Cam.GetEnumEntrySymbolic("PixelFormat", &stPixelFormatInfo);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    strcpy_s(m_chPixelFormat, MV_MAX_SYMBOLIC_LEN, stPixelFormatInfo.chSymbolic);

    return MV_OK;
}
bool	CameraMVSGigE::GetIntValue	 (const char* strKey ,int64 &CurrentValue ,int64 &MaxValue ,int64 &MinValue)
{
    MVCC_INTVALUE_EX    IntValue;
    int Ret=Cam.GetIntValue(strKey, &IntValue);
    if(Ret==MV_OK){
        CurrentValue=IntValue.nCurValue;
        MaxValue    =IntValue.nMax;
        MinValue    =IntValue.nMin;
        return true;
    }
    return false;
}
bool	CameraMVSGigE::GetfloatValue(const char* strKey ,float &CurrentValue ,float &MaxValue ,float &MinValue)
{
    MVCC_FLOATVALUE    FloatValue;
    int Ret=Cam.GetFloatValue(strKey, &FloatValue);
    if(Ret==MV_OK){
        CurrentValue=FloatValue.fCurValue;
        MaxValue    =FloatValue.fMax;
        MinValue    =FloatValue.fMin;
        return true;
    }
    return false;
}
bool	CameraMVSGigE::GetBoolValue (const char* strKey ,bool &CurrentValue )
{
    MVCC_FLOATVALUE    FloatValue;
    int Ret=Cam.GetBoolValue(strKey, &CurrentValue);
    if(Ret==MV_OK){
        return true;
    }
    return false;
}


/* ////////////////////////////////////////////////////////////////////////////////////////////////
 DLL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////// */
WORD DLL_GetDLLType(void)
//	return	DLL type for CameraDLL
{
	return(DLLCameraMode);
}

bool _cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str=/**/"MVS Camera GigE";
	return(true);
}

WORD _cdecl	DLL_GetVersion(void)
//	return Camera DLL version
{
	return(1);
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

extern int cameraCallbackCount;

/*
   make
   */

CameraHandle *_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
{
	static bool first = true;
	int ret;

	if(CameraNoInThisComputer==0){
		MV_CC_Initialize();
	}
	CameraMVSGigE	*v=new CameraMVSGigE(CameraNoInThisComputer,CameraParameter,base);
    if(v->Initial()==false){
        return NULL;
    }
	return v;
}

/*
   make
   */
bool _cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	CameraMVSGigE	*BaslerSystemInst=(CameraMVSGigE	*)handle;
	if(BaslerSystemInst!=NULL){
		delete	BaslerSystemInst;
		BaslerSystemInst=NULL;
	}
	CMvCamera::FinalizeSDK();
	return(true);
}

bool _cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	bool	Ret=false;
	if(Px!=NULL){
		Ret=true;
		if(Px->Load(&str)==false)
			Ret=false;
	}
	return Ret;
}

bool _cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	bool	Ret=false;
	if(Px!=NULL){
		Ret=true;
		if(Px->Save(&str)==false)
			Ret=false;
	}
	return Ret;
}

DEFFUNCEX	bool	_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	if(Px!=NULL){
		Px->ChangeInfo(caminfo.XLen ,caminfo.YLen);
	}

	return true;
}


bool _cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	if(Px->ShowSetting()==true){
		return(true);
	}
	return(false);
}

bool	_cdecl	DLL_SetQuickProperty(CameraHandle *handle,CameraQuickProperty Attr, double RelativeValue)
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	//return Px->SetQuickProperty(Attr, RelativeValue);
	return true;
}


bool _cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	return  Px->PrepareCapture();
}

bool _cdecl	DLL_StartCapture(CameraHandle *handle, CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	return Px->StartCapture();
}

bool _cdecl	DLL_SetAutoRepeat(CameraHandle *handle ,bool RepeatON)
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	Px->SetAutoRepeat(RepeatON);
	return true;
}
/*
   make
   おそらくそのまま
   */
bool _cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;

	 Px->HaltCapture();
	return true;	//Px->_sapera->unlink();
}

DEFFUNCEX	int _cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info)
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	if(Px->IsCaptured()==true){
        return 0;
    }
	return 2;
}

bool _cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

bool _cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	Px->GetImage(Buff,BufferDimCounts);
    return true;
}
DEFFUNCEX	void	_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	Px->TransmitDirectly(packet);
}
DEFFUNCEX	void	_cdecl	DLL_SpecifiedDirectly(CameraHandle *handle ,SpecifiedBroadcaster *v)
{
	CameraMVSGigE		*Px=(CameraMVSGigE *)handle;
	Px->SpecifiedDirectly(v);
}
