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

#include "EditGUILibResource.h"
#include "XTypeDef.h"

#include "EditFilterBank.h"
#include "ui_EditFilterBank.h"
#include "XGeneralDialog.h"
#include "Regulus64Version.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

EditFilterBank::EditFilterBank(LayersBase *base ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditFilterBank)
{
    ui->setupUi(this);

    FilterFileNames=GetLayersBase()->GetParamGlobal()->FilterBankFileNames;
    ui->tableWidgetFilter->setColumnWidth(0,70);
    ui->tableWidgetFilter->setColumnWidth(1,240);
    ShowGrid();
}

EditFilterBank::~EditFilterBank()
{
    delete ui;
}

void	EditFilterBank::ShowGrid(void)
{
    ui->tableWidgetFilter->setRowCount(FilterFileNames.count());

    for(int r=0;r<FilterFileNames.count();r++){
        QTableWidgetItem *W;
        W=ui->tableWidgetFilter->item ( r, 0);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetFilter->setItem ( r, 0,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(LangSolverGUILib.GetString(EditFilterBank_LS,LID_16)/*"Filter "*/
                +  QString::number(r+1));

        W=ui->tableWidgetFilter->item ( r, 1);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetFilter->setItem ( r, 1,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(FilterFileNames.value(r));
    }
}

void EditFilterBank::on_tableWidgetFilter_doubleClicked(const QModelIndex &index)
{
    /*
    if(GetLayersBase()->FilterBank==NULL){
        FilterBank=new
    int	Index=ui->tableWidgetFilter->currentRow();
    if(Index>=0){
        WTab = new WEditParameterTab(pbase ,this);
    */
}

void EditFilterBank::on_pushButtonOK_clicked()
{
    GetLayersBase()->GetParamGlobal()->FilterBankFileNames=FilterFileNames;
    emit	SignalClose();
    close();
}

void EditFilterBank::on_pushButtonCancel_clicked()
{
    emit	SignalClose();
    close();
}

void EditFilterBank::on_pushButtonLoadFiles_clicked()
{
    QStringList FileList=GetLayersBase()->LGetOpenFileNames (0
                                            , LangSolverGUILib.GetString(EditFilterBank_LS,LID_17)/*"Filter file names"*/
                                            , /**/""
                                            , /**/"Filter(*.dll *.so)");
    for(int i=0;i<FileList.count();i++){
        FilterFileNames.append(FileList.value(i));
        ShowGrid();
    }
}

void EditFilterBank::on_pushButtonUp_clicked()
{
    const   int	Index=ui->tableWidgetFilter->currentRow();
    if(Index>0){
        QString s1=FilterFileNames[Index];
        FilterFileNames[Index]=FilterFileNames[Index-1];
        FilterFileNames[Index-1]=s1;
        //FilterFileNames.swap(Index,Index-1);
        ShowGrid();
    }
}

void EditFilterBank::on_pushButtonDown_clicked()
{
    const   int	Index=ui->tableWidgetFilter->currentRow();
    if((Index+1)<ui->tableWidgetFilter->rowCount()){
        QString s=FilterFileNames[Index];
        FilterFileNames[Index]=FilterFileNames[Index+1];
        FilterFileNames[Index+1]=s;
        //FilterFileNames.swap(Index,Index+1);
        ShowGrid();
    }
}

void EditFilterBank::on_pushButtonDelete_clicked()
{
    const   int	Index=ui->tableWidgetFilter->currentRow();
    if(Index>=0){
        FilterFileNames.removeAt(Index);
        ShowGrid();
    }
}