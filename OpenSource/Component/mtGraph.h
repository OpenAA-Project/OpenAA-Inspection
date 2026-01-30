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

	void	SetMinX		(double MinX)	{	wuGraphMinX=uGraphMinX=MinX;	}	//�O���t�\���̈���X���ŏ��l���Z�b�g
	void	SetMaxX		(double MaxX)	{	wuGraphMaxX=uGraphMaxX=MaxX;	}	//�O���t�\���̈���X���ő��l���Z�b�g
	void	SetMinY		(double MinY)	{	wuGraphMinY=uGraphMinY=MinY;	}	//�O���t�\���̈���Y���ŏ��l���Z�b�g
	void	SetMaxY		(double MaxY)	{	wuGraphMaxY=uGraphMaxY=MaxY;	}	//�O���t�\���̈���Y���ő��l���Z�b�g
//	void	SetuMinY	(double MinY);	//���W�f�[�^��Y���ŏ��l���Z�b�g
//	void	SetuMaxY	(double MaxY);	//���W�f�[�^��Y���ő��l���Z�b�g

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

	void	gGetUniverseToCanvas	(double ux,double uy,	int &gx,int &gy);	//XY���W�ϊ��̐e�֐�
	void	GetUniverseToCanvas		(double ux,double uy,	int &gx,int &gy);	//�f�[�^���W(ux,uy)�����ʍ��W(gx,gy)�ɕϊ�����
	void	GetUniverseToCanvasX	(double ux,				int &gx);			//�f�[�^���W��X���W(ux)�����ʍ��W��X���W(gx)�ɕϊ�����
	void	GetUniverseToCanvasY	(double uy,				int &gy);			//�f�[�^���W��Y���W(uy)�����ʍ��W��Y���W(gy)�ɕϊ�����
	void	GetUniverseToCanvasLog	(double ux,double uy,	int &gx,int &gy);	//�f�[�^���W(ux,uy)�����ʍ��W(gx,gy)�ɕϊ������i�ΐ��\���j
	void	GetUniverseToCanvasLogX	(double ux,				int &gx);			//�f�[�^���W��X���W(ux)�����ʍ��W��X���W(gx)�ɕϊ������i�ΐ��\���j
	void	GetUniverseToCanvasLogY	(double uy,				int &gy);			//�f�[�^���W��Y���W(uy)�����ʍ��W��Y���W(gy)�ɕϊ������i�ΐ��\���j

	QList<double>	XValue;
	QList<double>	YValue;
	double	uMinX,uMaxX;					//���W�f�[�^��X���ŏ��l�A�ő��l
	double	uMinY,uMaxY;					//���W�f�[�^��Y���ŏ��l�A�ő��l

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

	double	uGraphMinX,uGraphMaxX;			//�O���t�\���̈���X���ŏ��l�A�ő��l�i�f�[�^���W�j
	double	uGraphMinY,uGraphMaxY;			//�O���t�\���̈���Y���ŏ��l�A�ő��l�i�f�[�^���W�j
	QVariant	wuGraphMinX,wuGraphMaxX;	//�O���t�\���̈���X���ŏ��l�A�ő��l�i�f�[�^���W�j�ޔ��p
	QVariant	wuGraphMinY,wuGraphMaxY;	//�O���t�\���̈���Y���ŏ��l�A�ő��l�i�f�[�^���W�j�ޔ��p
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