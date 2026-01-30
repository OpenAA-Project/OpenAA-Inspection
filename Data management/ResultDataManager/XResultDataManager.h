/*
 * Copyright (C) 2022
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

#if	!defined(XRESULTDATAMANAGER_H)
#define	XRESULTDATAMANAGER_H

#include "XParamBase.h"	
#include <QString>
#include <QSqlDatabase>

class	XMLServerHandle;
class	DatabaseLoader;
class	ResultDataManagerParam;

class	ResultDataManagerParam : public ParamBase
{
public:
	QString		ImageDrive;

	QString		XML_IPAddress;
	int			XML_Port;

	QString		DatabaseHost;
	int			DatabasePort;
	QString		DatabaseFileName;
	int			WaitMilisec;


	ResultDataManagerParam(void);

	virtual	QString	GetSavedFileName(void)	{	return QString("XMLResultDataManager.dat");	}
	virtual	QString	GetDataText(void)		{	return QString("XMLResultDataManager");		}

	void	ShowClient(int id);
protected:
	virtual	QString	GetDefaultFileName(void){	return QString("XMLResultDataManager.dat");	}
};

class	RServerParam : public ParamBase
{
public:

	RServerParam(void){}

	virtual	QString	GetSavedFileName(void)	{	return QString("XMLRDServer.dat");	}
	virtual	QString	GetDataText(void)		{	return QString("XMLRDServer");		}

	void	ShowClient(int id);
protected:
	virtual	QString	GetDefaultFileName(void){	return QString("XMLRDServer.dat");	}
};

void DeleteTable(const QString &TableStr
					,XMLServerHandle	*XMLServer
					,std::shared_ptr<DatabaseLoader> SQLDatabase ,QSqlDatabase &DB
					,ResultDataManagerParam	*SParam, QString *filepath=NULL);
void DeleteTable(const QString &TableStr, int LotAutoCount, int MasterCode
	,XMLServerHandle *XMLServer
	,std::shared_ptr<DatabaseLoader> SQLDatabase, QSqlDatabase &DB
	,ResultDataManagerParam *SParam, QString *filepath=NULL);
void DeleteJDT(const QString &ResultStr
				,ResultDataManagerParam	*SParam, QString *filepath=NULL);
void DeleteJDT(const QStringList &ResultStrList
				,ResultDataManagerParam	*SParam, QString *filepath=NULL);

int ReadLotAutoCount(const QString &TableStr, XMLServerHandle *XMLServer);
int ReadLotMasterCode(const QString &TableStr, XMLServerHandle *XMLServer);
int ReadLotMasterCode(const QString &TableStr, XMLServerHandle *XMLServer, QSqlDatabase &DB);

void DeleteEmptyDirectory(QString filepath);

#endif