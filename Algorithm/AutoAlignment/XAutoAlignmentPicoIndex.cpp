/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAutoAlignmentPicoIndex.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AutoAlignmentResource.h"
#include "XAutoAlignment.h"
#include "XDoubleClass.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include "XAutoMaskingPI.h"
#include "XAnyData.h"
#include "XGeneralFunc.h"
#include <omp.h>
#include "XStatisticPacket.h"
#include "XPointer.h"
#include "XFlexArea.h"
#define _USE_MATH_DEFINES
#include "math.h"
//#include <sse2mmx.h>

//=========================================================================================


AutoAlignmentInPico::CalcedIndexData::CalcedIndexData(void)
{
	XYIndex			=NULL;
	XYIndexCount	=0;
	MasterData		=NULL;
}
AutoAlignmentInPico::CalcedIndexData::~CalcedIndexData(void)
{
	if(XYIndex!=NULL){
		delete	[]XYIndex;
		XYIndex=NULL;
	}
	if(MasterData!=NULL){
		delete	[]MasterData;
		MasterData=NULL;
	}
}

int	XYIndexFunc(const void *a ,const void *b)
{
	AutoAlignmentInPico::CalcedIndexData::XYStruct	*ha=(AutoAlignmentInPico::CalcedIndexData::XYStruct *)a;
	AutoAlignmentInPico::CalcedIndexData::XYStruct	*hb=(AutoAlignmentInPico::CalcedIndexData::XYStruct *)b;

	if(ha->Y<hb->Y)
		return -1;
	if(ha->Y>hb->Y)
		return 1;

	if(ha->X<hb->X)
		return -1;
	if(ha->X>hb->X)
		return 1;
	return 0;
}

void AutoAlignmentInPico::CalcedIndexData::Initial(FlexArea &TransArea
												,ImageBuffer &Buff
												,int MinTransDot)
{
	if(XYIndex!=NULL){
		delete	[]XYIndex;
		XYIndex=NULL;
	}
	XYIndexCount=0;

	int64	N=TransArea.GetPatternByte();
	if(N<MinTransDot*2){
		return;
	}
	struct XYStruct	*MBuff=new struct XYStruct[N];
	int	MIndex=0;
	int	Len=TransArea.GetFLineLen();
	for(int i=0;i<Len;i++){
		int	X=TransArea.GetFLineLeftX(i);
		int	Y=TransArea.GetFLineAbsY(i);
		int	Numb=TransArea.GetFLineNumb(i);
		for(int n=0;n<Numb;n++){
			MBuff[MIndex].X=X+n;
			MBuff[MIndex].Y=Y;
			MIndex++;
		}
	}

	XYIndex=new struct XYStruct[MinTransDot];
	XYIndexCount	=0;

	srand(100);
	for(;;){
		int	V=0;
		for(int d=0;d<8;d++){
			V*=10;
			int	h=(int)(10*rand()/RAND_MAX);
			V+=h;
		}

		int	m=V%MIndex;
		if(MBuff[m].X>=0 && MBuff[m].Y>=0){
			XYIndex[XYIndexCount]=MBuff[m];
			MBuff[m].X=-1;
			MBuff[m].Y=-1;
			XYIndexCount++;
			if(XYIndexCount>=MinTransDot){
				break;
			}
		}
	}

	delete	[]MBuff;

	QSort(XYIndex,XYIndexCount,sizeof(XYIndex[0]),XYIndexFunc);

	MasterAddA=0;
	MasterAddA2=0;
	for(int i=0;i<XYIndexCount;i++){
		int	d=*(Buff.GetY(XYIndex[i].Y)+XYIndex[i].X);
		MasterAddA+=d;
		MasterAddA2+=d*d;
	}
	MinX=99999999;
	MinY=99999999;
	MaxX=-99999999;
	MaxY=-99999999;
	for(int i=0;i<XYIndexCount;i++){
		if(XYIndex[i].X<MinX){
			MinX=XYIndex[i].X;
		}
		if(XYIndex[i].Y<MinY){
			MinY=XYIndex[i].Y;
		}
		if(XYIndex[i].X>MaxX){
			MaxX=XYIndex[i].X;
		}
		if(XYIndex[i].Y>MaxY){
			MaxY=XYIndex[i].Y;
		}
	}
	if(MasterData!=NULL){
		delete	[]MasterData;
		MasterData=NULL;
	}
	MasterData=new BYTE[XYIndexCount];
	for(int i=0;i<XYIndexCount;i++){
		MasterData[i]=*(Buff.GetY(XYIndex[i].Y)+XYIndex[i].X);
	}
}

double	AutoAlignmentInPico::CalcedIndexData::CoefCalc(int dx ,int dy
													   ,ImageBuffer &MasterBuff 
													   ,ImageBuffer &TargetBuff)
{
	if(XYIndexCount==0){
		return -100.0;
	}
	int		TargetAddA	=0;
	int		TargetAddA2	=0;
	int		AddAB		=0;
	int		DotPerLine	=MasterBuff.GetWidth();
	int		MaxLines	=MasterBuff.GetHeight();
	if((MinX+dx)<0 || DotPerLine<=(MaxX+dx)	|| (MinY+dy)<0 || MaxLines  <=(MaxY+dy)){
		return -100.0;
	}

	for(int i=0;i<XYIndexCount;i++){
		int	dM=MasterData[i];
		int	dT=*(TargetBuff.GetY(XYIndex[i].Y+dy)+XYIndex[i].X+dx);

		TargetAddA	+=dT;
		TargetAddA2 +=dT*dT;
		AddAB		+=dM*dT;
	}
	double	AvrS=((double)MasterAddA)/(double)XYIndexCount;
	double	AvrD=((double)TargetAddA)/(double)XYIndexCount;
	double	M=(((double)MasterAddA2)-AvrS*AvrS*XYIndexCount)*(((double)TargetAddA2)-AvrD*AvrD*XYIndexCount);
	if(M>0){
		double	R=(((double)AddAB)-AvrS*AvrD*XYIndexCount)/sqrt(M);
		return R;
	}
	return 0.0;
}


//=========================================================================================
