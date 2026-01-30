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

#include "SettingCameraDialog.h"
#include "ui_SettingCameraDialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "math.h"
#include "CLHS_PX8CommandCreater.h"
#include "sapClassBasic.h"
#include "featureCtrl.h"

SettingCameraDialog::SettingCameraDialog(CLHS_PX8Setting *s ,featureCtrl *f ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingCameraDialog)
{
    ui->setupUi(this);
	Setting		=s;
	Feature		=f;
	Setting->LoadFromCam(Feature);

	ui->spinBoxStartPos				->setValue(Setting->StartPos);
	ui->spinBoxRefStart				->setValue(Setting->RefStart);
	ui->spinBoxBindedPixels			->setValue(Setting->BindedPixels);

	ui->spinBoxLineRate				->setValue(Setting->LineRate);
	ui->doubleSpinBoxExposureTime	->setValue(Setting->ExposureTime);
	ui->checkBoxDirection			->setChecked(Setting->TDIDirection);
	ui->doubleSpinBoxGainRed		->setValue(Setting->GainRed);
	ui->spinBoxOffsetRed			->setValue(Setting->OffsetRed);
	ui->spinBoxHorizontalBinning	->setValue(Setting->HorizontalBinning);
	ui->spinBoxVerticalBinning		->setValue(Setting->VerticalBinning);
	ui->checkBoxLeftRight			->setChecked(Setting->LeftRight);
	ui->checkBoxExternalTrigger		->setChecked(Setting->ExternalTrigger);
}

SettingCameraDialog::~SettingCameraDialog()
{
    delete ui;
}

void SettingCameraDialog::on_pushButtonOK_clicked()
{
	Setting->StartPos		=ui->spinBoxStartPos			->value();
	Setting->RefStart		=ui->spinBoxRefStart			->value();
	Setting->BindedPixels	=ui->spinBoxBindedPixels		->value();

	Setting->LineRate		=ui->spinBoxLineRate			->value();
	Setting->ExposureTime	=ui->doubleSpinBoxExposureTime	->value();
	Setting->TDIDirection	=ui->checkBoxDirection			->isChecked();

	Setting->GainRed		=ui->doubleSpinBoxGainRed		->value();
	Setting->OffsetRed		=ui->spinBoxOffsetRed			->value();

	Setting->HorizontalBinning	=ui->spinBoxHorizontalBinning	->value();
	Setting->VerticalBinning	=ui->spinBoxVerticalBinning		->value();
	Setting->LeftRight			=ui->checkBoxLeftRight			->isChecked();
	Setting->ExternalTrigger	=ui->checkBoxExternalTrigger	->isChecked();
	Setting->StoreToCam(Feature);

	done(true);
}
