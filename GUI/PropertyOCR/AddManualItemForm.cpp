//#include "AddManualItemFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyOCR\AddManualItemForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AddManualItemForm.h"
#include "XRememberer.h"

AddManualItemForm::AddManualItemForm(LayersBase *Base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);

	Mergin			=20;

	InstallOperationLog(this);
}

AddManualItemForm::~AddManualItemForm()
{

}

void	AddManualItemForm::Initial(void)
{
}

void	AddManualItemForm::SlotColorSampleBeforeSave()
{
}

void	AddManualItemForm::SlotColorSampleSelectOne()
{
}

void AddManualItemForm::on_pushButtonAddColor_clicked()
{
}

void AddManualItemForm::on_pushButtonEliminateColor_clicked()
{
}

void AddManualItemForm::on_pushButtonSetMergin_clicked()
{
	//Mergin=ui.spinBoxMergin->value();
}

void AddManualItemForm::on_pushButtonOK_clicked()
{
	//Mergin		=ui.spinBoxMergin		->value();

	done(true);
}

void AddManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}
