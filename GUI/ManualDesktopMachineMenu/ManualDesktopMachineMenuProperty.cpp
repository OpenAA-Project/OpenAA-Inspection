#include "ManualDesktopMachineMenuResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ManualDesktopMachineMenu\ManualDesktopMachineMenuProperty.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DesktopMachineMenuProperty.h"
#include "XSequenceLocal.h"
#include "XExecuteInspect.h"
#include "NextMasterForm.h"
#include "XGeneralFunc.h"
#include "XAnyData.h"
#include "XPixelInspection.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

DesktopMachineMenuProperty::DesktopMachineMenuProperty(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
	,MasterButton(Base,this)
	,InspectButton(Base ,this)
	,ToolButtonMaster(false)
	,ToolButtonTarget(false)
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

	ChangeButtonType(&ToolButtonMaster,ui.toolButtonScanMaster);
	connect(&ToolButtonMaster,SIGNAL(clicked()),this,SLOT(on_toolButtonScanMaster_clicked()));
	ChangeButtonType(&ToolButtonTarget,ui.toolButtonScanTarget);
	connect(&ToolButtonTarget,SIGNAL(clicked()),this,SLOT(on_toolButtonScanTarget_clicked()));

	ToolButtonTarget.setAutoExclusive(false);

	MasterButton.setParent(this);
	MasterButton.setVisible(false);
	MasterButton.disconnect();

	InspectButton.setParent(this);
	InspectButton.setVisible(false);
	InspectButton.disconnect();

	CurrentMasterCounter=0;
}

DesktopMachineMenuProperty::~DesktopMachineMenuProperty()
{
}

void	DesktopMachineMenuProperty::ChangeButtonType(mtToolButtonColored *Dest ,QToolButton *Src)
{
	Dest->setParent(this);
	Dest->setText(Src->text());
	Dest->setGeometry(Src->geometry());
	Dest->setAutoExclusive(Src->autoExclusive());
	Dest->setCheckable(Src->isCheckable());
	delete	Src;
	Src=NULL;
}

void	DesktopMachineMenuProperty::Prepare(void)
{
	ToolButtonMaster		.setFont (CFont);
	ToolButtonTarget		.setFont (CFont);
	ui.pushButtonDetail		->setFont (CFont);
	ui.pushButtonClose		->setFont (CFont);
	ui.labelCounter1		->setFont (CFont);
	ui.labelCurrentCount	->setFont (CFont);
	ui.labelQuality			->setFont (CFont);
	ui.spinBoxQuality		->setFont (CFont);
}

