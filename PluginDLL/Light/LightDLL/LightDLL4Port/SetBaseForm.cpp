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

#include "SetBaseForm.h"
#include "ui_SetBaseForm.h"
#include "LightDLL4PortForm.h"

SetBaseForm::SetBaseForm(LayersBase *base, int BasePort[],QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetBaseForm),ServiceForLayers(base)
{
    ui->setupUi(this);
	ui->spinBoxPort0->setValue(BasePort[0]);
	ui->spinBoxPort1->setValue(BasePort[1]);
	ui->spinBoxPort2->setValue(BasePort[2]);
	ui->spinBoxPort3->setValue(BasePort[3]);

	InstallOperationLog(this);
}

SetBaseForm::~SetBaseForm()
{
    delete ui;
}

void SetBaseForm::on_pushButtonOK_clicked()
{
	LightDLL4PortForm::BasePort[0]	=ui->spinBoxPort0->value();
	LightDLL4PortForm::BasePort[1]	=ui->spinBoxPort1->value();
	LightDLL4PortForm::BasePort[2]	=ui->spinBoxPort2->value();
	LightDLL4PortForm::BasePort[3]	=ui->spinBoxPort3->value();
	done(true);
}