/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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