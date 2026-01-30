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

#include "XTypeDef.h"
#include "NList.h"
#include <QString>
#include <QIODevice>

//========================================================================================

class	LoadedInfoList : public NPList<LoadedInfoList>
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	QString		FileName;
	enum LoadedStatus{
			 _None		=0
			,_Success	=1
			,_NoFile	=2
			,_Error		=3
	};
	int64			ItemCount;
	LoadedStatus	Error;

	LoadedInfoList(void);
	LoadedInfoList(const LoadedInfoList &src);

	virtual	~LoadedInfoList(void);

	LoadedInfoList	&operator=(const LoadedInfoList &src);

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};


class	LoadedInfoContainerInPhase : public NPListPack<LoadedInfoList>
{
public:
	int		Phase;
	bool	SuccessForImage;

	LoadedInfoContainerInPhase(void)
		:Phase(-1),SuccessForImage(false){}
	LoadedInfoContainerInPhase(const LoadedInfoContainerInPhase &src);

	virtual	~LoadedInfoContainerInPhase(void);

	LoadedInfoContainerInPhase	&operator=(const LoadedInfoContainerInPhase &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	LoadedInfoContainerInPhaseList : public LoadedInfoContainerInPhase ,public NPList<LoadedInfoContainerInPhaseList>
{
public:
	LoadedInfoContainerInPhaseList(void){}
	LoadedInfoContainerInPhaseList(const LoadedInfoContainerInPhaseList &src);
	virtual	~LoadedInfoContainerInPhaseList(void);

	LoadedInfoContainerInPhaseList	&operator=(const LoadedInfoContainerInPhaseList &src);
};

class	LoadedInfoContainer : public NPListPack<LoadedInfoContainerInPhaseList>
{
public:
	LoadedInfoContainer(void){}
	LoadedInfoContainer(const LoadedInfoContainer &src);
	virtual	~LoadedInfoContainer(void);

	LoadedInfoContainer	&operator=(const LoadedInfoContainer &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};
