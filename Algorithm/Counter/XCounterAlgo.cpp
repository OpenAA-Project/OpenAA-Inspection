/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XCounterItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "XCounterResource.h"
#include "XCounter.h"
#include "XMasking.h"
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
#include <omp.h>

//-----------------------------------------------------------------
MatchingLineBase::MatchingLineBase(void)
{
	PosX=PosY=0;
	LineLen=0;
	Data=NULL;
	Layer=0;
	A=AA=0;
	AvrS=0;
}
MatchingLineBase::~MatchingLineBase(void)
{
	if(Data!=NULL){
		delete	[]Data;
	}
	Data=NULL;
	LineLen=0;
}

void	MatchingLineBase::Initial(void)
{
	A=AA=0;
	AASS=0;
	if(LineLen!=0){
		for(int n=0;n<LineLen;n++){
			int	a=Data[n];
			A+=a;
			AA+=a*a;
		}
		AvrS=((double)A)/(double)LineLen;

		AASS=AA-LineLen*AvrS*AvrS;
		RLineLen=1.0/((double)LineLen);
	}
}

bool	MatchingLineV::Set(double cx, double cy ,double Len 
				,ImageBufferListContainer &SourcePattern)
{
	if(cy-Len/2<0 || cx<0){
		return false;
	}
	PosX=cx;
	PosY=cy-Len/2;
	int	layer=0;
	double	MaxD=0;
	for(ImageBufferList *p=SourcePattern.GetFirst();p!=NULL;p=p->GetNext(),layer++){
		double	d=GetVar(*p);
		if(MaxD<d){
			MaxD=d;
			Layer=layer;
		}
	}
	LineLen=Len;
	ImageBufferList *p=SourcePattern[Layer];
	if(PosY+LineLen>=p->GetHeight() || PosX>=p->GetWidth())
		return false;

	if(Data!=NULL){
		delete	[]Data;
	}
	Data=new BYTE[LineLen];
	for(int n=0;n<LineLen;n++){
		int	b=p->GetYWithoutDepended(PosY+n)[PosX];
		Data[n]=b;
	}
	Initial();
	return true;
}
void	MatchingLineV::Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)
{
	Pnt.drawLine((PosX+movx)*ZoomRate ,(PosY+movy)*ZoomRate
			    ,(PosX+movx)*ZoomRate ,(PosY+LineLen+movy)*ZoomRate);
}

double	MatchingLineV::GetVar(ImageBuffer &Buff)
{
	double	B,BB;
	B=BB=0.0;
	if(LineLen!=0){
		for(int n=0;n<LineLen;n++){
			int	b=Buff.GetYWithoutDepended(PosY+n)[PosX];
			B+=b;
			BB+=b*b;
		}
		double	AvrB=((double)B)/(double)LineLen;
		double	D=(BB-LineLen*AvrB*AvrB)/LineLen;
		if(D<0){
			return 0;
		}
		return sqrt(D);
	}
	return 0;
}

bool	MatchingLineH::Set(double cx, double cy ,double Len 
				,ImageBufferListContainer &SourcePattern)
{
	if(cx-Len/2<0 || cy<0){
		return false;
	}
	PosX=cx-Len/2;
	PosY=cy;
	int	layer=0;
	double	MaxD=0;
	for(ImageBufferList *p=SourcePattern.GetFirst();p!=NULL;p=p->GetNext(),layer++){
		double	d=GetVar(*p);
		if(MaxD<d){
			MaxD=d;
			Layer=layer;
		}
	}
	LineLen=Len;
	ImageBufferList *p=SourcePattern[Layer];
	if(PosY>=p->GetHeight() || PosX+LineLen>=p->GetWidth())
		return false;

	if(Data!=NULL){
		delete	[]Data;
	}
	Data=new BYTE[LineLen];
	BYTE	*s=p->GetYWithoutDepended(PosY);
	for(int n=0;n<LineLen;n++){
		int	b=s[PosX+n];
		Data[n]=b;
	}
	Initial();
	return true;
}
void	MatchingLineH::Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)
{
	Pnt.drawLine((PosX+movx)*ZoomRate ,(PosY+movy)*ZoomRate
			    ,(PosX+LineLen+movx)*ZoomRate ,(PosY+movy)*ZoomRate);
}
double	MatchingLineH::GetVar(ImageBuffer &Buff)
{
	double	B,BB;
	B=BB=0.0;
	if(LineLen!=0){
		BYTE	*s=Buff.GetYWithoutDepended(PosY);
		for(int n=0;n<LineLen;n++){
			int	b=s[PosX+n];
			B+=b;
			BB+=b*b;
		}
		double	AvrB=((double)B)/(double)LineLen;
		double	D=(BB-LineLen*AvrB*AvrB)/LineLen;
		if(D<0){
			return 0;
		}
		return sqrt(D);
	}
	return 0;
}

//===============================================================

MatchingSomePoints::MatchingSomePoints(void)
{
	PointCount		=0;
	Data			=NULL;
	PointDim		=NULL;
	PointInsideCount	=0;
	PointInsideDim		=NULL;
	PointInsideCountD	=0;
	PointInsideDimD		=NULL;
	PointOutsideCountD	=0;
	PointOutsideDimD	=NULL;
	Layer		=0;
	A	=0;
	AA	=0;
	AvrS	=0;
	AASS	=0;
	MinX=MinY=MaxX=MaxY=0;
}
MatchingSomePoints::~MatchingSomePoints(void)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
	if(PointDim!=NULL){
		delete	[]PointDim;
		PointDim=NULL;
	}
	if(PointInsideDim!=NULL){
		delete	[]PointInsideDim;
		PointInsideDim=NULL;
	}
	if(PointInsideDimD!=NULL){
		delete	[]PointInsideDimD;
		PointInsideDimD=NULL;
	}
	if(PointOutsideDimD!=NULL){
		delete	[]PointOutsideDimD;
		PointOutsideDimD=NULL;
	}
	PointCount			=0;
	PointInsideCount	=0;
	PointInsideCountD	=0;
	PointOutsideCountD	=0;
	Layer				=0;
	A					=0;
	AA					=0;
	AvrS				=0;
	AASS				=0;
}

