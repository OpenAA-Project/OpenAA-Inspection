/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDirectComm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XDirectComm.h"
#include "XGeneralFunc.h"
#include "XDataInExe.h"
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include "XErrorCode.h"
#include <string.h>
#include <QBuffer>
#include <QElapsedTimer>
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"

DirectComm::DirectComm(LayersBase *base,QObject * parent) 
: CommBase(parent),ServiceForLayers(base)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		Leaf[i]				=NULL;
		LeafFromServer[i]	=NULL;
	}
	int	CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(0);
	StartServer(DirectCommPort+CurrentGlobalPage);
	Joined=NULL;
}

DirectComm::~DirectComm(void)
{
	ClearAllReqConnection();
	if(Joined!=NULL){
		delete	[]Joined;
	}
	Joined=NULL;
}

bool	DirectComm::InitialCreate(QObject *parent,SystemConnectionInfoContainer &Info)
{
	SystemConnectionInfoList=Info;

	if(Joined!=NULL){
		delete	[]Joined;
	}
	Joined=new bool3[GetLayersBase()->GetGlobalPageNumb()];
	ClearJoined();

	bool	Ret=true;
	if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
		int	ID=0;
		for(SystemConnectionInfo *p=SystemConnectionInfoList.GetFirst();p!=NULL;p=p->GetNext()){
			AddReqConnection(parent ,ID,p->GetIPAddress(),DirectCommPort+p->GetGlobalPage());
			ID++;
		}
		Ret=StartAllReqConnection(SystemConnectionInfoList.WaitingTimeToConnect);
	}
	return Ret;
}


void	DirectComm::SlotReceived(int ID ,int Cmd)
{
	RecList	*R=UnpackTopRxBuff(ID);
	if(R!=NULL){
		const char	*EmitterRoot;
		char	EmitterRootBuff[100];
		const char	*EmitterName;
		char	EmitterNameBuff[100];
		const char	*CmdClass;
		char	CmdClassBuff[100];
		BYTE	*fp	=R->GetClassNamePointer(EmitterRootBuff ,EmitterNameBuff ,CmdClassBuff,sizeof(CmdClassBuff));
		if(fp==NULL){
			delete	R;
			return;
		}
		ErrorCodeList	ErrorData((ErrorCodeList::CautionLevel)R->ErrorLevel);
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			fp	=R->GetError(fp,ErrorData);
		}
		EmitterRoot	=EmitterRootBuff;
		EmitterName	=EmitterNameBuff;
		CmdClass	=CmdClassBuff;

		LayersBase	*LBase=GetLayersBase()->GetTopLayersBase()->GetShadowTree(R->ShadowLevel ,R->ShadowNumber);

		QBuffer buff;
		R->GetPointer(fp ,buff);
		buff.open(QIODevice::ReadWrite);
		if(strcmp(EmitterRoot,"ANY")==0 && strcmp(EmitterName,"ANY")==0){
			for(GuiDLLItem *s=LBase->GetGuiInitializer()->GuiDLLPack->GetFirst();s!=NULL;s=s->GetNext()){
				if(s->ReceivePacketDirectComm(Cmd ,R->GlobalPage ,EmitterRoot ,EmitterName ,CmdClass,buff,R->IDForUndo,ErrorData)==true)
					break;
			}
		}
		else{
			for(GUIRootClassified *L=LBase->GetGuiInitializer()->RootList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->Root==EmitterRoot){
					for(GUINameClassified *e=L->NameList.GetFirst();e!=NULL;e=e->GetNext()){
						if(e->Point->Name==EmitterName){
							if(e->Point->ReceivePacketDirectComm(Cmd ,R->GlobalPage ,EmitterRoot ,EmitterName ,CmdClass,buff,R->IDForUndo,ErrorData)==true){
								delete	R;
								return;
							}
						}
					}
				}
			}
			for(LogicDLL *L=LBase->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetDLLRoot()==EmitterRoot && L->GetDLLName()==EmitterName){
					//DirectCommPacketBase *H=GetLayersBase()->FindDirectCommPacket(R->GlobalPage ,CmdClass);
					if(L->ReceivePacketDirectComm(Cmd ,R->GlobalPage ,EmitterRoot ,EmitterName ,CmdClass,buff,R->IDForUndo,ErrorData)==true){
						delete	R;
						return;
					}
				}
			}
		}
		delete	R;
	}
}


