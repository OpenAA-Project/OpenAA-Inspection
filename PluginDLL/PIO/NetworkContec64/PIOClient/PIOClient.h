/*
 * Copyright (C) 2012
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

#ifndef PIOCLIENT_H
#define PIOCLIENT_H

#include "pioclient_global.h"
#include "QTcpSocket"
#include "XTypeDef.h"

class PIOClient : public QTcpSocket
{
	Q_OBJECT
public:
	PIOClient(QObject *parent);
	~PIOClient();

	BYTE	InData[16];
	BYTE	OutData[16];

	void	Initial(const QString &Address);

	void	Outport(int port ,BYTE data);
	BYTE	Inport(int port);
	BYTE	GetOutData(int port);

private:
	
public slots:
	void ReadyRead();
};

#endif // PIOCLIENT_H