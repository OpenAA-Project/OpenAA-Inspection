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