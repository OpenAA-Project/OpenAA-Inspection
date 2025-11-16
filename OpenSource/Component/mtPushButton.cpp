/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtPushButtonColored.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
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