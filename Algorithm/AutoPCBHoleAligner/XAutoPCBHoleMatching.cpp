/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAutoPCBHoleMatching.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "XAutoPCBHoleAlignerResource.h"
#include "XAutoPCBHoleAligner.h"
#include "XDoubleClass.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include "XGeneralFunc.h"
#include <omp.h>
#include "XPointer.h"
#define _USE_MATH_DEFINES
#include "math.h"



int	HoleTestDataFunc(const void *a ,const void *b)
{
	if(((struct MatchingHoleClass::HoleIndexStruct *)a)->OffsetY<((struct MatchingHoleClass::HoleIndexStruct *)b)->OffsetY){
		return 1;
	}
	if(((struct MatchingHoleClass::HoleIndexStruct *)a)->OffsetY>((struct MatchingHoleClass::HoleIndexStruct *)b)->OffsetY){
		return -1;
	}
	if(((struct MatchingHoleClass::HoleIndexStruct *)a)->OffsetX<((struct MatchingHoleClass::HoleIndexStruct *)b)->OffsetX){
		return 1;
	}
	if(((struct MatchingHoleClass::HoleIndexStruct *)a)->OffsetX>((struct MatchingHoleClass::HoleIndexStruct *)b)->OffsetX){
		return -1;
	}
	return 0;
}

void	MatchingHoleClass::Initial(int holeRadius)
{
	HoleRadius=holeRadius;
	HoleTestData[ 0].Value=20;
	HoleTestData[ 1].Value=40;
	HoleTestData[ 2].Value=40;
	HoleTestData[ 3].Value=40;
	HoleTestData[ 4].Value=40;
	HoleTestData[ 5].Value=70;
	HoleTestData[ 6].Value=70;
	HoleTestData[ 7].Value=70;
	HoleTestData[ 8].Value=70;
	HoleTestData[ 9].Value=70;
	HoleTestData[10].Value=70;
	HoleTestData[11].Value=70;
	HoleTestData[12].Value=70;
	HoleTestData[13].Value=70;
	HoleTestData[14].Value=70;
	HoleTestData[15].Value=70;

	HoleTestData[ 0].OffsetX=0;
	HoleTestData[ 0].OffsetY=0;
	HoleTestData[ 1].OffsetX=(2*HoleRadius/3+1)/2;
	HoleTestData[ 1].OffsetY=0;
	HoleTestData[ 2].OffsetX=-(2*HoleRadius/3+1)/2;
	HoleTestData[ 2].OffsetY=0;
	HoleTestData[ 3].OffsetX=0;
	HoleTestData[ 3].OffsetY=(2*HoleRadius/3+1)/2;
	HoleTestData[ 4].OffsetX=0;
	HoleTestData[ 4].OffsetY=-(2*HoleRadius/3+1)/2;

	double	Ds=2.0*M_PI/11.0;
	for(int i=0;i<11;i++){
		double	SinS=sin(Ds*i);
		double	CosS=cos(Ds*i);
		int	R=HoleRadius+3;
		HoleTestData[i+5].OffsetX=R*CosS;
		HoleTestData[i+5].OffsetY=R*SinS;
	}
	QSort(HoleTestData,5,sizeof(HoleTestData[0]),HoleTestDataFunc);
	QSort(&HoleTestData[5],11,sizeof(HoleTestData[0]),HoleTestDataFunc);

	AddA=0;
	AddA2=0;
	int	MinX=0;
	int	MinY=0;
	for(int i=0;i<16;i++){
		AddA +=HoleTestData[i].Value;
		AddA2+=HoleTestData[i].Value*HoleTestData[i].Value;
		if(MinX>HoleTestData[i].OffsetX){
			MinX=HoleTestData[i].OffsetX;
		}
		if(MinY>HoleTestData[i].OffsetY){
			MinY=HoleTestData[i].OffsetY;
		}
	}
	int	MaxX=0;
	int	MaxY=0;
	for(int i=0;i<16;i++){
		HoleTestData[i].OffsetX-=MinX;
		HoleTestData[i].OffsetY-=MinY;
		if(MaxX<HoleTestData[i].OffsetX){
			MaxX=HoleTestData[i].OffsetX;
		}
		if(MaxY<HoleTestData[i].OffsetY){
			MaxY=HoleTestData[i].OffsetY;
		}
	}
	XCount=GetDotPerLine(0)-MaxX;
	YCount=GetMaxLines(0)-MaxY;
	Cx=MaxX/2;
	Cy=MaxY/2;
}

