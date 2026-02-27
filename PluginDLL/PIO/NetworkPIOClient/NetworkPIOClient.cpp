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
#include "NetworkPIOClient.h"
#include "XPointer.h"
#include "NetworkPIOLib.h"
#include "XCriticalFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

NetworkPIOClient::NetworkPIOClient(QObject *parent)
:QTcpSocket(parent)
{
	QWidget	*p=dynamic_cast<QWidget *>(parent);
	connect(this,SIGNAL(readyRead()),this,SLOT(ReadyRead()));
	connect(this,SIGNAL(readyRead()),this,SLOT(ReadyRead()));

	for(int i=0;i<sizeof(InData)/sizeof(InData[0]);i++){
		InData[i]=0;
	}
	for(int i=0;i<sizeof(OutData)/sizeof(OutData[0]);i++){
		OutData[i]=0;
	}
	WaitToReceive	=false;
	InNumb=0;
	OutNumb=0;
}

NetworkPIOClient::~NetworkPIOClient()
{
}

void	NetworkPIOClient::Initial(int _ID ,const QString &Address,int port ,int _InNumb ,int _OutNumb)
{
	ID		=_ID;
	IPAddress=Address;
	Port	=port;
	InNumb	=_InNumb;
	OutNumb	=_OutNumb;

	OpenSocket();
}
void	NetworkPIOClient::Initial(const QString &Something)
{
	QStringList	List=Something.split(',');
	if(List.count()>=1)
		ID		=List[0].toInt();
	if(List.count()>=2)
		IPAddress=List[1];
	if(List.count()>=3)
		Port	=List[2].toInt();
	if(List.count()>=4)
		InNumb=List[3].toInt();
	if(List.count()>=5)
		OutNumb=List[4].toInt();

	OpenSocket();
}

bool	NetworkPIOClient::OpenSocket(void)
{
	if(state()!=QAbstractSocket::ConnectedState){
		AccessMutex.lock();
		connectToHost (IPAddress, Port, QIODevice::ReadWrite );
		waitForConnected(2000);
		AccessMutex.unlock();
		if(state()==QAbstractSocket::ConnectedState){
			ReqData(false);
			return true;
		}
	}
	else{
		return true;
	}
	return false;
}

void NetworkPIOClient::ReadyRead()
{
	AccessMutex.lock();
	int	N=bytesAvailable();
	while(N!=0){
		struct	CommandNetworkPIO	RCmd;
		int	RByte=read((char *)&RCmd,sizeof(RCmd));
		if(RByte==sizeof(RCmd)){
			if(RCmd.Cmd==1){
				for(int i=0;i<4;i++){
					InData	[i]=RCmd.InData[i];
				}
			}
			else if(RCmd.Cmd==2){
				for(int i=0;i<4;i++){
					InData	[i]=RCmd.InData[i];
					OutData	[i]=RCmd.OutData[i];
				}
			}
			WaitToReceive=false;
		}
		N-=RByte;
	}
	AccessMutex.unlock();
}

void	NetworkPIOClient::OutByte(int port ,BYTE data)
{
	if(0<=port && port<(OutNumb+7)/8){
		OutData[port]=data;
	}
	//ReqData(true);
}

BYTE	NetworkPIOClient::InByte(int port)
{
	//ReqData(true);
	if(0<=port && port<(InNumb+7)/8){
		return InData[port];
	}
	return 0;
}

void	NetworkPIOClient::OutBit(int BitIndex ,BYTE data)
{
	if(0<=BitIndex && BitIndex<OutNumb){
		if(data==0)
			SetBitOnDim0(OutData,BitIndex);
		else
			SetBitOnDim1(OutData,BitIndex);
	}

	//ReqData(true);
}

BYTE	NetworkPIOClient::InBit(int BitIndex)
{
	//ReqData(true);
	if(0<=BitIndex && BitIndex<InNumb){
		if(GetBitOnDim(InData,BitIndex)==0)
			return 0;
	}
	return 1;
}

BYTE	NetworkPIOClient::GetOutByte(int port)
{
	//ReqData(true);
	if(0<=port && port<(OutNumb+7)/8){
		return OutData[port];
	}
	return 0;
}

