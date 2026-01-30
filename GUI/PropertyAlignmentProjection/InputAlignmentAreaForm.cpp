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


#include "InputAlignmentAreaForm.h"
#include "XAlignmentProjection.h"

InputAlignmentAreaForm::InputAlignmentAreaForm(bool ModifyMode ,LayersBase *base ,QString areaName ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base),Libs(base,this)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	setWindowTitle(QString("Input"));
	AreaName;
	ui.EditAreaName->setText(AreaName);

	Libs.setParent(ui.frameLibrary);
	Libs.move(0,0);
	DeleteMode=false;
	if(ModifyMode==true){
		ui.ButtonDelete->setEnabled(true);
	}
	else{
		ui.ButtonDelete->setEnabled(false);
	}
	InstallOperationLog(this);
}

InputAlignmentAreaForm::~InputAlignmentAreaForm()
{

}

void	InputAlignmentAreaForm::Reflect(AlignmentProjectionAreaList *a)
{
	ui.EditAreaName->setText(a->AreaName);
	if(a->Priority==XAlignmentProjectionArea::_PriorityHigh)
		ui.radioButtonPriorityHigh	->setChecked(true);
	if(a->Priority==XAlignmentProjectionArea::_PriorityMiddle)
		ui.radioButtonPriorityMiddle->setChecked(true);
	if(a->Priority==XAlignmentProjectionArea::_PriorityLow)
		ui.radioButtonPriorityLow	->setChecked(true);
	if(a->Priority==XAlignmentProjectionArea::_PriorityGlobal)
		ui.radioButtonPriorityLGlobal->setChecked(true);
	Libs.SetSelected(a->LimitedLib);
}

void	InputAlignmentAreaForm::Reflect(void)
{
	Libs.ShowSelectedList();
	ui.EditAreaName->setText(AreaName);
	if(Priority==XAlignmentProjectionArea::_PriorityHigh){
		ui.radioButtonPriorityHigh	->setChecked(true);
	}
	else if(Priority==XAlignmentProjectionArea::_PriorityMiddle){
		ui.radioButtonPriorityMiddle	->setChecked(true);
	}
	else if(Priority==XAlignmentProjectionArea::_PriorityLow){
		ui.radioButtonPriorityLow	->setChecked(true);
	}
	else if(Priority==XAlignmentProjectionArea::_PriorityGlobal){
		ui.radioButtonPriorityLGlobal	->setChecked(true);
	}

}

void InputAlignmentAreaForm::on_ButtonCancel_clicked()
{
	reject();
}

void InputAlignmentAreaForm::on_ButtonOK_clicked()
{
	DeleteMode=false;
	AreaName=ui.EditAreaName->text();
	if(ui.radioButtonPriorityHigh->isChecked()==true){
		Priority=XAlignmentProjectionArea::_PriorityHigh;
	}
	else if(ui.radioButtonPriorityMiddle->isChecked()==true){
		Priority=XAlignmentProjectionArea::_PriorityMiddle;
	}
	else if(ui.radioButtonPriorityLow->isChecked()==true){
		Priority=XAlignmentProjectionArea::_PriorityLow;
	}
	else if(ui.radioButtonPriorityLGlobal->isChecked()==true){
		Priority=XAlignmentProjectionArea::_PriorityGlobal;
	}
	accept();
}

void InputAlignmentAreaForm::on_ButtonDelete_clicked()
{
	DeleteMode=true;
	accept();	
}