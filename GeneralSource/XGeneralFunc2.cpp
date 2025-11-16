/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGeneralFunc.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XTypeDef.h"
#include <QtGui>
#include "XGeneralFunc.h"
#include <stdio.h>
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XYCross.h"
#include <omp.h>
#include "swap.h"
#include <QTextCodec>
#include "XIntClass.h"
#include "XDateTime.h"

#include<QStackedWidget>
#include<QListWidget>
#include<QTableWidget>

//----------------------------------------------------------------

void	FuncCall	AddAlphaChannel(QImage &image, int alpha)
{
	int	YLen=image.height();
	int	XLen=image.width();
	int	Depth=image.depth();
	if(Depth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)image.scanLine(y);
				for(int x=0;x<XLen;x++){
					if((*d & 0xFFFFFF)!=0){
						*(((BYTE *)d)+3)=alpha;
					}
					else{
						*(((BYTE *)d)+3)=0;
					}
					d++;
				}
			}
		}
	}
}

void	ClearImage(QImage& image, int alpha)
{
	int	YLen=image.height();
	int	XLen=image.width();
	int	Depth=image.depth();
	DWORD	D;
	*(((BYTE *)&D)+0)=0;
	*(((BYTE *)&D)+1)=0;
	*(((BYTE *)&D)+2)=0;
	*(((BYTE *)&D)+3)=alpha;
	if(Depth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)image.scanLine(y);
				for(int x=0;x<XLen;x++){
					*d =D;
					d++;
				}
			}
		}
	}

}
void	FuncCall	MultiplyImage(QImage &image, double Multiply)
{
	BYTE	CTable[256];
	for(int i=0;i<256;i++){
		CTable[i] = Clipping((int)(i*Multiply),0,255);
	}

	int	YLen=image.height();
	int	XLen=image.width();
	int	Depth=image.depth();
	if(Depth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*d=(BYTE *)image.scanLine(y);
				for(int x=0;x<XLen;x++){
					*(d+0) =CTable[*(d+0)];
					*(d+1) =CTable[*(d+1)];
					*(d+2) =CTable[*(d+2)];
					d+=4;
				}
			}
		}
	}
}
void	MoveZoomImage(QImage& dst, QImage& src, int OffsetX, int OffsetY ,double ZoomRate)
{
	int	sYLen=src.height();
	int	sXLen=src.width() ;
	int	dYLen=dst.height();
	int	dXLen=dst.width() ;
	int	dDepth=dst.depth();
	int	sDepth=src.depth();
	double	Z=1.0/ZoomRate;
	if(dDepth==32 && sDepth==32){
		int	StartX	=min(dXLen,(int)(OffsetX*ZoomRate));
		int	EndX	=min(dXLen,(int)((sXLen+OffsetX)*ZoomRate));
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<dYLen;y++){
				QRgb	*d=(QRgb *)dst.scanLine(y);
				int	Y=y*Z-OffsetY;
				if(0<=Y && Y<sYLen){
					QRgb	*s=(QRgb *)src.scanLine(Y);
					int	x;
					for(x=0;x<StartX;x++,d++){
						*d=qRgb(0,0,0);
					}
					for(;x<EndX;x++,d++){
						int	X=x*Z-OffsetX;
						*d=s[X];
					}
					for(;x<dXLen;x++,d++){
						*d=qRgb(0,0,0);
					}
				}
				else{
					for(int x=0;x<dXLen;x++,d++){
						*d=qRgb(0,0,0);
					}
				}
			}
		}
	}
}

void	FuncCall	CopyPixelsWithAlpha(QImage &dst, QImage &src)
{
	int	YLen=min(src.height(),dst.height());
	int	XLen=min(src.width() ,dst.width());
	int	dDepth=dst.depth();
	int	sDepth=src.depth();
	if(dDepth==32 && sDepth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y);
				DWORD	*s=(DWORD *)src.scanLine(y);
				for(int x=0;x<XLen;x++,d++,s++){
					int	ca=qAlpha(*s);
					*d=qRgba(Clipping((((qRed(*s)	-qRed(*d))*ca)>>8)+qRed(*d),0,255)
							,Clipping((((qGreen(*s)	-qGreen(*d))*ca)>>8)+qGreen(*d),0,255)
							,Clipping((((qBlue(*s)	-qBlue(*d))*ca)>>8)+qBlue(*d),0,255)
							,ca);
				}
			}
		}
	}
}

void	FuncCall	CopyPixelsWithAlpha(QImage &dst, QImage &src,int alpha)
{
	int	YLen=min(src.height(),dst.height());
	int	XLen=min(src.width() ,dst.width());
	int	dDepth=dst.depth();
	int	sDepth=src.depth();
	if(dDepth==32 && sDepth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y);
				DWORD	*s=(DWORD *)src.scanLine(y);
				for(int x=0;x<XLen;x++,d++,s++){
					*d=qRgba(Clipping((((qRed(*s)	-qRed(*d))*alpha)>>8)+qRed(*d),0,255)
							,Clipping((((qGreen(*s)	-qGreen(*d))*alpha)>>8)+qGreen(*d),0,255)
							,Clipping((((qBlue(*s)	-qBlue(*d))*alpha)>>8)+qBlue(*d),0,255)
							,alpha);
				}
			}
		}
	}
}

