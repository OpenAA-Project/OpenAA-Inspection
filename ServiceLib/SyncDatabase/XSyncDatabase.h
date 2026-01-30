/*
 * Copyright (C) 2014
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

#if	!defined(XSyncDatabase_h)
#define	XSyncDatabase_h

#include <QString>
#include <QIODevice>
#include <QDateTime>
#include <QByteArray>
#include <QSqldatabase>
#include "XServiceForLayers.h"
#include "XDatabase.h"

class	LocalDatabaseBasicClass;
class	LayersBase;


class	XFieldWithData : public NPList<XFieldWithData>
{
public:
	XField		*PointField;
	int			DataInt;
	QString		DataStr;
	QDateTime	DataTime;
	double		DataDouble;
	QByteArray	DataArray;

	XFieldWithData(XField *p){	PointField=p;	}
	XFieldWithData(const XFieldWithData &src);

	QVariant	GetData(void);
	bool	operator==(XFieldWithData &src);
	bool	operator!=(XFieldWithData &src)		{	return !operator==(src);	}
};

class	XRecordWithData : public NPList<XRecordWithData>
{
public:
	NPListPack<XFieldWithData>	FieldDatas;
	XTable						*PointTable;

	XRecordWithData(XTable *p)	{	PointTable=p;	}
	XRecordWithData(const XRecordWithData &src);

	bool	LoadAllFields(QSqlQuery *query);
	bool	operator==(XRecordWithData &src);
	bool	operator!=(XRecordWithData &src)	{	return !operator==(src);	}

	XFieldWithData	*FindField(const QString &fieldname);
	bool	MatchIndex(XRecordWithData *SrcRecord,XIndex &Index);
};

class	XTableWithData : public NPList<XTableWithData>
{
public:
	NPListPack<XRecordWithData>	RecordDatas;
	XTable						*PointTable;

	XTableWithData(XTable *p)	{	PointTable=p;	}
	XTableWithData(const XTableWithData &src);

	XRecordWithData	*FindWithKey(XRecordWithData *SrcRecord,XIndex &Index);
};

class	DBAccessInfo :public ServiceForLayers
{
public:
	QString		IPAddress;
	int			Port;
	QString		FilePathName;
	QString		UserName;
	QString		Password;

	bool	Opened;
	LocalDatabaseBasicClass	*DB;
	NPListPack<XTable>			TableList;
	NPListPack<XTableWithData>	AllOldDatas;
	NPListPack<XTableWithData>	CurrentDatas;

	DBAccessInfo(LayersBase *base);

	bool	Open(void);
	bool	Close(void);
	bool	IsOpen(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	XTable	*Find(const QString &TableName);
	XTableWithData	*FindWithCurrentData(const QString &TableName);
	XTableWithData	*FindWithAllOldData(const QString &TableName);
	void	CopyToOld(void);

	bool	LoadAllData(NPListPack<XTableWithData> &AllDatas);
};

class	SyncAccess : public ServiceForLayers
{
public:
	DBAccessInfo	DBSrc;
	DBAccessInfo	DBDst;

	SyncAccess(LayersBase *base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};





#endif