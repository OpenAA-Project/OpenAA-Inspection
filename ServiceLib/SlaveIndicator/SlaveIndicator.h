/*
 * Copyright (C) 2025
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

#ifndef SLAVEINDICATOR_H
#define SLAVEINDICATOR_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QLabel>
#include "ui_SlaveIndicator.h"
#include "NList.h"
#include "mtColorFrame.h"
#include "XTypeDef.h"

class SlaveIndicator;

class	SocketList : public QObject , public NPList<SocketList>
{
	Q_OBJECT

	friend	class SlaveIndicator;

	SlaveIndicator	*Parent;
	bool			Received;
public:
	QTcpSocket	*Sock;
	QString		Title;
	DWORD		LastTime;
	int			ID;
	int			MachineID;
	QString		ComputerName;
	bool		Shown;

	SocketList(SlaveIndicator *parent);

	void	SetFromServer(QTcpSocket *sock);
	void	SendRebootCommand(void);
	bool	IsSlaveAlive(void);

private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};

class	ColorFrameWithClick : public mtColorFrame
{
	Q_OBJECT

	int		Number;
public:
	ColorFrameWithClick( int number ,QWidget * parent = 0, Qt::WindowFlags f = Qt::Widget );

	virtual	void	mousePressEvent(QMouseEvent *event)	override;

private slots:
	void	SlotReboot();
	void	SlotCheck();
	void	SlotRebootAll();
};

class SlaveIndicator : public QMainWindow
{
	Q_OBJECT

	friend	class	SocketList;

	NPListPack<SocketList>	Slaves;
	QTimer	TM;

	class	SlaveLine : public NPList<SlaveLine>
	{
		int					Number;
		QLabel				Label;
		ColorFrameWithClick	Frame;
		SlaveIndicator		*Parent;
		bool				State;

	public:
		SlaveLine(int n,SlaveIndicator *parent);
		void	Show(bool state,int MachineID,int ID ,const QString &ComputerName);

		int		GetNumber(void)	{	return Number;	}
		bool	GetState(void)	{	return State;	}
	};

	NPListPack<SlaveLine>	SlaveLines;

public:
	SlaveIndicator(int SlaveCount ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~SlaveIndicator();

	QTcpServer	Server;
	int			SlaveCount;

	bool	GetSlaveState(int number);
	void	Show(void);
	void	SetSlaveCount(int n);

	void	SlaveReboot(int number);
	void	SlaveCheck(int number);
	void	RebootAllSlaves(void);
protected:
	virtual	void moveEvent ( QMoveEvent * event )	override;

private:
	Ui::SlaveIndicatorClass ui;

	QString	GetPositionFileName(void);

private slots:
	void	SlotNewConnection ();
	void	SlotTimeout ();
};

#endif // SLAVEINDICATOR_H