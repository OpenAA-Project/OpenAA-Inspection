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

#ifndef COLORFORM_H
#define COLORFORM_H

#include <QDialog>
#include "ui_colorform.h"
 #include <QCloseEvent>
class colorForm : public QDialog
{
	Q_OBJECT
protected:
	void closeEvent(QCloseEvent *event);
public:
	colorForm(QWidget *parent = 0);
	~colorForm();
	Ui::colorFormClass ui;
private:
	bool cPalette(QPalette &palette);
    void widgetSetColor(QPalette palette, int x);
private slots:
	void on_tableWidget_cellClicked(int,int);
	void on_tableWidget_doubleClicked(QModelIndex);
	void on_pushButton_clicked();
	void on_lineEdit_selectionChanged();
};

#endif // COLORFORM_H