void	MatchingSomePoints::Allocate(ImageBufferListContainer &SourcePattern
									,FlexArea &PickedAreaInPattern
									,int FocusLevel
									,int OutMergin)
{
	if(Data!=NULL){
		delete	[]Data;
		Data=NULL;
	}
	if(PointDim!=NULL){
		delete	[]PointDim;
		PointDim=NULL;
	}

	PointCount=18;
	Data=new BYTE[PointCount];
	PointDim=new QPoint[PointCount];

	int	W=SourcePattern[0]->GetWidth();
	int	H=SourcePattern[0]->GetHeight();
	int	n=0;
	for(int	xn=0;xn<3;xn++){
		int	x=W/4*(xn+1);
		int	y1,y2;
		for(y1=2;y1<H-2;y1++){
			if(PickedAreaInPattern.IsInclude(x,y1)==true){
				y1-=OutMergin;
				break;
			}
		}
		for(y2=H-2;y2>2;y2--){
			if(PickedAreaInPattern.IsInclude(x,y2)==true){
				y2+=OutMergin;
				break;
			}
		}
		if(y1<y2 && 0<=y1 && y2<H){
			PointDim[n].setX(x);
			PointDim[n].setY(y1);
			n++;
			PointDim[n].setX(x);
			PointDim[n].setY(y2);
			n++;

			int	y3=-1;
			int	L=(y2-y1)/2;
			int	cy=(y1+y2)/2;
			for(int t=0;t<L;t++){
				for(int px=-3;px<=3;px++){
					for(int py=-3;py<=3;py++){
						if(PickedAreaInPattern.IsInclude(x+px,cy+t+py)==false){
							goto	NextP1;
						}
					}
				}
				y3=cy+t;
				goto	FoundP1;

				NextP1:;
				for(int px=-3;px<=3;px++){
					for(int py=-3;py<=3;py++){
						if(PickedAreaInPattern.IsInclude(x+px,cy-t+py)==false){
							goto	NextP2;
						}
					}
				}
				y3=cy-t;
				goto	FoundP1;
				NextP2:;
			}
		FoundP1:;
			if(y1<y3 && y3<y2){
				PointDim[n].setX(x);
				PointDim[n].setY(y3);
				n++;
			}
		}
	}
			
	for(int	yn=0;yn<3;yn++){
		int	y=H/4*(yn+1);
		if(0<=y && y<H){
			int	x1,x2;
			for(x1=2;x1<W-2;x1++){
				if(PickedAreaInPattern.IsInclude(x1,y)==true){
					x1-=OutMergin;
					break;
				}
			}
			for(x2=W-2;x2>2;x2--){
				if(PickedAreaInPattern.IsInclude(x2,y)==true){
					x2+=OutMergin;
					break;
				}
			}
			if(x1<x2){
				PointDim[n].setX(x1);
				PointDim[n].setY(y);
				n++;
				PointDim[n].setX(x2);
				PointDim[n].setY(y);
				n++;

				int	x3=-1;
				int	L=(x2-x1)/2;
				int	cx=(x1+x2)/2;
				for(int t=0;t<L;t++){
					for(int px=-3;px<=3;px++){
						for(int py=-3;py<=3;py++){
							if(PickedAreaInPattern.IsInclude(cx+t+px,y+py)==false){
								goto	NextQ1;
							}
						}
					}
					x3=cx+t;
					goto	FoundQ1;

					NextQ1:;
					for(int px=-3;px<=3;px++){
						for(int py=-3;py<=3;py++){
							if(PickedAreaInPattern.IsInclude(cx-t+px,y+py)==false){
								goto	NextQ2;
							}
						}
					}
					x3=cx-t;
					goto	FoundQ1;
					NextQ2:;
				}
			FoundQ1:;
				if(x1<x3 && x3<x2){
					PointDim[n].setX(x3);
					PointDim[n].setY(y);
					n++;
				}
			}
		}
	}
	PointCount=n;

	MinX=99999999;
	MinY=99999999;
	MaxX=-99999999;
	MaxY=-99999999;
	AvrS=0;
	A=0;
	AA=0;
	if(PointCount>0){
		RPointCount	=1.0/((double)PointCount);
		for(int i=0;i<PointCount;i++){
			MinX=min(MinX,PointDim[i].x());
			MinY=min(MinY,PointDim[i].y());
			MaxX=max(MaxX,PointDim[i].x());
			MaxY=max(MaxY,PointDim[i].y());
		}
		Layer=0;
		int	N=SourcePattern.GetCount();
		double	MaxD=0;
		for(int	L=0;L<N;L++){
			double	D=GetVar(*SourcePattern[L]);
			if(MaxD<D){
				MaxD=D;
				Layer=L;
			}
		}

		ImageBuffer *D=SourcePattern[Layer];
		BYTE	*s=Data;
		for(int i=0;i<PointCount;i++){
			int	TargetPosX=PointDim[i].x();
			int	TargetPosY=PointDim[i].y();
			BYTE	d=D->GetYWithoutDepended(TargetPosY)[TargetPosX];
			A +=d;
			AA+=d*d;
			*s=d;
			s++;
		}
		AvrS=((double)A)*RPointCount;
		AASS=AA-PointCount*AvrS*AvrS;
	}
	CalcFocusLevel(SourcePattern,PickedAreaInPattern,FocusLevel);

	if(PointInsideDimD!=NULL){
		delete	[]PointInsideDimD;
		PointInsideDimD=NULL;
	}
	PointInsideCountD=30;
	PointInsideDimD=new QPoint[PointInsideCountD];
	n=0;
	for(int	xn=0;xn<5;xn++){
		int	x=W/6*(xn+1);
		int	y1,y2;
		for(y1=2;y1<H-2;y1++){
			if(PickedAreaInPattern.IsInclude(x,y1)==true){
				y1+=OutMergin;
				break;
			}
		}
		for(y2=H-2;y2>2;y2--){
			if(PickedAreaInPattern.IsInclude(x,y2)==true){
				y2-=OutMergin;
				break;
			}
		}
		if(y1<y2){
			//if(PickedAreaInPattern.IsInclude(x,y1)==true){
			//	PointInsideDimD[n].setX(x);
			//	PointInsideDimD[n].setY(y1);
			//	n++;
			//}
			//if(PickedAreaInPattern.IsInclude(x,y2)==true){
			//	PointInsideDimD[n].setX(x);
			//	PointInsideDimD[n].setY(y2);
			//	n++;
			//}

			int	y3=-1;
			int	L=(y2-y1)/2;
			int	cy=(y1+y2)/2;
			for(int t=0;t<L;t++){
				for(int px=-3;px<=3;px++){
					for(int py=-3;py<=3;py++){
						if(PickedAreaInPattern.IsInclude(x+px,cy+t+py)==false){
							goto	NextDP1;
						}
					}
				}
				y3=cy+t;
				goto	FoundDP1;

				NextDP1:;
				for(int px=-3;px<=3;px++){
					for(int py=-3;py<=3;py++){
						if(PickedAreaInPattern.IsInclude(x+px,cy-t+py)==false){
							goto	NextDP2;
						}
					}
				}
				y3=cy-t;
				goto	FoundDP1;
				NextDP2:;
			}
		FoundDP1:;
			if(y1<y3 && y3<y2){
				PointInsideDimD[n].setX(x);
				PointInsideDimD[n].setY(y3);
				n++;
			}
		}
	}
			
	for(int	yn=0;yn<5;yn++){
		int	y=H/6*(yn+1);
		int	x1,x2;
		for(x1=2;x1<W-2;x1++){
			if(PickedAreaInPattern.IsInclude(x1,y)==true){
				x1+=OutMergin;
				break;
			}
		}
		for(x2=W-2;x2>2;x2--){
			if(PickedAreaInPattern.IsInclude(x2,y)==true){
				x2-=OutMergin;
				break;
			}
		}
		if(x1<x2){
			//if(PickedAreaInPattern.IsInclude(x1,y)==true){
			//	PointInsideDimD[n].setX(x1);
			//	PointInsideDimD[n].setY(y);
			//	n++;
			//}
			//if(PickedAreaInPattern.IsInclude(x2,y)==true){
			//	PointInsideDimD[n].setX(x2);
			//	PointInsideDimD[n].setY(y);
			//	n++;
			//}

			int	x3=-1;
			int	L=(x2-x1)/2;
			int	cx=(x1+x2)/2;
			for(int t=0;t<L;t++){
				for(int px=-3;px<=3;px++){
					for(int py=-3;py<=3;py++){
						if(PickedAreaInPattern.IsInclude(cx+t+px,y+py)==false){
							goto	NextDQ1;
						}
					}
				}
				x3=cx+t;
				goto	FoundDQ1;

				NextDQ1:;
				for(int px=-3;px<=3;px++){
					for(int py=-3;py<=3;py++){
						if(PickedAreaInPattern.IsInclude(cx-t+px,y+py)==false){
							goto	NextDQ2;
						}
					}
				}
				x3=cx-t;
				goto	FoundDQ1;
				NextDQ2:;
			}
		FoundDQ1:;
			if(x1<x3 && x3<x2){
				PointInsideDimD[n].setX(x3);
				PointInsideDimD[n].setY(y);
				n++;
			}
		}
	}
	PointInsideCountD=n;

}

