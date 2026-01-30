/*
 * Copyright (C) 2014
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

#ifndef EDITAXISIDFORM_H
#define EDITAXISIDFORM_H

#include <QDialog>
#include "ui_EditAxisIDForm.h"

class EditAxisIDForm : public QDialog
{
	Q_OBJECT

public:
	EditAxisIDForm(QWidget *parent = 0);
	~EditAxisIDForm();

	void	SetData(int axisID ,int centerInMaster ,int okZone);

	int	AxisID;
	int	CenterInMaster;
	int	OKZone;
private:
	Ui::EditAxisIDFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // EDITAXISIDFORM_H