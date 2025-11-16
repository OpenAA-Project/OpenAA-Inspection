#include "StartCaptureButtonForDesktopResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DesktopMachineMenu\NextMasterForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "NextMasterForm.h"
#include "XGeneralFunc.h"

NextMasterForm::NextMasterForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	SetWidgetCenter(this);
//	setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);

	ui.lbMasterCount		->setVisible(false);
	ui.lbMasterCountLabel	->setVisible(false);

	//画面表示部の言語対応
	LangSolver.SetUI(this);
}

NextMasterForm::~NextMasterForm()
{
}

void NextMasterForm::SetLanguageCode(int LCode)
{
	LanguageCode=LCode;

	//フォントの設定
    QFont font1[5];
	//日本語
    font1[0].setPointSize(13);
    font1[0].setBold(true);
    font1[0].setWeight(75);
	//English
    font1[1].setPointSize(13);
    font1[1].setBold(true);
    font1[1].setWeight(75);
	//簡体中文
    font1[2].setPointSize(13);
    font1[2].setBold(true);
    font1[2].setWeight(75);
	//繁体中文
	font1[3].setPointSize(13);
    font1[3].setBold(true);
    font1[3].setWeight(75);
	//Korean
    font1[4].setPointSize(13);
    font1[4].setBold(true);
    font1[4].setWeight(75);

	QString strFont=/**/"";
	if(font1[LanguageCode].bold()==true){
		strFont	+=/**/"font-weight: bold;";
	}
	if(font1[LanguageCode].style()==QFont::StyleItalic){
		strFont	+=/**/"font-style: italic;";
	}
	else if(font1[LanguageCode].style()==QFont::StyleOblique){
		strFont	+=/**/"font-style: oblique;";
	}
	QString strFontStyleSheet;
	strFontStyleSheet=/**/"font-family: "
						+ font1[LanguageCode].family() + /**/";"
						+ /**/"font-size: "
						+ QString::number(font1[LanguageCode].pointSize()) + /**/"pt;"
						+ strFont;

	if(LanguageCode>0){
		ui.lbNext				->setStyleSheet(strFontStyleSheet);
		ui.lbNone				->setStyleSheet(strFontStyleSheet);
		ui.pushButtonFinish		->setStyleSheet(strFontStyleSheet);
		ui.pushButtonStartNext	->setStyleSheet(strFontStyleSheet);
	}
}

void NextMasterForm::SetNextMasterFlag(bool Flag)
{
	ui.lbNext->setVisible(Flag);
	ui.lbNone->setVisible(!Flag);
}

void NextMasterForm::SetMasterCounter(int Count,bool Enable)
{
	ui.lbMasterCount		->setText(QString::number(Count));
	ui.lbMasterCount		->setVisible(Enable);
	ui.lbMasterCountLabel	->setVisible(Enable);
}

void NextMasterForm::on_pushButtonFinish_clicked()
{
	accept();
}

void NextMasterForm::on_pushButtonStartNext_clicked()
{
	reject();
}