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

#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterMergeColor.h"

SettingDialog::SettingDialog(LayersBase *base,FilterMergeColor *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),Parent(p),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    ui->doubleSpinBoxR1 ->setValue(Parent->R1);
    ui->doubleSpinBoxB1 ->setValue(Parent->B1);
    ui->doubleSpinBoxR2 ->setValue(Parent->R2);
    ui->doubleSpinBoxB2 ->setValue(Parent->B2);
    ui->doubleSpinBoxGain->setValue(Parent->Gain);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
    Parent->R1      =ui->doubleSpinBoxR1 ->value();
    Parent->B1      =ui->doubleSpinBoxB1 ->value();
    Parent->R2      =ui->doubleSpinBoxR2 ->value();
    Parent->B2      =ui->doubleSpinBoxB2 ->value();
    Parent->Gain    =ui->doubleSpinBoxGain->value();
    done(true);
}


void SettingDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
