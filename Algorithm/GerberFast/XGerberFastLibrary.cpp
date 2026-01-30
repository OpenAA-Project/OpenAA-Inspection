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

#include "XGerberAperture.h"
#include "XGerberFastLibrary.h"

GerberFastLibrary::GerberFastLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	MaxEnlargeDot	=2;
	MaxShrinkDot	=2;
	MaxShiftDot		=2;
	MaxAngleRadius	=1;
	UnstableZone	=2;
}
GerberFastLibrary::~GerberFastLibrary(void)
{
}

bool	GerberFastLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MaxEnlargeDot)==false)
		return false;
	if(::Save(f,MaxShrinkDot)==false)
		return false;
	if(::Save(f,MaxShiftDot)==false)
		return false;
	if(::Save(f,MaxAngleRadius)==false)
		return false;
	if(::Save(f,UnstableZone)==false)
		return false;
	return true;
}
bool	GerberFastLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,MaxEnlargeDot)==false)
		return false;
	if(::Load(f,MaxShrinkDot)==false)
		return false;
	if(::Load(f,MaxShiftDot)==false)
		return false;
	if(::Load(f,MaxAngleRadius)==false)
		return false;
	if(::Load(f,UnstableZone)==false)
		return false;
	return true;
}

GerberFastLibrary	&GerberFastLibrary::operator=(const AlgorithmLibrary &src)
{
	const GerberFastLibrary	*s=dynamic_cast<const GerberFastLibrary *>(&src);
	MaxEnlargeDot	=s->MaxEnlargeDot;
	MaxShrinkDot	=s->MaxShrinkDot;
	MaxShiftDot		=s->MaxShiftDot;
	MaxAngleRadius	=s->MaxAngleRadius;
	UnstableZone	=s->UnstableZone;
	return *this;
}