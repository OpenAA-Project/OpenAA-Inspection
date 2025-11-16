/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGUIPacketForDLL.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XGUIPacketForDLL.h"
#include "XParamGlobal.h"
#include<QTcpSocket>
#include<QBuffer>
#include "XDLLOnly.h"
#include "XGUIDLL.h"
#include "XGUI.h"
#include "XDataInLayer.h"
#include <QTimer>
#include <QThread>
#include "XGeneralFunc.h"
#include "XDataInLayerCommander.h"
#include "XDataInLayerCmdLocal.h"
#include "XCriticalFunc.h"
#include "XErrorMessage.h"
#include "XIntegrationPacketComm.h"
#include "XEntryPoint.h"

int	NoReceivedPacketNumb;

DEFFUNCEX	bool	DLL_ReceivePacket(LayersBase *Base,int32 cmd ,int32 globalPage 
									  ,const char *EmitterRoot ,const char *EmitterName 
									  ,const char *ClassName,QBuffer &buff
									  ,int32 IDForUndo
									  ,ErrorCodeList &ErrorData)
{
	QString	className=ClassName;
	int	lpage=Base->GetLocalPageFromGlobal(globalPage);
	if(lpage>=0){
		if(strcmp(EmitterRoot,"ANY")==0 && strcmp(EmitterName,"ANY")==0){
			QString	emitterRoot("ANY");
			QString	emitterName("ANY");
			GUICmdPacketBase *PPoint=Base->FindPacket(globalPage ,className ,emitterRoot,emitterName);
			if(PPoint!=NULL){
				if(PPoint->Load(&buff)==false){
					return false;
				}
				PPoint->SetIDForUndo(IDForUndo);
				PPoint->SetFromMaster(true);
				PPoint->AddErrorDataToSystem(ErrorData,globalPage);
				PPoint->Receive(lpage ,cmd,emitterRoot ,emitterName);
				PPoint->SetReceived(true);
				return true;				
			}
		}
		else{
			QString	emitterRoot=EmitterRoot;
			QString	emitterName=EmitterName;
			GUICmdPacketBase *PPoint=Base->FindPacket(globalPage ,className ,emitterRoot,emitterName);
			if(PPoint!=NULL){
				if(PPoint->Load(&buff)==false){
					return false;
				}
				PPoint->SetIDForUndo(IDForUndo);
				PPoint->SetFromMaster(true);
				PPoint->AddErrorDataToSystem(ErrorData,globalPage);
				PPoint->Receive(lpage ,cmd,emitterRoot ,emitterName);
				PPoint->SetReceived(true);
				return true;
			}
		}
	}
	NoReceivedPacketNumb++;
			
	return(false);
}

GUIDirectMessage::GUIDirectMessage(LayersBase *base)
{
	if(base!=NULL){
		IDForUndo=base->GetIDForUndo();
	}
	else{
		IDForUndo=-1;
	}
}

GUIDirectMessage::GUIDirectMessage(GUICmdPacketBase *base)
{
	if(base!=NULL){
		IDForUndo=base->GetLayersBase()->GetIDForUndo();
	}
	else{
		IDForUndo=-1;
	}
}


GUICmdPacketBase::GUICmdPacketBase(LayersBase *base,const QString &emitterRoot ,const QString &emitterName ,const QString &className ,int globalPage)
	:GUIDirectMessage(base),ServiceForLayers(base)
{
	EmitterRoot	=emitterRoot;
	EmitterName =emitterName;
	SendBackPacket		=NULL;
	ReturnBackInReceive	=NULL;
	ClearReceivedFlag();
	FromMaster=false;
	SentRealSocket=false;
	QString	C1=ClassName=className;
	QString	C2=C1.remove(/**/" __ptr64");
	ClassName=C2.remove(/**/" __ptr32");
	GlobalPage=globalPage;
	GetLayersBase()->AppendPacket(this ,emitterRoot ,emitterName ,ClassName);
}
GUICmdPacketBase::~GUICmdPacketBase(void)
{
	GetLayersBase()->RemovePacket(this);
	if(ReturnBackInReceive!=NULL){
		delete	ReturnBackInReceive;
		ReturnBackInReceive=NULL;
	}
}

