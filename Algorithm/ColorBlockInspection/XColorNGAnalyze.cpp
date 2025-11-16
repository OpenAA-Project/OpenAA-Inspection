#include "ColorBlockFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XColorBlockInspectionAlgo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XColorBlockInspection.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XColorBlockLibrary.h"
#include <stdlib.h>
#include "swap.h"

ColorBlockLibNGTypeItem	*ColorBlockItem::MakeNGType(FlexArea &NGArea ,LibNGTypeInAlgorithm &NGContainer)
{
	if(NGContainer.GetFirst()==NULL){
		return NULL;
	}
	int64	Dots=NGArea.GetPatternByte();
	int64	CircleDots=3.14159*(NGArea.GetWidth()*NGArea.GetWidth()+NGArea.GetHeight()*NGArea.GetHeight())/4;
			CircleDots=1;
	int	CRate=(100*Dots)/CircleDots;

	for(LibNGTypeItem *L=NGContainer.GetFirst();L!=NULL;L=L->GetNext()){
		ColorBlockLibNGTypeItem	*BL=(ColorBlockLibNGTypeItem *)L;
		if(BL->MinColorR==0 && BL->MaxColorR>=255
		&& BL->MinColorG==0 && BL->MaxColorG>=255
		&& BL->MinColorB==0 && BL->MaxColorB>=255
		&& BL->MinSize<=Dots && Dots<=BL->MaxSize
		&& BL->MinRoundRate<=CRate && CRate<=BL->MaxRoundRate){
			return BL;
		}
	}

	ImageBuffer *TargetBuff[10];
	GetTargetBuffList(TargetBuff);

	int N=NGArea.GetFLineLen();
	BYTE	MinCR=0xFF;
	BYTE	MaxCR=0;
	BYTE	MinCG=0xFF;
	BYTE	MaxCG=0;
	BYTE	MinCB=0xFF;
	BYTE	MaxCB=0;
	for(int i=0;i<N;i++){
		int	Y	=NGArea.GetFLineAbsY(i);
		int	X1	=NGArea.GetFLineLeftX(i);
		int	Numb=NGArea.GetFLineNumb(i);
		BYTE	*sR=TargetBuff[0]->GetY(Y);
		BYTE	*sG=TargetBuff[1]->GetY(Y);
		BYTE	*sB=TargetBuff[2]->GetY(Y);
		for(int x=0;x<Numb;x++){
			BYTE	cR=sR[X1+x];
			BYTE	cG=sG[X1+x];
			BYTE	cB=sB[X1+x];
			if(cR<MinCR)
				MinCR=cR;
			if(MaxCR<cR)
				MaxCR=cR;
			if(cG<MinCG)
				MinCG=cG;
			if(MaxCG<cG)
				MaxCG=cG;
			if(cB<MinCB)
				MinCB=cB;
			if(MaxCB<cB)
				MaxCB=cB;
		}
	}

	for(LibNGTypeItem *L=NGContainer.GetFirst();L!=NULL;L=L->GetNext()){
		ColorBlockLibNGTypeItem	*BL=(ColorBlockLibNGTypeItem *)L;
		if(BL->MinColorR<=MinCR && MaxCR<=BL->MaxColorR
		&& BL->MinColorG<=MinCG && MaxCG<=BL->MaxColorG
		&& BL->MinColorB<=MinCB && MaxCB<=BL->MaxColorB
		&& BL->MinSize<=Dots && Dots<=BL->MaxSize
		&& BL->MinRoundRate<=CRate && CRate<=BL->MaxRoundRate){
			return BL;
		}
	}
	return NULL;
}

