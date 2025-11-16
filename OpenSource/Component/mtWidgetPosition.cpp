/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtWidgetPosition.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "mtWidgetPosition.h"

mtWidgetPosition::mtWidgetPosition(QWidget * parent)
:QWidget(parent),AOWData(_None)
{
	//if(parent!=NULL)
	//	connect(parent,SIGNAL(geometryChanged()),this,SLOT(On_geometryChanged()));
	setMouseTracking(true);
}

void	mtWidgetPosition::SetAOW(AlighmentOfWidget data)
{
	AOWData=data;
	SetWindowPos();
}

void	mtWidgetPosition::SetWindowPos(void)
{
	if(parentWidget()==NULL){
		return;
	}
	switch(AOWData){
		case _None:
			break;
		case _Client:
			move(0,0);
			resize(parentWidget()->width(),parentWidget()->height());
			break;
		case _Left	:
			move(0,y());
			break;
		case _Right	:
			move(parentWidget()->width()-width(),y());
			break;
		case _Top	:
			move(x(),0);
			break;
		case _Bottom:
			move(x(),parentWidget()->height()-height());
			break;
	}
}

void mtWidgetPosition::resizeEvent ( QResizeEvent * event )
{
	QWidget::resizeEvent ( event );
	SetWindowPos();
}

void	mtWidgetPosition::On_geometryChanged()
{
	SetWindowPos();
}
void mtWidgetPosition::enterEvent ( QEnterEvent * event )
{
	emit	SignalEnter();
}
void mtWidgetPosition::leaveEvent ( QEvent * event )
{
	emit	SignalLeave();
}
