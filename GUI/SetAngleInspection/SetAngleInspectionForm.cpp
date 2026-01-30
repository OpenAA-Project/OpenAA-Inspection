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

#include "SetAngleInspectionForm.h"
#include "ui_SetAngleInspectionForm.h"
#include "XGeneralFunc.h"
#include "XAngleInspection.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SetAngleInspectionForm::SetAngleInspectionForm(LayersBase *base,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::SetAngleInspectionForm)
{
    ui->setupUi(this);
}

SetAngleInspectionForm::~SetAngleInspectionForm()
{
    delete ui;
}

void	SetAngleInspectionForm::BuildForShow(void)
{
	int	page=0;
	GUICmdReqAngleInspection	RCmd(GetLayersBase(),sRoot,sName,page);
	GUICmdAckAngleInspection	ACmd(GetLayersBase(),sRoot,sName,page);
	if(RCmd.Send(page,0,ACmd)==true){
		ui->doubleSpinBoxOKAngleL->setValue(ACmd.OKAngleL);
		ui->doubleSpinBoxOKAngleH->setValue(ACmd.OKAngleH);
	}
	else{
		ui->doubleSpinBoxOKAngleL->setValue(0);
		ui->doubleSpinBoxOKAngleH->setValue(0);
	}
}

void SetAngleInspectionForm::on_pushButtonSet_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdSetAngleInspection	RCmd(GetLayersBase(),sRoot,sName,globalPage);
        RCmd.OKAngleL=ui->doubleSpinBoxOKAngleL->value();
        RCmd.OKAngleH=ui->doubleSpinBoxOKAngleH->value();
		RCmd.Send(NULL,globalPage,0);
	}
}


//=======================================================================================
GUICmdSetAngleInspection::GUICmdSetAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetAngleInspection::Load(QIODevice *f)
{
	if(::Load(f,OKAngleL)==false)	return false;
	if(::Load(f,OKAngleH)==false)	return false;
	return true;
}
bool	GUICmdSetAngleInspection::Save(QIODevice *f)
{
	if(::Save(f,OKAngleL)==false)	return false;
	if(::Save(f,OKAngleH)==false)	return false;
	return true;
}

void	GUICmdSetAngleInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AngleInspection");
	if(Base!=NULL){
		AngleInspectionInPage	*PPage=dynamic_cast<AngleInspectionInPage *>(Base->GetPageData(localPage));
		CmdSetAngleInspection	Cmd(GetLayersBase());
		Cmd.OKAngleL		=OKAngleL;
		Cmd.OKAngleH		=OKAngleH;
		PPage->TransmitDirectly(&Cmd);
	}
}

GUICmdReqAngleInspection::GUICmdReqAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAngleInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckAngleInspection	*SendBack=GetSendBack(GUICmdAckAngleInspection,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AngleInspection");
	if(Base!=NULL){
		AngleInspectionInPage	*PPage=dynamic_cast<AngleInspectionInPage *>(Base->GetPageData(localPage));
		AngleInspectionItem	*Item=(AngleInspectionItem *)PPage->GetFirstData();
		if(Item!=NULL){
			const	AngleInspectionThreshold	*RThr=Item->GetThresholdR();
			SendBack->OKAngleL=RThr->OKAngleL;
			SendBack->OKAngleH=RThr->OKAngleH;
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdAckAngleInspection::GUICmdAckAngleInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckAngleInspection::Load(QIODevice *f)
{
	if(::Load(f,OKAngleL)==false)	return false;
	if(::Load(f,OKAngleH)==false)	return false;
	return true;
}
bool	GUICmdAckAngleInspection::Save(QIODevice *f)
{
	if(::Save(f,OKAngleL)==false)	return false;
	if(::Save(f,OKAngleH)==false)	return false;
	return true;
}