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

#include "MvCamera.h"
#include <QFile>
#include <QDateTime>
#include <QThread>

QString CMvCamera::LogFileName="HikRobotCameraLog.txt";
bool    CMvCamera::OutputLogFile=false;
QFile   *CMvCamera::LogFile     =NULL;

static  void    SleepFunc(void)
{
    QThread::msleep(10);
}

CMvCamera::CMvCamera()
{
    m_hDevHandle = MV_NULL;
    Grabbing    =false;

    //OutputLogFile=false;
    //LogFile=NULL;
}

CMvCamera::~CMvCamera()
{
    if (m_hDevHandle)
    {
        MV_CC_DestroyHandle(m_hDevHandle);
        m_hDevHandle    = MV_NULL;
    }
    if(LogFile!=NULL){
        LogFile->close();
        delete  LogFile;
        LogFile=NULL;
    }
}

bool    CMvCamera::OutputLog(const QString &Func ,int Result)
{
    if(OutputLogFile==false){
        QThread::msleep(10);
        return true;
    }
    if(LogFile==NULL){
        LogFile=new QFile(LogFileName);
        if(LogFile->open(QIODevice::Append)==false){
            return false;
        }
    }
    QString s=QDateTime::currentDateTime().toString("yyMMdd-hh:mm:ss.zzz")
            + QString(" Func=")+Func
            + QString(" Return=")+QString::number(Result)
            + QString("\n");
    QByteArray  SArray=s.toLocal8Bit();
    LogFile->write(SArray.data());
    LogFile->flush();
    return true;
}

bool    CMvCamera::OutputLog(const QString &Func ,const QString &Arg ,int Result)
{
    if(OutputLogFile==false){
        QThread::msleep(10);
        return true;
    }
    if(LogFile==NULL){
        LogFile=new QFile(LogFileName);
        if(LogFile->open(QIODevice::Append)==false){
            return false;
        }
    }
    QString s=QDateTime::currentDateTime().toString("yyMMdd-hh:mm:ss.zzz")
            + QString(" Func=")+Func
            + QString(" Arg=")+Arg
            + QString(" Return=")+QString::number(Result)
            + QString("\n");
    QByteArray  SArray=s.toLocal8Bit();
    LogFile->write(SArray.data());
    LogFile->flush();
    return true;
}
bool    CMvCamera::OutputLog(const QString &Func ,const QString &Value1 ,int64 Value2,int Result)
{
    if(OutputLogFile==false){
        QThread::msleep(10);
        return true;
    }
    if(LogFile==NULL){
        LogFile=new QFile(LogFileName);
        if(LogFile->open(QIODevice::Append)==false){
            return false;
        }
    }
    QString s=QDateTime::currentDateTime().toString("yyMMdd-hh:mm:ss.zzz")
            + QString(" Func=")+Func
            + QString(" Arg1=")+Value1
            + QString(" Arg2=")+QString::number(Value2)
            + QString(" Return=")+QString::number(Result)
            + QString("\n");
    QByteArray  SArray=s.toLocal8Bit();
    LogFile->write(SArray.data());
    LogFile->flush();
    return true;
}
bool    CMvCamera::OutputLog(const QString &Func ,const QString &Value1 ,float Value2,int Result)
{
    if(OutputLogFile==false){
        QThread::msleep(10);
        return true;
    }
    if(LogFile==NULL){
        LogFile=new QFile(LogFileName);
        if(LogFile->open(QIODevice::Append)==false){
            return false;
        }
    }
    QString s=QDateTime::currentDateTime().toString("yyMMdd-hh:mm:ss.zzz")
            + QString(" Func=")+Func
            + QString(" Arg1=")+Value1
            + QString(" Arg2=")+QString::number(Value2,'f',5)
            + QString(" Return=")+QString::number(Result)
            + QString("\n");
    QByteArray  SArray=s.toLocal8Bit();
    LogFile->write(SArray.data());
    LogFile->flush();
    return true;
}
bool    CMvCamera::OutputLog(const QString &Func ,const QString &Value1 ,bool Value2,int Result)
{
    if(OutputLogFile==false){
        QThread::msleep(10);
        return true;
    }
    if(LogFile==NULL){
        LogFile=new QFile(LogFileName);
        if(LogFile->open(QIODevice::Append)==false){
            return false;
        }
    }
    QString s=QDateTime::currentDateTime().toString("yyMMdd-hh:mm:ss.zzz")
            + QString(" Func=")+Func
            + QString(" Arg1=")+Value1
            + QString(" Arg2=")+((Value2==true)?QString("true"):QString("false"))
            + QString(" Return=")+QString::number(Result)
            + QString("\n");
    QByteArray  SArray=s.toLocal8Bit();
    LogFile->write(SArray.data());
    LogFile->flush();
    return true;
}
bool    CMvCamera::OutputLog(const QString &Func ,const QString &Value1 ,const char *Value2,int Result)
{
    if(OutputLogFile==false){
        QThread::msleep(10);
        return true;
    }
    if(LogFile==NULL){
        LogFile=new QFile(LogFileName);
        if(LogFile->open(QIODevice::Append)==false){
            return false;
        }
    }
    QString s=QDateTime::currentDateTime().toString("yyMMdd-hh:mm:ss.zzz")
            + QString(" Func=")+Func
            + QString(" Arg1=")+Value1
            + QString(" Arg2=")+QString(Value2)
            + QString(" Return=")+QString::number(Result)
            + QString("\n");
    QByteArray  SArray=s.toLocal8Bit();
    LogFile->write(SArray.data());
    LogFile->flush();
    return true;
}
bool    CMvCamera::OutputLog(const QString &Func ,int64 Arg,int Result)
{
    if(OutputLogFile==false){
        QThread::msleep(10);
        return true;
    }
    if(LogFile==NULL){
        LogFile=new QFile(LogFileName);
        if(LogFile->open(QIODevice::Append)==false){
            return false;
        }
    }
    QString s=QDateTime::currentDateTime().toString("yyMMdd-hh:mm:ss.zzz")
            + QString(" Func=")+Func
            + QString(" Arg=")+QString::number(Arg)
            + QString(" Return=")+QString::number(Result)
            + QString("\n");
    QByteArray  SArray=s.toLocal8Bit();
    LogFile->write(SArray.data());
    LogFile->flush();
    return true;
}



