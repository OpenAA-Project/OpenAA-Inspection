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

#include "NGNamingListResource.h"
#include "NGNamingListForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

NGNamingListForm::NGNamingListForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	WidthAreaName		=120;
	WidthNGCountInPiece	=40;
	ui.tableWidget->move(0,0);
	resize(202,304);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	ui.tableWidget->setColumnWidth(0,60);
	ui.tableWidget->setColumnWidth(1,200);
	ui.tableWidget->setColumnWidth(2,60);
}

NGNamingListForm::~NGNamingListForm()
{

}

void	NGNamingListForm::Prepare(void)
{
	ShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	NGNamingListForm::ResizeAction()
{
	ui.tableWidget->resize(width(),height()-ui.frameAmount->height());
	ui.frameAmount->move(0,height()-ui.frameAmount->height());
	ui.frameAmount->resize(width(),ui.frameAmount->height());
}

void	NGNamingListForm::ShowInPlayer(int64 shownInspectionID)
{
	NGData.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqNGNamingList	CmdReq(GetLayersBase(),sRoot,sName,page);
		CmdReq.ShownInspectionID=shownInspectionID;
		GUICmdSendNGNamingList	CmdAck(GetLayersBase(),sRoot,sName,page);
		if(CmdReq.Send(page ,0,CmdAck)==true){
			NGAreaList *e;
			while((e=CmdAck.NGData.GetFirst())!=NULL){
				CmdAck.NGData.RemoveList(e);
				NGAreaList *c=NGData.Search(e->GetAreaName());
				if(c==NULL){
					NGData.AppendList(e);
				}
				else{
					c->SetNGCount(c->GetNGCount()+e->GetNGCount());
					delete	e;
				}
			}
		}
	}

	int	LNumb=NGData.GetNumber();
	ui.tableWidget->setRowCount(LNumb);
	ui.tableWidget->clearSelection();
	ui.tableWidget->setUpdatesEnabled(false);
	int	row=0;
	for(NGAreaList *e=NGData.GetFirst();e!=NULL;e=e->GetNext(),row++){
		QTableWidgetItem *W;
		
		W=ui.tableWidget->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidget->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(row));
		
		W=ui.tableWidget->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidget->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(e->GetAreaName());

		W=ui.tableWidget->item ( row, 2);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidget->setItem ( row, 2,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(e->GetNGCount()));
	}

	ui.lineEdit->setText(QString::number(LNumb));
	ui.tableWidget->setUpdatesEnabled(true);
}

