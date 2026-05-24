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




#include "AIP_IO.h"
#include <QStringList>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include "PIOClient.h"
#include "NetworkPIO.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

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

DEFFUNCEX WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

DEFFUNCEX bool	DLL_GetName(QString &str)
{
	str="PIOClient";
	return true;
}
DEFFUNCEX const char	*DLL_GetExplain(void)
{
	return "PIO Client for network PIO";
}
DEFFUNCEX WORD	DLL_GetVersion(void)
{
	return 1;
}
DEFFUNCEX bool	DLL_CheckCopyright(QString &CopyrightString)
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
	if(strcmp(PIO_NAME,"IOLIB_PIO16")==0)
		return(16);
	else if(strcmp(PIO_NAME,"IOLIB_PIO32")==0)
		return(32);
	else if(strcmp(PIO_NAME,"IOLIB_PIO64")==0)
		return(64);
	return 0;
}

int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
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

PIODLLBaseClass  _cdecl *AIP_IO_Open(LayersBase *Base,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	PIOClient	*PIO=new PIOClient(Base->GetMainWidget());
	PIO->Initial(Something);
	return(PIO);
}

BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	if(PIO->Inport(bitIndex/8) & (0x01<<(bitIndex%8))!=0)
		return 1;
	return 0;
}

BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	return PIO->Inport(byteIndex);
}

BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	PIO->Outport(byteIndex,data);
	return(data);
}

int  _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	return PIO->GetOutData(byteIndex);
}

bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	PIOClient	*PIO=(PIOClient	*)handle;
	delete	PIO;

	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{
	return(true);
}