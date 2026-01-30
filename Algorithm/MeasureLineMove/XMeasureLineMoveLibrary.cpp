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

#include "XMeasureLineMoveLibrary.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XMeasureLineMove.h"


MeasureLineMoveLibrary::MeasureLineMoveLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	SearchDot	=10;
	ThresholdM	=0;
	ThresholdP	=0;
	EdgeWidth	=10;
	PrevailRight=false;
	PrevailLeft	=false;
	UsageLayer	=0;
	ModeToSetInInitial	=true;
	OKRangeInInitial	=0;
	OutputType			=0;
	SearchType			=0;
	ThresholdRate		=0.1;
}

MeasureLineMoveLibrary::~MeasureLineMoveLibrary(void)
{
}

bool	MeasureLineMoveLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=7;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,ThresholdM)==false)
		return false;
	if(::Save(f,ThresholdP)==false)
		return false;
	if(::Save(f,EdgeWidth)==false)
		return false;
	if(::Save(f,PrevailRight)==false)
		return(false);
	if(::Save(f,PrevailLeft)==false)
		return(false);
	if(::Save(f,UsageLayer)==false)
		return(false);
	if(::Save(f,ModeToSetInInitial)==false)
		return(false);
	if(::Save(f,OKRangeInInitial)==false)
		return(false);
	if(::Save(f,OutputType)==false)
		return(false);
	if(::Save(f,SearchType)==false)
		return(false);
	if(::Save(f,ThresholdRate)==false)
		return(false);
	return true;
}
bool	MeasureLineMoveLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,SearchDot)==false)
		return(false);
	if(::Load(f,ThresholdM)==false)
		return(false);
	if(::Load(f,ThresholdP)==false)
		return(false);
	if(::Load(f,EdgeWidth)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,PrevailRight)==false)
			return(false);
		if(::Load(f,PrevailLeft)==false)
			return(false);
	}
	if(Ver>=3){
		if(::Load(f,UsageLayer)==false)
			return(false);
	}
	if(Ver>=4){
		if(::Load(f,ModeToSetInInitial)==false)
			return(false);
		if(::Load(f,OKRangeInInitial)==false)
			return(false);
	}
	if(Ver>=5){
		if(::Load(f,OutputType)==false)
			return(false);
	}
	if(Ver>=6){
		if(::Load(f,SearchType)==false)
			return(false);
	}
	if(Ver>=7){
		if(::Load(f,ThresholdRate)==false)
			return(false);
	}
	return true;
}

MeasureLineMoveLibrary	&MeasureLineMoveLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((MeasureLineMoveLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}