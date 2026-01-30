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

#include "AllocateIODialog.h"
#include "ui_AllocateIODialog.h"
#include "LEDControl16JioPrnRasPIMain.h"

AllocateIODialog::AllocateIODialog(LEDControl16JioPrnRasPIMain *p, QWidget *parent) :
    QDialog(parent),Parent(p),
    ui(new Ui::AllocateIODialog)
{
    ui->setupUi(this);

    int  N=sizeof(Parent->JioData.AllocateGOut)/sizeof(Parent->JioData.AllocateGOut[0]);
    ui->comboBoxGOut0->setCurrentIndex(Parent->JioData.AllocateGOut[0]);
    ui->comboBoxGOut1->setCurrentIndex(Parent->JioData.AllocateGOut[1]);
    ui->comboBoxGOut2->setCurrentIndex(Parent->JioData.AllocateGOut[2]);
    ui->comboBoxGOut3->setCurrentIndex(Parent->JioData.AllocateGOut[3]);
    ui->comboBoxGOut4->setCurrentIndex(Parent->JioData.AllocateGOut[4]);
    ui->comboBoxGOut5->setCurrentIndex(Parent->JioData.AllocateGOut[5]);
    ui->comboBoxGOut6->setCurrentIndex(Parent->JioData.AllocateGOut[6]);
    ui->comboBoxGOut7->setCurrentIndex(Parent->JioData.AllocateGOut[7]);
}

AllocateIODialog::~AllocateIODialog()
{
    delete ui;
}

void AllocateIODialog::on_pushButtonOK_clicked()
{
    Parent->JioData.AllocateGOut[0]=ui->comboBoxGOut0->currentIndex();
    Parent->JioData.AllocateGOut[1]=ui->comboBoxGOut1->currentIndex();
    Parent->JioData.AllocateGOut[2]=ui->comboBoxGOut2->currentIndex();
    Parent->JioData.AllocateGOut[3]=ui->comboBoxGOut3->currentIndex();
    Parent->JioData.AllocateGOut[4]=ui->comboBoxGOut4->currentIndex();
    Parent->JioData.AllocateGOut[5]=ui->comboBoxGOut5->currentIndex();
    Parent->JioData.AllocateGOut[6]=ui->comboBoxGOut6->currentIndex();
    Parent->JioData.AllocateGOut[7]=ui->comboBoxGOut7->currentIndex();
    done(true);
}

void AllocateIODialog::on_pushButtonCancel_clicked()
{
    done(false);
}