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

#include "XCheckEverydayCommon.h"



CheckEverydayLightInfo::CheckEverydayLightInfo(void)
{
	Page	=0;
	Layer	=0;
	ID		=0;
	BrightnessLow	=0;
	BrightnessHigh	=255;
	CurrentValue	=0;
	Result		=true;
	x1=y1=x2=y2=0;
}

bool	CheckEverydayLightInfo::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,BrightnessLow)==false)
		return false;
	if(::Load(f,BrightnessHigh)==false)
		return false;
	if(::Load(f,CurrentValue)==false)
		return false;
	if(::Load(f,Result)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

bool	CheckEverydayLightInfo::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,BrightnessLow)==false)
		return false;
	if(::Save(f,BrightnessHigh)==false)
		return false;
	if(::Save(f,CurrentValue)==false)
		return false;
	if(::Save(f,Result)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}


CheckEverydayFocusInfo::CheckEverydayFocusInfo(void)
{
	Page		=0;
	Layer		=0;
	ID			=0;
	FocusLow	=0;
	CurrentValue=0;
	Result		=true;
	x1=y1=x2=y2=0;
}


bool	CheckEverydayFocusInfo::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,FocusLow)==false)
		return false;
	if(::Load(f,CurrentValue)==false)
		return false;
	if(::Load(f,Result)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

bool	CheckEverydayFocusInfo::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,FocusLow)==false)
		return false;
	if(::Save(f,CurrentValue)==false)
		return false;
	if(::Save(f,Result)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}