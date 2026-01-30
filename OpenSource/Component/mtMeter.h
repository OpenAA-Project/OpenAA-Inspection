/*
 * Copyright (C) 2025
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