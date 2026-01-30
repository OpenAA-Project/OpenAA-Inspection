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

#if	!defined(XDatabaseList_h)
#define	XDatabaseList_h

#include <QIODevice>
#include "NList.h"
#include "XTypeDef.h"

class	DatabaseList : public NPList<DatabaseList>
{
public:
	QString	Name;
	QString	IP;
	QString	FileName;
	int32	PortNo;

	DatabaseList(void){	PortNo=3050;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DatabaseListContainer : public NPListPack<DatabaseList>
{
public:
	DatabaseListContainer(void){}

	QString	GetFileName(void){	return "DatabaseList.dat";	}

	DatabaseListContainer	&operator=(DatabaseListContainer &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif