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

#include "SelectAlgorithmDialog.h"
#include "ui_SelectAlgorithmDialog.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"

SelectAlgorithmDialog::SelectAlgorithmDialog(LayersBase *base
                                            ,const RootNameListContainer &_Selected
                                            ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,Selected(_Selected)
    ,ui(new Ui::SelectAlgorithmDialog)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidgetAlgorithm ,0, 10);
    ::SetColumnWidthInTable(ui->tableWidgetAlgorithm ,1, 40);
    ::SetColumnWidthInTable(ui->tableWidgetAlgorithm ,2, 40);

    int N=GetLayersBase()->GetLogicDLLBase()->GetCount();
    ui->tableWidgetAlgorithm->setRowCount(N);
    int row=0;
    for(LogicDLL *a=GetLayersBase()->GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext(),row++){
        bool    C=Selected.Exists(a->GetDLLRoot(),a->GetDLLName());
        ::SetDataToTableCheckable(ui->tableWidgetAlgorithm,0, row, /**/"",C);
        //AlgorithmBase   *ABase=a->GetInstance();
        //QString AlgoName=ABase->GetNameByCurrentLanguage();
        //::SetDataToTable(ui->tableWidgetAlgorithm,1, row,AlgoName);
        ::SetDataToTable(ui->tableWidgetAlgorithm,1, row,a->GetDLLRoot());
        ::SetDataToTable(ui->tableWidgetAlgorithm,2, row,a->GetDLLName());
    }
}

SelectAlgorithmDialog::~SelectAlgorithmDialog()
{
    delete ui;
}

void SelectAlgorithmDialog::resizeEvent(QResizeEvent *event)
{
    ui->frame->move(0,height()-ui->frame->height());
    ui->tableWidgetAlgorithm->resize(ui->tableWidgetAlgorithm->width()
                                    ,height()-ui->frame->height()-10);
}

void SelectAlgorithmDialog::on_pushButtonAll_clicked()
{
    bool    Checked=false;
    int row=0;
    for(LogicDLL *a=GetLayersBase()->GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext(),row++){
        bool    C=GetCheckedFromTable(ui->tableWidgetAlgorithm,0, row);
        if(C==true){
            Checked=true;
        }
    }

    row=0;
    for(LogicDLL *a=GetLayersBase()->GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext(),row++){
        ::SetDataToTableCheckable(ui->tableWidgetAlgorithm,0, row, /**/"",!Checked);
    }
}


void SelectAlgorithmDialog::on_pushButtonSelectOK_clicked()
{
    RootNameListContainer   Ret;
    int row=0;
    for(LogicDLL *a=GetLayersBase()->GetLogicDLLBase()->GetFirst();a!=NULL;a=a->GetNext(),row++){
        bool    C=GetCheckedFromTable(ui->tableWidgetAlgorithm,0, row);
        if(C==true){
            Ret.Add(a->GetDLLRoot(),a->GetDLLName());
        }
    }
    Selected=Ret;
    done(true);
}


void SelectAlgorithmDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
