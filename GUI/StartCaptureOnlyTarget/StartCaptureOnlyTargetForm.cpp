//#include "StartCaptureOnlyTargetResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartCaptureOnlyTarget\StartCaptureOnlyTarget.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "StartInspectionButtonFormResource.h"
#include "StartCaptureOnlyTarget.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "swap.h"
#include "XLotInformation.h"
#include "XDateTime.h"
#include "ButtonAutoMode.h"
#include "XResult.h"
#include "XSyncGUI.h"
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==================================================================================================
StartCaptureOnlyTarget::StartCaptureOnlyTarget(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	SyncMode		=false;
	Button.setParent(this);
	Button.move(0,0);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.setObjectName(/**/"StartCaptureOnlyTarget");
	NormalColor=Qt::lightGray;
	PushedColor=Qt::red;
	Calculating				=false;

	Msg=/**/"Capture target";
	WaitingMilisecForSlave=5000;
	resize(60,25);
//	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(this,SIGNAL(SignalSync(bool)), this ,SLOT(SlotToggled(bool)),Qt::QueuedConnection);

	SetKeyGrab(true);
	Started=false;
	IsNecessaryLot=true;
	GetParamGUI()->SetParam(&IsNecessaryLot, /**/"StartCaptureOnlyTarget",/**/"IsNecessaryLot"	
												,"True if lot-id is necessary"	);
}

StartCaptureOnlyTarget::~StartCaptureOnlyTarget(void)
{
}

void	StartCaptureOnlyTarget::Prepare(void)
{
	Button.setText(Msg);
	Button.setColor(NormalColor);
	Button.setFont (CFont);
	ResizeAction();
}

void	StartCaptureOnlyTarget::ResizeAction()
{
	Button.resize(width(),height());
}

IntList	DbgSlotList;

//void StartInspectionButton::SlotClicked (bool checked)
void	StartCaptureOnlyTarget::SlotToggled (bool checked)
{
	static	bool	ReEntrant=false;
	static	QString	LStr;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	if(checked==true){
		if(Started==true){
			ReEntrant=false;
			return;
		}
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
		if(f!=NULL){
			CmdGetStateOnAutoMode	GACmd(GetLayersBase());
			f->TransmitDirectly(&GACmd);
			if(GACmd.AutoModeOn==true){
				CmdSetStateOnAutoMode	ACmd(GetLayersBase());
				ACmd.AutoModeOn=false;
				f->TransmitDirectly(&ACmd);
				if(GetLayersBase()->GetEntryPoint()!=NULL && GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
					while(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()!=ExecuteInspectBase::_CaptureNone){
						GSleep(100);
					}
				}
			}
		}


		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==true){
			//if(GetLayersBase()->GetLotBase()->GetLotID()==/**/"-1" || GetLayersBase()->GetLotBase()->GetLotID().isEmpty()==true){
			//	if(IsNecessaryLot==true){
			//		QMessageBox::warning ( NULL, "Warning"
			//									, "Lot information is necessary");
			//		Button.setChecked(false);
			//		ReEntrant=false;
			//		return;
			//	}
			//}

			if(GetParamGlobal()->ViewProcessingWindow==true){
				GetLayersBase()->ShowProcessingForm ("Start capture");
				GetLayersBase()->AddMaxProcessing(-1,0);
			}
			Button.setColor(PushedColor);

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

			GUICmdStartCaptureOnlyTarget		*Cmd[1000];
			GUICmdReplyStartCaptureOnlyTarget	*Reply[1000];
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
				Cmd[N]	=new GUICmdStartCaptureOnlyTarget(GetLayersBase(),sRoot,sName,page);
				Cmd[N]->StartInspectionTime	=ResTime;
				Cmd[N]->CurrentInspectID	=GetLayersBase()->GetCurrentInspectIDForExecute();
				Cmd[N]->Layer				=s->Layer;
				Cmd[N]->StrategicNumber		=GetLayersBase()->GetCurrentStrategicNumberForSeq();
				Reply[N]	=new GUICmdReplyStartCaptureOnlyTarget(GetLayersBase(),sRoot,sName,page);
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
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()!=ExecuteInspectBase::_CaptureOnlyTarget){
					GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoTargetCaptureOnly();
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
	else{
		ExecuteInspectBase	*EBase=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(EBase!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)EBase->GetSeqParam();
			if(Started==true){
				EBase->GoHalt();

				Button.setColor(NormalColor);
				Started=false;
				GetLayersBase()->CloseProcessingForm();
				GSleep(500);
			}
		}
	}
	SyncMode=false;
	ReEntrant=false;
}
void	StartCaptureOnlyTarget::ShowInScanning(int64 shownInspectionID)
{
	Calculating=false;
	Started	=false;
	if(Button.isChecked()==true){
		SlotToggled (true);
	}
}
void	StartCaptureOnlyTarget::CommandStart(void)
{
	Calculating=true;
	Button.setChecked(true);
	//SlotToggled (true);
	while(Calculating==true){
		QCoreApplication::processEvents();
	}
}
void StartCaptureOnlyTarget::keyPressEvent ( QKeyEvent * event )
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
bool StartCaptureOnlyTarget::OnIdle(void)
{
	GUIFormBase::OnIdle();
	
	if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
		ExecuteInspectBase	*EBase=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(EBase!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)EBase->GetSeqParam();
			if(Started==true){
				if(EBase->GetHaltMode()==true){
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
				Param->ExecuteInspection=false;
				Button.setChecked(true);
				SlotToggled (true);
			}
		}
	}
	return true;
}

