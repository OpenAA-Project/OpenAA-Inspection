/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\IntegrationLib\XIntegrationPacketComm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XGUIPacketForDLL.h"
#include "XParamGlobal.h"
#include<QBuffer>
#include "XDLLOnly.h"
#include "XGUIDLL.h"
//#include "XGUI.h"
#include "XDataInLayer.h"
#include <QTimer>
#include <QThread>
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XErrorMessage.h"
#include "XIntegrationComm.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationBase.h"


IntegrationCmdPacketBase::IntegrationCmdPacketBase(LayersBase *base,const QString &emitterRoot ,const QString &emitterName ,const QString &className ,int _SlaveNo)
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
	SlaveNo=_SlaveNo;
	GetLayersBase()->AppendIntegrationPacket(this ,emitterRoot ,emitterName ,ClassName);
}
/*
// This is described in XDataInLayerComm.cpp
IntegrationCmdPacketBase::~IntegrationCmdPacketBase(void)
{
	GetLayersBase()->RemoveIntegrationPacket(this);
}
*/

void	IntegrationCmdPacketBase::PopupPacketPriority(void)
{
	GetLayersBase()->PopupIntegrationPacketPriority(this);
}

void	IntegrationCmdPacketBase::SetError(int errorCode ,const QString &errorMessage ,ErrorCodeList::CautionLevel level)
{
	ErrorData.SetError(errorCode ,errorMessage ,level,XDateTime::currentDateTime());
}
void	IntegrationCmdPacketBase::SetError(ErrorCodeList &_ErrorData)
{
	ErrorData=_ErrorData;
}
	
void	IntegrationCmdPacketBase::AddErrorDataToSystem(ErrorCodeList &_ErrorData,int slaveNo)
{
	if(_ErrorData.GetLevel()!=ErrorCodeList::_None){
		ErrorData=_ErrorData;
		ErrorCodeList	*c=new ErrorCodeList();
		*c=ErrorData;
		GetLayersBase()->AddIntegrationError(c,slaveNo);
	}
}
IntegrationCmdPacketBase	*IntegrationCmdPacketBase::SetSlaveNo(int slaveno)
{	
	SlaveNo=slaveno;
	return(this);
}

bool	IntegrationCmdPacketBase::SendFromSlaveToMaster(int32 OwnSlaveNo ,int32 cmd)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetOnTerminating()==true){
		return false;
	}
	IntegrationBase	*IBase=LBase->GetIntegrationBasePointer();
	if(IBase->GetParamIntegrationMaster()->IsIntegrationMaster()==true){
		SentRealSocket=false;
		IntegrationCmdPacketBase *PPoint=LBase->FindIntegrationPacket(OwnSlaveNo ,ClassName);
		if(PPoint!=NULL){
			PPoint->FromMaster=false;
			PPoint->AddErrorDataToSystem(ErrorData,OwnSlaveNo);
			PPoint->Receive(OwnSlaveNo, cmd ,EmitterRoot,EmitterName);
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
			if(LBase->GetEntryPoint()->SendIntegrationData(OwnSlaveNo,Info,&F,ErrorData)==false){
				LBase->SetIntegrationSendingData(OwnSlaveNo,false);
				return false;
			}
		}
		SentRealSocket=true;
	}
	return true;
}


