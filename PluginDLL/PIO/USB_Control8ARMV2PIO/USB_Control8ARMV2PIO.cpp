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



//#include "windows.h"
#include "AIP_IO.h"
#include "math.h"
#include "XGUIFormBase.h"
#include "XLightUSB_ARM8V2.h"
#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"
#include "XLightClass.h"
#include "USB_Control8ARMV2PIO.h"
#include "swap.h"

//static short Id;

//LayersBase	*Layers;
//int			LightNumber=0;

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
	str="USB_Control8ARMV2";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "USB_Control8ARMV2 PIO";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2014";
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

PIODLLBaseClass  _cdecl *AIP_IO_Open(LayersBase *Base,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	PioAccessor	*PIO=new PioAccessor();
	GUIFormBase	*b=dynamic_cast<GUIFormBase	*>(mainW);
	if(b!=NULL){
		PIO->Layers=b->GetLayersBase();
	}
	if(Something.isEmpty()==false){
		PIO->LightNumber=Something.toInt();
	}
	return PIO;
}

BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	PioAccessor	*PIO=(PioAccessor *)handle;
	if(PIO->Layers->GetLightBase()!=NULL){
		int	LCount=PIO->Layers->GetLightBase()->GetCount();
		int	iLightNumber=min(PIO->LightNumber,LCount);
		LightDLLBaseClass	*p=PIO->Layers->GetLightBase()->GetLight(iLightNumber);
		if(p!=NULL){
			CmdReqInput	Cmd(PIO->Layers);
			p->TransmitDirectly(&Cmd);
			if(bitIndex==0){
				if((Cmd.Data&0x01)==0)
					return 0;
				else
					return 1;
			}
			if(bitIndex==1){
				if((Cmd.Data&0x02)==0)
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
	PioAccessor	*PIO=(PioAccessor *)handle;
	if(PIO->Layers->GetLightBase()!=NULL){
		int	LCount=PIO->Layers->GetLightBase()->GetCount();
		int	iLightNumber=min(PIO->LightNumber,LCount);
		LightDLLBaseClass	*p=PIO->Layers->GetLightBase()->GetLight(iLightNumber);
		if(p!=NULL){
			CmdReqInput	Cmd(PIO->Layers);
			p->TransmitDirectly(&Cmd);
			return Cmd.Data;
		}
	}
	return(0);
}

BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	PioAccessor	*PIO=(PioAccessor *)handle;
	return(0);
}

int  _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	PioAccessor	*PIO=(PioAccessor *)handle;
	return(0);
}

bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	PioAccessor	*PIO=(PioAccessor *)handle;
	delete	PIO;
	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}