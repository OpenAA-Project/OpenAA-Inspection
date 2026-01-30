/*
 * Copyright (C) 2024
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
#include "XAlgorithmLibrary.h"

class LibraryUsage : public NPListSaveLoad<LibraryUsage>
{
public:
	QString	UsageName;
	//int		LibType;
	//int		LibID;
	AlgorithmLibraryListContainer	LibList;
	int		AlignmentPriority;
	bool	DefaultPushed;

	LibraryUsage(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class LibraryUsageContainer : public NPListPackSaveLoad<LibraryUsage>
{
public:
	LibraryUsageContainer(void){}
	virtual	LibraryUsage	*Create(void)	override;
};