// ch:初始化SDK | en:Initialize SDK
int CMvCamera::InitSDK()
{
	int nRet  = MV_CC_Initialize();
    OutputLog("MV_CC_Initialize"  ,nRet);
    SleepFunc();
    return nRet;
}

// ch:反初始化SDK | en:Finalize SDK
int CMvCamera::FinalizeSDK()
{
	int nRet  = MV_CC_Finalize();
    OutputLog("MV_CC_Finalize" ,nRet);
    SleepFunc();
    return nRet;
}

// ch:获取SDK版本号 | en:Get SDK Version
int CMvCamera::GetSDKVersion()
{
    int nRet  = MV_CC_GetSDKVersion();
    OutputLog("MV_CC_GetSDKVersion" ,nRet);
    SleepFunc();
    return nRet;
}

// ch:枚举设备 | en:Enumerate Device
int CMvCamera::EnumDevices(unsigned int nTLayerType, MV_CC_DEVICE_INFO_LIST* pstDevList)
{
    int nRet  = MV_CC_EnumDevices(nTLayerType, pstDevList);
    OutputLog("MV_CC_EnumDevices" ,nTLayerType ,nRet);
    SleepFunc();
    return nRet;
}

// ch:判断设备是否可达 | en:Is the device accessible
bool CMvCamera::IsDeviceAccessible(MV_CC_DEVICE_INFO* pstDevInfo, unsigned int nAccessMode)
{
    int nRet  = MV_CC_IsDeviceAccessible(pstDevInfo, nAccessMode);
    OutputLog("MV_CC_IsDeviceAccessible" ,nAccessMode ,nRet);
    SleepFunc();
    return nRet;
}

// ch:打开设备 | en:Open Device
int CMvCamera::Open(MV_CC_DEVICE_INFO* pstDeviceInfo)
{
    if (MV_NULL == pstDeviceInfo)
    {
        return MV_E_PARAMETER;
    }

    if (m_hDevHandle)
    {
        return MV_E_CALLORDER;
    }

    int nRet  = MV_CC_CreateHandle(&m_hDevHandle, pstDeviceInfo);
    OutputLog("MV_CC_CreateHandle" ,nRet);
    if (MV_OK != nRet)
    {
        return nRet;
    }
    SleepFunc();

    nRet = MV_CC_OpenDevice(m_hDevHandle);
    OutputLog("MV_CC_OpenDevice" ,nRet);
    if (MV_OK != nRet)
    {
        nRet=MV_CC_DestroyHandle(m_hDevHandle);
        OutputLog("MV_CC_DestroyHandle" ,nRet);
        m_hDevHandle = MV_NULL;
    }
    SleepFunc();

    return nRet;
}

// ch:关闭设备 | en:Close Device
int CMvCamera::Close()
{
    if (MV_NULL == m_hDevHandle)
    {
        return MV_E_HANDLE;
    }

    int nRet1 = MV_CC_CloseDevice(m_hDevHandle);
    OutputLog("MV_CC_CloseDevice" ,nRet1);
    SleepFunc();

    int nRet2 = MV_CC_DestroyHandle(m_hDevHandle);
    OutputLog("MV_CC_DestroyHandle" ,nRet2);
    m_hDevHandle = MV_NULL;

    return nRet2;
}
int CMvCamera::SetBayerCvtQuality(int n)
{
	int nRet = MV_CC_SetBayerCvtQuality(m_hDevHandle, n);
    OutputLog("MV_CC_SetBayerCvtQuality" ,n ,nRet);
    SleepFunc();
    return nRet;
}

// ch:判断相机是否处于连接状态 | en:Is The Device Connected
bool CMvCamera::IsDeviceConnected()
{
    int nRet = MV_CC_IsDeviceConnected(m_hDevHandle);
    OutputLog("MV_CC_IsDeviceConnected" ,nRet);
    SleepFunc();
    return nRet;
}

