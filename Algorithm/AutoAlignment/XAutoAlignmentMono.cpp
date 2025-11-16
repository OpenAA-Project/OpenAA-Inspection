/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAutoAlignmentMono.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAutoAlignment.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include "XAutoMaskingPI.h"
#include "XAnyData.h"
#include "XGeneralFunc.h"
#include <omp.h>
#include "XPointer.h"
#define _USE_MATH_DEFINES
#include "math.h"

AutoAlignmentInPageMonoMiniSize::AutoAlignmentInPageMonoMiniSize(AutoAlignmentInPage *parent)
{
	MasterMap=NULL;
	TargetMap=NULL;
	Parent=parent;
	SparseDot	=0;
	sXByte		=0;
	sDotPerLine	=0;
	sMaxLines	=0;
	LeftMergin	=0;
	XCalcNumb	=0;
	TopMergin	=0;
	YCalcNumb	=0;

	AlignedDx	=0;
	AlignedDy	=0;
	AlignedTheta=0;
	MatchResult	=0;
}
AutoAlignmentInPageMonoMiniSize::~AutoAlignmentInPageMonoMiniSize(void)
{
	DeleteMatrixBuff(MasterMap,sMaxLines);
	DeleteMatrixBuff(TargetMap,sMaxLines);
	MasterMap=NULL;
	TargetMap=NULL;
}

void	AutoAlignmentInPageMonoMiniSize::InitialAlloc(int sparseDot)
{
	SparseDot	=sparseDot;
	sDotPerLine	=Parent->GetDotPerLine()/SparseDot;
	sMaxLines	=Parent->GetMaxLines()/SparseDot;
	sXByte		=(sDotPerLine+7)/8;

	DeleteMatrixBuff(MasterMap,sMaxLines);
	DeleteMatrixBuff(TargetMap,sMaxLines);
	MasterMap	=MakeMatrixBuff(sDotPerLine,sMaxLines);
	TargetMap	=MakeMatrixBuff(sDotPerLine,sMaxLines);
}

void	AutoAlignmentInPageMonoMiniSize::CreateMasterMap(const BYTE **Mask)
{
	LeftMergin	=4*(((AutoAlignmentBase*)Parent->GetParentBase())->SearchDot+SparseDot-1)/SparseDot;
	XCalcNumb	=sDotPerLine-LeftMergin;
	TopMergin	=4*(((AutoAlignmentBase*)Parent->GetParentBase())->SearchDot+SparseDot-1)/SparseDot;
	YCalcNumb	=sMaxLines-TopMergin;

	ImagePointerContainer Images;
	Parent->GetDataInPage()->GetMasterImages(Images);
	CreateMap(Images,MasterMap,Mask);
	CalcMaster();
}

void	AutoAlignmentInPageMonoMiniSize::CreateTargetMap(void)
{
	ImagePointerContainer Images;
	Parent->GetDataInPage()->GetTargetImages(Images);
	CreateMap(Images,TargetMap);
}


void	AutoAlignmentInPageMonoMiniSize::FirstMatch(double &Dx ,double &Dy ,double &Theta
				, int SearchDot ,double MaxTheta)
{
	double	M=hypot(sDotPerLine,sMaxLines)/2.0;
	double	ds=atan(1.0/M);
	double	MaxD=0;

	for(double s=-MaxTheta;s<=MaxTheta;s+=ds){
		for(int dy=-SearchDot;dy<=SearchDot;dy++){
			for(int dx=-SearchDot;dx<=SearchDot;dx++){
				double	d=Match(dx ,dy ,s);
				if(MaxD<d){
					MaxD=d;
					Dx=dx;
					Dy=dy;
					Theta=s;
				}
			}
		}
	}
	AlignedDx	=Dx;
	AlignedDy	=Dy;
	AlignedTheta=Theta;
	MatchResult	=MaxD;
}
void	AutoAlignmentInPageMonoMiniSize::FirstMatch(double &Dx ,double &Dy
				, int SearchDot)
{
	double	MaxD=0;

	for(int dy=-SearchDot;dy<=SearchDot;dy++){
		for(int dx=-SearchDot;dx<=SearchDot;dx++){
			double	d=Match(dx ,dy);
			if(MaxD<d){
				MaxD=d;
				Dx=dx;
				Dy=dy;
			}
		}
	}
	AlignedDx	=Dx;
	AlignedDy	=Dy;
	MatchResult	=MaxD;
}

