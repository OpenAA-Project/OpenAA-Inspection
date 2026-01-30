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