void	FuncCall	CopyPixels(QImage &dst, QImage &src,int OffsetX ,int OffsetY,int NumThreads)
{
	int	dDepth=dst.depth();
	int	sDepth=src.depth();
	if(dDepth==32 && sDepth==32){
		if(OffsetX>=0 && OffsetY>=0){
			int	YLen=min(src.height()	,dst.height()-OffsetY);
			int	XLen=min(src.width()	,dst.width()-OffsetX);
			if(XLen<=0){
				return;
			}
			int	XLen4=XLen*4;
			int	N=NumThreads;
			if(YLen<50 || N<=1){
				//#pragma omp parallel num_threads(2)
				//{                                                
				//	#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d=((DWORD *)dst.scanLine(y+OffsetY))+OffsetX;
						DWORD	*s= (DWORD *)src.scanLine(y);
						memcpy(d,s,XLen4);
					}
				//}
			}
			else
			if(N==2){
				//#pragma omp parallel num_threads(2)
				//{                                                
				//	#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d=((DWORD *)dst.scanLine(y+OffsetY))+OffsetX;
						DWORD	*s= (DWORD *)src.scanLine(y);
						memcpy(d,s,XLen4);
					}
				//}
			}
			else
			if(N<=4){
				#pragma omp parallel num_threads(4)
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d=((DWORD *)dst.scanLine(y+OffsetY))+OffsetX;
						DWORD	*s= (DWORD *)src.scanLine(y);
						memcpy(d,s,XLen4);
					}
				}
			}
			else{
				#pragma omp parallel num_threads(8)
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d=((DWORD *)dst.scanLine(y+OffsetY))+OffsetX;
						DWORD	*s= (DWORD *)src.scanLine(y);
						memcpy(d,s,XLen4);
					}
				}
			}
		}
		else if(OffsetX<0 && OffsetY>=0){
			int	YLen=min(src.height()		,dst.height()-OffsetY);
			int	XLen=min(src.width()+OffsetX,dst.width());
			if(XLen<=0){
				return;
			}
			int	XLen4=XLen*4;
			int	N=NumThreads;
			if(YLen<50 || N<=1){
				//#pragma omp parallel num_threads(2)
				//{                                                
				//	#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d= (DWORD *)dst.scanLine(y+OffsetY);
						DWORD	*s=((DWORD *)src.scanLine(y))-OffsetX;
						memcpy(d,s,XLen4);
					}
				//}
			}
			else
			if(N==2){
				//#pragma omp parallel num_threads(2)
				//{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d= (DWORD *)dst.scanLine(y+OffsetY);
						DWORD	*s=((DWORD *)src.scanLine(y))-OffsetX;
						memcpy(d,s,XLen4);
					}
				//}
			}
			else
			if(N<=4){
				#pragma omp parallel num_threads(4)
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d= (DWORD *)dst.scanLine(y+OffsetY);
						DWORD	*s=((DWORD *)src.scanLine(y))-OffsetX;
						memcpy(d,s,XLen4);
					}
				}
			}
			else{
				#pragma omp parallel num_threads(8)
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d= (DWORD *)dst.scanLine(y+OffsetY);
						DWORD	*s=((DWORD *)src.scanLine(y))-OffsetX;
						memcpy(d,s,XLen4);
					}
				}
			}
		}
		else if(OffsetX>=0 && OffsetY<0){
			int	YLen=min(src.height()+OffsetY	,dst.height());
			int	XLen=min(src.width()			,dst.width()-OffsetX);
			if(XLen<=0){
				return;
			}
			int	XLen4=XLen*4;
			int	N=NumThreads;
			if(YLen<50 || N<=1){
				//#pragma omp parallel num_threads(2)
				//{                                                
				//	#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d=((DWORD *)dst.scanLine(y))+OffsetX;
						DWORD	*s= (DWORD *)src.scanLine(y-OffsetY);
						memcpy(d,s,XLen4);
					}
				//}
			}
			else
			if(N==2){
				//#pragma omp parallel num_threads(2)
				//{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d=((DWORD *)dst.scanLine(y))+OffsetX;
						DWORD	*s= (DWORD *)src.scanLine(y-OffsetY);
						memcpy(d,s,XLen4);
					}
				//}
			}
			else
			if(N<=4){
				#pragma omp parallel num_threads(4)
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d=((DWORD *)dst.scanLine(y))+OffsetX;
						DWORD	*s= (DWORD *)src.scanLine(y-OffsetY);
						memcpy(d,s,XLen4);
					}
				}
			}
			else{
				#pragma omp parallel num_threads(8)
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d=((DWORD *)dst.scanLine(y))+OffsetX;
						DWORD	*s= (DWORD *)src.scanLine(y-OffsetY);
						memcpy(d,s,XLen4);
					}
				}
			}
		}
		else{
			int	YLen=min(src.height()+OffsetY	,dst.height());
			int	XLen=min(src.width()+OffsetX	,dst.width() );
			if(XLen<=0){
				return;
			}
			int	XLen4=XLen*4;
			int	N=NumThreads;
			if(YLen<50 || N<=1){
				//#pragma omp parallel	num_threads(2)
				//{                                                
				//	#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d= (DWORD *)dst.scanLine(y);
						DWORD	*s=((DWORD *)src.scanLine(y-OffsetY))-OffsetX;
						memcpy(d,s,XLen4);
					}
				//}
			}
			else
			if(N==2){
				//#pragma omp parallel	num_threads(2)
				//{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d= (DWORD *)dst.scanLine(y);
						DWORD	*s=((DWORD *)src.scanLine(y-OffsetY))-OffsetX;
						memcpy(d,s,XLen4);
					}
				//}
			}
			else
			if(N<=4){
				#pragma omp parallel	num_threads(4)
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d= (DWORD *)dst.scanLine(y);
						DWORD	*s=((DWORD *)src.scanLine(y-OffsetY))-OffsetX;
						memcpy(d,s,XLen4);
					}
				}
			}
			else{
				#pragma omp parallel	num_threads(8)
				{                                                
					#pragma omp for
					for(int y=0;y<YLen;y++){
						DWORD	*d= (DWORD *)dst.scanLine(y);
						DWORD	*s=((DWORD *)src.scanLine(y-OffsetY))-OffsetX;
						memcpy(d,s,XLen4);
					}
				}
			}
		}
	}
}

void	FuncCall	ExtendImage(QImage &dest, QImage &src ,double zx ,double zy)
{
	if(fabs(zx)<0.0001 || fabs(zy)<0.0001){
		return;
	}

	double	NZx=1.0/zx;
	double	NZy=1.0/zy;
	int	DestXLen=dest.width();
	int	DestYLen=dest.height();
	int	*TableX=new int[DestXLen];
	int	*TableY=new int[DestYLen];
	for(int x=0;x<DestXLen;x++){
		TableX[x]=x*NZx;
		if(TableX[x]>=src.width()){
			TableX[x]=src.width()-1;
		}
		if(TableX[x]<0){
			TableX[x]=0;
		}
	}
	for(int y=0;y<DestYLen;y++){
		TableY[y]=y*NZy;
		if(TableY[y]>=src.height()){
			TableY[y]=src.height()-1;
		}
		if(TableY[y]<0){
			TableY[y]=0;
		}
	}
	int	dDepth=dest.depth();
	int	sDepth=src.depth();
	if(dDepth==32 && sDepth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<DestYLen;y++){
				QRgb	*d=(QRgb *)dest.scanLine(y);
				QRgb	*s=(QRgb *)src.scanLine(TableY[y]);
				for(int x=0;x<DestXLen;x++,d++){
					*d=*(s+TableX[x]);
				}
			}
		}
	}
	delete	[]TableX;
	delete	[]TableY;
}

void	ExtendImage(QImage& dest, QImage& src, double zx, double zy, int cx, int cy)
{
	if(fabs(zx)<0.0001 || fabs(zy)<0.0001){
		return;
	}

	double	NZx=1.0/zx;
	double	NZy=1.0/zy;
	int	DestXLen=dest.width();
	int	DestYLen=dest.height();
	int	*TableX=new int[DestXLen];
	int	*TableY=new int[DestYLen];
	for(int x=0;x<DestXLen;x++){
		TableX[x]=(x-cx)*NZx+cx;
		if(TableX[x]>=src.width()){
			TableX[x]=src.width()-1;
		}
		if(TableX[x]<0){
			TableX[x]=0;
		}
	}
	for(int y=0;y<DestYLen;y++){
		TableY[y]=(y-cy)*NZy+cy;
		if(TableY[y]>=src.height()){
			TableY[y]=src.height()-1;
		}
		if(TableY[y]<0){
			TableY[y]=0;
		}
	}
	int	dDepth=dest.depth();
	int	sDepth=src.depth();
	if(dDepth==32 && sDepth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<DestYLen;y++){
				QRgb	*d=(QRgb *)dest.scanLine(y);
				QRgb	*s=(QRgb *)src.scanLine(TableY[y]);
				for(int x=0;x<DestXLen;x++,d++){
					*d=*(s+TableX[x]);
				}
			}
		}
	}
	delete	[]TableX;
	delete	[]TableY;
}


void	FuncCall	RotateImage(QImage &dest, QImage &src ,double s)
{
	double	coss=cos(-s);
	double	sins=sin(-s);
	int	DestXLen=dest.width();
	int	DestYLen=dest.height();
	int	DestCx=DestXLen/2;
	int	DestCy=DestYLen/2;
	int	SrcXLen=src.width();
	int	SrcYLen=src.height();
	int	SrcCx=SrcXLen/2;
	int	SrcCy=SrcYLen/2;

	int	dDepth=dest.depth();
	int	sDepth=src.depth();
	if(dDepth==32 && sDepth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<DestYLen;y++){
				QRgb	*d=(QRgb *)dest.scanLine(y);
				double	tYx=- (y-DestCy)*sins +SrcCx;
				double	tYy=+ (y-DestCy)*coss +SrcCy;
				for(int x=0;x<DestXLen;x++,d++){
					int	X=(x-DestCx)*coss +tYx;
					if(X<0 || X>=SrcXLen){
						continue;
					}
					int	Y=(x-DestCx)*sins +tYy;
					if(Y<0 || Y>=SrcYLen){
						continue;
					}
					QRgb	*se=(QRgb *)src.scanLine(Y);
					*d=*(se+X);
				}
			}
		}
	}
}
void	RotateImage(QImage& dest, QImage& src, double s, int cx, int cy)
{
	double	coss=cos(-s);
	double	sins=sin(-s);
	int	DestXLen=dest.width();
	int	DestYLen=dest.height();
	int	SrcXLen=src.width();
	int	SrcYLen=src.height();

	int	dDepth=dest.depth();
	int	sDepth=src.depth();
	if(dDepth==32 && sDepth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<DestYLen;y++){
				QRgb	*d=(QRgb *)dest.scanLine(y);
				double	tYx=- (y-cy)*sins +cx;
				double	tYy=+ (y-cy)*coss +cy;
				for(int x=0;x<DestXLen;x++,d++){
					int	X=(x-cx)*coss +tYx;
					if(X<0 || X>=SrcXLen){
						continue;
					}
					int	Y=(x-cx)*sins +tYy;
					if(Y<0 || Y>=SrcYLen){
						continue;
					}
					QRgb	*se=(QRgb *)src.scanLine(Y);
					*d=*(se+X);
				}
			}
		}
	}
}

