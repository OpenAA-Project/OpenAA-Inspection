/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentFlexArea\XAlignmentFlexAreaLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAlignmentFlexAreaLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XAlignmentFlexArea.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>

AlignmentFlexAreaLibrary::AlignmentFlexAreaLibrary(int LibType,LayersBase *Base)
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
	AdaptedPriority	=-1;
	PickUpEdge		=false;
	PickUpEdgeMinDiff=10;
	MaxCoeffInNeighbor=0.85;

	GlobalSearchDot	=100;
	SearchDot		=40;
	GroupAreaSize	=500;
	CloserRate		=0.1;		//0-0.2
	SmallSearch		=5;
	KeepBW			=true;
}

bool	AlignmentFlexAreaLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=8;

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
	if(::Save(f,PickUpEdge)==false)
		return false;
	if(::Save(f,PickUpEdgeMinDiff)==false)
		return false;
	if(::Save(f,MaxCoeffInNeighbor)==false)
		return false;

	if(::Save(f,GlobalSearchDot)==false)
		return false;
	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,GroupAreaSize)==false)
		return false;
	if(::Save(f,KeepBW)==false)
		return false;
	if(::Save(f,AdaptedPriority)==false)
		return false;
	if(::Save(f,CloserRate)==false)
		return false;
	if(::Save(f,SmallSearch)==false)
		return false;
	return true;
}
bool	AlignmentFlexAreaLibrary::LoadBlob(QIODevice *f)
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
	if(Ver>=6){
		if(::Load(f,PickUpEdge)==false)
			return false;
	}
	if(Ver>=7){
		if(::Load(f,PickUpEdgeMinDiff)==false)
			return false;
	}
	if(Ver>=8){
		if(::Load(f,MaxCoeffInNeighbor)==false)
			return false;
	}

	if(::Load(f,GlobalSearchDot)==false)
		return false;
	if(::Load(f,SearchDot)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,GroupAreaSize)==false)
			return false;
	}
	if(Ver>=3){
		if(::Load(f,KeepBW)==false)
			return false;
	}
	if(Ver>=4){
		if(::Load(f,AdaptedPriority)==false)
			return false;
	}
	if(Ver>=5){
		if(::Load(f,CloserRate)==false)
			return false;
		if(::Load(f,SmallSearch)==false)
			return false;
	}
	return true;
}


AlignmentFlexAreaLibrary	&AlignmentFlexAreaLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AlignmentFlexAreaLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

AlignmentFlexAreaLibraryContainer::AlignmentFlexAreaLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}


