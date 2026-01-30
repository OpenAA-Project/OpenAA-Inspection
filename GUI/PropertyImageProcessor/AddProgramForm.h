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


#ifndef ADDPROGRAMFORM_H
#define ADDPROGRAMFORM_H

#include <QDialog>
#include "ui_AddProgramForm.h"
#include "XServiceForLayers.h"

class AddProgramForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	AddProgramForm(LayersBase *base, QWidget *parent);
	~AddProgramForm();
	
	QString	ProgName;

private:
	Ui::AddProgramFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // ADDPROGRAMFORM_H