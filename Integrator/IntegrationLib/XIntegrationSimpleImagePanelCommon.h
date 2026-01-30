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

#pragma once

#include "NListComp.h"
#include <QString>

class	SelectedItemsInfo : public NPListSaveLoad<SelectedItemsInfo>
{
public:
	int	Phase;
	int	Page;
	int	Layer;
	int	ItemID;
	QString	ItemName;
	QString	Comment;
	QByteArray	SomethingData;

	SelectedItemsInfo(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	SelectedItemsInfo	&operator=(const SelectedItemsInfo &src);
};

class	SelectedItemsInfoContainer : public NPListPackSaveLoad<SelectedItemsInfo>
{
public:
	SelectedItemsInfoContainer(void){}

	virtual	SelectedItemsInfo	*Create(void)	{	return new SelectedItemsInfo();	}

	SelectedItemsInfoContainer	&operator=(const SelectedItemsInfoContainer &src);
};
