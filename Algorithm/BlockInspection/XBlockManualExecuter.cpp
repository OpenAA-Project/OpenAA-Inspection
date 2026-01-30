/*
 * Copyright (C) 2021
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

#include "XBlockManualExecuter.h"


bool	ManualExecuterBlockBBrightL::Save(QIODevice *f)
{
	if(::Save(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockBBrightL::Load(QIODevice *f)
{
	if(::Load(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockBBrightL::Execute(AlgorithmItemRoot *item)
{
	BlockItem	*Item=dynamic_cast<BlockItem *>(item);
	if(Item!=NULL){
		Item->GetThresholdW()->ThreshouldBag.BBrightWidthL=NewValue;
	}
	return true;
}

//---------------------------------------------------------------------
	
bool	ManualExecuterBlockBBrightH::Save(QIODevice *f)
{
	if(::Save(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockBBrightH::Load(QIODevice *f)
{
	if(::Load(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockBBrightH::Execute(AlgorithmItemRoot *item)
{
	BlockItem	*Item=dynamic_cast<BlockItem *>(item);
	if(Item!=NULL){
		Item->GetThresholdW()->ThreshouldBag.BBrightWidthH=NewValue;
	}
	return true;
}

//---------------------------------------------------------------------

bool	ManualExecuterBlockNBrightL::Save(QIODevice *f)
{
	if(::Save(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockNBrightL::Load(QIODevice *f)
{
	if(::Load(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockNBrightL::Execute(AlgorithmItemRoot *item)
{
	BlockItem	*Item=dynamic_cast<BlockItem *>(item);
	if(Item!=NULL){
		Item->GetThresholdW()->ThreshouldBag.NBrightWidthL=NewValue;
	}
	return true;
}

//---------------------------------------------------------------------
	
bool	ManualExecuterBlockNBrightH::Save(QIODevice *f)
{
	if(::Save(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockNBrightH::Load(QIODevice *f)
{
	if(::Load(f,NewValue)==false)
		return false;
	return true;
}
	
bool	ManualExecuterBlockNBrightH::Execute(AlgorithmItemRoot *item)
{
	BlockItem	*Item=dynamic_cast<BlockItem *>(item);
	if(Item!=NULL){
		Item->GetThresholdW()->ThreshouldBag.NBrightWidthH=NewValue;
	}
	return true;
}

//---------------------------------------------------------------------
