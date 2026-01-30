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

#include "SettingLogDialog.h"
#include "ui_SettingLogDialog.h"
#include "Maintainer.h"
#include <QFileDialog>

SettingLogDialog::SettingLogDialog(Maintainer *p,QWidget *parent) :
    QDialog(parent)
	,Parent(p)
    ,ui(new Ui::SettingLogDialog)
{
    ui->setupUi(this);

	ui->lineEditLogFileName->setText(Parent->LogFileName);
}

SettingLogDialog::~SettingLogDialog()
{
    delete ui;
}

void SettingLogDialog::on_pushButtonSelectFile_clicked()
{
	QString	FileName	=QFileDialog::getOpenFileName(NULL,"Log file name"
									,QString()
									,QString(/**/"Maintainer.log;;Log file(*.log);;All files(*.*)"));
	if(FileName.isEmpty()==false){
		ui->lineEditLogFileName->setText(FileName);
	}
}

void SettingLogDialog::on_pushButtonOK_clicked()
{
	Parent->LogFileName	=ui->lineEditLogFileName->text();
	done(true);
}

void SettingLogDialog::on_pushButtonCancel_clicked()
{
	done(false);
}