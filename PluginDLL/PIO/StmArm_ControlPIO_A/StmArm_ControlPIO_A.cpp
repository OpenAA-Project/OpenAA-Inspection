/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\Contec64DLL\Contec64DLL\contec64dll.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "windows.h"
#include "AIP_IO.h"
#include "math.h"
#include "XGUIFormBase.h"
#include "XCCSControl.h"
#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"
#include "XLightClass.h"


//LayersBase	*Layers;

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
	str="StmArm_ControlPIO";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "StmArm_ControlPIO";
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
	LayersBase	*Layers=(LayersBase	*)handle;
	return 5;
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	LayersBase	*Layers=(LayersBase	*)handle;
	return 0;
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	LayersBase	*Layers=NULL;
	GUIFormBase	*b=dynamic_cast<GUIFormBase	*>(mainW);
	if(b!=NULL){
		Layers=b->GetLayersBase();
	}
	return Layers;
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	LayersBase	*Layers=(LayersBase	*)handle;
	if(Layers->GetLightBase()!=NULL){
		LightDLLBaseClass	*p=Layers->GetLightBase()->GetLight(0);
		if(p!=NULL){
			CmdReqInput	Cmd(Layers);
			p->TransmitDirectly(&Cmd);
			if((Cmd.Data&(0x01<<bitIndex))==0)
				return 0;
			else
				return 1;
		}
	}
	return(0);
}

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	LayersBase	*Layers=(LayersBase	*)handle;
	if(Layers->GetLightBase()!=NULL){
		LightDLLBaseClass	*p=Layers->GetLightBase()->GetLight(0);
		if(p!=NULL){
			CmdReqInput	Cmd(Layers);
			p->TransmitDirectly(&Cmd);
			return Cmd.Data;
		}
	}
	return(0);
}

BYTE  _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	LayersBase	*Layers=(LayersBase	*)handle;
	return(0);
}

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	LayersBase	*Layers=(LayersBase	*)handle;
	return(0);
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	LayersBase	*Layers=(LayersBase	*)handle;
	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{	
	return(true);
}
