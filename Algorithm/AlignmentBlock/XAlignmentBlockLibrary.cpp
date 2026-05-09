/*
 * Copyright (C) 2025
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


#include "XAlignmentBlockLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XAlignmentBlock.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>

AlignmentBlockLibrary::AlignmentBlockLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
    MinAreaSize	=0;
    MaxAreaSize	=99999;
    MinAreaDots	=0;
    MaxAreaDots	=99999999;

	OverlapDot		=10;
	LimitSize		=500;
	NoisePinholeSize=2;
	NoiseIslandSize =2;
	DeadZone		=30;
	ExpandArea		=10;
	NeighborArea		=100;
	NeighborMatchingRate=0.6;
	FlatnessLimit	=6;
	LaplaceFilterSize	=11;
	UseRemover			=true;

	SearchDot	=200;
	MaxDegree	=10;
	LineLength	=20;
	MinVar		=5;
	ThreDiv		=20;
	DustSize	=10;
}

bool	AlignmentBlockLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=AlignmentBlockVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MinAreaSize)==false)
		return false;
	if(::Save(f,MaxAreaSize)==false)
		return false;
	if(::Save(f,MinAreaDots)==false)
		return false;
	if(::Save(f,MaxAreaDots)==false)
		return false;

	if(::Save(f,OverlapDot)==false)
		return false;
	if(::Save(f,LimitSize)==false)
		return false;
	if(::Save(f,NoisePinholeSize)==false)
		return false;
	if(::Save(f,NoiseIslandSize)==false)
		return false;
	if(::Save(f,DeadZone)==false)
		return false;
	if(::Save(f,ExpandArea)==false)
		return false;
	if(::Save(f,NeighborArea)==false)
		return false;
	if(::Save(f,NeighborMatchingRate)==false)
		return false;
	if(::Save(f,FlatnessLimit)==false)
		return false;
	if(::Save(f,LaplaceFilterSize)==false)
		return false;
	if(::Save(f,UseRemover)==false)
		return false;

	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,MaxDegree)==false)
		return false;
	if(::Save(f,LineLength)==false)
		return false;
	if(::Save(f,MinVar)==false)
		return false;
	if(::Save(f,ThreDiv)==false)
		return false;
	if(::Save(f,DustSize)==false)
		return false;
	return true;
}
bool	AlignmentBlockLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,MinAreaSize)==false)
		return false;
	if(::Load(f,MaxAreaSize)==false)
		return false;
	if(::Load(f,MinAreaDots)==false)
		return false;
	if(::Load(f,MaxAreaDots)==false)
		return false;

	if(::Load(f,OverlapDot)==false)
		return false;
	if(::Load(f,LimitSize)==false)
		return false;
	if(::Load(f,NoisePinholeSize)==false)
		return false;
	if(::Load(f,NoiseIslandSize)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,DeadZone)==false)
			return false;
	}
	if(Ver>=3){
		if(::Load(f,ExpandArea)==false)
			return false;
	}
	if(Ver>=5){
		if(::Load(f,NeighborArea)==false)
			return false;
		if(::Load(f,NeighborMatchingRate)==false)
			return false;
	}
	if(Ver>=5){
		if(::Load(f,FlatnessLimit)==false)
			return false;
	}
	if(Ver>=5){
		if(::Load(f,LaplaceFilterSize)==false)
			return false;
	}
	if(Ver>=6){
		if(::Load(f,UseRemover)==false)
			return false;
	}

	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,MaxDegree)==false)
		return false;
	if(::Load(f,LineLength)==false)
		return false;
	if(::Load(f,MinVar)==false)
		return false;
	if(Ver>=4){
		if(::Load(f,ThreDiv)==false)
			return false;
	}
	if(Ver>=7){
		if(::Load(f,DustSize)==false)
			return false;
	}

	return true;
}


AlignmentBlockLibrary	&AlignmentBlockLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AlignmentBlockLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

AlignmentBlockLibraryContainer::AlignmentBlockLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}


