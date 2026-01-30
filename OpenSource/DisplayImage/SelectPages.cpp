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


#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectPages.h"
#include "ui_SelectPages.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"


SelectPages::SelectPages(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SelectPages)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(base->GetLanguagePackageData(),base->GetLanguageCode());
    LangDISolver.SetUI(this);

    SetWidgetCenter(this);
    SelectedPages.RemoveAll();
    for(int page=0;page<GetPageNumb();page++){
        ui->listWidgetSelect->addItem(LangDISolver.GetString(SelectPages_LS,LID_11)/*"Page "*/+QString::number(page));
        QListWidgetItem *w=ui->listWidgetSelect->item (page);
        w->setData (Qt::UserRole,page);
    }

    QModelIndex	W=ui->listWidgetSelect->indexAt(QPoint(0,0));
    QRect Q=ui->listWidgetSelect->visualRect(W);
    int	H=(Q.height()+6+ui->listWidgetSelect->lineWidth())*GetPageNumb()+ui->listWidgetSelect->lineWidth();
    H+=10;
    if(H>110){
        resize(width(),H+60);
        ui->listWidgetSelect->resize(ui->listWidgetSelect->width(),H);
        ui->pushButtonSelect->move(ui->pushButtonSelect->geometry().left(),H+20);
    }

    InstallOperationLog(this);
}
SelectPages::SelectPages(LayersBase *base ,const IntList &Pages ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SelectPages)
{
    ui->setupUi(this);
    LangDISolver.SetUI(this);

    SetWidgetCenter(this);
    SelectedPages.RemoveAll();
    int	row=0;
    for(IntClass *p=Pages.GetFirst();p!=NULL;p=p->GetNext(),row++){
        int	page=p->GetValue();
        ui->listWidgetSelect->addItem(LangDISolver.GetString(SelectPages_LS,LID_12)/*"Page "*/+QString::number(page));
        QListWidgetItem *w=ui->listWidgetSelect->item (row);
        w->setData (Qt::UserRole,page);
    }
    if(row>0){
        QModelIndex	W=ui->listWidgetSelect->indexAt(QPoint(0,0));
        QRect Q=ui->listWidgetSelect->visualRect(W);
        int	H=(Q.height()+6+ui->listWidgetSelect->lineWidth())*row+ui->listWidgetSelect->lineWidth();
        H+=10;
        if(H>110){
            resize(width(),H+60);
            ui->listWidgetSelect->resize(ui->listWidgetSelect->width(),H);
            ui->pushButtonSelect->move(ui->pushButtonSelect->geometry().left(),H+20);
        }
    }
	InstallOperationLog(this);
}
SelectPages::~SelectPages()
{
    delete ui;
}

void SelectPages::on_pushButtonSelect_clicked()
{
    QList<QListWidgetItem *> R=ui->listWidgetSelect->selectedItems();
    for(int i=0;i<R.count();i++){
        QListWidgetItem *w=R.value(i);
        int	page=w->data(Qt::UserRole).toInt();
        SelectedPages.Add(page);
    }
    done(true);
}

void SelectPages::on_listWidgetSelect_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void SelectPages::on_pushButtonAll_clicked()
{
    for(int row=0;row<ui->listWidgetSelect->count();row++){
        QListWidgetItem *w= ui->listWidgetSelect->item(row);
        if(w!=NULL){
            w->setSelected(true);
        }
    }
}

void SelectPages::on_pushButtonRelease_clicked()
{
    for(int row=0;row<ui->listWidgetSelect->count();row++){
        QListWidgetItem *w= ui->listWidgetSelect->item(row);
        if(w!=NULL){
            w->setSelected(false);
        }
    }
}