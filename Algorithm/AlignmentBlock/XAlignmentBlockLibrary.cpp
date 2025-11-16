/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentBlock\XAlignmentBlockLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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

	SearchDot	=200;
	MaxDegree	=10;
	LineLength	=20;
	MinVar		=5;
	ThreDiv		=20;
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
		if(::Save(f,ExpandArea)==false)
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


