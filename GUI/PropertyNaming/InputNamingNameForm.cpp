#include "PropertyNamingFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyNaming\InputNamingNameForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "InputNamingNameForm.h"
#include "XPropertyNamingPacket.h"

InputNamingNameForm::InputNamingNameForm(LayersBase *base, QWidget *parent)
	: QWidget(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ui.lineEditName->setText(InputedName);
	ui.spinBoxX	->setValue(-1);
	ui.spinBoxY	->setValue(-1);
	RetOK=false;
	InstallOperationLog(this);
}

InputNamingNameForm::~InputNamingNameForm()
{

}


void	InputNamingNameForm::SetNamingItem(NamingListForPacket *item)
{
	ui.lineEditName->setText(item->AreaName);
	ui.spinBoxX	->setValue(item->Column);
	ui.spinBoxY	->setValue(item->Row);
	NamingItem	=item;
}


void InputNamingNameForm::on_pushButtonOK_clicked()
{
	InputedName=ui.lineEditName->text();
	Column	=ui.spinBoxX	->value();
	Row		=ui.spinBoxY	->value();
	RetOK=true;
	emit	SignalClose();
}
void InputNamingNameForm::on_pushButtonCancel_clicked()
{
    RetOK=false;
    emit	SignalClose();
}
