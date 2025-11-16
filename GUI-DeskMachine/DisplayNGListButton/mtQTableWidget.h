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

	void		SetwTime(clock_t t)	{	wTime=t;			}
	clock_t		GetwTime()			{	return wTime;		}
	void		SetWaitTime(int t)	{	WaitTime=t;			}
	int			GetWaitTime()		{	return WaitTime;	}
	void		SetCurrentRowList()	{	RowList.append(currentRow());	}
	void		ClearRowList()		{	RowList.clear();	}
	bool		CheckRowList()		{	return RowList.contains(currentRow()+1);	}

	void	SetEnableListControl(bool Enable);
	void	SetIsSignalKeyDown	(bool Enable)	{	IsSignalKeyDown=Enable;	}

	void	SetThumbnailCount(int Cnt)	{	ThumbnailCount=Cnt;	}

	void	ExecKeyPageUp();
	bool	ExecKeyPageDown();

protected:
    virtual	void	keyPressEvent	(QKeyEvent *event)	override;
    virtual	void	keyReleaseEvent	(QKeyEvent *event)	override;

signals:
	void	SignalKeyEnter();
	void	SignalKeyLR();
	void	SignalKeyLRReverse();
	void	SignalKeyDelete();
	void	SignalKeyDeleteRepeat();
	void	SignalKeyDown();

private:
	clock_t		wTime;
	int			WaitTime;
	QList<int>	RowList;

	bool	EnableListControl;
	bool	IsSignalKeyDown;

	int		ThumbnailCount;
};

#endif	//MTQTABLEWIDGET_H
