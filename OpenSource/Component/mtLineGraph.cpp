/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtLineGraph.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QtGui>
#define	_USE_MATH_DEFINES
#include <math.h>

#include "mtGraph.h"
#include "mtLineGraph.h"

mtLineGraph::mtLineGraph(QWidget *parent)
{
	resize(400, 400);

	OnSorted		=false;
	OnSTypeFlag		=false;
	STypeX=STypeY	=mtConstant;
	OffsetX=OffsetY	=30;
	setMouseTracking(true);
	wuGraphMinX	=wuGraphMaxX	="NULL";
	wuGraphMinY	=wuGraphMaxY	="NULL";

	BackgroundColor	=QColor(Qt::white);
	MeasureColor	=QColor(Qt::gray);

	//connect
	connect(this,SIGNAL(SignalOnPaint(QPainter &)),		this,SLOT(SlotOnPaint(QPainter &)));
//	connect(this,SIGNAL(SignalLineGraphDClick(int,int)),this,SLOT(SlotDClick(int,int)));
}

mtLineGraph::~mtLineGraph()
{
	disconnect(this,SLOT(SlotOnPaint(QPainter &)));
}

void	mtLineGraph::SetScaleTypeX(ScaleType type)
{
//	ChangeScaleTypeX(type);
	if(STypeX==mtConstant){
	}
	else if(STypeX==mtLog){
	}
    STypeX=type;
}

void	mtLineGraph::SetScaleTypeY(ScaleType type)
{
//	ChangeScaleTypeY(type);
	if(STypeY==mtConstant){
	}
	else if(STypeY==mtLog){
	}
    STypeY=type;
}

//void	mtLineGraph::AddGraph(mtGraph Graph)
//{
//	GraphList << Graph;
//}

void	mtLineGraph::AddGraph(mtGLine *Graph)
{
	GraphList << Graph;
	Graph->ParentGraph=this;
}

void	mtLineGraph::AddGraph(mtGStick *Graph)
{
	GraphList << Graph;
	Graph->ParentGraph=this;
}

void	mtLineGraph::ClearGraph(void)
{
	GraphList.clear();
}

void	mtLineGraph::SlotOnPaint(QPainter &pnt)
{
	repaint(0,0,width(),height());
}

void	mtLineGraph::SlotDClick(int X,int Y)
{
//	LineX=X;
//	LineY=Y;
//	LineFlag=true;
//	repaint(0,0,width(),height());
}

