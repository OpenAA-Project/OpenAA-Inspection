/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\ProcessingForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "ProcessingForm.h"

ProcessingForm::ProcessingForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
}

ProcessingForm::~ProcessingForm()
{
}

void ProcessingForm::SetUpdate(int value)
{
	ui.pgbProcessing->setValue(value);
	update();
}
