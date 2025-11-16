/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartInspectionButton\StartInspectionButtonForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "StartInspectionButtonFormResource.h"
#include "StartInspectionButton.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "swap.h"
#include "XLotInformation.h"
#include "XDateTime.h"
#include <QMessageBox>
#include "XLogOut.h"
#include "XResult.h"
#include "XSyncGUI.h"
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==================================================================================================
StartInspectionButton::StartInspectionButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	SyncMode		=false;
	Button.setParent(this);
	Button.move(0,0);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.setObjectName(/**/"ButtonStartInspection");
	NormalColor=Qt::lightGray;
	PushedColor=Qt::red;
	CheckExecuteInNoMaster	=false;
	Calculating				=false;
	Started=false;
	IsNecessaryLot=true;
	StartCount	=0;
	ExecutedCount=0;
	IdleLoopCounter=0;
	UseRetry	=false;
	iFlagSet		=NULL;
	RegNoInFlagSet	=-1;

	Msg=/**/"Inspect";
	WaitingMilisecForSlave=5000;
	resize(60,25);
//	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(this,SIGNAL(SignalSync(bool)), this ,SLOT(SlotToggled(bool)),Qt::QueuedConnection);

	SetKeyGrab(true);

	GetParamGUI()->SetParam(&IsNecessaryLot, /**/"StartInspectionButton",/**/"IsNecessaryLot"	
												,LangSolver.GetString(StartInspectionButtonForm_LS,LID_0)/*"True if lot-id is necessary"*/		);
	GetParamGUI()->SetParam(&UseRetry, /**/"StartInspectionButton",/**/"UseRetry"	
												,"Use retry function"	);
}

StartInspectionButton::~StartInspectionButton(void)
{
}

void	StartInspectionButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setColor(NormalColor);
	Button.setFont (CFont);
	ResizeAction();

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& RegNoInFlagSet>=0
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iFlagSet	=new SignalOperandBit(this,RegNoInFlagSet,/**/"StartInspectionButton:iFlagSet");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iFlagSet,&Error)==false){
				iFlagSet->ShowErrorMessage(Error);
			}

			iFlagSet->Set(Started);
		}
	}

}

void	StartInspectionButton::ResizeAction()
{
	Button.resize(width(),height());
}

IntList	DbgSlotList;

