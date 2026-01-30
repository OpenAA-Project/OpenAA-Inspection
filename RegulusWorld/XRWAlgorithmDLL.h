/*
 * Copyright (C) 2025
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

#pragma once

#include <QtGui>
#include <QColor>
#include <QString>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XCSV.h"
#include "XDataComponent.h"
#include "XRegulusWorld.h"
#include "XMacroFunction.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	LanguagePackage;

extern	"C"{

struct	DllToAppFuncs
{
	void		(*APP_MouseMove)(int gx ,int gy);
};


#ifdef _MSC_VER
DEFFUNCEX	bool		DLL_GetOrganization(QString &str);
DEFFUNCEX	WORD		DLL_GetDLLType(void);
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD		DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	bool		DLL_CheckCopyright(QString &CopyrightString);
DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void		DLL_SetLanguageCommon(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	void		DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);

DEFFUNCEX	RW3DBaseRoot	*DLL_InitialAlloc(RegulusWorld *Base);
DEFFUNCEX	void		DLL_Close(void);
DEFFUNCEX	void		ReleaseAlgorithmBase(RW3DBaseRoot *handle);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);

DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);
#endif

};