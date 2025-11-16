#include "ShowCurrentOpinionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowCurrentOpinion\ShowCurrentOpinionForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ShowCurrentOpinionForm.h"
#include "XStatusController.h"
#include "XGeneralFunc.h"

ShowCurrentOpinionForm::ShowCurrentOpinionForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

ShowCurrentOpinionForm::~ShowCurrentOpinionForm()
{

}

void	ShowCurrentOpinionForm::Prepare(void)
{
	ui.tableWidgetGUI->setColumnWidth(0,100);
	ui.tableWidgetGUI->setColumnWidth(1,100);
	ui.tableWidgetGUI->setColumnWidth(2,100);
}

void ShowCurrentOpinionForm::on_pushButtonUpdate_clicked()
{
	ui.tableWidgetGUI->setRowCount(GetLayersBase()->GetStatusController()->GetCount());
	int	Row=0;
	for(StatusOpinionInGUI *c=GetLayersBase()->GetStatusController()->GetFirst();c!=NULL;c=c->GetNext()){
		SetDataToTable(ui.tableWidgetGUI,0 ,Row ,c->GetGUIRoot());
		SetDataToTable(ui.tableWidgetGUI,1 ,Row ,c->GetGUIName());
		SetDataToTable(ui.tableWidgetGUI,2 ,Row ,c->GetGUIInst());
		Row++;
	}
	ui.listWidgetCommentOpinionList->clear();
	ui.listWidgetMode->clear();
	ui.textEditCommentNow->clear();
}

void ShowCurrentOpinionForm::on_tableWidgetGUI_clicked(const QModelIndex &)
{
	int	Row=ui.tableWidgetGUI->currentRow();
	if(Row>=0){
		StatusOpinionInGUI	*L=GetLayersBase()->GetStatusController()->GetItem(Row);
		if(L!=NULL){
			ui.listWidgetCommentOpinionList->clear();
			int	R=0;
			for(CommentOpinion *c=L->NPListPackSaveLoad<CommentOpinion>::GetFirst();c!=NULL;c=c->GetNext(),R++){
				ui.listWidgetCommentOpinionList->addItem(QString::number(R));
			}
		}
	}
}
void ShowCurrentOpinionForm::on_listWidgetCommentOpinionList_clicked(const QModelIndex &index)
{
	int	Row=ui.tableWidgetGUI->currentRow();
	if(Row>=0){
		StatusOpinionInGUI	*L=GetLayersBase()->GetStatusController()->GetItem(Row);
		int	R=ui.listWidgetCommentOpinionList->currentRow();
		if(R>=0){
			CommentOpinion *c=L->NPListPackSaveLoad<CommentOpinion>::GetItem(R);
			if(c!=NULL){
				ui.listWidgetMode	->addItems(c->GetObjectPath());
				if(c->IsHTML()==true){
					ui.textEditCommentNow->setHtml(c->GetCommentString());
				}
				else{
					ui.textEditCommentNow->setText(c->GetCommentString());
				}
			}
		}
	}
}
