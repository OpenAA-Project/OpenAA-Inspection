#include "CameraHIKRobotGigE.h"
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "SettingCameraDialog.h"
#include "XCriticalFunc.h"
#include <QMessageBox>
#include <omp.h>
#include "XCameraRobotCommon.h"

#ifndef _MSC_VER
#include <cstdio>
#include <cstring>
#define sprintf_s snprintf
#define strcpy_s(dest, destsz, src) strncpy(dest, src, destsz)
#endif

//=========================================================

DEFFUNCEX   WORD DLL_GetDLLType(void)
//	return	DLL type for CameraDLL
{
	return(DLLCameraMode);
}

DEFFUNCEX   bool _cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="HikRobot-MVCamera";
	return(true);
}

DEFFUNCEX   WORD _cdecl	DLL_GetVersion(void)
//	return Camera DLL version
{
	return(1);
}

DEFFUNCEX	CameraHandle*_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
//	CamInfo : Set unique several attributes in this function
{
	CMvCamera::InitSDK();

	CameraHIKRobotGigE	*cam=new CameraHIKRobotGigE(CameraNoInThisComputer,base);
	if(cam->Initial(1000,CameraParameter)==false){
		return NULL;
	}
	return cam;
}

DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
    CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
    return C->ChangeInfo(caminfo.XLen,caminfo.YLen);
}


DEFFUNCEX	bool		_cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	CameraHIKRobotGigE	*BaslerSystemInst=(CameraHIKRobotGigE	*)handle;
	if(BaslerSystemInst!=NULL){
		delete	BaslerSystemInst;
		BaslerSystemInst=NULL;
	}
	CMvCamera::FinalizeSDK();

	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
	return C->Load(&str);
}

DEFFUNCEX	bool		_cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
	return C->Save(&str);
}

DEFFUNCEX	bool		_cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
	SettingCameraDialog	D(C);
	if(D.exec()==(int)true){
        C->ExposureTime =D.ExposureTime;
        C->Gain         =D.Gain;
		C->TriggerMode  = D.TriggerMode;
		C->TriggerSource = D.TriggerSource;
        C->SetExposureTime();
        C->SetGain();
		return true;
	}
	return false;
}

DEFFUNCEX	bool		_cdecl	DLL_PrepareCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	//CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
	//C->StartCapture();
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_StartCapture(CameraHandle *handle ,CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
	//C->Camera.StartGrabbing(1);
	C->StartCapture();
    return true;
}


DEFFUNCEX	bool		_cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	int			_cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info)
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
//					Bit5		1:Start DMA transfer
//								Set bit soon after DMA starts in frame capturing
//								Set bit soon after one DMA frame starts in continuous capturing
//								This bit must be kept until DLL_ClearBit
//					Bit6		1:Finish DMA transfer
//								Set bit soon after DMA finishes in frame capturing
//								Set bit soon after 1 DMA frame finishes in continuous capturing
//								This bit must be kept until DLL_ClearBit
{

	CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
	if(C->IsCaptured()==true){
	    return 0;
    }
    return 1;
}
DEFFUNCEX	bool		_cdecl	DLL_StartCaptureContinuously(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
//	Start capruting till DLL_StopCaptureContinuously. 
//	This function must return soon
//	if process fails, it returns false
{
    CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
    return C->StartCaptureContinuously(Buff,BufferDimCounts ,Info);
}

DEFFUNCEX	int			_cdecl	DLL_GetCurrentLineCount(CameraHandle *handle)
//	Return captured line count on capturing mode
//	This must return quickly.
{
	return 0;
}

DEFFUNCEX	bool		_cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_ClearBit(CameraHandle *handle)
//	Clear status bit
//	This function must return soon
//	if process fails, it returns false
//	This function is used to reset Bit5 of GetStatus from application
{
	return true;
}

DEFFUNCEX	bool		_cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
	return C->GetImage(Buff,BufferDimCounts);
}

