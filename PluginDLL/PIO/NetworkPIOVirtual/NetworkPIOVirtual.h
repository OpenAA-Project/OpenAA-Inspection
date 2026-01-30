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

#ifndef NETWORKPIOVIRTUAL_H
#define NETWORKPIOVIRTUAL_H

#include "networkpiovirtual_global.h"
#include <QSharedMemory>
#include <QMutex>
#include "XTypeDef.h"


struct	NetworkPIOVirtualPacket
{
	BYTE	Cmd;
	BYTE	InData[4];
	BYTE	OutData[4];
};


class NetworkPIOVirtual
{
	QSharedMemory	MemMap;
	struct	NetworkPIOVirtualPacket	*Pointer;
public:
	int		InNumb;
	int		OutNumb;

	NetworkPIOVirtual(void);
	~NetworkPIOVirtual();

	void	Initial(int _InNumb ,int _OutNumb);
	void	Initial(const QString &Something);

	void	OutByte(int port ,BYTE data);
	BYTE	InByte(int port);
	void	OutBit(int BitIndex,BYTE data);
	BYTE	InBit(int BitIndex);
	BYTE	GetOutByte(int port);

private:

};


#endif // NETWORKPIOVIRTUAL_H