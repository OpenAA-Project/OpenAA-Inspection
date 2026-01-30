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

#ifndef ERRORFORM_H
#define ERRORFORM_H

#include <QWidget>
#include <QTimer>
#include "ui_ErrorForm.h"

class ErrorForm : public QWidget
{
	Q_OBJECT

public:
//	ErrorForm(const QString &KibanNo,QWidget *parent = 0);			//D-20091106
	ErrorForm(const QString &KibanNo,int Code,QWidget *parent = 0);	//A-20091106
	~ErrorForm();

private slots:
	void	update();

private:
	Ui::ErrorFormClass ui;
	QTimer *timer;
	QPalette palette[2];
	char	Index;
};

#endif // ERRORFORM_H