void	FuncCall	SlopeXImage(QImage &dest, QImage &src ,double s ,int cx ,int cy)
{
	double	tans=tan(-s);
	int	DestXLen=dest.width();
	int	DestYLen=dest.height();
	int	SrcXLen=src.width();
	int	SrcYLen=src.height();

	int	dDepth=dest.depth();
	int	sDepth=src.depth();
	if(dDepth==32 && sDepth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<DestYLen;y++){
				QRgb	*d=(QRgb *)dest.scanLine(y);
				int	tY=(y-cy)*tans;
				for(int x=0;x<DestXLen;x++,d++){
					int	X=x+tY;
					if(X<0 || X>=SrcXLen){
						continue;
					}
					int	Y=y;
					if(Y<0 || Y>=SrcYLen){
						continue;
					}
					QRgb	*se=(QRgb *)src.scanLine(Y);
					*d=*(se+X);
				}
			}
		}
	}
}

void	FuncCall	SlopeYImage(QImage &dest, QImage &src ,double s ,int cx ,int cy)
{
	double	tans=tan(-s);
	int	DestXLen=dest.width();
	int	DestYLen=dest.height();
	int	SrcXLen=src.width();
	int	SrcYLen=src.height();

	int	dDepth=dest.depth();
	int	sDepth=src.depth();
	if(dDepth==32 && sDepth==32){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<DestYLen;y++){
				QRgb	*d=(QRgb *)dest.scanLine(y);
				for(int x=0;x<DestXLen;x++,d++){
					int	X=x;
					if(X<0 || X>=SrcXLen){
						continue;
					}
					int	Y=y+(x-cx)*tans;
					if(Y<0 || Y>=SrcYLen){
						continue;
					}
					QRgb	*se=(QRgb *)src.scanLine(Y);
					*d=*(se+X);
				}
			}
		}
	}
}
bool	MakeTransformReverse(double d[6],double s[6])
/*
*	X=s0*x+s1*y+s2
*	Y=s3+x+s4*y+s5
* 
*	s4*X=s0*s4*x+s1*s4*y+s4*s2
*	s1*Y=s1*s3*x+x1*s4*y+s1*s5
*	s4*X-s1*Y=(s0*s4-s1*s3)*x+s4*s2-s1*s5
*	x=(s4*X-s1*Y - s4*s2+s1*s5)/(s0*s4-s1*s3)
* 
*	s3*X=s0*s3*x+s1*s3*y+s2*s3
*	s0*Y=s0*s3*x+s0*s4*y+s0*s5
*	s3*X-s0*Y=(s1*s3-s0*s4)*y+s2*s3-s0*s5
*	y=(-s3*X+s0*Y +s2*s3-s0*s5)/(s0*s4-s1*s3)
*/
{
	double	M=s[0]*s[4]-s[1]*s[3];
	if(M==0.0){
		return false;
	}
	d[0]=s[4]/M;
	d[1]=-s[1]/M;
	d[2]=(-s[4]*s[2]+s[1]*s[5])/M;
	d[3]=-s[3]/M;
	d[4]=s[0]/M;
	d[5]=(s[2]*s[3]-s[0]*s[5])/M;
	return true;
}
void	TransformImage(QImage& dest, QImage& src, double m[6])
{
	double w[6];
	if(MakeTransformReverse(w,m)==true){
		int	DestXLen=dest.width();
		int	DestYLen=dest.height();
		int	SrcXLen=src.width();
		int	SrcYLen=src.height();

		int	dDepth=dest.depth();
		int	sDepth=src.depth();
		if(dDepth==32 && sDepth==32){
			#pragma omp parallel                             
			{                                                
				#pragma omp for
				for(int y=0;y<DestYLen;y++){
					QRgb	*d=(QRgb *)dest.scanLine(y);
					double	tYx=w[1]*y+w[2];
					double	tYy=w[4]*y+w[5];
					double	fX=tYx;
					double	fY=tYy;
					for(int x=0;x<DestXLen;x++,d++){
						int	X=fX;
						int	Y=fY;
						fX+=w[0];
						fY+=w[3];
						if(0<=X && X<SrcXLen && 0<=Y && Y<SrcYLen){
							QRgb	*s=(QRgb *)src.scanLine(Y);
							*d=*(s+X);
						}
					}
				}
			}
		}
	}
}

