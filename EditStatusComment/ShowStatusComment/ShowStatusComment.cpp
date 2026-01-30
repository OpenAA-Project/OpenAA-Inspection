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

#include "ShowStatusComment.h"
#include "XStatusController.h"
#include "XGeneralFunc.h"
#include "XParamGlobal.h"
#include <QGuiApplication>

ShowStatusComment::ShowStatusComment(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ConnectedOnce=false;
	Sock=new QLocalSocket(this);
	bool	Ret;
	Ret=(connect(Sock,SIGNAL(readyRead())		,this,SLOT(SlotReadyRead())))?true:false;
	Ret=(connect(Sock,SIGNAL(disconnected())	,this,SLOT(SlotDisconnected())))?true:false;

	TM.setSingleShot(false);
	TM.setInterval(2000);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

ShowStatusComment::~ShowStatusComment()
{
	delete	Sock;
}

void	ShowStatusComment::SlotTimeOut()
{
	if(Sock->state()!=QLocalSocket::ConnectedState){
		Sock->connectToServer ( /**/"StatusComment" );
	}
	else{
		ConnectedOnce=true;
	}
}

void ShowStatusComment::resizeEvent ( QResizeEvent * event )
{
	ui.textEdit->resize(width(),height());
}

void	ShowStatusComment::SlotDisconnected()
{
	if(ConnectedOnce==true){
		close();
	}
}

void	ShowStatusComment::SlotReadyRead()
{
	int32	Len;
	if(Sock->read((char *)&Len,sizeof(Len))!=sizeof(Len))
		return;
	QByteArray	A=Sock->readAll();
	if(A.size()!=Len)
		return;
	CommentOpinion	C;
	QBuffer	Buff(&A);
	if(Buff.open(QIODevice::ReadOnly)==false)
		return;
	if(C.Load(&Buff)==false)
		return;
	if(C.IsHTML()==true){
		ui.textEdit->setHtml(C.GetCommentString());
	}
	else{
		ui.textEdit->setText(C.GetCommentString());
	}
}
void ShowStatusComment::closeEvent ( QCloseEvent * event )
{
	OutputPosition();
}

void	ShowStatusComment::OutputPosition(void)
{
	int	PosX;
	int	PosY;
	QString	FileName=GetPositionFileName();
	QFile	F(FileName);
	if(F.open(QIODevice::WriteOnly)==true){
		PosX=geometry().left();
		PosY=geometry().top();
		if(::Save(&F,PosX)==false){
			return;
		}
		if(::Save(&F,PosY)==false){
			return;
		}
		int	W=geometry().width();
		int	H=geometry().height();
		if(::Save(&F,W)==false){
			return;
		}
		if(::Save(&F,H)==false){
			return;
		}
	}
}

void ShowStatusComment::showEvent ( QShowEvent * event )
{
	int	PosX,PosY;
	QString	FileName=GetPositionFileName();
	QFile	F(FileName);
	if(F.open(QIODevice::ReadOnly)==true){
		if(::Load(&F,PosX)==false){
			return;
		}
		if(::Load(&F,PosY)==false){
			return;
		}
		int	W,H;
		if(::Load(&F,W)==false){
			return;
		}
		if(::Load(&F,H)==false){
			return;
		}		//move(PosX,PosY);

		QScreen	*Scr=qGuiApp->screens()[0];
		//QRect R=s->availableGeometry ();
		int	MaxW=Scr->geometry().width();
		int	MaxH=Scr->geometry().height();
		if(32<=W && W<MaxW && 32<H && H<MaxH
			&& 0<(PosX+W) && PosX<MaxW && 0<(PosY+H) && PosY<MaxH){
			setGeometry(PosX,PosY,W,H);
		}
	}
}