/*
 * Copyright (C) 2024
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

#include "RunningMachineForm.h"
#include "ui_RunningMachineForm.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"

RunningMachineForm::RunningMachineForm(LayersBase *base ,const QString &root ,const QString &name
						 ,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent),
    ui(new Ui::RunningMachineForm)
{
    ui->setupUi(this);
	ui->dateTimeEditStart	->setDateTime(QDateTime::currentDateTime());
	ui->dateTimeEditEnd		->setDateTime(QDateTime::currentDateTime());
}

RunningMachineForm::~RunningMachineForm()
{
    delete ui;
}
bool	RunningMachineForm::Initial(void)
{
	return true;
}
const QString	RunningMachineForm::GetPath(void)
{
	return "設備稼働率グラフ/設備稼働率グラフ";
}
void RunningMachineForm::showEvent(QShowEvent *event)
{

}
void RunningMachineForm::on_pushButtonStartSearch_clicked()
{

}

void RunningMachineForm::on_pushButtonView_clicked()
{

}

void RunningMachineForm::on_pushButtonExcel_clicked()
{

}