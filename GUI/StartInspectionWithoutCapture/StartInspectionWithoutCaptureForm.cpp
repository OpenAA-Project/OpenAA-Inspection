#include "StartInspectionWithoutCaptureResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartInspectionWithoutCapture\StartInspectionWithoutCapture.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "StartInspectionButtonFormResource.h"
#include "StartInspectionWithoutCapture.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "swap.h"
#include "XLotInformation.h"
#include "XDateTime.h"
#include "XResult.h"
#include "XSyncGUI.h"
#include <QMessageBox>
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==================================================================================================
StartInspectionWithoutCapture::StartInspectionWithoutCapture(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	SyncMode		=false;
	Button.setParent(this);
	Button.move(0,0);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.setObjectName(/**/"StartInspectionWithoutCapture");
	NormalColor=Qt::lightGray;
	PushedColor=Qt::red;
	CheckExecuteInNoMaster	=false;
	Calculating				=false;

	Msg=/**/"Inspect without capture";
	WaitingMilisecForSlave=5000;
	resize(60,25);
//	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(this,SIGNAL(SignalSync(bool)), this ,SLOT(SlotToggled(bool)),Qt::QueuedConnection);

	SetKeyGrab(true);
	Started=false;
	IsNecessaryLot=true;
	GetParamGUI()->SetParam(&IsNecessaryLot, /**/"StartInspectionWithoutCapture",/**/"IsNecessaryLot"	
												,LangSolver.GetString(StartInspectionWithoutCaptureForm_LS,LID_0)/*"True if lot-id is necessary"*/	);
}

StartInspectionWithoutCapture::~StartInspectionWithoutCapture(void)
{
}

void	StartInspectionWithoutCapture::Prepare(void)
{
	Button.setText(Msg);
	Button.setColor(NormalColor);
	Button.setFont (CFont);
	ResizeAction();
}

void	StartInspectionWithoutCapture::ResizeAction()
{
	Button.resize(width(),height());
}

IntList	DbgSlotList;

