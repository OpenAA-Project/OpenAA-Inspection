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

#include "mtImageToolButtonWithBalloon.h"

mtImageToolButtonWithBalloon::mtImageToolButtonWithBalloon(const QImage &_img, QWidget *parent)
	: mtImageToolButton(_img,parent)
{
	setMouseTracking(true);
}

mtImageToolButtonWithBalloon::~mtImageToolButtonWithBalloon()
{

}

void mtImageToolButtonWithBalloon::closeEvent(QCloseEvent *event) {
	mtButtonWithBalloonBase::Close();
}

void mtImageToolButtonWithBalloon::mousePressEvent(QMouseEvent *event) 
{
	mtButtonWithBalloonBase::MousePressEvent();
	mtImageToolButton::mousePressEvent(event);
	if(event->button()==Qt::RightButton){
		emit	RClick(event);
	}
}
void mtImageToolButtonWithBalloon::mouseDoubleClickEvent(QMouseEvent *event)
{
	mtImageToolButton::mouseDoubleClickEvent(event);
	emit	LDoubleClick(event);
}

void mtImageToolButtonWithBalloon::mouseMoveEvent(QMouseEvent *event) {
	mtButtonWithBalloonBase::MouseMoveEvent(event);
}

void mtImageToolButtonWithBalloon::enterEvent(QEnterEvent *event) {
	mtButtonWithBalloonBase::EnterEvent(this);
}

void mtImageToolButtonWithBalloon::SlotMessageMouseMove(int x, int y) {
	closeBalloon();
}