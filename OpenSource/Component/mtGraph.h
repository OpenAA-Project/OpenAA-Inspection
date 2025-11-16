/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtGraph.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MTGRAPH_H
#define MTGRAPH_H

#define	_USE_MATH_DEFINES
#include <math.h>
#include <QWidget>
#include <QVariant>

class mtLineGraph;

class mtGraph
{
//    Q_OBJECT

public:
    mtGraph(void);
    ~mtGraph(void);

//	void	SetScaleTypeX(ScaleType type);
//	ScaleType GetScaleTypeX(void){	return(STypeX);	}
//	void	SetScaleTypeY(ScaleType type);
//	ScaleType GetScaleTypeY(void){	return(STypeY);	}

	void	SetLineColor(QColor Color);
	QColor	GetLineColor(void);
	void	SetLineWidth(int W);
	int		GetLineWidth(void);
	void	SetLineStyle(Qt::PenStyle Style);
	Qt::PenStyle	GetLineStyle();
	double	_GetXValue	(double Y);
	double	_GetYValue	(double X);
	double	GetPointX	(int X);
	double	GetPointY	(int Y);
	int		GetPointCount(void);
	void	AddXY		(double X,double Y);
	void	AddX		(double X);
	void	SubXY		(int idx);
	double	GetAverageY	(void);
	void	DeleteXY	(void);
	void	ReplaceXY	(double X,double Y);

	void	SetMinX		(double MinX)	{	wuGraphMinX=uGraphMinX=MinX;	}	//グラフ表示領域のX軸最小値をセット
	void	SetMaxX		(double MaxX)	{	wuGraphMaxX=uGraphMaxX=MaxX;	}	//グラフ表示領域のX軸最大値をセット
	void	SetMinY		(double MinY)	{	wuGraphMinY=uGraphMinY=MinY;	}	//グラフ表示領域のY軸最小値をセット
	void	SetMaxY		(double MaxY)	{	wuGraphMaxY=uGraphMaxY=MaxY;	}	//グラフ表示領域のY軸最大値をセット
//	void	SetuMinY	(double MinY);	//座標データのY軸最小値をセット
//	void	SetuMaxY	(double MaxY);	//座標データのY軸最大値をセット

	void*	SortXY		(void);
	bool	isSortXY	(void){	return(Sorted);	}
//	virtual void	DrawPaint(QPainter &Pnt,void (*)(double,int &),void (*)(double,int &)){};
//	virtual void	DrawPaint(QPainter &Pnt,void (*pGetUniverseToCanvasX)(double,int &),void (*pGetUniverseToCanvasY)(double,int &)){};
///	virtual void	DrawPaint(QPainter &Pnt,void (*pGetUniverseToCanvasX)(double,int &,int,int),void (*pGetUniverseToCanvasY)(double,int &,int,int),int W,int H){};
//	virtual void	DrawPaint(QPainter &Pnt,void (*pGetUniverseToCanvasX)(double,int &,int,int),void (*pGetUniverseToCanvasY)(double,int &,int,int),int W,int H)=0;
//	virtual void	DrawPaint(QPainter &Pnt,PGETUNIVERSETOCANVASX pGetUniverseToCanvasX,PGETUNIVERSETOCANVASY pGetUniverseToCanvasY){};
	virtual void	DrawPaint(QPainter &Pnt){};

	mtLineGraph	*ParentGraph;
	mtLineGraph	*GetParent(void)	{	return(ParentGraph);	}

	void	gGetUniverseToCanvas	(double ux,double uy,	int &gx,int &gy);	//XY座標変換の親関数
	void	GetUniverseToCanvas		(double ux,double uy,	int &gx,int &gy);	//データ座標(ux,uy)を画面座標(gx,gy)に変換する
	void	GetUniverseToCanvasX	(double ux,				int &gx);			//データ座標のX座標(ux)を画面座標のX座標(gx)に変換する
	void	GetUniverseToCanvasY	(double uy,				int &gy);			//データ座標のY座標(uy)を画面座標のY座標(gy)に変換する
	void	GetUniverseToCanvasLog	(double ux,double uy,	int &gx,int &gy);	//データ座標(ux,uy)を画面座標(gx,gy)に変換する（対数表示）
	void	GetUniverseToCanvasLogX	(double ux,				int &gx);			//データ座標のX座標(ux)を画面座標のX座標(gx)に変換する（対数表示）
	void	GetUniverseToCanvasLogY	(double uy,				int &gy);			//データ座標のY座標(uy)を画面座標のY座標(gy)に変換する（対数表示）

