/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\ImageData.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include "ImageDataUnit.h"
#include <QTime>
#include <QPen>

//********************************************
//　マスター画像格納クラス
//********************************************
class MasterImg : public MasterImage
{
	Q_OBJECT

public:
	MasterImg(QWidget *parent = 0);
	~MasterImg();


private:
	class DrawNG{
	public:
		DrawNG():_point(0,0),_color(0,0,0){};
	public:
		void setPoint(QPoint point){ _point = point; };
		void setColor(QColor color){ _color = color; };
		QPoint getPoint(){ return _point; };
		QColor getColor(){ return _color; };
	public:
		bool operator==(const DrawNG &ng){
			return _point == ng._point;
		};
	private:
		QPoint _point;
		QColor _color;
	};
	class DrawNGs{
	public:
		DrawNGs(){};
	public:
		void add(DrawNG ng){
			int index = NGPoints.indexOf(ng);
			// 追加
			if(index==-1){
				NGPoints.append(ng);
			}
			// 座標は合うけど色違い（色の更新）
			else if(NGPoints[index].getColor() != ng.getColor()){
				NGPoints[index].setColor(ng.getColor());
			}
		};
		void add(QPoint point, QColor color)
		{
			DrawNG ng;
			ng.setPoint(point);
			ng.setColor(color);
			add(ng);
		};
		void add(int x, int y, QColor color)
		{
			DrawNG ng;
			ng.setPoint(QPoint(x, y));
			ng.setColor(color);
			add(ng);
		};
		void del(DrawNG ng){
			int index = NGPoints.indexOf(ng);
			if(index!=-1)
				NGPoints.removeAt(index);
		};
		void del(QPoint point)
		{
			for(int i=0; i<NGPoints.size(); i++){
				if(point == NGPoints[i].getPoint()){
					NGPoints.removeAt(i);
					return;
				}
			}
		}
		void clear(){ NGPoints.clear(); };
		int size(){ return NGPoints.size(); };
		bool hasPoint(QPoint point)
		{
			for(int i=0; i<NGPoints.size(); i++){
				if(point == NGPoints[i].getPoint())
					return true;
			}
			return false;
		};
		bool hasColor(QColor color)
		{
			for(int i=0; i<NGPoints.size(); i++){
				if(color == NGPoints[i].getColor())
					return true;
			}
			return false;
		};
		int indexOf(DrawNG ng)
		{
			for(int i=0; i<NGPoints.size(); i++){
				if(ng == NGPoints[i])
					return i;
			}
			return -1;
		};
		int indexOf(QPoint point)
		{
			DrawNG ng;
			ng.setPoint(point);
			return indexOf(ng);
		};
		void removeAt(int pos)
		{
			NGPoints.removeAt(pos);
		};
		void remove(DrawNG ng)
		{
			NGPoints.removeOne(ng);
		};
		QList<DrawNG> toList(){ return NGPoints; };
	public:
		const QPair<QPoint,QColor> operator[](int i){
			return QPair<QPoint, QColor>(NGPoints[i].getPoint(), NGPoints[i].getColor());
		};
	private:
		QList<DrawNG> NGPoints;
	};


public:
	void setDrawNGSize(int size){ drawNGSize = size; };
	int  getDrawNGSize(){ return drawNGSize; };
	void setDrawNGPenWidth(int size){ drawNGPenWidth = size; };
	int  getDrawNGPenWidth(){ return drawNGPenWidth; };
	void addDrawNGPoint(QPoint point, QColor color);
	void addDrawNGPoint(int x, int y, QColor color){ addDrawNGPoint(QPoint(x,y),color); };
	void delDrawNGPoint(QPoint point);
	void clearDrawNGPoint();
	QList<DrawNG> getDrawNGList(){ return DrawNGPoints.toList(); };
	void setVisibleDrawNG(bool visible){ drawNGEnable = visible; };
	bool isVisibleDrawNG(){ return drawNGEnable; };
	void setDrawPenDragZoomRect(QPen pen){ dragZoomPen = pen; };
	QPen getDrawPenDragZoomRect(){ return dragZoomPen; };

protected:
	//確認している箇所を四角く枠で囲んで表示する(マウスクリックイベント)
//	virtual	void mtMouseLDown		(QMouseEvent *Ev ,int x ,int y)	override;
	virtual	void mousePressEvent	(QMouseEvent *Ev)	override;
	virtual	void mouseMoveEvent		(QMouseEvent *Ev)	override;
	virtual	void mouseReleaseEvent	(QMouseEvent *Ev)	override;
	virtual	void paintEvent			(QPaintEvent *Ev)	override;

/*	//画像描画関数
	virtual void DrawPaint		(QPainter &Pnt);
	virtual void DrawNGDot		(QPainter &Pnt,QTableWidget *W,int Index,QList<QList<QPoint> > *pNGPointList,int Type);
	virtual void DrawPieceRect	(QPainter &Pnt);
*/
protected:

signals:
//	void SignalOnMouseLDrag	(int x,int y,int w,int h);
	void SignalOnMouseLDrag	(int x,int y,int w,int h,MasterImage *MImageClass);
//	void SignalOnMouseRClick();
	void SignalOnMouseRClick(MasterImage *MImageClass);
	void SignalOnMouseLClick(int x, int y, MasterImage *MasterClass);

private slots:

private:
	int	PressX,PressY;
	bool nowDrag;
	QPoint nowMousePos;
	QTime startDragTime;

	int drawNGSize;
	int drawNGPenWidth;
	DrawNGs DrawNGPoints;
	bool drawNGEnable;

	QPen dragZoomPen;
};

#endif // IMAGEDATA_H
