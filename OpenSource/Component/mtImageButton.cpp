/*
 * Copyright (C) 2020
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

#include "mtImageButton.h"

mtImageButton::mtImageButton(const QImage &_img, QWidget *parent)
	: QPushButton(parent),TM(this)
{
	img = _img;
	nDrawX = 0;
	nDrawY = 0;
	setImage();
	//resize(img.width(),img.height());
	connect(this,SIGNAL(clicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(&TM,SIGNAL(timeout()),this,SLOT(TimeOutOneShot()));
	TM.setSingleShot(true);
	TM.setInterval(250);
}

mtImageButton::~mtImageButton()
{
	disconnect(this,SLOT(SlotClicked(bool)));
	disconnect(this,SLOT(TimeOutOneShot()));
}

void mtImageButton::paintEvent(QPaintEvent *evt)
{
	QPainter pnt2(this);
	pnt2.drawImage(nDrawX,nDrawY,img);
}

void mtImageButton::mousePressEvent(QMouseEvent *evt)
{
	QPoint pnt = evt->pos();
	QRgb rgb1 = img.pixel(pnt.x(),pnt.y());
	QColor col = QColor::fromRgba(rgb1);
	if ( col.alpha() == 0 ) { //&& col.red() == 0 && col.green() == 0 && col.blue() == 0 ) {
		return;
	}
	nDrawX = 3;
	nDrawY = 3;
	repaint();
}

void mtImageButton::mouseReleaseEvent(QMouseEvent *evt)
{
	nDrawX = 0;
	nDrawY = 0;
	repaint();
	emit SignalClicked();
}
void	mtImageButton::click ()
{
	nDrawX = 3;
	nDrawY = 3;
	repaint();
	TM.start();
	emit SignalClicked();
}

void mtImageButton::SlotClicked(bool checked)
{
	click ();
}

void	mtImageButton::TimeOutOneShot()
{
	nDrawX = 0;
	nDrawY = 0;
	repaint();
}