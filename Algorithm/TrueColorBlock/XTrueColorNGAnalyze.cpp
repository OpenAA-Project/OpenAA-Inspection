/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\XTrueColorBlockAlgo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTrueColorBlockResource.h"
#include "XTrueColorBlock.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XTrueColorBlockLibrary.h"
#include <stdlib.h>
#include "swap.h"

TrueColorBlockLibNGTypeItem	*TrueColorBlockItem::MakeNGType(FlexArea &NGArea ,LibNGTypeInAlgorithm &NGContainer)
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
		TrueColorBlockLibNGTypeItem	*BL=(TrueColorBlockLibNGTypeItem *)L;
		if(BL->ColorZone.IsEmpty()==true
		&& BL->MinSize<=Dots && Dots<=BL->MaxSize
		&& BL->MinRoundRate<=CRate && CRate<=BL->MaxRoundRate){
			return BL;
		}
	}

	ImageBuffer	*ImageList[100];
	ImageBuffer	**ImagePoint;
	int	Ln=GetLayerNumb();
	if(Ln>sizeof(ImageList)/sizeof(ImageList[0]))
		ImagePoint=new ImageBuffer	*[GetLayerNumb()];
	else
		ImagePoint=ImageList;
	GetTargetBuffList(ImagePoint);

	int N=NGArea.GetFLineLen();
	for(LibNGTypeItem *L=NGContainer.GetFirst();L!=NULL;L=L->GetNext()){
		TrueColorBlockLibNGTypeItem	*BL=(TrueColorBlockLibNGTypeItem *)L;
		bool	NotInside=false;
		for(int i=0;i<N;i++){
			int	Y	=NGArea.GetFLineAbsY(i);
			int	X1	=NGArea.GetFLineLeftX(i);
			int	Numb=NGArea.GetFLineNumb(i);
			BYTE	*sR=ImagePoint[0]->GetY(Y)+X1;
			BYTE	*sG=ImagePoint[1]->GetY(Y)+X1;
			BYTE	*sB=ImagePoint[2]->GetY(Y)+X1;
			int	X=0;
			while(X+8<Numb){
				BYTE	b=BL->ColorZone.Calc8(sR,sG,sB,0);
				if(b!=0xFF){
					NotInside=true;
					goto	OutOfInside;
				}
				X+=8;
				sR+=8;
				sG+=8;
				sB+=8;
			}
			while(X<Numb){
				bool	b=BL->ColorZone.Calc(*sR,*sG,*sB,0);
				if(b==false){
					NotInside=true;
					goto	OutOfInside;
				}
				X++;
				sR++;
				sG++;
				sB++;
			}
		}
OutOfInside:;
		if(NotInside==false){
			if(ImagePoint!=ImageList){
				delete	[]ImagePoint;
			}
			return BL;
		}
	}

	if(ImagePoint!=ImageList){
		delete	[]ImagePoint;
	}
	return NULL;
}
