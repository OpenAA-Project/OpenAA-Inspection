/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\SignalResultDoneToMaster\SignalResultDoneToMaster.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "SignalResultDoneToMaster.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationComm.h"
#include "ThreadSequence.h"
#include "XCriticalFunc.h"
#include "XSequenceLocal.h"
#include "XWriteResultThread.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"SignalResultDoneToMaster";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Signal Resul tDone to Master");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new CmdReqSignalResultDoneToMaster	(Base,sRoot,sName);
	(*Base)	=new CmdSignalResultDoneToMaster	(Base,sRoot,sName);
	(*Base)	=new CmdSignalScanningDoneToMaster	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SignalResultDoneToMaster(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((SignalResultDoneToMaster *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((SignalResultDoneToMaster *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"NormalColor";
	Data[2].Pointer				 =&((SignalResultDoneToMaster *)Instance)->NormalColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"PushedColor";
	Data[3].Pointer				 =&((SignalResultDoneToMaster *)Instance)->PushedColor;	
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((SignalResultDoneToMaster *)Instance)->CFont;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"SpoolingMilisec";
	Data[5].Pointer				 =&((SignalResultDoneToMaster *)Instance)->SpoolingMilisec;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"RefreshCycleMilisec";
	Data[6].Pointer				 =&((SignalResultDoneToMaster *)Instance)->RefreshCycleMilisec;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SignalResultDoneToMaster.png")));
}

//==================================================================================================================
SignalResultDoneToMaster::SignalResultDoneToMaster(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Send";
	SpoolingMilisec		=1000;
	RefreshCycleMilisec	=300;
	ResultButtPointW	=0;
	ReEntrant			=false;
	MaxSignalCountForResult	=20;

	CharColor	=Qt::white;
	NormalColor	=Qt::gray;
	PushedColor	=Qt::yellow;

	resize(80,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	GetParamGUI()->SetParam(&MaxSignalCountForResult, /**/"SignalResultDoneToMaster",/**/"MaxSignalCountForResult"	
										,"Max signal count for result");

	Timer.setParent(this);
	Timer.setSingleShot(false);
	connect(&Timer,SIGNAL(timeout()),this,SLOT(SlotTimeOutInMaster()));
}

void	SignalResultDoneToMaster::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();


	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL){
		if(IBase->GetParamIntegrationMaster()->Mastered==true
		&& GetLayersBase()->GetShadowLevel()==0){
			Timer.setInterval(RefreshCycleMilisec);
			Timer.start();
			int	N=IBase->GetIntegrationSlaveCount();
			for(int slave=0;slave<N;slave++){
				ReqCommand[slave]=new CmdReqSignalResultDoneToMaster(GetLayersBase(),sRoot,sName,slave);
				AckCommand[slave]=new CmdSignalResultDoneToMaster(GetLayersBase(),sRoot,sName,slave);
			}
		}
	}
}
void	SignalResultDoneToMaster::ResizeAction()
{
	Button.resize(width(),height());
}

void	SignalResultDoneToMaster::SlotClicked()
{
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL){
		if(IBase->GetParamIntegrationMaster()->Mastered==false){
			//int	OwnSlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->OwnSlaveNo;
			//CmdSignalResultDoneToMaster		RCmd(GetLayersBase(),sRoot,sName,OwnSlaveNo);
			//RCmd.InspectionID	=GetLayersBase()->GetCurrentInspectIDForDisplay();
			//RCmd.SendFromSlaveToMaster(OwnSlaveNo ,0);
			PushResultDone(true,GetLayersBase()->GetCurrentInspectIDForDisplay());
		}
	}
}

void	SignalResultDoneToMaster::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSignalResultDoneToMaster	*CmdSignalResultDoneToMasterVar=dynamic_cast<CmdSignalResultDoneToMaster *>(packet);
	if(CmdSignalResultDoneToMasterVar!=NULL){
		CmdSignalResultDoneToMasterVar->ResultDoneInfo.ResultCount=0;
		MutexResultBuff.lock();
		if(ResultButtPointW>0
		&& (GetParamGlobal()->UseSystemResultStocker==false 
		 || GetLayersBase()->GetStockedSystemResult()>0)){
			for(int i=0;i<SignalResultCommandCount && i<ResultButtPointW;i++){
				CmdSignalResultDoneToMasterVar->ResultDoneInfo.InspectionID [CmdSignalResultDoneToMasterVar->ResultDoneInfo.ResultCount]=ResultBuff[i];
				CmdSignalResultDoneToMasterVar->ResultDoneInfo.OK			[CmdSignalResultDoneToMasterVar->ResultDoneInfo.ResultCount]=ResultOKBuff[i];
				CmdSignalResultDoneToMasterVar->ResultDoneInfo.ResultCount++;
			}

			CmdSignalResultDoneToMasterVar->ResultDoneInfo.UseSystemResultStocker=GetParamGlobal()->UseSystemResultStocker;
			if(CmdSignalResultDoneToMasterVar->ResultDoneInfo.UseSystemResultStocker==true){
				SystemResult	*SystemResultDim[1000];
				int				SystemResultNumb=0;
				for(;;){
					SystemResult	*s=GetLayersBase()->PopSystemResult();
					if(s==NULL){
						break;
					}
					if(SystemResultNumb<1000){
						SystemResultDim	 [SystemResultNumb]=s;
						SystemResultNumb++;
					}
					else{
						break;
					}
				}

				QBuffer	Buff;
				Buff.open(QIODevice::WriteOnly);
				::Save(&Buff,SystemResultNumb);
				for(int i=0;i<SystemResultNumb && i<1000;i++){;
					::Save(&Buff,SystemResultDim[i]->Result);
				}
				CmdSignalResultDoneToMasterVar->SystemResultData=Buff.buffer();
			}

			ResultButtPointW-=CmdSignalResultDoneToMasterVar->ResultDoneInfo.ResultCount;
		}
		MutexResultBuff.unlock();
		return;
	}
}

void	SignalResultDoneToMaster::RunByEveryInspection(int64 shownInspectionID)
{
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL){
		if(IBase->HasLocalCamera()==true){
			ResultInspection	*R=GetLayersBase()->GetResultThread()->GetBufferedResult(shownInspectionID);
			if(R!=NULL){
				//int	OwnSlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->OwnSlaveNo;
				//CmdSignalResultDoneToMaster		RCmd(GetLayersBase(),sRoot,sName,OwnSlaveNo);
				//RCmd.InspectionID	=shownInspectionID;
				bool3	ShadowOk;
				bool	ShadowTimeOver;
				bool	ShadowMaxError;
				bool	ResultOK;
				GetLayersBase()->GetShadowResult(R
								,ShadowOk ,ShadowTimeOver, ShadowMaxError
								,true,false);
				if(ShadowOk==true3 && R->IsResultOK()==true){
					ResultOK=true;
				}
				else{
					ResultOK=false;
				}
				//RCmd.OK=ResultOK;
				//RCmd.SendFromSlaveToMaster(OwnSlaveNo ,0);
				PushResultDone(ResultOK,shownInspectionID);
			}
		}
	}
}

