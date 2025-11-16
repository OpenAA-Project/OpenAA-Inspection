/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExit\CloseMessageForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonExitResource.h"
#include "CloseMessageForm.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"

extern	char	*sRoot;
extern	char	*sName;

CloseMessageForm::CloseMessageForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	LogoInQWidget(Base,this,sRoot ,sName);

	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
//	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	if(GetLayersBase()->GetParamComm()->ConnectedPCNumb==0){
		ui.pushButtonCloseAll->setVisible(false);
		ui.pushButtonCloseOne->setDefault(true);
	}
}

CloseMessageForm::~CloseMessageForm()
{

}

void CloseMessageForm::on_pushButtonCloseAll_clicked()
{
	GetLayersBase()->CloseAll();
	QCoreApplication::quit();	
}

void CloseMessageForm::on_pushButtonCloseOne_clicked()
{
	GetLayersBase()->CloseOne();
	QCoreApplication::quit();	
}

void CloseMessageForm::on_pushButtonCalcen_clicked()
{
	close();
}
