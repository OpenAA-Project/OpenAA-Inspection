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

#include "ShowColorDifferenceEditManualForm.h"
#include "ui_ShowColorDifferenceEditManualForm.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowColorDifferenceEditManualForm::ShowColorDifferenceEditManualForm(LayersBase *Base ,QWidget *parent)
    : GUIFormBase(Base,parent)
    , ui(new Ui::ShowColorDifferenceEditManualForm)
{
    ui->setupUi(this);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowColorDifferenceEditManualForm::~ShowColorDifferenceEditManualForm()
{
    delete ui;
}

void	ShowColorDifferenceEditManualForm::Prepare(void)
{
}
void	ShowColorDifferenceEditManualForm::BuildForShow(void)
{
}
void	ShowColorDifferenceEditManualForm::ResizeAction()
{
	ui->frame->resize(width(),ui->frame->height());
	ui->tableWidget->resize(width(),height()-ui->frame->height());
	ui->pushButtonAddMeasure->move((width()-ui->pushButtonAddMeasure->width())/2,ui->pushButtonAddMeasure->y());

	::SetColumnWidthInTable(ui->tableWidget ,0, 10);
	::SetColumnWidthInTable(ui->tableWidget ,1, 10);
	::SetColumnWidthInTable(ui->tableWidget ,2, 25);
	::SetColumnWidthInTable(ui->tableWidget ,3, 12);
	::SetColumnWidthInTable(ui->tableWidget ,4, 12);
	::SetColumnWidthInTable(ui->tableWidget ,5, 12);
	::SetColumnWidthInTable(ui->tableWidget ,6, 12);

}

void	ShowColorDifferenceEditManualForm::ShowInPlayer(int64 shownInspectionID)
{
	CurrentResults.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqColorDifferenceResult	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckColorDifferenceResult	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,SCmd)==true){
			for(ColorDifferenceResultInfo *R=SCmd.Results.GetFirst();R!=NULL;R=R->GetNext()){
				R->Page=GlobalPage;
			}
			CurrentResults += SCmd.Results;
		}
	}
	int N = CurrentResults.GetCount();
	ui->tableWidget->setRowCount(N);
	for(int row=0;row<N;row++){
		ColorDifferenceResultInfo	*R=CurrentResults.GetItem(row);
		::SetDataToTable(ui->tableWidget,0,row, QString::number(R->Page));
		::SetDataToTable(ui->tableWidget,1,row, QString::number(R->ItemID));
		::SetDataToTable(ui->tableWidget,2,row, R->ItemName);
		::SetDataToTable(ui->tableWidget,3,row, QString::number(R->ResultDeltaE,'f',2));
		::SetDataToTable(ui->tableWidget,4,row,/**/"",Qt::ItemIsEditable | Qt::ItemIsSelectable);
		::SetDataToTable(ui->tableWidget,5,row, QString::number(R->ResultDense ,'f',2));
		::SetDataToTable(ui->tableWidget,6,row,/**/"",Qt::ItemIsEditable | Qt::ItemIsSelectable);
	}
}

void ShowColorDifferenceEditManualForm::on_pushButtonAddMeasure_clicked()
{
	int N = CurrentResults.GetCount();
	for(int row=0;row<N;row++){
		ColorDifferenceResultInfo	*R=CurrentResults.GetItem(row);
		QString		sDeltaE=::GetDataToTable(ui->tableWidget, 4, row);
		if(sDeltaE.isEmpty()==false){
			int	GlobalPage=R->Page;
			GUICmdSetColorDifferenceManualDeltaE	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
			Cmd.ItemID = R->ItemID;
			Cmd.DeltaE = sDeltaE.toDouble();
			Cmd.Send(NULL,GlobalPage,0);
		}
		QString		sDense=::GetDataToTable(ui->tableWidget, 6, row);
		if(sDense.isEmpty()==false){
			int	GlobalPage=R->Page;
			GUICmdSetColorDifferenceManualDense	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
			Cmd.ItemID = R->ItemID;
			Cmd.Dense = sDense.toDouble();
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
}

//========================================================================================
GUICmdReqColorDifferenceResult::GUICmdReqColorDifferenceResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
    :GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

void	GUICmdReqColorDifferenceResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckColorDifferenceResult	*SendBack=GetSendBack(GUICmdAckColorDifferenceResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdReqColorDifferenceResult	Cmd(GetLayersBase());
			PData->TransmitDirectly(&Cmd);
			SendBack->Results = Cmd.Results;
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckColorDifferenceResult::GUICmdAckColorDifferenceResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckColorDifferenceResult::Load(QIODevice *f)
{
	if(Results.Load(f)){
		return true;
	}
	return false;
}

bool	GUICmdAckColorDifferenceResult::Save(QIODevice *f)
{
	if(Results.Save(f)){
		return true;
	}
	return false;
}
//========================================================================================
GUICmdSetColorDifferenceManualDeltaE::GUICmdSetColorDifferenceManualDeltaE(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetColorDifferenceManualDeltaE::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,DeltaE)==false)
		return false;
	return true;
}
bool	GUICmdSetColorDifferenceManualDeltaE::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,DeltaE)==false)
		return false;
	return true;
}

void	GUICmdSetColorDifferenceManualDeltaE::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdSetColorDifferenceManualDeltaE	Cmd(GetLayersBase());
			Cmd.ItemID = ItemID;
			Cmd.DeltaE = DeltaE;
			PData->TransmitDirectly(&Cmd);
		}
	}
}
//========================================================================================
GUICmdSetColorDifferenceManualDense::GUICmdSetColorDifferenceManualDense(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetColorDifferenceManualDense::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Dense)==false)
		return false;
	return true;
}
bool	GUICmdSetColorDifferenceManualDense::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Dense)==false)
		return false;
	return true;
}

void	GUICmdSetColorDifferenceManualDense::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *RBBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(RBBase!=NULL){
		AlgorithmInPageRoot	*PData=RBBase->GetPageData(localPage);
		if(PData!=NULL){
			CmdSetColorDifferenceManualDense	Cmd(GetLayersBase());
			Cmd.ItemID = ItemID;
			Cmd.Dense = Dense;
			PData->TransmitDirectly(&Cmd);
		}
	}
}