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


#ifndef XAUTOALIGNMENTCOMMON_H
#define XAUTOALIGNMENTCOMMON_H

#include "NList.h"
#include <QString>

class	AASheetInfoList : public NPList<AASheetInfoList>
{
public:
	int		ID;
	int		PicoShift;
	bool	CreatedManual;

	AASheetInfoList(void){}
	AASheetInfoList(int id ,int picosheet,bool createdManual);

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	AASheetInfos : public NPListPack<AASheetInfoList>
{
public:
	AASheetInfos(void){}
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	AAListAttr : public NPList<AAListAttr>
{
public:
	int		LibID;
	bool	CreatedManual;

	AAListAttr(void){}

	AAListAttr	&operator=(AAListAttr &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	AAListAttrContainer : public NPListPack<AAListAttr>
{
public:
	AAListAttrContainer(void){}

	void	Add(int libID, bool createdManual);
	AAListAttrContainer	&operator=(AAListAttrContainer &src);
	bool	IsInclude(int libID ,bool createdManual);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};


#endif
