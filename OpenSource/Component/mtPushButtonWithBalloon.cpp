/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtPushButtonWithBalloon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include"mtPushButtonWithBalloon.h"
#include<QMouseEvent>


mtPushButtonWithBalloon::mtPushButtonWithBalloon(QWidget *parent) : QPushButton(parent)
{
	setMouseTracking(true);
	//connect(&MessageWindow,SIGNAL(SignalMouseMove(int,int)),this,SLOT(SlotMessageMouseMove(int,int)));
}
mtPushButtonWithBalloon::~mtPushButtonWithBalloon()
{
}


void mtPushButtonWithBalloon::closeEvent ( QCloseEvent * event )
{
	mtButtonWithBalloonBase::Close();
	QPushButton::closeEvent (event );
}

void	mtPushButtonWithBalloon::mousePressEvent ( QMouseEvent * event )
{
	mtButtonWithBalloonBase::MousePressEvent();
	QPushButton::mousePressEvent(event);
}

void	mtPushButtonWithBalloon::mouseMoveEvent ( QMouseEvent * event )
{
	mtButtonWithBalloonBase::MouseMoveEvent (event);
}

void mtPushButtonWithBalloon::enterEvent ( QEnterEvent * event )
{
	mtButtonWithBalloonBase::EnterEvent(this);
}

void	mtPushButtonWithBalloon::SlotMessageMouseMove(int x ,int y)
{
	closeBalloon();
}


