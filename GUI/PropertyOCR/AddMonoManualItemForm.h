/*
 * Copyright (C) 2026
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

#ifndef ADDMONOMANUALITEMFORM_H
#define ADDMONOMANUALITEMFORM_H

#include <QDialog>
#include "ui_AddMonoManualItemForm.h"
#include "XTypeDef.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"

class AddMonoManualItemForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	AddMonoManualItemForm(LayersBase *base ,QWidget *parent);
	~AddMonoManualItemForm();

	int			Mergin;

	void	SetInitial(void);

private:
	Ui::AddMonoManualItemFormClass ui;

private slots:

	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
    void on_pushButtonOK_2_clicked();
    void on_pushButtonCancel_2_clicked();
};

#endif // ADDMONOMANUALITEMFORM_H