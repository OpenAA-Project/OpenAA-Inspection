/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtGraph.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include <QtGui>
//#include <math.h>
#include <QPainter>
#include <stdlib.h>
#include "mtGraph.h"
#include "mtLineGraph.h"
#include "XBsearch.h"
#include "swap.h"

mtGraph::mtGraph()
{
	//Init
	Sorted		=false;
//	STypeFlag	=false;
	wuGraphMinX	=wuGraphMaxX	="NULL";
	wuGraphMinY	=wuGraphMaxY	="NULL";
	LineColor=QColor(Qt::black);
	LineWidth=0;
	LineStyle=Qt::SolidLine;
	MClickFlag	=false;
	ParentGraph=NULL;

	OffsetX=OffsetY=0;
}

mtGraph::~mtGraph()
{
}

void	mtGraph::SetLineColor(QColor Color)
{
	LineColor=Color;
}

QColor	mtGraph::GetLineColor()
{
	return LineColor;
}

void	mtGraph::SetLineWidth(int W)
{
	LineWidth=W;
}

int		mtGraph::GetLineWidth()
{
	return LineWidth;
}

void	mtGraph::SetLineStyle(Qt::PenStyle Style)
{
	LineStyle=Style;
}

Qt::PenStyle	mtGraph::GetLineStyle()
{
	return LineStyle;
}

double	mtGraph::_GetXValue(double Y)
{
	return 0;
}

double	mtGraph::_GetYValue(double X)
{
	if(X<XValue.at(0)){
		return 0;
	}
	for(int i=1;i<XValue.count();i++){
		if(X<=XValue.at(i)){
			return (X*(YValue.at(i-1)-YValue.at(i)))/(XValue.at(i-1)-XValue.at(i))+(XValue.at(i-1)*YValue.at(i)-XValue.at(i)*YValue.at(i-1))/(XValue.at(i-1)-XValue.at(i));
		}
	}
	return 0;
}

double	mtGraph::GetPointX(int X)
{
	return XValue.at(X);
}

double	mtGraph::GetPointY(int Y)
{
	return YValue.at(Y);
}

int		mtGraph::GetPointCount()
{
	return XValue.count();
}

void	mtGraph::AddXY(double X,double Y)
{
	XValue << X;
	YValue << Y;
	if(GetParent()->OnSorted){
		GetParent()->OnSorted=Sorted=GetParent()->OnSTypeFlag=false;
	}
}

void	mtGraph::AddX(double X)
{
	if(XValue.contains(X)){
		YValue.replace(XValue.indexOf(X),YValue.at(XValue.indexOf(X))+1);
	}
	else{
		XValue << X;
		YValue << 1;
	}
	if(GetParent()->OnSorted){
		GetParent()->OnSorted=Sorted=GetParent()->OnSTypeFlag=false;
	}
}

void	mtGraph::SubXY(int idx)
{
	XValue.removeAt(idx);
	YValue.removeAt(idx);
	if(GetParent()->OnSorted){
		GetParent()->OnSorted=Sorted=GetParent()->OnSTypeFlag=false;
	}
}

double	mtGraph::GetAverageY()
{
	double SumYValue=0;
	for(int i=0;i<YValue.count();i++){
		SumYValue+=YValue.at(i);
	}
	return SumYValue/YValue.count();
}

void	mtGraph::DeleteXY()
{
	XValue.clear();
	YValue.clear();
	if(ParentGraph!=NULL){
		GetParent()->OnSorted=Sorted=GetParent()->OnSTypeFlag=false;
	}
}

void	mtGraph::ReplaceXY(double X,double Y)
{
	if(XValue.contains(X)){
		YValue.replace(XValue.indexOf(X),Y);
	}
//	if(GetParent()->OnSorted)
//		GetParent()->OnSorted=Sorted=GetParent()->OnSTypeFlag=false;
}
/*
void	mtGraph::SetuMinY(double MinY)
{
	wuGraphMinY=uGraphMinY=uMinY=MinY;
	GetParent()->OnSTypeFlag=false;
}

void	mtGraph::SetuMaxY(double MaxY)
{
	wuGraphMaxY=uGraphMaxY=uMaxY=MaxY;
	GetParent()->OnSTypeFlag=false;
}
*/

