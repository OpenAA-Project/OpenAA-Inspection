/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\InputAlignmentAreaForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAlignmentFormResource.h"
#include "InputAlignmentAreaForm.h"
#include "SelectLibrariesForAnyType.h"
#include "XAlignment.h"

InputAlignmentAreaForm::InputAlignmentAreaForm(bool ModifyMode ,LayersBase *base ,QString areaName ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	setWindowTitle(LangSolver.GetString(InputAlignmentAreaForm_LS,LID_10)/*"Input"*/);
	ui.EditAreaName->setText(areaName);

	Libs=new SelectLibrariesForAnyType(base,this);
	Libs->setParent(ui.frameLibrary);
	Libs->move(0,0);
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

void	InputAlignmentAreaForm::Reflect(void)
{
	Libs->ShowSelectedList();
	ui.EditAreaName->setText(AreaName);
	if(Priority==XAlignmentArea::_PriorityHigh){
		ui.radioButtonPriorityHigh	->setChecked(true);
	}
	else if(Priority==XAlignmentArea::_PriorityMiddle){
		ui.radioButtonPriorityMiddle	->setChecked(true);
	}
	else if(Priority==XAlignmentArea::_PriorityLow){
		ui.radioButtonPriorityLow	->setChecked(true);
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
		Priority=XAlignmentArea::_PriorityHigh;
	}
	else if(ui.radioButtonPriorityMiddle->isChecked()==true){
		Priority=XAlignmentArea::_PriorityMiddle;
	}
	else if(ui.radioButtonPriorityLow->isChecked()==true){
		Priority=XAlignmentArea::_PriorityLow;
	}
	accept();
}

void InputAlignmentAreaForm::on_ButtonDelete_clicked()
{
	DeleteMode=true;
	accept();	
}
void	InputAlignmentAreaForm::SetSelectedList(AlgorithmLibraryListContainer &s)
{
	Libs->SetSelected(s);
}
AlgorithmLibraryListContainer	InputAlignmentAreaForm::GetSelectedList(void)
{
	return Libs->SelectedList;
}
