/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\SystemVersion.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
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