//void StartInspectionButton::SlotClicked (bool checked)
void	StartInspectionWithoutCapture::SlotToggled (bool checked)
{
	static	bool	ReEntrant=false;
	static	QString	LStr;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	if(checked==true){
		if(CheckExecuteInNoMaster==true){
			if(GetLayersBase()->GetMasterCode()<0){
				if(QMessageBox::warning ( NULL, LangSolver.GetString(StartInspectionWithoutCaptureForm_LS,LID_1)/*"Warning"*/
										, LangSolver.GetString(StartInspectionWithoutCaptureForm_LS,LID_2)/*"Master data is not loaded"*/
										,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No){
					Button.setChecked(false);
					ReEntrant=false;
					return;
				}
			}
		}
		if(Started==true){
			ReEntrant=false;
			return;
		}
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==true){
			if(GetLayersBase()->GetLotBase()->GetLotID()==/**/"-1" || GetLayersBase()->GetLotBase()->GetLotID().isEmpty()==true){
				if(IsNecessaryLot==true){
					QMessageBox::warning ( NULL, LangSolver.GetString(StartInspectionWithoutCaptureForm_LS,LID_3)/*"Warning"*/
												, LangSolver.GetString(StartInspectionWithoutCaptureForm_LS,LID_4)/*"Lot information is necessary"*/);
					Button.setChecked(false);
					ReEntrant=false;
					return;
				}
			}

			if(GetParamGlobal()->ViewProcessingWindow==true){
				GetLayersBase()->ShowProcessingForm (LangSolver.GetString(StartInspectionWithoutCaptureForm_LS,LID_5)/*"Start inspection"*/);
				GetLayersBase()->AddMaxProcessing(-1,0);
			}
			Button.setColor(PushedColor);
			//GetLayersBase()->ExecuteStartByInspection(GetLayersBase()->GetEntryPoint());
			//GetLayersBase()->GetInspectionData()->GetExecuteInspect()->StartAllCamera();
			SeqControlParam	*Param=NULL;
			if(GetLayersBase()->GetEntryPoint()!=NULL && GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
				if(Param!=NULL){
					Param->CaptureMode=4;
					Param->StartInspection=true;
				}
			}

			if(GetParamGlobal()->GetMaxScanStrategy()<=1 || (GetLayersBase()->GetCurrentStrategicNumberForSeq()==0)){
				GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
				GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());
			}

			GUICmdStartInspectWithoutCapture	*Cmd[1000];
			GUICmdReplyInspectWithoutCapture	*Reply[1000];
			Started=true;
			StrategicListContainer SList;
			int	CStrategic=max(GetLayersBase()->GetCurrentStrategicNumber(),GetLayersBase()->GetCurrentStrategicNumberForSeq());
			GetParamGlobal()->GetStrategy(CStrategic,SList);

			XDateTime	ResTime=GetLayersBase()->GetStartInspectTime();
			ResultInspection	*Res=GetLayersBase()->GetNextResultForCalc();
			if(Res!=NULL){
				Res->SetStartTimeForInspect(ResTime);
			}
			LStr=ResTime.toString(/**/"yy/MM/dd hh:mm:ss");

			int	N=0;
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				int page=s->Page;
				Cmd[N]	=new GUICmdStartInspectWithoutCapture(GetLayersBase(),sRoot,sName,page);
				Cmd[N]->StartInspectionTime	=ResTime;
				Cmd[N]->CurrentInspectID	=GetLayersBase()->GetCurrentInspectIDForExecute();
				Cmd[N]->Layer				=s->Layer;
				Cmd[N]->StrategicNumber		=GetLayersBase()->GetCurrentStrategicNumberForSeq();
				Reply[N]	=new GUICmdReplyInspectWithoutCapture(GetLayersBase(),sRoot,sName,page);
			}
			DWORD	LastTime=GetComputerMiliSec();
			bool	ReadyAll;
			for(int i=0;i<N;i++){
				Cmd[i]->Send(Cmd[i]->GetGlobalPage() ,0,*Reply[i]);
			}
			do{
				ReadyAll=true;
				for(int i=0;i<N;i++){
					if(Reply[i]->IsReceived()==false){
						ReadyAll=false;
					}
				}
				if(GetComputerMiliSec()-LastTime>WaitingMilisecForSlave){
					break;
				}
			}while(ReadyAll==false);
			if(ReadyAll==false){
				for(int i=0;i<N;i++){
					if(Reply[i]->IsReceived()==false){
						Cmd[i]->Send(Cmd[i]->GetGlobalPage() ,0,*Reply[i]);
					}
				}
				do{
					ReadyAll=true;
					for(int i=0;i<N;i++){
						if(Reply[i]->IsReceived()==false){
							ReadyAll=false;
						}
					}
					if(GetComputerMiliSec()-LastTime){
						break;
					}
				}while(ReadyAll==false);
			}
			
			if(Param!=NULL){
				Param->InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
				Param->ReadyForScan=true;
			}

			if((GetParamGlobal()->DebugLevel & 0x04)!=0){
				DbgSlotList.Add(CStrategic);
			}

			for(int i=0;i<N;i++){
				delete	Cmd[i]	;
				delete	Reply[i];
			}
			if(GetLayersBase()->GetEntryPoint()!=NULL && GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()!=ExecuteInspectBase::_CaptureInspectWithoutCapture){
					GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoInspectWithoutCapture();
				}
			}

			if(Param!=NULL){
				while(Param->PermitCapture==false){
					if(GetLayersBase()->GetOnTerminating()==true){
						ReEntrant=false;
						return;
					}
					//SeqControlParamData->CaptureMode=3;
					GSleep(10);
					QCoreApplication::processEvents();
					if(Button.isChecked()==false){
						Button.setColor(NormalColor);
						ReEntrant=false;
						return;
					}
				}
			}
		}
		if(SyncMode==false){
			if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				TxSync(Buff.buffer());
			}
		}
	}
	SyncMode=false;
	ReEntrant=false;
}
void	StartInspectionWithoutCapture::ShowInPlayer(int64 shownInspectionID)
{
	Calculating=false;
}
void	StartInspectionWithoutCapture::CommandStart(void)
{
	Calculating=true;
	Button.setChecked(true);
	//SlotToggled (true);
	while(Calculating==true){
		QCoreApplication::processEvents();
	}
}
void StartInspectionWithoutCapture::keyPressEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_F9){
		//SlotClicked(true);
		Button.setChecked(true);
		event->accept();
	}
	else{
		GUIFormBase::keyPressEvent ( event );
	}
}
bool StartInspectionWithoutCapture::OnIdle(void)
{
	GUIFormBase::OnIdle();
	
	if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
		ExecuteInspectBase	*EBase=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(EBase!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)EBase->GetSeqParam();
			if(Started==true){
				if(Param->StartInspection==false){
					//Button.setChecked(true);
					//Param->StartInspection=false;
					Button.setColor(NormalColor);
					Button.setChecked(false);
					Started=false;
				}
				if(EBase->GetHaltMode()==true){
					//Button.setChecked(true);
					//Param->StartInspection=false;
					Button.setColor(NormalColor);
					Button.setChecked(false);
					Started=false;
					GetLayersBase()->CloseProcessingForm();
					GSleep(500);
					EBase->ClearHaltMode();
				}
			}
			else if(EBase->GetMode()==ExecuteInspectBase::_CaptureNone
			&& Param->ExecuteInspection==true && Param->PermitCapture==true){
			//&& Param->ExecuteInspection==true){
				Param->ExecuteInspection=false;
				Button.setChecked(true);
				SlotToggled (true);
			}
		}
	}
	return true;
}

