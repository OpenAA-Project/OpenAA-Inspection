/*
 * Copyright (C) 2021
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

#ifndef MAPFORM_H
#define MAPFORM_H

#include <QWidget>
#include "mtGraphicUnit.h"

namespace Ui {
class MapForm;
}

class NGCauseForm;
const	int		DivX=16;
const	int		DivY=16;


class MapGraphic : public mtGraphicUnit
{
public:
	MapGraphic(QWidget *parent = 0
				,bool	EnableMeasure=true
				,bool	EnableToolArea=true
				,bool	EnableVScroller=true
				,bool	EnableHScroller=true
				,bool	EnableZoom=true
				,bool	EnableMove=true
				,bool	EnableFitZoom=true);
	~MapGraphic();
};

class MapForm : public QWidget
{
    Q_OBJECT

    NGCauseForm	*Parent;
	MapGraphic	MapPanel;

	int		MapDim[DivX][DivY];
	int		LastMovX;
	int		LastMovY;
	double	LastZoomRate;
	int		LastMaster;
	QImage	MasterImage;
	QImage	MapMask;   
public:
    explicit MapForm(NGCauseForm *p,QWidget *parent = 0);
    ~MapForm();
    
private slots:
    void on_comboBoxMachine_currentIndexChanged(int index);
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseLDown(int ,int);
	void	SlotMouseRDown(int ,int);
	void	SlotMouseWheel(int delta ,int x,int y);
protected:
	virtual	void	resizeEvent(QResizeEvent *event)	override;
private:
    Ui::MapForm *ui;

	void	MakeMapDim(void);
};

#endif // MAPFORM_H