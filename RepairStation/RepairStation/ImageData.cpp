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



#include "ImageData.h"
#include <QMouseEvent>
#include <QPainter>


//********************************************
//�@�}�X�^�[�摜�i�[�N���X
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
	//���`�I�����ɃN���b�N�̕�����������
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
		//�P�����N���b�N
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
	//�摜�̕`��
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
			//�I�����`���摜���Ɏ��܂��ꍇ
			if(-movx>=uOffsetX && (-movx+uW)<=(uOffsetX+ImageW) && -movy>=uOffsetY && (-movy+uH)<=(uOffsetY+ImageH))
				MPnt.drawImage(0,0,ImageList[Cnt]->Image->copy(-movx-uOffsetX,-movy-uOffsetY,uW,uH).transformed(matrix));
			else{
				int X,Y,W,H;
				//�I�����`���摜�̉E�[���܂����ꍇ
				if(-movx<(uOffsetX+ImageW) && (-movx+uW)>(uOffsetX+ImageW) && (-movy+uH)>=uOffsetY && -movy<(uOffsetY+ImageH))
					MPnt.drawImage(0,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,ImageList[Cnt]->Image->copy(-movx-uOffsetX,-movy-uOffsetY+Y,uOffsetX+ImageW+movx,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
				//�I�����`���摜�̍��[���܂����ꍇ
				else if(-movx<uOffsetX && (-movx+uW)>uOffsetX && (-movy+uH)>=uOffsetY && -movy<(uOffsetY+ImageH))
					MPnt.drawImage((uOffsetX+movx)*ZoomRate,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,ImageList[Cnt]->Image->copy(0,-movy-uOffsetY+Y,-movx+uW-uOffsetX,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
				//�I�����`���摜�̉��[���܂����ꍇ
				else if(-movy<(uOffsetY+ImageH) && (-movy+uH)>(uOffsetY+ImageH) && (-movx+uW)>=uOffsetX && -movx<(uOffsetX+ImageW))
					MPnt.drawImage((uOffsetX+movx)*ZoomRate,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,ImageList[Cnt]->Image->copy(0,-movy-uOffsetY+Y,-movx+uW-uOffsetX,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
				//�I�����`���摜�̏��[���܂����ꍇ
				else if(-movy<uOffsetY && (-movy+uH)>uOffsetY && (-movx+uW)>=uOffsetX && -movx<(uOffsetX+ImageW))
					MPnt.drawImage((uOffsetX+movx)*ZoomRate,Y=(-movy<uOffsetY) ? (uOffsetY+movy)*ZoomRate : 0,ImageList[Cnt]->Image->copy(0,-movy-uOffsetY+Y,-movx+uW-uOffsetX,((-movy+uH)>(H=uOffsetY+ImageH)) ? H+movy : uH-Y).transformed(matrix));
			}
		}
	}
}

void MasterImg::DrawNGDot(QPainter &Pnt,QTableWidget *W,int Index,QList<QList<QPoint> > *pNGPointList,int Type)
{
	//�}�X�^�[�S�̉摜����NG�|�C���g���\��
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
	//�\���G���A���`�̕`��
	Pnt.setPen(QPen(PieceRectColor,PieceRectWidth,PieceRectStyle));
	Pnt.drawRect(RectX+gmovx,RectY+gmovy,RectWidth,RectHeight);
}
*/