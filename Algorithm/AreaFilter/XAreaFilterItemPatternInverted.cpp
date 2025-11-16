/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilterThresholdPatternInverted.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include "XAreaFilter.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMaskingFromGeneral.h"
#include "XAreaFilterPacket.h"
#include "XDynamicMaskingPICommon.h"
#include "swap.h"

#define _USE_MATH_DEFINES
#include "math.h"
#include <omp.h>


AreaFilterThresholdPatternInverted::AreaFilterThresholdPatternInverted(AreaFilterItemPatternInverted *parent)
:AlgorithmThreshold(parent)
{
}

void	AreaFilterThresholdPatternInverted::CopyFrom(const AlgorithmThreshold &src)
{

}
bool	AreaFilterThresholdPatternInverted::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);

	return(true);
}
bool	AreaFilterThresholdPatternInverted::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);

	return(true);
}
AreaFilterItemPatternInverted::AreaFilterItemPatternInverted(void)
{
}
AreaFilterItemPatternInverted::~AreaFilterItemPatternInverted(void)
{
}
AlgorithmItemPLI	&AreaFilterItemPatternInverted::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}

bool    AreaFilterItemPatternInverted::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    AreaFilterItemPatternInverted::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	return true;
}

static	int	DEmpDimFunc(const void *a ,const void *b)
{
	if(*((BYTE *)a)>*((BYTE *)b))
		return 1;
	if(*((BYTE *)a)<*((BYTE *)b))
		return -1;
	return 0;
}

ExeResult	AreaFilterItemPatternInverted::ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	AreaDot=6;
	int	YLen=GetMaxLines();
	int	XLen=GetMaxLines();

	int	Len=GetArea().GetFLineLen();
	BYTE	*TmpBuff=new BYTE[GetArea().GetPatternByte()];

	int	KNumb=0;
	for(int i=0;i<Len;i++){
		int	y	=GetArea().GetFLineAbsY(i);
		int	x1	=GetArea().GetFLineLeftX(i);
		int	x2	=GetArea().GetFLineRightX(i);
		for(int x=x1;x<x2;x++){
			int	N	=0;
			BYTE	DEmpDim[1000];
			for(int yi=-AreaDot;yi<=AreaDot;yi+=2){
				if((y+yi)<0 || YLen<=(y+yi))
					continue;
				BYTE	*s=GetTargetBuff().GetY(y+yi);
				for(int xi=-AreaDot;xi<=AreaDot;xi+=2){
					if((x+xi)<0 || XLen<=(x+xi))
						continue;
					DEmpDim[N]=s[x+xi];
					N++;
				}
			}
			QSort(DEmpDim,N,sizeof(DEmpDim[0]),DEmpDimFunc);
			int	D=0;
			int	k=0;
			for(int i=N/3;i<2*N/3;i++){
				D+=DEmpDim[i];
				k++;
			}
			if(k>0){
				D/=k;
			}
			else{
				D=GetTargetBuff().GetY(y)[x];
			}
				
			TmpBuff[KNumb++]=D;
		}
	}
	KNumb=0;
	double	Avr=0;
	for(int i=0;i<Len;i++){
		int	y	=GetArea().GetFLineAbsY(i);
		int	x1	=GetArea().GetFLineLeftX(i);
		int	x2	=GetArea().GetFLineRightX(i);
		BYTE	*s=GetTargetBuff().GetY(y);
		for(int x=x1;x<x2;x++){
			Avr+=TmpBuff[KNumb];
			s[x]=TmpBuff[KNumb];
			KNumb++;
		}
	}

	/*
	Avr/=KNumb;
	for(int i=0;i<Len;i++){
		int	y	=GetArea().GetFLineAbsY(i);
		int	x1	=GetArea().GetFLineLeftX(i);
		int	x2	=GetArea().GetFLineRightX(i);
		BYTE	*s=GetTargetBuff().GetY(y);
		for(int x=x1;x<x2;x++){
			int	d=(s[x]-Avr)*10+Avr;
			if(d<0)	d=0;
			if(d>255)	d=255;
			s[x]=d;
			KNumb++;
		}
	}
	*/

	delete	[]TmpBuff;
	return _ER_true;
}