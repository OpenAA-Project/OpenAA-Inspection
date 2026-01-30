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

#include "DisplayNGListButtonResource.h"


#include <QKeyEvent>
#include <QHeaderView>
#include "mtQTableWidget.h"

mtQTableWidget::mtQTableWidget(QWidget *parent)
{
	wTime=WaitTime=0;
	RowList.clear();
	EnableListControl=false;
	IsSignalKeyDown=true;

	ThumbnailCount=1;
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

void  mtQTableWidget::ExecKeyPageUp()
{
	int mod=currentRow()%ThumbnailCount;
	if(mod==0){
		mod=ThumbnailCount;
	}
	selectRow(currentRow()-mod);
}

bool  mtQTableWidget::ExecKeyPageDown()
{
	int mod=currentRow()%ThumbnailCount;
	if(currentRow()+ThumbnailCount-mod>=rowCount()){
		return false;
	}
	selectRow(currentRow()+ThumbnailCount-mod);
	return true;
}

void mtQTableWidget::keyPressEvent(QKeyEvent *event)
{
	if(EnableListControl==true){
		return;
	}

    switch(event->key()){
		case Qt::Key_Up:
			if(event->isAutoRepeat()==true){
				break;
			}
			QTableWidget::keyPressEvent(event);
			break;
		case Qt::Key_Down:
			if(CheckRowList()==false){
				if(clock()-wTime < WaitTime){
					break;
				}
			}
			if(event->isAutoRepeat()==true){
				break;
			}
			emit	SignalKeyDown();
			if(IsSignalKeyDown==false){
				break;
			}
			QTableWidget::keyPressEvent(event);
			RowList.append(currentRow());
			wTime=clock();
			break;
		case Qt::Key_PageUp:
			if(event->isAutoRepeat()==true){
				break;
			}
			if(ThumbnailCount>1){
				ExecKeyPageUp();
				break;
			}
			QTableWidget::keyPressEvent(event);
			break;
		case Qt::Key_PageDown:
			if(CheckRowList()==false){
				if(clock()-wTime < WaitTime){
					break;
				}
			}
			if(event->isAutoRepeat()==true){
				break;
			}
			if(ThumbnailCount>1){
				if(ExecKeyPageDown()==false){
					break;
				}
			}
			else{
				QTableWidget::keyPressEvent(event);
			}
			RowList.append(currentRow());
			wTime=clock();
			break;
		case Qt::Key_Return:
		case Qt::Key_Enter:
			//�T���l�C�����A�g���Ή�
			if(event->isAutoRepeat()==true){
				break;
			}
			emit SignalKeyEnter();
			break;
		case Qt::Key_Right:
			if(event->isAutoRepeat()==true){
				break;
			}
			emit SignalKeyLR();
			break;
		case Qt::Key_Left:
			if(event->isAutoRepeat()==true){
				break;
			}
			emit SignalKeyLRReverse();
			break;
		case Qt::Key_Delete:
			if(event->isAutoRepeat()==true){
				//����Form�̕\���Ή�
				emit SignalKeyDeleteRepeat();
			}
			break;
		default:
			QTableWidget::keyPressEvent(event);
			break;
	}
}

void mtQTableWidget::keyReleaseEvent(QKeyEvent *event)
{
	if(EnableListControl==true){
		return;
	}

    switch(event->key()){
		case Qt::Key_Delete:
			if(event->isAutoRepeat()==false){
				//�����̍폜�Ή�
				emit SignalKeyDelete();
			}
			break;
		default:
			QTableWidget::keyReleaseEvent(event);
			break;
	}
}