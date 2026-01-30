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

#include "ButtonChangeServerFormResource.h"
#include "XChangeServerInfo.h"
#include "XGeneralFunc.h"


bool	ChangeServerInfo::Save(QIODevice *f)
{
	if(::Save(f,ServerName)==false)
		return false;
	if(::Save(f,DBIPAddress)==false)
		return false;
	if(::Save(f,DBPort)==false)
		return false;
	if(::Save(f,DBFileName)==false)
		return false;
	if(::Save(f,ImagePath)==false)
		return false;
	return true;
}

bool	ChangeServerInfo::Load(QIODevice *f)
{
	if(::Load(f,ServerName)==false)
		return false;
	if(::Load(f,DBIPAddress)==false)
		return false;
	if(::Load(f,DBPort)==false)
		return false;
	if(::Load(f,DBFileName)==false)
		return false;
	if(::Load(f,ImagePath)==false)
		return false;
	return true;
}
ChangeServerInfo	&ChangeServerInfo::operator=(ChangeServerInfo &src)
{
	ServerName	=src.ServerName;
	DBIPAddress	=src.DBIPAddress;
	DBPort		=src.DBPort;
	DBFileName	=src.DBFileName;
	ImagePath	=src.ImagePath;
	return *this;
}