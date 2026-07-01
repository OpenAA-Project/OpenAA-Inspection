/*
 * Copyright (C) 2024
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

#include "NList.h"
#include <QString>
#include <QIODevice>
#include "XTypeDef.h"
#include "XDLLType.h"
#include <QApplication>


class	LayersBase;
class	LanguagePackage;
class	PQSystemRunner;

#if	!defined(ForApplication)

extern "C"{

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD	DLL_GetDLLType(void);
DEFFUNCEX	WORD	DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	const char	*DLL_GetExplain(void);
DEFFUNCEX	void	DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);

DEFFUNCEX	PQSystemRunner	*DLL_CreateRunner(LayersBase *Base);
DEFFUNCEX	void	DLL_CloseRunner(PQSystemRunner *handle);
DEFFUNCEX	void	DLL_InitialQt(QApplication *AppBase);

#else
bool	DLL_GetName(QString &Root ,QString &Name);
WORD	DLL_GetDLLType(void);
WORD	DLL_GetVersion(void);
const char	*DLL_GetSystemVersion(VersionType vtype);
const char	*DLL_GetExplain(void);
void	DLL_SetLanguage		 (LanguagePackage &Pkg ,int LanguageCode);
bool	DLL_CheckCopyright(QString &CopyrightString);

PQSystemRunner	*DLL_InitialRunner(LayersBase *Base);
void	DLL_CloseRunner(PQSystemRunner *handle);
void	DLL_InitialQt(QApplication *AppBase);


};

#endif