void	mtLineGraph::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);
	const	double	XMergin=0.05;

	//ソート＆目盛りの最小値／最大値の取得
	if(!OnSorted){
		for(int GNumb=0;GNumb<GraphList.count();GNumb++){
			if(GraphList[GNumb]->isSortXY()==false){
				if(GraphList[GNumb]->SortXY()==NULL){
					continue;
				}
			}
			if(GNumb==0){
				uMinX=GraphList[GNumb]->uMinX;
				uMaxX=GraphList[GNumb]->uMaxX;
				uMinY=GraphList[GNumb]->uMinY;
				uMaxY=GraphList[GNumb]->uMaxY;
			}
			else{
				if(GraphList[GNumb]->uMinX<uMinX ){
					uMinX=GraphList[GNumb]->uMinX;
				}
				if(GraphList[GNumb]->uMaxX>uMaxX){
					uMaxX=GraphList[GNumb]->uMaxX;
				}
				if(GraphList[GNumb]->uMinY<uMinY){
					uMinY=GraphList[GNumb]->uMinY;
				}
				if(GraphList[GNumb]->uMaxY>uMaxY){
					uMaxY=GraphList[GNumb]->uMaxY;
				}
			}
		}
		double	dy=uMaxY-uMinY;
		uMinY-=dy*0.1;
		uMaxY+=dy*0.1;
		OnSorted=true;
	}
	double	dx=uMaxX-uMinX;
	double	tuMinX=uMinX-dx*XMergin;
	double	tuMaxX=uMaxX+dx*XMergin;

	//目盛りモードによる表示設定
	if(!OnSTypeFlag){
		if(STypeX==mtConstant){
			//X座標目盛りコンスタント
			StepMeasureX=1;
			double wuWidth;
			if(wuGraphMinX=="NULL"){
				uGraphMinX=tuMinX;
			}
			if(wuGraphMaxX=="NULL"){
				uGraphMaxX=tuMaxX;
			}
			uWidth=wuWidth=uGraphMaxX-uGraphMinX;	//データ座標のX軸領域幅
			if(uWidth<=0.0){
				int AAA=0;
			}
			else if(uWidth>=20 || (uWidth>=10 && !(tuMaxX==ceil(tuMaxX) && tuMinX==ceil(tuMinX)))){
				do{
					StepMeasureX*=10.0;
					wuWidth/=10.0;
				}while(wuWidth>=10.0);
				int ExpX=(int)floor(wuWidth);
				if(ExpX==1){
					StepMeasureX=(int)(StepMeasureX)>>2;
				}
				else if(ExpX<4){
					StepMeasureX=(int)(StepMeasureX)>>1;
				}
				else if(ExpX>=8){
					StepMeasureX=(int)(StepMeasureX)<<1;
				}
			}
			else if(uWidth<1.0){
				do{
					StepMeasureX*=10.0;
					wuWidth*=10.0;
				}while(wuWidth<1.0);
				int ExpX=(int)floor(wuWidth);
				if(ExpX==1){
					StepMeasureX=1.0/((int)(StepMeasureX)<<2);
				}
				else if(ExpX<4){
					StepMeasureX=2.0/((int)(StepMeasureX)<<2);
				}
				else if(ExpX<8){
					StepMeasureX=4.0/((int)(StepMeasureX)<<2);
				}
				else{
					StepMeasureX=8.0/((int)(StepMeasureX)<<2);
				}
			}
			else if(uWidth>=10.0){
				StepMeasureX=2;
			}
			else if(uWidth>=4.0){
				StepMeasureX=1;
			}
			else if(uWidth>=2.0){
				StepMeasureX=0.5;
			}
			else{
				StepMeasureX=0.2;
			}
		}
		else if(STypeX==mtLog){
		}
		if(STypeY==mtConstant){
			//Y座標目盛り
			StepMeasureY=1;
			double wuHeight;
			if(wuGraphMinY=="NULL"){
				uGraphMinY=uMinY;
			}
			if(wuGraphMaxY=="NULL"){
				uGraphMaxY=uMaxY;
			}
			uHeight=wuHeight=uGraphMaxY-uGraphMinY;		//データ座標のY軸領域幅
			if(uHeight<=0.0){}
			else if(uHeight>=20.0 || (uHeight>=10.0 && !(uMaxY==ceil(uMaxY) && uMinY==ceil(uMinY)))){
				do{
					StepMeasureY*=10.0;
					wuHeight/=10.0;
				}while(wuHeight>=10.0);
				int ExpY=(int)floor(wuHeight);
				if(ExpY==1){
					StepMeasureY=(int)(StepMeasureY)>>2;
				}
				else if(ExpY<4){
					StepMeasureY=(int)(StepMeasureY)>>1;
				}
				else if(ExpY>=8){
					StepMeasureY=(int)(StepMeasureY)<<1;
				}
			}
			else if(uHeight<1.0){
				do{
					StepMeasureY*=10.0;
					wuHeight*=10.0;
				}while(wuHeight<1.0);

				int ExpY=(int)floor(wuHeight);
				if(ExpY==1){
					StepMeasureY=1.0/((int)(StepMeasureY)<<2);
				}
				else if(ExpY<4){
					StepMeasureY=2.0/((int)(StepMeasureY)<<2);
				}
				else if(ExpY<8){
					StepMeasureY=4.0/((int)(StepMeasureY)<<2);
				}
				else{
					StepMeasureY=8.0/((int)(StepMeasureY)<<2);
				}
			}
			else if(uHeight>=10.0){
				StepMeasureY=2;
			}
			else if(uHeight>=4.0){
				StepMeasureY=1;
			}
			else if(uHeight>=2.0){
				StepMeasureY=0.5;
			}
			else{
				StepMeasureY=0.2;
			}
		}
		else if(STypeY==mtLog){
			//Y座標目盛り
			StepMeasureY=1;
			double wuHeight;
			if(wuGraphMinY=="NULL"){
				uGraphMinY=0;
			}
			if(wuGraphMaxY=="NULL"){
				uGraphMaxY=uMaxY;
			}
			double	nH=uGraphMaxY-uGraphMinY;		//データ座標のY軸領域幅
			if(nH>0.0){
				uHeight=wuHeight=nH;
				uLogYDbl=log10(uHeight)+1;
			}
			else{
				uLogYDbl=0;
			}
		}
		OnSTypeFlag=true;
	}

	//共通表示部のDraw
