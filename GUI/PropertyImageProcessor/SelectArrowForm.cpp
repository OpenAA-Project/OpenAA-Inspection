#include "AddProgramFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyImageProcessor\SelectArrowForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SelectArrowForm.h"

SelectArrowForm::SelectArrowForm(LayersBase *base, QWidget *parent)
	: QWidget(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	InstallOperationLog(this);
}

SelectArrowForm::~SelectArrowForm()
{

}
