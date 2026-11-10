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

#ifndef LOTBINDER_H
#define LOTBINDER_H

#include <QMainWindow>
#include "ui_LotBinder.h"

class LotBinder : public QMainWindow
{
	Q_OBJECT

public:
	LotBinder(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LotBinder();

private:
	Ui::LotBinderClass ui;
};

#endif // LOTBINDER_H