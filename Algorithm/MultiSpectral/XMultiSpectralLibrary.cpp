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

#include "XMultiSpectralLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMultiSpectral.h"

MultiSpectralLibrary::MultiSpectralLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	SearchDot		=2;
	ThresholdLength	=15;
	OKDot			=15;
}

MultiSpectralLibrary::~MultiSpectralLibrary(void)
{
}

bool	MultiSpectralLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	if(::Save(f,OKDot)==false)
		return false;
	return true;
}
bool	MultiSpectralLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,ThresholdLength)==false)
		return false;
	if(::Load(f,OKDot)==false)
		return false;
	return true;
}

MultiSpectralLibrary	&MultiSpectralLibrary::operator=(const AlgorithmLibrary &src)
{
	MultiSpectralLibrary	*s=(MultiSpectralLibrary *)&src;
	SearchDot		=s->SearchDot;
	ThresholdLength	=s->ThresholdLength;
	return *this;
}