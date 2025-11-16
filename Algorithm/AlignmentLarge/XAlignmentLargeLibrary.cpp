/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentLarge\XAlignmentLargeLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XAlignmentLargeLibrary.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "swap.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include <QBuffer>
#include "XAlignmentLarge.h"
#include <omp.h>
#define	_USE_MATH_DEFINES
#include <math.h>


AlignmentLargeLibrary::AlignmentLargeLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	GenerateArea	=false;	
	GenerateMark	=false;	
	GenerateBitBuff	=true;
	MinGenerationAreaDots	=1000;
	MinGenerationMarkDots	=1000;

	Priority		=_PriorityMiddle;

	MoveDotX		=10;		
	MoveDotY		=10;
	MoveDotX2		=10;		
	MoveDotY2		=10;
	SearchAround	=0;
	UsageGlobal		=false;
	MaxCountHLine	=-1;
	MaxCountVLine	=-1;
	JudgeWithBrDif	=true;
	CharacterMode	=false;
	UseLayer		=-1;
	ThresholdColor	=-1;
}

bool	AlignmentLargeLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=4;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,GenerateArea)==false)
		return false;
	if(::Save(f,GenerateMark)==false)
		return false;
	if(::Save(f,GenerateBitBuff)==false)
		return false;
	if(::Save(f,MinGenerationAreaDots)==false)
		return false;
	if(::Save(f,MinGenerationMarkDots)==false)
		return false;
	int32	PriorityData=(int32)Priority;
	if(::Save(f,PriorityData)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;

	if(::Save(f,MoveDotX)==false)
		return false;
	if(::Save(f,MoveDotY)==false)
		return false;
	if(::Save(f,MoveDotX2)==false)
		return false;
	if(::Save(f,MoveDotY2)==false)
		return false;
	if(::Save(f,SearchAround)==false)
		return false;
	if(::Save(f,UsageGlobal)==false)
		return false;
	if(::Save(f,MaxCountHLine)==false)
		return false;
	if(::Save(f,MaxCountVLine)==false)
		return false;
	if(::Save(f,JudgeWithBrDif)==false)
		return false;
	if(::Save(f,CharacterMode)==false)
		return false;
	if(::Save(f,UseLayer)==false)
		return false;
	if(::Save(f,ThresholdColor)==false)
		return false;
	return true;
}
bool	AlignmentLargeLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,GenerateArea)==false)
			return false;
		if(::Load(f,GenerateMark)==false)
			return false;
		if(::Load(f,GenerateBitBuff)==false)
			return false;
		if(::Load(f,MinGenerationAreaDots)==false)
			return false;
		if(::Load(f,MinGenerationMarkDots)==false)
			return false;
		int32	PriorityData;
		if(::Load(f,PriorityData)==false)
			return false;
		Priority	=(_EnumPriority)PriorityData;
		if(LimitedLib.Load(f)==false)
			return false;
	}

	if(::Load(f,MoveDotX)==false)
		return false;
	if(::Load(f,MoveDotY)==false)
		return false;
	if(::Load(f,MoveDotX2)==false)
		return false;
	if(::Load(f,MoveDotY2)==false)
		return false;
	if(::Load(f,SearchAround)==false)
		return false;
	if(::Load(f,UsageGlobal)==false)
		return false;
	if(::Load(f,MaxCountHLine)==false)
		return false;
	if(::Load(f,MaxCountVLine)==false)
		return false;
	if(::Load(f,JudgeWithBrDif)==false)
		return false;
	if(Ver>=3){
		if(::Load(f,CharacterMode)==false)
			return false;
	}
	if(Ver>=4){
		if(::Load(f,UseLayer)==false)
			return false;
		if(::Load(f,ThresholdColor)==false)
			return false;
	}
	else{
		UseLayer=-1;
		ThresholdColor=-1;
	}
	return true;
}


AlignmentLargeLibrary	&AlignmentLargeLibrary::operator=(const AlgorithmLibrary &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((AlignmentLargeLibrary *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

AlignmentLargeLibraryContainer::AlignmentLargeLibraryContainer(LayersBase *base)
:AlgorithmLibraryContainer(base)
{
}


