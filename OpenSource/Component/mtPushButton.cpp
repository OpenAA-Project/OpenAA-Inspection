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

#include <QColorDialog>
#include "mtPushButton.h"
#include "XGeneralFunc.h"

mtPushButton::mtPushButton(QWidget *parent)
:QPushButton(parent)
{
	QPalette P=palette();
	NormalCol=P.color(QPalette::Button);
	PushedCol=P.color(QPalette::Button);

}
mtPushButton::mtPushButton(const QColor &normalcol,const QColor &pushedcol ,QWidget *parent)
	:QPushButton(parent)
{
	setColor(normalcol,pushedcol);
}
	
QColor	mtPushButton::NormalColor(void)
{
	return NormalCol;
}
QColor	mtPushButton::PushedColor(void)
{
	return PushedCol;
}

void	mtPushButton::setColor(const QColor &normalcol,const QColor &pushedcol)
{
	NormalCol=normalcol;
	PushedCol=pushedcol;
	QPalette P=palette();
	P.setColor(QPalette::Button,NormalCol);
	setPalette(P);
	repaint();
}

void mtPushButton::mousePressEvent ( QMouseEvent * Ev )
{
	bool	RightClicked	= ((Ev->buttons() & Qt::RightButton)!=0) ? true : false;
	if(RightClicked==true){
		emit	SignalRightClick();
	}
	else{
		QPushButton::mousePressEvent ( Ev );
	}
}