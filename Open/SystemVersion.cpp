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

#include <cmath>
#include "Regulus64Version.h"
#include "XTypeDef.h"
#include <QtGlobal>
#include <stdlib.h>
#include <QStringList>
#include "XGeneralFunc.h"
#include "Regulus64Version.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

extern "C"{

DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	bool		DLL_GetRelatedDLL(QStringList &DLLFileNames);		
DEFFUNCEX	char		*DLL_GetRelatedDLLSystemVersion(const QString &DLLFileName ,VersionType vtype);
};


const char	*DLL_GetSystemVersion(VersionType vtype)
{
	static	char	buff[10];
	switch(vtype){
		case Ver_Qt:	
			return QT_VERSION_STR;
		case Ver_Regulus:
			ItoA(RegulusVersion,buff,10);
			return buff;
		case Ver_Revision:
			return RegulusVersionRevision;
		case Ver_IsMatched:
			return NULL;
	}
	return /**/"";
}