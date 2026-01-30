/*
 * Copyright (C) 2016
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

#if	!defined(XPQSystemService_h)
#define	XPQSystemService_h

#include <QString>
#include <QSqlDatabase>
#include "XTypeDef.h"
#include "NList.h"

class	PQSystemDBLoader;
class	PQSystemParam;
class	PQSystemResult;
class	PQSystemXMLLoader;
class	PQSystemXMLAccessor;
class	LanguagePackage;
class	PQSystemXMLDLLBaseRoot;
class	PQSystemRunnerLoaderContainer;
class	MachineInfoContainer;
class	LocalDatabaseBasicClass;
class	FileRegistry;
class	PQSystemRunner;

class	PQSystemBase
{
	QString					CurrentPath;
	FileRegistry			*FRegistry;
	PQSystemDBLoader		*DBLoader;
	PQSystemParam			*PQSystemParamData;
	PQSystemXMLLoader		*XMLLoader;
	PQSystemRunnerLoaderContainer	*Runners;

	PQSystemXMLAccessor		*PQSystemResult;
	int						LanguageCode;
	LanguagePackage			*LanguagePackageData;
	QSqlDatabase			*RootDBase;
	LocalDatabaseBasicClass	*KDatabase;
public:
	PQSystemBase(const QString &currentpath);
	virtual ~PQSystemBase(void);

	bool	LoadInitialParam(void);

	bool	InitialDBLoader(void);
	bool	InitialXMLLoader(void);
	bool	InitialRunner(void);

	QString	GetCurrentPath(void)	{	return CurrentPath;		}
	int		GetLanguageCode(void)	{	return LanguageCode;	}
	LanguagePackage		&GetLanguagePackageData(void)	{	return *LanguagePackageData;	}

	PQSystemParam			*GetPQSystemParam(void)	{	return PQSystemParamData;	}

	//--------SQL database---------//
	PQSystemDBLoader	*GetDB(void)	{	return DBLoader;	}
	bool	IsSQLDatabaseExist(void);
	bool	SQLEnumMachines(MachineInfoContainer &AllMachines);

	PQSystemXMLDLLBaseRoot	*GetXML(void);
	PQSystemRunnerLoaderContainer	*GetRunners(void)	{	return Runners;		}
};

//=====================================================================================

class	MachineInfoList : public NPList<MachineInfoList>
{
public:
	int		MachineCode;
	QString	MachineName;

	MachineInfoList(void){	MachineCode=0;	}
};

class	MachineInfoContainer : public NPListPack<MachineInfoList>
{
public:
	MachineInfoContainer(void){}
};


#endif