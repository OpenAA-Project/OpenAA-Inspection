/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtToolButtonWithBalloon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include"mtToolButtonWithBalloon.h"
#include<QMouseEvent>


mtToolButtonWithBalloon::mtToolButtonWithBalloon(QWidget *parent) : QToolButton(parent)
{
	setMouseTracking(true);
	//connect(&MessageWindow,SIGNAL(SignalMouseMove(int,int)),this,SLOT(SlotMessageMouseMove(int,int)));
}
mtToolButtonWithBalloon::~mtToolButtonWithBalloon()
{
}


void mtToolButtonWithBalloon::closeEvent ( QCloseEvent * event )
{
	mtButtonWithBalloonBase::Close();
	QToolButton::closeEvent (event );
}

void	mtToolButtonWithBalloon::mousePressEvent ( QMouseEvent * event )
{
	mtButtonWithBalloonBase::MousePressEvent();
	QToolButton::mousePressEvent(event);
	if(event->button()==Qt::RightButton){
		emit	RClick(event);
	}
}

void	mtToolButtonWithBalloon::mouseMoveEvent ( QMouseEvent * event )
{
	mtButtonWithBalloonBase::MouseMoveEvent (event);
}

void mtToolButtonWithBalloon::enterEvent ( QEnterEvent * event )
{
	mtButtonWithBalloonBase::EnterEvent(this);
}


void	mtToolButtonWithBalloon::SlotMessageMouseMove(int x ,int y)
{
	closeBalloon();
}


