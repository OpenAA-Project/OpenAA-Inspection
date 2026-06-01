/*
 * Copyright (C) 2013
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

#if	!defined(XTREEMASTERCOMMON_H)
#define	XTREEMASTERCOMMON_H

#include "XFlexArea.h"
#include "XColorSpace.h"
#include "NListComp.h"


class	AreaWithColor : public NPListSaveLoad<AreaWithColor>
{
public:
	FlexArea	Area;
	ColorLogic	Color;

	AreaWithColor(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	FlexArea	&GetArea(void)	{	return Area;	}
	void	MoveTo(int dx ,int dy);
};

class	AreaWithColorContainer : public NPListPackSaveLoad<AreaWithColor>
{
public:
	AreaWithColorContainer(void){}

	virtual	AreaWithColor	*Create(void){	return new AreaWithColor();	}
	void	MoveTo(int dx ,int dy);
};

class	TreeMasterResultList : public NPListSaveLoad<TreeMasterResultList>
{
public:
	int		Page;
	int		ItemID;
	QString	CatName;
	int		MasterCode;
	double	ResultE;

	TreeMasterResultList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	TreeMasterResultList	&operator=(TreeMasterResultList &src);
};

class	TreeMasterResultListForPacketPack: public NPListPackSaveLoad<TreeMasterResultList>
{
public:
	TreeMasterResultListForPacketPack(void){}

	TreeMasterResultList	*FindByItemID(int TMItemID);
	virtual	TreeMasterResultList	*Create(void)	{	return new TreeMasterResultList();	}
};


class	TreeMasterList : public NPList<TreeMasterList>
{
public:
	int		Page;
	int		x1,y1,x2,y2;
	int		ItemID;
	QString	CatName;
	int		MasterCode;
	QString MasterName;
	bool	AlertMask;

	TreeMasterList(void){}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
	TreeMasterList	&operator=(TreeMasterList &src);
};

class	TreeMasterListForPacketPack: public NPListPack<TreeMasterList>
{
public:
	TreeMasterListForPacketPack(void){}

	TreeMasterList	*FindByItemID(int TMItemID);
	TreeMasterList *FindByMasterCode(int MasterCode);
	void decreaseID(int BaseID);
	TreeMasterListForPacketPack	&operator+=(TreeMasterListForPacketPack &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};


#endif