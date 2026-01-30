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

#include "ShowCameraDialog.h"
#include "ui_ShowCameraDialog.h"

ShowCameraDialog::ShowCameraDialog(CameraMVSGigE *Cam,QWidget *parent) :
    QDialog(parent)
    ,Parent(Cam)
    ,ui(new Ui::ShowCameraDialog)
{
    ui->setupUi(this);

	ExposureTime			=Cam->ExposureTime			;
	Gain					=Cam->Gain					;
	FrameRate				=Cam->FrameRate				;
	bSoftWareTriggerCheck	=Cam->bSoftWareTriggerCheck	;
	TriggerSource			=Cam->TriggerSource			;
    TriggerMode				=Cam->TriggerMode			;
    TriggerSource			=Cam->TriggerSource			;


	float	CurrentValue ,MaxValue ,MinValue;
	if(Cam->GetfloatValue("ExposureTime",CurrentValue ,MaxValue ,MinValue)==true){
		ui->spinBoxExposureTime	->setMaximum(MaxValue);
	}
	if(Cam->GetfloatValue("Gain",CurrentValue ,MaxValue ,MinValue)==true){
		ui->doubleSpinBoxGain	->setMaximum(MaxValue);
	}

	ui->spinBoxExposureTime	->setValue(ExposureTime);
	ui->doubleSpinBoxGain			->setValue(Gain);
}

ShowCameraDialog::~ShowCameraDialog()
{
    delete ui;
}

void ShowCameraDialog::on_pushButtonOK_clicked()
{
	ExposureTime	=ui->spinBoxExposureTime	->value();
	Gain			=ui->doubleSpinBoxGain		->value();
	done(true);
}


void ShowCameraDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
