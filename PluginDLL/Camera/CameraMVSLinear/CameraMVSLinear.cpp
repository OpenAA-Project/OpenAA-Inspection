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

#include "CameraMVSLinear.h"
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "ThreadSequence.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"
#include "SettingLinearCameraDialog.h"

#ifndef _MSC_VER
#include <stdio.h>
#include <string.h>
#define sprintf_s snprintf
#define strcpy_s(dest, size, src) strncpy(dest, src, size); dest[(size)-1] = '\0'
#endif

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


CameraMVSLinear::CameraMVSLinear(int CamNo ,const QString &_ParamStr,LayersBase *base)
	:CameraHandle(CamNo,base)
{
    ParamStr                    = _ParamStr;
	LineTriggerMode				= false;
	LineTriggerSource			= MV_TRIGGER_SOURCE_SOFTWARE;
    FrameTriggerMode			= false;
	FrameTriggerSource			= MV_TRIGGER_SOURCE_SOFTWARE;
    Line0Format     =0;
    Line1Format     =0;
    Line2Format     =0;
    Line3Format     =0;
    Line4Format     =0;
    ExposureAuto    =MV_EXPOSURE_AUTO_MODE_OFF;
    ExposureMode    =0;
    ExposureTime    =10000;

    BinningHMode    =1;
    BinningVMode    =1;
    DecimationH     =1;
    DecimationV     =1;
	Gain    = 0;
    GainR = 0;
	GainG = 0;
	GainB = 0;

    ReverseX    =false;
    ReverseTDIY =false;

    AOIMode     =false;
    AOIOffsetX  =0;
    AOIWidth    =0;
	BlackLevelEnable    =false;
	BlackLevel          =200;
	ImageCompression    = 0;
	AcquisitionLineRateEnable = false;
    GammaEnable =true;
	Gamma       =0.7;
    FrameDelay  =0;

    CamBuffWPoint   =0;
    CamBuffRPoint   =0;
    CamBuffStockedCount=0;
    for(int i=0;i<MaxCountCamBufferStack;i++){
        CamBuffDim[i]=new CamBufferStack();
    }
    RGBBuff =NULL;
    XLen    =0;
    YLen    =0;

    Cam.SetLogMode(true);
}
CameraMVSLinear::~CameraMVSLinear(void)
{
	Release();
}

void    CameraMVSLinear::Release(void)
{
    Cam.Close();
    for(int i=0;i<MaxCountCamBufferStack;i++){
        if(CamBuffDim[i]!=NULL){
            delete  CamBuffDim[i];
            CamBuffDim[i]=NULL;
        }
    }
}


bool    CameraMVSLinear::Initial(void)
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
            uint32_t ip = pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp;
            QString ipStr = QString("%1.%2.%3.%4")
                            .arg((ip >> 24) & 0xFF)
                            .arg((ip >> 16) & 0xFF)
                            .arg((ip >> 8) & 0xFF)
                            .arg(ip & 0xFF);

            QString modelName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chModelName));
            QString userDefName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName));

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


            QStringList List=ParamStr.split("=");
            if(List[0].trimmed()=="IP"){
                if(ipStr==List[1]){
                    DevNo=i;
                    break;
                }
            }
            else if(List[0].trimmed()=="Model"){
                if(modelName==List[1]){
                    DevNo=i;
                    break;
                }
            }
            else if(List[0].trimmed()=="UserDefName"){
                if(userDefName==List[1]){
                    DevNo=i;
                    break;
                }
			}
            else if(List[0].trimmed()==ipStr){
                DevNo=i;
                break;
            }
            else if(List[0].trimmed()==modelName){
                DevNo=i;
                break;
            }
            else if(List[0].trimmed()==userDefName){
                DevNo=i;
                break;
			}
            //DevNo=i;
		}
	}
	if(DevNo<0){
        for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++) {
            MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
            
            if (pDeviceInfo && pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
                QString modelName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chModelName));
  
                if (modelName.startsWith("MV-C")) {
                DevNo=i;
                break;
                }
            }
        }

		return false;
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
    CameraMVSLinear  *Handle=(CameraMVSLinear *)pUser;
    Handle->CaptureImage(pData,pFrameInfo);
}

