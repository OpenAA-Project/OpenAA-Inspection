/*
 * Copyright (C) 2016
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

#if	!defined(XVIRTUALPIOSERVER_H)
#define	XVIRTUALPIOSERVER_H

#include "NList.h"
#include <QString>
#include "XTypeDef.h"
#include <QBuffer>
#include "XVirtualPIOCommon.h"
#include <QWidget>
#include <QTcpServer>

class	PIOServer;

class	ClientBitPort : public NPList<ClientBitPort>
{
public:
	int		BitNumber;
	bool	Output;
	QString	BitName;

	int		CurrentOutput;

	ClientBitPort(void){}
};


class	AllocatedClient : public NPList<AllocatedClient> ,public PIOSocket
{	
	PIOServer	*Parent;
public:
	int		ClientID;
	QString	ClientIP;
	int		ClientPortNumber;
	int		HandleNumber;

	NPListPack<ClientBitPort>	BitPorts;

	AllocatedClient(PIOServer *parent,QTcpSocket *sv);

	int		GetBitCountIn(void);
	int		GetBitCountOut(void);
private:
	void	Received(int cmd ,QByteArray &data);
	virtual	void	SlotDisconnected();
	ClientBitPort	*FindInBit(int BitNumber);
	ClientBitPort	*FindOutBit(int BitNumber);
	int		GetOutData(const QString &BitName);
};


class	BindedBit : public NPList<BindedBit>
{
public:
	ClientBitPort	*BitPoint;
	AllocatedClient	*ClientPoint;
};

class	BindedIOBit : public NPList<BindedIOBit>
{
public:
	BindedBit				*BitOut;
	NPListPack<BindedBit>	BitIn;
	bool			Duplicated;

	BindedIOBit(void);
	virtual	~BindedIOBit(void);
};

class	BindedIOBitContainer : public NPListPack<BindedIOBit>
{
public:
	BindedIOBitContainer(void){}

	BindedIOBit	*FindOutBit(const QString &BitName);
};


class	PIOServer : public QTcpServer ,public NPListPack<AllocatedClient>
{
	Q_OBJECT
		
public:
	BindedIOBitContainer	IOBitsToShow;

	PIOServer(QObject *parent);

	void	StartServer(int PortNumber=28200);

	void	BindData(void);
	ClientBitPort	*SearchOutputBit(const QString &BitName);
	void	DeleteDirectAccess(void);
	AllocatedClient	*GetAllocatedClient(int handle);
signals:
	void	SignalStructureChanged();
private slots:
	void SlotNewConnection ();

};

#endif