void	StartInspectionWithoutCapture::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetStateStartInspectionWithoutCapture *CmdGetStateStartInspectionWithoutCaptureVar=dynamic_cast<CmdGetStateStartInspectionWithoutCapture *>(packet);
	if(CmdGetStateStartInspectionWithoutCaptureVar!=NULL){
		if(Button.isChecked()==true){
			CmdGetStateStartInspectionWithoutCaptureVar->StartInspectionOn=true;
		}
		else{
			CmdGetStateStartInspectionWithoutCaptureVar->StartInspectionOn=false;
		}
		return;
	}
}
void	StartInspectionWithoutCapture::RxSync(QByteArray &f)
{
	SyncMode=true;
	Button.setChecked(true);
}

//==================================================================================================

GUICmdStartInspectWithoutCapture::GUICmdStartInspectWithoutCapture(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdStartInspectWithoutCapture::~GUICmdStartInspectWithoutCapture(void)
{
}

bool	GUICmdStartInspectWithoutCapture::Load(QIODevice *f)
{
	if(::Load(f,StartInspectionTime)==false)
		return false;
	if(::Load(f,CurrentInspectID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,StrategicNumber)==false)
		return false;
	return true;
}
bool	GUICmdStartInspectWithoutCapture::Save(QIODevice *f)
{
	if(::Save(f,StartInspectionTime)==false)
		return false;
	if(::Save(f,CurrentInspectID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,StrategicNumber)==false)
		return false;
	return true;
}

void	GUICmdStartInspectWithoutCapture::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1 || StrategicNumber==0){
		GetLayersBase()->SetStartInspectTime(StartInspectionTime);
		GetLayersBase()->SetCurrentInspectID(CurrentInspectID);
	}
	if(GetParamComm()->Mastered==false){
		GetLayersBase()->SetCurrentStrategicNumber		(StrategicNumber);
		GetLayersBase()->SetCurrentStrategicNumberForSeq(StrategicNumber);
	}
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoInspectWithoutCapture();
	}
	//}
	
	GUICmdReplyInspectWithoutCapture	*SendBack=GetSendBack(GUICmdReplyInspectWithoutCapture,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdReplyInspectWithoutCapture::GUICmdReplyInspectWithoutCapture(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdReplyInspectWithoutCapture::~GUICmdReplyInspectWithoutCapture(void)
{
}

bool	GUICmdReplyInspectWithoutCapture::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReplyInspectWithoutCapture::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReplyInspectWithoutCapture::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

