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


#define	_USE_MATH_DEFINES
#include "XCrossObj.h"
#include "math.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMeasureHolePos.h"
#include "omp.h"

MeasureHolePosLibrary::MeasureHolePosLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	DiaPrecision=25;	//micron size
	PosPrecision=25;	//micron size
	NoiseSize	=2;
	BandWidth	=10;
	SearchDot	=10;
	CalcMode	=0;
}

MeasureHolePosLibrary::~MeasureHolePosLibrary(void)
{
}

bool	MeasureHolePosLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false)
		return false;
	if(HoleColor.Save(f)==false)
		return false;
	if(::Save(f,DiaPrecision)==false)
		return(false);
	if(::Save(f,PosPrecision)==false)
		return(false);
	if(::Save(f,NoiseSize)==false)
		return(false);
	if(::Save(f,SearchDot)==false)
		return(false);
	if(::Save(f,BandWidth)==false)
		return(false);
	if(::Save(f,CalcMode)==false)
		return(false);

	return true;
}
bool	MeasureHolePosLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(HoleColor.Load(f)==false)
		return false;
	if(::Load(f,DiaPrecision)==false)
		return(false);
	if(::Load(f,PosPrecision)==false)
		return(false);
	if(::Load(f,NoiseSize)==false)
		return(false);
	if(::Load(f,SearchDot)==false)
		return(false);
	if(::Load(f,BandWidth)==false)
		return(false);
	if(Ver>=2){
		if(::Load(f,CalcMode)==false)
			return(false);
	}
	return true;
}

MeasureHolePosLibrary	&MeasureHolePosLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((MeasureHolePosLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

//==============================================================================

MeasureHolePosLibraryContainer::MeasureHolePosLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}

MeasureHolePosLibraryContainer::~MeasureHolePosLibraryContainer(void)
{
}