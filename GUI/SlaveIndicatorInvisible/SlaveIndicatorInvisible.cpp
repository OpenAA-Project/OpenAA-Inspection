#include "SlaveIndicatorInvisibleResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SlaveIndicatorInvisible\SlaveIndicatorInvisible.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SlaveIndicatorInvisible.h"
#include "XDLLOnly.h"
#include "XForWindows.h"
#include <QMessageBox>
#include "XSlaveIndicator.h"

static	const	char	*sRoot=/**/"Other";
static	const	char	*sName=/**/"SlaveIndicatorInvisible";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Slave Indicator Invisible");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SlaveIndicatorInvisible(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"HostIPAddress";
	Data[0].Pointer				 =&((SlaveIndicatorInvisible *)Instance)->HostIPAddress;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"HostPort";
	Data[1].Pointer				 =&((SlaveIndicatorInvisible *)Instance)->HostPort;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SlaveIndicatorInvisible.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
SlaveIndicatorInvisible::SlaveIndicatorInvisible(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),ThreadRunInst(Base,this)
{
	HostIPAddress=/**/"localhost";
	HostPort=SlaveIndicatorPort;

	connect(&ThreadRunInst,SIGNAL(SignalReboot()),this,SLOT(SlotReboot()),Qt::QueuedConnection);
	connect(&ThreadRunInst,SIGNAL(SignalSendAck()),this,SLOT(SlotSendAck()),Qt::QueuedConnection);
}
void	SlaveIndicatorInvisible::Prepare(void)
{
	if(GetParamComm()->Mastered==false){
		ThreadRunInst.start();
	}
	MtGetComputerName(ComputerName);
}
SlaveIndicatorInvisible::~SlaveIndicatorInvisible(void)
{
	ThreadRunInst.FinMode=true;
	ThreadRunInst.wait(5000);
}

void	SlaveIndicatorInvisible::SlotReboot()
{
	GetLayersBase()->CloseOne();
}

void	SlaveIndicatorInvisible::SlotSendAck()
{
	ThreadRunInst.SendAck();
}

//=================================================================

ThreadSlaveIndicatorRun::ThreadSlaveIndicatorRun(LayersBase *Base ,QObject * parent)
:QThread(parent),ServiceForLayers(Base),Sock(parent)
{	
	FinMode=false;

	connect(&Sock,SIGNAL(readyRead()),this,SLOT(SlotRead()),Qt::QueuedConnection);
}

void ThreadSlaveIndicatorRun::run ()
{
	SlaveIndicatorInvisible	*p=dynamic_cast<SlaveIndicatorInvisible *>(parent());
	if(p!=NULL){
		while(FinMode==false){
			if(Sock.state()!=QAbstractSocket::ConnectedState){
				Sock.connectToHost(p->HostIPAddress,p->HostPort);
				Sock.waitForConnected(1000);
				if(Sock.state()==QAbstractSocket::ConnectedState){
					struct	SlaveInfo	RxData;
					RxData.GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(0);
					RxData.MachineID	=GetLayersBase()->GetMachineID();
					char	Cmd=1;
					Sock.write((char *)&Cmd,sizeof(Cmd));
					Sock.write((char *)&RxData,sizeof(RxData));
					::Save(&Sock,p->ComputerName);
					Sock.flush();
				}
			}
			if(Sock.state()==QAbstractSocket::ConnectedState){
				for(int i=0;i<60*10;i++){
					if(FinMode==true){
						break;
					}
					msleep(100);
				}
			}
			msleep(100);
		}
		if(Sock.state()==QAbstractSocket::ConnectedState){
			Sock.disconnectFromHost();
			Sock.waitForDisconnected(1000);
		}
	}
}
void	ThreadSlaveIndicatorRun::SlotRead()
{
	ReadInSock();
}

void	ThreadSlaveIndicatorRun::SendAck()
{
	if(Sock.isOpen()==false){
		SlaveIndicatorInvisible	*p=dynamic_cast<SlaveIndicatorInvisible *>(parent());
		if(p!=NULL){
			Sock.connectToHost(p->HostIPAddress,p->HostPort);
			Sock.waitForConnected(5000);
		}
		if(Sock.state()==QAbstractSocket::ConnectedState){
			struct	SlaveInfo	RxData;
			RxData.GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(0);
			RxData.MachineID	=GetLayersBase()->GetMachineID();
			char	Cmd=1;
			Sock.write((char *)&Cmd,sizeof(Cmd));
			Sock.write((char *)&RxData,sizeof(RxData));
			Sock.flush();
		}
	}
}

void	ThreadSlaveIndicatorRun::ReadInSock()
{
	if(Sock.bytesAvailable()!=0){
		char	Cmd;
		if(Sock.read((char *)&Cmd,sizeof(Cmd))==sizeof(Cmd)){
			if(Cmd==10){
				emit	SignalReboot();
			}
			if(Cmd==12){
				emit	SignalSendAck();
			}
		}
	}
}