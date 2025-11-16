#include "RemoteControlForServerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\RemoteControlForServer\RemoteControlForServer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "RemoteControlForServer.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"

static	const	char	*sRoot=/**/"Other";
static	const	char	*sName=/**/"RemoteControlForServer";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"RemoteControl Server");
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
	return(new RemoteControlForServer(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"PortNo";
	Data[0].Pointer				 =&((RemoteControlForServer *)Instance)->PortNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RemoteControlForServer.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
RemoteControlForServer::RemoteControlForServer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	PortNo	=36755;
}
void	RemoteControlForServer::Prepare(void)
{
	connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
	Server.listen(QHostAddress::Any,PortNo);
	
}
RemoteControlForServer::~RemoteControlForServer(void)
{
	Server.close();
}

void RemoteControlForServer::RemoveSocket(RCSocket *c)
{
	SocketPointer.RemoveList(c);
}

void RemoteControlForServer::SlotNewConnection ()
{
	RCSocket	*p=new RCSocket(this);
	p->ID=GetMaxSocketID()+1;
	p->Sock=Server.nextPendingConnection();
	p->Initial();
	SocketPointer.AppendList(p);
}

int	RemoteControlForServer::GetMaxSocketID(void)
{
	int	MaxID=0;
	for(RCSocket *p=SocketPointer.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->ID>MaxID){
			MaxID=p->ID;
		}
	}
	return MaxID;
}


RCSocket::RCSocket(RemoteControlForServer *parent)
{
	Parent=parent;
}

void	RCSocket::Initial(void)
{
	connect(Sock,SIGNAL(disconnected ()),this,SLOT(SlotDisconnected()));
	connect(Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
}
void	RCSocket::SlotDisconnected()
{
	emit	Disconnect(ID);
}

void	RCSocket::SlotReadyRead()
{
	int	N=Sock->bytesAvailable();
	if(N!=0){
		char	Buff[100000];
		int	Len=Sock->read(Buff, N);
		QString	StrBuff = QString::fromLocal8Bit(Buff);
		//if(strncmp(Buff,LangSolver.GetString(RemoteControlForServer_LS,LID_0)/*"CloseAll"*/,8)==0){
		if(StrBuff.left(8)== LangSolver.GetString(RemoteControlForServer_LS, LID_0)/*"CloseAll"*/.left(0)){
			Parent->GetLayersBase()->CloseAll();
			Parent->GetLayersBase()->SetOnTerminating(true);
			QCoreApplication::quit();
		}
		else
		//if(strncmp(Buff,LangSolver.GetString(RemoteControlForServer_LS,LID_1)/*"CloseOne"*/,8)==0){
		if (StrBuff.left(8) == LangSolver.GetString(RemoteControlForServer_LS, LID_1)/*"CloseOne"*/.left(0)) {
			Parent->GetLayersBase()->CloseOne();
			Parent->GetLayersBase()->SetOnTerminating(true);
			QCoreApplication::quit();
		}
	}
}