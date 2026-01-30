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

#ifndef MULTIOPERATION_H
#define MULTIOPERATION_H

#include <QMainWindow>
#include "ui_MultiOperation.h"

class MultiOperation : public QMainWindow
{
	Q_OBJECT

public:
	MultiOperation(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~MultiOperation();

private slots:
    void on_pushButtonCreateNewConnect_clicked();

    void on_pushButtonUpdateConnect_clicked();

    void on_pushButtonDeleteConnect_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
	Ui::MultiOperationClass ui;
};

#endif // MULTIOPERATION_H