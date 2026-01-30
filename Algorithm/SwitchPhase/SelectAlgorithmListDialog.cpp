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

#include "SwitchPhaseResource.h"
#include "SelectAlgorithmListDialog.h"
#include "ui_SelectAlgorithmListDialog.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

SelectAlgorithmListDialog::SelectAlgorithmListDialog(LayersBase *Base,SwitchPhaseBase *p ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,Parent(p)
    ,ui(new Ui::SelectAlgorithmListDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    ::SetColumnWidthInTable(ui->tableWidgetAlgorithmList,0, 50);
    ::SetColumnWidthInTable(ui->tableWidgetAlgorithmList,1, 50);

    CopiedAlgorithmDim=Parent->CopiedAlgorithmDim;
    ::SetColumnWidthInTable(ui->tableWidgetOperationList,0, 50);
    ::SetColumnWidthInTable(ui->tableWidgetOperationList,1, 50);

    ShowSrcList();
    ShowDestList();
}

SelectAlgorithmListDialog::~SelectAlgorithmListDialog()
{
    delete ui;
}

void SelectAlgorithmListDialog::ShowSrcList(void)
{
    int SN=GetLayersBase()->GetLogicDLLBase()->GetCount();
    ui->tableWidgetAlgorithmList->setRowCount(SN);
    int Row=0;
    for(LogicDLL *s=GetLayersBase()->GetLogicDLLBase()->GetFirst();s!=NULL;s=s->GetNext(),Row++){
        ::SetDataToTable(ui->tableWidgetAlgorithmList, 0, Row, s->GetDLLRoot());
        ::SetDataToTable(ui->tableWidgetAlgorithmList, 1, Row, s->GetDLLName());
    }
}
void SelectAlgorithmListDialog::ShowDestList(void)
{
    int DN=CopiedAlgorithmDim.GetCount();
    ui->tableWidgetOperationList->setRowCount(DN);
    int n=0;
    for(n=0;n<DN;n++){
        RootNameList *RList=CopiedAlgorithmDim.GetItem(n);
        ::SetDataToTable(ui->tableWidgetOperationList, 0, n, RList->DLLRoot);
        ::SetDataToTable(ui->tableWidgetOperationList, 1, n, RList->DLLName);
    }
}

void SelectAlgorithmListDialog::on_tableWidgetAlgorithmList_doubleClicked(const QModelIndex &index)
{
    on_pushButtonGet_clicked();
}

void SelectAlgorithmListDialog::on_tableWidgetOperationList_doubleClicked(const QModelIndex &index)
{
    on_pushButtonReturn_clicked();
}

void SelectAlgorithmListDialog::on_pushButtonGet_clicked()
{
    int Row=ui->tableWidgetAlgorithmList->currentRow();
    if(Row<0)
        return;
    LogicDLL *s=GetLayersBase()->GetLogicDLLBase()->GetItem(Row);
    if(s!=NULL){
        CopiedAlgorithmDim.Merge(s->GetDLLRoot(),s->GetDLLName());
        ShowDestList();
    }
}

void SelectAlgorithmListDialog::on_pushButtonReturn_clicked()
{
    int Row=ui->tableWidgetOperationList->currentRow();
    if(Row<0)
        return;
    RootNameList *RList=CopiedAlgorithmDim.GetItem(Row);
    CopiedAlgorithmDim.RemoveList(RList);
    ShowDestList();
}

void SelectAlgorithmListDialog::on_pushButtonOK_clicked()
{
    done(true);
}

void SelectAlgorithmListDialog::on_pushButtonCancel_clicked()
{
    done(false);
}