/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDirectCommPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XDirectCommPacket.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XDataInLayer.h"
#include "XAlgorithmDLL.h"
#include "XCriticalFunc.h"
#include "XDirectComm.h"

DEFFUNCEX	bool	DLL_ReceivePacketDirectCommAlgo(AlgorithmBase *ABase 
													,LayersBase *Base
													,int32 cmd 
													,int32 globalPage 
													,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName
													,QBuffer &buff
													,int32 IDForUndo
													,ErrorCodeList &ErrorData)
{
	return DLL_ReceivePacketDirectComm(Base,cmd ,globalPage 
									  ,EmitterRoot ,EmitterName 
									  ,ClassName
									  ,buff
									  ,IDForUndo
									  ,ErrorData);
}
DEFFUNCEX	bool	DLL_ReceivePacketDirectComm(LayersBase *Base,int32 cmd ,int32 globalPage 
									  ,const char *EmitterRoot ,const char *EmitterName 
									  ,const char *ClassName,QBuffer &buff
									  ,int32 IDForUndo
									  ,ErrorCodeList &ErrorData)
{
	if(Base->GetOnTerminating()==true){
		return true;
	}
	int32	GlobalPageFrom;
	QString	className=ClassName;
	int	lpage=Base->GetLocalPageFromGlobal(globalPage);
	if(lpage>=0){
		if(strcmp(EmitterRoot,"ANY")==0 && strcmp(EmitterName,"ANY")==0){
			QString	emitterRoot("ANY");
			QString	emitterName("ANY");
			DirectCommPacketBase *PPoint=Base->FindDirectCommPacket(globalPage ,className ,emitterRoot,emitterName);
			if(PPoint!=NULL){
				if(::Load(&buff,GlobalPageFrom)==false){
					return false;
				}
				if(PPoint->Load(&buff)==false){
					return false;
				}
				//PPoint->SetFromMaster(true);
				//PPoint->AddErrorDataToSystem(ErrorData,globalPage);
				int	tGlobalPageFrom=PPoint->GetGlobalPageFrom();
				PPoint->SetGlobalPageFrom(GlobalPageFrom);
				PPoint->Receive(lpage ,cmd,emitterRoot ,emitterName);
				PPoint->SetGlobalPageFrom(tGlobalPageFrom);
				PPoint->SetReceived(true);
				return true;				
			}
		}
		else{
			QString	emitterRoot=EmitterRoot;
			QString	emitterName=EmitterName;
			DirectCommPacketBase *PPoint=Base->FindDirectCommPacket(globalPage ,className ,emitterRoot,emitterName);
			if(PPoint!=NULL){
				if(::Load(&buff,GlobalPageFrom)==false){
					return false;
				}
				if(PPoint->Load(&buff)==false){
					return false;
				}
				//PPoint->SetFromMaster(true);
				//PPoint->AddErrorDataToSystem(ErrorData,globalPage);
				int	tGlobalPageFrom=PPoint->GetGlobalPageFrom();
				PPoint->SetGlobalPageFrom(GlobalPageFrom);
				PPoint->Receive(lpage ,cmd,emitterRoot ,emitterName);
				PPoint->SetGlobalPageFrom(tGlobalPageFrom);
				PPoint->SetReceived(true);
				return true;
			}
		}
	}
			
	return(false);
}

//=========================================================================================================

SystemConnectionInfo::SystemConnectionInfo(int32 globalPage ,int32 id ,const QString &ipAddress)
{
	ID			=id;
	IPAddress	=ipAddress;
	GlobalPage	=globalPage;
}


