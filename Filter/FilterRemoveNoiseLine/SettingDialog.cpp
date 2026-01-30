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

#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterRemoveNoiseLine.h"

SettingDialog::SettingDialog(LayersBase *base,FilterRemoveNoiseLine *v ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	FParent=v;

	ui->comboBoxNoiseLineH	->setCurrentIndex((FParent->NoiseLineH==true)?0:1);
	ui->spinBoxNoiseLineWidth	->setValue(FParent->NoiseLineWidth);
	ui->spinBoxThresholdL		->setValue(FParent->ThresholdL);
	ui->spinBoxThresholdH		->setValue(FParent->ThresholdH);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	FParent->NoiseLineH		=(ui->comboBoxNoiseLineH	->currentIndex()==0)?true:false;
	FParent->NoiseLineWidth	=ui->spinBoxNoiseLineWidth	->value();
	FParent->ThresholdL		=ui->spinBoxThresholdL		->value();
	FParent->ThresholdH		=ui->spinBoxThresholdH		->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}