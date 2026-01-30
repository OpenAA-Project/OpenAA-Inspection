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
#include "XServiceForLayers.h"
#include "XTypeDef.h"

class LevelFolder;

class LevelFolderContainer final
			: public NPListPackSaveLoad<LevelFolder>,public ServiceForLayers
{
public:
	explicit	LevelFolderContainer(LayersBase *base);
	LevelFolderContainer(const LevelFolderContainer &src);

	LevelFolder	*Create(void);

	LevelFolderContainer	&operator=(const LevelFolderContainer &src);

	LevelFolder	*FindByLevelID(int LevelID);
	LevelFolder	*FindByLevelValue(int LevelParentID,int LevelValue);
	bool	RemoveByLevelID(int LevelID);
	bool	BuildFromDB(int ParentID=0	/*From top*/);
	int		GetMaxLevelID(void);
private:
	LevelFolder *RemoveByLevelIDInner(int LevelID);
};


class LevelFolder : public NPListSaveLoad<LevelFolder>,public ServiceForLayers
{
public:
	int		LevelID		;
	int		LevelValue	;		//Order in folder	0,1,2,3...
	int		ParentID	;		//0:Top root
	QString	LevelName	;
	QString	Remark		;
	LevelFolderContainer	Children;

	explicit	LevelFolder(LayersBase *base);
	LevelFolder(const LevelFolder &src);

	LevelFolder	&operator=(const LevelFolder &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	int	Compare(LevelFolder &src)	override;

};