//	Pnt.setBrush(QBrush(QColor(Qt::white)));
	Pnt.setBrush(QBrush(GetBackgroundColor()));
	Pnt.drawRect(OffsetX,0,width(),height()-OffsetY);
//	Pnt.setPen(QPen(QColor(Qt::gray),2,Qt::DashLine));
	Pnt.setPen(QPen(GetMeasureColor(),2,Qt::DashLine));
	int gMeasureX;
	double uMeasureX;
	if(STypeX==mtConstant){
		//X軸目盛り
		int	WLen=uWidth/StepMeasureX;
		for(int XXX=0;XXX<=WLen;XXX++){
			if((uMeasureX=(int)((uGraphMinX/StepMeasureX+XXX))*StepMeasureX)<uGraphMinX){
				continue;
			}
			if(GraphList.at(0)!=NULL){
				GraphList[0]->GetUniverseToCanvasX(uMeasureX,gMeasureX);
				Pnt.drawLine(gMeasureX,height()-OffsetY,gMeasureX,0);	//区切り網目線
			}
		}
	}
	else if(STypeX==mtLog){
		for(int XXX=0;XXX<uLogXDbl;XXX++){
			if(GraphList.at(0)!=NULL){
				GraphList[0]->GetUniverseToCanvasLogX(pow(10.0,XXX),gMeasureX);
				Pnt.drawLine(gMeasureX,height()-OffsetY,gMeasureX,0);	//区切り網目線
			}
		}
	}
	int gMeasureY;
	double uMeasureY;
	if(STypeY==mtConstant){
		//Y軸目盛り
		int	HLen=uHeight/StepMeasureY;
		for(int YYY=0;YYY<=HLen;YYY++){
			if((uMeasureY=(int)((uGraphMinY/StepMeasureY+YYY))*StepMeasureY)<uGraphMinY){
				continue;
			}
			if(GraphList.at(0)!=NULL){
				GraphList[0]->GetUniverseToCanvasY(uMeasureY,gMeasureY);
				Pnt.drawLine(OffsetX,gMeasureY,width(),gMeasureY);	//区切り網目線
			}
		}
	}
	else if(STypeY==mtLog){
		for(int YYY=0;YYY<uLogYDbl;YYY++){
			if(GraphList.at(0)!=NULL){
				GraphList[0]->GetUniverseToCanvasLogY(pow(10.0,YYY),gMeasureY);
				Pnt.drawLine(OffsetX,gMeasureY,width(),gMeasureY);	//区切り網目線
			}
		}
	}
	Pnt.setPen(QPen());

	//各グラフの描画
	for(int GNumb=0;GNumb<GraphList.count();GNumb++){
		GraphList[GNumb]->DrawPaint(Pnt);
	}

	//目盛り部ペイント
	Pnt.setPen(QPen());
