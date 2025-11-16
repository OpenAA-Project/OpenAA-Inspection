/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtColorFrame.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "mtColorFrame.h"
#include<QPainter>
#include<QBrush>

mtColorFrame::mtColorFrame( QWidget * parent, Qt::WindowFlags f)
:QFrame(parent, f)
{
}

void mtColorFrame::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);
	QBrush	B(BaseColor);
	Pnt.setBrush(B);
	Pnt.drawRect(0,0,width(),height());
}

void	mtColorFrame::SetColor(const QColor &col)
{
	BaseColor=col;
	repaint();
}
