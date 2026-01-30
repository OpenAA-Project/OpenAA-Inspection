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

#ifndef JDTUNPACKER_H
#define JDTUNPACKER_H

#include <QDialog>
#include <QEvent>
#include "ui_jdtunpacker.h"

class JDTUnpacker : public QDialog
{
	Q_OBJECT

public:
	JDTUnpacker(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~JDTUnpacker();

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);

private:
	void setEnableInput(bool b);
	QString unpack(void);	//return path

private slots:
	void slotClickUnpack();
	void fileopen(void);


private:
	Ui::JDTUnpackerClass ui;
};

#endif // JDTUNPACKER_H