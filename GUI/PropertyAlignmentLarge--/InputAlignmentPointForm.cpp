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

InputAlignmentPointForm::InputAlignmentPointForm(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	on_ButtonDefault_clicked();

	ControlRememberer::RestoreForm(this);
	InstallOperationLog(this);

}

InputAlignmentPointForm::~InputAlignmentPointForm()
{

}

void	InputAlignmentPointForm::UpdateData(void)
{
	ui.EditMoveDot			->setValue(MoveDotX);
	ui.EditMoveDotY			->setValue(MoveDotY);
	ui.EditMoveDot2			->setValue(MoveDotX2);
	ui.EditMoveDotY2		->setValue(MoveDotY2);
	ui.checkBoxUsageGlobal	->setChecked(UsageGlobal);
	ui.EditGroupNumber		->setValue(GroupID);
}

void InputAlignmentPointForm::on_ButtonOK_clicked()
{
	MoveDotX	=ui.EditMoveDot		->value();
	MoveDotY	=ui.EditMoveDotY	->value();
	MoveDotX2	=ui.EditMoveDot2	->value();
	MoveDotY2	=ui.EditMoveDotY2	->value();
	GroupID		=ui.EditGroupNumber	->value();
	UsageGlobal	=ui.checkBoxUsageGlobal->isChecked();

	ControlRememberer::SaveForm(this);

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
}
