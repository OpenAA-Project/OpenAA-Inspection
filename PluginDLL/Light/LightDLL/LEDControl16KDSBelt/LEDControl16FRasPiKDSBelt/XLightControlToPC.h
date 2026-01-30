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

#ifndef XLIGHTCONTROLTOPC_H
#define XLIGHTCONTROLTOPC_H

#include <QIODevice>
#include "LightDeviceStruct.h"
#include <QMutex>
#include "NListRPi.h"
#include "XLightControlToPC.h"
#include "DeviceStruct.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

class   ShowLEDControl16GForm;
class	LightControlToPCServer;

const	int	LightControlToPCPort=25950;


class	LightControlToPCClient : public QObject
{
    Q_OBJECT
    friend  class	LightControlToPCServer;

    QTcpSocket	*Sock;
    LightControlToPCServer	*Parent;

public:
    LightControlToPCClient(LightControlToPCServer *p ,QTcpSocket *s);

private slots:
    void	SlotReadyRead();
    void	SlotDisconnected();
};

class	LightControlToPCServer : public QTcpServer
{
    Q_OBJECT
    friend  class	LightControlToPCClient;

    ShowLEDControl16GForm	*Parent;

public:
    LightControlToPCServer(ShowLEDControl16GForm *p);

    void	StartListen(void);

private slots:
    void	SlotNewConnection();
};

#endif // XLIGHTCONTROLTOPC_H