void	FuncCall	DrawLine(QImage &dest,QRgb col ,int x1, int y1 ,int x2 ,int y2)
{
	int	dx=x2-x1;
	int	dy=y2-y1;
	if(dx==0 && dy==0){
		if(0<=y1 && y1<dest.height()
		&& 0<=x1 && x1<dest.width()){
			BYTE	*d=dest.scanLine(y1);
			if(dest.depth()==32){
				((QRgb *)d)[x1]=col;
			}
			else if(dest.depth()==8){
				d[x1]=(BYTE)col;
			}
		}
	}
	else if(dy==0){
		if(0<=y1 && y1<dest.height()){
			if(x1>x2){
				swap(x1,x2);
			}
			if(x1<0)
				x1=0;
			if(x2>=dest.width())
				x2=dest.width()-1;

			BYTE	*d=dest.scanLine(y1);
			if(dest.depth()==32){
				for(int x=x1;x<=x2;x++){
					((QRgb *)d)[x]=col;
				}
			}
			else if(dest.depth()==8){
				for(int x=x1;x<=x2;x++){
					d[x]=(BYTE)col;
				}
			}
		}
	}
	else if(dx==0){
		if(0<=x1 && x1<dest.width()){
			if(y1>y2){
				swap(y1,y2);
			}
			if(y1<0)
				y1=0;
			if(y2>=dest.height())
				y2=dest.height()-1;

			if(dest.depth()==32){
				for(int y=y1;y<=y2;y++){
					BYTE	*d=dest.scanLine(y);
					((QRgb *)d)[x1]=col;
				}
			}
			else if(dest.depth()==8){
				for(int y=y1;y<=y2;y++){
					BYTE	*d=dest.scanLine(y);
					d[x1]=(BYTE)col;
				}
			}
		}
	}
	else if(abs(dx)>=abs(dy)){
		if(x1>x2){
			swap(x1,x2);
			swap(y1,y2);
		}
		int	AddedM=dy*65536/dx;
		int	M=0;
		int	LastY=-99999999;
		BYTE	*d;
		if(x1<0){
			M=-AddedM*x1;
			x1=0;
		}
		if(x2>=dest.width())
			x2=dest.width()-1;
		if(dest.depth()==32){
			for(int x=x1;x<=x2;x++,M+=AddedM){
				int	y=y1+(M>>16);
				if(y<0 || dest.height()<=y){
					continue;
				}
				if(y!=LastY){
					d=dest.scanLine(y);
					LastY=y;
				}
				((QRgb *)d)[x]=col;
			}
		}
		else if(dest.depth()==8){
			for(int x=x1;x<=x2;x++,M+=AddedM){
				int	y=y1+(M>>16);
				if(y<0 || dest.height()<=y){
					continue;
				}
				if(y!=LastY){
					d=dest.scanLine(y);
					LastY=y;
				}
				d[x]=(BYTE)col;
			}
		}
	}
	else{
		if(y1>y2){
			swap(x1,x2);
			swap(y1,y2);
		}
		int	AddedM=dx*65536/dy;
		int	M=0;
		BYTE	*d;
		if(y1<0){
			M=-AddedM*y1;
			y1=0;
		}
		if(y2>=dest.height())
			y2=dest.height()-1;

		if(dest.depth()==32){
			for(int y=y1;y<=y2;y++,M+=AddedM){
				d=dest.scanLine(y);
				int	x=x1+(M>>16);
				if(0<=x && x<dest.width()){
					((QRgb *)d)[x]=col;
				}
			}
		}
		else if(dest.depth()==8){
			for(int y=y1;y<=y2;y++,M+=AddedM){
				d=dest.scanLine(y);
				int	x=x1+(M>>16);
				if(0<=x && x<dest.width()){
					d[x]=(BYTE)col;
				}
			}
		}
	}
}
void	FuncCall	DrawRect(QImage &dest,QRgb col ,int x1, int y1 ,int x2 ,int y2)
{
	x1=min(x1,dest.width());
	x1=max(0,x1);
	x2=min(x2,dest.width());
	x2=max(0,x2);
	y1=min(y1,dest.height());
	y1=max(0,y1);
	y2=min(y2,dest.height());
	y2=max(0,y2);
	if(x1>x2)	swap(x1,x2);
	if(y1>y2)	swap(y1,y2);

	if(dest.depth()==32){
		int	N=y2-y1;
		int	XNumb=x2-x1;
		//#pragma omp parallel                             
		//{                                                
		//	#pragma omp for
			for(int i=0;i<N;i++){
			//for(int y=y1;y<y2;y++){
				int	y=y1+i;
				QRgb	*d=&((QRgb *)dest.scanLine(y))[x1];
				for(int x=0;x<XNumb;x++,d++){
					*d=col;
				}
			}
		//}
	}
}
void	FuncCall	CombinePixels(QImage &dst, QImage &src ,int OffsetX ,int OffsetY,int Alpha)
{
	static	int	StaticAlpha=-1;
	static	BYTE	CombTable[256][256];
	if(StaticAlpha!=Alpha){
		for(int s=0;s<256;s++){
			for(int d=0;d<256;d++){
				CombTable[d][s]=ClipByte((d*Alpha+s*(255-Alpha))/256);
			}
		}
		StaticAlpha=Alpha;
	}
	if(OffsetX>=0 && OffsetY>=0){
		int	YLen=min(src.height()	,dst.height()-OffsetY);
		int	XLen=min(src.width()	,dst.width()-OffsetX);
		if(XLen<=0){
			return;
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y+OffsetY)+OffsetX;
				DWORD	*s=(DWORD *)src.scanLine(y);
				for(int i=0;i<XLen;i++,s++,d++){
					*(((BYTE *)d)+0)=CombTable[*(((BYTE *)d)+0)][*(((BYTE *)s)+0)];
					*(((BYTE *)d)+1)=CombTable[*(((BYTE *)d)+1)][*(((BYTE *)s)+1)];
					*(((BYTE *)d)+2)=CombTable[*(((BYTE *)d)+2)][*(((BYTE *)s)+2)];
				}
			}
		}
	}
	else if(OffsetX<0 && OffsetY>=0){
		int	YLen=min(src.height()		,dst.height()-OffsetY);
		int	XLen=min(src.width()+OffsetX,dst.width());
		if(XLen<=0){
			return;
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y+OffsetY);
				DWORD	*s=(DWORD *)src.scanLine(y)-OffsetX;
				for(int i=0;i<XLen;i++,s++,d++){
					*(((BYTE *)d)+0)=CombTable[*(((BYTE *)d)+0)][*(((BYTE *)s)+0)];
					*(((BYTE *)d)+1)=CombTable[*(((BYTE *)d)+1)][*(((BYTE *)s)+1)];
					*(((BYTE *)d)+2)=CombTable[*(((BYTE *)d)+2)][*(((BYTE *)s)+2)];
				}
			}
		}
	}
	else if(OffsetX>=0 && OffsetY<0){
		int	YLen=min(src.height()+OffsetY	,dst.height());
		int	XLen=min(src.width()			,dst.width()-OffsetX);
		if(XLen<=0){
			return;
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y)+OffsetX;
				DWORD	*s=(DWORD *)src.scanLine(y-OffsetY);
				for(int i=0;i<XLen;i++,s++,d++){
					*(((BYTE *)d)+0)=CombTable[*(((BYTE *)d)+0)][*(((BYTE *)s)+0)];
					*(((BYTE *)d)+1)=CombTable[*(((BYTE *)d)+1)][*(((BYTE *)s)+1)];
					*(((BYTE *)d)+2)=CombTable[*(((BYTE *)d)+2)][*(((BYTE *)s)+2)];
				}
			}
		}
	}
	else{
		int	YLen=min(src.height()+OffsetY	,dst.height());
		int	XLen=min(src.width()+OffsetX	,dst.width() );
		if(XLen<=0){
			return;
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y);
				DWORD	*s=(DWORD *)src.scanLine(y-OffsetY)-OffsetX;
				for(int i=0;i<XLen;i++,s++,d++){
					*(((BYTE *)d)+0)=CombTable[*(((BYTE *)d)+0)][*(((BYTE *)s)+0)];
					*(((BYTE *)d)+1)=CombTable[*(((BYTE *)d)+1)][*(((BYTE *)s)+1)];
					*(((BYTE *)d)+2)=CombTable[*(((BYTE *)d)+2)][*(((BYTE *)s)+2)];
				}
			}
		}
	}
}
void	FuncCall	AddPixels(QImage &dst, QImage &src ,int OffsetX ,int OffsetY)
{
	static	int	StaticAlpha=-1;
	static	BYTE	CombTable[256][256];
	for(int s=0;s<256;s++){
		for(int d=0;d<256;d++){
			CombTable[d][s]=ClipByte(d+s);
		}
	}
	if(OffsetX>=0 && OffsetY>=0){
		int	YLen=min(src.height()	,dst.height()-OffsetY);
		int	XLen=min(src.width()	,dst.width() -OffsetX);
		if(XLen<=0){
			return;
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y+OffsetY)+OffsetX;
				DWORD	*s=(DWORD *)src.scanLine(y);
				for(int i=0;i<XLen;i++,s++,d++){
					*(((BYTE *)d)+0)=CombTable[*(((BYTE *)d)+0)][*(((BYTE *)s)+0)];
					*(((BYTE *)d)+1)=CombTable[*(((BYTE *)d)+1)][*(((BYTE *)s)+1)];
					*(((BYTE *)d)+2)=CombTable[*(((BYTE *)d)+2)][*(((BYTE *)s)+2)];
				}
			}
		}
	}
	else if(OffsetX<0 && OffsetY>=0){
		int	YLen=min(src.height()		,dst.height()-OffsetY);
		int	XLen=min(src.width()+OffsetX,dst.width());
		if(XLen<=0){
			return;
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y+OffsetY);
				DWORD	*s=(DWORD *)src.scanLine(y)-OffsetX;
				for(int i=0;i<XLen;i++,s++,d++){
					*(((BYTE *)d)+0)=CombTable[*(((BYTE *)d)+0)][*(((BYTE *)s)+0)];
					*(((BYTE *)d)+1)=CombTable[*(((BYTE *)d)+1)][*(((BYTE *)s)+1)];
					*(((BYTE *)d)+2)=CombTable[*(((BYTE *)d)+2)][*(((BYTE *)s)+2)];
				}
			}
		}
	}
	else if(OffsetX>=0 && OffsetY<0){
		int	YLen=min(src.height()+OffsetY	,dst.height());
		int	XLen=min(src.width()			,dst.width()-OffsetX);
		if(XLen<=0){
			return;
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y)+OffsetX;
				DWORD	*s=(DWORD *)src.scanLine(y-OffsetY);
				for(int i=0;i<XLen;i++,s++,d++){
					*(((BYTE *)d)+0)=CombTable[*(((BYTE *)d)+0)][*(((BYTE *)s)+0)];
					*(((BYTE *)d)+1)=CombTable[*(((BYTE *)d)+1)][*(((BYTE *)s)+1)];
					*(((BYTE *)d)+2)=CombTable[*(((BYTE *)d)+2)][*(((BYTE *)s)+2)];
				}
			}
		}
	}
	else{
		int	YLen=min(src.height()+OffsetY	,dst.height());
		int	XLen=min(src.width()+OffsetX	,dst.width() );
		if(XLen<=0){
			return;
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int y=0;y<YLen;y++){
				DWORD	*d=(DWORD *)dst.scanLine(y);
				DWORD	*s=(DWORD *)src.scanLine(y-OffsetY)-OffsetX;
				for(int i=0;i<XLen;i++,s++,d++){
					*(((BYTE *)d)+0)=CombTable[*(((BYTE *)d)+0)][*(((BYTE *)s)+0)];
					*(((BYTE *)d)+1)=CombTable[*(((BYTE *)d)+1)][*(((BYTE *)s)+1)];
					*(((BYTE *)d)+2)=CombTable[*(((BYTE *)d)+2)][*(((BYTE *)s)+2)];
				}
			}
		}
	}
}