DEFFUNCEX	bool		_cdecl	DLL_ReqCameraError(CameraHandle *handle ,QStringList &Msg)
//	Request camera error from system
//	This function must set error message into Msg when any errors occur
//	this function is called after any functions return false
{
	return true;
}

DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
	CameraHIKRobotGigE	*C=(CameraHIKRobotGigE *)handle;
	C->TransmitDirectly(packet);
}

//===============================================================

CamBufferStack::CamBufferStack()
{
    Adopted=false;
    Data=NULL;
    XLen=0;
    YLen=0;
    Number  =-1;
    Distance=99999999;
    for(int i=0;i<6;i++){
        CurrentPos[i]=0;
    }
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
    Adopted     =src.Adopted;
    ChangeInfo(src.XLen ,src.YLen);
    memcpy(Data,src.Data,XLen*YLen*4+100);
    PixelFormat =src.PixelFormat;
    FrameSize   =src.FrameSize;
    Number      =src.Number;
    Distance    =src.Distance;
    for(int i=0;i<6;i++){
        CurrentPos[i]=src.CurrentPos[i];
    }
    return *this;
}


CameraHIKRobotGigE::CameraHIKRobotGigE(int CamNo,LayersBase *Base)
		:CameraHandle(CamNo,Base)
{
	TriggerMode				= MV_TRIGGER_MODE_OFF;
	TriggerSource			= MV_TRIGGER_SOURCE_SOFTWARE;
	TriggerEdge             = 0;

    CamBuffWPoint   =0;
    CamBuffRPoint   =0;
    CamBuffStockedCount=0;
    for(int i=0;i<MaxCountCamBufferStack;i++){
        CamBuffDim[i]=new CamBufferStack();
    }
    //CapturedBuffWPoint=0;
    //CapturedBuffRPoint=0;
    //for(int i=0;i<MaxCountCapturedBufferStack;i++){
    //    CapturedBuffDim[i]=new CamBufferStack();
    //}
    RGBBuff=NULL;
    ContinuousON    =false;
    CapturedCount   =0;
    LockCapture     =false;
    CaptureOneMode  =false;
    //CaptureOne      =false;
}
CameraHIKRobotGigE::~CameraHIKRobotGigE(void)
{
	Cam.Close();
    for(int i=0;i<MaxCountCamBufferStack;i++){
        delete  CamBuffDim[i];
        CamBuffDim[i]=NULL;
    }
    //for(int i=0;i<MaxCountCapturedBufferStack;i++){
    //    delete  CapturedBuffDim[i];
    //    CapturedBuffDim[i]=NULL;
    //}
}

static  void    FuncCameraOutput(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);

