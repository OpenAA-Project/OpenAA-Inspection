/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowStockedResult\ShowStockedResultForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <time.h>
#include "ShowStockedResultFormResource.h"
#include "ShowStockedResultForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XWriteResultThread.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowStockedResultForm::ShowStockedResultForm(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
}

ShowStockedResultForm::~ShowStockedResultForm()
{

}


void ShowStockedResultForm::on_pushButtonForceWrite_clicked()
{
	GetLayersBase()->GetResultThread()->ForceWrite();
	time_t	t=time(NULL);
	while(time(NULL)-t<10){
		if(GetLayersBase()->GetResultThread()->GetForceWriteMode()==false)
			break;
	}
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqCastStockedResult		CmdReq(GetLayersBase(),sRoot,sName,page);
		CmdReq.Send(NULL ,page ,0);
	}
	ShowInPlayer(0);
}

void ShowStockedResultForm::on_pushButtonCast_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqCastStockedResult		CmdReq(GetLayersBase(),sRoot,sName,page);
		CmdReq.Send(NULL ,page ,0);
	}
	ShowInPlayer(0);
}

void	ShowStockedResultForm::Prepare(void)
{
}
void	ShowStockedResultForm::ShowInPlayer(int64 shownInspectionID)
{
	int	StockedResultCount=0;
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqStockedResultCount		CmdReq(GetLayersBase(),sRoot,sName,page);
		GUICmdSendStockedResultCount	CmdAck(GetLayersBase(),sRoot,sName,page);
		if(CmdReq.Send(page ,0,CmdAck)==true){
			if(StockedResultCount<CmdAck.StockedResultCount){
				StockedResultCount=CmdAck.StockedResultCount;
			}
		}
	}
	ui.lineEditStockedNumb->setText(QString::number(StockedResultCount));
}
void	ShowStockedResultForm::BuildForShow(void)
{
	ShowInPlayer(0);
}

//============================================================================================

GUICmdReqStockedResultCount::GUICmdReqStockedResultCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqStockedResultCount::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqStockedResultCount::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqStockedResultCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendStockedResultCount	*SendBack=GetSendBack(GUICmdSendStockedResultCount,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->StockedResultCount=GetLayersBase()->GetResultThread()->GetStockedCount();
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//---------------------------------------------------------------------------------------------------------------

GUICmdSendStockedResultCount::GUICmdSendStockedResultCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	StockedResultCount=0;
}

bool	GUICmdSendStockedResultCount::Load(QIODevice *f)
{
	if(::Load(f,StockedResultCount)==false)
		return false;
	return true;
}
bool	GUICmdSendStockedResultCount::Save(QIODevice *f)
{
	if(::Save(f,StockedResultCount)==false)
		return false;
	return true;
}

void	GUICmdSendStockedResultCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//---------------------------------------------------------------------------------------------------------------

GUICmdReqCastStockedResult::GUICmdReqCastStockedResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqCastStockedResult::Load(QIODevice *f)
{
	return true;
}

bool	GUICmdReqCastStockedResult::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqCastStockedResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetResultThread()->SetCastAll();
}



