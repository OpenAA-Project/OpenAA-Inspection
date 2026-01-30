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

#pragma once

#include <QString>
#include <QStringList>
#include <QIODevice>
#include "NList.h"

class StepFileEntityArg;


class StepFileEntity : public NPList<StepFileEntity>
{
public:
	int					LineNo;
	QString				EntityName;
	StepFileEntityArg	*ArgPoint[10];
	int					ArgCount;

	StepFileEntity(void)	{	ArgCount=0;	}
	~StepFileEntity(void);

	virtual	QString	GetEntityName(void)	{	return EntityName;	}
	virtual	int		GetArgCount(void)	{	return ArgCount;	}

	StepFileEntityArg	*GetArg(int n){	return ArgPoint[n];	}
};

class StepFileEntityArg
{
public:
	enum _ArgType
	{
		_None
		,_String
		,_Numeric
		,_Index
		,_True
		,_False
		,_SpecialString
		,_Star		// *
	}ArgType;

	QString			ArgLabel;
	QString			StringValue;
	double			NumericValue;
	int				IndexNumber;
	StepFileEntity	*IndexEntity;

	StepFileEntityArg(const QString &aname);
};

class StepFileStructure
{
	QString						Version;
	QStringList					Header;
	NPListPack<StepFileEntity>	DataEntity;
public:
	StepFileStructure(void);

	bool	LoadStepFile(QIODevice *f);

private:
	bool	LoadEntityLine(const QString &LStr);
};

//===========================================================