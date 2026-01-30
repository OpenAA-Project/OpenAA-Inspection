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



#include "XMatchShiftRotationLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMatchShiftRotation.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


MatchShiftRotationLibrary::MatchShiftRotationLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	PickupL		=0;
	PickupH		=255;
    MinAreaSize	=0;
    MaxAreaSize	=99999;
    MinAreaDots	=0;
    MaxAreaDots	=99999999;

	ExpansionDot	=10;
	LimitSize		=500;

	NoisePinholeSize	=0;
	NoiseIslandSize		=0;
	EdgeWidth			=0;

	SearchArea			=100;
	SearchAngle			=180;
	SearchLittleInItem	=2;
	MatchingRate		=0.8;
}

bool	MatchShiftRotationLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=2;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,PickupL)==false)
		return false;
	if(::Save(f,PickupH)==false)
		return false;

	if(::Save(f,MinAreaSize)==false)
		return false;
	if(::Save(f,MaxAreaSize)==false)
		return false;
	if(::Save(f,MinAreaDots)==false)
		return false;
	if(::Save(f,MaxAreaDots)==false)
		return false;

	if(::Save(f,ExpansionDot)==false)
		return false;
	if(::Save(f,LimitSize)==false)
		return false;

	if(::Save(f,NoisePinholeSize)==false)
		return false;
	if(::Save(f,NoiseIslandSize)==false)
		return false;
	if(::Save(f,EdgeWidth)==false)
		return false;

	if(::Save(f,SearchArea)==false)
		return false;
	if(::Save(f,SearchAngle)==false)
		return false;
	if(::Save(f,SearchLittleInItem)==false)
		return false;
	if(::Save(f,MatchingRate)==false)
		return false;
	return true;
}
bool	MatchShiftRotationLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,PickupL)==false)
		return false;
	if(::Load(f,PickupH)==false)
		return false;

	if(::Load(f,MinAreaSize)==false)
		return false;
	if(::Load(f,MaxAreaSize)==false)
		return false;
	if(::Load(f,MinAreaDots)==false)
		return false;
	if(::Load(f,MaxAreaDots)==false)
		return false;

	if(::Load(f,ExpansionDot)==false)
		return false;
	if(::Load(f,LimitSize)==false)
		return false;

	if(::Load(f,NoisePinholeSize)==false)
		return false;
	if(::Load(f,NoiseIslandSize)==false)
		return false;
	if(::Load(f,EdgeWidth)==false)
		return false;

	if(::Load(f,SearchArea)==false)
		return false;
	if(::Load(f,SearchAngle)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,SearchLittleInItem)==false)
			return false;
	}
	if(::Load(f,MatchingRate)==false)
		return false;

	return true;
}


MatchShiftRotationLibrary	&MatchShiftRotationLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((MatchShiftRotationLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

MatchShiftRotationLibraryContainer::MatchShiftRotationLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}

