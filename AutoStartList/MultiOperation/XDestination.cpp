/*
 * Copyright (C) 2017
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

#include "XDestination.h"
#include "XGeneralFunc.h"

bool	DestinationPartner::Save(QIODevice *f)
{
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,IPAddress)==false)
		return false;
	if(::Save(f,LocalPath)==false)
		return false;
	return true;
}

bool	DestinationPartner::Load(QIODevice *f)
{
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,IPAddress)==false)
		return false;
	if(::Load(f,LocalPath)==false)
		return false;
	return true;
}