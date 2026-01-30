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
#include <QIODevice>

enum ConfirmType
{
	CF_Emergency		=1
	,CF_Alert			=2
	,CF_NG				=3
	,CF_ReqConfirm		=4
};

class ConfirmItemList : public NPListSaveLoad<ConfirmItemList>
{
public:
	int		Phase	;
	int		Page	;
	int		Layer	;
	int		ItemID	;
	QString	Cause	;
	ConfirmType	CType;

	ConfirmItemList(void);
	ConfirmItemList(const ConfirmItemList &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	ConfirmItemList	&operator=(const ConfirmItemList &src);
};

class ConfirmItemListContainer : public NPListPackSaveLoad<ConfirmItemList>
{
public:
	ConfirmItemListContainer(void);
	ConfirmItemListContainer(const ConfirmItemListContainer &src);

	virtual	ConfirmItemList	*Create(void);

	ConfirmItemListContainer	&operator=(const ConfirmItemListContainer &src);
};