struct XValueStruct
{
	double	XValue;
	double	YValue;
	int		n;
};

static	int	XValueStructFunc(const void *a ,const void *b)
{
	struct XValueStruct	*pa=(struct XValueStruct *)a;
	struct XValueStruct	*pb=(struct XValueStruct *)b;
	if(pa->XValue<pb->XValue)
		return -1;
	if(pa->XValue>pb->XValue)
		return 1;
	return 0;
}

void*	mtGraph::SortXY()
{
	int	N=XValue.count();
	if(N==0){
		return NULL;
	}

	struct XValueStruct		WDim[10000];
	struct XValueStruct		*W=WDim;
	if(N>sizeof(WDim)/sizeof(WDim[0])){
		W=new struct XValueStruct[N];
	}
	for(int i=0;i<N;i++){
		W[i].n=0;
		W[i].XValue=XValue.at(i);
		W[i].YValue=YValue.at(i);
	}
	qsort(W,N,sizeof(struct XValueStruct),XValueStructFunc);
	uMinY=uMaxY=YValue.at(0);
	for(int i=0;i<N;i++){
		XValue.replace(i,W[i].XValue);
		YValue.replace(i,W[i].YValue);
		uMinY=min(uMinY,W[i].YValue);
		uMaxY=max(uMaxY,W[i].YValue);
	}
	uMinX=XValue.at(0);							//X軸値の最小値を取得
	uMaxX=XValue.at(XValue.count()-1);			//X軸値の最大値を取得

	if(W!=WDim){
		delete	[]W;
	}


	//QList<int>		wXValue;		//ソートインデックスの退避
	//QList<double>	wYValue;		//Y軸値の退避
	//wXValue.clear();
	//for(int i=0;i<XValue.count();i++){
	//	wXValue << i;
	//}
	//for(int i=0;i<XValue.count()-1;i++){
	//	for(int j=i+1;j<XValue.count();j++){
	//		if(XValue.at(i)>XValue.at(j)){
	//			XValue.swap(i,j);		//X軸値のソート
	//			wXValue.swap(i,j);
	//		}
	//	}
	//}
	//wYValue=YValue;
	//for(int i=0;i<YValue.count();i++){
	//	YValue.replace(i,wYValue.at(wXValue.at(i)));		//Y軸値のソート
	//}
	//
	//qSort(wYValue.begin(),wYValue.end());
	//
	//uMinX=XValue.at(0);							//X軸値の最小値を取得
	//uMaxX=XValue.at(XValue.count()-1);			//X軸値の最大値を取得
	//uMinY=wYValue.at(0);						//Y軸値の最小値を取得
	//uMaxY=wYValue.at(wYValue.count()-1);		//Y軸値の最大値を取得
	//
	//wYValue.clear();
	Sorted=true;
	return &XValue;
}

//void	mtGraph::DrawPaint(QPainter &Pnt)
//{
//}

//データ座標(ux,uy)を画面座標(gx,gy)に変換する
void	mtGraph::gGetUniverseToCanvas(double ux,double uy,int &gx,int &gy)
{
	if(GetParent()->STypeX==GetParent()->mtConstant){
		GetUniverseToCanvasX(ux,gx);
		if(GetParent()->STypeY==GetParent()->mtConstant){
			GetUniverseToCanvasY(uy,gy);
		}
		else if(GetParent()->STypeY==GetParent()->mtLog){
			GetUniverseToCanvasLogY(uy,gy);
		}
	}
	else if(GetParent()->STypeX==GetParent()->mtLog){
		GetUniverseToCanvasLogX(ux,gx);
		if(GetParent()->STypeY==GetParent()->mtConstant){
			GetUniverseToCanvasY(uy,gy);
		}
		else if(GetParent()->STypeY==GetParent()->mtLog){
			GetUniverseToCanvasLogY(uy,gy);
		}
	}
}

//データ座標(ux,uy)を画面座標(gx,gy)に変換する
void	mtGraph::GetUniverseToCanvas(double ux,double uy,int &gx,int &gy)
{
	gx=GetParent()->OffsetX+(ux-GetParent()->uGraphMinX)*((GetParent()->width()-GetParent()->OffsetX)/GetParent()->uWidth);
	gy=(GetParent()->uGraphMaxY-uy)*((GetParent()->height()-GetParent()->OffsetY)/GetParent()->uHeight);
}