void	CameraMVSLinear::CaptureImage(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo)
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
        Cam.SetGrabbing(false);
    }
}

bool	CameraMVSLinear::IsCaptured(void)
{
    MutexImageSize.lock();
    bool    Ret=(CamBuffStockedCount!=0)?true:false;
    MutexImageSize.unlock();
    return Ret;
}

bool	CameraMVSLinear::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
    return ChangeInfo(NewDotPerLine ,NewMaxLines);
}


bool	CameraMVSLinear::ChangeInfo(int _XLen ,int _YLen)
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

    int64 _YLen64=_YLen;
    if(SetIntValue	 ("Height",_YLen64)==false){
        return false;
    }

    return true;
}

bool    CameraMVSLinear::ReqSystemChange(CameraReqSystemChangeInfo &caminfo)
{
    int     Width ,Height;

    int CurrentValue ,MaxValue ,MinValue;
    if(GetIntValue	 ("Width",Width ,MaxValue ,MinValue)==false){
        return false;
    }
    if(GetIntValue	 ("Height",Height ,MaxValue ,MinValue)==false){
        return false;
    }
	
    caminfo.LayerNumber=1;
	int	Index = UserName.indexOf('(');
	if(Index>0){
		QString ModelName = UserName.left(Index).trimmed();
		if(ModelName.last(1)=="C"){
            caminfo.LayerNumber=3;
        }
    }

	caminfo.XLen = Width;
	//caminfo.YLen = Height;

    return true;
}


bool    CameraMVSLinear::GetLine0(void)
{
    return Cam.GetLine0Input();
}


bool	CameraMVSLinear::SetLine1(bool b)
{
    return Cam.SetLine1Output(b);
}


bool    CameraMVSLinear::SetLineCount(int _YLen)
{
    ChangeInfo(XLen ,_YLen);
    return true;
}
bool    CameraMVSLinear::ShowSetting(void)
{
	SettingLinearCameraDialog	D(this);
	if(D.exec()==true){
        ExposureAuto        =D.ExposureAuto        ;
        ExposureMode        =D.ExposureMode        ;
	    ExposureTime        =D.ExposureTime        ;
        Gain                =D.Gain;
	    GainR               =D.GainR                ;
        GainG               =D.GainG                ;
        GainB               =D.GainB                ;
	    LineRate            =D.LineRate            ;
        LineTriggerMode     =D.LineTriggerMode      ;   
        LineTriggerSource   =D.LineTriggerSource    ; 
        FrameTriggerMode    =D.FrameTriggerMode     ;   
        FrameTriggerSource  =D.FrameTriggerSource   ; 
        Line0Format         =D.Line0Format;
        Line1Format         =D.Line1Format;
        Line2Format         =D.Line2Format;
        Line3Format         =D.Line3Format;
        Line4Format         =D.Line4Format;
        BinningHMode        =D.BinningHMode         ;
        BinningVMode        =D.BinningVMode         ;
        DecimationH         =D.DecimationH          ;
        DecimationV         =D.DecimationV          ;

        ReverseX            =D.ReverseX            ;
        ReverseTDIY         =D.ReverseTDIY         ;

        AOIMode             =D.AOIMode             ;
        AOIOffsetX          =D.AOIOffsetX          ;
        AOIWidth            =D.AOIWidth            ;
        
        BlackLevelEnable=D.BlackLevelEnable;
        BlackLevel      =D.BlackLevel      ;
        ImageCompression=D.ImageCompression;
        AcquisitionLineRateEnable   =D.AcquisitionLineRateEnable;
        GammaEnable =D.GammaEnable;
	    Gamma       =D.Gamma      ;
        FrameDelay  =D.FrameDelay ;

        Cam.SetupLineTriggers (LineTriggerMode  , LineTriggerSource );
        Cam.SetupFrameTriggers(FrameTriggerMode , FrameTriggerSource);
        SetExposure();
        SetRGBGain();
        SetLineRate();
        //SetBinningDecimation();
        SetReverse();
        SetAOI();
        SetBlackLevel();
        SetImageCompression();
        SetGamma();
        SetDelay();
	    SetLineFormat(0,Line0Format);
	    SetLineFormat(1,Line1Format);
	    SetLineFormat(2,Line2Format);
	    SetLineFormat(3,Line3Format);
	    SetLineFormat(4,Line4Format);
		return true;
	}
	return false;
}

