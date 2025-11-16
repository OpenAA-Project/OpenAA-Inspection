/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\LightDLL\DummyLightDLL\DummyLightForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "DummyLightForm.h"

DummyLightForm::DummyLightForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

DummyLightForm::~DummyLightForm()
{

}


void DummyLightForm::on_pushButtonTurnOn_clicked()
{
	close();
}

void DummyLightForm::on_pushButtonTurnOff_clicked()
{
	close();
}