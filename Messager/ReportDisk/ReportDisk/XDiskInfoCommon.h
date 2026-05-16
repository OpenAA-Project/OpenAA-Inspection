/*
 * Copyright (C) 2016
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

#if	!defined(XDISKINFOCOMMON_H)
#define	XDISKINFOCOMMON_H

#include "NListComp.h"
#include <QString>
#include "XDateTime.h"
#include <time.h>
#include "XTypeDef.h"
#include "XGeneralFunc.h"

class	DiskFileInfo : public NPListSaveLoad<DiskFileInfo>
{
public:
	QString		PCName;
	QString		Path;
	QString		FileName;
	qint64		Size;
	XDateTime	UpdatedTime;

	DiskFileInfo(void){	Size=0;	}

	virtual	bool Save(QIODevice *f);
	virtual	bool Load(QIODevice *f);

	DiskFileInfo	&operator=(DiskFileInfo &src);
};

class	DiskFileInfoContainer : public NPListPackSaveLoad<DiskFileInfo>
{
public:
	DiskFileInfoContainer(void){}
	virtual	DiskFileInfo	*Create(void){	return new DiskFileInfo();	}
};

//------------------------------------------------------------------------
inline	bool DiskFileInfo::Save(QIODevice *f)
{
	if(::Save(f,PCName)==false)
		return false;
	if(::Save(f,Path)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Size)==false)
		return false;
	if(::Save(f,UpdatedTime)==false)
		return false;
	return true;
}

inline	bool DiskFileInfo::Load(QIODevice *f)
{
	if(::Load(f,PCName)==false)
		return false;
	if(::Load(f,Path)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Size)==false)
		return false;
	if(::Load(f,UpdatedTime)==false)
		return false;
	return true;
}

inline	DiskFileInfo	&DiskFileInfo::operator=(DiskFileInfo &src)
{
	PCName	=src.PCName;
	Path	=src.Path;
	FileName=src.FileName;
	Size	=src.Size;
	UpdatedTime	=src.UpdatedTime;
	return *this;
}

#endif