bool    CameraMVSLinear::PrepareCapture()
{
    return true;
}
bool    CameraMVSLinear::StartCapture()
{
    if(Cam.StartGrabbing()==0){
        return true;
	}
	return false;
}
bool    CameraMVSLinear::SetAutoRepeat(bool b)
{
    return true;
}
bool    CameraMVSLinear::HaltCapture()
{
    return true;
}

bool    CameraMVSLinear::GetStatus(CameraScanInfo *Info)
{
    return true;
}
bool	CameraMVSLinear::StartCaptureContinuously(ImageBuffer *Buff[],int BufferDimCounts ,CameraScanInfo *Info)
{
    if(CamBuffStockedCount==0){
        return false;
    }

    GetImage(Buff ,BufferDimCounts);

    return true;
}
void	CameraMVSLinear::GetImage(ImageBuffer *Buff[3] ,int LayerNumb)
{
    MutexImageSize.lock();

    int iCamBuffWPoint=CamBuffWPoint-1;
    if(iCamBuffWPoint<0){
        iCamBuffWPoint=MaxCountCamBufferStack-1;
    }
    if(CamBuffRPoint!=iCamBuffWPoint){
        CamBuffRPoint=iCamBuffWPoint;
        CamBuffStockedCount=0;
    }

    CamBufferStack		*p=CamBuffDim[CamBuffRPoint];

    if(ImageCompression==0){
        MV_CC_PIXEL_CONVERT_PARAM_EX stConvertParam = {0};       

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
    }
    else{
        if(LayerNumb==3){
        // HBデコード用のパラメータを設定
            MV_CC_HB_DECODE_PARAM stDecodeParam = {0};
            stDecodeParam.pSrcBuf   = p->Data;      // カメラから受信した圧縮データ
            stDecodeParam.nSrcLen   = p->FrameSize;         // 受信データのサイズ
            stDecodeParam.nWidth    = p->XLen;             // 画像の幅
            stDecodeParam.nHeight   = p->YLen;           // 画像の高さ
            
            stDecodeParam.pDstBuf = RGBBuff;               // 展開先バッファ
            stDecodeParam.nDstBufSize = XLen*YLen*4;    // 展開先バッファの最大サイズ
            stDecodeParam.enDstPixelType = PixelType_Gvsp_RGB8_Packed; // 展開後の希望ピクセルフォーマット

            // HBデコードの実行
            int Ret = Cam.HB_Decode(&stDecodeParam);
            if(Ret==MV_OK){
                BYTE    *s=RGBBuff;
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
        else if(LayerNumb==1){
        // HBデコード用のパラメータを設定
            MV_CC_HB_DECODE_PARAM stDecodeParam = {0};
            stDecodeParam.pSrcBuf   = p->Data;      // カメラから受信した圧縮データ
            stDecodeParam.nSrcLen   = p->FrameSize;         // 受信データのサイズ
            stDecodeParam.nWidth    = p->XLen;             // 画像の幅
            stDecodeParam.nHeight   = p->YLen;           // 画像の高さ
            
            stDecodeParam.pDstBuf = RGBBuff;               // 展開先バッファ
            stDecodeParam.nDstBufSize = XLen*YLen;    // 展開先バッファの最大サイズ
            stDecodeParam.enDstPixelType = PixelType_Gvsp_RGB8_Packed; // 展開後の希望ピクセルフォーマット

            // HBデコードの実行
            int Ret = Cam.HB_Decode(&stDecodeParam);
            if(Ret==MV_OK){
                BYTE    *s=RGBBuff;
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


    CamBuffRPoint++;
    if(CamBuffRPoint>=MaxCountCamBufferStack){
        CamBuffRPoint=0;
    }
    CamBuffStockedCount--;
    if(CamBuffStockedCount<0)
        CamBuffStockedCount=0;

    MutexImageSize.unlock();
}

void    CameraMVSLinear::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdInputHIKRobotCamera *CmdInputHIKRobotCameraVar = dynamic_cast<CmdInputHIKRobotCamera *>(packet);
    //if(CmdInputHIKRobotCameraVar!=NULL){      
    //    CmdInputHIKRobotCameraVar->Line0=GetLine0();
    //    return;
	//}
	//CmdOutputHIKRobotCamera *CmdOutputHIKRobotCameraVar = dynamic_cast<CmdOutputHIKRobotCamera *>(packet);
    //if(CmdOutputHIKRobotCameraVar!=NULL){
    //    SetLine1(CmdOutputHIKRobotCameraVar->Line1);
    //    return;
	//}
}


void    CameraMVSLinear::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CloseApplicationSpecifiedBroadcaster *CloseApplicationSpecifiedBroadcasterVar = dynamic_cast<CloseApplicationSpecifiedBroadcaster *>(v);
    if(CloseApplicationSpecifiedBroadcasterVar!=NULL){
        HaltCapture();
        Release();
        return;
	}
}

bool	CameraMVSLinear::Save(QIODevice *f)
{
	if(::Save(f,ExposureTime)==false)	        return false;
    if(::Save(f,Gain )==false)			        return false;
	if(::Save(f,GainR)==false)			        return false;
    if(::Save(f,GainG)==false)			        return false;
    if(::Save(f,GainB)==false)			        return false;
    if(::Save(f,LineRate)==false)			    return false;
    if(::Save(f,LineTriggerMode)==false)		return false;
    if(::Save(f,LineTriggerSource)==false)		return false;
    if(::Save(f,FrameTriggerMode)==false)		return false;
    if(::Save(f,FrameTriggerSource)==false)		return false;
    if(::Save(f,Line0Format)==false)		    return false;
    if(::Save(f,Line1Format)==false)		    return false;
    if(::Save(f,Line2Format)==false)		    return false;
    if(::Save(f,Line3Format)==false)		    return false;
    if(::Save(f,Line4Format)==false)		    return false;
    if(::Save(f,ExposureAuto)==false)	        return false;
    if(::Save(f,ExposureMode)==false)	        return false;
    if(::Save(f,BinningHMode)==false)	        return false;
    if(::Save(f,BinningVMode)==false)	        return false;
    if(::Save(f,DecimationH)==false)	        return false;
    if(::Save(f,DecimationV)==false)	        return false;

    if(::Save(f,ReverseX    )==false)	        return false;
    if(::Save(f,ReverseTDIY    )==false)        return false;

    if(::Save(f,AOIMode     )==false)	        return false;
    if(::Save(f,AOIOffsetX  )==false)	        return false;
    if(::Save(f,AOIWidth    )==false)	        return false;

    if(::Save(f,BlackLevelEnable)==false)       return false;
    if(::Save(f,BlackLevel      )==false)       return false;
    if(::Save(f,ImageCompression)==false)       return false;
    if(::Save(f,AcquisitionLineRateEnable   )==false)       return false;
    if(::Save(f,GammaEnable     )==false)       return false;
    if(::Save(f,Gamma           )==false)       return false;
    if(::Save(f,FrameDelay      )==false)       return false;

	return true;
}
bool	CameraMVSLinear::Load(QIODevice *f)
{
	if(::Load(f,ExposureTime)==false)	        return false;
    if(::Load(f,Gain )==false)			        return false;
	if(::Load(f,GainR)==false)			        return false;
    if(::Load(f,GainG)==false)			        return false;
    if(::Load(f,GainB)==false)			        return false;
    if(::Load(f,LineRate)==false)			    return false;
    if(::Load(f,LineTriggerMode)==false)		return false;
    if(::Load(f,LineTriggerSource)==false)		return false;
    if(::Load(f,FrameTriggerMode)==false)		return false;
    if(::Load(f,FrameTriggerSource)==false)		return false;
    if(::Load(f,Line0Format)==false)		    return false;
    if(::Load(f,Line1Format)==false)		    return false;
    if(::Load(f,Line2Format)==false)		    return false;
    if(::Load(f,Line3Format)==false)		    return false;
    if(::Load(f,Line4Format)==false)		    return false;
    if(::Load(f,ExposureAuto)==false)	        return false;
    if(::Load(f,ExposureMode)==false)	        return false;
    if(::Load(f,BinningHMode)==false)	        return false;
    if(::Load(f,BinningVMode)==false)	        return false;
    if(::Load(f,DecimationH)==false)	        return false;
    if(::Load(f,DecimationV)==false)	        return false;

    if(::Load(f,ReverseX    )==false)	        return false;
    if(::Load(f,ReverseTDIY    )==false)        return false;

    if(::Load(f,AOIMode     )==false)	        return false;
    if(::Load(f,AOIOffsetX  )==false)	        return false;
    if(::Load(f,AOIWidth    )==false)	        return false;

    if(::Load(f,BlackLevelEnable)==false)       return false;
    if(::Load(f,BlackLevel      )==false)       return false;
    if(::Load(f,ImageCompression)==false)       return false;
    if(::Load(f,AcquisitionLineRateEnable   )==false)       return false;
    if(::Load(f,GammaEnable     )==false)       return false;
    if(::Load(f,Gamma           )==false)       return false;
    if(::Load(f,FrameDelay      )==false)       return false;

    bool    IsGrabbing=Cam.IsGrabbing();
    if(IsGrabbing==true){
        Cam.StopGrabbing();
    }
    Cam.ClearImageBuffer();


    Cam.SetupLineTriggers (LineTriggerMode  , LineTriggerSource);
    Cam.SetupFrameTriggers(FrameTriggerMode , FrameTriggerSource);
    SetExposure();
    SetRGBGain();
    SetLineRate();
    //SetBinningDecimation();
    SetReverse();
    SetAOI();
    SetBlackLevel();
    SetImageCompression();
    SetGamma();
    SetDelay();
	SetLineFormat(0,Line0Format);
	SetLineFormat(1,Line1Format);
	SetLineFormat(2,Line2Format);
	SetLineFormat(3,Line3Format);
	SetLineFormat(4,Line4Format);

    QThread::msleep(500);

    Cam.ClearImageBuffer();

    MutexImageSize.lock();
    CamBuffRPoint=CamBuffWPoint;
    CamBuffStockedCount=0;
    MutexImageSize.unlock();

    if(IsGrabbing==true){ 
        Cam.StartGrabbing();
    }

	return true;
}

// ch:获取触发模式 | en:Get Trigger Mode
bool CameraMVSLinear::GetTriggerMode(void)
{
    bool    tLineTriggerMode;
    int     tLineLineNo;
    Cam.GetLineTriggerSettings(tLineTriggerMode , tLineLineNo);

    bool    tFrameTriggerMode;
    int     tFrameLineNo;
    Cam.GetFrameTriggerSettings(tFrameTriggerMode , tFrameLineNo);

    if(tLineTriggerMode==true && tFrameTriggerMode==true)
        return true;
    return false;
}

// ch:设置触发模式 | en:Set Trigger Mode
bool CameraMVSLinear::SetTriggerMode(bool b)
{
    if(b==true){
        Cam.SetupLineTriggers (LineTriggerMode  , LineTriggerSource );
        Cam.SetupFrameTriggers(FrameTriggerMode , FrameTriggerSource);
    }
    else{
        Cam.SetupLineTriggers (false, LineTriggerSource );
        Cam.SetupFrameTriggers(false, FrameTriggerSource);
    }
    return true;
}

// ch:获取曝光时间 | en:Get Exposure Time
int CameraMVSLinear::GetExposureTime()
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
int CameraMVSLinear::SetExposure()
{
    int nRet;
    nRet = Cam.SetEnumValue("ExposureAuto", ExposureAuto);
    nRet = Cam.SetEnumValue("ExposureMode", ExposureMode);
    nRet = Cam.SetBoolValue("AcquisitionLineRateEnable",AcquisitionLineRateEnable);
    nRet = Cam.SetFloatValue("ExposureTime", (float)ExposureTime);
    return nRet;
}

// ch:获取增益 | en:Get Gain
bool CameraMVSLinear::GetGain(float &fGainR,float &fGainG,float &fGainB)
{
	bool nRet = Cam.GetRGBGain(fGainR,fGainG,fGainB);
    
    return nRet;
}

bool CameraMVSLinear::SetRGBGain()
{
	if(Cam.SetFloatValue("Gain",Gain)==true){
        return false;
	}
	if(Cam.SetEnumValueByString("BalanceRatioSelector", "Red")==MV_OK){
		if(Cam.SetIntValue("BalanceRatio",(int64_t)GainR)!=MV_OK){
	        return false;
		}
	}
	if(Cam.SetEnumValueByString("BalanceRatioSelector", "Green")==MV_OK){
		if(Cam.SetIntValue("BalanceRatio",(int64_t)GainG)!=MV_OK){
	        return false;
		}
	}
	if(Cam.SetEnumValueByString("BalanceRatioSelector", "Blue")==MV_OK){
		if(Cam.SetIntValue("BalanceRatio",(int64_t)GainB)!=MV_OK){
	        return false;
		}
	}
	return true;
}

// ch:获取帧率 | en:Get Frame Rate
int CameraMVSLinear::GetLineRate()
{
    MVCC_INTVALUE Value64 ;

    int nRet = Cam.GetIntValue("AcquisitionLineRate", &Value64);
    if (MV_OK != nRet)
    {
        return nRet;
    }
    LineRate = Value64.nCurValue;

    return MV_OK;
}

// ch:设置帧率 | en:Set Frame Rate
int CameraMVSLinear::SetLineRate()
{
    int64 Value64=LineRate ;
    return Cam.SetIntValue("AcquisitionLineRate", (int64_t)Value64);
}


// 该接口只展示GetEnumEntrySymbolic接口的使用方法
int CameraMVSLinear::GetPixelFormat()
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

bool    CameraMVSLinear::SetLineFormat(int LineNo,int LineFormat)
{
    if(Cam.SetLineFormat(LineNo,LineFormat)==false){
        return false;
	}
	return true;
}


bool	CameraMVSLinear::GetIntValue	 (const char* strKey ,int &CurrentValue ,int   &MaxValue ,int   &MinValue)
{
    MVCC_INTVALUE    IntValue;
    int Ret=Cam.GetIntValue(strKey, &IntValue);
    if(Ret==MV_OK){
        CurrentValue=IntValue.nCurValue;
        MaxValue    =IntValue.nMax;
        MinValue    =IntValue.nMin;
        return true;
    }
    return false;
}
bool	CameraMVSLinear::GetIntValue	 (const char* strKey ,int64 &CurrentValue ,int64 &MaxValue ,int64 &MinValue)
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
bool	CameraMVSLinear::SetIntValue	 (const char* strKey ,int64 &CurrentValue)
{
    int Ret=Cam.SetIntValue(strKey, (int64_t)CurrentValue);
    if(Ret==MV_OK){
        return true;
    }
    return false;

}
bool	CameraMVSLinear::GetfloatValue(const char* strKey ,float &CurrentValue ,float &MaxValue ,float &MinValue)
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
bool	CameraMVSLinear::GetBoolValue (const char* strKey ,bool &CurrentValue )
{
    MVCC_FLOATVALUE    FloatValue;
    int Ret=Cam.GetBoolValue(strKey, &CurrentValue);
    if(Ret==MV_OK){
        return true;
    }
    return false;
}

bool	CameraMVSLinear::GetEnumValue (const char* strKey ,int &CurrentValue ,int EnumData[64],int &EnumCount)
{
    MVCC_ENUMVALUE    stParam;
    int Ret=Cam.GetEnumValue(strKey, &stParam);
    if(Ret==MV_OK){
        EnumCount=stParam.nSupportedNum;
        for(int i=0;i<EnumCount;i++){
            EnumData[i]=stParam.nSupportValue[i];
        }
        CurrentValue=stParam.nCurValue;
        return true;
    }
    return false;
}
bool	CameraMVSLinear::GetEnumSymblic (const char* strKey ,int EnumValue ,QString &Str)
{
    MVCC_ENUMENTRY	enumParam;
    memset(&enumParam, 0, sizeof(enumParam));
    enumParam.nValue=EnumValue;
    int Ret=Cam.GetEnumEntrySymbolic(strKey, &enumParam);
    if(Ret==MV_OK){
        Str=enumParam.chSymbolic;
        return true;
    }
    return false;
}
bool    CameraMVSLinear::SetEnumValueByString(IN const char* strKey, IN const char* sValue)
{
    int nRet = Cam.SetEnumValueByString(strKey, sValue);
    if (MV_OK != nRet)
    {
        return false;
    }
    return true;
}


bool    CameraMVSLinear::SetBinningDecimation(void)
{
    bool    Ret=true;
    bool    IsGrabbing=Cam.IsGrabbing();
    if(IsGrabbing==true){
        Cam.StopGrabbing();
    }
    int nRet;
    nRet=Cam.SetIntValue("BinningHorizontal", BinningHMode);
    if(nRet!=MV_OK){
        Ret=false;
        goto    EndBinning;
    }
    nRet=Cam.SetIntValue("BinningVertical", BinningVMode);
    if(nRet!=MV_OK){
        Ret=false;
        goto    EndBinning;
    }
    nRet=Cam.SetIntValue("DecimationHorizontal", DecimationH);
    if(nRet!=MV_OK){
        Ret=false;
        goto    EndBinning;
    }
    nRet=Cam.SetIntValue("DecimationVertical", DecimationV);
    if(nRet!=MV_OK){
        Ret=false;
        goto    EndBinning;
    }
    int     Width ,Height;
    nRet=Cam.GetResolution(Width ,Height);
    if (MV_OK == nRet){
        ChangeInfo(Width ,Height);
    }
EndBinning:;

    if(IsGrabbing==true){
        Cam.StartGrabbing();
    }
    return Ret;
}

    
bool    CameraMVSLinear::SetReverse(void)
{
    int nRet;

    nRet = Cam.SetBoolValue("ReverseX", ReverseX);
    if (MV_OK != nRet)
    {
        return false;
    }
    if(Cam.SetTDIDirection(ReverseTDIY)==false){
        return false;
    }
    return true;
}
    
bool    CameraMVSLinear::SetAOI(void)
{
    bool    IsGrabbing=Cam.IsGrabbing();
    if(IsGrabbing==true){
        Cam.StopGrabbing();
    }
    int     Ret;
    int     Width ,Height;
    Ret=Cam.GetResolution(Width ,Height);
    if (MV_OK != Ret){
        return false;
    }

    Cam.SetIntValue("OffsetX", 0u);
    Cam.SetIntValue("OffsetY", 0u);

    if(AOIWidth>0){
        Ret = Cam.SetIntValue("Width", AOIWidth);
        if (MV_OK != Ret){
            return false;
        }
    }

    if(AOIOffsetX>0){
        Ret = Cam.SetIntValue("OffsetX", AOIOffsetX);
        if (MV_OK != Ret){
            return false;
        }
    }

    int MaxValue ,MinValue;
    bool    bRet = GetIntValue("Width", Width,MaxValue ,MinValue);
    if (bRet==false){
        return false;
    }
    bRet = GetIntValue("Height", Height,MaxValue ,MinValue);
    if (bRet==false){
        return false;
    }

    ChangeInfo(Width ,Height);

	CameraReqSystemChangeInfo caminfo;
	if(ReqSystemChange(caminfo)==true){
		if(GetPageNumb()==1){
			GetLayersBase()->ReallocXYPixels(caminfo.XLen,caminfo.YLen);
		}
		else{
			IntList PageList;
			GetParamGlobal()->GetPageListFromCameraNo(GetCamNo() ,PageList);
			for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
				int	Page = p->GetValue();
				for(int phase = 0;phase<GetPhaseNumb();phase++){
					GetLayersBase()->ReallocXYPixelsPage(phase,Page,caminfo.XLen,caminfo.YLen);
				}
			}
		}
	}

    if(IsGrabbing==true){
        Cam.StartGrabbing();
    }
    return true;
}
bool    CameraMVSLinear::SetBlackLevel(void)
{
    int nRet;
    nRet=Cam.SetBoolValue("BlackLevelEnable",BlackLevelEnable);
    if (MV_OK != nRet){
        return false;
    }
    if(BlackLevelEnable==true){
        nRet=Cam.SetIntValue("BlackLevel",(int64_t)BlackLevel);
        if (MV_OK != nRet){
            return false;
        }
    }
    return true;
}

bool    CameraMVSLinear::SetImageCompression(void)
{
    int nRet;
    nRet=Cam.SetEnumValue("ImageCompressionMode", ImageCompression);
    if (MV_OK != nRet){
        return false;
    }
	return true;
}
bool    CameraMVSLinear::SetGamma(void)
{
    int nRet;
    nRet=Cam.SetBoolValue("GammaEnable", GammaEnable);
    if (MV_OK != nRet){
        return false;
    }
    if(GammaEnable==true){
        nRet=Cam.SetFloatValue("Gamma", Gamma);
        if (MV_OK != nRet){
            return false;
        }
    }
    return true;
}

bool    CameraMVSLinear::SetDelay(void)
{
    return Cam.SetupFrameTriggersDelay(FrameDelay);
}
bool    CameraMVSLinear::GetResolution(int &Width ,int &Height)
{
    int Ret=Cam.GetResolution(Width ,Height);
    if (MV_OK == Ret){
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
	str=/**/"MVS Camera Linear GigE";
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

	if(CameraNoInThisComputer==0){
		MV_CC_Initialize();
	}
	CameraMVSLinear	*v=new CameraMVSLinear(CameraNoInThisComputer,CameraParameter,base);
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
	CameraMVSLinear	*BaslerSystemInst=(CameraMVSLinear	*)handle;
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
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
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
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
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
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
	if(Px!=NULL){
		Px->ChangeInfo(caminfo.XLen ,caminfo.YLen);
	}

	return true;
}
DEFFUNCEX	bool	_cdecl	DLL_ReqSystemChange(CameraHandle *handle ,CameraReqSystemChangeInfo &caminfo)
{
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
	if(Px!=NULL){
		Px->ReqSystemChange(caminfo);
	}

	return true;
}

bool _cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
	if(Px->ShowSetting()==true){
		return(true);
	}
	return(false);
}

bool	_cdecl	DLL_SetQuickProperty(CameraHandle *handle,CameraQuickProperty Attr, double RelativeValue)
{
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
	//return Px->SetQuickProperty(Attr, RelativeValue);
	return true;
}


bool _cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
	return  Px->PrepareCapture();
}

bool _cdecl	DLL_StartCapture(CameraHandle *handle, CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
	return Px->StartCapture();
}

bool _cdecl	DLL_SetAutoRepeat(CameraHandle *handle ,bool RepeatON)
{
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
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
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;

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
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
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
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
	Px->GetImage(Buff,BufferDimCounts);
    return true;
}
DEFFUNCEX	void	_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
	Px->TransmitDirectly(packet);
}
DEFFUNCEX	void	_cdecl	DLL_SpecifiedDirectly(CameraHandle *handle ,SpecifiedBroadcaster *v)
{
	CameraMVSLinear		*Px=(CameraMVSLinear *)handle;
	Px->SpecifiedDirectly(v);
}