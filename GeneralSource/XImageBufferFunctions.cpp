/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XImageBufferFunctions.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "XImageBufferFunctions.h"
#include "XMainSchemeMemory.h"
#include "swap.h"
#define	_USE_MATH_DEFINES
#include<math.h>
#include<memory.h>

void	TransColorToMono(ImageBuffer *ColorBuff[3] ,ImageBuffer *Dest)
{
	int	XLen=Dest->GetWidth();
	int	YLen=Dest->GetHeight();

	for(int i=0;i<3;i++){
		if(XLen>ColorBuff[i]->GetWidth()){
			XLen=ColorBuff[i]->GetWidth();
		}
		if(YLen>ColorBuff[i]->GetHeight()){
			YLen=ColorBuff[i]->GetHeight();
		}
	}
	for(int y=0;y<YLen;y++){
		BYTE	*d	=Dest->GetY(y);
		BYTE	*s0	=ColorBuff[0]->GetY(y);
		BYTE	*s1	=ColorBuff[1]->GetY(y);
		BYTE	*s2	=ColorBuff[2]->GetY(y);
		for(int x=0;x<XLen;x++){
			*d=sqrt((*s0**s0+*s1**s1+*s2**s2)/3.0);
			d++;
			s0++;
			s1++;
			s2++;
		}
	}
}

inline	BYTE	Gem(int a1,int a2,int a3,int a4)
{
	//int	MaxD=max(max(a1,a2),max(a3,a4));
	//int	MinD=min(min(a1,a2),min(a3,a4));
	//return (BYTE)((a1+a2+a3+a4-MaxD-MinD)/2);
	if(a1<a2){
		swap(a1,a2);
	}
	if(a1<a3){
		swap(a1,a3);
		swap(a2,a3);
	}
	else if(a2<a3){
		swap(a2,a3);
	}
	if(a1<a4){
		return (BYTE)a1;
	}
	else if(a2<a4){
		return (BYTE)a4;
	}
	else{
		return (BYTE)a2;
	}
}
bool	ShrinkImage(ImageBuffer &IBuff,double Rate)
{
	if(Rate>1.0){
		return false;
	}

	double	Z=1.0/Rate;
	int	SrcW=IBuff.GetWidth();
	int	SrcH=IBuff.GetHeight();
	int	DestW=SrcW*Rate;
	int	DestH=SrcH*Rate;
	//#pragma omp parallel                             
	//{                                                
		#pragma omp for
		for(int y=0;y<DestH;y++){
			int	SrcY=y*Z;
			if(SrcY==(SrcH-1)){
				BYTE	*s=IBuff.GetY(SrcY);
				BYTE	*d=IBuff.GetY(y);
				double	SrcX=0;
				for(int x=0;x<DestW;x++,SrcX+=Z){
					d[x]=s[(int)SrcX];
				}
			}
			else{
				BYTE	*s0=IBuff.GetY(SrcY+1);
				BYTE	*s1=IBuff.GetY(SrcY);
				BYTE	*d=IBuff.GetY(y);
				double	SrcX=0;
				for(int x=0;x<DestW;x++,SrcX+=Z){
					int	Sx=(int)SrcX;
					if(Sx==(SrcW-1)){
						d[x]=s1[Sx];
					}
					else{
						d[x]=Gem(s0[Sx+1],s0[Sx],s1[Sx+1],s1[Sx]);

					}
				}
			}
		}
	//}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<DestH;y++){
			BYTE	*d=IBuff.GetY(y);
			for(int x=DestW;x<SrcW;x++){
				d[x]=0;
			}
		}
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=DestH;y<SrcH;y++){
			BYTE	*d=IBuff.GetY(y);
			memset(d,0,SrcW);
		}
	}

	return true;
}
