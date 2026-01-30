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

#include "ExistItemVectorDialog.h"
#include "ui_ExistItemVectorDialog.h"
#include "SelectLibForValidationForm.h"
#include "XCheckDataValidation.h"

ExistItemVectorDialog::ExistItemVectorDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::ExistItemVectorDialog)
{
    ui->setupUi(this);


    SelectedLibType =-1;
    SelectedLibID   =-1;

    SelectLibPanel=new SelectLibForValidationForm(Base);
    SelectLibPanel->setParent(ui->frame);
    SelectLibPanel->move(0,0);
    connect(SelectLibPanel,SIGNAL(SignalSelectedLib(int ,int)),this,SLOT(SlotSelectedLib(int,int)));

    ui->pushButtonModify    ->setVisible(false);
    ui->pushButtonDelete    ->setVisible(false);
}

ExistItemVectorDialog::~ExistItemVectorDialog()
{
    delete ui;
}

void    ExistItemVectorDialog::SetCurrentItem(const CheckDataValidationExistItemVectorThreshold *RThr)
{
    ui->pushButtonModify    ->setVisible(true);
    ui->pushButtonDelete    ->setVisible(true);

    SelectedLibType =RThr->LibType;
    SelectedLibID   =RThr->LibID;

    SelectLibPanel->Initial(SelectedLibType, SelectedLibID);
    SlotSelectedLib(SelectedLibType,SelectedLibID);
}

void    ExistItemVectorDialog::GetCurrentItem(CheckDataValidationExistItemVectorThreshold *WThr)
{
    WThr->LibType=SelectedLibType;
    WThr->LibID  =SelectedLibID;
}

void    ExistItemVectorDialog::SlotSelectedLib(int LibType,int LibID)
{
    ui->spinBoxLibID    ->setValue(LibID);
    QString LibName=GetLayersBase()->GetLibraryName(LibType,LibID);
    ui->lineEditLibName ->setText(LibName);
    SelectedLibType =LibType;
    SelectedLibID   =LibID;
}

void ExistItemVectorDialog::on_pushButtonCreateNew_clicked()
{
    done(1);
}


void ExistItemVectorDialog::on_pushButtonModify_clicked()
{
    done(2);
}


void ExistItemVectorDialog::on_pushButtonDelete_clicked()
{
    done(3);
}


void ExistItemVectorDialog::on_pushButtonClose_clicked()
{
    done(-1);
}
