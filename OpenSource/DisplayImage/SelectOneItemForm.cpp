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

#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectOneItemForm.h"
#include "ui_SelectOneItemForm.h"
#include "XParamGlobal.h"
#include "XIntClass.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XDataAlgorithm.h"
#include "XGeneralFunc.h"

SelectOneItemForm::SelectOneItemForm(AlgorithmBase *Algo ,ListLayerIDLibNamePack &itemIDList ,QWidget *parent ,int _GlobalPage) :
    QDialog(parent)
    ,ServiceForLayers(Algo->GetLayersBase())
    ,ui(new Ui::SelectOneItemForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);
    GlobalPage=_GlobalPage;
    if(GlobalPage>=0){
        setWindowTitle(QString(/**/"Page ")+QString::number(GlobalPage));
    }
    else{
        setWindowTitle(/**/"");
    }

    ui->tableWidgetItem	->setColumnWidth(0,72);
    ui->tableWidgetItem	->setColumnWidth(1,72);
    ui->tableWidgetItem	->setColumnWidth(2,72);
    ui->tableWidgetItem	->setColumnWidth(3,200);
    ui->tableWidgetItem	->setColumnWidth(4,185);

    int	Row=0;
    ItemIDList=itemIDList;
    ui->tableWidgetItem->setRowCount(ItemIDList.GetCount());
    for(ListLayerIDLibName *d=itemIDList.GetFirst();d!=NULL;d=d->GetNext()){
        ::SetDataToTable(ui->tableWidgetItem ,0,Row ,QString::number(d->Layer));
        ::SetDataToTable(ui->tableWidgetItem ,1,Row ,QString::number(d->ID));
        ::SetDataToTable(ui->tableWidgetItem ,2,Row ,QString::number(d->LibID));
        QString	LibName=Algo->GetLibraryContainer()->GetLibraryName(d->LibID);
        ::SetDataToTable(ui->tableWidgetItem ,3,Row ,LibName);
        ::SetDataToTable(ui->tableWidgetItem ,4,Row ,d->ItemName);
        Row++;
    }
    if(Row>0){
        IntList Rows;
        Rows.Add(0);
        ::SetSelectedRows(ui->tableWidgetItem ,Rows);
    }

    InstallOperationLog(this);
}

SelectOneItemForm::~SelectOneItemForm()
{
    delete ui;
}

void SelectOneItemForm::on_pushButtonOK_clicked()
{
    int	Row=ui->tableWidgetItem->currentRow();
    if(Row>=0){
        ListLayerIDLibName	*c=ItemIDList.GetItem(Row);
        if(c!=NULL){
            SelectedItem.Layer=c->Layer;
            SelectedItem.ID=c->ID;
            done(true);
        }
    }
}

void SelectOneItemForm::on_tableWidgetItem_clicked(const QModelIndex &index)
{
    DisplayImageWithAlgorithm	*P=dynamic_cast<DisplayImageWithAlgorithm *>(parent());
    if(P!=NULL){
        P->ClearActivattionItems();
        int	Row=ui->tableWidgetItem->currentRow();
        if(Row>=0){
            ListLayerIDLibName	*c=ItemIDList.GetItem(Row);
            if(c!=NULL){
                P->SetActivateItem(GlobalPage ,c->Layer, c->ID);
                P->Repaint();
            }
        }
    }
}

void SelectOneItemForm::on_tableWidgetItem_doubleClicked(const QModelIndex &index)
{
    on_pushButtonOK_clicked();
}