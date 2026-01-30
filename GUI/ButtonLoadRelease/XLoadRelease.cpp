/*
 * Copyright (C) 2018
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

#include "XLoadRelease.h"
#include "XGeneralFunc.h"
	
bool	LoadReleaseAlgoList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,DLLRoot)==false)
		return false;
	if(::Save(f,DLLName)==false)
		return false;
	if(::Save(f,Releaseable)==false)
		return false;
	return true;
}
	
bool	LoadReleaseAlgoList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,DLLRoot)==false)
		return false;
	if(::Load(f,DLLName)==false)
		return false;
	if(::Load(f,Releaseable)==false)
		return false;
	return true;
}


LoadReleaseAlgoContainer::LoadReleaseAlgoContainer(void)
{
	ReleaseableMasterBuff	=false;
	ReleaseableTargetBuff	=false;
}

LoadReleaseAlgoList	*LoadReleaseAlgoContainer::Create(void)
{
	return new LoadReleaseAlgoList();
}

bool	LoadReleaseAlgoContainer::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,ReleaseableMasterBuff)==false)
		return false;
	if(::Save(f,ReleaseableTargetBuff)==false)
		return false;
	if(NPListPackSaveLoad<LoadReleaseAlgoList>::Save(f)==false)
		return false;
	return true;
}
bool	LoadReleaseAlgoContainer::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,ReleaseableMasterBuff)==false)
		return false;
	if(::Load(f,ReleaseableTargetBuff)==false)
		return false;
	if(NPListPackSaveLoad<LoadReleaseAlgoList>::Load(f)==false)
		return false;
	return true;
}