void	GUICmdPacketBase::PopupPacketPriority(void)
{
	GetLayersBase()->PopupPacketPriority(this);
}


void	GUICmdPacketBase::SetError(int errorCode ,const QString &errorMessage ,ErrorCodeList::CautionLevel level)
{
	ErrorData.SetError(errorCode ,errorMessage ,level,XDateTime::currentDateTime());
}
void	GUICmdPacketBase::SetError(const ErrorCodeList &_ErrorData)
{
	ErrorData=_ErrorData;
}


GUICmdPacketBase	*GUICmdPacketBase::SetLocalPage(int localPage)
{	
	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	return(this);	
}
	
void	GUICmdPacketBase::AddErrorDataToSystem(ErrorCodeList &_ErrorData,int globalPage)
{
	if(_ErrorData.GetLevel()!=ErrorCodeList::_None){
		ErrorData=_ErrorData;
		ErrorCodeList	*c=new ErrorCodeList();
		*c=ErrorData;
		GetLayersBase()->AddError(c,GetLayersBase()->GetLocalPageFromGlobal(globalPage));
	}
}
bool	GUICmdPacketBase::IsPossibleToSend(int32 globalPage)	const
{
	return GetLayersBase()->GetSendingData(globalPage);
}
bool	GUICmdPacketBase::Send(GUICmdPacketBase *parent ,int32 globalPage ,int32 cmd)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetOnTerminating()==true){
		return false;
	}
	if(LBase->GetStopCommSender()==true){
		return false;
	}

	LBase->SetSendingData(globalPage,true);
	int	localpage	=LBase->GetLocalPageFromGlobal(globalPage);
	DataInPage	*Pg	=LBase->GetPageData(localpage);
	if(Pg==NULL){
		::SendErrorMessage(QString(/**/"globalPage is invalid in  : ")
						+EmitterRoot+QString(":")+EmitterName+QString(" : ")
						+ClassName
						+QString("::Send :  globalPage=")+QString::number(globalPage));
		return false;
	}

	SentRealSocket=false;
	ParamComm	*Pc=LBase->GetParamComm();
	Pg->LockTxComm();
	if(Pc->Mastered==true){
		int	ComNo=Pc->GetCommIDFromPage(*LBase->GetParamGlobal(),globalPage);
		if(Pc->EnabledComm==true && ComNo>=0){
			//Send Packet to Salve
			QBuffer	F;
			F.open(QIODevice::ReadWrite);
			if(Save(&F)==true){
				struct EntryPointBase::EntryPointPacketInfo	Info(cmd
																,LBase->GetShadowLevel()
																,LBase->GetShadowNumber()
																,IDForUndo
																,EmitterRoot
																,EmitterName 
																,ClassName);
				if(LBase->GetEntryPoint()->SendData(ComNo,globalPage,Info,&F,ErrorData)==false){
					Pg->UnlockTxComm();
					LBase->SetSendingData(globalPage,false);
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

					if(LBase->GetEntryPoint()->SendArray(ComNo,globalPage,Info,FA,ErrorData)==false){
						Pg->UnlockTxComm();
						LBase->SetSendingData(globalPage,false);
						return false;
					}
				}
			}
			SentRealSocket=true;
		}
		else{
			//Send Packet to same PC receiver
			GUICmdPacketBase *PPoint=LBase->FindPacket(globalPage ,ClassName);
			if(PPoint!=NULL){
				PPoint->FromMaster=false;
				PPoint->AddErrorDataToSystem(ErrorData,globalPage);
				PPoint->Receive(globalPage, cmd ,EmitterRoot,EmitterName);
				PPoint->Received=true;				
			}
		}
	}
	else{
		if(parent==NULL || parent->FromMaster==false){
			if(localpage>=0){
				//Send packet to SameCPU
				GUICmdPacketBase *PPoint=LBase->FindPacket(globalPage ,ClassName);
				if(PPoint!=NULL){
					PPoint->FromMaster=false;
					PPoint->AddErrorDataToSystem(ErrorData,globalPage);
					PPoint->Receive(localpage, cmd ,EmitterRoot,EmitterName);
					PPoint->Received=true;
				}
			}
			else{
				Pg->UnlockTxComm();
				//Send packet to OtherCPU
				LBase->SetSendingData(globalPage,false);
				return false;
			}
		}
		else{
			QBuffer	F;
			F.open(QIODevice::ReadWrite);
			if(Save(&F)==true){
				struct EntryPointBase::EntryPointPacketInfo	Info(cmd
																,LBase->GetShadowLevel()
																,LBase->GetShadowNumber()
																,IDForUndo
																,EmitterRoot
																,EmitterName 
																,ClassName);

				if(LBase->GetEntryPoint()->SendData(localpage,globalPage,Info,&F,ErrorData)==false){
					Pg->UnlockTxComm();
					LBase->SetSendingData(globalPage,false);
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
					if(LBase->GetEntryPoint()->SendArray(localpage,globalPage,Info ,FA,ErrorData)==false){
						Pg->UnlockTxComm();
						LBase->SetSendingData(globalPage,false);
						return false;
					}
				}
			}
			SentRealSocket=true;
		}
	}
	Pg->UnlockTxComm();
	LBase->SetSendingData(globalPage,false);

	return(true);
}

