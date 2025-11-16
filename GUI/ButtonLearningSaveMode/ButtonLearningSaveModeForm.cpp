#include "ButtonLearningSaveModeResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLearningSaveMode\ButtonLearningSaveModeForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonLearningSaveModeForm.h"
#include "XDataInLayer.h"
#include "XLearning.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

GUICmdReqLearningSaveMode::GUICmdReqLearningSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	GUICmdReqLearningSaveMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckLearningSaveMode	*SendBack=GetSendBack(GUICmdAckLearningSaveMode,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;

	LearningReqSaveMode	Cmd(this);
	L->TransmitDirectly(&Cmd);
	SendBack->Mode=Cmd.Mode;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

	
GUICmdAckLearningSaveMode::GUICmdAckLearningSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Mode=false;
}

bool	GUICmdAckLearningSaveMode::Load(QIODevice *f)
{
	if(::Load(f,Mode)==false)
		return false;
	return true;
}
bool	GUICmdAckLearningSaveMode::Save(QIODevice *f)
{
	if(::Save(f,Mode)==false)
		return false;
	return true;
}

GUISetLearningSaveMode::GUISetLearningSaveMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Mode=false;
}

bool	GUISetLearningSaveMode::Load(QIODevice *f)
{
	if(::Load(f,Mode)==false)
		return false;
	return true;
}
bool	GUISetLearningSaveMode::Save(QIODevice *f)
{
	if(::Save(f,Mode)==false)
		return false;
	return true;
}

void	GUISetLearningSaveMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Learning");
	if(L==NULL)
		return;

	LearningSetSaveMode	Cmd(this);
	Cmd.Mode=Mode;
	L->TransmitDirectly(&Cmd);
	GUIFormBase	*g=GetLayersBase()->FindByName(sRoot ,sName ,/**/"");
	if(g!=NULL){
		g->TransmitDirectly(&Cmd);
	}
}


//========================================================================================

ButtonLearningSaveModeForm::ButtonLearningSaveModeForm(LayersBase *Base,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	Msg=/**/"Save learn";
	ui.setupUi(this);
	ui.toolButton->move(0,0);
	ui.toolButton->setText(/**/"AutoMode");
	resize(60,25);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonLearningSaveModeForm::~ButtonLearningSaveModeForm()
{

}

void	ButtonLearningSaveModeForm::BuildForShow(void)
{
	bool	mode=true;
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqLearningSaveMode	RCmd(GetLayersBase(),sRoot,sName,page);
		GUICmdAckLearningSaveMode	ACmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(page,0,ACmd);
		if(ACmd.Mode==false)
			mode=false;
	}
	ui.toolButton->setChecked(mode);
}

void ButtonLearningSaveModeForm::on_toolButton_toggled(bool mode)
{
	for(int page=0;page<GetPageNumb();page++){
		GUISetLearningSaveMode	SCmd(GetLayersBase(),sRoot,sName,page);
		SCmd.Mode=mode;
		SCmd.Send(NULL,page,0);
	}
}

void	ButtonLearningSaveModeForm::TransmitDirectly(GUIDirectMessage *packet)
{
	LearningSetSaveMode	*LearningSetSaveModeVar=dynamic_cast<LearningSetSaveMode *>(packet);
	if(LearningSetSaveModeVar!=NULL){
		if(LearningSetSaveModeVar->Mode==true){
			ui.toolButton->setChecked(true);
		}
		else{
			ui.toolButton->setChecked(false);
		}
		return;
	}
}
void	ButtonLearningSaveModeForm::Prepare(void)
{
	ui.toolButton->setText(Msg);
	ui.toolButton->setFont (CFont);
	ResizeAction();
}

void	ButtonLearningSaveModeForm::ResizeAction()
{
	ui.toolButton->resize(width(),height());
}


