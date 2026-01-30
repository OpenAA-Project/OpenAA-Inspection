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

#include "mtImageToolButtonColored.h"
#include "XGeneralFunc.h"
#include <QPalette>

#define BLEND_ALPHA 0.5

mtImageToolButtonColored::mtImageToolButtonColored(QWidget *parent, bool checked)
	: mtImageToolButton(parent,checked)
{
	nBlend_Alfa = BLEND_ALPHA;
	img2 = img;
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
	setMouseTracking(true);
}

mtImageToolButtonColored::mtImageToolButtonColored(const QImage &_img, const QColor &_col, QWidget *parent, bool checked)
	: mtImageToolButton(_img,parent,checked)
{
	nBlend_Alfa = BLEND_ALPHA;
	img2 = img;
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
	setMouseTracking(true);

	setColor(_col);
	setMouseTracking(true);
}

mtImageToolButtonColored::mtImageToolButtonColored(const QImage &_img, QWidget *parent, bool checked)
	: mtImageToolButton(_img,parent,checked)
{
	nBlend_Alfa = BLEND_ALPHA;
	img2 = img;
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
	setMouseTracking(true);

	QPalette P=palette();
	Col = P.color(QPalette::Button);
	setMouseTracking(true);
}

mtImageToolButtonColored::~mtImageToolButtonColored()
{
	disconnect(this,SLOT(SlotClicked()));
}

void mtImageToolButtonColored::setImageBmpColored(const QImage &_img)
{
	QPalette P=palette();
	Col = P.color(QPalette::Button);

	mtImageToolButton::setImageBmp(_img);
	img2 = img;
}

QColor mtImageToolButtonColored::color() const
{
	return Col;
}

void mtImageToolButtonColored::setColor(const QColor &col)
{
	Col = col;
	//setImageCombine(img);
	//PressedImg = img;

	QImage wimg;
	wimg=img.convertToFormat(QImage::Format_ARGB32);
	wimg.fill(((uint)Col.rgb()) | 0x8f000000);
	PressedImg=img.convertToFormat(QImage::Format_ARGB32);
	QPainter	pnt(&PressedImg);
	pnt.drawImage(0,0,wimg);
	repaint();
}

void mtImageToolButtonColored::setColor(const QString &ColString)
{
	QColor col=QString2QColor(ColString);
	setColor(col);
}

void mtImageToolButtonColored::setPressedColor(const QColor &col) {
	Col = col;
	setImageCombine(PressedImg);
	repaint();
/*
	//PressedImg�̕ۑ�
	PressedImg.save("PressedImg2.bmp","BMP");
*/
}

void mtImageToolButtonColored::setPressedColor(const QString &ColString) {
	QColor col=QString2QColor(ColString);
	setColor(col);
}

void mtImageToolButtonColored::DrawNormalColor() {
	wImg=&img;
	repaint();
}

void mtImageToolButtonColored::DrawPressedColor() {
	wImg=&PressedImg;
	repaint();
}

void mtImageToolButtonColored::setImageCombine(QImage &image) 
{
/*
	//img2�̕ۑ�
	img2.save("img2.bmp","BMP");
*/
	QRgb rgb0, rgb1, rgb2=Col.rgb();
	for( int i=0; i<img2.width(); i++ ) {
		QColor cl;
		for( int j=0; j<img2.height(); j++ ) {
			rgb1 = img2.pixel(i,j);
			if ( qAlpha(rgb1) != 0 ) {
				int r = qRed(rgb1);
				int g = qGreen(rgb1);
				int b = qBlue(rgb1);
				r = (int)(nBlend_Alfa*r+(1-nBlend_Alfa)*qRed(rgb2));
				g = (int)(nBlend_Alfa*g+(1-nBlend_Alfa)*qGreen(rgb2));
				b = (int)(nBlend_Alfa*b+(1-nBlend_Alfa)*qBlue(rgb2));
				cl = QColor(r,g,b);
				rgb0 = cl.rgb();
				image.setPixel(i,j,rgb0);
			} else {
				image.setPixel(i,j,rgb1);
			}
		}
	}
}


void mtImageToolButtonColored::closeEvent(QCloseEvent *event)
{
	mtButtonWithBalloonBase::Close();
}

void mtImageToolButtonColored::mousePressEvent(QMouseEvent *event) 
{
	mtButtonWithBalloonBase::MousePressEvent();
	mtImageToolButton::mousePressEvent(event);
	if(event->button()==Qt::RightButton){
		emit	RClick(event);
	}
}

void mtImageToolButtonColored::mouseMoveEvent(QMouseEvent *event)
{
	mtButtonWithBalloonBase::MouseMoveEvent(event);
	mtImageToolButton::mouseMoveEvent(event);
}

void mtImageToolButtonColored::enterEvent(QEnterEvent *event)
{
	mtButtonWithBalloonBase::EnterEvent(this);
	mtImageToolButton::enterEvent(event);
}

void mtImageToolButtonColored::SlotMessageMouseMove(int x, int y) {
	closeBalloon();
}