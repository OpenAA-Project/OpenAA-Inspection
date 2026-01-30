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

#ifndef PIODEVICER_H
#define PIODEVICER_H

#include <QMainWindow>
#include <QTimer>
#include <QTcpSocket>
#include <QTcpServer>

#include "ui_PIODevicer.h"
#include "XTypeDef.h"

class PIODevicer;

class	ClientSocket : public QObject
{
	Q_OBJECT
		
	PIODevicer	*Parent;
	QTcpSocket	*Client;
public:
	ClientSocket(PIODevicer *parent);

	void	SetClient(QTcpSocket *client);
	bool	Send(BYTE *data,int len);

public slots:
	void	Disconnected();
	void	ReadyRead ();
};


class PIODevicer : public QMainWindow
{
	Q_OBJECT
	QTcpServer	Server;
	QTimer		TM;

	ClientSocket	*Client[1000];

	int		InportBitCount;
	int		OutportBitCount;
	BYTE	InData[16];

	short BoardId;
	bool	CameNew;

public:
	PIODevicer(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~PIODevicer();

	void	DeleteClient(ClientSocket *c);

	void	OutPort(int port ,BYTE data);
	void	InPort(int port ,BYTE &data);
	void	OutPort(BYTE data[]);

private:
	Ui::PIODevicerClass ui;

public slots:
	void NewConnection ();
	void TimeOut ();
};

#endif // PIODEVICER_H