/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AlgorithmAlignmentProjection\XPacketAlignmentProjection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPacketAlignmentProjection.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlignmentProjection.h"

extern	char	*sRoot;
extern	char	*sName;


bool	AlignmentProjectionShiftList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,CalcDone)==false)
		return false;
	if(::Save(f,ShiftX)==false)
		return false;
	if(::Save(f,ShiftY)==false)
		return false;
	if(::Save(f,MasterX)==false)
		return false;
	if(::Save(f,MasterY)==false)
		return false;
	return true;
}

bool	AlignmentProjectionShiftList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,CalcDone)==false)
		return false;
	if(::Load(f,ShiftX)==false)
		return false;
	if(::Load(f,ShiftY)==false)
		return false;
	if(::Load(f,MasterX)==false)
		return false;
	if(::Load(f,MasterY)==false)
		return false;
	return true;
}


//==================================================================================
