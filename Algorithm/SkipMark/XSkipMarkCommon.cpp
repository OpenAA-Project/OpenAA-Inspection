/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algoritnm\SkipMark\XSkipMarkCommon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "XSkipMarkResource.h"
#include "XSkipMark.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XAlgorithmDLL.h"


//-----------------------------------------------------------------

SkipMarkSourceAlgoList::SkipMarkSourceAlgoList(LayersBase *b)
		:ServiceForLayers(b)
{
	AlgoBase=NULL;
}

bool	SkipMarkSourceAlgoList::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	bool	B=(AlgoBase!=NULL)?true:false;
	if(::Save(f,B)==false)
		return false;
	if(B==true){
		QString	DLLRoot;
		QString	DLLName;
		AlgoBase->GetAlgorithmRootName(DLLRoot,DLLName);
		if(::Save(f,DLLRoot)==false)
			return false;
		if(::Save(f,DLLName)==false)
			return false;
	}
	if(IDList.Save(f)==false)
		return false;
	return true;
}

bool	SkipMarkSourceAlgoList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	bool	B;
	if(::Load(f,B)==false)
		return false;
	if(B==true){
		QString	DLLRoot;
		QString	DLLName;
		if(::Load(f,DLLRoot)==false)
			return false;
		if(::Load(f,DLLName)==false)
			return false;
		AlgoBase=GetLayersBase()->GetAlgorithmBase(DLLRoot,DLLName);
	}
	else{
		AlgoBase=NULL;
	}
	if(IDList.Load(f)==false)
		return false;
	return true;
}
