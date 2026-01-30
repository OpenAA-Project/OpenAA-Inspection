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



#include "XProcess3DLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XProcess3D.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


Process3DLibrary::Process3DLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	BaseCycleDot	=100;
	VFilterLength	=5;
	HeightPerShift	=1;

	LargeTilt		=10;
	LargeFlatness	=10;
	SmallFlatness	=10;
	SmallAreaSize	=100;
}

bool	Process3DLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,BaseCycleDot)==false)
		return false;
	if(::Save(f,HeightPerShift)==false)
		return false;
	if(::Save(f,LargeTilt)==false)
		return false;
    if(::Save(f,LargeFlatness)==false)
		return false;
    if(::Save(f,SmallFlatness)==false)
		return false;
    if(::Save(f,SmallAreaSize)==false)
		return false;
    if(::Save(f,VFilterLength)==false)
		return false;

	return true;
}
bool	Process3DLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,BaseCycleDot)==false)
		return false;
	if(::Load(f,HeightPerShift)==false)
		return false;
	if(::Load(f,LargeTilt)==false)
		return false;
    if(::Load(f,LargeFlatness)==false)
		return false;
    if(::Load(f,SmallFlatness)==false)
		return false;
    if(::Load(f,SmallAreaSize)==false)
		return false;
    if(::Load(f,VFilterLength)==false)
		return false;

	return true;
}



Process3DLibrary	&Process3DLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((Process3DLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

Process3DLibraryContainer::Process3DLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}

