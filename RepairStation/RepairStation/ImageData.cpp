/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\ImageData.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "ImageData.h"
#include <QMouseEvent>
#include <QPainter>


//********************************************
//　マスター画像格納クラス
//********************************************
MasterImg::MasterImg(QWidget *parent) : MasterImage(parent)
{
	SetMode(fdRectangle);
	SetFrameColor(QColor(Qt::yellow));
	nowDrag = false;
	startDragTime = QTime::currentTime();

	drawNGSize = 5;
	drawNGPenWidth = 4;
	drawNGEnable = true;

	dragZoomPen = QPen(QColor(200,50,50), 2);

	NoShiftCanvasMode = false;
}

MasterImg::~MasterImg()
{
}

void MasterImg::addDrawNGPoint(QPoint point, QColor color)
{
	DrawNG ng;
	ng.setPoint(point);
	ng.setColor(color);
	DrawNGPoints.add(ng);
}

void MasterImg::delDrawNGPoint(QPoint point)
{
	DrawNGPoints.del(point);
}

void MasterImg::mousePressEvent(QMouseEvent *Ev)
{
	if(Ev->button()==Qt::LeftButton){
		PressX=Ev->x();
		PressY=Ev->y();
		nowDrag = false;
	}
	startDragTime = QTime::currentTime();
	MasterImage::mousePressEvent(Ev);
}

void MasterImg::mouseMoveEvent(QMouseEvent *Ev)
{
	if(!(Ev->buttons()&Qt::LeftButton)){
		MasterImage::mouseMoveEvent(Ev);
		return;
	}
	if(!nowDrag && startDragTime.msecsTo(QTime::currentTime())>200){
		nowDrag = true;
	}
	else if(nowDrag){
		nowMousePos.setX(Ev->x());
		nowMousePos.setY(Ev->y());
	}

	MasterImage::mouseMoveEvent(Ev);
}

void MasterImg::mouseReleaseEvent(QMouseEvent *Ev)
{
	nowDrag = false;
	if(Ev->button()!=Qt::LeftButton){
		if(Ev->button()==Qt::RightButton)
			emit SignalOnMouseRClick(this);
		return;
	}
//	if(Ev->x()!=PressX || Ev->y()!=PressY){
	//矩形選択時にクリックの幅を持たせる
	if(abs(Ev->x()-PressX)>5 || abs(Ev->y()-PressY)>5){
		MasterImage::mtMouseLDown(Ev,Ev->x(),Ev->y());
		int uX1,uY1,uX2,uY2;
		GetCanvasToUniverse(PressX, PressY, uX1,uY1);
		GetCanvasToUniverse(Ev->x(),Ev->y(),uX2,uY2);
		if(uX1>uX2){
			int wuX=uX1;
			uX1=uX2;
			uX2=wuX;
		}
		if(uY1>uY2){
			int wuY=uY1;
			uY1=uY2;
			uY2=wuY;
		}
		emit SignalOnMouseLDrag(uX1,uY1,uX2-uX1,uY2-uY1,this);
		return;
	}
	else
	{
		//単純左クリック
		emit SignalOnMouseLClick(Ev->x(), Ev->y(), this);
		return;
	}
	MasterImage::mouseReleaseEvent(Ev);
	Clear();
}

void MasterImg::clearDrawNGPoint()
{
	DrawNGPoints.clear();
}

