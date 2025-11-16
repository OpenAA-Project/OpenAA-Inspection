/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XBitImageProcessor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XBitImageProcessor.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "swap.h"
#include <omp.h>

void	PickupBitmapWithAverage(BYTE **BmpImage , int XByte ,int YLen
								,ImageBuffer &SrcImage
								,int BlockWidth ,int BlockHeight
								,int RelThresholdL ,int RelThresholdH
								,int EnsmallSize ,int EnlargeSize
								,int Sep)
{
	int	XImageLen=SrcImage.GetWidth();
	int	YImageLen=SrcImage.GetHeight();

	int	XMinLen=min(XImageLen,XByte*8);
	int	YMinLen=min(YImageLen,YLen);

	int	YNumb=(YMinLen+BlockHeight-1)/BlockHeight;
	//int	XNumb=(XMinLen+BlockWidth -1)/BlockWidth ;

	if(RelThresholdL>RelThresholdH)
		swap(RelThresholdL,RelThresholdH);

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int ky=0;ky<YNumb;ky++){
			int	y1=ky*BlockHeight;
			int	y2=y1+BlockHeight;
			if(y2>YMinLen)
				y2=YMinLen;
			for(int x1=0;x1<XMinLen;x1+=BlockWidth){
				int	x2=x1+BlockWidth;
				double	Dn=0;
				int	N=0;
				for(int y=y1;y<y2;y+=Sep){
					BYTE	*s=SrcImage.GetY(y);
					int	D=0;
					for(int x=x1;x<x2;x+=Sep){
						D+=*(s+x);
						N++;
					}
					Dn+=D;
				}
				if(N!=0){
					double	Avr=Dn/N;
					int	LLevel=Avr+RelThresholdL;
					int	HLevel=Avr+RelThresholdH;

					for(int y=y1;y<y2;y++){
						BYTE	*s=SrcImage.GetY(y);
						BYTE	*d=BmpImage[y];
						for(int x=x1;x<x2;x++){
							if(LLevel<=*(s+x) && *(s+x)<=HLevel){
								d[x>>3] |= 0x80>>(x&7);
							}
						}
					}
				}
			}
		}
	}
	if(EnsmallSize!=0 || EnlargeSize!=0){
		BYTE	**tmp=MakeMatrixBuff(XByte ,YLen);
		for(int i=0;i<EnsmallSize;i++){
			ThinArea(BmpImage
					,tmp
					,XByte ,YLen);
		}
		for(int i=0;i<(EnsmallSize+EnlargeSize);i++){
			FatArea(BmpImage
					,tmp
					,XByte ,YLen);
		}
		DeleteMatrixBuff(tmp,YLen);
	}
}
void	PickupBitmap(FlexArea &Area
					 ,BYTE **BmpImage , int XByte ,int YLen
					,ImageBuffer &SrcImage
					,int AbsThresholdL ,int AbsThresholdH)
{
	int	XImageLen=SrcImage.GetWidth();
	int	YImageLen=SrcImage.GetHeight();

	int	XMinLen=min(XImageLen,XByte*8);
	int	YMinLen=min(YImageLen,YLen);

	if(AbsThresholdL>AbsThresholdH)
		swap(AbsThresholdL,AbsThresholdH);

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YMinLen;y++){
			BYTE	*s=SrcImage.GetY(y);
			BYTE	*d=BmpImage[y];
			for(int x=0;x<XMinLen;x++){
				if(AbsThresholdL<=*(s+x) && *(s+x)<=AbsThresholdH){
					d[x>>3] |= 0x80>>(x&7);
				}
			}
		}
	}
}

