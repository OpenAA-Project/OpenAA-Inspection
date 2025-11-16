/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\InputAlignmentPointForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
