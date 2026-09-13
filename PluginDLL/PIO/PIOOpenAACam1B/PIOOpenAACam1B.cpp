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

#include "PIOOpenAACam1B.h"
#include "AIP_IO.h"
#include "math.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XEntryPoint.h"
#include "XLightClass.h"
#include "XGeneralFunc.h"
#include "XLightOpenAACam1B.h"


//static short Id;

PIOOpenAACam1B::PIOOpenAACam1B(LayersBase *base)
	:ServiceForLayers(base)
{
	LightPointer= nullptr;
	DeviceNo	=0;
}

bool	PIOOpenAACam1B::FindLight(void)
{
	LightDLLBaseClass	*s=GetLayersBase()->GetLightBase()->GetLight(0 ,/**/"LightOpenAACam1B");
	LightPointer=(XLightOpenAACam1B *)s;
	return (LightPointer!=nullptr);
}

bool	PIOOpenAACam1B::GetBitBySocket(void)
{
	if(LightPointer==NULL)
		FindLight();
	if(LightPointer!=NULL){
		CmdReqLightOpenAACam1BPacket	Cmd(GetLayersBase());
		LightPointer->TransmitDirectly(&Cmd);
		DataPacket=Cmd.DataPacket;
		return true;
	}
	return false;
}
BYTE	PIOOpenAACam1B::SetByteBySocket(BYTE data)
{
	if(LightPointer==NULL)
		FindLight();
	if(LightPointer!=NULL){
		CmdSetLightOpenAACam1BPacket	Cmd(GetLayersBase());
		Cmd.DataPacket.Data1.Out0 = (data&0x01)?true:false;
		Cmd.DataPacket.Data1.Out1 = (data&0x02)?true:false;
		Cmd.DataPacket.Data1.Out2 = (data&0x04)?true:false;
		Cmd.DataPacket.Data1.Out3 = (data&0x08)?true:false;
		LightPointer->TransmitDirectly(&Cmd);
		return true;
	}
	return false;
}

DEFFUNCEX WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

DEFFUNCEX bool	DLL_GetName(QString &str)
{
	str="PIOOpenAACam1B";
	return true;
}
DEFFUNCEX const char	*DLL_GetExplain(void)
{
	return "PIO for OpenAACam1B";
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
	return 4;
}

DEFFUNCEX	int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	return 4;
}

DEFFUNCEX	bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

DEFFUNCEX	PIODLLBaseClass  _cdecl *AIP_IO_Open(LayersBase *Base,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	PIOOpenAACam1B *GIO = new PIOOpenAACam1B(Base);
	GIO->DeviceNo =boardNumber;

	return(GIO);
}

DEFFUNCEX	BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	PIOOpenAACam1B *Handle = dynamic_cast<PIOOpenAACam1B *>(handle);
	if(Handle!=NULL){
		if(Handle->GetBitBySocket()==true){
			switch(bitIndex){
				case 0:	return (Handle->DataPacket.Data2.Inp0==true)?1:0;
				case 1:	return (Handle->DataPacket.Data2.Inp1==true)?1:0;
				case 2:	return (Handle->DataPacket.Data2.Inp2==true)?1:0;
				case 3:	return (Handle->DataPacket.Data2.Inp3==true)?1:0;
			}
		}
	}
	return 0;
}

DEFFUNCEX	BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	PIOOpenAACam1B *Handle = dynamic_cast<PIOOpenAACam1B *>(handle);
	if(Handle!=NULL){
		if(Handle->GetBitBySocket()==true){
			BYTE	d=0;
			d|=(Handle->DataPacket.Data2.Inp0==true)?0x01:0x00;
			d|=(Handle->DataPacket.Data2.Inp1==true)?0x02:0x00;
			d|=(Handle->DataPacket.Data2.Inp2==true)?0x04:0x00;
			d|=(Handle->DataPacket.Data2.Inp3==true)?0x08:0x00;
			return d;
		}
	}
	return 0;
}

DEFFUNCEX	BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	PIOOpenAACam1B *Handle = dynamic_cast<PIOOpenAACam1B *>(handle);
	if(Handle!=NULL){
		if(Handle->SetByteBySocket(data)==true){
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