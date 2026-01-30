/*
 * Copyright (C) 2023
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

#include "ColorBlockFormResource.h"
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
