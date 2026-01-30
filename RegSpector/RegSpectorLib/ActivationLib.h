/*
 * Copyright (C) 2021
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
#include <QStringList>
#include "NListComp.h"
#include "XDateTime.h"
#include "XIntClass.h"

char* getFirstHddSerialNumber(void);

class	SerialNumberClass
{
public:
	QString			OSSerial;
	QString			BiosSerial;
	QStringList		NetworkMacAddress;
	QString			UserFirstHDD;

	SerialNumberClass(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	SerialNumberClass	&operator=(const SerialNumberClass &src);

	bool	isMatch(SerialNumberClass &s);
};

bool    GetWMicFunc(SerialNumberClass &Ret);

int MakeEncryption(const unsigned char *s ,int Len ,unsigned char *r ,int MaxLen);
int MakeDecryption(const unsigned char *s ,int Len ,unsigned char *r ,int MaxLen);

class	AuthenticatedProgramList : public NPListSaveLoad<AuthenticatedProgramList>
{
public:
	IntList		CategoryAutoCount;
	int32		ApplicationAutoCode;
	XDateTime	StartTime;
	XDateTime	EndTime;

	AuthenticatedProgramList(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	AuthenticatedProgramContainer : public NPListPackSaveLoad<AuthenticatedProgramList>
{
public:
	virtual	AuthenticatedProgramList	*Create(void);
};

//----------------------------------------------------------------------------------

class	AuthenticatedComponentList : public NPListSaveLoad<AuthenticatedComponentList>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	int32	AuthenticatedID;
	XDateTime	StartTime;
	XDateTime	EndTime;

	AuthenticatedComponentList(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	AuthenticatedComponentContainer : public NPListPackSaveLoad<AuthenticatedComponentList>
{
public:
	virtual	AuthenticatedComponentList	*Create(void);
};

//----------------------------------------------------------------------------------

class	AuthenticatedInfo
{
public:
	SerialNumberClass					AuthenticatedUser;
	
	AuthenticatedProgramContainer		Programs;
	AuthenticatedComponentContainer		Components;

	AuthenticatedInfo(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