void	PickupBitmap(BYTE **BmpImage , int XByte ,int YLen
					,ImageBuffer &SrcImage
					,int AbsThresholdL ,int AbsThresholdH
					,int EnsmallSize ,int EnlargeSize)
{
	int	XImageLen=SrcImage.GetWidth();
	int	YImageLen=SrcImage.GetHeight();

	int	XMinLen=min(XImageLen,XByte*8);
	int	YMinLen=min(YImageLen,YLen);

	if(AbsThresholdL>AbsThresholdH)
		swap(AbsThresholdL,AbsThresholdH);

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YMinLen;y++){
			BYTE	*s=SrcImage.GetY(y);
			BYTE	*d=BmpImage[y];
			for(int x=0;x<XMinLen;x++){
				if(AbsThresholdL<=*(s+x) && *(s+x)<=AbsThresholdH){
					d[x>>3] |= 0x80>>(x&7);
				}
			}
		}
	}
	if(EnsmallSize!=0 || EnlargeSize!=0){
		BYTE	**tmp=MakeMatrixBuff(XByte ,YLen);
		for(int i=0;i<EnsmallSize;i++){
			ThinArea(BmpImage
					,tmp
					,XByte ,YLen);
		}
		for(int i=0;i<(EnsmallSize+EnlargeSize);i++){
			FatArea(BmpImage
					,tmp
					,XByte ,YLen);
		}
		DeleteMatrixBuff(tmp,YLen);
	}
}


void	PickupBitmap(FlexArea &Area,int dx ,int dy
					,BYTE **BmpImage , int XByte ,int YLen
					,ImageBuffer &SrcImage
					,int AbsThresholdL ,int AbsThresholdH
					,int EnsmallSize ,int EnlargeSize)
{
	BYTE	**tmp=MakeMatrixBuff(XByte ,YLen);
	PickupBitmapWithTmp(Area,dx ,dy
					,BmpImage , XByte ,YLen
					,SrcImage
					,AbsThresholdL ,AbsThresholdH
					,EnsmallSize ,EnlargeSize
					,tmp);
	DeleteMatrixBuff(tmp,YLen);
}

void	PickupBitmapWithTmp(FlexArea &Area,int dx ,int dy
					,BYTE **BmpImage , int XByte ,int YLen
					,ImageBuffer &SrcImage
					,int AbsThresholdL ,int AbsThresholdH
					,int EnsmallSize ,int EnlargeSize
					,BYTE	**tmp)
{
	int	XImageLen=SrcImage.GetWidth();
	int	YImageLen=SrcImage.GetHeight();

	//int	XMin=Area.GetMinX();
	//int	YMin=Area.GetMinY();
	int	XMax=min(XImageLen,XByte*8);
	int	YMax=min(YImageLen,YLen);
	XMax=min(XMax,Area.GetMaxX());
	YMax=min(YMax,Area.GetMaxY());

	if(AbsThresholdL>AbsThresholdH){
		swap(AbsThresholdL,AbsThresholdH);
	}

	int	Numb=Area.GetFLineLen();
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int i=0;i<Numb;i++){
		    int x1=Area.GetFLineLeftX(i)+dx;
			int x2=Area.GetFLineRightX(i)+dx;
			int y =Area.GetFLineAbsY(i)+dy;
			if(0<=y && y<YMax){
				BYTE	*s=SrcImage.GetY(y);
				BYTE	*d=BmpImage[y];
				x1=max(x1,0);
				x2=min(x2,XMax);
				for(int x=x1;x<x2;x++){
					if(AbsThresholdL<=*(s+x) && *(s+x)<=AbsThresholdH){
						d[x>>3] |= 0x80>>(x&7);
					}
				}
			}
		}
	}
	if(EnsmallSize!=0 || EnlargeSize!=0){
		FlexArea	CArea;
		CArea=Area;
		CArea.MoveToNoClip(dx,dy);
		for(int i=0;i<EnsmallSize;i++){
			CArea.ThinAreaPartial(BmpImage
								,tmp
								,XByte ,YLen);
		}
		for(int i=0;i<(EnsmallSize+EnlargeSize);i++){
			CArea.FatAreaPartial(i, BmpImage
								,tmp
								,XByte ,YLen);
		}
	}
}
void	PickupBitmapWithTmpMulti(FlexArea &Area ,int dx ,int dy
					,BYTE **BmpImage , int XByte ,int YLen
					,ImageBuffer *SrcImage[] ,int ImageNumb
					,int AbsThresholdL[] ,int AbsThresholdH[]
					,int EnsmallSize ,int EnlargeSize
					,BYTE	**tmp)
{
	if(ImageNumb==0)
		return;

	int	XImageLen=SrcImage[0]->GetWidth();
	int	YImageLen=SrcImage[0]->GetHeight();

	//int	XMin=Area.GetMinX();
	//int	YMin=Area.GetMinY();
	int	XMax=min(XImageLen,XByte*8);
	int	YMax=min(YImageLen,YLen);
	XMax=min(XMax,Area.GetMaxX());
	YMax=min(YMax,Area.GetMaxY());

	for(int k=0;k<ImageNumb;k++){
		if(AbsThresholdL[k]>AbsThresholdH[k]){
			swap(AbsThresholdL[k],AbsThresholdH[k]);
		}
	}

	int	Numb=Area.GetFLineLen();
	#pragma omp parallel                             
	{                                                
		#pragma omp for
	    for(int i=0;i<Numb;i++){
		    int x1=Area.GetFLineLeftX(i)+dx;
			int x2=Area.GetFLineRightX(i)+dx;
			int y =Area.GetFLineAbsY(i)+dy;
			if(0<=y && y<YMax){
				BYTE	*s[100];
				for(int k=0;k<ImageNumb;k++){
					s[k]=SrcImage[k]->GetY(y);
				}
				BYTE	*d=BmpImage[y];
				x1=max(x1,0);
				x2=min(x2,XMax);
				for(int x=x1;x<x2;x++){
					for(int k=0;k<ImageNumb;k++){
						int	Col=*(s[k]+x);
						if(Col<AbsThresholdL[k] || AbsThresholdH[k]<Col){
							goto	ColNext;
						}
					}
					d[x>>3] |= 0x80>>(x&7);
					ColNext:;
				}
			}
		}
	}
	if(EnsmallSize!=0 || EnlargeSize!=0){
		FlexArea	CArea;
		CArea=Area;
		CArea.MoveToNoClip(dx,dy);
		for(int i=0;i<EnsmallSize;i++){
			CArea.ThinAreaPartial(BmpImage
								,tmp
								,XByte ,YLen);
		}
		for(int i=0;i<(EnsmallSize+EnlargeSize);i++){
			CArea.FatAreaPartial(i, BmpImage
								,tmp
								,XByte ,YLen);
		}
	}
}