bool	IntegrationCmdPacketBase::IsPossibleToSend(int32 slaveNo)	const
{
	return GetLayersBase()->GetIntegrationSendingData(slaveNo);
}
bool	IntegrationCmdPacketBase::Send(IntegrationCmdPacketBase *parent ,int32 slaveNo ,int32 cmd)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetOnTerminating()==true){
		return false;
	}
	if(LBase->GetStopCommSender()==true){
		return false;
	}

	LBase->SetIntegrationSendingData(slaveNo,true);

	SentRealSocket=false;
	IntegrationBase	*IBase=LBase->GetIntegrationBasePointer();
	ParamIntegrationMaster	*Param=IBase->GetParamIntegrationMaster();
	if(Param->IsIntegrationMaster()==true){
		if(IBase->GetIntegrationSlaveCount()>slaveNo
		&& slaveNo>=0 
		&& Param->IntegrationSlaveMode==false){
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
				if(LBase->GetEntryPoint()->SendIntegrationData(slaveNo,Info,&F,ErrorData)==false){
					LBase->SetIntegrationSendingData(slaveNo,false);
					return false;
				}
			}
			SentRealSocket=true;
		}
		else{
			//Send Packet to same PC receiver
			IntegrationCmdPacketBase *PPoint=LBase->FindIntegrationPacket(slaveNo ,ClassName);
			if(PPoint!=NULL){
				PPoint->FromMaster=false;
				PPoint->AddErrorDataToSystem(ErrorData,slaveNo);
				PPoint->Receive(slaveNo, cmd ,EmitterRoot,EmitterName);
				PPoint->Received=true;				
			}
		}
	}
	else{
		if(parent==NULL || parent->FromMaster==false){
			if(slaveNo>=0){
				//Send packet to SameCPU
				IntegrationCmdPacketBase *PPoint=LBase->FindIntegrationPacket(slaveNo ,ClassName);
				if(PPoint!=NULL){
					PPoint->FromMaster=false;
					PPoint->AddErrorDataToSystem(ErrorData,slaveNo);
					PPoint->Receive(slaveNo, cmd ,EmitterRoot,EmitterName);
					PPoint->Received=true;
				}
			}
			else{
				//Send packet to OtherCPU
				LBase->SetIntegrationSendingData(slaveNo,false);
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
				if(LBase->GetEntryPoint()->SendIntegrationData(slaveNo,Info,&F,ErrorData)==false){
					LBase->SetIntegrationSendingData(slaveNo,false);
					return false;
				}
			}
			SentRealSocket=true;
		}
	}
	LBase->SetIntegrationSendingData(slaveNo,false);

	return(true);
}

bool	IntegrationCmdPacketBase::SendReqAck(IntegrationCmdPacketBase *parent ,int32 slaveNo ,int32 cmd)
{
	IntegrationCommPack		*P=GetLayersBase()->GetIntegrationCommPointer();
	if(P!=NULL){
		IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
		IntegrationCommPipe	*pp=P->GetSocket(slaveNo);
		if(pp!=NULL && pp->IsConnected()==true){
			if(IBase->GetParamIntegrationMaster()->Mastered==true){
				IntegrationAck	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",slaveNo);
				return Send(slaveNo ,cmd ,RCmd);
			}
			else{
				return Send(parent,slaveNo ,cmd);
			}
		}
		else{
			EachMaster	*m=IBase->GetMaster(slaveNo);
			if(m!=NULL && m->GetSlave()->SlaveIsInMaster==true){
				if(IBase->GetParamIntegrationMaster()->Mastered==true){
					//Receive(slaveNo, cmd ,EmitterRoot,EmitterName);
					IntegrationAck	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",slaveNo);
					return Send(slaveNo ,cmd ,RCmd);
				}
			}
		}
	}
	return false;
}

void	IntegrationCmdPacketBase::SendAck(int slaveNo)
{
	IntegrationAck	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",slaveNo);
	RCmd.SendFromSlaveToMaster(slaveNo,0);
}

bool	IntegrationCmdPacketBase::WaitForReadyRead(int slaveNo ,int milisec)
{
	if(GetLayersBase()->GetOnTerminating()==true){
		return false;
	}
	QTcpSocket	*q=GetLayersBase()->GetEntryPoint()->GetIntegrationSocket(slaveNo);
	if(q!=NULL){
		return q->waitForReadyRead(milisec);
	}
	return false;
}

bool	IntegrationCmdPacketBase::Send(int32 slaveNo ,int32 cmd ,IntegrationCmdPacketBase &AckPacket ,int32 MaxWaitMiliSec)
{
	LayersBase	*LBase=GetLayersBase();
	if(LBase->GetOnTerminating()==true){
		return false;
	}
	if(LBase->GetStopCommSender()==true){
		return false;
	}
	IntegrationBase	*b=LBase->GetIntegrationBasePointer();
	if(b->GetIntegrationSlaveCount()>slaveNo && slaveNo>=0){
		AckPacket.SetSlaveNo(slaveNo);
	}

	AckPacket.PopupPacketPriority();
	PopupPacketPriority();
	AckPacket.ClearReceivedFlag();

	SendBackPacket=&AckPacket;
	FromMaster=false;
	if(Send(this ,slaveNo ,cmd)==false){
		AckPacket.Received=false;
		return false;
	}
	LBase->SetIntegrationSendingData(slaveNo,true);
	if(SentRealSocket==false){
		QElapsedTimer	TM;
		TM.start();
		while(TM.hasExpired(MaxWaitMiliSec)==false){
			if(AckPacket.IsReceived()==true){
				LBase->SetIntegrationSendingData(slaveNo,false);
				return(true);
			}
			QThreadForWait::MSWait(20);
			if(LBase->GetOnTerminating()==true){
				LBase->SetIntegrationSendingData(slaveNo,false);
				return false;
			}
		}
	}
	else{
		//bool	tEnableLoopOnIdle=LBase->GetEnableLoopOnIdle();
		//LBase->SetEnableLoopOnIdle(false);
		//QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		//LBase->SetEnableLoopOnIdle(tEnableLoopOnIdle);

		DWORD	StartTime=GetComputerMiliSec();
		//for(;;){
		while(GetComputerMiliSec()-StartTime<MaxWaitMiliSec){
			AckPacket.WaitForReadyRead(slaveNo,MaxWaitMiliSec/5);
			if(AckPacket.IsReceived()==true){
				LBase->SetIntegrationSendingData(slaveNo,false);
				return(true);
			}
			if(LBase->GetOnTerminating()==true){
				LBase->SetIntegrationSendingData(slaveNo,false);
				return false;
			}
		}
		LBase->SetIntegrationSendingData(slaveNo,false);
		LBase->SetCommErrorNoAck(slaveNo,typeid(*this).name());
		return false;
	}
	LBase->SetIntegrationSendingData(slaveNo,false);
	LBase->SetCommErrorNoAck(slaveNo,typeid(*this).name());
	return(false);
}

