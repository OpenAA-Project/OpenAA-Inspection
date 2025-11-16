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
#include "XSyncGUI.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

CloseMessageForm::CloseMessageForm(LayersBase *Base,GUIFormBase *parentGUI,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	LogoInQWidget(Base,this,sRoot ,sName);
	ParentGUI=dynamic_cast<GUIFormBase *>(parentGUI);

	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | windowFlags());
	if(GetLayersBase()->GetParamComm()->ConnectedPCNumb==0){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()==0){
			ui.pushButtonCloseAll->setVisible(false);
			ui.pushButtonCloseOne->setDefault(true);
		}
	}
	InstallOperationLog(this);
}

CloseMessageForm::~CloseMessageForm()
{

}

void CloseMessageForm::on_pushButtonCloseAll_clicked()
{
	CloseApplicationSpecifiedBroadcaster	SData;
	ParentGUI->BroadcastSpecifiedDirectly(&SData);
	
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	int	Cmd=1;
	::Save(&Buff,Cmd);
	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		if(ParentGUI!=NULL){
			ParentGUI->TxSync(Buff.buffer());
		}
	}
	GetLayersBase()->CloseAll();
	QCoreApplication::quit();	
}

void CloseMessageForm::on_pushButtonCloseOne_clicked()
{
	CloseApplicationSpecifiedBroadcaster	SData;
	ParentGUI->BroadcastSpecifiedDirectly(&SData);

	if(GetLayersBase()->GetBootingLevel()!=0){
		GetLayersBase()->GetMainWidget()->close();
		close();
		/*
		QWidget	*c=this;
		for(;;){
			if(c->parentWidget()==NULL){
				c->close();
				break;
			}
			c=c->parentWidget();
		}
		*/
	}
	else{
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			int	Cmd=2;
			::Save(&Buff,Cmd);
			ParentGUI->TxSync(Buff.buffer());
		}
		GetLayersBase()->CloseOne();
		QCoreApplication::quit();	
	}
}

void CloseMessageForm::on_pushButtonCalcen_clicked()
{
	close();
}