void	StartCaptureOnlyTarget::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetStateStartCaptureOnlyTarget *CmdGetStateStartCaptureOnlyTargetVar=dynamic_cast<CmdGetStateStartCaptureOnlyTarget *>(packet);
	if(CmdGetStateStartCaptureOnlyTargetVar!=NULL){
		if(Button.isChecked()==true){
			CmdGetStateStartCaptureOnlyTargetVar->StartCaptureOnlyTargetOn=true;
		}
		else{
			CmdGetStateStartCaptureOnlyTargetVar->StartCaptureOnlyTargetOn=false;
		}
		return;
	}
	CmdSetStateStartCaptureOnlyTarget *CmdSetStateStartCaptureOnlyTargetVar=dynamic_cast<CmdSetStateStartCaptureOnlyTarget *>(packet);
	if(CmdSetStateStartCaptureOnlyTargetVar!=NULL){
		Button.setChecked(CmdSetStateStartCaptureOnlyTargetVar->StartCaptureOnlyTargetOn);
		SlotToggled (CmdSetStateStartCaptureOnlyTargetVar->StartCaptureOnlyTargetOn);
		return;
	}
}
void	StartCaptureOnlyTarget::RxSync(QByteArray &f)
{
	SyncMode=true;
	Button.setChecked(true);
}

//==================================================================================================

GUICmdStartCaptureOnlyTarget::GUICmdStartCaptureOnlyTarget(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdStartCaptureOnlyTarget::~GUICmdStartCaptureOnlyTarget(void)
{
}

bool	GUICmdStartCaptureOnlyTarget::Load(QIODevice *f)
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
bool	GUICmdStartCaptureOnlyTarget::Save(QIODevice *f)
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

void	GUICmdStartCaptureOnlyTarget::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoTargetCaptureOnly();
	}
	
	GUICmdReplyStartCaptureOnlyTarget	*SendBack=GetSendBack(GUICmdReplyStartCaptureOnlyTarget,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdReplyStartCaptureOnlyTarget::GUICmdReplyStartCaptureOnlyTarget(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdReplyStartCaptureOnlyTarget::~GUICmdReplyStartCaptureOnlyTarget(void)
{
}

bool	GUICmdReplyStartCaptureOnlyTarget::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReplyStartCaptureOnlyTarget::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReplyStartCaptureOnlyTarget::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

