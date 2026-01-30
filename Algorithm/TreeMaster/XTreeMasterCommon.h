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


#endif