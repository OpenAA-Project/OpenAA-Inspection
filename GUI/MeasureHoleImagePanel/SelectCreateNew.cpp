#include "MeasureHoleImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MeasureHoleImagePanel\SelectCreateNew.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "SelectCreateNew.h"

SelectCreateNew::SelectCreateNew(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SelectCreateNew::~SelectCreateNew()
{

}


void SelectCreateNew::on_pushButtonCreateNew_clicked()
{
	done(1);
}

void SelectCreateNew::on_pushButtonGetColorMap_clicked()
{
	done(2);
}