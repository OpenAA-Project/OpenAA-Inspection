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

#include "SelectDispatchDialog.h"
#include "ui_SelectDispatchDialog.h"
#include "XDataInLayer.h"

MasterButton::MasterButton(int _ID ,QWidget *obj)
    :QPushButton(obj),ID(_ID)
{
    connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}
void    MasterButton::SlotClicked()
{
    emit    SignalClicked(ID);
}


SelectDispatchDialog::SelectDispatchDialog(LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SelectDispatchDialog)
{
    ui->setupUi(this);
    MasterNo=0;
    CountMasterButton=GetLayersBase()->GetCountBufferInfo();
    int Y=0;
    int H=40;
    MasterButtonDim=new MasterButton*[CountMasterButton];
    for(int i=0;i<CountMasterButton;i++){
        MasterButtonDim[i]=new MasterButton(i);
        MasterButtonDim[i]->setParent(this);
        MasterButtonDim[i]->setGeometry(0,Y,width(),H);
        BufferInfoList	*L=GetLayersBase()->GetBufferInfo(i);
        if(L!=NULL){
        	MasterButtonDim[i]->setText(L->BufferName);
        }
        connect(MasterButtonDim[i],SIGNAL(SignalClicked(int)),this,SLOT(SlotMasterChanged(int)));
        Y+=H;
    }
    resize(width(),Y);
}

SelectDispatchDialog::~SelectDispatchDialog()
{
    for(int i=0;i<CountMasterButton;i++){
        MasterButtonDim[i]->deleteLater();
    }
    delete  []MasterButtonDim;
    MasterButtonDim=NULL;

    delete ui;
}

void SelectDispatchDialog::SlotMasterChanged(int ID)
{
    MasterNo=ID;
    done(true);
}