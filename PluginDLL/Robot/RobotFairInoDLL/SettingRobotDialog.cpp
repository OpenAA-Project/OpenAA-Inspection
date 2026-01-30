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

#include "SettingRobotDialog.h"
#include "ui_SettingRobotDialog.h"

SettingRobotDialog::SettingRobotDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SettingRobotDialog)
{
    ui->setupUi(this);

    IPAddress           =/**/"192.168.58.2";
    velPercentage       =30;
    accPercentage       =30;
    max_disPercentage   =20;
}

SettingRobotDialog::~SettingRobotDialog()
{
    delete ui;
}

void    SettingRobotDialog::Initial(void)
{
    ui->lineEditIPAddress           ->setText(IPAddress);
    ui->doubleSpinBoxSpeed          ->setValue(velPercentage);
    ui->doubleSpinBoxAccel          ->setValue(accPercentage);
    ui->doubleSpinBoxMaxDisPercent  ->setValue(max_disPercentage);
}

void SettingRobotDialog::on_pushButtonOK_clicked()
{
    IPAddress           =ui->lineEditIPAddress           ->text();
    velPercentage       =ui->doubleSpinBoxSpeed          ->value();
    accPercentage       =ui->doubleSpinBoxAccel          ->value();
    max_disPercentage   =ui->doubleSpinBoxMaxDisPercent  ->value();
    done(true);
}


void SettingRobotDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