DEFFUNCEX	bool	DLL_ReceiveIntegrationPacket(LayersBase *Base,int32 cmd ,int32 SlaveNo 
									  ,const char *EmitterRoot ,const char *EmitterName 
									  ,const char *ClassName,QBuffer &buff
									  ,int32 IDForUndo
									  ,ErrorCodeList &ErrorData)
{
	QString	className=ClassName;

	if(SlaveNo>=0){
		if(strcmp(EmitterRoot,"ANY")==0 && strcmp(EmitterName,"ANY")==0){
			QString	emitterRoot("ANY");
			QString	emitterName("ANY");
			IntegrationCmdPacketBase *PPoint=Base->FindIntegrationPacket(SlaveNo ,className ,emitterRoot,emitterName);
			if(PPoint!=NULL){
				if(PPoint->Load(&buff)==false){
					return false;
				}
				PPoint->SetIDForUndo(IDForUndo);
				PPoint->SetFromMaster(true);
				PPoint->AddErrorDataToSystem(ErrorData,SlaveNo);
				PPoint->Receive(SlaveNo ,cmd,emitterRoot ,emitterName);
				PPoint->SetReceived(true);
				return true;				
			}
		}
		else{
			QString	emitterRoot=EmitterRoot;
			QString	emitterName=EmitterName;
			IntegrationCmdPacketBase *PPoint=Base->FindIntegrationPacket(SlaveNo ,className ,emitterRoot,emitterName);
			if(PPoint!=NULL){
				if(PPoint->Load(&buff)==false){
					return false;
				}
				PPoint->SetIDForUndo(IDForUndo);
				PPoint->SetFromMaster(true);
				PPoint->AddErrorDataToSystem(ErrorData,SlaveNo);
				PPoint->Receive(SlaveNo ,cmd,emitterRoot ,emitterName);
				PPoint->SetReceived(true);
				return true;
			}
		}
	}
			
	return(false);
}
bool	IntegrationMultiReq( IntegrationCmdPacketBaseContainer &RCmdContainer
							,IntegrationCmdPacketBaseContainer &ACmdContainer
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
	IntegrationCmdPacketBase *a=ACmdContainer.GetFirst();
	for(IntegrationCmdPacketBase *r=RCmdContainer.GetFirst();r!=NULL;r=r->GetNext(),a=a->GetNext()){
		if(r->Send(r->GetSlaveNo(),0,*a)==false){
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
		for(IntegrationCmdPacketBase *a=ACmdContainer.GetFirst();a!=NULL;a=a->GetNext()){
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

bool	IntegrationMultiAck( IntegrationCmdPacketBaseContainer &RCmdContainer
							,DWORD WaitingMilisec
							,bool ShowProcessingPanel
							,const QString &TitleOnPanel)
{
	if(RCmdContainer.GetCount()==0){
		return true;
	}
	IntegrationAck	*ACmd[1000];
	int	i=0;
	int	CmdNumb=0;
	for(IntegrationCmdPacketBase *r=RCmdContainer.GetFirst();r!=NULL;r=r->GetNext(),i++){
		ACmd[i]=new IntegrationAck(r->GetLayersBase(),/**/"ANY",/**/"ANY",r->GetSlaveNo());
		CmdNumb++;
		if(r->Send(r->GetSlaveNo(),0,*ACmd[i],WaitingMilisec)==false){
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
