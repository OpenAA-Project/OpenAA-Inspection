/*
 * Copyright (C) 2026
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

#include "AlignmentLargeFormResource.h"

#include "InputAlignmentPointForm.h"
#include "XDLLOnly.h"
#include "XAlignmentLarge.h"
#include "XRememberer.h"

static	int	LastMoveDot=20;
static	int	LastThreshold=0;

InputAlignmentPointForm::InputAlignmentPointForm(bool EditMode 
												,XAlignmentLargeArea::_EnumPriority _AreaPriority
												,LayersBase *base 
												,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
	,AreaPriority(_AreaPriority)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	on_ButtonDefault_clicked();
	ui.pushButtonDelete->setVisible(EditMode);
	DeleteMode=false;

	ui.comboBoxUseLayer	->clear();
	ui.comboBoxUseLayer	->addItem("Auto select");
	for(int layer=0;layer<GetLayerNumb(0);layer++){
		ui.comboBoxUseLayer	->addItem(QString(/**/"Layer")
									+QString::number(layer)
									+QString(/**/" ")
									+GetParamGlobal()->GetLayerName(layer));
	}

	RestoreForm((int)AreaPriority,this);
	InstallOperationLog(this);

}

InputAlignmentPointForm::~InputAlignmentPointForm()
{

}

void	InputAlignmentPointForm::UpdateData(void)
{
	ui.EditMoveDot				->setValue(MoveDotX);
	ui.EditMoveDotY				->setValue(MoveDotY);
	ui.EditMoveDot2				->setValue(MoveDotX2);
	ui.EditMoveDotY2			->setValue(MoveDotY2);
	ui.checkBoxUsageGlobal		->setChecked(UsageGlobal);
	ui.EditGroupNumber			->setValue(GroupNumber);
	ui.checkBoxJudgeWithBrDif	->setChecked(JudgeWithBrDif);
	ui.checkBoxCharacterMode	->setChecked(CharacterMode);
	ui.comboBoxUseLayer			->setCurrentIndex(UseLayer+1);
	ui.spinBoxThresholdColor	->setValue(ThresholdColor);
}

void InputAlignmentPointForm::on_ButtonOK_clicked()
{
	MoveDotX	=ui.EditMoveDot		->value();
	MoveDotY	=ui.EditMoveDotY	->value();
	MoveDotX2	=ui.EditMoveDot2	->value();
	MoveDotY2	=ui.EditMoveDotY2	->value();
	GroupNumber	=ui.EditGroupNumber	->value();
	UsageGlobal	=ui.checkBoxUsageGlobal->isChecked();
	JudgeWithBrDif	=ui.checkBoxJudgeWithBrDif	->isChecked();
	CharacterMode	=ui.checkBoxCharacterMode	->isChecked();
	UseLayer		=ui.comboBoxUseLayer->currentIndex()-1;
	ThresholdColor	=ui.spinBoxThresholdColor	->value();

	SaveForm((int)AreaPriority,this);

	accept();
}

void InputAlignmentPointForm::on_ButtonCancel_clicked()
{
	reject();
}

void InputAlignmentPointForm::on_ButtonDefault_clicked()
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
	if(L==NULL)
		return;
	AlignmentLargeBase	*A=static_cast<AlignmentLargeBase *>(L);
	if(A==NULL)
		return;
	ui.EditMoveDot	->setValue(A->DefaultMoveDot);
	ui.EditMoveDotY	->setValue(A->DefaultMoveDot);
	ui.EditMoveDot2	->setValue(A->DefaultMoveDot);
	ui.EditMoveDotY2->setValue(A->DefaultMoveDot);
	ui.checkBoxUsageGlobal->setChecked(false);
	ui.EditGroupNumber		->setValue(0);
	ui.checkBoxJudgeWithBrDif	->setChecked(true);
	ui.checkBoxCharacterMode	->setChecked(false);
	ui.comboBoxUseLayer			->setCurrentIndex(A->DefaultLayer);
	ui.spinBoxThresholdColor	->setValue(A->DefaultThreshold);
}

void InputAlignmentPointForm::on_pushButtonDelete_clicked()
{
	accept();
	DeleteMode=true;
}
