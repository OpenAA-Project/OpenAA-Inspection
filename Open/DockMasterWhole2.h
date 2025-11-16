/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\DockMasterWhole2.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef DOCKMASTERWHOLE2_H
#define DOCKMASTERWHOLE2_H

#include "ui_DockMasterWhole2.h"
#include "WindowBase.h"
#include <QLineEdit>

class DockMasterWhole2 : public WindowBase
{
//	Q_OBJECT

public:
	DockMasterWhole2(const QString &title=/**/"", QWidget *parent = 0);
	~DockMasterWhole2();

	void	SetTitle(bool Enabled);

	Ui::DockMasterWhole2Class ui;
	QLineEdit	*leMasterImage2Title;

private:
//	Ui::DockMasterWhole2Class ui;
};

#endif // DOCKMASTERWHOLE2_H
