/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBlockAnalyze.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XBlockInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XBlockLibrary.h"
#include <stdlib.h>
#include "swap.h"
#include <omp.h>

BlockLibNGTypeItem	*BlockItem::MakeNGType(FlexArea &NGArea ,LibNGTypeInAlgorithm &NGContainer)
{
	if(NGContainer.GetFirst()==NULL){
		return NULL;
	}
	int64	Dots=NGArea.GetPatternByte();
	int64	CircleDots=3.14159*(NGArea.GetWidth()*NGArea.GetWidth()+NGArea.GetHeight()*NGArea.GetHeight())/4;
	if(CircleDots==0)
		CircleDots=1;
	int	CRate=(100*Dots)/CircleDots;

	for(LibNGTypeItem *L=NGContainer.GetFirst();L!=NULL;L=L->GetNext()){
		BlockLibNGTypeItem	*BL=(BlockLibNGTypeItem *)L;
		if(BL->MinColor==0 && BL->MaxColor>=255
		&& BL->MinSize<=Dots && Dots<=BL->MaxSize
		&& BL->MinRoundRate<=CRate && CRate<=BL->MaxRoundRate){
			return BL;
		}
	}

	ImageBuffer &a=GetTargetBuff();
	int N=NGArea.GetFLineLen();
	BYTE	MinC=0xFF;
	BYTE	MaxC=0;
	for(int i=0;i<N;i++){
		int	Y	=NGArea.GetFLineAbsY(i);
		int	X1	=NGArea.GetFLineLeftX(i);
		int	Numb=NGArea.GetFLineNumb(i);
		BYTE	*s=a.GetY(Y);
		for(int x=0;x<Numb;x++){
			BYTE	c=s[X1+x];
			if(c<MinC)
				MinC=c;
			if(MaxC<c)
				MaxC=c;
		}
	}

	for(LibNGTypeItem *L=NGContainer.GetFirst();L!=NULL;L=L->GetNext()){
		BlockLibNGTypeItem	*BL=(BlockLibNGTypeItem *)L;
		if(BL->MinColor<=MinC && MaxC<=BL->MaxColor
		&& BL->MinSize<=Dots && Dots<=BL->MaxSize
		&& BL->MinRoundRate<=CRate && CRate<=BL->MaxRoundRate){
			return BL;
		}
	}
	return NULL;
}

