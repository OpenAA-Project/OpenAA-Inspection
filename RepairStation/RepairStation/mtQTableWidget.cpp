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
			//NG�摜�̕ۑ�
			emit SignalKeyInsert();
			break;
*/
		case Qt::Key_Insert:
			//NG�摜�̕ۑ�
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