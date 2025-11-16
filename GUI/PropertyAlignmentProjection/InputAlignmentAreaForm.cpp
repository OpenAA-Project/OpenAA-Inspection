/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentProjection\InputAlignmentProjectionAreaForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
