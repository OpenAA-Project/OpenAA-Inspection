/*
 * Copyright (C) 2025
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

#pragma once

#include "XTypeDef.h"
#include "XFlexArea.h"

class HoughLine : public NPListSaveLoad<HoughLine>
{
public:
	double	X1,Y1,X2,Y2;
	int		DotCount;

	HoughLine(void);
	~HoughLine(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class HoughLineContainer : public NPListPackSaveLoad<HoughLine>
{
public:
	HoughLineContainer(void){}
	~HoughLineContainer(void){}

	virtual	HoughLine	*Create(void)	{	return new HoughLine();	}
};

//=========================================================================
void	PickupLinesByHough(FlexArea &Area
							,HoughLineContainer &PickedLines
							,int LineArea=2);

void	PickupLinesByHough(PureFlexAreaListContainer &FPack
							,HoughLineContainer &PickedLines
							,int LineArea=2);
