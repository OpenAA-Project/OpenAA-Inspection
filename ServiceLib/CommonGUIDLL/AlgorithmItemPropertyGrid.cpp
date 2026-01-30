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

#include "CommonGUIDLLResource.h"

#include "AlgorithmItemPropertyGrid.h"
#include "ui_AlgorithmItemPropertyGrid.h"

AlgorithmItemPropertyGrid::AlgorithmItemPropertyGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlgorithmItemPropertyGrid)
{
    ui->setupUi(this);
}

AlgorithmItemPropertyGrid::~AlgorithmItemPropertyGrid()
{
    delete ui;
}


void AlgorithmItemPropertyGrid::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void	AlgorithmItemPropertyGrid::ShowGrid(const AlgorithmItemPropertyContainer &_AlgorithmItemPropertyData)
{
    ItemLines.RemoveAll();
    AlgorithmItemPropertyData=_AlgorithmItemPropertyData;
    for(AlgorithmItemPropertyBase *a=AlgorithmItemPropertyData.GetFirst();a!=NULL;a=a->GetNext()){
        for(ParamBase::ParamStruct *t=a->GetParamData().GetFirst();t!=NULL;t=t->GetNext()){
            QString	V=t->GetValue();
            bool	FoundB=false;
            for(AlgorithmItemPropertyLine *b=ItemLines.GetFirst();b!=NULL && FoundB==false;b=b->GetNext()){
                if(b->CategoryName==t->Category && b->PropertyName==t->Name){
                    int i;
                    for(i=0;i<b->Values.count();i++){
                        if(V==b->Values.value(i)){
                            break;
                        }
                    }
                    if(i>=b->Values.count()){
                        b->Values.append(V);
                    }
                    FoundB=true;
                }
            }
            if(FoundB==false){
                AlgorithmItemPropertyLine *b=new AlgorithmItemPropertyLine();
                b->CategoryName=t->Category;
                b->PropertyName=t->Name;
                b->Values.append(V);
                ItemLines.AppendList(b);
            }
        }
    }
    ui->tableWidget->setRowCount(ItemLines.GetNumber());
    int	row=0;
    for(AlgorithmItemPropertyLine *c=ItemLines.GetFirst();c!=NULL;c=c->GetNext()){
        QTableWidgetItem *W;
        W=ui->tableWidget->item ( row, 0);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidget->setItem ( row, 0,W);
            W->setFlags(Qt::ItemIsEnabled);
        }
        W->setText(c->CategoryName);

        W=ui->tableWidget->item ( row, 1);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidget->setItem ( row, 1,W);
            W->setFlags(Qt::ItemIsEnabled);
        }
        W->setText(c->PropertyName);

        W=ui->tableWidget->item ( row, 2);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidget->setItem ( row, 2,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
        }
        if(c->Values.count()==1){
            W->font().setBold(true);
        }
        else{
            W->font().setBold(false);
        }
        W->setText(c->Values.value(0));
        row++;
    }
}