// ch:注册图像数据回调 | en:Register Image Data CallBack
int CMvCamera::RegisterImageCallBack(void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser), void* pUser)
{
    int nRet =MV_CC_RegisterImageCallBackEx(m_hDevHandle, cbOutput, pUser);
    OutputLog("MV_CC_RegisterImageCallBackEx" ,nRet);
    SleepFunc();
    return nRet;
}

int CMvCamera::ClearImageBuffer()
{
    int nRet = MV_CC_ClearImageBuffer(m_hDevHandle);
    OutputLog("MV_CC_ClearImageBuffer" ,nRet);
    SleepFunc();
    return nRet;
}

// ch:开启抓图 | en:Start Grabbing
int CMvCamera::StartGrabbing()
{
    int nRet=0;
    if(Grabbing==false){
        nRet =MV_CC_StartGrabbing(m_hDevHandle);
        if(nRet!=0){
            nRet =MV_CC_StopGrabbing(m_hDevHandle);
            SleepFunc();
            nRet =MV_CC_StartGrabbing(m_hDevHandle);
        }
        OutputLog("MV_CC_StartGrabbing" ,nRet);
        SleepFunc();
    }
    Grabbing=true;
    return nRet;
}

// ch:停止抓图 | en:Stop Grabbing
int CMvCamera::StopGrabbing()
{
    Grabbing=false;
    int nRet =MV_CC_StopGrabbing(m_hDevHandle);
    OutputLog("MV_CC_StopGrabbing" ,nRet);
    SleepFunc();
    return nRet;
}

bool    CMvCamera::IsGrabbing(void)
{
    return Grabbing;
}


int CMvCamera::GetResolution(int &Width ,int &Height)
{
    int nRet = MV_OK;
    MVCC_INTVALUE stWidth = {0};
    MVCC_INTVALUE stHeight = {0};
    
    // 1. 幅 (Width) の取得
    nRet = MV_CC_GetIntValue(m_hDevHandle, "WidthMax", &stWidth);
    OutputLog("MV_CC_GetIntValue" ,"WidthMax" ,nRet);
    if (MV_OK != nRet) {
        return nRet;
    }
    SleepFunc();

    // 2. 高さ (Height) の取得
    nRet = MV_CC_GetIntValue(m_hDevHandle, "HeightMax", &stHeight);
    OutputLog("MV_CC_GetIntValue" ,"HeightMax" ,nRet);
    if (MV_OK != nRet) {
        return nRet;
    }
    SleepFunc();

    Width   =stWidth.nCurValue;
	Height  = stHeight.nCurValue;
    return  nRet;
}

// ch:主动获取一帧图像数据 | en:Get one frame initiatively
int CMvCamera::GetImageBuffer(MV_FRAME_OUT* pFrame, int nMsec)
{
    int nRet = MV_CC_GetImageBuffer(m_hDevHandle, pFrame, nMsec);
    OutputLog("MV_CC_GetImageBuffer" ,nMsec ,nRet);
    SleepFunc();

    return  nRet;
}

// ch:释放图像缓存 | en:Free image buffer
int CMvCamera::FreeImageBuffer(MV_FRAME_OUT* pFrame)
{
    int nRet = MV_CC_FreeImageBuffer(m_hDevHandle, pFrame);
    OutputLog("MV_CC_GetImageBuffer" ,nRet);
    SleepFunc();

    return  nRet;
}

// ch:设置显示窗口句柄 | en:Set Display Window Handle
int CMvCamera::DisplayOneFrame(void* hwndDisplay,MV_CC_IMAGE* pImageInfo)
{
	int nRet = MV_CC_DisplayOneFrameEx2(m_hDevHandle, hwndDisplay, pImageInfo,0);
    OutputLog("MV_CC_DisplayOneFrameEx2" ,nRet);
    return  nRet;  
}

// ch:设置SDK内部图像缓存节点个数 | en:Set the number of the internal image cache nodes in SDK
int CMvCamera::SetImageNodeNum(unsigned int nNum)
{
    int nRet = MV_CC_SetImageNodeNum(m_hDevHandle, nNum);
    OutputLog("MV_CC_SetImageNodeNum" ,nNum ,nRet);
    return  nRet;  
}

// ch:获取设备信息 | en:Get device information
int CMvCamera::GetDeviceInfo(MV_CC_DEVICE_INFO* pstDevInfo)
{
    int nRet = MV_CC_GetDeviceInfo(m_hDevHandle, pstDevInfo);
    OutputLog("MV_CC_GetDeviceInfo" ,nRet);
    SleepFunc();

    return  nRet;  
}

