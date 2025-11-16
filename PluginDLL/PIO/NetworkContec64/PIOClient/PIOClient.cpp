/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\PIO\NetworkContec64\PIOClient.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/



#include "AIP_IO.h"
#include <QStringList>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include "PIOClient.h"
#include "NetworkPIO.h"

PIOClient::PIOClient(QObject *parent)
:QTcpSocket(parent)
{
	connect(this,SIGNAL(readyRead()),this,SLOT(ReadyRead()));
	for(int i=0;i<sizeof(InData)/sizeof(InData[0]);i++){
		InData[i]=0;
	}
	for(int i=0;i<sizeof(OutData)/sizeof(OutData[0]);i++){
		OutData[i]=0;
	}
}

PIOClient::~PIOClient()
{
}

void	PIOClient::Initial(const QString &Address)
{
	connectToHost (Address, NetworkPIOPort, QIODevice::ReadWrite );
	waitForConnected(2000);
}

void PIOClient::ReadyRead()
{
	int	N=bytesAvailable();
	if(N!=0){
		read((char *)InData,N);
	}
}


void	PIOClient::Outport(int port ,BYTE data)
{
	OutData[port]=data;
	if(write((const char *)OutData,8)==8){
		flush();
	}
}

BYTE	PIOClient::GetOutData(int port)
{
	return OutData[port];
}

BYTE	PIOClient::Inport(int port)
{
	return InData[port];
}


//===============================================================================

//PIOClient	*PIO;

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="PIOClient";
	return true;
}
IO_DLLFUNC const char	*DLL_GetExplain(void)
{
	return "PIO Client for network PIO";
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

int _cdecl  AIP_IO_GetIOInBitCount(void *handle ,int boardNumber)
{
	if(strcmp(PIO_NAME,"IOLIB_PIO16")==0)
		return(16);
	else if(strcmp(PIO_NAME,"IOLIB_PIO32")==0)
		return(32);
	else if(strcmp(PIO_NAME,"IOLIB_PIO64")==0)
		return(64);
	return 0;
}

int _cdecl  AIP_IO_GetIOOutBitCount(void *handle ,int boardNumber)
{
	if(strcmp(PIO_NAME,"IOLIB_PIO16")==0)
		return(16);
	else if(strcmp(PIO_NAME,"IOLIB_PIO32")==0)
		return(32);
	else if(strcmp(PIO_NAME,"IOLIB_PIO64")==0)
		return(64);
	return 0;
}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

void  _cdecl *AIP_IO_Open(QWidget *mainW,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	PIOClient	*PIO=new PIOClient(mainW);
	PIO->Initial(Something);
	return(PIO);
}

BYTE  _cdecl AIP_IO_GetBit(void *handle ,int boardNumber , BYTE bitIndex)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	if(PIO->Inport(bitIndex/8) & (0x01<<(bitIndex%8))!=0)
		return 1;
	return 0;
}

BYTE  _cdecl AIP_IO_GetByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	return PIO->Inport(byteIndex);
}

BYTE  _cdecl AIP_IO_SetByte(void *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	PIO->Outport(byteIndex,data);
	return(data);
}

int  _cdecl AIP_IO_GetOutByte(void *handle ,int boardNumber , BYTE byteIndex)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	return PIO->GetOutData(byteIndex);
}

bool  _cdecl AIP_IO_Close(void *handle ,int boardNumber)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	delete	PIO;

	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{
	return(true);
}
