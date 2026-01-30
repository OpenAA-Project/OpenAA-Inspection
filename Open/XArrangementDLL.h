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

#if	!defined(XARRANGEMENTDLL_H)
#define	XARRANGEMENTDLL_H

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif

class	ArrangementItem;
class	LayersBase;

extern	"C"{

#ifdef _MSC_VER
DEFFUNCEX	bool		DLL_GetOrganization(QString &str);
DEFFUNCEX	WORD		DLL_GetDLLType(void);
DEFFUNCEX	bool		DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD		DLL_GetVersion(void);
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	const char	*DLL_GetExplain(void);

DEFFUNCEX	bool		DLL_Initial(LayersBase *Base);
DEFFUNCEX	bool		DLL_GetFileExtType(QString &ExtTypeStr);
DEFFUNCEX	bool		DLL_LoadFromFile  (QString &FileName ,NPListPack<ArrangementItem> &RetList);
DEFFUNCEX	bool		DLL_LoadFromStream(QIODevice *DevStr,NPListPack<ArrangementItem> &RetList);

#endif
};

#endif