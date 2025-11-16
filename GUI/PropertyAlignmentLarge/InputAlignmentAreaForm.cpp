#include "AlignmentLargeFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentLarge\InputAlignmentLargeAreaForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "InputAlignmentAreaForm.h"
#include "XAlignmentLarge.h"

InputAlignmentAreaForm::InputAlignmentAreaForm(bool ModifyMode ,LayersBase *base ,QString areaName ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base),Libs(base,this)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	setWindowTitle(LangSolver.GetString(InputAlignmentAreaForm_LS,LID_0)/*"Input"*/);
	AreaName=areaName;
	ui.EditAreaName->setText(AreaName);

	Libs.setParent(ui.frameLibrary);
	Libs.move(0,0);

	int CountMaster=GetLayersBase()->GetCountBufferInfo();
    for(int i=0;i<CountMaster;i++){
        BufferInfoList	*L=GetLayersBase()->GetBufferInfo(i);
        if(L!=NULL){
			ui.comboBoxSelectMaster->addItem(L->BufferName);
		}
    }

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

void	InputAlignmentAreaForm::Reflect(AlignmentLargeAreaList *a)
{
	ui.comboBoxSelectMaster->setCurrentIndex(a->MasterNo);
	MasterNo=a->MasterNo;

	ui.EditAreaName->setText(a->AreaName);
	if(a->Priority==XAlignmentLargeArea::_PriorityHigh)
		ui.radioButtonPriorityHigh	->setChecked(true);
	if(a->Priority==XAlignmentLargeArea::_PriorityMiddle)
		ui.radioButtonPriorityMiddle->setChecked(true);
	if(a->Priority==XAlignmentLargeArea::_PriorityLow)
		ui.radioButtonPriorityLow	->setChecked(true);
	if(a->Priority==XAlignmentLargeArea::_PriorityGlobal)
		ui.radioButtonPriorityLGlobal->setChecked(true);
	Libs.SetSelected(a->LimitedLib);
}

void	InputAlignmentAreaForm::Reflect(void)
{
	Libs.ShowSelectedList();
	ui.EditAreaName->setText(AreaName);
	if(Priority==XAlignmentLargeArea::_PriorityHigh){
		ui.radioButtonPriorityHigh	->setChecked(true);
	}
	else if(Priority==XAlignmentLargeArea::_PriorityMiddle){
		ui.radioButtonPriorityMiddle	->setChecked(true);
	}
	else if(Priority==XAlignmentLargeArea::_PriorityLow){
		ui.radioButtonPriorityLow	->setChecked(true);
	}
	else if(Priority==XAlignmentLargeArea::_PriorityGlobal){
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
		Priority=XAlignmentLargeArea::_PriorityHigh;
	}
	else if(ui.radioButtonPriorityMiddle->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityMiddle;
	}
	else if(ui.radioButtonPriorityLow->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityLow;
	}
	else if(ui.radioButtonPriorityLGlobal->isChecked()==true){
		Priority=XAlignmentLargeArea::_PriorityGlobal;
	}
	MasterNo=ui.comboBoxSelectMaster->currentIndex();
	accept();
}

void InputAlignmentAreaForm::on_ButtonDelete_clicked()
{
	DeleteMode=true;
	accept();	
}
