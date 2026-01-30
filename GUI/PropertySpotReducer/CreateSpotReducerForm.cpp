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

#include "CreateSpotReducerFormResource.h"
#include "CreateSpotReducerForm.h"
#include "XRememberer.h"

CreateSpotReducerForm::CreateSpotReducerForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	ControlRememberer::LoadValue(ui.spinBoxSpotBrightness,200);
	ControlRememberer::LoadValue(ui.doubleSpinBoxReductionLevel,50);
	ControlRememberer::LoadValue(ui.spinBoxSpotArea,4);
	ControlRememberer::LoadValue(ui.spinBoxSpotCount,6);
	InstallOperationLog(this);
}

CreateSpotReducerForm::~CreateSpotReducerForm()
{

}


void CreateSpotReducerForm::on_pushButtonOK_clicked()
{
	SpotBrightness	=ui.spinBoxSpotBrightness		->value();
	ReductionLevel	=ui.doubleSpinBoxReductionLevel	->value();
	SpotArea		=ui.spinBoxSpotArea				->value();
	SpotCount		=ui.spinBoxSpotCount			->value();

	ControlRememberer::SetValue(ui.spinBoxSpotBrightness	);
	ControlRememberer::SetValue(ui.doubleSpinBoxReductionLevel	);
	ControlRememberer::SetValue(ui.spinBoxSpotArea		);
	ControlRememberer::SetValue(ui.spinBoxSpotCount		);
	done((int)true);
}

void CreateSpotReducerForm::on_pushButtonCancel_clicked()
{
	done((int)false);
}