void	NetworkPIOClient::ReqData(bool SendOutData)
{
	if(WaitToReceive==true){
		return;
	}
	struct	CommandNetworkPIO	RCmd;
	RCmd.ID=ID;
	RCmd.InNumb	=InNumb;
	RCmd.OutNumb=OutNumb;

	if(SendOutData==true){
		RCmd.Cmd	=1;
		for(int i=0;i<4;i++){
			RCmd.OutData[i]=OutData[i];
		}
	}
	else{
		RCmd.Cmd	=2;
	}
	if(OpenSocket()==true){
		WaitToReceive=true;
		AccessMutex.lock();
		if(write((const char *)&RCmd,sizeof(RCmd))==sizeof(RCmd)){
			flush();
		}
		AccessMutex.unlock();
	}
}

//===============================================================================

//PIOClient	*PIO;
DWORD	StartOutTime;

IO_DLLFUNC WORD	DLL_GetDLLType(void)
{
	return(DLLPIOMode);
}

IO_DLLFUNC bool	DLL_GetName(QString &str)
{
	str="NetworkPIOClient";
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

int _cdecl  AIP_IO_GetIOInBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	NetworkPIOClient	*PIO=(NetworkPIOClient	*)handle;
	if(handle!=NULL && PIO!=NULL){
		return PIO->InNumb;
	}
	return 0;
}

int _cdecl  AIP_IO_GetIOOutBitCount(PIODLLBaseClass *handle ,int boardNumber)
{
	NetworkPIOClient	*PIO=(NetworkPIOClient	*)handle;
	if(handle!=NULL && PIO!=NULL){
		return PIO->OutNumb;
	}
	return 0;

}

bool  _cdecl AIP_IO_Initial(const QStringList &NameList)
{
	return(true);
}

PIODLLBaseClass  _cdecl *AIP_IO_Open(LayersBase *Base,int boardNumber , char *name ,int maxbuffsize,const QString &Something)
{
	NetworkPIOClient	*PIO=new NetworkPIOClient(Base->GetMainWidget());
	PIO->Initial(Something);
	return(PIO);
}

BYTE  _cdecl AIP_IO_GetBit(PIODLLBaseClass *handle ,int boardNumber , BYTE bitIndex)
{
	NetworkPIOClient	*PIO=(NetworkPIOClient	*)handle;
	return PIO->InBit(bitIndex);
}

BYTE  _cdecl AIP_IO_GetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	NetworkPIOClient	*PIO=(NetworkPIOClient	*)handle;
	return PIO->InByte(byteIndex);
}

BYTE  _cdecl AIP_IO_SetByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex , BYTE data)
{
	NetworkPIOClient	*PIO=(NetworkPIOClient	*)handle;
	PIO->OutByte(byteIndex,data);
	StartOutTime=::GetComputerMiliSec();
	return(data);
}

int  _cdecl AIP_IO_GetOutByte(PIODLLBaseClass *handle ,int boardNumber , BYTE byteIndex)
{
	NetworkPIOClient	*PIO=(NetworkPIOClient	*)handle;
	return PIO->GetOutByte(byteIndex);
}

bool  _cdecl AIP_IO_Close(PIODLLBaseClass *handle ,int boardNumber)
{
	NetworkPIOClient	*PIO=(NetworkPIOClient	*)handle;
	delete	PIO;

	return(true);
}

bool  _cdecl AIP_IO_Release(void)
{
	return(true);
}

DWORD	DiffTimeDim[10000];
int		DiffCounter=0;

void  _cdecl AIP_IO_LoopOnIdle(PIODLLBaseClass *handle ,int boardNumber)
{
	DWORD	CurrentTime=::GetComputerMiliSec();
	DiffTimeDim[DiffCounter]=CurrentTime-StartOutTime;
	DiffCounter++;
	if(DiffCounter>=10000)
		DiffCounter=0;

	NetworkPIOClient	*PIO=(NetworkPIOClient	*)handle;
	PIO->ReqData(true);
}