void	MatchingSomePoints::CalcFocusLevel(ImageBufferListContainer &SourcePattern
										   ,FlexArea &PickedAreaInPattern,int FocusLevel)
{
	int	W=SourcePattern[0]->GetWidth();
	int	H=SourcePattern[0]->GetHeight();

	if(PointInsideDim!=NULL){
		delete	[]PointInsideDim;
		PointInsideDim=NULL;
	}
	PointInsideCount=18;
	PointInsideDim=new QPoint[PointInsideCount];
	int	n=0;
	for(int	xn=0;xn<3;xn++){
		int	x=W/4*(xn+1);
		int	y1,y2;
		for(y1=2;y1<H-2;y1++){
			if(PickedAreaInPattern.IsInclude(x,y1)==true){
				//y1+=OutMergin;
				break;
			}
		}
		for(y2=H-2;y2>2;y2--){
			if(PickedAreaInPattern.IsInclude(x,y2)==true){
				//y2-=OutMergin;
				break;
			}
		}
		if(FocusLevel<9){
			y1+=FocusLevel*2+2;
			y2-=FocusLevel*2+2;
		}
		if(y1<y2){
			if(FocusLevel==9){
				int	W=(y2-y1)/4;
				if(W>0){
					y1+=W;
					y2-=W;
				}
				else{
					y1+=FocusLevel*2+2;
					y2-=FocusLevel*2+2;
				}
			}
			if(PickedAreaInPattern.IsInclude(x,y1)==true){
				PointInsideDim[n].setX(x);
				PointInsideDim[n].setY(y1);
				n++;
			}
			if(PickedAreaInPattern.IsInclude(x,y2)==true){
				PointInsideDim[n].setX(x);
				PointInsideDim[n].setY(y2);
				n++;
			}
		}
	}
	for(int	yn=0;yn<3;yn++){
		int	y=H/4*(yn+1);
		int	x1,x2;
		for(x1=2;x1<W-2;x1++){
			if(PickedAreaInPattern.IsInclude(x1,y)==true){
				//x1+=OutMergin;
				break;
			}
		}
		for(x2=W-2;x2>2;x2--){
			if(PickedAreaInPattern.IsInclude(x2,y)==true){
				//x2-=OutMergin;
				break;
			}
		}
		if(FocusLevel<9){
			x1+=FocusLevel*2+2;
			x2-=FocusLevel*2+2;
		}
		if(x1<x2){
			if(FocusLevel==9){
				int	W=(x2-x1)/4;
				if(W>0){
					x1+=W;
					x2-=W;
				}
				else{
					x1+=FocusLevel*2+2;
					x2-=FocusLevel*2+2;
				}
			}
			if(PickedAreaInPattern.IsInclude(x1,y)==true){
				PointInsideDim[n].setX(x1);
				PointInsideDim[n].setY(y);
				n++;
			}
			if(PickedAreaInPattern.IsInclude(x2,y)==true){
				PointInsideDim[n].setX(x2);
				PointInsideDim[n].setY(y);
				n++;
			}
		}
	}
	PointInsideCount=n;

	if(PointOutsideDimD!=NULL){
		delete	[]PointOutsideDimD;
		PointOutsideDimD=NULL;
	}
	PointOutsideCountD=30;
	PointOutsideDimD=new QPoint[PointOutsideCountD];
	n=0;
	for(int	xn=0;xn<5;xn++){
		int	x=W/6*(xn+1);
		int	y1,y2;
		for(y1=2;y1<H-2;y1++){
			if(PickedAreaInPattern.IsInclude(x,y1)==true){
				y1-=FocusLevel*2;
				break;
			}
		}
		for(y2=H-2;y2>2;y2--){
			if(PickedAreaInPattern.IsInclude(x,y2)==true){
				y2+=FocusLevel*2;
				break;
			}
		}
		if(y1<y2){
			if(PickedAreaInPattern.IsInclude(x,y1)==false){
				PointOutsideDimD[n].setX(x);
				PointOutsideDimD[n].setY(y1);
				n++;
			}
			if(PickedAreaInPattern.IsInclude(x,y2)==false){
				PointOutsideDimD[n].setX(x);
				PointOutsideDimD[n].setY(y2);
				n++;
			}
		}
	}
	for(int	yn=0;yn<5;yn++){
		int	y=H/6*(yn+1);
		int	x1,x2;
		for(x1=2;x1<W-2;x1++){
			if(PickedAreaInPattern.IsInclude(x1,y)==true){
				x1-=FocusLevel*2;
				break;
			}
		}
		for(x2=W-2;x2>2;x2--){
			if(PickedAreaInPattern.IsInclude(x2,y)==true){
				x2+=FocusLevel*2;
				break;
			}
		}
		if(x1<x2){
			if(PickedAreaInPattern.IsInclude(x1,y)==false){
				PointOutsideDimD[n].setX(x1);
				PointOutsideDimD[n].setY(y);
				n++;
			}
			if(PickedAreaInPattern.IsInclude(x2,y)==false){
				PointOutsideDimD[n].setX(x2);
				PointOutsideDimD[n].setY(y);
				n++;
			}
		}
	}
	PointOutsideCountD=n;
}

void	RotatedMatchingPattern::CalcFocusLevel(void)
{
	CounterBase	*ABase=Parent->tGetParentBase();
	RoughPoints.CalcFocusLevel(SourcePattern
						   ,PickedAreaInPattern,ABase->FocusLevel);
}

bool	RotatedMatchingPattern::GetCrossDetailPoints(int dx,int dy ,BYTE **ExecuteMap ,int XLen ,int YLen)
{
	for(int i=0;i<RoughPoints.PointInsideCountD;i++){
		int	hx=RoughPoints.PointInsideDimD[i].x()+dx;
		int	hy=RoughPoints.PointInsideDimD[i].y()+dy;
		if(0<=hx && hx<XLen && 0<=hy && hy<YLen){
			if(GetBmpBit(ExecuteMap,hx,hy)==0){
				return false;
			}
		}
		else{
			return false;
		}
	}
	CounterBase	*ABase=Parent->tGetParentBase();
	if(ABase->OutsideCalc==true){
		int	OutCount=0;
		for(int i=0;i<RoughPoints.PointOutsideCountD;i++){
			int	hx=RoughPoints.PointOutsideDimD[i].x()+dx;
			int	hy=RoughPoints.PointOutsideDimD[i].y()+dy;
			if(0<=hx && hx<XLen && 0<=hy && hy<YLen){
				if(GetBmpBit(ExecuteMap,hx,hy)==0){
					OutCount++;
				}
			}
		}
		if(OutCount<(RoughPoints.PointOutsideCountD-3))
			return false;
	}
	return true;
}
double	MatchingSomePoints::Match(ImageBuffer *TBuff[],int dx,int dy)
{
	ImageBuffer *D=TBuff[Layer];
	if(0<=(MinY+dy) && (MaxY+dy)<D->GetHeight()
	&& 0<=(MinX+dy) && (MaxX+dx)<D->GetWidth()
	&& PointCount>0){
		int	B =0;
		unsigned	int	BB=0;
		unsigned	int	AB=0;
		BYTE	*s=Data;
		for(int i=0;i<PointCount;i++){
			int	TargetPosX=PointDim[i].x()+dx;
			int	TargetPosY=PointDim[i].y()+dy;
			BYTE	d=D->GetYWithoutDepended(TargetPosY)[TargetPosX];
			B +=d;
			BB+=d*d;
			AB+=d*(*s);
			s++;
		}
		double	AvrD=((double)B)*RPointCount;

		double	M=AASS*(BB-PointCount*AvrD*AvrD);
		if(M<=0){
			return 0;
		}
		M=sqrt(M);
		double	K=AB-PointCount*AvrS*AvrD;
		return K/M;
	}
	return 0;
}

