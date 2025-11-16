/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XParamDatabase.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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