void	DrawImage(QPainter &Pnt ,int PanelXLen ,int PanelYLen
				,const QImage &Img ,int movx ,int movy ,double ZoomRate)
{
	QImage	TmpImage(PanelXLen,PanelYLen,QImage::Format_ARGB32);
	TmpImage.fill(qRgba(0,0,0,0));
	double	Z=1.0/ZoomRate;
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<PanelYLen;y++){
			int	Y=y*Z-movy;
			if(0<=Y && Y<Img.height()){
				QRgb	*s=(QRgb *)Img.scanLine(Y);
				QRgb	*d=(QRgb *)TmpImage.scanLine(y);
				for(int x=0;x<PanelXLen;x++,d++){
					int	X=x*Z-movx;
					if(0<=X && X<Img.width()){
						*d=qRgba(qRed(s[X]),qGreen(s[X]),qBlue(s[X]),255);
					}
				}
			}
		}
	}
	//int	Lx=movx*ZoomRate;
	//int	Ly=movy*ZoomRate;
	Pnt.drawImage(0,0,TmpImage);
}

void	DrawImageAlpha(QImage &Pnt
				,const QImage &Img ,int movx ,int movy ,double ZoomRate)
{
	int	PanelXLen=Pnt.width();
	int	PanelYLen=Pnt.height();
	double	Z=1.0/ZoomRate;
	if(Pnt.depth()==32){
		int	SMaxX=Img.width();
		int	SMaxY=Img.height();
		int	x1=(0+movx)*ZoomRate;
		int	y1=(0+movy)*ZoomRate;
		int	x2=(SMaxX+movx)*ZoomRate;
		int	y2=(SMaxY+movx)*ZoomRate;

		if(y1<0)
			y1=0;
		if(PanelYLen<y2)
			y2=PanelYLen;
		if(x1<0)
			x1=0;
		if(PanelXLen<x2)
			x2=PanelXLen;


		int	N=y2-y1;
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			//for(int y=y1;y<y2;y++){
			for(int i=0;i<N;i++){
				int	y=y1+i;
				int	Y=y*Z-movy;
				if(0<=Y && Y<SMaxY){
					QRgb	*d=(QRgb *)Pnt.scanLine(y);
					QRgb	*s=(QRgb *)Img.scanLine(Y);
					double	fX=x1*Z-movx;
					for(int x=x1;x<x2;x++,d++){
						//int	X=x*Z-movx;
						int	X=fX;
						fX+=Z;
						if(0<=X && X<SMaxX){
							QRgb	S=s[X];
							int		Alpha=qAlpha(S);
							int		rAlpha=255-Alpha;
							QRgb	D=*d;
							*d=qRgba(Clipping((rAlpha*qRed(D)	+Alpha*qRed(S)	)>>8,0,255)
									,Clipping((rAlpha*qGreen(D)	+Alpha*qGreen(S))>>8,0,255)
									,Clipping((rAlpha*qBlue(D)	+Alpha*qBlue(S)	)>>8,0,255)
									,qAlpha(D));
						}
					}
				}
			}
		}
	}
}

//============================================================================

void	FuncCall	ChangePathSeparator(char Dest ,char Src ,char *PathName)
{
	for(char *fp=PathName;*fp!=0;fp++){
		if(*fp==Src){
			*fp=Dest;
		}
	}
}


int64	FuncCall	StrToInt64(char *buff)
{
	char	*cp=buff;
	int64	ret=0;
	int64	sign=1;
	if(*cp=='-'){
		sign=-1;
		cp++;
	}
	else if(*cp=='+'){
		sign=1;
		cp++;
	}
	while('0'<=*cp && *cp<='9'){
		ret =ret*10;
		ret = ret+(*cp-'0');
		cp++;
	}
	return(ret*sign);
}
void	FuncCall	Int64ToStr(int64 m,char *buff)
{
	char	*cp=buff;
	if(m<0){
		*cp='-';
		cp++;
		m=-m;
	}
	int64 n;
	for(n=1;;n=n*10){
		if(n>m){
			n=n/10;
			while(n>0){
				int64	k=m/n;
				*cp='0'+k;
				cp++;
				m=m%n;
				n=n/10;
			}
			*cp=0;
			return;
		}
	}
}
int32	FuncCall	StrToInt32(char *buff)
{
	char	*cp=buff;
	int32	ret=0;
	int32	sign=1;
	if(*cp=='-'){
		sign=-1;
		cp++;
	}
	else if(*cp=='+'){
		sign=1;
		cp++;
	}
	while('0'<=*cp && *cp<='9'){
		ret =ret*10;
		ret = ret+(*cp-'0');
		cp++;
	}
	return(ret*sign);
}

int16	FuncCall	StrToInt16(char *buff)
{
	char	*cp=buff;
	int16	ret=0;
	int16	sign=1;
	if(*cp=='-'){
		sign=-1;
		cp++;
	}
	else if(*cp=='+'){
		sign=1;
		cp++;
	}
	while('0'<=*cp && *cp<='9'){
		ret =ret*10;
		ret = ret+(*cp-'0');
		cp++;
	}
	return(ret*sign);
}
void	FuncCall	Int32ToStr(int32 m,char *buff)
{
	char	*cp=buff;
	if(m<0){
		*cp='-';
		cp++;
		m=-m;
	}
	int32 n;
	for(n=1;;n=n*10){
		if(n>m){
			n=n/10;
			while(n>0){
				int32	k=m/n;
				*cp='0'+k;
				cp++;
				m=m%n;
				n=n/10;
			}
			*cp=0;
			return;
		}
	}
}

void	FuncCall	Int16ToStr(int16 m,char *buff)
{
	char	*cp=buff;
	if(m<0){
		*cp='-';
		cp++;
		m=-m;
	}
	int16 n;
	for(n=1;;n=n*10){
		if(n>m){
			n=n/10;
			while(n>0){
				int16	k=m/n;
				*cp='0'+k;
				cp++;
				m=m%n;
				n=n/10;
			}
			*cp=0;
			return;
		}
	}
}
double	FuncCall	StrToDouble(char *buff)
{
	double	d;
	sscanf(buff,"%lf",&d);
	return(d);
}

QString	FuncCall	QColor2QString(const QColor &c)
{
	if(c.isValid()==true){
		return(QString::number(c.red()) 
			 + QString(",")
			 + QString::number(c.green())
			 + QString(",")
			 + QString::number(c.blue())
			 + QString(",")
			+ QString::number(c.alpha()));
	}
	return QString(/**/"InValid");
}
QColor	FuncCall	QString2QColor(const QString &str)
{
	char	Buff[100];
	if(str==/**/"InValid"){
		return QColor();
	}
	QString2Char(str ,Buff,sizeof(Buff));
	int	r,g,b,a;
	matchscanf(Buff,"%d,%d,%d,%d",&r,&g,&b,&a);
	return(QColor(r,g,b,a));
}

