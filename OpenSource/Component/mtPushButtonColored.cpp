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
#include "mtPushButtonColored.h"
#include "XGeneralFunc.h"
#include "swap.h"

mtPushButtonColored::mtPushButtonColored(QWidget *parent)
:QPushButton(parent)
{
	QPalette P=palette();
	Col=P.color(QPalette::Button);
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}
mtPushButtonColored::mtPushButtonColored(const QColor &col ,QWidget *parent)
	:QPushButton(parent)
{
	setColor(col);
}
mtPushButtonColored::~mtPushButtonColored(void)
{
	disconnect(this,SLOT(SlotClicked()));
}
QColor	mtPushButtonColored::color(void)
{
	return Col;
}
void	mtPushButtonColored::setColor(const QColor &col)
{
	Col=col;
	QPalette P=palette();
	P.setColor(QPalette::Button,Col);
	setPalette(P);
	repaint();
}

void	mtPushButtonColored::setColor(const QString &ColString)
{
	QColor	col=QString2QColor(ColString);
	setColor(col);
}

void	mtPushButtonColored::SlotClicked()
{
	QColor	col=QColorDialog::getColor (Col);
	if(col.isValid()==true){
		setColor(col);
	}
	emit	SignalClicked();
}

void	mtPushButtonColored::paintEvent ( QPaintEvent * event )
{
	QPainter	pnt(this);
	if(isChecked()==true){
		QBrush		B(Col);
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