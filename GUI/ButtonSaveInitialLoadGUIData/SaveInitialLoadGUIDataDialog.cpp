/*
 * Copyright (C) 2025
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

#include "SaveInitialLoadGUIDataDialog.h"
#include "ui_SaveInitialLoadGUIDataDialog.h"
#include "XGUI.h"
#include "XGeneralFunc.h"


SaveInitialLoadGUIDataDialog::SaveInitialLoadGUIDataDialog(ButtonSaveInitialLoadGUIData *p,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(p->GetLayersBase())
    ,Parent(p)
    ,ui(new Ui::SaveInitialLoadGUIDataDialog)
{
    ui->setupUi(this);

	AllComponentsData.RemoveAll();
    for(GUIInstancePack	*G=GetLayersBase()->GetGuiInitializer()->GetGUIInstanceRoot();G!=NULL;G=G->GetNext()){
		for(GUIItemInstance *I=G->NPListPack<GUIItemInstance> ::GetFirst();I!=NULL;I=I->GetNext()){
            GUIFormBase	*f=I->GetForm();
			if(f!=NULL){
                GUIDataList	*data=new GUIDataList;
                data->DLLRoot=I->GetDLLRoot();
                data->DLLName=I->GetDLLName();
                data->InstName=f->GetName();
				AllComponentsData.AppendListItem(data);
            }
		}
    }
    ::SetColumnWidthInTable(ui->tableWidgetAllComponents,0, 30);
    ::SetColumnWidthInTable(ui->tableWidgetAllComponents,1, 30);
    ::SetColumnWidthInTable(ui->tableWidgetAllComponents,2, 30);

	ui->tableWidgetAllComponents->setRowCount(AllComponentsData.GetCount());
	int row = 0;
	for(GUIDataList *f = AllComponentsData.GetFirst();f!=NULL;f = f->GetNext(),row++){
        ::SetDataToTable(ui->tableWidgetAllComponents,0, row, f->DLLRoot);
        ::SetDataToTable(ui->tableWidgetAllComponents,1, row, f->DLLName);
        ::SetDataToTable(ui->tableWidgetAllComponents,2, row, f->InstName);
    }

	TmpData = Parent->Data;
    ::SetColumnWidthInTable(ui->tableWidgetManagedComponents,0, 30);
    ::SetColumnWidthInTable(ui->tableWidgetManagedComponents,1, 30);
    ::SetColumnWidthInTable(ui->tableWidgetManagedComponents,2, 30);

	ShowManagedTable();
}

SaveInitialLoadGUIDataDialog::~SaveInitialLoadGUIDataDialog()
{
    delete ui;
}

void SaveInitialLoadGUIDataDialog::ShowManagedTable(void)
{
	ui->tableWidgetManagedComponents->setRowCount(TmpData.GetCount());
	int row = 0;
	for(GUIDataList *f = TmpData.GetFirst();f!=NULL;f = f->GetNext(),row++){
        ::SetDataToTable(ui->tableWidgetManagedComponents,0, row, f->DLLRoot);
        ::SetDataToTable(ui->tableWidgetManagedComponents,1, row, f->DLLName);
        ::SetDataToTable(ui->tableWidgetManagedComponents,2, row, f->InstName);
    }
}

void SaveInitialLoadGUIDataDialog::on_tableWidgetAllComponents_doubleClicked(const QModelIndex &index)
{
    on_pushButtonUseOne_clicked();
}


void SaveInitialLoadGUIDataDialog::on_tableWidgetManagedComponents_doubleClicked(const QModelIndex &index)
{
	on_pushButtonReturnOne_clicked();
}


void SaveInitialLoadGUIDataDialog::on_pushButtonUseOne_clicked()
{
	int row = ui->tableWidgetAllComponents->currentRow();
    GUIDataList *g=AllComponentsData.GetItem(row);
    if(g!=NULL){
        if(TmpData.HasSameData(g)==false){
		    GUIDataList *newdata = new GUIDataList;
		    *newdata = *g;
            TmpData.AppendList(newdata);
        }
    }
    ShowManagedTable();
    ::SetCurrentRow(ui->tableWidgetAllComponents, row);
}


void SaveInitialLoadGUIDataDialog::on_pushButtonReturnOne_clicked()
{
	int row = ui->tableWidgetManagedComponents->currentRow();
    GUIDataList *g=TmpData.GetItem(row);
    if(g!=NULL){
        TmpData.RemoveList(g);
    }
    ShowManagedTable();
	::SetCurrentRow(ui->tableWidgetManagedComponents,row);
}


void SaveInitialLoadGUIDataDialog::on_pushButtonUseAll_clicked()
{
	TmpData.RemoveAll();
    for(GUIDataList *g=AllComponentsData.GetFirst();g!=NULL;g=AllComponentsData.GetRingNext(g)){
        GUIDataList *newdata = new GUIDataList;
        *newdata = *g;
        TmpData.AppendList(newdata);
    }
	ShowManagedTable();
}


void SaveInitialLoadGUIDataDialog::on_pushButtonReturnAll_clicked()
{
    TmpData.RemoveAll();
    ShowManagedTable();
}


void SaveInitialLoadGUIDataDialog::on_pushButtonOK_clicked()
{
	Parent->Data = TmpData;
    done(true);
}


void SaveInitialLoadGUIDataDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


void SaveInitialLoadGUIDataDialog::on_pushButtonSaveData_clicked()
{
    Parent->Data = TmpData;
    Parent->SaveData();
}
