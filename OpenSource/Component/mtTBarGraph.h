/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtTBarGraph.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MTTBARGRAPH_H
#define MTTBARGRAPH_H

//#include <QMetaType>
#include <QWidget>
#include <QColor>
#include "mtWidgetPosition.h"

class	mtMeter;

class mtTBarGraph : public mtWidgetPosition
{
    Q_OBJECT
	Q_PROPERTY(QColor BarColor READ GetBarColor WRITE SetBarColor)
	Q_PROPERTY(int  MaxWidth READ GetMaxWidth WRITE SetMaxWidth)
	Q_PROPERTY(int  MaxValue READ GetMaxValue WRITE SetMaxValue)

	QColor	FBarColor;
	int		FMaxWidth;
	int		FMaxValue;
	int		FMovx;
	int		FMovy;
	double	FZoomRateX;
	double	FZoomRateY;

	int		*VData;
	int		AllocatedNumb;
	int		LastX,LastY;
	bool	RectMode;
	int		RectX1,RectY1,RectX2,RectY2;
	mtMeter	*MeterLeft;
	mtMeter	*MeterBottom;
public:
	explicit	mtTBarGraph(QWidget *parent = 0);
    ~mtTBarGraph();

	QColor	GetBarColor(void)	{	return(FBarColor);	}
	int		GetMaxWidth(void)	{	return(FMaxWidth);	}
	int		GetMaxValue(void)	{	return(FMaxValue);	}

	void	SetBarColor(const QColor &c);
	void	SetMaxWidth(int c);
	void	SetMaxValue(int c);

	int		GetYData(int x);
	void	SetYData(int x ,int ydata);
	void	SetMeter(mtMeter *mBottom,mtMeter *mLeft);
	
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

private:
	void	AllocData(void);	
	void	SetPoint(int rx ,int ry);

    virtual	void	paintEvent(QPaintEvent *event)			override;
	virtual	void	mousePressEvent ( QMouseEvent *Ev )		override;
	virtual	void	mouseMoveEvent ( QMouseEvent *Ev )		override;
	virtual	void	mouseReleaseEvent ( QMouseEvent * Ev)	override;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
	void	SetMeter(void);

signals:
	void	SignalChanged(void);

private slots:
	void	SlotChanged(void);
};

#endif