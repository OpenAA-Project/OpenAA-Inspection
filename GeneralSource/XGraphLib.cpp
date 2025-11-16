/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGraphLib.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/

#include "Regulus64Version.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include "XGrobalData.h"
#include "XGraphLib.h"
#include "XDataInLayer.h"


MakeBitmapDataInPage::MakeBitmapDataInPage(void)
{
	BuffLayer=NULL;
	Parent	=NULL;
}

void    MakeBitmapDataInPage::SetMaster(void)
{
    BuffLayer=&Layers.GetLayer(Parent->LayerNumb)->PageData[Page].MasterBuff;
}
void    MakeBitmapDataInPage::SetLoaded(void)
{
    BuffLayer=&Layers.GetLayer(Parent->LayerNumb)->PageData[Page].LoadedBuff;
}

MakeBitmapDataInLayer::MakeBitmapDataInLayer(void)
{
	BuffPage		=NULL;
	BuffLayerAttr	=NULL;
}
void	MakeBitmapDataInLayer::Set(int _MaxPages)
{
	MaxPages	=_MaxPages;
    BuffPage	=new MakeBitmapDataInPage[MaxPages];
	for(int page=0;page<MaxPages;page++){
		BuffPage[page].Parent=this;
		BuffPage[page].Page=page;
	}
}

MakeBitmapDataInLayer::~MakeBitmapDataInLayer(void)
{
	delete	[]BuffPage;
}

void    MakeBitmapDataInLayer::SetMaster(void)
{
	for(int page=0;page<MaxPages;page++){
        BuffPage[page].SetMaster();
        }
    BuffLayerAttr=&Layers.GetLayer(LayerNumb)->DataInLayerAttr;
}
void    MakeBitmapDataInLayer::SetLoaded(void)
{
	for(int page=0;page<MaxPages;page++){
        BuffPage[page].SetLoaded();
        }
    BuffLayerAttr=&Layers.GetLayer(LayerNumb)->DataInLayerAttr;
}

MakeBitmapData::MakeBitmapData(int MaxLayer ,int MaxPages)
{
	GBuff=new MakeBitmapDataInLayer[MaxLayer];
	BuffLayerNumb=MaxLayer;
	for(int L=0;L<MaxLayer;L++){
		GBuff[L].Set(MaxPages);
		GBuff[L].LayerNumb=L;
	}
}
MakeBitmapData::~MakeBitmapData(void)
{
	delete	[]GBuff;
}