void	AutoAlignmentInPageMonoMiniSize::SlightMatch(double &Dx ,double &Dy ,double &Theta
					,double RealDx ,double RealDy ,double RealTheta)
{
	double	M=hypot(sDotPerLine,sMaxLines)/2.0;
	double	ds=atan(1.0/M);
	double	MaxD=0;

	for(double s=RealTheta-ds;s<=RealTheta+ds;s+=ds){
		for(int dy=RealDy-1;dy<=RealDy+1;dy++){
			for(int dx=RealDx-1;dx<=RealDx+1;dx++){
				double	d=Match(dx ,dy ,s);
				if(MaxD<d){
					MaxD=d;
					Dx=dx;
					Dy=dy;
					Theta=s;
				}
			}
		}
	}
	AlignedDx	=Dx;
	AlignedDy	=Dy;
	AlignedTheta=Theta;
	MatchResult	=MaxD;
}
void	AutoAlignmentInPageMonoMiniSize::SlightMatch(double &Dx ,double &Dy
					,double RealDx ,double RealDy)
{
	double	MaxD=0;

	for(int dy=RealDy-1;dy<=RealDy+1;dy++){
		for(int dx=RealDx-1;dx<=RealDx+1;dx++){
			double	d=Match(dx ,dy);
			if(MaxD<d){
				MaxD=d;
				Dx=dx;
				Dy=dy;
			}
		}
	}
	AlignedDx	=Dx;
	AlignedDy	=Dy;
	MatchResult	=MaxD;
}

double	AutoAlignmentInPageMonoMiniSize::Match(double Dx ,double Dy ,double Theta)
{
	double	coss=cos(Theta);
	double	sins=sin(Theta);
	double	dS=0;
	double	dD=0;
	double	dSS=0;
	double	dDD=0;
	double	dSD=0;
	int		N=0;
	
	double	Cx=sDotPerLine*0.5;
	double	Cy=sMaxLines*0.5;
	//#pragma omp parallel for reduction(+:N,dS,dD,dSS,dDD,dSD)
	for(int y=0;y<sMaxLines;y++){
		double	dy2=(y+Dy-Cy);
		int	iS=0;
		int	iD=0;
		int	iSS=0;
		int	iDD=0;
		int	iSD=0;
		int	iN=0;
		for(int x=0;x<sDotPerLine;x++){
			BYTE	cm=MasterMap[y][x];
			if(cm!=0){
				double	dx2=(x+Dx-Cx);
				int	mx=dx2*coss-dy2*sins+Cx;
				int	my=dy2*sins+dy2*coss+Cy;
				if(0<=mx && mx<sDotPerLine && 0<=my && my<sMaxLines){
					BYTE	ct=TargetMap[my][mx];
					iS +=cm;
					iSS+=cm*cm;
					iD +=ct;
					iDD+=ct*ct;
					iSD+=cm*ct;
					iN++;
				}
			}
		}
		dS+=iS;
		dD+=iD;
		dSS+=iSS;
		dDD+=iDD;
		dSD+=iSD;
		N+=iN;
	}
	double	AvrS=dS/N;
	double	AvrD=dD/N;
	double	ret=(dSD-AvrS*AvrD*N)/sqrt((dSS-AvrS*AvrS*N)*(dDD-AvrD*AvrD*N));
	return ret;
}

double	AutoAlignmentInPageMonoMiniSize::Match(double Dx ,double Dy)
{
	double	dD=0;
	double	dDD=0;
	double	dSD=0;
	int		N=0;
	int		iDx=Dx;
	int		iDy=Dy;

	int	YNumb=YCalcNumb-TopMergin;
	#pragma omp parallel for reduction(+:N,dD,dDD,dSD)
	for(int i=0;i<YNumb;i++){
	//for(int y=TopMergin;y<YCalcNumb;y++){
		int	y=i+TopMergin;
		int	iS=0;
		int	iD=0;
		int	iSS=0;
		int	iDD=0;
		int	iSD=0;
		int	iN=0;
		int	my=y+iDy;
		BYTE	*s=MasterMap[y];
		BYTE	*d=TargetMap[my];
		for(int x=LeftMergin;x<XCalcNumb;x++){
			int	cm=s[x];
			int	ct=d[x+iDx];
			iD +=ct;
			iDD+=ct*ct;
			iSD+=cm*ct;
			iN++;
		}
		dD+=iD;
		dDD+=iDD;
		dSD+=iSD;
		N+=iN;
	}
	double	AvrS=MasterAddA/N;
	double	AvrD=dD/N;
	double	ret=(dSD-AvrS*AvrD*N)/sqrt((MasterAddA2-AvrS*AvrS*N)*(dDD-AvrD*AvrD*N));
	return ret;
}

void	AutoAlignmentInPageMonoMiniSize::CalcMaster(void)
{
	double	dS=0;
	double	dSS=0;
	int		N=0;
	
	for(int y=TopMergin;y<YCalcNumb;y++){
		int	iS=0;
		int	iSS=0;
		int	iN=0;
		BYTE	*s=MasterMap[y];
		for(int x=LeftMergin;x<XCalcNumb;x++){
			int	c=s[x];
			iS +=c;
			iSS+=c*c;
			iN++;
		}
		dS+=iS;
		dSS+=iSS;
		N+=iN;
	}
	MasterAddA=dS;
	MasterAddA2=dSS;
}