int	FuncCall	HexToByte(char c)
{
	switch(c){
	case '0':	return 0;
	case '1':	return 1;
	case '2':	return 2;
	case '3':	return 3;
	case '4':	return 4;
	case '5':	return 5;
	case '6':	return 6;
	case '7':	return 7;
	case '8':	return 8;
	case '9':	return 9;
	case 'A':	return 10;
	case 'a':	return 10;
	case 'B':	return 11;
	case 'b':	return 11;
	case 'C':	return 12;
	case 'c':	return 12;
	case 'D':	return 13;
	case 'd':	return 13;
	case 'E':	return 14;
	case 'e':	return 14;
	case 'F':	return 15;
	case 'f':	return 15;
	}
	return 0;
}

char	FuncCall	ToHex(int d)
{
	static	const char *TableC="0123456789ABCDEF";
	if(0<=d && d<16)
		return TableC[d];
	return '0';
}

QByteArray	FuncCall	QString2ByteArray(const QString &str)
{
	char	Buff[100000];
	int		Len=sizeof(Buff);
	QByteArray	RetArray;

	QString2Char(str ,Buff,sizeof(Buff));
	char	*fp=Buff;
	DWORD	XByte=HexToByte(*(fp+0))
				 +(HexToByte(*(fp+1))<<4)
				 +(HexToByte(*(fp+2))<<8)
				 +(HexToByte(*(fp+3))<<12)
				 +(HexToByte(*(fp+4))<<16)
				 +(HexToByte(*(fp+5))<<20)
				 +(HexToByte(*(fp+6))<<24)
				 +(HexToByte(*(fp+7))<<28);
	fp+=8;
	Len-=8;
	for(int i=0;i<XByte;i++){
		if(Len<2)
			break;
		BYTE	D =HexToByte(*(fp+0))
				 +(HexToByte(*(fp+1))<<4);
		fp+=2;
		Len-=2;
		RetArray.append((char)D);
	}
	return RetArray;
}
QString		FuncCall	QByteArray2QString(QByteArray &B)
{
	char	Buff[100000];
	int		Len=sizeof(Buff);

	char	*fp=Buff;
	int	XByte=B.count();
	*(fp+0)=ToHex((XByte>>0 )&0x0f);
	*(fp+1)=ToHex((XByte>>4 )&0x0f);
	*(fp+2)=ToHex((XByte>>8 )&0x0f);
	*(fp+3)=ToHex((XByte>>12)&0x0f);
	*(fp+4)=ToHex((XByte>>16)&0x0f);
	*(fp+5)=ToHex((XByte>>20)&0x0f);
	*(fp+6)=ToHex((XByte>>24)&0x0f);
	*(fp+7)=ToHex((XByte>>28)&0x0f);
	fp+=8;
	Len-=8;
	for(int i=0;i<B.count();i++){
		if(Len<2)
			break;
		BYTE	d=B.data()[i];
		*(fp+0)=ToHex((d>>0 )&0x0f);
		*(fp+1)=ToHex((d>>4 )&0x0f);
		fp+=2;
		Len-=2;
	}
	*fp=0;
	return QString(Buff);
}

