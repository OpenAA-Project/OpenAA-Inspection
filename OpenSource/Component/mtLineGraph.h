/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtLineGraph.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MTLINEGRAPH_H
#define MTLINEGRAPH_H

#include <QWidget>
#include <QVariant>

class mtGraph;
class mtGLine;
class mtGStick;

class mtLineGraph: public QWidget
{
    Q_OBJECT

public:
   explicit	 mtLineGraph(QWidget *parent=0);
    ~mtLineGraph(void);

	enum	ScaleType{
				 mtConstant
				,mtLog
	};

	ScaleType	STypeX,STypeY;
	int		OffsetX,OffsetY;				//グラフ表示領域のオフセット値
	double	uWidth,uHeight;					//データ座標のX軸領域幅／Y軸領域幅
	double	uGraphMinX,uGraphMaxX;			//グラフ表示領域のX軸最小値、最大値（データ座標）
	double	uGraphMinY,uGraphMaxY;			//グラフ表示領域のY軸最小値、最大値（データ座標）
	double	uLogXDbl,uLogYDbl;
	bool	OnSorted;
	bool	OnSTypeFlag;

	void	SetScaleTypeX(ScaleType type);
	ScaleType GetScaleTypeX(void){	return(STypeX);	}
	void	SetScaleTypeY(ScaleType type);
	ScaleType GetScaleTypeY(void){	return(STypeY);	}

	void	SetOffsetX(int offx)	{	OffsetX=offx;	}
	int		GetOffsetX(void)		{	return OffsetX;	}
	void	SetOffsetY(int offy)	{	OffsetY=offy;	}
	int		GetOffsetY(void)		{	return OffsetY;	}

//	void	AddGraph(mtGraph Graph);
	void	AddGraph(mtGLine *Graph);
	void	AddGraph(mtGStick *Graph);
	void	ClearGraph(void);
	QList<mtGraph*>	GraphList;

	QColor	GetBackgroundColor()				{	return BackgroundColor;	}
	void	SetBackgroundColor(QColor color)	{	BackgroundColor=color;	}
	QColor	GetMeasureColor()					{	return MeasureColor;	}
	void	SetMeasureColor(QColor color)		{	MeasureColor=color;		}

	double	GetMinY()			{	return uGraphMinY;					}
	void	SetMinY(double Y)	{	uGraphMinY=uMinY=Y;	OnSTypeFlag=false;	wuGraphMinY="SetMinY";}
	double	GetMaxY()			{	return uGraphMaxY;					}
	void	SetMaxY(double Y)	{	uGraphMaxY=uMaxY=Y;	OnSTypeFlag=false;	wuGraphMaxY="SetMaxY";	}

protected:
    virtual	void	paintEvent(QPaintEvent *event)				override;
	virtual	void	mouseDoubleClickEvent(QMouseEvent *event)	override;

signals:
	void	SignalOnPaint(QPainter &pnt);
	void	SignalLineGraphDClick(int X,int Y);

private slots:
	virtual	void	SlotOnPaint(QPainter &pnt);
	virtual	void	SlotDClick(int X,int Y);

private:
	double	uMinX,uMaxX;
	double	uMinY,uMaxY;

	double	StepMeasureX,StepMeasureY;		//目盛のステップ数
	QVariant	wuGraphMinX,wuGraphMaxX;	//グラフ表示領域のX軸最小値、最大値（データ座標）退避用
	QVariant	wuGraphMinY,wuGraphMaxY;	//グラフ表示領域のY軸最小値、最大値（データ座標）退避用

	void	gGetCanvasToUniverse	(double gx,double gy,	int &ux,int &uy);	//XY座標変換の親関数
	void	GetCanvasToUniverse		(double gx,double gy,	int &ux,int &uy);	//画面座標(gx,gy)をデータ座標(ux,uy)に変換する
	void	GetCanvasToUniverseX	(double gx,				int &ux);			//画面座標のX座標(gx)をデータ座標のX座標(ux)に変換する
	void	GetCanvasToUniverseY	(double gy,				int &uy);			//画面座標のY座標(gy)をデータ座標のY座標(uy)に変換する
	void	GetCanvasToUniverseLog	(double gx,double gy,	int &ux,int &uy);	//画面座標(gx,gy)をデータ座標(ux,uy)に変換する（対数表示）
	void	GetCanvasToUniverseLogX	(double gx,				int &ux);			//画面座標のX座標(gx)をデータ座標のX座標(ux)に変換する（対数表示）
	void	GetCanvasToUniverseLogY	(double gy,				int &uy);			//画面座標のY座標(gy)をデータ座標のY座標(uy)に変換する（対数表示）

	QColor	BackgroundColor;
	QColor	MeasureColor;
};

#endif	//MTLINEGRAPH
