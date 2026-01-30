/*
 * Copyright (C) 2017
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

#include "AutoStartEachParam.h"
#include <QFileDialog>

AutoStartEachParam::AutoStartEachParam(const QString &_ExeFilePath,const QString &_Parameters,const QString &_WorkingPath,int32	_Location ,int32 _BootingWaitTime
									   ,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ExeFilePath		=_ExeFilePath;
	Parameters		=_Parameters;
	WorkingPath		=_WorkingPath;
	Location		=_Location;
	BootingWaitTime	=_BootingWaitTime;

	ui.lineEditExeFilePath	->setText(ExeFilePath);
	ui.lineEditParameters	->setText(Parameters);
	ui.lineEditWorkingPath	->setText(WorkingPath);
	ui.comboBoxLocation		->setCurrentIndex(Location);
	ui.spinBoxBootingWaitTime	->setValue(BootingWaitTime);
}

AutoStartEachParam::~AutoStartEachParam()
{

}


void AutoStartEachParam::on_pushButtonOK_clicked()
{
	ExeFilePath		=ui.lineEditExeFilePath	->text();
	Parameters		=ui.lineEditParameters	->text();
	WorkingPath		=ui.lineEditWorkingPath	->text();
	Location		=ui.comboBoxLocation	->currentIndex();
	BootingWaitTime	=ui.spinBoxBootingWaitTime->value();
	done(true);
}

void AutoStartEachParam::on_pushButtonCancel_clicked()
{
	done(false);
}

void AutoStartEachParam::on_pushButtonFile_clicked()
{
	QString	F=QFileDialog::getOpenFileName ( 0, /**/"File name", QString());
	if(F.isEmpty()==false){
		ui.lineEditExeFilePath	->setText(F);
	}
}