void	DirectComm::StartServer(int port)
{
	listen ( QHostAddress::Any, port );
	connect(this,SIGNAL(newConnection()),this, SLOT(SlotNewConnection()));
}

void	DirectComm::SetNullInChild(FastCommLeaf *child)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]==child){
			Leaf[i]=NULL;
		}
	}
}

void	DirectComm::ClearAllReqConnection(void)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			delete	Leaf[i];
		}
		Leaf[i]=NULL;
		if(LeafFromServer[i]!=NULL){
			delete	LeafFromServer[i];
		}
		LeafFromServer[i]=NULL;
	}

}
void	DirectComm::WaitReadyReadAll(int milisec)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			Leaf[i]->WaitReadyRead(milisec);
		}
		else if(LeafFromServer[i]!=NULL){
			LeafFromServer[i]->WaitReadyRead(milisec);
		}
	}
}

int		DirectComm::GetFirstCommID(void)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			return i;
		}
		else if(LeafFromServer[i]!=NULL){
			return i;
		}
	}
	return -1;
}
void	DirectComm::AddReqConnection(QObject *parent ,int ID ,QString ip ,int Port)
{
	if(Leaf[ID]!=NULL){
		delete	Leaf[ID];
	}
	Leaf[ID]=new FastCommLeaf(ID,this);
	QString	PureIP=ip.section(':',0,0);
	Leaf[ID]->Set(parent ,PureIP ,Port);
}
bool	DirectComm::StartAllReqConnection(int WaitingMiliSec)
{
	bool	Ret=true;
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			if(Leaf[i]->IsConnected()==false){
				if(Leaf[i]->StartConnect(WaitingMiliSec)==false)
					Ret=false;
			}
		}
	}
	return Ret;
}
bool	DirectComm::IsConnected(int ID)
{
	if(Leaf[ID]!=NULL){
		if(Leaf[ID]->IsConnected()==true){
			return(true);
		}
	}
	else if(LeafFromServer[ID]!=NULL){
		if(LeafFromServer[ID]->IsConnected()==true){
			return(true);
		}
	}

	return(false);
}
bool	DirectComm::TxData(int32 globalPage 
						 ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
						 ,int commID ,BYTE *buff ,int xbyte
						 ,ErrorCodeList &ErrorData)
{
	if(commID==-2){
		commID=GetFirstCommID();
	}
	if(Leaf[commID]!=NULL){
		return(Leaf[commID]->TxData(globalPage ,IndoPacket,buff ,xbyte,ErrorData));
	}
	else if(LeafFromServer[commID]!=NULL){
		return(LeafFromServer[commID]->TxData(globalPage ,IndoPacket,buff ,xbyte,ErrorData));
	}
	return false;
}

bool	DirectComm::TxData(int32 globalPage 
						 ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
						 ,int commID ,QBuffer *f
						 ,ErrorCodeList &ErrorData)
{
	if(commID==-2){
		commID=GetFirstCommID();
	}
	if(Leaf[commID]!=NULL){
		return(Leaf[commID]->TxData(globalPage ,IndoPacket,f,ErrorData));
	}
	else if(LeafFromServer[commID]!=NULL){
		return(LeafFromServer[commID]->TxData(globalPage ,IndoPacket,f,ErrorData));
	}
	return false;
}
bool	DirectComm::TxData(int32 globalPage 
						 ,struct EntryPointBase::EntryPointPacketInfo &IndoPacket
						 ,int commID ,QByteArray *f
						 ,ErrorCodeList &ErrorData)
{
	if(commID==-2){
		commID=GetFirstCommID();
	}
	if(Leaf[commID]!=NULL){
		return(Leaf[commID]->TxData(globalPage ,IndoPacket,f,ErrorData));
	}
	else if(LeafFromServer[commID]!=NULL){
		return(LeafFromServer[commID]->TxData(globalPage ,IndoPacket,f,ErrorData));
	}
	return false;
}
QTcpSocket	*DirectComm::GetSocket(int ComNo)
{
	if(Leaf[ComNo]!=NULL){
		return Leaf[ComNo]->GetSocket();
	}
	else if(LeafFromServer[ComNo]!=NULL){
		return LeafFromServer[ComNo]->GetSocket();
	}
	return NULL;
}