DirectCommPacketBase::DirectCommPacketBase(LayersBase *base,int globalPageOwn
										   ,const QString &emitterRoot ,const QString &emitterName ,const QString &className)
										   :GUIDirectMessage(base)
										   ,ServiceForLayers(base)
{
	EmitterRoot			=emitterRoot;
	EmitterName			=emitterName;
	SendBackPacket		=NULL;
	ReturnBackInReceive	=NULL;
	ClearReceivedFlag();
	FromMaster=false;
	SentRealSocket=false;
	ClassName=className;
	GlobalPageFrom=globalPageOwn;
	GetLayersBase()->AppendDirectCommPacket(this ,emitterRoot ,emitterName ,className);
}
DirectCommPacketBase::~DirectCommPacketBase(void)
{
	if(GetLayersBase()->GetOnTerminating()==false){
		GetLayersBase()->RemoveDirectCommPacket(this);
	}
	if(ReturnBackInReceive!=NULL){
		delete	ReturnBackInReceive;
		ReturnBackInReceive=NULL;
	}
}

void	DirectCommPacketBase::PopupPacketPriority(void)
{
	GetLayersBase()->PopupDirectCommPacketPriority(this);
}

DirectCommPacketBase	*DirectCommPacketBase::SetLocalPage(int localPage)
{	
	GlobalPageFrom=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	return(this);	
}

