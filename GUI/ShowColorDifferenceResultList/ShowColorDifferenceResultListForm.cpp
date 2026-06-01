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

#include "ShowColorDifferenceResultListForm.h"
#include "ui_ShowColorDifferenceResultListForm.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowColorDifferenceResultListForm::ShowColorDifferenceResultListForm(LayersBase *Base ,QWidget *parent)
    : GUIFormBase(Base,parent)
    , ui(new Ui::ShowColorDifferenceResultListForm)
{
    ui->setupUi(this);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowColorDifferenceResultListForm::~ShowColorDifferenceResultListForm()
{
    delete ui;
}

void	ShowColorDifferenceResultListForm::Prepare(void)
{
}
void	ShowColorDifferenceResultListForm::BuildForShow(void)
{
}
void	ShowColorDifferenceResultListForm::ResizeAction()
{
	ui->tableWidget->resize(width(),height());

	::SetColumnWidthInTable(ui->tableWidget ,0, 10);
	::SetColumnWidthInTable(ui->tableWidget ,1, 10);
	::SetColumnWidthInTable(ui->tableWidget ,2, 25);
	::SetColumnWidthInTable(ui->tableWidget ,3, 12);
	::SetColumnWidthInTable(ui->tableWidget ,4, 12);
	::SetColumnWidthInTable(ui->tableWidget ,5, 12);
	::SetColumnWidthInTable(ui->tableWidget ,6, 12);

}

void	ShowColorDifferenceResultListForm::ShowInPlayer(int64 shownInspectionID)
{
	CurrentResults.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqShowColorDifferenceResult	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdAckShowColorDifferenceResult	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
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
		if(R->ResultDeltaEOK==true3){
			::SetDataToTable(ui->tableWidget,4,row,QString::number(R->ResultManualDeltaE,'f',2));
			::SetTableColor(ui->tableWidget,4,row, Qt::green);
		}
		else if(R->ResultDeltaEOK==false3){
			::SetDataToTable(ui->tableWidget,4,row,QString::number(R->ResultManualDeltaE,'f',2));
			::SetTableColor(ui->tableWidget,4,row, Qt::red);
		}
		else{
			::SetDataToTable(ui->tableWidget,4,row,QString(/**/""));
			::SetTableColor(ui->tableWidget,4,row, Qt::darkGray);
		}
		::SetDataToTable(ui->tableWidget,5,row, QString::number(R->ResultDense ,'f',2));
		::SetDataToTable(ui->tableWidget,6,row,/**/"",Qt::ItemIsEditable | Qt::ItemIsSelectable);
		if(R->ResultDenseOK==true3){
			::SetDataToTable(ui->tableWidget,6,row,QString::number(R->ResultManualDense,'f',2));
			::SetTableColor(ui->tableWidget,6,row, Qt::green);
		}
		else if(R->ResultDenseOK==false3){
			::SetDataToTable(ui->tableWidget,6,row,QString::number(R->ResultManualDense,'f',2));
			::SetTableColor(ui->tableWidget,6,row, Qt::red);
		}
		else{
			::SetDataToTable(ui->tableWidget,6,row,QString(/**/""));
			::SetTableColor(ui->tableWidget,6,row, Qt::darkGray);
		}
	}
}

//========================================================================================
GUICmdReqShowColorDifferenceResult::GUICmdReqShowColorDifferenceResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
    :GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

void	GUICmdReqShowColorDifferenceResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckShowColorDifferenceResult	*SendBack=GetSendBack(GUICmdAckShowColorDifferenceResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

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


GUICmdAckShowColorDifferenceResult::GUICmdAckShowColorDifferenceResult(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
	:GUICmdPacketBase(Base,emitterRoot,emitterName,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckShowColorDifferenceResult::Load(QIODevice *f)
{
	if(Results.Load(f)){
		return true;
	}
	return false;
}

bool	GUICmdAckShowColorDifferenceResult::Save(QIODevice *f)
{
	if(Results.Save(f)){
		return true;
	}
	return false;
}
