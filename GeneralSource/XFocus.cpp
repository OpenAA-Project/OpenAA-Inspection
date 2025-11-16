/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XFocus.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XFocus.h"
#include "XPointer.h"
#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XImageProcess.h"
#include "swap.h"

static	int	DDimFunc(const void *a,const void *b)
{
	if(*((BYTE *)a)>*((BYTE *)b))
		return 1;
	if(*((BYTE *)a)<*((BYTE *)b))
		return -1;
	return 0;
}

static	void	GetAddBrightFormBit(ImageBuffer &Img
									,BYTE **TmpBit ,int XLen ,int YLen
									,int MovX ,int MovY
									,double &AvrD, int &AvrN)
//ƒrƒbƒg‚ª‚P‚Ì‰æ‘œ‚Ì‹P“x‚Ì‰ÁŽZ’l‚Æƒhƒbƒg”‚ðŒvŽZ‚·‚é
{
	AvrD=0;
	AvrN=0;
	BYTE	DDim[100000];
	int	N=0;
	for(int y=0;y<YLen;y++){
		BYTE	*s=TmpBit[y];
		BYTE	*d=Img.GetY(MovY+y)+MovX;
		for(int x=0;x<XLen;x++){
			if((s[x>>3]&(0x80>>(x&7)))!=0){
				DDim[N]=d[x];
				N++;
			}
		}
	}
	QSort(DDim,N,sizeof(DDim[0]),DDimFunc);
	for(int i=N/3;i<2*N/3;i++){
		AvrD+=DDim[i];
		AvrN++;
	}
}

static	double	CalcV(double Ex,double Ox,double Ey,double Oy
					  ,double AvrTable[] ,int AvrTableN)
//ƒVƒOƒ‚ƒCƒhŠÖ”‚Æ‚Ì‚QæŒë·˜a‚ðŒvŽZ‚·‚é
{
	double	ret=0;
	for(int x=0;x<AvrTableN;x++){
		double	y=Oy+Ey/(1.0+exp(-Ex*(x-Ox)));
		double	dy=y-AvrTable[x];
		ret+=dy*dy;
	}
	return ret;
}

static	double	CalcV(double H,double L,double X,double A,double G,double C,double S
					  ,double AvrTable[] ,int AvrTableN)
//ƒVƒOƒ‚ƒCƒhŠÖ”‚Æ‚Ì‚QæŒë·˜a‚ðŒvŽZ‚·‚é
{
	double	ret=0;
	for(int x=0;x<AvrTableN;x++){
		double	y=(L-H)/(1+exp(-A*(x-X))) + H +C*exp(-(x-G)*(x-G)/(S*S));
		double	dy=y-AvrTable[x];
		ret+=dy*dy;
	}
	return ret;
}
static	double	CalcV2(double H,double L,double X,double A
					  ,double AvrTable[] ,int AvrTableN)
//ƒVƒOƒ‚ƒCƒhŠÖ”‚Æ‚Ì‚QæŒë·˜a‚ðŒvŽZ‚·‚é
{
	double	ret=0;
	for(int x=0;x<AvrTableN;x++){
		double	y=(L-H)/(1+exp(-A*(x-X))) + H;
		double	dy=y-AvrTable[x];
		ret+=dy*dy;
	}
	return ret;
}

