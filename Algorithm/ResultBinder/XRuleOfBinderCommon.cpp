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

#include "XRuleOfBinderCommon.h"
#include "XGeneralFunc.h"

bool	ItemIDNameList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	return true;
}

bool	ItemIDNameList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}

		
bool	ConditionList::InputList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,OK)==false)
		return false;
	if(::Save(f,ErrorCode)==false)
		return false;
	if(::Save(f,ErrorCondition)==false)
		return false;
	return true;
}

bool	ConditionList::InputList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,OK)==false)
		return false;
	if(::Load(f,ErrorCode)==false)
		return false;
	if(::Load(f,ErrorCondition)==false)
		return false;
	return true;
}

			
bool	ConditionList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(InputData.Save(f)==false)
		return false;
	if(::Save(f,OutputOK)==false)
		return false;
	if(::Save(f,OutputErrorCode)==false)
		return false;
	return true;
}

bool	ConditionList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(InputData.Load(f)==false)
		return false;
	if(::Load(f,OutputOK)==false)
		return false;
	if(::Load(f,OutputErrorCode)==false)
		return false;
	return true;
}

