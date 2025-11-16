/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XOutlineInspect.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "OutlineInspectionResource.h"

#define	_USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XOutlineInspect.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XParamGlobal.h"
#include "XPSpline.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDisplayBitImage.h"
#include <omp.h>



double	OutlineItem::MatchingCalcFull(ImageBuffer *MasterBuff ,ImageBuffer *TargetBuff
									,int mx,int my)
{
	double	TargetAdd	=0;
	double	TargetAdd2	=0;
	double	MTMul		=0;

	int	N=MatchingArea.GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y	=MatchingArea.GetFLineAbsY(i);
		int	x1	=MatchingArea.GetFLineLeftX(i);
		int	x2	=MatchingArea.GetFLineRightX(i);
		BYTE	*s=MasterBuff->GetY(Y);
		BYTE	*d=TargetBuff->GetY(Y+my);
		int	iAdd=0;
		int	iAdd2=0;
		int	iAddSD=0;

		int	n=x2-x1;
	//	#pragma omp parallel for reduction(+:iAdd,iAdd2,iAddSD)
		for(int ix=0;ix<n;ix++){
			int	x=x1+ix;
			int	b=d[x+mx];
			iAdd	+=b;
			iAdd2	+=b*b;
			iAddSD	+=s[x]*b;
		}
		TargetAdd	+=iAdd;
		TargetAdd2	+=iAdd2;
		MTMul		+=iAddSD;
	}
	double	AvrS=MasterAdd/MatchingDotCount;
	double	AvrD=TargetAdd/MatchingDotCount;
	double	M=(MasterAdd2-AvrS*AvrS*MatchingDotCount)*(TargetAdd2-AvrD*AvrD*MatchingDotCount);
	if(M>0){
		double	R=(MTMul-AvrS*AvrD*MatchingDotCount)/sqrt(M);
		return R;
	}
	return 0.0;

}