// ch:获取GEV相机的统计信息 | en:Get detect info of GEV camera
int CMvCamera::GetGevAllMatchInfo(MV_MATCH_INFO_NET_DETECT* pMatchInfoNetDetect)
{
    if (MV_NULL == pMatchInfoNetDetect)
    {
        return MV_E_PARAMETER;
    }

    MV_CC_DEVICE_INFO stDevInfo = {0};
    GetDeviceInfo(&stDevInfo);
    if (stDevInfo.nTLayerType != MV_GIGE_DEVICE)
    {
        return MV_E_SUPPORT;
    }

    MV_ALL_MATCH_INFO struMatchInfo = {0};

    struMatchInfo.nType = MV_MATCH_TYPE_NET_DETECT;
    struMatchInfo.pInfo = pMatchInfoNetDetect;
    struMatchInfo.nInfoSize = sizeof(MV_MATCH_INFO_NET_DETECT);
    memset(struMatchInfo.pInfo, 0, sizeof(MV_MATCH_INFO_NET_DETECT));

    return MV_CC_GetAllMatchInfo(m_hDevHandle, &struMatchInfo);
}

// ch:获取U3V相机的统计信息 | en:Get detect info of U3V camera
int CMvCamera::GetU3VAllMatchInfo(MV_MATCH_INFO_USB_DETECT* pMatchInfoUSBDetect)
{
    if (MV_NULL == pMatchInfoUSBDetect)
    {
        return MV_E_PARAMETER;
    }

    MV_CC_DEVICE_INFO stDevInfo = {0};
    GetDeviceInfo(&stDevInfo);
    if (stDevInfo.nTLayerType != MV_USB_DEVICE)
    {
        return MV_E_SUPPORT;
    }

    MV_ALL_MATCH_INFO struMatchInfo = {0};

    struMatchInfo.nType = MV_MATCH_TYPE_USB_DETECT;
    struMatchInfo.pInfo = pMatchInfoUSBDetect;
    struMatchInfo.nInfoSize = sizeof(MV_MATCH_INFO_USB_DETECT);
    memset(struMatchInfo.pInfo, 0, sizeof(MV_MATCH_INFO_USB_DETECT));
    
    return MV_CC_GetAllMatchInfo(m_hDevHandle, &struMatchInfo);
}

    
int CMvCamera::GetIntValue(IN const char* strKey, OUT MVCC_INTVALUE *pIntValue)
{
    int nRet = MV_CC_GetIntValue(m_hDevHandle, strKey, pIntValue);
    OutputLog("MV_CC_GetIntValue" ,strKey ,nRet);
    SleepFunc();

    return  nRet; 
}

    
int CMvCamera::SetIntValue(IN const char* strKey, IN unsigned int nValue)
{
    int nRet = MV_CC_SetIntValue(m_hDevHandle, strKey, nValue);
    OutputLog("MV_CC_SetIntValue" ,strKey ,(int64)nValue,nRet);
    SleepFunc();

    return  nRet; 
}


// ch:获取和设置Int型参数，如 Width和Height
// en:Get Int type parameters, such as Width and Height
int CMvCamera::GetIntValue(IN const char* strKey, OUT MVCC_INTVALUE_EX *pIntValue)
{
    int nRet = MV_CC_GetIntValueEx(m_hDevHandle, strKey, pIntValue);
    OutputLog("MV_CC_GetIntValueEx" ,strKey ,nRet);
    SleepFunc();

    return  nRet; 
}

int CMvCamera::SetIntValue(IN const char* strKey, IN int64_t nValue)
{
    int nRet = MV_CC_SetIntValueEx(m_hDevHandle, strKey, nValue);
    OutputLog("MV_CC_SetIntValueEx" ,strKey ,(int64)nValue,nRet);
    SleepFunc();

    return  nRet; 
}

// ch:获取和设置Enum型参数，如 PixelFormat
// en:Get Enum type parameters, such as PixelFormat
int CMvCamera::GetEnumValue(IN const char* strKey, OUT MVCC_ENUMVALUE *pEnumValue)
{
    int nRet = MV_CC_GetEnumValue(m_hDevHandle, strKey, pEnumValue);
    OutputLog("MV_CC_GetEnumValue" ,strKey ,nRet);
    SleepFunc();

    return  nRet; 
}

int CMvCamera::SetEnumValue(IN const char* strKey, IN unsigned int nValue)
{
    int nRet = MV_CC_SetEnumValue(m_hDevHandle, strKey, nValue);
    OutputLog("MV_CC_SetEnumValue" ,strKey ,(int64)nValue,nRet);
    SleepFunc();

    return  nRet; 
}

int CMvCamera::SetEnumValueByString(IN const char* strKey, IN const char* sValue)
{
    int nRet = MV_CC_SetEnumValueByString(m_hDevHandle, strKey, sValue);
    OutputLog("MV_CC_SetEnumValueByString" ,strKey ,sValue,nRet);
    SleepFunc();
    return  nRet; 
}

int CMvCamera::GetEnumEntrySymbolic(IN const char* strKey, IN MVCC_ENUMENTRY* pstEnumEntry)
{
    int nRet = MV_CC_GetEnumEntrySymbolic(m_hDevHandle, strKey, pstEnumEntry);
    OutputLog("MV_CC_GetEnumEntrySymbolic" ,strKey,nRet);
    SleepFunc();

    return  nRet; 
}