//	Pnt.setBrush(QBrush(QColor(Qt::lightGray)));
	Pnt.setBrush(this->palette().dark());
	const	QFont	&font=Pnt.font();
	QFontMetrics	FontMetrics(font);
	int	CharacterHeight=FontMetrics.height();
	Pnt.drawRect(-1,-1,OffsetX,height()-OffsetY);
	Pnt.drawRect(-1,height()-OffsetY,OffsetX,OffsetY);
	Pnt.drawRect(OffsetX,height()-OffsetY,width()-OffsetX,OffsetY);
	Pnt.setBrush(QBrush());
	int	CharY=-OffsetY+((OffsetY-CharacterHeight)>>1);
	if(STypeX==mtConstant){
		//X軸目盛り
		int	WLen=uWidth/StepMeasureX;
		for(int XXX=0;XXX<=WLen;XXX++){
			if((uMeasureX=(int)((uGraphMinX/StepMeasureX+XXX))*StepMeasureX)<uGraphMinX){
				continue;
			}
			if(GraphList.at(0)!=NULL){
				GraphList[0]->GetUniverseToCanvasX(uMeasureX,gMeasureX);
				Pnt.drawLine(gMeasureX,height()-OffsetY,gMeasureX,height()-(OffsetY>>1));
				//Pnt.drawText(0,height()-(OffsetY>>1),gMeasureX-1,OffsetY>>1,Qt::AlignRight,QString().setNum(uMeasureX));	//目盛り数値
				Pnt.drawText(0,height()+CharY,gMeasureX-1,CharacterHeight,Qt::AlignRight,QString().setNum(uMeasureX));	//目盛り数値
			}
		}
	}
	else if(STypeX==mtLog){
		Pnt.drawText(0,height()-(OffsetY>>1),OffsetX-1,OffsetY>>1,Qt::AlignRight,QString().setNum(0));	//目盛り数値
		for(int XXX=0;XXX<uLogXDbl;XXX++){
			if(GraphList.at(0)!=NULL){
				GraphList[0]->GetUniverseToCanvasLogX((uMeasureX=pow(10.0,XXX)),gMeasureX);
				Pnt.drawLine(gMeasureX,height()-OffsetY,gMeasureX,height()-(OffsetY>>1));
				//Pnt.drawText(0,height()-(OffsetY>>1),gMeasureX-1,OffsetY>>1,Qt::AlignRight,QString().setNum(uMeasureX));	//目盛り数値
				Pnt.drawText(0,height()+CharY,gMeasureX-1,CharacterHeight,Qt::AlignRight,QString().setNum(uMeasureX));	//目盛り数値
			}
		}
	}
	if(STypeY==mtConstant){
		//Y軸目盛り
		int	LastPosY=height()+CharacterHeight;
		int	HLen=uHeight/StepMeasureY;
		for(int YYY=0;YYY<=HLen;YYY++){
			if((uMeasureY=(int)((uGraphMinY/StepMeasureY+YYY))*StepMeasureY)<uGraphMinY){
				continue;
			}
			if(GraphList.at(0)!=NULL){
				GraphList[0]->GetUniverseToCanvasY(uMeasureY,gMeasureY);
				Pnt.drawLine(OffsetX,gMeasureY,OffsetX>>1,gMeasureY);
				if(LastPosY-CharacterHeight>=gMeasureY){
					Pnt.drawText(1,gMeasureY+1,OffsetX,height(),Qt::AlignLeft,QString().setNum(uMeasureY));	//目盛り数値
					LastPosY=gMeasureY;
				}
			}
		}
	}
	else if(STypeY==mtLog){
		Pnt.drawText(1,height()-OffsetY+1,OffsetX,height(),Qt::AlignLeft,QString().setNum(0));	//目盛り数値
		int	LastPosY=height()+CharacterHeight;
		for(int YYY=0;YYY<uLogYDbl;YYY++){
			if(GraphList.at(0)!=NULL){
				GraphList[0]->GetUniverseToCanvasLogY((uMeasureY=pow(10.0,YYY)),gMeasureY);
				Pnt.drawLine(OffsetX,gMeasureY,OffsetX>>1,gMeasureY);
				if(LastPosY-CharacterHeight>=gMeasureY){
					Pnt.drawText(1,gMeasureY+1,OffsetX,height(),Qt::AlignLeft,QString().setNum(uMeasureY));	//目盛り数値
					LastPosY=gMeasureY;
				}
			}
		}
	}

