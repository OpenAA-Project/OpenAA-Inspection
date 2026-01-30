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
	int		OffsetX,OffsetY;				//�O���t�\���̈��̃I�t�Z�b�g�l
	double	uWidth,uHeight;					//�f�[�^���W��X���̈敝�^Y���̈敝
	double	uGraphMinX,uGraphMaxX;			//�O���t�\���̈���X���ŏ��l�A�ő��l�i�f�[�^���W�j
	double	uGraphMinY,uGraphMaxY;			//�O���t�\���̈���Y���ŏ��l�A�ő��l�i�f�[�^���W�j
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

	double	StepMeasureX,StepMeasureY;		//�ڐ��̃X�e�b�v��
	QVariant	wuGraphMinX,wuGraphMaxX;	//�O���t�\���̈���X���ŏ��l�A�ő��l�i�f�[�^���W�j�ޔ��p
	QVariant	wuGraphMinY,wuGraphMaxY;	//�O���t�\���̈���Y���ŏ��l�A�ő��l�i�f�[�^���W�j�ޔ��p

	void	gGetCanvasToUniverse	(double gx,double gy,	int &ux,int &uy);	//XY���W�ϊ��̐e�֐�
	void	GetCanvasToUniverse		(double gx,double gy,	int &ux,int &uy);	//���ʍ��W(gx,gy)���f�[�^���W(ux,uy)�ɕϊ�����
	void	GetCanvasToUniverseX	(double gx,				int &ux);			//���ʍ��W��X���W(gx)���f�[�^���W��X���W(ux)�ɕϊ�����
	void	GetCanvasToUniverseY	(double gy,				int &uy);			//���ʍ��W��Y���W(gy)���f�[�^���W��Y���W(uy)�ɕϊ�����
	void	GetCanvasToUniverseLog	(double gx,double gy,	int &ux,int &uy);	//���ʍ��W(gx,gy)���f�[�^���W(ux,uy)�ɕϊ������i�ΐ��\���j
	void	GetCanvasToUniverseLogX	(double gx,				int &ux);			//���ʍ��W��X���W(gx)���f�[�^���W��X���W(ux)�ɕϊ������i�ΐ��\���j
	void	GetCanvasToUniverseLogY	(double gy,				int &uy);			//���ʍ��W��Y���W(gy)���f�[�^���W��Y���W(uy)�ɕϊ������i�ΐ��\���j

	QColor	BackgroundColor;
	QColor	MeasureColor;
};

#endif	//MTLINEGRAPH