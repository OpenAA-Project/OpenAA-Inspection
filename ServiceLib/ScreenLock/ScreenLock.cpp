/*
 * Copyright (C) 2025
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

#include "ScreenLock.h"
#include <QSizePolicy>
#include <QGuiApplication>
#include <QScreen>

extern	bool	CloseAfterPassword;

ScreenLock::ScreenLock(const QString &_Password , const QString &title 
						,int _BreakTime
						,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),Password(_Password),BreakTime(_BreakTime)
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	ui.setupUi(this);
	move(0,0);

	ui.LabelTitle->move(0,0);
	ui.LabelTitle->setText(title);

	TM.setInterval(BreakTime*1000);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.setSingleShot(true);
}

ScreenLock::~ScreenLock()
{

}

void ScreenLock::showEvent ( QShowEvent * event )
{
	QScreen	*Scr=qGuiApp->screens()[0];
	setFixedSize(Scr->geometry().width(),Scr->geometry().height());
	ui.LabelTitle->resize(width(),30);

	int	Lx=(Scr->geometry().width() -ui.frame->width())/2;
	int	Ly=(Scr->geometry().height()-ui.frame->height())/2;

	ui.frame->move(Lx,Ly);
}

void ScreenLock::on_pushButtonOK_clicked()
{
	QString	Str=ui.lineEditPassword->text();
	if(Password==Str){
		TM.start();
		setFixedSize(100,50);
		resize(100,50);
		if(CloseAfterPassword==true){
			close();
		}
	}
}

void	ScreenLock::SlotTimeOut()
{
	QScreen	*Scr=qGuiApp->screens()[0];
	setFixedSize(Scr->geometry().width(),Scr->geometry().height());
	resize(Scr->geometry().width(),Scr->geometry().height());
	ui.lineEditPassword->setText(/**/"");
}