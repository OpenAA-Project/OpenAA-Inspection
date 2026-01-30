/*
 * Copyright (C) 2022
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

#pragma once

#include <QApplication>
#include <QFrame>
#include <QFileInfo>
#include <QTextStream>
#include <QPainter>
#include <QPixmap>
//#include <QGlobal.h>
#include <QMouseEvent>
#include <QStringList>

#include "PasswordMimeData.h"//専用MimeData
#include "PasswordFileOperator.h"

//ドラッグ用クラス
class PasswordDragFrame : public QFrame
{
	Q_OBJECT

public:
	PasswordDragFrame(QWidget *parent);
//以下2つの関数はオーバーライド必須
protected:
	virtual	void mousePressEvent( QMouseEvent *event )	override;
	virtual	void mouseMoveEvent( QMouseEvent *event )	override;
	virtual	void paintEvent(QPaintEvent*)				override;

public:
	void setPasswordFileOperator(PasswordFileOperator *pfo);
	QString PasswordFilePath();
private:
	QString m_FilePath;
	void startDrag();
	QPoint startPos;
public:
	PasswordFileOperator *m_pfo;
public:
	void addItem(QString ItemName);
};