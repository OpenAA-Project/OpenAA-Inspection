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

#if	!defined(XDLLMANAGER_H)
#define	XDLLMANAGER_H

#include "Regulus64Version.h"
#include "XTypeDef.h"
#include <QtGlobal>
#include <stdlib.h>
#include <QStringList>
#include <QLibrary>

class	DLLManager
{
protected:
	bool	ReEntrantDLL;

	const char	*(*DLL_GetSystemVersion)(VersionType vtype);
	bool	(*DLL_GetRelatedDLL)(QStringList &DLLFileNames);		
	char	*(*DLL_GetRelatedDLLSystemVersion)(const QString &DLLFileName ,VersionType vtype);

public:
	DLLManager(void);
	virtual	~DLLManager(void);

	bool	LoadDLL(QLibrary &DllLib);

	bool	GetRelatedDLL(QStringList &DLLFileNames);
	char	*GetRelatedDLLSystemVersion(const QString &DLLFileName ,VersionType vtype);
	const char	*GetSystemVersion(VersionType vtype);

	virtual	void	GetExportFunctions(QStringList &Str);
	bool	CheckSystemVersionFunc(QStringList &Str 
							   ,const QString &DLLType 
							   ,const QString &DLLRoot 
							   ,const QString &DLLName);
};

#endif