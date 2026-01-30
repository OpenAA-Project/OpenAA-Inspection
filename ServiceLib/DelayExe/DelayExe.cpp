/*
 * Copyright (C) 2021
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

#include "DelayExe.h"
#include <QProcess>

DelayExe::DelayExe(const QString &FileName , int WaitingTime , QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	CurrentCounter=WaitingTime;
	ui.labelCounter	->setText(QString::number(CurrentCounter));
	ExeFileName	=FileName;
	ui.labelFileName->setText(FileName);

	TM.setInterval(1000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

DelayExe::~DelayExe()
{

}

void	DelayExe::SlotTimeOut()
{
	CurrentCounter--;
	ui.labelCounter	->setText(QString::number(CurrentCounter));
	if(CurrentCounter==0){
		if(SArg.isEmpty()==true)
			QProcess::startDetached ( ExeFileName);
		else
			QProcess::startDetached ( ExeFileName,SArg);

		close();
	}
}