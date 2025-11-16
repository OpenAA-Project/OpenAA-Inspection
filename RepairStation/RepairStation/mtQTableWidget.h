/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\mtQTableWidget.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef MTQTABLEWIDGET_H
#define MTQTABLEWIDGET_H

#include <QTableWidget>
#include "time.h"

class mtQTableWidget: public QTableWidget
{
    Q_OBJECT

public:
    mtQTableWidget(QWidget *parent=0);
    ~mtQTableWidget(void);

	void	SetWaitTime(int time)	{	WaitTime=time;	}
	void	SetEnableListControl(bool Enable);

protected:
    virtual	void keyPressEvent(QKeyEvent *event)	override;

	virtual void mousePressEvent(QMouseEvent *event)		override;
	virtual	void mouseDoubleClickEvent(QMouseEvent *event)	override;
	virtual void mouseMoveEvent(QMouseEvent *event)			override;

signals:
	void	SignalKeyLeft();
	void	SignalKeyRight();
	void	SignalKeyDown();
	void	SignalKeyEnter();
	void	SignalKeyInsert();
	void	SignalKeyInsertAll();

private:
	clock_t	wTime;
	int		WaitTime;
	bool	EnableListControl;
};

#endif	//MTQTABLEWIDGET_H
