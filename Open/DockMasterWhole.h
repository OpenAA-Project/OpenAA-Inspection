/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\DockMasterWhole.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef DOCKMASTERWHOLE_H
#define DOCKMASTERWHOLE_H

#include "ui_DockMasterWhole.h"
#include "WindowBase.h"
#include <QLineEdit>

class DockMasterWhole : public WindowBase
{
//	Q_OBJECT

public:
	DockMasterWhole(const QString &title=/**/"", QWidget *parent = 0);
	~DockMasterWhole();

	void	SetTitle(bool Enabled);

	Ui::DockMasterWholeClass ui;
	QLineEdit	*leMasterImageTitle;

private:
//	Ui::DockMasterWholeClass ui;
};

#endif // DOCKMASTERWHOLE_H