void	MatchingSomePoints::Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)
{
	for(int i=0;i<PointCount;i++){
		int	X=PointDim[i].x();
		int	Y=PointDim[i].y();
		int	Gx=(X+movx)*ZoomRate;
		int	Gy=(Y+movy)*ZoomRate;
		Pnt.drawLine(Gx-10,Gy,Gx+10,Gy);
		Pnt.drawLine(Gx,Gy-10,Gx,Gy+10);
	}
}

double	MatchingSomePoints::GetVar(ImageBuffer &Buff)
{
	if(0<=MinY && MaxY<Buff.GetHeight()
	&& 0<=MinX && MaxX<Buff.GetWidth()
	&& PointCount>0){
		int	B =0;
		unsigned	int	BB=0;
		for(int i=0;i<PointCount;i++){
			int	TargetPosX=PointDim[i].x();
			int	TargetPosY=PointDim[i].y();
			BYTE	d=Buff.GetYWithoutDepended(TargetPosY)[TargetPosX];
			B +=d;
			BB+=d*d;
		}
		double	AvrB=((double)B)/(double)PointCount;
		double	D=(BB-PointCount*AvrB*AvrB)/PointCount;
		if(D<0){
			return 0;
		}
		return sqrt(D);
	}
	return 0;
}

//===============================================================

RotatedMatchingPattern::RotatedMatchingPattern(CounterItem *p)
{	
	Angle			=0;
	Parent			=p;
	ShiftXYDim		=NULL;
	ShiftXYDimCount	=0;
}

RotatedMatchingPattern::~RotatedMatchingPattern(void)
{
	if(ShiftXYDim!=NULL){
		delete	[]ShiftXYDim;
		ShiftXYDim=NULL;
	}
}

static	int	SepLineLen=12;
static	int	MatachingLinesDivN=3;

