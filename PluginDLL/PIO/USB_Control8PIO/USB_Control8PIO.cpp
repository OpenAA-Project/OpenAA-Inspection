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



#include "windows.h"
#include "AIP_IO.h"
#include "math.h"
#include "XGUIFormBase.h"
#include "XLight_USBControl8.h"
#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"
#include "XLightClass.h"

//static short Id;


const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}
IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="USB_Control8";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "USB_Control8 PIO";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2011";
	return true;
}


int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	return 2;
}

int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	return 0;
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

PIODLLBaseClass  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	LayersBase	*Layers=NULL;
	GUIFormBase	*b=dynamic_cast<GUIFormBase	*>(mainW);
	if(b!=NULL){
		Layers=b->GetLayersBase();
	}
	return Layers;
}

BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	LayersBase	*Layers=(LayersBase	*)handle;
	if(Layers->GetLightBase()!=NULL){
		LightDLLBaseClass	*p=Layers->GetLightBase()->GetLight(0);
		if(p!=NULL){
			CmdReqInput	Cmd(Layers);
			p->TransmitDirectly(&Cmd);
			if(bitIndex==0){
				if((Cmd.Data&0x40)==0)
					return 0;
				else
					return 1;
			}
			if(bitIndex==1){
				if((Cmd.Data&0x80)==0)
					return 0;
				else
					return 1;
			}
		}
	}
	return(0);
}

BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	LayersBase	*Layers=(LayersBase	*)handle;
	if(Layers->GetLightBase()!=NULL){
		LightDLLBaseClass	*p=Layers->GetLightBase()->GetLight(0);
		if(p!=NULL){
			CmdReqInput	Cmd(Layers);
			p->TransmitDirectly(&Cmd);
			return Cmd.Data>>6;
		}
	}
	return(0);
}

BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	return(0);
}

int  _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	return(0);
}

bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}