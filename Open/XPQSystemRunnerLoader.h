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

#if	!defined(XPQSystemRunnerLoader_h)
#define	XPQSystemRunnerLoader_h

#include "XDLLManager.h"
#include "XPQSystemServiceLib.h"
#include "XPQSystemBaseService.h"
#include <QLibrary>
#include "XPQSystemResult.h"
#include "NList.h"

class	PQSystemRunner;

class	PQSystemRunnerLoader : public NPList<PQSystemRunnerLoader>
							 , public DLLManager , public PQSystemBaseService
{
	QLibrary 		DllLib;

	bool		(*DLL_GetOrganization)(QString &str);
	WORD		(*DLL_GetDLLType)(void);
	bool		(*DLL_GetName)(QString &Root ,QString &Name);
	WORD		(*DLL_GetVersion)(void);
	const char	*(*DLL_GetSystemVersion)(VersionType vtype);
	bool		(*DLL_CheckCopyright)(QString &CopyrightString);
	const char	*(*DLL_GetExplain)(void);
	void		(*DLL_SetLanguageCommon)(LanguagePackage &Pkg ,int LanguageCode);
	void		(*DLL_SetLanguage)		 (LanguagePackage &Pkg ,int LanguageCode);

	PQSystemRunner	*(*DLL_AllocateRunner)(PQSystemBase *Base);
	bool		(*DLL_Release)(PQSystemRunner *pointer);

	PQSystemRunner	*Pointer;

private:
	QString				FileName;
	QString				Organization;
	QString				DLLRoot;
	QString				DLLName;
	QString				ParamFileName;
	WORD				Ver;
	QString				Copyright;

public:
	PQSystemRunnerLoader(PQSystemBase *Base);
	~PQSystemRunnerLoader(void);

	bool		LoadDLL(const QString &filename);
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
	PQSystemRunner	*GetDLLPoint(void)			{	return Pointer;		}
	QString			GetCopyright(void)				{	return Copyright;		}
	WORD			GetDLLType(void);
	QString			GetExplain(void);

	void	GetExportFunctions(QStringList &Str);
};

class	PQSystemRunnerLoaderPointer : public NPList<PQSystemRunnerLoaderPointer>
{
	PQSystemRunnerLoader	*Pointer;
public:
	PQSystemRunnerLoaderPointer(PQSystemRunnerLoader *s):Pointer(s){}

	PQSystemRunnerLoader	*GetPointer(void)	{	return Pointer;	}
	QString		GetDLLName(void)	{	return Pointer->GetDLLName();	}
	virtual	int	Compare(PQSystemRunnerLoaderPointer &src)	override;
};

class	PQSystemRunnerLoaderClassified : public NPListPack<PQSystemRunnerLoaderPointer>
										,public NPList<PQSystemRunnerLoaderClassified>
{
	QString	DLLRoot;

public:
	PQSystemRunnerLoaderClassified(const QString &_DLLRoot):DLLRoot(_DLLRoot){}

	QString	GetDLLRoot(void)	{	return DLLRoot;	}
	virtual	int	Compare(PQSystemRunnerLoaderClassified &src)	override;
};

class	PQSystemRunnerLoaderPointerPack : public NPListPack<PQSystemRunnerLoaderClassified>
{
public:
	PQSystemRunnerLoaderPointerPack(void){}
};


class	PQSystemRunnerLoaderContainer : public NPListPack<PQSystemRunnerLoader>
										, public PQSystemBaseService
{
public:
	PQSystemRunnerLoaderPointerPack	Classified;

	PQSystemRunnerLoaderContainer(PQSystemBase *Base);
	~PQSystemRunnerLoaderContainer(void);

	int		LoadAllDLL(const QString &RelativePath);
};

#endif