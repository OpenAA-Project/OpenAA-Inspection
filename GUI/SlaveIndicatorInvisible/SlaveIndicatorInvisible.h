/*
 * Copyright (C) 2022
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

#ifndef SLAVEINDICATORINVISIBLE_H
#define SLAVEINDICATORINVISIBLE_H

#include "slaveindicatorinvisible_global.h"
#include "XServiceForLayers.h"
#include <QTcpSocket>
#include <QThread>
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

class	ThreadSlaveIndicatorRun : public QThread,public ServiceForLayers
{
	Q_OBJECT

	QTcpSocket	Sock;
public:
	volatile	bool	FinMode;

	ThreadSlaveIndicatorRun(LayersBase *Base ,QObject * parent);

	virtual void run ();

	void	ReadInSock(void);
	void	SendAck();

signals:
	void	SignalReboot();
	void	SignalSendAck();
private slots:
	void	SlotRead();
};


class	SlaveIndicatorInvisible : public GUIFormBase
{
	Q_OBJECT

	ThreadSlaveIndicatorRun		ThreadRunInst;
public:
	QString		ComputerName;
	QString	HostIPAddress;
	int32		HostPort;

	SlaveIndicatorInvisible(LayersBase *Base ,QWidget *parent);
	~SlaveIndicatorInvisible(void);

	virtual	void	Prepare(void)	override;


private slots:
	void	SlotReboot();
	void	SlotSendAck();
};

#endif // SLAVEINDICATORINVISIBLE_H