void	DesktopMachineMenuProperty::BuildForShow(void)
{
	PixelInspectionBase	*PBase=(PixelInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PixelInspection");
	ui.horizontalSliderQuality	->setValue(PBase->getInspectionLevel());
	ui.spinBoxQuality			->setValue(PBase->getInspectionLevel());
}

void	DesktopMachineMenuProperty::SlotBlickTimer()
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
		SetButtonColor(&ToolButtonMaster	,NormalColor);
		SetButtonColor(&ToolButtonTarget	,NormalColor);
	}
	else if(ExecuteType==_OnMasterScanning1){
		if(BlinkingMode==false){
			SetButtonColor(&ToolButtonMaster	,ScanningColor);
			BlinkingMode=true;
		}
		else{
			SetButtonColor(&ToolButtonMaster	,WaitingColor);
			BlinkingMode=false;
		}
		SetButtonColor(&ToolButtonTarget		,NormalColor);
		if(Param!=NULL && Param->StartScanOnly==true){
			ExecuteType=_OnMasterScanning2;
		}
	}
	else if(ExecuteType==_OnMasterScanning2){
		if(BlinkingMode==false){
			SetButtonColor(&ToolButtonMaster	,ScanningColor);
			BlinkingMode=true;
		}
		else{
			SetButtonColor(&ToolButtonMaster	,WaitingColor);
			BlinkingMode=false;
		}
		SetButtonColor(&ToolButtonTarget		,NormalColor);

		if(Param!=NULL && Param->StartScanOnly==false && CurrentMasterCounter>1){
			CurrentMasterCounter++;
			ui.labelCurrentCount->setText(QString::number(CurrentMasterCounter));
		}
		else{
			ExecuteType=_AfterMasterScanning;
			GetLayersBase()->GetAnyData()->Set(/**/"CurrentMasterCounter",CurrentMasterCounter);
			ToolButtonMaster.setChecked(false);
		}

/*		if(Param!=NULL && Param->StartScanOnly==false){
			NPListPack<GUICmdPacketDim>	GUICmdDim;
			GUICmdReqExecuteInitialAfterEdit	*CmdReq[100];
			GUICmdSendExecuteInitialAfterEdit	*CmdSend[100];
			for(int page=0;page<GetPageNumb();page++){
				CmdReq [page]=new GUICmdReqExecuteInitialAfterEdit (GetLayersBase(),sRoot,sName,page);
				CmdReq [page]->CurrentMasterCounter=CurrentMasterCounter;
				CmdSend[page]=new GUICmdSendExecuteInitialAfterEdit(GetLayersBase(),sRoot,sName,page);
				GUICmdDim.AppendList(new GUICmdPacketDim(CmdReq[page],CmdSend[page],page,0));
			}
			GetLayersBase()->PacketSender(GUICmdDim);

			NextMasterForm	DUp;
			if(((bool)DUp.exec())==true){
				CurrentMasterCounter++;
				ui.labelCurrentCount->setText(QString::number(CurrentMasterCounter));
				ExecuteType=_OnMasterScanning1;
				MasterButton.ImageType="Target";
				MasterButton.SlotToggled (true);
				ExecuteType=_OnMasterScanning1;
			}
			else{
				GetLayersBase()->ShowProcessingForm ();
				NPListPack<GUICmdPacketDim>	GUICmdDimFin;
				GUICmdReqExecuteInitialAfterEdit	*CmdReqFin[100];
				GUICmdSendExecuteInitialAfterEdit	*CmdSendFin[100];
				for(int page=0;page<GetPageNumb();page++){
					CmdReqFin [page]=new GUICmdReqExecuteInitialAfterEdit (GetLayersBase(),sRoot,sName,page);
					CmdReqFin [page]->CurrentMasterCounter=99999999;
					CmdSendFin[page]=new GUICmdSendExecuteInitialAfterEdit(GetLayersBase(),sRoot,sName,page);
					GUICmdDimFin.AppendList(new GUICmdPacketDim(CmdReqFin[page],CmdSendFin[page],page,0));
				}
				GetLayersBase()->PacketSender(GUICmdDimFin,GetParamGlobal()->MaxWaitingCommMilisec);
				ExecuteType=_AfterMasterScanning;
				GetLayersBase()->GetAnyData()->Set("CurrentMasterCounter",CurrentMasterCounter);
				CurrentMasterCounter++;
				ui.labelCurrentCount->setText(QString::number(CurrentMasterCounter));
				GetLayersBase()->CloseProcessingForm();
			}
		}
*/
	}
	else if(ExecuteType==_AfterMasterScanning){
		SetButtonColor(&ToolButtonMaster		,DoneColor	);
		SetButtonColor(&ToolButtonTarget		,NormalColor);
	}
	else if(ExecuteType==_OnTargetScanning){
		SetButtonColor(&ToolButtonMaster		,NormalColor);
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
		SetButtonColor(&ToolButtonMaster		,NormalColor);
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

void	DesktopMachineMenuProperty::SetButtonColor(mtToolButtonColored *Btn ,QColor &Col)
{
	/*
	QPalette P=palette();
	P.setColor(QPalette::Button,Col);
	Btn->setPalette(P);
	Btn->repaint();
	*/
	Btn->setColor(Col);
}


void DesktopMachineMenuProperty::on_toolButtonScanMaster_clicked()
{
	if(ToolButtonMaster.isChecked()==true){
		if(CurrentMasterCounter==0){
			CurrentMasterCounter++;
			ui.labelCurrentCount->setText(QString::number(CurrentMasterCounter));
			ExecuteType=_OnMasterScanning1;
			MasterButton.ImageType=/**/"Master";
			MasterButton.SlotToggled (true);
		}
		else{
			CurrentMasterCounter++;
			ui.labelCurrentCount->setText(QString::number(CurrentMasterCounter));
			ExecuteType=_OnMasterScanning2;
			MasterButton.ImageType=/**/"Master";
			MasterButton.SlotToggled (true);
		}
	}
	else{
		ExecuteType=_None;
	}
}

void DesktopMachineMenuProperty::on_toolButtonScanTarget_clicked()
{
	if(ToolButtonTarget.isChecked()==true){
		ExecuteType=_OnTargetScanning;
		InspectButton.SlotToggled (true);
	}
	else{
		ExecuteType=_None;
	}
}

void DesktopMachineMenuProperty::on_pushButtonDetail_clicked()
{
	QString CurrentPath=GetLayersBase()->GetUserPath();
	CurrentPath+=QDir::separator()+QString(/**/"InspectionPlayerDesktopDetailManual.gui");
	GetLayersBase()->GetEntryPoint()->ShowOtherGUI(this,CurrentPath,GetLayersBase());
}

void DesktopMachineMenuProperty::on_pushButtonClose_clicked()
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
	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->GetAnyData()->Set(/**/"CurrentMasterCounter",CurrentMasterCounter);
	GetLayersBase()->ExecuteInitialAfterEdit	(EInfo);

	GUICmdSendExecuteInitialAfterEdit	*SendBack=GetSendBack(GUICmdSendExecuteInitialAfterEdit,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}


void DesktopMachineMenuProperty::on_horizontalSliderQuality_valueChanged(int)
{
	PixelInspectionBase	*PBase=(PixelInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PixelInspection");
	PBase->setInspectionLevel(ui.horizontalSliderQuality	->value());
	ui.spinBoxQuality->setValue(PBase->getInspectionLevel());
}

void DesktopMachineMenuProperty::on_spinBoxQuality_valueChanged(int)
{
	PixelInspectionBase	*PBase=(PixelInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PixelInspection");
	PBase->setInspectionLevel(ui.spinBoxQuality->value());
	ui.horizontalSliderQuality	->setValue(PBase->getInspectionLevel());
}