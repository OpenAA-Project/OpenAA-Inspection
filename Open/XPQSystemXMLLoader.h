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

#if	!defined(XPQSystemXMLLoader_h)
#define	XPQSystemXMLLoader_h

#include "XTypeDef.h"
#include "NList.h"
#include "XDLLManager.h"
#include "XPQSystemServiceLib.h"
#include "XPQSystemBaseService.h"
#include "XPQSystemResult.h"

class	LanguagePackage;
class	PQSystemXMLAccessor;

class	PQSystemXMLLoader : public DLLManager , public PQSystemBaseService
{
	QLibrary 		DllLib;
public:
	bool			(*DLL_GetOrganization)(QString &str);
	WORD			(*DLL_GetDLLType)(void);
	bool			(*DLL_GetName)(QString &Root ,QString &Name);
	WORD			(*DLL_GetVersion)(void);
	void			(*DLL_SetLanguage)(LanguagePackage &Pkg ,int LanguageCode);
	const char		*(*DLL_GetExplain)(void);
	bool			(*DLL_CheckCopyright)(QString &CopyrightString);
	const	char	*(*DLL_GetParamName)(void);

	PQSystemXMLDLLBaseRoot	*(*DLL_Initial)(PQSystemBase *Base);
	bool			(*DLL_Release)(PQSystemXMLDLLBaseRoot *DLL);

private:
	QString				FileName;
	QString				Organization;
	QString				DLLRoot;
	QString				DLLName;
	QString				ParamFileName;
	WORD				Ver;
	PQSystemXMLDLLBaseRoot	*DLLPoint;
	QString				Copyright;

public:
	PQSystemXMLLoader(PQSystemBase *Base);
	~PQSystemXMLLoader(void);

	bool		LoadDLL(const QString &filename);
	bool		IsResultDLL(void);
	bool		Initial(void);
	void		Release(void);
	bool		CheckSystemVersion(QStringList &Str);


	const QString	&GetFileName(void)				{	return FileName;		}
	void			SetFileName(const QString &s)	{	FileName=s;		}
	QString			GetOrganization(void)			{	return Organization;	}
	QString			GetDLLRoot(void)				{	return DLLRoot;			}
	QString			GetDLLName(void)				{	return DLLName;			}
	QString			GetParamFileName(void)			{	return ParamFileName;	}
	WORD			GetVersion(void)				{	return Ver;				}
	PQSystemXMLDLLBaseRoot	*GetDLLPoint(void)			{	return DLLPoint;		}
	QString			GetCopyright(void)				{	return Copyright;		}
	WORD			GetDLLType(void);
	QString			GetExplain(void);

	void	GetExportFunctions(QStringList &Str);
};


#endif