// ch:获取和设置Float型参数，如 ExposureTime和Gain
// en:Get Float type parameters, such as ExposureTime and Gain
int CMvCamera::GetFloatValue(IN const char* strKey, OUT MVCC_FLOATVALUE *pFloatValue)
{
    int nRet = MV_CC_GetFloatValue(m_hDevHandle, strKey, pFloatValue);
    OutputLog("MV_CC_GetFloatValue" ,strKey,nRet);
    SleepFunc();

    return  nRet; 
}

int CMvCamera::SetFloatValue(IN const char* strKey, IN float fValue)
{
    int nRet = MV_CC_SetFloatValue(m_hDevHandle, strKey, fValue);
    OutputLog("MV_CC_SetFloatValue" ,strKey,fValue,nRet);
    SleepFunc();

    return  nRet; 
}

// ch:获取和设置Bool型参数，如 ReverseX
// en:Get Bool type parameters, such as ReverseX
int CMvCamera::GetBoolValue(IN const char* strKey, OUT bool *pbValue)
{
    int nRet = MV_CC_GetBoolValue(m_hDevHandle, strKey, pbValue);
    OutputLog("MV_CC_GetBoolValue" ,strKey,nRet);
    SleepFunc();

    return  nRet; 
}

int CMvCamera::SetBoolValue(IN const char* strKey, IN bool bValue)
{
    int nRet = MV_CC_SetBoolValue(m_hDevHandle, strKey, bValue);
    OutputLog("MV_CC_SetBoolValue" ,strKey,bValue,nRet);
    SleepFunc();

    return  nRet; 
}

// ch:获取和设置String型参数，如 DeviceUserID
// en:Get String type parameters, such as DeviceUserID
int CMvCamera::GetStringValue(IN const char* strKey, MVCC_STRINGVALUE *pStringValue)
{
    int nRet = MV_CC_GetStringValue(m_hDevHandle, strKey, pStringValue);
    OutputLog("MV_CC_GetStringValue" ,strKey,nRet);
    SleepFunc();

    return  nRet; 
}

int CMvCamera::SetStringValue(IN const char* strKey, IN const char* strValue)
{
    int nRet = MV_CC_SetStringValue(m_hDevHandle, strKey, strValue);
    OutputLog("MV_CC_SetStringValue" ,strKey,strValue,nRet);
    SleepFunc();

    return  nRet; 
}

// ch:执行一次Command型命令，如 UserSetSave
// en:Execute Command once, such as UserSetSave
int CMvCamera::CommandExecute(IN const char* strKey)
{
    int nRet = MV_CC_SetCommandValue(m_hDevHandle, strKey);
    OutputLog("MV_CC_SetCommandValue" ,strKey,nRet);
    SleepFunc();

    return  nRet; 
}

// ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
int CMvCamera::GetOptimalPacketSize(unsigned int* pOptimalPacketSize)
{
    if (MV_NULL == pOptimalPacketSize)
    {
        return MV_E_PARAMETER;
    }

    int nRet = MV_CC_GetOptimalPacketSize(m_hDevHandle);
    OutputLog("MV_CC_GetOptimalPacketSize",nRet);
    if (nRet < MV_OK)
    {
        return nRet;
    }
    SleepFunc();
    *pOptimalPacketSize = (unsigned int)nRet;

    return MV_OK;
}

// ch:注册消息异常回调 | en:Register Message Exception CallBack
int CMvCamera::RegisterExceptionCallBack(void(__stdcall* cbException)(unsigned int nMsgType, void* pUser),void* pUser)
{
    int nRet = MV_CC_RegisterExceptionCallBack(m_hDevHandle, cbException, pUser);
    OutputLog("MV_CC_RegisterExceptionCallBack",nRet);
    SleepFunc();

    return  nRet;
}

// ch:注册单个事件回调 | en:Register Event CallBack
int CMvCamera::RegisterEventCallBack(const char* pEventName, void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser), void* pUser)
{
    int nRet = MV_CC_RegisterEventCallBackEx(m_hDevHandle, pEventName, cbEvent, pUser);
    OutputLog("MV_CC_RegisterEventCallBackEx" ,pEventName,nRet);
    SleepFunc();

    return  nRet;
}

// ch:强制IP | en:Force IP
int CMvCamera::ForceIp(unsigned int nIP, unsigned int nSubNetMask, unsigned int nDefaultGateWay)
{
    int nRet = MV_GIGE_ForceIpEx(m_hDevHandle, nIP, nSubNetMask, nDefaultGateWay);
    OutputLog("MV_GIGE_ForceIpEx" ,nIP,nRet);
    SleepFunc();

    return  nRet;
}

// ch:配置IP方式 | en:IP configuration method
int CMvCamera::SetIpConfig(unsigned int nType)
{
    int nRet = MV_GIGE_SetIpConfig(m_hDevHandle, nType);
    OutputLog("MV_GIGE_SetIpConfig" ,nType,nRet);
    SleepFunc();

    return  nRet;
}

