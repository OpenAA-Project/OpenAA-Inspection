/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\InputAlignmentGroupForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAlignmentFormResource.h"
#include "InputAlignmentGroupForm.h"

InputAlignmentGroupForm::InputAlignmentGroupForm(LayersBase *Base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	Group=0;
	InstallOperationLog(this);
}

InputAlignmentGroupForm::~InputAlignmentGroupForm()
{

}


void InputAlignmentGroupForm::on_ButtonOK_clicked()
{
	Group=ui.comboBGroup->currentIndex();
	accept();
}

void InputAlignmentGroupForm::on_ButtonCancel_clicked()
{
	reject();
}
