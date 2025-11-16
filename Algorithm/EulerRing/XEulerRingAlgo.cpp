/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRing\XEulerRingAlgo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XEulerRing.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XEulerRingLibrary.h"
#include "XImageProcess.h"
#include <omp.h>


bool    EulerRingItem::ExecuteProcessingInner(ResultInItemRoot *Res
						  ,int mx ,int my
						  ,ColorLogic &Brightness
						  ,int Mergin)
{
	const EulerRingThreshold	*RThr=GetThresholdR();
	int	XLen=GetArea().GetWidth()+RThr->ExpandedDot*2+16;
	int	XByte=(XLen+7)/8;
	int	YLen=GetArea().GetHeight()+RThr->ExpandedDot*2+2;
	BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpBuff2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear(TmpBuff,0,XByte,YLen);

	int	Kx=GetArea().GetMinX()-RThr->ExpandedDot;
	int	Ky=GetArea().GetMinY()-RThr->ExpandedDot;

	CheckOnNGInner1(mx ,my ,RThr->ExpandedDot
					,Brightness
					,Mergin
					,TmpBuff);

	GetLayersBase()->FatAreaN(TmpBuff,TmpBuff2
						,XByte ,YLen
						,RThr->ExpandedDot);
	MatrixBuffCopy(TmpBuff2					,XByte ,YLen
                 , (const BYTE **)TmpBuff	,XByte ,YLen);	//TmpBuff2‚ÍƒŠƒ“ƒO—Ìˆæ
	MatrixBuffNot	(TmpBuff  ,XByte ,YLen);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(TmpBuff ,XByte ,XLen,YLen ,FPack);


	DeleteMatrixBuff(TmpBuff ,YLen);

	int	AreaCount=0;
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;){
		if(f->GetPatternByte()<4 
			|| (Kx+f->GetMinX())<=GetArea().GetMinX()+1
			|| (Ky+f->GetMinY())<=GetArea().GetMinY()+1
			|| (Kx+f->GetMaxX())>=GetArea().GetMaxX()-1
			|| (Ky+f->GetMaxY())>=GetArea().GetMaxY()-1){
			PureFlexAreaList	*NextP=f->GetNext();
			FPack.RemoveList(f);
			delete	f;
			f=NextP;
		}
		else{
			f=f->GetNext();
			AreaCount++;
		}
	}
	if(AreaCount==0){
		if(Res->GetAddedData()==NULL){
			Res->SetAddedData(new ResultClusterOnItem(),ResultEulerRingOnItemType,0);
		}
		((ResultClusterOnItem *)Res->GetAddedData())->ResultArea.BuildFromRaster(TmpBuff2 
																				,XByte ,YLen
																	              ,Kx,Ky);
		Res->SetAlignedXY(mx,my);
		Res->SetItemSearchedXY(0,0);
		Res->SetResult1(AreaCount);
		Res->SetResult2(0);
		Res->SetError(2);	//NG

		DeleteMatrixBuff(TmpBuff2,YLen);

		return false;
	}

	Res->SetAlignedXY(mx,my);
	Res->SetItemSearchedXY(0,0);
	Res->SetResult1(AreaCount);
	Res->SetResult2(0);
	Res->SetError(1);	//OK
	DeleteMatrixBuff(TmpBuff2,YLen);
	return true;
}

void	EulerRingItem::CheckOnNGInner1(int dx ,int dy ,int turn
                                    ,ColorLogic &Level
									,int Mergin
                                    ,BYTE **pMap)
{
	ImageBuffer	*ImageList[100];
	ImageBuffer	**ImagePoint;
	int	Ln=GetLayerNumb();
	if(Ln>sizeof(ImageList)/sizeof(ImageList[0]))
		ImagePoint=new ImageBuffer*[GetLayerNumb()];
	else
		ImagePoint=ImageList;
	GetTargetBuffList(ImagePoint);

	FlexArea	*fa=&GetArea();
	int	XLen=GetDotPerLine();
	int	YLen=GetMaxLines();
    int starty =fa->GetFLineAbsY(0);
	BYTE	*q;
	int	tx;
	int X;
	int Numb;
	int px;
	int mdy;

	for(int i=0;i<fa->GetFLineLen();i++){
		int Y =fa->GetFLineAbsY(i);
		if(Y+dy<0 || Y+dy>=YLen)
			continue;
		X   =fa->GetFLineLeftX(i);
		Numb=fa->GetFLineNumb(i);
		int x1=X;
		int x2=X+Numb;
		if(x2<0 || x1>=(XLen-1) || x1>x2)
			continue;
		if(x1<0)
			x1=0;
		if(x2>=XLen-1)
			x2=XLen-1;
		Numb=x2-x1;
		X=x1;
		if((dx+X)<0 || (dx+X)>=XLen)
			continue;
		if(Numb<=0)
			continue;

		px=X-fa->GetMinX();
		mdy=Y-starty;
		BYTE	*p0=ImagePoint[0]->GetY(dy+Y)+dx+X;
		BYTE	*p1=ImagePoint[1]->GetY(dy+Y)+dx+X;
		BYTE	*p2=ImagePoint[2]->GetY(dy+Y)+dx+X;

		q=pMap[mdy+turn];

		for(int x=0;x<Numb;x++,p0++,p1++,p2++){
			tx=px+turn+x;
			if(Level.Calc(*p0,*p1,*p2,Mergin)==true){
				q[tx>>3] |= 0x80>>(tx&7);
			}
		}
	}
	if(ImagePoint!=ImageList)
		delete	[]ImagePoint;
}

