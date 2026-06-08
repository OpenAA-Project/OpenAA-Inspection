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

#include "EditOrderDialog.h"
#include "ui_EditOrderDialog.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XGeneralFunc.h"

int SortFuncGDim(const void *a ,const void *b)
{
    GUIFormBase **ap=(GUIFormBase**)a;
    GUIFormBase **bp=(GUIFormBase**)b;

    int32   d=(*ap)->GetShowingOrder() - (*bp)->GetShowingOrder();

    return d;
}


EditOrderDialog::EditOrderDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::EditOrderDialog)
{
    ui->setupUi(this);

    GUIInitializer	*G=GetLayersBase()->GetGuiInitializer();
    
    GDimCount=0;
    for(GUIInstancePack	*Gp=G->GetGUIInstanceRoot();Gp!=NULL;Gp=Gp->GetNext()){
        for(GUIItemInstance *Gi=Gp->NPListPack<GUIItemInstance> ::GetFirst();Gi!=NULL;Gi=Gi->GetNext()){
            if(Gi->GetForm()!=NULL){
                GDimCount++;
            }
        }
    }
    GDim=new GUIFormBase*[GDimCount];
    int n=0;
    for(GUIInstancePack	*Gp=G->GetGUIInstanceRoot();Gp!=NULL;Gp=Gp->GetNext()){
        for(GUIItemInstance *Gi=Gp->NPListPack<GUIItemInstance> ::GetFirst();Gi!=NULL;Gi=Gi->GetNext()){
            if(Gi->GetForm()!=NULL){
                GDim[n]=Gi->GetForm();
                n++;
            }
        }
    }
    QSort(GDim,GDimCount,sizeof(GDim[0]),SortFuncGDim);

    ShowDim();
}

EditOrderDialog::~EditOrderDialog()
{
    delete ui;

    delete  []GDim;
    GDim=NULL;
}

void EditOrderDialog::ShowDim(void)
{
    ui->tableWidget->setRowCount(GDimCount);
    for(int i=0;i<GDimCount;i++){
        ::SetDataToTable(ui->tableWidget, 0, i, GDim[i]->GetDLLRoot());
        ::SetDataToTable(ui->tableWidget, 1, i, GDim[i]->GetDLLName());
        ::SetDataToTable(ui->tableWidget, 2, i, GDim[i]->GetName());
        ::SetDataToTable(ui->tableWidget, 3, i, QString::number(GDim[i]->GetShowingOrder()));
    }
}

void EditOrderDialog::on_pushButtonUp_clicked()
{
    int     Row=ui->tableWidget->currentRow();
    if(Row<1)
        return;
    GUIFormBase *c=GDim[Row-1];
    GDim[Row-1]=GDim[Row];
    GDim[Row]=c;
    ::SetCurrentRow(ui->tableWidget,Row-1);
    ShowDim();
}


void EditOrderDialog::on_pushButtonDown_clicked()
{
    int     Row=ui->tableWidget->currentRow();
    if(Row<0 || Row>=GDimCount-1)
        return;
    GUIFormBase *c=GDim[Row];
    GDim[Row]=GDim[Row+1];
    GDim[Row+1]=c;
    ::SetCurrentRow(ui->tableWidget,Row+1);
    ShowDim();
}


void EditOrderDialog::on_pushButtonOK_clicked()
{
    for(int i=0;i<GDimCount;i++){
        GDim[i]->SetShowingOrder(i);
    }
    close();
}