void MasterImg::paintEvent(QPaintEvent *Ev)
{
	MasterImage::paintEvent(Ev);
	QPainter Pnt(this);

	if(drawNGEnable){
		for(int i=0; i<DrawNGPoints.size(); i++){
			QPoint point = DrawNGPoints[i].first;
			int x,y;
			
			GetUniverseToCanvas(point.x() + movx, point.y() + movy, x, y);

			QPen oldPen = Pnt.pen();
			QPen pen;
			pen.setWidth(drawNGPenWidth);
			pen.setColor(DrawNGPoints[i].second);
			Pnt.setPen(pen);
			
			Pnt.drawLine(x - drawNGSize, y - drawNGSize, x + drawNGSize, y + drawNGSize);
			Pnt.drawLine(x - drawNGSize, y + drawNGSize, x + drawNGSize, y - drawNGSize);

			Pnt.setPen(oldPen);
		}
	}

	if(nowDrag){
		int x = PressX < nowMousePos.x() ? PressX : nowMousePos.x();
		int y = PressY < nowMousePos.y() ? PressY : nowMousePos.y();
		int w = abs(PressX - nowMousePos.x());
		int h = abs(PressY - nowMousePos.y());

		QRect rect(x, y, w, h);

		QPen oldPen = Pnt.pen();
		Pnt.setPen(dragZoomPen);

		Pnt.drawRect(rect);
		Pnt.setPen(oldPen);
	}

}
/*
void MasterImg::DrawPaint(QPainter &MPnt)
{
	//画像の描画
	QMatrix matrix;
	matrix.scale(ZoomRate,ZoomRate);
	int uW=width()/ZoomRate;
	int uH=height()/ZoomRate;
	if(ImageList.count()==1){
		int uOffsetX=ImageList[0]->OffsetX;
		int uOffsetY=ImageList[0]->OffsetY;
		int ImageW=ImageList[0]->Image->width();
		int ImageH=ImageList[0]->Image->height();
		MPnt.drawImage(0,0,ImageList[0]->Image->copy(-movx-uOffsetX,-movy-uOffsetY,uW,uH).transformed(matrix));
	}
	else{
		for(int Cnt=0;Cnt<ImageList.count();Cnt++){
			int uOffsetX=ImageList[Cnt]->OffsetX;
			int uOffsetY=ImageList[Cnt]->OffsetY;
			int ImageW=ImageList[Cnt]->Image->width();
			int ImageH=ImageList[Cnt]->Image->height();
			//選択矩形が画像中に収まる場合
			if(-movx>=uOffsetX && (-movx+uW)<=(uOffsetX+ImageW) && -movy>=uOffsetY && (-movy+uH)<=(uOffsetY+ImageH))
				MPnt.drawImage(0,0,ImageList[Cnt]->Image->copy(-movx-uOffsetX,-movy-uOffsetY,uW,uH).transformed(matrix));
			else{
				int X,Y,W,H;
				//選択矩形が画像の右端をまたぐ場合
				if(-movx<(uOffsetX+ImageW) && (-movx+uW)>(uOffsetX+ImageW) && (-movy+uH)>=uOffsetY && -movy<(uOffsetY+ImageH))
					MPnt.drawImage(0,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,ImageList[Cnt]->Image->copy(-movx-uOffsetX,-movy-uOffsetY+Y,uOffsetX+ImageW+movx,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
				//選択矩形が画像の左端をまたぐ場合
				else if(-movx<uOffsetX && (-movx+uW)>uOffsetX && (-movy+uH)>=uOffsetY && -movy<(uOffsetY+ImageH))
					MPnt.drawImage((uOffsetX+movx)*ZoomRate,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,ImageList[Cnt]->Image->copy(0,-movy-uOffsetY+Y,-movx+uW-uOffsetX,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
				//選択矩形が画像の下端をまたぐ場合
				else if(-movy<(uOffsetY+ImageH) && (-movy+uH)>(uOffsetY+ImageH) && (-movx+uW)>=uOffsetX && -movx<(uOffsetX+ImageW))
					MPnt.drawImage((uOffsetX+movx)*ZoomRate,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,ImageList[Cnt]->Image->copy(0,-movy-uOffsetY+Y,-movx+uW-uOffsetX,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
				//選択矩形が画像の上端をまたぐ場合
				else if(-movy<uOffsetY && (-movy+uH)>uOffsetY && (-movx+uW)>=uOffsetX && -movx<(uOffsetX+ImageW))
					MPnt.drawImage((uOffsetX+movx)*ZoomRate,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,ImageList[Cnt]->Image->copy(0,-movy-uOffsetY+Y,-movx+uW-uOffsetX,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
			}
		}
	}
}

void MasterImg::DrawNGDot(QPainter &Pnt,QTableWidget *W,int Index,QList<QList<QPoint> > *pNGPointList,int Type)
{
	//マスター全体画像上にNGポイントを表示
	for(int Row=0;Row<W->rowCount();Row++){
		if(W->item(Row,Index)->text().toInt()==Type){
			for(int RowIndex=0;RowIndex<pNGPointList->at(Row).count();RowIndex++){
				int gX,gY;
				GetUniverseToCanvas(movx,movy,gmovx,gmovy);
				GetUniverseToCanvas(pNGPointList->at(Row).at(RowIndex).x(),pNGPointList->at(Row).at(RowIndex).y(),gX,gY);
				Pnt.fillRect(gX+gmovx-(NGDotWidth>>1),gY+gmovy-(NGDotWidth>>1),NGDotWidth,NGDotWidth,NGDotColor);
			}
		}
	}
}

void MasterImg::DrawPieceRect(QPainter &Pnt)
{
	//表示エリア矩形の描画
	Pnt.setPen(QPen(PieceRectColor,PieceRectWidth,PieceRectStyle));
	Pnt.drawRect(RectX+gmovx,RectY+gmovy,RectWidth,RectHeight);
}
*/
