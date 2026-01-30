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

#if	!defined(XChangeServer_h)
#define	XChangeServer_h

#include "NList.h"
#include "XTypeDef.h"
#include <QString>
#include <QIODevice>
#include <QStringList>

#define	ChangeServerVersion	1

class	ChangeServerItem : public NPList<ChangeServerItem>
{
public:
	int32	ID;

	QString	ServerName;
	QString	Remark;
	bool	ExecuteBatMode;
	QString	ExeFilePath;
	QStringList		DirectCommandLine;

	ChangeServerItem(void){	ID=-1;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	Execute(void);

private:
	void	MakeTmpFile(QString &FileName);

};

class	ChangeServerContainer : public NPListPack<ChangeServerItem>
{
public:
	int	CurrentID;

	ChangeServerContainer(void){	CurrentID=-1;	}

	ChangeServerItem	*SearchByID(int id);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif