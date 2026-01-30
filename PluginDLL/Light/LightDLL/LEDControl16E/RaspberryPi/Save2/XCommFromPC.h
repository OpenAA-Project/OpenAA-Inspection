/*
 * Copyright (C) 2020
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

#if	!defined(XCommFropmPC)
#define	XCommFropmPC

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

class	MainWindow;
class	TriggerServer;

const	int	TriggerControllerPort=25950;
struct	TriggerInfo
{
	long int	TriggerTiming1;
	long int	TriggerTiming2;
	long int	DropTiming	  ;
};


class	TriggerClient : public QObject
{
	Q_OBJECT

	QTcpSocket	*Sock;
	TriggerServer	*Parent;
	
public:
	TriggerClient(TriggerServer *p ,QTcpSocket *s);
	
private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
};

class	TriggerServer : public QTcpServer
{
	Q_OBJECT
	
	MainWindow	*Parent;

public:
	TriggerServer(MainWindow *p);
	
	void	StartListen(void);
	void	SetData(struct	TriggerInfo &Data);
	void	ReqData(struct	TriggerInfo &Data);
	
private slots:
	void	SlotNewConnection();
};	






#endif