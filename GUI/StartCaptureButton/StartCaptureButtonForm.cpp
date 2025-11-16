#include "startcapturebuttonResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartCaptureButton\StartCaptureButtonForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StartCaptureButton.h"
#include "XPushCmdPacket.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XSyncGUI.h"
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

StartCaptureButton::StartCaptureButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(false)
{
	SyncMode		=false;
	Button.setParent(this);
	Button.move(0,0);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	NormalColor=Qt::lightGray;
	PushedColor=Qt::red;
	Calculating				=false;

	Msg=/**/"Start";
	ImageType=/**/"Master";
	resize(40,25);
	//connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	SetKeyGrab(true);
	ClickOn=0;
}

StartCaptureButton::~StartCaptureButton(void)
{
}

void	StartCaptureButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setColor(NormalColor);
	Button.setFont (CFont);
	ResizeAction();
}

void	StartCaptureButton::ResizeAction()
{
	Button.resize(width(),height());
}

IntList	HDbgSlotList;

//void	StartCaptureButton::SlotClicked (bool checked)
void	StartCaptureButton::SlotToggled (bool checked)
{
	if(checked==true){
		Button.setColor(PushedColor);
		SeqControlParam	*Param=NULL;
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StartAllCamera();
			Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				Param->CaptureMode=2;
			}
		}
	
		int	CStrategic=max(GetLayersBase()->GetCurrentStrategicNumber(),GetLayersBase()->GetCurrentStrategicNumberForSeq());
		IntList		SList;
		//GetParamGlobal()->GetStrategy(CStrategic,SList);
		GetParamGlobal()->GetStrategyPage (CStrategic ,SList);
		if(GetParamGlobal()->GetMaxScanStrategy()<=1 || CStrategic==0){
			GetLayersBase()->ExecuteStartByScanOnly(GetLayersBase()->GetEntryPoint());
		}

		if((GetParamGlobal()->DebugLevel & 0x04)!=0){
			HDbgSlotList.Add(CStrategic);
		}

		GUICmdPushedStartCapture		*Cmd[100];
		GUICmdRepliedPushStartCapture	*Reply[100];
		/*
		for(int page=0;page<GetPageNumb();page++){
			Cmd[page]	=new GUICmdPushedStartCapture(GetLayersBase(),sRoot,sName,page);
			Cmd[page]->ImageType=ImageType;
			Cmd[page]->StrategicNumber		=CStrategic;
			Reply[page]	=new GUICmdRepliedPushStartCapture(GetLayersBase(),sRoot,sName,page);
		}
		for(int page=0;page<GetPageNumb();page++){
			Cmd[page]->Send(page ,0,*Reply[page]);
		}
		bool	ReadyAll;
		do{
			ReadyAll=true;
			for(int page=0;page<GetPageNumb();page++){
				if(Reply[page]->IsReceived()==false){
					ReadyAll=false;
				}
			}
		}while(ReadyAll==false);
		*/
		int	N=0;
		for(IntClass *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
			int page=s->GetValue();
			Cmd[N]	=new GUICmdPushedStartCapture(GetLayersBase(),sRoot,sName,page);
			Cmd[N]->ImageType=ImageType;
			Cmd[N]->StrategicNumber		=CStrategic;
			Reply[N]	=new GUICmdRepliedPushStartCapture(GetLayersBase(),sRoot,sName,page);
		}
		for(int i=0;i<N;i++){
			Cmd[i]->Send(Cmd[i]->GetGlobalPage() ,0,*Reply[i]);
		}
		bool	ReadyAll;
		do{
			ReadyAll=true;
			for(int i=0;i<N;i++){
				if(Reply[i]->IsReceived()==false){
					ReadyAll=false;
				}
			}
		}while(ReadyAll==false);

		if(Param!=NULL)
			Param->ReadyForScan=true;

		for(int i=0;i<N;i++){
			delete	Cmd[i]	;
			delete	Reply[i];
		}
		Button.setColor(NormalColor);
		Button.setChecked(false);

		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()!=ExecuteInspectBase::_CaptureOnlyMaster){
				GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoMasterCaptureOnly();
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
}

void StartCaptureButton::keyPressEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_F5){
		//SlotClicked(true);
		Button.setChecked(true);
		event->accept();
	}
	else{
		GUIFormBase::keyPressEvent ( event );
	}
}
void	StartCaptureButton::ShowInPlayer(int64 shownInspectionID)
{
	Calculating=false;
}
void	StartCaptureButton::CommandStart(void)
{
	Calculating=true;
	SlotToggled (true);

	while(Calculating==true){
		QCoreApplication::processEvents();
	}
}

IntList	HDbgScanMaster;

bool StartCaptureButton::OnIdle(void)
{
	if(GetLayersBase()==NULL || GetLayersBase()->GetEntryPoint()==NULL || GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL)
		return true;
	SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
	if(Param->StartScanOnly==true){
		//SlotClicked (true);
		//Button.setChecked(true);
		//Param->StartScanOnly=false;
	}
	if(Param->ExecuteScanMaster==true){
		ClickOn++;
		if((GetParamGlobal()->DebugLevel & 0x04)!=0){
			HDbgScanMaster.Add(ClickOn);
		}
		Param->ExecuteScanMaster=false;
	}
	if(ClickOn!=0 
	&& (GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()==ExecuteInspectBase::_EI_IDLE)){
		SlotToggled (true);
		ClickOn--;
	}
	return true;
}
void	StartCaptureButton::RxSync(QByteArray &f)
{
	SyncMode=true;
	SlotToggled(true);
	SyncMode=false;
}