//データ座標のX座標(ux)を画面座標のX座標(gx)に変換する
void	mtGraph::GetUniverseToCanvasX(double ux,int &gx)
{
	gx=GetParent()->OffsetX+(ux-GetParent()->uGraphMinX)*((GetParent()->width()-GetParent()->OffsetX)/GetParent()->uWidth);
}

//データ座標のY座標(uy)を画面座標のY座標(gy)に変換する
void	mtGraph::GetUniverseToCanvasY(double uy,int &gy)
{
	gy=(GetParent()->uGraphMaxY-uy)*((GetParent()->height()-GetParent()->OffsetY)/GetParent()->uHeight);
}

//データ座標(ux,uy)を画面座標(gx,gy)に変換する（対数表示）
void	mtGraph::GetUniverseToCanvasLog(double ux,double uy,int &gx,int &gy)
{
	if(ux>0.0){
		gx=GetParent()->OffsetX+((GetParent()->width()-GetParent()->OffsetX)/GetParent()->uLogXDbl)*(log10(ux)+1);
	}
	else{
		gx=GetParent()->OffsetX+((GetParent()->width()-GetParent()->OffsetX)/GetParent()->uLogXDbl);
	}
	if(uy>0.0){
		gy=GetParent()->height()-GetParent()->OffsetY-((GetParent()->height()-GetParent()->OffsetY)/GetParent()->uLogYDbl)*(log10(uy)+1);
	}
	else{
		gy=GetParent()->height()-GetParent()->OffsetY-((GetParent()->height()-GetParent()->OffsetY)/GetParent()->uLogYDbl);
	}
}

//データ座標のX座標(ux)を画面座標のX座標(gx)に変換する（対数表示）
void	mtGraph::GetUniverseToCanvasLogX(double ux,int &gx)
{
	if(ux>0.0){
		gx=GetParent()->OffsetX+((GetParent()->width()-GetParent()->OffsetX)/GetParent()->uLogXDbl)*(log10(ux)+1);
	}
	else{
		gx=GetParent()->OffsetX+((GetParent()->width()-GetParent()->OffsetX)/GetParent()->uLogXDbl);
	}
}

//データ座標のY座標(uy)を画面座標のY座標(gy)に変換する（対数表示）
void	mtGraph::GetUniverseToCanvasLogY(double uy,int &gy)
{
	if(uy<=0.0){
		gy=GetParent()->height()-GetParent()->OffsetY;
	}
	else{
		gy=GetParent()->height()-GetParent()->OffsetY-((GetParent()->height()-GetParent()->OffsetY)/GetParent()->uLogYDbl)*(log10(uy)+1);
	}
}

mtGLine::mtGLine(QWidget *parent)
{
}

mtGLine::~mtGLine()
{
}

void	mtGLine::DrawPaint(QPainter &Pnt)
{
	int gX1,gY1,gX2,gY2;
	Pnt.setPen(QPen(GetLineColor(),GetLineWidth(),GetLineStyle()));
	if(XValue.count()==0){
		return;
	}
	gGetUniverseToCanvas(XValue.at(0),YValue.at(0),gX1,gY1);
	for(int Count=1;Count<XValue.count();Count++,gX1=gX2,gY1=gY2){
		gGetUniverseToCanvas(XValue.at(Count),YValue.at(Count),gX2,gY2);
		Pnt.drawLine(gX1,gY1,gX2,gY2);
	}
	Pnt.setPen(QPen());
}

mtGStick::mtGStick(QWidget *parent)
{
}

mtGStick::~mtGStick()
{
}

void	mtGStick::DrawPaint(QPainter &Pnt)
{
	int gX1,gY1;
	Pnt.setPen(QPen(GetLineColor(),GetLineWidth(),GetLineStyle()));
	for(int Count=0;Count<XValue.count();Count++){
		gGetUniverseToCanvas(XValue.at(Count),YValue.at(Count),gX1,gY1);
//		Pnt.drawLine(gX1,gY1,gX1,GetParent()->height()-GetParent()->OffsetY);
		Pnt.drawLine(gX1+GetOffsetX(),gY1,gX1+GetOffsetX(),GetParent()->height()-GetParent()->OffsetY);
	}
	Pnt.setPen(QPen());
}
