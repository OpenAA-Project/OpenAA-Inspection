/*
 * Copyright (C) 2024
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

#include "XLibraryUsage.h"
#include "XGeneralFunc.h"
#include "XAlgorithmLibrary.h"

LibraryUsage::LibraryUsage(void)
{
	//LibType=0;
	//LibID=0;
	AlignmentPriority=-1;
	DefaultPushed	=false;
}
bool	LibraryUsage::Save(QIODevice *f)
{
	int	Ver=2;

	if(::Save(f,Ver					)	==false)	return false;

	if(::Save(f,UsageName			)	==false)	return false;
	if(LibList.Save(f)==false)						return false;
	if(::Save(f,AlignmentPriority	)	==false)	return false;
	if(::Save(f,DefaultPushed	)	==false)	return false;
	return true;
}
bool	LibraryUsage::Load(QIODevice *f)
{
	int	Ver;
	if(::Load(f,Ver					)	==false)	return false;

	if(::Load(f,UsageName			)	==false)	return false;
	if(Ver>=2){
		if(LibList.Load(f)==false)					return false;
	}
	else{
		int32	tLibType	;
		int32	tLibID	;
		if(::Load(f,tLibType		)	==false)	return false;
		if(::Load(f,tLibID			)	==false)	return false;
		AlgorithmLibraryList	*a=new AlgorithmLibraryList(tLibType,tLibID,/**/"");
		LibList.RemoveAll();
		LibList.AppendList(a);
	}

	if(::Load(f,AlignmentPriority	)	==false)	return false;
	if(::Load(f,DefaultPushed		)	==false)	return false;
	return true;
}

LibraryUsage	*LibraryUsageContainer::Create(void)
{	
	return new LibraryUsage();
}