int	MatchingHoleClass::ExecuteMatch(ImageBuffer *Image[],BYTE **Mask 
						,struct PointClass PointDim[],int MaxPointDim
						,double MatchingRate1, double MatchingRate2)
{
	int	PointIndex=0;

	#pragma omp parallel for
	for(int y=0;y<YCount;y++){
		int	Py=y+Cy;
		BYTE	*m=Mask[Py];
		if(PointIndex<MaxPointDim){
			for(int x=0;x<XCount;x++){
				int	Px=x+Cx;
				if(GetBmpBitOnY(m,Px)!=0){
					double	VarR;
					double	VarG;
					double	VarB;
					double	cG=MatchOne(x ,y ,Image[1],VarG);
					if(cG>MatchingRate1 && VarG<MatchingRate2){
						double	cR=MatchOne(x ,y ,Image[0],VarR);
						double	cB=MatchOne(x ,y ,Image[2],VarB);
						if((cR*cG*cB)>MatchingRate1 && VarR<MatchingRate2 && VarG<MatchingRate2 && VarB<MatchingRate2){
							int	Hindex;
							#pragma omp critical
							{
								if(PointIndex<MaxPointDim){
									PointDim[PointIndex].X=Px;
									PointDim[PointIndex].Y=Py;
									PointIndex++;
								}
							}
							BreakMask(Mask,Px,Py);
						}
					}
				}
			}
		}
	}
	#pragma omp parallel for
	for(int i=0;i<PointIndex;i++){
		int	mx,my;
		SearchFittablePosition(Image,PointDim[i].X,PointDim[i].Y
								,mx,my);
		PointDim[i].X=mx;
		PointDim[i].Y=my;
	}
	return PointIndex;
}

double	MatchingHoleClass::MatchOne(int X ,int Y ,ImageBuffer *IBuff ,double	&Var)
{
	int	AddB=0;
	int	AddB2=0;
	int	AddAB=0;
	for(int i=5;i<16;i++){
		BYTE	c=*(IBuff->GetY(Y+HoleTestData[i].OffsetY)+HoleTestData[i].OffsetX);
		AddB	+=c;
		AddB2	+=c*c;
		AddAB	+=c*HoleTestData[i].Value;
	}
	int	Count=11;
	Var=((double)(AddB2-AddB*AddB*Count))/((double)Count);

	for(int i=0;i<5;i++){
		BYTE	c=*(IBuff->GetY(Y+HoleTestData[i].OffsetY)+HoleTestData[i].OffsetX);
		AddB	+=c;
		AddB2	+=c*c;
		AddAB	+=c*HoleTestData[i].Value;
	}
	Count=16;
	int64	M=((int64)(AddB2-AddB*AddB*Count))*((int64)(AddA2-AddA*AddA*Count));
	if(M==0){
		return 0;
	}
	int64	S=AddAB-AddA*AddB*Count;
	return ((double)S)/sqrt((double)M);
}

void	MatchingHoleClass::BreakMask(BYTE **Mask,int Px,int Py)
{
	for(int y=-HoleRadius;y<=HoleRadius;y++){
		BYTE	*m=Mask[Py+y];
		for(int x=-HoleRadius;x<=HoleRadius;x++){
			SetBmpBitOnY0(m,Px+x);
		}
	}
}

void	MatchingHoleClass::SearchFittablePosition(ImageBuffer *Image[]
												,int PosX,int PosY
												,int &mx,int &my)
{
	int	ix=0,iy=0;
	double	MaxD=0;
	for(int sy=-4;sy<=4;sy++){
		for(int sx=-4;sx<=4;sx++){
			double	VarR;
			double	VarG;
			double	VarB;
			double	cR=MatchOne(PosX+sx ,PosY+sy ,Image[0],VarR);
			double	cG=MatchOne(PosX+sx ,PosY+sy ,Image[1],VarG);
			double	cB=MatchOne(PosX+sx ,PosY+sy ,Image[2],VarB);
			double	M=cR*cG*cB;
			if(M>MaxD){
				MaxD=M;
				ix=sx;
				iy=sy;
			}
		}
	}
	mx=ix;
	my=iy;
}
