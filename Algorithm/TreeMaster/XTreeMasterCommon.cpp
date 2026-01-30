/*
 * Copyright (C) 2013
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

#include "XTreeMasterCommon.h"
#include "XGeneralFunc.h"


bool	AreaWithColor::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(Color.Save(f)==false)
		return false;
	return true;
}

bool	AreaWithColor::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(Color.Load(f)==false)
		return false;
	return true;
}

void	AreaWithColor::MoveTo(int dx ,int dy)
{
	Area.MoveToNoClip(dx,dy);
}

//====================================================

void	AreaWithColorContainer::MoveTo(int dx ,int dy)
{
	for(AreaWithColor *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveTo(dx,dy);
	}
}