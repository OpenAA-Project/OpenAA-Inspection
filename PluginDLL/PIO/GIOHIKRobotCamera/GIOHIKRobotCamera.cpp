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

//static short Id;

GIOHIKRobotCamera::GIOHIKRobotCamera(LayersBase *base)
	:ServiceForLayers(base)
{
	HIKRobotCamera = nullptr;
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
			}
		}
	}
}


IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="GIOHIKRobotCamera";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "GIO by HIKRobot camera";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2026";
	return true;
}


int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	return 1;
}

int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	return 1;
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

PIODLLBaseClass  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	long Ret;
	GUIFormBase *MainForm = dynamic_cast<GUIFormBase *>(mainW);
	if(MainForm==NULL){
		return NULL;
	}
	GIOHIKRobotCamera *GIO = new GIOHIKRobotCamera(MainForm->GetLayersBase());

	GIO->DeviceNo =boardNumber;

	return(GIO);
}

BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	GIOHIKRobotCamera *Handle = dynamic_cast<GIOHIKRobotCamera *>(handle);
	if(Handle!=NULL){
		CmdInputHIKRobotCamera	RCmd(Handle->GetLayersBase());
		Handle->HIKRobotCamera->TransmitDirectly(&RCmd);
		return RCmd.Line0;
	}
	return false;
}

BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	GIOHIKRobotCamera *Handle = dynamic_cast<GIOHIKRobotCamera *>(handle);
	if(Handle!=NULL){
		CmdInputHIKRobotCamera	RCmd(Handle->GetLayersBase());
		Handle->HIKRobotCamera->TransmitDirectly(&RCmd);
		return (RCmd.Line0==true)?1:0;
	}
	return 0;
}

BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	GIOHIKRobotCamera *Handle = dynamic_cast<GIOHIKRobotCamera *>(handle);
	if(Handle!=NULL){
		CmdOutputHIKRobotCamera	RCmd(Handle->GetLayersBase());
		RCmd.Line1 = (data!=0)?true:false;
		Handle->HIKRobotCamera->TransmitDirectly(&RCmd);
		return data;
	}
	return data;
}

bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	return true;
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}