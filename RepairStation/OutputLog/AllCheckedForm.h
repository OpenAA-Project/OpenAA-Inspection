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

#ifndef ALLCHECKEDFORM_H
#define ALLCHECKEDFORM_H

#include <QWidget>
#include <QTimer>
#include "ui_AllCheckedForm.h"

class AllCheckedForm : public QWidget
{
	Q_OBJECT

public:
	AllCheckedForm(QWidget *parent = 0);
	~AllCheckedForm();

	void	SetShowPickupEnable	(QString &KibanNo);
	void	SetShowMaxOverEnable(QString &KibanNo);

private slots:
	void	update();

private:
	Ui::AllCheckedFormClass ui;
	QTimer *timer;
	QPalette palette[2];
	char	Index;
};

#endif // ALLCHECKEDFORM_H