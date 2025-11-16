#include "AlignmentLargeFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentLarge\InputAlignmentLargePointForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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

	ControlRememberer::RestoreForm((int)AreaPriority,this);
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

	ControlRememberer::SaveForm((int)AreaPriority,this);

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
	AlignmentLargeBase	*A=dynamic_cast<AlignmentLargeBase *>(L);
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

