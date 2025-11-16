/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDot.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XDOT_H)
#define	XDOT_H
#include "XTypeDef.h"
#include "NList.h"
#include "XFlexArea.h"
#include <QIODevice>

class	DotList : public NPList<DotList>
{
	int	X,Y;
public:

	DotList(void)	{	X=0;	Y=0;	}
	DotList(const DotList &src);
	DotList(int x ,int y):X(x),Y(y){}
	DotList	&operator=(const DotList &src);

	int	GetX(void){	return X;	}
	int	GetY(void){	return Y;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DotListContainer : public NPListPack<DotList>
{
public:
	DotListContainer(void){}
	DotListContainer	&operator=(DotListContainer &src);
	DotListContainer	&operator+=(DotListContainer &src);

	void	MakeFilledDotsFrom(FlexArea &src);
	void	Add(int x ,int y)		{	AppendList(new DotList(x,y));	}
	void	AddPoint(int x ,int y)	{	AppendList(new DotList(x,y));	}
	void	GetCenter(double &cx, double &cy);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DotListContainerList : public DotListContainer ,public NPList<DotListContainerList>
{
public:
	DotListContainerList(void){}
};

#endif
