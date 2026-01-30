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

#include "SearchDialog.h"
#include "ui_SearchDialog.h"

#include "XDataInExe.h"
#include "XGeneralFunc.h"
#include <QTableWidgetItem>
#include "itemlistwindow.h"
#include "propertylist.h"
#include "XGUIInterfaceDLL.h"

extern	ItemListWindow	*MainItem;
extern	PropertyList	*MainProperty;


SearchDialog::SearchDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
    ,ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

	for(GUIRootClassified *R=GetLayersBase()->GetGuiInitializer()->RootList.GetFirst();R!=NULL;R=R->GetNext()){
		ui->listWidgetRootList->addItem(R->Root);
	}

	ui->tableWidgetComponents->setColumnWidth(0,48);
	ui->tableWidgetComponents->setColumnWidth(1,150);
	ui->tableWidgetComponents->setColumnWidth(2,150);
	ui->tableWidgetComponents->setColumnWidth(3,300);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_listWidgetRootList_clicked(const QModelIndex &index)
{
	int	Row=ui->listWidgetRootList->currentRow();
	if(Row<0)
		return;
	GUIRootClassified *R=GetLayersBase()->GetGuiInitializer()->RootList[Row];
	if(R==NULL)
		return;
	PointerList.RemoveAll();
	for(GUINameClassified *a=R->NameList.GetFirst();a!=NULL;a=a->GetNext()){
		PointerList.AppendList(new GUINameClassifiedPointer(a));
	}
	ShowGUIItemGrid();
}
QTableWidgetItem	*SetDataToTable(QTableWidget *W ,int col ,int row ,const QIcon &icon ,const QString &str)
{
	QTableWidgetItem	*item=new QTableWidgetItem(icon,str);
	W->setItem(row,col,item);
	return item;
}

void SearchDialog::ShowGUIItemGrid(void)
{
	ui->tableWidgetComponents->setRowCount(PointerList.GetCount());
	int	row=0;
	for(GUINameClassifiedPointer *v=PointerList.GetFirst();v!=NULL;v=v->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetComponents,0,row ,v->GUIItemPointer->Point->GetIcon(),/**/"");
		::SetDataToTable(ui->tableWidgetComponents,1,row ,v->GUIItemPointer->Point->GetDLLRoot());
		::SetDataToTable(ui->tableWidgetComponents,2,row ,v->GUIItemPointer->Point->GetDLLName());
		::SetDataToTable(ui->tableWidgetComponents,3,row ,v->GUIItemPointer->Point->GetExplain());
	}
}

void SearchDialog::on_pushButtonSearcg_clicked()
{
	QString	Str=ui->lineEditSearcgStr->text();
	PointerList.RemoveAll();
	for(GUIRootClassified *R=GetLayersBase()->GetGuiInitializer()->RootList.GetFirst();R!=NULL;R=R->GetNext()){
		for(GUINameClassified *a=R->NameList.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->Point->GetDLLRoot().contains(Str,Qt::CaseInsensitive)==true){
				PointerList.AppendList(new GUINameClassifiedPointer(a));
			}
			else
			if(a->Point->GetDLLName().contains(Str,Qt::CaseInsensitive)==true){
				PointerList.AppendList(new GUINameClassifiedPointer(a));
			}
			else
			if(a->Point->GetExplain().contains(Str,Qt::CaseInsensitive)==true){
				PointerList.AppendList(new GUINameClassifiedPointer(a));
			}
		}
	}
	ShowGUIItemGrid();
}

void SearchDialog::on_tableWidgetComponents_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void SearchDialog::on_pushButtonSelect_clicked()
{
	int	R=ui->tableWidgetComponents->currentRow();
	if(R<0)
		return;
	GUINameClassifiedPointer *v=PointerList[R];
	if(v==NULL)
		return;
	MainItem->SelectGUI(v->GUIItemPointer);
	close();
}

void SearchDialog::on_pushButtonClose_clicked()
{
	close();
}