void    MakeBitmapData::SetMaster(void)
{
	for(int L=0;L<BuffLayerNumb;L++){
		GBuff[L].SetMaster();
	}
}
void    MakeBitmapData::SetLoaded(void)
{
	for(int L=0;L<BuffLayerNumb;L++){
		GBuff[L].SetLoaded();
	}
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    Data
//    DataNumb
//    bitmapx
//    bitmapy
//    movx
//    movy
//    ZoomRate
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/

struct	XXLineData
{
	int		x1,x2;
	bool	Enabled;
};

void	MakeBitmap(QImage *m ,MakeBitmapData &Data
                  ,int bitmapx ,int bitmapy
                  ,int movx ,int movy ,double ZoomRate)
{
    if(ZoomRate==0.0)
        return;

    double  Z=1.0/ZoomRate;

	QRect	RectBuff[100];
	int		RectBuffNumb=0;

	for(int page=0;page<Data.GBuff[0].MaxPages;page++){
		MakeBitmapDataInPage	*DL0=&Data.GBuff[0].BuffPage[page];
		int LX1=ceil ((DL0->OutlineOffsetX+movx)*ZoomRate);
		int LY1=ceil ((DL0->OutlineOffsetY+movy)*ZoomRate);
		int LX2=floor((DL0->OutlineOffsetX+DL0->BuffLayer->MaxX+movx)*ZoomRate);
		int LY2=floor((DL0->OutlineOffsetY+DL0->BuffLayer->MaxY+movy)*ZoomRate);
		if(LX2<0 || bitmapx<=LX1 || LY2<0 || bitmapy<=LY1)
			continue;
		RectBuff[RectBuffNumb]=QRect(LX1,LY1,LX2-LX1,LY2-LY1);
		RectBuffNumb++;

		int	bmpX1=(LX1>0)?LX1:0;
		int	bmpY1=(LY1>0)?LY1:0;
		int	bmpX2=(LX2<bitmapx)?LX2:bitmapx;
		int	bmpY2=(LY2<bitmapy)?LY2:bitmapy;

		int		XPoint[2048];
		for(int x=0;x<sizeof(XPoint)/sizeof(XPoint[0]);x++){
			XPoint[x]=-1;
		}
		for(int x=bmpX1;x<bmpX2;x++){
			int	X=x*Z-movx;
			if(0<=X && X<Sikii::DotPerLine)
				XPoint[x]=X;
		}

		for(int y=bmpY1;y<bmpY2;y++){
			int	Y=y*Z-movy;
			if(DL0->BuffLayer->MaxY>Y){
				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=bmpX1;
				if(Data.BuffLayerNumb==1){
					BYTE	*src1=DL0->BuffLayer->GetY(Y);
					BYTE	*br =Data.GBuff[0].ColTable;
					for(int x=bmpX1;x<bmpX2;x++,dst++){
						int	c=br[src1[XPoint[x]]];
						*dst=qRgb(c,c,c);
					}
				}
				else
				if(Data.BuffLayerNumb==2){
					BYTE	*src1=DL0->BuffLayer->GetY(Y);
					BYTE	*src2=Data.GBuff[1].BuffPage[page].BuffLayer->GetY(Y);
					BYTE	*br1 =Data.GBuff[0].ColTable;
					BYTE	*br2 =Data.GBuff[1].ColTable;
					for(int x=bmpX1;x<bmpX2;x++,dst++){
						int	c1=br1[src1[XPoint[x]]];
						int	c2=br2[src2[XPoint[x]]];
						*dst=qRgb(c1,c2,c1);
					}
				}
				else
				if(Data.BuffLayerNumb>=3){
					BYTE	*src1=DL0->BuffLayer->GetY(Y);
					BYTE	*src2=Data.GBuff[1].BuffPage[page].BuffLayer->GetY(Y);
					BYTE	*src3=Data.GBuff[2].BuffPage[page].BuffLayer->GetY(Y);
					BYTE	*br1 =Data.GBuff[0].ColTable;
					BYTE	*br2 =Data.GBuff[1].ColTable;
					BYTE	*br3 =Data.GBuff[2].ColTable;
					for(int x=bmpX1;x<bmpX2;x++,dst++){
						int	c1=br1[src1[XPoint[x]]];
						int	c2=br2[src2[XPoint[x]]];
						int	c3=br3[src3[XPoint[x]]];
						*dst=qRgb(c1,c2,c3);
					}
				}
			}
			else{
				QRgb *dst=(QRgb *)m->scanLine(y);
				dst+=bmpX1;
				if(Data.BuffLayerNumb==1){
					BYTE	*br =Data.GBuff[0].ColTable;
					for(int x=bmpX1;x<bmpX2;x++,dst++){
						int	c=br[0];
						*dst=qRgb(c,c,c);
					}
				}
				else
				if(Data.BuffLayerNumb==2){
					BYTE	*br1 =Data.GBuff[0].ColTable;
					BYTE	*br2 =Data.GBuff[1].ColTable;
					for(int x=bmpX1;x<bmpX2;x++,dst++){
						int	c1=br1[0];
						int	c2=br2[0];
						*dst=qRgb(c1,c2,c1);
					}
				}
				else
				if(Data.BuffLayerNumb>=3){
					BYTE	*br1 =Data.GBuff[0].ColTable;
					BYTE	*br2 =Data.GBuff[1].ColTable;
					BYTE	*br3 =Data.GBuff[2].ColTable;
					for(int x=bmpX1;x<bmpX2;x++,dst++){
						int	c1=br1[0];
						int	c2=br2[1];
						int	c3=br3[2];
						*dst=qRgb(c1,c2,c3);
					}
				}
			}
		}
	}

	XXLineData	DData[sizeof(RectBuff)/sizeof(RectBuff[0])];
	int			DDataNumb=0;
	for(int y=0;y<bitmapy;y++){
		DData[0].x1=0;
		DData[0].x2=bitmapx;
		DData[0].Enabled=true;
		DDataNumb=1;
		for(int i=0;i<RectBuffNumb;i++){
			if(RectBuff[i].top()<=y && y<=RectBuff[i].bottom()){
				for(int j=0;j<DDataNumb;j++){
					if(DData[j].Enabled==true && DData[j].x1<=RectBuff[i].left() && RectBuff[i].left()<DData[j].x2){
						if(DData[j].x1<=RectBuff[i].right() && RectBuff[i].right()<DData[j].x2){
							DData[DDataNumb].x2=DData[j].x2;
							DData[j].x2=RectBuff[i].left();
							DData[DDataNumb].x1=RectBuff[i].right()+1;
							DData[DDataNumb].Enabled=true;
							if(DData[j].x1>=DData[j].x2)
								DData[j].Enabled=false;
							if(DData[DDataNumb].x1<DData[DDataNumb].x2)
								DDataNumb++;
						}
						else{
							DData[j].x2=RectBuff[i].left();
							if(DData[j].x1>=DData[j].x2)
								DData[j].Enabled=false;
						}
					}
					else if(DData[j].Enabled==true && RectBuff[i].left()<=DData[j].x1 && DData[j].x1<RectBuff[i].right()){
						if(RectBuff[i].right()<DData[j].x2){
							DData[j].x1=RectBuff[i].right()+1;
							if(DData[j].x1>=DData[j].x2)
								DData[j].Enabled=false;
						}
						else{
							DData[j].Enabled=false;
						}
					}
				}
			}
		}
		QRgb *dst=(QRgb *)m->scanLine(y);
		for(int j=0;j<DDataNumb;j++){
			if(DData[j].Enabled==true){
				for(int x=DData[j].x1;x<DData[j].x2;x++){
					dst[x]=qRgb(0,0,0);
				}
			}
		}
	}
}

void	DrawLine(QImage *m ,QRgb c ,int x1, int y1 ,int x2 ,int y2)
{
	int	dx=x2-x1;
	int	dy=y2-y1;

	if(dx>0 && dx>=abs(dy)){
		for(int i=0;i<=dx;i++){
			int	x=x1+i;
			int	y=y1+i*dy/dx;
			if(0<=x && x<m->width() && 0<=y && y<m->height())
				m->setPixel(x1+i,y1+i*dy/dx,c);
		}
	}
	else
	if(dy>0 && dy>=abs(dx)){
		for(int i=0;i<=dy;i++){
			int	x=x1+i*dx/dy;
			int	y=y1+i;
			if(0<=x && x<m->width() && 0<=y && y<m->height())
				m->setPixel(x1+i*dx/dy,y1+i,c);
		}
	}
	else
	if(dx<0 && (-dx)>=abs(dy)){
		for(int i=0;i>=dx;i--){
			int	x=x1+i;
			int	y=y1+i*dy/dx;
			if(0<=x && x<m->width() && 0<=y && y<m->height())
			m->setPixel(x1+i,y1+i*dy/dx,c);
		}
	}
	else
	if(dy<0 && (-dy)>=abs(dx)){
		for(int i=0;i>=dy;i--){
			int	x=x1+i*dx/dy;
			int	y=y1+i;
			if(0<=x && x<m->width() && 0<=y && y<m->height())
			m->setPixel(x1+i*dx/dy,y1+i,c);
		}
	}
	else{
		if(0<=x1 && x1<m->width() && 0<=y1 && y1<m->height())
			m->setPixel(x1,y1,c);
	}
}

bool  CheckZoomRate(double ZoomRate)
{
    if(ZoomRate<1.0e6)
        return(true);
    return(false);
}

bool  RCheckZoomRate(double ZoomRate)
{
    if(1.0e-6<ZoomRate)
        return(true);
    return(false);
}

void	DrawBitArea(BYTE **Area ,int XLen, int XByte ,int YLen
					,QImage *canvas,QRgb c
					,int bitmapx ,int bitmapy
					,int movx ,int movy ,double ZoomRate
					,int OffsetX ,int OffsetY)
{
    if(ZoomRate==0.0)
        return;

    double  Z=1.0/ZoomRate;

	int LX1=ceil((OffsetX+movx)*ZoomRate);
	int LY1=ceil((OffsetY+movy)*ZoomRate);
	int LX2=floor((OffsetX+Sikii::DotPerLine+movx)*ZoomRate);
	int LY2=floor((OffsetY+Sikii::MaxLines  +movy)*ZoomRate);
	if(LX2<0 || bitmapx<=LX1 || LY2<0 || bitmapy<=LY1)
		return;
	int	bmpX1=(LX1>0)?LX1:0;
	int	bmpY1=(LY1>0)?LY1:0;
	int	bmpX2=(LX2<bitmapx)?LX2:bitmapx;
	int	bmpY2=(LY2<bitmapy)?LY2:bitmapy;

	int		XPoint[2048];
	BYTE	XShift[2048];
	for(int x=bmpX1;x<bmpX2;x++){
		int	X=x*Z-movx;
		if(0<=X && X<Sikii::DotPerLine){
			XPoint[x]=X>>3;
			XShift[x]=(0x80>>(X&7));
		}
		else{
			XPoint[x]=-1;
			XShift[x]=0;
		}
	}
	for(int y=bmpY1;y<bmpY2;y++){
		int	Y=y*Z-movy;
		QRgb *dst=(QRgb *)canvas->scanLine(y);
		dst+=bmpX1;
		BYTE	*src1=Area[Y];
		for(int x=bmpX1;x<bmpX2;x++,dst++){
			if((src1[XPoint[x]]&XShift[x])!=0)
				*dst=c;
		}
	}
}
