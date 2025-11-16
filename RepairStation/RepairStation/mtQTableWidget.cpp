/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\mtQTableWidget.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QKeyEvent>
#include <QHeaderView>
#include "mtQTableWidget.h"

mtQTableWidget::mtQTableWidget(QWidget *parent)
{
	wTime=WaitTime=0;
	EnableListControl=false;
}

mtQTableWidget::~mtQTableWidget()
{
}

void mtQTableWidget::SetEnableListControl(bool Enable)
{
	EnableListControl=Enable;
	setCornerButtonEnabled(!Enable);
	verticalHeader()->setEnabled(!Enable);
}

void mtQTableWidget::keyPressEvent(QKeyEvent *event)
{
	if(EnableListControl==true){
		return;
	}

    switch(event->key()){
		case Qt::Key_Left:
			emit SignalKeyLeft();
			break;
		case Qt::Key_Right:
			if(event->isAutoRepeat()==true){
				break;
			}
			emit SignalKeyRight();
			break;
		case Qt::Key_Down:
			if(clock()-wTime<WaitTime){
				break;
			}
			if(event->isAutoRepeat()==true){
				break;
			}
			QTableWidget::keyPressEvent(event);
			wTime=clock();
/*
			if(GetTickCount()-wTime<WaitTime)
				break;
			QTableWidget::keyPressEvent(event);
			wTime=GetTickCount();
*/
			break;
		case Qt::Key_Return:
		case Qt::Key_Enter:
			if(event->isAutoRepeat()==true){
				break;
			}
			emit SignalKeyEnter();
			break;
/*		case Qt::Key_Print:
			//NG‰æ‘œ‚Ì•Û‘¶
			emit SignalKeyInsert();
			break;
*/
		case Qt::Key_Insert:
			//NG‰æ‘œ‚Ì•Û‘¶
			if(event->modifiers()==Qt::AltModifier)
				emit SignalKeyInsertAll();
			else
				emit SignalKeyInsert();
			break;
		default:
			QTableWidget::keyPressEvent(event);
			break;
	}
}

void mtQTableWidget::mousePressEvent(QMouseEvent *event)
{
	if(EnableListControl==true){
		return;
	}
	QTableWidget::mousePressEvent(event);
}

void mtQTableWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if(EnableListControl==true){
		return;
	}
	QTableWidget::mouseDoubleClickEvent(event);
}

void mtQTableWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(EnableListControl==true){
		return;
	}
	QTableWidget::mouseMoveEvent(event);
}