bool	GUICmdPacketBase::SendFromSlaveToMaster(int32 globalPage ,int32 cmd)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetOnTerminating()==true){
		return false;
	}
	if(LBase->GetParamComm()->Mastered==true){
		SentRealSocket=false;
		GUICmdPacketBase *PPoint=LBase->FindPacket(globalPage ,ClassName);
		if(PPoint!=NULL){
			PPoint->FromMaster=false;
			PPoint->AddErrorDataToSystem(ErrorData,globalPage);
			QBuffer	F;
			F.open(QIODevice::ReadWrite);
			Save(&F);
			F.seek(0);
			PPoint->Load(&F);
			PPoint->Receive(globalPage, cmd ,EmitterRoot,EmitterName);
			PPoint->Received=true;
		}
	}
	else{
		SentRealSocket=false;

		QBuffer	F;
		F.open(QIODevice::ReadWrite);
		if(Save(&F)==true){
			struct EntryPointBase::EntryPointPacketInfo	Info(cmd
															,LBase->GetShadowLevel()
															,LBase->GetShadowNumber()
															,IDForUndo
															,EmitterRoot
															,EmitterName 
															,ClassName);
			if(LBase->GetEntryPoint()->SendData(0,globalPage,Info,&F,ErrorData)==false){
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
				if(GetLayersBase()->GetEntryPoint()->SendArray(0,globalPage,Info,FA,ErrorData)==false){
					return false;
				}
			}
		}

		SentRealSocket=true;
	}
	return true;
}
bool	GUICmdPacketBase::SendAllPages(GUICmdPacketBase *parent ,int32 cmd)
{
	for(int page=0;page<GetPageNumb();page++){
		SetGlobalPage(page);
		if(Send(parent,page,cmd)==false){
			return false;
		}
	}
	return true;
}


bool	GUICmdPacketBase::WaitForReadyRead(int GlobalPage ,int milisec)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetOnTerminating()==true){
		return false;
	}
	int	ComNo=LBase->GetParamComm()->GetCommIDFromPage(*LBase->GetParamGlobal(),GlobalPage);
	QTcpSocket	*q=LBase->GetEntryPoint()->GetSocket(ComNo);
	if(q!=NULL){
		return q->waitForReadyRead(milisec);
	}
	return false;
}

