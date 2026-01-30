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

#pragma once

#include <QString>
#include "XTypeDef.h"
#include "XDLLType.h"

class	LayersBase;
class	QWidget;
class	ShadowTree;
class	LanguagePackage;

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

extern	"C"
{
DEFFUNCEX	WORD		DLL_GetDLLType(void);
DEFFUNCEX	bool		DLL_GetName(QString &str);
DEFFUNCEX	WORD		DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void		DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	bool		DLL_CheckCopyright(QString &CopyrightString);

DEFFUNCEX	ShadowTree	*DLL_Initial(int ShadowNumber,LayersBase *ParentBase
									,const QString &GlobalParamFileName
									,const QString &GUIFileName);
DEFFUNCEX	bool		DLL_Close(ShadowTree *handle);
DEFFUNCEX	bool		DLL_ShowSetting(ShadowTree *handle, QWidget *parent);

};