void	AutoAlignmentInPageMonoMiniSize::CreateMap(ImagePointerContainer &SrcImg ,BYTE **Map)
{
	int	N=SrcImg.GetCount();
	for(int DstY=0;DstY<sMaxLines;DstY++){
		int	SrcY=DstY*SparseDot;
		int	SrcX=0;
		BYTE	*XPointer[100];
		for(int i=0;i<N && i<100;i++){
			XPointer[i]=SrcImg.GetItem(i)->GetImage()->GetY(SrcY);
		}
		for(int DstX=0;DstX<sDotPerLine;DstX++){
			SrcX=DstX*SparseDot;
			int	D=0;
			for(int i=0;i<N && i<100;i++){
				D+=XPointer[i][SrcX]*XPointer[i][SrcX];
			}
			double	mD=(double)D/(double)N;
			Map[DstY][DstX]=sqrt(mD);
		}
	}
}
void	AutoAlignmentInPageMonoMiniSize::CreateMap(ImagePointerContainer &SrcImg ,BYTE **Map,const BYTE **Mask)
{
	int	N=SrcImg.GetCount();
	if(Mask!=NULL){
		for(int DstY=0;DstY<sMaxLines;DstY++){
			int	SrcY=DstY*SparseDot;
			int	SrcX=0;
			BYTE	*XPointer[100];
			for(int i=0;i<N && i<100;i++){
				XPointer[i]=SrcImg.GetItem(i)->GetImage()->GetY(SrcY);
			}
			for(int DstX=0;DstX<sDotPerLine;DstX++){
				SrcX=DstX*SparseDot;
				if((Mask[SrcY][SrcX>>3] & (0x80>>(SrcX&7)))!=0){
					int	D=0;
					for(int i=0;i<N && i<100;i++){
						D+=XPointer[i][SrcX]*XPointer[i][SrcX];
					}
					double	mD=(double)D/(double)N;
					Map[DstY][DstX]=sqrt(mD);
				}
				else{
					Map[DstY][DstX]=0;
				}
			}
		}
	}
	else{
		for(int DstY=0;DstY<sMaxLines;DstY++){
			int	SrcY=DstY*SparseDot;
			int	SrcX=0;
			BYTE	*XPointer[100];
			for(int i=0;i<N && i<100;i++){
				XPointer[i]=SrcImg.GetItem(i)->GetImage()->GetY(SrcY);
			}
			for(int DstX=0;DstX<sDotPerLine;DstX++){
				SrcX=DstX*SparseDot;
				Map[DstY][DstX]=0;
			}
		}
	}
}

void	AutoAlignmentInPageMonoMiniSize::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AutoAlignmentDrawAttr	*A=(AutoAlignmentDrawAttr *)Attr;
	if(A!=NULL){
		if(A->Mastered==true && A->DrawMono==true){
			int	W=pnt.width();
			int	H=pnt.height();
			for(int y=0;y<H;y++){
				int	sy=(y/ZoomRate-movy)/SparseDot;
				BYTE	*B=pnt.scanLine(y);
				if(0<=sy && sy<sMaxLines){
					for(int x=0;x<W;x++){
						int	sx=(x/ZoomRate-movx)/SparseDot;
						if(0<=sx && sx<sDotPerLine){
							if(MasterMap[sy][sx]!=0){
								*(B+0)=MasterMap[sy][sx];
								*(B+1)=0;
								*(B+2)=0;
								*(B+3)=128;
							}
							else{
								*(B+0)=0;
								*(B+1)=0;
								*(B+2)=0;
								*(B+3)=0;
							}
						}
						else{
							*(B+0)=0;
							*(B+1)=0;
							*(B+2)=0;
							*(B+3)=0;
						}
						B+=4;
					}
				}
				else{
					for(int x=0;x<W;x++){
						*(B+0)=0;
						*(B+1)=0;
						*(B+2)=0;
						*(B+3)=0;
						B+=4;
					}
				}
			}
		}
		else if(A->Mastered==false && A->DrawMono==true){
			int	W=pnt.width();
			int	H=pnt.height();
			double	CosS=cos(AlignedTheta);
			double	SinS=sin(AlignedTheta);
			double	zZoomRate	=1.0/(double)ZoomRate;
			double	zSparseDot	=1.0/(double)SparseDot;
			double	sMaxLines2	=sMaxLines/2.0;
			double	sDotPerLine2=sDotPerLine/2.0;

			for(int y=0;y<H;y++){
				double	ky=(y*zZoomRate-movy)*zSparseDot-AlignedDy-sMaxLines2;
				BYTE	*B=pnt.scanLine(y);
				for(int x=0;x<W;x++){
					double	kx=(x*zZoomRate-movx)*zSparseDot-AlignedDx-sDotPerLine2;
					int	sx=kx*CosS - ky*SinS + sDotPerLine2;
					int	sy=kx*SinS + ky*CosS + sMaxLines2;
					
					if(0<=sy && sy<sMaxLines
					&& 0<=sx && sx<sDotPerLine){
						if(MasterMap[sy][sx]!=0){
							*(B+0)=MasterMap[sy][sx];
							*(B+1)=0;
							*(B+2)=0;
							*(B+3)=128;
						}
						else{
							*(B+0)=0;
							*(B+1)=0;
							*(B+2)=0;
							*(B+3)=0;
						}
					}
					B+=4;
				}
			}
		}
	}
}
void	AutoAlignmentInPageMonoMiniSize::DrawResult(ResultInItemRoot &Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
}

//====================================================================================================
