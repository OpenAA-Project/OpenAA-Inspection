/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\WindowBase.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef WINDOWBASE_H
#define WINDOWBASE_H

#include <QDockWidget>

class WindowBase : public QDockWidget
{
public:
	WindowBase(const QString &title, QWidget *parent = 0);
	~WindowBase();

	virtual bool Save(QIODevice *file);
	virtual bool Load(QIODevice *file);

private:
};

#endif // WINDOWBASE_H
