/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRingL1\XEulerRingL1Search.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XEulerRingL1.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XEulerRingL1Library.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XDisplayBitImage.h"
#include "swap.h"

EulerRingL1Searcher::EulerRingL1Searcher(void)
{
	R	=0;
	Vy1=Vy2=0;
	Hx1=Hx2=0;
	Skip	=2;
	A=AA	=0.0;
	VNumb	=0;
	HNumb	=0;
	VData	=NULL;
	HData	=NULL;

	MDimHole	=NULL;
	MDimRing	=NULL;
	MDotSecondNumb=0;
	SA=SAA		=0;
}
EulerRingL1Searcher::~EulerRingL1Searcher(void)
{
	R	=0;
	Vy1=Vy2=0;
	Hx1=Hx2=0;
	Skip	=2;
	A=AA	=0.0;
	VNumb	=0;
	HNumb	=0;
	if(VData!=NULL)
		delete	[]VData;
	VData	=NULL;
	if(HData!=NULL)
		delete	[]HData;
	HData	=NULL;

	if(MDimHole!=NULL)
		delete	[]MDimHole;
	MDimHole	=NULL;

	if(MDimRing!=NULL)
		delete	[]MDimRing;
	MDimRing	=NULL;

	MDotSecondNumb=0;
	SA=SAA		=0;
}

void	EulerRingL1Searcher::ExecuteInitialAfterEdit(int radius
													,ExecuteInitialAfterEditInfo &EInfo)
{
	R=radius;
	int	RingLen=10;
	if(R<4){
		Skip=1;
		RingLen=2;
	}
	if(R<20){
		Skip=2;
		RingLen=6;
	}
	else{
		Skip=3;
		RingLen=10;
	}
	Vy1=-R-RingLen;
	Vy2= R+RingLen;
	Hx1=-R-RingLen;
	Hx2= R+RingLen;
	VNumb=0;
	HNumb=0;
	for(int y=Vy1;y<=Vy2;y+=Skip,VNumb++);
	for(int x=Hx1;x<=Hx2;x+=Skip,HNumb++);

	if(VData!=NULL)
		delete	[]VData;
	VData = new BYTE[VNumb];

	if(HData!=NULL)
		delete	[]HData;
	HData = new BYTE[HNumb];

	int	n=0;
	for(int y=Vy1;y<=Vy2 && n<VNumb;y+=Skip,n++){
		if(y<-R || R<y)
			VData[n]=0xFF;
		else
			VData[n]=0;
	}
	n=0;
	for(int x=Hx1;x<=Hx2 && n<HNumb;x+=Skip,n++){
		if(x<-R || R<x)
			HData[n]=0xFF;
		else
			HData[n]=0;
	}
	A=0;
	AA=0;
	for(int i=0;i<VNumb;i++){
		A +=VData[i];
		AA+=VData[i]*VData[i];
	}
	for(int i=0;i<HNumb;i++){
		A +=HData[i];
		AA+=HData[i]*HData[i];
	}

	int	NumbInside=0;
	int	NumbOutside=0;
	for(int y=Vy1;y<=Vy2;y++){
		for(int x=Hx1;x<=Hx2;x++){
			double	D=hypot(x,y);
			if(D<R)
				NumbInside++;
			else if(D<(R+RingLen))
				NumbOutside++;
		}
	}
	MDotSecondNumb	=min(NumbInside,NumbOutside);
	if(MDotSecondNumb>100)
		MDotSecondNumb=100;
	int	SkipInside =NumbInside /MDotSecondNumb;
	int	SkipOutside=NumbOutside/MDotSecondNumb;
	if(MDimHole!=NULL)
		delete	[]MDimHole;
	MDimHole	=new struct	MatchingDot[MDotSecondNumb];

	if(MDimRing!=NULL)
		delete	[]MDimRing;
	MDimRing	=new struct	MatchingDot[MDotSecondNumb];

	int	Ni=0;
	int	No=0;
	for(int y=Vy1;y<=Vy2;y++){
		for(int x=Hx1;x<=Hx2;x++){
			double	D=hypot(x,y);
			if(D<R){
				NumbInside++;
				if((NumbInside%SkipInside)==0){
					if(Ni<MDotSecondNumb){
						MDimHole[Ni].x=x;
						MDimHole[Ni].y=y;
						Ni++;
					}
				}
			}
			else if(D<(R+RingLen)){
				NumbOutside++;
				if((NumbOutside%SkipOutside)==0){
					if(No<MDotSecondNumb){
						MDimRing[No].x=x;
						MDimRing[No].y=y;
						No++;
					}
				}
			}
		}
	}
	SA =255*MDotSecondNumb;
	SAA=255*255*MDotSecondNumb;
}
	
