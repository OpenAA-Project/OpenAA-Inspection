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

#include "NListComp.h"
#include <QIODevice>


class AlignmentBlockItemList : public NPListSaveLoad<AlignmentBlockItemList>
{
public:
	int		ItemID;
	int		X1,Y1,X2,Y2;
	int		CurrentRotationPatternNo;
	double	ResultRadian;
	int		ResultDx,ResultDy;

	AlignmentBlockItemList(void){}
	AlignmentBlockItemList(const AlignmentBlockItemList &src);

	AlignmentBlockItemList	&operator=(const AlignmentBlockItemList &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class AlignmentBlockItemListContainer : public NPListPackSaveLoad<AlignmentBlockItemList>
{
public:
	AlignmentBlockItemListContainer(void){}
	AlignmentBlockItemListContainer(const AlignmentBlockItemListContainer &src);

	AlignmentBlockItemListContainer	&operator=(const AlignmentBlockItemListContainer &src);
	virtual	AlignmentBlockItemList	*Create(void);
};