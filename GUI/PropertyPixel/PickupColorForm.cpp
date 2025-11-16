#include "PickupColorFormResource.h"
#include "PropertyPixelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyPixel\PickupColorForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PickupColorForm.h"

PickupColorForm::PickupColorForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	InstallOperationLog(this);
}

PickupColorForm::~PickupColorForm()
{

}
