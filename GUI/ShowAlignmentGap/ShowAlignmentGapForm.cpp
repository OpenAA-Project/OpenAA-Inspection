#include "ShowAlignmentGapResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowAlignmentGap\ShowAlignmentGapForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowAlignmentGapForm.h"
#include "XDLLOnly.h"
#include "XDataInLayer.h"
//#include "XResultDLLManager.h"
#include "XGeneralFunc.h"

ShowAlignmentGapForm::ShowAlignmentGapForm(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowAlignmentGapForm::~ShowAlignmentGapForm()
{
}
void	ShowAlignmentGapForm::Prepare(void)
{
	ResizeAction();
}

void	ShowAlignmentGapForm::ResizeAction()
{
}

void	ShowAlignmentGapForm::ShowInPlayer(int64 shownInspectionID)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqAlignGap	CmdReq(GetLayersBase(),/**/"Panel",/**/"ShowAlignmentGap",page);
		GUICmdSendAlignGap	CmdAck(GetLayersBase(),/**/"Panel",/**/"ShowAlignmentGap",page);
		if(CmdReq.Send(page ,0,CmdAck)==true){
			if(CmdAck.FirstX==-1)
				return;
			//第一原点でのズレ量
			QString FirstXY=/**/"(";
			FirstXY+=QString::number(CmdAck.FirstX);
			FirstXY+=/**/", ";
			FirstXY+=QString::number(CmdAck.FirstY);
			FirstXY+=/**/")";
			ui.FirstXY		->setText(FirstXY);
			ui.FirstGapX	->setText(QString::number(CmdAck.FirstGapX));
			ui.FirstGapY	->setText(QString::number(CmdAck.FirstGapY));
			//第二原点でのズレ量
			QString SecondXY=/**/"(";
			SecondXY+=QString::number(CmdAck.SecondX);
			SecondXY+=/**/", ";
			SecondXY+=QString::number(CmdAck.SecondY);
			SecondXY+=/**/")";
			ui.SecondXY		->setText(SecondXY);
			ui.SecondGapX	->setText(QString::number(CmdAck.SecondGapX));
			ui.SecondGapY	->setText(QString::number(CmdAck.SecondGapY));
			//第三原点でのズレ量
			QString ThirdXY=/**/"(";
			ThirdXY+=QString::number(CmdAck.ThirdX);
			ThirdXY+=/**/", ";
			ThirdXY+=QString::number(CmdAck.ThirdY);
			ThirdXY+=/**/")";
			ui.ThirdXY		->setText(ThirdXY);
			ui.ThirdGapX	->setText(QString::number(CmdAck.ThirdGapX));
			ui.ThirdGapY	->setText(QString::number(CmdAck.ThirdGapY));
		}
	}
}
void	ShowAlignmentGapForm::BuildForShow(void)
{
	ShowInPlayer(-1);
}

//=======================================================================
GUICmdReqAlignGap::GUICmdReqAlignGap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlignGap::Save(QIODevice *f)
{
	::Save(f,ShownInspectionID);
	return(true);
}
bool	GUICmdReqAlignGap::Load(QIODevice *f)
{
	::Load(f,ShownInspectionID);
	return(true);
}

void	GUICmdReqAlignGap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlignGap	*SendBack=GetSendBack(GUICmdSendAlignGap,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(ABase!=NULL){
		CmdCreateAlignGapPacket	Cmd;
		ABase->TransmitDirectly(&Cmd);

		//ズレ量の取得
//		SendBack->FirstPoint=Cmd.FirstPoint;
//		SendBack->SecondPoint=Cmd.SecondPoint;
//		SendBack->ThirdPoint=Cmd.ThirdPoint;
		SendBack->FirstX=Cmd.FirstX;
		SendBack->FirstY=Cmd.FirstY;
		SendBack->FirstGapX=Cmd.FirstGapX;
		SendBack->FirstGapY=Cmd.FirstGapY;
		SendBack->SecondX=Cmd.SecondX;
		SendBack->SecondY=Cmd.SecondY;
		SendBack->SecondGapX=Cmd.SecondGapX;
		SendBack->SecondGapY=Cmd.SecondGapY;
		SendBack->ThirdX=Cmd.ThirdX;
		SendBack->ThirdY=Cmd.ThirdY;
		SendBack->ThirdGapX=Cmd.ThirdGapX;
		SendBack->ThirdGapY=Cmd.ThirdGapY;
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendAlignGap::GUICmdSendAlignGap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAlignGap::Load(QIODevice *f)
{
//	if(NGData.Load(f)==false)
//		return false;
	return true;
}
bool	GUICmdSendAlignGap::Save(QIODevice *f)
{
//	if(NGData.Save(f)==false)
//		return false;
	return true;
}

void	GUICmdSendAlignGap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
