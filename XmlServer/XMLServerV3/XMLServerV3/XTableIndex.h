/*
 * Copyright (C) 2015
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

#if	!defined(XTableIndex_h)
#define	XTableIndex_h

#include "NList.h"
#include <QString>
#include <QIODevice>

class	TableIndexInformation : public NPList<TableIndexInformation>
{
	QString	TableName;
	QString	Information;
public:
	TableIndexInformation(void);
	TableIndexInformation(const QString &TableName);

	QString	GetTableName(void)		{	return TableName;	}
	QString	GetInformation(void)	{	return Information;	}
	void	SetInformation(QString &s)	{	Information=s;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	TableIndexContainer : public NPListPack<TableIndexInformation>
{
public:
	TableIndexInformation	*FindTableIndex(QString &str);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};



#endif