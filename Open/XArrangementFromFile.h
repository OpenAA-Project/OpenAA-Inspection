/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XArrangementFromFile.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XARRANGEMENTFROMFILE_H)
#define	XARRANGEMENTFROMFILE_H

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XServiceForLayers.h"
#include "XDLLManager.h"

class	ArrangementItem	: public NPList<ArrangementItem>
{
public:
	double	CenterX	 ,CenterY;
	double	ItemWidth,ItemHeight;

	ArrangementItem &operator=(const ArrangementItem &src);
};

inline	ArrangementItem &ArrangementItem::operator=(const ArrangementItem &src)
{
	CenterX		=src.CenterX;
	CenterY		=src.CenterY;
	ItemWidth	=src.ItemWidth;
	ItemHeight	=src.ItemHeight;
	return *this;
}


class	ArrangementDLLClass : public NPList<ArrangementDLLClass> ,public DLLManager,public ServiceForLayers
{
	QLibrary 		DllLib;
protected:

	bool		(*DLL_GetOrganization)(QString &str);
	WORD		(*DLL_GetDLLType)(void);
	bool		(*DLL_GetName)(QString &Root ,QString &Name);
	WORD		(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);

	bool		(*DLL_Initial)(LayersBase *Base);

	bool		(*DLL_GetFileExtType)(QString &ExtTypeStr);
	bool		(*DLL_LoadFromFile  )(QString &FileName ,NPListPack<ArrangementItem> &RetList);
	bool		(*DLL_LoadFromStream)(QIODevice *DevStr ,NPListPack<ArrangementItem> &RetList);

public:
	QString			FileName;
	QString			Organization;
	QString			DLLRoot;
	QString			DLLName;
	WORD			Ver;

	ArrangementDLLClass(LayersBase *base);
	~ArrangementDLLClass(void);

	bool		LoadDLL(QString &filename);
	bool		IsArrangementDLL(void);
	bool		Initial(LayersBase *Base);
	bool		CheckSystemVersion(QStringList &Str);

	bool		GetFileExtType(QString &ExtTypeStr);
	bool		LoadFile(QString &FileName ,NPListPack<ArrangementItem> &RetList);

	void	CopyPointerFrom(ArrangementDLLClass &src);
};

class	ArrangementDLLBase : public NPListPack<ArrangementDLLClass>,public ServiceForLayers
{
public:
	ArrangementDLLBase(LayersBase *Base);

	int		SearchAddDLL(QString path);
	bool	CheckSystemVersion(QStringList &Str);

	void	CopyPointerFrom(ArrangementDLLBase &src);
};

#endif
