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

#if	!defined(XLIBRARYTYPE_H)
#define	XLIBRARYTYPE_H

#include "NList.h"
#include "XTypeDef.h"
#include <QIODevice>
#include <QString>

class	LayersBase;
class	LogicDLLBaseClass;

class	LibraryTypeList : public NPList<LibraryTypeList>
{
	int		LibType;
	QString	LibName;
public:
	LibraryTypeList(void){	LibType=0;	}
	LibraryTypeList(const LibraryTypeList &s)	{	LibType=s.LibType;	LibName=s.LibName;	}

	LibraryTypeList	&operator=(const LibraryTypeList &s)	{	LibType=s.LibType;	LibName=s.LibName;	return *this;	}

	int		GetLibType(void)	const	{	return LibType;	}
	QString	GetLibName(void)	const	{	return LibName;	}

	void	SetLibType(int b)			{	LibType=b;	}
	void	SetLibName(const QString &s){	LibName=s;	}
};

class	LibTypeListContainer : public NPListPack<LibraryTypeList>
{
public:
	LibTypeListContainer(void){}

	void	LoadFromDatabase(LayersBase *Base);
	void	LoadFromDatabaseInstalled(LayersBase *Base ,LogicDLLBaseClass *LContainer);
	LibraryTypeList	*FindLibraryType(int LibType);
	QString	FindLibraryTypeName(int LibType);
};

#endif