bool	GUICmdPacketBase::Send(int32 globalPage ,int32 cmd ,GUICmdPacketBase &AckPacket ,int32 MaxWaitMiliSec)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetOnTerminating()==true){
		return false;
	}
	if(LBase->GetStopCommSender()==true){
		return false;
	}
	if(globalPage>=0){
		AckPacket.SetGlobalPage(globalPage);
	}

	DataInPage	*Pg=LBase->GetPageData(LBase->GetLocalPageFromGlobal(globalPage));
	Pg->LockRxComm();

	AckPacket.PopupPacketPriority();
	PopupPacketPriority();
	AckPacket.ClearReceivedFlag();
	GlobalPage=globalPage;
	SendBackPacket=&AckPacket;
	FromMaster=false;
	if(Send(this ,globalPage ,cmd)==false){
		AckPacket.Received=false;
		Pg->UnlockRxComm();
		return false;
	}
	LBase->SetSendingData(globalPage,true);
	if(SentRealSocket==false){
		QTimer	TM;
		TM.setSingleShot(true);
		TM.start(MaxWaitMiliSec);
		while(TM.isActive()==true){
			if(AckPacket.IsReceived()==true){
				Pg->UnlockRxComm();
				LBase->SetSendingData(globalPage,false);
				return(true);
			}
			QThreadForWait::MSWait(20);
			if(LBase->GetOnTerminating()==true){
				Pg->UnlockRxComm();
				LBase->SetSendingData(globalPage,false);
				return false;
			}
		}
	}
	else{
		/*
		QTimer	TM;
		TM.setSingleShot(true);
		TM.start(MaxWaitMiliSec);
		while(TM.isActive()==true){
			AckPacket.WaitForReadyRead(globalPage,MaxWaitMiliSec);
			if(AckPacket.IsReceived()==true)
				return(true);
		}
		*/
		if(Pg->IsWaitingReq==true){
			Pg->UnlockRxComm();
			LBase->SetSendingData(globalPage,false);
			return false;
		}
		Pg->IsWaitingReq=true;

		DWORD	StartTime=GetComputerMiliSec();
		//for(;;){
		while(GetComputerMiliSec()-StartTime<MaxWaitMiliSec){
			AckPacket.WaitForReadyRead(globalPage,MaxWaitMiliSec/5);
			if(AckPacket.IsReceived()==true){
				LBase->SendInfo(globalPage);
				Pg->IsWaitingReq=false;
				Pg->UnlockRxComm();
				LBase->SetSendingData(globalPage,false);
				return(true);
			}
			if(LBase->GetOnTerminating()==true){
				Pg->IsWaitingReq=false;
				Pg->UnlockRxComm();
				LBase->SetSendingData(globalPage,false);
				return false;
			}
		}
		Pg->IsWaitingReq=false;
		Pg->UnlockRxComm();
		LBase->SetSendingData(globalPage,false);
		LBase->SetCommErrorNoAck(globalPage,typeid(*this).name());
		return false;
	}
	Pg->UnlockRxComm();
	LBase->SetSendingData(globalPage,false);
	LBase->SetCommErrorNoAck(globalPage,typeid(*this).name());
	return(false);
}

bool	GUICmdPacketBase::SendOnly(int32 globalPage ,int32 cmd ,int32 MaxWaitMiliSec)
{
	GUICmdSendAck Receiver(GetLayersBase(), "ANY", "ANY", globalPage);
	if(!Send(globalPage, cmd, Receiver, MaxWaitMiliSec)){
		return false;
	}
	return true;
}

bool	GUICmdPacketBase::SendAck(int LocalPage)
{
	GUICmdSendAck	*SendBack=GetSendBack(GUICmdSendAck,GetLayersBase(),"ANY","ANY" ,LocalPage);
	if(SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(LocalPage),0)==false){
		return false;
	}
	CloseSendBack(SendBack);
	return true;
}
void	GUICmdPacketBase::ActivePhaseList(IntList &PhaseList)
{
	if(GetParamGlobal()->CommonOperationInAllPhases==false){
		PhaseList.Add(GetLayersBase()->GetCurrentPhase());
	}
	else{
		for(int phase=0;phase<GetPhaseNumb();phase++){
			PhaseList.Add(phase);
		}
	}
}

