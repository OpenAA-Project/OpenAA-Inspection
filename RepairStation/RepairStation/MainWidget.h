/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\MainWidget.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ui_MainWidget.h"
#include "WindowBase.h"
//#include <QLineEdit>
#include <QLabel>

class MainWidget : public WindowBase
{
//	Q_OBJECT

public:
	MainWidget(const QString &title=/**/"", QWidget *parent = 0);
	~MainWidget();

	void SetTitle(bool Enabled);
	void SetFont	(QFont &f);

	bool Save(QIODevice *file);
	bool Load(QIODevice *file);

	Ui::MainWidgetClass ui;
//	QLineEdit	*leMainFrameTitle;
	QLabel		*leMainFrameTitle;

private:
//	Ui::MainWidgetClass ui;
};

#endif // MAINWIDGET_H