void	RotatedMatchingPattern::MakeInitial(CounterItem *Item
											,FlexArea &OriginalPart
											,FlexArea &OriginalPickedAreaInPattern
											,ImageBufferListContainer &OriginalImage)
{
	int	L=ceil(hypot(OriginalPart.GetWidth(),OriginalPart.GetHeight()));
	CounterBase	*ABase=Parent->tGetParentBase();

	int	CenterX,CenterY;
	OriginalPart.GetCenter(CenterX,CenterY);
	CenterX-=OriginalPart.GetMinX();
	CenterY-=OriginalPart.GetMinY();

	PickedAreaInPattern=OriginalPickedAreaInPattern;
	PickedAreaInPattern.MoveToNoClip(L/2-CenterX,L/2-CenterY);
	PickedAreaInPattern.Rotate(Angle*180.0/M_PI ,L/2 ,L/2);

	SourcePattern.RemoveAll();
	for(ImageBufferList *s=OriginalImage.GetFirst();s!=NULL;s=s->GetNext()){
		//int	w=s->GetWidth();
		//int	h=s->GetHeight();
		ImageBufferList	*d=new ImageBufferList(0,L,L);
		d->Memset(0);
		d->PartialCopy(*s,-(L/2-CenterX),-(L/2-CenterY));
		d->RotateImage(L/2 ,L/2 ,-Angle);
		SourcePattern.AppendList(d);
	}
	XYClassCluster XY;
	PickedAreaInPattern.MakeOutlineDot(XY);

	PickedAreaInPatternShrinked	=PickedAreaInPattern;
	PickedAreaInPatternShrinked.ThinAreaN(4);
	PickedAreaInPatternFatMask	=PickedAreaInPattern;
	PickedAreaInPatternFatMask.FatAreaN(6);
	PickedAreaInPatternFatMask=PickedAreaInPatternFatMask.MakeSkipYArea(ABase->SkipFlat);
	PickedAreaInPatternFat		=PickedAreaInPattern;
	PickedAreaInPatternFat.FatAreaN(3);	//6);
	//PickedAreaInPatternFat.ThinAreaN(4);

	FlexArea	tEdgeFlexArea;
	tEdgeFlexArea=PickedAreaInPatternFat;
	//tEdgeFlexArea.FatAreaN(10);
	tEdgeFlexArea-=PickedAreaInPatternShrinked;
	double	MaxV=0;
	EdgeLayer=0;
	int	layer=0;
	for(ImageBufferList *a=SourcePattern.GetFirst();a!=NULL;a=a->GetNext(),layer++){
		FlexAreaImageListCoeff	L;
		L.Set(tEdgeFlexArea,*a);
		L.MakeSum();
		double	d=L.GetV();
		if(d>MaxV){
			MaxV=d;
			EdgeArea	=L;
			EdgeLayer	=layer;
		}
	}

	int	OffX=PickedAreaInPattern.GetMinX();
	int	OffY=PickedAreaInPattern.GetMinY();
	PickedAreaInPatternXLen=PickedAreaInPattern.GetWidth();
	PickedAreaInPatternYLen=PickedAreaInPattern.GetHeight();

	ExeOffsetX=PickedAreaInPattern.GetMinX();
	ExeOffsetY=PickedAreaInPattern.GetMinY();

	WNumb=ABase->CountIndexLine;
	HNumb=ABase->CountIndexLine;
	int	dW=PickedAreaInPatternXLen/WNumb;
	int	dH=PickedAreaInPatternYLen/HNumb;

	if(dW<20){
		WNumb=1;
		dW=PickedAreaInPatternXLen/WNumb;
		if(dW<20){
			WNumb=1;
			dW=PickedAreaInPatternXLen;
		}
	}
	if(dH<20){
		HNumb=1;
		dH=PickedAreaInPatternYLen/HNumb;
		if(dH<20){
			HNumb=1;
			dH=PickedAreaInPatternYLen;
		}
	}
	int	SepLen=SepLineLen/2;
	double	SepLen2=SepLen/2.0;
	if(SepLen2<1.5)
		SepLen2=1.5;
	const	CounterThreshold	*RThr=Item->GetThresholdR(NULL);
	int		LineLen=RThr->LineLength;

	for(int xn=0;xn<WNumb;xn++){
		int	ex1=OffX+ xn*dW;
		int	ex2=OffX+(xn+1)*dW;
		for(int yn=0;yn<HNumb;yn++){
			int	ey1=OffY+ yn*dH;
			int	ey2=OffY+(yn+1)*dH;
			MatachingLines[xn][yn].RemoveAll();
			for(XYClassArea *a=XY.GetFirst();a!=NULL;a=a->GetNext()){
				int	PointNumb=a->NPListPack<XYClass>::GetCount();
				int	n=0;
				XYClass *LastC=NULL;
				for(XYClass *c=a->NPListPack<XYClass>::GetFirst();n<PointNumb;c=a->NPListPack<XYClass>::GetRingNext(c),n++){
					if((LastC==NULL || hypot(*c,*LastC)>SepLineLen)
					&& ex1<=c->x && c->x<=ex2 & ey1<=c->y && c->y<=ey2){
						int	k=0;
						XYClass *c1;
						for(c1=a->NPListPack<XYClass>::GetRingNext(c);k<PointNumb;c1=a->NPListPack<XYClass>::GetRingNext(c1),k++){
							if(hypot(*c,*c1)>SepLen2){
								break;
							}
						}
						k=0;
						XYClass *c2;
						for(c2=a->NPListPack<XYClass>::GetRingPrev(c);k<PointNumb;c2=a->NPListPack<XYClass>::GetRingPrev(c2),k++){
							if(hypot(*c,*c2)>SepLen2){
								break;
							}
						}
						double x[100] ,y[100];
						k=0;
						if(c1!=NULL && c2!=NULL){
							for(XYClass *cm=c2;k<PointNumb;cm=a->NPListPack<XYClass>::GetRingNext(cm),k++){
								x[k]=cm->x;
								y[k]=cm->y;
								if(cm==c1){
									k++;
									break;
								}
							}
						}
						double A,B,C;
						if(MakeInterpolatedLine(x ,y ,k ,A,B,C)==true){
							double RetMaxSeparation;
							double RetVarietySeparatedDistanceFromLine;
							double RetStartPointOnLine[2];
							double RetEndPointOnLine[2];
							AnalizeInterpolatedLine(x ,y ,k ,A,B,C
									,RetMaxSeparation
									,RetVarietySeparatedDistanceFromLine
									,RetStartPointOnLine
									,RetEndPointOnLine);
							if(RetMaxSeparation<2){
								double	cx=(RetStartPointOnLine[0]+RetEndPointOnLine[0])/2;
								double	cy=(RetStartPointOnLine[1]+RetEndPointOnLine[1])/2;
								double	Hx=RetEndPointOnLine[0]-RetStartPointOnLine[0];
								double	Hy=RetEndPointOnLine[1]-RetStartPointOnLine[1];
								double	G=hypot(Hx,Hy);
								if(G>0){
									double	vx=-Hy/G;
									double	vy= Hx/G;
									if(fabs(vx)>fabs(vy)){
										MatchingLineH	*e=new MatchingLineH();
										if(e->Set(cx, cy ,LineLen ,SourcePattern)==true){
											MatachingLines[xn][yn].AppendList(e);
										}
									}
									else{
										MatchingLineV	*e=new MatchingLineV();
										if(e->Set(cx, cy ,LineLen ,SourcePattern)==true){
											MatachingLines[xn][yn].AppendList(e);
										}
									}
									LastC=c;
								}
							}
						}
					}
				}
			}
		}
	}
	for(int w=0;w<WNumb;w++){
		for(int h=0;h<HNumb;h++){
			if(MatachingLines[w][h].GetCount()>=6){
				int	DivN=MatachingLines[w][h].GetCount()/MatachingLinesDivN;
				int	n=0;
				for(MatchingLineBase *f=MatachingLines[w][h].GetFirst();f!=NULL;n++){
					MatchingLineBase *NextF=f->GetNext();
					if((n%DivN)!=0){
						MatachingLines[w][h].RemoveList(f);
						delete	f;
					}
					f=NextF;
				}
			}
		}
	}
	SinglePointer=NULL;
	double	MaxSingleD=0;
	int		SingleW=0;
	int		SingleH=0;
	for(int w=0;w<WNumb;w++){
		for(int h=0;h<HNumb;h++){
			for(MatchingLineBase *f=MatachingLines[w][h].GetFirst();f!=NULL;f=f->GetNext()){
				MatchingLineH	*H=dynamic_cast<MatchingLineH *>(f);
				if(H!=NULL){
					ImageBuffer	*B=SourcePattern[f->GetLayer()];
					double	D=H->GetVar(*B);
					if(MaxSingleD<D){
						MaxSingleD=D;
						SingleW=w;
						SingleH=h;
						SinglePointer=f;
					}
				}
			}
		}
	}
	if(SinglePointer==NULL){
		for(int w=0;w<WNumb;w++){
			for(int h=0;h<HNumb;h++){
				for(MatchingLineBase *f=MatachingLines[w][h].GetFirst();f!=NULL;f=f->GetNext()){
					ImageBuffer	*B=SourcePattern[f->GetLayer()];
					double	D=f->GetVar(*B);
					if(MaxSingleD<D){
						MaxSingleD=D;
						SingleW=w;
						SingleH=h;
						SinglePointer=f;
					}
				}
			}
		}
	}

	SecondPointer=NULL;
	double	MaxSecondD=0;
	for(int w=0;w<WNumb;w++){
		for(int h=0;h<HNumb;h++){
			for(MatchingLineBase *f=MatachingLines[w][h].GetFirst();f!=NULL;f=f->GetNext()){
				MatchingLineV	*V=dynamic_cast<MatchingLineV *>(f);
				if(V!=NULL){
					ImageBuffer	*B=SourcePattern[f->GetLayer()];
					double	D=f->GetVar(*B);
					if(MaxSecondD<D){
						MaxSecondD=D;
						SecondPointer=f;
					}
				}
			}
		}
	}
	if(SecondPointer==NULL){
		for(int w=0;w<WNumb;w++){
			for(int h=0;h<HNumb;h++){
				if(w!=SingleW && h!=SingleH){
					for(MatchingLineBase *f=MatachingLines[w][h].GetFirst();f!=NULL;f=f->GetNext()){
						ImageBuffer	*B=SourcePattern[f->GetLayer()];
						double	D=f->GetVar(*B);
						if(MaxSecondD<D){
							MaxSecondD=D;
							SecondPointer=f;
						}
					}
				}
			}
		}
	}

	if(ShiftXYDim!=NULL){
		delete	[]ShiftXYDim;
	}
	ShiftXYDim=new struct ShiftXY[MaxShiftXYDimCount];
	ShiftXYDimCount=0;

	RoughPoints.Allocate(SourcePattern,PickedAreaInPattern
						 ,ABase->FocusLevel
						 ,Parent->GetThresholdR()->OutMergin);
}

static	int	FuncRTable(const void *a ,const void *b)
{
	double	*pa=(double *)a;
	double	*pb=(double *)b;
	if(*pa<*pb)
		return 1;
	if(*pa>*pb)
		return -1;
	return 0;
}