bool	DirectCommPacketBase::WaitForReadyRead(int _GlobalPage ,int milisec)
{
	if(GetLayersBase()->GetOnTerminating()==true){
		return false;
	}
	int	ComNo=GetLayersBase()->GetParamComm()->GetCommIDFromPage(*GetLayersBase()->GetParamGlobal(),_GlobalPage);
	QTcpSocket	*q=GetLayersBase()->GetEntryPoint()->GetSocket(ComNo);
	if(q!=NULL){
		return q->waitForReadyRead(milisec);
	}
	return false;
}
bool	DirectCommPacketBase::Send(DirectCommPacketBase *parent ,int32 globalPageTo ,int32 cmd)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetOnTerminating()==true){
		return false;
	}
	if(LBase->GetStopCommSender()==true){
		return false;
	}
	SentRealSocket=false;
	if(GetParamComm()->Mastered==true){
		int	ComNo=GetParamComm()->GetCommIDFromPage(*GetParamGlobal(),globalPageTo);
		if(GetParamComm()->EnabledComm==true && ComNo>=0){
			//Send Packet to Salve
			QBuffer	F;
			F.open(QIODevice::ReadWrite);
			if(::Save(&F,GlobalPageFrom)==false){
				return false;
			}
			if(Save(&F)==true){
				struct EntryPointBase::EntryPointPacketInfo	Info(cmd
																,LBase->GetShadowLevel()
																,LBase->GetShadowNumber()
																,IDForUndo
																,EmitterRoot
																,EmitterName 
																,ClassName);

				if(GetEntryPoint()->SendDataDirectComm(ComNo,globalPageTo,Info,&F,ErrorData)==false){
					return false;
				}
			}
			/*
			else{
				QByteArray	*FA=GetSaveArray();
				if(FA!=NULL){
					if(Base->GetEntryPoint()->SendArray(cmd ,ComNo,globalPageTo,EmitterRoot,EmitterName ,ClassName,FA,ErrorData)==false){
						return false;
					}
				}
			}
			*/
			SentRealSocket=true;
		}
		else{
			//Send Packet to same PC receiver
			DirectCommPacketBase *PPoint=LBase->FindDirectCommPacket(GetGlobalPageFrom() ,ClassName,EmitterRoot,EmitterName);
			if(PPoint!=NULL){
				PPoint->FromMaster=false;
				PPoint->ErrorData=ErrorData;
				PPoint->Receive(globalPageTo, cmd ,EmitterRoot,EmitterName);
				PPoint->Received=true;				
			}
			else{
				PPoint=LBase->FindDirectCommPacket(globalPageTo ,ClassName);
				if(PPoint!=NULL){
					PPoint->FromMaster=false;
					PPoint->ErrorData=ErrorData;
					PPoint->Receive(globalPageTo, cmd ,EmitterRoot,EmitterName);
					PPoint->Received=true;				
				}
			}
		}
	}
	else{
		if(parent==NULL || parent->FromMaster==false){
			int	lpage=LBase->GetLocalPageFromGlobal(globalPageTo);
			if(lpage>=0){
				//Send packet to SameCPU
				DirectCommPacketBase *PPoint=LBase->FindDirectCommPacket(GetGlobalPageFrom() ,ClassName,EmitterRoot,EmitterName);
				if(PPoint!=NULL){
					PPoint->FromMaster=false;
					PPoint->ErrorData=ErrorData;
					PPoint->Receive(lpage, cmd ,EmitterRoot,EmitterName);
					PPoint->Received=true;
				}
				else{
					PPoint=LBase->FindDirectCommPacket(globalPageTo ,ClassName);
					if(PPoint!=NULL){
						PPoint->FromMaster=false;
						PPoint->ErrorData=ErrorData;
						PPoint->Receive(lpage, cmd ,EmitterRoot,EmitterName);
						PPoint->Received=true;
					}
				}
			}
			else{
				int	ComNo=GetEntryPoint()->GetDirectCommIDFromGlobalPage(globalPageTo);
				if(ComNo>=0){
					QBuffer	F;
					F.open(QIODevice::ReadWrite);
					if(::Save(&F,GlobalPageFrom)==false){
						return false;
					}
					if(Save(&F)==true){
						struct EntryPointBase::EntryPointPacketInfo	Info(cmd
																		,LBase->GetShadowLevel()
																		,LBase->GetShadowNumber()
																		,IDForUndo
																		,EmitterRoot
																		,EmitterName 
																		,ClassName);
						if(LBase->GetEntryPoint()->SendDataDirectComm(ComNo,globalPageTo,Info,&F,ErrorData)==false){
							return false;
						}
						SentRealSocket=true;
						return true;
					}
				}
				return false;
			}
		}
		else{
			QBuffer	F;
			F.open(QIODevice::ReadWrite);
			if(::Save(&F,GlobalPageFrom)==false){
				return false;
			}
			if(Save(&F)==true){
				struct EntryPointBase::EntryPointPacketInfo	Info(cmd
																,LBase->GetShadowLevel()
																,LBase->GetShadowNumber()
																,IDForUndo
																,EmitterRoot
																,EmitterName 
																,ClassName);
				if(GetEntryPoint()->SendData(-2,globalPageTo,Info,&F,ErrorData)==false){
					return false;
				}
			}
			else{
				QByteArray	*FA=GetSaveArray();
				if(FA!=NULL){
					struct EntryPointBase::EntryPointPacketInfo	Info(cmd
																	,LBase->GetShadowLevel()
																	,LBase->GetShadowNumber()
																	,IDForUndo
																	,EmitterRoot
																	,EmitterName 
																	,ClassName);
					if(GetEntryPoint()->SendArray(-2,globalPageTo,Info,FA,ErrorData)==false){
						return false;
					}
				}
			}
			SentRealSocket=true;
		}
	}
	return(true);
}
bool	DirectCommPacketBase::Send(int32 globalPageTo ,int32 cmd ,DirectCommPacketBase &AckPacket ,int32 MaxWaitMiliSec)
{
	if(GetLayersBase()->GetOnTerminating()==true){
		return false;
	}
	if(GetLayersBase()->GetStopCommSender()==true){
		return false;
	}
	if(globalPageTo>=0){
		AckPacket.SetGlobalPageFrom(GetGlobalPageFrom());
	}

NextAgain:;
	AckPacket.PopupPacketPriority();
	PopupPacketPriority();
	AckPacket.ClearReceivedFlag();
	//GlobalPage=globalPageTo;
	SendBackPacket=&AckPacket;

	if(Send(this ,globalPageTo ,cmd)==false){
		AckPacket.Received=false;
		return false;
	}
	if(SentRealSocket==false){
		DWORD	LastMilisec=GetComputerMiliSec();
		while(GetComputerMiliSec()-LastMilisec<MaxWaitMiliSec){
			//QCoreApplication::processEvents();	?? May be necessary
			GetLayersBase()->GetEntryPoint()->ReadyReadDirectComm();
			//AckPacket.WaitForReadyRead(globalPageTo,MaxWaitMiliSec);
			if(AckPacket.IsReceived()==true){
				return(true);
			}
			QThreadForWait::MSWait(20);
			if(GetLayersBase()->GetOnTerminating()==true){
				return false;
			}
		}
		for(int k=0;k<3;k++){
			//ReTry
			QThreadForWait::MSWait(300);
			if(Send(this ,globalPageTo ,cmd)==false){
				AckPacket.Received=false;
				return false;
			}
			LastMilisec=GetComputerMiliSec();
			while(GetComputerMiliSec()-LastMilisec<MaxWaitMiliSec){
				GetLayersBase()->GetEntryPoint()->ReadyReadDirectComm();
				//AckPacket.WaitForReadyRead(globalPageTo,MaxWaitMiliSec);
				if(AckPacket.IsReceived()==true){
					return(true);
				}
				QThreadForWait::MSWait(20);
				if(GetLayersBase()->GetOnTerminating()==true){
					return false;
				}
			}
		}
	}
	else{

		DWORD	StartTime=GetComputerMiliSec();
		//for(;;){
		while(GetComputerMiliSec()-StartTime<MaxWaitMiliSec){
			//AckPacket.WaitForReadyRead(globalPageTo,MaxWaitMiliSec/20);
			QCoreApplication::processEvents();
			GetLayersBase()->GetEntryPoint()->ReadyReadDirectComm();
			if(AckPacket.IsReceived()==true){
				//GetLayersBase()->SendInfo(globalPageTo);
				return(true);
			}
			QThreadForWait::MSWait(10);
			if(GetLayersBase()->GetOnTerminating()==true){
				return false;
			}
		}
		goto	NextAgain;
	}
	return(false);
}
//---------------------------------------------------------------

