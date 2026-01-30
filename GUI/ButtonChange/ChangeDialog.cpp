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

#include "ChangeDialog.h"
#include "ui_ChangeDialog.h"
#include "XDataInLayer.h"

ChangeDialog::ChangeDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::ChangeDialog)
{
    ui->setupUi(this);

	NewPhaseCount	=GetPhaseNumb();
	NewPageCount	=GetPageNumb();
	NewLayerCount	=GetLayersBase()->GetMaxLayerNumb();
	NewLineCount	=GetMaxLines(-1);

	ui->spinBoxPhaseCount	->setValue(NewPhaseCount	);
	ui->spinBoxPageCount	->setValue(NewPageCount		);
	ui->spinBoxLayerCount	->setValue(NewLayerCount	);
	ui->spinBoxLineCount	->setValue(NewLineCount		);
}

ChangeDialog::~ChangeDialog()
{
    delete ui;
}

void ChangeDialog::on_pushButtonExecute_clicked()
{
	NewPhaseCount	=ui->spinBoxPhaseCount	->value();
	NewPageCount	=ui->spinBoxPageCount	->value();
	NewLayerCount	=ui->spinBoxLayerCount	->value();
	NewLineCount	=ui->spinBoxLineCount	->value();
	done(true);
}

void ChangeDialog::on_pushButtonCancel_clicked()
{
	done(false);
}