void	SignalResultDoneToMaster::ShowInScanning(int64 shownInspectionID)
{
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL){
		if(IBase->HasLocalCamera()==true){
			ResultInspection	*R=GetLayersBase()->GetResultThread()->GetBufferedResult(shownInspectionID);
			if(R!=NULL){
				//int	OwnSlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->OwnSlaveNo;
				//CmdSignalScanningDoneToMaster		RCmd(GetLayersBase(),sRoot,sName,OwnSlaveNo);
				//RCmd.InspectionID	=shownInspectionID;	
				//RCmd.SendFromSlaveToMaster(OwnSlaveNo ,0);
				PushResultDone(true,shownInspectionID);
			}
		}
	}
}
void	SignalResultDoneToMaster::BroadcastInspectionDone(int SlaveNo,int64 InspectionID ,bool OK)
{
	for(int i=0;i<100;i++){
		if(SignalRingBuffer[i].Alive==false){
			SignalRingBuffer[i].InspectionID=InspectionID;
			SignalRingBuffer[i].SlaveNo		=SlaveNo;
			SignalRingBuffer[i].OK			=OK;
			SignalRingBuffer[i].StartTime	=::GetComputerMiliSec();
			SignalRingBuffer[i].Alive		=true;
			break;
		}
	}
}
void	SignalResultDoneToMaster::BroadcastScanningDone(int SlaveNo,int64 InspectionID)
{
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL){
		IBase->BroadcastScanningDone(SlaveNo,InspectionID);
	}
}

bool SignalResultDoneToMaster::OnIdle(void)
{
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL){
		DWORD	PresentTime	=::GetComputerMiliSec();
		for(int i=0;i<100;i++){
			if(SignalRingBuffer[i].Alive==true){
				if(PresentTime-SignalRingBuffer[i].StartTime>=SpoolingMilisec){
					IBase->BroadcastInspectionDone(SignalRingBuffer[i].SlaveNo
												,SignalRingBuffer[i].InspectionID
												,SignalRingBuffer[i].OK);
					SignalRingBuffer[i].Alive=false;
					break;
				}
			}
		}
	}
	return true;
}