void	FuncCall	RemoveFiles(const QString &FileNameWithWildcard)
{
	QFileInfo	FInfo(FileNameWithWildcard);
	QString	P=FInfo.path();
	QString	FileName=FInfo.fileName();
	QDir	LDir(P);
	QStringList	files = LDir.entryList(QStringList(FileName),
                                 QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
	for(int i=0;i<files.count();i++){
		QString	F=P+files.value(i);
		QFile::remove(F);
	}
}



qint64	FuncCall	StringToLongLong(char *Str ,bool &Ok)
{
	qint64	Ret=0;
	qint64	Sign=1;
	while(*Str==' ' || *Str=='\t'){
		Str++;
	}
	if(*Str=='-'){
		Sign=-1;
		Str++;
	}
	else if(*Str=='+'){
		Sign=1;
		Str++;
	}
	if(*Str<'0' || '9'<*Str){
		Ok=false;
		return 0;
	}									
	while(*Str!=0 && ('0'<=*Str && *Str<='9')){	//"12345"
		Ret *=10;
		Ret += *Str-'0';
		Str++;
	}
	if(*Str==0){
		Ok=true;
	}
	else{
		Ok=false;
	}
	return Ret*Sign;
}

double	FuncCall	GetRGBBrightness(QRgb a)
{	
	return sqrt((double)qRed(a)*qRed(a) + (double)qGreen(a)*qGreen(a) + (double)qBlue(a)*qBlue(a));	
}


//============================================================================

void	FuncCall	GetObjectPath(QObject * newTarget ,QString &name)
{
	QObject *p=newTarget->parent();
	if(p==NULL){
		name+=newTarget->objectName();
	}
	else{
		name=p->objectName()+name;
		GetObjectPath(p,name);
	}
}

void	FuncCall	GetObjectPath(QObject * newTarget ,QStringList &name)
{
	QWidget	*w=dynamic_cast<QWidget *>(newTarget);

	for(QWidget *m=w;m!=NULL;m=m->parentWidget()){
		QString	ObjName=m->objectName();
		name.append(ObjName);
	}
}

//============================================================================

static	int		BitNumbTable[256];
static	bool	InitialBitNumbTable=false;
static	void	InitialBitCount(void)
{
	if(InitialBitNumbTable==false){
		for(int i=0;i<256;i++){
			int	N=0;
			for(int j=0;j<8;j++){
				if((i&(0x01<<j))!=0){
					N++;
				}
			}
			BitNumbTable[i]=N;
		}
		InitialBitNumbTable=true;
	}
}

int FuncCall	GetBitCount(BYTE *p ,int bytelen)
{
	InitialBitCount();

    int ret=0;
    for(int i=0;i<bytelen;i++){
        ret+=BitNumbTable[*p];
        p++;
        }
    return(ret);
}

int FuncCall	GetBitCount(BYTE p)
{
	InitialBitCount();
	return(BitNumbTable[p]);
}

void    FuncCall	DeleteHair(BYTE **bmpdata ,int xbyte,int YLen)
{
    bool    Flag;
    do{
        Flag=false;
        for(int y=1;y<YLen-1;y++){
            uchar   *p=&bmpdata[y][1];
            uchar   *pp=&bmpdata[y+1][1];
            uchar   *pm=&bmpdata[y-1][1];
            for(int x=1;x<xbyte-2;x++,p++,pp++,pm++){
                uchar   m22;
				if((m22=*p)==0){
                    continue;
				}
                uchar   m11=*(pm-1);
                uchar   m12=*(pm);
                uchar   m13=*(pm+1);
                uchar   m21=*(p-1);
                uchar   m23=*(p+1);
                uchar   m31=*(pp-1);
                uchar   m32=*(pp);
                uchar   m33=*(pp+1);

                if((m22&0x80)!=0){
                    int L=0;
					if((m21&0x01)!=0){
                        L++;
					}
					if((m11&0x01)!=0){
                        L++;
					}
					if((m31&0x01)!=0){
                        L++;
					}
					if((m12&0x80)!=0){
                        L++;
					}
					if((m32&0x80)!=0){
                        L++;
					}
					if((m22&0x40)!=0){
                        L++;
					}
					if((m12&0x40)!=0){
                        L++;
					}
					if((m32&0x40)!=0){
                        L++;
					}
                    if(L<=1){
                        *p &= 0x7F;
                        Flag=true;
                        }
                    }

                uchar   mask=0x40;
                uchar   mask1=0x80;
                uchar   mask2=0x20;
                for(int i=1;i<7;i++){
                    if((m22&mask)!=0){
                        int L=0;
						if((m12&mask1)!=0){
                            L++;
						}
						if((m12&mask)!=0){
                            L++;
						}
						if((m12&mask2)!=0){
                            L++;
						}
						if((m22&mask1)!=0){
                            L++;
						}
						if((m22&mask2)!=0){
                            L++;
						}
						if((m32&mask1)!=0){
                            L++;
						}
						if((m32&mask)!=0){
                            L++;
						}
						if((m32&mask2)!=0){
                            L++;
						}
                        if(L<=1){
                            *p &= (uchar)~mask;
                            Flag=true;
                            }
                        }
                    }
                if((m22&0x01)!=0){
                    int L=0;
					if((m22&0x02)!=0){
                        L++;
					}
					if((m12&0x02)!=0){
                        L++;
					}
					if((m32&0x02)!=0){
                        L++;
					}
					if((m12&0x01)!=0){
                        L++;
					}
					if((m32&0x01)!=0){
                        L++;
					}
					if((m23&0x80)!=0){
                        L++;
					}
					if((m13&0x80)!=0){
                        L++;
					}
					if((m33&0x80)!=0){
                        L++;
					}
                    if(L<=1){
                        *p &= 0xFE;
                        Flag=true;
                        }
                    }
                }
            }
        }while(Flag==true);
}

void    FuncCall	DeleteCornerDot(BYTE **bmpdata ,int xbyte ,int YLen)
{
    for(int y=1;y<YLen-1;y++){
        uchar   *p=&bmpdata[y][1];
        uchar   *pp=&bmpdata[y+1][1];
        uchar   *pm=&bmpdata[y-1][1];
        for(int x=1;x<xbyte-2;x++,p++,pp++,pm++){
            uchar   m22;
            MNext:;
			if((m22=*p)==0){
                continue;
			}
            BYTE    Mask;

            Mask=0x80;
            if((m22&0x80)!=0){
                if((*(p-1)&0x01)!=0){
                    if((*(pm)&0x80)!=0
					|| (*(pp)&0x80)!=0){
                        goto    DelBit;
                    }
				}
                if((*(pm)&0x80)!=0){
					if((m22&0x40)!=0){
                        goto    DelBit;
                    }
				}
                if((m22&0x40)!=0){
					if((*(pp)&0x80)!=0){
                        goto    DelBit;
                    }
                }
			}
            for(int i=1;i<7;i++){
                Mask=0x80>>i;
                BYTE    Mask2=Mask<<1;
                BYTE    Mask3=Mask>>1;
                if((m22&Mask)!=0){
                    if((m22&Mask2)!=0){
                        if((*(pm)&Mask)!=0
						|| (*(pp)&Mask)!=0){
                            goto    DelBit;
                        }
					}
                    if((*(pm)&Mask)!=0){
						if((m22&Mask3)!=0){
                            goto    DelBit;
                        }
					}
                    if((m22&Mask3)!=0){
						if((*(pp)&Mask)!=0){
                            goto    DelBit;
                        }
                    }
                }
			}
            Mask=0x01;
            if((m22&0x01)!=0){
                if((m22&0x02)!=0){
                    if((*(pm)&0x01)!=0
					|| (*(pp)&0x01)!=0){
                        goto    DelBit;
                    }
				}
                if((*(pm)&0x01)!=0){
					if((*(p+1)&0x80)!=0){
                        goto    DelBit;
                    }
				}
                if((*(p+1)&0x80)!=0){
					if((*(pp)&0x01)!=0){
                        goto    DelBit;
                    }
                }
			}
            continue;

            DelBit:;
            *p &= ~Mask;
            goto    MNext;
            }
        }
}

void    FuncCall	DeleteManyArm(BYTE **data,int xbyte ,int YLen)
//—ÖŠsƒhƒbƒg‚Ì‹ß–T‚W“_‚Í‚Q“_ˆÈ‰º‚Å‚È‚¯‚ê‚Î‚È‚ç‚È‚¢
{
    for(int y=1;y<YLen-1;y++){
        BYTE   *p=data[y];
        for(int x=0;x<xbyte;x++,p++){
            BYTE   mask=0x80;
            for(int i=0;i<8;i++,mask>>=1){
				if((*p&mask)==0){
                    continue;
				}
                uchar   D=0;
                int kx=(x<<3)+i;
				if((data[(y-1)][((kx-1)>>3)]&(0x80>>((kx-1)&7)))!=0){
                    D|=0x80;
				}
				if((data[(y-1)][((kx  )>>3)]&(0x80>>((kx  )&7)))!=0){
                    D|=0x40;
				}
				if((data[(y-1)][((kx+1)>>3)]&(0x80>>((kx+1)&7)))!=0){
                    D|=0x20;
				}
				if((data[(y)][ ((kx-1)>>3)]&(0x80>>((kx-1)&7)))!=0){
                    D|=0x10;
				}
				if((data[(y)][ ((kx+1)>>3)]&(0x80>>((kx+1)&7)))!=0){
                    D|=0x08;
				}
				if((data[(y+1)][ ((kx-1)>>3)]&(0x80>>((kx-1)&7)))!=0){
                    D|=0x04;
				}
				if((data[(y+1)][ ((kx  )>>3)]&(0x80>>((kx  )&7)))!=0){
                    D|=0x02;
				}
				if((data[(y+1)][ ((kx+1)>>3)]&(0x80>>((kx+1)&7)))!=0){
                    D|=0x01;
				}
                if(GetBitCount(D)>=3){
                    }
                }
            }
        }
}

static  BYTE    IsolatedDotPattern[]={
 0		//000
		//010
		//000

,1		//000
		//010
		//001

,2		//000
		//010
		//010

,3		//000
		//010
		//011

,4		//000
		//010
		//100

//,5		//000
		//010
		//101

,6		//000
		//010
		//110

,7		//000
		//010
		//111

,8		//000
		//011
		//000

,9		//000
		//011
		//001

,10		//000
		//011
		//010

,11		//000
		//011
		//011

//,12		//000
		//011
		//100

//,13		//000
		//011
		//101

,14		//000
		//011
		//110

,15		//000
		//011
		//111

,16		//000
		//110
		//000

//,17		//000
		//110
		//001

,18		//000
		//110
		//010

//,19		//000
		//110
		//011

,20		//000
		//110
		//100

//,21		//000
		//110
		//101

,22		//000
		//110
		//110

,23		//000
		//110
		//111

//,24		//000
		//111
		//000

//,25		//000
		//111
		//001

,26		//000
		//111
		//010

,27		//000
		//111
		//011

//,28		//000
		//111
		//100

//,29		//000
		//111
		//101

,30		//000
		//111
		//110

,31		//000
		//111
		//111

//,32		//001
		//010
		//000

//,33		//001
		//010
		//001

//,34		//001
		//010
		//010

//,35		//001
		//010
		//011

//,36		//001
		//010
		//100

//,37		//001
		//010
		//101

//,38		//001
		//010
		//110

//,39		//001
		//010
		//111

,40		//001
		//011
		//000

,41		//001
		//011
		//001

,42		//001
		//011
		//010

,43		//001
		//011
		//011

//,44		//001
		//011
		//100

//,45		//001
		//011
		//101

,46		//001
		//011
		//110

,47		//001
		//011
		//111

//,48		//001
		//110
		//000

//,49		//001
		//110
		//001

//,50		//001
		//110
		//010

//,51		//001
		//110
		//011

//,52		//001
		//110
		//100

//,53		//001
		//110
		//101

//,54		//001
		//110
		//110

//,55		//001
		//110
		//111

//,56		//001
		//111
		//000

//,57		//001
		//111
		//001

,58		//001
		//111
		//010

,59		//001
		//111
		//011

//,60		//001
		//111
		//100

//,61		//001
		//111
		//101

,62		//001
		//111
		//110

,63		//001
		//111
		//111

,64		//010
		//010
		//000

//,65		//010
		//010
		//001

//,66		//010
		//010
		//010

//,67		//010
		//010
		//011

//,68		//010
		//010
		//100

//,69		//010
		//010
		//101

//,70		//010
		//010
		//110

//,71		//010
		//010
		//111

,72		//010
		//011
		//000

,73		//010
		//011
		//001

,74		//010
		//011
		//010

,75		//010
		//011
		//011

//,76		//010
		//011
		//100

//,77		//010
		//011
		//101

,78		//010
		//011
		//110

,79		//010
		//011
		//111

,80		//010
		//110
		//000

//,81		//010
		//110
		//001

,82		//010
		//110
		//010

,83		//010
		//110
		//011

,84		//010
		//110
		//100

//,85		//010
		//110
		//101

,86		//010
		//110
		//110

,87		//010
		//110
		//111

,88		//010
		//111
		//000

,89		//010
		//111
		//001

//,90		//010
		//111
		//010

//,91		//010
		//111
		//011

,92		//010
		//111
		//100

,93		//010
		//111
		//101

,94		//010
		//111
		//110

//,95		//010
		//111
		//111

,96		//011
		//010
		//000

//,97		//011
		//010
		//001

//,98		//011
		//010
		//010

//,99		//011
		//010
		//011

//,100		//011
		//010
		//100

//,101		//011
		//010
		//101

//,102		//011
		//010
		//110

//,103		//011
		//010
		//111

,104		//011
		//011
		//000

,105		//011
		//011
		//001

,106		//011
		//011
		//010

,107		//011
		//011
		//011

//,108		//011
		//011
		//100

//,109		//011
		//011
		//101

//,110		//011
		//011
		//110

,111		//011
		//011
		//111

,112		//011
		//110
		//000

//,113		//011
		//110
		//001

//,114		//011
		//110
		//010

,115		//011
		//110
		//011

,116		//011
		//110
		//100

//,117		//011
		//110
		//101

,118		//011
		//110
		//110

,119		//011
		//110
		//111

,120		//011
		//111
		//000

,121		//011
		//111
		//001

//,122		//011
		//111
		//010

//,123		//011
		//111
		//011

,124		//011
		//111
		//100

,125		//011
		//111
		//101

//,126		//011
		//111
		//110

//,127		//011
		//111
		//111

,128		//100
		//010
		//000

//,129		//100
		//010
		//001

//,130		//100
		//010
		//010

//,131		//100
		//010
		//011

//,132		//100
		//010
		//100

//,133		//100
		//010
		//101

//,134		//100
		//010
		//110

//,135		//100
		//010
		//111

//,136		//100
		//011
		//000

//,137		//100
		//011
		//001

//,138		//100
		//011
		//010

//,139		//100
		//011
		//011

//,140		//100
		//011
		//100

//,141		//100
		//011
		//101

//,142		//100
		//011
		//110

//,143		//100
		//011
		//111

,144		//100
		//110
		//000

//,145		//100
		//110
		//001

,146		//100
		//110
		//010

,147		//100
		//110
		//011

,148		//100
		//110
		//100

//,149		//100
		//110
		//101

,150		//100
		//110
		//110

,151		//100
		//110
		//111

//,152		//100
		//111
		//000

//,153		//100
		//111
		//001

//,154		//100
		//111
		//010

,155		//100
		//111
		//011

//,156		//100
		//111
		//100

//,157		//100
		//111
		//101

,158		//100
		//111
		//110

,159		//100
		//111
		//111

//,160		//101
		//010
		//000

//,161		//101
		//010
		//001

//,162		//101
		//010
		//010

//,163		//101
		//010
		//011

//,164		//101
		//010
		//100

//,165		//101
		//010
		//101

//,166		//101
		//010
		//110

//,167		//101
		//010
		//111

//,168		//101
		//011
		//000

//,169		//101
		//011
		//001

//,170		//101
		//011
		//010

//,171		//101
		//011
		//011

//,172		//101
		//011
		//100

//,173		//101
		//011
		//101

//,174		//101
		//011
		//110

//,175		//101
		//011
		//111

//,176		//101
		//110
		//000

//,177		//101
		//110
		//001

//,178		//101
		//110
		//010

//,179		//101
		//110
		//011

//,180		//101
		//110
		//100

//,181		//101
		//110
		//101

//,182		//101
		//110
		//110

//,183		//101
		//110
		//111

//,184		//101
		//111
		//000

//,185		//101
		//111
		//001

,186		//101
		//111
		//010

,187		//101
		//111
		//011

//,188		//101
		//111
		//100

//,189		//101
		//111
		//101

,190		//101
		//111
		//110

,191		//101
		//111
		//111

,192		//110
		//010
		//000

//,193		//110
		//010
		//001

//,194		//110
		//010
		//010

//,195		//110
		//010
		//011

//,196		//110
		//010
		//100

//,197		//110
		//010
		//101

//,198		//110
		//010
		//110

//,199		//110
		//010
		//111

,200		//110
		//011
		//000

,201		//110
		//011
		//001

,202		//110
		//011
		//010

,203		//110
		//011
		//011

//,204		//110
		//011
		//100

//,205		//110
		//011
		//101

,206		//110
		//011
		//110

,207		//110
		//011
		//111

,208		//110
		//110
		//000

//,209		//110
		//110
		//001

,210		//110
		//110
		//010

,211		//110
		//110
		//011

,212		//110
		//110
		//100

//,213		//110
		//110
		//101

,214		//110
		//110
		//110

,215		//110
		//110
		//111

,216		//110
		//111
		//000

,217		//110
		//111
		//001

,218		//110
		//111
		//010

,219		//110
		//111
		//011

,220		//110
		//111
		//100

,221		//110
		//111
		//101

//,222		//110
		//111
		//110

//,223		//110
		//111
		//111

,224		//111
		//010
		//000

//,225		//111
		//010
		//001

//,226		//111
		//010
		//010

//,227		//111
		//010
		//011

//,228		//111
		//010
		//100

//,229		//111
		//010
		//101

//,230		//111
		//010
		//110

//,231		//111
		//010
		//111

,232		//111
		//011
		//000

,233		//111
		//011
		//001

,234		//111
		//011
		//010

,235		//111
		//011
		//011

//,236		//111
		//011
		//100

//,237		//111
		//011
		//101

,238		//111
		//011
		//110

,239		//111
		//011
		//111

,240		//111
		//110
		//000

//,241		//111
		//110
		//001

,242		//111
		//110
		//010

,243		//111
		//110
		//011

,244		//111
		//110
		//100

//,245		//111
		//110
		//101

,246		//111
		//110
		//110

,247		//111
		//110
		//111

,248		//111
		//111
		//000

,249		//111
		//111
		//001

//,250		//111
		//111
		//010

//,251		//111
		//111
		//011

,252		//111
		//111
		//100

,253		//111
		//111
		//101

//,254		//111
		//111
		//110

//,255		//111
		//111
		//111
};

void    FuncCall	DeleteIsolatedDot(BYTE **bmpdata ,int xbyte ,int YLen)
{
    for(int y=1;y<YLen-1;y++){
        uchar   *p=&bmpdata[y][1];
        uchar   *pp=&bmpdata[y+1][1];
        uchar   *pm=&bmpdata[y-1][1];
        for(int x=1;x<xbyte-2;x++,p++,pp++,pm++){
			if(*p==0){
                continue;
			}
            BYTE    Mask;

            if((*p&0x80)!=0){
                Mask= (*(pm-1)<<7) + ((*(pm)>>1)&0x60)
                     +((*(p-1)<<4)&0x10) + ((*p>>3)&0x08)
                     +((*(pp-1)<<2)&0x04) + ((*(pp)>>6)&0x03);
                if(memchr(IsolatedDotPattern,Mask,sizeof(IsolatedDotPattern))!=NULL){
                    *p&=0x7F;
                    }
                }
            for(int i=1;i<7;i++){
                if((*p&(0x80>>i))!=0){
                    Mask=((*(pm)<<(i-1))&0xe0)
                         +(((*(p)<<(i-1))>>3)&0x10) + (((*(p)<<(i+1))>>4)&0x08)
                         +(((*(pp)<<(i-1))&0xe0)>>5);
                    if(memchr(IsolatedDotPattern,Mask,sizeof(IsolatedDotPattern))!=NULL){
                        *p&=~(0x80>>i);
                        }
                    }
                }
            if((*p&0x01)!=0){
                Mask= (*(pm)<<6) + ((*(pm+1)>>2)&0x20)
                     +((*p<<3)&0x10) + ((*(p+1)>>4)&0x08)
                     +((*pp<<1)&0x06) + ((*(pp+1)>>7)&0x01);
                if(memchr(IsolatedDotPattern,Mask,sizeof(IsolatedDotPattern))!=NULL){
                    *p&=0xFE;
                    }
                }
            }
        }
}

