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
#include "SelectByOrigin.h"
#include "ui_SelectByOrigin.h"
#include "XGeneralFunc.h"
#include "XDisplayImagePacket.h"

SelectByOrigin::SelectByOrigin(LayersBase *Base,NPListPack<OriginNames>	&originNameList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectByOrigin)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);

    SetWidgetCenter(this);

    Selected=NULL;
    OriginNameList.RemoveAll();
    for(OriginNames *v=originNameList.GetFirst();v!=NULL;v=v->GetNext()){
        OriginNames	*d=new OriginNames();
        *d=*v;
        OriginNameList.AppendList(d);
    }
    ui->tableWidget->setRowCount(OriginNameList.GetNumber());
    int	Row=0;
    for(OriginNames *v=OriginNameList.GetFirst();v!=NULL;v=v->GetNext(),Row++){
        QTableWidgetItem *w;
        w=ui->tableWidget->item (Row, 0);
        if(w==NULL){
            ui->tableWidget->setItem(Row,0,(w=new QTableWidgetItem()));
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        w->setText(v->DLLRoot);

        w=ui->tableWidget->item (Row, 1);
        if(w==NULL){
            ui->tableWidget->setItem(Row,1,(w=new QTableWidgetItem()));
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        w->setText(v->DLLName);

        w=ui->tableWidget->item (Row, 2);
        if(w==NULL){
            ui->tableWidget->setItem(Row,2,(w=new QTableWidgetItem()));
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        w->setText(QString::number(v->Numb));
    }
    Base->InstallOperationLog(this);
}

SelectByOrigin::~SelectByOrigin()
{
    delete ui;
}

void SelectByOrigin::on_tableWidget_cellDoubleClicked(int row, int column)
{
    on_pushButtonSelect_clicked();
}

void SelectByOrigin::on_pushButtonSelect_clicked()
{
    int	r=ui->tableWidget->currentRow();
    if(r>=0){
        Selected=OriginNameList.GetItem(r);
        done((int)true);
    }
}

void SelectByOrigin::on_pushButtonCancel_clicked()
{
    done((int)false);
}