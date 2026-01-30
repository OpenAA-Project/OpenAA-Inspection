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

#include "PieceListFormResource.h"
#include "PieceListForm.h"
#include "ui_PieceListForm.h"
#include "XGeneralFunc.h"
#include "XPieceForReview.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PieceListForm::PieceListForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PieceListForm)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,40);
	ui->tableWidget->setColumnWidth(1,200);
}

PieceListForm::~PieceListForm()
{
    delete ui;
}

PieceReviewSideBase	*PieceListForm::GetResultImportanceBase(void)
{
	return (PieceReviewSideBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceReviewSide");
}
void	PieceListForm::BuildForShow(void)
{
	PieceReviewSideBase	*ABase=GetResultImportanceBase();
	ListData.RemoveAll();

	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqItemListReviewSide		RCmd(GetLayersBase(),sRoot,sName,globalPage);
		GUICmdSendItemListReviewSide	ACmd(GetLayersBase(),sRoot,sName,globalPage);

		if(RCmd.Send(globalPage,0,ACmd)==true
		&& ACmd.IsReceived()==true){
			ItemListReviewSide *c;
			for(c=ACmd.ListData.GetFirst();c!=NULL;c=c->GetNext()){
				if(ListData.IsInclude(c)==false){
					ItemListReviewSide	*k=new ItemListReviewSide(*c);
					ListData.AppendList(k);
				}
			}
		}
	}
	ui->tableWidget->setRowCount(ListData.GetCount());
	int	Row=0;
	for(ItemListReviewSide *a=ListData.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui->tableWidget ,0,Row ,QString::number(a->AreaNumber));
		::SetDataToTable(ui->tableWidget ,1,Row ,a->AreaName);
		Row++;
	}
}

void PieceListForm::resizeEvent ( QResizeEvent * event )
{
	ui->tableWidget->resize(width(),height());
}
