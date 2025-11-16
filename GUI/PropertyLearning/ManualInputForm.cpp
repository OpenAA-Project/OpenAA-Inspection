#include "AddFileDialogResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLearning\ManualInputForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ManualInputForm.h"

ManualInputForm::ManualInputForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	InstallOperationLog(this);
}

ManualInputForm::~ManualInputForm()
{

}


void ManualInputForm::on_pushButtonOK_clicked()
{
	if(ui.toolButtonNG->isChecked()==true)
		Ok=false;
	else
		Ok=true;
	NGLevel=ui.spinBoxNGLevel->value();

	done(true);
}

void ManualInputForm::on_pushButtonCancel_clicked()
{
	done(false);
}