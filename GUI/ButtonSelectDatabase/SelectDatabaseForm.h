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

#ifndef SELECTDATABASEFORM_H
#define SELECTDATABASEFORM_H

#include <QDialog>
#include "ui_SelectDatabaseForm.h"
#include "XServiceForLayers.h"
#include "XDatabaseList.h"

class SelectDatabaseForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectDatabaseForm(LayersBase *Base,QWidget *parent = 0);
	~SelectDatabaseForm();

	DatabaseListContainer	DatabaseListData;

private:
	Ui::SelectDatabaseFormClass ui;

	void	ShowList(void);
	void	LoadData(void);


private slots:
	void on_pushButtonEdit_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonOk_clicked();
	void on_tableWidget_doubleClicked(QModelIndex);
};

#endif // SELECTDATABASEFORM_H