double	RotatedMatchingPattern::Match(ImageBuffer *TBuff[]
									  ,int dx,int dy
									  ,int SearchDot
									  ,MatchingMethod Method)
{
	int	WH=SearchDot;	//3;
	int	WH2=(WH+1)/2;
	double	RTable[9];
	int		TableNumb=0;
	for(int w=0;w<WNumb;w++){
		for(int h=0;h<HNumb;h++){
			double	D=1.0;
			int		Numb=0;
			for(MatchingLineBase *f=MatachingLines[w][h].GetFirst();f!=NULL;f=f->GetNext()){
				double	MaxD=0;
				int		MaxDx=0;
				int		MaxDy=0;
				
				if(f->GetLineClass()==1){
					for(int hdy=-WH;hdy<=WH;hdy+=2){
						double	d=f->Match(TBuff,dx,dy+hdy);
						if(MaxD<d){
							MaxD=d;
							MaxDy=hdy;
						}
					}
					for(int hdy=-WH2;hdy<=WH2;hdy++){
						int	ky=MaxDy+hdy;
						if(-WH<=ky && ky<=WH){
							double	d=f->Match(TBuff,dx,ky+dy);
							if(MaxD<d){
								MaxD=d;
							}
						}
					}
				}
				else
				if(f->GetLineClass()==2){
					for(int hdx=-WH;hdx<=WH;hdx+=2){
						double	d=f->Match(TBuff,dx+hdx,dy);
						if(MaxD<d){
							MaxD=d;
							MaxDx=hdx;
						}
					}
					for(int hdx=-WH2;hdx<=WH2;hdx++){
						int	kx=MaxDx+hdx;
						if(-WH<=kx && kx<=WH){
							double	d=f->Match(TBuff,kx+dx,dy);
							if(MaxD<d){
								MaxD=d;
							}
						}
					}
				}
				else{
					for(int hdy=-WH;hdy<=WH;hdy+=2){
						for(int hdx=-WH;hdx<=WH;hdx+=2){
							double	d=f->Match(TBuff,dx+hdx,dy+hdy);
							if(MaxD<d){
								MaxD=d;
								MaxDx=hdx;
								MaxDy=hdy;
							}
						}
					}
					for(int hdy=-WH2;hdy<=WH2;hdy++){
						for(int hdx=-WH2;hdx<=WH2;hdx++){
							int	kx=MaxDx+hdx;
							int	ky=MaxDy+hdy;
							if(-WH<=kx && kx<=WH && -WH<=ky && ky<=WH){
								double	d=f->Match(TBuff,kx+dx,ky+dy);
								if(MaxD<d){
									MaxD=d;
								}
							}
						}
					}
				}

				if(MaxD>0){
					D*=MaxD;
					Numb++;
				}
				else{
					D*=0.01;
					Numb++;
				}
			}
			if(Numb!=0){
				RTable[TableNumb]=pow(D,1.0/Numb);
				TableNumb++;
			}
		}
	}
	if(TableNumb==0){
		return 0;
	}
	//qsort(RTable,TableNumb,sizeof(RTable[0]),FuncRTable);
	//double	Avr=0;
	//for(int i=0;i<TableNumb;i++){
	//	Avr+=RTable[i];
	//}
	//return Avr/TableNumb;

	if(Method==_AveragePower){
		double	Avr=1.0;
		for(int i=0;i<TableNumb;i++){
			Avr*=RTable[i];
		}
		Avr=pow(Avr,1.0/TableNumb);
		return Avr;
	}
	if(Method==_MinRate){
		double	Avr=RTable[0];
		for(int i=1;i<TableNumb;i++){
			Avr=min(Avr,RTable[i]);
		}
		return Avr;
	}
	return 0;
}

double	RotatedMatchingPattern::MatchByEdge(ImageBuffer *TBuff[] 
											,int &dx,int &dy
											,int SearchDot)
{
	double	MaxD=0;
	int		MaxTx=0;
	int		MaxTy=0;
	for(int ty=-SearchDot;ty<=SearchDot;ty++){
		for(int tx=-SearchDot;tx<=SearchDot;tx++){
			double	d=EdgeArea.CalcCoeff(dx+tx,dy+ty,*TBuff[EdgeLayer]);
			if(d>=MaxD){
				MaxD=d;
				MaxTx=tx;
				MaxTy=ty;
			}
		}
	}
	dx+=MaxTx;
	dy+=MaxTy;
	return MaxD;
}

double	RotatedMatchingPattern::MatchRough(ImageBuffer *TBuff[]
										,int dx,int dy
										,int Sep)
{
	double	RTable[9];
	int		TableNumb=0;
	for(int w=0;w<WNumb;w++){
		for(int h=0;h<HNumb;h++){
			double	D=1.0;
			int		Numb=0;
			//int	tCount=MatachingLines[w][h].GetCount();
			int	n=0;
			for(MatchingLineBase *f=MatachingLines[w][h].GetFirst();f!=NULL;f=f->GetNext()){
				if((n%Sep)==0){
					double	d=f->Match(TBuff,dx,dy);
					if(d>0){
						D*=d;
						Numb++;
					}
					else{
						D*=0.1;
						Numb++;
					}
				}
				n++;
			}
			if(Numb!=0){
				RTable[TableNumb]=pow(D,1.0/Numb);
				TableNumb++;
			}
		}
	}
	if(TableNumb==0){
		return 0;
	}
	//if(TableNumb<=3){
	//	double	Avr=0;
	//	for(int i=0;i<TableNumb;i++){
	//		Avr+=RTable[i];
	//	}
	//	return Avr/TableNumb;
	//}
	//
	//QSort(RTable,TableNumb,sizeof(RTable[0]),FuncRTable);
	//TableNumb-=2;
	double	Avr=0;
	for(int i=0;i<TableNumb;i++){
		Avr+=RTable[i];
	}
	return Avr/TableNumb;
}

double	RotatedMatchingPattern::MatchRoughSuper(ImageBuffer *TBuff[]
										   ,int dx,int dy
										   ,int Sep)
{
	if(WNumb!=0 && HNumb!=0){
		MatchingLineBase *f=MatachingLines[0][0].GetFirst();
		if(f!=NULL){
			double	D=f->Match(TBuff,dx,dy);
			return D;
		}
	}
	return 0;
}

void	RotatedMatchingPattern::MatchSingle(int XLen,int YLen
											,ImageBuffer *TBuff[],int LayerNumb
											,FlexArea &PickedArea)
{
	SingleNumb=0;
	if(SinglePointer!=0){
		int	x1=PickedArea.GetMinX();
		int	y1=PickedArea.GetMinY();
		int	x2=PickedArea.GetMaxX();
		int	y2=PickedArea.GetMaxY();

		x1-=20;
		y1-=20;
		x2+=20;
		y2+=20;

		int	WLen=x2-x1-PickedAreaInPattern.GetWidth();
		int	HLen=y2-y1-PickedAreaInPattern.GetHeight();

		if(WLen<0 || HLen<0)
			return;

		if(WLen<20){
			WLen=20;
		}
		if(HLen<20){
			HLen=20;
		}
		int	Cx,Cy;
		PickedAreaInPattern.GetCenter(Cx,Cy);
		int	Hx,Hy;
		PickedArea.GetCenter(Hx,Hy);

		WLen/=2;
		HLen/=2;
		for(int dy=-HLen;dy<=HLen;dy+=2){
			for(int dx=-WLen;dx<=WLen;dx+=2){
				double	D=SinglePointer->Match(TBuff,Hx-Cx+dx,Hy-Cy+dy);
				if(D>0){
					ShiftXYDim[SingleNumb].Dx=Hx-Cx+dx;
					ShiftXYDim[SingleNumb].Dy=Hy-Cy+dy;
					ShiftXYDim[SingleNumb].D =D;
					SingleNumb++;
				}
			}
		}

		//int	N=PickedArea.GetFLineLen();
		//for(int i=0;i<N;i++){
		//	int	Y	=PickedArea.GetFLineAbsY(i);
		//	int	X1	=PickedArea.GetFLineLeftX(i);
		//	int	Numb=PickedArea.GetFLineNumb(i);
		//	for(int n=0;n<Numb;n+=2){
		//		int	X=X1+n;
		//		double	D=SinglePointer->Match(TBuff,X,Y);
		//		if(D>0){
		//			ShiftXYDim[SingleNumb].Dx=X;
		//			ShiftXYDim[SingleNumb].Dy=Y;
		//			ShiftXYDim[SingleNumb].D =D;
		//			SingleNumb++;
		//		}
		//	}
		//}
	}
}
int	ShiftXYDimFunc(const void *a ,const void *b)
{
	struct ShiftXY	*pa=(struct ShiftXY *)a;
	struct ShiftXY	*pb=(struct ShiftXY *)b;
	if(pa->D<pb->D)
		return 1;
	if(pa->D>pb->D)
		return -1;
	return 0;
}

