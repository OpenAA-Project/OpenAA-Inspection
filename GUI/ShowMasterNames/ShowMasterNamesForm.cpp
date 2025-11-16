/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowMasterNames\ShowMasterNamesForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowMasterNamesFormResource.h"
#include "ShowMasterNamesForm.h"
#include "XLotInformation.h"
#include "swap.h"

ShowMasterNamesForm::ShowMasterNamesForm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

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

ShowMasterNamesForm::~ShowMasterNamesForm()
{

}

void	ShowMasterNamesForm::Prepare(void)
{
	QFontInfo	TitleFontInfo(TitleFont);
	QFontInfo	DataFontInfo(DataFont);
	int	YLen=max(TitleFontInfo.pixelSize(),DataFontInfo.pixelSize());
	YLen+=4;
	QFontMetrics	FontM(TitleFont);
	int	TitleWidth=0;
	if(ShowMasterID==true){
		TitleWidth=max(max(TitleWidth,FontM.boundingRect(TitleMasterID).width()),ui.labelHeadMasterID->width());
	}
	if(ShowMasterName==true){
		TitleWidth=max(max(TitleWidth,FontM.boundingRect(TitleMasterName).width()),ui.labelHeadMasterName->width());
	}
	if(ShowLotID==true){
		TitleWidth=max(max(TitleWidth,FontM.boundingRect(TitleLotID).width()),ui.labelHeadLotID->width());
	}
	if(ShowLotName==true){
		TitleWidth=max(max(TitleWidth,FontM.boundingRect(TitleLotName).width()),ui.labelHeadLotName->width());
	}
	if(ShowWorkerID==true){
		TitleWidth=max(max(TitleWidth,FontM.boundingRect(TitleWorkerID).width()),ui.labelHeadWorkerID->width());
	}
	if(ShowWorkerName==true){
		TitleWidth=max(max(TitleWidth,FontM.boundingRect(TitleWorkerName).width()),ui.labelHeadWorkerName->width());
	}

	int	TopY=0;
	if(ShowMasterID==true){
		ui.labelHeadMasterID->setFont(TitleFont);
		ui.labelMasterID	->setFont(DataFont);
		ui.labelHeadMasterID->setVisible(true);
		ui.labelMasterID	->setVisible(true);
		ui.labelHeadMasterID->move(0,TopY);
		ui.labelMasterID	->move(TitleWidth,TopY);
		ui.labelHeadMasterID->resize(TitleWidth,YLen);
		ui.labelMasterID	->resize(width()-TitleWidth-1,YLen);
		TopY+=YLen+2;
	}
	else{
		ui.labelHeadMasterID->setVisible(false);
		ui.labelMasterID	->setVisible(false);
	}
	if(ShowMasterName==true){
		ui.labelHeadMasterName	->setFont(TitleFont);
		ui.labelMasterName		->setFont(DataFont);
		ui.labelHeadMasterName	->setVisible(true);
		ui.labelMasterName		->setVisible(true);
		ui.labelHeadMasterName	->move(0,TopY);
		ui.labelMasterName		->move(TitleWidth,TopY);
		ui.labelHeadMasterName	->resize(TitleWidth,YLen);
		ui.labelMasterName		->resize(width()-TitleWidth-1,YLen);
		TopY+=YLen+2;
	}
	else{
		ui.labelHeadMasterName	->setVisible(false);
		ui.labelMasterName		->setVisible(false);
	}
	if(ShowLotID==true){
		ui.labelHeadLotID	->setFont(TitleFont);
		ui.labelLotID		->setFont(DataFont);
		ui.labelHeadLotID	->setVisible(true);
		ui.labelLotID		->setVisible(true);
		ui.labelHeadLotID	->move(0,TopY);
		ui.labelLotID		->move(TitleWidth,TopY);
		ui.labelHeadLotID	->resize(TitleWidth,YLen);
		ui.labelLotID		->resize(width()-TitleWidth-1,YLen);
		TopY+=YLen+2;
	}
	else{
		ui.labelHeadLotID	->setVisible(false);
		ui.labelLotID		->setVisible(false);
	}
	if(ShowLotName==true){
		ui.labelHeadLotName	->setFont(TitleFont);
		ui.labelLotName		->setFont(DataFont);
		ui.labelHeadLotName	->setVisible(true);
		ui.labelLotName		->setVisible(true);
		ui.labelHeadLotName	->move(0,TopY);
		ui.labelLotName		->move(TitleWidth,TopY);
		ui.labelHeadLotName	->resize(TitleWidth,YLen);
		ui.labelLotName		->resize(width()-TitleWidth-1,YLen);
		TopY+=YLen+2;
	}
	else{
		ui.labelHeadLotName		->setVisible(false);
		ui.labelLotName			->setVisible(false);
	}
	if(ShowWorkerID==true){
		ui.labelHeadWorkerID	->setFont(TitleFont);
		ui.labelWorkerID		->setFont(DataFont);
		ui.labelHeadWorkerID	->setVisible(true);
		ui.labelWorkerID		->setVisible(true);
		ui.labelHeadWorkerID	->move(0,TopY);
		ui.labelWorkerID		->move(TitleWidth,TopY);
		ui.labelHeadWorkerID	->resize(TitleWidth,YLen);
		ui.labelWorkerID		->resize(width()-TitleWidth-1,YLen);
		TopY+=YLen+2;
	}
	else{
		ui.labelHeadWorkerID	->setVisible(false);
		ui.labelWorkerID		->setVisible(false);
	}
	if(ShowWorkerName==true){
		ui.labelHeadWorkerName	->setFont(TitleFont);
		ui.labelWorkerName		->setFont(DataFont);
		ui.labelHeadWorkerName	->setVisible(true);
		ui.labelWorkerName		->setVisible(true);
		ui.labelHeadWorkerName	->move(0,TopY);
		ui.labelWorkerName		->move(TitleWidth,TopY);
		ui.labelHeadWorkerName	->resize(TitleWidth,YLen);
		ui.labelWorkerName		->resize(width()-TitleWidth-1,YLen);
		TopY+=YLen+2;
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

void	ShowMasterNamesForm::ResizeAction()
{
	Prepare();
}

void	ShowMasterNamesForm::BuildForShow(void)
{
	if(ShowMasterID==true){
		ui.labelMasterID	->setText(QString::number(GetLayersBase()->GetMasterCode()));
	}
	if(ShowMasterName==true){
		ui.labelMasterName	->setText(GetLayersBase()->GetMasterName());
	}
	if(ShowLotID==true){
		ui.labelLotID	->setText(GetLayersBase()->GetLotBase()->GetLotID());
	}
	if(ShowLotName==true){
		ui.labelLotName	->setText(GetLayersBase()->GetLotBase()->GetLotName());
	}
	if(ShowWorkerID==true){
		ui.labelWorkerID	->setText(QString::number(GetLayersBase()->GetWorkerID()));
	}
	if(ShowWorkerName==true){
		ui.labelWorkerName	->setText(GetLayersBase()->GetWorkerName());
	}
}
