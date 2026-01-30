/*
 * Copyright (C) 2012
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

#include "LogIntegratorProcessForm.h"

LogIntegratorProcessForm::LogIntegratorProcessForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

LogIntegratorProcessForm::~LogIntegratorProcessForm()
{
}

void LogIntegratorProcessForm::SetUpdate(int value)
{
	ui.pgbProcessing->setValue(value);
	update();
}

void LogIntegratorProcessForm::SetLotNo(QString LotNo)
{
	ui.lbLotNo->setText(LotNo);
}

void LogIntegratorProcessForm::SetExecCount(int Count)
{
	ui.lbCount->setText(QString::number(Count));
}

void LogIntegratorProcessForm::SetExecNo(int No)
{
	ui.lbNo->setText(QString::number(No));
}