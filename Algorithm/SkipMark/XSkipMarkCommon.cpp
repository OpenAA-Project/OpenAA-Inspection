/*
 * Copyright (C) 2023
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



//#include "XSkipMarkResource.h"
#include "XSkipMark.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XAlgorithmDLL.h"


//-----------------------------------------------------------------

SkipMarkSourceAlgoList::SkipMarkSourceAlgoList(LayersBase *b)
		:ServiceForLayers(b)
{
	AlgoBase=NULL;
}

bool	SkipMarkSourceAlgoList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	bool	B=(AlgoBase!=NULL)?true:false;
	if(::Save(f,B)==false)
		return false;
	if(B==true){
		QString	DLLRoot;
		QString	DLLName;
		AlgoBase->GetAlgorithmRootName(DLLRoot,DLLName);
		if(::Save(f,DLLRoot)==false)
			return false;
		if(::Save(f,DLLName)==false)
			return false;
	}
	if(IDList.Save(f)==false)
		return false;
	return true;
}

bool	SkipMarkSourceAlgoList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	bool	B;
	if(::Load(f,B)==false)
		return false;
	if(B==true){
		QString	DLLRoot;
		QString	DLLName;
		if(::Load(f,DLLRoot)==false)
			return false;
		if(::Load(f,DLLName)==false)
			return false;
		AlgoBase=GetLayersBase()->GetAlgorithmBase(DLLRoot,DLLName);
	}
	else{
		AlgoBase=NULL;
	}
	if(IDList.Load(f)==false)
		return false;
	return true;
}