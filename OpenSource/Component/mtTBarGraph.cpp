/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtTBarGraph.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QtGui>
#define	_USE_MATH_DEFINES
#include <math.h>

#include"mtTBarGraph.h"
#include"mtMeter.h"
#include "swap.h"

mtTBarGraph::mtTBarGraph(QWidget *parent)
    : mtWidgetPosition(parent)
{
	FBarColor=Qt::red;
	FMaxWidth=256;
	FMaxValue=256;
	FMovx=0;
	FMovy=0;
	FZoomRateX=1.0;
	FZoomRateY=1.0;

	VData=NULL;
	AllocatedNumb=0;
	LastX=0;
	LastY=0;
	RectMode=false;
	MeterLeft=NULL;
	MeterBottom=NULL;

	AllocData();
	resize(256, 256);
	connect(this,SIGNAL(SignalChanged(void))	,this,SLOT(SlotChanged(void)));
}

mtTBarGraph::~mtTBarGraph()
{
	disconnect(this,SLOT(SlotChanged(void)));
	if(VData!=NULL){
		delete	[]VData;
		VData=NULL;
	}
}

void	mtTBarGraph::SetMeter(mtMeter *mBottom,mtMeter *mLeft)
{
	MeterBottom	=mBottom;
	MeterLeft	=mLeft;

	if(MeterBottom!=NULL){
		MeterBottom->SetDrawMode(mtMeter::mtHorizUpper);
	}
	if(MeterLeft!=NULL){
		MeterLeft->SetDrawMode(mtMeter::mtVertRightReverse);
	}
}

void	mtTBarGraph::SetMeter(void)
{
	if(MeterBottom!=NULL){
		MeterBottom->SetZoomRate(FZoomRateX);
		MeterBottom->SetLeftPosition(FMovx);
	}
	if(MeterLeft!=NULL){
		MeterLeft->SetZoomRate(FZoomRateY);
		MeterLeft->SetLeftPosition(FMovy);
	}
}


void	mtTBarGraph::AllocData(void)
{
	int	*D=new int[FMaxWidth];
	int	i;
	for(i=0;i<FMaxWidth && i<AllocatedNumb;i++){
		D[i]=VData[i];
	}
	for(;i<FMaxWidth;i++){
		D[i]=FMaxValue/2;
	}
	AllocatedNumb=FMaxWidth;

	if(VData!=NULL){
		delete	[]VData;
	}
	VData=D;
}

void	mtTBarGraph::SetBarColor(const QColor &c)
{
	FBarColor=c;
	repaint(0,0,width()-1,height()-1);
}
void	mtTBarGraph::SetMaxWidth(int c)
{
	FMaxWidth=c;
	AllocData();
	repaint(0,0,width()-1,height()-1);
}
void	mtTBarGraph::SetMaxValue(int c)
{
	FMaxValue=c;
	for(int i=0;i<AllocatedNumb;i++){
		if(VData[i]>FMaxValue){
			VData[i]=FMaxValue;
		}
	}
	repaint(0,0,width()-1,height()-1);
}

