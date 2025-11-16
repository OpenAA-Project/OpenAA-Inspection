/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\IntegrationPlayer\IDatabaseMessageDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "IDatabaseMessageDialog.h"

IDatabaseMessageDialog::IDatabaseMessageDialog(QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
}

IDatabaseMessageDialog::~IDatabaseMessageDialog()
{

}

bool	IDatabaseMessageDialog::SetMessages(QStringList &msg)
{
	bool	Ret=false;
	ui.textMessage->clear();
	for(int i=0;i<msg.count();i++){
		ui.textMessage->append(msg[i]);
		Ret=true;
	}
	return Ret;
}
