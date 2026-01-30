/*
 * Copyright (C) 2014
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

#include "XBooter.h"
#include "XGeneralFunc.h"

bool	ExecuteApplicationList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,Program)==false)
		return false;
	if(::Save(f,Parameter)==false)
		return false;
	return true;
}

bool	ExecuteApplicationList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,Program)==false)
		return false;
	if(::Load(f,Parameter)==false)
		return false;
	return true;
}

BooterParameter::BooterParameter(void)
{
	DefaultFileName=/**/"BooterParameter.dat";
}

bool	BooterParameter::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,WindowMessage)==false)
		return false;
	if(::Save(f,ButtonMessage)==false)
		return false;
	if(::Save(f,RemoteReceiver)==false)
		return false;
	if(BeforeBoot.Save(f)==false)
		return false;
	if(::Save(f,ExecuteBeforeBooter)==false)
		return false;
	if(AfterBoot.Save(f)==false)
		return false;
	if(::Save(f,ExecuteAfterBooter)==false)
		return false;
	return true;
}

bool	BooterParameter::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,WindowMessage)==false)
		return false;
	if(::Load(f,ButtonMessage)==false)
		return false;
	if(::Load(f,RemoteReceiver)==false)
		return false;
	if(BeforeBoot.Load(f)==false)
		return false;
	if(::Load(f,ExecuteBeforeBooter)==false)
		return false;
	if(AfterBoot.Load(f)==false)
		return false;
	if(::Load(f,ExecuteAfterBooter)==false)
		return false;
	return true;
}