double	EulerRingItem::EnAverage(int mx,int my
						,ColorLogic &TmpBrightness)
{
	ImageBuffer	*ImageList[100];
	ImageBuffer	**ImagePoint;
	int	Ln=GetLayerNumb();
	if(Ln>sizeof(ImageList)/sizeof(ImageList[0]))
		ImagePoint=new ImageBuffer	*[GetLayerNumb()];
	else
		ImagePoint=ImageList;
	GetTargetBuffList(ImagePoint);
	QRgb	D=CalcCenterBright(ImagePoint,mx,my);
	GetMasterBuffList(ImagePoint);
	QRgb	M=CalcCenterBright(ImagePoint,0,0);
	if(ImagePoint!=ImageList)
		delete	[]ImagePoint;

	const EulerRingThreshold	*RThr=GetThresholdR();
	double	Vc	=GetRGBBrightness(M);
	double	Vd	=GetRGBBrightness(D);

	double	kDifCol=Vd-Vc;
	if(kDifCol> RThr->AdjustWhite)
		kDifCol=RThr->AdjustWhite;
	if(-kDifCol>RThr->AdjustBlack)
		kDifCol=-((int)RThr->AdjustBlack);

	double	Vk=Vc+kDifCol;
	if(Vc>0.0){
		double	m=Vk/Vc;
		TmpBrightness.Multiply(m);
		return m;
	}
	return 1.0;
}

QRgb	EulerRingItem::CalcCenterBright(ImageBuffer *ImageList[] ,int mx ,int my)
{
	int	N=0;
	double	DR=0;
	double	DG=0;
	double	DB=0;
	BYTE	*srcR;
	BYTE	*srcG;
	BYTE	*srcB;
	int		XNumb;
	int		DTmpR;
	int		DTmpG;
	int		DTmpB;

	int	MaxLines	=GetMaxLines();
	int	DotPerLine	=GetDotPerLine();

	FlexArea	*A=&GetArea();
	int		Ln=GetLayerNumb();
	int	YSep;
	int	XSep;
	if(A->GetFLineLen()<20)
		YSep=1;
	else if(A->GetFLineLen()<40)
		YSep=2;
	else if(A->GetFLineLen()<60)
		YSep=3;
	else if(A->GetFLineLen()<100)
		YSep=4;
	else
		YSep=5;

	for(int i=0;i<A->GetFLineLen();i+=YSep){
		int	y =A->GetFLineAbsY  (i)+my;
		if(y<0)
			continue;
		if(y>=MaxLines)
			break;
		int	x1=A->GetFLineLeftX (i)+mx;
		int	x2=A->GetFLineRightX(i)+mx;
		if(x1<0)
			x1=0;
		if(x2>=DotPerLine)
			x2=DotPerLine;
		if(x1>x2)
			continue;

		XNumb=x2-x1;

		if(XNumb<20)
			XSep=1;
		else if(XNumb<40)
			XSep=2;
		else if(XNumb<60)
			XSep=3;
		else if(XNumb<100)
			XSep=4;
		else
			XSep=5;

		if(Ln>=3){
			DTmpR=DTmpG=DTmpB=0;
			srcR=ImageList[0]->GetY(y)+x1;
			srcG=ImageList[1]->GetY(y)+x1;
			srcB=ImageList[2]->GetY(y)+x1;
			for(int x=0;x<XNumb;x+=XSep){
				DTmpR+=*(srcR+x);
				DTmpG+=*(srcG+x);
				DTmpB+=*(srcB+x);
			}
			DR+=DTmpR;
			DG+=DTmpG;
			DB+=DTmpB;
		}
		else if(Ln==2){
			DTmpR=DTmpG=0;
			srcR=ImageList[0]->GetY(y)+x1;
			srcG=ImageList[1]->GetY(y)+x1;
			for(int x=0;x<XNumb;x+=XSep){
				DTmpR+=*(srcR+x);
				DTmpG+=*(srcG+x);
			}
			DR+=DTmpR;
			DG+=DTmpG;
		}
		else if(Ln==1){
			DTmpR=0;
			srcR=ImageList[0]->GetY(y)+x1;
			for(int x=0;x<XNumb;x+=XSep){
				DTmpR+=*(srcR+x);
			}
			DR+=DTmpR;
		}
		N+=(XNumb+XSep-1)/XSep;
	}
	if(N!=0){
		DR/=N;
		DG/=N;
		DB/=N;
	}
	return qRgb((int)DR,(int)DG,(int)DB);
}

