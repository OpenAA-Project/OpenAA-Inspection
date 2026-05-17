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

	ShowHeadMasterID	=true;
	ShowHeadMasterName	=true;
	ShowHeadLotID		=true;
	ShowHeadLotName		=true;
	ShowHeadWorkerID	=true;
	ShowHeadWorkerName	=true;

	AlignAttr				=/**/"AlignLeft";
	TransparentBackColor	=true;
	BorderWidth				=1;
	BorderStyle				=/**/"Solid";

	HeadAlignAttr			=/**/"AlignLeft";
	HeadTransparentBackColor=true;
	HeadBorderWidth			=1;
	HeadBorderStyle			=/**/"Solid";

	HeadWidth	=ui.labelHeadMasterID->width();
}

ShowMasterNamesForm::~ShowMasterNamesForm()
{

}

void	ShowMasterNamesForm::Prepare(void)
{
//	int	TopY=0;
	if(ShowMasterID==true){
		ui.labelMasterID	->setVisible(true);
//		ui.labelHeadMasterID->move(0,TopY);
//		ui.labelMasterID	->move(ui.labelHeadMasterID->width(),TopY);
		ui.labelMasterID	->resize(width()-ui.labelHeadMasterID->width()-1,ui.labelMasterID->height());
//		TopY+=ui.labelMasterID->height()+2;
	}
	else{
		ui.labelMasterID	->setVisible(false);
	}
	if(ShowMasterName==true){
		ui.labelMasterName		->setVisible(true);
//		ui.labelHeadMasterName->move(0,TopY);
//		ui.labelMasterName	->move(ui.labelHeadMasterName->width(),TopY);
		ui.labelMasterName	->resize(width()-ui.labelHeadMasterName->width()-1,ui.labelMasterName->height());
//		TopY+=ui.labelMasterName->height()+2;
	}
	else{
		ui.labelMasterName		->setVisible(false);
	}
	if(ShowLotID==true){
		ui.labelLotID			->setVisible(true);
//		ui.labelHeadLotID->move(0,TopY);
//		ui.labelLotID	->move(ui.labelHeadLotID->width(),TopY);
		ui.labelLotID	->resize(width()-ui.labelHeadLotID->width()-1,ui.labelLotID->height());
//		TopY+=ui.labelLotID->height()+2;
	}
	else{
		ui.labelLotID			->setVisible(false);
	}
	if(ShowLotName==true){
		ui.labelLotName			->setVisible(true);
//		ui.labelHeadLotName->move(0,TopY);
//		ui.labelLotName	->move(ui.labelHeadLotName->width(),TopY);
		ui.labelLotName	->resize(width()-ui.labelHeadLotName->width()-1,ui.labelLotName->height());
//		TopY+=ui.labelLotName->height()+2;
	}
	else{
		ui.labelLotName			->setVisible(false);
	}
	if(ShowWorkerID==true){
		ui.labelWorkerID		->setVisible(true);
//		ui.labelHeadWorkerID->move(0,TopY);
//		ui.labelWorkerID	->move(ui.labelHeadWorkerID->width(),TopY);
		ui.labelWorkerID	->resize(width()-ui.labelHeadWorkerID->width()-1,ui.labelWorkerID->height());
//		TopY+=ui.labelWorkerID->height()+2;
	}
	else{
		ui.labelWorkerID		->setVisible(false);
	}
	if(ShowWorkerName==true){
		ui.labelWorkerName		->setVisible(true);
//		ui.labelHeadWorkerName->move(0,TopY);
//		ui.labelWorkerName	->move(ui.labelHeadWorkerName->width(),TopY);
		ui.labelWorkerName	->resize(width()-ui.labelHeadWorkerName->width()-1,ui.labelWorkerName->height());
//		TopY+=ui.labelWorkerName->height()+2;
	}
	else{
		ui.labelWorkerName		->setVisible(false);
	}
	ui.labelHeadMasterID	->setText(TitleMasterID);
	ui.labelHeadMasterName	->setText(TitleMasterName);
	ui.labelHeadLotID		->setText(TitleLotID);
	ui.labelHeadLotName		->setText(TitleLotName);
	ui.labelHeadWorkerID	->setText(TitleWorkerID);
	ui.labelHeadWorkerName	->setText(TitleWorkerName);

	if(ShowHeadMasterID==true){
		ui.labelHeadMasterID->setVisible(true);
//		ui.labelHeadMasterID->move(0,TopY);
//		ui.labelMasterID	->move(ui.labelHeadMasterID->width(),TopY);
//		ui.labelMasterID	->resize(width()-ui.labelHeadMasterID->width()-1,ui.labelMasterID->height());
//		TopY+=ui.labelMasterID->height()+2;
	}
	else{
		ui.labelHeadMasterID->setVisible(false);
	}
	if(ShowHeadMasterName==true){
		ui.labelHeadMasterName	->setVisible(true);
//		ui.labelHeadMasterName->move(0,TopY);
//		ui.labelMasterName	->move(ui.labelHeadMasterName->width(),TopY);
//		ui.labelMasterName	->resize(width()-ui.labelHeadMasterName->width()-1,ui.labelMasterName->height());
//		TopY+=ui.labelMasterName->height()+2;
	}
	else{
		ui.labelHeadMasterName	->setVisible(false);
	}
	if(ShowHeadLotID==true){
		ui.labelHeadLotID		->setVisible(true);
//		ui.labelHeadLotID->move(0,TopY);
//		ui.labelLotID	->move(ui.labelHeadLotID->width(),TopY);
//		ui.labelLotID	->resize(width()-ui.labelHeadLotID->width()-1,ui.labelLotID->height());
//		TopY+=ui.labelLotID->height()+2;
	}
	else{
		ui.labelHeadLotID		->setVisible(false);
	}
	if(ShowHeadLotName==true){
		ui.labelHeadLotName		->setVisible(true);
//		ui.labelHeadLotName->move(0,TopY);
//		ui.labelLotName	->move(ui.labelHeadLotName->width(),TopY);
//		ui.labelLotName	->resize(width()-ui.labelHeadLotName->width()-1,ui.labelLotName->height());
//		TopY+=ui.labelLotName->height()+2;
	}
	else{
		ui.labelHeadLotName		->setVisible(false);
	}
	if(ShowHeadWorkerID==true){
		ui.labelHeadWorkerID	->setVisible(true);
//		ui.labelHeadWorkerID->move(0,TopY);
//		ui.labelWorkerID	->move(ui.labelHeadWorkerID->width(),TopY);
//		ui.labelWorkerID	->resize(width()-ui.labelHeadWorkerID->width()-1,ui.labelWorkerID->height());
//		TopY+=ui.labelWorkerID->height()+2;
	}
	else{
		ui.labelHeadWorkerID	->setVisible(false);
	}
	if(ShowHeadWorkerName==true){
		ui.labelHeadWorkerName	->setVisible(true);
//		ui.labelHeadWorkerName->move(0,TopY);
//		ui.labelWorkerName	->move(ui.labelHeadWorkerName->width(),TopY);
//		ui.labelWorkerName	->resize(width()-ui.labelHeadWorkerName->width()-1,ui.labelWorkerName->height());
//		TopY+=ui.labelWorkerName->height()+2;
	}
	else{
		ui.labelHeadWorkerName	->setVisible(false);
	}

	//HeadWidth
	ui.labelHeadMasterID	->setMaximumWidth(HeadWidth);
	ui.labelHeadMasterID	->setMinimumWidth(HeadWidth);
	ui.labelHeadMasterName	->setMaximumWidth(HeadWidth);
	ui.labelHeadMasterName	->setMinimumWidth(HeadWidth);
	ui.labelHeadLotID		->setMaximumWidth(HeadWidth);
	ui.labelHeadLotID		->setMinimumWidth(HeadWidth);
	ui.labelHeadLotName		->setMaximumWidth(HeadWidth);
	ui.labelHeadLotName		->setMinimumWidth(HeadWidth);
	ui.labelHeadWorkerID	->setMaximumWidth(HeadWidth);
	ui.labelHeadWorkerID	->setMinimumWidth(HeadWidth);
	ui.labelHeadWorkerName	->setMaximumWidth(HeadWidth);
	ui.labelHeadWorkerName	->setMinimumWidth(HeadWidth);

	//[Style Sheet]
	//Alignment
	if(AlignAttr==/**/"AlignLeft"){
		ui.labelMasterID	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelMasterName	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelLotID		->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelLotName		->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelWorkerID	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelWorkerName	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	}
	else if(AlignAttr==/**/"AlignRight"){
		ui.labelMasterID	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelMasterName	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelLotID		->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelLotName		->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelWorkerID	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelWorkerName	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
	}
	else{
		ui.labelMasterID	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelMasterName	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelLotID		->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelLotName		->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelWorkerID	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelWorkerName	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	}
	//Background
	QString strBackgroundStyleSheet;
	if(TransparentBackColor==true){
		strBackgroundStyleSheet=/**/"background: none;";
	}
	else{
		strBackgroundStyleSheet	= /**/"background-color: "
								+ BackColor.name() + /**/";";
	}
	//Font
	QString strFont=/**/"";
	if(CFont.bold()==true){
		strFont	+=/**/"font-weight: bold;";
	}
	if(CFont.style()==QFont::StyleItalic){
		strFont	+=/**/"font-style: italic;";
	}
	else if(CFont.style()==QFont::StyleOblique){
		strFont	+=/**/"font-style: oblique;";
	}
	QString strFontStyleSheet	= /**/"font-family: "
								+ CFont.family() + /**/";"
								+ /**/"font-size: "
								+ QString::number(CFont.pointSize()) + /**/"pt;"
								+ strFont;
	//StyleSheet
	QString strStyleSheet	= /**/"color: "
							+ CharColor.name() + /**/";"
							+ /**/"border-width: "
							+ QString::number(BorderWidth) + /**/"px;"
							+ /**/"border-color: "
							+ BorderColor.name() + /**/";"
							+ /**/"border-style: "
							+ BorderStyle + /**/";"
							+ strBackgroundStyleSheet
							+ strFontStyleSheet;
	ui.labelMasterID	->setStyleSheet(strStyleSheet);
	ui.labelMasterName	->setStyleSheet(strStyleSheet);
	ui.labelLotID		->setStyleSheet(strStyleSheet);
	ui.labelLotName		->setStyleSheet(strStyleSheet);
	ui.labelWorkerID	->setStyleSheet(strStyleSheet);
	ui.labelWorkerName	->setStyleSheet(strStyleSheet);

	//Alignment
	if(HeadAlignAttr==/**/"AlignLeft"){
		ui.labelHeadMasterID	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelHeadMasterName	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelHeadLotID		->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelHeadLotName		->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelHeadWorkerID	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelHeadWorkerName	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	}
	else if(HeadAlignAttr==/**/"AlignRight"){
		ui.labelHeadMasterID	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelHeadMasterName	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelHeadLotID		->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelHeadLotName		->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelHeadWorkerID	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelHeadWorkerName	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
	}
	else{
		ui.labelHeadMasterID	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelHeadMasterName	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelHeadLotID		->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelHeadLotName		->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelHeadWorkerID	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelHeadWorkerName	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	}
	//Background
	if(HeadTransparentBackColor==true){
		strBackgroundStyleSheet=/**/"background: none;";
	}
	else{
		strBackgroundStyleSheet	= /**/"background-color: "
								+ HeadBackColor.name() + /**/";";
	}
	//Font
	strFont=/**/"";
	if(HeadCFont.bold()==true){
		strFont	+=/**/"font-weight: bold;";
	}
	if(HeadCFont.style()==QFont::StyleItalic){
		strFont	+=/**/"font-style: italic;";
	}
	else if(HeadCFont.style()==QFont::StyleOblique){
		strFont	+=/**/"font-style: oblique;";
	}
	strFontStyleSheet	= /**/"font-family: "
						+ HeadCFont.family() + /**/";"
						+ /**/"font-size: "
						+ QString::number(HeadCFont.pointSize()) + /**/"pt;"
						+ strFont;
	//StyleSheet
	strStyleSheet	= /**/"color: "
					+ HeadCharColor.name() + /**/";"
					+ /**/"border-width: "
					+ QString::number(HeadBorderWidth) + /**/"px;"
					+ /**/"border-color: "
					+ HeadBorderColor.name() + /**/";"
					+ /**/"border-style: "
					+ HeadBorderStyle + /**/";"
					+ strBackgroundStyleSheet
					+ strFontStyleSheet;
	ui.labelHeadMasterID	->setStyleSheet(strStyleSheet);
	ui.labelHeadMasterName	->setStyleSheet(strStyleSheet);
	ui.labelHeadLotID		->setStyleSheet(strStyleSheet);
	ui.labelHeadLotName		->setStyleSheet(strStyleSheet);
	ui.labelHeadWorkerID	->setStyleSheet(strStyleSheet);
	ui.labelHeadWorkerName	->setStyleSheet(strStyleSheet);
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
		ui.labelLotID	->setText(GetLayersBase()->GetLot(0)->GetLotID());
	}
	if(ShowLotName==true){
		ui.labelLotName	->setText(GetLayersBase()->GetLot(0)->GetLotName());
	}
	if(ShowWorkerID==true){
		ui.labelWorkerID	->setText(QString::number(GetLayersBase()->GetWorkerID()));
	}
	if(ShowWorkerName==true){
		ui.labelWorkerName	->setText(GetLayersBase()->GetWorkerName());
	}
}
