/*
 * Copyright (C) 2023
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

#include "XTypeDef.h"
#include "NListComp.h"
#include <QString>
#include <QIODevice>

//========================================================================================

class	RootNameList : public NPListSaveLoad<RootNameList>
{
public:
	QString	DLLRoot;
	QString	DLLName;

	RootNameList(void){}
	RootNameList(const RootNameList &src);
	RootNameList(const QString &dllRoot, const QString &dllName):DLLRoot(dllRoot),DLLName(dllName){}

	RootNameList &operator=(const RootNameList &src);
	bool	operator==(const RootNameList &s)	const;
	bool	operator!=(const RootNameList &s)	const;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};
class	RootNameListContainer : public NPListPackSaveLoad<RootNameList>
{
public:
	RootNameListContainer(void){}
	RootNameListContainer(const RootNameListContainer &src);

	virtual	RootNameList	*Create(void)	{	return new RootNameList();	}
	RootNameListContainer	&operator=(const RootNameListContainer &src);

	bool	Exists(const QString &Root ,const QString &Name);
	void	Add(const QString &Root ,const QString &Name);
	void	Merge(const QString &Root ,const QString &Name);
	void	Merge(RootNameList &s);
};
