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

#include "BrightHistgramFormResource.h"
#include "CreateManualItemForm.h"
#include "XRememberer.h"

CreateManualItemForm::CreateManualItemForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	ui.spinBoxCellSize			->setValue	(ControlRememberer::GetInt(ui.spinBoxCellSize,50));
	ui.doubleSpinBoxAdoptRate	->setValue	(ControlRememberer::GetDouble(ui.doubleSpinBoxAdoptRate,50));
	ui.checkBoxFixed			->setChecked(ControlRememberer::GetBool(ui.checkBoxFixed,false));
	ui.doubleSpinBoxAverage		->setValue	(ControlRememberer::GetDouble(ui.doubleSpinBoxAverage	,100.0));
	ui.doubleSpinBoxSigma		->setValue	(ControlRememberer::GetDouble(ui.doubleSpinBoxSigma	,5.0));

	InstallOperationLog(this);
}

CreateManualItemForm::~CreateManualItemForm()
{

}


void CreateManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void CreateManualItemForm::on_pushButtonOK_clicked()
{
	CellSize	=ui.spinBoxCellSize->value();
	AdoptRate	=ui.doubleSpinBoxAdoptRate->value();
	Fixed		=ui.checkBoxFixed->isChecked();
	Average		=ui.doubleSpinBoxAverage->value();
	Sigma		=ui.doubleSpinBoxSigma->value();

	ControlRememberer::SetValue(ui.spinBoxCellSize			,ui.spinBoxCellSize->value()		);
	ControlRememberer::SetValue(ui.doubleSpinBoxAdoptRate	,ui.doubleSpinBoxAdoptRate->value()	);
	ControlRememberer::SetValue(ui.checkBoxFixed			,ui.checkBoxFixed->isChecked()		);
	ControlRememberer::SetValue(ui.doubleSpinBoxAverage		,ui.doubleSpinBoxAverage->value()	);
	ControlRememberer::SetValue(ui.doubleSpinBoxSigma		,ui.doubleSpinBoxSigma->value()		);

	done(true);
}