//void StartInspectionButton::SlotClicked (bool checked)
void	StartInspectionButton::SlotToggled (bool checked)
{
	static	bool	ReEntrant=false;
	static	QString	LStr;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	if(checked==true){
		GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"StartInspectionButton:Enter");
		if(CheckExecuteInNoMaster==true){
			if(GetLayersBase()->GetMasterCode()<0){
				if(QMessageBox::warning ( NULL
										, LangSolver.GetString(StartInspectionButtonForm_LS,LID_3)/*"Warning"*/
										, LangSolver.GetString(StartInspectionButtonForm_LS,LID_4)/*"?}?X?^?[?f?[?^?d?o?^?E?C?Y?o??E??E?A????U?1?n?a?A????C?????d?s????U??E?c?H"*/
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
					QMessageBox::warning ( NULL, LangSolver.GetString(StartInspectionButtonForm_LS,LID_1)/*"Warning"*/
												, LangSolver.GetString(StartInspectionButtonForm_LS,LID_2)/*"???b?g?d?Y?e??E?A?-???3???"*/);
					Button.setChecked(false);
					ReEntrant=false;
					return;
				}
			}

			if(GetParamGlobal()->ViewProcessingWindow==true){
				GetLayersBase()->ShowProcessingForm (LangSolver.GetString(StartInspectionButtonForm_LS,LID_5)/*"Start inspection"*/);
				GetLayersBase()->AddMaxProcessing(-1,0);
			}
			Button.setColor(PushedColor);
			//GetLayersBase()->ExecuteStartByInspection(GetLayersBase()->GetEntryPoint());
			//GetLayersBase()->GetInspectionData()->GetExecuteInspect()->StartAllCamera();
			SeqControlParam	*Param=NULL;
			ExecuteInspectBase	*EBase=NULL;
			if(GetLayersBase()->GetEntryPoint()!=NULL && GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				EBase=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
			}
			if(EBase!=NULL){
				Param=(SeqControlParam *)EBase->GetSeqParam();
				if(Param!=NULL){
					Param->CaptureMode=3;
					Param->StartInspection=true;
				}
			}

			if(GetParamGlobal()->GetMaxScanStrategy()<=1 || (GetLayersBase()->GetCurrentStrategicNumberForSeq()==0)){
				GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
				GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());
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

			GUICmdStartInspect	*Cmd[1000];
			GUICmdReplyInspect	*Reply[1000];
			Started=true;
			if(iFlagSet!=NULL){
				iFlagSet->Set(Started);
			}
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
				Cmd[N]	=new GUICmdStartInspect(GetLayersBase(),sRoot,sName,page);
				Cmd[N]->StartInspectionTime	=ResTime;
				Cmd[N]->CurrentInspectID	=GetLayersBase()->GetCurrentInspectIDForExecute();
				Cmd[N]->Layer				=s->Layer;
				Cmd[N]->StrategicNumber		=GetLayersBase()->GetCurrentStrategicNumberForSeq();
				Reply[N]	=new GUICmdReplyInspect(GetLayersBase(),sRoot,sName,page);
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
				if(GetLayersBase()->GetOnTerminating()==true){
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
					if(GetLayersBase()->GetOnTerminating()==true){
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
			if(EBase->GetMode()!=ExecuteInspectBase::_CaptureInspect){
				EBase->GoInspect();
				ExecutedCount++;
				IdleLoopCounter=EBase->GetIdleLoopCounter();
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
void	StartInspectionButton::ShowInPlayer(int64 shownInspectionID)
{
	Calculating=false;
}
void	StartInspectionButton::CommandStart(void)
{
	Calculating=true;
	Button.setChecked(true);
	//SlotToggled (true);
	while(Calculating==true){
		if(GetLayersBase()->GetOnTerminating()==true)
			break;
		QCoreApplication::processEvents();
	}
}
void StartInspectionButton::keyPressEvent ( QKeyEvent * event )
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
bool StartInspectionButton::OnIdle(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;

	ReEntrant=true;
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
					if(iFlagSet!=NULL){
						iFlagSet->Set(Started);
					}
				}
				else if(UseRetry==true){
					if(Started==true && EBase->GetMode()==ExecuteInspectBase::_CaptureNone
					&& EBase->GetIdleLoopCounter()-IdleLoopCounter>3){
						GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"StartInspectionButton:GoInspect");
						EBase->GoInspect();
						ExecutedCount++;
						IdleLoopCounter=EBase->GetIdleLoopCounter();
					}
				}
				if(EBase->GetHaltMode()==true){
					//Button.setChecked(true);
					//Param->StartInspection=false;
					Button.setColor(NormalColor);
					Button.setChecked(false);
					Started=false;
					if(iFlagSet!=NULL){
						iFlagSet->Set(Started);
					}
					GetLayersBase()->CloseProcessingForm();
					GSleep(500);
					EBase->ClearHaltMode();
				}
			}
			else if(EBase->GetMode()==ExecuteInspectBase::_CaptureNone
			//&& Param->ExecuteInspection==true && Param->PermitCapture==true){
			&& Param->ExecuteInspection==true
			&& Started==false){
				Param->ExecuteInspection=false;
				Button.setChecked(true);
				GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"StartInspectionButton:OnIdle");
				//SlotToggled (true);
				while(EBase->GetMode()==ExecuteInspectBase::_CaptureNone){
					if(GetLayersBase()->GetOnTerminating()==true)
						break;
					QApplication::processEvents();
				}
				StartCount++;
			}
		}
	}
	ReEntrant=false;
	return true;
}

void	StartInspectionButton::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetStateStartInspection *CmdGetStateStartInspectionVar=dynamic_cast<CmdGetStateStartInspection *>(packet);
	if(CmdGetStateStartInspectionVar!=NULL){
		if(Button.isChecked()==true){
			CmdGetStateStartInspectionVar->StartInspectionOn=true;
		}
		else{
			CmdGetStateStartInspectionVar->StartInspectionOn=false;
		}
		return;
	}
	CmdGoStateStartInspection	*CmdGoStateStartInspectionVar=dynamic_cast<CmdGoStateStartInspection *>(packet);
	if(CmdGoStateStartInspectionVar!=NULL){
		Button.setChecked(true);
		//SlotToggled(true);
		return;
	}
}
void	StartInspectionButton::RxSync(QByteArray &f)
{
	SyncMode=true;
	Button.setChecked(true);
}

//==================================================================================================

GUICmdStartInspect::GUICmdStartInspect(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdStartInspect::~GUICmdStartInspect(void)
{
}

bool	GUICmdStartInspect::Load(QIODevice *f)
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
bool	GUICmdStartInspect::Save(QIODevice *f)
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

void	GUICmdStartInspect::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoInspect();
		GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,/**/"");
		if(f!=NULL){
			StartInspectionButton	*g=dynamic_cast<StartInspectionButton *>(f);
			if(g!=NULL){
				g->ExecutedCount++;
				g->IdleLoopCounter=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetIdleLoopCounter();
			}
		}
	}
	//}
	
	GUICmdReplyInspect	*SendBack=GetSendBack(GUICmdReplyInspect,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdReplyInspect::GUICmdReplyInspect(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdReplyInspect::~GUICmdReplyInspect(void)
{
}

bool	GUICmdReplyInspect::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReplyInspect::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReplyInspect::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

