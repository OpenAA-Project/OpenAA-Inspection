/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtToolButtonColored.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QColorDialog>
#include "mtToolButtonColored.h"
#include "XGeneralFunc.h"
#include "swap.h"

mtToolButtonColored::mtToolButtonColored(bool _ColorDialogOnLClick ,QWidget *parent)
:QToolButton(parent)
{
	ColorDialogOnLClick	=_ColorDialogOnLClick;
	QPalette P=palette();
	Col=P.color(QPalette::Button);
	PressedCol=Col;
	setCheckable(true);

	Pressed=false;
	TM.setInterval(200);
	TM.setSingleShot(true);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
}
mtToolButtonColored::mtToolButtonColored(bool _ColorDialogOnLClick ,const QColor &col ,QWidget *parent)
{
	ColorDialogOnLClick	=_ColorDialogOnLClick;
	Col=col;
	PressedCol=Col;
	setCheckable(true);

	Pressed=false;
	TM.setInterval(200);
	TM.setSingleShot(true);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
}
mtToolButtonColored::~mtToolButtonColored(void)
{
	disconnect(this,SLOT(SlotTimeOut()));
}

QColor	mtToolButtonColored::color(void)	const
{
	return Col;
}
void	mtToolButtonColored::setColor(const QColor &col)
{
	Col=col;
	PressedCol=Col;
	QPalette P=palette();
	P.setColor(QPalette::Active ,QPalette::Button,Col);
	setPalette(P);

	P.setColor(QPalette::Inactive ,QPalette::Button,Col);
	setPalette(P);

	repaint();
}

void	mtToolButtonColored::setColor(const QString &ColString)
{
	QColor	col=QString2QColor(ColString);
	setColor(col);
}
void	mtToolButtonColored::setPressedColor(const QColor &col)
{
	PressedCol=col;
	QPalette P=palette();
	P.setColor(QPalette::Active ,QPalette::Button,Col);
	setPalette(P);

	repaint();
}

void	mtToolButtonColored::mousePressEvent ( QMouseEvent * event )
{
	mtButtonWithBalloonBase::MousePressEvent();
	QToolButton::mousePressEvent(event);
	if(ColorDialogOnLClick==false && (event->button() & Qt::RightButton)!=0){
		QColor	col=QColorDialog::getColor (Col);
		if(col.isValid()==true){
			setColor(col);
			emit	colorChanged();
		}		
	}
	else{
		if(isCheckable()==false){
			Pressed=true;
		}
		TM.start();
		QToolButton::mousePressEvent ( event );
	}
}

void	mtToolButtonColored::paintEvent ( QPaintEvent * event )
{
	QPainter	pnt(this);
	if(isChecked()==true || Pressed==true){
		QBrush		B(PressedCol);
		pnt.fillRect ( event->rect(), B);
		QColor	cframe(Col.red()/3,Col.green()/3,Col.blue()/3);
		pnt.setPen(cframe);
		pnt.drawLine(0,0,0,event->rect().height()-1);
		pnt.drawLine(0,0,event->rect().width()-1,0);
		pnt.drawLine(1,1,1,event->rect().height()-2);
		pnt.drawLine(1,1,event->rect().width()-2,1);
		QColor	bframe(min(255,Col.red()*2),min(255,Col.green()*2),min(255,Col.blue()*2));
		pnt.setPen(bframe);
		pnt.drawLine(event->rect().width()-1,0,event->rect().width()-1,event->rect().height()-1);
		pnt.drawLine(0,event->rect().height()-1,event->rect().width()-1,event->rect().height()-1);
		pnt.drawLine(event->rect().width()-2,1,event->rect().width()-2,event->rect().height()-2);
		pnt.drawLine(1,event->rect().height()-2,event->rect().width()-2,event->rect().height()-2);
	}
	else{
		QBrush		B(Col);
		pnt.fillRect ( event->rect(), B);
		QColor	cframe(Col.red()/3,Col.green()/3,Col.blue()/3);
		pnt.setPen(cframe);
		pnt.drawLine(event->rect().width()-1,0,event->rect().width()-1,event->rect().height()-1);
		pnt.drawLine(0,event->rect().height()-1,event->rect().width()-1,event->rect().height()-1);
		pnt.drawLine(event->rect().width()-2,1,event->rect().width()-2,event->rect().height()-2);
		pnt.drawLine(1,event->rect().height()-2,event->rect().width()-2,event->rect().height()-2);
		QColor	bframe(min(255,Col.red()*2),min(255,Col.green()*2),min(255,Col.blue()*2));
		pnt.setPen(bframe);
		pnt.drawLine(0,0,0,event->rect().height()-1);
		pnt.drawLine(0,0,event->rect().width()-1,0);
		pnt.drawLine(1,1,1,event->rect().height()-2);
		pnt.drawLine(1,1,event->rect().width()-2,1);
	}
	QBrush		B(Qt::black);
	pnt.setBrush(B);
	pnt.setPen(Qt::black);
	pnt.drawText ( 3,3,width()-3,height()-3, Qt::AlignHCenter | Qt::AlignVCenter, text());

	if(icon().isNull()==false){
		QPixmap	Icn=icon().pixmap(width()*2/3,height()*2/3);
		pnt.drawPixmap(2,2,Icn);
	}
}

void	mtToolButtonColored::SlotTimeOut()
{
	if(isCheckable()==false){
		Pressed=false;
	}
	repaint();
}


void mtToolButtonColored::closeEvent ( QCloseEvent * event )
{
	mtButtonWithBalloonBase::Close();
	QToolButton::closeEvent (event );
}

void	mtToolButtonColored::mouseMoveEvent ( QMouseEvent * event )
{
	mtButtonWithBalloonBase::MouseMoveEvent (event);
}

void mtToolButtonColored::enterEvent ( QEnterEvent * event )
{
	mtButtonWithBalloonBase::EnterEvent(this);
}

void	mtToolButtonColored::SlotMessageMouseMove(int x ,int y)
{
	closeBalloon();
}
