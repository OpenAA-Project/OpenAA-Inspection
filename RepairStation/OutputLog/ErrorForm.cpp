/*
 * Copyright (C) 2021
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

#include "ErrorForm.h"
#include <QDesktopWidget>

//ErrorForm::ErrorForm(const QString &KibanNo,QWidget *parent)			//D-20091106
ErrorForm::ErrorForm(const QString &KibanNo,int Code,QWidget *parent)	//A-20091106
	: QWidget(parent)
{
	ui.setupUi(this);

//	//表示位置の設定
//	move(500,30);

	//表示位置の設定
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

	//画面の設定
	palette[0].setColor(QPalette::Window,QColor(Qt::red));
	palette[1].setColor(QPalette::Window,QColor(Qt::yellow));
	setPalette(palette[0]);

	//メッセージラベルの表示設定
	QString MessageText;
	MessageText	="LOT数 ";
	MessageText+=QString::number(KibanNo.toInt());
	ui.lbMessage3_1->setText(MessageText);

	if(Code==1){										//A-20091106
		ui.lbMessage_2->setVisible(false);				//A-20091106
	}													//A-20091106

	//Timer
	Index=0;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(500);
}

ErrorForm::~ErrorForm()
{
	delete timer;
}

void ErrorForm::update()
{
	Index^=1;
	setPalette(palette[Index]);
}