bool	SystemConnectionInfo::Save(QIODevice *f)
{
	if(::Save(f,ID)==false){
		return false;
	}
	if(::Save(f,IPAddress)==false){
		return false;
	}
	if(::Save(f,GlobalPage)==false){
		return false;
	}
	return true;
}
bool	SystemConnectionInfo::Load(QIODevice *f)
{
	if(::Load(f,ID)==false){
		return false;
	}
	if(::Load(f,IPAddress)==false){
		return false;
	}
	if(::Load(f,GlobalPage)==false){
		return false;
	}
	return true;
}

bool	SystemConnectionInfoContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(SystemConnectionInfo *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->Save(f)==false){
			return false;
		}
	}
	if(::Save(f,WaitingTimeToConnect)==false){
		return false;
	}
	return true;
}
bool	SystemConnectionInfoContainer::Load(QIODevice *f)
{
	int32	N=0;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		SystemConnectionInfo	*p=new SystemConnectionInfo();
		if(p->Load(f)==false){
			return false;
		}
		AppendList(p);
	}
	if(::Load(f,WaitingTimeToConnect)==false){
		return false;
	}
	return true;
}
SystemConnectionInfo	*SystemConnectionInfoContainer::GetInfo(int ID)	const
{
	for(SystemConnectionInfo *p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetID()==ID){
			return p;
		}
	}
	return NULL;
}
SystemConnectionInfoContainer	&SystemConnectionInfoContainer::operator=(SystemConnectionInfoContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

//==============================================================================================================

SlaveCommForkStart::SlaveCommForkStart(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPageOwn)
:DirectCommPacketBase(base,globalPageOwn,EmitterRoot,EmitterName ,typeid(this).name())
{
}

void	SlaveCommForkStart::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	globalpage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	GetLayersBase()->GetDirectCommBase()->SetStartFork(globalpage);
}

SlaveCommJoin::SlaveCommJoin(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPageOwn)
:DirectCommPacketBase(base,globalPageOwn,EmitterRoot,EmitterName ,typeid(this).name())
{
}

void	SlaveCommJoin::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	int	globalpage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	GetLayersBase()->GetDirectCommBase()->SetJoined(globalpage);
}