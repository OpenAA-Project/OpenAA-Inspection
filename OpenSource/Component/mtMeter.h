/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtMeter.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef MTMETER_H
#define MTMETER_H

#include <QWidget>
#include "NList.h"

class mtMeter : public QWidget
{
    Q_OBJECT
	Q_PROPERTY(mtDirection  DrawMode READ GetDrawMode WRITE SetDrawMode)
	Q_PROPERTY(QColor Color READ GetColor WRITE SetColor)

public:
enum    mtDirection{
                 mtHorizUpper
                ,mtHorizLower
                ,mtVertLeft
                ,mtVertRight
                ,mtHorizUpperReverse
                ,mtHorizLowerReverse
                ,mtVertLeftReverse
                ,mtVertRightReverse
                };
private:
    mtDirection FDrawMode;
    QColor  FColor;
    QFont   FFont;
    double  FLeftPosition;
    int     FSeparation;
    double  FZoomRate;
	int		OffsetValue;

public:
    void	SetFont(const QFont &font);
    void	SetSeparation(int sep);
    void	SetZoomRate(double ZoomRate);
    void	SetLeftPosition(double leftposition);
	void	SetOffsetValue(int n)	        {	OffsetValue=n;	}
	int		GetOffsetValue(void)	const   {	return OffsetValue;	}
    
	mtMeter::mtDirection GetDrawMode(void)  const;
	void		SetDrawMode(mtMeter::mtDirection d);
	QColor		GetColor(void)              const;
	void		SetColor(const QColor &col);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
	virtual void enterEvent ( QEnterEvent * event )  override;
	virtual void leaveEvent ( QEvent * event )  override;
signals:
	void	SignalEnter();
	void	SignalLeave();

public:
    explicit	mtMeter(QWidget *parent = 0);
};

#endif
