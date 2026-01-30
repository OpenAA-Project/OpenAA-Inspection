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

#include "SettingRecordDialog.h"
#include "ui_SettingRecordDialog.h"
#include "RecordMovie.h"

SettingRecordDialog::SettingRecordDialog(RecordMovie *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(p->GetLayersBase())
    ,RecordParent(p)
    ,ui(new Ui::SettingRecordDialog)
{
    ui->setupUi(this);

    if(AVFormatStr==/**/"MotionJPEG"){
        ui->radioButtonAVI->setChecked(true);
    }
    else 
    if(AVFormatStr==/**/"MPEG1"){
        ui->radioButtonMPEG1->setChecked(true);
    }
    ui->comboBoxCamMovieSize	->setCurrentIndex(MovieSizeMode);

	float	TargetFrameRate;
	bool	DivideMovieFile;
}

SettingRecordDialog::~SettingRecordDialog()
{
    delete ui;
}

void SettingRecordDialog::on_pushButtonOK_clicked()
{

}


void SettingRecordDialog::on_pushButtonCancel_clicked()
{

}


void SettingRecordDialog::on_radioButtonAVI_clicked()
{

}


void SettingRecordDialog::on_radioButtonMPEG1_clicked()
{

}
