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

#if	!defined(XPQSystemDBLoader_h)
#define	XPQSystemDBLoader_h

#include <QString>
#include <QLibrary>
#include <QSqlDatabase>
#include <QBuffer>
#include "XDateTime.h"
#include <QImage>
#include "XTypeDef.h"
#include "XPQSystemServiceLib.h"

class	PQSystemBase;

class	PQSystemDBLoader
{
	QLibrary 	DllLib;
public:
	PQSystemDBLoader(PQSystemBase *base);

	bool	InitialLoad(const QString &PathAndFileName);

	void	(*G_StartDatabase)(QSqlDatabase &DBase ,QString HostName ,QString UserName ,QString Password ,QString DBName,int32 Port);
	bool	(*G_OpenDatabase)(QSqlDatabase *DB);
	bool	(*G_CloseDatabase)(QSqlDatabase *DB);
	bool	(*G_IsValidDatabase)(QSqlDatabase *DB);

	bool	(*G_SQLLoadMasterData)(QSqlDatabase &DB ,int masterCode
										,QBuffer &GeneralBuff ,QBuffer	&SettingBuff
										,QBuffer &LightBuff
										,int32 &MasterCode ,int32 &MachineID
										,XDateTime &RegTime
										,QString &MasterName ,QString &Remark
										,int32 &Version
										,XDateTime &LastEditTime
										,int32 &CategoryID
										,int16 &MasterType
										,QImage &TopView
										,int32 &iLibFolderID);
	bool	(*G_SQLEnumMachines)(QSqlDatabase &DB ,MachineInfoContainer &AllMachines);
};

#endif