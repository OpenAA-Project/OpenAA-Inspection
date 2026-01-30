/*
 * Copyright (C) 2022
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

#include "XFromToInfo.h"
#include "XGeneralFunc.h"

FromToClass::FromToClass(void)
{
	SrcType	=Info_AllPages;
	SrcShadowLevel	=0;
	SrcShadowNumber	=0;
	DstType	=Info_AllPages;
	DstShadowLevel	=0;
	DstShadowNumber	=0;
}

bool	FromToClass::Save(QIODevice *f)
{
	BYTE	d=(BYTE)SrcType;
	if(::Save(f,d			)==false)	return false;
	if(::Save(f,SrcFileName	)==false)	return false;
	if(SrcPage.Save(f)==false)			return false;
	if(::Save(f,SrcShadowLevel)==false)	return false;
	if(::Save(f,SrcShadowNumber)==false)	return false;

	d=(BYTE)DstType;
	if(::Save(f,d			)==false)	return false;
	if(::Save(f,DstFileName	)==false)	return false;
	if(DstPage.Save(f)==false)			return false;
	if(::Save(f,DstShadowLevel)==false)	return false;
	if(::Save(f,DstShadowNumber)==false)	return false;
	return true;
}
	
bool	FromToClass::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d			)==false)	return false;
	SrcType	=(FromToClassType)d;
	if(::Load(f,SrcFileName	)==false)	return false;
	if(SrcPage.Load(f)==false)			return false;
	if(::Load(f,SrcShadowLevel)==false)	return false;
	if(::Load(f,SrcShadowNumber)==false)	return false;

	if(::Load(f,d			)==false)	return false;
	DstType	=(FromToClassType)d;
	if(::Load(f,DstFileName	)==false)	return false;
	if(DstPage.Load(f)==false)			return false;
	if(::Load(f,DstShadowLevel)==false)	return false;
	if(::Load(f,DstShadowNumber)==false)	return false;

	return true;
}