// ch:设置网络传输模式 | en:Set Net Transfer Mode
int CMvCamera::SetNetTransMode(unsigned int nType)
{
    int nRet = MV_GIGE_SetNetTransMode(m_hDevHandle, nType);
    OutputLog("MV_GIGE_SetNetTransMode" ,nType,nRet);
    SleepFunc();

    return  nRet;
}

// ch:像素格式转换 | en:Pixel format conversion
int CMvCamera::ConvertPixelType(MV_CC_PIXEL_CONVERT_PARAM_EX* pstCvtParam)
{
    int nRet = MV_CC_ConvertPixelTypeEx(m_hDevHandle, pstCvtParam);
    OutputLog("MV_CC_ConvertPixelTypeEx",nRet);
    SleepFunc();

    return  nRet;
}

int CMvCamera::HB_Decode(MV_CC_HB_DECODE_PARAM *pstDecodeParam)
{
    int nRet = MV_CC_HB_Decode(m_hDevHandle, pstDecodeParam);
    OutputLog("MV_CC_HB_Decode",nRet);
    SleepFunc();

    return  nRet;
}

// ch:保存图片 | en:save image
int CMvCamera::SaveImage(MV_SAVE_IMAGE_PARAM_EX3* pstParam)
{
    int nRet = MV_CC_SaveImageEx3(m_hDevHandle, pstParam);
    OutputLog("MV_CC_SaveImageEx3",nRet);
    SleepFunc();

    return  nRet;
}

// ch:保存图片为文件 | en:Save the image as a file
int CMvCamera::SaveImageToFile(MV_CC_IMAGE* pstImage, MV_CC_SAVE_IMAGE_PARAM* pSaveImageParam, const char* pcImagePath)
{
	int nRet = MV_CC_SaveImageToFileEx2(m_hDevHandle, pstImage, pSaveImageParam, pcImagePath);
    OutputLog("MV_CC_SaveImageToFileEx2",nRet);
    SleepFunc();

    return  nRet;
}

// ch:绘制圆形辅助线 | en:Draw circle auxiliary line
int CMvCamera::DrawCircle(MVCC_CIRCLE_INFO* pCircleInfo)
{
    int nRet = MV_CC_DrawCircle(m_hDevHandle, pCircleInfo);
    OutputLog("MV_CC_DrawCircle",nRet);
    SleepFunc();

    return  nRet;
}

// ch:绘制线形辅助线 | en:Draw lines auxiliary line
int CMvCamera::DrawLines(MVCC_LINES_INFO* pLinesInfo)
{
    int nRet = MV_CC_DrawLines(m_hDevHandle, pLinesInfo);
    OutputLog("MV_CC_DrawLines",nRet);
    SleepFunc();

    return  nRet;
}
bool CMvCamera::GetLine0Input(void)
{
    if (m_hDevHandle == nullptr) {
        return false;
    }

    int nRet = MV_OK;

    nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "LineSelector", "Line0");
    OutputLog("MV_CC_SetEnumValueByString" ,"LineSelector",nRet);
    if (nRet != MV_OK) {
        return false;
    }
    SleepFunc();

    // 2. Line0の現在の状態(LineStatus)を取得
    bool bIsHigh = false;
    nRet = MV_CC_GetBoolValue(m_hDevHandle, "LineStatus", &bIsHigh);
    OutputLog("MV_CC_GetBoolValue" ,"LineStatus",nRet);
    if (nRet != MV_OK) {
        return false;
    }
    SleepFunc();

    return bIsHigh; // true: High, false: Low
}

bool CMvCamera::SetLine1Output(bool bHigh)
{
    if (m_hDevHandle == nullptr) {
        return false;
    }

    int nRet = MV_OK;

    // 1. 対象をLine1に設定
    MVCC_ENUMENTRY  LineTarget;
    GetEnumEntrySymbolic("LineSelector", &LineTarget);
    nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "LineSelector", "Line1");
    OutputLog("MV_CC_SetEnumValueByString" ,"LineSelector", "Line1",nRet);
    if (nRet != MV_OK) {
        return false;
    }
    SleepFunc();

    nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "LineMode", "Strobe");
    OutputLog("MV_CC_SetEnumValueByString" ,"LineMode", "Strobe" ,nRet);

    // 2. ソフトウェア制御(UserOutput1)をLine1の出力ソースに設定
    //MVCC_ENUMENTRY  LineSourceEntry;
    //GetEnumEntrySymbolic("LineSource", &LineSourceEntry);
    //nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "LineSource", "UserOutput1");
    //if (nRet != MV_OK) {
    //    return false;
    //}
    //
    //// 3. UserOutputの操作対象をUserOutput1に設定
    //nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "UserOutputSelector", "UserOutput1");
    //if (nRet != MV_OK) {
    //    return false;
    //}
    SleepFunc();

    // 4. 実際の出力値(true=High, false=Low)を書き込む
    nRet = MV_CC_SetBoolValue(m_hDevHandle, "LineInverter", bHigh);
    OutputLog("MV_CC_SetBoolValue" ,"LineInverter",bHigh,nRet);
    if (nRet != MV_OK) {
        return false;
    }
    SleepFunc();

    return true;
}

