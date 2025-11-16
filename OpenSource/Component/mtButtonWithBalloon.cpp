/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\Component\mtButtonWithBalloon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "mtButtonWithBalloon.h"
#include <QApplication>

const	int	MessageWindowW=200;
const	int	MessageWindowH=40;
const	int	WaitingMilisec=500;
const	int	ShowingMilisec=2000;

mtBalloonWindow::mtBalloonWindow(QWidget *parent): QWidget(parent)
{
	setMouseTracking(true);
	QPalette P=palette();
	P.setColor(QPalette::Window,Qt::white);
	setPalette(P);		

	Label.setParent(this);
	Label.setGeometry(0,0,MessageWindowW,MessageWindowH);
	Label.setWordWrap (true);
	Label.setFrameShadow(QFrame::Sunken);
	Label.setFrameStyle (QFrame::Panel);
	Label.setBackgroundRole(QPalette::Light);
}

void mtBalloonWindow::mouseMoveEvent ( QMouseEvent * event )
{
	/*
	if(0<=event->x() && event->x()<width() && 0<=event->y() && event->y()<height()){
		emit	SignalMouseMove(event->x(),event->y());
	}
	*/
}

//=======================================================
void mtQTimer::Start ( int msec )
{
	Counter=0;
	start(msec/20);
}

void mtQTimer::timerEvent ( QTimerEvent * event )
{
	Counter++;
	if(Counter==20){
		BParent->TimerEvent();
	}
	else{
		BParent->CheckEvent();
	}
}

//=======================================================
mtButtonWithBalloonBase::mtButtonWithBalloonBase(void) 
: BallonTimer(this)
{
	Pushed=false;

	MThis	=NULL;
	BallonTimer.stop();
	Mode=_Leave;
	MessageWindow.resize(MessageWindowW,MessageWindowH);
	MessageWindow.setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	MessageWindow.hide();
	BallonTimer.setSingleShot(false);
}
mtButtonWithBalloonBase::~mtButtonWithBalloonBase(void)
{
}

void mtButtonWithBalloonBase::closeBalloon(void)
{
	if((Mode==_Waiting) || (Mode==_Showing)){
		BallonTimer.stop();
		MessageWindow.hide();
		Mode=_Off;
	}
}

void mtButtonWithBalloonBase::Close(void)
{
	BallonTimer.stop();
}

void	mtButtonWithBalloonBase::MousePressEvent()
{
	if(Mode==_Waiting){
		Close();
		MessageWindow.hide();
	}
	else if(Mode==_Showing){
		Close();
		MessageWindow.hide();
	}
	Mode=_Off;
	Pushed=true;
}
void	mtButtonWithBalloonBase::MouseMoveEvent ( QMouseEvent * event )
{
	if(Message.isEmpty()==true){
		return;
	}
	if(Pushed==true){
		return;
	}
	if(Mode==_Showing){
		MessageWindow.hide();
		return;
	}
	else if(Mode==_Waiting){
		return;
	}
	Mode=_Waiting;
	LastPoint		=event->pos();
	LastGlobalPoint	=event->globalPos();
	BallonTimer.stop();
	BallonTimer.Start(WaitingMilisec);
}

void mtButtonWithBalloonBase::EnterEvent ( QWidget *_this)
{
	MThis=_this;
	QWidget	*topParent=_this;
	while(topParent->parentWidget()!=NULL){
		topParent=topParent->parentWidget();
	}
	CloseChildBaloon(topParent,_this);
}


void	mtButtonWithBalloonBase::CheckEvent(void)
{
	QPoint Q=QCursor::pos();
	if(MThis!=NULL){
		QPoint Lq=MThis->mapFromGlobal(Q);
		if((Lq.x()<0) || (MThis->width()<Lq.x()) || (Lq.y()<0) || (MThis->height()<Lq.y())){
			MessageWindow.hide();
			Mode=_Off;
		}
	}
}

void mtButtonWithBalloonBase::CloseChildBaloon(QWidget *CurrentWidget ,QWidget *exceptionWindow)
{
	mtButtonWithBalloonBase	*m=dynamic_cast<mtButtonWithBalloonBase *>(CurrentWidget);
	if(m!=NULL){
		m->closeBalloon();
		m->Pushed=false;
	}
	for(int i=0;i<CurrentWidget->children().count();i++){
		QObject	*q=CurrentWidget->children().value(i);
		QWidget	*w=dynamic_cast<QWidget	*>(q);
		if(w!=exceptionWindow){
			if(w!=NULL){
				CloseChildBaloon(w ,exceptionWindow);
			}
		}
	}		
}

void mtButtonWithBalloonBase::TimerEvent (void)
{
	if(Mode==_Waiting){
		if(Pushed==false){
			MessageWindow.Label.setText(Message);
			QScreen	*Scr=qApp->screens()[0];
			if((LastGlobalPoint.x()+MessageWindow.width()+16)>=Scr->size().width()){
				MessageWindow.move(LastGlobalPoint.x()-MessageWindow.width()-16,LastGlobalPoint.y()+1);
			}
			else{
				MessageWindow.move(LastGlobalPoint.x()+16,LastGlobalPoint.y()+16);
			}
		
			MessageWindow.show();
			BallonTimer.Start(ShowingMilisec);
			Mode=_Showing;
		}
		else{
			Mode=_Off;
		}
	}
	else if(Mode==_Showing){
		MessageWindow.hide();
		Mode=_Off;
	}
	else{
		MessageWindow.hide();
		Mode=_Off;
	}
}

void	mtButtonWithBalloonBase::setMessage(const QString &msg)
{
	Message=msg;
}
