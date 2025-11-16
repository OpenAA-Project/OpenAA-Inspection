/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilterItemLineEmphasize.cpp
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


AreaFilterThresholdVerticalEmphasize::AreaFilterThresholdVerticalEmphasize(AreaFilterItemVerticalEmphasize *parent)
:AlgorithmThreshold(parent)
{
}

void	AreaFilterThresholdVerticalEmphasize::CopyFrom(const AlgorithmThreshold &src)
{

}
bool	AreaFilterThresholdVerticalEmphasize::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);

	return(true);
}
bool	AreaFilterThresholdVerticalEmphasize::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);

	return(true);
}
AreaFilterItemVerticalEmphasize::AreaFilterItemVerticalEmphasize(void)
{
}
AreaFilterItemVerticalEmphasize::~AreaFilterItemVerticalEmphasize(void)
{
}
AlgorithmItemPLI	&AreaFilterItemVerticalEmphasize::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}

bool    AreaFilterItemVerticalEmphasize::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    AreaFilterItemVerticalEmphasize::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	return true;
}

ExeResult	AreaFilterItemVerticalEmphasize::ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	AreaDot=10;
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
			int	DAvr=0;
			for(int yi=-AreaDot;yi<=AreaDot;yi++){
				if((y+yi)<0 || YLen<=(y+yi))
					continue;
				BYTE	*s=GetTargetBuff().GetY(y+yi);
				DAvr+=s[x];
				N++;
			}
			DAvr/=N;				
			TmpBuff[KNumb++]=DAvr;
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

	delete	[]TmpBuff;
	return _ER_true;
}
