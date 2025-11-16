/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\AutoStartParamDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "AutoStartParamDialog.h"

AutoStartParamDialog::AutoStartParamDialog(ParamBase *pbase,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	WTab = new WEditParameterTab(pbase ,-1,this);
	WTab->ShowToWindow();
}

AutoStartParamDialog::~AutoStartParamDialog()
{
	delete	WTab;
}


void AutoStartParamDialog::on_OKButton_clicked()
{
	WTab->LoadFromWindow();
	done((int)true);
}

void AutoStartParamDialog::on_CancelButton_clicked()
{
	done((int)false);
}