bool CMvCamera::SetupLineTriggers(bool LineTriggerMode , int LineNo)
{
    int nRet = MV_OK;

    // --- 1: ライントリガーをLine0に設定 ---
    // Selectorをライントリガー(LineStart)に切り替え
    nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "TriggerSelector", "LineStart");
    OutputLog("MV_CC_SetEnumValueByString" ,"TriggerSelector", "LineStart" ,nRet);
    if (nRet != MV_OK) return false;
    SleepFunc();

    // LineStartのトリガーモードをON
    if(LineTriggerMode==true){
		nRet = MV_CC_SetEnumValueByString(m_hDevHandle,"TriggerMode","On");
        OutputLog("MV_CC_SetEnumValueByString" ,"TriggerMode", "On" ,nRet);
	}
	else{
		nRet = MV_CC_SetEnumValueByString(m_hDevHandle,"TriggerMode","Off");
        OutputLog("MV_CC_SetEnumValueByString" ,"TriggerMode", "Off" ,nRet);
	}
    SleepFunc();

    nRet = MV_CC_SetEnumValue(m_hDevHandle, "TriggerSource", LineNo);
    OutputLog("MV_CC_SetEnumValue" ,"TriggerSource", (int64)LineNo ,nRet);
    SleepFunc();

    return true;
}
bool CMvCamera::SetupFrameTriggers(bool FrameTriggerMode , int LineNo)
{
    int nRet = MV_OK;

    nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "TriggerSelector", "FrameBurstStart");
    OutputLog("MV_CC_SetEnumValueByString" ,"TriggerSource", "FrameBurstStart" ,nRet);
    if (nRet != MV_OK) return false;
    SleepFunc();

    if(FrameTriggerMode==true){
		nRet = MV_CC_SetEnumValueByString(m_hDevHandle,"TriggerMode","On");
        OutputLog("MV_CC_SetEnumValueByString" ,"TriggerMode", "On" ,nRet);
	}
	else{
		nRet = MV_CC_SetEnumValueByString(m_hDevHandle,"TriggerMode","Off");
        OutputLog("MV_CC_SetEnumValueByString" ,"TriggerMode", "Off" ,nRet);
	}
    SleepFunc();

    nRet = MV_CC_SetEnumValue(m_hDevHandle, "TriggerSource", LineNo);
    OutputLog("MV_CC_SetEnumValue" ,"TriggerSource", (int64)LineNo ,nRet);
    SleepFunc();

    return true;
}

bool CMvCamera::SetupFrameTriggersDelay(float FrameDelay)
{
    int nRet = MV_OK;

    nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "TriggerSelector", "FrameBurstStart");
    OutputLog("MV_CC_SetEnumValueByString" ,"TriggerSource", "FrameBurstStart" ,nRet);
    if (nRet != MV_OK) return false;
    SleepFunc();

    nRet = MV_CC_SetFloatValue(m_hDevHandle, "TriggerDelay", FrameDelay);
    OutputLog("MV_CC_SetFloatValue" ,"TriggerDelay", FrameDelay ,nRet);
    SleepFunc();

    return true;
}
    
void CMvCamera::GetLineTriggerSettings(bool &LineTriggerMode , int &LineNo)
{
    MVCC_ENUMVALUE stMode = {0};
    MVCC_ENUMVALUE stSource = {0};

    int nRet1 =MV_CC_SetEnumValueByString(m_hDevHandle, "TriggerSelector", "LineStart");
    OutputLog("MV_CC_SetEnumValueByString" ,"TriggerSelector", "LineStart" ,nRet1);
    SleepFunc();

    int nRet2 =MV_CC_GetEnumValue(m_hDevHandle, "TriggerMode", &stMode);
    OutputLog("MV_CC_GetEnumValue" ,"TriggerMode" ,nRet2);
    SleepFunc();

    int nRet3 =MV_CC_GetEnumValue(m_hDevHandle, "TriggerSource", &stSource);
    OutputLog("MV_CC_GetEnumValue" ,"TriggerSource" ,nRet3);
    SleepFunc();

    LineTriggerMode =(stMode.nCurValue == 1)? true:false;
    LineNo          =stSource.nCurValue;
}

void CMvCamera::GetFrameTriggerSettings(bool &FrameTriggerMode , int &LineNo)
{
    MVCC_ENUMVALUE stMode = {0};
    MVCC_ENUMVALUE stSource = {0};

    int nRet1 =MV_CC_SetEnumValueByString(m_hDevHandle, "TriggerSelector", "FrameBurstStart");
    OutputLog("MV_CC_SetEnumValueByString" ,"TriggerSelector", "FrameBurstStart" ,nRet1);
    SleepFunc();

    int nRet2 =MV_CC_GetEnumValue(m_hDevHandle, "TriggerMode", &stMode);
    OutputLog("MV_CC_GetEnumValue" ,"TriggerMode", nRet2);
    SleepFunc();

    int nRet3 =MV_CC_GetEnumValue(m_hDevHandle, "TriggerSource", &stSource);
    OutputLog("MV_CC_GetEnumValue" ,"TriggerSource", nRet3);
    SleepFunc();

    FrameTriggerMode=(stMode.nCurValue == 1)? true:false;
    LineNo          =stSource.nCurValue;
}



