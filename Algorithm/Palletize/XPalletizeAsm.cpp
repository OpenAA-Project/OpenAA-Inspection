/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XPalletizeAsm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "XCounterResource.h"
#include "XPalletize.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XInterpolation.h"
#include "XImageProcess.h"
#include "XCrossObj.h"


#ifdef _MSC_VER
#define	InlineAsmMode
#endif


double	MatchingLineV::Match(ImageBuffer *TBuff,int dx,int dy)
{
	int	TargetPosX=PosX+dx;
	int	TargetPosY=PosY+dy;
	ImageBuffer *D=TBuff;

	if(0<=TargetPosY && (TargetPosY+LineLen)<D->GetHeight()
	&& 0<=TargetPosX &&  TargetPosX			<D->GetWidth()
	&& 0<=PosY && (PosY+LineLen)<D->GetHeight()
	&& 0<=PosX &&  PosX			<D->GetWidth()
	&& LineLen>0){
		int	B =0;
		unsigned	int	BB=0;
		unsigned	int	AB=0;
		BYTE	W[32];
		for(int n=0;n<LineLen;n++){
			W[n]=D->GetYWithoutDepended(TargetPosY+n)[TargetPosX];
		}
#if	defined(InlineAsmMode)
		BYTE	*s=Data;
		__asm{
			pxor	xmm0,xmm0
			mov		rax,s
			movq	xmm1,QWORD ptr [rax]
			//mov		ebx,s
			movq	xmm2,QWORD ptr W

			PUNPCKLBW	xmm1,xmm0
			PUNPCKLBW	xmm2,xmm0

			MOVDQU	xmm3,xmm1
			PMADDWD xmm3,xmm2	//AB

			MOVDQU	xmm1,xmm2
			PMADDWD xmm1,xmm1	//BB

			PHADDD	xmm1,xmm3
			PHADDW	xmm2,xmm0	//B

			PHADDD	xmm1,xmm1	//
			PHADDW	xmm2,xmm0	//B

			PEXTRD	AB,xmm1,1
			PHADDW	xmm2,xmm0	//B
			PEXTRD	BB,xmm1,0

			PEXTRD	B,xmm2,0
		}
#else
		BYTE	*d=W;
		BYTE	*s=Data;
		for(int n=0;n<LineLen;n++,s++,d++){
			BYTE	b=*d;
			B +=b;
			BB+=b*b;
			AB+=(*s)*b;
		}

#endif

		double	AvrD=((double)B)*RLineLen;

		double	BBSS=BB-LineLen*AvrD*AvrD;
		double	M=AASS*BBSS;
		if(M<=0){
			return 0;
		}
		double	Rt;
		if(AASS>=BBSS)
			Rt=sqrt(BBSS/AASS);
		else
			Rt=sqrt(AASS/BBSS);
		M=sqrt(M);
		double	K=AB-LineLen*AvrS*AvrD;
		return Rt*K/M;
	}
	return 0;
}


double	MatchingLineH::Match(ImageBuffer *TBuff,int dx,int dy)
{
	int	TargetPosX=PosX+dx;
	int	TargetPosY=PosY+dy;
	ImageBuffer *D=TBuff;

	if(0<=TargetPosY &&  TargetPosY			<D->GetHeight()
	&& 0<=TargetPosX && (TargetPosX+LineLen)<D->GetWidth()
	&& 0<=PosY &&  PosY			<D->GetHeight()
	&& 0<=PosX && (PosX+LineLen)<D->GetWidth()
	&& LineLen>0){

		int	B =0;
		unsigned	int	BB=0;
		unsigned	int	AB=0;
		BYTE	*d=&D->GetYWithoutDepended(TargetPosY)[TargetPosX];
		BYTE	*s=Data;

#if	defined(InlineAsmMode)
		__asm{
			pxor	xmm0,xmm0
			mov		rax,s
			movq	xmm1,QWORD ptr [rax]
			mov		rbx,d
			movq	xmm2,QWORD ptr [rbx]

			PUNPCKLBW	xmm1,xmm0
			PUNPCKLBW	xmm2,xmm0

			MOVDQU	xmm3,xmm1
			PMADDWD xmm3,xmm2	//AB

			MOVDQU	xmm1,xmm2
			PMADDWD xmm1,xmm1	//BB

			PHADDD	xmm1,xmm3
			PHADDW	xmm2,xmm0	//B

			PHADDD	xmm1,xmm1	//
			PHADDW	xmm2,xmm0	//B

			PEXTRD	AB,xmm1,1
			PHADDW	xmm2,xmm0	//B
			PEXTRD	BB,xmm1,0

			PEXTRD	B,xmm2,0
		}
#else
		for(int n=0;n<LineLen;n++,d++,s++){
			BYTE	b=*d;
			B +=b;
			BB+=b*b;
			AB+=(*s)*b;
		}
#endif
		double	AvrD=((double)B)*RLineLen;

		double	BBSS=BB-LineLen*AvrD*AvrD;
		double	M=AASS*BBSS;
		if(M<=0){
			return 0;
		}
		double	Rt;
		if(AASS>=BBSS)
			Rt=sqrt(BBSS/AASS);
		else
			Rt=sqrt(AASS/BBSS);
		M=sqrt(M);
		double	K=AB-LineLen*AvrS*AvrD;
		return Rt*K/M;
	}
	return 0;
}
