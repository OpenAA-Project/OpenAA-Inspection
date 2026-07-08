/*
 * Copyright (C) 2023
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

#include "GIOHIKRobotCamera.h"
#include "AIP_IO.h"
#include "math.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XEntryPoint.h"
#include "CameraMVSGigECommon.h"
#include "XCameraClass.h"
#include "XGeneralFunc.h"

//static short Id;

GIOHIKRobotCamera::GIOHIKRobotCamera(LayersBase *base)
	:ServiceForLayers(base)
{
	HIKRobotCamera = nullptr;
	Socket		=NULL;
	DeviceNo	=0;
}
void	GIOHIKRobotCamera::AfterStartSequence(void)
{
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=nullptr){
		if(0<=DeviceNo && DeviceNo<E->GetAllocatedCameraCount()){
			CameraClass *Cam=E->GetCamera(DeviceNo);
			if(Cam!=nullptr){
				HIKRobotCamera=Cam;
				return;
			}
		}
	}
	Socket = new QLocalSocket(this);
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	Socket->connectToServer(QString("CameraMVSGigE%1").arg(DeviceNo),QIODevice::ReadWrite);
}

void    GIOHIKRobotCamera::SlotReadyRead()
{
    if(Socket!=NULL){
        QByteArray Data=Socket->readAll();
        if(Data.size()>0){
            QString StrData=QString::fromUtf8(Data);
			if(StrData=="T"){
				InLine0=true3;
			}
			else if(StrData=="F"){
				InLine0 = false3;
			}
		}
	}
}

bool	GIOHIKRobotCamera::GetBitBySocket(void)
{
	//InLine0=none3;
    if(Socket!=NULL){
		Socket->write("R");
		Socket->flush();
		//if(Socket->waitForReadyRead(1000)){
			if(InLine0==true3){
				GSleep(20);
				return true;
			}
			else
			if(InLine0==false3){
				GSleep(20);
				return false;
			}
		//}
	}
	return false;
}


BYTE	GIOHIKRobotCamera::GetByteBySocket(void)
{
	//InLine0=none3;
    if(Socket!=NULL){
		Socket->write("R");
		Socket->flush();
		//if(Socket->waitForReadyRead(1000)){
			if(InLine0==true3){
				GSleep(20);
				return 1;
			}
			else
			if(InLine0==false3){
				GSleep(20);
				return 0;
			}
		//}
	}
	return 0;
}
BYTE	GIOHIKRobotCamera::SetByteBySocket(BYTE data)
{
	InLine0=none3;
    if(Socket!=NULL){
		if(data!=0){
			Socket->write("ST");
			Socket->flush();
		}
		else{
			Socket->write("SF");
			Socket->flush();
		}
		GSleep(20);
	}
	return data;
}

DEFFUNCEX WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

DEFFUNCEX bool	DLL_GetName(QString &str)
{
	str="GIOHIKRobotCamera";
	return true;
}
DEFFUNCEX const char	*DLL_GetExplain(void)
{
	return "GIO by HIKRobot camera";
}
DEFFUNCEX WORD	DLL_GetVersion(void)
{
	return 1;
}
DEFFUNCEX bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2026";
	return true;
}


DEFFUNCEX	int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

DEFFUNCEX	int _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	return 1;
}

DEFFUNCEX	int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	return 1;
}

DEFFUNCEX	bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

DEFFUNCEX	PIODLLBaseClass  _cdecl *AIP_IO_Open(LayersBase *Base,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	GIOHIKRobotCamera *GIO = new GIOHIKRobotCamera(Base);
	GIO->DeviceNo =boardNumber;

	return(GIO);
}

DEFFUNCEX	BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	GIOHIKRobotCamera *Handle = dynamic_cast<GIOHIKRobotCamera *>(handle);
	if(Handle!=NULL){
		if(Handle->HIKRobotCamera!=NULL){
			CmdInputHIKRobotCamera	RCmd(Handle->GetLayersBase());
			Handle->LockCommand.lock();
			Handle->HIKRobotCamera->TransmitDirectly(&RCmd);
			Handle->LockCommand.unlock();
			return (RCmd.Line0==true)?1:0;
		}
		else{
			Handle->LockCommand.lock();
			bool	b=Handle->GetBitBySocket();
			Handle->LockCommand.unlock();
			return (b==true)?1:0;
		}
	}
	return 0;
}

DEFFUNCEX	BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	GIOHIKRobotCamera *Handle = dynamic_cast<GIOHIKRobotCamera *>(handle);
	if(Handle!=NULL){
		if(Handle->HIKRobotCamera!=NULL){
			CmdInputHIKRobotCamera	RCmd(Handle->GetLayersBase());
			Handle->LockCommand.lock();
			Handle->HIKRobotCamera->TransmitDirectly(&RCmd);
			Handle->LockCommand.unlock();
			return (RCmd.Line0==true)?1:0;
		}
		else{
			Handle->LockCommand.lock();
			BYTE	d=Handle->GetByteBySocket();
			Handle->LockCommand.unlock();
			return d;
		}
	}
	return 0;
}

DEFFUNCEX	BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	GIOHIKRobotCamera *Handle = dynamic_cast<GIOHIKRobotCamera *>(handle);
	if(Handle!=NULL){
		if(Handle->HIKRobotCamera!=NULL){
			CmdOutputHIKRobotCamera	RCmd(Handle->GetLayersBase());
			RCmd.Line1 = (data!=0)?true:false;
			Handle->LockCommand.lock();
			Handle->HIKRobotCamera->TransmitDirectly(&RCmd);
			Handle->LockCommand.unlock();
			return data;
		}
		else{
			Handle->LockCommand.lock();
			Handle->SetByteBySocket(data);
			Handle->LockCommand.unlock();
			return data;
		}
	}
	return 0;
}

DEFFUNCEX	bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	return true;
}

DEFFUNCEX	bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}