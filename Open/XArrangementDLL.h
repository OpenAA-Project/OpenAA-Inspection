/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XArrangementDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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
