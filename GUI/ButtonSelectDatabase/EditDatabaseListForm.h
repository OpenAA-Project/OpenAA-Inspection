/*
 * Copyright (C) 2017
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

#ifndef EDITDATABASELISTFORM_H
#define EDITDATABASELISTFORM_H

#include <QDialog>
#include "ui_EditDatabaseListForm.h"
#include "XDatabaseList.h"
#include "XServiceForLayers.h"

class EditDatabaseListForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditDatabaseListForm(LayersBase *base, QWidget *parent = 0);
	~EditDatabaseListForm();

	DatabaseListContainer	DatabaseListData;

	void	ShowList(void);

private:
	Ui::EditDatabaseListFormClass ui;

private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonDel_clicked();
	void on_pushButtonMod_clicked();
	void on_pushButtonNew_clicked();
};

#endif // EDITDATABASELISTFORM_H