void	mtTBarGraph::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	Pnt.setBrush(QBrush(FBarColor));
    Pnt.setPen(FBarColor);

	for(int i=0;i<AllocatedNumb;i++){
		int	x1=(int)((i-FMovx)*FZoomRateX);
		int	x2=(int)((i-FMovx+1)*FZoomRateX);
		int	y1=(int)((0-FMovy)*FZoomRateY);
		int	y2=(int)((VData[i]-FMovy)*FZoomRateY);
	
		if(x2<0 || width()<=x1
		|| y2<0 || height()<=y1){
			continue;
		}
		
		Pnt.drawRect(x1,height()-y2,x2-x1,y2-y1);
	}
	Pnt.setPen(Qt::black);
	for(int i=0;i<AllocatedNumb;i++){
		int	x1=(int)((i-FMovx)*FZoomRateX);
		int	x2=(int)((i-FMovx+1)*FZoomRateX);
		int	y1=(int)((0-FMovy)*FZoomRateY);
		int	y2=(int)((VData[i]-FMovy)*FZoomRateY);
	
		if(x2<0 || width()<=x1
		|| y2<0 || height()<=y1){
			continue;
		}
		if(FZoomRateX<=0.5){
			if((i%50)==0){
				Pnt.drawLine(x1,height()-y2,x1,height()-y1);
			}
		}
		else
		if(FZoomRateX<=2.0){
			if((i%10)==0){
				Pnt.drawLine(x1,height()-y2,x1,height()-y1);
			}
		}
		else
		if(FZoomRateX<=5.0){
			if((i%5)==0){
				Pnt.drawLine(x1,height()-y2,x1,height()-y1);
			}
		}
		else
		if(FZoomRateX<=10.0){
			Pnt.drawLine(x1,height()-y2,x1,height()-y1);
		}
		Pnt.drawLine(x1,height()-y2,x2,height()-y2);
	}
	if(RectMode==true){
		Pnt.setPen(Qt::green);
		Pnt.drawLine(RectX1,RectY1 ,RectX2,RectY1);
		Pnt.drawLine(RectX2,RectY1 ,RectX2,RectY2);
		Pnt.drawLine(RectX2,RectY2 ,RectX1,RectY2);
		Pnt.drawLine(RectX1,RectY2 ,RectX1,RectY1);
	}
}
void	mtTBarGraph::mousePressEvent ( QMouseEvent *Ev )
{
	int	X=Ev->x();
	int	Y=Ev->y();
    if((Ev->buttons()&Qt::LeftButton)!=0){
		LastX=X;
		LastY=Y;
		SetPoint(X,Y);
		RectMode=false;
		repaint(0,0,width()-1,height()-1);
		emit SignalChanged();
	}
	else
    if((Ev->buttons()&Qt::RightButton)!=0){
		RectMode=true;
		RectX1=X;
		RectY1=Y;
		RectX2=X;
		RectY2=Y;
		repaint(0,0,width()-1,height()-1);
	}
	else{
		RectMode=false;
	}
}
void	mtTBarGraph::mouseMoveEvent ( QMouseEvent *Ev )
{
	int	X=Ev->x();
	int	Y=Ev->y();
	if((Ev->buttons()&Qt::LeftButton)!=0){
		if(LastX<X){
			for(int x=LastX;x<=X;x++){
				int	y=(Y-LastY)/(X-LastX)*(x-LastX)+LastY;
				SetPoint(x,y);
			}
			LastX=X;
			LastY=Y;
			repaint(0,0,width()-1,height()-1);
			emit SignalChanged();
		}
		else
		if(X<LastX){
			for(int x=X;x<=LastX;x++){
				int	y=(LastY-Y)/(LastX-X)*(x-X)+Y;
				SetPoint(x,y);
			}
			LastX=X;
			LastY=Y;
			repaint(0,0,width()-1,height()-1);
			emit SignalChanged();
		}	
	}
	else
    if((Ev->buttons()&Qt::RightButton)!=0){
		RectX2=X;
		RectY2=Y;
		repaint(0,0,width()-1,height()-1);
	}
}
void	mtTBarGraph::mouseReleaseEvent ( QMouseEvent * Ev)
{
	if(RectMode==true){
		RectMode=false;
		if(RectX1<RectX2){
			FMovx=min(RectX1,RectX2)/FZoomRateX+FMovx;
			FMovy=min(height()-RectY1,height()-RectY2)/FZoomRateY+FMovy;
			int	dw=diff(RectX1,RectX2)/FZoomRateX;
			FZoomRateX=(double)width()/(double)dw;
			int	dh=diff(RectY1,RectY2)/FZoomRateY;
			FZoomRateY=(double)height()/(double)dh;
			repaint(0,0,width()-1,height()-1);
			SetMeter();
		}
		else{
			FMovx=FMovy=0;
			FZoomRateX=(double)width() /(double)FMaxWidth;
			FZoomRateY=(double)height()/(double)FMaxValue;
			repaint(0,0,width()-1,height()-1);
			SetMeter();
		}
	}
}

void	mtTBarGraph::resizeEvent ( QResizeEvent * event )
{
	FZoomRateX=(double)width() /(double)FMaxWidth;
	FZoomRateY=(double)height()/(double)FMaxValue;
	repaint(0,0,width()-1,height()-1);
	SetMeter();
}


void	mtTBarGraph::SetPoint(int rx ,int ry)
{
	int	x=rx/FZoomRateX+FMovx;
	int	y=(height()-ry)/FZoomRateY+FMovy;
	if(0<=x && x<AllocatedNumb && 0<=y && y<FMaxValue){
		VData[x]=y;
	}
}

int		mtTBarGraph::GetYData(int x)
{
	if(0<=x && x<AllocatedNumb){
		return(VData[x]);
	}
	return(0);
}

void	mtTBarGraph::SetYData(int x ,int ydata)
{
	VData[x]=ydata;
	repaint(0,0,width()-1,height()-1);
}

void	mtTBarGraph::SlotChanged(void)
{
}


bool	mtTBarGraph::Save(QIODevice *f)
{
	if(f->write((const char *)&FMaxWidth,sizeof(FMaxWidth))!=sizeof(FMaxWidth)){
		return(false);
	}
	if(f->write((const char *)VData,sizeof(VData[0])*FMaxWidth)!=sizeof(VData[0])*FMaxWidth){
		return(false);
	}
	return(true);
}
bool	mtTBarGraph::Load(QIODevice *f)
{
	int	iFMaxWidth;
	if(f->read((char *)&iFMaxWidth,sizeof(FMaxWidth))!=sizeof(FMaxWidth)){
		return(false);
	}
	if(iFMaxWidth!=FMaxWidth){
		FMaxWidth=iFMaxWidth;
		AllocData();
	}
	if(f->read((char *)VData,sizeof(VData[0])*FMaxWidth)!=sizeof(VData[0])*FMaxWidth){
		return(false);
	}
	FZoomRateX=(double)width() /(double)FMaxWidth;
	FZoomRateY=(double)height()/(double)FMaxValue;
	FMovx=0;
	FMovy=0;
	repaint(0,0,width()-1,height()-1);
	return(true);
}
