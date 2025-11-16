/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Palletize\XPalletizeLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XPalletizeLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XDataInLayer.h"
#include <QBuffer>
#include "XPalletize.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


PalletizeLibrary::PalletizeLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	AngleRange		=20;
	MinZoomSize		=0.8;
	MaxZoomSize		=1.3;
	PieceSize		=50;
	SearchDotPiece	=4;
	ThresholdV		=30;
	MaxCountOfPiece	=1;
	ThreshCoeff		=0.6;
	SearchNearBy	=50;
	MaxShift		=200;
}

bool	PalletizeLibrary::SaveBlob(QIODevice *f)
{
	WORD	Ver=4;

	if(::Save(f,Ver)==false){
		return false;
	}

	if(::Save(f,AngleRange)==false)
		return false;
	if(::Save(f,MinZoomSize)==false)
		return false;
	if(::Save(f,MaxZoomSize)==false)
		return false;
	if(::Save(f,PieceSize)==false)
		return false;
	if(::Save(f,SearchDotPiece)==false)
		return false;
	if(::Save(f,ThresholdV)==false)
		return false;
	if(::Save(f,MaxCountOfPiece)==false)
		return false;
	if(::Save(f,ThreshCoeff)==false)
		return false;
	if(::Save(f,SearchNearBy)==false)
		return false;
	if(::Save(f,MaxShift)==false)
		return false;

	return true;
}
bool	PalletizeLibrary::LoadBlob(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,AngleRange)==false)
		return false;
	if(::Load(f,MinZoomSize)==false)
		return false;
	if(::Load(f,MaxZoomSize)==false)
		return false;
	if(::Load(f,PieceSize)==false)
		return false;
	if(::Load(f,SearchDotPiece)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,ThresholdV)==false)
			return false;
		if(::Load(f,MaxCountOfPiece)==false)
			return false;
		if(::Load(f,ThreshCoeff)==false)
			return false;
		if(::Load(f,SearchNearBy)==false)
			return false;
	}
	if(Ver>=3){
		if(::Load(f,MaxShift)==false)
			return false;
	}

	return true;
}


PalletizeLibrary	&PalletizeLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((PalletizeLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

//==============================================================================
PalletizeLibraryContainer::PalletizeLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}


