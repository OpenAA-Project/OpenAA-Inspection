/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XAlgorithmLibNGType.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XALGORITHMLIBNGTYPE_H)
#define	XALGORITHMLIBNGTYPE_H

#include <QIODevice>
#include <QColor>
#include <QPainter>
#include "XTypeDef.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"

class	ResultPosList;
class	AlgorithmItemRoot;


class	LibNGTypeItem : public NPList<LibNGTypeItem>,public ServiceForLayers
{
public:
	int32	TypeUniqueCode;	//ÉfÅ[É^ÉxÅ[ÉXì‡Ç≈óBàÍÇÃíl
	int32	TypeCode;
	QColor	NGColor;
	bool	Blink;
	enum	NGShapeType
	{
		 NG_Circle		=0	//Åõ ìhÇËÇ¬Ç‘Ç≥Ç»Ç¢ä€
		,NG_FilledCircle=1	//Åú ìhÇËÇ¬Ç‘ÇµÇΩä€
		,NG_Rectangle	=2	//Å† ìhÇËÇ¬Ç‘Ç≥Ç»Ç¢éläp
		,NG_FilledRect	=3	//Å° ìhÇËÇ¬Ç‘ÇµÇΩéläp
		,NG_X			=4	//Çw ÉoÉbÉeÉì
		,NG_Star		=5	//Åô
		,NG_FilledStar	=6	//Åö
		,NG_Cross		=7	//Å{
		,NG_Sharp		=8	//ÅÚ
	}NGShape;
	int32	Priority;
	int		NextJumpMilisec;
	QString	NGName;

	LibNGTypeItem(LayersBase *base);

	LibNGTypeItem	&operator=(const LibNGTypeItem &src);

	virtual	int32	GetVersion(void)	{	return 1;	}
	int32	GetTypeUniqueCode(void)		{	return TypeUniqueCode;	}

	bool	SaveCommon(QIODevice *f);
	bool	LoadCommon(QIODevice *f);
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;

	virtual	bool	ShowSetting(void){		return true;	}

	virtual	void	Draw(QPainter &pnt ,int x ,int y ,int size);
};

class	LibNGTypeInAlgorithm : public NPListPack<LibNGTypeItem>
{
public:
	LibNGTypeInAlgorithm(void){}

	LibNGTypeItem	*GetTypeItem(int TypeCode);

	virtual	LibNGTypeItem	*CreateNewItem(void){	return NULL;	}

	void	SortInPriority(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	void	Draw(QPainter &pnt ,int x ,int y ,int size);
};

//------------------------------------------------------------------------
class	LibraryListWithNGType : public NPList<LibraryListWithNGType>
{
public:
	int		LibID;
	LibNGTypeInAlgorithm	NGList;

	explicit	LibraryListWithNGType(int libId){	LibID=libId;	}
	LibNGTypeInAlgorithm	*GetLibNGTypeInAlgorithm(void){	return &NGList;	}

	virtual	void	Draw(QPainter &pnt ,int x ,int y ,int size);
};

class	LibraryListWithNGTypeContainer : public NPListPack<LibraryListWithNGType>
{
public:
	LibraryListWithNGTypeContainer(void){}

	void	SortInPriority(void);
	LibraryListWithNGType	*GetNGTypeList(int libID);

	void	ExecuteInitialAfterEdit(void);
};


#endif
