/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\NetworkPIOVirtual\NetworkPIOVirtual.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/



#include "AIP_IO.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "NetworkPIOVirtual.h"
#include "XPointer.h"
#include "NetworkPIOLib.h"


NetworkPIOVirtual::NetworkPIOVirtual(void)
	:MemMap(/**/"NetworkPIOVirtual")
{
	InNumb=0;
	OutNumb=0;
	Pointer=NULL;
}

NetworkPIOVirtual::~NetworkPIOVirtual()
{
}

void	NetworkPIOVirtual::Initial(int _InNumb ,int _OutNumb)
{
	InNumb	=_InNumb;
	OutNumb	=_OutNumb;

	if(MemMap.isAttached ()==false){
		MemMap.attach();
		Pointer=(struct	NetworkPIOVirtualPacket	* )MemMap.data();
	}
}
void	NetworkPIOVirtual::Initial(const QString &Something)
{
	QStringList	List=Something.split(',');
	if(List.count()>=1)
		InNumb=List[0].toInt();
	if(List.count()>=2)
		OutNumb=List[1].toInt();
	if(MemMap.isAttached ()==false){
		MemMap.attach();
		Pointer=(struct	NetworkPIOVirtualPacket	* )MemMap.data();
	}
}

void	NetworkPIOVirtual::OutByte(int port ,BYTE data)
{
	if(0<=port && port<(OutNumb+7)/8){
		MemMap.lock();
		Pointer->OutData[port]=data;
		Pointer->Cmd=1;		
		MemMap.unlock();
	}
}

BYTE	NetworkPIOVirtual::InByte(int port)
{
	if(0<=port && port<(OutNumb+7)/8){
		BYTE	d;
		MemMap.lock();
		d=Pointer->InData[port];
		Pointer->Cmd=2;
		MemMap.unlock();
		return d;
	}
	return 0;
}

void	NetworkPIOVirtual::OutBit(int BitIndex ,BYTE data)
{
	if(0<=BitIndex && BitIndex<OutNumb){
		MemMap.lock();
		if(data==0)
			Pointer->OutData[BitIndex>>3] &=~(1<<(BitIndex&7));
		else
			Pointer->OutData[BitIndex>>3] |= (1<<(BitIndex&7));
		Pointer->Cmd=1;		
		MemMap.unlock();
	}
}

BYTE	NetworkPIOVirtual::InBit(int BitIndex)
{
	//ReqData(true);
	if(0<=BitIndex && BitIndex<InNumb){
		BYTE	d;
		MemMap.lock();
		d=Pointer->InData[BitIndex>>3];
		Pointer->Cmd=2;
		MemMap.unlock();
		return (d&(1<<BitIndex&7))==0?0:1;
	}
	return 1;
}

BYTE	NetworkPIOVirtual::GetOutByte(int port)
{
	//ReqData(true);
	if(0<=port && port<(OutNumb+7)/8){
		BYTE	d;
		MemMap.lock();
		d=Pointer->OutData[port];
		Pointer->Cmd=1;		
		MemMap.unlock();
		return d;
	}
	return 0;
}


//===============================================================================

//PIOClient	*PIO;

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="NetworkPIOVirtual";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "PIO for network PIO";
}
IO_DLLFUNC WORD	DLL_GetVersion(void)
{
	return 1;
}
IO_DLLFUNC bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="MEGATRADE (C) 2020";
	return true;
}


int _cdecl  AIP_IO_GetIOBoardNumb(void)
{
	return(1);
}

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
{
	NetworkPIOVirtual	*PIO=(NetworkPIOVirtual	*)handle;
	if(handle!=NULL && PIO!=NULL){
		return PIO->InNumb;
	}
	return 0;
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	NetworkPIOVirtual	*PIO=(NetworkPIOVirtual	*)handle;
	if(handle!=NULL && PIO!=NULL){
		return PIO->OutNumb;
	}
	return 0;

}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	NetworkPIOVirtual	*PIO=new NetworkPIOVirtual();
	PIO->Initial(Something);
	return(PIO);
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	NetworkPIOVirtual	*PIO=(NetworkPIOVirtual	*)handle;
	return PIO->InBit(bitIndex);
}

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	NetworkPIOVirtual	*PIO=(NetworkPIOVirtual	*)handle;
	return PIO->InByte(byteIndex);
}

BYTE  _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	NetworkPIOVirtual	*PIO=(NetworkPIOVirtual	*)handle;
	PIO->OutByte(byteIndex,data);
	return(data);
}

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	NetworkPIOVirtual	*PIO=(NetworkPIOVirtual	*)handle;
	return PIO->GetOutByte(byteIndex);
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	NetworkPIOVirtual	*PIO=(NetworkPIOVirtual	*)handle;
	delete	PIO;

	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{
	return(true);
}
