//#include "AddManualItemFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyOCR\AddMonoManualItemForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AddMonoManualItemForm.h"
#include "XRememberer.h"
#include "XDataInLayer.h"

AddMonoManualItemForm::AddMonoManualItemForm(LayersBase *base ,QWidget *parent)
	: QDialog(parent) ,ServiceForLayers(base)
{
	ui.setupUi(this);

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	if(LayerNumb==1)
		ui.stackedWidget->setCurrentIndex(2);
	else
		ui.stackedWidget->setCurrentIndex(0);

	InstallOperationLog(this);
}

AddMonoManualItemForm::~AddMonoManualItemForm()
{

}

void	AddMonoManualItemForm::SetInitial(void)
{
}

void AddMonoManualItemForm::on_pushButtonOK_clicked()
{
	done(true);
}

void AddMonoManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}



void AddMonoManualItemForm::on_pushButtonOK_2_clicked()
{
	done(true);
}

void AddMonoManualItemForm::on_pushButtonCancel_2_clicked()
{
	done(false);
}
