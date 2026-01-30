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

#include "XNaming.h"


bool	NamingGroupList::Save(QIODevice *f)
{
	if(::Save(f,GroupName)==false)
		return false;
	if(::Save(f,GroupID)==false)
		return false;
	return true;
}

bool	NamingGroupList::Load(QIODevice *f)
{
	if(::Load(f,GroupName)==false)
		return false;
	if(::Load(f,GroupID)==false)
		return false;
	return true;
}