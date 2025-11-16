#include "NGNamingListResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\NGNamingList\NGNamingListForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
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