void	RotatedMatchingPattern::MatchDual(int XLen,int YLen
											,ImageBuffer *TBuff[],int LayerNumb
											,FlexArea &PickedArea)
{
	//DualNumb=0;
	if(SinglePointer!=0 && SecondPointer!=0){
		QSort(ShiftXYDim,SingleNumb,sizeof(ShiftXYDim[0]),ShiftXYDimFunc);

		DualNumb=SingleNumb/200;
		if(DualNumb<100){
			DualNumb=min(100,SingleNumb);
		}
		if(DualNumb>=500){
			DualNumb=min(500,SingleNumb);
		}
		//int	MinX=PickedAreaInPattern.GetMinX();
		//int	MinY=PickedAreaInPattern.GetMinY();

		for(int i=0;i<DualNumb;i++){
			double	D=SecondPointer->Match(TBuff,ShiftXYDim[i].Dx,ShiftXYDim[i].Dy);
			if(D>0){
				ShiftXYDim[i].D*=D;
			}
			else{
				ShiftXYDim[i].D=0;
			}
		}
	}
}

int64	RotatedMatchingPattern::GetCrossCount(FlexArea &F,int dx,int dy)
{
	return PickedAreaInPattern.GetCrossCount(F,dx,dy);
}

void	RotatedMatchingPattern::MakeImage(int width ,int height ,double ZoomRate
											,QImage &ItemImage)
{
	ItemImage=QImage(width,height,QImage::Format_RGB32);
	SourcePattern.MakeImage(ItemImage ,0,0 ,ZoomRate);
	PickedAreaInPattern.DrawAlpha(0,0
								,&ItemImage,qRgba(255,255,0,128)
								,ZoomRate,0,0);
	EdgeArea.DrawAlpha(0,0
				,&ItemImage,qRgba(255,128,0,128)
				,ZoomRate,0,0);

	//PickedAreaInPatternShrinked.DrawAlpha(0,0
	//							,&ItemImage,qRgba(255,255,0,128)
	//							,ZoomRate,0,0);

	QPainter	Pnt(&ItemImage);
	static	QRgb	ColTable[]={	 qRgb(255,0,0)
									,qRgb(255,128,0)
									,qRgb(0  ,128,255)
									,qRgb(0,0,255)
									,qRgb(128,0,255)
									,qRgb(255,0,255)
									,qRgb(0,255,255)
									,qRgb(255,255,0)
									,qRgb(255,255,255)	
	};

	int	N=0;
	for(int w=0;w<WNumb;w++){
		for(int h=0;h<HNumb;h++){
			Pnt.setPen(QColor(ColTable[N%9]));
			for(MatchingLineBase *f=MatachingLines[w][h].GetFirst();f!=NULL;f=f->GetNext()){
				f->Draw(Pnt,ZoomRate,0,0);
			}
			N++;
		}
	}
	Pnt.setPen(Qt::white);
	RoughPoints.Draw(Pnt,ZoomRate,0,0);
}

void	RotatedMatchingPattern::MakeShiftDim(int XLen,int YLen
											,ImagePointerContainer &ImageList
											,FlexArea &PickedArea)
{
	const	CounterThreshold	*RThr=Parent->GetThresholdR();
	CounterBase	*ABase=Parent->tGetParentBase();

	int	X1=PickedArea.GetMinX()-15-ExeOffsetX;
	int	X2=PickedArea.GetMaxX()+15-PickedAreaInPattern.GetWidth()*RThr->FilterRate-ExeOffsetX;
	int	Y1=PickedArea.GetMinY()-15-ExeOffsetY;
	int	Y2=PickedArea.GetMaxY()+15-PickedAreaInPattern.GetHeight()*RThr->FilterRate-ExeOffsetY;
	if(X1<6)
		X1=6;
	if((XLen-PickedAreaInPatternFatMask.GetWidth())-6<X2)
		X2=XLen-PickedAreaInPatternFatMask.GetWidth()-6;
	if(Y1<6)
		Y1=6;
	if((YLen-PickedAreaInPatternFatMask.GetHeight())-6<Y2)
		Y2=YLen-PickedAreaInPatternFatMask.GetHeight()-6;
			
	qint64	PCount=PickedAreaInPattern.GetPatternByte();
	ShiftXYDimCount=0;

	int	Lx1=PickedAreaInPatternFatMask.GetMinX();
	int	Ly1=PickedAreaInPatternFatMask.GetMinY();
	int	Lx2=PickedAreaInPatternFatMask.GetMaxX();
	int	Ly2=PickedAreaInPatternFatMask.GetMaxY();
	int	Isolation=8;
	double	CrossRateInPickedArea=Parent->tGetParentBase()->CrossRateInPickedArea;
	for(int dy=Y1;dy<Y2;dy+=Isolation){
		for(int dx=X1;dx<X2;dx+=Isolation){
			qint64	GCrossPixels=PickedArea.GetCrossCount(Lx1+dx,Ly1+dy,Lx2+dx,Ly2+dy);
			if(GCrossPixels>PCount*CrossRateInPickedArea){
				qint64	CrossPixels=PickedAreaInPatternFatMask.GetCrossCount(PickedArea ,-dx ,-dy);
				CrossPixels*=ABase->SkipFlat;
				if(CrossPixels>PCount*CrossRateInPickedArea){
					if(ShiftXYDimCount>=MaxShiftXYDimCount){
						return;
					}
					ShiftXYDim[ShiftXYDimCount].X=dx;
					ShiftXYDim[ShiftXYDimCount].Y=dy;
					ShiftXYDimCount++;
				}
			}
		}
	}
}

int	ShiftXYSortDimFunc(const void *a ,const void *b)
{
	struct ShiftXY	*pa=(struct ShiftXY *)a;
	struct ShiftXY	*pb=(struct ShiftXY *)b;
	if(pa->D<pb->D)
		return -1;
	if(pa->D>pb->D)
		return 1;
	return 0;
}

