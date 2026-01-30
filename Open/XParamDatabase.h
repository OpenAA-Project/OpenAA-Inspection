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

#if	!defined(XPARAMDATABASE_H)
#define	XPARAMDATABASE_H

#include <QString>
#include <QByteArray>
#include <QIODevice>
#include "NList.h"
#include "XTypeDef.h"

class	ParamDatabase;

class	ParamDatabaseLeaf : public NPList<ParamDatabaseLeaf>
{
	friend	class	ParamDatabase;

	QString		IDName;
	QByteArray	Data;
public:
	ParamDatabaseLeaf(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};	


class	ParamDatabase : public NPListPack<ParamDatabaseLeaf>
{
	QString	ParamDatabaseFileName;
public:
	ParamDatabase(const QString &FileName);

	QIODevice	*CreateIODevice(const QString &IDName);
	void		DeleteIODevice(QIODevice *f);

	bool	Save(void);
	bool	Load(void);
};

class	RelationMasterList
{
public:
	int	MasterCode;
	int	MachineID;
	int	RelationID;

	RelationMasterList(void){	MasterCode=0;	MachineID=0;	RelationID=0;	}
};


#endif