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

#include "ShowStrategicAllFormResource.h"
#include "ShowStrategicAllForm.h"
#include "ui_ShowStrategicAllForm.h"

ShowStrategicAllForm::ShowStrategicAllForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowStrategicAllForm)
{
    ui->setupUi(this);
}

ShowStrategicAllForm::~ShowStrategicAllForm()
{
    delete ui;
}

void ShowStrategicAllForm::on_pushButtonShow_clicked()
{
	int	n=GetLayersBase()->GetCurrentStrategicNumber();
	ui->lineEditCurrentStrategicNumber->setText(QString::number(n));

	n=GetLayersBase()->GetCurrentStrategicNumberForSeq();
	ui->lineEditCurrentStrategicNumberForSeq->setText(QString::number(n));

	n=GetLayersBase()->GetCurrentStrategicNumberForCalc();
	ui->lineEditCurrentStrategicNumberForCalc->setText(QString::number(n));
}