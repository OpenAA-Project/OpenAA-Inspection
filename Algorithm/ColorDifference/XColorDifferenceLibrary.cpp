/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XColorDifferenceLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "XColorDifferenceResource.h"
#include "XColorDifference.h"
#include "XColorDifferenceLibrary.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XMainSchemeMemory.h"
#include "XFlexArea.h"


ColorDifferenceLibrary::ColorDifferenceLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	MaxLength				=100;
	GenDeltaE				=4.0;
	GenBlockResolution		=20;
	GenMinArea				=2000;
	GenMaxArea				=20000;
	GenMaxVariable			=5;
	GenMaxBrightDifference	=5;
	GenSurroundMergin		=15;

	AdoptedRate	=100;
	JudgeMethod	=0;
	THDeltaE	=10;
	ItemClass	=0;
	dH			=5;
	dSL			=10;
	dSH			=10;
	dVL			=20;
	dVH			=10;
	AdaptAlignment	=true;
}
ColorDifferenceLibrary::~ColorDifferenceLibrary(void)
{
}

bool	ColorDifferenceLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=ColorDifferenceVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,MaxLength)==false)
		return false;
	if(::Save(f,GenDeltaE)==false)
		return false;
	if(::Save(f,GenBlockResolution	)==false)
		return false;
	if(::Save(f,GenMinArea			)==false)
		return false;
	if(::Save(f,GenMaxArea			)==false)
		return false;
	if(::Save(f,GenMaxVariable		)==false)
		return false;
	if(::Save(f,GenMaxBrightDifference	)==false)
		return false;
	if(::Save(f,GenSurroundMergin)==false)
		return false;
	if(::Save(f,AdoptedRate)==false)
		return false;
	if(::Save(f,THDeltaE)==false)
		return false;
	if(::Save(f,ItemClass)==false)
		return false;
	if(::Save(f,JudgeMethod)==false)
		return(false);
	if(::Save(f,dH)==false)
		return(false);
	if(::Save(f,dSL)==false)
		return(false);
	if(::Save(f,dSH)==false)
		return(false);
	if(::Save(f,dVL)==false)
		return(false);
	if(::Save(f,dVH)==false)
		return(false);
	if(::Save(f,AdaptAlignment)==false)
		return(false);

	return true;
}
bool	ColorDifferenceLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(Ver>=3){
		if(::Load(f,MaxLength)==false)
			return false;
		if(::Load(f,GenDeltaE)==false)
			return false;
	}
	if(Ver>=4){
		if(::Load(f,GenBlockResolution	)==false)
			return false;
		if(::Load(f,GenMinArea			)==false)
			return false;
		if(::Load(f,GenMaxArea			)==false)
			return false;
		if(::Load(f,GenMaxVariable		)==false)
			return false;
	}
	if(Ver>=5){
		if(::Load(f,GenMaxBrightDifference	)==false)
			return false;
		if(::Load(f,GenSurroundMergin)==false)
			return false;
	}
	if(::Load(f,AdoptedRate)==false)
		return false;
	if(::Load(f,THDeltaE)==false)
		return false;
	if(::Load(f,ItemClass)==false)
		return false;

	if(Ver>=2){
		if(::Load(f,JudgeMethod)==false)
			return(false);
		if(::Load(f,dH)==false)
			return(false);
		if(::Load(f,dSL)==false)
			return(false);
		if(::Load(f,dSH)==false)
			return(false);
		if(::Load(f,dVL)==false)
			return(false);
		if(::Load(f,dVH)==false)
			return(false);
	}
	if(Ver>=6){
		if(::Load(f,AdaptAlignment)==false)
			return(false);
	}
	return true;
}


ColorDifferenceLibrary	&ColorDifferenceLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((ColorDifferenceLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

//==============================================================================

ColorDifferenceLibraryContainer::ColorDifferenceLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}
ColorDifferenceLibraryContainer::~ColorDifferenceLibraryContainer(void)
{
}
