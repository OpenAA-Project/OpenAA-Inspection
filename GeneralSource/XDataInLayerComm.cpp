
#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <stdlib.h>
#include <QTimer>
#include <QThread>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XAlert.h"
#include "XPointer.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "SelectPasteForm.h"
#include "XTransfer.h"
#include "XCriticalFunc.h"
#include "XDatabaseLoader.h"
#include "XPieceArchitect.h"
#include "OnProcessingForm.h"
#include "XCrossObj.h"
#include "XDirectComm.h"
#include "XLightClass.h"
#include "ServiceLibResource.h"
#include "XGUIFormBase.h"
#include "XFilterManager.h"
#include "XErrorCode.h"
#include "XFileRegistry.h"
#include "XOutlineOffset.h"
#include "XLogo.h"
#include "XAnyData.h"
#include <QMessageBox>
#include "XDirectComm.h"
#include "XGeneralStocker.h"
#include "XServiceForLayers.h"
#include "XGUI.h"
#include "XSyncGUI.h"
#include "XStatusController.h"
#include "XLearningRegist.h"
#include "XImageProcess.h"
#include "XDateTime.h"
#include "XShareMasterData.h"
#include "XPrinterManager.h"
#include "XPointer.h"
#include "XIntegrationComm.h"
#include "XIntegrationPacketComm.h"


IntegrationCmdPacketBase::~IntegrationCmdPacketBase(void)
{
	GetLayersBase()->RemoveIntegrationPacket(this);
	if(ReturnBackInReceive!=NULL){
		delete	ReturnBackInReceive;
		ReturnBackInReceive=NULL;
	}
}

void	LayersBase::AppendPacket(GUICmdPacketBase *PSrc ,const QString &emitterRoot ,const QString &emitterName ,const QString &className)
{
	GUICmdPacketMutex.lock();
	NPListPack<ReceiverList>	*P=GetRCmdBase();
	if(P!=NULL){
		GetRCmdBase()->AppendList(new ReceiverList(emitterRoot,emitterName ,className,PSrc));
	}
	GUICmdPacketMutex.unlock();
}

bool	LayersBase::RemovePacket(GUICmdPacketBase *PSrc)
{
	bool	Ret=false;
	GUICmdPacketMutex.lock();
	if(GetRCmdBase()!=NULL){
		for(ReceiverList *p=GetRCmdBase()->GetLast();p!=NULL;p=p->GetPrev()){
			if(p->Point==PSrc){
				GetRCmdBase()->RemoveList(p);
				delete	p;
				Ret=true;
				break;
			}
		}
	}
	GUICmdPacketMutex.unlock();
	return Ret;
}


void	LayersBase::PopupPacketPriority(GUICmdPacketBase *PSrc)
{
	GUICmdPacketMutex.lock();
	NPListPack<ReceiverList>	*P=GetRCmdBase();
	if(P!=NULL){
		for(ReceiverList *p=P->GetLast();p!=NULL;p=p->GetPrev()){
			if(p->Point==PSrc){
				P->RemoveList(p);
				P->AppendList(p);
				break;
			}
		}
	}
	GUICmdPacketMutex.unlock();
}

GUICmdPacketBase *LayersBase::FindPacket(int globalPage ,const QString &ClassName)
{
	GUICmdPacketMutex.lock();
	NPListPack<ReceiverList>	*P=GetRCmdBase();
	if(P!=NULL){
		for(ReceiverList *p=P->GetLast();p!=NULL;p=p->GetPrev()){
			if(((p->Point->GlobalPage==globalPage) || (p->Point->GlobalPage==-1)) && (p->ClassName==ClassName)){
				GUICmdPacketMutex.unlock();
				return p->Point;
			}
		}
	}
	GUICmdPacketMutex.unlock();
	return NULL;
}

GUICmdPacketBase *LayersBase::FindPacket(int globalPage ,const QString &ClassName, QString &emitterRoot, QString &emitterName)
{
	if((emitterRoot=="ANY") && (emitterName=="ANY")){
		GUICmdPacketMutex.lock();
		NPListPack<ReceiverList>	*P=GetRCmdBase();
		if(P!=NULL){
			for(ReceiverList *p=P->GetLast();p!=NULL;p=p->GetPrev()){
				if(((p->Point->GlobalPage==globalPage) || (p->Point->GlobalPage==-1)) && (p->ClassName==ClassName)){
					GUICmdPacketMutex.unlock();
					emitterRoot	=p->EmitterRoot;
					emitterName	=p->EmitterName;
					return p->Point;
				}
			}
		}
	}
	else{
		GUICmdPacketMutex.lock();
		NPListPack<ReceiverList>	*P=GetRCmdBase();
		if(P!=NULL){
			for(ReceiverList *p=P->GetLast();p!=NULL;p=p->GetPrev()){
				if(((p->Point->GlobalPage==globalPage) || (p->Point->GlobalPage==-1)) 
				&& (((p->EmitterRoot==emitterRoot) && (p->EmitterName==emitterName))) && (p->ClassName==ClassName) ){
					GUICmdPacketMutex.unlock();
					emitterRoot	=p->EmitterRoot;
					emitterName	=p->EmitterName;
					return p->Point;
				}
			}
		}
	}
	GUICmdPacketMutex.unlock();
	return NULL;
}

