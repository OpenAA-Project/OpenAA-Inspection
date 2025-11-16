#include "DesktopMachineMenuResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DesktopMachineMenu\NextMasterForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "NextMasterForm.h"
#include "XGeneralFunc.h"

NextMasterForm::NextMasterForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	SetWidgetCenter(this);
	InstallOperationLog(this);
}

NextMasterForm::~NextMasterForm()
{

}


void NextMasterForm::on_pushButtonStartNext_clicked()
{
	done((int)true);
}

void NextMasterForm::on_pushButtonFinish_clicked()
{
	done((int)false);
}