bool CMvCamera::SetRGBGain(float rGain, float gGain, float bGain)
{
    int nRet = MV_OK;

    auto setGain = [&](const char* color, float val) {
        int nRet1 = MV_CC_SetEnumValueByString(m_hDevHandle, "GainSelector", color);
        OutputLog("MV_CC_SetEnumValueByString" ,"GainSelector", nRet1);
        SleepFunc();

        int nRet2 = MV_CC_SetFloatValue(m_hDevHandle, "Gain", val);
        OutputLog("MV_CC_SetFloatValue" ,"Gain", nRet2);
        SleepFunc();
        return nRet2;
    };

    nRet |= setGain("Red", rGain);
    nRet |= setGain("Green", gGain);
    nRet |= setGain("Blue", bGain);

    if (nRet != MV_OK) {
        return false;
    }
    return true;
}    


struct GainInfo {
    float current;
    float min;
    float max;
	int nRet;
};

bool CMvCamera::GetRGBGain(float &rGain, float &gGain, float &bGain
                            ,float *RMinValue, float *RMaxValue
                            ,float *GMinValue, float *GMaxValue
                            ,float *BMinValue, float *BMaxValue)
{
    // 内部ヘルパーラムダ関数: 指定した色のゲイン情報を取得する
    auto getGain = [&](const char* colorName) -> GainInfo {
        GainInfo info = {0.0f, 0.0f, 0.0f};
        
        // 1. 対象の色 (Red, Green, Blue) をセレクタに設定
        int nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "GainSelector", colorName);
        OutputLog("MV_CC_SetEnumValueByString" ,"GainSelector", nRet);
        if (nRet != MV_OK) {
            info.nRet = nRet;
            return info;
        }
        SleepFunc();
        // 2. ゲイン値を取得
        // 取得先の構造体 MVCC_FLOATVALUE に fCurValue(現在値), fMin(最小値), fMax(最大値) が格納されます
        MVCC_FLOATVALUE stFloatVal = {0};
        nRet = MV_CC_GetFloatValue(m_hDevHandle, "Gain", &stFloatVal);
        OutputLog("MV_CC_GetFloatValue" ,"Gain", nRet);
        if (nRet == MV_OK) {
            info.current = stFloatVal.fCurValue;
            info.min = stFloatVal.fMin;
            info.max = stFloatVal.fMax;
			info.nRet = nRet;
        }
        SleepFunc();
        return info;
    };

    GainInfo redGain   = getGain("Red");
    GainInfo greenGain = getGain("Green");
    GainInfo blueGain  = getGain("Blue");
	rGain = redGain.current;
	gGain = greenGain.current;
    bGain = blueGain.current;
    if (RMinValue) *RMinValue = redGain.min;
    if (RMaxValue) *RMaxValue = redGain.max;
    if (GMinValue) *GMinValue = greenGain.min;
    if (GMaxValue) *GMaxValue = greenGain.max;
    if (BMinValue) *BMinValue = blueGain.min;
	if(BMaxValue) *BMaxValue = blueGain.max;
    if(redGain.nRet==MV_OK && greenGain.nRet==MV_OK && blueGain.nRet==MV_OK){
        // 全てのゲイン情報が正常に取得できた場合は成功とみなす
		return true;
    }
    else{
        // いずれかのゲイン情報の取得に失敗した場合はエラー処理を行う
        // 例えば、エラーログを出力するなど
		return false;
	}
}

bool CMvCamera::SetTDIDirection(bool b)
{
    int nRet = MV_CC_SetBoolValue(m_hDevHandle, "ReverseScanDirection",  b);
    OutputLog("MV_CC_SetBoolValue" ,"ReverseScanDirection",b, nRet);
    SleepFunc();

    if (nRet == MV_OK) { 
        return true;
    } else {
        return false;
    }
}
bool CMvCamera::GetTDIDirection(bool &b)
{
    int nRet = MV_CC_GetBoolValue(m_hDevHandle, "ReverseScanDirection", &b);
    OutputLog("MV_CC_GetBoolValue" ,"ReverseScanDirection", nRet);
    if (nRet == MV_OK) {
		return true;
    }
    SleepFunc();
    return false;
}

bool    CMvCamera::SetLineFormat(int LineNo,int LineFormat)
{
	QString LineSelectorStr="Line"+QString::number(LineNo);    
	QByteArray  A=LineSelectorStr.toLocal8Bit();
	char *LineSelector = A.data();  
    int nRet = MV_CC_SetEnumValueByString(m_hDevHandle, "LineSelector", LineSelector);
    OutputLog("MV_CC_SetEnumValueByString" ,"LineSelector",nRet);
    if (nRet != MV_OK) {
        return false;
    }
    SleepFunc();
    nRet = MV_CC_SetEnumValue(m_hDevHandle, "LineFormat", LineFormat);
    if (nRet != MV_OK) {
        return false;
    }
    SleepFunc();

	return true;
}