void	LayersBase::AddError(ErrorCodeList *e,int localPage)
{
	ErrorMutex.lock();
	e->SetPage(localPage);
	GetErrorContainer()->AppendList(e);
	ErrorMutex.unlock();
	if(GetParamGlobal()->ErrorLogFile.isEmpty()==false){
		QFile	FL(GetParamGlobal()->ErrorLogFile);
		if(FL.open(QIODevice::Append | QIODevice::Text)==true){
			QTextStream	TxtStr(&FL);
			e->OutputStr(TxtStr);
			TxtStr<<QString("\n");
		}
	}
}
bool	LayersBase::PacketSender(NPListPack<GUICmdPacketDim> &Dim ,int32 MaxWaitMiliSec)
{
	int	N=Dim.GetNumber();
	GUICmdPacketDim *CDim[1000];
	GUICmdPacketDim **CDimPoint;
	if(N<=sizeof(CDim)/sizeof(CDim[0])){
		CDimPoint=CDim;
	}
	else{
		CDimPoint=new GUICmdPacketDim *[N];
	}

	int	n=0;
	for(GUICmdPacketDim *C=Dim.GetFirst();C!=NULL;C=C->GetNext(),n++){
		CDimPoint[n]=C;
	}
	if(GetParamComm()->GetConnectedPCNumb()==0){
		for(int i=0;i<N;i++){
			GUICmdPacketDim *C=CDimPoint[i];
			if(C->GlobalPage>=0){
				C->Receiver->SetGlobalPage(C->GlobalPage);
			}

			C->Receiver->PopupPacketPriority();
			C->Sender->PopupPacketPriority();
			C->Receiver->ClearReceivedFlag();
			C->Sender->GlobalPage=C->GlobalPage;
			C->Sender->SendBackPacket=C->Receiver;
			C->Sender->FromMaster=false;
			if(C->Sender->Send(C->Sender ,C->GlobalPage ,C->Cmd)==false){
				C->Receiver->Received=false;
			}
		}

		DWORD	NowTime=GetComputerMiliSec();

		for(;;){
			int	Numb=0;
			for(GUICmdPacketDim *C=Dim.GetFirst();C!=NULL;C=C->GetNext()){
				if(C->Receiver->IsReceived()==false){
					if(C->Sender->SentRealSocket==false){
						if(GetComputerMiliSec()-NowTime>MaxWaitMiliSec){
							return false;
						}
					}
					else{
						//if(_CrtCheckMemory()==false)
						//	return(false);
						C->Receiver->WaitForReadyRead(C->GlobalPage,MaxWaitMiliSec/(2*N));
						if(GetComputerMiliSec()-NowTime>MaxWaitMiliSec){
							return false;
						//if(_CrtCheckMemory()==false)
						//	return(false);
						}
					}
					if(OnTerminating==true){
						return false;
					}
					Numb++;
				}
			}	
			if(Numb==0){
				break;
			}
		}
	}
	else{
		for(int i=0;i<N;i++){
			GUICmdPacketDim *C=CDimPoint[i];
			if(C->GlobalPage>=0)
				C->Receiver->SetGlobalPage(C->GlobalPage);

			C->Receiver->PopupPacketPriority();
			C->Sender->PopupPacketPriority();
			C->Receiver->ClearReceivedFlag();
			C->Sender->GlobalPage=C->GlobalPage;
			C->Sender->SendBackPacket=C->Receiver;
			C->Sender->FromMaster=false;
			if(C->Sender->Send(C->Sender ,C->GlobalPage ,C->Cmd)==false){
				C->Receiver->Received=false;
			}
			else{

				DWORD	NowTime=GetComputerMiliSec();
				while(C->Receiver->IsReceived()==false){
					if(C->Sender->SentRealSocket==false){
						if(GetComputerMiliSec()-NowTime>MaxWaitMiliSec){
							return false;
						}
					}
					else{
						C->Receiver->WaitForReadyRead(C->GlobalPage,MaxWaitMiliSec/(2*N));
						//C->Receiver->WaitForReadyRead(C->GlobalPage,0);
						if(GetComputerMiliSec()-NowTime>MaxWaitMiliSec){
							return false;
						}
					}
					if(OnTerminating==true){
						return false;
					}
				}
			}
		}
	}
	if(CDimPoint!=CDim){
		delete	[]CDimPoint;
	}
	return true;
}

