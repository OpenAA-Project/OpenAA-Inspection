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

#include "XTypeDef.h"
#include "PasswordDragFrame.h"
#include <QDrag>

PasswordDragFrame::PasswordDragFrame(QWidget *parent)
:QFrame(parent), m_FilePath(/**/""), startPos(0, 0), m_pfo(NULL)
{
	QFrame::setFrameShadow(QFrame::Raised);
	QFrame::setFrameShape(QFrame::Box);
}

//�}�E�X���������Ƃ��ɌĂяo�����鉼�z�֐�
void PasswordDragFrame::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
		startPos = event->pos();
	QFrame::mousePressEvent(event);
}

//�h���b�O�J�n���ɌĂяo�����鉼�z�֐�
void PasswordDragFrame::mouseMoveEvent(QMouseEvent * event)
{
	if(event->buttons() & Qt::LeftButton){
		int distance = (event->pos() - startPos).manhattanLength();
		if(distance >= QApplication::startDragDistance())
			startDrag();//���ۂ̃h���b�O�J�n
	}
	QFrame::mouseMoveEvent(event);
}

//�h���b�O�J�n
void PasswordDragFrame::startDrag()
{
	QDrag *drag = new QDrag(this);
	PasswordMimeData *mimeData = new PasswordMimeData;

	//QString appPath = qApp->applicationFilePath();
	//appPath = appPath.left(appPath.findRev('.')) + ".pwd";

	mimeData->setText("Password");
	mimeData->setDragFrame(this);
	drag->setMimeData(mimeData);
	QPixmap pix(/**/"images/dragpict.png");
	drag->setPixmap(pix);
	drag->exec();
}

QString PasswordDragFrame::PasswordFilePath()
{
	QString passFileName = qApp->applicationFilePath();
	passFileName = passFileName.left(passFileName.lastIndexOf('.')) + /**/".pwd";
	return passFileName;
}

//�`���C�x���g
void PasswordDragFrame::paintEvent(QPaintEvent* event)
{
	QPixmap pix(/**/"images/dragpict.png");

	QPainter paint;
	paint.begin(this);
	paint.drawPixmap(0, 0, pix);
	paint.end();

	QFrame::paintEvent(event);
}

void PasswordDragFrame::setPasswordFileOperator(PasswordFileOperator *pfo)
{
	m_pfo = pfo;
}

void PasswordDragFrame::addItem(QString objectName)
{
	m_pfo->addItem(objectName);
}