/*
 * Copyright (C) 2024
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

#include "EditEachPageLocalDialog.h"
#include "ui_EditEachPageLocalDialog.h"

EditEachPageLocalDialog::EditEachPageLocalDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditEachPageLocalDialog)
{
    ui->setupUi(this);

    OldPage=-1;

    for(int page=0;page<GetPageNumb();page++){
        ui->listWidgetPageList->addItem(QString(/**/"Page ")+QString::number(page));
    }

    if(GetParamGlobal()->CountOfPageLocal!=GetPageNumb()){
        GetParamGlobal()->ReallocPageLocal(GetPageNumb());
    }


    WTab = new WEditParameterTab(&GetParamGlobal()->PageLocalData[0] ,-1,ui->frameEachPageLocal);
    WTab->ShowToWindow();

    if(GetPageNumb()>0){
        ui->listWidgetPageList->setCurrentRow(0);
    }
    OldPage=0;
}

EditEachPageLocalDialog::~EditEachPageLocalDialog()
{
    delete ui;
}

void EditEachPageLocalDialog::on_ButtonOK_clicked()
{
    if(OldPage>=0){
        WTab->LoadFromWindow();
    }
    done(true);
}


void EditEachPageLocalDialog::on_listWidgetPageList_itemSelectionChanged()
{
    if(OldPage>=0){
        WTab->LoadFromWindow();
    }
    int page=ui->listWidgetPageList->currentRow();
    if(page>=0){
        WTab->Set(&GetParamGlobal()->PageLocalData[page],-1);
        OldPage=page;
    }
}


void EditEachPageLocalDialog::on_listWidgetPageList_itemClicked(QListWidgetItem *item)
{
    on_listWidgetPageList_itemSelectionChanged();
}
