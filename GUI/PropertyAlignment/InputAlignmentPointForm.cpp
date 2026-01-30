/*
 * Copyright (C) 2023
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


#include "PropertyAlignmentFormResource.h"
#include "InputAlignmentPointForm.h"
#include "XDLLOnly.h"
#include "XAlignment.h"
#include "XRememberer.h"

InputAlignmentPointForm::InputAlignmentPointForm(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	on_ButtonDefault_clicked();
	/*
	on_ButtonDefault_clicked();
	ui.EditMoveDot	->setValue(MoveDot);
	ui.EditThreshold->setValue(Threshold);
	ui.CheckBAlignmentOnOutline->setChecked(AlignmentOnOutline);
	*/
	ui.EditMoveDot	->setValue(ControlRememberer::GetInt(ui.EditMoveDot,20));
	ui.EditThreshold->setValue(ControlRememberer::GetInt(ui.EditThreshold,0));

	InstallOperationLog(this);
}

InputAlignmentPointForm::~InputAlignmentPointForm()
{

}

void	InputAlignmentPointForm::UpdateData(void)
{
	ui.EditMoveDot	->setValue(MoveDot);
	ui.EditThreshold->setValue(Threshold);
	ui.CheckBAlignmentOnOutline->setChecked(AlignmentOnOutline);
}

void InputAlignmentPointForm::on_ButtonOK_clicked()
{
	MoveDot		=ui.EditMoveDot	->value();
	ControlRememberer::SetValue(ui.EditMoveDot ,ui.EditMoveDot->value());

	Threshold	=ui.EditThreshold->value();
	ControlRememberer::SetValue(ui.EditThreshold ,ui.EditThreshold->value());

	AlignmentOnOutline	=ui.CheckBAlignmentOnOutline->isChecked();
	accept();
}

void InputAlignmentPointForm::on_ButtonCancel_clicked()
{
	reject();
}

void InputAlignmentPointForm::on_ButtonDefault_clicked()
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"Alignment");
	if(L==NULL)
		return;
	AlignmentBase	*A=dynamic_cast<AlignmentBase *>(L);
	if(A==NULL)
		return;
	ui.EditMoveDot	->setValue(A->DefaultMoveDot);
	ui.EditThreshold->setValue(A->DefaultThreshold);
	ui.CheckBAlignmentOnOutline->setChecked(A->DefaultAlignmentOnOutline);
}