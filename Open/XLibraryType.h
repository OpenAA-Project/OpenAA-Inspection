/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XLibraryType.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XLIBRARYTYPE_H)
#define	XLIBRARYTYPE_H

#include "NList.h"
#include "XTypeDef.h"
#include <QIODevice>
#include <QString>

class	LayersBase;
class	LogicDLLBaseClass;

class	LibraryTypeList : public NPList<LibraryTypeList>
{
	int		LibType;
	QString	LibName;
public:
	LibraryTypeList(void){	LibType=0;	}
	LibraryTypeList(const LibraryTypeList &s)	{	LibType=s.LibType;	LibName=s.LibName;	}

	LibraryTypeList	&operator=(const LibraryTypeList &s)	{	LibType=s.LibType;	LibName=s.LibName;	return *this;	}

	int		GetLibType(void)	const	{	return LibType;	}
	QString	GetLibName(void)	const	{	return LibName;	}

	void	SetLibType(int b)			{	LibType=b;	}
	void	SetLibName(const QString &s){	LibName=s;	}
};

class	LibTypeListContainer : public NPListPack<LibraryTypeList>
{
public:
	LibTypeListContainer(void){}

	void	LoadFromDatabase(LayersBase *Base);
	void	LoadFromDatabaseInstalled(LayersBase *Base ,LogicDLLBaseClass *LContainer);
	LibraryTypeList	*FindLibraryType(int LibType);
	QString	FindLibraryTypeName(int LibType);
};

#endif