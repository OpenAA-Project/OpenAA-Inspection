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

#include "ControlPrecisionCheckerResource.h"
#include "ControlPrecisionCheckerForm.h"

ControlPrecisionCheckerForm::ControlPrecisionCheckerForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
}

ControlPrecisionCheckerForm::~ControlPrecisionCheckerForm()
{

}


void ControlPrecisionCheckerForm::on_pushButtonSetParam_clicked()
{
	on_ParamButton_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonGrp_clicked()
{
	//on_GRP_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonFocus_clicked()
{
	on_Focus_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonBrightness_clicked()
{
	on_Brightness_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonResolution_clicked()
{
	on_Resolution_clicked();
}

void ControlPrecisionCheckerForm::on_pushButtonAngle_clicked()
{
	on_Angle_clicked();
}

void ControlPrecisionCheckerForm::on_comboBoxPage_currentIndexChanged(int index)
{
	CurrentPage=index;
}