static	int	MakeTableFocusLevel(ImageBuffer &Img , FlexArea &Area
						,int FlowDot
						,double AvrTable[])
{
	int	MinX=Area.GetMinX()-FlowDot-1;
	int	MinY=Area.GetMinY()-FlowDot-1;
	int	MaxX=Area.GetMaxX()+FlowDot+1;
	int	MaxY=Area.GetMaxY()+FlowDot+1;

	MinX=max(MinX,0);
	MinY=max(MinY,0);
	MaxX=min(MaxX,Img.GetWidth());
	MaxY=min(MaxY,Img.GetHeight());

	int		XByte		=(MaxX-MinX+7)>>3;
	int		XLen		=XByte*8;
	int		YLen		=MaxY-MinY+1;
	BYTE	**TmpBit	=MakeMatrixBuff(XByte,YLen);
	BYTE	**TmpBit2	=MakeMatrixBuff(XByte,YLen);
	BYTE	**TmpBit3	=MakeMatrixBuff(XByte,YLen);
	BYTE	**BitOpe	=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear(TmpBit ,0,XByte,YLen);

	int	MovX=FlowDot+1;
	int	MovY=FlowDot+1;

	int n = Area.GetFLineLen();
	Area.MakeBitData(TmpBit,-MinX,-MinY,XByte*8 ,YLen);

	int		AvrTableN=0;

	double	tAvrTable[100];
	int		tAvrTableN=0;

	MatrixBuffCopy(TmpBit2				,XByte ,YLen
                 , (const BYTE **)TmpBit,XByte ,YLen);
	MatrixBuffCopy(TmpBit3				,XByte ,YLen
                 , (const BYTE **)TmpBit,XByte ,YLen);

	for(int i=0;i<FlowDot;i++){
		ThinArea(TmpBit2
				,BitOpe
				,XByte ,YLen);

		MatrixBuffNotAnd(TmpBit,(const BYTE **)TmpBit2 ,XByte ,YLen);
		double	AvrD;
		int		AvrN;
		GetAddBrightFormBit(Img
							,TmpBit ,XLen ,YLen
							,MinX ,MinY
							,AvrD, AvrN);
		if(AvrN==0)
			break;
		tAvrTable[tAvrTableN]=AvrD/AvrN;
		tAvrTableN++;

		MatrixBuffCopy(TmpBit				 ,XByte ,YLen
                     , (const BYTE **)TmpBit2,XByte ,YLen);
	}

	for(int i=0;i<tAvrTableN;i++){
		AvrTable[tAvrTableN-i-1]=tAvrTable[i];
	}
	AvrTableN=tAvrTableN;

	MatrixBuffCopy(TmpBit ,XByte ,YLen
                 , (const BYTE **)TmpBit3,XByte ,YLen);
	MatrixBuffCopy(TmpBit2,XByte ,YLen
                 , (const BYTE **)TmpBit ,XByte ,YLen);
	for(int i=0;i<FlowDot;i++){
		FatArea(TmpBit
				,BitOpe
				,XByte ,YLen);

		MatrixBuffCopy(TmpBit3				,XByte ,YLen
		             , (const BYTE **)TmpBit,XByte ,YLen);
		MatrixBuffNotAnd(TmpBit,(const BYTE **)TmpBit2 ,XByte ,YLen);
		double	AvrD;
		int		AvrN;
		GetAddBrightFormBit(Img
							,TmpBit ,XLen ,YLen
							,MinX ,MinY
							,AvrD, AvrN);
		if(AvrN==0)
			break;
		AvrTable[AvrTableN]=AvrD/AvrN;
		AvrTableN++;

		MatrixBuffCopy(TmpBit					,XByte ,YLen
		             , (const BYTE **)TmpBit3	,XByte ,YLen);
	}

	DeleteMatrixBuff(TmpBit ,YLen);
	DeleteMatrixBuff(TmpBit2,YLen);
	DeleteMatrixBuff(TmpBit3,YLen);
	DeleteMatrixBuff(BitOpe	,YLen);

	return AvrTableN;
}

double	GetFocusLevel(ImageBuffer &Img , FlexArea &Area
					  ,int FlowDot)
{
	double	AvrTable[100];
	int	AvrTableN=MakeTableFocusLevel(Img , Area
						,FlowDot
						,AvrTable);

	double	Ex=0.0,Ox=0.0,Ey=0.0,Oy=0.0;
	double	MinQ=99999999;

	double	MidEy=(AvrTable[AvrTableN-1]+AvrTable[AvrTableN-2])/2.0-(AvrTable[0]+AvrTable[1])/2.0;
	double	MidOy=(AvrTable[0]+AvrTable[1])/2.0;

	for(double ey=MidEy-10;ey<=MidEy+10;ey+=2.0){
		for(double oy=MidOy-25;oy<MidOy+25;oy+=4.0){
			for(double ox=max(0.0,AvrTableN/2.0-2);ox<min(AvrTableN/2.0+3,(double)AvrTableN-1);ox+=1.0){
				for(double ex=0.1;ex<4.0;ex+=0.2){
					double	m=CalcV(ex,ox,ey,oy,AvrTable,AvrTableN);
					if(m<MinQ){
						MinQ=m;
						Ex=ex;
						Ox=ox;
						Ey=ey;
						Oy=oy;
					}
				}
			}
		}
	}
	double	hEx=Ex;
	double	hOx=Ox;
	double	hEy=Ey;
	double	hOy=Oy;

	double	ZEy=1;
	double	ZOy=2;
	double	ZOx=0.5;
	double	ZEx=0.1;
	for(int i=0;i<7;i++){
		double	MinQ=99999999;
		for(double ey=Ey-ZEy;ey<=Ey+ZEy;ey+=2*ZEy){
			for(double oy=Oy-ZOy;oy<=Oy+ZOy;oy+=2*ZOy){
				for(double ox=Ox-ZOx;ox<=Ox+ZOx;ox+=2*ZOx){
					for(double ex=Ex-ZEx;ex<=Ex+ZEx;ex+=2*ZEx){
						double	m=CalcV(ex,ox,ey,oy,AvrTable,AvrTableN);
						if(m<MinQ){
							MinQ=m;
							hEx=ex;
							hOx=ox;
							hEy=ey;
							hOy=oy;
						}
					}
				}
			}
		}
		Ex=hEx;
		Ox=hOx;
		Ey=hEy;
		Oy=hOy;

		ZEy/=2.0;
		ZOy/=2.0;
		ZOx/=2.0;
		ZEx/=2.0;
	}
	return Ex;
}