void	DirectComm::SlotNewConnection ()
{
	QTcpSocket	*pClient=nextPendingConnection ();
	QString	Addr=pClient->peerAddress().toString();
	int	LeafID;
	for(LeafID=0;LeafID<MaxCommLeafNumb;LeafID++){
		if(LeafFromServer[LeafID]==NULL){
			break;
		}
	}
	if(LeafID>=MaxCommLeafNumb)
		return;


	LeafFromServer[LeafID]=new FastCommLeaf(LeafID,this);
	LeafFromServer[LeafID]->SetCommParent(this);
	LeafFromServer[LeafID]->SetServerMode(pClient);
	connect(LeafFromServer[LeafID] ,SIGNAL(SignalDisconnected(int)),this ,SLOT(SlotDisconnected(int)));
	SetConnectedAttr(LeafFromServer[LeafID]);

}

void	DirectComm::SlotDisconnected(int id)
{
	Leaf[id]=NULL;
	LeafFromServer[id]=NULL;
}


RecList	*DirectComm::UnpackTopRxBuff(int ID)
{
	if(LeafFromServer[ID]!=NULL){
		RecList	*p=LeafFromServer[ID]->UnpackTopRxBuff();
		if(p!=NULL){
			return p;
		}
	}
	if(Leaf[ID]!=NULL){
		return(Leaf[ID]->UnpackTopRxBuff());
	}

	return NULL;
}

void	DirectComm::ReadyReadDirectComm(void)
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(Leaf[i]!=NULL){
			if(Leaf[i]->IsConnected()==true){
				Leaf[i]->WaitReadyRead(10);
			}
		}
	}
	for(int i=0;i<MaxCommLeafNumb;i++){
		if(LeafFromServer[i]!=NULL){
			if(LeafFromServer[i]->IsConnected()==true){
				LeafFromServer[i]->WaitReadyRead(10);
			}
		}
	}

}


void	DirectComm::Fork(int localpage ,int WaitMilisec)
{
	QElapsedTimer	Timer;
	Timer.start();
	ClearJoined();
	while(Timer.hasExpired(WaitMilisec)==false){
		ReadyReadDirectComm();
	}

	int	GlobalPageOwn=GetLayersBase()->GetGlobalPageFromLocal(localpage);
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(GlobalPageOwn==globalpage)
			continue;
		SlaveCommForkStart	RCmd(GetLayersBase()
									, /**/"ANY",/**/"ANY",GlobalPageOwn);
		RCmd.Send(NULL,globalpage,0);
	}
	while(Timer.hasExpired(WaitMilisec)==false){
		ReadyReadDirectComm();
	}
}

void	DirectComm::Join(int localpage)
{
	int	GlobalPageOwn=GetLayersBase()->GetGlobalPageFromLocal(localpage);
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(GlobalPageOwn==globalpage)
			continue;
		SlaveCommJoin	RCmd(GetLayersBase()
									, /**/"ANY",/**/"ANY",GlobalPageOwn);
		RCmd.Send(NULL,globalpage,0);
	}
	bool	Flag;
	do{
		Flag=true;
		ReadyReadDirectComm();
		for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
			if(GlobalPageOwn==globalpage)
				continue;
			if(IsJoined(globalpage)==false){
				Flag=false;
			}
		}
	}while(Flag==false);
}


void	DirectComm::ClearJoined(void)
{
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		Joined[globalpage]=none3;
	}
}

bool	DirectComm::IsJoined(int globalpage)
{
	if(Joined[globalpage]==true3)
		return false;
	return true;
}

void	DirectComm::MiscatchPacket(int GlobalPage ,QString EmitterRoot ,QString EmitterName ,QString CmdClass)
{
	QString	FileName="MiscatchPacket.txt";
	QFileInfo LInfo(FileName);
	if(LInfo.size()<10000000){
		QFile	F(FileName);

		if(F.open(QIODevice::Append)==true){
			QTextStream	LF(&F);
			LF<<"GlobalPage=";
			LF<<GlobalPage;
			LF<<"  Root:";
			LF<<EmitterRoot;
			LF<<"  Name:";
			LF<<EmitterName;
			LF<<"  CmdClass:";
			LF<<CmdClass;
			LF<<"\n";
		}
	}
}
