/*
 * Copyright (C) 2019
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

#include "LightHIKRobotLAN.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include <QDir>
#include <QFile>
#include "XCriticalFunc.h"
#include "SettingLightDialog.h"

//=================================================================================================


LightSourceValue::LightSourceValue()
{
	Brightness=100;
	ONMode = true;
}

LightSourceValue::~LightSourceValue()
{
}

	
bool	LightSourceValue::Save(QIODevice *f)
{
	QDataStream out(f);
	out.setVersion(QDataStream::Qt_5_15);
	out<<Brightness;
	out<<ONMode;
	return true;
}
	
bool	LightSourceValue::Load(QIODevice *f)
{
	QDataStream in(f);
	in.setVersion(QDataStream::Qt_5_15);
	in>>Brightness;
	in>>ONMode;
	return true;
}

//=================================================================================================


LightHIKRobotLAN::LightHIKRobotLAN(LayersBase *base,const QString &LightParamStr)
	:LightDLLBaseClass(base->GetMainWidget(),base)
{
	DeviceNo	=0;
	ChannelCount=0;
	LightDim	=NULL;
	memset(&m_deviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    
    LoadCommon();
    Open(LightParamStr);
}

LightHIKRobotLAN::~LightHIKRobotLAN(void)
{
    Close();
}

bool	LightHIKRobotLAN::Open(const QString &LightParamStr)
{
    // デバイスの検索とリスト取得
    int deviceCount = enumerateDevices();
    if (deviceCount == 0) {
        emit errorOccurred("デバイスが見つかりませんでした。");
        return false;
    }
    DeviceNo=SelectDevice(deviceCount,LightParamStr);
    // デバイスに接続
    if (!connectByIndex(DeviceNo)) {
		return false;
    }
    ChannelCount=getChannelCount();

    if(LightDim!=NULL){
        delete [] LightDim;
        LightDim = NULL;
	}
	LightDim = new LightSourceValue[ChannelCount];

    return true;
}

bool	LightHIKRobotLAN::Close(void)
{
    disconnectDevice();
    if(LightDim!=NULL){
        delete[] LightDim;
        LightDim=NULL;
    }
    return true;
}

bool	LightHIKRobotLAN::Save(QIODevice *f)
{
	if(::Save(f,DeviceNo)==false)
		return false;
	if(::Save(f,ChannelCount)==false)
		return false;

	for(int s=0;s<ChannelCount;s++){
		if(LightDim[s].Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	LightHIKRobotLAN::Load(QIODevice *f)
{
	if(::Load(f,DeviceNo)==false)
		return false;
	if(::Load(f,ChannelCount)==false)
		return false;

    if(LightDim!=NULL){
        delete [] LightDim;
        LightDim = NULL;
	}
	LightDim = new LightSourceValue[ChannelCount];

	for(int s=0;s<ChannelCount;s++){
		if(LightDim[s].Load(f)==false){
			return false;
		}
	}
	return true;
}

const	char		*LightHIKRobotLAN::CommentFileName="LightHIKRobotLANCommon.dat";

bool	LightHIKRobotLAN::SaveCommon()
{
	QString filePath = GetLayersBase()->GetUserPath()+QDir::separator()+CommentFileName;
	QFile file(filePath);
	if(file.open(QIODevice::WriteOnly)==true){
		if(::Save(&file,ChannelNames)==false){
            return false;
        }
	}
	return true;
}

bool	LightHIKRobotLAN::LoadCommon()
{
	QString filePath = GetLayersBase()->GetUserPath()+QDir::separator()+CommentFileName;
	QFile file(filePath);
	if(file.open(QIODevice::ReadOnly)==true){
		if(::Load(&file,ChannelNames)==false){
            return false;
        }
	}
	return true;
}


bool	LightHIKRobotLAN::ShowSettingDialog(void)
{
	SettingLightDialog	*LightForm=new SettingLightDialog(this);
	bool	Ret=LightForm->exec();
    if(Ret==true){
	    for(int s = 0;s<ChannelCount;s++){
		    LightDim[s] = LightForm->LightDim[s];
	    }
		ChannelNames = LightForm->ChannelNames;
        SaveCommon();

        ReflectPhysical();
	}
	delete LightForm;
	return Ret;
}

void	LightHIKRobotLAN::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CloseApplicationSpecifiedBroadcaster *CloseApplicationSpecifiedBroadcasterVar = dynamic_cast<CloseApplicationSpecifiedBroadcaster *>(v);
    if(CloseApplicationSpecifiedBroadcasterVar!=NULL){
        Close();
        return;
	}
}

	//Don't call directly

bool	LightHIKRobotLAN::InitialPhysical(const QString &Param)
{
    Open(Param);

	return true;
}

bool	LightHIKRobotLAN::ReflectPhysical(void)
{
	for(int s=0;s<ChannelCount;s++){
        if(setChannelState(s+1, LightDim[s].ONMode)==false){
            emit errorOccurred(QString("チャンネル%1の状態の設定に失敗しました。").arg(s+1));
        }
        if(setBrightness(s+1, LightDim[s].Brightness)==false){
            emit errorOccurred(QString("チャンネル%1の明るさの設定に失敗しました。").arg(s+1));
        }
	}
	return true;
}

bool	LightHIKRobotLAN::ReflectPhysicalTurnOn(bool LightOn)
{
	for(int s=0;s<ChannelCount;s++){
        LightDim[s].ONMode=LightOn;
        if(setChannelState(s+1, LightDim[s].ONMode)==false){
            emit errorOccurred(QString("チャンネル%1の状態の設定に失敗しました。").arg(s+1));
        }
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
// ネットワーク上のGigEデバイスを検索
int LightHIKRobotLAN::enumerateDevices()
{
    memset(&m_deviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    
    // GigEデバイス（ネットワーク機器）のみを検索対象にする
    int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE, &m_deviceList);
    if (nRet != MV_OK) {
        emit errorOccurred(QString("デバイスの検索に失敗しました。エラーコード: %1").arg(nRet, 0, 16));
        return 0;
    }

    qDebug() << "発見したデバイス数:" << m_deviceList.nDeviceNum;
    return m_deviceList.nDeviceNum;
}

// UI（コンボボックスなど）に表示するためのデバイス名リストを取得
QStringList LightHIKRobotLAN::getDeviceNames() const
{
    QStringList names;
    for (unsigned int i = 0; i < m_deviceList.nDeviceNum; i++) {
        MV_CC_DEVICE_INFO* pDeviceInfo = m_deviceList.pDeviceInfo[i];
        
        if (pDeviceInfo && pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
            // IPアドレスのパース
            uint32_t ip = pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp;
            QString ipStr = QString("%1.%2.%3.%4")
                            .arg((ip >> 24) & 0xFF)
                            .arg((ip >> 16) & 0xFF)
                            .arg((ip >> 8) & 0xFF)
                            .arg(ip & 0xFF);
            
            // モデル名とユーザー定義名の取得
            QString modelName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chModelName));
            QString userDefName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName));
            
            // 例: "[0] MV-LE200-120W24-4TD (Light1) - 192.168.1.100"
            QString displayName = QString("[%1] %2 (%3) - %4").arg(i).arg(modelName).arg(userDefName).arg(ipStr);
            names << displayName;
        }
    }
    return names;
}

int LightHIKRobotLAN::SelectDevice(int deviceCount,const QString &LightParamStr)
{
    for (unsigned int i = 0; i < m_deviceList.nDeviceNum; i++) {
        MV_CC_DEVICE_INFO* pDeviceInfo = m_deviceList.pDeviceInfo[i];
        
        if (pDeviceInfo && pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
            // IPアドレスのパース
            uint32_t ip = pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp;
            QString ipStr = QString("%1.%2.%3.%4")
                            .arg((ip >> 24) & 0xFF)
                            .arg((ip >> 16) & 0xFF)
                            .arg((ip >> 8) & 0xFF)
                            .arg(ip & 0xFF);
            
            // モデル名とユーザー定義名の取得
            QString modelName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chModelName));
            QString userDefName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName));

            QStringList List=LightParamStr.split("=");
            if(List[0].trimmed()=="IP"){
                if(ipStr==List[1]){
                    return i;
                }
            }
            else if(List[0].trimmed()=="Model"){
                if(modelName==List[1]){
                    return i;
                }
            }
            else if(List[0].trimmed()=="UserDefName"){
                if(userDefName==List[1]){
                    return i;
                }
			}
            else if(List[0].trimmed()==ipStr){
                return i;
            }
            else if(List[0].trimmed()==modelName){
                return i;
            }
            else if(List[0].trimmed()==userDefName){
                return i;
			}
        }
    }

    for (unsigned int i = 0; i < m_deviceList.nDeviceNum; i++) {
        MV_CC_DEVICE_INFO* pDeviceInfo = m_deviceList.pDeviceInfo[i];
        
        if (pDeviceInfo && pDeviceInfo->nTLayerType == MV_GIGE_DEVICE) {
            // IPアドレスのパース
            uint32_t ip = pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp;
            QString ipStr = QString("%1.%2.%3.%4")
                            .arg((ip >> 24) & 0xFF)
                            .arg((ip >> 16) & 0xFF)
                            .arg((ip >> 8) & 0xFF)
                            .arg(ip & 0xFF);
            
            // モデル名とユーザー定義名の取得
            QString modelName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chModelName));
  
            if (modelName.startsWith("MV-L")) {
                return i;
            }
        }
    }
    if(deviceCount==1){
        return 0;
    }
    return -1;
}

// 検索したリストのインデックスを指定して接続
bool LightHIKRobotLAN::connectByIndex(int index)
{
    if (index < 0 || index >= static_cast<int>(m_deviceList.nDeviceNum)) {
        emit errorOccurred("無効なデバイスインデックスです。");
        return false;
    }

    disconnectDevice(); // 既に開いていれば閉じる

    // 選択されたデバイス情報を取得
    MV_CC_DEVICE_INFO* pDeviceInfo = m_deviceList.pDeviceInfo[index];
    modelName   = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chModelName));
    userDefName = QString::fromUtf8(reinterpret_cast<char*>(pDeviceInfo->SpecialInfo.stGigEInfo.chUserDefinedName));

    // ハンドルの作成
    int nRet = MV_CC_CreateHandle(&m_handle, pDeviceInfo);
    if (nRet != MV_OK) {
        emit errorOccurred(QString("ハンドルの作成に失敗しました。エラーコード: %1").arg(nRet, 0, 16));
        return false;
    }

    // デバイスを開く
    nRet = MV_CC_OpenDevice(m_handle);
    if (nRet != MV_OK) {
        MV_CC_DestroyHandle(m_handle);
        m_handle = nullptr;
        emit errorOccurred(QString("デバイスのオープンに失敗しました。エラーコード: %1").arg(nRet, 0, 16));
        return false;
    }

    qDebug() << "インデックス" << index << "のデバイスに接続しました。";
    return true;
}

void LightHIKRobotLAN::disconnectDevice()
{
    if (m_handle) {
        MV_CC_CloseDevice(m_handle);
        MV_CC_DestroyHandle(m_handle);
        m_handle = nullptr;
        qDebug() << "デバイスから切断しました。";
    }
}
int LightHIKRobotLAN::getChannelCount()
{
    if (!m_handle) return 0;

    // 1. まずは戻り値(nRet)が MV_OK (0) かどうかをしっかり確認します
    MVCC_ENUMVALUE stEnumValue = {0};
    int nRetEnum = MV_CC_GetEnumValue(m_handle, "LightControllerSelector", &stEnumValue);
    
    if (nRetEnum == MV_OK && stEnumValue.nSupportedNum > 0) {
        qDebug() << "Enum型として取得成功。チャンネル数:" << stEnumValue.nSupportedNum;
        return stEnumValue.nSupportedNum;
    }

    // 2. Enumで取れなかった場合、Integer型として取得を試みる
    MVCC_INTVALUE stIntValue = {0};
    // ※ノード名が "LightSelector" ではなく "ChannelSelector" などの場合もあるので注意
    int nRetInt = MV_CC_GetIntValue(m_handle, "LightControllerSelector", &stIntValue);
    
    if (nRetInt == MV_OK) {
        // nMax に設定可能な最大値（＝チャンネル数）が入る
        qDebug() << "Integer型として取得成功。最大チャンネル:" << stIntValue.nMax;
        return stIntValue.nMax;
    }

    // どちらも失敗した場合はエラーコードを16進数で出力して原因を特定
    qWarning() << "チャンネル数取得失敗。Enum Err:" << QString::number(nRetEnum, 16) 
               << ", Int Err:" << QString::number(nRetInt, 16);
    return 0; 
}

bool LightHIKRobotLAN::setChannelState(int channel, bool isOn)
{
    if (!m_handle) return false;

    // 1. 制御したいチャンネルを選択 (※ノード名は機器により異なる場合があります)
    // 通常、チャンネル1が Index:0, チャンネル2が Index:1 に割り当てられます

    MVCC_ENUMVALUE stEnumValue = {0};
    int nRet = MV_CC_GetEnumValue(m_handle, "LightControllerSelector", &stEnumValue);
    if (nRet != MV_OK) return false;

    nRet = MV_CC_SetEnumValue(m_handle, "LightControllerSelector", stEnumValue.nSupportValue[channel - 1]);
    if (nRet != MV_OK) return false;

    // 2. 選択したチャンネルのON/OFFを設定
    if(isOn==true){
        nRet = MV_CC_SetEnumValueByString(m_handle, "LightControllerSource", "On");
        if (nRet != MV_OK)
            return false;
    }
    else{
        nRet = MV_CC_SetEnumValueByString(m_handle, "LightControllerSource", "Off");
        if (nRet != MV_OK)
            return false;
	}
    return (nRet == MV_OK);
}

bool LightHIKRobotLAN::GetBrightnessRange(int channel, int &MaxBrightness,int &MinBrightness)
{
    if (!m_handle) return false;

    MVCC_ENUMVALUE stEnumValue = {0};
    int nRet = MV_CC_GetEnumValue(m_handle, "LightControllerSelector", &stEnumValue);
    if (nRet != MV_OK) return false;

    nRet = MV_CC_SetEnumValue(m_handle, "LightControllerSelector", stEnumValue.nSupportValue[channel - 1]);
    if (nRet != MV_OK) return false;
   
    MVCC_INTVALUE_EX    Value;
    nRet = MV_CC_GetIntValueEx(m_handle,"LightBrightness",&Value);
    if (nRet != MV_OK) return false;

    MaxBrightness   = Value.nMax;
	MinBrightness   = Value.nMin;
	return true;
}



bool LightHIKRobotLAN::setBrightness(int channel, int brightness)
{
    if (!m_handle) return false;
    
    MVCC_ENUMVALUE stEnumValue = {0};
    int nRet = MV_CC_GetEnumValue(m_handle, "LightControllerSelector", &stEnumValue);
    if (nRet != MV_OK) return false;

    nRet = MV_CC_SetEnumValue(m_handle, "LightControllerSelector", stEnumValue.nSupportValue[channel - 1]);
    if (nRet != MV_OK) return false;

    // 2. 選択したチャンネルの光量を設定 (例: 0〜255)
    nRet = MV_CC_SetIntValue(m_handle, "LightBrightness", brightness);
    return (nRet == MV_OK);
}