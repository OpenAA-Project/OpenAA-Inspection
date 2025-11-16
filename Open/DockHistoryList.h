/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\DockHistoryList.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef DOCKHISTORYLIST_H
#define DOCKHISTORYLIST_H

#include "ui_DockHistoryList.h"
#include "WindowBase.h"
#include <QLineEdit>

class DockHistoryList : public WindowBase
{
//	Q_OBJECT

public:
	DockHistoryList(const QString &title=/**/"", QWidget *parent = 0);
	~DockHistoryList();

	void SetTitle(bool Enabled);
	void SetFont	(QFont &f);

	bool Save(QIODevice *file);
	bool Load(QIODevice *file);

	Ui::DockHistoryListClass ui;
	QLineEdit	*leHistoryListTitle;

private:
//	Ui::DockHistoryListClass ui;
};

#endif // DOCKHISTORYLIST_H
