/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowThresholdFileName\ShowThresholdFileNameForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowThresholdFileNameForm.h"
#include "XLotInformation.h"
#include "ShowThresholdFileNamePacket.h"

ShowThresholdFileNameForm::ShowThresholdFileNameForm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
///	LangSolver.SetUI(this);

	ShowThresholdFile		=true;
	TitleThresholdFile		=ui.labelHeadThresholdFileName->text();
	ShowHeadThresholdFile	=true;

	AlignAttr				=/**/"AlignLeft";
	TransparentBackColor	=true;
	BorderWidth				=1;
	BorderStyle				=/**/"Solid";

	HeadAlignAttr			=/**/"AlignLeft";
	HeadTransparentBackColor=true;
	HeadBorderWidth			=1;
	HeadBorderStyle			=/**/"Solid";

	HeadWidth	=ui.labelHeadThresholdFileName->width();
}

ShowThresholdFileNameForm::~ShowThresholdFileNameForm()
{
}

void	ShowThresholdFileNameForm::Prepare(void)
{
//	int	TopY=0;
	if(ShowThresholdFile==true){
		ui.labelThresholdFileName->setVisible(true);
		ui.labelThresholdFileName->resize(width()-ui.labelHeadThresholdFileName->width()-1,ui.labelThresholdFileName->height());
	}
	else{
		ui.labelThresholdFileName->setVisible(false);
	}
	ui.labelThresholdFileName->setText(TitleThresholdFile);

	if(ShowHeadThresholdFile==true){
		ui.labelHeadThresholdFileName->setVisible(true);
	}
	else{
		ui.labelHeadThresholdFileName->setVisible(false);
	}

	//HeadWidth
	ui.labelHeadThresholdFileName->setMaximumWidth(HeadWidth);
	ui.labelHeadThresholdFileName->setMinimumWidth(HeadWidth);

	//[Style Sheet]
	//Alignment
	if(AlignAttr==/**/"AlignLeft"){
		ui.labelThresholdFileName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	}
	else if(AlignAttr==/**/"AlignRight"){
		ui.labelThresholdFileName->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
	}
	else{
		ui.labelThresholdFileName->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
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
	ui.labelThresholdFileName->setStyleSheet(strStyleSheet);

	//Alignment
	if(HeadAlignAttr==/**/"AlignLeft"){
		ui.labelHeadThresholdFileName->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	}
	else if(HeadAlignAttr==/**/"AlignRight"){
		ui.labelHeadThresholdFileName->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
	}
	else{
		ui.labelHeadThresholdFileName->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
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
	ui.labelHeadThresholdFileName->setStyleSheet(strStyleSheet);
}

void	ShowThresholdFileNameForm::ResizeAction()
{
	Prepare();
}

void	ShowThresholdFileNameForm::BuildForShow(void)
{
}

void	ShowThresholdFileNameForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdShowThresholdFileName	*CmdShowThresholdFileNameVar=dynamic_cast<CmdShowThresholdFileName*>(packet);
	if(CmdShowThresholdFileNameVar!=NULL){
		if(ShowThresholdFile==true){
			ui.labelThresholdFileName->setText(CmdShowThresholdFileNameVar->ThresholdFileName);
		}
	}
}
