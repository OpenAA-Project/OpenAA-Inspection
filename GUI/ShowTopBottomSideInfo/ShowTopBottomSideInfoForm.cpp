#include "ShowTopBottomSideInfoResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowTopBottomSideInfo\ShowTopBottomSideInfoForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "ShowMasterNamesFormResource.h"
#include "ShowTopBottomSideInfoForm.h"
#include "XFormOperator.h"
#include "XLotInformation.h"

ShowTopBottomSideInfoForm::ShowTopBottomSideInfoForm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);

	ShowMasterID	=true;
	ShowMasterName	=true;
	ShowLotID		=true;
	ShowLotName		=true;
	ShowWorkerID	=true;
	ShowWorkerName	=true;

	TitleMasterID	=ui.labelHeadMasterID	->text();
	TitleMasterName	=ui.labelHeadMasterName	->text();
	TitleLotID		=ui.labelHeadLotID		->text();
	TitleLotName	=ui.labelHeadLotName	->text();
	TitleWorkerID	=ui.labelHeadWorkerID	->text();
	TitleWorkerName	=ui.labelHeadWorkerName	->text();
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowTopBottomSideInfoForm::~ShowTopBottomSideInfoForm()
{

}

void	ShowTopBottomSideInfoForm::Prepare(void)
{
	int	TopY=0;

	int	X1	=ui.labelHeadMasterID->width();
	int	W	=(width()-ui.labelHeadMasterID->width())/2-1;
	int	X2	=ui.labelHeadMasterID->width() + (width()-ui.labelHeadMasterID->width())/2+1;

	if(ShowMasterID==true){
		ui.labelHeadMasterID->setVisible(true);
		ui.labelHeadMasterID->move(0,TopY);

		ui.labelMasterIDTop		->setVisible(true);
		ui.labelMasterIDTop		->move(X1,TopY);
		ui.labelMasterIDTop		->resize(W,ui.labelMasterIDTop->height());

		ui.labelMasterIDBottom	->setVisible(true);
		ui.labelMasterIDBottom	->move(X2,TopY);
		ui.labelMasterIDBottom	->resize(W,ui.labelMasterIDBottom->height());

		TopY+=ui.labelMasterIDTop->height()+2;
	}
	else{
		ui.labelHeadMasterID	->setVisible(false);
		ui.labelMasterIDTop		->setVisible(false);
		ui.labelMasterIDBottom	->setVisible(false);
	}
	if(ShowMasterName==true){
		ui.labelHeadMasterName	->setVisible(true);
		ui.labelHeadMasterName	->move(0,TopY);

		ui.labelMasterNameTop	->setVisible(true);
		ui.labelMasterNameTop	->move(X1,TopY);
		ui.labelMasterNameTop	->resize(W,ui.labelMasterNameTop->height());

		ui.labelMasterNameBottom->setVisible(true);
		ui.labelMasterNameBottom->move(X2,TopY);
		ui.labelMasterNameBottom->resize(W,ui.labelMasterNameBottom->height());

		TopY+=ui.labelMasterNameTop->height()+2;
	}
	else{
		ui.labelHeadMasterName	->setVisible(false);
		ui.labelMasterNameTop	->setVisible(false);
		ui.labelMasterNameBottom->setVisible(false);
	}
	if(ShowLotID==true){
		ui.labelHeadLotID		->setVisible(true);
		ui.labelHeadLotID		->move(0,TopY);

		ui.labelLotIDTop		->setVisible(true);
		ui.labelLotIDTop		->move(X1,TopY);
		ui.labelLotIDTop		->resize(W,ui.labelLotIDTop->height());

		ui.labelLotIDBottom		->setVisible(true);
		ui.labelLotIDBottom		->move(X2,TopY);
		ui.labelLotIDBottom		->resize(W,ui.labelLotIDBottom->height());

		TopY+=ui.labelLotIDTop->height()+2;
	}
	else{
		ui.labelHeadLotID		->setVisible(false);
		ui.labelLotIDTop		->setVisible(false);
		ui.labelLotIDBottom		->setVisible(false);
	}
	if(ShowLotName==true){
		ui.labelHeadLotName		->setVisible(true);
		ui.labelHeadLotName		->move(0,TopY);

		ui.labelLotNameTop		->setVisible(true);
		ui.labelLotNameTop		->move(X1,TopY);
		ui.labelLotNameTop		->resize(W,ui.labelLotNameTop->height());

		ui.labelLotNameBottom	->setVisible(true);
		ui.labelLotNameBottom	->move(X2,TopY);
		ui.labelLotNameBottom	->resize(W,ui.labelLotNameBottom->height());

		TopY+=ui.labelLotNameTop->height()+2;
	}
	else{
		ui.labelHeadLotName		->setVisible(false);
		ui.labelLotNameTop		->setVisible(false);
		ui.labelLotNameBottom	->setVisible(false);
	}
	if(ShowWorkerID==true){
		ui.labelHeadWorkerID	->setVisible(true);
		ui.labelHeadWorkerID	->move(0,TopY);

		ui.labelWorkerID		->setVisible(true);
		ui.labelWorkerID		->move(X1,TopY);
		ui.labelWorkerID		->resize(W,ui.labelWorkerID->height());

		TopY+=ui.labelWorkerID->height()+2;
	}
	else{
		ui.labelHeadWorkerID	->setVisible(false);
		ui.labelWorkerID		->setVisible(false);
	}
	if(ShowWorkerName==true){
		ui.labelHeadWorkerName	->setVisible(true);
		ui.labelHeadWorkerName	->move(0,TopY);

		ui.labelWorkerName		->setVisible(true);
		ui.labelWorkerName		->move(ui.labelHeadWorkerName->width(),TopY);
		ui.labelWorkerName		->resize(width()-ui.labelHeadWorkerName->width()-1,ui.labelWorkerName->height());
		TopY+=ui.labelWorkerName->height()+2;
	}
	else{
		ui.labelHeadWorkerName	->setVisible(false);
		ui.labelWorkerName		->setVisible(false);
	}
	ui.labelHeadMasterID	->setText(TitleMasterID);
	ui.labelHeadMasterName	->setText(TitleMasterName);
	ui.labelHeadLotID		->setText(TitleLotID);
	ui.labelHeadLotName		->setText(TitleLotName);
	ui.labelHeadWorkerID	->setText(TitleWorkerID);
	ui.labelHeadWorkerName	->setText(TitleWorkerName);
}