void	RotatedMatchingPattern::GetSearchMax(ImagePointerContainer &ImageList
											,FlexArea &PickedArea
											,struct ShiftXY	*tShiftXYDim
											,int tShiftXYDimCount)
{
	ImageBuffer *TBuff[3];
	//const	CounterThreshold	*RThr=Parent->GetThresholdR();
	int	Layer=0;
	for(ImagePointerList *L=ImageList.GetFirst();L!=NULL && Layer<3;L=L->GetNext()){
		TBuff[Layer]=L->GetImage();
	}
	//int	W2=PickedAreaInPattern.GetWidth()/2;
	//int	H2=PickedAreaInPattern.GetHeight()/2;
	//double	DifAngle=30*M_PI/180.0;

	ShiftXYDimCount=tShiftXYDimCount;
	for(int i=0;i<tShiftXYDimCount;i++){
		ShiftXYDim[i].D=0;
		ShiftXYDim[i].X=tShiftXYDim[i].X;
		ShiftXYDim[i].Y=tShiftXYDim[i].Y;
		ShiftXYDim[i].Dx=0;
		ShiftXYDim[i].Dy=0;
		for(int hdy=-2;hdy<3;hdy+=4){
			for(int hdx=-2;hdx<3;hdx+=4){
				int	dx=hdx+tShiftXYDim[i].X;
				int	dy=hdy+tShiftXYDim[i].Y;

				double	D=MatchRoughSuper(TBuff,dx,dy,2);
				if(ShiftXYDim[i].D<D){
					ShiftXYDim[i].D=D;
					ShiftXYDim[i].Dx=hdx;
					ShiftXYDim[i].Dy=hdy;
				}
			}
		}
	}
	QSort(ShiftXYDim,tShiftXYDimCount,sizeof(ShiftXYDim[0]),ShiftXYSortDimFunc);
	for(int i=0;i<tShiftXYDimCount;i++){
		ShiftXYDim[i].D=0;
	}
	int	N=tShiftXYDimCount/10;
	if(N<10)
		N=tShiftXYDimCount;
	for(int i=0;i<N;i++){
		ShiftXYDim[i].D=0;
		ShiftXYDim[i].X=tShiftXYDim[i].X;
		ShiftXYDim[i].Y=tShiftXYDim[i].Y;
		ShiftXYDim[i].Dx=0;
		ShiftXYDim[i].Dy=0;
		for(int hdy=-2;hdy<3;hdy+=4){
			for(int hdx=-2;hdx<3;hdx+=4){
				int	dx=hdx+tShiftXYDim[i].X;
				int	dy=hdy+tShiftXYDim[i].Y;

				double	D=MatchRough(TBuff,dx,dy,2);
				if(ShiftXYDim[i].D<D){
					ShiftXYDim[i].D=D;
					ShiftXYDim[i].Dx=hdx;
					ShiftXYDim[i].Dy=hdy;
				}
			}
		}
	}
	/*
	NextP:;
	QSort(ShiftXYSortDim,Index,sizeof(ShiftXYSortDim[0]),ShiftXYSortDimFunc);
	int	N=Index/10;
	for(int i=0;i<N;i++){
		int	dx=ShiftXYSortDim[i].X;
		int	dy=ShiftXYSortDim[i].Y;
		bool	Already=false;
		for(int t=0;t<LocalResultCount;t++){
			double	ds=::DiffSita(LocalResult[t].Pointer->Angle,Angle);
			if(ds<30*M_PI/180.0){
				int	kx=abs(LocalResult[t].PosX-dx);
				int	ky=abs(LocalResult[t].PosY-dy);
				if(kx<W2 && ky<H2){
					Already=true;
					break;
				}
			}
		}
		if(Already==false){
			double	D=MatchRough(TBuff,dx,dy,1);
			if(MaxD<D){
				Found=true;
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
	}
	*/
	/*
	if(Found==true){
		MaxD=0;
		for(int dy=-2;dy<=2;dy++){
			for(int dx=-2;dx<=2;dx++){
				double	D=MatchRough(TBuff,MaxDx+dx,MaxDy+dy,1);
				if(MaxD<D){
					MaxD=D;
					Dx=MaxDx+dx;
					Dy=MaxDy+dy;
				}
			}
		}
	}
	*/

	//return MaxD;		
}
double	RotatedMatchingPattern::GetSearchMaxDetail(ImagePointerContainer &ImageList
						,FlexArea &PickedArea
						,int LocalResultCount
						,MatchingResultList	LocalResult[100]
						,int PosX ,int PosY
						,int &Dx ,int &Dy)
{
	const	CounterThreshold	*RThr=Parent->GetThresholdR();

	MatchingMethod Method=_AveragePower;
	if(RThr->OutlineSearchDot<=2){
		Method=_MinRate;
	}
	ImageBuffer *TBuff[3];
	int	Layer=0;
	for(ImagePointerList *L=ImageList.GetFirst();L!=NULL && Layer<3;L=L->GetNext()){
		TBuff[Layer]=L->GetImage();
		Layer++;
	}
	int	W2=PickedAreaInPattern.GetWidth()/2;
	int	H2=PickedAreaInPattern.GetHeight()/2;

	double	MaxD=0;
	int	MaxDx=0;
	int	MaxDy=0;
	for(int dy=PosY-8;dy<PosY+8;dy+=2){
		for(int dx=PosX-8;dx<PosX+8;dx+=2){
			bool	Already=false;
			for(int t=0;t<LocalResultCount;t++){
				double	ds=::DiffSita(LocalResult[t].Pointer->Angle,Angle);
				if(ds<30*M_PI/180.0){
					int	kx=abs(LocalResult[t].ResultPosX-dx);
					int	ky=abs(LocalResult[t].ResultPosY-dy);
					if(kx<W2 && ky<H2){
						Already=true;
						break;
					}
				}
			}
			if(Already==false){
				double	D=Match(TBuff,dx,dy,RThr->OutlineSearchDot,Method);
				if(MaxD<D){
					MaxD=D;
					MaxDx=dx;
					MaxDy=dy;
				}
			}
		}
	}
	Dx=MaxDx;
	Dy=MaxDy;
	//MaxD=0;
	//for(int dy=-1;dy<=1;dy++){
	//	for(int dx=-1;dx<=1;dx++){
	//		double	D=Match(TBuff,MaxDx+dx,MaxDy+dy);
	//		if(MaxD<D){
	//			MaxD=D;
	//			Dx=MaxDx+dx;
	//			Dy=MaxDy+dy;
	//		}
	//	}
	//}
	qint64	PCount=PickedAreaInPattern.GetPatternByte();
	qint64	CrossPixels=PickedArea.GetCrossCount(PickedAreaInPattern ,Dx ,Dy);

	if(PCount*0.3<CrossPixels)
		return MaxD;
	return 0;
}

struct MatchStruct
{
	int	dx,dy;
	double	D;
};

double	RotatedMatchingPattern::Match(RotatedMatchingPattern *src)
{
	const	CounterThreshold	*RThr=Parent->GetThresholdR();
	MatchingMethod Method=_AveragePower;
	if(RThr->OutlineSearchDot<=2){
		Method=_MinRate;
	}

	ImageBuffer *TBuff[3];
	int	Layer=0;
	for(ImageBufferList *L=SourcePattern.GetFirst();L!=NULL && Layer<3;L=L->GetNext()){
		TBuff[Layer]=L;
		Layer++;
	}
	int	DivMergin=8;
	int	W2=PickedAreaInPattern.GetWidth()/DivMergin;
	int	H2=PickedAreaInPattern.GetHeight()/DivMergin;
	double	MaxD=0;
	int		MaxDx=0;
	int		MaxDy=0;
	int		Isolation=4;

	struct MatchStruct	MatchStructDim[10000];
	int	MatchStructDimNumb=0;
	for(int dy=-H2;dy<=H2;dy+=Isolation){
		for(int dx=-W2;dx<=W2;dx+=Isolation){
			MatchStructDim[MatchStructDimNumb].dx=dx;
			MatchStructDim[MatchStructDimNumb].dy=dy;
			MatchStructDimNumb++;
		}
	}

	#pragma omp parallel
	{                                                
		#pragma omp for
		for(int i=0;i<MatchStructDimNumb;i++){
			MatchStructDim[i].D=src->Match(TBuff,MatchStructDim[i].dx,MatchStructDim[i].dy
										   ,RThr->OutlineSearchDot,Method);
		}
	}
	//for(int dy=-H2;dy<=H2;dy+=Isolation){
	//	for(int dx=-W2;dx<=W2;dx+=Isolation){
	//		double	D=src->Match(TBuff,dx,dy);
	//		if(MaxD<D){
	//			MaxD=D;
	//			MaxDx=dx;
	//			MaxDy=dy;
	//		}
	//	}
	//}
	for(int i=0;i<MatchStructDimNumb;i++){
		if(MaxD<MatchStructDim[i].D){
			MaxD=MatchStructDim[i].D;
			MaxDx=MatchStructDim[i].dx;
			MaxDy=MatchStructDim[i].dy;
		}
	}
	MaxD=0;
	for(int dy=(-Isolation+1);dy<=(Isolation-1);dy++){
		for(int dx=(-Isolation+1);dx<=(Isolation-1);dx++){
			double	D=src->Match(TBuff,MaxDx+dx,MaxDy+dy
								 ,RThr->OutlineSearchDot,Method);
			if(MaxD<D){
				MaxD=D;
			}
		}
	}
	return MaxD;
}
void	RotatedMatchingPattern::Draw(QImage &IData
							,int MovX ,int MovY ,double ZoomRate
							,int PosX,int PosY
							,const QColor &Col)
{
	PickedAreaInPattern.DrawAlpha(PosX,PosY,&IData,Col.rgba(),ZoomRate,MovX,MovY);
}
