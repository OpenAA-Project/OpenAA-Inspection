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

#include "ShowCurrentOpinionResource.h"
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