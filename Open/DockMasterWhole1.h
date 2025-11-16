/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\DockMasterWhole1.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef DOCKMASTERWHOLE1_H
#define DOCKMASTERWHOLE1_H

#include "ui_DockMasterWhole1.h"
#include "WindowBase.h"
#include <QLineEdit>

class DockMasterWhole1 : public WindowBase
{
//	Q_OBJECT

public:
	DockMasterWhole1(const QString &title=/**/"", QWidget *parent = 0);
	~DockMasterWhole1();

	void	SetTitle(bool Enabled);

	Ui::DockMasterWhole1Class ui;
	QLineEdit	*leMasterImage1Title;

private:
//	Ui::DockMasterWhole1Class ui;
};

#endif // DOCKMASTERWHOLE1_H