bool	LayersBase::GetSendingData(int globalpage)
{	
	if(SendingData==NULL)
		return false;
	return SendingData[globalpage];
}

void	LayersBase::SetSendingData(int globalpage ,bool d)
{	
	if(SendingData!=NULL){
		SendingData[globalpage]=d;
	}
}


//===================================================================================================================================================

void	LayersBase::AppendDirectCommPacket(DirectCommPacketBase *PSrc ,const QString &emitterRoot ,const QString &emitterName ,const QString &className)
{
	GUICmdPacketMutex.lock();
	if(GetRCmdDirectCommBase()!=NULL){
		GetRCmdDirectCommBase()->AppendList(new DirectCommReceiverList(emitterRoot,emitterName ,className,PSrc));
	}
	GUICmdPacketMutex.unlock();
}

bool	LayersBase::RemoveDirectCommPacket(DirectCommPacketBase *PSrc)
{
	bool	Ret=false;
	GUICmdPacketMutex.lock();
	if(GetRCmdDirectCommBase()!=NULL){
		for(DirectCommReceiverList *p=GetRCmdDirectCommBase()->GetLast();p!=NULL;p=p->GetPrev()){
			if(p->Point==PSrc){
				GetRCmdDirectCommBase()->RemoveList(p);
				delete	p;
				Ret=true;
				break;
			}
		}
	}
	GUICmdPacketMutex.unlock();
	return Ret;
}

void	LayersBase::PopupDirectCommPacketPriority(DirectCommPacketBase *PSrc)
{
	GUICmdPacketMutex.lock();
	for(DirectCommReceiverList *p=GetRCmdDirectCommBase()->GetLast();p!=NULL;p=p->GetPrev()){
		if(p->Point==PSrc){
			GetRCmdDirectCommBase()->RemoveList(p);
			GetRCmdDirectCommBase()->AppendList(p);
			break;
		}
	}
	GUICmdPacketMutex.unlock();
}

DirectCommPacketBase *LayersBase::FindDirectCommPacket(int globalPageFrom ,const QString &ClassName)
{
	GUICmdPacketMutex.lock();
	for(DirectCommReceiverList *p=GetRCmdDirectCommBase()->GetLast();p!=NULL;p=p->GetPrev()){
		if(((p->Point->GetGlobalPageFrom()==globalPageFrom) || (p->Point->GetGlobalPageFrom()==-1)) && (p->ClassName==ClassName)){
			GUICmdPacketMutex.unlock();
			return p->Point;
		}
	}
	GUICmdPacketMutex.unlock();
	return NULL;
}