double	EulerRingL1Searcher::MatchFirst(EulerRingL1InLayer *Parent ,ImageBuffer &IBuff ,int dx ,int dy)
{
	if(Hx1+dx<0 || Parent->GetDotPerLine()<=Hx2+dx)
		return 0.0;
	if(Hx2+dx<0 || Parent->GetDotPerLine()<=Hx1+dx)
		return 0.0;
	if(Vy1+dy<0 || Parent->GetMaxLines()<=Vy2+dy)
		return 0.0;
	if(Vy2+dy<0 || Parent->GetMaxLines()<=Vy1+dy)
		return 0.0;

	int	n=0;
	BYTE	CBuff[10000];
	for(int y=Vy1;y<=Vy2;y+=Skip,n++){
		CBuff[n]=IBuff.GetY(y+dy)[dx];
	}
	BYTE	LowD =255;
	BYTE	HighD=0;
	double	B=0;
	double	BB=0;
	double	AB=0;

	unsigned int	tB=0;
	unsigned int	tBB=0;
	unsigned int	tAB=0;
	for(int i=0;i<VNumb;i++){
		BYTE	c=CBuff[i];
		BYTE	h=VData[i];
		if(c<LowD)
			LowD=c;
		if(c>HighD)
			HighD=c;
		tB +=c;
		tBB+=c*c;
		tAB+=h*c;
	}
	n=0;
	BYTE	*s=IBuff.GetY(dy);
	for(int x=Hx1;x<=Hx2;x+=Skip,n++){
		BYTE	c=s[x+dx];
		BYTE	h=HData[n];
		if(c<LowD)
			LowD=c;
		if(c>HighD)
			HighD=c;
		tB +=c;
		tBB+=c*c;
		tAB+=h*c;
	}
	B =tB;
	BB=tBB;
	AB=tAB;
	
	int	L=HNumb+VNumb;
	double	DivL=1.0/(double)L;
	double	AvrS=((double)A)*DivL;
	double	AvrD=((double)B)*DivL;

	double	K=AB-L*AvrS*AvrD;

	double	M=(AA-L*AvrS*AvrS)*(BB-L*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	Cff=K/M;
	if(Cff<0)
		return 0.0;
	return (HighD-LowD)*Cff;
}

double	EulerRingL1Searcher::MatchSecond(EulerRingL1InLayer *Parent ,ImageBuffer &IBuff ,int dx ,int dy)
{
	BYTE	HPix[1000];
	BYTE	RPix[1000];
	for(int i=0;i<MDotSecondNumb;i++){
		HPix[i]=IBuff.GetY(MDimHole[i].y+dy)[MDimHole[i].x+dx];
	}
	for(int i=0;i<MDotSecondNumb;i++){
		RPix[i]=IBuff.GetY(MDimRing[i].y+dy)[MDimRing[i].x+dx];
	}
	BYTE	LowD =255;
	BYTE	HighD=0;
	int32	B=0;
	int32	BB=0;
	int32	AB=0;
	int32	HoleB=0;
	int32	RingB=0;
	for(int i=0;i<MDotSecondNumb;i++){
		BYTE	c=HPix[i];
		if(c<LowD)
			LowD=c;
		HoleB+=c;
		B +=c;
		BB+=c*c;
		//AB+=c*0;
	}
	for(int i=0;i<MDotSecondNumb;i++){
		BYTE	c=RPix[i];
		if(c>HighD)
			HighD=c;
		RingB+=c;
		B +=c;
		BB+=c*c;
		AB+=c*255;
	}
	if(HoleB<2)
		HoleB=2;
	double	Ratio=((double)RingB)/((double)HoleB);
	int	L=2*MDotSecondNumb;
	double	DivL=1.0/(double)L;
	double	AvrS=((double)SA)*DivL;
	double	AvrD=((double)B)*DivL;

	double	K=((double)AB)-L*AvrS*AvrD;

	double	M=(SAA-L*AvrS*AvrS)*(((double)BB)-L*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	Cff=K/M;
	if(Cff<0)
		return 0.0;
	return Ratio*(HighD-LowD)*Cff;
}
