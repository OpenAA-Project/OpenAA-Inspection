/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\Contec64DLL\Contec64DLL\contec64dll.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


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

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
{
	return 2;
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	return 0;
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
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

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
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

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
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

BYTE  _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	PioAccessor	*PIO=(PioAccessor *)handle;
	return(0);
}

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	PioAccessor	*PIO=(PioAccessor *)handle;
	return(0);
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	PioAccessor	*PIO=(PioAccessor *)handle;
	delete	PIO;
	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}