bool	CameraHIKRobotGigE::Initial(int AllocCount,const QString &_IPAddress)
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
				snprintf(strUserName, 256, "%s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName,
					pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
		        UserName=strUserName;
		    }
		    else
		    {
		        memset(strUserName,0,256);
		        snprintf(strUserName, 256, "%s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
		            pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
		        UserName=strUserName;
		    }
			char strBuff[256];
		    snprintf(strBuff, 256, "%d.%d.%d.%d", nIp1, nIp2, nIp3, nIp4);
			IPAddress=strBuff;
			if(_IPAddress.isEmpty()==true){
				DevNo=i;
				break;
			}
			else if(_IPAddress==IPAddress){
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

    bool TrRet = SetTriggerMode(TriggerMode);
    if (true != TrRet){
        return false;
    }
    int TsrRet = SetTriggerSource();
    if (MV_OK != TsrRet){
        return false;
    }
    GetTriggerMode();
    GetTriggerSource();

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

    nRet = Cam.SetEnumValue("BalanceWhiteAuto", (int)0);
    if (MV_OK != nRet){
        return nRet;
    }

	Cam.GetDeviceInfo(&stDevInfo);

	return true;
}
/*
Register an image data callback, supporting getting chunk information. 
Parameters
handle [IN] Device handle.  
cbOutput [IN] Image data callback function.  
pUser [IN] User data.  
ReturnsReturn MV_OK for success, and return corresponding error code for failure. 
RemarksAfter calling MV_CC_CreateHandle() , call this API to set image data callback function.
There are two available image data acquisition modes, and cannot be used together: 
Mode 1: Call MV_CC_RegisterImageCallBack() to set image data callback function, 
and then call MV_CC_StartGrabbing() to start acquisition. 
The acquired image data will be returned in the set callback function.
Mode 2: Call MV_CC_StartGrabbing() to start acquisition, and then call MV_CC_GetOneFrame() repeatedly in application layer to get frame data of specified pixel format. When getting frame data, the frequency of calling this API should be controlled by upper layer application according to frame rate. 
This API is not supported by devices in MV_CAMERALINK_DEVICE() . ExamplesChunkData.cpp, Events_Interface.cpp, Grab_Asynchronous.cpp, Grab_Callback.cpp, InterfaceAndDeviceDemo.cpp, LensShadingCorrection.cpp, and ParametrizeCamera_LineScanIOSettings.cpp.
*/
static  void    FuncCameraOutput(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
{
    CameraHIKRobotGigE  *Handle=(CameraHIKRobotGigE *)pUser;
    Handle->CaptureImage(pData,pFrameInfo); 
}

void	CameraHIKRobotGigE::CaptureImage(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo)
{
    if(CamBuffDim[CamBuffWPoint]->Data!=NULL
    && LockCapture==false){
        CapturedCount++;
        MutexImageSize.lock();
        memcpy(CamBuffDim[CamBuffWPoint]->Data,pData,pFrameInfo->nFrameLen);
        CamBuffDim[CamBuffWPoint]->FrameSize    =pFrameInfo->nFrameLen;
        CamBuffDim[CamBuffWPoint]->PixelFormat  =pFrameInfo->enPixelType;
        CamBuffDim[CamBuffWPoint]->Number       =CurrentNumber;
        CamBuffDim[CamBuffWPoint]->Distance     =CurrentDistance;
        MutexImageSize.unlock();

        emit    SignalCapturedImage(CamBuffWPoint);

        MutexCounter.lock();
        CamBuffWPoint++;
        if(CamBuffWPoint>=MaxCountCamBufferStack){
            CamBuffWPoint=0;
        }
        CamBuffStockedCount++;
        if(CamBuffStockedCount>=MaxCountCamBufferStack){
            CamBuffStockedCount=MaxCountCamBufferStack;
        }
        MutexCounter.unlock();
    }
}

bool	CameraHIKRobotGigE::ChangeInfo(int _XLen ,int _YLen)
{
    MutexImageSize.lock();
    for(int i=0;i<MaxCountCamBufferStack;i++){
        CamBuffDim[i]->ChangeInfo(_XLen ,_YLen);
    }
    //for(int i=0;i<MaxCountCapturedBufferStack;i++){
    //    CapturedBuffDim[i]->ChangeInfo(_XLen ,_YLen);
    //}

    if(RGBBuff!=NULL){
        delete  []RGBBuff;
    }
    RGBBuff=new BYTE[_XLen*_YLen*4];
    XLen=_XLen;
    YLen=_YLen;
    MutexImageSize.unlock();

    return true;
}

bool	CameraHIKRobotGigE::Save(QIODevice *f)
{
	if(::Save(f,ExposureTime)==false)	return false;
	if(::Save(f,Gain)==false)			return false;
	if(::Save(f,TriggerMode )==false)   return false;
	if(::Save(f,TriggerSource)==false)  return false;
    if(::Save(f,TriggerEdge )==false)   return false;

	return true;
}
bool	CameraHIKRobotGigE::Load(QIODevice *f)
{
	if(::Load(f,ExposureTime)==false)	return false;
	if(::Load(f,Gain)==false)			return false;
	if(::Load(f,TriggerMode )==false)   return false;
	if(::Load(f,TriggerSource)==false)  return false;
    if(::Load(f,TriggerEdge )==false)   return false;

    SetExposureTime();
    SetGain();
    bool TrRet = SetTriggerMode(TriggerMode);
    if (true != TrRet){
        return false;
    }
    int TsrRet = SetTriggerSource();
    if (MV_OK != TsrRet){
        return false;
    }
    GetTriggerMode();
    GetTriggerSource();
	return true;
}

bool	CameraHIKRobotGigE::StartCapture(void)
{
    return Cam.StartGrabbing();
}
bool	CameraHIKRobotGigE::IsCaptured(void)
{
    if(CamBuffWPoint!=CamBuffRPoint && CaptureOneMode==true){
    //if(CapturedRList.GetFirst()!=NULL){
        CaptureOneMode=false;
        return true;
    }

    return false;
}

bool	CameraHIKRobotGigE::StartCaptureContinuously(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
{
    //if(CamBuffWPoint==CamBuffRPoint){
    //    return false;
    //}
    int Rp=CamBuffWPoint-1;
    if(Rp<0){
        Rp=MaxCountCamBufferStack-1;
    }
    
    CamBufferStack		*p=CamBuffDim[Rp];
               
    MV_CC_PIXEL_CONVERT_PARAM_EX stConvertParam = {0};

    MutexImageSize.lock();

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
        if(BufferDimCounts>=3){
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
        else
        if(BufferDimCounts==2){
            for(int y=0;y<YLen;y++){
                BYTE    *dR=Buff[0]->GetY(y);
                BYTE    *dG=Buff[1]->GetY(y);
                for(int x=0;x<XLen;x++){
                    *dR=*(s+0);
                    *dG=*(s+1);
                    s+=3;
                    dR++;
                    dG++;
                }
            }
        }
        else
        if(BufferDimCounts==1){
            for(int y=0;y<YLen;y++){
                BYTE    *dR=Buff[0]->GetY(y);
                for(int x=0;x<XLen;x++){
                    *dR=*(s+0);
                    s+=3;
                    dR++;
                }
            }
        }
    }
    CamBuffRPoint++;
    if(CamBuffRPoint>=MaxCountCamBufferStack){
        CamBuffRPoint=0;
    }
    MutexImageSize.unlock();
    return true;
}
bool	CameraHIKRobotGigE::GetImage(ImageBuffer *Buff[3] ,int LayerNumb)
{
    //CamBufferStack		*p=CamBuffDim[CamBuffRPoint];
    //IntClass    *R=CapturedRList.GetFirst();
    //if(R==NULL){
    //    return false;
    //}
    //MutexRList.lock();
    //int RPoint=R->GetValue();
    //CapturedRList.RemoveList(R);
    //MutexRList.unlock();
    //CamBufferStack		*p=CamBuffDim[RPoint];
               
    int RIndex=CamBuffWPoint-1;
    if(RIndex<0){
        RIndex=MaxCountCamBufferStack-1;
	}
    CamBufferStack		*p=CamBuffDim[RIndex];

    MutexImageSize.lock();
    p->Adopted=true;

    GetImage(p,Buff ,LayerNumb);

    CamBuffRPoint++;
    if(CamBuffRPoint>=MaxCountCamBufferStack){
        CamBuffRPoint=0;
    }
    MutexImageSize.unlock();
    return true;
}

void	CameraHIKRobotGigE::GetImage(CamBufferStack *p,ImageBuffer *Buff[3] ,int LayerNumb)
{
    MV_CC_PIXEL_CONVERT_PARAM_EX stConvertParam = {0};
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
        else
        if(LayerNumb==2){
            for(int y=0;y<YLen;y++){
                BYTE    *dR=Buff[0]->GetY(y);
                BYTE    *dG=Buff[1]->GetY(y);
                for(int x=0;x<XLen;x++){
                    *dR=*(s+0);
                    *dG=*(s+1);
                    s+=3;
                    dR++;
                    dG++;
                }
            }
        }
        else
        if(LayerNumb==1){
            for(int y=0;y<YLen;y++){
                BYTE    *dR=Buff[0]->GetY(y);
                for(int x=0;x<XLen;x++){
                    *dR=*(s+0);
                    s+=3;
                    dR++;
                }
            }
        }
    }
}


// ch:获取触发模式 | en:Get Trigger Mode
bool CameraHIKRobotGigE::GetTriggerMode(void)
{
    MVCC_ENUMVALUE stEnumValue = {0};

    int nRet = Cam.GetEnumValue("TriggerMode", &stEnumValue);
    if (MV_OK != nRet)
    {
        return false;
    }

    //TriggerMode = stEnumValue.nCurValue;
    if((unsigned int)MV_TRIGGER_MODE_ON == stEnumValue.nCurValue)
    {
        return true;
    }
    else
    {
        return false;
	}
}

// ch:设置触发模式 | en:Set Trigger Mode
bool CameraHIKRobotGigE::SetTriggerMode(bool b)
{
    TriggerMode=b;
    if(TriggerMode==true){
       if(Cam.SetEnumValue("TriggerMode", (int)MV_TRIGGER_MODE_ON)==MV_OK){
           return true;
	   }
       else{
           return false;
	   }
    }
    else{
        if(Cam.SetEnumValue("TriggerMode", (int)MV_TRIGGER_MODE_OFF)==MV_OK){
           return true;
	   }
       else{
           return false;
	   }
    }
}

int CameraHIKRobotGigE::SetTriggerModeOff()
{
    return Cam.SetEnumValue("TriggerMode", (int)MV_TRIGGER_MODE_OFF);
}

// ch:获取曝光时间 | en:Get Exposure Time
int CameraHIKRobotGigE::GetExposureTime()
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
int CameraHIKRobotGigE::SetExposureTime()
{
    Cam.SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);

    return Cam.SetFloatValue("ExposureTime", (float)ExposureTime);
}

// ch:获取增益 | en:Get Gain
int CameraHIKRobotGigE::GetGain()
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
int CameraHIKRobotGigE::SetGain()
{
    // ch:设置增益前先把自动增益关闭，失败无需返回
    //en:Set Gain after Auto Gain is turned off, this failure does not need to return
    Cam.SetEnumValue("GainAuto", 0);

    return Cam.SetFloatValue("Gain", (float)Gain);
}

// ch:获取帧率 | en:Get Frame Rate
int CameraHIKRobotGigE::GetFrameRate()
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
int CameraHIKRobotGigE::SetFrameRate()
{
    int nRet = Cam.SetBoolValue("AcquisitionFrameRateEnable", true);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    return Cam.SetFloatValue("AcquisitionFrameRate", (float)FrameRate);
}

// ch:获取触发源 | en:Get Trigger Source
int CameraHIKRobotGigE::GetTriggerSource()
{
    MVCC_ENUMVALUE stEnumValue = {0};

    int nRet = Cam.GetEnumValue("TriggerSource", &stEnumValue);
    if (MV_OK != nRet)
    {
        return nRet;
    }

    if ((unsigned int)MV_TRIGGER_SOURCE_SOFTWARE == stEnumValue.nCurValue)
    {
        TriggerSource = 0;
    }
    else if(MV_TRIGGER_SOURCE_LINE0==stEnumValue.nCurValue){
        TriggerSource = 1;
    }
    else if(MV_TRIGGER_SOURCE_LINE2==stEnumValue.nCurValue){
        TriggerSource = 2;
    }
    else{
        TriggerSource = 0;
    }

    return MV_OK;
}

// ch:设置触发源 | en:Set Trigger Source
int CameraHIKRobotGigE::SetTriggerSource()
{
    int nRet = MV_OK;
    if (TriggerMode==true){
        if(TriggerSource==0){
            nRet = Cam.SetEnumValue("TriggerSource", (int)MV_TRIGGER_SOURCE_SOFTWARE);
            if (MV_OK != nRet){
                return nRet;
            }
        }

        if(TriggerSource==1){
            nRet = Cam.SetEnumValue("TriggerSource", (int)MV_TRIGGER_SOURCE_LINE0);
            if (MV_OK != nRet)
            {
                return nRet;
            }
        }
        else if(TriggerSource==2){
            nRet = Cam.SetEnumValue("TriggerSource", (int)MV_TRIGGER_SOURCE_LINE2);
            if (MV_OK != nRet)
            {
                return nRet;
            }
        }
    }
    else
    {
        nRet = Cam.SetEnumValue("TriggerSource", (int)MV_TRIGGER_SOURCE_SOFTWARE);
        if (MV_OK != nRet){
            return nRet;
        }
    }

    return nRet;
}

// 该接口只展示GetEnumEntrySymbolic接口的使用方法
int CameraHIKRobotGigE::GetPixelFormat()
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

    strncpy(m_chPixelFormat, stPixelFormatInfo.chSymbolic, MV_MAX_SYMBOLIC_LEN - 1);
    m_chPixelFormat[MV_MAX_SYMBOLIC_LEN - 1] = '\0';

    return MV_OK;
}
bool	CameraHIKRobotGigE::GetIntValue	 (const char* strKey ,int64 &CurrentValue ,int64 &MaxValue ,int64 &MinValue)
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
bool	CameraHIKRobotGigE::GetfloatValue(const char* strKey ,float &CurrentValue ,float &MaxValue ,float &MinValue)
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
bool	CameraHIKRobotGigE::GetBoolValue (const char* strKey ,bool &CurrentValue )
{
    MVCC_FLOATVALUE    FloatValue;
    int Ret=Cam.GetBoolValue(strKey, &CurrentValue);
    if(Ret==MV_OK){
        return true;
    }
    return false;
}

