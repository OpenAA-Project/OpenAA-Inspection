#include "DisplayNGListButtonResource.h"
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
			//サムネイル時、拡大対応
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
				//履歴Formの表示対応
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
				//履歴の削除対応
				emit SignalKeyDelete();
			}
			break;
		default:
			QTableWidget::keyReleaseEvent(event);
			break;
	}
}
