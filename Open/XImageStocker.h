/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XImageStocker.h
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#ifndef XImageStockerH
#define XImageStockerH
//---------------------------------------------------------------------------
#include "NList.h"
#include "XTypeDef.h"
#include "XPointer.h"
#include <QImage>
#include <QString>

class	ListOfQImage : public NPList<ListOfQImage>
{
	QString	ResourceName;
	QImage	*Img;
public:
	explicit	ListOfQImage(QImage &img);
	explicit	ListOfQImage(const QString &resourcename);
	virtual	~ListOfQImage(void);

	ListOfQImage	&operator=(const ListOfQImage &src);
	const QString	&GetResourceName(void)	{	return ResourceName;	}	
	const QImage	&GetImage(void)					{	return *((const QImage *)Img);				}
};

class	ListOfQImageStocker : public NPListPack<ListOfQImage>
{
public:
	ListOfQImageStocker(void){}

	const QImage	&GetImage(const QString &resourcename);
};


#endif
