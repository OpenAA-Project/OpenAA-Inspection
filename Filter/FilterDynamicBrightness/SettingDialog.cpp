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
#include "FilterDynamicBrightness.h"

SettingDialog::SettingDialog(LayersBase *base,FilterDynamicBrightness *v ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,FParent(v)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    ui->spinBoxCheckPointX      ->setValue(v->CheckPointX);
    ui->spinBoxCheckPointWidth  ->setValue(v->CheckPointWidth);
    ui->spinBoxStartX       ->setValue(v->ExeX1);
    ui->spinBoxEndX         ->setValue(v->ExeX2);
    ui->doubleSpinBoxGainP  ->setValue(v->GainP);
    ui->doubleSpinBoxGainM  ->setValue(v->GainM);
    ui->doubleSpinBoxStatic ->setValue(v->StaticBrightness);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
    FParent->CheckPointX        =ui->spinBoxCheckPointX     ->value();
    FParent->CheckPointWidth    =ui->spinBoxCheckPointWidth ->value();
    FParent->ExeX1              =ui->spinBoxStartX          ->value();
    FParent->ExeX2              =ui->spinBoxEndX            ->value();
    FParent->GainP              =ui->doubleSpinBoxGainP     ->value();
    FParent->GainM              =ui->doubleSpinBoxGainM     ->value();
    FParent->StaticBrightness   =ui->doubleSpinBoxStatic    ->value();
    done(true);
}


void SettingDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
