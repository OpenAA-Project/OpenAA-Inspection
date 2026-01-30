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

#include "ExistItemAreaDialog.h"
#include "ui_ExistItemAreaDialog.h"
#include "SelectLibForValidationForm.h"
#include "XCheckDataValidation.h"

ExistItemAreaDialog::ExistItemAreaDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::ExistItemAreaDialog)
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

ExistItemAreaDialog::~ExistItemAreaDialog()
{
    delete ui;
}

void    ExistItemAreaDialog::SetCurrentItem(const CheckDataValidationExistItemAreaThreshold *RThr)
{
    ui->pushButtonModify    ->setVisible(true);
    ui->pushButtonDelete    ->setVisible(true);

    SelectedLibType =RThr->LibType;
    SelectedLibID   =RThr->LibID;
    
    SelectLibPanel->Initial(SelectedLibType, SelectedLibID);

    ui->doubleSpinBoxFilledPercentageInMask ->setValue(RThr->FilledPercentageInMask);
    ui->checkBoxCheckExistence              ->setChecked(RThr->CheckExistence);
    SlotSelectedLib(SelectedLibType,SelectedLibID);
}

void    ExistItemAreaDialog::GetCurrentItem(CheckDataValidationExistItemAreaThreshold *WThr)
{
    WThr->LibType=SelectedLibType;
    WThr->LibID  =SelectedLibID;
    WThr->FilledPercentageInMask    =ui->doubleSpinBoxFilledPercentageInMask ->value();
    WThr->CheckExistence            =ui->checkBoxCheckExistence ->isChecked();
}

void    ExistItemAreaDialog::SlotSelectedLib(int LibType,int LibID)
{
    ui->spinBoxLibID    ->setValue(LibID);
    QString LibName=GetLayersBase()->GetLibraryName(LibType,LibID);
    ui->lineEditLibName ->setText(LibName);

    SelectedLibType =LibType;
    SelectedLibID   =LibID;
}

void ExistItemAreaDialog::on_pushButtonCreateNew_clicked()
{
    FilledPercentageInMask  =ui->doubleSpinBoxFilledPercentageInMask->value();
    CheckExistence          =ui->checkBoxCheckExistence             ->isChecked();
    done(1);
}


void ExistItemAreaDialog::on_pushButtonModify_clicked()
{
    FilledPercentageInMask  =ui->doubleSpinBoxFilledPercentageInMask->value();
    CheckExistence          =ui->checkBoxCheckExistence             ->isChecked();
    done(2);
}


void ExistItemAreaDialog::on_pushButtonDelete_clicked()
{
    done(3);
}


void ExistItemAreaDialog::on_pushButtonClose_clicked()
{
    done(-1);
}
