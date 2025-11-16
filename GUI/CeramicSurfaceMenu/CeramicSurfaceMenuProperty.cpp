#include "CeramicSurfaceMenuResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CeramicSurfaceMenu\CeramicSurfaceMenuProperty.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "CeramicSurfaceMenuProperty.h"
#include "XSequenceLocal.h"
#include "XExecuteInspect.h"
#include "XGeneralFunc.h"
#include "XAnyData.h"
#include "XHalconInspection.h"

extern	char	*sRoot;
extern	char	*sName;

CeramicSurfaceMenuProperty::CeramicSurfaceMenuProperty(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent),ToolButtonTarget(false),InspectButton(Base ,this)
{
	ui.setupUi(this);

	BlickTimer.setInterval(300);
	BlickTimer.setSingleShot(false);
	BlickTimer.start();
	ExecuteType=_None;

	NormalColor		=Qt::gray;
	WaitingColor	=Qt::green;
	ScanningColor	=Qt::red;
	DoneColor		=Qt::yellow;
	BlinkingMode	=false;
	connect(&BlickTimer,SIGNAL(timeout()),this,SLOT(SlotBlickTimer()));

	ChangeButtonType(&ToolButtonTarget,ui.toolButtonScanTarget);
	connect(&ToolButtonTarget,SIGNAL(clicked()),this,SLOT(on_toolButtonScanTarget_clicked()));

	ToolButtonTarget.setAutoExclusive(false);

	InspectButton.setParent(this);
	InspectButton.setVisible(false);
	InspectButton.disconnect();

	CurrentMasterCounter=0;
}

CeramicSurfaceMenuProperty::~CeramicSurfaceMenuProperty()
{
}

void	CeramicSurfaceMenuProperty::ChangeButtonType(mtToolButtonColored *Dest ,QToolButton *Src)
{
	Dest->setParent(this);
	Dest->setText(Src->text());
	Dest->setGeometry(Src->geometry());
	Dest->setAutoExclusive(Src->autoExclusive());
	Dest->setCheckable(Src->isCheckable());
	delete	Src;
	Src=NULL;
}

void	CeramicSurfaceMenuProperty::Prepare(void)
{
	ToolButtonTarget		.setFont (CFont);
	ui.pushButtonDetail		->setFont (CFont);
	ui.pushButtonClose		->setFont (CFont);
}

void	CeramicSurfaceMenuProperty::BuildForShow(void)
{
	HalconInspectionBase	*PBase=(HalconInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"HalconInspection");
}

void	CeramicSurfaceMenuProperty::SlotBlickTimer()
{
	static	bool	ReEntrant=false;
	static	bool	FirstTime=true;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	if(FirstTime==true){
		BuildForShow();
	}
	FirstTime=false;

	if(GetLayersBase()==NULL || GetLayersBase()->GetEntryPoint()==NULL || GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL){
		ReEntrant=false;
		return;
	}
	SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
	if(ExecuteType==_None){
		SetButtonColor(&ToolButtonTarget	,NormalColor);
	}
	else if(ExecuteType==_OnTargetScanning){
		if(BlinkingMode==false){
			SetButtonColor(&ToolButtonTarget	,ScanningColor);
			BlinkingMode=true;
		}
		else{
			SetButtonColor(&ToolButtonTarget	,WaitingColor);
			BlinkingMode=false;
		}
		if(Param!=NULL && Param->StartInspection==false){
			ExecuteType=_AfterTargetScanning;
			ToolButtonTarget.setChecked(false);
		}
	}
	else if(ExecuteType==_AfterTargetScanning){
		if(BlinkingMode==false){
			SetButtonColor(&ToolButtonTarget	,DoneColor);
			BlinkingMode=true;
		}
		else{
			SetButtonColor(&ToolButtonTarget	,NormalColor);
			BlinkingMode=true;
		}
	}
	ReEntrant=false;
}

void	CeramicSurfaceMenuProperty::SetButtonColor(mtToolButtonColored *Btn ,QColor &Col)
{
	/*
	QPalette P=palette();
	P.setColor(QPalette::Button,Col);
	Btn->setPalette(P);
	Btn->repaint();
	*/
	Btn->setColor(Col);
}

void CeramicSurfaceMenuProperty::on_toolButtonScanTarget_clicked()
{
	if(ToolButtonTarget.isChecked()==true){
		ExecuteType=_OnTargetScanning;
		InspectButton.SlotToggled (true);
	}
	else{
		ExecuteType=_None;
	}
}

void CeramicSurfaceMenuProperty::on_pushButtonDetail_clicked()
{
	GetLayersBase()->GetEntryPoint()->ShowOtherGUI(this,/**/"/Regulus64v5/InspectionPlayerCeramicSurfaceDetail.gui",GetLayersBase());
}

void CeramicSurfaceMenuProperty::on_pushButtonClose_clicked()
{
	GetLayersBase()->CloseAll();
	QCoreApplication::quit();
}

//============================================================================================================================
bool	GUICmdReqExecuteInitialAfterEdit::Load(QIODevice *f)
{	
	if(::Load(f,CurrentMasterCounter)==false)
		return false;
	return true;	
}
bool	GUICmdReqExecuteInitialAfterEdit::Save(QIODevice *f)
{	
	if(::Save(f,CurrentMasterCounter)==false)
		return false;
	return true;	
}

void	GUICmdReqExecuteInitialAfterEdit::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetAnyData()->Set(LangSolver.GetString(CeramicSurfaceMenuProperty_LS,LID_0)/*"CurrentMasterCounter"*/,CurrentMasterCounter);
	GetLayersBase()->ExecuteInitialAfterEdit	(GetLayersBase()->GetEntryPoint());

	GUICmdSendExecuteInitialAfterEdit	*SendBack=GetSendBack(GUICmdSendExecuteInitialAfterEdit,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}
