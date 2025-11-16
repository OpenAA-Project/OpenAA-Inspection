#include "AddProgramFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyImageProcessor\AddProgramForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AddProgramForm.h"

AddProgramForm::AddProgramForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	InstallOperationLog(this);
}

AddProgramForm::~AddProgramForm()
{

}


void AddProgramForm::on_pushButtonOK_clicked()
{
	ProgName=ui.EditName->text();
	done((int)true);
}

void AddProgramForm::on_pushButtonCancel_clicked()
{
	done((int)false);
}