//	if(LineFlag)
//		Pnt.drawLine(LineX,0,LineX,height()-OffsetY);

//	if(MClickFlag)
//		Pnt.drawRect(StartPointX,StartPointY,MoveWidth,MoveHeight);
}

void	mtLineGraph::mouseDoubleClickEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton){
		if(event->x()>=OffsetX){
			int uX,uY;
			gGetCanvasToUniverse(event->x(),event->y(),uX,uY);
			emit SignalLineGraphDClick(uX,uY);
		}
	}
}

//データ座標(ux,uy)を画面座標(gx,gy)に変換する
void	mtLineGraph::gGetCanvasToUniverse(double gx,double gy,int &ux,int &uy)
{
	if(STypeX==mtConstant){
		GetCanvasToUniverseX(gx,ux);
		if(STypeY==mtConstant){
			GetCanvasToUniverseY(gy,uy);
		}
		else if(STypeY==mtLog){
			GetCanvasToUniverseLogY(gy,uy);
		}
	}
	else if(STypeX==mtLog){
		GetCanvasToUniverseLogX(gx,ux);
		if(STypeY==mtConstant){
			GetCanvasToUniverseY(gy,uy);
		}
		else if(STypeY==mtLog){
			GetCanvasToUniverseLogY(gy,uy);
		}
	}
}

//データ座標(ux,uy)を画面座標(gx,gy)に変換する
void	mtLineGraph::GetCanvasToUniverse(double gx,double gy,int &ux,int &uy)
{
	ux=uWidth*(gx-OffsetX)/(width()-OffsetX)+uGraphMinX;
	uy=uGraphMaxY-(uHeight*gy)/(height()-OffsetY);
}

//データ座標のX座標(ux)を画面座標のX座標(gx)に変換する
void	mtLineGraph::GetCanvasToUniverseX(double gx,int &ux)
{
	ux=uWidth*(gx-OffsetX)/(width()-OffsetX)+uGraphMinX;
}

//データ座標のY座標(uy)を画面座標のY座標(gy)に変換する
void	mtLineGraph::GetCanvasToUniverseY(double gy,int &uy)
{
	uy=uGraphMaxY-(uHeight*gy)/(height()-OffsetY);
}

//データ座標(ux,uy)を画面座標(gx,gy)に変換する（対数表示）
void	mtLineGraph::GetCanvasToUniverseLog(double gx,double gy,int &ux,int &uy)
{
	ux=pow(10.0,(uLogXDbl*(gx-OffsetX)/(width()-OffsetX))-1);
	uy=pow(10.0,(uLogYDbl*(height()-OffsetY-gy)/(height()-OffsetY))-1);
}

//データ座標のX座標(ux)を画面座標のX座標(gx)に変換する（対数表示）
void	mtLineGraph::GetCanvasToUniverseLogX(double gx,int &ux)
{
	ux=pow(10.0,(uLogXDbl*(gx-OffsetX)/(width()-OffsetX))-1);
}

//データ座標のY座標(uy)を画面座標のY座標(gy)に変換する（対数表示）
void	mtLineGraph::GetCanvasToUniverseLogY(double gy,int &uy)
{
	uy=pow(10.0,(uLogYDbl*(height()-OffsetY-gy)/(height()-OffsetY))-1);
}
