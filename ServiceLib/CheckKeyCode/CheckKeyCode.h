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

#ifndef CHECKKEYCODE_H
#define CHECKKEYCODE_H

#include <QMainWindow>
#include "ui_CheckKeyCode.h"
#include <QKeyEvent>

class CheckKeyCode : public QMainWindow
{
	Q_OBJECT

public:
	CheckKeyCode(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~CheckKeyCode();

private:
	Ui::CheckKeyCodeClass ui;

	virtual	void	keyPressEvent ( QKeyEvent * event )	override;
};

#endif // CHECKKEYCODE_H