void	DrawBitRectangle(BYTE **BmpImage , int XByte ,int YLen
						 ,int x1, int y1, int x2, int y2)
{
	if(x1<0)
		x1=0;
	if(y1<0)
		y1=0;
	if(x2>=XByte*8)
		x2=XByte*8-1;
	if(y2>=YLen)
		y2=YLen-1;
		
	int	NLen=y2-y1+1;

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int n=0;n<NLen;n++){
			int	y=y1+n;
			BYTE	*d=BmpImage[y];
			for(int x=x1;x<=x2;x++){
				d[x>>3] |= 0x80>>(x&7);
			}
		}
	}
}
void    CopyBlocyBitBuff(BYTE **dst			,int dstXLen ,int dstYLen
						,const BYTE **src	,int srcXLen ,int srcYLen
						,int OffsetX ,int OffsetY)
{
	for(int y=0;y<srcYLen;y++){
		int	Y=y+OffsetY;
		if(Y<0){
			continue;
		}
		if(Y>=dstYLen){
			break;
		}
		const BYTE	*s=src[y];
		BYTE	*d=dst[Y];
		for(int x=0;x<srcXLen;x++){
			int	X=x+OffsetX;
			if(X<0){
				continue;
			}
			if(X>=dstXLen){
				break;
			}
			if(GetBmpBitOnY(s,x)==0){
				SetBmpBitOnY0(d,X);
			}
			else{
				SetBmpBitOnY1(d,X);
			}
		}
	}
}

void	ClearBitInRect(BYTE **BitMapDim , int XByte ,int YLen
						 ,int x1, int y1, int x2, int y2)
{
	x1=Clipping(x1,0,XByte*8);
	x2=Clipping(x2,0,XByte*8);
	y1=Clipping(y1,0,YLen);
	y2=Clipping(y2,0,YLen);

	for(int y=y1;y<y2;y++){
		BYTE	*d=BitMapDim[y];
		for(int x=x1;x<x2;x++){
			SetBmpBitOnY0(d,x);
		}
	}
}