void	SignalResultDoneToMaster::PushResultDone(bool OK,int64 shownInspectionID)
{
	MutexResultBuff.lock();
	ResultBuff[ResultButtPointW]	=shownInspectionID;
	ResultOKBuff[ResultButtPointW]	=OK;
	ResultButtPointW++;
	if(ResultButtPointW>=sizeof(SignalRingBuffer)/sizeof(SignalRingBuffer[0]))
		ResultButtPointW=0;
	MutexResultBuff.unlock();
}

int	DbgError=0;
void	SignalResultDoneToMaster::SlotTimeOutInMaster()
{
	if(ReEntrant==true)
		return;

	ReEntrant=true;
	IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	if(IBase!=NULL){
		int	N=IBase->GetIntegrationSlaveCount();
		if(N!=1){
			DbgError++;
		}
		for(int slave=0;slave<N;slave++){
			ReqCommand[slave]->Send(slave,0,*AckCommand[slave],WaitForSignalKnock);
		}
	}
	emit	SignalTimeOutInMaster();
	ReEntrant=false;
}

//============================================================================
	
CmdReqSignalResultDoneToMaster::CmdReqSignalResultDoneToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
void	CmdReqSignalResultDoneToMaster::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdSignalResultDoneToMaster	*SendBack=GetSendBackIntegration(CmdSignalResultDoneToMaster,GetLayersBase(),EmitterRoot,EmitterName,slaveNo);
	SignalResultDoneToMaster	*f=(SignalResultDoneToMaster *)GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/"");
	if(f!=NULL){
		f->TransmitDirectly(SendBack);
	}
	
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(slaveNo),0);
	CloseSendBackIntegration(SendBack);
}


CmdSignalResultDoneToMaster::CmdSignalResultDoneToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	CmdSignalResultDoneToMaster::Load(QIODevice *f)
{
	if(f->read((char *)&ResultDoneInfo,sizeof(ResultDoneInfo))!=sizeof(ResultDoneInfo))
		return false;
	if(ResultDoneInfo.UseSystemResultStocker==true){
		if(::Load(f,SystemResultData)==false){
			return false;
		}
	}
	return true;
}
bool	CmdSignalResultDoneToMaster::Save(QIODevice *f)
{
	if(f->write((const char *)&ResultDoneInfo,sizeof(ResultDoneInfo))!=sizeof(ResultDoneInfo))
		return false;
	if(ResultDoneInfo.UseSystemResultStocker==true){
		if(::Save(f,SystemResultData)==false){
			return false;
		}
	}
	return true;
}

void	CmdSignalResultDoneToMaster::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetIntegrationBasePointer()->UpdateInspection();
	SignalResultDoneToMaster	*f=(SignalResultDoneToMaster *)GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/"");
	if(f!=NULL){
		if(ResultDoneInfo.ResultCount>0){
			SignalResultDoneToMaster	*f=(SignalResultDoneToMaster *)GetLayersBase()->FindByName(sRoot,sName,/**/"");
			int	MaxSignalCountForResult=f->MaxSignalCountForResult;
			
			if(ResultDoneInfo.UseSystemResultStocker==true){
				EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(slaveNo);
				QBuffer	Buff(&SystemResultData);
				Buff.open(QIODevice::ReadOnly);
				int	SystemResultNumb;
				if(::Load(&Buff,SystemResultNumb)==true){
					for(int i=0;i<SystemResultNumb && i<MaxSignalCountForResult;i++){
						QByteArray	sResult;
						if(::Load(&Buff,sResult)==false){
							break;
						}
						if(m!=NULL){
							m->PushResult(sResult);
						}
					}
				}
			}
			for(int i=0;i<ResultDoneInfo.ResultCount && i<MaxSignalCountForResult;i++){
				f->BroadcastInspectionDone(slaveNo,ResultDoneInfo.InspectionID[i],ResultDoneInfo.OK[i]);
			}
			SystemResultData.clear();
		}
	}
}


//============================================================================

CmdSignalScanningDoneToMaster::CmdSignalScanningDoneToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	CmdSignalScanningDoneToMaster::Load(QIODevice *f)
{
	if(::Load(f,InspectionID)==false)
		return false;
	return true;
}
bool	CmdSignalScanningDoneToMaster::Save(QIODevice *f)
{
	if(::Save(f,InspectionID)==false)
		return false;
	return true;
}

void	CmdSignalScanningDoneToMaster::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetIntegrationBasePointer()->UpdateInspection();
	SignalResultDoneToMaster	*f=(SignalResultDoneToMaster *)GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/"");
	if(f!=NULL){
		f->BroadcastScanningDone(slaveNo,InspectionID);
	}
}


