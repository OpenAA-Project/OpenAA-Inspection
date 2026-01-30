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

#include "SettingResolutionDialog.h"
#include "ui_SettingResolutionDialog.h"

SettingResolutionDialog::SettingResolutionDialog(double _XZoom ,double _YZoom ,int _Cx ,int _Cy
                                                ,LayersBase *Base
                                                ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SettingResolutionDialog)
{
    ui->setupUi(this);

    ui->doubleSpinBoxXZoom  ->setValue(_XZoom);
    ui->doubleSpinBoxYZoom  ->setValue(_YZoom);
    ui->spinBoxCx           ->setValue(_Cx);
    ui->spinBoxCy           ->setValue(_Cy);
}

SettingResolutionDialog::~SettingResolutionDialog()
{
    delete ui;
}

void SettingResolutionDialog::on_pushButtonOK_clicked()
{
    XZoom   =ui->doubleSpinBoxXZoom  ->value();
    YZoom   =ui->doubleSpinBoxYZoom  ->value();
    Cx      =ui->spinBoxCx           ->value();
    Cy      =ui->spinBoxCy           ->value();
    done(true);
}

void SettingResolutionDialog::on_pushButtonCancel_clicked()
{
    done(false);
}