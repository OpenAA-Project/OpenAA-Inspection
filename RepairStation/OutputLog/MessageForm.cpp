/*
 * Copyright (C) 2012
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

#include "MessageForm.h"
#include <QDesktopWidget>

MessageForm::MessageForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//�\���ʒu�̐ݒ�
	if(parentWidget()==NULL){
		QDesktopWidget *q=QApplication::desktop();
		QRect R=q->availableGeometry ();
		//setGeometry((R.width ()-width ())/2 ,(R.height()-height())/2,width() ,height());
		move((R.width ()-width ())/2 ,(R.height()-height())/2);
	}
	else{
		QWidget	*s=parentWidget();
		//setGeometry((s->width ()-width ())/2 ,(s->height()-height())/2 ,width() ,height());
		move((s->width ()-width ())/2 ,(s->height()-height())/2);
	}

	//���ʂ̐ݒ�
	palette[0].setColor(QPalette::Window,QColor(Qt::magenta));
	palette[1].setColor(QPalette::Window,QColor(Qt::yellow));
	setPalette(palette[0]);

	//Timer
	Index=0;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//	timer->start(500);
}

MessageForm::~MessageForm()
{
	delete timer;
}

void MessageForm::SetBlink()
{
	if(timer->isActive()==false){
		timer->start(500);
	}
}

void MessageForm::update()
{
	Index^=1;
	setPalette(palette[Index]);
}