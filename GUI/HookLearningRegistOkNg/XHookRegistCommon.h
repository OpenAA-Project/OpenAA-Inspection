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
#include <QIODevice>

class LibIDListWithResult : public NPListSaveLoad<LibIDListWithResult>
{
public:
	int		LibType	;
	int		LibID	;
	int		Result	;	//0:Not inspect ,1:OK	2:NG

	LibIDListWithResult(void);
	LibIDListWithResult(const LibIDListWithResult &src);

	LibIDListWithResult	&operator=(const LibIDListWithResult &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class LibIDListWithResultContainer : public NPListPackSaveLoad<LibIDListWithResult>
{
public:
	LibIDListWithResultContainer(void);
	LibIDListWithResultContainer(const LibIDListWithResultContainer &src);

	LibIDListWithResultContainer	&operator=(const LibIDListWithResultContainer &src);
	void	Merge(const LibIDListWithResultContainer &src);

	virtual	LibIDListWithResult	*Create(void)	override;
};