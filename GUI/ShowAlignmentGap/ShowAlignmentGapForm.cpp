/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "ShowAlignmentGapResource.h"

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
			//���ꌴ�_�ł̃Y����
			QString FirstXY=/**/"(";
			FirstXY+=QString::number(CmdAck.FirstX);
			FirstXY+=/**/", ";
			FirstXY+=QString::number(CmdAck.FirstY);
			FirstXY+=/**/")";
			ui.FirstXY		->setText(FirstXY);
			ui.FirstGapX	->setText(QString::number(CmdAck.FirstGapX));
			ui.FirstGapY	->setText(QString::number(CmdAck.FirstGapY));
			//���񌴓_�ł̃Y����
			QString SecondXY=/**/"(";
			SecondXY+=QString::number(CmdAck.SecondX);
			SecondXY+=/**/", ";
			SecondXY+=QString::number(CmdAck.SecondY);
			SecondXY+=/**/")";
			ui.SecondXY		->setText(SecondXY);
			ui.SecondGapX	->setText(QString::number(CmdAck.SecondGapX));
			ui.SecondGapY	->setText(QString::number(CmdAck.SecondGapY));
			//���O���_�ł̃Y����
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

		//�Y���ʂ̎擾
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