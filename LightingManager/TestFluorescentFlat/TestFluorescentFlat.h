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

#ifndef TESTFLUORESCENTFLAT_H
#define TESTFLUORESCENTFLAT_H

#include <QMainWindow>
#include "ui_TestFluorescentFlat.h"
#include "XFluorescentFlat.h"

class TestFluorescentFlat : public QMainWindow
{
	Q_OBJECT

	SystemLEDSheet	SystemData;

public:
	TestFluorescentFlat(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~TestFluorescentFlat();

private slots:
        void on_pushButtonSetAll_clicked();
        void on_pushButtonOK_clicked();

        void on_toolButtonOnOff_clicked();

private:
	Ui::TestFluorescentFlatClass ui;

	void	FromWindow(void);
	void	ToWindow(void);

};

#endif // TESTFLUORESCENTFLAT_H