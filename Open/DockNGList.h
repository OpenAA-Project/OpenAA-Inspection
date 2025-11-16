/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\DockNGList.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef DOCKNGLIST_H
#define DOCKNGLIST_H

#include "ui_DockNGList.h"
#include "WindowBase.h"
#include "mtQTableWidget.h"
#include <QLineEdit>

class DockNGList : public WindowBase
{
//	Q_OBJECT

public:
	DockNGList(const QString &title=/**/"", QWidget *parent = 0);
	~DockNGList();

	void SetTitle(bool Enabled);
	void SetFont	(QFont &f);

	bool Save(QIODevice *file);
	bool Load(QIODevice *file);

	Ui::DockNGListClass ui;
	mtQTableWidget	*twNGList;
	QLineEdit		*leNGListTitle;

public slots:
	void selectNearNG(int x, int y);

private:
//	Ui::DockNGListClass ui;
};

#endif // DOCKNGLIST_H