bool	CameraHIKRobotGigE::ImageToTarget(int TargetPhase ,int TargetPage,int Index)
{
    DataInPage  *Dp=GetLayersBase()->GetPageDataPhase(TargetPhase)->GetPageData(TargetPage);
    DataInLayer *L0=Dp->GetLayerData(0);
    DataInLayer *L1=Dp->GetLayerData(1);
    DataInLayer *L2=Dp->GetLayerData(2);
    ImageBuffer *Buff[3];
    Buff[0]=&L0->GetTargetBuff();
    Buff[1]=&L1->GetTargetBuff();
    Buff[2]=&L2->GetTargetBuff();

    GetImage(CamBuffDim[Index],Buff ,3);
    return true;
}

void	CameraHIKRobotGigE::TransmitDirectly(GUIDirectMessage *packet)
{
    CmdSetCaptureOne    *CmdSetCaptureOneVar=dynamic_cast<CmdSetCaptureOne *>(packet);
    if(CmdSetCaptureOneVar!=NULL){
        CaptureOneMode  =true;
        //if(CmdSetCaptureOneVar->Index<0){
        //    int iCamBuffRPoint=CamBuffWPoint-1;
        //    if(iCamBuffRPoint<0){
        //        iCamBuffRPoint=MaxCountCamBufferStack-1;
        //    }
        //    *CapturedBuffDim[CapturedBuffWPoint]=*CamBuffDim[iCamBuffRPoint];
        //    CapturedBuffWPoint++;
        //    if(CapturedBuffWPoint>=MaxCountCapturedBufferStack){
        //        CapturedBuffWPoint=0;
        //    }
        //}
        //else{
        //    *CapturedBuffDim[CapturedBuffWPoint]=*CamBuffDim[CmdSetCaptureOneVar->Index];
        //    CapturedBuffWPoint++;
        //    if(CapturedBuffWPoint>=MaxCountCapturedBufferStack){
        //        CapturedBuffWPoint=0;
        //    }
        //}

        MutexRList.lock();
        CapturedRList.Add(CmdSetCaptureOneVar->Index);
        MutexRList.unlock();
    }
    CmdSetContinuousMode    *CmdSetContinuousModeVar=dynamic_cast<CmdSetContinuousMode *>(packet);
    if(CmdSetContinuousModeVar!=NULL){
        ContinuousON=CmdSetContinuousModeVar->ContinuousON;
        return;
    }
    CmdReqCaptureClosed *CmdReqCaptureClosedVar=dynamic_cast<CmdReqCaptureClosed *>(packet);
    if(CmdReqCaptureClosedVar!=NULL){
        CmdReqCaptureClosedVar->Index=0;
        CmdReqCaptureClosedVar->MinD=999999999;
        int k=0;
        for(int i = CmdReqCaptureClosedVar->Index;i<MaxCountCamBufferStack && k<CamBuffStockedCount;i++,k++){
            float   d0=(CmdReqCaptureClosedVar->Pos[0]-CamBuffDim[i]->CurrentPos[0])/*CmdReqCaptureClosedVar->CompareParamJ[0]*/;
            float   d1=(CmdReqCaptureClosedVar->Pos[1]-CamBuffDim[i]->CurrentPos[1])/*CmdReqCaptureClosedVar->CompareParamJ[1]*/;
            float   d2=(CmdReqCaptureClosedVar->Pos[2]-CamBuffDim[i]->CurrentPos[2])/*CmdReqCaptureClosedVar->CompareParamJ[2]*/;
            float   d3=(CmdReqCaptureClosedVar->Pos[3]-CamBuffDim[i]->CurrentPos[3])/*CmdReqCaptureClosedVar->CompareParamJ[3]*/;
            float   d4=(CmdReqCaptureClosedVar->Pos[4]-CamBuffDim[i]->CurrentPos[4])/*CmdReqCaptureClosedVar->CompareParamJ[4]*/;
            float   d5=(CmdReqCaptureClosedVar->Pos[5]-CamBuffDim[i]->CurrentPos[5])/*CmdReqCaptureClosedVar->CompareParamJ[5]*/;
            double  D=d0*d0+d1*d1+d2*d2+d3*d3+d4*d4+d5*d5;
            if(D<CmdReqCaptureClosedVar->MinD){
                CmdReqCaptureClosedVar->MinD=D;
                CmdReqCaptureClosedVar->Index=i;
            }
        }
        return;
    }
    CmdResetCounter *CmdResetCounterVar=dynamic_cast<CmdResetCounter *>(packet);
    if(CmdResetCounterVar!=NULL){
        MutexCounter.lock();
        CamBuffStockedCount =0;
        CamBuffWPoint       =0;
        CamBuffRPoint       =0;
        MutexCounter.unlock();
        return;
    }
    CmdReqCapturedCount *CmdReqCapturedCountVar=dynamic_cast<CmdReqCapturedCount *>(packet);
    if(CmdReqCapturedCountVar!=NULL){
        CmdReqCapturedCountVar->CapturedCount=CapturedCount;
        return;
    }
    CmdReqJointFrameClass   *CmdReqJointFrameClassVar=dynamic_cast<CmdReqJointFrameClass *>(packet);
    if(CmdReqJointFrameClassVar!=NULL){
        CmdReqJointFrameClassVar->DimCount=CamBuffStockedCount;
        CmdReqJointFrameClassVar->Dim=new JointFrameClass[CamBuffStockedCount];
        for(int i=0;i<CamBuffStockedCount;i++){
            for(int j=0;j<6;j++){
                CmdReqJointFrameClassVar->Dim[i].CurrentPos[j]=CamBuffDim[i]->CurrentPos[j];
            }
        }
        return;
    }
    CmdLockCapture  *CmdLockCaptureVar=dynamic_cast<CmdLockCapture *>(packet);
    if(CmdLockCaptureVar!=NULL){
        LockCapture=true;
        return;
    }
    CmdUnlockCapture  *CmdUnlockCaptureVar=dynamic_cast<CmdUnlockCapture *>(packet);
    if(CmdUnlockCaptureVar!=NULL){
        LockCapture=false;
        return;
    }
    CmdImageToTarget    *CmdImageToTargetVar=dynamic_cast<CmdImageToTarget *>(packet);
    if(CmdImageToTargetVar!=NULL){
        ImageToTarget(CmdImageToTargetVar->TargetPhase
                     ,CmdImageToTargetVar->TargetPage
                     ,CmdImageToTargetVar->Index);
        return;
    }
}