//===============================================================================================================
IntegrationCmdPacketBasePointerList::~IntegrationCmdPacketBasePointerList(void)
{	
	delete	Base;
	Base=NULL;
}

IntegrationCmdPacketBasePointerListContainer	&IntegrationCmdPacketBasePointerListContainer::operator=(IntegrationCmdPacketBase *a)
{	
	AppendList(new IntegrationCmdPacketBasePointerList(a));
	return *this;
}

//===============================================================================================================

bool	GUICmdMultiReq(  GUICmdPacketBaseContainer &RCmdContainer
						,GUICmdPacketBaseContainer &ACmdContainer
						,DWORD WaitingMilisec
						,bool ShowProcessingPanel
						,const QString &TitleOnPanel)
{
	if(RCmdContainer.GetCount()==0){
		return true;
	}
	if(RCmdContainer.GetCount()>ACmdContainer.GetCount()){
		return false;
	}
	GUICmdPacketBase *a=ACmdContainer.GetFirst();
	for(GUICmdPacketBase *r=RCmdContainer.GetFirst();r!=NULL;r=r->GetNext(),a=a->GetNext()){
		if(r->Send(r->GetGlobalPage(),0,*a)==false){
			return false;
		}
	}
	LayersBase	*Base=RCmdContainer.GetFirst()->GetLayersBase();
	bool	ShowingPanel=false;
	if(Base!=NULL && ShowProcessingPanel==true){
		Base->ShowProcessingForm(TitleOnPanel);
		ShowingPanel=true;
	}
	DWORD	LastTime=::GetComputerMiliSec();
	for(;;){
		DWORD	t=::GetComputerMiliSec();
		if((t-LastTime)>WaitingMilisec){
			if(ShowingPanel==true){
				Base->CloseProcessingForm();
				return false;
			}
		}
		int	UnReceived=0;
		for(GUICmdPacketBase *a=ACmdContainer.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->IsReceived()==false){
				UnReceived++;
			}
		}
		if(UnReceived==0){
			break;
		}
	}
	if(ShowingPanel==true){
		Base->CloseProcessingForm();
	}
	return true;
}

bool	GUICmdMultiAck(  GUICmdPacketBaseContainer &RCmdContainer
						,DWORD WaitingMilisec
						,bool ShowProcessingPanel
						,const QString &TitleOnPanel)
{
	if(RCmdContainer.GetCount()==0){
		return true;
	}
	GUICmdSendAck	*ACmd[1000];
	int	i=0;
	int	CmdNumb=0;
	for(GUICmdPacketBase *r=RCmdContainer.GetFirst();r!=NULL;r=r->GetNext(),i++){
		ACmd[i]=new GUICmdSendAck(r->GetLayersBase(),/**/"ANY",/**/"ANY"
												,r->GetGlobalPage());
		CmdNumb++;
		if(r->Send(r->GetGlobalPage(),0,*ACmd[i])==false){
			for(int k=0;k<CmdNumb;k++){
				delete	ACmd[k];
			}
			return false;
		}
	}

	LayersBase	*Base=RCmdContainer.GetFirst()->GetLayersBase();
	bool	ShowingPanel=false;
	if(Base!=NULL && ShowProcessingPanel==true){
		Base->ShowProcessingForm(TitleOnPanel);
		ShowingPanel=true;
	}
	DWORD	LastTime=::GetComputerMiliSec();
	for(;;){
		DWORD	t=::GetComputerMiliSec();
		if((t-LastTime)>WaitingMilisec){
			if(ShowingPanel==true){
				Base->CloseProcessingForm();
				for(int i=0;i<CmdNumb;i++){
					delete	ACmd[i];
				}
				return false;
			}
		}
		int	UnReceived=0;
		for(int i=0;i<CmdNumb;i++){
			if(ACmd[i]->IsReceived()==false){
				UnReceived++;
			}
		}
		if(UnReceived==0){
			break;
		}
	}
	if(ShowingPanel==true){
		Base->CloseProcessingForm();
	}
	for(int i=0;i<CmdNumb;i++){
		delete	ACmd[i];
	}
	return true;
}
