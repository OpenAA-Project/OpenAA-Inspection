/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



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