double	GetFocusLevel2(ImageBuffer &Img , FlexArea &Area
					  ,int FlowDot)
{
	double	AvrTable[100];
	int	AvrTableN=MakeTableFocusLevel(Img , Area
						,FlowDot
						,AvrTable);

	double	H=(AvrTable[0]+AvrTable[1])/2.0;
	double	L=(AvrTable[AvrTableN-1]+AvrTable[AvrTableN-2])/2.0;
	double	X=AvrTableN/2.0;
	double	A=1.0;

	double	dH=5;
	double	dL=5;
	double	dX=0.5;
	double	dA=0.5;

	for(int i=0;i<7;i++){
		double	kH=0.0;
		double	kL=0.0;
		double	kX=0.0;
		double	kA=0.0;

		double eh;
		double el;
		double ex;
		double ea;

		int	rh;
		int	rl;
		int	rx;
		int	ra;

		int	mh;
		int	ml;
		int	mx;
		int	ma;

		double	MinQ=99999999.0;
		for(eh=H-dH,rh=0;rh<=5;eh+=dH/2.0,rh++){
			for(el=L-dL,rl=0;rl<=5;el+=dL/2.0,rl++){
				for(ex=X-dX,rx=0;rx<=5;ex+=dX/2.0,rx++){
					for(ea=A-dA,ra=0;ra<=7;ea+=dA/4.0,ra++){
						double	m=CalcV2(eh,el,ex,ea,AvrTable,AvrTableN);
						if(m<MinQ){
							MinQ=m;
							kH=eh;
							kL=el;
							kX=ex;
							kA=ea;
							mh=rh;
							ml=rl;
							mx=rx;
							ma=ra;
						}
					}
				}
			}
		}
		H=kH;
		L=kL;
		X=kX;
		A=kA;
		if(1<=mh && mh<=5)
			dH/=2.0;
		if(1<=ml && ml<=5)
			dL/=2.0;
		if(1<=mx && mx<=5)
			dX/=2.0;
		if(1<=ma && ma<=7)
			dA/=2.0;
	}

	double	C=AvrTable[AvrTableN/2]-(H+L)/2.0;
	double	S=1.0;
	double	G=X+1;
	double	dC=5;
	double	dG=0.5;
	double	dS=0.5;

	for(int i=0;i<7;i++){
		double	kG=0.0;
		double	kC=0.0;
		double	kS=0.0;

		double eg;
		double ec;
		double es;

		int	rg;
		int	rc;
		int	rs;

		int	mg;
		int	mc;
		int	ms;

		double	MinQ=99999999.0;
		for(eg=G-dG,rg=0;rg<=5;eg+=dG/2.0,rg++){
			for(ec=C-dC,rc=0;rc<=5;ec+=dC/2.0,rc++){
				for(es=S-dS,rs=0;rs<=7;es+=dS/4.0,rs++){
					double	m=CalcV(H,L,X,A,eg,ec,es,AvrTable,AvrTableN);
					if(m<MinQ){
						MinQ=m;
						kG=eg;
						kC=ec;
						kS=es;
						mg=rg;
						mc=rc;
						ms=rs;
					}
				}
			}
		}
		G=kG;
		C=kC;
		S=kS;
		if(1<=mg && mg<=5)
			dG/=2.0;
		if(1<=mc && mc<=5)
			dC/=2.0;
		if(1<=ms && ms<=7)
			dS/=2.0;
	}
	if(S<0.2)

		return -S;
	return S;
}