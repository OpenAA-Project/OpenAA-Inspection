/*
 * Copyright (C) 2024
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

#pragma once

#include <QString>
#include <QIODevice>
#include "DeviceStruct.h"

#define	DefPortPIOAIN		1
#define	DefPortPIOBIN		2
#define	DefPortPIOCIN		3
#define	DefPortPIODIN		4

#define	DefPortPIOAOUT		5
#define	DefPortPIOBOUT		6
#define	DefPortPIOCOUT		7
#define	DefPortPIODOUT		8

#define	DefPortGIN			9
#define	DefPortGOUT			10
#define	DefPortTRGIN		11
#define	DefPortOuterSW		12
#define	DefPortExtDirect	13

struct JioPortDefinition
{
	QString	StrPIOAIN[4];
	QString	StrPIOBIN[4];
	QString	StrPIOCIN[4];
	QString	StrPIODIN[4];

	QString	StrPIOAOUT[4];
	QString	StrPIOBOUT[4];
	QString	StrPIOCOUT[4];
	QString	StrPIODOUT[4];

	QString	StrGIN[4];
	QString	StrGOUT[4];

	QString	StrTRGIN[4];
	QString	StrOuterSW;
	QString	StrExtDirect;

	QString	GetString	(int PortType ,int BitNo);
	QString	GetTypeName	(int PortType,int BitNo);
	void	SetString(int PortType ,int BitNo ,const QString &s);

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

	bool	GetSignal(int PortType ,int BitNo ,struct  TimingData &d);
};