	QList<double>	XValue;
	QList<double>	YValue;
	double	uMinX,uMaxX;					//座標データのX軸最小値、最大値
	double	uMinY,uMaxY;					//座標データのY軸最小値、最大値

	int		GetOffsetX	()			{	return OffsetX;	}
	void	SetOffsetX	(int X)		{	OffsetX=X;		}
	int		GetOffsetY	()			{	return OffsetY;	}
	void	SetOffsetY	(int Y)		{	OffsetY=Y;		}

private:
//	void	GetUniverseToCanvas		(double ux,double uy,int &gx,int &gy);
//	void	GetUniverseToCanvasX	(double ux,int &gx);
//	void	GetUniverseToCanvasY	(double uy,int &gy);
//	void	GetUniverseToCanvasLog	(double ux,double uy,int &gx,int &gy);
//	void	GetUniverseToCanvasLogX	(double ux,int &gx);
//	void	GetUniverseToCanvasLogY	(double uy,int &gy);
//	void	GetCanvasToUniverse		(int gx,int gy,double &ux,double &uy);
//	void	GetCanvasToUniverseX	(int gx,double &ux);
//	void	GetCanvasToUniverseY	(int gy,double &uy);
//	void	GetCanvasToUniverseLog	(int gx,int gy,double &ux,double &uy);
//	void	GetCanvasToUniverseLogX	(int gx,double &ux);
//	void	GetCanvasToUniverseLogY	(int gy,double &uy);

	bool	Sorted;
	QColor	LineColor;
	int		LineWidth;
	Qt::PenStyle	LineStyle;

	double	uGraphMinX,uGraphMaxX;			//グラフ表示領域のX軸最小値、最大値（データ座標）
	double	uGraphMinY,uGraphMaxY;			//グラフ表示領域のY軸最小値、最大値（データ座標）
	QVariant	wuGraphMinX,wuGraphMaxX;	//グラフ表示領域のX軸最小値、最大値（データ座標）退避用
	QVariant	wuGraphMinY,wuGraphMaxY;	//グラフ表示領域のY軸最小値、最大値（データ座標）退避用
	//double	uLogXDbl,uLogYDbl;
	//bool	LineFlag;
	//int		LineX,LineY;
	bool	MClickFlag;
	//int		StartPointX,StartPointY,FinishPointX,FinishPointY;
	//int		MoveWidth,MoveHeight;

	int		OffsetX;
	int		OffsetY;
};

class mtGLine : public mtGraph
{
//    Q_OBJECT

public:
    mtGLine(QWidget *parent=0);
    ~mtGLine(void);
//	void	DrawPaint(QPainter &Pnt,void (*)(double,int &),void (*)(double,int &));
//	void	DrawPaint(QPainter &Pnt,void (*pGetUniverseToCanvasX)(double,int &),void (*pGetUniverseToCanvasY)(double,int &));
///	void	DrawPaint(QPainter &Pnt,void (*pGetUniverseToCanvasX)(double,int &,int,int),void (*pGetUniverseToCanvasY)(double,int &,int,int),int W,int H);
//	void	DrawPaint(QPainter &Pnt,PGETUNIVERSETOCANVASX pGetUniverseToCanvasX,PGETUNIVERSETOCANVASY pGetUniverseToCanvasY);
	void	DrawPaint(QPainter &Pnt);

private:
};

class mtGStick : public mtGraph
{
//    Q_OBJECT

public:
    mtGStick(QWidget *parent=0);
    ~mtGStick(void);
//	void	DrawPaint(QPainter &Pnt,void (*)(double,int &),void (*)(double,int &));
//	void	DrawPaint(QPainter &Pnt,void (*pGetUniverseToCanvasX)(double,int &),void (*pGetUniverseToCanvasY)(double,int &));
///	void	DrawPaint(QPainter &Pnt,void (*pGetUniverseToCanvasX)(double,int &,int,int),void (*pGetUniverseToCanvasY)(double,int &,int,int),int W,int H);
//	void	DrawPaint(QPainter &Pnt,PGETUNIVERSETOCANVASX pGetUniverseToCanvasX,PGETUNIVERSETOCANVASY pGetUniverseToCanvasY);
	void	DrawPaint(QPainter &Pnt);

private:
};

#endif	//MTGRAPH