void	ShowTopBottomSideInfoForm::ResizeAction()
{
	Prepare();
}

void	ShowTopBottomSideInfoForm::BuildForShow(void)
{
	PageDataInOnePhase	*SecondPhase=NULL;
	int32	BottomMachineID;
	QString	BottomMasterName;
	QString BottomRemark;
	QString BottomLotID;
	QString BottomLotName;
	QString BottomLotRemark;

	if(GetLayersBase()->GetPhaseNumb()>=2){
		SecondPhase=GetLayersBase()->GetPageDataPhase(1);
		if(SecondPhase!=NULL){
			SecondPhase->GetMasterInfo(BottomMachineID,BottomMasterName,BottomRemark);
			SecondPhase->GetLotInfo(BottomLotID,BottomLotName,BottomLotRemark);
		}
	}

	if(ShowMasterID==true){
		ui.labelMasterIDTop		->setText(QString::number(GetLayersBase()->GetMasterCode()));
		if(SecondPhase!=NULL){
			ui.labelMasterIDBottom	->setText(QString::number(SecondPhase->GetMasterCode()));
		}
	}
	if(ShowMasterName==true){
		ui.labelMasterNameTop	->setText(GetLayersBase()->GetMasterName());
		if(SecondPhase!=NULL){
			ui.labelMasterNameBottom->setText(BottomMasterName);
		}
	}
	if(ShowLotID==true){
		ui.labelLotIDTop		->setText(GetLayersBase()->GetLotBase()->GetLotID());
		if(SecondPhase!=NULL){
			ui.labelLotIDBottom		->setText(BottomLotID);
		}
	}
	if(ShowLotName==true){
		ui.labelLotNameTop		->setText(GetLayersBase()->GetLotBase()->GetLotName());
		if(SecondPhase!=NULL){
			ui.labelLotNameBottom	->setText(BottomLotName);
		}
	}
	if(ShowWorkerID==true){
		ui.labelWorkerID		->setText(QString::number(GetLayersBase()->GetWorkerID()));
	}
	if(ShowWorkerName==true){
		ui.labelWorkerName	->setText(GetLayersBase()->GetWorkerName());
	}
}
