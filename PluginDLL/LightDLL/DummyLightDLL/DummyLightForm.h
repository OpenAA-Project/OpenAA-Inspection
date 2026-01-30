/*
 * Copyright (C) 2023
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



#ifndef DUMMYLIGHTFORM_H
#define DUMMYLIGHTFORM_H

#include <QDialog>
#include "ui_DummyLightForm.h"

class DummyLightForm : public QDialog
{
	Q_OBJECT

public:
	DummyLightForm(QWidget *parent = 0);
	~DummyLightForm();

private:
	Ui::DummyLightFormClass ui;

private slots:
	void on_pushButtonTurnOff_clicked();
	void on_pushButtonTurnOn_clicked();
};

#endif // DUMMYLIGHTFORM_H