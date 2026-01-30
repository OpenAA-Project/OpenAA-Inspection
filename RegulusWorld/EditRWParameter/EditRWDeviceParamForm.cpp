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

#include "EditRWDeviceParamForm.h"
#include "ui_EditRWDeviceParamForm.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XRegulusWorld.h"

EditRWDeviceParamForm::EditRWDeviceParamForm(LayersBase *base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditRWDeviceParamForm)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidgetDeviceList,0, 15);
    ::SetColumnWidthInTable(ui->tableWidgetDeviceList,1, 42);
    ::SetColumnWidthInTable(ui->tableWidgetDeviceList,2, 42);
}

EditRWDeviceParamForm::~EditRWDeviceParamForm()
{
    delete ui;
}
    
void	EditRWDeviceParamForm::Show(void)
{
    RegulusWorld	*R=GetRegulusWorld(GetLayersBase());
    ui->tableWidgetDeviceList->setRowCount(R->GetParamRegulusWorld()->RWDeviceParams.GetCount());
    int row=0;
    for(RWDeviceParamList *w=R->GetParamRegulusWorld()->RWDeviceParams.GetFirst();w!=NULL;w=w->GetNext(),row++){
        ::SetDataToTable(ui->tableWidgetDeviceList, 0, row, QString::number(w->DeviceID));
        ::SetDataToTable(ui->tableWidgetDeviceList, 1, row, w->DLLFileName);
        ::SetDataToTable(ui->tableWidgetDeviceList, 2, row, w->Parameter);
    }
}

void	EditRWDeviceParamForm::LoadFromWindow(void)
{
    RegulusWorld	*R=GetRegulusWorld(GetLayersBase());
    R->GetParamRegulusWorld()->RWDeviceParams.RemoveAll();
    int N=ui->tableWidgetDeviceList->rowCount();
    for(int row=0;row<N;row++){
        RWDeviceParamList   *w=new RWDeviceParamList();
        QString DeviceIDStr =::GetDataToTable(ui->tableWidgetDeviceList, 0, row);
        w->DeviceID =DeviceIDStr.toInt();
        w->DLLFileName      =::GetDataToTable(ui->tableWidgetDeviceList, 1, row);
        w->Parameter        =::GetDataToTable(ui->tableWidgetDeviceList, 2, row);
        R->GetParamRegulusWorld()->RWDeviceParams.AppendList(w);
    }
}

void EditRWDeviceParamForm::on_tableWidgetDeviceList_itemSelectionChanged()
{
    int row=ui->tableWidgetDeviceList->currentRow();
    if(row<0)
        return;
    QString DeviceIDStr =::GetDataToTable(ui->tableWidgetDeviceList, 0, row);
    int DeviceID =DeviceIDStr.toInt();
    ui->spinBoxDeviceID ->setValue(DeviceID);
    ui->lineEditDLLFileName ->setText(::GetDataToTable(ui->tableWidgetDeviceList, 1, row));
    ui->lineEditParameter   ->setText(::GetDataToTable(ui->tableWidgetDeviceList, 2, row));
}

void EditRWDeviceParamForm::on_tableWidgetDeviceList_clicked(const QModelIndex &index)
{
    on_tableWidgetDeviceList_itemSelectionChanged();
}

void EditRWDeviceParamForm::on_pushButtonAddLine_clicked()
{
    int N=ui->tableWidgetDeviceList->rowCount();
    ui->tableWidgetDeviceList->setRowCount(N+1);
}

void EditRWDeviceParamForm::on_pushButtonDelLine_clicked()
{
    int row=ui->tableWidgetDeviceList->currentRow();
    if(row<0)
        return;
    ui->tableWidgetDeviceList->removeRow(row);
}

void EditRWDeviceParamForm::on_pushButtonSelectFile_clicked()
{
    QString	 fileName=GetLayersBase()->LGetOpenFileName (NULL, /**/"", QString(), QString(/**/"dll(*.dll);;AllFile(*.*)"));
    if(fileName.isEmpty()==false){
        ui->lineEditDLLFileName ->setText(fileName);
    }
}

void EditRWDeviceParamForm::on_pushButtonSet_clicked()
{
    int row=ui->tableWidgetDeviceList->currentRow();
    int DeviceID=ui->spinBoxDeviceID ->value();
    ::SetDataToTable(ui->tableWidgetDeviceList, 0, row, QString::number(DeviceID));
    ::SetDataToTable(ui->tableWidgetDeviceList, 1, row,  ui->lineEditDLLFileName ->text());
    ::SetDataToTable(ui->tableWidgetDeviceList, 2, row,  ui->lineEditParameter   ->text());
}