DirectCommPacketBase *LayersBase::FindDirectCommPacket(int globalPageFrom ,const QString &ClassName, QString &emitterRoot, QString &emitterName)
{
	if((emitterRoot=="ANY") && (emitterName=="ANY")){
		GUICmdPacketMutex.lock();
		for(DirectCommReceiverList *p=GetRCmdDirectCommBase()->GetLast();p!=NULL;p=p->GetPrev()){
			if(((p->Point->GetGlobalPageFrom()==globalPageFrom) || (p->Point->GetGlobalPageFrom()==-1)) && (p->ClassName==ClassName)){
				GUICmdPacketMutex.unlock();
				emitterRoot	=p->EmitterRoot;
				emitterName	=p->EmitterName;
				return p->Point;
			}
		}
	}
	else{
		GUICmdPacketMutex.lock();
		for(DirectCommReceiverList *p=GetRCmdDirectCommBase()->GetLast();p!=NULL;p=p->GetPrev()){
			if(((p->Point->GetGlobalPageFrom()==globalPageFrom) || (p->Point->GetGlobalPageFrom()==-1)) 
			&& (((p->EmitterRoot==emitterRoot) && (p->EmitterName==emitterName))) && (p->ClassName==ClassName) ){
				GUICmdPacketMutex.unlock();
				emitterRoot	=p->EmitterRoot;
				emitterName	=p->EmitterName;
				return p->Point;
			}
		}
	}
	GUICmdPacketMutex.unlock();
	return NULL;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------
void	LayersBase::AppendIntegrationPacket(IntegrationCmdPacketBase *PSrc ,const QString &emitterRoot ,const QString &emitterName ,const QString &className)
{
{
	CmdIntegrationPacketMutex.lock();
	GetRIntegrationCmdBase()->AppendList(new ReceiverList(emitterRoot,emitterName ,className,PSrc));
	CmdIntegrationPacketMutex.unlock();
}
}
bool	LayersBase::RemoveIntegrationPacket(IntegrationCmdPacketBase *PSrc)
{
	bool	Ret=false;
	CmdIntegrationPacketMutex.lock();
	if(GetRIntegrationCmdBase()!=NULL){
		for(ReceiverList *p=GetRIntegrationCmdBase()->GetLast();p!=NULL;p=p->GetPrev()){
			if(p->IntegrationPoint==PSrc){
				GetRIntegrationCmdBase()->RemoveList(p);
				delete	p;
				Ret=true;
				break;
			}
		}
	}
	CmdIntegrationPacketMutex.unlock();
	return Ret;
}

void	LayersBase::PopupIntegrationPacketPriority(IntegrationCmdPacketBase *PSrc)
{
	CmdIntegrationPacketMutex.lock();
	for(ReceiverList *p=GetRIntegrationCmdBase()->GetLast();p!=NULL;p=p->GetPrev()){
		if(p->IntegrationPoint==PSrc){
			GetRIntegrationCmdBase()->RemoveList(p);
			GetRIntegrationCmdBase()->AppendList(p);
			break;
		}
	}
	CmdIntegrationPacketMutex.unlock();
}

IntegrationCmdPacketBase *LayersBase::FindIntegrationPacket(int slaveNo ,const QString &ClassName)
{
	CmdIntegrationPacketMutex.lock();
	for(ReceiverList *p=GetRIntegrationCmdBase()->GetLast();p!=NULL;p=p->GetPrev()){
		if(((p->IntegrationPoint->GetSlaveNo()==slaveNo) || (p->IntegrationPoint->GetSlaveNo()==-1)) && (p->ClassName==ClassName)){
			CmdIntegrationPacketMutex.unlock();
			return p->IntegrationPoint;
		}
	}
	CmdIntegrationPacketMutex.unlock();
	return NULL;
}

IntegrationCmdPacketBase *LayersBase::FindIntegrationPacket(int slaveNo ,const QString &ClassName, QString &emitterRoot, QString &emitterName)
{
	if((emitterRoot=="ANY") && (emitterName=="ANY")){
		CmdIntegrationPacketMutex.lock();
		for(ReceiverList *p=GetRIntegrationCmdBase()->GetLast();p!=NULL;p=p->GetPrev()){
			if(((p->IntegrationPoint->GetSlaveNo()==slaveNo) || (p->IntegrationPoint->GetSlaveNo()==-1)) && (p->ClassName==ClassName)){
				CmdIntegrationPacketMutex.unlock();
				emitterRoot	=p->EmitterRoot;
				emitterName	=p->EmitterName;
				return p->IntegrationPoint;
			}
		}
	}
	else{
		CmdIntegrationPacketMutex.lock();
		for(ReceiverList *p=GetRIntegrationCmdBase()->GetLast();p!=NULL;p=p->GetPrev()){
			if(((p->IntegrationPoint->GetSlaveNo()==slaveNo) || (p->IntegrationPoint->GetSlaveNo()==-1)) 
			&& (((p->EmitterRoot==emitterRoot) && (p->EmitterName==emitterName))) && (p->ClassName==ClassName) ){
				CmdIntegrationPacketMutex.unlock();
				emitterRoot	=p->EmitterRoot;
				emitterName	=p->EmitterName;
				return p->IntegrationPoint;
			}
		}
	}
	CmdIntegrationPacketMutex.unlock();
	return NULL;
}
void	LayersBase::AddIntegrationError(ErrorCodeList *e ,int slaveNo)
{
	ErrorMutex.lock();
	e->SetPage(slaveNo);
	GetErrorContainer()->AppendList(e);
	ErrorMutex.unlock();
	if(GetParamGlobal()->ErrorLogFile.isEmpty()==false){
		QFile	FL(GetParamGlobal()->ErrorLogFile);
		if(FL.open(QIODevice::Append | QIODevice::Text)==true){
			QTextStream	TxtStr(&FL);
			e->OutputStr(TxtStr);
			TxtStr<<QString("\n");
		}
	}
}
bool	LayersBase::GetIntegrationSendingData(int slaveNo)
{	
	if(IntegrationSendingData==NULL)
		return false;
	return IntegrationSendingData[slaveNo];
}
void	LayersBase::SetIntegrationSendingData(int slaveNo ,bool d)
{	
	if(IntegrationSendingData!=NULL){
		IntegrationSendingData[slaveNo]=d;
	}
}
bool	LayersBase::HasReceivedIntegrationAck(int slaveNo)
{
	const	QString	ClassName=typeid(IntegrationAck).name();
	for(ReceiverList *p=GetRIntegrationCmdBase()->GetLast();p!=NULL;p=p->GetPrev()){
		if(((p->IntegrationPoint->GetSlaveNo()==slaveNo) || (p->IntegrationPoint->GetSlaveNo()==-1)) && (p->ClassName==ClassName)){
			return p->IntegrationPoint->IsReceived();
		}
	}
	return true;
}
